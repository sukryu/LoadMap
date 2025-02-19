/*
이 예제는 unsafe 패키지를 사용하여 포인터 산술을 수행하는 방법을 보여줍니다.
주요 기능:
1. 배열의 첫 번째 요소의 포인터를 unsafe.Pointer로 얻고, 이를 uintptr로 변환하여 메모리 주소 계산에 사용합니다.
2. uintptr 산술을 통해 배열의 각 요소에 해당하는 메모리 주소를 계산하고, 해당 주소를 다시 unsafe.Pointer로 복원합니다.
3. unsafe.Pointer를 원래의 타입 포인터로 변환하여 배열 요소의 값을 동적으로 읽어 출력합니다.

주의:
- unsafe 패키지를 사용한 포인터 산술은 메모리 레이아웃과 자료형의 크기에 의존하므로, 올바른 계산을 위해 unsafe.Sizeof를 정확하게 사용해야 합니다.
- 이 방식은 주로 저수준 최적화나 특정 시스템 프로그래밍에서 사용되며, 일반 애플리케이션에서는 주의해서 사용해야 합니다.
*/

package main

import (
	"fmt"
	"unsafe"
)

func main3() {
	fmt.Println("=== Unsafe Pointer Arithmetic Demo ===")

	// 1. 정수형 배열 생성: 5개의 정수로 구성된 배열을 선언합니다.
	arr := [5]int{10, 20, 30, 40, 50}
	fmt.Printf("배열: %v\n", arr)

	// 2. 배열의 첫 번째 요소의 포인터를 구합니다.
	// &arr[0]는 배열의 첫 번째 요소의 주소를 반환합니다.
	firstElemPtr := unsafe.Pointer(&arr[0])
	fmt.Printf("배열 첫 번째 요소의 주소: %v\n", firstElemPtr)

	// 3. unsafe.Pointer를 uintptr로 변환하여 메모리 주소를 정수로 취급합니다.
	baseAddr := uintptr(firstElemPtr)
	// unsafe.Sizeof(arr[0])를 사용해 배열 요소 하나의 메모리 크기를 구합니다.
	elemSize := unsafe.Sizeof(arr[0])
	fmt.Printf("배열 요소 하나의 크기: %d 바이트\n", elemSize)

	// 4. 포인터 산술을 사용하여 배열의 각 요소에 접근합니다.
	fmt.Println("\n배열 요소에 대한 포인터 산술 결과:")
	for i := 0; i < len(arr); i++ {
		// 각 요소의 주소는 기본 주소(baseAddr)에서 i * elemSize 만큼 오프셋을 더한 값입니다.
		currentAddr := baseAddr + uintptr(i)*elemSize
		// uintptr를 다시 unsafe.Pointer로 변환합니다.
		currentPtr := unsafe.Pointer(currentAddr)
		// currentPtr를 *int 타입 포인터로 변환하여 해당 요소의 값을 읽습니다.
		value := *(*int)(currentPtr)
		fmt.Printf("arr[%d]의 주소: %v, 값: %d\n", i, currentPtr, value)
	}

	fmt.Println("=== Unsafe Pointer Arithmetic Demo 종료 ===")
}
