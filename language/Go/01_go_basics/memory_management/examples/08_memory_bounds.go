/*
이 예제는 Go 프로그램의 메모리 사용 제한과 관리 방법을 설명합니다.
컨테이너 환경이나 제한된 리소스 환경에서 실행되는 애플리케이션의
안정적인 운영을 위한 다양한 기법을 다룹니다.

주요 내용:
1. 메모리 사용량 제한 설정과 모니터링
2. OOM(Out of Memory) 상황 처리
3. 점진적 메모리 해제 전략
4. 적응형 메모리 관리

실행 방법:
GOMAXPROCS=2 go run memory_bounds.go
*/

package examples

import (
	"context"
	"fmt"
	"runtime"
	"sync"
	"time"
)

// =============================================================
// Chapter 1: 메모리 사용량 제한과 모니터링
// 애플리케이션의 메모리 사용량을 제한하고 추적하는 방법을 설명합니다.
// =============================================================

// MemoryLimiter는 애플리케이션의 메모리 사용을 제한하고 모니터링합니다.
type MemoryLimiter struct {
	maxMemory   uint64 // 최대 허용 메모리 (바이트)
	currentUsed uint64 // 현재 사용 중인 메모리
	mu          sync.RWMutex
	alerts      chan MemoryAlert
}

// MemoryAlert는 메모리 사용량 관련 경고를 나타냅니다.
type MemoryAlert struct {
	Level     AlertLevel
	Usage     float64 // 사용률 (%)
	Timestamp time.Time
}

// AlertLevel은 메모리 경고 수준을 정의합니다.
type AlertLevel int

const (
	AlertLevelNormal AlertLevel = iota
	AlertLevelWarning
	AlertLevelCritical
)

// NewMemoryLimiter는 새로운 메모리 제한기를 생성합니다.
func NewMemoryLimiter(maxMemoryMB uint64) *MemoryLimiter {
	return &MemoryLimiter{
		maxMemory: maxMemoryMB * 1024 * 1024,
		alerts:    make(chan MemoryAlert, 100),
	}
}

// StartMonitoring은 메모리 사용량 모니터링을 시작합니다.
func (ml *MemoryLimiter) StartMonitoring(ctx context.Context) {
	ticker := time.NewTicker(time.Second)
	defer ticker.Stop()

	for {
		select {
		case <-ctx.Done():
			return
		case <-ticker.C:
			ml.checkMemoryUsage()
		}
	}
}

// checkMemoryUsage는 현재 메모리 사용량을 확인하고 필요한 조치를 취합니다.
func (ml *MemoryLimiter) checkMemoryUsage() {
	var stats runtime.MemStats
	runtime.ReadMemStats(&stats)

	usage := float64(stats.HeapAlloc) / float64(ml.maxMemory) * 100
	alert := MemoryAlert{
		Timestamp: time.Now(),
		Usage:     usage,
	}

	switch {
	case usage > 90:
		alert.Level = AlertLevelCritical
	case usage > 75:
		alert.Level = AlertLevelWarning
	default:
		alert.Level = AlertLevelNormal
	}

	select {
	case ml.alerts <- alert:
	default:
		// 알림 채널이 가득 찬 경우 오래된 알림 제거
		<-ml.alerts
		ml.alerts <- alert
	}
}

// =============================================================
// Chapter 2: OOM 방지 전략
// Out of Memory 상황을 예방하고 처리하는 방법을 설명합니다.
// =============================================================

// MemoryGuard는 OOM 방지를 위한 보호 메커니즘을 구현합니다.
type MemoryGuard struct {
	limiter    *MemoryLimiter
	buffer     [][]byte // 비상용 메모리 버퍼
	bufferSize int
	mu         sync.Mutex
}

// NewMemoryGuard는 새로운 메모리 보호기를 생성합니다.
func NewMemoryGuard(limiter *MemoryLimiter, bufferSizeMB int) *MemoryGuard {
	return &MemoryGuard{
		limiter:    limiter,
		bufferSize: bufferSizeMB,
	}
}

// AllocateEmergencyBuffer는 비상용 메모리 버퍼를 할당합니다.
func (mg *MemoryGuard) AllocateEmergencyBuffer() {
	mg.mu.Lock()
	defer mg.mu.Unlock()

	// 1MB 단위로 버퍼 할당
	mg.buffer = make([][]byte, mg.bufferSize)
	for i := range mg.buffer {
		mg.buffer[i] = make([]byte, 1024*1024)
	}
}

// ReleaseEmergencyBuffer는 비상 시 메모리를 해제합니다.
func (mg *MemoryGuard) ReleaseEmergencyBuffer() {
	mg.mu.Lock()
	defer mg.mu.Unlock()

	// 점진적으로 메모리 해제
	for i := range mg.buffer {
		mg.buffer[i] = nil
	}
	mg.buffer = nil
	runtime.GC()
}

// =============================================================
// Chapter 3: 적응형 메모리 관리
// 시스템 부하에 따라 메모리 사용을 조절하는 방법을 설명합니다.
// =============================================================

// AdaptiveMemoryManager는 시스템 상태에 따라 메모리 사용을 조절합니다.
type AdaptiveMemoryManager struct {
	currentLimit uint64
	minLimit     uint64
	maxLimit     uint64
	adjustFactor float64
	mu           sync.RWMutex
}

// NewAdaptiveMemoryManager는 새로운 적응형 메모리 관리자를 생성합니다.
func NewAdaptiveMemoryManager(minMB, maxMB uint64) *AdaptiveMemoryManager {
	return &AdaptiveMemoryManager{
		currentLimit: minMB * 1024 * 1024,
		minLimit:     minMB * 1024 * 1024,
		maxLimit:     maxMB * 1024 * 1024,
		adjustFactor: 1.2, // 20% 조절
	}
}

// AdjustLimit는 시스템 상태에 따라 메모리 제한을 조절합니다.
func (amm *AdaptiveMemoryManager) AdjustLimit(systemLoad float64) {
	amm.mu.Lock()
	defer amm.mu.Unlock()

	switch {
	case systemLoad > 0.8: // 높은 부하
		amm.decreaseLimit()
	case systemLoad < 0.3: // 낮은 부하
		amm.increaseLimit()
	}
}

// increaseLimit는 메모리 제한을 증가시킵니다.
func (amm *AdaptiveMemoryManager) increaseLimit() {
	newLimit := uint64(float64(amm.currentLimit) * amm.adjustFactor)
	if newLimit > amm.maxLimit {
		newLimit = amm.maxLimit
	}
	amm.currentLimit = newLimit
}

// decreaseLimit는 메모리 제한을 감소시킵니다.
func (amm *AdaptiveMemoryManager) decreaseLimit() {
	newLimit := uint64(float64(amm.currentLimit) / amm.adjustFactor)
	if newLimit < amm.minLimit {
		newLimit = amm.minLimit
	}
	amm.currentLimit = newLimit
}

// =============================================================
// Chapter 4: 메모리 사용량 최적화
// 메모리 사용을 최적화하는 다양한 전략을 구현합니다.
// =============================================================

// MemoryOptimizer는 메모리 사용을 최적화하는 기능을 제공합니다.
type MemoryOptimizer struct {
	cache       map[string][]byte
	cacheLimit  int
	accessCount map[string]int
	mu          sync.RWMutex
}

// NewMemoryOptimizer는 새로운 메모리 최적화기를 생성합니다.
func NewMemoryOptimizer(cacheLimitMB int) *MemoryOptimizer {
	return &MemoryOptimizer{
		cache:       make(map[string][]byte),
		cacheLimit:  cacheLimitMB * 1024 * 1024,
		accessCount: make(map[string]int),
	}
}

// AddToCache는 캐시에 데이터를 추가합니다.
func (mo *MemoryOptimizer) AddToCache(key string, data []byte) bool {
	mo.mu.Lock()
	defer mo.mu.Unlock()

	// 캐시 크기 제한 확인
	currentSize := mo.getCurrentCacheSize()
	if currentSize+len(data) > mo.cacheLimit {
		mo.evictLeastUsed()
	}

	mo.cache[key] = data
	mo.accessCount[key] = 0
	return true
}

// getCurrentCacheSize는 현재 캐시 크기를 반환합니다.
func (mo *MemoryOptimizer) getCurrentCacheSize() int {
	var size int
	for _, data := range mo.cache {
		size += len(data)
	}
	return size
}

// evictLeastUsed는 가장 적게 사용된 항목을 제거합니다.
func (mo *MemoryOptimizer) evictLeastUsed() {
	var leastUsedKey string
	minCount := int(^uint(0) >> 1) // 최대 정수값

	for key, count := range mo.accessCount {
		if count < minCount {
			minCount = count
			leastUsedKey = key
		}
	}

	if leastUsedKey != "" {
		delete(mo.cache, leastUsedKey)
		delete(mo.accessCount, leastUsedKey)
	}
}

// RunMemoryBoundsDemo demonstrates memory bounds management
func RunMemoryBoundsDemo() {
	ctx, cancel := context.WithTimeout(context.Background(), 30*time.Second)
	defer cancel()

	// 메모리 제한기 설정
	limiter := NewMemoryLimiter(1024)                      // 1GB 제한
	guard := NewMemoryGuard(limiter, 100)                  // 100MB 비상 버퍼
	adaptiveManager := NewAdaptiveMemoryManager(512, 2048) // 512MB-2GB 범위
	optimizer := NewMemoryOptimizer(256)                   // 256MB 캐시 제한

	// 모니터링 시작
	go limiter.StartMonitoring(ctx)

	// 알림 처리
	go func() {
		for alert := range limiter.alerts {
			fmt.Printf("Memory Alert - Level: %v, Usage: %.2f%%\n",
				alert.Level, alert.Usage)

			if alert.Level == AlertLevelCritical {
				guard.ReleaseEmergencyBuffer()
			}
		}
	}()

	// 시뮬레이션 실행
	var wg sync.WaitGroup
	for i := 0; i < 5; i++ {
		wg.Add(1)
		go func(id int) {
			defer wg.Done()

			// 메모리 사용 시뮬레이션
			data := make([]byte, 50*1024*1024) // 50MB
			key := fmt.Sprintf("data_%d", id)
			optimizer.AddToCache(key, data)

			// 시스템 부하 시뮬레이션
			systemLoad := float64(id) / 5.0
			adaptiveManager.AdjustLimit(systemLoad)

			time.Sleep(time.Second * 2)
		}(i)
	}

	wg.Wait()
}

/*
메모리 제한 관리 가이드라인:

1. 제한 설정
   - 컨테이너/환경에 맞는 적절한 제한 설정
   - 비상용 버퍼 확보
   - 점진적 조정 메커니즘 구현

2. 모니터링
   - 실시간 메모리 사용량 추적
   - 경고 수준 설정
   - 사용 패턴 분석

3. OOM 방지
   - 선제적 메모리 해제
   - 비상용 버퍼 관리
   - 백프레셔 메커니즘 구현

4. 최적화 전략
   - 캐시 크기 제한
   - 메모리 재사용
   - 점진적 확장/축소

운영 고려사항:

1. 모니터링
   - 메모리 사용량 추이 관찰
   - 경고 임계값 조정
   - 로그 분석

2. 튜닝
   - 워크로드에 따른 제한 조정
   - GC 주기 최적화
   - 캐시 정책 조정

3. 장애 대응
   - OOM 상황 감지
   - 자동 복구 메커니즘
   - 알림 설정
*/
