# Unsafe in Go: Low-Level Memory Access ⚠️

이 디렉토리는 Go의 `unsafe` 패키지를 활용하여, 저수준 메모리 접근 및 포인터 조작 등 고급 시스템 프로그래밍 기법을 학습하는 데 중점을 둡니다.  
`unsafe`는 일반적인 Go 코드에서는 피해야 하지만, 성능 최적화나 특정 시스템 작업에서 반드시 필요한 경우에 활용됩니다.

---

## What You'll Learn 🎯

- **Unsafe 패키지 기본 개념**:  
  - Go의 타입 안전성을 우회하는 방법 및 메모리 모델 이해
- **포인터와 메모리 주소**:  
  - 포인터 연산, 메모리 주소 변환, 구조체 메모리 배치 등을 학습합니다.
- **타입 변환**:  
  - 안전하지 않은 타입 변환을 통해, 데이터를 직접 조작하는 방법을 익힙니다.
- **실무 활용 및 주의사항**:  
  - `unsafe` 사용 시 고려해야 할 성능, 코드 가독성, 안정성 문제와 Best Practice

---

## 디렉토리 구조 📁

```plaintext
02-advanced-go/
└── unsafe/
    ├── main.go         # unsafe 패키지 기본 사용 예제
    ├── examples/       # 추가 실습 예제 및 다양한 사용 사례
    └── README.md       # 이 문서
```

- **main.go**: `unsafe` 패키지를 사용하여 메모리 주소 접근 및 타입 변환을 시연하는 기본 예제 코드가 포함되어 있습니다.
- **examples/**: 포인터 산술, 구조체 메모리 레이아웃, 고급 변환 예제 등 다양한 시나리오를 다룹니다.

---

## Getting Started 🚀

### 1. 필수 도구 설치
- 최신 Go 버전: [Download Go](https://go.dev/dl/)

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/02-advanced-go/unsafe
```

### 3. 예제 코드 실행
```bash
go run main.go
```
- 실행 결과를 확인하며, `unsafe`를 통한 메모리 접근 방식을 직접 체험해 보세요.

---

## Example Code Snippet 📄

아래는 간단한 예제 코드로, `unsafe`를 사용하여 변수의 메모리 주소를 확인하고 타입 변환을 수행하는 예제입니다:

```go
package main

import (
    "fmt"
    "unsafe"
)

func main() {
    // 변수 선언 및 주소 확인
    x := 42
    fmt.Println("Value of x:", x)
    fmt.Println("Address of x:", &x)

    // unsafe.Pointer를 사용하여 주소를 uintptr로 변환
    ptr := unsafe.Pointer(&x)
    addr := uintptr(ptr)
    fmt.Printf("Address as uintptr: %x\n", addr)

    // uintptr를 다시 unsafe.Pointer로 변환 후, int 포인터로 변환하여 값 확인
    newPtr := (*int)(unsafe.Pointer(addr))
    fmt.Println("Value at new pointer:", *newPtr)

    // 구조체의 메모리 배치를 확인하는 예제
    type MyStruct struct {
        a int32
        b int64
    }
    s := MyStruct{a: 10, b: 20}
    fmt.Println("Size of MyStruct:", unsafe.Sizeof(s))
    fmt.Printf("Offset of a: %d, b: %d\n", unsafe.Offsetof(s.a), unsafe.Offsetof(s.b))
}
```

이 예제는:
- 변수 `x`의 메모리 주소를 안전하지 않은 방식으로 변환하는 과정을 보여주고,
- 구조체의 필드 배치를 확인하여, 메모리 정렬과 패딩의 개념을 이해하는 데 도움이 됩니다.

---

## Best Practices & Tips 💡

- **최소한으로 사용하기**:  
  - `unsafe`는 Go의 타입 안전성을 우회하므로, 반드시 필요한 경우에만 사용하세요.
- **코드 가독성 유지**:  
  - `unsafe`를 사용할 때는 주석과 문서화를 통해, 왜 사용했는지 명확하게 설명해야 합니다.
- **성능 고려**:  
  - 성능 최적화를 위해 `unsafe`를 사용할 때, 실제 성능 개선 효과를 측정하고, 안정성 테스트를 충분히 수행하세요.
- **보안 주의**:  
  - 잘못된 메모리 접근은 예기치 않은 버그나 보안 취약점을 유발할 수 있으므로, 사용 시 매우 주의해야 합니다.

---

## Next Steps

- **심화 실습**:  
  - 예제 코드를 기반으로 다양한 구조체의 메모리 배치 및 포인터 산술을 실습해 보세요.
- **고급 활용 사례**:  
  - 성능 최적화, 캐시 라인 정렬, 또는 저수준 시스템 인터페이스 구현 시 `unsafe`를 어떻게 적용할 수 있는지 연구해 보세요.

Happy Unsafe Coding! ⚠️✨