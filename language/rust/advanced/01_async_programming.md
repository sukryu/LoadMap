# 🦀 Rust 비동기 프로그래밍 (Async Programming)

## 📌 개요
Rust의 **비동기 프로그래밍(Async Programming)** 은 **효율적인 동시 실행**을 가능하게 합니다. Rust에서는 **`async`/`await`**, **Future**, 그리고 **비동기 런타임(Tokio, async-std)** 를 활용하여 비동기 처리를 수행할 수 있습니다.

이 장에서는 **Rust의 비동기 프로그래밍 개념과 실전 활용법**을 배워보겠습니다.

---

## 🚀 `async`와 `await`의 기본 개념
Rust에서 비동기 코드를 작성하려면 **`async` 키워드**와 **`await` 키워드**를 사용해야 합니다.

### 🏷️ 비동기 함수 작성하기
```rust
async fn hello() {
    println!("안녕하세요, 비동기 Rust!");
}
```
📌 `async fn` → 비동기 함수 선언

📌 비동기 함수는 **즉시 실행되지 않으며**, 반드시 `.await`을 사용해야 실행됨


### 🏷️ `await`을 사용하여 비동기 함수 실행하기
```rust
async fn hello() {
    println!("안녕하세요, 비동기 Rust!");
}

#[tokio::main]
async fn main() {
    hello().await;
}
```
📌 `hello().await;` → `async` 함수 실행을 기다림

📌 `#[tokio::main]` → `tokio` 런타임을 사용하여 `main()`을 비동기 함수로 실행

---

## 🔄 `async` 블록과 `Future`
Rust에서 **비동기 함수는 `Future` 타입을 반환**합니다.

```rust
use std::future::Future;

fn async_fn() -> impl Future<Output = i32> {
    async { 42 }
}

#[tokio::main]
async fn main() {
    let result = async_fn().await;
    println!("결과: {}", result);
}
```
📌 `async {}` 블록 → **Future를 반환하는 익명 비동기 코드 블록**

📌 `impl Future<Output = i32>` → 이 함수는 `Future`를 반환하며 최종적으로 `i32` 값을 반환

---

## 🏗️ 비동기 실행 모델과 런타임
Rust의 **비동기 함수는 직접 실행되지 않으며, 반드시 실행기(Runtime)가 필요합니다.** 대표적인 런타임은 `Tokio`와 `async-std`입니다.

### 🏷️ `Tokio` 런타임 사용하기
```rust
use tokio::time::{sleep, Duration};

async fn task() {
    println!("작업 시작");
    sleep(Duration::from_secs(2)).await;
    println!("작업 완료");
}

#[tokio::main]
async fn main() {
    task().await;
}
```
📌 `tokio::time::sleep` → 비동기적으로 **2초 동안 대기**

📌 `#[tokio::main]` → Tokio 런타임에서 실행됨

### 🏷️ `async-std` 런타임 사용하기
```rust
use async_std::task;

async fn task() {
    println!("작업 시작");
    task::sleep(std::time::Duration::from_secs(2)).await;
    println!("작업 완료");
}

fn main() {
    task::block_on(task());
}
```
📌 `async-std::task::block_on()` → 비동기 코드를 동기적으로 실행

---

## 🔄 여러 개의 비동기 작업 실행하기
여러 개의 `async` 함수를 동시에 실행하려면 `join!`을 사용할 수 있습니다.

### 🏷️ `tokio::join!`을 사용한 병렬 실행
```rust
use tokio::time::{sleep, Duration};

async fn task1() {
    sleep(Duration::from_secs(2)).await;
    println!("Task 1 완료");
}

async fn task2() {
    sleep(Duration::from_secs(1)).await;
    println!("Task 2 완료");
}

#[tokio::main]
async fn main() {
    tokio::join!(task1(), task2());
    println!("모든 작업 완료!");
}
```
📌 `tokio::join!` → 여러 개의 비동기 작업을 동시에 실행

📌 `task1()`은 2초, `task2()`는 1초 동안 대기 후 실행됨

---

## 🚀 `select!`을 활용한 첫 번째 완료된 작업 처리
```rust
use tokio::time::{sleep, Duration};
use tokio::select;

async fn task1() {
    sleep(Duration::from_secs(2)).await;
    println!("Task 1 완료");
}

async fn task2() {
    sleep(Duration::from_secs(1)).await;
    println!("Task 2 완료");
}

#[tokio::main]
async fn main() {
    select! {
        _ = task1() => println!("첫 번째 완료된 작업: Task 1"),
        _ = task2() => println!("첫 번째 완료된 작업: Task 2"),
    }
}
```
📌 `tokio::select!` → **첫 번째 완료된 작업을 우선적으로 처리**

📌 `task2()`가 먼저 완료되므로 `Task 2 완료`가 먼저 출력됨

---

## 🎯 마무리
이 장에서는 **Rust의 비동기 프로그래밍 기법**을 배웠습니다.

- `async fn`과 `.await`을 사용하여 **비동기 함수 실행**
- `Future`와 `async` 블록을 활용한 **비동기 작업 관리**
- `Tokio` 및 `async-std` 런타임을 활용한 **비동기 실행 환경 구성**
- `join!`과 `select!`을 이용한 **동시 실행 및 첫 번째 완료 작업 처리**

다음 장에서는 **Rust의 메모리 안전성과 고급 최적화 기법**을 배워보겠습니다! 🚀
