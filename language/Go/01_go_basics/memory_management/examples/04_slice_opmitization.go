/*
이 예제는 Go 슬라이스의 메모리 최적화 기법을 설명합니다.
슬라이스는 Go에서 가장 많이 사용되는 데이터 구조 중 하나이며,
효율적인 사용은 프로그램의 전반적인 성능에 큰 영향을 미칩니다.

주요 내용:
1. 슬라이스 내부 구조와 메모리 레이아웃
2. 용량 관리와 재할당 최적화
3. 메모리 누수 방지
4. 대용량 슬라이스 처리 기법

실행 방법:
go run slice_optimization.go
*/

package examples

import (
	"fmt"
	"runtime"
	"time"
)

// =============================================================
// Chapter 1: 슬라이스 기본 구조와 메모리 레이아웃
// 슬라이스의 내부 구조를 이해하고 메모리 사용을 최적화합니다.
// =============================================================

// SliceHeader는 슬라이스의 내부 구조를 시뮬레이션합니다.
// 실제 런타임의 슬라이스 헤더와 유사한 구조입니다.
type SliceHeader struct {
	Data uintptr // 배열에 대한 포인터
	Len  int     // 슬라이스의 길이
	Cap  int     // 슬라이스의 용량
}

// demonstrateSliceInternals는 슬라이스의 내부 동작을 보여줍니다.
func demonstrateSliceInternals() {
	// 기본 슬라이스 생성
	original := make([]int, 3, 5)
	original[0] = 1
	original[1] = 2
	original[2] = 3

	// 슬라이싱 작업
	slice1 := original[1:3]
	slice2 := original[1:3:3] // 용량 제한

	fmt.Printf("Original: len=%d cap=%d %v\n",
		len(original), cap(original), original)
	fmt.Printf("Slice1: len=%d cap=%d %v\n",
		len(slice1), cap(slice1), slice1)
	fmt.Printf("Slice2: len=%d cap=%d %v\n",
		len(slice2), cap(slice2), slice2)

	// 메모리 공유 demonstration
	slice1[0] = 20
	fmt.Printf("After modification - Original: %v\n", original)
}

// =============================================================
// Chapter 2: 용량 관리와 재할당 최적화
// 슬라이스 확장 시의 메모리 재할당을 최적화합니다.
// =============================================================

// OptimizedAppend는 용량을 고려한 최적화된 append 연산을 보여줍니다.
func OptimizedAppend() {
	// 초기 용량을 충분히 할당
	s := make([]int, 0, 1000)
	start := time.Now()

	// 최적화된 추가 작업
	for i := 0; i < 1000; i++ {
		s = append(s, i)
	}

	fmt.Printf("Optimized append took: %v\n", time.Since(start))
	fmt.Printf("Final capacity: %d\n", cap(s))
}

// UnoptimizedAppend는 잦은 재할당이 발생하는 비최적화 버전입니다.
func UnoptimizedAppend() {
	// 초기 용량 없이 시작
	var s []int
	start := time.Now()

	// 비최적화된 추가 작업
	for i := 0; i < 1000; i++ {
		s = append(s, i)
	}

	fmt.Printf("Unoptimized append took: %v\n", time.Since(start))
	fmt.Printf("Final capacity: %d\n", cap(s))
}

// =============================================================
// Chapter 3: 메모리 누수 방지
// 슬라이스 사용 시 발생할 수 있는 메모리 누수를 방지합니다.
// =============================================================

// LargeData는 메모리 누수 시나리오를 시뮬레이션합니다.
type LargeData struct {
	items []byte
}

// PreventMemoryLeak은 메모리 누수를 방지하는 기법을 보여줍니다.
func PreventMemoryLeak() {
	// 큰 슬라이스 생성
	data := &LargeData{
		items: make([]byte, 1000000),
	}

	// 작은 부분을 추출할 때 메모리 누수 방지
	leaked := data.items[10:20]       // 전체 배열을 참조
	safe := make([]byte, len(leaked)) // 새로운 슬라이스 생성
	copy(safe, leaked)                // 필요한 데이터만 복사

	// data 변수가 스코프를 벗어나도 leaked는 전체 배열을 메모리에 유지
	// safe는 필요한 부분만 유지
	runtime.GC()
	printMemStats("After slicing")
}

// =============================================================
// Chapter 4: 대용량 슬라이스 처리
// 대용량 데이터를 효율적으로 처리하는 기법을 설명합니다.
// =============================================================

// ChunkProcessor는 대용량 슬라이스를 청크 단위로 처리합니다.
type ChunkProcessor struct {
	chunkSize int
	data      []int
}

// NewChunkProcessor는 새로운 청크 프로세서를 생성합니다.
func NewChunkProcessor(chunkSize int) *ChunkProcessor {
	return &ChunkProcessor{
		chunkSize: chunkSize,
	}
}

// ProcessInChunks는 대용량 데이터를 청크 단위로 처리합니다.
func (cp *ChunkProcessor) ProcessInChunks(data []int) {
	cp.data = data
	dataLen := len(data)

	for i := 0; i < dataLen; i += cp.chunkSize {
		end := i + cp.chunkSize
		if end > dataLen {
			end = dataLen
		}

		// 청크 단위로 처리
		chunk := cp.data[i:end]
		cp.processChunk(chunk)

		// 메모리 사용량 모니터링
		if i%1000000 == 0 {
			runtime.GC()
			printMemStats(fmt.Sprintf("After processing %d items", i))
		}
	}
}

// processChunk는 개별 청크를 처리합니다.
func (cp *ChunkProcessor) processChunk(chunk []int) {
	// 청크 처리 로직
	for i := range chunk {
		chunk[i] *= 2 // 예시 처리
	}
}

// printMemStats는 현재 메모리 사용량을 출력합니다.
func printMemStats(msg string) {
	var stats runtime.MemStats
	runtime.ReadMemStats(&stats)

	fmt.Printf("\n=== %s ===\n", msg)
	fmt.Printf("Heap Alloc: %d MB\n", stats.HeapAlloc/1024/1024)
	fmt.Printf("Total Alloc: %d MB\n", stats.TotalAlloc/1024/1024)
}

// RunSliceOptimizationDemo demonstrates various slice optimization techniques
func RunSliceOptimizationDemo() {
	fmt.Println("=== Slice Internals Demo ===")
	demonstrateSliceInternals()

	fmt.Println("\n=== Append Performance Demo ===")
	OptimizedAppend()
	UnoptimizedAppend()

	fmt.Println("\n=== Memory Leak Prevention Demo ===")
	PreventMemoryLeak()

	fmt.Println("\n=== Large Data Processing Demo ===")
	// 대용량 데이터 생성
	data := make([]int, 1000000)
	for i := range data {
		data[i] = i
	}

	processor := NewChunkProcessor(1000)
	processor.ProcessInChunks(data)
}

/*
슬라이스 최적화 주요 팁:

1. 용량 관리
   - 예상 크기로 초기 용량 설정
   - append 호출 최소화
   - 용량이 크게 증가할 것이 예상되면 미리 할당

2. 메모리 누수 방지
   - 큰 배열의 작은 슬라이스 참조 주의
   - 필요한 데이터만 새로운 슬라이스로 복사
   - 참조가 필요 없는 슬라이스는 nil 설정

3. 대용량 처리
   - 청크 단위로 처리하여 메모리 사용 제어
   - 정기적인 GC 고려
   - 메모리 사용량 모니터링

4. 성능 최적화
   - 불필요한 복사 작업 방지
   - 슬라이싱 작업 최소화
   - 적절한 용량 예측과 할당

모니터링 및 프로파일링:
1. runtime.ReadMemStats로 메모리 사용량 추적
2. pprof로 메모리 할당 패턴 분석
3. 벤치마크로 최적화 효과 측정
*/
