/*
이 예제는 reflection을 이용하여 구조체의 필드 값을 동적으로 수정하는 방법을 보여줍니다.
주요 기능:
1. settable한 reflect.Value를 얻기 위해 구조체의 포인터를 활용하는 방법
2. 특정 필드를 찾아 해당 필드의 값을 동적으로 변경하는 방법
3. 수정 전후의 값을 비교하여 변경 사항을 확인하는 방법
4. 동적으로 변경된 필드 값을 사용하여, 이후 메서드 호출 등에서 변경 효과를 확인하는 예제

이 예제는 실무에서 구조체의 필드 값을 런타임에 유연하게 조작해야 하는 경우에 활용할 수 있습니다.
*/

package main

import (
	"fmt"
	"reflect"
)

// Person 구조체는 필드 수정 예제에 사용할 기본 구조체입니다.
type Person1 struct {
	Name    string  // 사람의 이름
	Age     int     // 나이
	Salary  float64 // 급여 정보
	Married bool    // 결혼 여부
}

// Greet 메서드는 Person 구조체의 현재 상태를 출력하는 메서드입니다.
func (p Person1) Greet1() {
	status := "unmarried"
	if p.Married {
		status = "married"
	}
	fmt.Printf("Hello, I'm %s, %d years old, earning %.2f, and I'm %s.\n", p.Name, p.Age, p.Salary, status)
}

func main3() {
	// 1. Person 구조체 인스턴스 생성
	p := Person1{Name: "Alice", Age: 30, Salary: 75000.50, Married: false}
	fmt.Println("원래 Person 값:")
	p.Greet1()
	fmt.Println()

	// 2. Reflection을 사용하여 필드 값을 수정하려면, 구조체의 포인터를 사용해야 함
	// p의 포인터를 얻고, 이를 통해 settable한 reflect.Value를 생성합니다.
	pPtr := &p
	// reflect.ValueOf(pPtr)는 포인터의 값이고, Elem()를 호출하면 실제 구조체의 settable한 값을 얻을 수 있습니다.
	pValue := reflect.ValueOf(pPtr).Elem()

	// 3. 각 필드의 현재 값 출력 및 수정
	fmt.Println("== 수정 전 필드 값 ==")
	fmt.Printf("Name: %s, Age: %d, Salary: %.2f, Married: %v\n",
		pValue.FieldByName("Name").Interface(),
		pValue.FieldByName("Age").Interface(),
		pValue.FieldByName("Salary").Interface(),
		pValue.FieldByName("Married").Interface())

	// 4. 동적으로 각 필드 값을 수정하기
	// Name 필드를 "Bob"으로 수정
	nameField := pValue.FieldByName("Name")
	if nameField.IsValid() && nameField.CanSet() {
		nameField.SetString("Bob")
	} else {
		fmt.Println("Name 필드를 수정할 수 없습니다.")
	}

	// Age 필드를 40으로 수정
	ageField := pValue.FieldByName("Age")
	if ageField.IsValid() && ageField.CanSet() {
		ageField.SetInt(40)
	} else {
		fmt.Println("Age 필드를 수정할 수 없습니다.")
	}

	// Salary 필드를 85000.75로 수정
	salaryField := pValue.FieldByName("Salary")
	if salaryField.IsValid() && salaryField.CanSet() {
		salaryField.SetFloat(85000.75)
	} else {
		fmt.Println("Salary 필드를 수정할 수 없습니다.")
	}

	// Married 필드를 true로 수정
	marriedField := pValue.FieldByName("Married")
	if marriedField.IsValid() && marriedField.CanSet() {
		marriedField.SetBool(true)
	} else {
		fmt.Println("Married 필드를 수정할 수 없습니다.")
	}

	// 5. 수정 후의 필드 값 출력
	fmt.Println("\n== 수정 후 필드 값 ==")
	fmt.Printf("Name: %s, Age: %d, Salary: %.2f, Married: %v\n",
		pValue.FieldByName("Name").Interface(),
		pValue.FieldByName("Age").Interface(),
		pValue.FieldByName("Salary").Interface(),
		pValue.FieldByName("Married").Interface())
	fmt.Println()

	// 6. 동적으로 수정된 값이 반영되었음을 메서드 호출을 통해 확인
	fmt.Println("수정 후 Greet 메서드 호출 결과:")
	p.Greet1()

	// 7. 추가: 동적으로 필드 이름을 받아서 수정하는 예제
	fmt.Println("\n-- 동적 필드 수정 예제: 사용자 지정 수정 --")
	fieldToModify := "Name"
	newValue := "Charlie"
	fieldVal := pValue.FieldByName(fieldToModify)
	if fieldVal.IsValid() && fieldVal.CanSet() && fieldVal.Kind() == reflect.String {
		fmt.Printf("필드 %s의 원래 값: %s\n", fieldToModify, fieldVal.String())
		fieldVal.SetString(newValue)
		fmt.Printf("필드 %s의 수정된 값: %s\n", fieldToModify, fieldVal.String())
	} else {
		fmt.Printf("필드 %s를 수정할 수 없습니다.\n", fieldToModify)
	}
}
