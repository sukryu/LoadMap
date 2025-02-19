/*
이 예제는 Go에서 동시성 환경의 에러 처리 패턴을 구현한 포괄적인 예시를 제공합니다. 이 구현은 여러 고루틴에서 발생하는 에러를 효과적으로 수집, 집계, 분석하는 방법을 보여줍니다.
구현의 핵심 컴포넌트는 다음과 같은 주요 기능을 제공합니다:
ErrorCollector는 동시성 작업에서 발생하는 에러를 안전하게 수집합니다. 각 에러에 대해 발생 시간과 컨텍스트 정보를 함께 저장하여 후속 분석을 가능하게 합니다.
ErrorAggregator는 수집된 에러들을 집계하고 분석합니다. 에러 타입별 통계를 관리하고, 전체적인 에러 발생 패턴을 파악할 수 있도록 도와줍니다.
이 시스템은 다음과 같은 에러 처리 전략을 구현합니다:
첫째, 모든 에러는 발생 컨텍스트와 함께 수집됩니다. 이는 문제 해결 시 중요한 맥락 정보를 제공합니다.
둘째, 에러 통계는 실시간으로 집계되어 시스템의 전반적인 건강 상태를 모니터링할 수 있게 합니다.
셋째, 에러 요약 기능을 통해 복잡한 동시성 작업에서 발생한 문제들을 명확하게 이해할 수 있습니다.
이 패턴은 다음과 같은 상황에서 특히 유용합니다:
대규모 배치 작업 처리: 여러 작업이 동시에 실행될 때 발생하는 에러를 효과적으로 관리할 수 있습니다.
마이크로서비스 환경: 여러 서비스 간의 상호작용에서 발생하는 에러를 추적하고 분석할 수 있습니다.
데이터 처리 파이프라인: 복잡한 데이터 처리 과정에서 발생하는 에러를 체계적으로 관리할 수 있습니다.
이 구현은 실제 프로덕션 환경에서 사용할 수 있도록 설계되었으며, 필요에 따라 추가 기능을 확장할 수 있습니다. 예를 들어, 에러 심각도 수준 구분, 자동 복구 메커니즘, 알림 시스템 연동 등을 추가할 수 있습니다.
*/

package examples

import (
	"context"
	"errors"
	"fmt"
	"log"
	"strings"
	"sync"
	"time"
)

// ErrorCollector manages error collection and aggregation in concurrent operations
// 동시성 작업에서 발생하는 에러를 수집하고 집계하는 구조체입니다.
type ErrorCollector struct {
	mu     sync.Mutex
	errors []error
	// 에러 발생 시간과 컨텍스트를 포함한 상세 정보를 저장합니다.
	errorDetails []ErrorDetail
}

// ErrorDetail contains detailed information about an error
// 에러의 상세 정보를 저장하는 구조체입니다.
type ErrorDetail struct {
	Error     error
	Timestamp time.Time
	Context   map[string]interface{}
}

// ErrorAggregator handles error aggregation and reporting
// 에러를 집계하고 보고하는 구조체입니다.
type ErrorAggregator struct {
	collector *ErrorCollector
	// 에러 타입별 통계를 관리합니다.
	stats struct {
		sync.Mutex
		countByType map[string]int
		totalCount  int
	}
}

// NewErrorAggregator creates a new error aggregator
// 새로운 에러 집계기를 생성합니다.
func NewErrorAggregator() *ErrorAggregator {
	return &ErrorAggregator{
		collector: &ErrorCollector{
			errors:       make([]error, 0),
			errorDetails: make([]ErrorDetail, 0),
		},
		stats: struct {
			sync.Mutex
			countByType map[string]int
			totalCount  int
		}{
			countByType: make(map[string]int),
		},
	}
}

// CollectError adds an error to the collector with context
// 컨텍스트 정보와 함께 에러를 수집합니다.
func (ec *ErrorCollector) CollectError(err error, context map[string]interface{}) {
	if err == nil {
		return
	}

	ec.mu.Lock()
	defer ec.mu.Unlock()

	detail := ErrorDetail{
		Error:     err,
		Timestamp: time.Now(),
		Context:   context,
	}

	ec.errors = append(ec.errors, err)
	ec.errorDetails = append(ec.errorDetails, detail)
}

// GetErrors returns all collected errors
// 수집된 모든 에러를 반환합니다.
func (ec *ErrorCollector) GetErrors() []ErrorDetail {
	ec.mu.Lock()
	defer ec.mu.Unlock()

	// 복사본을 반환하여 동시성 문제 방지
	result := make([]ErrorDetail, len(ec.errorDetails))
	copy(result, ec.errorDetails)
	return result
}

// ProcessErrors processes a batch of operations with error handling
// 에러 처리를 포함한 배치 작업을 처리합니다.
func (ea *ErrorAggregator) ProcessErrors(ctx context.Context, operations []func() error) error {
	var wg sync.WaitGroup
	wg.Add(len(operations))

	for i, op := range operations {
		go func(index int, operation func() error) {
			defer wg.Done()

			// 작업 실행 및 에러 수집
			if err := operation(); err != nil {
				ea.collector.CollectError(err, map[string]interface{}{
					"operation_id": index,
					"timestamp":    time.Now(),
				})
				ea.updateStats(err)
			}
		}(i, op)
	}

	// 모든 작업 완료 대기
	wg.Wait()

	// 에러 요약 생성
	return ea.summarizeErrors()
}

// updateStats updates error statistics
// 에러 통계를 업데이트합니다.
func (ea *ErrorAggregator) updateStats(err error) {
	ea.stats.Lock()
	defer ea.stats.Unlock()

	errorType := fmt.Sprintf("%T", err)
	ea.stats.countByType[errorType]++
	ea.stats.totalCount++
}

// summarizeErrors creates a summary of all errors
// 모든 에러의 요약을 생성합니다.
func (ea *ErrorAggregator) summarizeErrors() error {
	details := ea.collector.GetErrors()
	if len(details) == 0 {
		return nil
	}

	// 에러 요약 생성
	var summary strings.Builder
	summary.WriteString(fmt.Sprintf("Encountered %d errors:\n", len(details)))

	for i, detail := range details {
		summary.WriteString(fmt.Sprintf("%d. %v (at %v, context: %v)\n",
			i+1, detail.Error, detail.Timestamp, detail.Context))
	}

	return errors.New(summary.String())
}

// GetErrorStats returns error statistics
// 에러 통계를 반환합니다.
func (ea *ErrorAggregator) GetErrorStats() map[string]interface{} {
	ea.stats.Lock()
	defer ea.stats.Unlock()

	stats := make(map[string]interface{})
	stats["total_errors"] = ea.stats.totalCount
	stats["errors_by_type"] = ea.stats.countByType

	details := ea.collector.GetErrors()
	if len(details) > 0 {
		firstError := details[0].Timestamp
		lastError := details[len(details)-1].Timestamp
		stats["error_time_span"] = lastError.Sub(firstError).String()
	}

	return stats
}

// CustomError represents a domain-specific error
// 도메인 특화 에러를 정의합니다.
type CustomError struct {
	Code    int
	Message string
}

func (e *CustomError) Error() string {
	return fmt.Sprintf("error code %d: %s", e.Code, e.Message)
}

// ErrorHandlingExample demonstrates concurrent error handling
func ErrorHandlingExample() {
	// 에러 집계기 생성
	aggregator := NewErrorAggregator()

	// 테스트 작업 생성
	operations := []func() error{
		func() error {
			time.Sleep(100 * time.Millisecond)
			return &CustomError{Code: 404, Message: "Resource not found"}
		},
		func() error {
			time.Sleep(150 * time.Millisecond)
			return fmt.Errorf("network timeout")
		},
		func() error {
			time.Sleep(50 * time.Millisecond)
			return nil // 성공 케이스
		},
		func() error {
			time.Sleep(200 * time.Millisecond)
			return &CustomError{Code: 500, Message: "Internal server error"}
		},
	}

	// 컨텍스트 생성
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	// 작업 처리
	log.Println("Starting error handling example...")
	if err := aggregator.ProcessErrors(ctx, operations); err != nil {
		log.Printf("Process completed with errors: %v", err)
	}

	// 통계 출력
	stats := aggregator.GetErrorStats()
	log.Printf("\nError Statistics:")
	log.Printf("Total Errors: %d", stats["total_errors"])
	log.Printf("Errors by Type: %v", stats["errors_by_type"])
	if timeSpan, ok := stats["error_time_span"]; ok {
		log.Printf("Error Time Span: %v", timeSpan)
	}
}
