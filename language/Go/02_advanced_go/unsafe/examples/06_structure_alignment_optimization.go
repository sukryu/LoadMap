/*
이 예제는 Go의 unsafe 패키지를 활용하여 구조체의 메모리 정렬 최적화를 시연합니다.
주요 기능:
1. 비효율적인 필드 배치를 가진 구조체와 최적화된 필드 배치를 가진 구조체를 정의합니다.
2. unsafe.Sizeof와 unsafe.Offsetof를 사용하여 각 구조체의 전체 크기 및 필드 오프셋을 측정합니다.
3. 각 구조체에서 불필요한 패딩(낭비된 메모리)이 얼마나 발생하는지 계산하는 유틸리티 함수를 구현합니다.
4. 두 구조체의 메모리 사용 차이를 비교하여, 필드 순서를 변경함으로써 최적화가 어떻게 이루어지는지 확인합니다.

주의:
- 구조체의 필드 순서에 따라 컴파일러가 추가하는 패딩이 달라지므로, 메모리 효율성을 높이기 위해 큰 필드부터 작은 필드 순으로 배치하는 것이 일반적입니다.
*/

package main

import (
	"fmt"
	"reflect"
	"unsafe"
)

// PoorlyAligned는 비효율적인 필드 순서를 가진 구조체 예제입니다.
// 불필요한 패딩으로 인해 메모리 사용량이 증가할 수 있습니다.
type PoorlyAligned1 struct {
	Flag   bool    // 1바이트: 불리언 값 (이후 7바이트 패딩 발생 가능)
	Count  int32   // 4바이트: 정수형 (32비트)
	Amount float64 // 8바이트: 부동소수점
}

// WellAligned는 최적화된 필드 순서를 가진 구조체 예제입니다.
// 큰 필드부터 작은 필드 순으로 배치하여, 패딩을 최소화합니다.
type WellAligned1 struct {
	Amount float64 // 8바이트
	Count  int32   // 4바이트
	Flag   bool    // 1바이트
	// 예상: Flag 이후에 3바이트 패딩 (전체 16바이트로 정렬)
}

// analyzeStructAlignment는 주어진 구조체의 전체 크기와 각 필드의 오프셋을 출력하고,
// 불필요한 패딩(낭비된 메모리)의 총량을 계산하여 출력합니다.
// 입력 s는 구조체 타입이어야 합니다.
func analyzeStructAlignment(s interface{}) {
	val := reflectValue(s)
	typ := val.Type()
	totalSize := unsafe.Sizeof(val.Interface())

	fmt.Printf("구조체 타입: %s\n", typ.Name())
	fmt.Printf("전체 크기: %d 바이트\n", totalSize)

	var prevOffset uintptr = 0
	var wastedBytes uintptr = 0
	for i := 0; i < typ.NumField(); i++ {
		field := typ.Field(i)
		offset := field.Offset
		// 낭비된 공간은 이전 필드의 끝과 현재 필드의 시작 사이의 차이입니다.
		if offset > prevOffset {
			waste := offset - prevOffset
			wastedBytes += waste
			if waste > 0 {
				fmt.Printf("필드 %s: 오프셋=%d (이전 필드 끝과의 차이: %d 바이트 낭비)\n", field.Name, offset, waste)
			} else {
				fmt.Printf("필드 %s: 오프셋=%d\n", field.Name, offset)
			}
		} else {
			fmt.Printf("필드 %s: 오프셋=%d\n", field.Name, offset)
		}
		// 현재 필드의 끝: 오프셋 + 필드 크기
		fieldSize := field.Type.Size()
		prevOffset = offset + fieldSize
	}
	// 전체 크기와 마지막 필드의 끝 사이에도 패딩이 있을 수 있습니다.
	if totalSize > prevOffset {
		finalWaste := totalSize - prevOffset
		wastedBytes += finalWaste
		fmt.Printf("구조체 끝과 마지막 필드 끝 사이의 낭비: %d 바이트\n", finalWaste)
	}
	fmt.Printf("총 낭비된 메모리: %d 바이트\n", wastedBytes)
	fmt.Println("-----------------------------")
}

// reflectValue는 입력값 s를 reflect.Value로 반환합니다.
// s가 포인터면 Elem()을 호출하여 실제 값을 반환합니다.
func reflectValue(s interface{}) reflect.Value {
	val := reflect.ValueOf(s)
	if val.Kind() == reflect.Ptr {
		return val.Elem()
	}
	return val
}

func main6() {
	fmt.Println("=== Structure Alignment Optimization Demo ===")

	// 1. PoorlyAligned 구조체 분석
	pa := PoorlyAligned1{
		Flag:   true,
		Count:  123,
		Amount: 456.78,
	}
	fmt.Println("PoorlyAligned 구조체 분석:")
	analyzeStructAlignment(pa)

	// 2. WellAligned 구조체 분석
	wa := WellAligned1{
		Amount: 456.78,
		Count:  123,
		Flag:   true,
	}
	fmt.Println("WellAligned 구조체 분석:")
	analyzeStructAlignment(wa)

	fmt.Println("=== Structure Alignment Optimization Demo 종료 ===")
}
