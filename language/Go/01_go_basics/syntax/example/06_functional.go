package examples

import (
	"fmt"
	"strings"
)

// MapFunc applies a function to each element in a slice
func MapFunc[T, U any](slice []T, fn func(T) U) []U {
	result := make([]U, len(slice))
	for i, v := range slice {
		result[i] = fn(v)
	}
	return result
}

// FilterFunc filters elements based on a predicate
func FilterFunc[T any](slice []T, predicate func(T) bool) []T {
	var result []T
	for _, v := range slice {
		if predicate(v) {
			result = append(result, v)
		}
	}
	return result
}

// ReduceFunc reduces a slice to a single value
func ReduceFunc[T, U any](slice []T, initial U, fn func(U, T) U) U {
	result := initial
	for _, v := range slice {
		result = fn(result, v)
	}
	return result
}

// Compose combines two functions
func Compose[T, U, V any](f func(U) V, g func(T) U) func(T) V {
	return func(x T) V {
		return f(g(x))
	}
}

// FunctionalExamples demonstrates functional programming patterns in Go
func FunctionalExamples() {
	// Map 예제
	numbers := []int{1, 2, 3, 4, 5}
	doubled := MapFunc(numbers, func(x int) int {
		return x * 2
	})
	fmt.Printf("원본 숫자: %v\n", numbers)
	fmt.Printf("두 배된 숫자: %v\n", doubled)

	// Filter 예제
	evenNumbers := FilterFunc(numbers, func(x int) bool {
		return x%2 == 0
	})
	fmt.Printf("짝수만 필터링: %v\n", evenNumbers)

	// Reduce 예제
	sum := ReduceFunc(numbers, 0, func(acc, curr int) int {
		return acc + curr
	})
	fmt.Printf("합계: %d\n", sum)

	// 함수 합성 예제
	words := []string{"hello", "world", "functional", "programming"}

	toUpper := func(s string) string { return strings.ToUpper(s) }
	addExclamation := func(s string) string { return s + "!" }

	emphasize := Compose(addExclamation, toUpper)

	emphasized := MapFunc(words, emphasize)
	fmt.Printf("강조된 단어들: %v\n", emphasized)

	// 체이닝 예제
	result := FilterFunc(
		MapFunc(numbers, func(x int) int { return x * x }),
		func(x int) bool { return x > 10 },
	)
	fmt.Printf("제곱 후 10보다 큰 수: %v\n", result)
}
