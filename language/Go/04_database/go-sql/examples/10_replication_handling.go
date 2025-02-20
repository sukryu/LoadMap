// examples/10_replication_handling.go

package examples

import (
	"context"
	"database/sql"
	"errors"
	"fmt"
	"log"
	"sync"
	"time"

	_ "github.com/lib/pq"
)

// ReplicationManager는 데이터베이스 복제 및 읽기/쓰기 분리를 관리하는 구조체입니다.
type ReplicationManager struct {
	master         *sql.DB
	replicas       []*sql.DB
	currentReplica int
	metrics        *ReplicationMetrics
	mu             sync.RWMutex
	healthCheck    *time.Ticker
}

// ReplicationMetrics는 복제 관련 메트릭을 추적합니다.
type ReplicationMetrics struct {
	TotalReads       int64
	TotalWrites      int64
	FailedReads      int64
	FailedWrites     int64
	FailoverCount    int64
	ReplicaLag       time.Duration
	LastFailoverTime time.Time
}

// DatabaseConfig는 데이터베이스 연결 설정을 저장합니다.
type DatabaseConfig struct {
	Host     string
	Port     int
	User     string
	Password string
	Database string
	SSLMode  string
}

// NewReplicationManager는 새로운 ReplicationManager를 생성합니다.
func NewReplicationManager(masterConfig DatabaseConfig, replicaConfigs []DatabaseConfig) (*ReplicationManager, error) {
	// 마스터 데이터베이스 연결
	master, err := connectToDatabase(masterConfig)
	if err != nil {
		return nil, fmt.Errorf("마스터 데이터베이스 연결 실패: %v", err)
	}

	// 레플리카 데이터베이스 연결
	replicas := make([]*sql.DB, 0, len(replicaConfigs))
	for _, config := range replicaConfigs {
		replica, err := connectToDatabase(config)
		if err != nil {
			log.Printf("레플리카 연결 실패 (%s:%d): %v", config.Host, config.Port, err)
			continue
		}
		replicas = append(replicas, replica)
	}

	if len(replicas) == 0 {
		return nil, errors.New("사용 가능한 레플리카가 없습니다")
	}

	rm := &ReplicationManager{
		master:      master,
		replicas:    replicas,
		metrics:     &ReplicationMetrics{},
		healthCheck: time.NewTicker(10 * time.Second),
	}

	// 상태 체크 고루틴 시작
	go rm.startHealthCheck()

	return rm, nil
}

// connectToDatabase는 지정된 설정으로 데이터베이스에 연결합니다.
func connectToDatabase(config DatabaseConfig) (*sql.DB, error) {
	connStr := fmt.Sprintf(
		"host=%s port=%d user=%s password=%s dbname=%s sslmode=%s",
		config.Host, config.Port, config.User, config.Password, config.Database, config.SSLMode,
	)

	db, err := sql.Open("postgres", connStr)
	if err != nil {
		return nil, err
	}

	// 연결 풀 설정
	db.SetMaxOpenConns(25)
	db.SetMaxIdleConns(10)
	db.SetConnMaxLifetime(5 * time.Minute)

	// 연결 테스트
	if err := db.Ping(); err != nil {
		db.Close()
		return nil, err
	}

	return db, nil
}

// ExecuteRead는 읽기 작업을 레플리카에서 실행합니다.
func (rm *ReplicationManager) ExecuteRead(ctx context.Context, query string, args ...interface{}) (*sql.Rows, error) {
	rm.mu.RLock()
	replica := rm.replicas[rm.currentReplica]
	rm.mu.RUnlock()

	rows, err := replica.QueryContext(ctx, query, args...)

	rm.mu.Lock()
	rm.metrics.TotalReads++
	if err != nil {
		rm.metrics.FailedReads++
		// 실패 시 다음 레플리카로 전환
		rm.currentReplica = (rm.currentReplica + 1) % len(rm.replicas)
	}
	rm.mu.Unlock()

	return rows, err
}

// ExecuteWrite는 쓰기 작업을 마스터에서 실행합니다.
func (rm *ReplicationManager) ExecuteWrite(ctx context.Context, query string, args ...interface{}) (sql.Result, error) {
	result, err := rm.master.ExecContext(ctx, query, args...)

	rm.mu.Lock()
	rm.metrics.TotalWrites++
	if err != nil {
		rm.metrics.FailedWrites++
	}
	rm.mu.Unlock()

	return result, err
}

// checkReplicationLag은 마스터와 레플리카 간의 복제 지연을 확인합니다.
func (rm *ReplicationManager) checkReplicationLag(ctx context.Context, replica *sql.DB) (time.Duration, error) {
	// 마스터에 타임스탬프 기록
	timestamp := time.Now()
	_, err := rm.master.ExecContext(ctx, "CREATE TABLE IF NOT EXISTS replication_check (ts TIMESTAMP)")
	if err != nil {
		return 0, err
	}

	_, err = rm.master.ExecContext(ctx, "INSERT INTO replication_check (ts) VALUES ($1)", timestamp)
	if err != nil {
		return 0, err
	}

	// 레플리카에서 타임스탬프 확인
	var replicaTs time.Time
	maxAttempts := 10
	for i := 0; i < maxAttempts; i++ {
		err = replica.QueryRowContext(ctx, "SELECT MAX(ts) FROM replication_check").Scan(&replicaTs)
		if err == nil && !replicaTs.IsZero() {
			break
		}
		time.Sleep(100 * time.Millisecond)
	}

	if err != nil || replicaTs.IsZero() {
		return 0, fmt.Errorf("복제 지연 확인 실패: %v", err)
	}

	return timestamp.Sub(replicaTs), nil
}

// startHealthCheck는 주기적으로 데이터베이스 상태를 확인합니다.
func (rm *ReplicationManager) startHealthCheck() {
	for range rm.healthCheck.C {
		ctx := context.Background()

		// 마스터 상태 확인
		if err := rm.master.PingContext(ctx); err != nil {
			log.Printf("마스터 데이터베이스 연결 실패: %v", err)
		}

		// 레플리카 상태 및 복제 지연 확인
		for i, replica := range rm.replicas {
			if err := replica.PingContext(ctx); err != nil {
				log.Printf("레플리카 %d 연결 실패: %v", i, err)
				continue
			}

			lag, err := rm.checkReplicationLag(ctx, replica)
			if err != nil {
				log.Printf("레플리카 %d 복제 지연 확인 실패: %v", i, err)
				continue
			}

			rm.mu.Lock()
			rm.metrics.ReplicaLag = lag
			rm.mu.Unlock()

			// 복제 지연이 너무 큰 경우 경고
			if lag > 10*time.Second {
				log.Printf("경고: 레플리카 %d의 복제 지연이 큽니다: %v", i, lag)
			}
		}
	}
}

// performFailover는 마스터 장애 시 새로운 마스터를 선택합니다.
func (rm *ReplicationManager) performFailover(ctx context.Context) error {
	rm.mu.Lock()
	defer rm.mu.Unlock()

	// 가장 최신 데이터를 가진 레플리카 선택
	var bestReplica *sql.DB
	var minLag time.Duration = time.Hour

	for _, replica := range rm.replicas {
		lag, err := rm.checkReplicationLag(ctx, replica)
		if err != nil {
			continue
		}
		if lag < minLag {
			minLag = lag
			bestReplica = replica
		}
	}

	if bestReplica == nil {
		return errors.New("페일오버를 위한 적절한 레플리카를 찾을 수 없습니다")
	}

	// 새로운 마스터로 승격
	oldMaster := rm.master
	rm.master = bestReplica
	rm.replicas = append(rm.replicas, oldMaster)
	rm.metrics.FailoverCount++
	rm.metrics.LastFailoverTime = time.Now()

	return nil
}

// GetMetrics는 현재 복제 메트릭을 반환합니다.
func (rm *ReplicationManager) GetMetrics() ReplicationMetrics {
	rm.mu.RLock()
	defer rm.mu.RUnlock()
	return *rm.metrics
}

// Close는 모든 데이터베이스 연결을 정리합니다.
func (rm *ReplicationManager) Close() error {
	rm.healthCheck.Stop()

	if err := rm.master.Close(); err != nil {
		log.Printf("마스터 연결 종료 실패: %v", err)
	}

	for i, replica := range rm.replicas {
		if err := replica.Close(); err != nil {
			log.Printf("레플리카 %d 연결 종료 실패: %v", i, err)
		}
	}

	return nil
}

// RunReplicationHandlingDemo는 복제 처리 예제를 실행합니다.
func RunReplicationHandlingDemo() {
	// 데이터베이스 설정
	masterConfig := DatabaseConfig{
		Host:     "localhost",
		Port:     5432,
		User:     "postgres",
		Password: "postgres",
		Database: "testdb",
		SSLMode:  "disable",
	}

	replicaConfigs := []DatabaseConfig{
		{
			Host:     "localhost",
			Port:     5433,
			User:     "postgres",
			Password: "postgres",
			Database: "testdb",
			SSLMode:  "disable",
		},
		{
			Host:     "localhost",
			Port:     5434,
			User:     "postgres",
			Password: "postgres",
			Database: "testdb",
			SSLMode:  "disable",
		},
	}

	rm, err := NewReplicationManager(masterConfig, replicaConfigs)
	if err != nil {
		log.Fatalf("ReplicationManager 초기화 실패: %v", err)
	}
	defer rm.Close()

	ctx := context.Background()

	// 테스트 테이블 생성 (마스터에서 실행)
	_, err = rm.ExecuteWrite(ctx, `
		CREATE TABLE IF NOT EXISTS test_replication (
			id SERIAL PRIMARY KEY,
			data TEXT,
			created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
		)
	`)
	if err != nil {
		log.Printf("테이블 생성 실패: %v", err)
	}

	// 데이터 쓰기 테스트
	for i := 0; i < 5; i++ {
		data := fmt.Sprintf("test-data-%d", i)
		_, err := rm.ExecuteWrite(ctx, "INSERT INTO test_replication (data) VALUES ($1)", data)
		if err != nil {
			log.Printf("데이터 쓰기 실패: %v", err)
			continue
		}
	}

	// 데이터 읽기 테스트
	rows, err := rm.ExecuteRead(ctx, "SELECT id, data, created_at FROM test_replication")
	if err != nil {
		log.Printf("데이터 읽기 실패: %v", err)
	} else {
		defer rows.Close()
		for rows.Next() {
			var (
				id        int
				data      string
				createdAt time.Time
			)
			if err := rows.Scan(&id, &data, &createdAt); err != nil {
				log.Printf("데이터 스캔 실패: %v", err)
				continue
			}
			log.Printf("읽은 데이터: ID=%d, Data=%s, CreatedAt=%v", id, data, createdAt)
		}
	}

	// 페일오버 시뮬레이션
	log.Println("페일오버 시뮬레이션 시작...")
	if err := rm.performFailover(ctx); err != nil {
		log.Printf("페일오버 실패: %v", err)
	} else {
		log.Println("페일오버 성공")
	}

	// 메트릭스 출력
	metrics := rm.GetMetrics()
	log.Printf("\n복제 처리 메트릭스:\n"+
		"총 읽기 작업: %d\n"+
		"총 쓰기 작업: %d\n"+
		"실패한 읽기: %d\n"+
		"실패한 쓰기: %d\n"+
		"페일오버 횟수: %d\n"+
		"복제 지연: %v\n"+
		"마지막 페일오버: %v",
		metrics.TotalReads,
		metrics.TotalWrites,
		metrics.FailedReads,
		metrics.FailedWrites,
		metrics.FailoverCount,
		metrics.ReplicaLag,
		metrics.LastFailoverTime)
}
