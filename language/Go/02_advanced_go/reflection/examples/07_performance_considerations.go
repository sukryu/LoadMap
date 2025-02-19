/*
이 예제는 Go의 reflection 기능 사용 시 성능 측면에서 발생하는 오버헤드를 측정하고,
최적화할 수 있는 전략(예: 캐싱)을 적용하는 방법을 보여줍니다.

주요 기능:
1. 직접 호출과 reflection을 통한 동적 메서드 호출의 성능 비교
2. 캐싱을 통해 반응형(반복적인) reflection 호출의 오버헤드를 줄이는 방법
3. 반복 실행을 통한 벤치마크 결과를 출력하여, reflection 사용의 비용과 최적화 효과를 이해

이 예제는 고급 애플리케이션에서 reflection을 사용할 때 성능 최적화의 필요성을 인지하고,
적절한 전략을 적용하는 데 도움을 줍니다.
*/

package main

import (
	"fmt"
	"reflect"
	"time"
)

// Calculator 구조체는 두 정수의 연산을 수행하는 예제로 사용됩니다.
type Calculator1 struct{}

// Add 메서드는 두 정수를 더한 결과를 반환합니다.
func (c Calculator1) Add(a, b int) int {
	return a + b
}

// Multiply 메서드는 두 정수를 곱한 결과를 반환합니다.
func (c Calculator1) Multiply(a, b int) int {
	return a * b
}

// benchmarkDirectCall은 직접 메서드 호출을 반복하여 수행 시간을 측정합니다.
func benchmarkDirectCall(iterations int) time.Duration {
	calc := Calculator1{}
	start := time.Now()
	var sum int
	// 반복문 내에서 직접 호출
	for i := 0; i < iterations; i++ {
		sum += calc.Add(i, i)
	}
	duration := time.Since(start)
	// sum 값을 출력하여 컴파일러 최적화로 인한 호출 제거를 방지합니다.
	fmt.Printf("Direct call result: %d\n", sum)
	return duration
}

// benchmarkReflectionCall은 reflection을 사용하여 메서드를 동적으로 호출하고, 수행 시간을 측정합니다.
func benchmarkReflectionCall(iterations int) time.Duration {
	calc := Calculator1{}
	calcValue := reflect.ValueOf(calc)
	// MethodByName을 통해 매 반복마다 메서드 심볼을 검색하는 경우 (캐싱 없이)
	start := time.Now()
	var sum int
	for i := 0; i < iterations; i++ {
		// 매번 동적으로 메서드를 조회
		method := calcValue.MethodByName("Add")
		if !method.IsValid() {
			panic("Method Add not found")
		}
		// 인수를 reflect.Value 슬라이스로 준비
		args := []reflect.Value{reflect.ValueOf(i), reflect.ValueOf(i)}
		results := method.Call(args)
		sum += int(results[0].Int())
	}
	duration := time.Since(start)
	fmt.Printf("Reflection call (no cache) result: %d\n", sum)
	return duration
}

// benchmarkReflectionCallWithCache는 첫 번째에 메서드를 캐싱한 후, 캐시된 메서드로 반복 호출하여 수행 시간을 측정합니다.
func benchmarkReflectionCallWithCache(iterations int) time.Duration {
	calc := Calculator1{}
	calcValue := reflect.ValueOf(calc)
	// 캐싱: 한 번만 메서드 심볼을 조회합니다.
	cachedMethod := calcValue.MethodByName("Add")
	if !cachedMethod.IsValid() {
		panic("Method Add not found")
	}
	start := time.Now()
	var sum int
	for i := 0; i < iterations; i++ {
		args := []reflect.Value{reflect.ValueOf(i), reflect.ValueOf(i)}
		results := cachedMethod.Call(args)
		sum += int(results[0].Int())
	}
	duration := time.Since(start)
	fmt.Printf("Reflection call (with cache) result: %d\n", sum)
	return duration
}

func main() {
	iterations := 1000000 // 반복 횟수 설정
	fmt.Println("=== Reflection Performance Considerations Demo ===")

	// 1. 직접 호출 벤치마크
	directDuration := benchmarkDirectCall(iterations)
	fmt.Printf("Direct call took: %v for %d iterations\n", directDuration, iterations)
	fmt.Println()

	// 2. reflection 호출 (캐시 없이) 벤치마크
	reflectDuration := benchmarkReflectionCall(iterations)
	fmt.Printf("Reflection call (no cache) took: %v for %d iterations\n", reflectDuration, iterations)
	fmt.Println()

	// 3. reflection 호출 (캐시 사용) 벤치마크
	reflectCacheDuration := benchmarkReflectionCallWithCache(iterations)
	fmt.Printf("Reflection call (with cache) took: %v for %d iterations\n", reflectCacheDuration, iterations)
	fmt.Println()

	fmt.Println("=== Performance Demo Complete ===")
}
