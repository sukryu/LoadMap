package examples

import (
	"fmt"

	"golang.org/x/exp/constraints"
)

// Stack is a generic stack implementation
type Stack[T any] struct {
	items []T
}

// Push adds an item to the stack
func (s *Stack[T]) Push(item T) {
	s.items = append(s.items, item)
}

// Pop removes and returns the top item from the stack
func (s *Stack[T]) Pop() (T, error) {
	var zero T
	if len(s.items) == 0 {
		return zero, fmt.Errorf("스택이 비어있습니다")
	}

	item := s.items[len(s.items)-1]
	s.items = s.items[:len(s.items)-1]
	return item, nil
}

// FindMax finds the maximum value in a slice of ordered types
func FindMax[T constraints.Ordered](items []T) (T, error) {
	var zero T
	if len(items) == 0 {
		return zero, fmt.Errorf("빈 슬라이스입니다")
	}

	max := items[0]
	for _, item := range items[1:] {
		if item > max {
			max = item
		}
	}
	return max, nil
}

// GenericExamples demonstrates the use of generics in Go
func GenericExamples() {
	// 정수형 스택 사용
	intStack := &Stack[int]{}
	intStack.Push(1)
	intStack.Push(2)
	intStack.Push(3)

	if val, err := intStack.Pop(); err == nil {
		fmt.Printf("Pop된 정수: %d\n", val)
	}

	// 문자열 스택 사용
	strStack := &Stack[string]{}
	strStack.Push("Hello")
	strStack.Push("World")

	if val, err := strStack.Pop(); err == nil {
		fmt.Printf("Pop된 문자열: %s\n", val)
	}

	// 제네릭 함수 사용
	numbers := []int{3, 1, 4, 1, 5, 9, 2, 6}
	if max, err := FindMax(numbers); err == nil {
		fmt.Printf("최대값: %d\n", max)
	}

	strings := []string{"apple", "banana", "cherry"}
	if max, err := FindMax(strings); err == nil {
		fmt.Printf("사전순 최대값: %s\n", max)
	}
}
