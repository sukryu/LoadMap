/*
이 예제는 Go의 reflection 기능을 사용하여 구조체의 필드에 지정된 태그 정보를 기반으로
데이터 검증을 수행하는 방법을 보여줍니다.

주요 기능:
1. 구조체에 validation 태그를 지정하여 필수값, 최소/최대 길이, 숫자 범위, 이메일 형식 등의 규칙을 정의합니다.
2. reflect 패키지를 사용하여 구조체의 각 필드와 해당 태그를 동적으로 조회합니다.
3. 각 검증 규칙에 따라 필드의 값이 조건을 만족하는지 확인하고, 위반 시 에러 메시지를 생성합니다.
4. 모든 필드의 검증 결과를 종합하여, 하나 이상의 오류가 있을 경우 이를 반환합니다.

이 예제는 실무에서 데이터 유효성 검사, 사용자 입력 검증, API 요청 파라미터 검증 등에 활용할 수 있습니다.
*/

package main

import (
	"errors"
	"fmt"
	"reflect"
	"strconv"
	"strings"
)

// User 구조체는 validation 예제에 사용할 데이터 타입입니다.
// 각 필드에 validate 태그를 지정하여, 필수값(required), 최소값(min), 최대값(max),
// 그리고 간단한 이메일 형식(email) 검증 규칙을 정의합니다.
type User1 struct {
	Name  string `json:"name" validate:"required,min=3,max=50"`
	Age   int    `json:"age" validate:"min=18,max=100"`
	Email string `json:"email" validate:"required,email"`
}

// ValidateStruct는 입력된 구조체 s의 각 필드에 대해 validate 태그에 명시된 규칙을 검사합니다.
// 규칙에 위반되는 경우, 해당 오류 메시지를 모아서 반환합니다.
func ValidateStruct(s interface{}) error {
	val := reflect.ValueOf(s)
	// 만약 s가 포인터라면 실제 값으로 변환합니다.
	if val.Kind() == reflect.Ptr {
		val = val.Elem()
	}
	// s가 구조체가 아닌 경우 오류 반환.
	if val.Kind() != reflect.Struct {
		return errors.New("입력값이 구조체가 아닙니다")
	}

	typ := val.Type()
	var errorsList []string

	// 구조체의 각 필드를 순회합니다.
	for i := 0; i < val.NumField(); i++ {
		field := typ.Field(i)
		fieldValue := val.Field(i)
		// validate 태그가 없다면 건너뜁니다.
		tag := field.Tag.Get("validate")
		if tag == "" {
			continue
		}
		// 태그를 콤마(,)를 기준으로 분리하여 각 검증 조건을 얻습니다.
		constraints := strings.Split(tag, ",")
		for _, constraint := range constraints {
			// 'required' 조건 처리: 필드가 비어있으면 오류 처리.
			if constraint == "required" {
				if isEmptyValue(fieldValue) {
					errorsList = append(errorsList, fmt.Sprintf("%s 필드는 필수값입니다", field.Name))
				}
			} else if strings.HasPrefix(constraint, "min=") {
				// min 조건 처리: 문자열의 최소 길이 또는 숫자의 최소 값 검사
				minValStr := strings.TrimPrefix(constraint, "min=")
				if fieldValue.Kind() == reflect.String {
					minVal, err := strconv.Atoi(minValStr)
					if err == nil && len(fieldValue.String()) < minVal {
						errorsList = append(errorsList, fmt.Sprintf("%s 필드는 최소 %d 글자 이상이어야 합니다", field.Name, minVal))
					}
				} else if isNumericKind(fieldValue.Kind()) {
					minVal, err := strconv.ParseInt(minValStr, 10, 64)
					if err == nil && fieldValue.Int() < minVal {
						errorsList = append(errorsList, fmt.Sprintf("%s 필드는 최소 %d 이상이어야 합니다", field.Name, minVal))
					}
				}
			} else if strings.HasPrefix(constraint, "max=") {
				// max 조건 처리: 문자열의 최대 길이 또는 숫자의 최대 값 검사
				maxValStr := strings.TrimPrefix(constraint, "max=")
				if fieldValue.Kind() == reflect.String {
					maxVal, err := strconv.Atoi(maxValStr)
					if err == nil && len(fieldValue.String()) > maxVal {
						errorsList = append(errorsList, fmt.Sprintf("%s 필드는 최대 %d 글자 이하이어야 합니다", field.Name, maxVal))
					}
				} else if isNumericKind(fieldValue.Kind()) {
					maxVal, err := strconv.ParseInt(maxValStr, 10, 64)
					if err == nil && fieldValue.Int() > maxVal {
						errorsList = append(errorsList, fmt.Sprintf("%s 필드는 최대 %d 이하이어야 합니다", field.Name, maxVal))
					}
				}
			} else if constraint == "email" {
				// 간단한 이메일 형식 검증: '@' 문자가 포함되어 있는지 확인합니다.
				if fieldValue.Kind() == reflect.String {
					if !strings.Contains(fieldValue.String(), "@") {
						errorsList = append(errorsList, fmt.Sprintf("%s 필드는 유효한 이메일 형식이어야 합니다", field.Name))
					}
				}
			}
		}
	}

	// 하나 이상의 오류가 있으면 이를 종합하여 반환합니다.
	if len(errorsList) > 0 {
		return errors.New(strings.Join(errorsList, "; "))
	}
	return nil
}

// isEmptyValue는 reflect.Value가 비어있는지 확인하는 헬퍼 함수입니다.
func isEmptyValue(v reflect.Value) bool {
	switch v.Kind() {
	case reflect.String, reflect.Array, reflect.Slice, reflect.Map:
		return v.Len() == 0
	case reflect.Bool:
		return !v.Bool()
	case reflect.Int, reflect.Int8, reflect.Int16, reflect.Int32, reflect.Int64:
		return v.Int() == 0
	case reflect.Uint, reflect.Uint8, reflect.Uint16, reflect.Uint32, reflect.Uint64, reflect.Uintptr:
		return v.Uint() == 0
	case reflect.Float32, reflect.Float64:
		return v.Float() == 0
	case reflect.Interface, reflect.Ptr:
		return v.IsNil()
	}
	return false
}

// isNumericKind는 주어진 reflect.Kind이 숫자 타입인지 확인합니다.
func isNumericKind(k reflect.Kind) bool {
	return k >= reflect.Int && k <= reflect.Float64
}

func main8() {
	fmt.Println("=== Reflection in Validation Demo ===")

	// 1. 유효한 User 인스턴스 생성
	user1 := User1{
		Name:  "Alice",
		Age:   30,
		Email: "alice@example.com",
	}
	err := ValidateStruct(user1)
	if err != nil {
		fmt.Println("user1 검증 오류:", err)
	} else {
		fmt.Println("user1 검증 통과!")
	}

	// 2. 유효하지 않은 User 인스턴스 생성: 필수 필드 누락 및 규칙 위반
	user2 := User1{
		Name:  "Al",           // 최소 3 글자 요구 위반
		Age:   16,             // 최소 18 요구 위반
		Email: "invalidemail", // 이메일 형식 위반 (문자열에 '@' 없음)
	}
	err = ValidateStruct(user2)
	if err != nil {
		fmt.Println("user2 검증 오류:", err)
	} else {
		fmt.Println("user2 검증 통과!")
	}

	fmt.Println("=== Reflection in Validation Demo 완료 ===")
}
