/*
이 예제는 런타임에 동적으로 메서드를 호출하는 방법을 보여줍니다.
주요 기능:
1. 구조체에 정의된 메서드를 reflect 패키지를 사용해 동적으로 검색합니다.
2. 메서드 호출 시, 필요한 인수를 reflect.Value 슬라이스로 준비하여 동적 호출을 수행합니다.
3. 반환값을 확인하여, 호출 결과를 출력합니다.

예제에서는 Calculator 구조체를 정의하여, Add와 Multiply 메서드를 포함합니다.
이를 통해 동적으로 메서드를 선택하여 호출하고, 결과를 출력하는 과정을 상세한 주석과 함께 설명합니다.
*/

package main

import (
	"fmt"
	"reflect"
)

// Calculator는 두 정수를 연산하는 간단한 구조체입니다.
type Calculator struct {
	// 필드가 없지만, 메서드를 통해 연산 기능을 제공합니다.
}

// Add 메서드는 두 정수를 더한 결과를 반환합니다.
func (c Calculator) Add(a, b int) int {
	return a + b
}

// Multiply 메서드는 두 정수를 곱한 결과를 반환합니다.
func (c Calculator) Multiply(a, b int) int {
	return a * b
}

func main2() {
	// Calculator의 인스턴스 생성
	calc := Calculator{}

	// reflect.Value를 사용하여 calc의 값을 얻습니다.
	calcValue := reflect.ValueOf(calc)

	// 동적으로 호출할 메서드 이름을 설정합니다.
	// 예제에서는 "Add"와 "Multiply" 메서드를 호출합니다.
	methodNames := []string{"Add", "Multiply"}

	// 각 메서드에 대해 동적 호출을 수행합니다.
	for _, methodName := range methodNames {
		// MethodByName을 사용하여 메서드 심볼을 검색합니다.
		method := calcValue.MethodByName(methodName)
		if !method.IsValid() {
			fmt.Printf("메서드 %s를 찾을 수 없습니다.\n", methodName)
			continue
		}

		// 동적 메서드 호출을 위해 인수를 reflect.Value 슬라이스로 준비합니다.
		// 예제에서는 두 정수 인수를 전달합니다.
		args := []reflect.Value{reflect.ValueOf(10), reflect.ValueOf(5)}

		// 메서드 호출: Call 메서드를 통해 동적으로 인수를 전달하고 호출합니다.
		resultValues := method.Call(args)

		// 반환값 처리: 이 예제의 메서드들은 단일 int 값을 반환합니다.
		if len(resultValues) > 0 {
			result := resultValues[0].Interface()
			fmt.Printf("메서드 %s(%d, %d) 호출 결과: %v\n", methodName, 10, 5, result)
		} else {
			fmt.Printf("메서드 %s는 반환값이 없습니다.\n", methodName)
		}
	}

	// 추가: 메서드 동적 호출의 응용 예제
	// 예를 들어, 런타임에 메서드 이름을 사용자 입력 등으로 받아서 호출할 수 있습니다.
	// 아래는 "Add" 메서드를 동적으로 호출하는 예제입니다.
	userMethodName := "Add"
	userArgs := []reflect.Value{reflect.ValueOf(7), reflect.ValueOf(3)}
	userMethod := calcValue.MethodByName(userMethodName)
	if userMethod.IsValid() {
		results := userMethod.Call(userArgs)
		fmt.Printf("사용자 지정 메서드 %s(7, 3) 호출 결과: %v\n", userMethodName, results[0].Interface())
	} else {
		fmt.Printf("사용자 지정 메서드 %s를 찾을 수 없습니다.\n", userMethodName)
	}
}
