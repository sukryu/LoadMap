/*
이 예제는 Go의 reflection을 활용하여 복합 데이터 구조(배열, 슬라이스, 맵)의 내부 정보를 동적으로 조회하고 조작하는 방법을 보여줍니다.
주요 기능:
1. 배열: 배열의 길이, 요소 타입, 각 요소의 값 조회
2. 슬라이스: 슬라이스의 길이, 용량, 요소 접근 및 동적 수정
3. 맵: 맵의 키, 값, 길이 조회 및 동적으로 요소 추가/삭제하는 방법
4. 복합 데이터 구조에 대한 reflection 활용: 다양한 데이터 타입의 메타데이터를 분석하여 동적 처리를 구현하는 기법

이 예제는 실제 업무에서 동적 데이터 처리, 제네릭 라이브러리 구현, 데이터 검증 등 다양한 응용 분야에 활용할 수 있는 기초를 제공합니다.
*/

package main

import (
	"fmt"
	"reflect"
)

func main5() {
	// ---------------------------------
	// 1. 배열 (Array) Reflection 예제
	// ---------------------------------
	fmt.Println("=== 배열 Reflection 예제 ===")
	// 정수형 배열 선언 (길이 5)
	arr := [5]int{10, 20, 30, 40, 50}
	// 배열의 reflect.Value 생성
	arrValue := reflect.ValueOf(arr)
	// 배열의 reflect.Type 생성
	arrType := reflect.TypeOf(arr)
	fmt.Printf("배열: %v\n", arr)
	fmt.Printf("타입: %s, 길이: %d\n", arrType, arrValue.Len())

	// 배열의 각 요소 출력
	for i := 0; i < arrValue.Len(); i++ {
		elem := arrValue.Index(i)
		fmt.Printf("arr[%d] = %v\n", i, elem.Interface())
	}
	fmt.Println()

	// ---------------------------------
	// 2. 슬라이스 (Slice) Reflection 예제
	// ---------------------------------
	fmt.Println("=== 슬라이스 Reflection 예제 ===")
	// 문자열 슬라이스 선언
	slice := []string{"apple", "banana", "cherry", "date"}
	// 슬라이스의 reflect.Value 생성
	sliceValue := reflect.ValueOf(slice)
	sliceType := reflect.TypeOf(slice)
	fmt.Printf("슬라이스: %v\n", slice)
	fmt.Printf("타입: %s, 길이: %d, 용량: %d\n", sliceType, sliceValue.Len(), sliceValue.Cap())

	// 슬라이스의 각 요소 출력
	for i := 0; i < sliceValue.Len(); i++ {
		elem := sliceValue.Index(i)
		fmt.Printf("slice[%d] = %v\n", i, elem.Interface())
	}
	// 슬라이스 요소 수정: 슬라이스는 settable하므로 직접 수정 가능
	// 단, reflect.ValueOf(slice)로 생성한 값은 수정 불가능하므로, 포인터를 사용하여 수정합니다.
	slicePtr := &slice
	sliceValueSet := reflect.ValueOf(slicePtr).Elem() // settable reflect.Value
	// 첫 번째 요소를 "avocado"로 변경
	if sliceValueSet.Index(0).CanSet() {
		original := sliceValueSet.Index(0).Interface().(string)
		fmt.Printf("원래 첫 번째 요소: %s\n", original)
		sliceValueSet.Index(0).SetString("avocado")
		fmt.Printf("수정 후 첫 번째 요소: %s\n", sliceValueSet.Index(0).Interface().(string))
	} else {
		fmt.Println("슬라이스 요소를 수정할 수 없습니다.")
	}
	fmt.Println()

	// ---------------------------------
	// 3. 맵 (Map) Reflection 예제
	// ---------------------------------
	fmt.Println("=== 맵 Reflection 예제 ===")
	// 정수 값을 가지는 문자열 맵 선언
	m := map[string]int{
		"one":   1,
		"two":   2,
		"three": 3,
	}
	mapValue := reflect.ValueOf(m)
	mapType := reflect.TypeOf(m)
	fmt.Printf("맵: %v\n", m)
	fmt.Printf("타입: %s, 길이: %d\n", mapType, mapValue.Len())

	// 맵의 각 키와 값 출력
	// MapKeys()를 사용하여 키들의 슬라이스를 얻을 수 있습니다.
	keys := mapValue.MapKeys()
	for _, key := range keys {
		value := mapValue.MapIndex(key)
		fmt.Printf("키: %v, 값: %v\n", key.Interface(), value.Interface())
	}

	// 동적 맵 수정: 맵은 reflect.Value를 통해 직접 수정할 수 있습니다.
	// 새로운 키-값 쌍 추가
	newKey := reflect.ValueOf("four")
	newValue := reflect.ValueOf(4)
	mapValue.SetMapIndex(newKey, newValue)
	fmt.Println("새로운 항목 추가 후 맵:", m)
	// 기존 키 삭제: Delete() 메서드 사용
	mapValue.SetMapIndex(reflect.ValueOf("one"), reflect.Value{})
	fmt.Println("키 'one' 삭제 후 맵:", m)

	// ---------------------------------
	// 4. 복합 데이터 구조의 Reflection 종합 예제
	// ---------------------------------
	fmt.Println("\n=== 복합 데이터 구조 종합 Reflection 예제 ===")
	// 예제: 구조체 내부에 배열, 슬라이스, 맵을 포함하는 경우
	type ComplexData struct {
		Numbers   [3]int
		Fruits    []string
		WordCount map[string]int
	}
	data := ComplexData{
		Numbers:   [3]int{7, 8, 9},
		Fruits:    []string{"kiwi", "mango", "papaya"},
		WordCount: map[string]int{"hello": 1, "world": 2},
	}
	dataValue := reflect.ValueOf(data)
	dataType := reflect.TypeOf(data)
	fmt.Printf("ComplexData 타입: %s\n", dataType)
	// 각 필드의 정보를 동적으로 조회
	for i := 0; i < dataType.NumField(); i++ {
		field := dataType.Field(i)
		value := dataValue.Field(i)
		fmt.Printf("필드 %d: %s (타입: %s) = %v\n", i, field.Name, field.Type, value.Interface())
	}

	fmt.Println("\nAdvanced Data Structures Reflection 예제 데모 완료.")
}
