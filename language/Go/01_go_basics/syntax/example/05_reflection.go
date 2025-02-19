package examples

import (
	"fmt"
	"reflect"
)

// Person represents a sample struct for reflection
type Person struct {
	Name    string `json:"name" validate:"required"`
	Age     int    `json:"age" validate:"gte=0,lte=150"`
	Address string `json:"address,omitempty"`
}

// ValidateStruct validates struct fields based on tags
func ValidateStruct(s interface{}) []string {
	var errors []string
	v := reflect.ValueOf(s)

	// 포인터인 경우 실제 값을 가져옴
	if v.Kind() == reflect.Ptr {
		v = v.Elem()
	}

	// 구조체가 아닌 경우 에러 반환
	if v.Kind() != reflect.Struct {
		return []string{"입력값이 구조체가 아닙니다"}
	}

	t := v.Type()
	for i := 0; i < t.NumField(); i++ {
		field := t.Field(i)
		value := v.Field(i)

		// required 태그 검사
		if field.Tag.Get("validate") == "required" && value.String() == "" {
			errors = append(errors, fmt.Sprintf("%s 필드는 필수값입니다", field.Name))
		}
	}

	return errors
}

// PrintStructInfo prints detailed information about a struct
func PrintStructInfo(s interface{}) {
	t := reflect.TypeOf(s)
	v := reflect.ValueOf(s)

	fmt.Printf("Type: %s\n", t.Name())
	fmt.Printf("Kind: %s\n", t.Kind())

	for i := 0; i < t.NumField(); i++ {
		field := t.Field(i)
		value := v.Field(i)

		fmt.Printf("\nField: %s\n", field.Name)
		fmt.Printf("Type: %s\n", field.Type)
		fmt.Printf("Value: %v\n", value.Interface())
		fmt.Printf("Tags: %s\n", field.Tag)
	}
}

// ReflectionExamples demonstrates the use of reflection in Go
func ReflectionExamples() {
	person := Person{
		Name:    "John Doe",
		Age:     30,
		Address: "123 Main St",
	}

	// 구조체 정보 출력
	fmt.Println("=== 구조체 정보 ===")
	PrintStructInfo(person)

	// 구조체 검증
	fmt.Println("\n=== 구조체 검증 ===")
	if errors := ValidateStruct(person); len(errors) > 0 {
		fmt.Println("검증 에러:")
		for _, err := range errors {
			fmt.Printf("- %s\n", err)
		}
	} else {
		fmt.Println("검증 성공!")
	}

	// 동적으로 필드 값 설정
	v := reflect.ValueOf(&person).Elem()
	if nameField := v.FieldByName("Name"); nameField.IsValid() && nameField.CanSet() {
		nameField.SetString("Jane Doe")
		fmt.Printf("\n이름이 변경됨: %s\n", person.Name)
	}
}
