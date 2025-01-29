# 🦀 Rust의 성능 최적화 및 시스템 프로그래밍 기법

## 📌 개요
Rust는 **안전성**과 **성능**을 모두 고려하여 설계된 언어입니다. 이를 활용하여 **최적화된 시스템 프로그래밍**을 할 수 있습니다.

이 장에서는 **Rust의 성능 최적화 기법과 시스템 프로그래밍의 핵심 개념**을 다루겠습니다.

---

## 🚀 성능 최적화를 위한 주요 기법

### 🏷️ 1️⃣ `#[inline(always)]`을 활용한 인라인 최적화
컴파일러가 함수 호출을 최적화할 수 있도록 인라인을 명시할 수 있습니다.

```rust
#[inline(always)]
fn add(a: i32, b: i32) -> i32 {
    a + b
}

fn main() {
    let result = add(5, 10);
    println!("결과: {}", result);
}
```
📌 `#[inline(always)]` → 함수 호출을 **인라인 처리**하여 성능 향상 가능

📌 주의: 과도한 인라인 사용은 바이너리 크기를 증가시킬 수 있음

---

### 🏷️ 2️⃣ `Unsafe` 코드 활용 (주의 필요)
`unsafe` 블록을 사용하면 Rust의 안전성 검사를 우회할 수 있습니다.

```rust
fn main() {
    let mut x: i32 = 42;
    let r = &mut x as *mut i32; // Raw 포인터 생성
    unsafe {
        *r += 1;
    }
    println!("x: {}", x);
}
```
📌 `unsafe` → Rust의 **안전성 검사 없이 직접 메모리 조작 가능**

📌 **잘못된 포인터 접근 시, Segmentation Fault 발생 가능**

---

### 🏷️ 3️⃣ `SIMD`를 활용한 고속 연산
Rust의 `std::arch` 모듈을 사용하면 **SIMD(Single Instruction, Multiple Data) 연산**을 최적화할 수 있습니다.

```rust
#[cfg(target_arch = "x86_64")]
use std::arch::x86_64::_mm_add_ps;

fn main() {
    #[cfg(target_arch = "x86_64")]
    unsafe {
        let a = std::mem::transmute([1.0f32, 2.0, 3.0, 4.0]);
        let b = std::mem::transmute([5.0f32, 6.0, 7.0, 8.0]);
        let result = _mm_add_ps(a, b);
        println!("SIMD 연산 결과: {:?}", result);
    }
}
```
📌 `#[cfg(target_arch = "x86_64")]` → 특정 CPU 아키텍처에서만 실행되도록 제한

📌 `_mm_add_ps` → **4개의 부동 소수점 값을 한 번에 더하는 SIMD 연산**

---

### 🏷️ 4️⃣ `mmap`을 활용한 고속 파일 I/O
Rust에서는 `mmap`을 사용하여 **메모리 매핑된 파일 입출력(Memory-mapped I/O)** 을 수행할 수 있습니다.

```rust
use std::fs::File;
use std::io::{Write, Read};
use memmap2::Mmap;

fn main() {
    let file = File::open("data.txt").expect("파일을 열 수 없음");
    let mmap = unsafe { Mmap::map(&file).expect("메모리 매핑 실패") };
    println!("파일 내용: {}", std::str::from_utf8(&mmap).unwrap());
}
```
📌 `Mmap::map(&file)` → 파일을 메모리에 직접 매핑하여 **빠른 읽기 성능 제공**

📌 `std::str::from_utf8(&mmap).unwrap()` → 파일 내용을 문자열로 변환하여 출력

---

## 🏗️ 시스템 프로그래밍 기법
Rust는 운영체제와 저수준 하드웨어와 직접 상호 작용할 수 있습니다.

### 🏷️ 1️⃣ `nix` 크레이트를 활용한 시스템 호출(Syscall)
`nix` 크레이트를 사용하면 Linux 및 Unix의 **시스템 호출(SYS Call)** 을 쉽게 사용할 수 있습니다.

```rust
use nix::unistd::getpid;

fn main() {
    let pid = getpid();
    println!("현재 프로세스 ID: {}", pid);
}
```
📌 `nix::unistd::getpid()` → 현재 프로세스의 PID 가져오기

📌 시스템 프로그래밍에서 **프로세스 및 파일 조작**에 사용됨

---

### 🏷️ 2️⃣ `epoll`을 활용한 비동기 I/O 이벤트 처리
Rust는 Linux의 `epoll`을 활용하여 고성능 네트워크 프로그래밍을 지원합니다.

```rust
use mio::{Events, Poll, Token, Interest};
use std::net::TcpListener;

fn main() {
    let listener = TcpListener::bind("127.0.0.1:8080").expect("바인딩 실패");
    let poll = Poll::new().unwrap();
    let mut events = Events::with_capacity(128);
    
    loop {
        poll.poll(&mut events, None).unwrap();
        for event in &events {
            println!("이벤트 발생: {:?}", event);
        }
    }
}
```
📌 `mio` 크레이트 → Rust의 **비동기 이벤트 기반 I/O 처리** 지원

📌 `poll.poll(&mut events, None)` → 비동기적으로 I/O 이벤트 감지

📌 **고성능 네트워크 서버 개발 시 활용 가능**

---

## 🎯 마무리
이 장에서는 **Rust의 성능 최적화 및 시스템 프로그래밍 기법**을 배웠습니다.

- `#[inline(always)]`를 활용하여 **인라인 최적화**
- `unsafe` 블록을 사용하여 **메모리 직접 조작**
- `SIMD`를 활용하여 **고속 벡터 연산 수행**
- `mmap`을 사용하여 **빠른 파일 입출력** 수행
- `nix` 크레이트를 활용하여 **시스템 호출(Syscall) 수행**
- `mio`를 사용하여 **고성능 비동기 이벤트 처리**

다음 장에서는 **Rust 기반 웹 백엔드 개발(Actix 및 Axum 활용)** 에 대해 배워보겠습니다! 🚀
