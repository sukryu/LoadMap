package examples

import (
	"context"
	"database/sql"
	"fmt"
	"log"
	"sync"
	"time"

	_ "github.com/lib/pq" // PostgreSQL 드라이버
)

// ConnectionStats는 연결 풀의 상태를 모니터링하기 위한 통계 정보를 저장합니다.
type ConnectionStats struct {
	ActiveConnections int           // 현재 활성 연결 수
	IdleConnections   int           // 현재 유휴 연결 수
	WaitCount         int64         // 연결을 기다린 총 횟수
	WaitDuration      time.Duration // 연결을 기다린 총 시간
	MaxIdleTimeClosed int64         // 최대 유휴 시간 초과로 닫힌 연결 수
	MaxLifetimeClosed int64         // 최대 수명 초과로 닫힌 연결 수
}

// PoolManager는 데이터베이스 연결 풀을 관리하고 모니터링하는 구조체입니다.
type PoolManager struct {
	db          *sql.DB
	stats       ConnectionStats
	mu          sync.RWMutex  // 통계 정보 동시성 보호
	monitorDone chan struct{} // 모니터링 고루틴 종료 신호
}

// NewPoolManager는 최적화된 설정으로 새로운 데이터베이스 연결 풀 관리자를 생성합니다.
func NewPoolManager(connStr string) (*PoolManager, error) {
	// 데이터베이스 연결을 초기화합니다.
	db, err := sql.Open("postgres", connStr)
	if err != nil {
		return nil, fmt.Errorf("데이터베이스 연결 초기화 실패: %v", err)
	}

	// 연결 풀 설정을 최적화합니다.
	db.SetMaxOpenConns(25)                  // 동시 연결 수 제한
	db.SetMaxIdleConns(10)                  // 유휴 연결 풀 크기
	db.SetConnMaxLifetime(30 * time.Minute) // 연결 최대 수명
	db.SetConnMaxIdleTime(5 * time.Minute)  // 유휴 연결 최대 시간

	pm := &PoolManager{
		db:          db,
		monitorDone: make(chan struct{}),
	}

	// 연결 풀 상태 모니터링을 시작합니다.
	go pm.monitorPool()

	return pm, nil
}

// monitorPool은 연결 풀의 상태를 주기적으로 모니터링합니다.
func (pm *PoolManager) monitorPool() {
	ticker := time.NewTicker(5 * time.Second)
	defer ticker.Stop()

	for {
		select {
		case <-ticker.C:
			stats := pm.db.Stats()

			pm.mu.Lock()
			pm.stats = ConnectionStats{
				ActiveConnections: stats.InUse,
				IdleConnections:   stats.Idle,
				WaitCount:         stats.WaitCount,
				WaitDuration:      stats.WaitDuration,
				MaxIdleTimeClosed: stats.MaxIdleTimeClosed,
				MaxLifetimeClosed: stats.MaxLifetimeClosed,
			}
			pm.mu.Unlock()

			// 연결 풀 상태를 로깅합니다.
			log.Printf("Pool Stats - Active: %d, Idle: %d, WaitCount: %d, WaitDuration: %v",
				stats.InUse, stats.Idle, stats.WaitCount, stats.WaitDuration)

		case <-pm.monitorDone:
			return
		}
	}
}

// ExecuteWithRetry는 일시적인 연결 문제를 처리하기 위해 재시도 로직을 구현합니다.
func (pm *PoolManager) ExecuteWithRetry(ctx context.Context, query string, args ...interface{}) error {
	maxRetries := 3
	var lastErr error

	for attempt := 0; attempt < maxRetries; attempt++ {
		if attempt > 0 {
			// 재시도 전에 잠시 대기합니다. 지수 백오프를 적용합니다.
			backoff := time.Duration(attempt*attempt) * time.Second
			time.Sleep(backoff)
		}

		// 컨텍스트가 취소되었는지 확인합니다.
		if ctx.Err() != nil {
			return ctx.Err()
		}

		// 쿼리를 실행합니다.
		_, err := pm.db.ExecContext(ctx, query, args...)
		if err == nil {
			return nil
		}

		lastErr = err
		log.Printf("쿼리 실행 실패 (시도 %d/%d): %v", attempt+1, maxRetries, err)
	}

	return fmt.Errorf("최대 재시도 횟수 초과 (%d회): %v", maxRetries, lastErr)
}

// SimulateConcurrentLoad는 동시 연결 부하를 시뮬레이션합니다.
func (pm *PoolManager) SimulateConcurrentLoad(ctx context.Context) error {
	// 동시 요청을 시뮬레이션하기 위한 작업자 수를 설정합니다.
	workerCount := 10
	requestsPerWorker := 5

	var wg sync.WaitGroup
	errorChan := make(chan error, workerCount*requestsPerWorker)

	// 여러 고루틴에서 동시에 데이터베이스에 접근합니다.
	for i := 0; i < workerCount; i++ {
		wg.Add(1)
		go func(workerID int) {
			defer wg.Done()

			for j := 0; j < requestsPerWorker; j++ {
				// 각 요청에 대해 새로운 컨텍스트를 생성합니다.
				requestCtx, cancel := context.WithTimeout(ctx, 5*time.Second)
				defer cancel()

				// 간단한 SELECT 쿼리를 실행합니다.
				query := "SELECT 1"
				if err := pm.ExecuteWithRetry(requestCtx, query); err != nil {
					errorChan <- fmt.Errorf("worker %d, request %d failed: %v", workerID, j, err)
				}

				// 실제 워크로드를 시뮬레이션하기 위해 잠시 대기합니다.
				time.Sleep(100 * time.Millisecond)
			}
		}(i)
	}

	// 모든 작업자가 완료될 때까지 대기합니다.
	wg.Wait()
	close(errorChan)

	// 발생한 모든 에러를 수집합니다.
	var errors []error
	for err := range errorChan {
		errors = append(errors, err)
	}

	if len(errors) > 0 {
		return fmt.Errorf("시뮬레이션 중 %d개의 에러 발생: %v", len(errors), errors[0])
	}

	return nil
}

// GetStats는 현재 연결 풀의 통계 정보를 반환합니다.
func (pm *PoolManager) GetStats() ConnectionStats {
	pm.mu.RLock()
	defer pm.mu.RUnlock()
	return pm.stats
}

// Close는 연결 풀과 모니터링을 정리합니다.
func (pm *PoolManager) Close() error {
	// 모니터링 고루틴을 종료합니다.
	close(pm.monitorDone)

	// 데이터베이스 연결을 닫습니다.
	return pm.db.Close()
}

// RunConnectionPoolingDemo는 연결 풀링 예제를 실행합니다.
func RunConnectionPoolingDemo() {
	// 컨텍스트를 생성하고 타임아웃을 설정합니다.
	ctx, cancel := context.WithTimeout(context.Background(), 1*time.Minute)
	defer cancel()

	// 데이터베이스 연결 문자열을 설정합니다.
	connStr := "host=localhost port=5432 user=postgres password=postgres dbname=testdb sslmode=disable"

	// 풀 관리자를 초기화합니다.
	pm, err := NewPoolManager(connStr)
	if err != nil {
		log.Fatalf("풀 관리자 초기화 실패: %v", err)
	}
	defer pm.Close()

	// 동시 부하를 시뮬레이션합니다.
	log.Println("동시 부하 시뮬레이션 시작...")
	if err := pm.SimulateConcurrentLoad(ctx); err != nil {
		log.Printf("부하 시뮬레이션 중 에러 발생: %v", err)
	}

	// 최종 통계를 출력합니다.
	stats := pm.GetStats()
	log.Printf("최종 통계:\n"+
		"활성 연결: %d\n"+
		"유휴 연결: %d\n"+
		"대기 횟수: %d\n"+
		"총 대기 시간: %v\n"+
		"최대 유휴 시간 초과로 닫힌 연결: %d\n"+
		"최대 수명 초과로 닫힌 연결: %d\n",
		stats.ActiveConnections,
		stats.IdleConnections,
		stats.WaitCount,
		stats.WaitDuration,
		stats.MaxIdleTimeClosed,
		stats.MaxLifetimeClosed)
}
