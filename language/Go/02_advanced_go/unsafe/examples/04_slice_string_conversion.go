/*
이 예제는 unsafe 패키지를 사용하여 []byte와 string 간의 변환을 수행하는 방법을 보여줍니다.
기본적으로, Go에서 문자열은 불변(immutable)이며, 일반적인 변환은 메모리 복사가 발생합니다.
그러나 unsafe를 사용하면, 메모리 복사 없이 문자열과 []byte 간의 변환을 수행할 수 있습니다.

주요 기능:
1. 문자열을 []byte로 변환 (메모리 복사 없이)
   - reflect.StringHeader와 reflect.SliceHeader를 사용하여 문자열의 내부 구조(데이터 포인터와 길이)를 그대로 활용합니다.
2. []byte를 문자열로 변환 (메모리 복사 없이)
   - []byte의 내부 정보를 그대로 사용하여 문자열을 생성합니다.

주의:
- 이 방식은 메모리 복사를 피하기 때문에 성능상 이점을 제공하지만, 문자열은 불변이어야 한다는 Go의 보장을 우회합니다.
- 따라서, unsafe를 통한 변환 후 []byte를 수정하면 예기치 않은 결과가 발생할 수 있습니다.
*/

package main

import (
	"fmt"
	"reflect"
	"unsafe"
)

func main4() {
	fmt.Println("=== Unsafe: []byte와 string 간의 변환 데모 ===")

	// -------------------------------------------
	// 1. 문자열을 []byte로 변환 (메모리 복사 없이)
	// -------------------------------------------
	originalStr := "Hello, unsafe world!"
	fmt.Println("원본 문자열:", originalStr)

	// 문자열의 내부 구조를 알아보기 위해 reflect.StringHeader를 사용합니다.
	// StringHeader는 문자열의 Data(포인터)와 Len(길이)을 포함합니다.
	strHeader := (*reflect.StringHeader)(unsafe.Pointer(&originalStr))

	// []byte의 내부 구조를 표현하는 reflect.SliceHeader를 선언합니다.
	// SliceHeader는 Data, Len, Cap을 포함합니다.
	var byteSlice []byte
	sliceHeader := (*reflect.SliceHeader)(unsafe.Pointer(&byteSlice))

	// 문자열의 Data와 Len를 그대로 할당하여, []byte가 같은 메모리 영역을 참조하도록 합니다.
	sliceHeader.Data = strHeader.Data
	sliceHeader.Len = strHeader.Len
	sliceHeader.Cap = strHeader.Len // Cap도 동일하게 설정

	fmt.Println("unsafe를 사용하여 변환한 []byte:", byteSlice)

	// -------------------------------------------
	// 2. []byte를 문자열로 변환 (메모리 복사 없이)
	// -------------------------------------------
	// 예제용 []byte 생성
	originalBytes := []byte("Unsafe conversion from []byte to string!")
	fmt.Println("\n원본 []byte:", originalBytes)

	// []byte의 내부 구조를 가져오기 위해 reflect.SliceHeader 사용
	byteHeader := (*reflect.SliceHeader)(unsafe.Pointer(&originalBytes))

	// byteHeader를 활용하여, unsafe.Pointer를 통해 문자열을 생성합니다.
	// 문자열의 내부 구조는 reflect.StringHeader와 동일한 포맷을 가지므로, 데이터 포인터와 길이 정보를 그대로 사용합니다.
	convertedStr := *(*string)(unsafe.Pointer(byteHeader))
	fmt.Println("unsafe를 사용하여 변환한 문자열:", convertedStr)

	// -------------------------------------------
	// 3. 주의사항
	// -------------------------------------------
	fmt.Println("\n주의: unsafe를 사용한 변환은 메모리 복사 없이 이루어지므로,")
	fmt.Println("원본 []byte를 수정하면, 해당 문자열도 영향을 받을 수 있습니다.")
	fmt.Println("따라서, 변환 후에는 원본 데이터를 수정하지 않는 것이 좋습니다.")

	fmt.Println("\n=== Unsafe Slice-String Conversion Demo 종료 ===")
}
