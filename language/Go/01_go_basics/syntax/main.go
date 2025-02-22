package main

import (
	"fmt"
	"sync"
	"time"
)

// =============================================================
// Chapter 1: 기본 데이터 타입과 변수
// =============================================================

// basicTypesExtended는 정수, 부동소수점, 문자열, 불리언 외에 포인터 사용법을 보충합니다.
func basicTypesExtended() {
	// 정수형 변수 선언
	var a int = 42
	var b int = 100

	// 부동소수점 변수 선언
	var pi float64 = 3.14159

	// 문자열 변수 선언
	var greeting string = "Hello, Go!"

	// 불리언 변수 선언
	var isActive bool = true

	// 포인터 변수 선언 및 사용 예제
	var ptr *int = &a // a의 주소를 포인터에 저장
	*ptr = *ptr + b   // 포인터를 통해 a의 값을 변경 (42 + 100 = 142)

	fmt.Printf("정수 a: %d, b: %d\n", a, b)
	fmt.Printf("부동소수점 pi: %.5f\n", pi)
	fmt.Printf("문자열: %s\n", greeting)
	fmt.Printf("불리언: %v\n", isActive)
	fmt.Printf("포인터를 통한 a의 값: %d\n", *ptr)
}

// =============================================================
// Chapter 2: 복합 데이터 타입
// =============================================================

// 구조체 정의 및 인터페이스 활용 예제
type Animal interface {
	Speak() string
}

type Dog struct {
	Name string
	Age  int
}

func (d Dog) Speak() string {
	return fmt.Sprintf("%s: Woof!", d.Name)
}

func complexTypesExtended() {
	// 배열: 고정 크기의 데이터 집합
	var arr [3]int = [3]int{10, 20, 30}

	// 슬라이스: 동적 배열
	fruits := []string{"apple", "banana", "cherry"}
	fruits = append(fruits, "date")

	// 맵: 키-값 쌍 저장
	countryCodes := map[string]string{
		"US": "United States",
		"KR": "South Korea",
	}
	// 맵에 값 추가
	countryCodes["JP"] = "Japan"

	// 구조체: 복합 데이터 타입
	person := struct {
		FirstName string
		LastName  string
		Age       int
	}{
		FirstName: "Jane",
		LastName:  "Doe",
		Age:       30,
	}

	// 인터페이스 활용: Animal 인터페이스를 구현하는 Dog 구조체
	myDog := Dog{Name: "Buddy", Age: 5}

	fmt.Printf("배열: %v\n", arr)
	fmt.Printf("슬라이스: %v\n", fruits)
	fmt.Printf("맵: %v\n", countryCodes)
	fmt.Printf("구조체: %+v\n", person)
	fmt.Printf("인터페이스 활용 (Dog): %s\n", myDog.Speak())
}

// =============================================================
// Chapter 3: 함수와 메서드, 조건문, 반복문
// =============================================================

// addNumbers는 두 정수를 더하여 결과를 반환하는 기본 함수입니다.
func addNumbers(x, y int) int {
	return x + y
}

// compareNumbers는 조건문을 활용하여 두 정수 중 큰 값을 반환합니다.
func compareNumbers(x, y int) int {
	if x > y {
		return x
	} else if x < y {
		return y
	} else {
		return x // x와 y가 동일한 경우
	}
}

// printNumbers는 for 반복문을 사용하여 1부터 n까지의 숫자를 출력합니다.
func printNumbers(n int) {
	for i := 1; i <= n; i++ {
		fmt.Printf("%d ", i)
	}
	fmt.Println()
}

// multiReturnExample는 두 정수의 나눗셈 결과와 에러를 반환하는 함수입니다.
func multiReturnExample(dividend, divisor float64) (float64, error) {
	if divisor == 0 {
		return 0, fmt.Errorf("0으로 나눌 수 없습니다")
	}
	return dividend / divisor, nil
}

// functionsAndControlStructures demonstrates 함수 호출, 조건문, 반복문, 다중 반환 함수 사용법.
func functionsAndControlStructures() {
	sum := addNumbers(15, 27)
	maxNum := compareNumbers(100, 80)
	fmt.Printf("덧셈 결과: %d\n", sum)
	fmt.Printf("두 수 중 큰 값: %d\n", maxNum)

	fmt.Print("1부터 10까지 숫자 출력: ")
	printNumbers(10)

	// 다중 반환 함수 사용 및 에러 처리 예제
	quotient, err := multiReturnExample(100, 20)
	if err != nil {
		fmt.Printf("나눗셈 에러: %v\n", err)
	} else {
		fmt.Printf("나눗셈 결과: %.2f\n", quotient)
	}
}

// =============================================================
// Chapter 4: 고루틴과 채널
// =============================================================

func concurrencyBasicsExtended() {
	// 문자열 데이터를 전달할 채널 생성
	messageChannel := make(chan string)
	// 작업 완료 신호를 전달할 채널 생성
	doneChannel := make(chan bool)

	// 고루틴: 메시지를 채널에 전송
	go func() {
		for i := 0; i < 5; i++ {
			messageChannel <- fmt.Sprintf("고루틴 메시지 %d", i)
			time.Sleep(300 * time.Millisecond)
		}
		close(messageChannel)
	}()

	// 고루틴: 채널에서 메시지를 수신하여 출력
	go func() {
		for msg := range messageChannel {
			fmt.Println("수신:", msg)
		}
		doneChannel <- true
	}()

	<-doneChannel // 모든 메시지 수신 후 완료 대기
}

// =============================================================
// Chapter 5: 동기화와 뮤텍스
// =============================================================

func synchronizationExtended() {
	var sharedCounter int
	var wg sync.WaitGroup
	var mutex sync.Mutex

	// 1000개의 고루틴이 공유 변수에 접근하여 값을 증가시킴
	for i := 0; i < 1000; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			// 임계 구역 보호: 뮤텍스를 사용하여 동시 접근 제어
			mutex.Lock()
			sharedCounter++
			mutex.Unlock()
		}()
	}
	wg.Wait()
	fmt.Printf("동기화 후 최종 카운터 값: %d\n", sharedCounter)
}

// =============================================================
// Chapter 6: 에러 처리와 패닉 복구
// =============================================================

func errorHandlingExtended() {
	// defer와 recover를 사용한 패닉 복구 예제
	defer func() {
		if rec := recover(); rec != nil {
			fmt.Printf("패닉 복구: %v\n", rec)
		}
	}()

	// 다중 반환 함수를 사용하여 에러 발생을 시뮬레이션
	result, err := multiReturnExample(10, 0)
	if err != nil {
		fmt.Printf("에러 발생: %v\n", err)
		// 고의로 패닉 발생 (실제 상황에서는 패닉을 피해야 함)
		panic("예외 상황 발생!")
	}
	fmt.Printf("나눗셈 결과: %.2f\n", result)
}

func main() {
	fmt.Println("=== Chapter 1: 기본 데이터 타입과 변수 (Extended) ===")
	basicTypesExtended()

	fmt.Println("\n=== Chapter 2: 복합 데이터 타입 및 인터페이스 (Extended) ===")
	complexTypesExtended()

	fmt.Println("\n=== Chapter 3: 함수, 조건문, 반복문, 다중 반환 ===")
	functionsAndControlStructures()

	fmt.Println("\n=== Chapter 4: 고루틴과 채널 (Extended) ===")
	concurrencyBasicsExtended()

	fmt.Println("\n=== Chapter 5: 동기화와 뮤텍스 (Extended) ===")
	synchronizationExtended()

	fmt.Println("\n=== Chapter 6: 에러 처리와 패닉 복구 (Extended) ===")
	errorHandlingExtended()
}
