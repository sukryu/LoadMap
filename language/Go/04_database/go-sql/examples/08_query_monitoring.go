package examples

import (
	"context"
	"database/sql"
	"encoding/json"
	"fmt"
	"log"
	"strings"
	"sync"
	"time"

	_ "github.com/lib/pq"
)

// QueryMonitor는 데이터베이스 쿼리 성능을 모니터링하는 구조체입니다.
type QueryMonitor struct {
	db            *sql.DB
	metrics       *QueryPerformanceMetrics
	slowQueries   []*QueryExecution
	mu            sync.RWMutex
	slowThreshold time.Duration
}

// QueryPerformanceMetrics는 쿼리 성능 지표를 추적합니다.
type QueryPerformanceMetrics struct {
	TotalQueries         int64
	TotalExecutionTime   time.Duration
	AverageExecutionTime time.Duration
	SlowQueryCount       int64
	ErrorCount           int64
	QueryCountByType     map[string]int64
}

// QueryExecution은 개별 쿼리 실행에 대한 정보를 저장합니다.
type QueryExecution struct {
	Query        string
	Args         []interface{}
	StartTime    time.Time
	Duration     time.Duration
	Error        error
	RowsAffected int64
}

// QueryStats는 쿼리 통계 정보를 저장하는 구조체입니다.
type QueryStats struct {
	ExecutionCount  int64
	TotalDuration   time.Duration
	AverageDuration time.Duration
	LastExecutedAt  time.Time
	ErrorCount      int64
}

// NewQueryMonitor는 새로운 QueryMonitor를 생성합니다.
func NewQueryMonitor(connStr string, slowThreshold time.Duration) (*QueryMonitor, error) {
	db, err := sql.Open("postgres", connStr)
	if err != nil {
		return nil, fmt.Errorf("데이터베이스 연결 실패: %v", err)
	}

	return &QueryMonitor{
		db:            db,
		slowThreshold: slowThreshold,
		metrics: &QueryPerformanceMetrics{
			QueryCountByType: make(map[string]int64),
		},
		slowQueries: make([]*QueryExecution, 0),
	}, nil
}

// InitializeMonitoringSchema는 모니터링을 위한 테이블을 생성합니다.
func (qm *QueryMonitor) InitializeMonitoringSchema(ctx context.Context) error {
	queries := []string{
		`CREATE TABLE IF NOT EXISTS query_stats (
			id SERIAL PRIMARY KEY,
			query_hash TEXT NOT NULL,
			query_text TEXT NOT NULL,
			execution_count BIGINT NOT NULL DEFAULT 0,
			total_duration BIGINT NOT NULL DEFAULT 0,
			average_duration BIGINT NOT NULL DEFAULT 0,
			last_executed_at TIMESTAMP WITH TIME ZONE,
			error_count BIGINT NOT NULL DEFAULT 0
		)`,
		`CREATE INDEX IF NOT EXISTS idx_query_stats_hash ON query_stats(query_hash)`,
	}

	for _, query := range queries {
		if err := qm.ExecuteQuery(ctx, query); err != nil {
			return fmt.Errorf("모니터링 스키마 초기화 실패: %v", err)
		}
	}

	return nil
}

// ExecuteQuery는 쿼리를 실행하고 성능을 모니터링합니다.
func (qm *QueryMonitor) ExecuteQuery(ctx context.Context, query string, args ...interface{}) error {
	start := time.Now()
	var rowsAffected int64
	var execErr error

	// 쿼리 실행
	result, err := qm.db.ExecContext(ctx, query, args...)
	if err != nil {
		execErr = err
	} else if result != nil {
		rowsAffected, _ = result.RowsAffected()
	}

	duration := time.Since(start)

	// 쿼리 실행 정보 기록
	execution := &QueryExecution{
		Query:        query,
		Args:         args,
		StartTime:    start,
		Duration:     duration,
		Error:        execErr,
		RowsAffected: rowsAffected,
	}

	qm.recordQueryExecution(execution)

	return execErr
}

// recordQueryExecution은 쿼리 실행 정보를 기록합니다.
func (qm *QueryMonitor) recordQueryExecution(execution *QueryExecution) {
	qm.mu.Lock()
	defer qm.mu.Unlock()

	// 기본 메트릭 업데이트
	qm.metrics.TotalQueries++
	qm.metrics.TotalExecutionTime += execution.Duration
	qm.metrics.AverageExecutionTime = time.Duration(
		int64(qm.metrics.TotalExecutionTime) / qm.metrics.TotalQueries,
	)

	// 쿼리 타입별 카운트 업데이트
	queryType := qm.getQueryType(execution.Query)
	qm.metrics.QueryCountByType[queryType]++

	// 에러 카운트 업데이트
	if execution.Error != nil {
		qm.metrics.ErrorCount++
	}

	// 슬로우 쿼리 기록
	if execution.Duration >= qm.slowThreshold {
		qm.metrics.SlowQueryCount++
		qm.slowQueries = append(qm.slowQueries, execution)

		// 슬로우 쿼리 목록 크기 제한
		maxSlowQueries := 100
		if len(qm.slowQueries) > maxSlowQueries {
			qm.slowQueries = qm.slowQueries[1:]
		}
	}
}

// getQueryType은 SQL 쿼리의 타입을 반환합니다.
func (qm *QueryMonitor) getQueryType(query string) string {
	// 간단한 쿼리 타입 분류
	query = strings.TrimSpace(strings.ToUpper(query))
	if strings.HasPrefix(query, "SELECT") {
		return "SELECT"
	} else if strings.HasPrefix(query, "INSERT") {
		return "INSERT"
	} else if strings.HasPrefix(query, "UPDATE") {
		return "UPDATE"
	} else if strings.HasPrefix(query, "DELETE") {
		return "DELETE"
	}
	return "OTHER"
}

// GetSlowQueries는 기록된 슬로우 쿼리 목록을 반환합니다.
func (qm *QueryMonitor) GetSlowQueries() []*QueryExecution {
	qm.mu.RLock()
	defer qm.mu.RUnlock()

	// 복사본 반환
	result := make([]*QueryExecution, len(qm.slowQueries))
	copy(result, qm.slowQueries)
	return result
}

// GetMetrics는 현재 쿼리 성능 메트릭을 반환합니다.
func (qm *QueryMonitor) GetMetrics() QueryPerformanceMetrics {
	qm.mu.RLock()
	defer qm.mu.RUnlock()

	// 깊은 복사 수행
	metrics := *qm.metrics
	metrics.QueryCountByType = make(map[string]int64)
	for k, v := range qm.metrics.QueryCountByType {
		metrics.QueryCountByType[k] = v
	}
	return metrics
}

// GeneratePerformanceReport는 쿼리 성능 보고서를 생성합니다.
func (qm *QueryMonitor) GeneratePerformanceReport() string {
	metrics := qm.GetMetrics()
	slowQueries := qm.GetSlowQueries()

	report := map[string]interface{}{
		"summary": map[string]interface{}{
			"total_queries":          metrics.TotalQueries,
			"total_execution_time":   metrics.TotalExecutionTime.String(),
			"average_execution_time": metrics.AverageExecutionTime.String(),
			"slow_query_count":       metrics.SlowQueryCount,
			"error_count":            metrics.ErrorCount,
			"query_count_by_type":    metrics.QueryCountByType,
		},
		"slow_queries": make([]map[string]interface{}, 0),
	}

	for _, sq := range slowQueries {
		queryInfo := map[string]interface{}{
			"query":         sq.Query,
			"duration":      sq.Duration.String(),
			"start_time":    sq.StartTime,
			"rows_affected": sq.RowsAffected,
		}
		if sq.Error != nil {
			queryInfo["error"] = sq.Error.Error()
		}
		report["slow_queries"] = append(report["slow_queries"].([]map[string]interface{}), queryInfo)
	}

	jsonReport, _ := json.MarshalIndent(report, "", "  ")
	return string(jsonReport)
}

// Close는 데이터베이스 연결을 정리합니다.
func (qm *QueryMonitor) Close() error {
	return qm.db.Close()
}

// RunQueryMonitoringDemo는 쿼리 모니터링 예제를 실행합니다.
func RunQueryMonitoringDemo() {
	ctx := context.Background()
	connStr := "host=localhost port=5432 user=postgres password=postgres dbname=testdb sslmode=disable"

	// 2초 이상 걸리는 쿼리를 슬로우 쿼리로 간주
	qm, err := NewQueryMonitor(connStr, 2*time.Second)
	if err != nil {
		log.Fatalf("QueryMonitor 초기화 실패: %v", err)
	}
	defer qm.Close()

	// 모니터링 스키마 초기화
	if err := qm.InitializeMonitoringSchema(ctx); err != nil {
		log.Fatalf("모니터링 스키마 초기화 실패: %v", err)
	}

	// 테스트 쿼리 실행
	testQueries := []struct {
		name  string
		query string
	}{
		{
			name:  "빠른 SELECT 쿼리",
			query: "SELECT 1",
		},
		{
			name:  "의도적인 슬로우 쿼리",
			query: "SELECT pg_sleep(3)",
		},
		{
			name: "테이블 생성",
			query: `CREATE TABLE IF NOT EXISTS test_table (
				id SERIAL PRIMARY KEY,
				data TEXT
			)`,
		},
		{
			name:  "데이터 삽입",
			query: "INSERT INTO test_table (data) VALUES ('test data')",
		},
	}

	for _, test := range testQueries {
		log.Printf("%s 실행 중...", test.name)
		if err := qm.ExecuteQuery(ctx, test.query); err != nil {
			log.Printf("쿼리 실행 실패: %v", err)
		}
	}

	// 성능 보고서 생성 및 출력
	report := qm.GeneratePerformanceReport()
	log.Printf("\n쿼리 성능 보고서:\n%s", report)
}
