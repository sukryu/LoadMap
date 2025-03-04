package examples

import (
	"fmt"
	"sync"
)

// IterationManager는 반복 작업을 관리하는 구조체입니다.
// K8s 스타일: 관련 로직을 구조체로 묶어 모듈화하고 재사용성을 높임.
type IterationManager struct{}

// NewIterationManager는 새로운 IterationManager 인스턴스를 생성합니다.
// K8s 스타일: 생성자 함수는 'New'를 접두사로 사용하며 초기화 캡슐화.
func NewIterationManager() *IterationManager {
	return &IterationManager{}
}

// DemonstrateRangeAdvanced는 range의 다양한 활용법을 보여줍니다.
// K8s 스타일: 메서드는 단일 책임을 가지며 동작을 상세히 주석으로 설명.
func (im *IterationManager) DemonstrateRangeAdvanced() {
	// 슬라이스: 다양한 range 사용 패턴.
	// K8s 스타일: 초기 데이터와 상태를 명확히 로깅.
	numbers := []int{10, 20, 30, 40, 50}
	fmt.Println("=== 슬라이스 Range 심화 ===")

	// 1. 인덱스와 값 모두 사용.
	fmt.Println("인덱스와 값:")
	for i, v := range numbers {
		fmt.Printf("  인덱스: %d, 값: %d\n", i, v)
	}

	// 2. 값만 사용 (인덱스 생략).
	fmt.Println("\n값만 사용:")
	for _, v := range numbers {
		fmt.Printf("  값: %d\n", v)
	}

	// 3. 인덱스만 사용 (값 생략).
	fmt.Println("\n인덱스만 사용:")
	for i := range numbers {
		fmt.Printf("  인덱스: %d\n", i)
	}

	// 맵: 키와 값 순회.
	countryCodes := map[string]string{
		"US": "United States",
		"KR": "South Korea",
		"JP": "Japan",
	}
	fmt.Println("\n=== 맵 Range 심화 ===")

	// 4. 키와 값 모두 사용.
	fmt.Println("키와 값:")
	for k, v := range countryCodes {
		fmt.Printf("  키: %s, 값: %s\n", k, v)
	}

	// 5. 키만 사용 (값 생략).
	fmt.Println("\n키만 사용:")
	for k := range countryCodes {
		fmt.Printf("  키: %s\n", k)
	}

	// 구조체 슬라이스: 복합 데이터 순회.
	type Person struct {
		Name string
		Age  int
	}
	people := []Person{
		{Name: "Alice", Age: 25},
		{Name: "Bob", Age: 30},
	}
	fmt.Println("\n=== 구조체 슬라이스 Range 심화 ===")
	for i, p := range people {
		fmt.Printf("  사람 %d: 이름=%s, 나이=%d\n", i+1, p.Name, p.Age)
	}
}

// IntIterator는 정수 리스트에 대한 사용자 정의 이터레이터입니다.
// K8s 스타일: 인터페이스와 구조체로 이터레이터 패턴 정의.
type IntIterator struct {
	data    []int
	current int
	mu      sync.Mutex // 동시성 안전성을 위한 뮤텍스.
}

// NewIntIterator는 주어진 데이터로 새로운 IntIterator를 생성합니다.
// K8s 스타일: 생성자 함수로 초기화 로직 캡슐화.
func NewIntIterator(data []int) *IntIterator {
	// 데이터 복사본을 만들어 원본 수정 방지.
	// K8s 스타일: 입력 데이터 무결성 보장.
	dataCopy := make([]int, len(data))
	copy(dataCopy, data)
	return &IntIterator{
		data:    dataCopy,
		current: -1, // 초기 위치: 첫 요소 전.
	}
}

// HasNext는 다음 요소가 있는지 확인합니다.
// K8s 스타일: 상태 확인 메서드는 간단하고 명확.
func (it *IntIterator) HasNext() bool {
	it.mu.Lock()
	defer it.mu.Unlock()
	return it.current+1 < len(it.data)
}

// Next는 다음 요소를 반환하고 커서를 이동합니다.
// K8s 스타일: 동작과 에러 조건을 주석으로 명시.
// 반환: 다음 값과 성공 여부 (없으면 0, false).
func (it *IntIterator) Next() (int, bool) {
	it.mu.Lock()
	defer it.mu.Unlock()
	if it.current+1 >= len(it.data) {
		return 0, false // 더 이상 요소 없음.
	}
	it.current++
	return it.data[it.current], true
}

// Reset은 이터레이터를 초기 상태로 되돌립니다.
// K8s 스타일: 리소스 재사용을 위한 메서드 제공.
func (it *IntIterator) Reset() {
	it.mu.Lock()
	defer it.mu.Unlock()
	it.current = -1
}

// DemonstrateIteratorPattern은 사용자 정의 이터레이터 패턴을 보여줍니다.
// K8s 스타일: 동작과 사용 사례를 상세히 설명.
func (im *IterationManager) DemonstrateIteratorPattern() {
	// 초기 데이터 생성.
	// K8s 스타일: 초기 상태를 명확히 로깅.
	numbers := []int{1, 2, 3, 4, 5}
	iterator := NewIntIterator(numbers)
	fmt.Println("=== 사용자 정의 이터레이터 데모 ===")
	fmt.Printf("입력 데이터: %v\n", numbers)

	// 이터레이터 사용: 모든 요소 순회.
	fmt.Println("첫 번째 순회:")
	for iterator.HasNext() {
		if value, ok := iterator.Next(); ok {
			fmt.Printf("  값: %d\n", value)
		}
	}

	// 이터레이터 재설정 후 재사용.
	iterator.Reset()
	fmt.Println("\n이터레이터 재설정 후 두 번째 순회:")
	for iterator.HasNext() {
		if value, ok := iterator.Next(); ok {
			fmt.Printf("  값: %d\n", value)
		}
	}

	// 동시성 테스트: 여러 고루틴에서 이터레이터 사용.
	// K8s 스타일: 동시성 안전성을 위한 뮤텍스 활용.
	var wg sync.WaitGroup
	fmt.Println("\n동시성 테스트 (2개 고루틴):")
	for i := 0; i < 2; i++ {
		wg.Add(1)
		go func(id int) {
			defer wg.Done()
			iterator.Reset()
			for iterator.HasNext() {
				if value, ok := iterator.Next(); ok {
					fmt.Printf("  고루틴 %d: 값 %d\n", id, value)
				}
			}
		}(i + 1)
	}
	wg.Wait()
}

// Iteration demonstrates advanced range usage and iterator pattern in Go.
// K8s 스타일: 메인 함수는 각 데모를 독립적으로 호출하며 실행 흐름을 명확히 보여줌.
func Iteration() {
	// IterationManager 인스턴스 생성.
	manager := NewIterationManager()

	// 데모 1: Range 심화.
	fmt.Println("=== Range 심화 데모 ===")
	manager.DemonstrateRangeAdvanced()

	// 데모 2: 이터레이터 패턴.
	fmt.Println("\n=== 이터레이터 패턴 데모 ===")
	manager.DemonstrateIteratorPattern()
}
