/*
이 예제는 Go의 메모리 프로파일링 기능을 실제로 활용하는 방법을 보여줍니다.
주요 내용:
1. pprof를 사용한 메모리 프로파일 생성
2. 런타임 메모리 통계 수집 및 분석
3. 메모리 할당 패턴 시각화
4. 일반적인 메모리 문제 식별 방법

실행 방법:
1. 프로그램 실행: go run memory_profiling.go
2. 프로파일 분석: go tool pprof memory.prof
3. 웹 인터페이스: go tool pprof -http=:8080 memory.prof
*/

package examples

import (
	"fmt"
	"os"
	"runtime"
	"runtime/pprof"
	"sync"
	"time"
)

// MemoryIntensiveTask는 메모리를 많이 사용하는 작업을 시뮬레이션합니다.
// 이 구조체는 다양한 메모리 할당 패턴을 보여주기 위해 설계되었습니다.
type MemoryIntensiveTask struct {
	// 대용량 데이터를 저장하는 맵
	dataStore map[string][]byte
	// 동시성 접근을 위한 뮤텍스
	mu sync.Mutex
	// 메모리 사용 통계
	stats struct {
		totalAllocations int64
		currentSize      int64
	}
}

// NewMemoryIntensiveTask는 새로운 작업 인스턴스를 생성합니다.
func NewMemoryIntensiveTask() *MemoryIntensiveTask {
	return &MemoryIntensiveTask{
		dataStore: make(map[string][]byte),
	}
}

// allocateMemory는 지정된 크기의 메모리를 할당합니다.
// size: 할당할 메모리 크기 (바이트)
// key: 데이터 저장소에서 사용할 키
func (m *MemoryIntensiveTask) allocateMemory(size int, key string) {
	m.mu.Lock()
	defer m.mu.Unlock()

	// 대용량 바이트 슬라이스 할당
	data := make([]byte, size)
	// 데이터 초기화 (메모리 실제 사용을 시뮬레이션)
	for i := range data {
		data[i] = byte(i % 256)
	}

	m.dataStore[key] = data
	m.stats.totalAllocations++
	m.stats.currentSize += int64(size)
}

// releaseMemory는 특정 키에 해당하는 메모리를 해제합니다.
func (m *MemoryIntensiveTask) releaseMemory(key string) {
	m.mu.Lock()
	defer m.mu.Unlock()

	if data, exists := m.dataStore[key]; exists {
		m.stats.currentSize -= int64(len(data))
		delete(m.dataStore, key)
	}
}

// printMemoryStats는 현재 메모리 사용 통계를 출력합니다.
// memStats를 통해 Go 런타임의 자세한 메모리 통계를 확인할 수 있습니다.
func printMemoryStats(msg string) {
	var memStats runtime.MemStats
	runtime.ReadMemStats(&memStats)

	fmt.Printf("\n=== %s ===\n", msg)
	fmt.Printf("Heap 할당: %d MB\n", memStats.HeapAlloc/1024/1024)
	fmt.Printf("전체 할당: %d MB\n", memStats.TotalAlloc/1024/1024)
	fmt.Printf("Heap 객체 수: %d\n", memStats.HeapObjects)
	fmt.Printf("GC 횟수: %d\n", memStats.NumGC)
	fmt.Printf("GC CPU 사용률: %v%%\n", memStats.GCCPUFraction*100)
}

// RunMemoryProfilingDemo는 메모리 프로파일링 데모를 실행합니다.
func RunMemoryProfilingDemo() error {
	// 프로파일링 파일 생성
	f, err := os.Create("memory.prof")
	if err != nil {
		return fmt.Errorf("프로파일 파일 생성 실패: %v", err)
	}
	defer f.Close()

	// 초기 메모리 상태 출력
	printMemoryStats("초기 상태")

	// 메모리 집중 작업 시작
	task := NewMemoryIntensiveTask()

	// 다양한 크기의 메모리 할당
	sizes := []int{
		10 * 1024 * 1024, // 10MB
		5 * 1024 * 1024,  // 5MB
		15 * 1024 * 1024, // 15MB
		8 * 1024 * 1024,  // 8MB
	}

	// 메모리 할당 수행
	for i, size := range sizes {
		key := fmt.Sprintf("data_%d", i)
		task.allocateMemory(size, key)

		// 일부 키는 바로 해제하여 메모리 패턴 생성
		if i%2 == 0 {
			time.Sleep(100 * time.Millisecond)
			task.releaseMemory(key)
		}

		printMemoryStats(fmt.Sprintf("할당 #%d 후", i+1))
	}

	// 인위적인 메모리 압박 생성
	var stress [][]byte
	for i := 0; i < 100; i++ {
		stress = append(stress, make([]byte, 1024*1024)) // 1MB씩 할당
		if i%10 == 0 {
			time.Sleep(100 * time.Millisecond)
			printMemoryStats(fmt.Sprintf("스트레스 테스트 #%d", i/10))
		}
	}

	// 최종 상태에서 힙 프로파일 작성
	if err := pprof.WriteHeapProfile(f); err != nil {
		return fmt.Errorf("힙 프로파일 작성 실패: %v", err)
	}

	// 메모리 해제 (stress 슬라이스)
	stress = nil

	// 가비지 컬렉션 실행
	runtime.GC()
	printMemoryStats("최종 상태")

	fmt.Println("\n프로파일링 완료. 다음 명령으로 결과를 분석하세요:")
	fmt.Println("1. go tool pprof memory.prof")
	fmt.Println("2. go tool pprof -http=:8080 memory.prof")

	return nil
}

// 프로파일 분석 가이드:
/*
pprof 사용 방법:

1. 상위 메모리 할당 지점 확인
   (pprof) top

2. 특정 함수의 메모리 사용량 확인
   (pprof) list RunMemoryProfilingDemo

3. 할당 그래프 생성
   (pprof) web

4. 메모리 사용량 시각화
   go tool pprof -http=:8080 memory.prof

주요 분석 포인트:
1. 대용량 할당이 발생하는 지점 식별
2. 메모리 해제 패턴 확인
3. 일시적 할당과 영구적 할당 구분
4. GC 동작 패턴 분석
*/
