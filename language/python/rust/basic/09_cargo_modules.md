# 🦀 Rust의 Cargo와 모듈 시스템

## 📌 개요
Rust는 **Cargo 패키지 관리자**와 **모듈 시스템**을 통해 **프로젝트 관리를 효율적으로 수행**할 수 있습니다.
이 장에서는 **Cargo 기본 사용법, 의존성 관리, 모듈 시스템**에 대해 배우겠습니다.

---

## 🚀 Cargo란?
Cargo는 Rust의 **패키지 관리자**로, 다음과 같은 기능을 제공합니다.

✅ 프로젝트 생성 및 빌드
✅ 의존성(Dependencies) 관리
✅ 테스트 및 배포 지원

### 🏷️ Cargo 설치 확인
```sh
cargo --version
```
📌 Cargo가 설치되어 있지 않다면, Rust 설치 시 포함되므로 **rustup**을 사용하여 설치할 수 있습니다.

```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

---

## 🏗️ Cargo 프로젝트 생성 및 실행

### 🏷️ 새로운 프로젝트 생성
```sh
cargo new my_project
cd my_project
```
📌 `cargo new`를 실행하면 프로젝트 폴더가 생성됩니다.

```sh
my_project/
 ├── Cargo.toml  # 프로젝트 설정 및 의존성 관리
 ├── src/
 │   ├── main.rs  # 프로그램 진입점
```

### 🏷️ 프로젝트 빌드 및 실행
```sh
cargo build    # 프로젝트 빌드
cargo run      # 프로그램 실행
cargo check    # 빠르게 코드 검사
```

📌 `cargo build`는 `target/` 디렉토리에 실행 파일을 생성합니다.

📌 `cargo run`은 빌드 후 실행까지 수행합니다.

📌 `cargo check`는 빌드하지 않고 오류만 검사합니다.

---

## 🔄 Cargo 의존성 관리
Cargo는 프로젝트의 **외부 라이브러리(크레이트, Crates)** 를 쉽게 관리할 수 있습니다.

### 🏷️ `Cargo.toml` 파일에서 의존성 추가
```toml
[dependencies]
rand = "0.8"
serde = { version = "1.0", features = ["derive"] }
```
📌 `rand = "0.8"` → `rand` 크레이트의 최신 0.8 버전 설치

📌 `serde = { version = "1.0", features = ["derive"] }` → 추가 기능 포함한 의존성 설정

### 🏷️ 의존성 설치
```sh
cargo build  # 자동으로 의존성 설치
cargo update # 최신 버전으로 업데이트
```

---

## 📦 모듈 시스템과 패키지 구조
Rust의 모듈 시스템을 사용하면 코드를 **구성하고 재사용**할 수 있습니다.

### 🏗️ 기본 모듈 사용법
```rust
mod greetings {
    pub fn hello() {
        println!("안녕하세요, Rust!");
    }
}

fn main() {
    greetings::hello();
}
```
📌 `mod greetings` → 새로운 모듈 생성

📌 `pub fn hello()` → **공개 함수(public function)** 선언

📌 `greetings::hello();` → **모듈 내 함수 호출**

---

## 📂 파일 기반 모듈 시스템
Rust에서는 파일을 기반으로 모듈을 관리할 수도 있습니다.

### 🏷️ 프로젝트 구조
```sh
src/
 ├── main.rs
 ├── lib.rs  # 라이브러리 모듈
 ├── greetings.rs  # 별도 모듈 파일
```

### 🏷️ `greetings.rs` 파일 생성
```rust
pub fn hello() {
    println!("안녕하세요, Rust 모듈!");
}
```

### 🏷️ `main.rs`에서 모듈 사용
```rust
mod greetings;

fn main() {
    greetings::hello();
}
```
📌 `mod greetings;` → `greetings.rs` 파일을 모듈로 사용

📌 `greetings::hello();` → 외부 파일의 함수 호출

---

## 🏗️ `use` 키워드를 활용한 모듈 호출
모듈이 깊어질 경우, `use` 키워드를 사용하여 접근을 단순화할 수 있습니다.

### 🏷️ 중첩 모듈 구조
```rust
mod utils {
    pub mod greetings {
        pub fn hello() {
            println!("안녕하세요, 모듈 시스템!");
        }
    }
}
```

### 🏷️ `use` 키워드로 모듈 호출
```rust
use utils::greetings;

fn main() {
    greetings::hello();
}
```
📌 `use utils::greetings;` → `utils::greetings::hello()`를 `greetings::hello()`로 간략화

---

## 🚀 라이브러리 패키지(`lib.rs`)

`lib.rs` 파일을 사용하면 **라이브러리 패키지**를 만들 수 있습니다.

### 🏗️ 프로젝트 구조
```sh
src/
 ├── main.rs  # 실행 파일
 ├── lib.rs   # 라이브러리 모듈
```

### 🏗️ `lib.rs` 파일 생성
```rust
pub mod greetings {
    pub fn hello() {
        println!("안녕하세요, 라이브러리 패키지!");
    }
}
```

### 🏗️ `main.rs`에서 라이브러리 사용
```rust
use my_project::greetings;

fn main() {
    greetings::hello();
}
```
📌 `use my_project::greetings;` → 라이브러리 패키지의 모듈 호출

📌 `cargo build` 시 `target/debug/libmy_project.rlib` 생성

---

## 🎯 마무리
이 장에서는 **Rust의 Cargo와 모듈 시스템**을 학습했습니다.

- `Cargo`를 사용한 **프로젝트 생성, 빌드 및 실행**
- `Cargo.toml`에서 **의존성 관리**
- **모듈 시스템을 활용한 코드 구성**

다음 장에서는 **Rust의 테스트와 디버깅 기법**에 대해 배워보겠습니다! 🚀
