# Go Syntax Fundamentals 🔤

이 디렉토리는 Go 언어의 **기본 문법**을 익히기 위한 자료와 예제들을 제공합니다.  
여기서는 변수 선언, 데이터 타입, 제어문, 함수, 패키지 구조 등 Go의 기초적인 구문을 학습하여, Go 개발의 기초를 탄탄히 다질 수 있도록 구성되어 있습니다.

---

## What You'll Learn 🎯

- **변수 및 상수 선언**:  
  Go에서 변수와 상수를 선언하고 초기화하는 다양한 방법을 익힙니다.
  
- **데이터 타입**:  
  정수, 부동소수점, 불린, 문자열, 배열, 슬라이스, 맵, 구조체 등 기본 데이터 타입을 다룹니다.
  
- **제어 흐름**:  
  조건문 (`if`, `switch`)과 반복문 (`for`) 등 기본 제어문을 사용하여 로직을 작성하는 방법을 학습합니다.
  
- **함수**:  
  함수 선언, 인자와 반환값, 가변 인자 함수 등을 통한 함수 작성법을 익힙니다.
  
- **패키지와 모듈**:  
  Go의 패키지 구조와 모듈 관리 방식을 이해하여, 프로젝트를 체계적으로 구성하는 방법을 배웁니다.

---

## 디렉토리 구조 📁

```plaintext
01-go-basics/
└── syntax/
    ├── main.go        # 예제 코드: 기본 문법 시연
    ├── examples/      # 추가 연습 예제 (선택 사항)
    └── README.md      # 이 문서
```

- **main.go**: Go의 기본 문법을 직접 실습할 수 있는 샘플 코드가 포함되어 있습니다.
- **examples/**: 추가적인 연습 문제 및 코드 예제들이 모여 있습니다 (필요 시 활용).

---

## Getting Started 🚀

1. **Go 설치 확인**  
   Go가 설치되어 있지 않다면 [Go Downloads](https://go.dev/dl/)에서 최신 버전을 설치하세요.

2. **프로젝트 클론 및 디렉토리 이동**
   ```bash
   git clone https://github.com/your-username/go-backend-roadmap.git
   cd go-backend-roadmap/01-go-basics/syntax
   ```

3. **샘플 코드 실행**
   ```bash
   go run main.go
   ```
   - 콘솔에 출력되는 결과를 통해 기본 문법이 어떻게 동작하는지 확인하세요.

---

## Example Code Snippet 📄

아래는 간단한 Go 예제 코드입니다:
```go
package main

import "fmt"

func main() {
    // 변수 선언 및 초기화
    var message string = "Hello, Go!"
    fmt.Println(message)

    // 짧은 변수 선언
    number := 42
    fmt.Println("Number:", number)

    // 조건문
    if number > 10 {
        fmt.Println("The number is greater than 10")
    } else {
        fmt.Println("The number is 10 or less")
    }

    // 반복문
    for i := 0; i < 5; i++ {
        fmt.Printf("Iteration %d\n", i)
    }
}
```

---

## 학습 팁 💡

- **실습 중심 학습**: 예제 코드를 수정하고 확장해보며, 다양한 구문을 직접 체험해 보세요.
- **참고 자료 활용**: [Go 공식 문서](https://go.dev/doc/)와 관련 서적을 통해 더 깊은 이해를 얻으세요.
- **작은 프로그램 작성**: 간단한 프로젝트를 통해 배운 개념들을 실제로 적용해 보세요.

---

## Next Steps

- 기본 문법을 충분히 숙지한 후, [concurrency](../concurrency/README.md) 디렉토리로 넘어가 Go의 동시성 프로그래밍을 학습하세요.
- 실습을 통해 이해도를 높이고, 코드 리뷰 및 토론을 통해 개선점을 찾아보세요.

Happy Coding! 🎉