/*
이 예제는 Go에서 세마포어 패턴을 구현한 포괄적인 예시를 제공합니다. 세마포어는 제한된 리소스에 대한 접근을 제어하고 동시성을 관리하는 데 중요한 역할을 합니다.
이 구현의 핵심 컴포넌트는 다음과 같습니다:
ResourcePool 구조체는 제한된 리소스의 풀을 관리합니다. 채널을 사용하여 리소스의 가용성을 제어하고, 상세한 사용 통계를 추적합니다.
Semaphore 구조체는 카운팅 세마포어의 주요 기능을 구현합니다. 리소스 획득과 해제를 관리하며, 타임아웃 처리와 성능 메트릭 수집을 담당합니다.
ResourceUser 구조체는 리소스를 사용하는 실제 작업을 시뮬레이션합니다. 리소스 획득, 사용, 해제의 전체 생명주기를 보여줍니다.
이 구현은 다음과 같은 주요 기능을 제공합니다:

리소스 제어: 동시에 사용 가능한 리소스의 수를 엄격하게 제한합니다.
타임아웃 처리: 리소스 획득 시도에 대한 타임아웃을 지원하여 교착 상태를 방지합니다.
상태 모니터링: 리소스 사용량, 대기 시간, 타임아웃 발생 등의 상세한 메트릭을 제공합니다.
컨텍스트 통합: Go의 컨텍스트 패키지와 통합하여 작업 취소와 타임아웃을 지원합니다.

이 세마포어 패턴은 다음과 같은 상황에서 특히 유용합니다:

데이터베이스 연결 풀 관리
외부 API 호출 제한
시스템 리소스 사용 제어
동시 처리 작업 수 제한

구현된 코드는 실제 프로덕션 환경에서 사용할 수 있도록 설계되었으며, 필요에 따라 분산 시스템 지원이나 우선순위 기반 리소스 할당과 같은 추가 기능을 확장할 수 있습니다.
*/

package examples

import (
	"context"
	"fmt"
	"log"
	"sync"
	"time"
)

// ResourcePool represents a pool of limited resources
// 제한된 리소스의 풀을 관리하는 구조체입니다.
type ResourcePool struct {
	resources chan struct{}
	// 리소스 사용 통계를 추적합니다.
	stats struct {
		sync.Mutex
		inUse         int
		maxInUse      int
		totalUsed     int
		waitingCount  int
		totalWaitTime time.Duration
	}
}

// NewResourcePool creates a new resource pool with specified capacity
// 지정된 용량의 새로운 리소스 풀을 생성합니다.
func NewResourcePool(capacity int) *ResourcePool {
	return &ResourcePool{
		resources: make(chan struct{}, capacity),
	}
}

// Semaphore implements a counting semaphore pattern
// 카운팅 세마포어 패턴을 구현하는 구조체입니다.
type Semaphore struct {
	pool    *ResourcePool
	timeout time.Duration
	// 세마포어 작동 상태를 추적합니다.
	metrics struct {
		sync.Mutex
		acquireCount  int
		timeoutCount  int
		totalWaitTime time.Duration
	}
}

// NewSemaphore creates a new semaphore with specified capacity and timeout
// 지정된 용량과 타임아웃을 가진 새로운 세마포어를 생성합니다.
func NewSemaphore(capacity int, timeout time.Duration) *Semaphore {
	return &Semaphore{
		pool:    NewResourcePool(capacity),
		timeout: timeout,
	}
}

// Acquire attempts to acquire a resource within the specified timeout
// 지정된 타임아웃 내에 리소스 획득을 시도합니다.
func (s *Semaphore) Acquire(ctx context.Context) error {
	startTime := time.Now()
	s.pool.stats.Lock()
	s.pool.stats.waitingCount++
	s.pool.stats.Unlock()

	// 타임아웃 컨텍스트 생성
	acquireCtx, cancel := context.WithTimeout(ctx, s.timeout)
	defer cancel()

	select {
	case s.pool.resources <- struct{}{}:
		// 리소스 획득 성공
		waitTime := time.Since(startTime)
		s.updateMetrics(true, waitTime)
		s.updatePoolStats(true)
		return nil

	case <-acquireCtx.Done():
		// 타임아웃 또는 컨텍스트 취소
		s.updateMetrics(false, time.Since(startTime))
		s.updatePoolStats(false)
		if acquireCtx.Err() == context.DeadlineExceeded {
			return fmt.Errorf("timeout waiting for resource: %v", s.timeout)
		}
		return ctx.Err()
	}
}

// Release releases an acquired resource back to the pool
// 획득한 리소스를 풀로 반환합니다.
func (s *Semaphore) Release() {
	select {
	case <-s.pool.resources:
		s.pool.stats.Lock()
		s.pool.stats.inUse--
		s.pool.stats.Unlock()
	default:
		panic("Release called without matching Acquire")
	}
}

// updateMetrics updates semaphore performance metrics
// 세마포어의 성능 메트릭을 업데이트합니다.
func (s *Semaphore) updateMetrics(success bool, waitTime time.Duration) {
	s.metrics.Lock()
	defer s.metrics.Unlock()

	if success {
		s.metrics.acquireCount++
		s.metrics.totalWaitTime += waitTime
	} else {
		s.metrics.timeoutCount++
	}
}

// updatePoolStats updates resource pool statistics
// 리소스 풀의 통계를 업데이트합니다.
func (s *Semaphore) updatePoolStats(acquired bool) {
	s.pool.stats.Lock()
	defer s.pool.stats.Unlock()

	s.pool.stats.waitingCount--
	if acquired {
		s.pool.stats.inUse++
		s.pool.stats.totalUsed++
		if s.pool.stats.inUse > s.pool.stats.maxInUse {
			s.pool.stats.maxInUse = s.pool.stats.inUse
		}
	}
}

// GetMetrics returns current semaphore metrics
// 현재 세마포어의 메트릭을 반환합니다.
func (s *Semaphore) GetMetrics() map[string]interface{} {
	s.metrics.Lock()
	s.pool.stats.Lock()
	defer s.metrics.Unlock()
	defer s.pool.stats.Unlock()

	var avgWaitTime time.Duration
	if s.metrics.acquireCount > 0 {
		avgWaitTime = s.metrics.totalWaitTime / time.Duration(s.metrics.acquireCount)
	}

	return map[string]interface{}{
		"acquire_count":     s.metrics.acquireCount,
		"timeout_count":     s.metrics.timeoutCount,
		"average_wait_time": avgWaitTime.Milliseconds(),
		"current_in_use":    s.pool.stats.inUse,
		"max_in_use":        s.pool.stats.maxInUse,
		"total_used":        s.pool.stats.totalUsed,
		"waiting_count":     s.pool.stats.waitingCount,
	}
}

// ResourceUser simulates a resource-consuming operation
// 리소스를 사용하는 작업을 시뮬레이션합니다.
type ResourceUser struct {
	ID        int
	UseTime   time.Duration
	semaphore *Semaphore
}

// Execute performs the resource-consuming operation
// 리소스를 사용하는 작업을 실행합니다.
func (r *ResourceUser) Execute(ctx context.Context) error {
	log.Printf("User %d: attempting to acquire resource", r.ID)

	if err := r.semaphore.Acquire(ctx); err != nil {
		log.Printf("User %d: failed to acquire resource: %v", r.ID, err)
		return err
	}

	log.Printf("User %d: acquired resource, starting work", r.ID)

	// 작업 시뮬레이션
	select {
	case <-ctx.Done():
		r.semaphore.Release()
		return ctx.Err()
	case <-time.After(r.UseTime):
		r.semaphore.Release()
		log.Printf("User %d: completed work and released resource", r.ID)
		return nil
	}
}

// SemaphoreExample demonstrates the usage of the semaphore pattern
func SemaphoreExample() {
	// 3개의 동시 리소스 사용을 허용하는 세마포어 생성
	sem := NewSemaphore(3, 2*time.Second)

	// 컨텍스트 생성
	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	// 다수의 리소스 사용자 생성
	var users []*ResourceUser
	for i := 1; i <= 8; i++ {
		users = append(users, &ResourceUser{
			ID:        i,
			UseTime:   time.Duration(500+i*100) * time.Millisecond,
			semaphore: sem,
		})
	}

	// 동시에 리소스 사용 시도
	var wg sync.WaitGroup
	for _, user := range users {
		wg.Add(1)
		go func(u *ResourceUser) {
			defer wg.Done()
			if err := u.Execute(ctx); err != nil {
				log.Printf("Error executing user %d: %v", u.ID, err)
			}
		}(user)
	}

	// 모든 작업 완료 대기
	wg.Wait()

	// 최종 메트릭 출력
	metrics := sem.GetMetrics()
	log.Printf("\nSemaphore Metrics:")
	log.Printf("Total Acquires: %d", metrics["acquire_count"])
	log.Printf("Timeout Count: %d", metrics["timeout_count"])
	log.Printf("Average Wait Time: %dms", metrics["average_wait_time"])
	log.Printf("Max Resources In Use: %d", metrics["max_in_use"])
}
