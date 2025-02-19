/*
이 예제는 unsafe 패키지를 사용하여 기본 자료형 및 구조체의 메모리 배치를 확인하는 방법을 보여줍니다.
주요 기능:
1. 기본 자료형의 메모리 크기 확인: unsafe.Sizeof를 사용해 int, float64, bool, string 등의 크기를 출력합니다.
2. 구조체의 메모리 배치 확인: unsafe.Sizeof와 unsafe.Offsetof를 사용하여 구조체 전체의 크기와 각 필드의 메모리 오프셋을 확인합니다.
3. 메모리 정렬 및 패딩 현상 이해: 필드 순서에 따른 패딩 차이를 비교하여 최적화 기법을 모색할 수 있습니다.

주의:
- unsafe.Sizeof는 컴파일러가 실제 할당하는 크기를 반영하므로, 구조체 내부의 필드 배치 및 패딩에 따라 예상과 다른 결과가 나타날 수 있습니다.
*/

package main

import (
	"fmt"
	"unsafe"
)

// PoorlyAligned 구조체는 필드 순서가 최적화되지 않아 불필요한 패딩이 발생할 수 있는 예제입니다.
type PoorlyAligned struct {
	a bool  // 1 byte: 불리언 값, 이후 7바이트 패딩이 추가될 가능성이 있음
	b int64 // 8 bytes: 정수형 (64비트)
	c int32 // 4 bytes: 정수형 (32비트)
}

// WellAligned 구조체는 큰 타입부터 작은 타입 순으로 배치하여 패딩을 최소화한 예제입니다.
type WellAligned struct {
	b int64 // 8 bytes: 가장 큰 타입을 우선 배치
	c int32 // 4 bytes
	a bool  // 1 byte
	// 예상: a 다음에 3바이트 패딩이 추가되어 전체 크기는 16바이트로 정렬됨
}

func main2() {
	fmt.Println("=== Unsafe Memory Layout Demo ===")

	// -----------------------------------
	// 1. 기본 자료형 메모리 크기 확인
	// -----------------------------------
	fmt.Println("== 기본 자료형 크기 ==")
	var i int = 42
	var f float64 = 3.14
	var b bool = true
	var s string = "Hello"

	fmt.Printf("int의 크기: %d 바이트\n", unsafe.Sizeof(i))
	fmt.Printf("float64의 크기: %d 바이트\n", unsafe.Sizeof(f))
	fmt.Printf("bool의 크기: %d 바이트\n", unsafe.Sizeof(b))
	// 문자열은 내부적으로 포인터와 길이를 가지므로, 일반적으로 16 또는 24바이트로 할당됨 (플랫폼에 따라 다름)
	fmt.Printf("string의 크기: %d 바이트\n", unsafe.Sizeof(s))

	// -----------------------------------
	// 2. PoorlyAligned 구조체의 메모리 배치 확인
	// -----------------------------------
	fmt.Println("\n== PoorlyAligned 구조체 메모리 레이아웃 ==")
	pa := PoorlyAligned{a: true, b: 100, c: 200}
	// 전체 구조체 크기 출력
	fmt.Printf("PoorlyAligned 전체 크기: %d 바이트\n", unsafe.Sizeof(pa))
	// 각 필드의 메모리 오프셋 확인
	fmt.Printf("필드 a의 오프셋: %d 바이트\n", unsafe.Offsetof(pa.a))
	fmt.Printf("필드 b의 오프셋: %d 바이트\n", unsafe.Offsetof(pa.b))
	fmt.Printf("필드 c의 오프셋: %d 바이트\n", unsafe.Offsetof(pa.c))

	// -----------------------------------
	// 3. WellAligned 구조체의 메모리 배치 확인
	// -----------------------------------
	fmt.Println("\n== WellAligned 구조체 메모리 레이아웃 ==")
	wa := WellAligned{b: 100, c: 200, a: true}
	fmt.Printf("WellAligned 전체 크기: %d 바이트\n", unsafe.Sizeof(wa))
	fmt.Printf("필드 b의 오프셋: %d 바이트\n", unsafe.Offsetof(wa.b))
	fmt.Printf("필드 c의 오프셋: %d 바이트\n", unsafe.Offsetof(wa.c))
	fmt.Printf("필드 a의 오프셋: %d 바이트\n", unsafe.Offsetof(wa.a))

	// -----------------------------------
	// 4. 구조체 배치 비교 및 최적화 설명
	// -----------------------------------
	fmt.Println("\n== 구조체 배치 비교 ==")
	fmt.Println("PoorlyAligned 구조체는 필드 순서가 최적화되지 않아 불필요한 패딩이 발생할 수 있습니다.")
	fmt.Println("WellAligned 구조체는 큰 필드부터 작은 필드 순으로 배치하여 패딩을 최소화합니다.")

	fmt.Println("\n=== Unsafe Memory Layout Demo 종료 ===")
}
