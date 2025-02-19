/*
이 예제는 Go 구조체의 메모리 정렬과 최적화를 설명합니다.
구조체 필드의 순서와 크기는 메모리 패딩과 캐시 성능에
중요한 영향을 미칩니다.

주요 내용:
1. 구조체 메모리 레이아웃과 패딩
2. 캐시 라인 정렬
3. 성능 최적화 기법
4. 실제 성능 측정

실행 방법:
go run struct_alignment.go
*/

package examples

import (
	"fmt"
	"sync"
	"time"
	"unsafe"
)

// =============================================================
// Chapter 1: 구조체 메모리 레이아웃
// 구조체 필드의 정렬과 패딩이 메모리에 미치는 영향을 설명합니다.
// =============================================================

// PoorlyAligned는 비효율적인 메모리 정렬을 가진 구조체입니다.
// 불필요한 패딩이 발생하여 메모리를 낭비합니다.
type PoorlyAligned struct {
	flag    bool    // 1바이트 + 7바이트 패딩
	num     float64 // 8바이트
	name    string  // 16바이트
	data    byte    // 1바이트 + 7바이트 패딩
	counter uint64  // 8바이트
}

// WellAligned는 효율적인 메모리 정렬을 가진 구조체입니다.
// 패딩을 최소화하여 메모리를 절약합니다.
type WellAligned struct {
	num     float64 // 8바이트
	counter uint64  // 8바이트
	name    string  // 16바이트
	flag    bool    // 1바이트
	data    byte    // 1바이트
	// 6바이트 패딩 (8바이트 정렬을 위해)
}

// MemoryLayout은 구조체의 메모리 레이아웃을 분석합니다.
func AnalyzeMemoryLayout() {
	poor := PoorlyAligned{}
	well := WellAligned{}

	fmt.Printf("=== 구조체 메모리 레이아웃 분석 ===\n")
	fmt.Printf("PoorlyAligned 크기: %d 바이트\n", unsafe.Sizeof(poor))
	fmt.Printf("WellAligned 크기: %d 바이트\n", unsafe.Sizeof(well))

	// 필드 오프셋 분석
	fmt.Printf("\nPoorlyAligned 필드 오프셋:\n")
	fmt.Printf("flag: %d\n", unsafe.Offsetof(poor.flag))
	fmt.Printf("num: %d\n", unsafe.Offsetof(poor.num))
	fmt.Printf("name: %d\n", unsafe.Offsetof(poor.name))
	fmt.Printf("data: %d\n", unsafe.Offsetof(poor.data))
	fmt.Printf("counter: %d\n", unsafe.Offsetof(poor.counter))
}

// =============================================================
// Chapter 2: 캐시 라인 정렬
// 캐시 성능을 고려한 구조체 설계를 설명합니다.
// =============================================================

// CacheAligned는 캐시 라인(64바이트)에 맞춰 정렬된 구조체입니다.
type CacheAligned struct {
	// 첫 번째 캐시 라인
	data [64]byte // 64바이트
	_    [64]byte // 패딩

	// 두 번째 캐시 라인
	counter uint64   // 8바이트
	padding [56]byte // 패딩
}

// NonCacheAligned는 캐시 라인을 고려하지 않은 구조체입니다.
type NonCacheAligned struct {
	data    [64]byte
	counter uint64
}

// BenchmarkCacheAlignment은 캐시 정렬의 성능 영향을 측정합니다.
func BenchmarkCacheAlignment() {
	const iterations = 10000000

	aligned := make([]CacheAligned, 4)
	nonAligned := make([]NonCacheAligned, 4)

	start := time.Now()
	var wg sync.WaitGroup
	for i := 0; i < 4; i++ {
		wg.Add(1)
		go func(idx int) {
			defer wg.Done()
			for j := 0; j < iterations; j++ {
				aligned[idx].counter++
			}
		}(i)
	}
	wg.Wait()
	alignedDuration := time.Since(start)

	start = time.Now()
	for i := 0; i < 4; i++ {
		wg.Add(1)
		go func(idx int) {
			defer wg.Done()
			for j := 0; j < iterations; j++ {
				nonAligned[idx].counter++
			}
		}(i)
	}
	wg.Wait()
	nonAlignedDuration := time.Since(start)

	fmt.Printf("\n=== 캐시 정렬 성능 비교 ===\n")
	fmt.Printf("Cache Aligned: %v\n", alignedDuration)
	fmt.Printf("Non-Cache Aligned: %v\n", nonAlignedDuration)
}

// =============================================================
// Chapter 3: 동시성을 고려한 구조체 설계
// 동시 접근 시 발생하는 false sharing을 방지하는 설계를 설명합니다.
// =============================================================

// FalseSharingProne는 false sharing이 발생하기 쉬운 구조체입니다.
type FalseSharingProne struct {
	counters [8]uint64 // 동시 접근되는 카운터들
}

// FalseSharingProtected는 false sharing을 방지하는 구조체입니다.
type FalseSharingProtected struct {
	counters [8]struct {
		value uint64
		_     [56]byte // 패딩으로 캐시 라인 분리
	}
}

// BenchmarkFalseSharing은 false sharing의 영향을 측정합니다.
func BenchmarkFalseSharing() {
	const iterations = 10000000

	prone := &FalseSharingProne{}
	protected := &FalseSharingProtected{}

	start := time.Now()
	var wg sync.WaitGroup
	for i := 0; i < 8; i++ {
		wg.Add(1)
		go func(idx int) {
			defer wg.Done()
			for j := 0; j < iterations; j++ {
				prone.counters[idx]++
			}
		}(i)
	}
	wg.Wait()
	proneDuration := time.Since(start)

	start = time.Now()
	for i := 0; i < 8; i++ {
		wg.Add(1)
		go func(idx int) {
			defer wg.Done()
			for j := 0; j < iterations; j++ {
				protected.counters[idx].value++
			}
		}(i)
	}
	wg.Wait()
	protectedDuration := time.Since(start)

	fmt.Printf("\n=== False Sharing 성능 비교 ===\n")
	fmt.Printf("False Sharing Prone: %v\n", proneDuration)
	fmt.Printf("False Sharing Protected: %v\n", protectedDuration)
}

// =============================================================
// Chapter 4: 최적화 도구와 테크닉
// 구조체 최적화를 위한 도구와 기법을 설명합니다.
// =============================================================

// StructOptimizer는 구조체 최적화를 돕는 유틸리티입니다.
type StructOptimizer struct {
	totalSize    uintptr
	wasted       uintptr
	fieldCount   int
	alignmentGap []uintptr
}

// analyzeStruct는 구조체의 메모리 사용을 분석합니다.
func (so *StructOptimizer) analyzeStruct(size uintptr, fields ...uintptr) {
	so.totalSize = size
	so.fieldCount = len(fields)

	var currentOffset uintptr
	for i, fieldSize := range fields {
		alignment := fieldSize
		if alignment > 8 {
			alignment = 8
		}

		padding := (alignment - (currentOffset % alignment)) % alignment
		so.wasted += padding
		so.alignmentGap = append(so.alignmentGap, padding)

		currentOffset += padding + fieldSize
	}

	finalPadding := (8 - (currentOffset % 8)) % 8
	so.wasted += finalPadding
}

// printAnalysis는 구조체 분석 결과를 출력합니다.
func (so *StructOptimizer) printAnalysis() {
	fmt.Printf("\n=== 구조체 최적화 분석 ===\n")
	fmt.Printf("총 크기: %d 바이트\n", so.totalSize)
	fmt.Printf("낭비된 공간: %d 바이트 (%.1f%%)\n",
		so.wasted, float64(so.wasted)/float64(so.totalSize)*100)
	fmt.Printf("필드 수: %d\n", so.fieldCount)

	if len(so.alignmentGap) > 0 {
		fmt.Printf("필드 간 패딩:\n")
		for i, gap := range so.alignmentGap {
			if gap > 0 {
				fmt.Printf("필드 %d 후: %d 바이트\n", i+1, gap)
			}
		}
	}
}

// RunStructAlignmentDemo demonstrates various struct alignment techniques
func RunStructAlignmentDemo() {
	// 1. 메모리 레이아웃 분석
	AnalyzeMemoryLayout()

	// 2. 캐시 정렬 벤치마크
	BenchmarkCacheAlignment()

	// 3. False Sharing 벤치마크
	BenchmarkFalseSharing()

	// 4. 구조체 최적화 분석
	optimizer := &StructOptimizer{}

	// PoorlyAligned 구조체 분석
	optimizer.analyzeStruct(unsafe.Sizeof(PoorlyAligned{}),
		1,  // bool
		8,  // float64
		16, // string
		1,  // byte
		8)  // uint64
	optimizer.printAnalysis()

	// WellAligned 구조체 분석
	optimizer = &StructOptimizer{}
	optimizer.analyzeStruct(unsafe.Sizeof(WellAligned{}),
		8,  // float64
		8,  // uint64
		16, // string
		1,  // bool
		1)  // byte
	optimizer.printAnalysis()
}

/*
구조체 최적화 가이드라인:

1. 필드 정렬
   - 큰 필드부터 작은 필드 순으로 배치
   - 같은 크기의 필드끼리 그룹화
   - 1바이트 필드들을 연속 배치

2. 캐시 고려사항
   - 자주 접근하는 필드를 캐시 라인 시작에 배치
   - 동시 접근되는 필드는 다른 캐시 라인에 배치
   - 필요한 경우 명시적 패딩 추가

3. 메모리 효율성
   - 불필요한 패딩 최소화
   - 필드 크기와 정렬 요구사항 고려
   - 핫 패스의 필드를 최적화

4. 성능 측정
   - 벤치마크로 성능 영향 확인
   - 프로파일링으로 캐시 미스 분석
   - 실제 워크로드에서 테스트

최적화 체크리스트:

1. 구조체 분석
   - unsafe.Sizeof로 전체 크기 확인
   - unsafe.Offsetof로 필드 오프셋 확인
   - 패딩 낭비 계산

2. 성능 고려사항
   - 캐시 라인 크기 (일반적으로 64바이트)
   - CPU 아키텍처의 정렬 요구사항
   - 동시성 패턴

3. 도구 활용
   - go build -gcflags="-m"
   - go tool pprof
   - go test -bench
*/
