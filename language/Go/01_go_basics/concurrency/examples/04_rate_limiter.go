/*
이 예제는 Go에서 속도 제한(Rate Limiting) 패턴을 구현한 포괄적인 예시를 제공합니다. 두 가지 주요 알고리즘(토큰 버킷과 리키 버킷)을 구현하며, 실제 서비스에서 사용할 수 있는 완전한 기능을 제공합니다.
주요 컴포넌트와 특징은 다음과 같습니다:

속도 제한 인터페이스: RateLimiter 인터페이스는 모든 속도 제한 구현체가 따라야 할 공통 메서드를 정의합니다. 이를 통해 다양한 알고리즘을 일관된 방식으로 사용할 수 있습니다.
토큰 버킷 구현: TokenBucket 구조체는 토큰 버킷 알고리즘을 구현합니다. 이 알고리즘은 다음과 같은 특징을 가집니다:

일정 속도로 토큰 생성
버킷 크기 제한
토큰 소비 기반의 요청 허용
정확한 타이밍 제어


리키 버킷 구현: LeakyBucket 구조체는 리키 버킷 알고리즘을 구현합니다. 이 알고리즘의 특징은 다음과 같습니다:

고정 속도로 요청 처리
큐 기반의 요청 관리
초과 요청에 대한 드롭 정책


동시성 제어: 두 구현 모두 다음과 같은 동시성 제어 메커니즘을 포함합니다:

뮤텍스를 통한 상태 보호
컨텍스트 기반의 취소 지원
고루틴 안전한 작업 처리


모니터링과 통계: 각 구현체는 상세한 통계 정보를 제공합니다:

처리된 요청 수
거부된 요청 수
대기 시간
현재 상태 정보



이 패턴은 다음과 같은 상황에서 특히 유용합니다:

API 요청 제한
리소스 사용량 제어
DDoS 방어
서비스 품질(QoS) 관리

구현된 속도 제한기의 주요 장점은 다음과 같습니다:

정확한 속도 제어
유연한 설정 가능성
상세한 모니터링 지원
고루틴 안전성
취소 가능한 대기 지원

이 구현은 실제 프로덕션 환경에서 사용할 수 있으며, 필요에 따라 분산 시스템 지원이나 사용자별 제한과 같은 추가 기능을 확장할 수 있습니다.
*/

package examples

import (
	"context"
	"log"
	"sync"
	"time"
)

// RateLimiter defines the interface for rate limiting implementations
// 다양한 속도 제한 알고리즘을 위한 인터페이스를 정의합니다.
type RateLimiter interface {
	// Allow checks if a request can proceed
	Allow() bool
	// Wait blocks until a request can proceed
	Wait(context.Context) error
	// GetStats returns current limiter statistics
	GetStats() map[string]interface{}
}

// TokenBucket implements the token bucket rate limiting algorithm
// 토큰 버킷 알고리즘을 구현한 속도 제한기입니다.
type TokenBucket struct {
	mu sync.Mutex
	// 설정값
	rate       float64 // 초당 생성되는 토큰 수
	bucketSize float64 // 버킷의 최대 용량
	// 상태
	tokens     float64   // 현재 사용 가능한 토큰 수
	lastRefill time.Time // 마지막 토큰 리필 시간
	// 통계
	stats struct {
		AllowedRequests   int64
		ThrottledRequests int64
		TotalWaitTime     time.Duration
	}
}

// NewTokenBucket creates a new token bucket rate limiter
// 새로운 토큰 버킷 속도 제한기를 생성하고 초기화합니다.
func NewTokenBucket(rate, bucketSize float64) *TokenBucket {
	return &TokenBucket{
		rate:       rate,
		bucketSize: bucketSize,
		tokens:     bucketSize,
		lastRefill: time.Now(),
	}
}

// refill adds tokens to the bucket based on elapsed time
// 경과 시간에 따라 토큰을 버킷에 추가합니다.
func (tb *TokenBucket) refill() {
	now := time.Now()
	elapsed := now.Sub(tb.lastRefill).Seconds()

	// 새로운 토큰 추가
	tb.tokens += elapsed * tb.rate
	// 버킷 용량 제한
	if tb.tokens > tb.bucketSize {
		tb.tokens = tb.bucketSize
	}

	tb.lastRefill = now
}

// Allow checks if a request can proceed immediately
func (tb *TokenBucket) Allow() bool {
	tb.mu.Lock()
	defer tb.mu.Unlock()

	tb.refill()

	if tb.tokens >= 1 {
		tb.tokens--
		tb.stats.AllowedRequests++
		return true
	}

	tb.stats.ThrottledRequests++
	return false
}

// Wait blocks until a token is available or context is cancelled
func (tb *TokenBucket) Wait(ctx context.Context) error {
	start := time.Now()

	for {
		tb.mu.Lock()
		tb.refill()

		if tb.tokens >= 1 {
			tb.tokens--
			tb.stats.AllowedRequests++
			waitTime := time.Since(start)
			tb.stats.TotalWaitTime += waitTime
			tb.mu.Unlock()
			return nil
		}

		// 다음 토큰 생성까지 대기 시간 계산
		waitTime := time.Duration(1 / tb.rate * float64(time.Second))
		tb.mu.Unlock()

		select {
		case <-ctx.Done():
			return ctx.Err()
		case <-time.After(waitTime):
			// 대기 후 다시 시도
		}
	}
}

// GetStats returns current statistics of the rate limiter
func (tb *TokenBucket) GetStats() map[string]interface{} {
	tb.mu.Lock()
	defer tb.mu.Unlock()

	return map[string]interface{}{
		"allowed_requests":   tb.stats.AllowedRequests,
		"throttled_requests": tb.stats.ThrottledRequests,
		"total_wait_time_ms": tb.stats.TotalWaitTime.Milliseconds(),
		"current_tokens":     tb.tokens,
		"bucket_size":        tb.bucketSize,
		"rate_per_second":    tb.rate,
	}
}

// LeakyBucket implements the leaky bucket rate limiting algorithm
// 리키 버킷 알고리즘을 구현한 속도 제한기입니다.
type LeakyBucket struct {
	mu sync.Mutex
	// 설정값
	rate     float64 // 초당 처리할 수 있는 요청 수
	capacity int     // 버킷의 최대 용량
	// 상태
	queue     []time.Time // 요청 큐
	lastDrain time.Time   // 마지막 드레인 시간
	// 통계
	stats struct {
		ProcessedRequests int64
		DroppedRequests   int64
	}
}

// NewLeakyBucket creates a new leaky bucket rate limiter
func NewLeakyBucket(rate float64, capacity int) *LeakyBucket {
	return &LeakyBucket{
		rate:      rate,
		capacity:  capacity,
		queue:     make([]time.Time, 0, capacity),
		lastDrain: time.Now(),
	}
}

// drain removes processed requests from the queue
func (lb *LeakyBucket) drain() {
	now := time.Now()
	elapsed := now.Sub(lb.lastDrain).Seconds()
	toRemove := int(elapsed * lb.rate)

	if toRemove > 0 && len(lb.queue) > 0 {
		if toRemove > len(lb.queue) {
			toRemove = len(lb.queue)
		}
		lb.queue = lb.queue[toRemove:]
		lb.stats.ProcessedRequests += int64(toRemove)
	}

	lb.lastDrain = now
}

// Allow checks if a request can be added to the bucket
func (lb *LeakyBucket) Allow() bool {
	lb.mu.Lock()
	defer lb.mu.Unlock()

	lb.drain()

	if len(lb.queue) < lb.capacity {
		lb.queue = append(lb.queue, time.Now())
		return true
	}

	lb.stats.DroppedRequests++
	return false
}

// Wait waits for space in the bucket
func (lb *LeakyBucket) Wait(ctx context.Context) error {
	for {
		lb.mu.Lock()
		lb.drain()

		if len(lb.queue) < lb.capacity {
			lb.queue = append(lb.queue, time.Now())
			lb.mu.Unlock()
			return nil
		}

		waitTime := time.Duration(1 / lb.rate * float64(time.Second))
		lb.mu.Unlock()

		select {
		case <-ctx.Done():
			return ctx.Err()
		case <-time.After(waitTime):
			// 대기 후 다시 시도
		}
	}
}

// GetStats returns current statistics of the rate limiter
func (lb *LeakyBucket) GetStats() map[string]interface{} {
	lb.mu.Lock()
	defer lb.mu.Unlock()

	return map[string]interface{}{
		"processed_requests": lb.stats.ProcessedRequests,
		"dropped_requests":   lb.stats.DroppedRequests,
		"current_queue_size": len(lb.queue),
		"capacity":           lb.capacity,
		"rate_per_second":    lb.rate,
	}
}

// RateLimiterExample demonstrates the usage of rate limiters
func RateLimiterExample() {
	// 토큰 버킷 속도 제한기 생성 (초당 10개 요청, 최대 버킷 크기 20)
	tokenBucket := NewTokenBucket(10, 20)

	// 리키 버킷 속도 제한기 생성 (초당 5개 요청, 큐 크기 10)
	leakyBucket := NewLeakyBucket(5, 10)

	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	// 고루틴을 사용한 동시 요청 시뮬레이션
	var wg sync.WaitGroup
	simulateRequests := func(limiter RateLimiter, name string, requests int) {
		defer wg.Done()

		for i := 0; i < requests; i++ {
			if err := limiter.Wait(ctx); err != nil {
				log.Printf("%s: Request %d failed: %v", name, i, err)
				return
			}
			log.Printf("%s: Request %d processed", name, i)
			time.Sleep(time.Millisecond * 50) // 요청 처리 시뮬레이션
		}
	}

	wg.Add(2)
	go simulateRequests(tokenBucket, "TokenBucket", 30)
	go simulateRequests(leakyBucket, "LeakyBucket", 20)

	// 모든 요청이 완료될 때까지 대기
	wg.Wait()

	// 통계 출력
	log.Printf("\nToken Bucket Stats: %+v", tokenBucket.GetStats())
	log.Printf("Leaky Bucket Stats: %+v", leakyBucket.GetStats())
}
