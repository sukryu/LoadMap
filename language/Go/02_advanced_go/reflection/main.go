/*
이 예제는 Go의 reflection 기능을 심도 있게 다룹니다.
주요 기능:
1. 구조체의 타입과 값 정보 조사:
   - reflect.Type과 reflect.Value를 통해 변수의 메타데이터(필드 이름, 타입, 값 등)를 확인합니다.
2. 동적 메서드 호출:
   - 런타임에 결정된 메서드를 호출하여, 동적 기능 확장을 구현할 수 있습니다.
3. 동적 필드 수정:
   - settable한 reflect.Value를 통해 구조체 필드 값을 동적으로 변경하는 방법을 보여줍니다.
4. 슬라이스 및 기타 데이터 타입의 reflection 활용:
   - 슬라이스의 길이, 용량, 요소 접근 등의 정보를 확인하고, 값을 수정하는 예제를 포함합니다.
*/

package main

import (
	"fmt"
	"reflect"
)

// Person 구조체는 reflection 예제에 사용할 데이터 타입입니다.
type Person struct {
	Name string
	Age  int
}

// Greet 메서드는 Person의 인스턴스가 인사 메시지를 출력하는 메서드입니다.
func (p Person) Greet(greeting string) {
	fmt.Printf("%s, I'm %s and I'm %d years old.\n", greeting, p.Name, p.Age)
}

func main() {
	// 1. Person 구조체 인스턴스 생성
	p := Person{Name: "Alice", Age: 30}

	// reflect.Type과 reflect.Value를 사용해 p의 메타데이터를 얻습니다.
	pType := reflect.TypeOf(p)
	pValue := reflect.ValueOf(p)

	fmt.Println("== Reflection Example: Inspecting a Person Struct ==")
	fmt.Println("Type:", pType)
	fmt.Println("Value:", pValue)

	// 2. 구조체 필드 정보 출력: 각 필드의 이름, 타입, 값 확인
	fmt.Println("\n-- Struct Fields --")
	for i := 0; i < pType.NumField(); i++ {
		field := pType.Field(i)
		value := pValue.Field(i)
		fmt.Printf("Field %d: %s (Type: %s) = %v\n", i, field.Name, field.Type, value)
	}

	// 3. 동적 메서드 호출: Greet 메서드를 런타임에 호출
	fmt.Println("\n-- Dynamic Method Invocation --")
	// pValue에서 "Greet" 메서드 심볼을 찾습니다.
	greetMethod := pValue.MethodByName("Greet")
	if greetMethod.IsValid() {
		// 메서드 호출 시 필요한 인수를 reflect.Value 슬라이스로 준비합니다.
		args := []reflect.Value{reflect.ValueOf("Hello")}
		fmt.Println("Calling method Greet dynamically:")
		greetMethod.Call(args)
	} else {
		fmt.Println("Method 'Greet' not found!")
	}

	// 4. 동적 필드 수정: 구조체의 Name 필드를 변경합니다.
	fmt.Println("\n-- Modifying a Field Dynamically --")
	// p의 포인터를 사용하여 settable한 reflect.Value를 얻습니다.
	pPtr := &p
	pValuePtr := reflect.ValueOf(pPtr).Elem() // settable
	nameField := pValuePtr.FieldByName("Name")
	if nameField.IsValid() && nameField.CanSet() {
		fmt.Printf("Original Name: %v\n", nameField.Interface())
		// Name 필드를 "Bob"으로 변경합니다.
		nameField.SetString("Bob")
		fmt.Printf("Modified Name: %v\n", nameField.Interface())
	} else {
		fmt.Println("Cannot modify field 'Name'")
	}

	// 5. 구조체의 메서드 목록 출력: 해당 구조체가 제공하는 메서드들 확인
	fmt.Println("\n-- Listing Methods of Person --")
	for i := 0; i < pType.NumMethod(); i++ {
		method := pType.Method(i)
		fmt.Printf("Method %d: %s (Type: %s)\n", i, method.Name, method.Type)
	}

	// 6. 슬라이스에 대한 reflection 활용: 슬라이스 정보 확인 및 수정
	fmt.Println("\n-- Reflection with a Slice --")
	nums := []int{10, 20, 30, 40, 50}
	numsValue := reflect.ValueOf(nums)
	fmt.Printf("Slice Value: %v, Type: %s, Length: %d, Capacity: %d\n",
		numsValue, numsValue.Type(), numsValue.Len(), numsValue.Cap())

	// 슬라이스 요소를 수정하기 위해서는 settable한 값이 필요합니다.
	// 이를 위해 슬라이스의 포인터를 사용합니다.
	numsPtr := &nums
	numsValueSet := reflect.ValueOf(numsPtr).Elem()
	// 첫 번째 요소를 100으로 변경합니다.
	if numsValueSet.Index(0).CanSet() {
		fmt.Printf("Original first element: %d\n", numsValueSet.Index(0).Int())
		numsValueSet.Index(0).SetInt(100)
		fmt.Printf("Modified first element: %d\n", numsValueSet.Index(0).Int())
	} else {
		fmt.Println("Cannot modify slice element")
	}

	fmt.Println("\nReflection demo complete.")
}
