/*
이 예제는 Go의 reflection 기능을 사용하여 구조체에 지정된 태그 정보를 추출하는 방법을 보여줍니다.
주요 기능:
1. 사용자 정의 태그가 포함된 구조체를 정의합니다.
2. reflect.TypeOf를 통해 구조체의 메타데이터를 조회하고, 각 필드에 할당된 태그 값을 추출합니다.
3. 추출된 태그 정보를 활용하여 데이터 검증, 직렬화, ORM 등 다양한 응용 사례에 적용할 수 있는 기초를 마련합니다.

이 예제는 실제 업무에서 구조체의 태그를 분석하여 동적으로 처리할 때 유용하게 사용할 수 있습니다.
*/

package main

import (
	"fmt"
	"reflect"
)

// User 구조체는 다양한 태그를 포함하여 정의됩니다.
// json 태그는 직렬화에 사용되고, db 태그는 데이터베이스 매핑, validate 태그는 데이터 검증에 사용됩니다.
type User struct {
	ID    int    `json:"id" db:"user_id" validate:"required"`
	Name  string `json:"name" db:"user_name" validate:"min=3,max=50"`
	Email string `json:"email" db:"user_email" validate:"email"`
	Age   int    `json:"age" validate:"gte=0,lte=120"`
}

func main4() {
	fmt.Println("=== Struct Tag Extraction Demo ===")

	// User 구조체의 인스턴스 생성
	user := User{
		ID:    1,
		Name:  "Alice",
		Email: "alice@example.com",
		Age:   30,
	}

	// reflect.TypeOf를 사용하여 user 변수의 타입 정보를 얻습니다.
	// 이는 구조체의 모든 필드와 해당 태그 정보를 포함합니다.
	userType := reflect.TypeOf(user)

	// 구조체의 필드 수 만큼 반복하면서 각 필드의 태그 정보를 출력합니다.
	for i := 0; i < userType.NumField(); i++ {
		field := userType.Field(i)
		fmt.Printf("Field: %s\n", field.Name)
		fmt.Printf("  Type: %s\n", field.Type)

		// 각 태그 값을 추출합니다.
		// json 태그는 데이터를 JSON 형식으로 직렬화할 때 사용됩니다.
		jsonTag := field.Tag.Get("json")
		// db 태그는 데이터베이스 매핑에 활용됩니다.
		dbTag := field.Tag.Get("db")
		// validate 태그는 데이터 검증 규칙을 정의하는 데 사용됩니다.
		validateTag := field.Tag.Get("validate")

		fmt.Printf("  json tag: %s\n", jsonTag)
		if dbTag != "" {
			fmt.Printf("  db tag: %s\n", dbTag)
		}
		if validateTag != "" {
			fmt.Printf("  validate tag: %s\n", validateTag)
		}
		fmt.Println()
	}

	fmt.Println("=== Struct Tag Extraction Demo Complete ===")
}
