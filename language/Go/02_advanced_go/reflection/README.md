# Reflection in Go 🔍

이 디렉토리는 Go의 **reflection** 기능을 심도 있게 다룹니다.  
Go의 `reflect` 패키지를 활용하여 런타임에 타입 정보를 확인하고, 동적으로 객체를 조작하는 방법을 학습할 수 있습니다.  
이를 통해 보다 유연한 라이브러리 개발, 데이터 검증, 직렬화/역직렬화 등의 다양한 응용 사례에 적용할 수 있습니다.

---

## What You'll Learn 🎯

- **Reflection 개념 이해**:  
  - 런타임에 타입과 값을 조사하는 방법
  - 변수, 구조체, 배열, 슬라이스 등 다양한 타입에 대한 정보 확인
- **reflect 패키지 사용법**:  
  - `reflect.Type`과 `reflect.Value`를 통해 객체의 메타데이터를 획득하는 법
  - 동적 메서드 호출, 필드 접근 및 수정
- **실무 활용 및 주의사항**:  
  - Reflection을 사용한 동적 처리 패턴
  - 성능 및 코드 가독성 측면에서의 고려사항

---

## 디렉토리 구조 📁

```plaintext
02-advanced-go/
└── reflection/
    ├── main.go        # 기본 reflection 예제 코드
    ├── examples/      # 추가 실습 예제 및 고급 활용 사례
    └── README.md      # 이 문서
```

- **main.go**: Go의 기본 reflection 기능을 실습할 수 있는 샘플 코드가 포함되어 있습니다.
- **examples/**: 다양한 시나리오(동적 메서드 호출, 필드 수정 등)를 다룬 추가 예제들을 제공합니다.

---

## Reflection in Go: 기본 개념

Reflection은 프로그램이 자신의 구조를 런타임에 조사하고 조작할 수 있도록 해줍니다. Go에서는 `reflect` 패키지를 통해 이를 수행하며, 주요 활용 예는 다음과 같습니다:

- **타입 및 값 검사**:  
  - 변수의 타입, 값, 구조체의 필드 등을 동적으로 확인
- **동적 메서드 호출**:  
  - 런타임에 결정된 메서드를 호출하거나, 필드 값을 수정할 수 있음
- **제네릭 프로그래밍**:  
  - 다양한 타입에 대해 공통적으로 처리하는 함수를 작성할 때 활용

---

## Example Code Snippet 📄

아래는 간단한 구조체의 필드와 타입 정보를 출력하는 예제입니다:

```go
package main

import (
    "fmt"
    "reflect"
)

type Person struct {
    Name string
    Age  int
}

func main() {
    p := Person{Name: "Alice", Age: 30}
    
    // reflect.Type과 reflect.Value를 통해 p의 타입과 값을 획득
    pType := reflect.TypeOf(p)
    pValue := reflect.ValueOf(p)
    
    fmt.Println("Type:", pType)
    fmt.Println("Value:", pValue)
    
    // 구조체의 각 필드에 대해 이름, 타입, 값을 출력
    for i := 0; i < pType.NumField(); i++ {
        field := pType.Field(i)
        value := pValue.Field(i)
        fmt.Printf("Field: %s, Type: %s, Value: %v\n", field.Name, field.Type, value)
    }
}
```

이 예제는 `Person` 구조체의 필드 정보를 동적으로 출력하는 간단한 사용법을 보여줍니다.

---

## Best Practices & Tips 💡

- **Reflection은 필요한 경우에만 사용하세요**:  
  - 코드 가독성과 성능에 영향을 줄 수 있으므로, 반드시 필요한 경우에 한해서 활용하세요.
  
- **유효성 검사**:  
  - `reflect.Value`가 유효하고 settable한지 항상 확인한 후, 수정 작업을 수행하세요.
  
- **성능 고려**:  
  - 직접적인 타입 선언이나 인터페이스 활용이 가능한 경우, 반영(reflection) 사용을 줄여 성능 저하를 방지하세요.
  
- **코드 유지보수**:  
  - reflection 코드는 디버깅이 어려울 수 있으므로, 충분한 주석과 테스트를 통해 코드를 명확하게 작성하세요.

---

## Next Steps

- **동적 메서드 호출**:  
  - reflection을 이용해 런타임에 메서드를 선택적으로 호출하는 예제를 작성해 보세요.
- **구조체 수정 및 복사**:  
  - 동적으로 구조체 필드 값을 수정하는 방법과, 이를 활용한 데이터 검증 로직을 구현해 보세요.
- **고급 활용 사례**:  
  - 데이터 직렬화, ORM, 혹은 의존성 주입 라이브러리와 같은 실제 응용 사례를 통해 reflection의 활용도를 높이세요.

Happy Reflecting! 🔍✨