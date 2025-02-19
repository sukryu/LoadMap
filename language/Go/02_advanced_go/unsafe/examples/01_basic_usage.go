/*
이 예제는 Go의 unsafe 패키지를 활용하여 기본적인 저수준 메모리 접근 및 포인터 조작 방법을 시연합니다.
주요 기능:
1. 변수의 메모리 주소를 unsafe.Pointer 및 uintptr로 변환하여 확인하는 방법.
2. uintptr로 변환된 값을 다시 unsafe.Pointer로 복원하여 원래의 값을 읽어들이는 방법.
3. 간단한 포인터 산술을 통해 메모리 주소의 연산을 시연합니다.

주의:
- unsafe 패키지는 Go의 타입 안전성을 우회하므로, 실제 프로덕션 코드에서는 반드시 신중하게 사용해야 합니다.
*/

package main

import (
	"fmt"
	"unsafe"
)

func main1() {
	fmt.Println("=== Unsafe Basic Usage Demo ===")

	// 1. 변수의 메모리 주소 확인
	var a int = 100
	fmt.Printf("a의 값: %d\n", a)
	fmt.Printf("a의 주소: %p\n", &a)

	// 2. unsafe.Pointer를 사용하여 a의 주소를 일반 포인터로 변환합니다.
	ptr := unsafe.Pointer(&a)
	fmt.Printf("unsafe.Pointer를 통한 a의 주소: %v\n", ptr)

	// 3. unsafe.Pointer를 uintptr로 변환하여, 주소를 정수형으로 확인합니다.
	addr := uintptr(ptr)
	fmt.Printf("uintptr로 변환한 a의 주소: 0x%x\n", addr)

	// 4. uintptr를 사용한 포인터 산술 예제
	// a의 크기를 구하여, a 다음에 할당된 메모리 주소를 계산합니다.
	// (주의: 이 예제는 산술 연산을 시연하기 위한 용도이며, 실제로 이 주소에 유효한 데이터가 존재하지 않을 수 있습니다.)
	nextAddr := addr + unsafe.Sizeof(a)
	fmt.Printf("a 다음 메모리 주소 (unsafe.Sizeof(a)만큼 증가): 0x%x\n", nextAddr)

	// 5. uintptr 값을 다시 unsafe.Pointer로 변환
	nextPtr := unsafe.Pointer(nextAddr)
	fmt.Printf("uintptr에서 복원한 unsafe.Pointer: %v\n", nextPtr)

	// 6. 원래 변수 a의 값을 복원하는 안전한 예제
	// a의 주소를 uintptr로 변환한 후, 이를 다시 unsafe.Pointer로 복원하여 원래 변수에 접근합니다.
	restoredPtr := (*int)(unsafe.Pointer(addr))
	fmt.Printf("복원한 포인터를 통해 읽은 a의 값: %d\n", *restoredPtr)

	fmt.Println("=== Unsafe Basic Usage Demo 종료 ===")
}
