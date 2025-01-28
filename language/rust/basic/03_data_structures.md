# 3. Data Structures

이 문서는 Rust의 데이터 구조를 다룹니다.  
튜플, 배열, 벡터, 해시맵, 구조체, 열거형 등 Rust에서 사용하는 주요 데이터 구조를 학습합니다.

---

## 📌 튜플(Tuple)

튜플은 고정된 길이의 다양한 타입을 저장할 수 있는 복합 데이터 타입입니다.  
튜플의 각 요소는 인덱스로 접근할 수 있습니다.

### 튜플 사용 예시
```rust
fn main() {
    let tup: (i32, f64, char) = (500, 6.4, 'A');
    println!("튜플: {:?}", tup);
    println!("첫 번째 요소: {}", tup.0);
    println!("두 번째 요소: {}", tup.1);
    println!("세 번째 요소: {}", tup.2);
}
```

---

## 📌 배열(Array)

배열은 고정된 길이의 동일한 타입을 저장하는 데이터 구조입니다.  
배열의 크기는 컴파일 시점에 결정되며, 변경할 수 없습니다.

### 배열 사용 예시
```rust
fn main() {
    let arr = [1, 2, 3, 4, 5];
    println!("배열: {:?}", arr);
    println!("첫 번째 요소: {}", arr[0]);
    println!("두 번째 요소: {}", arr[1]);
}
```

---

## 📌 벡터(Vector)

벡터는 동적 배열로, 런타임에 크기가 변경될 수 있습니다.  
벡터는 `Vec<T>` 타입으로 표현되며, 힙 메모리에 데이터를 저장합니다.

### 벡터 사용 예시
```rust
fn main() {
    let mut v = Vec::new();
    v.push(1);
    v.push(2);
    v.push(3);
    println!("벡터: {:?}", v);
    println!("첫 번째 요소: {}", v[0]);
    println!("두 번째 요소: {}", v[1]);
}
```

---

## 📌 해시맵(HashMap)

해시맵은 키-값 쌍을 저장하는 데이터 구조입니다.  
`HashMap<K, V>` 타입으로 표현되며, 키는 고유해야 합니다.

### 해시맵 사용 예시
```rust
use std::collections::HashMap;

fn main() {
    let mut scores = HashMap::new();
    scores.insert(String::from("Blue"), 10);
    scores.insert(String::from("Yellow"), 50);
    println!("해시맵: {:?}", scores);
    println!("Blue 팀의 점수: {}", scores["Blue"]);
}
```

---

## 📌 구조체(Struct)

구조체는 여러 필드를 묶어 사용자 정의 타입을 만드는 데 사용됩니다.  
구조체는 `struct` 키워드로 정의하며, 각 필드는 이름과 타입을 가집니다.

### 구조체 사용 예시
```rust
struct User {
    username: String,
    email: String,
    sign_in_count: u64,
}

fn main() {
    let user = User {
        username: String::from("john_doe"),
        email: String::from("john@example.com"),
        sign_in_count: 1,
    };
    println!("사용자 이름: {}", user.username);
    println!("이메일: {}", user.email);
    println!("로그인 횟수: {}", user.sign_in_count);
}
```

---

## 📌 열거형(Enum)

열거형은 여러 가능한 값 중 하나를 나타내는 타입입니다.  
`enum` 키워드로 정의하며, 각 값은 열거형의 변형(variant)입니다.

### 열거형 사용 예시
```rust
enum Message {
    Quit,
    Move { x: i32, y: i32 },
    Write(String),
    ChangeColor(i32, i32, i32),
}

fn main() {
    let msg = Message::Write(String::from("hello"));
    match msg {
        Message::Quit => println!("Quit"),
        Message::Move { x, y } => println!("Move to ({}, {})", x, y),
        Message::Write(text) => println!("Write: {}", text),
        Message::ChangeColor(r, g, b) => println!("Change color to ({}, {}, {})", r, g, b),
    }
}
```

---

## 📌 Option과 Result

Rust는 `Option`과 `Result` 타입을 통해 안전한 에러 처리를 지원합니다.

### Option
`Option`은 값이 있거나 없을 수 있는 경우를 표현합니다.

```rust
fn divide(a: f64, b: f64) -> Option<f64> {
    if b == 0.0 {
        None
    } else {
        Some(a / b)
    }
}

fn main() {
    let result = divide(4.0, 2.0);
    match result {
        Some(value) => println!("결과: {}", value),
        None => println!("0으로 나눌 수 없습니다."),
    }
}
```

### Result
`Result`는 성공 또는 실패를 표현합니다.

```rust
fn divide(a: f64, b: f64) -> Result<f64, String> {
    if b == 0.0 {
        Err(String::from("0으로 나눌 수 없습니다."))
    } else {
        Ok(a / b)
    }
}

fn main() {
    let result = divide(4.0, 0.0);
    match result {
        Ok(value) => println!("결과: {}", value),
        Err(e) => println!("에러: {}", e),
    }
}
```

---

## 🎯 학습 목표

이 섹션을 마치면 다음과 같은 내용을 이해할 수 있습니다:

- 튜플, 배열, 벡터, 해시맵의 사용법
- 구조체와 열거형을 통한 사용자 정의 타입 생성
- `Option`과 `Result`를 통한 안전한 에러 처리

---

## 📚 추가 자료

- [The Rust Programming Language - Chapter 4: Understanding Ownership](https://doc.rust-lang.org/book/ch04-00-understanding-ownership.html)
- [Rust by Example - Data Structures](https://doc.rust-lang.org/rust-by-example/std.html)

---

다음으로 [4. Error Handling](../4.%20Error%20Handling/)에서 Rust의 에러 처리 방법을 학습해보세요! 🦀

---

이 문서는 Rust의 데이터 구조를 체계적으로 설명하며, Mermaid 다이어그램을 통해 개념을 시각적으로 표현했습니다. 필요에 따라 추가적인 내용을 보완하거나 수정할 수 있습니다. 😊