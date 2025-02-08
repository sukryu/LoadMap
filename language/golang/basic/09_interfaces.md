# 08. Go 인터페이스 (Interfaces)

## 1. 인터페이스란?

Go에서 **인터페이스(Interface)**는 메서드의 집합을 정의하는 추상적인 타입입니다. 인터페이스를 사용하면 다형성을 활용하여 코드의 유연성을 높일 수 있습니다.

### 인터페이스의 특징
- 인터페이스는 **구조체(struct) 또는 다른 타입들이 특정 메서드를 구현하도록 강제**할 수 있습니다.
- Go에서는 **명시적인 `implements` 키워드 없이** 특정 타입이 인터페이스를 자동으로 구현합니다.
- 빈 인터페이스(`interface{}`)는 **모든 타입을 저장**할 수 있습니다.

---

## 2. 기본적인 인터페이스 사용

### 인터페이스 정의 및 구현
```go
package main
import "fmt"

type Speaker interface {
    Speak()
}

type Dog struct {
    Name string
}

func (d Dog) Speak() {
    fmt.Println(d.Name, "says Woof!")
}

type Cat struct {
    Name string
}

func (c Cat) Speak() {
    fmt.Println(c.Name, "says Meow!")
}

func MakeSound(s Speaker) {
    s.Speak()
}

func main() {
    dog := Dog{Name: "Buddy"}
    cat := Cat{Name: "Whiskers"}
    
    MakeSound(dog) // Buddy says Woof!
    MakeSound(cat) // Whiskers says Meow!
}
```

> `Dog`과 `Cat` 구조체는 `Speaker` 인터페이스를 자동으로 구현합니다.
> `MakeSound` 함수는 `Speaker` 인터페이스를 구현한 타입을 인자로 받을 수 있습니다.

---

## 3. 빈 인터페이스 (`interface{}`)

Go의 빈 인터페이스는 **모든 타입을 저장할 수 있는 컨테이너 역할**을 합니다.

### 빈 인터페이스 활용 예제
```go
package main
import "fmt"

func PrintValue(value interface{}) {
    fmt.Println("Value:", value)
}

func main() {
    PrintValue(42)
    PrintValue("Hello, Go!")
    PrintValue([]int{1, 2, 3})
}
```

> 빈 인터페이스를 사용하면 **모든 타입을 인자로 받을 수 있습니다.**

---

## 4. 타입 어서션 (Type Assertion)

빈 인터페이스를 사용할 경우, 원래의 타입을 알고 싶다면 **타입 어서션(Type Assertion)** 을 사용할 수 있습니다.

### 타입 어서션 예제
```go
package main
import "fmt"

func Describe(i interface{}) {
    v, ok := i.(string) // 타입 어서션
    if ok {
        fmt.Println("String value:", v)
    } else {
        fmt.Println("Not a string")
    }
}

func main() {
    Describe("Go Lang") // String value: Go Lang
    Describe(100)       // Not a string
}
```

> `i.(string)`을 통해 `interface{}` 타입을 `string`으로 변환할 수 있습니다.

---

## 5. 타입 스위치 (Type Switch)

여러 개의 타입을 처리해야 할 경우, `switch` 문을 이용한 **타입 스위치(Type Switch)** 를 사용할 수 있습니다.

### 타입 스위치 예제
```go
package main
import "fmt"

func TypeCheck(i interface{}) {
    switch v := i.(type) {
    case int:
        fmt.Println("Integer value:", v)
    case string:
        fmt.Println("String value:", v)
    case bool:
        fmt.Println("Boolean value:", v)
    default:
        fmt.Println("Unknown type")
    }
}

func main() {
    TypeCheck(42)
    TypeCheck("Hello")
    TypeCheck(true)
    TypeCheck(3.14)
}
```

> `switch v := i.(type)` 구문을 통해 다양한 타입을 처리할 수 있습니다.

---

## 6. 인터페이스 임베딩 (Interface Embedding)

Go의 인터페이스는 다른 인터페이스를 포함(임베딩)할 수 있습니다.

### 인터페이스 임베딩 예제
```go
package main
import "fmt"

type Walker interface {
    Walk()
}

type Talker interface {
    Talk()
}

type Human interface {
    Walker
    Talker
}

type Person struct {
    Name string
}

func (p Person) Walk() {
    fmt.Println(p.Name, "is walking")
}

func (p Person) Talk() {
    fmt.Println(p.Name, "is talking")
}

func main() {
    p := Person{Name: "Alice"}
    var h Human = p
    h.Walk()
    h.Talk()
}
```

> `Human` 인터페이스는 `Walker`와 `Talker` 인터페이스를 포함하며, `Person`이 이를 구현합니다.

---

## 7. 인터페이스 활용 패턴

### 인터페이스를 활용한 의존성 주입
인터페이스를 사용하면 **유연한 코드 설계**가 가능합니다. 특히, 함수나 메서드가 특정 구현이 아닌 **인터페이스를 의존하도록 설계**하면, 유지보수성이 높아집니다.

```go
package main
import "fmt"

type Logger interface {
    Log(message string)
}

type ConsoleLogger struct{}

func (c ConsoleLogger) Log(message string) {
    fmt.Println("Log:", message)
}

type Application struct {
    logger Logger
}

func (app Application) Run() {
    app.logger.Log("Application is running")
}

func main() {
    logger := ConsoleLogger{}
    app := Application{logger: logger}
    app.Run()
}
```

> `Application` 구조체는 `Logger` 인터페이스에 의존하므로, `ConsoleLogger`를 교체하면 다른 로깅 방식을 쉽게 추가할 수 있습니다.

---

## 8. 결론

Go의 인터페이스는 **명시적인 구현 없이도 특정 메서드만 충족하면 자동으로 인터페이스를 구현하는 특징**이 있습니다. 이를 활용하면 다형성을 구현하고, 코드를 보다 유연하게 설계할 수 있습니다.

다음으로 Go의 메모리 관리와 기본 데이터 구조에 대해 알아보겠습니다.