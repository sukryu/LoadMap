/*
이 예제는 Go에서 워커 풀 패턴을 구현하는 완전한 예시를 제공합니다. 코드는 다음과 같은 주요 컴포넌트들로 구성되어 있습니다:

Task와 Result 구조체: 작업과 결과를 표현하는 기본 데이터 구조를 정의합니다. 각 작업은 고유한 ID를 가지며, 결과에는 처리한 워커의 ID도 포함됩니다.
WorkerPool 구조체: 전체 워커 풀의 상태를 관리합니다. 작업 채널, 결과 채널, 컨텍스트 등 필요한 모든 컴포넌트를 포함합니다.
Worker 함수: 개별 워커의 동작을 구현합니다. 각 워커는 작업 채널에서 새로운 작업을 받아 처리하고 결과를 결과 채널로 전송합니다.
풀 관리 메서드: 워커 풀의 시작, 정지, 작업 제출 등을 관리하는 메서드들을 제공합니다.

이 구현의 주요 특징들은 다음과 같습니다:

컨텍스트 기반 취소: 컨텍스트를 사용하여 워커들의 정상적인 종료를 관리합니다.
버퍼링된 채널: 성능 최적화를 위해 버퍼가 있는 채널을 사용합니다.
우아한 종료: 모든 진행 중인 작업이 완료될 때까지 대기하는 정상 종료 메커니즘을 구현합니다.
에러 처리: 작업 제출과 처리 과정에서 발생할 수 있는 에러를 적절히 처리합니다.

이 패턴은 대량의 작업을 병렬로 처리해야 하는 상황에서 특히 유용합니다. 예를 들어, 이미지 처리, 데이터 변환, API 요청 처리 등의 시나리오에서 효과적으로 사용될 수 있습니다.
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

// Task represents a unit of work to be processed
// 작업 처리의 결과를 추적하기 위한 ID와 실제 처리할 데이터를 포함합니다.
type Task struct {
	ID   int
	Data interface{}
}

// Result represents the outcome of task processing
// 작업 처리의 결과를 저장하며, 원본 작업의 ID와 처리 결과, 발생한 에러를 포함합니다.
type Result struct {
	TaskID   int
	Output   interface{}
	Error    error
	WorkerID int
}

// WorkerPool manages a pool of workers for concurrent task processing
// 워커 풀의 전체적인 상태와 동작을 관리하는 구조체입니다.
type WorkerPool struct {
	numWorkers int                // 워커의 수
	tasks      chan Task          // 작업을 전달하는 채널
	results    chan Result        // 결과를 수집하는 채널
	done       chan struct{}      // 풀 종료를 알리는 채널
	wg         sync.WaitGroup     // 워커들의 완료를 대기하기 위한 WaitGroup
	ctx        context.Context    // 작업 취소를 위한 컨텍스트
	cancel     context.CancelFunc // 컨텍스트 취소 함수
}

// NewWorkerPool creates and initializes a new worker pool
// 워커 풀을 생성하고 초기화하는 생성자 함수입니다.
// numWorkers: 동시에 실행될 워커의 수
// bufferSize: 작업과 결과 채널의 버퍼 크기
func NewWorkerPool(numWorkers int, bufferSize int) *WorkerPool {
	// 컨텍스트를 생성하여 워커 풀의 수명을 관리합니다.
	ctx, cancel := context.WithCancel(context.Background())

	return &WorkerPool{
		numWorkers: numWorkers,
		// 버퍼가 있는 채널을 사용하여 작업 제출과 결과 수집의 효율을 높입니다.
		tasks:   make(chan Task, bufferSize),
		results: make(chan Result, bufferSize),
		done:    make(chan struct{}),
		ctx:     ctx,
		cancel:  cancel,
	}
}

// worker implements the main logic for processing tasks
// 각 워커의 실제 작업 처리 로직을 구현합니다.
func (wp *WorkerPool) worker(workerID int) {
	defer wp.wg.Done()

	for {
		select {
		// 컨텍스트가 취소되면 워커를 종료합니다.
		case <-wp.ctx.Done():
			log.Printf("Worker %d shutting down", workerID)
			return

		// 새로운 작업을 수신하여 처리합니다.
		case task, ok := <-wp.tasks:
			if !ok {
				log.Printf("Worker %d: task channel closed", workerID)
				return
			}

			// 작업 처리를 시뮬레이션합니다.
			// 실제 애플리케이션에서는 여기에 실제 비즈니스 로직이 들어갑니다.
			result := wp.processTask(task, workerID)

			// 결과를 결과 채널로 전송합니다.
			// 채널이 가득 차있을 경우 블로킹될 수 있습니다.
			select {
			case wp.results <- result:
				// 결과가 성공적으로 전송됨
			case <-wp.ctx.Done():
				// 컨텍스트가 취소된 경우 작업을 중단
				return
			}
		}
	}
}

// processTask simulates task processing
// 실제 작업 처리를 시뮬레이션하는 함수입니다.
func (wp *WorkerPool) processTask(task Task, workerID int) Result {
	// 작업 처리 시작을 로깅합니다.
	log.Printf("Worker %d processing task %d", workerID, task.ID)

	// 작업 처리를 시뮬레이션하기 위해 임의의 지연을 추가합니다.
	time.Sleep(100 * time.Millisecond)

	// 현재 고루틴의 상태를 확인합니다.
	var memStats runtime.MemStats
	runtime.ReadMemStats(&memStats)

	return Result{
		TaskID:   task.ID,
		Output:   fmt.Sprintf("Processed task %d by worker %d", task.ID, workerID),
		WorkerID: workerID,
	}
}

// Start initializes and starts the worker pool
// 워커 풀을 초기화하고 시작하는 메서드입니다.
func (wp *WorkerPool) Start() {
	log.Printf("Starting worker pool with %d workers", wp.numWorkers)

	// 지정된 수만큼의 워커를 생성하고 시작합니다.
	wp.wg.Add(wp.numWorkers)
	for i := 0; i < wp.numWorkers; i++ {
		go wp.worker(i)
	}

	// 모든 워커가 종료되면 결과 채널을 닫습니다.
	go func() {
		wp.wg.Wait()
		close(wp.results)
		close(wp.done)
	}()
}

// SubmitTask adds a new task to the worker pool
// 새로운 작업을 워커 풀에 제출하는 메서드입니다.
func (wp *WorkerPool) SubmitTask(task Task) error {
	select {
	case <-wp.ctx.Done():
		return fmt.Errorf("worker pool is shutting down")
	case wp.tasks <- task:
		return nil
	}
}

// Results returns a channel for receiving processed results
// 처리된 결과를 수신할 수 있는 채널을 반환합니다.
func (wp *WorkerPool) Results() <-chan Result {
	return wp.results
}

// Stop gracefully shuts down the worker pool
// 워커 풀을 정상적으로 종료하는 메서드입니다.
func (wp *WorkerPool) Stop() {
	log.Println("Initiating worker pool shutdown")

	// 컨텍스트를 취소하여 모든 워커에게 종료 신호를 보냅니다.
	wp.cancel()

	// 작업 채널을 닫아 더 이상의 작업 제출을 막습니다.
	close(wp.tasks)

	// 모든 워커가 종료될 때까지 대기합니다.
	<-wp.done
	log.Println("Worker pool shutdown complete")
}

// Example usage of the worker pool
func WorkerPoolExample() {
	// 4개의 워커와 10개의 버퍼 크기로 워커 풀을 생성합니다.
	pool := NewWorkerPool(4, 10)
	pool.Start()
	defer pool.Stop()

	// 결과를 수집하기 위한 고루틴을 시작합니다.
	go func() {
		for result := range pool.Results() {
			log.Printf("Received result for task %d: %v (Worker: %d)",
				result.TaskID, result.Output, result.WorkerID)
		}
	}()

	// 10개의 테스트 작업을 제출합니다.
	for i := 1; i <= 10; i++ {
		task := Task{
			ID:   i,
			Data: fmt.Sprintf("Task %d data", i),
		}

		if err := pool.SubmitTask(task); err != nil {
			log.Printf("Failed to submit task %d: %v", i, err)
		}
	}

	// 모든 작업이 처리될 때까지 잠시 대기합니다.
	time.Sleep(2 * time.Second)
}
