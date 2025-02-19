/*
이 예제는 Go의 reflect 패키지를 사용하여 기본적인 reflection 기능을 체험합니다.
주요 기능:
1. 변수의 타입과 값 조사: reflect.TypeOf와 reflect.ValueOf를 사용하여 변수의 메타데이터를 확인합니다.
2. 구조체 필드 정보 출력: 구조체의 각 필드 이름, 타입, 값을 동적으로 조회합니다.
3. 구조체의 메서드 목록 출력: 해당 구조체가 제공하는 메서드들을 나열합니다.
4. 다양한 데이터 타입에 대한 reflection 활용: 기본 자료형 및 복합 데이터 타입에 대해 동적으로 정보를 추출하는 방법을 보여줍니다.

이 예제를 통해 reflection의 기본 사용법을 이해하고, 나아가 동적 프로그래밍, 데이터 검증, 직렬화/역직렬화 등 다양한 응용 사례에 활용할 수 있습니다.
*/

package main

import (
	"fmt"
	"reflect"
)

// Person 구조체는 reflection 예제에 사용할 기본 구조체입니다.
type Person struct {
	Name    string  // 사람의 이름
	Age     int     // 나이
	Salary  float64 // 급여 정보
	Married bool    // 결혼 여부
}

// Greet 메서드는 Person 구조체에 정의된 메서드로, 인사 메시지를 출력합니다.
func (p Person) Greet(greeting string) {
	fmt.Printf("%s! My name is %s, I am %d years old.\n", greeting, p.Name, p.Age)
}

func main1() {
	// 1. 기본 변수에 대한 reflection 예제
	fmt.Println("=== 기본 변수에 대한 Reflection 예제 ===")
	x := 42
	// reflect.TypeOf를 사용하여 변수의 타입 정보를 얻습니다.
	xType := reflect.TypeOf(x)
	// reflect.ValueOf를 사용하여 변수의 값을 감싸는 객체를 얻습니다.
	xValue := reflect.ValueOf(x)
	fmt.Printf("변수 x의 값: %v, 타입: %s\n", xValue, xType)
	fmt.Println()

	// 2. Person 구조체 인스턴스 생성 및 타입/값 조사
	fmt.Println("=== Person 구조체에 대한 Reflection 예제 ===")
	// Person 구조체의 인스턴스 생성
	p := Person{Name: "Alice", Age: 30, Salary: 75000.50, Married: true}
	// 변수 p의 타입과 값을 reflection을 통해 얻습니다.
	pType := reflect.TypeOf(p)
	pValue := reflect.ValueOf(p)
	fmt.Printf("p의 타입: %s\n", pType)
	fmt.Printf("p의 값: %v\n", pValue)
	fmt.Println()

	// 3. 구조체 필드 정보 출력
	fmt.Println("=== 구조체 필드 정보 출력 ===")
	// pType.NumField()를 사용해 구조체의 필드 수를 얻습니다.
	for i := 0; i < pType.NumField(); i++ {
		// Field(i)를 통해 각 필드의 정보를 가져옵니다.
		field := pType.Field(i)
		// pValue.Field(i)를 통해 필드의 값을 가져옵니다.
		value := pValue.Field(i)
		fmt.Printf("필드 %d: 이름=%s, 타입=%s, 값=%v\n", i, field.Name, field.Type, value)
	}
	fmt.Println()

	// 4. 구조체 메서드 목록 출력
	fmt.Println("=== 구조체 메서드 목록 출력 ===")
	// pType.NumMethod()를 사용해 구조체에 정의된 메서드의 수를 확인합니다.
	for i := 0; i < pType.NumMethod(); i++ {
		method := pType.Method(i)
		fmt.Printf("메서드 %d: 이름=%s, 시그니처=%s\n", i, method.Name, method.Type)
	}
	fmt.Println()

	// 5. 동적 메서드 호출
	fmt.Println("=== 동적 메서드 호출 예제 ===")
	// pValue.MethodByName을 통해 "Greet" 메서드 심볼을 찾아 호출합니다.
	greetMethod := pValue.MethodByName("Greet")
	if greetMethod.IsValid() {
		// 호출 시 필요한 인수는 reflect.Value 슬라이스로 준비합니다.
		args := []reflect.Value{reflect.ValueOf("Hello")}
		fmt.Println("동적으로 Greet 메서드를 호출합니다:")
		greetMethod.Call(args)
	} else {
		fmt.Println("Greet 메서드를 찾을 수 없습니다.")
	}
	fmt.Println()

	// 6. 다양한 데이터 타입에 대한 reflection 활용
	fmt.Println("=== 기본 데이터 타입과 복합 데이터 타입의 Reflection ===")
	// 배열 예제
	arr := [5]int{10, 20, 30, 40, 50}
	arrValue := reflect.ValueOf(arr)
	fmt.Printf("배열 값: %v, 타입: %s, 길이: %d\n", arrValue, arrValue.Type(), arrValue.Len())
	// 슬라이스 예제
	slice := []string{"apple", "banana", "cherry"}
	sliceValue := reflect.ValueOf(slice)
	fmt.Printf("슬라이스 값: %v, 타입: %s, 길이: %d, 용량: %d\n",
		sliceValue, sliceValue.Type(), sliceValue.Len(), sliceValue.Cap())

	// 맵 예제
	m := map[string]int{"one": 1, "two": 2, "three": 3}
	mapValue := reflect.ValueOf(m)
	fmt.Printf("맵 값: %v, 타입: %s, 길이: %d\n", mapValue, mapValue.Type(), mapValue.Len())

	fmt.Println("\nReflection 기본 예제 데모 종료.")
}
