package main

import (
	"fmt"
	"runtime"
	"sync"
	"time"
	"unsafe"
)

// =============================================================
// Chapter 1: 스택 vs 힙 할당
// Go에서 변수가 스택과 힙 중 어디에 할당되는지 이해하는 것은
// 성능 최적화에 매우 중요합니다.
// =============================================================

// 스택에 할당되는 간단한 구조체
type Point struct {
	X, Y int
}

// stackAllocation은 주로 스택에 메모리가 할당되는 예제입니다.
// 컴파일러의 escape 분석 결과, 이 함수에서 생성된 변수들은
// 함수 스코프를 벗어나지 않으므로 스택에 할당됩니다.
func stackAllocation() Point {
	// Point 구조체는 스택에 할당됩니다.
	p := Point{X: 10, Y: 20}

	// 지역 변수도 스택에 할당됩니다.
	x := 100
	y := 200

	// 작은 크기의 배열도 스택에 할당됩니다.
	arr := [3]int{x, y, x + y}

	fmt.Printf("%d", arr)

	return p // 반환값은 복사됩니다.
}

// heapAllocation은 힙에 메모리가 할당되는 예제입니다.
// 함수가 변수에 대한 포인터를 반환하거나, 변수가 함수 스코프를
// 벗어나는 경우 힙에 할당됩니다.
func heapAllocation() *Point {
	// Point 구조체가 힙에 할당됩니다.
	// 포인터를 반환하기 때문에 escape 분석에 의해 힙 할당이 결정됩니다.
	p := &Point{X: 10, Y: 20}

	// 큰 크기의 슬라이스는 힙에 할당됩니다.
	data := make([]int, 1000000)

	// 고루틴에서 사용되는 변수도 힙에 할당됩니다.
	go func() {
		fmt.Println(*p)
		fmt.Println(len(data))
	}()

	return p
}

// =============================================================
// Chapter 2: 가비지 컬렉션과 메모리 해제
// Go의 GC는 더 이상 참조되지 않는 힙 메모리를 자동으로 회수합니다.
// 하지만 개발자가 메모리 사용 패턴을 이해하고 최적화하는 것이 중요합니다.
// =============================================================

// MemoryUser는 메모리를 사용하고 해제하는 예제를 위한 구조체입니다.
type MemoryUser struct {
	data []byte
}

// allocateMemory는 대량의 메모리를 할당하고 GC 동작을 유발합니다.
func (m *MemoryUser) allocateMemory() {
	// 대량의 메모리 할당
	m.data = make([]byte, 100*1024*1024) // 100MB

	// 메모리 사용 현황 출력
	printMemStats("대량 메모리 할당 후")

	// GC 강제 실행
	runtime.GC()
	printMemStats("GC 실행 후")
}

// releaseMemory는 명시적으로 메모리를 해제합니다.
func (m *MemoryUser) releaseMemory() {
	// 슬라이스를 nil로 설정하여 메모리 해제
	m.data = nil

	// GC 실행을 위한 힌트 제공
	runtime.GC()
	printMemStats("메모리 해제 후")
}

// printMemStats는 현재 메모리 사용 현황을 출력합니다.
func printMemStats(msg string) {
	var stats runtime.MemStats
	runtime.ReadMemStats(&stats)

	fmt.Printf("\n=== %s ===\n", msg)
	fmt.Printf("Heap 할당: %d MB\n", stats.HeapAlloc/1024/1024)
	fmt.Printf("전체 할당: %d MB\n", stats.TotalAlloc/1024/1024)
	fmt.Printf("GC 횟수: %d\n", stats.NumGC)
}

// =============================================================
// Chapter 3: 메모리 누수 방지
// 메모리 누수는 주로 불필요한 참조가 유지되거나,
// 리소스가 적절히 해제되지 않을 때 발생합니다.
// =============================================================

// LeakyResource는 메모리 누수가 발생할 수 있는 리소스를 시뮬레이션합니다.
type LeakyResource struct {
	mu      sync.Mutex
	cache   map[string][]byte
	cleanup chan struct{}
}

// NewLeakyResource는 잠재적 메모리 누수가 있는 리소스를 생성합니다.
func NewLeakyResource() *LeakyResource {
	lr := &LeakyResource{
		cache:   make(map[string][]byte),
		cleanup: make(chan struct{}),
	}

	// 정리 작업을 수행하는 고루틴
	// 주의: cleanup 채널이 닫히지 않으면 고루틴 누수 발생
	go func() {
		ticker := time.NewTicker(time.Second)
		defer ticker.Stop()

		for {
			select {
			case <-ticker.C:
				lr.mu.Lock()
				// 캐시 정리 작업
				lr.mu.Unlock()
			case <-lr.cleanup:
				return
			}
		}
	}()

	return lr
}

// Close는 리소스를 적절히 정리합니다.
func (lr *LeakyResource) Close() {
	// cleanup 채널을 닫아 고루틴 종료
	close(lr.cleanup)

	lr.mu.Lock()
	// 캐시 맵 초기화
	lr.cache = nil
	lr.mu.Unlock()
}

// =============================================================
// Chapter 4: 메모리 효율적인 데이터 구조
// 데이터 구조의 설계는 메모리 사용량과 성능에 큰 영향을 미칩니다.
// =============================================================

// 메모리 효율적인 구조체 설계
// 필드를 크기순으로 정렬하여 패딩을 최소화합니다.
type EfficientStruct struct {
	// 8바이트 필드
	timestamp int64
	value     float64
	// 4바이트 필드
	count int32
	// 2바이트 필드
	flag int16
	// 1바이트 필드
	status byte
	// 1바이트 패딩이 자동으로 추가됨
}

// 비효율적인 구조체 설계
// 필드 순서가 잘못되어 불필요한 패딩이 발생합니다.
type InefficientStruct struct {
	// 1바이트 필드
	status byte
	// 7바이트 패딩
	// 8바이트 필드
	timestamp int64
	// 2바이트 필드
	flag int16
	// 6바이트 패딩
	// 8바이트 필드
	value float64
	// 4바이트 필드
	count int32
	// 4바이트 패딩
}

func main() {
	// Chapter 1: 스택 vs 힙 할당 예제
	stackPoint := stackAllocation()
	heapPoint := heapAllocation()
	fmt.Printf("Stack Point: %+v\n", stackPoint)
	fmt.Printf("Heap Point: %+v\n", *heapPoint)

	// Chapter 2: 가비지 컬렉션 예제
	mu := &MemoryUser{}
	mu.allocateMemory()
	time.Sleep(time.Second) // GC 동작 대기
	mu.releaseMemory()

	// Chapter 3: 메모리 누수 방지 예제
	lr := NewLeakyResource()
	// 리소스 사용
	time.Sleep(2 * time.Second)
	// 적절한 리소스 정리
	lr.Close()

	// Chapter 4: 메모리 효율적인 구조체 예제
	efficient := EfficientStruct{
		timestamp: time.Now().Unix(),
		value:     3.14,
		count:     100,
		flag:      1,
		status:    1,
	}

	inefficient := InefficientStruct{
		timestamp: time.Now().Unix(),
		value:     3.14,
		count:     100,
		flag:      1,
		status:    1,
	}

	fmt.Printf("\nEfficient struct size: %d bytes\n",
		unsafe.Sizeof(efficient))
	fmt.Printf("Inefficient struct size: %d bytes\n",
		unsafe.Sizeof(inefficient))
}
