/*
이 예제는 unsafe 패키지를 활용한 고급 타입 변환 기법을 보여줍니다.
주요 기능:
1. 구조체를 []byte 슬라이스로 변환 (메모리 복사 없이)
   - StructToBytes 함수는 구조체의 내부 메모리 레이아웃(데이터 포인터와 길이)을 그대로 사용해 []byte로 재해석합니다.
2. []byte 슬라이스를 구조체로 복원
   - BytesToStruct 함수는 주어진 []byte 슬라이스의 데이터를 타겟 구조체의 메모리 영역에 복사하여, 원래의 구조체 형태로 복원합니다.
3. unsafe를 활용한 타입 변환의 주의사항
   - 이 방식은 메모리 복사를 피하므로 성능상 이점이 있으나, Go의 불변 문자열 및 메모리 안전성 보장을 우회하므로 매우 신중하게 사용해야 합니다.
*/

package main

import (
	"fmt"
	"reflect"
	"unsafe"
)

// Header 구조체는 예제로 사용할 사용자 정의 데이터 타입입니다.
// 내부 필드로 Version, Flags, Length, Timestamp를 포함합니다.
type Header struct {
	Version   uint16 // 2바이트: 버전 정보
	Flags     uint16 // 2바이트: 플래그
	Length    uint32 // 4바이트: 데이터 길이
	Timestamp int64  // 8바이트: 타임스탬프
}

// StructToBytes는 주어진 구조체 포인터를 []byte 슬라이스로 변환합니다.
// 이 변환은 메모리 복사 없이, 구조체의 내부 메모리 영역을 그대로 재해석합니다.
func StructToBytes(s interface{}) []byte {
	// 입력 s는 반드시 구조체 포인터여야 하며, Elem()을 통해 실제 구조체 값에 접근합니다.
	val := reflect.ValueOf(s).Elem()
	// 구조체의 크기를 계산합니다.
	size := int(val.Type().Size())

	// []byte 슬라이스를 위한 SliceHeader를 준비합니다.
	var b []byte
	sliceHeader := (*reflect.SliceHeader)(unsafe.Pointer(&b))
	// 슬라이스의 Data 필드에 구조체의 메모리 주소를 할당합니다.
	sliceHeader.Data = val.UnsafeAddr()
	sliceHeader.Len = size
	sliceHeader.Cap = size

	return b
}

// BytesToStruct는 []byte 슬라이스의 데이터를 타겟 구조체의 메모리로 복사하여,
// 해당 구조체 포인터에 데이터를 채워 넣습니다. (메모리 복사 수행)
// target은 반드시 구조체 포인터여야 합니다.
func BytesToStruct(b []byte, target interface{}) {
	// target이 포인터인지 확인합니다.
	ptr := reflect.ValueOf(target)
	if ptr.Kind() != reflect.Ptr {
		panic("target은 반드시 포인터여야 합니다")
	}
	// target 구조체의 크기를 구합니다.
	size := int(ptr.Elem().Type().Size())
	if len(b) < size {
		panic("byte 슬라이스의 길이가 target 구조체 크기보다 작습니다")
	}
	// target 구조체의 메모리 주소를 얻습니다.
	structPtr := ptr.Elem().UnsafeAddr()
	// 대상 메모리 영역을 []byte 슬라이스로 재해석합니다.
	var dst []byte
	dstHeader := (*reflect.SliceHeader)(unsafe.Pointer(&dst))
	dstHeader.Data = structPtr
	dstHeader.Len = size
	dstHeader.Cap = size

	// 메모리 복사를 수행합니다.
	copy(dst, b[:size])
}

func main5() {
	fmt.Println("=== Advanced Type Conversion Demo ===")

	// 1. Header 구조체의 인스턴스 생성 및 출력
	header := Header{
		Version:   1,
		Flags:     0xAABB,
		Length:    1024,
		Timestamp: 1638400000,
	}
	fmt.Println("원본 Header 구조체:")
	fmt.Printf("%+v\n", header)

	// 2. 구조체를 []byte 슬라이스로 변환 (메모리 복사 없이)
	headerBytes := StructToBytes(&header)
	fmt.Println("\n구조체를 unsafe를 사용해 []byte로 변환한 결과:")
	fmt.Printf("%v\n", headerBytes)

	// 3. []byte를 이용하여 구조체 필드 수정
	// 예: Header 구조체의 Version 필드는 0~1바이트 위치에 저장됨.
	// unsafe를 사용하여 직접 메모리에서 값을 수정하면, 원본 구조체가 영향을 받습니다.
	versionPtr := (*uint16)(unsafe.Pointer(&headerBytes[0]))
	fmt.Printf("\n원래 Version 필드 값: %d\n", *versionPtr)
	// Version 값을 2로 수정
	*versionPtr = 2
	fmt.Printf("수정된 Version 필드 값: %d\n", *versionPtr)

	// 4. 수정 결과 확인: header 구조체의 값이 변경됨
	fmt.Println("\n수정 후 Header 구조체:")
	fmt.Printf("%+v\n", header)

	// 5. []byte를 새로운 구조체로 복원하는 예제
	var newHeader Header
	BytesToStruct(headerBytes, &newHeader)
	fmt.Println("\n[]byte에서 복원한 새로운 Header 구조체:")
	fmt.Printf("%+v\n", newHeader)

	fmt.Println("=== Advanced Type Conversion Demo 종료 ===")
}
