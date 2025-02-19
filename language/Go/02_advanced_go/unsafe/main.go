/*
이 예제는 Go의 unsafe 패키지를 활용하여, 저수준 메모리 접근 및 포인터 조작 기법을 보여줍니다.
주요 기능:
1. 변수의 메모리 주소 확인 및 uintptr 변환:
   - unsafe.Pointer와 uintptr를 사용하여 변수의 메모리 주소를 확인하고, 이를 다시 포인터로 복원하는 방법을 설명합니다.
2. 구조체의 메모리 배치 확인:
   - unsafe.Sizeof와 unsafe.Offsetof를 사용하여 구조체 전체의 크기와 각 필드의 메모리 오프셋을 확인합니다.
3. 안전하지 않은 타입 변환:
   - []byte와 string 간의 변환을 unsafe를 활용하여 수행하는 예제를 통해, 메모리 레이아웃을 직접 다루는 방법을 보여줍니다.

주의:
- unsafe 패키지는 Go의 타입 안전성을 우회하므로, 꼭 필요한 경우에만 사용해야 하며, 사용 시 매우 주의해야 합니다.
*/

package main

import (
	"fmt"
	"reflect"
	"unsafe"
)

// Person 구조체는 unsafe 예제에서 구조체의 메모리 배치를 확인하는 데 사용됩니다.
type Person struct {
	Name string // 문자열: 내부적으로는 두 필드(포인터, 길이)를 포함
	Age  int    // 정수형: 플랫폼에 따라 32비트 또는 64비트
}

// main 함수에서는 다양한 unsafe 기법들을 시연합니다.
func main() {
	fmt.Println("=== Unsafe 패키지 기본 사용 예제 ===")

	// 1. 변수의 메모리 주소 확인 및 uintptr 변환
	var x int = 42
	fmt.Printf("x의 값: %d\n", x)
	// &x를 통해 x의 메모리 주소를 얻습니다.
	fmt.Printf("x의 주소: %p\n", &x)
	// unsafe.Pointer를 사용하여 주소를 일반 포인터 타입으로 변환합니다.
	ptr := unsafe.Pointer(&x)
	// uintptr는 포인터 값을 정수형으로 변환한 값입니다.
	addr := uintptr(ptr)
	fmt.Printf("x의 주소 (uintptr 형식): %x\n", addr)

	// uintptr를 다시 unsafe.Pointer로 변환하고, 이를 통해 원래의 값에 접근합니다.
	newPtr := (*int)(unsafe.Pointer(addr))
	fmt.Printf("uintptr에서 복원한 포인터의 값: %d\n", *newPtr)
	fmt.Println()

	// 2. 구조체의 메모리 배치 확인
	person := Person{Name: "Alice", Age: 30}
	// unsafe.Sizeof를 사용해 구조체의 전체 크기를 확인합니다.
	personSize := unsafe.Sizeof(person)
	fmt.Printf("Person 구조체의 전체 크기: %d 바이트\n", personSize)
	// unsafe.Offsetof를 사용해 각 필드의 메모리 오프셋을 확인합니다.
	nameOffset := unsafe.Offsetof(person.Name)
	ageOffset := unsafe.Offsetof(person.Age)
	fmt.Printf("Name 필드의 오프셋: %d 바이트\n", nameOffset)
	fmt.Printf("Age 필드의 오프셋: %d 바이트\n", ageOffset)
	fmt.Println()

	// 3. 안전하지 않은 타입 변환 예제: []byte와 string 간의 변환
	// 일반적으로 string과 []byte 간의 변환은 메모리 복사가 발생하지만, unsafe를 사용하면 복사 없이 변환할 수 있습니다.
	originalString := "Hello, unsafe!"
	fmt.Printf("원본 문자열: %s\n", originalString)

	// 문자열을 []byte로 변환: 일반적으로 []byte(originalString)으로 변환하지만, unsafe를 사용해 메모리 복사를 피할 수 있습니다.
	// 먼저 문자열의 내부 표현을 알아보기 위해 reflect.StringHeader를 사용합니다.
	stringHeader := (*reflect.StringHeader)(unsafe.Pointer(&originalString))
	// reflect.SliceHeader를 사용해 []byte의 헤더를 생성하고, 문자열의 Data와 Len을 그대로 할당합니다.
	var byteSlice []byte
	sliceHeader := (*reflect.SliceHeader)(unsafe.Pointer(&byteSlice))
	sliceHeader.Data = stringHeader.Data
	sliceHeader.Len = stringHeader.Len
	sliceHeader.Cap = stringHeader.Len
	fmt.Printf("unsafe를 사용한 []byte 변환 결과: %v\n", byteSlice)

	// 주의: 이 방식은 원본 문자열이 immutable 하다는 Go의 보장을 우회하는 것으로, 원본 문자열을 변경하려고 하면 예기치 않은 결과가 발생할 수 있습니다.

	// 4. 메모리 레이아웃을 직접 다루기 위한 추가 예제: 구조체 포인터를 활용한 필드 접근
	// Person 구조체의 포인터를 얻고, unsafe를 활용하여 필드 값에 직접 접근합니다.
	personPtr := &person
	// personPtr의 타입은 *Person입니다. 이를 unsafe.Pointer로 변환한 후, uintptr로 변환합니다.
	personAddr := uintptr(unsafe.Pointer(personPtr))
	// Name 필드의 오프셋을 더해, Name 필드의 메모리 주소를 구합니다.
	nameFieldAddr := personAddr + nameOffset
	// unsafe.Pointer를 통해 이를 다시 문자열 포인터(*string)로 변환합니다.
	namePtr := (*string)(unsafe.Pointer(nameFieldAddr))
	fmt.Printf("unsafe로 접근한 Name 필드의 값: %s\n", *namePtr)

	fmt.Println("\n=== Unsafe 패키지 예제 종료 ===")
}
