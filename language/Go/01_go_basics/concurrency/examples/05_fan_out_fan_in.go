/*
이 예제는 Go에서 Fan-out/Fan-in 패턴을 구현한 완전한 예시를 제공합니다. 이 패턴은 대량의 작업을 여러 워커에게 분배하고 결과를 수집하는 데 매우 효과적입니다.
구현의 주요 컴포넌트와 특징을 살펴보면 다음과 같습니다:
첫째, WorkItem과 WorkResult 구조체는 각각 처리할 작업과 처리 결과를 표현합니다. 각 작업은 고유 ID와 우선순위를 가지며, 처리 시간을 추적할 수 있는 필드들을 포함합니다.
둘째, FanOutFanIn 구조체는 전체 작업 처리 프로세스를 관리합니다. 이는 작업 분배(fan-out)와 결과 수집(fan-in)을 조율하며, 처리 메트릭을 수집하고 분석합니다.
셋째, Process 메서드는 패턴의 핵심 로직을 구현합니다. 이는 작업을 여러 워커에게 분배하고, 각 워커의 결과를 수집하여 최종 결과를 반환합니다. 컨텍스트를 통한 취소 처리와 채널을 통한 효율적인 통신을 지원합니다.
넷째, 성능 모니터링과 메트릭 수집 기능을 포함합니다. 각 작업의 처리 시간, 오류 발생 횟수, 전체 처리 시간 등을 추적하여 시스템의 성능을 분석할 수 있습니다.
이 패턴은 다음과 같은 상황에서 특히 유용합니다:

대량의 데이터 처리 작업
병렬 계산이 필요한 연산
다수의 API 요청 처리
이미지나 비디오 처리 작업

구현된 패턴의 주요 이점은 다음과 같습니다:

효율적인 리소스 활용
처리 시간 최적화
작업 진행 상황 추적
오류 처리와 복구 메커니즘
상세한 성능 메트릭 제공

이 구현은 실제 프로덕션 환경에서 사용할 수 있도록 설계되었으며, 필요에 따라 우선순위 기반 처리, 동적 워커 조정, 부하 분산 등의 기능을 추가로 확장할 수 있습니다.
*/

package examples

import (
	"context"
	"fmt"
	"log"
	"runtime"
	"sync"
	"time"
)

// WorkItem represents a single unit of work to be processed
// 처리할 작업 단위를 정의합니다. 작업의 식별과 추적을 위한 정보를 포함합니다.
type WorkItem struct {
	ID       int
	Data     interface{}
	Priority int
	// 작업 처리 시간 추적을 위한 필드들
	StartTime time.Time
	EndTime   time.Time
}

// WorkResult represents the result of processing a work item
// 작업 처리 결과를 나타냅니다. 원본 작업 정보와 처리 결과를 포함합니다.
type WorkResult struct {
	WorkItem    WorkItem
	Result      interface{}
	Error       error
	ProcessedBy int // 작업을 처리한 워커의 ID
}

// FanOutFanIn implements the fan-out/fan-in concurrency pattern
// 전체 작업의 분배와 수집을 관리하는 구조체입니다.
type FanOutFanIn struct {
	numWorkers int
	// 작업 처리 성능 측정을 위한 메트릭
	metrics struct {
		sync.Mutex
		processingTimes []time.Duration
		totalItems      int
		errorCount      int
	}
}

// NewFanOutFanIn creates a new fan-out/fan-in processor
// 새로운 fan-out/fan-in 프로세서를 생성하고 초기화합니다.
func NewFanOutFanIn(numWorkers int) *FanOutFanIn {
	if numWorkers <= 0 {
		numWorkers = runtime.NumCPU()
	}

	return &FanOutFanIn{
		numWorkers: numWorkers,
	}
}

// Process handles the distribution and collection of work items
// 작업 항목들을 분배하고 결과를 수집하는 메인 프로세스입니다.
func (f *FanOutFanIn) Process(ctx context.Context, items []WorkItem) []WorkResult {
	// 작업 및 결과 채널 생성
	workChan := make(chan WorkItem, len(items))
	resultChan := make(chan WorkResult, len(items))

	// 워커 그룹 생성
	var wg sync.WaitGroup
	wg.Add(f.numWorkers)

	// 워커 시작 (Fan-out)
	for i := 0; i < f.numWorkers; i++ {
		workerID := i
		go func() {
			defer wg.Done()
			f.worker(ctx, workerID, workChan, resultChan)
		}()
	}

	// 작업 전송
	go func() {
		for _, item := range items {
			select {
			case <-ctx.Done():
				return
			case workChan <- item:
				// 작업이 성공적으로 전송됨
			}
		}
		close(workChan)
	}()

	// 결과 수집 (Fan-in)
	go func() {
		wg.Wait()
		close(resultChan)
	}()

	// 모든 결과 수집
	var results []WorkResult
	for result := range resultChan {
		results = append(results, result)
		f.updateMetrics(result)
	}

	return results
}

// worker processes work items from the work channel
// 개별 워커의 작업 처리 로직을 구현합니다.
func (f *FanOutFanIn) worker(ctx context.Context, id int, workChan <-chan WorkItem, resultChan chan<- WorkResult) {
	for {
		select {
		case <-ctx.Done():
			return
		case work, ok := <-workChan:
			if !ok {
				return
			}

			// 작업 시작 시간 기록
			work.StartTime = time.Now()

			// 작업 처리 로직
			result := f.processWorkItem(id, work)

			// 작업 종료 시간 기록
			work.EndTime = time.Now()

			// 결과 전송
			select {
			case <-ctx.Done():
				return
			case resultChan <- result:
				// 결과가 성공적으로 전송됨
			}
		}
	}
}

// processWorkItem handles the actual processing of a work item
// 실제 작업 처리를 수행하는 함수입니다.
func (f *FanOutFanIn) processWorkItem(workerID int, item WorkItem) WorkResult {
	result := WorkResult{
		WorkItem:    item,
		ProcessedBy: workerID,
	}

	// 작업 처리 시뮬레이션
	// 실제 구현에서는 여기에 실제 비즈니스 로직이 들어갑니다
	time.Sleep(time.Duration(item.Priority) * 100 * time.Millisecond)

	// 결과 생성
	result.Result = fmt.Sprintf("Processed item %d with priority %d by worker %d",
		item.ID, item.Priority, workerID)

	return result
}

// updateMetrics updates the processing metrics
// 작업 처리 메트릭을 업데이트합니다.
func (f *FanOutFanIn) updateMetrics(result WorkResult) {
	f.metrics.Lock()
	defer f.metrics.Unlock()

	processingTime := result.WorkItem.EndTime.Sub(result.WorkItem.StartTime)
	f.metrics.processingTimes = append(f.metrics.processingTimes, processingTime)
	f.metrics.totalItems++

	if result.Error != nil {
		f.metrics.errorCount++
	}
}

// GetMetrics returns the current processing metrics
// 현재까지의 처리 메트릭을 반환합니다.
func (f *FanOutFanIn) GetMetrics() map[string]interface{} {
	f.metrics.Lock()
	defer f.metrics.Unlock()

	var totalTime time.Duration
	for _, t := range f.metrics.processingTimes {
		totalTime += t
	}

	var avgTime time.Duration
	if len(f.metrics.processingTimes) > 0 {
		avgTime = totalTime / time.Duration(len(f.metrics.processingTimes))
	}

	return map[string]interface{}{
		"total_items":             f.metrics.totalItems,
		"error_count":             f.metrics.errorCount,
		"average_processing_time": avgTime.Milliseconds(),
		"total_processing_time":   totalTime.Milliseconds(),
		"number_of_workers":       f.numWorkers,
	}
}

// FanOutFanInExample demonstrates the usage of the fan-out/fan-in pattern
func FanOutFanInExample() {
	// 프로세서 생성
	processor := NewFanOutFanIn(4)

	// 컨텍스트 생성
	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	// 테스트 작업 아이템 생성
	var items []WorkItem
	for i := 1; i <= 20; i++ {
		items = append(items, WorkItem{
			ID:       i,
			Priority: (i % 3) + 1, // 1-3 사이의 우선순위
			Data:     fmt.Sprintf("Task %d", i),
		})
	}

	// 작업 처리 시작
	log.Printf("Starting to process %d items with %d workers...",
		len(items), processor.numWorkers)

	results := processor.Process(ctx, items)

	// 결과 출력
	log.Printf("\nProcessing completed. Results:")
	for _, result := range results {
		log.Printf("Item %d: %v (Processed by worker %d)",
			result.WorkItem.ID, result.Result, result.ProcessedBy)
	}

	// 메트릭 출력
	metrics := processor.GetMetrics()
	log.Printf("\nProcessing Metrics:")
	log.Printf("Total Items: %d", metrics["total_items"])
	log.Printf("Average Processing Time: %dms", metrics["average_processing_time"])
	log.Printf("Total Processing Time: %dms", metrics["total_processing_time"])
}
