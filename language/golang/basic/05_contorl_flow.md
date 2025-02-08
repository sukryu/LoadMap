# 04. Go 제어 구조 (Control Flow)

## 1. 조건문 (Conditional Statements)

Go에서는 `if`, `else if`, `else`, `switch` 문을 사용하여 조건을 평가하고 실행 흐름을 제어할 수 있습니다.

### 1.1 if-else 문
Go의 `if-else` 문은 조건에 따라 실행할 코드를 선택하는 기본적인 방법입니다.

#### 기본 문법
```go
if 조건 {
    // 조건이 참일 경우 실행
} else {
    // 조건이 거짓일 경우 실행
}
```

#### 예제
```go
package main
import "fmt"

func main() {
    age := 18
    if age >= 18 {
        fmt.Println("성인입니다.")
    } else {
        fmt.Println("미성년자입니다.")
    }
}
```

### 1.2 else if 문
여러 개의 조건을 평가할 때 `else if` 문을 사용할 수 있습니다.

```go
package main
import "fmt"

func main() {
    score := 85
    if score >= 90 {
        fmt.Println("A 등급")
    } else if score >= 80 {
        fmt.Println("B 등급")
    } else if score >= 70 {
        fmt.Println("C 등급")
    } else {
        fmt.Println("F 등급")
    }
}
```

### 1.3 조건문 안에서 변수 선언
Go에서는 `if` 문 내부에서 변수를 선언할 수 있으며, 해당 변수는 `if-else` 블록 내에서만 사용 가능합니다.

```go
if num := 10; num > 5 {
    fmt.Println("num은 5보다 큽니다.")
}
```

---

## 2. switch 문

`switch` 문은 여러 개의 경우를 비교해야 할 때 사용됩니다. `if-else` 문보다 가독성이 좋고 간결합니다.

### 2.1 기본 switch 문법
```go
switch 표현식 {
case 값1:
    // 실행 코드
case 값2:
    // 실행 코드
default:
    // 위의 경우에 해당하지 않을 때 실행
}
```

#### 예제
```go
package main
import "fmt"

func main() {
    day := "월요일"
    switch day {
    case "월요일":
        fmt.Println("한 주의 시작!")
    case "금요일":
        fmt.Println("주말이 다가온다!")
    default:
        fmt.Println("평범한 날")
    }
}
```

### 2.2 다중 case 처리
`case` 문을 한 줄에 여러 개 나열하여 같은 코드 블록을 실행할 수 있습니다.

```go
package main
import "fmt"

func main() {
    day := "토요일"
    switch day {
    case "토요일", "일요일":
        fmt.Println("주말입니다!")
    default:
        fmt.Println("평일입니다.")
    }
}
```

### 2.3 조건 없는 switch
Go에서는 `switch` 문에서 표현식을 생략하면 `true`와 같은 효과를 가집니다.

```go
package main
import "fmt"

func main() {
    score := 75
    switch {
    case score >= 90:
        fmt.Println("A 학점")
    case score >= 80:
        fmt.Println("B 학점")
    case score >= 70:
        fmt.Println("C 학점")
    default:
        fmt.Println("F 학점")
    }
}
```

---

## 3. 반복문 (Loops)

Go에서는 `for` 문을 사용하여 반복문을 구현합니다. Go에는 `while` 문이 없으며, `for` 문을 변형하여 사용합니다.

### 3.1 기본 for 문
```go
for 초기화; 조건; 증감 {
    // 실행 코드
}
```

#### 예제
```go
package main
import "fmt"

func main() {
    for i := 0; i < 5; i++ {
        fmt.Println("반복 중:", i)
    }
}
```

### 3.2 while과 유사한 for 문
Go에서는 `while` 문이 없으며, `for` 문을 아래처럼 사용하면 `while` 문과 같은 역할을 합니다.

```go
package main
import "fmt"

func main() {
    count := 0
    for count < 5 {
        fmt.Println("반복 중:", count)
        count++
    }
}
```

### 3.3 무한 루프
무한 루프는 `for` 문을 조건 없이 사용하면 구현할 수 있습니다.

```go
for {
    fmt.Println("무한 루프")
}
```

### 3.4 range를 이용한 반복문
Go에서는 `range` 키워드를 사용하여 배열, 슬라이스, 맵 등의 요소를 반복할 수 있습니다.

#### 예제: 슬라이스 순회
```go
package main
import "fmt"

func main() {
    numbers := []int{10, 20, 30, 40}
    for index, value := range numbers {
        fmt.Printf("Index: %d, Value: %d\n", index, value)
    }
}
```

---

## 4. break와 continue

### 4.1 break 문
`break` 문은 반복문을 즉시 종료합니다.

```go
for i := 0; i < 10; i++ {
    if i == 5 {
        break
    }
    fmt.Println(i)
}
```

### 4.2 continue 문
`continue` 문은 현재 반복을 건너뛰고 다음 반복을 수행합니다.

```go
for i := 0; i < 10; i++ {
    if i%2 == 0 {
        continue
    }
    fmt.Println(i) // 홀수만 출력됨
}
```

---

Go의 제어 구조는 코드의 흐름을 결정하는 중요한 요소입니다. 다음으로 Go의 함수(Function) 개념을 살펴보겠습니다.

