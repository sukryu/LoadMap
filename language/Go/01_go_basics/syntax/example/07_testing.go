package examples

import (
	"errors"
	"fmt"
	"testing"
)

// Calculator represents a simple calculator
type Calculator struct {
	memory float64
}

// Add adds two numbers
func (c *Calculator) Add(a, b float64) float64 {
	result := a + b
	c.memory = result
	return result
}

// Divide divides two numbers
func (c *Calculator) Divide(a, b float64) (float64, error) {
	if b == 0 {
		return 0, errors.New("0으로 나눌 수 없습니다")
	}
	result := a / b
	c.memory = result
	return result, nil
}

// TestCalculator shows testing patterns in Go
func TestCalculator(t *testing.T) {
	// 테스트 셋업
	calc := &Calculator{}

	// 테스트 케이스 정의
	t.Run("덧셈 테스트", func(t *testing.T) {
		result := calc.Add(2, 3)
		expected := 5.0
		if result != expected {
			t.Errorf("Add(2, 3) = %f; expected %f", result, expected)
		}
	})

	t.Run("나눗셈 테스트", func(t *testing.T) {
		result, err := calc.Divide(6, 2)
		if err != nil {
			t.Errorf("예상치 못한 에러: %v", err)
		}
		expected := 3.0
		if result != expected {
			t.Errorf("Divide(6, 2) = %f; expected %f", result, expected)
		}
	})

	t.Run("0으로 나누기 테스트", func(t *testing.T) {
		_, err := calc.Divide(6, 0)
		if err == nil {
			t.Error("0으로 나눌 때 에러가 발생해야 합니다")
		}
	})
}

// ExampleCalculator provides documentation examples
func ExampleCalculator() {
	calc := &Calculator{}

	// 덧셈 예제
	result := calc.Add(2, 3)
	fmt.Printf("2 + 3 = %.1f\n", result)

	// 나눗셈 예제
	result, err := calc.Divide(6, 2)
	if err == nil {
		fmt.Printf("6 / 2 = %.1f\n", result)
	}

	// Output:
	// 2 + 3 = 5.0
	// 6 / 2 = 3.0
}

// BenchmarkCalculator shows benchmarking patterns
func BenchmarkCalculator(b *testing.B) {
	calc := &Calculator{}

	b.Run("덧셈 벤치마크", func(b *testing.B) {
		for i := 0; i < b.N; i++ {
			calc.Add(2, 3)
		}
	})

	b.Run("나눗셈 벤치마크", func(b *testing.B) {
		for i := 0; i < b.N; i++ {
			calc.Divide(6, 2)
		}
	})
}
