# 🦀 Rust 트레이트(Trait)와 제네릭(Generic)

## 📌 개요
Rust는 **트레이트(Trait)** 와 **제네릭(Generic)** 을 활용하여 **코드의 재사용성과 유연성을 높이는 기능**을 제공합니다. 
이 장에서는 **트레이트(Trait)** 와 **제네릭(Generic)** 의 개념과 활용법을 배우겠습니다.

---

## 🏗️ 트레이트(Trait)란?

**트레이트(Trait)** 는 **다양한 타입이 공통으로 가져야 하는 동작(메서드)을 정의하는 방법**입니다. 
Rust에서 **인터페이스(interface)와 유사한 개념**으로 볼 수 있습니다.

```rust
trait Greet {
    fn say_hello(&self);
}

struct Person {
    name: String,
}

impl Greet for Person {
    fn say_hello(&self) {
        println!("안녕하세요! 저는 {}입니다.", self.name);
    }
}

fn main() {
    let user = Person { name: String::from("Alice") };
    user.say_hello();
}
```

🔹 `trait Greet` → `say_hello()` 메서드를 정의한 트레이트 생성

🔹 `impl Greet for Person` → `Person` 구조체에 `Greet` 트레이트 구현

🔹 `user.say_hello();` → `Person` 인스턴스에서 트레이트의 메서드를 호출

---

## ⚙️ 트레이트 활용법

### 🏷️ 기본 구현(Default Implementation)
트레이트에서 기본 동작을 정의할 수 있습니다.

```rust
trait Greet {
    fn say_hello(&self) {
        println!("안녕하세요!");
    }
}

struct Person;
impl Greet for Person {}

fn main() {
    let user = Person;
    user.say_hello(); // 기본 구현 사용
}
```

📌 `impl Greet for Person {}` 안에 별도 메서드를 정의하지 않으면 기본 구현이 사용됩니다.

---

### 🏷️ 다중 트레이트 구현 (Multiple Traits)

하나의 구조체에서 여러 개의 트레이트를 구현할 수도 있습니다.

```rust
trait Greet {
    fn say_hello(&self);
}

trait Farewell {
    fn say_goodbye(&self);
}

struct Person;

impl Greet for Person {
    fn say_hello(&self) {
        println!("안녕하세요!");
    }
}

impl Farewell for Person {
    fn say_goodbye(&self) {
        println!("안녕히 가세요!");
    }
}

fn main() {
    let user = Person;
    user.say_hello();
    user.say_goodbye();
}
```

📌 `impl Greet for Person`과 `impl Farewell for Person`을 각각 구현하여 다중 트레이트를 사용할 수 있습니다.

---

## 🔄 제네릭(Generic)이란?

**제네릭(Generic)** 은 **타입을 일반화하여 여러 타입에서 동작하도록 만드는 기능**입니다.

📌 **제네릭 함수**
```rust
fn add<T: std::ops::Add<Output = T>>(a: T, b: T) -> T {
    a + b
}

fn main() {
    println!("3 + 5 = {}", add(3, 5));
    println!("3.2 + 5.1 = {}", add(3.2, 5.1));
}
```
🔹 `T`는 **제네릭 타입**을 의미하며, `std::ops::Add<Output = T>` 제약을 추가하여 `+` 연산을 허용합니다.

📌 **제네릭 구조체**
```rust
struct Point<T> {
    x: T,
    y: T,
}

fn main() {
    let integer_point = Point { x: 5, y: 10 };
    let float_point = Point { x: 1.5, y: 3.4 };
    println!("정수 좌표: ({}, {})", integer_point.x, integer_point.y);
    println!("실수 좌표: ({}, {})", float_point.x, float_point.y);
}
```

📌 **제네릭과 트레이트 결합**
```rust
trait Area {
    fn area(&self) -> f64;
}

struct Circle {
    radius: f64,
}

impl Area for Circle {
    fn area(&self) -> f64 {
        3.14 * self.radius * self.radius
    }
}

fn print_area<T: Area>(shape: &T) {
    println!("면적: {}", shape.area());
}

fn main() {
    let circle = Circle { radius: 5.0 };
    print_area(&circle);
}
```

🔹 `T: Area`를 사용하여 `print_area()` 함수가 `Area` 트레이트를 구현한 타입에 대해서만 동작하도록 설정

🔹 `impl Area for Circle`을 통해 `Circle`이 `Area` 트레이트를 구현하도록 설정

---

## 🎯 마무리

이 장에서는 **트레이트(Trait)와 제네릭(Generic)** 의 개념과 활용법을 배웠습니다.

다음 장에서는 **Rust의 에러 처리(Error Handling) 방법**에 대해 배워보겠습니다! 🚀
