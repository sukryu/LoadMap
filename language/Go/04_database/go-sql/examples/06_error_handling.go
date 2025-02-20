// examples/06_error_handling.go

package examples

import (
	"context"
	"database/sql"
	"errors"
	"fmt"
	"log"
	"net"
	"strings"
	"sync"
	"time"

	_ "github.com/lib/pq"
)

// DatabaseError는 데이터베이스 작업 중 발생하는 에러를 래핑합니다.
type DatabaseError struct {
	Operation string
	Err       error
}

func (e *DatabaseError) Error() string {
	return fmt.Sprintf("데이터베이스 작업 실패 (%s): %v", e.Operation, e.Err)
}

func (e *DatabaseError) Unwrap() error {
	return e.Err
}

// ValidationError는 데이터 유효성 검사 실패를 나타냅니다.
type ValidationError struct {
	Field string
	Value interface{}
	Msg   string
}

func (e *ValidationError) Error() string {
	return fmt.Sprintf("유효성 검사 실패 (필드: %s, 값: %v): %s", e.Field, e.Value, e.Msg)
}

// RetryableError는 재시도 가능한 에러를 나타냅니다.
type RetryableError struct {
	OriginalErr error
	Attempt     int
	MaxAttempts int
}

func (e *RetryableError) Error() string {
	return fmt.Sprintf("재시도 가능한 에러 (시도: %d/%d): %v", e.Attempt, e.MaxAttempts, e.OriginalErr)
}

func (e *RetryableError) Unwrap() error {
	return e.OriginalErr
}

// ErrorHandler는 데이터베이스 에러 처리를 관리하는 구조체입니다.
type ErrorHandler struct {
	db      *sql.DB
	metrics *ErrorMetrics
	mu      sync.RWMutex
}

// ErrorMetrics는 에러 처리 관련 메트릭을 추적합니다.
type ErrorMetrics struct {
	TotalErrors      int64
	ValidationErrors int64
	NetworkErrors    int64
	RetryAttempts    int64
	RecoveredErrors  int64
	LastError        time.Time
}

// OrderData는 주문 정보를 저장하는 구조체입니다.
type OrderData struct {
	ID         int
	CustomerID int
	Amount     float64
	Status     string
	CreatedAt  time.Time
}

// NewErrorHandler는 새로운 ErrorHandler 인스턴스를 생성합니다.
func NewErrorHandler(connStr string) (*ErrorHandler, error) {
	db, err := sql.Open("postgres", connStr)
	if err != nil {
		return nil, fmt.Errorf("데이터베이스 연결 실패: %v", err)
	}

	return &ErrorHandler{
		db:      db,
		metrics: &ErrorMetrics{},
	}, nil
}

// InitializeOrderSchema는 주문 테이블을 생성합니다.
func (eh *ErrorHandler) InitializeOrderSchema(ctx context.Context) error {
	query := `
		CREATE TABLE IF NOT EXISTS orders (
			id SERIAL PRIMARY KEY,
			customer_id INTEGER NOT NULL,
			amount DECIMAL(10,2) NOT NULL,
			status VARCHAR(20) NOT NULL,
			created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
		)
	`
	if err := eh.executeWithRetry(ctx, "스키마 초기화", func() error {
		_, err := eh.db.ExecContext(ctx, query)
		return err
	}); err != nil {
		return &DatabaseError{Operation: "스키마 초기화", Err: err}
	}
	return nil
}

// executeWithRetry는 작업을 재시도 로직과 함께 실행합니다.
func (eh *ErrorHandler) executeWithRetry(ctx context.Context, operation string, fn func() error) error {
	maxAttempts := 3
	backoff := time.Second

	var lastErr error
	for attempt := 1; attempt <= maxAttempts; attempt++ {
		err := fn()
		if err == nil {
			return nil
		}

		lastErr = err
		eh.mu.Lock()
		eh.metrics.TotalErrors++
		eh.metrics.RetryAttempts++
		eh.metrics.LastError = time.Now()
		eh.mu.Unlock()

		// 네트워크 에러 확인
		var netErr net.Error
		if errors.As(err, &netErr) {
			eh.mu.Lock()
			eh.metrics.NetworkErrors++
			eh.mu.Unlock()
		}

		// 재시도 불가능한 에러인 경우 즉시 반환
		if !eh.isRetryableError(err) {
			return &DatabaseError{Operation: operation, Err: err}
		}

		// 마지막 시도가 아닌 경우 대기 후 재시도
		if attempt < maxAttempts {
			select {
			case <-ctx.Done():
				return ctx.Err()
			case <-time.After(backoff):
				backoff *= 2 // 지수 백오프
			}
			continue
		}
	}

	return &RetryableError{
		OriginalErr: lastErr,
		Attempt:     maxAttempts,
		MaxAttempts: maxAttempts,
	}
}

// isRetryableError는 주어진 에러가 재시도 가능한지 확인합니다.
func (eh *ErrorHandler) isRetryableError(err error) bool {
	if err == nil {
		return false
	}

	// 네트워크 에러 확인
	var netErr net.Error
	if errors.As(err, &netErr) {
		return true
	}

	// PostgreSQL 특정 에러 확인
	if strings.Contains(err.Error(), "deadlock detected") ||
		strings.Contains(err.Error(), "connection reset by peer") ||
		strings.Contains(err.Error(), "broken pipe") {
		return true
	}

	return false
}

// validateOrder는 주문 데이터의 유효성을 검사합니다.
func (eh *ErrorHandler) validateOrder(order *OrderData) error {
	if order.CustomerID <= 0 {
		return &ValidationError{
			Field: "customer_id",
			Value: order.CustomerID,
			Msg:   "고객 ID는 양수여야 합니다",
		}
	}

	if order.Amount <= 0 {
		return &ValidationError{
			Field: "amount",
			Value: order.Amount,
			Msg:   "주문 금액은 양수여야 합니다",
		}
	}

	validStatuses := map[string]bool{
		"pending":   true,
		"completed": true,
		"cancelled": true,
	}
	if !validStatuses[order.Status] {
		return &ValidationError{
			Field: "status",
			Value: order.Status,
			Msg:   "유효하지 않은 주문 상태입니다",
		}
	}

	return nil
}

// CreateOrder는 새로운 주문을 생성합니다.
func (eh *ErrorHandler) CreateOrder(ctx context.Context, order *OrderData) error {
	if err := eh.validateOrder(order); err != nil {
		eh.mu.Lock()
		eh.metrics.ValidationErrors++
		eh.mu.Unlock()
		return err
	}

	query := `
		INSERT INTO orders (customer_id, amount, status)
		VALUES ($1, $2, $3)
		RETURNING id, created_at
	`

	err := eh.executeWithRetry(ctx, "주문 생성", func() error {
		return eh.db.QueryRowContext(ctx, query,
			order.CustomerID,
			order.Amount,
			order.Status,
		).Scan(&order.ID, &order.CreatedAt)
	})

	if err != nil {
		return &DatabaseError{Operation: "주문 생성", Err: err}
	}

	return nil
}

// UpdateOrderStatus는 주문 상태를 업데이트합니다.
func (eh *ErrorHandler) UpdateOrderStatus(ctx context.Context, orderID int, newStatus string) error {
	if orderID <= 0 {
		return &ValidationError{
			Field: "order_id",
			Value: orderID,
			Msg:   "주문 ID는 양수여야 합니다",
		}
	}

	validStatuses := map[string]bool{
		"pending":   true,
		"completed": true,
		"cancelled": true,
	}
	if !validStatuses[newStatus] {
		return &ValidationError{
			Field: "status",
			Value: newStatus,
			Msg:   "유효하지 않은 주문 상태입니다",
		}
	}

	query := "UPDATE orders SET status = $1 WHERE id = $2"

	err := eh.executeWithRetry(ctx, "주문 상태 업데이트", func() error {
		result, err := eh.db.ExecContext(ctx, query, newStatus, orderID)
		if err != nil {
			return err
		}

		rows, err := result.RowsAffected()
		if err != nil {
			return err
		}
		if rows == 0 {
			return fmt.Errorf("주문을 찾을 수 없습니다: %d", orderID)
		}
		return nil
	})

	if err != nil {
		return &DatabaseError{Operation: "주문 상태 업데이트", Err: err}
	}

	return nil
}

// GetMetrics는 현재 에러 처리 메트릭을 반환합니다.
func (eh *ErrorHandler) GetMetrics() ErrorMetrics {
	eh.mu.RLock()
	defer eh.mu.RUnlock()
	return *eh.metrics
}

// Close는 데이터베이스 연결을 정리합니다.
func (eh *ErrorHandler) Close() error {
	return eh.db.Close()
}

// RunErrorHandlingDemo는 에러 처리 예제를 실행합니다.
func RunErrorHandlingDemo() {
	ctx := context.Background()
	connStr := "host=localhost port=5432 user=postgres password=postgres dbname=testdb sslmode=disable"

	eh, err := NewErrorHandler(connStr)
	if err != nil {
		log.Fatalf("ErrorHandler 초기화 실패: %v", err)
	}
	defer eh.Close()

	// 스키마 초기화
	if err := eh.InitializeOrderSchema(ctx); err != nil {
		log.Printf("스키마 초기화 실패: %v", err)
	}

	// 유효한 주문 생성
	validOrder := &OrderData{
		CustomerID: 1,
		Amount:     99.99,
		Status:     "pending",
	}
	if err := eh.CreateOrder(ctx, validOrder); err != nil {
		log.Printf("주문 생성 실패: %v", err)
	} else {
		log.Printf("주문이 성공적으로 생성되었습니다: ID=%d", validOrder.ID)
	}

	// 유효하지 않은 주문 시도
	invalidOrder := &OrderData{
		CustomerID: -1,
		Amount:     -50.0,
		Status:     "invalid_status",
	}
	if err := eh.CreateOrder(ctx, invalidOrder); err != nil {
		log.Printf("예상된 유효성 검사 실패: %v", err)
	}

	// 주문 상태 업데이트
	if err := eh.UpdateOrderStatus(ctx, validOrder.ID, "completed"); err != nil {
		log.Printf("주문 상태 업데이트 실패: %v", err)
	} else {
		log.Printf("주문 상태가 성공적으로 업데이트되었습니다")
	}

	// 존재하지 않는 주문 업데이트 시도
	if err := eh.UpdateOrderStatus(ctx, 9999, "completed"); err != nil {
		log.Printf("예상된 업데이트 실패: %v", err)
	}

	// 메트릭스 출력
	metrics := eh.GetMetrics()
	log.Printf("\n에러 처리 메트릭스:\n"+
		"총 에러 수: %d\n"+
		"유효성 검사 에러: %d\n"+
		"네트워크 에러: %d\n"+
		"재시도 횟수: %d\n"+
		"복구된 에러: %d\n"+
		"마지막 에러 발생: %v",
		metrics.TotalErrors,
		metrics.ValidationErrors,
		metrics.NetworkErrors,
		metrics.RetryAttempts,
		metrics.RecoveredErrors,
		metrics.LastError)
}
