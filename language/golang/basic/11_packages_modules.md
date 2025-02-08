# 10. Go 패키지와 모듈 (Packages and Modules)

## 1. 패키지(Packages)

### 1.1 패키지란?
Go의 패키지는 코드의 재사용성을 높이고, 모듈화를 통해 유지보수성을 개선하는 기능을 합니다. 모든 Go 프로그램은 **패키지 단위**로 구성됩니다.

### 1.2 패키지 선언
모든 Go 소스 파일의 최상단에는 `package` 선언이 있어야 합니다.

```go
package main // 실행 가능한 프로그램은 반드시 main 패키지를 사용해야 함.

import "fmt"

func main() {
    fmt.Println("Hello, Go!")
}
```

- `package main`: 실행 가능한 프로그램은 `main` 패키지를 사용해야 합니다.
- `import "fmt"`: 표준 패키지를 가져와서 사용합니다.

---

### 1.3 사용자 정의 패키지 만들기
#### **패키지 폴더 구조**
```plaintext
myproject/
├── main.go
├── greetings/
│   ├── greetings.go
│   └── greetings_test.go
```

#### **패키지 생성 (greetings.go)**
```go
package greetings

import "fmt"

func Hello(name string) string {
    return fmt.Sprintf("Hello, %s!", name)
}
```

#### **패키지 사용 (main.go)**
```go
package main

import (
    "fmt"
    "myproject/greetings"
)

func main() {
    fmt.Println(greetings.Hello("Alice"))
}
```

- 패키지를 **폴더 이름**과 동일하게 만들어야 합니다.
- `import "myproject/greetings"`을 통해 패키지를 불러올 수 있습니다.

---

## 2. 모듈(Modules)

### 2.1 Go 모듈이란?
Go 모듈은 **Go 프로젝트의 의존성을 관리**하는 시스템으로, `go.mod` 파일을 사용합니다.

### 2.2 Go 모듈 생성
Go 프로젝트의 루트 디렉토리에서 다음 명령어를 실행합니다.
```sh
go mod init myproject
```

이렇게 하면 `go.mod` 파일이 생성됩니다:
```mod
go module myproject

go 1.18
```

### 2.3 외부 패키지 사용
Go에서는 외부 패키지를 가져올 수 있습니다. 예를 들어 `rsc.io/quote` 패키지를 설치하려면:
```sh
go get rsc.io/quote
```

그런 다음 코드에서 사용합니다.
```go
package main

import (
    "fmt"
    "rsc.io/quote"
)

func main() {
    fmt.Println(quote.Hello())
}
```

### 2.4 의존성 관리
Go 모듈 시스템은 자동으로 의존성을 관리합니다.
- `go list -m all` → 현재 프로젝트의 모든 모듈 확인
- `go mod tidy` → 사용하지 않는 의존성 제거
- `go mod vendor` → 의존성을 `vendor/` 디렉토리에 저장

---

## 3. 내장 패키지 활용
Go는 다양한 내장 패키지를 제공합니다.

### 3.1 `fmt`: 입출력 처리
```go
import "fmt"
fmt.Println("Hello, Go!")
```

### 3.2 `math`: 수학 연산
```go
import "math"
fmt.Println(math.Sqrt(16)) // 4
```

### 3.3 `time`: 시간 관련 처리
```go
import "time"
fmt.Println(time.Now())
```

---

## 4. 모듈 버전 관리

### 4.1 특정 버전의 모듈 설치
```sh
go get example.com/mylib@v1.2.3
```

### 4.2 최신 버전으로 업데이트
```sh
go get -u example.com/mylib
```

### 4.3 특정 버전의 모듈 제거
```sh
go mod tidy
```

---

## 5. 패키지와 모듈의 차이

| 항목  | 패키지 (Package) | 모듈 (Module) |
|-------|----------------|--------------|
| 역할  | 코드 조직화   | 의존성 관리 |
| 정의  | 폴더 단위로 관리 | `go.mod` 파일로 관리 |
| 예시  | `import "fmt"` | `go get example.com/lib` |

---

## 6. 결론
- **패키지**는 코드를 모듈화하여 재사용 가능하게 함.
- **모듈**은 프로젝트의 의존성을 관리하는 시스템.
- Go 모듈을 사용하면 **의존성을 자동으로 관리하고, 버전 관리를 쉽게 할 수 있음.**

다음으로 **Go의 에러 처리(Error Handling)**에 대해 알아보겠습니다!

