# 🦀 Rust의 입출력(IO) 및 파일 시스템

## 📌 개요
Rust에서는 `std::io` 및 `std::fs` 모듈을 활용하여 **파일 시스템과 입출력(IO) 작업**을 수행할 수 있습니다.
이 장에서는 **표준 입출력 처리, 파일 읽기/쓰기, 오류 처리** 방법을 배워보겠습니다.

---

## 🏗️ 표준 입출력(Standard Input/Output)
Rust에서는 `std::io` 모듈을 사용하여 **사용자로부터 입력을 받고 출력**할 수 있습니다.

### 🏷️ 기본적인 입력 받기
```rust
use std::io;

fn main() {
    let mut input = String::new();
    println!("이름을 입력하세요:");
    io::stdin().read_line(&mut input).expect("입력 실패");
    println!("입력한 이름: {}", input.trim());
}
```
📌 `io::stdin().read_line(&mut input)` → 사용자 입력을 받음

📌 `trim()` → 입력된 문자열 끝의 개행 문자(`\n`)를 제거

---

### 🏷️ 파일 쓰기 (Write to File)
```rust
use std::fs::File;
use std::io::Write;

fn main() {
    let mut file = File::create("hello.txt").expect("파일 생성 실패");
    file.write_all(b"Hello, Rust!").expect("파일에 쓰기 실패");
    println!("파일이 생성되었습니다.");
}
```
📌 `File::create("파일명")` → 파일 생성 (기존 파일 덮어쓰기)

📌 `write_all(b"Hello, Rust!")` → 바이트 스트림을 파일에 기록

📌 `expect("오류 메시지")` → 오류 발생 시 메시지를 출력하고 종료

---

### 🏷️ 파일 읽기 (Read from File)
```rust
use std::fs;

fn main() {
    let content = fs::read_to_string("hello.txt").expect("파일 읽기 실패");
    println!("파일 내용: {}", content);
}
```
📌 `fs::read_to_string("파일명")` → 파일의 전체 내용을 문자열로 읽음

📌 `expect("파일 읽기 실패")` → 파일이 없거나 읽을 수 없으면 오류 발생

---

### 🏷️ 파일 존재 여부 확인
```rust
use std::path::Path;

fn main() {
    let path = "hello.txt";
    if Path::new(path).exists() {
        println!("파일이 존재합니다.");
    } else {
        println!("파일이 없습니다.");
    }
}
```
📌 `Path::new("파일명").exists()` → 파일이 존재하는지 여부 확인

📌 `exists()` → `true`(존재함) / `false`(존재하지 않음)를 반환

---

## 🔄 에러 처리와 파일 조작
Rust에서는 `Result<T, E>` 타입을 활용하여 파일 작업 중 발생할 수 있는 오류를 처리할 수 있습니다.

### 🏷️ 안전한 파일 읽기
```rust
use std::fs::File;
use std::io::{self, Read};

fn read_file(path: &str) -> Result<String, io::Error> {
    let mut file = File::open(path)?;
    let mut content = String::new();
    file.read_to_string(&mut content)?;
    Ok(content)
}

fn main() {
    match read_file("hello.txt") {
        Ok(content) => println!("파일 내용: {}", content),
        Err(e) => println!("파일 읽기 오류: {}", e),
    }
}
```
📌 `File::open(path)?` → 파일을 열다가 오류가 발생하면 자동 반환

📌 `read_to_string(&mut content)?` → 내용을 읽고 `Result` 타입 반환

📌 `match` 문을 사용하여 성공(`Ok`)과 실패(`Err`) 처리

---

## 🚀 디렉토리 생성 및 삭제

### 🏷️ 디렉토리 생성하기
```rust
use std::fs;

fn main() {
    fs::create_dir("my_folder").expect("디렉토리 생성 실패");
    println!("디렉토리 생성 완료!");
}
```
📌 `fs::create_dir("폴더명")` → 새 디렉토리 생성

### 🏷️ 디렉토리 삭제하기
```rust
use std::fs;

fn main() {
    fs::remove_dir("my_folder").expect("디렉토리 삭제 실패");
    println!("디렉토리 삭제 완료!");
}
```
📌 `fs::remove_dir("폴더명")` → **빈 디렉토리만 삭제 가능**

📌 **디렉토리 내 파일이 있을 경우 `fs::remove_dir_all("폴더명")` 사용**

---

## 🎯 마무리

이 장에서는 **Rust의 입출력 및 파일 시스템**을 다뤘습니다.

- `std::io` 를 사용한 **표준 입출력 처리**
- `std::fs` 를 사용한 **파일 읽기/쓰기 및 오류 처리**
- **디렉토리 생성 및 삭제**

다음 장에서는 **Rust의 Cargo와 모듈 시스템**에 대해 배워보겠습니다! 🚀
