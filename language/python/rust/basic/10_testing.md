# 🦀 Rust의 테스트와 디버깅 기법

## 📌 개요
Rust는 **안전성과 신뢰성을 보장하는 언어**이므로, 강력한 **테스트(Test) 및 디버깅(Debugging) 기능**을 제공합니다. 
이 장에서는 **Rust의 테스트 시스템과 디버깅 방법**을 배워보겠습니다.

---

## ✅ Rust의 테스트 시스템
Rust는 `cargo test`를 사용하여 **자동화된 테스트**를 수행할 수 있습니다.

### 🏗️ 기본 테스트 작성하기
```rust
fn add(a: i32, b: i32) -> i32 {
    a + b
}

#[test]
fn test_add() {
    assert_eq!(add(2, 3), 5);
}
```
📌 `#[test]` → 테스트 함수임을 표시

📌 `assert_eq!(a, b)` → 값이 같은지 확인

📌 `cargo test` → 모든 테스트 실행

---

## 🔄 다양한 테스트 방법
### 🏷️ `assert!()` 사용
```rust
#[test]
fn test_condition() {
    let x = 10;
    assert!(x > 5); // x가 5보다 크면 테스트 통과
}
```
📌 `assert!(조건)` → 조건이 `true`이면 테스트 성공

### 🏷️ 실패할 것으로 예상되는 테스트
```rust
#[test]
#[should_panic]
fn test_panic() {
    panic!("이 테스트는 실패해야 합니다!");
}
```
📌 `#[should_panic]` → 테스트가 패닉 발생 시 성공

📌 `panic!("메시지")` → 강제 패닉 발생

---

## 🏗️ 테스트 모듈과 그룹화
Rust에서는 모듈을 사용하여 **테스트를 그룹화**할 수 있습니다.

```rust
pub fn multiply(a: i32, b: i32) -> i32 {
    a * b
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_multiply() {
        assert_eq!(multiply(3, 4), 12);
    }
}
```
📌 `#[cfg(test)]` → 테스트 모듈임을 명시

📌 `use super::*;` → 상위 모듈의 함수를 가져옴

📌 `mod tests {}` → 테스트를 별도로 구성

---

## 🚀 통합 테스트(Integration Test)
Rust에서는 **단위 테스트(Unit Test)와 통합 테스트(Integration Test)** 를 지원합니다.

📌 `tests/` 디렉토리를 생성하여 **통합 테스트**를 수행할 수 있습니다.

```sh
mkdir tests
```

### 🏗️ `tests/integration_test.rs` 작성
```rust
use my_project::multiply;

#[test]
fn test_multiply() {
    assert_eq!(multiply(2, 3), 6);
}
```
📌 `tests/` 디렉토리 내부에 `.rs` 파일을 만들면 자동으로 통합 테스트로 인식됨

📌 `cargo test` 실행 시 통합 테스트도 함께 실행됨

---

## 🐞 Rust의 디버깅 기법
Rust에서는 **println!(), dbg!(), lldb/gdb** 등을 사용하여 디버깅할 수 있습니다.

### 🏷️ `println!()` 디버깅
```rust
fn main() {
    let x = 42;
    println!("x 값: {}", x);
}
```
📌 `println!()` → 변수의 값을 출력하여 확인

### 🏷️ `dbg!()` 활용
```rust
fn main() {
    let x = dbg!(2 * 5 + 3);
}
```
📌 `dbg!(값)` → **파일명, 라인번호와 함께 값 출력**

출력 예:
```
[src/main.rs:2] 2 * 5 + 3 = 13
```

---

## 🛠️ GDB 또는 LLDB 사용하기
Rust는 **GDB 및 LLDB** 디버거를 지원합니다.

📌 **디버그 빌드 실행**
```sh
cargo build --debug
```

📌 **GDB 실행**
```sh
gdb target/debug/my_project
```

📌 **LLDB 실행**
```sh
lldb target/debug/my_project
```

### 🔎 주요 디버깅 명령어
| 명령어 | 설명 |
|--------|----------|
| `break main` | main 함수에 중단점 설정 |
| `run` | 프로그램 실행 |
| `next` | 다음 줄 실행 |
| `print x` | 변수 `x` 값 출력 |
| `backtrace` | 호출 스택 확인 |

---

## 🎯 마무리
이 장에서는 **Rust의 테스트 및 디버깅 기법**을 배웠습니다.

- `cargo test`로 **테스트 실행**
- `assert!(), assert_eq!()`로 **테스트 작성**
- `#[should_panic]`로 **예외 처리 테스트**
- `println!(), dbg!(), GDB/LLDB`로 **디버깅 수행**

이제 Rust의 기본적인 내용을 마무리했습니다! 🎉

추후에는 **고급 Rust 개념과 백엔드 개발**에 대해 배워보겠습니다! 🚀