/*
이 예제는 Go에서 메모리 풀링을 구현하고 활용하는 방법을 설명합니다.
메모리 풀링은 자주 할당되고 해제되는 객체들을 재사용하여 GC 부하를 줄이고
성능을 향상시키는 기법입니다.

주요 내용:
1. sync.Pool을 사용한 기본적인 객체 풀링
2. 사용자 정의 메모리 풀 구현
3. 버퍼 풀링을 통한 I/O 최적화
4. 풀링 사용 시의 성능 비교

실행 방법:
go run memory_pooling.go
*/

package examples

import (
	"bytes"
	"fmt"
	"sync"
	"time"
)

// =============================================================
// Chapter 1: sync.Pool을 사용한 기본 객체 풀링
// sync.Pool은 Go 표준 라이브러리에서 제공하는 객체 풀 구현입니다.
// =============================================================

// LargeObject는 풀링할 대상이 되는 큰 객체를 시뮬레이션합니다.
type LargeObject struct {
	buffer []byte
	data   map[string]interface{}
}

// objectPool은 LargeObject의 풀입니다.
var objectPool = &sync.Pool{
	New: func() interface{} {
		// 새로운 객체가 필요할 때 호출되는 생성 함수
		return &LargeObject{
			buffer: make([]byte, 1024*1024), // 1MB 버퍼
			data:   make(map[string]interface{}),
		}
	},
}

// getLargeObject는 풀에서 객체를 가져오거나 새로 생성합니다.
func getLargeObject() *LargeObject {
	return objectPool.Get().(*LargeObject)
}

// releaseLargeObject는 객체를 풀로 반환합니다.
func releaseLargeObject(obj *LargeObject) {
	// 재사용 전에 객체 초기화
	obj.data = make(map[string]interface{})
	for i := range obj.buffer {
		obj.buffer[i] = 0
	}
	objectPool.Put(obj)
}

// =============================================================
// Chapter 2: 사용자 정의 메모리 풀
// 특정 요구사항에 맞춘 커스텀 메모리 풀 구현을 보여줍니다.
// =============================================================

// CustomPool은 크기별로 버퍼를 관리하는 사용자 정의 풀입니다.
type CustomPool struct {
	pools    map[int]*sync.Pool
	maxSize  int
	sizeTier []int
	mu       sync.RWMutex
}

// NewCustomPool은 새로운 커스텀 풀을 생성합니다.
func NewCustomPool(maxSize int, tiers []int) *CustomPool {
	cp := &CustomPool{
		pools:    make(map[int]*sync.Pool),
		maxSize:  maxSize,
		sizeTier: tiers,
	}

	for _, size := range tiers {
		size := size // 클로저를 위한 변수 복사
		cp.pools[size] = &sync.Pool{
			New: func() interface{} {
				return make([]byte, size)
			},
		}
	}

	return cp
}

// GetBuffer는 요청된 크기에 맞는 버퍼를 반환합니다.
func (cp *CustomPool) GetBuffer(size int) []byte {
	if size > cp.maxSize {
		return make([]byte, size)
	}

	// 적절한 크기 티어 찾기
	tierSize := cp.findTierSize(size)
	return cp.pools[tierSize].Get().([]byte)
}

// findTierSize는 요청된 크기에 맞는 티어 크기를 찾습니다.
func (cp *CustomPool) findTierSize(size int) int {
	cp.mu.RLock()
	defer cp.mu.RUnlock()

	for _, tierSize := range cp.sizeTier {
		if tierSize >= size {
			return tierSize
		}
	}
	return cp.sizeTier[len(cp.sizeTier)-1]
}

// PutBuffer는 버퍼를 풀로 반환합니다.
func (cp *CustomPool) PutBuffer(buf []byte) {
	size := cap(buf)
	if size > cp.maxSize {
		return // 큰 버퍼는 GC가 처리하도록 함
	}

	tierSize := cp.findTierSize(size)
	cp.pools[tierSize].Put(buf[:tierSize])
}

// =============================================================
// Chapter 3: 버퍼 풀을 활용한 I/O 최적화
// bytes.Buffer를 재사용하여 I/O 작업을 최적화하는 예제입니다.
// =============================================================

// BufferPool은 bytes.Buffer의 풀입니다.
var BufferPool = sync.Pool{
	New: func() interface{} {
		return new(bytes.Buffer)
	},
}

// getBuffer는 풀에서 Buffer를 가져옵니다.
func getBuffer() *bytes.Buffer {
	return BufferPool.Get().(*bytes.Buffer)
}

// putBuffer는 Buffer를 풀로 반환합니다.
func putBuffer(buf *bytes.Buffer) {
	buf.Reset()
	BufferPool.Put(buf)
}

// WriteData는 풀링된 버퍼를 사용하여 데이터를 처리합니다.
func WriteData(data []byte) string {
	buf := getBuffer()
	defer putBuffer(buf)

	buf.Write(data)
	buf.WriteString(" - processed")
	return buf.String()
}

// =============================================================
// Chapter 4: 성능 비교 및 벤치마킹
// 풀링 사용 여부에 따른 성능 차이를 측정합니다.
// =============================================================

// PoolingBenchmark는 풀링의 성능 이점을 측정합니다.
func PoolingBenchmark(iterations int) (withPool, withoutPool time.Duration) {
	// 풀링을 사용하는 경우
	start := time.Now()
	for i := 0; i < iterations; i++ {
		obj := getLargeObject()
		// 객체 사용 시뮬레이션
		obj.buffer[0] = byte(i)
		releaseLargeObject(obj)
	}
	withPool = time.Since(start)

	// 풀링을 사용하지 않는 경우
	start = time.Now()
	for i := 0; i < iterations; i++ {
		obj := &LargeObject{
			buffer: make([]byte, 1024*1024),
			data:   make(map[string]interface{}),
		}
		obj.buffer[0] = byte(i)
		// 객체가 자동으로 GC됨
	}
	withoutPool = time.Since(start)

	return
}

// RunMemoryPoolingDemo demonstrates various memory pooling techniques
func RunMemoryPoolingDemo() {
	// 1. 기본 객체 풀링 데모
	obj := getLargeObject()
	obj.data["key"] = "value"
	releaseLargeObject(obj)

	// 2. 커스텀 풀 사용 데모
	customPool := NewCustomPool(1024*1024, []int{
		1024,    // 1KB
		4096,    // 4KB
		16384,   // 16KB
		65536,   // 64KB
		262144,  // 256KB
		1048576, // 1MB
	})

	buf := customPool.GetBuffer(2000) // 4KB 티어 사용
	// 버퍼 사용
	customPool.PutBuffer(buf)

	// 3. I/O 최적화 데모
	result := WriteData([]byte("test data"))
	fmt.Println("Processed:", result)

	// 4. 성능 벤치마크
	withPool, withoutPool := PoolingBenchmark(1000)
	fmt.Printf("\n성능 비교 (1000회 반복):\n")
	fmt.Printf("풀링 사용: %v\n", withPool)
	fmt.Printf("풀링 미사용: %v\n", withoutPool)
	fmt.Printf("성능 향상: %.2f%%\n",
		float64(withoutPool-withPool)/float64(withoutPool)*100)
}

/*
메모리 풀링 사용 시 주의사항:

1. 객체 초기화
   - 풀에서 가져온 객체는 항상 적절히 초기화해야 함
   - 이전 사용에서 남은 데이터가 있을 수 있음

2. 동시성 고려
   - sync.Pool은 동시성에 안전함
   - 커스텀 풀 구현 시 동시성 보호 필요

3. 메모리 사용량
   - 풀 크기가 너무 크면 메모리 사용량 증가
   - 적절한 최대 크기 설정 필요

4. GC 영향
   - sync.Pool은 GC 발생 시 풀이 비워질 수 있음
   - 중요한 객체는 별도 보관 필요

5. 성능 모니터링
   - 실제 사용 패턴에서 성능 이점 확인
   - 프로파일링으로 메모리 사용량 모니터링

최적화 팁:
1. 자주 할당/해제되는 객체에 풀링 적용
2. 객체 크기와 수명 고려하여 풀링 결정
3. 버퍼 크기 티어 신중히 설계
4. 정기적인 성능 측정으로 효과 확인
*/
