# 🦀 Rust의 고급 메모리 안전성과 최적화

## 📌 개요
Rust는 **메모리 안전성(Memory Safety)** 을 보장하면서도 **성능 최적화**가 가능한 언어입니다. 
이 장에서는 **고급 메모리 관리 기법과 성능 최적화 전략**을 다뤄보겠습니다.

---

## 🔒 Rust의 메모리 안전성 원칙
Rust의 메모리 모델은 **소유권(Ownership), 차용(Borrowing), 라이프타임(Lifetime)** 을 기반으로 합니다.

### 🏷️ 소유권과 이동(Move) 복습
```rust
fn main() {
    let s1 = String::from("Rust");
    let s2 = s1; // s1의 소유권이 s2로 이동(Move)
    // println!("{}", s1); // ❌ 컴파일 에러 발생!
    println!("{}", s2);
}
```
📌 소유권이 이동되면 원래 변수를 사용할 수 없음

📌 깊은 복사가 필요하면 `.clone()`을 사용해야 함

### 🏷️ 복사(Clone)와 참조(Copy)
```rust
fn main() {
    let x = 10;
    let y = x; // 기본 타입(i32)은 Copy 특성을 가짐
    println!("x: {}, y: {}", x, y);
}
```
📌 `i32`, `f64`, `bool` 등은 **Copy 트레이트**가 적용되어 이동이 아닌 복사가 이루어짐

---

## 🚀 `Box<T>`를 활용한 힙 할당
Rust에서는 **Box 스마트 포인터(Box<T>)** 를 사용하여 힙(Heap)에 데이터를 저장할 수 있습니다.

### 🏷️ `Box<T>` 기본 사용법
```rust
fn main() {
    let b = Box::new(42);
    println!("b의 값: {}", b);
}
```
📌 `Box::new(42)` → `42` 값을 힙에 저장하고 스마트 포인터(`b`)가 이를 가리킴

📌 `b`가 범위를 벗어나면 자동으로 메모리 해제됨

### 🏷️ 재귀적 데이터 구조에서 `Box<T>` 활용
```rust
enum List {
    Cons(i32, Box<List>),
    Nil,
}

fn main() {
    let list = List::Cons(1, Box::new(List::Cons(2, Box::new(List::Nil))));
}
```
📌 `Box<T>`를 사용하지 않으면 **재귀 타입 크기를 컴파일러가 알 수 없음**

---

## 🏗️ `Rc<T>`를 활용한 다중 소유권
Rust에서는 **여러 개의 소유자가 같은 데이터를 가리켜야 할 경우**, `Rc<T>`(Reference Counting) 스마트 포인터를 사용합니다.

### 🏷️ `Rc<T>` 기본 사용법
```rust
use std::rc::Rc;

fn main() {
    let a = Rc::new(5);
    let b = Rc::clone(&a);
    println!("a = {}, b = {}", a, b);
}
```
📌 `Rc::new(5)` → `5` 값을 힙에 저장하고 참조 카운트 증가

📌 `Rc::clone(&a)` → **새로운 복사가 아닌 참조 카운트를 증가**

📌 `a`와 `b`는 동일한 값을 가리키며, 마지막 참조가 해제될 때 메모리 해제됨

---

## 🔄 `Arc<T>`를 활용한 멀티스레드 환경
Rust의 `Rc<T>`는 **싱글스레드 환경에서만 동작**합니다. 멀티스레드 환경에서는 **`Arc<T>`(Atomic Reference Counting)** 을 사용해야 합니다.

### 🏷️ `Arc<T>`를 사용한 안전한 멀티스레드 공유
```rust
use std::sync::Arc;
use std::thread;

fn main() {
    let data = Arc::new(100);
    let mut handles = vec![];

    for _ in 0..5 {
        let data = Arc::clone(&data);
        let handle = thread::spawn(move || {
            println!("스레드에서 접근: {}", data);
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }
}
```
📌 `Arc::clone(&data)` → 멀티스레드 환경에서 안전하게 공유

📌 모든 스레드가 종료되면 마지막 참조가 사라지면서 자동으로 메모리 해제됨

---

## 🚀 성능 최적화 기법
Rust는 **제로 비용 추상화(Zero-cost Abstraction)** 를 통해 성능을 극대화할 수 있습니다.

### 🏷️ `inline`을 활용한 성능 향상
```rust
#[inline(always)]
fn add(x: i32, y: i32) -> i32 {
    x + y
}
```
📌 `#[inline(always)]` → 함수 호출을 **인라인(inline) 처리**하여 성능 향상

📌 주의: **모든 경우에 인라인이 성능을 높이는 것은 아님**

### 🏷️ `unsafe` 블록 활용 (주의 필요)
```rust
fn main() {
    let mut num = 5;
    let r = &mut num as *mut i32; // Raw 포인터 생성
    unsafe {
        *r += 1;
    }
    println!("num: {}", num);
}
```
📌 `unsafe` → Rust의 안전성 검사 없이 직접 메모리 조작 가능

📌 반드시 필요한 경우에만 사용해야 함

---

## 🎯 마무리
이 장에서는 **Rust의 고급 메모리 관리 기법과 성능 최적화 전략**을 배웠습니다.

- `Box<T>`를 활용한 **힙 할당 및 재귀 타입 관리**
- `Rc<T>`를 사용하여 **싱글스레드에서 다중 소유권 관리**
- `Arc<T>`를 이용하여 **멀티스레드 환경에서 안전한 참조 카운팅**
- `unsafe`를 활용한 **로우 포인터 직접 조작**
- `inline(always)`를 사용한 **성능 최적화**

다음 장에서는 **Rust의 매크로(Macro) 시스템**을 배워보겠습니다! 🚀
