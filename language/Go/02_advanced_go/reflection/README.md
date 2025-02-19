# Reflection in Go 🔍

이 디렉토리는 Go의 **reflection** 기능을 심도 있게 다룹니다.  
Go의 `reflect` 패키지를 활용하여 런타임에 타입 정보를 확인하고, 동적으로 객체를 조작하는 방법을 학습할 수 있습니다.  
이를 통해 보다 유연한 라이브러리 개발, 데이터 검증, 직렬화/역직렬화, 동적 메서드 호출 및 필드 수정 등 다양한 응용 사례에 적용할 수 있습니다.

---

## What You'll Learn 🎯

- **Reflection 개념 이해**:  
  - 런타임에 변수와 객체의 타입 및 값을 조사하는 방법
  - 구조체, 배열, 슬라이스, 맵 등 다양한 데이터 타입의 메타데이터를 확인하는 법

- **reflect 패키지 사용법**:  
  - `reflect.Type`과 `reflect.Value`를 통해 객체의 내부 정보를 획득하는 방법
  - 동적 메서드 호출, 필드 접근 및 수정, 태그 추출 등 다양한 활용 기법

- **Reflection 유틸리티 구현**:  
  - 깊은 복사(Deep Copy), 동적 타입 변환, 구조체 상세 정보 출력 등 재사용 가능한 유틸리티 함수 개발

- **성능 및 최적화 고려사항**:  
  - Reflection 사용 시 발생하는 성능 오버헤드와 이를 완화하기 위한 캐싱 전략 등
  - Reflection 사용의 비용과 적절한 사용 시점을 이해

- **실무 활용 및 주의사항**:  
  - 동적 처리 패턴, 데이터 검증, 직렬화/역직렬화, ORM, 의존성 주입 등 실제 응용 사례
  - Reflection 사용 시 코드 가독성, 디버깅, 보안 및 성능 측면의 고려사항

---

## 디렉토리 구조 📁

```plaintext
02-advanced-go/
└── reflection/
    ├── main.go               # 기본 reflection 예제 코드
    ├── examples/             # 추가 실습 예제 및 고급 활용 사례
    │   ├── 01_basic_reflection.go         # 기본 변수, 구조체, 배열, 슬라이스, 맵 등 기본 reflection 사용법
    │   ├── 02_dynamic_method_invocation.go  # 런타임 동적 메서드 호출 예제
    │   ├── 03_field_modification.go         # 구조체 필드 동적 수정 예제
    │   ├── 04_struct_tag_extraction.go        # 구조체 태그 정보 추출 예제
    │   ├── 05_advanced_data_structures.go     # 복합 데이터 구조(배열, 슬라이스, 맵) reflection 활용 예제
    │   ├── 06_reflection_utilities.go         # DeepCopy, DynamicTypeConvert, PrintStructDetails 등 유틸리티 함수
    │   ├── 07_performance_considerations.go     # Reflection 사용 성능 측정 및 캐싱 최적화 예제
    │   └── 08_reflection_in_validation.go       # 태그 기반 데이터 검증 예제
    └── README.md               # 이 문서
```

- **main.go**: Go의 기본 reflection 기능을 실습할 수 있는 샘플 코드가 포함되어 있습니다.
- **examples/**: 기본 사용법부터 동적 메서드 호출, 필드 수정, 태그 추출, 복합 데이터 구조 처리, 유틸리티 함수, 성능 최적화, 그리고 데이터 검증 등 다양한 시나리오를 다룬 추가 예제들을 제공합니다.

---

## Reflection in Go: 기본 개념

Reflection은 프로그램이 자신의 구조를 런타임에 조사하고 조작할 수 있도록 해줍니다. Go에서는 `reflect` 패키지를 통해 이를 수행하며, 주요 활용 예는 다음과 같습니다:

- **타입 및 값 검사**:  
  - 변수의 타입, 값, 구조체 필드 및 메서드 정보를 동적으로 확인

- **동적 메서드 호출 및 필드 수정**:  
  - 런타임에 결정된 메서드를 호출하거나, 필드 값을 변경하여 유연한 로직을 구현

- **메타데이터 활용**:  
  - 구조체 태그를 읽어 데이터 검증, 직렬화/역직렬화, ORM, 의존성 주입 등 다양한 응용 사례에 적용

- **유틸리티 함수 개발**:  
  - 깊은 복사(Deep Copy), 동적 타입 변환 등 반복적으로 필요한 기능을 재사용 가능한 함수로 구현

---

## Getting Started 🚀

### 1. 필수 도구 설치
- 최신 Go 버전: [Download Go](https://go.dev/dl/)

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/02-advanced-go/reflection
```

### 3. 예제 코드 실행
```bash
go run main.go
```
- 실행 결과를 확인하며, reflection의 다양한 기능을 직접 실습해 보세요.

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

---

## Best Practices & Tips 💡

- **Reflection은 필요한 경우에만 사용하세요**:  
  - 코드 가독성과 성능에 영향을 줄 수 있으므로, 반드시 필요한 경우에 한해서 활용하세요.
  
- **유효성 검사**:  
  - `reflect.Value`가 유효하고 settable한지 항상 확인한 후, 수정 작업을 수행하세요.
  
- **성능 고려**:  
  - 직접적인 타입 선언이나 인터페이스 활용이 가능한 경우, reflection 사용을 최소화하여 성능 저하를 방지하세요.
  
- **코드 유지보수**:  
  - Reflection 코드는 디버깅이 어려울 수 있으므로, 충분한 주석과 테스트를 통해 코드를 명확하게 작성하세요.
  
- **유틸리티 함수 활용**:  
  - 반복적으로 사용되는 reflection 로직은 재사용 가능한 유틸리티 함수로 구현하여 코드 중복을 줄이세요.

---

## Next Steps

- **동적 메서드 호출**:  
  - reflection을 이용해 런타임에 메서드를 선택적으로 호출하는 예제를 작성해 보세요.
- **구조체 수정 및 복사**:  
  - 동적으로 구조체 필드 값을 수정하거나 깊은 복사를 수행하는 유틸리티 함수를 개발해 보세요.
- **고급 활용 사례**:  
  - 데이터 직렬화, ORM, 의존성 주입 라이브러리 등 실제 응용 사례를 통해 reflection의 활용도를 높이세요.
- **성능 최적화**:  
  - Reflection 사용 시 발생하는 오버헤드를 측정하고, 캐싱 등 최적화 기법을 적용해 보세요.

Happy Reflecting! 🔍✨