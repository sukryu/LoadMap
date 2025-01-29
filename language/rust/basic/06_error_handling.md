# 🦀 Rust의 에러 처리 (Error Handling)

## 📌 개요
Rust는 **안전한 시스템 프로그래밍 언어**로, 에러 처리를 강력하게 지원합니다. 
Rust에서는 **패닉(Panic)과 Result 타입**을 통해 **안정적인 에러 처리**를 구현할 수 있습니다.

이 장에서는 **에러 처리 기법**을 배우고 **실제 프로젝트에서 어떻게 적용할 수 있는지** 알아보겠습니다.

---

## ⚠️ 패닉(Panic)

Rust에서 **복구할 수 없는 치명적인 오류**가 발생하면 프로그램이 **패닉(Panic)** 상태에 빠집니다.

```rust
fn main() {
    panic!("치명적인 오류 발생!");
}
```
📌 프로그램이 즉시 중단되며 **스택 트레이스(Stack Trace)** 가 출력됩니다.

📌 배열의 범위를 초과하는 경우에도 패닉이 발생합니다.
```rust
fn main() {
    let arr = [1, 2, 3];
    println!("{}", arr[5]); // ❌ 패닉 발생!
}
```

---

## ✅ `Result<T, E>`를 이용한 에러 처리

Rust에서는 **복구 가능한 오류(Recoverable Error)** 를 처리하기 위해 `Result<T, E>` 타입을 사용합니다.

### 🏷️ `Result<T, E>` 기본 사용법
```rust
fn divide(a: f64, b: f64) -> Result<f64, String> {
    if b == 0.0 {
        Err(String::from("0으로 나눌 수 없습니다!"))
    } else {
        Ok(a / b)
    }
}

fn main() {
    match divide(10.0, 2.0) {
        Ok(result) => println!("결과: {}", result),
        Err(error) => println!("오류 발생: {}", error),
    }
}
```
📌 `Ok(value)` → 정상적인 결과 반환

📌 `Err(error)` → 에러 메시지 반환

📌 `match` 문을 사용하여 결과 처리

---

## 🔄 `?` 연산자를 이용한 간편한 에러 처리

Rust에서는 **`?` 연산자**를 사용하여 **더 간결하게 에러를 처리**할 수 있습니다.

```rust
fn read_file() -> std::io::Result<String> {
    std::fs::read_to_string("file.txt") // 에러가 발생하면 자동으로 반환됨
}

fn main() {
    match read_file() {
        Ok(content) => println!("파일 내용: {}", content),
        Err(e) => println!("파일을 읽을 수 없습니다: {}", e),
    }
}
```
📌 `?` 연산자를 사용하면 `Result` 타입의 값이 자동으로 반환됨

📌 에러 발생 시, `Err`를 즉시 반환하여 함수 실행을 중단함

---

## 🔄 여러 개의 에러 타입 처리하기

Rust에서는 다양한 에러 타입을 처리하기 위해 **`Box<dyn std::error::Error>`** 를 활용할 수 있습니다.

```rust
use std::fs::File;
use std::io::{self, Read};

fn read_file() -> Result<String, Box<dyn std::error::Error>> {
    let mut file = File::open("file.txt")?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    Ok(contents)
}
```
📌 `Box<dyn std::error::Error>`를 사용하면 **여러 종류의 에러를 처리**할 수 있음

📌 `?` 연산자를 활용하여 에러가 발생하면 자동으로 `Result`를 반환함

---

## 🚀 `unwrap()`과 `expect()`

Rust에서는 `Result<T, E>` 타입의 값을 강제로 추출하는 **`unwrap()`**과 **`expect()`**를 제공합니다.

```rust
fn main() {
    let result: Result<i32, &str> = Ok(10);
    println!("값: {}", result.unwrap()); // 10 반환
}
```
🚨 **주의!** `unwrap()`을 사용할 때 `Err`가 발생하면 패닉이 발생합니다.

```rust
fn main() {
    let result: Result<i32, &str> = Err("에러 발생");
    println!("값: {}", result.unwrap()); // ❌ 패닉 발생!
}
```

📌 `expect()`는 **커스텀 에러 메시지**를 포함할 수 있습니다.
```rust
fn main() {
    let result: Result<i32, &str> = Err("에러 발생");
    println!("값: {}", result.expect("에러가 발생했습니다!"));
}
```

---

## 🎯 마무리

이 장에서는 **Rust의 에러 처리 기법**을 배웠습니다.

- **패닉(Panic)** 을 사용하면 프로그램이 강제 종료됨
- **`Result<T, E>`** 를 활용하여 에러를 안전하게 처리 가능
- **`?` 연산자** 를 이용해 에러를 간결하게 처리 가능
- **`unwrap()`과 `expect()`** 는 주의해서 사용해야 함

다음 장에서는 **Rust의 동시성(Concurrency)과 비동기(Async) 프로그래밍**에 대해 배워보겠습니다! 🚀
