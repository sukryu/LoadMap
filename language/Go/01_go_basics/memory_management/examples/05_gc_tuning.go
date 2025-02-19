/*
이 예제는 Go의 가비지 컬렉션(GC) 튜닝 기법을 설명합니다.
Go의 GC는 자동으로 작동하지만, 애플리케이션의 요구사항에 따라
적절한 튜닝이 필요할 수 있습니다.

주요 내용:
1. GC 동작 원리와 모니터링
2. GOGC 설정과 영향
3. GC 지연 시간 최소화
4. 메모리 할당 패턴 최적화

실행 방법:
GOGC=100 go run gc_tuning.go  // 기본 GC 설정
GOGC=200 go run gc_tuning.go  // GC 빈도 감소
*/

package examples

import (
	"fmt"
	"runtime"
	"runtime/debug"
	"sync"
	"time"
)

// =============================================================
// Chapter 1: GC 모니터링과 기본 동작
// GC의 기본 동작을 이해하고 모니터링하는 방법을 설명합니다.
// =============================================================

// GCStats는 GC 통계를 수집하는 구조체입니다.
type GCStats struct {
	NumGC    uint32
	Pause    time.Duration
	PauseMax time.Duration
	Live     uint64
	Heap     uint64
}

// GCMonitor는 GC 활동을 모니터링하는 구조체입니다.
type GCMonitor struct {
	mu    sync.Mutex
	stats []GCStats
}

// NewGCMonitor는 새로운 GC 모니터를 생성합니다.
func NewGCMonitor() *GCMonitor {
	return &GCMonitor{
		stats: make([]GCStats, 0),
	}
}

// collectStats는 현재 GC 통계를 수집합니다.
func (m *GCMonitor) collectStats() {
	var stats runtime.MemStats
	runtime.ReadMemStats(&stats)

	m.mu.Lock()
	defer m.mu.Unlock()

	m.stats = append(m.stats, GCStats{
		NumGC:    stats.NumGC,
		Pause:    time.Duration(stats.PauseNs[(stats.NumGC+255)%256]),
		PauseMax: time.Duration(stats.PauseNs[0]),
		Live:     stats.Alloc,
		Heap:     stats.HeapAlloc,
	})
}

// =============================================================
// Chapter 2: GC 튜닝과 최적화
// GC 동작을 조정하고 최적화하는 방법을 설명합니다.
// =============================================================

// GCTuner는 GC 동작을 조정하는 구조체입니다.
type GCTuner struct {
	monitor *GCMonitor
	// GC 튜닝 매개변수
	gcPercent int
	memLimit  uint64
}

// NewGCTuner는 새로운 GC 튜너를 생성합니다.
func NewGCTuner(gcPercent int, memLimit uint64) *GCTuner {
	return &GCTuner{
		monitor:   NewGCMonitor(),
		gcPercent: gcPercent,
		memLimit:  memLimit,
	}
}

// SetGCPercent는 GOGC 값을 설정합니다.
func (t *GCTuner) SetGCPercent(percent int) {
	previousGC := debug.SetGCPercent(percent)
	fmt.Printf("Previous GC percentage: %d, New: %d\n", previousGC, percent)
	t.gcPercent = percent
}

// =============================================================
// Chapter 3: 메모리 할당 패턴
// GC 친화적인 메모리 할당 패턴을 구현합니다.
// =============================================================

// MemoryAllocator는 메모리 할당 패턴을 시뮬레이션합니다.
type MemoryAllocator struct {
	allocations [][]byte
	tuner       *GCTuner
}

// NewMemoryAllocator는 새로운 메모리 할당자를 생성합니다.
func NewMemoryAllocator(tuner *GCTuner) *MemoryAllocator {
	return &MemoryAllocator{
		allocations: make([][]byte, 0),
		tuner:       tuner,
	}
}

// AllocateMemory는 메모리를 할당하고 GC 동작을 모니터링합니다.
func (ma *MemoryAllocator) AllocateMemory(sizes []int) {
	for _, size := range sizes {
		// 메모리 할당
		data := make([]byte, size)
		ma.allocations = append(ma.allocations, data)

		// GC 통계 수집
		ma.tuner.monitor.collectStats()

		// 메모리 한계에 도달하면 일부 해제
		if ma.checkMemoryLimit() {
			ma.releaseMemory(len(ma.allocations) / 2)
		}
	}
}

// checkMemoryLimit는 메모리 사용량이 한계를 초과하는지 확인합니다.
func (ma *MemoryAllocator) checkMemoryLimit() bool {
	var stats runtime.MemStats
	runtime.ReadMemStats(&stats)
	return stats.HeapAlloc > ma.tuner.memLimit
}

// releaseMemory는 지정된 수의 할당을 해제합니다.
func (ma *MemoryAllocator) releaseMemory(count int) {
	if count > len(ma.allocations) {
		count = len(ma.allocations)
	}
	ma.allocations = ma.allocations[count:]
	runtime.GC() // 명시적 GC 실행
}

// =============================================================
// Chapter 4: GC 성능 측정
// GC의 성능을 측정하고 분석합니다.
// =============================================================

// GCBenchmark는 다양한 GC 설정의 성능을 측정합니다.
func RunGCBenchmark() {
	scenarios := []struct {
		gcPercent int
		memLimit  uint64
		allocSize []int
	}{
		{
			gcPercent: 100,                                      // 기본값
			memLimit:  1 * 1024 * 1024 * 1024,                   // 1GB
			allocSize: generateAllocationSizes(1000, 1024*1024), // 1MB 단위
		},
		{
			gcPercent: 200,                    // GC 빈도 감소
			memLimit:  2 * 1024 * 1024 * 1024, // 2GB
			allocSize: generateAllocationSizes(1000, 1024*1024),
		},
	}

	for i, scenario := range scenarios {
		fmt.Printf("\nScenario %d: GOGC=%d, Memory Limit=%d MB\n",
			i+1, scenario.gcPercent, scenario.memLimit/(1024*1024))

		tuner := NewGCTuner(scenario.gcPercent, scenario.memLimit)
		allocator := NewMemoryAllocator(tuner)

		start := time.Now()
		allocator.AllocateMemory(scenario.allocSize)
		duration := time.Since(start)

		printGCStats(tuner.monitor, duration)
	}
}

// generateAllocationSizes는 테스트용 할당 크기를 생성합니다.
func generateAllocationSizes(count, maxSize int) []int {
	sizes := make([]int, count)
	for i := range sizes {
		sizes[i] = (i % maxSize) + 1024 // 최소 1KB
	}
	return sizes
}

// printGCStats는 GC 통계를 출력합니다.
func printGCStats(monitor *GCMonitor, duration time.Duration) {
	monitor.mu.Lock()
	defer monitor.mu.Unlock()

	var totalPause time.Duration
	var maxPause time.Duration
	for _, stat := range monitor.stats {
		totalPause += stat.Pause
		if stat.Pause > maxPause {
			maxPause = stat.Pause
		}
	}

	fmt.Printf("실행 시간: %v\n", duration)
	fmt.Printf("GC 실행 횟수: %d\n", len(monitor.stats))
	fmt.Printf("평균 GC 중지 시간: %v\n", totalPause/time.Duration(len(monitor.stats)))
	fmt.Printf("최대 GC 중지 시간: %v\n", maxPause)
}

// RunGCTuningDemo demonstrates various GC tuning techniques
func RunGCTuningDemo() {
	fmt.Println("Starting GC Tuning Demo...")
	RunGCBenchmark()
}

/*
GC 튜닝 가이드라인:

1. GOGC 설정
   - 기본값(100)은 live heap의 100%가 추가로 할당되면 GC 실행
   - 값을 높이면 GC 빈도는 감소하지만 메모리 사용량 증가
   - 값을 낮추면 GC 빈도는 증가하지만 메모리 사용량 감소

2. 메모리 할당 패턴
   - 큰 객체의 수명주기 관리
   - 임시 객체 할당 최소화
   - 객체 풀링 고려

3. GC 모니터링
   - runtime.ReadMemStats 사용
   - GODEBUG=gctrace=1 환경변수 활용
   - pprof 프로파일링 도구 사용

4. 성능 최적화
   - GC 중지 시간 모니터링
   - 메모리 사용량 vs GC 빈도 트레이드오프 고려
   - 실제 워크로드에서 벤치마크 수행

일반적인 최적화 시나리오:

1. 대용량 힙
   - GOGC 값을 높여 GC 빈도 감소
   - 메모리 여유가 있는 환경에 적합

2. 낮은 지연 시간 요구사항
   - GOGC 값을 낮춰 GC 중지 시간 감소
   - 메모리 사용량이 증가할 수 있음

3. 배치 처리
   - 작업 완료 후 명시적 GC 실행
   - 메모리 사용량 피크 관리

4. 실시간 시스템
   - GC 중지 시간 최소화
   - 객체 할당 패턴 최적화
*/
