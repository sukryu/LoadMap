# 11. Go 에러 처리 (Error Handling)

## 1. Go의 에러 처리 개요

Go는 예외(Exception)를 지원하지 않으며, 대신 **에러(Error) 값을 반환하는 방식**을 사용합니다. 이 방식은 **명시적인 오류 처리를 가능하게 하고, 코드의 예측 가능성을 높이는 장점**이 있습니다.

```go
package main
import (
    "errors"
    "fmt"
)

func divide(a, b int) (int, error) {
    if b == 0 {
        return 0, errors.New("division by zero")
    }
    return a / b, nil
}

func main() {
    result, err := divide(10, 0)
    if err != nil {
        fmt.Println("Error:", err)
    } else {
        fmt.Println("Result:", result)
    }
}
```

- `errors.New("message")`: 새로운 에러 객체를 생성함.
- 함수가 `error` 타입을 반환하고, 호출자는 이를 확인하여 처리함.

---

## 2. `fmt.Errorf`를 활용한 에러 포맷팅
Go에서는 `fmt.Errorf`를 사용하여 포맷된 에러 메시지를 만들 수 있습니다.

```go
package main
import (
    "fmt"
)

func divide(a, b int) (int, error) {
    if b == 0 {
        return 0, fmt.Errorf("cannot divide %d by zero", a)
    }
    return a / b, nil
}

func main() {
    result, err := divide(10, 0)
    if err != nil {
        fmt.Println("Error:", err)
    } else {
        fmt.Println("Result:", result)
    }
}
```

- `fmt.Errorf`는 **포맷 문자열을 지원**하여 에러 메시지를 동적으로 생성할 수 있음.

---

## 3. 사용자 정의 에러 타입
고유한 에러 타입을 정의하여 보다 정교한 에러 처리를 할 수 있습니다.

```go
package main
import (
    "fmt"
)

type DivideError struct {
    Dividend int
    Divisor  int
}

func (e *DivideError) Error() string {
    return fmt.Sprintf("cannot divide %d by %d", e.Dividend, e.Divisor)
}

func divide(a, b int) (int, error) {
    if b == 0 {
        return 0, &DivideError{Dividend: a, Divisor: b}
    }
    return a / b, nil
}

func main() {
    _, err := divide(10, 0)
    if err != nil {
        fmt.Println("Error:", err)
    }
}
```

- `DivideError` 구조체는 `Error` 메서드를 구현하여 **Go의 표준 `error` 인터페이스를 만족**합니다.

---

## 4. `errors.Is`와 `errors.As` 활용
Go 1.13부터 도입된 `errors.Is`와 `errors.As`를 사용하면 에러의 유형을 검사할 수 있습니다.

### 4.1 `errors.Is` 사용 (특정 에러 비교)
```go
package main
import (
    "errors"
    "fmt"
)

var ErrNotFound = errors.New("not found")

func findItem(id int) error {
    if id != 1 {
        return ErrNotFound
    }
    return nil
}

func main() {
    err := findItem(2)
    if errors.Is(err, ErrNotFound) {
        fmt.Println("Item not found")
    }
}
```

- `errors.Is(err, target)`을 사용하면 특정 에러 값과 비교할 수 있음.

### 4.2 `errors.As` 사용 (에러 타입 변환)
```go
package main
import (
    "errors"
    "fmt"
)

type MyError struct {
    Msg string
}

func (e *MyError) Error() string {
    return e.Msg
}
}

func getError() error {
    return &MyError{Msg: "custom error"}
}

func main() {
    err := getError()
    var myErr *MyError
    if errors.As(err, &myErr) {
        fmt.Println("Caught MyError:", myErr.Msg)
    }
}
```

- `errors.As(err, &target)`을 사용하면 **에러 타입을 변환하여 추가적인 정보를 추출할 수 있음**.

---

## 5. `panic`과 `recover`를 활용한 예외 복구
일반적으로 Go는 `panic`을 자제하고 `error` 반환 방식을 사용하지만, **예상치 못한 심각한 에러를 처리**할 때 `panic`과 `recover`를 활용할 수 있습니다.

### 5.1 `panic` 사용 예제
```go
package main
import "fmt"

func riskyFunction() {
    panic("Something went wrong!")
}

func main() {
    fmt.Println("Start")
    riskyFunction()
    fmt.Println("End") // 실행되지 않음
}
```

- `panic("message")`을 호출하면 즉시 실행이 중단됨.

### 5.2 `recover`로 패닉 복구
`recover()`를 사용하면 패닉이 발생했을 때 프로그램이 종료되지 않도록 할 수 있습니다.

```go
package main
import "fmt"

func safeFunction() {
    defer func() {
        if r := recover(); r != nil {
            fmt.Println("Recovered from panic:", r)
        }
    }()
    panic("Critical error!")
}

func main() {
    fmt.Println("Start")
    safeFunction()
    fmt.Println("End") // 정상적으로 실행됨
}
```

- `defer` 안에서 `recover()`를 호출하면 패닉을 복구하고 프로그램을 계속 실행할 수 있음.

---

## 6. 결론
✅ Go는 **예외(Exception) 대신 명시적인 `error` 값을 반환하는 방식을 사용**하여 예측 가능한 코드 작성을 유도함.  
✅ `errors.New()`, `fmt.Errorf()`, `errors.Is()`, `errors.As()` 등을 활용하면 더욱 정교한 에러 처리가 가능함.  
✅ `panic`과 `recover`는 꼭 필요한 경우에만 사용하고, 일반적인 에러 처리는 `error` 값을 반환하는 방식으로 구현하는 것이 권장됨.  

다음으로 **Go의 테스팅(Testing)**에 대해 알아보겠습니다!

