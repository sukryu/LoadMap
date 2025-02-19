/*
이 예제는 Go의 unsafe 패키지를 사용할 때 주의해야 할 사항과
안전하게 사용하는 방법에 대해 설명합니다.

주요 기능:
1. 불변 문자열의 메모리 수정 위험성:
   - 문자열은 불변(immutable)하므로, unsafe를 사용해 내부 메모리에 접근하여 수정하면
     예기치 않은 동작이나 런타임 오류가 발생할 수 있습니다.
2. 포인터 산술 사용 시 주의사항:
   - 자료형의 크기를 정확히 고려하지 않고 포인터 산술을 수행하면, 잘못된 메모리 접근이 발생할 수 있습니다.
3. Best Practices:
   - unsafe 사용을 최소화하고, 해당 코드는 충분히 주석과 문서화하여 위험성을 명시할 것.
   - 변경하면 안되는 데이터는 절대 수정하지 않으며, 포인터 산술 시에는 항상 자료형 크기를 확인할 것.
   - 충분한 테스트와 코드 리뷰를 통해 안전성을 검증할 것.
*/

package main

import (
	"fmt"
	"reflect"
	"unsafe"
)

func main7() {
	fmt.Println("=== Unsafe Dangers and Best Practices Demo ===")

	// --------------------------------------------------
	// 1. 불변 문자열 수정의 위험성
	// --------------------------------------------------
	fmt.Println("\n-- 예제 1: 불변 문자열 수정의 위험성 --")
	originalStr := "Immutable String"
	fmt.Println("원본 문자열:", originalStr)

	// 문자열을 unsafe를 사용해 []byte로 변환 (메모리 복사 없이)
	stringHeader := (*reflect.StringHeader)(unsafe.Pointer(&originalStr))
	var byteSlice []byte
	sliceHeader := (*reflect.SliceHeader)(unsafe.Pointer(&byteSlice))
	sliceHeader.Data = stringHeader.Data
	sliceHeader.Len = stringHeader.Len
	sliceHeader.Cap = stringHeader.Len

	fmt.Println("unsafe를 사용하여 변환한 []byte:", byteSlice)

	// 주의: 아래와 같이 []byte를 수정하면, 원본 문자열의 불변성이 깨집니다.
	// 예를 들어, 첫 바이트를 변경하면 예기치 않은 동작이나 버그가 발생할 수 있습니다.
	// 아래 코드는 위험하므로 실제 사용 시 절대 수정해서는 안 됩니다.
	// byteSlice[0] = 'X'
	// fmt.Println("수정 후 []byte:", byteSlice)
	fmt.Println("※ 주의: unsafe를 사용한 []byte 변환 후에는 원본 문자열을 수정하지 마세요.")

	// --------------------------------------------------
	// 2. 포인터 산술 사용 시 주의사항
	// --------------------------------------------------
	fmt.Println("\n-- 예제 2: 포인터 산술 사용 시 주의사항 --")
	var num int = 100
	fmt.Printf("num의 값: %d, 주소: %p\n", num, &num)

	// num의 주소를 unsafe.Pointer와 uintptr로 변환
	numPtr := unsafe.Pointer(&num)
	numAddr := uintptr(numPtr)
	fmt.Printf("uintptr로 변환한 주소: 0x%x\n", numAddr)

	// 올바른 포인터 산술: num의 크기만큼 주소를 증가시켜, 연속된 메모리 영역의 계산을 수행합니다.
	sizeOfNum := unsafe.Sizeof(num)
	fmt.Printf("int 자료형의 크기: %d 바이트\n", sizeOfNum)
	correctAddr := numAddr + sizeOfNum
	fmt.Printf("올바른 산술: 다음 int 변수의 주소(예상): 0x%x\n", correctAddr)

	// 잘못된 산술: 자료형 크기의 절반만큼만 증가시킨 경우 (잘못된 결과)
	incorrectAddr := numAddr + sizeOfNum/2
	fmt.Printf("잘못된 산술: 잘못된 주소: 0x%x (예상치 못한 결과)\n", incorrectAddr)

	// --------------------------------------------------
	// 3. Best Practices 안내
	// --------------------------------------------------
	fmt.Println("\n-- Best Practices for Using unsafe --")
	fmt.Println("1. unsafe는 꼭 필요한 경우에만 사용하고, 사용 범위를 최소화하세요.")
	fmt.Println("2. unsafe를 사용하는 코드는 충분한 주석과 문서화를 통해 왜 사용했는지 명시해야 합니다.")
	fmt.Println("3. 불변 데이터(예: 문자열)는 unsafe 변환 후 수정하지 마세요.")
	fmt.Println("4. 포인터 산술 시에는 항상 자료형의 크기를 확인하여 올바른 오프셋을 계산하세요.")
	fmt.Println("5. 충분한 테스트와 코드 리뷰를 통해 unsafe 코드의 안정성을 검증하세요.")

	fmt.Println("\n=== Unsafe Dangers and Best Practices Demo 종료 ===")
}
