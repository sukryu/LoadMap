# 12. Go 테스팅 (Testing)

## 1. Go에서 테스팅이 중요한 이유

Go는 내장된 `testing` 패키지를 제공하여 효율적으로 단위 테스트(Unit Test), 벤치마킹(Benchmarking), 예제(Examples)를 작성할 수 있습니다.
테스트를 통해 **코드의 신뢰성을 높이고, 유지보수성을 향상**시킬 수 있습니다.

---

## 2. 기본적인 단위 테스트(Unit Test)

### 2.1 `testing` 패키지를 활용한 기본 테스트
Go의 테스트 함수는 `_test.go` 파일에서 `Test`로 시작하는 함수 형태로 작성됩니다.

```go
package main

import (
    "testing"
)

func Add(a, b int) int {
    return a + b
}

func TestAdd(t *testing.T) {
    result := Add(2, 3)
    expected := 5
    if result != expected {
        t.Errorf("Expected %d, but got %d", expected, result)
    }
}
```

### 2.2 테스트 실행
테스트는 `go test` 명령어를 사용하여 실행합니다.
```sh
go test
```
또는 상세한 출력을 원할 경우:
```sh
go test -v
```

---

## 3. 여러 개의 테스트 케이스 실행

테스트 케이스를 효율적으로 실행하기 위해 **테이블 기반 테스트(Table-driven Test)**를 활용할 수 있습니다.

```go
func TestAddCases(t *testing.T) {
    testCases := []struct {
        a, b, expected int
    }{
        {2, 3, 5},
        {1, 1, 2},
        {0, 0, 0},
    }

    for _, tc := range testCases {
        result := Add(tc.a, tc.b)
        if result != tc.expected {
            t.Errorf("For input (%d, %d), expected %d but got %d", tc.a, tc.b, tc.expected, result)
        }
    }
}
```

---

## 4. 벤치마킹 (Benchmarking)
Go에서는 `Benchmark` 테스트를 지원하여 성능을 측정할 수 있습니다.

### 4.1 벤치마킹 예제
```go
func BenchmarkAdd(b *testing.B) {
    for i := 0; i < b.N; i++ {
        Add(10, 20)
    }
}
```

### 4.2 벤치마킹 실행
```sh
go test -bench .
```
출력 예시:
```sh
BenchmarkAdd-8 1000000000 0.312 ns/op
```

---

## 5. Mocking과 Stub을 활용한 테스트

실제 데이터베이스나 네트워크 요청을 테스트할 때는 **Mocking**을 활용할 수 있습니다.

### 5.1 인터페이스를 활용한 Mocking 예제
```go
type Database interface {
    GetUser(id int) string
}

type MockDB struct{}

func (m MockDB) GetUser(id int) string {
    return "Mocked User"
}

func TestMockDatabase(t *testing.T) {
    mock := MockDB{}
    user := mock.GetUser(1)
    if user != "Mocked User" {
        t.Errorf("Expected 'Mocked User', got %s", user)
    }
}
```

---

## 6. `testing.T`를 활용한 에러 및 패닉 처리

Go에서는 `t.Fatal`과 `t.FailNow`를 사용하여 테스트를 즉시 종료할 수 있습니다.

```go
func TestDivide(t *testing.T) {
    _, err := Divide(10, 0)
    if err == nil {
        t.Fatal("Expected an error but got nil")
    }
}
```

---

## 7. 예제(Example) 테스트

Go의 문서화에 활용할 수 있는 **Example 테스트**를 작성할 수 있습니다.

```go
func ExampleAdd() {
    fmt.Println(Add(2, 3))
    // Output: 5
}
```

테스트 실행 시 **출력값이 주석의 Output과 일치하는지 검증**됩니다.

```sh
go test
```

---

## 8. `go test` 옵션 정리

| 명령어 | 설명 |
|--------|------|
| `go test` | 모든 테스트 실행 |
| `go test -v` | 상세한 로그 출력 |
| `go test -bench .` | 벤치마킹 실행 |
| `go test -cover` | 코드 커버리지 확인 |
| `go test -run TestAdd` | 특정 테스트만 실행 |

---

## 9. 결론

- **`testing` 패키지를 사용하여 단위 테스트를 작성**할 수 있음.
- **테이블 기반 테스트와 Mocking을 활용하면 더욱 유연한 테스트 코드 작성 가능**.
- **벤치마킹을 통해 성능을 측정하고 최적화할 수 있음**.
- **`go test` 명령어를 활용하여 코드의 신뢰성을 높일 수 있음**.

다음으로 **Go의 동시성 패턴과 실제 사례(Concurrency Patterns and Examples)**에 대해 알아보겠습니다!

