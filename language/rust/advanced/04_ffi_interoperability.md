# 🦀 Rust의 FFI (외부 함수 인터페이스)와 C/C++ 연동

## 📌 개요
Rust는 **FFI(Foreign Function Interface)** 를 통해 C 및 C++과의 상호 운용이 가능합니다. 이를 통해 Rust에서 **C/C++ 라이브러리를 호출하거나, Rust 라이브러리를 C/C++에서 사용할 수 있습니다.**

이 장에서는 **Rust와 C/C++ 연동 방법 및 FFI의 주요 개념**을 다루겠습니다.

---

## 🔗 Rust에서 C 코드 호출하기
Rust에서는 `extern "C"` 키워드를 사용하여 **C 함수 및 변수**를 호출할 수 있습니다.

### 🏷️ C 라이브러리 호출하기
C 코드 (`c_lib.c`):
```c
#include <stdio.h>

void hello_c() {
    printf("Hello from C!\n");
}
```

Rust 코드 (`main.rs`):
```rust
extern "C" {
    fn hello_c();
}

fn main() {
    unsafe {
        hello_c();
    }
}
```
📌 `extern "C" {}` → C 함수 선언

📌 `unsafe {}` → 외부 함수는 안전성 검사가 불가능하므로 `unsafe` 블록 필요

📌 `hello_c();` → Rust에서 C 함수를 호출

### 🏗️ 컴파일 및 실행
```sh
gcc -c -o c_lib.o c_lib.c  # C 코드 컴파일
ar rcs libclib.a c_lib.o   # 정적 라이브러리 생성
rustc main.rs -L . -l clib # Rust 코드 컴파일
./main                     # 실행
```
📌 `-L . -l clib` → 현재 디렉토리(`.`)에서 `libclib.a`를 연결하여 실행

---

## 🔄 Rust에서 C 데이터 타입 사용
Rust와 C는 기본 데이터 타입이 다를 수 있으므로, `std::os::raw` 모듈을 활용해야 합니다.

```rust
use std::os::raw::{c_int, c_char};

extern "C" {
    fn add(a: c_int, b: c_int) -> c_int;
    fn print_message(msg: *const c_char);
}
```
📌 `c_int` → C의 `int` 타입과 매칭됨

📌 `*const c_char` → C의 `char*` 타입을 나타냄

---

## 🚀 Rust에서 C++ 코드 호출하기
Rust는 **C++과 직접 연동할 수 없으며, `extern "C"`를 통해 C 스타일 인터페이스를 사용해야 합니다.**

### 🏷️ C++ 코드 (`cpp_lib.cpp`)
```cpp
#include <iostream>
extern "C" {
    void hello_cpp() {
        std::cout << "Hello from C++!" << std::endl;
    }
}
```
📌 `extern "C"` → C++ 함수가 C 방식의 이름 맹글링(Name Mangling)을 따르도록 지정

### 🏗️ Rust 코드 (`main.rs`)
```rust
extern "C" {
    fn hello_cpp();
}

fn main() {
    unsafe {
        hello_cpp();
    }
}
```
📌 `extern "C"` → Rust에서 C++ 함수를 호출하기 위해 C 방식의 이름 지정

### 🏗️ 컴파일 및 실행
```sh
g++ -c -o cpp_lib.o cpp_lib.cpp  # C++ 컴파일
ar rcs libcpplib.a cpp_lib.o     # 정적 라이브러리 생성
rustc main.rs -L . -l cpplib     # Rust 코드 컴파일
./main                           # 실행
```
📌 `-L . -l cpplib` → C++ 정적 라이브러리를 Rust에 연결하여 실행

---

## 🔄 C에서 Rust 함수 호출하기
Rust에서 작성한 함수를 **C에서 호출하려면 `#[no_mangle]`과 `extern "C"`를 사용해야 합니다.**

### 🏷️ Rust 라이브러리 코드 (`lib.rs`)
```rust
#[no_mangle]
pub extern "C" fn rust_function() {
    println!("Hello from Rust!");
}
```
📌 `#[no_mangle]` → 함수 이름이 변형되지 않도록 지정

📌 `pub extern "C" fn` → C에서 호출 가능한 Rust 함수

### 🏷️ C 코드 (`main.c`)
```c
#include <stdio.h>

extern void rust_function();

int main() {
    rust_function();
    return 0;
}
```
📌 `extern void rust_function();` → Rust에서 제공하는 함수 선언

### 🏗️ 컴파일 및 실행
```sh
rustc --crate-type=staticlib lib.rs -o librustlib.a  # Rust 라이브러리 컴파일
gcc main.c -L . -l rustlib -o main                  # C 코드 컴파일
./main                                              # 실행
```
📌 `--crate-type=staticlib` → 정적 라이브러리(`.a`) 생성

📌 `-l rustlib` → Rust 정적 라이브러리 연결

---

## 🔥 Rust에서 C 문자열 처리하기
C와 Rust의 문자열 표현 방식이 다르므로 변환이 필요합니다.

```rust
use std::ffi::{CStr, CString};
use std::os::raw::c_char;

#[no_mangle]
pub extern "C" fn print_message(msg: *const c_char) {
    let c_str = unsafe { CStr::from_ptr(msg) };
    println!("C에서 받은 메시지: {}", c_str.to_str().unwrap());
}
```
📌 `CStr::from_ptr(msg)` → C 문자열을 Rust 문자열로 변환

📌 `CString::new("Hello").unwrap().into_raw()` → Rust 문자열을 C 스타일로 변환

---

## 🎯 마무리
이 장에서는 **Rust와 C/C++ 연동(FFI)** 을 배웠습니다.

- `extern "C"`를 사용하여 **C 함수를 Rust에서 호출**
- `#[no_mangle]`과 `extern "C"`를 이용하여 **Rust 함수를 C에서 호출**
- `std::ffi::CStr`, `CString`을 활용하여 **C 문자열과 Rust 문자열 변환**
- **C++과 연동**할 때 `extern "C"`을 사용하여 C 스타일 인터페이스로 변환

다음 장에서는 **Rust의 성능 최적화 및 시스템 프로그래밍 기법**을 배워보겠습니다! 🚀
