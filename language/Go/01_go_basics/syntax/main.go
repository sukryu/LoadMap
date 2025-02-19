package main

import (
	"fmt"
	"sync"
	"time"
)

// =============================================================
// Chapter 1: 기본 데이터 타입과 변수
// =============================================================

func basicTypes() {
	// 정수형
	var integerNum int = 42
	var uint8Num uint8 = 255

	// 부동소수점
	var floatNum float64 = 3.14

	// 문자열
	var str string = "Hello, Go!"

	// 불리언
	var boolVar bool = true

	// 짧은 선언 방식
	shortDeclare := "short declaration"

	fmt.Printf("int: %d\n uint8 %d\n동소수점: %f\n문자열: %s\n불리언: %v\n짧은 선언: %s\n",
		integerNum, uint8Num, floatNum, str, boolVar, shortDeclare)
}

// =============================================================
// Chapter 2: 복합 데이터 타입
// =============================================================

// 구조체 정의
type Person struct {
	Name string
	Age  int
}

func complexTypes() {
	// 배열
	var numbers [5]int = [5]int{1, 2, 3, 4, 5}

	// 슬라이스
	slice := []string{"apple", "banana", "orange"}
	slice = append(slice, "grape")

	// 맵
	ages := map[string]int{
		"Alice": 25,
		"Bob":   30,
	}

	// 구조체
	person := Person{
		Name: "John",
		Age:  28,
	}

	fmt.Printf("배열: %v\n슬라이스: %v\n맵: %v\n구조체: %+v\n",
		numbers, slice, ages, person)
}

// =============================================================
// Chapter 3: 함수와 메서드
// =============================================================

// 기본 함수
func add(a, b int) int {
	return a + b
}

// 다중 반환 함수
func divide(a, b float64) (float64, error) {
	if b == 0 {
		return 0, fmt.Errorf("0으로 나눌 수 없습니다")
	}
	return a / b, nil
}

// 메서드
func (p Person) describe() string {
	return fmt.Sprintf("%s는 %d살입니다", p.Name, p.Age)
}

func functionsAndMethods() {
	// 함수 호출
	sum := add(5, 3)

	// 에러 처리
	result, err := divide(10, 2)
	if err != nil {
		fmt.Println("에러:", err)
	}

	// 메서드 호출
	person := Person{"Alice", 25}
	description := person.describe()

	fmt.Printf("덧셈 결과: %d\n나눗셈 결과: %.2f\n설명: %s\n",
		sum, result, description)
}

// =============================================================
// Chapter 4: 고루틴과 채널
// =============================================================

func concurrencyBasics() {
	// 채널 생성
	ch := make(chan string)
	done := make(chan bool)

	// 고루틴 실행
	go func() {
		for i := 0; i < 3; i++ {
			ch <- fmt.Sprintf("메시지 %d", i)
			time.Sleep(time.Millisecond * 500)
		}
		close(ch)
	}()

	// 채널 수신
	go func() {
		for msg := range ch {
			fmt.Println("수신:", msg)
		}
		done <- true
	}()

	<-done // 완료 대기
}

// =============================================================
// Chapter 5: 동기화와 뮤텍스
// =============================================================

func synchronization() {
	var counter int
	var wg sync.WaitGroup
	var mu sync.Mutex

	// 여러 고루틴에서 공유 자원에 접근
	for i := 0; i < 1000; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			mu.Lock()
			counter++
			mu.Unlock()
		}()
	}

	wg.Wait()
	fmt.Printf("최종 카운터 값: %d\n", counter)
}

// =============================================================
// Chapter 6: 에러 처리와 패닉 복구
// =============================================================

func errorHandling() {
	// defer와 recover를 사용한 패닉 처리
	defer func() {
		if r := recover(); r != nil {
			fmt.Printf("패닉 복구: %v\n", r)
		}
	}()

	// 에러 반환 함수 사용
	result, err := divide(10, 0)
	if err != nil {
		fmt.Printf("에러 발생: %v\n", err)
		return
	}

	fmt.Printf("결과: %.2f\n", result)
}

func main() {
	fmt.Println("=== Chapter 1: 기본 데이터 타입과 변수 ===")
	basicTypes()

	fmt.Println("\n=== Chapter 2: 복합 데이터 타입 ===")
	complexTypes()

	fmt.Println("\n=== Chapter 3: 함수와 메서드 ===")
	functionsAndMethods()

	fmt.Println("\n=== Chapter 4: 고루틴과 채널 ===")
	concurrencyBasics()

	fmt.Println("\n=== Chapter 5: 동기화와 뮤텍스 ===")
	synchronization()

	fmt.Println("\n=== Chapter 6: 에러 처리와 패닉 복구 ===")
	errorHandling()
}
