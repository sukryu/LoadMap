/*
이 예제는 reflection 기반의 유틸리티 함수들을 구현합니다.
주요 기능:
1. DeepCopy: 주어진 객체를 재귀적으로 복사하여 깊은 복사를 수행합니다.
   - 기본 자료형, 배열, 슬라이스, 맵, 구조체에 대해 작동하며, 복잡한 객체를 안전하게 복사할 수 있습니다.
2. DynamicTypeConvert: 런타임에 주어진 값(value)을 원하는 targetType으로 변환을 시도합니다.
   - 변환이 가능한 경우, targetType에 맞게 값을 반환하며, 그렇지 않으면 오류를 반환합니다.
3. PrintStructDetails: 구조체의 필드 이름, 타입, 값, 그리고 태그 정보를 출력하여, 구조체의 내부 메타데이터를 확인할 수 있습니다.

이러한 유틸리티 함수들은 동적 데이터 처리, 설정 복제, 런타임 타입 검증 등 다양한 실무 응용 분야에 활용될 수 있습니다.
*/

package main

import (
	"errors"
	"fmt"
	"reflect"
)

// DeepCopy는 주어진 input의 깊은 복사본을 생성하여 반환합니다.
// 이 함수는 기본 자료형, 배열, 슬라이스, 맵, 구조체에 대해 재귀적으로 복사를 수행합니다.
func DeepCopy(input interface{}) interface{} {
	// 입력값을 reflect.Value로 감쌉니다.
	val := reflect.ValueOf(input)
	return deepCopyRecursive(val).Interface()
}

// deepCopyRecursive는 재귀적으로 값을 복사하는 내부 함수입니다.
func deepCopyRecursive(val reflect.Value) reflect.Value {
	switch val.Kind() {
	// 기본 자료형 및 불변 값은 그대로 반환 (값 복사)
	case reflect.Bool, reflect.Int, reflect.Int8, reflect.Int16,
		reflect.Int32, reflect.Int64, reflect.Uint, reflect.Uint8,
		reflect.Uint16, reflect.Uint32, reflect.Uint64, reflect.Uintptr,
		reflect.Float32, reflect.Float64, reflect.Complex64, reflect.Complex128,
		reflect.String:
		return val

	// 포인터의 경우, 새로운 포인터를 생성하고 내부 값을 복사합니다.
	case reflect.Ptr:
		if val.IsNil() {
			return reflect.Zero(val.Type())
		}
		// 새로운 포인터 생성
		copyPtr := reflect.New(val.Elem().Type())
		copyPtr.Elem().Set(deepCopyRecursive(val.Elem()))
		return copyPtr

	// 배열의 경우, 각 요소를 복사하여 새로운 배열을 생성합니다.
	case reflect.Array:
		copyArr := reflect.New(val.Type()).Elem()
		for i := 0; i < val.Len(); i++ {
			copyArr.Index(i).Set(deepCopyRecursive(val.Index(i)))
		}
		return copyArr

	// 슬라이스의 경우, 새 슬라이스를 생성하고 각 요소를 복사합니다.
	case reflect.Slice:
		if val.IsNil() {
			return reflect.Zero(val.Type())
		}
		copySlice := reflect.MakeSlice(val.Type(), val.Len(), val.Cap())
		for i := 0; i < val.Len(); i++ {
			copySlice.Index(i).Set(deepCopyRecursive(val.Index(i)))
		}
		return copySlice

	// 맵의 경우, 새로운 맵을 생성하고, 각 키와 값을 복사합니다.
	case reflect.Map:
		if val.IsNil() {
			return reflect.Zero(val.Type())
		}
		copyMap := reflect.MakeMapWithSize(val.Type(), val.Len())
		for _, key := range val.MapKeys() {
			copyMap.SetMapIndex(deepCopyRecursive(key), deepCopyRecursive(val.MapIndex(key)))
		}
		return copyMap

	// 구조체의 경우, 각 필드를 복사하여 새로운 구조체를 생성합니다.
	case reflect.Struct:
		copyStruct := reflect.New(val.Type()).Elem()
		for i := 0; i < val.NumField(); i++ {
			// 필드가 settable 한지 확인 (비공개 필드는 복사하지 못할 수 있음)
			if copyStruct.Field(i).CanSet() {
				copyStruct.Field(i).Set(deepCopyRecursive(val.Field(i)))
			} else {
				// 만약 수정이 불가능하면 원본 필드 값 그대로 사용
				copyStruct.Field(i).Set(val.Field(i))
			}
		}
		return copyStruct

	// 기타 타입은 그대로 반환
	default:
		return val
	}
}

// DynamicTypeConvert는 주어진 value를 targetType으로 변환을 시도합니다.
// 변환이 가능하면 변환된 값을 반환하고, 불가능하면 오류를 반환합니다.
func DynamicTypeConvert(value interface{}, targetType reflect.Type) (interface{}, error) {
	val := reflect.ValueOf(value)
	// 만약 value의 타입이 이미 targetType과 같다면 그대로 반환
	if val.Type() == targetType {
		return value, nil
	}

	// 만약 value가 targetType으로 변환 가능하다면, convert 메서드를 사용
	if val.Type().ConvertibleTo(targetType) {
		converted := val.Convert(targetType)
		return converted.Interface(), nil
	}
	return nil, errors.New("변환 불가능한 타입: " + val.Type().String() + " -> " + targetType.String())
}

// PrintStructDetails는 구조체 s의 필드, 타입, 값, 그리고 태그 정보를 상세히 출력합니다.
// s는 구조체 또는 구조체 포인터여야 합니다.
func PrintStructDetails(s interface{}) error {
	val := reflect.ValueOf(s)
	// 만약 s가 포인터라면 Elem()를 통해 실제 값을 얻습니다.
	if val.Kind() == reflect.Ptr {
		val = val.Elem()
	}
	// s가 구조체가 아니라면 오류 반환
	if val.Kind() != reflect.Struct {
		return errors.New("입력값이 구조체가 아닙니다")
	}

	typ := val.Type()
	fmt.Printf("구조체 타입: %s\n", typ.Name())
	fmt.Printf("총 필드 수: %d\n", typ.NumField())
	fmt.Println("필드 상세 정보:")
	for i := 0; i < typ.NumField(); i++ {
		field := typ.Field(i)
		value := val.Field(i)
		fmt.Printf("필드 %d: %s\n", i, field.Name)
		fmt.Printf("  타입: %s\n", field.Type)
		fmt.Printf("  값: %v\n", value.Interface())
		fmt.Printf("  태그: %s\n", field.Tag)
	}
	return nil
}

func main6() {
	fmt.Println("=== Reflection Utilities Demo ===")

	// 1. DeepCopy 예제
	fmt.Println("\n-- DeepCopy 예제 --")
	original := map[string]interface{}{
		"name":   "Alice",
		"age":    30,
		"scores": []int{90, 85, 92},
	}
	copyInterface := DeepCopy(original)
	fmt.Println("원본:", original)
	fmt.Println("복사본:", copyInterface)

	// 2. DynamicTypeConvert 예제
	fmt.Println("\n-- DynamicTypeConvert 예제 --")
	var num int = 42
	// 정수를 float64로 변환 시도
	converted, err := DynamicTypeConvert(num, reflect.TypeOf(float64(0)))
	if err != nil {
		fmt.Println("타입 변환 오류:", err)
	} else {
		fmt.Printf("변환 결과: %v (타입: %T)\n", converted, converted)
	}

	// 3. PrintStructDetails 예제
	fmt.Println("\n-- PrintStructDetails 예제 --")
	type Sample struct {
		Title   string `json:"title" validate:"required"`
		Count   int    `json:"count" validate:"gte=0"`
		Enabled bool   `json:"enabled"`
	}
	sample := Sample{Title: "Reflection Demo", Count: 100, Enabled: true}
	if err := PrintStructDetails(sample); err != nil {
		fmt.Println("구조체 정보 출력 오류:", err)
	}

	fmt.Println("\nReflection Utilities Demo 완료.")
}
