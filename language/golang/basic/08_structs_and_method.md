# 07. Go 구조체와 메서드 (Structs and Methods)

## 1. 구조체 (Structs)

### 구조체란?
Go에서 구조체(Struct)는 여러 개의 필드를 하나의 데이터 타입으로 묶어 관리할 수 있는 사용자 정의 타입입니다. C의 `struct`와 유사하지만, Go에서는 객체지향적인 기능을 지원하기 위한 기본 단위로 사용됩니다.

### 구조체 선언 및 초기화
```go
type Person struct {
    Name string
    Age  int
}

func main() {
    // 필드명을 명시한 구조체 초기화
    p1 := Person{Name: "Alice", Age: 25}
    
    // 필드명을 생략한 구조체 초기화 (순서 중요)
    p2 := Person{"Bob", 30}
    
    // 빈 구조체 선언
    var p3 Person
    p3.Name = "Charlie"
    p3.Age = 40
    
    fmt.Println(p1, p2, p3)
}
```

### 구조체의 필드 접근 및 수정
```go
package main
import "fmt"

type Car struct {
    Brand string
    Year  int
}

func main() {
    myCar := Car{Brand: "Tesla", Year: 2023}
    fmt.Println("Before:", myCar)
    
    myCar.Year = 2025 // 필드 값 변경
    fmt.Println("After:", myCar)
}
```

---

## 2. 메서드 (Methods)

### 메서드란?
Go에서는 구조체에 함수를 연관시켜 사용할 수 있으며, 이를 **메서드(Method)**라고 합니다. 메서드는 특정 타입의 값에서만 호출될 수 있습니다.

### 기본적인 메서드 정의
```go
type Rectangle struct {
    Width, Height float64
}

// 구조체의 메서드 정의
func (r Rectangle) Area() float64 {
    return r.Width * r.Height
}

func main() {
    rect := Rectangle{Width: 10, Height: 5}
    fmt.Println("면적:", rect.Area())
}
```

> `func (r Rectangle) Area() float64`의 `(r Rectangle)` 부분이 메서드의 리시버(Receiver)입니다.

### 포인터 리시버를 활용한 메서드
구조체의 값을 변경하려면 **포인터 리시버**를 사용해야 합니다.

```go
type Counter struct {
    Value int
}

// 포인터 리시버를 사용하여 값을 변경
func (c *Counter) Increment() {
    c.Value++
}

func main() {
    cnt := Counter{Value: 0}
    cnt.Increment()
    fmt.Println("Counter Value:", cnt.Value) // 1
}
```

> 포인터 리시버(`*Counter`)를 사용하면 구조체의 값이 변경됩니다.

---

## 3. 구조체 임베딩 (Struct Embedding)

Go는 상속을 지원하지 않지만, **구조체 임베딩(Embedding)**을 통해 유사한 기능을 구현할 수 있습니다.

```go
type Animal struct {
    Name string
}

func (a Animal) Speak() {
    fmt.Println(a.Name, "makes a sound")
}

type Dog struct {
    Animal // 구조체 임베딩
    Breed  string
}

func main() {
    d := Dog{Animal: Animal{Name: "Buddy"}, Breed: "Golden Retriever"}
    d.Speak() // Buddy makes a sound
}
```

> `Dog` 구조체는 `Animal`을 포함하고 있으므로, `Dog` 객체에서 `Speak` 메서드를 호출할 수 있습니다.

---

## 4. 인터페이스와 구조체의 결합

구조체는 **인터페이스(Interface)**와 함께 사용될 때 더욱 강력한 기능을 발휘할 수 있습니다.

```go
type Speaker interface {
    Speak()
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
    myCat := Cat{Name: "Whiskers"}
    MakeSound(myCat)
}
```

> `MakeSound` 함수는 `Speaker` 인터페이스를 구현한 구조체를 인자로 받을 수 있습니다.

---

## 5. JSON과 구조체 활용

Go에서는 `encoding/json` 패키지를 사용하여 구조체를 JSON으로 변환하거나 JSON을 구조체로 변환할 수 있습니다.

### 구조체를 JSON으로 변환
```go
package main
import (
    "encoding/json"
    "fmt"
)

type User struct {
    Name  string `json:"name"`
    Email string `json:"email"`
}

func main() {
    user := User{Name: "Alice", Email: "alice@example.com"}
    jsonData, _ := json.Marshal(user)
    fmt.Println(string(jsonData)) // {"name":"Alice","email":"alice@example.com"}
}
```

### JSON을 구조체로 변환
```go
package main
import (
    "encoding/json"
    "fmt"
)

type User struct {
    Name  string `json:"name"`
    Email string `json:"email"`
}

func main() {
    jsonData := `{"name":"Bob","email":"bob@example.com"}`
    var user User
    json.Unmarshal([]byte(jsonData), &user)
    fmt.Println(user) // {Bob bob@example.com}
}
```

> `json.Marshal`과 `json.Unmarshal`을 사용하여 구조체와 JSON 간 변환이 가능합니다.

---

## 6. 고급 패턴: 태그 활용 및 필드 유효성 검사

### 태그 활용하기
Go에서는 구조체 필드에 **태그(Tags)**를 추가하여 JSON 변환, 데이터 검증 등에 활용할 수 있습니다.

```go
type Product struct {
    ID    int    `json:"id" validate:"required"`
    Name  string `json:"name" validate:"required"`
    Price int    `json:"price" validate:"min=1"`
}
```

- `json:"id"`: JSON 변환 시 `id`로 변환됩니다.
- `validate:"required"`: 유효성 검사 시 필수 필드로 지정됩니다.

### 유효성 검사 라이브러리 사용 예제
```go
package main
import (
    "fmt"
    "github.com/go-playground/validator/v10"
)

type Product struct {
    Name  string `validate:"required"`
    Price int    `validate:"min=1"`
}

func main() {
    validate := validator.New()
    product := Product{Name: "Laptop", Price: 0}
    err := validate.Struct(product)
    if err != nil {
        fmt.Println("Validation failed:", err)
    }
}
```

> `go-playground/validator` 패키지를 활용하면 구조체 필드의 유효성을 쉽게 검사할 수 있습니다.

---

Go의 구조체와 메서드는 객체지향 프로그래밍(OOP) 스타일로 코드를 구성할 수 있도록 도와줍니다. 다음으로 인터페이스(Interfaces)에 대해 다루겠습니다.

