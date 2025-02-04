# 🦀 Rust 구조체(Struct)와 열거형(Enum)

## 📌 개요
Rust에서는 데이터를 구조화하여 다룰 수 있도록 **구조체(Struct)** 와 **열거형(Enum)** 을 제공합니다. 
이 장에서는 구조체와 열거형을 배우고 활용하는 방법을 알아보겠습니다.

---

## 🏗️ 구조체(Struct)
Rust의 **구조체(struct)** 는 관련된 데이터를 하나의 단위로 묶어 표현할 때 사용됩니다.

📌 **Rust 구조체의 종류**
1️⃣ **일반 구조체(Named Struct)**
2️⃣ **튜플 구조체(Tuple Struct)**
3️⃣ **유닛 구조체(Unit Struct)**

### 1️⃣ 일반 구조체 (Named Struct)
```rust
struct User {
    username: String,
    email: String,
    age: u32,
}

fn main() {
    let user1 = User {
        username: String::from("rustacean"),
        email: String::from("rustacean@example.com"),
        age: 25,
    };
    println!("사용자: {}, 이메일: {}, 나이: {}", user1.username, user1.email, user1.age);
}
```
🔹 **필드명과 타입을 지정하여 구조화된 데이터를 저장**할 수 있습니다.

🔹 `user1.username`, `user1.email` 등을 통해 필드에 접근할 수 있습니다.


### 2️⃣ 튜플 구조체 (Tuple Struct)
```rust
struct Color(u8, u8, u8);

fn main() {
    let red = Color(255, 0, 0);
    println!("RGB: ({}, {}, {})", red.0, red.1, red.2);
}
```
🔹 **튜플과 비슷한 구조이지만, 타입을 구별할 수 있는 특징**이 있습니다.

🔹 필드명이 없고, **색인(index)으로 필드에 접근**합니다.


### 3️⃣ 유닛 구조체 (Unit Struct)
```rust
struct Marker;

fn main() {
    let _m = Marker;
}
```
🔹 **필드가 없는 구조체**이며, 특정 타입을 구별하는 용도로 사용됩니다.

---

## ⚙️ 구조체 활용법
### 🏷️ 구조체의 필드 값 변경하기
구조체의 필드를 변경하려면 **가변(mut) 변수** 로 선언해야 합니다.

```rust
fn main() {
    let mut user = User {
        username: String::from("rustacean"),
        email: String::from("rustacean@example.com"),
        age: 25,
    };
    user.email = String::from("new_email@example.com");
    println!("새 이메일: {}", user.email);
}
```

### 🏷️ 구조체 업데이트 문법 (Struct Update Syntax)
기존 구조체의 필드를 복사하여 새로운 인스턴스를 만들 수 있습니다.
```rust
fn main() {
    let user1 = User {
        username: String::from("rustacean"),
        email: String::from("rustacean@example.com"),
        age: 25,
    };
    let user2 = User {
        email: String::from("new@example.com"),
        ..user1 // 나머지 필드 복사
    };
    println!("{}", user2.username); // user1.username 복사됨
}
```
🚨 `user1`의 소유권이 `user2`로 이동하므로, 이후 `user1`을 사용할 수 없습니다!

---

## 🎭 열거형 (Enum)

열거형(Enum)은 **서로 다른 종류의 값을 하나의 타입으로 정의**할 때 유용합니다.

📌 **Enum의 장점**
- 여러 유형의 데이터를 하나의 타입으로 관리 가능
- 패턴 매칭과 결합하여 강력한 기능 제공


### 🏷️ 기본적인 열거형 사용하기
```rust
enum IpAddr {
    V4(String),
    V6(String),
}

fn main() {
    let home = IpAddr::V4(String::from("127.0.0.1"));
    let loopback = IpAddr::V6(String::from("::1"));
    println!("IPv4: {:?}, IPv6: {:?}", home, loopback);
}
```
🔹 `IpAddr::V4("127.0.0.1"), IpAddr::V6("::1")` 처럼 사용 가능


### 🏷️ 다양한 데이터 타입을 포함하는 Enum
```rust
enum Message {
    Quit,
    Move { x: i32, y: i32 },
    Write(String),
    ChangeColor(i32, i32, i32),
}

fn main() {
    let m = Message::Move { x: 10, y: 20 };
}
```
🔹 열거형 안에 **구조체와 튜플을 포함**할 수도 있습니다.

---

## 🔄 열거형과 패턴 매칭 (Pattern Matching)
열거형을 사용할 때 `match` 문을 사용하면 다양한 경우를 처리할 수 있습니다.

```rust
enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter,
}

fn value_in_cents(coin: Coin) -> u8 {
    match coin {
        Coin::Penny => 1,
        Coin::Nickel => 5,
        Coin::Dime => 10,
        Coin::Quarter => 25,
    }
}

fn main() {
    let coin = Coin::Dime;
    println!("동전의 가치: {} 센트", value_in_cents(coin));
}
```
🔹 `match` 문을 사용하여 모든 경우를 처리해야 합니다.

---

## 🎯 마무리

이 장에서는 **Rust의 구조체(Struct)와 열거형(Enum)** 에 대해 배웠습니다.

다음 장에서는 **Rust의 트레이트(Trait)와 제네릭(Generic)** 개념을 배워보겠습니다! 🚀