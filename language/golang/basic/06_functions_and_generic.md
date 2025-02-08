# 05. Go의 함수와 제네릭 (Functions and Generics)

## 1. 함수 (Functions)

### 함수란?
함수(Function)는 코드의 재사용성을 높이고 가독성을 개선하는 중요한 요소입니다. Go에서는 `func` 키워드를 사용하여 함수를 정의합니다.

### 함수 선언 방법
```go
func 함수이름(매개변수 타입) 반환타입 {
    // 실행할 코드
    return 값
}
```

### 예제: 기본 함수
```go
package main
import "fmt"

func add(a int, b int) int {
    return a + b
}

func main() {
    sum := add(3, 5)
    fmt.Println("합계:", sum)
}
```

### 다중 반환값 (Multiple Return Values)
Go의 함수는 여러 개의 값을 반환할 수 있습니다.

```go
package main
import "fmt"

func divide(a, b int) (int, int) {
    quotient := a / b
    remainder := a % b
    return quotient, remainder
}

func main() {
    q, r := divide(10, 3)
    fmt.Println("몫:", q, "나머지:", r)
}
```

### 반환값의 이름 지정
반환값에 이름을 지정하면 `return` 문에서 명시적인 반환값을 생략할 수 있습니다.

```go
func rectangleDimensions(length, width int) (area int, perimeter int) {
    area = length * width
    perimeter = 2 * (length + width)
    return // 반환값 생략 가능
}
```

---

## 2. 가변 인자 함수 (Variadic Functions)

Go에서는 가변 인자를 사용하여 여러 개의 인수를 처리할 수 있습니다.

```go
func sum(numbers ...int) int {
    total := 0
    for _, num := range numbers {
        total += num
    }
    return total
}

func main() {
    fmt.Println(sum(1, 2, 3, 4, 5))
}
```

`...int`를 사용하면 원하는 개수만큼 인자를 전달할 수 있습니다.

---

## 3. 익명 함수 (Anonymous Functions)

익명 함수는 함수의 이름 없이 사용할 수 있으며, 변수에 저장하거나 즉시 실행할 수 있습니다.

```go
package main
import "fmt"

func main() {
    add := func(a, b int) int {
        return a + b
    }
    fmt.Println(add(3, 4))
}
```

즉시 실행 함수도 가능합니다.
```go
func main() {
    result := func(a, b int) int {
        return a + b
    }(3, 4)
    fmt.Println(result)
}
```

---

## 4. 제네릭 (Generics)

Go 1.18부터 제네릭이 도입되면서 코드의 재사용성이 대폭 증가했습니다.

### 기본적인 제네릭 함수
```go
package main
import "fmt"

type Number interface {
    int | float64
}

func add[T Number](a, b T) T {
    return a + b
}

func main() {
    fmt.Println(add(3, 4))      // 정수
    fmt.Println(add(3.5, 2.1)) // 실수
}
```

- `T`는 타입 매개변수이며, 호출 시 자동으로 타입이 결정됩니다.
- `Number` 인터페이스를 활용하여 특정 타입만 허용할 수 있습니다.

---

## 5. 복잡한 제네릭 패턴

### 5.1 여러 개의 타입 매개변수
제네릭을 사용하여 여러 개의 타입을 처리할 수 있습니다.

```go
func swap[T, U any](a T, b U) (U, T) {
    return b, a
}

func main() {
    a, b := swap(10, "hello")
    fmt.Println(a, b) // 출력: hello 10
}
```

### 5.2 제네릭 구조체
제네릭을 구조체에도 적용할 수 있습니다.
```go
type Pair[T any] struct {
    First  T
    Second T
}

func main() {
    p := Pair[int]{First: 10, Second: 20}
    fmt.Println(p)
}
```

### 5.3 제네릭 맵을 활용한 유연한 데이터 저장
```go
type Dictionary[K comparable, V any] struct {
    items map[K]V
}

func (d *Dictionary[K, V]) Set(key K, value V) {
    d.items[key] = value
}

func (d *Dictionary[K, V]) Get(key K) V {
    return d.items[key]
}
}

func main() {
    dict := Dictionary[string, int]{items: make(map[string]int)}
    dict.Set("age", 25)
    fmt.Println("Age:", dict.Get("age"))
}
```

---

## 6. 함수형 프로그래밍 패턴과 제네릭 활용

제네릭을 활용하여 맵, 필터, 리듀스 같은 함수형 패턴을 구현할 수 있습니다.

### 6.1 맵 함수 구현
```go
func Map[T any, U any](arr []T, f func(T) U) []U {
    result := make([]U, len(arr))
    for i, v := range arr {
        result[i] = f(v)
    }
    return result
}

func main() {
    numbers := []int{1, 2, 3, 4}
    squared := Map(numbers, func(n int) int { return n * n })
    fmt.Println(squared) // 출력: [1 4 9 16]
}
```

제네릭을 활용하면 다양한 패턴을 유연하게 구현할 수 있습니다.

---

Go의 함수와 제네릭을 활용하면 코드의 재사용성과 확장성을 높일 수 있습니다. 다음으로 동시성 프로그래밍(Goroutines and Channels)에 대해 알아보겠습니다.

