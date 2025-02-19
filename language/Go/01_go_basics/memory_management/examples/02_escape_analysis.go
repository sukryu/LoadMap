/*
이 예제는 Go 컴파일러의 escape 분석 메커니즘을 상세히 설명합니다.
Escape 분석은 변수가 스택과 힙 중 어디에 할당될지 결정하는 컴파일러의 프로세스입니다.

실행 방법:
1. 일반 실행: go run escape_analysis.go
2. Escape 분석 로그 확인: go run -gcflags="-m" escape_analysis.go

주요 개념:
- 스택 할당: 함수 스코프 내에서만 사용되는 변수
- 힙 할당: 함수 스코프를 벗어나는 변수 (escape)
- 컴파일러 최적화: 가능한 한 스택 할당을 선호
*/

package examples

import (
	"fmt"
	"sync"
)

// =============================================================
// Chapter 1: 기본적인 Escape 사례
// 변수가 언제 힙으로 escape하는지 보여주는 기본 예제들입니다.
// =============================================================

// User는 escape 분석을 설명하기 위한 예시 구조체입니다.
type User struct {
	ID   int
	Name string
	Data []byte
}

// createUserOnStack은 User 객체를 스택에 할당합니다.
// 반환값이 값 타입이므로 복사본이 반환됩니다.
func createUserOnStack() User {
	// 이 User 구조체는 스택에 할당됩니다.
	user := User{
		ID:   1,
		Name: "Stack User",
		Data: make([]byte, 1024), // 슬라이스의 백업 배열은 힙에 할당
	}
	return user // 값 복사 발생
}

// createUserOnHeap은 User 객체를 힙에 할당합니다.
// 포인터를 반환하므로 객체가 힙으로 escape합니다.
func createUserOnHeap() *User {
	// 이 User 구조체는 힙에 할당됩니다 (escapes to heap).
	user := &User{
		ID:   2,
		Name: "Heap User",
		Data: make([]byte, 1024),
	}
	return user // 포인터 반환
}

// =============================================================
// Chapter 2: 인터페이스로 인한 Escape
// 인터페이스 사용 시 발생하는 escape 현상을 설명합니다.
// =============================================================

// Printer는 출력 기능을 정의하는 인터페이스입니다.
type Printer interface {
	Print()
}

// Document는 Printer 인터페이스를 구현하는 구조체입니다.
type Document struct {
	Content string
}

// Print는 Document의 내용을 출력합니다.
func (d Document) Print() {
	fmt.Println(d.Content)
}

// printDocument는 인터페이스를 매개변수로 받습니다.
// 인터페이스 사용으로 인해 매개변수가 힙으로 escape할 수 있습니다.
func printDocument(p Printer) {
	p.Print()
}

// =============================================================
// Chapter 3: 클로저와 고루틴으로 인한 Escape
// 클로저와 고루틴 사용 시 발생하는 escape 현상을 설명합니다.
// =============================================================

// processWithGoroutine은 고루틴에서 변수를 사용하여
// escape가 발생하는 상황을 보여줍니다.
func processWithGoroutine(data []int) {
	// 이 변수는 고루틴에서 사용되므로 힙으로 escape합니다.
	result := make([]int, len(data))

	var wg sync.WaitGroup
	wg.Add(1)

	go func() {
		defer wg.Done()
		// 고루틴에서 외부 변수 사용
		for i, v := range data {
			result[i] = v * 2
		}
	}()

	wg.Wait()
}

// =============================================================
// Chapter 4: 순환 참조와 크기가 큰 객체의 Escape
// 메모리 할당 크기와 참조 관계가 escape에 미치는 영향을 설명합니다.
// =============================================================

// LargeObject는 크기가 큰 객체를 시뮬레이션합니다.
type LargeObjects struct {
	Data [1024 * 1024]byte // 1MB
}

// createLargeObject는 큰 객체를 생성합니다.
// 크기가 큰 객체는 일반적으로 힙에 할당됩니다.
func createLargeObject() LargeObjects {
	return LargeObjects{} // 크기가 커도 값 반환이므로 가능하면 스택 사용
}

// createLargeObjectPtr은 큰 객체의 포인터를 반환합니다.
func createLargeObjectPtr() *LargeObjects {
	return &LargeObjects{} // 항상 힙에 할당
}

// Node는 순환 참조를 가능하게 하는 구조체입니다.
type Node struct {
	Next  *Node
	Value int
}

// createLinkedList는 연결 리스트를 생성합니다.
// 순환 참조 가능성으로 인해 노드들이 힙으로 escape합니다.
func createLinkedList(size int) *Node {
	if size == 0 {
		return nil
	}

	head := &Node{Value: 1}
	current := head

	for i := 2; i <= size; i++ {
		current.Next = &Node{Value: i}
		current = current.Next
	}

	return head
}

// =============================================================
// Chapter 5: Escape 분석 결과 확인
// 컴파일러의 escape 분석 결과를 확인하는 방법을 설명합니다.
// =============================================================

// RunEscapeAnalysisDemo는 다양한 escape 시나리오를 실행합니다.
func RunEscapeAnalysisDemo() {
	// 1. 기본 escape 사례
	stackUser := createUserOnStack()
	heapUser := createUserOnHeap()

	fmt.Printf("Stack User: %v\n", stackUser)
	fmt.Printf("Heap User: %v\n", heapUser)

	// 2. 인터페이스로 인한 escape
	doc := Document{Content: "Hello, Escape Analysis!"}
	printDocument(doc)

	// 3. 고루틴으로 인한 escape
	data := []int{1, 2, 3, 4, 5}
	processWithGoroutine(data)

	// 4. 큰 객체와 순환 참조
	largeObj := createLargeObject()
	largeObjPtr := createLargeObjectPtr()
	list := createLinkedList(5)

	// 메모리 사용 확인을 위한 임시 참조
	_ = largeObj
	_ = largeObjPtr
	_ = list
}

/*
Escape 분석 결과 확인 방법:

1. 기본 분석:
   go run -gcflags="-m" escape_analysis.go

2. 상세 분석:
   go run -gcflags="-m -m" escape_analysis.go

3. 컴파일된 최적화 확인:
   go build -gcflags="-m" escape_analysis.go

주요 분석 포인트:
1. "escapes to heap" 메시지 확인
2. 인터페이스 변환으로 인한 escape
3. 클로저와 고루틴에 의한 escape
4. 순환 참조와 큰 객체의 할당 위치

최적화 팁:
1. 가능한 값 타입 반환 사용
2. 불필요한 포인터 사용 피하기
3. 인터페이스 사용 시 escape 고려
4. 고루틴에서 사용하는 변수의 스코프 제한
*/
