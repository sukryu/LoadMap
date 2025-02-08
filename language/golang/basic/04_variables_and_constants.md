# 03. Go 변수와 상수 (Variables and Constants)

## 1. 변수 (Variables)

### 변수란?
변수(Variable)는 데이터를 저장할 수 있는 메모리 공간을 의미하며, 특정 타입을 갖습니다. Go에서는 정적 타입 시스템을 사용하므로, 변수를 선언할 때 타입을 명확히 정의해야 합니다.

### 변수 선언 방법
Go에서 변수를 선언하는 방법은 여러 가지가 있습니다.

#### 1. `var` 키워드를 이용한 변수 선언
```go
var age int
var name string
```
- `var` 키워드를 사용하면 명시적으로 타입을 지정할 수 있습니다.
- 초기화를 하지 않으면 기본값(Default Value)이 설정됩니다.
  - 정수형(`int`): `0`
  - 실수형(`float64`): `0.0`
  - 문자열(`string`): `""` (빈 문자열)
  - 불리언(`bool`): `false`

#### 2. 선언과 동시에 초기화
```go
var age int = 25
var name string = "Alice"
```
- 변수를 선언하면서 동시에 값을 초기화할 수 있습니다.

#### 3. 타입 추론 (`:=` 연산자)
```go
score := 90
username := "Bob"
```
- `:=` 연산자를 사용하면 변수의 타입을 자동으로 추론합니다.
- 이 방식은 함수 내부에서만 사용할 수 있으며, 함수 외부에서는 `var` 키워드를 사용해야 합니다.

#### 4. 여러 개의 변수 선언
```go
var (
    age  int    = 30
    name string = "Charlie"
    pi   float64 = 3.1415
)
```
- 여러 개의 변수를 한 번에 선언할 수 있습니다.

---

## 2. 상수 (Constants)

### 상수란?
상수(Constant)는 변하지 않는 값을 저장하는 변수입니다. `const` 키워드를 사용하여 선언합니다.

### 상수 선언
```go
const Pi = 3.1415
const Greeting = "Hello, Go!"
```
- 상수는 선언 후 변경할 수 없습니다.
- 기본적으로 타입을 지정하지 않으면 컴파일러가 자동으로 타입을 추론합니다.

### 여러 개의 상수 선언
```go
const (
    A = 10
    B = 20
    C = "Go Language"
)
```
- 여러 개의 상수를 `const` 블록 내에서 선언할 수 있습니다.

### `iota` 키워드를 이용한 상수 자동 증가
`iota`는 연속된 정수 값을 자동으로 증가시키는 특별한 키워드입니다.
```go
const (
    Red = iota // 0
    Green      // 1
    Blue       // 2
)
```
- `iota`는 0부터 시작하며, 다음 선언된 상수마다 1씩 증가합니다.
- 값을 명시하지 않으면 이전 상수의 값을 자동으로 사용합니다.

#### `iota` 활용 예제
```go
const (
    Sunday = iota  // 0
    Monday         // 1
    Tuesday        // 2
    Wednesday      // 3
    Thursday       // 4
    Friday         // 5
    Saturday       // 6
)
```
- 요일 상수를 쉽게 정의할 수 있습니다.

#### 복잡한 `iota` 패턴 활용 예제
```go
const (
    _ = iota  // 0 생략
    KB = 1 << (10 * iota) // 1 << 10 (1024)
    MB = 1 << (10 * iota) // 1 << 20 (1048576)
    GB = 1 << (10 * iota) // 1 << 30 (1073741824)
    TB = 1 << (10 * iota) // 1 << 40 (1099511627776)
)
```
- `iota`를 활용하여 메모리 크기 단위를 쉽게 정의할 수 있습니다.
- `1 << (10 * iota)`를 이용해 1024 단위의 크기를 생성합니다.

```go
const (
    FlagA = 1 << iota  // 1 (0001)
    FlagB              // 2 (0010)
    FlagC              // 4 (0100)
    FlagD              // 8 (1000)
)
```
- `iota`를 활용하여 비트 마스크 값을 설정할 수 있습니다.
- 각 상수 값은 `1 << iota`를 통해 이전 값의 2배가 됩니다.

---

## 3. 변수와 상수의 차이

| 특징    | 변수 (`var`) | 상수 (`const`) |
|---------|------------|---------------|
| 값 변경 | 가능       | 불가능        |
| 타입    | 명시적 또는 타입 추론 가능 | 자동 추론 가능 |
| 사용 범위 | 함수 내부 또는 패키지 수준 | 패키지 수준에서 주로 사용 |

---

## 4. 변수와 상수 예제

### 1. 변수 사용 예제
```go
package main

import "fmt"

func main() {
    var name string = "Alice"
    age := 25
    fmt.Println("이름:", name)
    fmt.Println("나이:", age)
}
```

### 2. 상수 사용 예제
```go
package main

import "fmt"

const Pi = 3.1415

func main() {
    fmt.Println("파이 값:", Pi)
}
```

### 3. `iota` 활용 예제
```go
package main

import "fmt"

const (
    Small = iota // 0
    Medium       // 1
    Large        // 2
)

func main() {
    fmt.Println("Small:", Small)
    fmt.Println("Medium:", Medium)
    fmt.Println("Large:", Large)
}
```

---

Go에서 변수와 상수를 올바르게 사용하면 코드의 가독성과 유지보수성을 높일 수 있습니다. 다음 단계에서는 제어 구조를 다루며, Go에서 조건문과 반복문을 어떻게 활용하는지 살펴보겠습니다.

