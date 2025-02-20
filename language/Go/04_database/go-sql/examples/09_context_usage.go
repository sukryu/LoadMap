package examples

import (
	"context"
	"database/sql"
	"fmt"
	"log"
	"sync"
	"time"

	_ "github.com/lib/pq"
)

// ContextManager는 컨텍스트를 활용한 데이터베이스 작업을 관리하는 구조체입니다.
type ContextManager struct {
	db      *sql.DB
	metrics *ContextMetrics
	mu      sync.RWMutex
}

// ContextMetrics는 컨텍스트 관련 작업의 메트릭을 추적합니다.
type ContextMetrics struct {
	TotalOperations      int64
	TimeoutCount         int64
	CancelledCount       int64
	DeadlineExceeded     int64
	SuccessfulOperations int64
	AverageResponseTime  time.Duration
}

// TaskResult는 비동기 작업의 결과를 저장하는 구조체입니다.
type TaskResult struct {
	ID        int
	Status    string
	StartTime time.Time
	EndTime   time.Time
	Error     error
}

// NewContextManager는 새로운 ContextManager를 생성합니다.
func NewContextManager(connStr string) (*ContextManager, error) {
	db, err := sql.Open("postgres", connStr)
	if err != nil {
		return nil, fmt.Errorf("데이터베이스 연결 실패: %v", err)
	}

	return &ContextManager{
		db:      db,
		metrics: &ContextMetrics{},
	}, nil
}

// InitializeTaskSchema는 작업 추적을 위한 테이블을 생성합니다.
func (cm *ContextManager) InitializeTaskSchema(ctx context.Context) error {
	query := `
		CREATE TABLE IF NOT EXISTS tasks (
			id SERIAL PRIMARY KEY,
			status VARCHAR(50) NOT NULL,
			start_time TIMESTAMP WITH TIME ZONE NOT NULL,
			end_time TIMESTAMP WITH TIME ZONE,
			error_message TEXT
		)
	`
	_, err := cm.db.ExecContext(ctx, query)
	if err != nil {
		return fmt.Errorf("테이블 생성 실패: %v", err)
	}
	return nil
}

// ExecuteWithTimeout은 지정된 시간 내에 작업을 실행합니다.
func (cm *ContextManager) ExecuteWithTimeout(baseCtx context.Context, query string, timeout time.Duration) error {
	ctx, cancel := context.WithTimeout(baseCtx, timeout)
	defer cancel()

	start := time.Now()
	done := make(chan error, 1)

	go func() {
		_, err := cm.db.ExecContext(ctx, query)
		done <- err
	}()

	select {
	case err := <-done:
		cm.recordMetrics(start, nil)
		return err
	case <-ctx.Done():
		cm.recordMetrics(start, ctx.Err())
		if ctx.Err() == context.DeadlineExceeded {
			cm.mu.Lock()
			cm.metrics.TimeoutCount++
			cm.mu.Unlock()
			return fmt.Errorf("작업 시간 초과: %v", timeout)
		}
		return ctx.Err()
	}
}

// ExecuteWithDeadline은 지정된 마감 시간 내에 작업을 실행합니다.
func (cm *ContextManager) ExecuteWithDeadline(baseCtx context.Context, query string, deadline time.Time) error {
	ctx, cancel := context.WithDeadline(baseCtx, deadline)
	defer cancel()

	start := time.Now()
	done := make(chan error, 1)

	go func() {
		_, err := cm.db.ExecContext(ctx, query)
		done <- err
	}()

	select {
	case err := <-done:
		cm.recordMetrics(start, nil)
		return err
	case <-ctx.Done():
		cm.recordMetrics(start, ctx.Err())
		if ctx.Err() == context.DeadlineExceeded {
			cm.mu.Lock()
			cm.metrics.DeadlineExceeded++
			cm.mu.Unlock()
			return fmt.Errorf("마감 시간 초과: %v", deadline)
		}
		return ctx.Err()
	}
}

// ExecuteBatchWithContext는 여러 작업을 동시에 실행하고 컨텍스트로 제어합니다.
func (cm *ContextManager) ExecuteBatchWithContext(ctx context.Context, queries []string) []error {
	results := make([]error, len(queries))
	var wg sync.WaitGroup

	for i, query := range queries {
		wg.Add(1)
		go func(index int, q string) {
			defer wg.Done()
			start := time.Now()

			done := make(chan error, 1)
			go func() {
				_, err := cm.db.ExecContext(ctx, q)
				done <- err
			}()

			select {
			case err := <-done:
				cm.recordMetrics(start, err)
				results[index] = err
			case <-ctx.Done():
				cm.recordMetrics(start, ctx.Err())
				cm.mu.Lock()
				cm.metrics.CancelledCount++
				cm.mu.Unlock()
				results[index] = ctx.Err()
			}
		}(i, query)
	}

	wg.Wait()
	return results
}

// ExecuteLongRunningTask는 장시간 실행되는 작업을 관리합니다.
func (cm *ContextManager) ExecuteLongRunningTask(ctx context.Context, taskID int) (*TaskResult, error) {
	result := &TaskResult{
		ID:        taskID,
		StartTime: time.Now(),
	}

	// 작업 시작 기록
	if err := cm.recordTaskStart(ctx, result); err != nil {
		return nil, fmt.Errorf("작업 시작 기록 실패: %v", err)
	}

	// 작업 실행
	done := make(chan error, 1)
	go func() {
		// 장시간 실행되는 작업 시뮬레이션
		time.Sleep(5 * time.Second)
		done <- nil
	}()

	// 작업 완료 또는 컨텍스트 취소 대기
	select {
	case err := <-done:
		result.EndTime = time.Now()
		result.Status = "completed"
		result.Error = err
		if err := cm.recordTaskCompletion(ctx, result); err != nil {
			return nil, fmt.Errorf("작업 완료 기록 실패: %v", err)
		}
		return result, nil
	case <-ctx.Done():
		result.EndTime = time.Now()
		result.Status = "cancelled"
		result.Error = ctx.Err()
		if err := cm.recordTaskCancellation(ctx, result); err != nil {
			return nil, fmt.Errorf("작업 취소 기록 실패: %v", err)
		}
		return result, ctx.Err()
	}
}

// recordTaskStart는 작업 시작을 데이터베이스에 기록합니다.
func (cm *ContextManager) recordTaskStart(ctx context.Context, result *TaskResult) error {
	query := `
		INSERT INTO tasks (id, status, start_time)
		VALUES ($1, 'running', $2)
	`
	_, err := cm.db.ExecContext(ctx, query, result.ID, result.StartTime)
	return err
}

// recordTaskCompletion은 작업 완료를 데이터베이스에 기록합니다.
func (cm *ContextManager) recordTaskCompletion(ctx context.Context, result *TaskResult) error {
	query := `
		UPDATE tasks 
		SET status = 'completed', end_time = $1
		WHERE id = $2
	`
	_, err := cm.db.ExecContext(ctx, query, result.EndTime, result.ID)
	return err
}

// recordTaskCancellation은 작업 취소를 데이터베이스에 기록합니다.
func (cm *ContextManager) recordTaskCancellation(ctx context.Context, result *TaskResult) error {
	query := `
		UPDATE tasks 
		SET status = 'cancelled', end_time = $1, error_message = $2
		WHERE id = $3
	`
	_, err := cm.db.ExecContext(ctx, query, result.EndTime, result.Error.Error(), result.ID)
	return err
}

// recordMetrics는 작업 메트릭을 기록합니다.
func (cm *ContextManager) recordMetrics(start time.Time, err error) {
	cm.mu.Lock()
	defer cm.mu.Unlock()

	duration := time.Since(start)
	cm.metrics.TotalOperations++

	if err == nil {
		cm.metrics.SuccessfulOperations++
	}

	// 평균 응답 시간 업데이트
	cm.metrics.AverageResponseTime = time.Duration(
		(int64(cm.metrics.AverageResponseTime)*(cm.metrics.TotalOperations-1) +
			int64(duration)) / cm.metrics.TotalOperations,
	)
}

// GetMetrics는 현재 컨텍스트 메트릭을 반환합니다.
func (cm *ContextManager) GetMetrics() ContextMetrics {
	cm.mu.RLock()
	defer cm.mu.RUnlock()
	return *cm.metrics
}

// Close는 데이터베이스 연결을 정리합니다.
func (cm *ContextManager) Close() error {
	return cm.db.Close()
}

// RunContextUsageDemo는 컨텍스트 사용 예제를 실행합니다.
func RunContextUsageDemo() {
	baseCtx := context.Background()
	connStr := "host=localhost port=5432 user=postgres password=postgres dbname=testdb sslmode=disable"

	cm, err := NewContextManager(connStr)
	if err != nil {
		log.Fatalf("ContextManager 초기화 실패: %v", err)
	}
	defer cm.Close()

	// 스키마 초기화
	if err := cm.InitializeTaskSchema(baseCtx); err != nil {
		log.Fatalf("스키마 초기화 실패: %v", err)
	}

	// 타임아웃이 있는 작업 실행
	log.Println("타임아웃이 있는 작업 실행 중...")
	err = cm.ExecuteWithTimeout(baseCtx, "SELECT pg_sleep(2)", 1*time.Second)
	if err != nil {
		log.Printf("예상된 타임아웃 발생: %v", err)
	}

	// 마감시간이 있는 작업 실행
	log.Println("마감시간이 있는 작업 실행 중...")
	deadline := time.Now().Add(2 * time.Second)
	err = cm.ExecuteWithDeadline(baseCtx, "SELECT pg_sleep(3)", deadline)
	if err != nil {
		log.Printf("예상된 마감시간 초과: %v", err)
	}

	// 배치 작업 실행
	log.Println("배치 작업 실행 중...")
	ctx, cancel := context.WithTimeout(baseCtx, 5*time.Second)
	queries := []string{
		"SELECT pg_sleep(1)",
		"SELECT pg_sleep(2)",
		"SELECT pg_sleep(3)",
	}
	errors := cm.ExecuteBatchWithContext(ctx, queries)
	for i, err := range errors {
		if err != nil {
			log.Printf("배치 작업 %d 실패: %v", i+1, err)
		}
	}
	cancel()

	// 장시간 실행 작업 테스트
	log.Println("장시간 실행 작업 테스트 중...")
	ctx, cancel = context.WithTimeout(baseCtx, 3*time.Second)
	result, err := cm.ExecuteLongRunningTask(ctx, 1)
	if err != nil {
		log.Printf("장시간 작업 실패: %v", err)
	} else {
		log.Printf("작업 결과: ID=%d, Status=%s, Duration=%v",
			result.ID, result.Status, result.EndTime.Sub(result.StartTime))
	}
	cancel()

	// 메트릭스 출력
	metrics := cm.GetMetrics()
	log.Printf("\n컨텍스트 사용 메트릭스:\n"+
		"총 작업 수: %d\n"+
		"성공한 작업 수: %d\n"+
		"타임아웃 횟수: %d\n"+
		"취소된 작업 수: %d\n"+
		"마감시간 초과 횟수: %d\n"+
		"평균 응답 시간: %v",
		metrics.TotalOperations,
		metrics.SuccessfulOperations,
		metrics.TimeoutCount,
		metrics.CancelledCount,
		metrics.DeadlineExceeded,
		metrics.AverageResponseTime)
}
