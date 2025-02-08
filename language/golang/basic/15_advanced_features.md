# 14. 최신 기능과 고급 활용 (Advanced Go Features)

## 1. 최신 Go 기능 개요
Go는 지속적으로 발전하며 성능 개선 및 새로운 기능을 추가하고 있습니다. Go 1.18 이후부터 **제네릭(Generic)**, **Fuzzing 테스트**, **Workspaces** 등 다양한 기능이 도입되었습니다.

---

## 2. 제네릭(Generics) 심화

### 2.1 제네릭을 사용한 유연한 함수
Go 1.18부터 도입된 **제네릭**을 활용하면 타입을 일반화하여 코드 재사용성을 높일 수 있습니다.

```go
package main
import "fmt"

type Number interface {
    int | float64
}

func Sum[T Number](a, b T) T {
    return a + b
}

func main() {
    fmt.Println(Sum(3, 4))      // 정수 연산
    fmt.Println(Sum(3.5, 2.1))  // 실수 연산
}
```

### 2.2 제네릭을 활용한 데이터 구조
```go
type Stack[T any] struct {
    elements []T
}

func (s *Stack[T]) Push(value T) {
    s.elements = append(s.elements, value)
}

func (s *Stack[T]) Pop() (T, bool) {
    if len(s.elements) == 0 {
        var zeroValue T
        return zeroValue, false
    }
    val := s.elements[len(s.elements)-1]
    s.elements = s.elements[:len(s.elements)-1]
    return val, true
}

func main() {
    var intStack Stack[int]
    intStack.Push(10)
    intStack.Push(20)
    fmt.Println(intStack.Pop()) // (20, true)
}
```

> 제네릭을 사용하면 **타입 안전성을 유지하면서도 다양한 데이터 구조를 재사용할 수 있음**.

---

## 3. Fuzzing 테스트

### 3.1 Fuzzing이란?
Go 1.18부터 **Fuzzing(퍼징) 테스트**를 공식적으로 지원합니다. 이는 랜덤한 입력값을 생성하여 프로그램의 안정성을 테스트하는 기법입니다.

### 3.2 Fuzzing 예제
```go
package main
import (
    "errors"
    "testing"
)

func Reverse(s string) (string, error) {
    if len(s) == 0 {
        return "", errors.New("empty string")
    }
    r := []rune(s)
    for i, j := 0, len(r)-1; i < j; i, j = i+1, j-1 {
        r[i], r[j] = r[j], r[i]
    }
    return string(r), nil
}

func FuzzReverse(f *testing.F) {
    testcases := []string{"hello", "world", "golang"}
    for _, tc := range testcases {
        f.Add(tc)
    }
    f.Fuzz(func(t *testing.T, input string) {
        _, err := Reverse(input)
        if err != nil {
            t.Errorf("Unexpected error: %v", err)
        }
    })
}
```

> `go test -fuzz=FuzzReverse` 명령어로 실행 가능하며, 다양한 입력값에 대해 함수의 안정성을 테스트함.

---

## 4. Workspaces: 다중 모듈 관리

### 4.1 Workspaces 개념
Go 1.18부터 **여러 개의 모듈을 한 프로젝트에서 관리할 수 있는 Workspaces 기능**이 추가되었습니다.

### 4.2 Workspaces 설정 예제
1. `go.work` 파일 생성:
```sh
go work init
```
2. `go.work` 파일 내용 예시:
```go
use ./moduleA
use ./moduleB
```
3. 프로젝트 구조:
```plaintext
myproject/
├── go.work
├── moduleA/
│   ├── go.mod
│   ├── main.go
├── moduleB/
│   ├── go.mod
│   ├── lib.go
```
> `go work`를 사용하면 **여러 개의 모듈을 하나의 작업 공간에서 쉽게 관리 가능**.

---

## 5. 새로운 `context` 기능

### 5.1 `context.WithCancel`을 활용한 고루틴 제어
```go
package main
import (
    "context"
    "fmt"
    "time"
)

func worker(ctx context.Context, id int) {
    for {
        select {
        case <-ctx.Done():
            fmt.Printf("Worker %d stopped\n", id)
            return
        default:
            fmt.Printf("Worker %d running\n", id)
            time.Sleep(500 * time.Millisecond)
        }
    }
}

func main() {
    ctx, cancel := context.WithCancel(context.Background())
    
    for i := 1; i <= 3; i++ {
        go worker(ctx, i)
    }
    
    time.Sleep(2 * time.Second)
    cancel() // 모든 고루틴 종료
    time.Sleep(1 * time.Second) // 종료 확인을 위해 대기
}
```

> `context.WithCancel()`을 활용하여 여러 개의 고루틴을 동시에 종료할 수 있음.

---

## 6. HTTP 서버 개선 (net/http 패키지 개선)

### 6.1 `http.Server.Shutdown`을 활용한 안전한 서버 종료
```go
package main
import (
    "context"
    "fmt"
    "net/http"
    "os"
    "os/signal"
    "syscall"
    "time"
)

func main() {
    srv := &http.Server{Addr: ":8080"}

    go func() {
        if err := srv.ListenAndServe(); err != nil && err != http.ErrServerClosed {
            fmt.Println("Server Error:", err)
        }
    }()

    quit := make(chan os.Signal, 1)
    signal.Notify(quit, os.Interrupt, syscall.SIGTERM)
    <-quit

    ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
    defer cancel()
    srv.Shutdown(ctx)
    fmt.Println("Server gracefully stopped")
}
```

> `http.Server.Shutdown()`을 사용하면 안전하게 서버를 종료할 수 있음.

---

## 7. 결론

✅ **제네릭을 활용하여 코드 재사용성을 높일 수 있음**.  
✅ **Fuzzing 테스트를 활용하여 보안과 안정성을 검증할 수 있음**.  
✅ **Workspaces 기능을 사용하면 다중 모듈을 효율적으로 관리 가능**.  
✅ **`context`와 `http.Server.Shutdown`을 활용하면 안정적인 서버 운영이 가능**.  

Go의 최신 기능을 활용하면 **더 강력하고 유연한 소프트웨어를 개발할 수 있습니다!** 🚀

