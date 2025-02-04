# 🦀 Rust의 동시성(Concurrency)과 비동기(Async) 프로그래밍

## 📌 개요
Rust는 안전하고 효율적인 **동시성(Concurrency)** 을 제공하기 위해 **스레드(Thread), 메시지 패싱(Message Passing), 공유 상태(Shared State) 및 비동기(Async)** 프로그래밍을 지원합니다.

이 장에서는 **Rust에서 동시성을 다루는 방법과 비동기 프로그래밍의 기초**를 배우겠습니다.

---

## 🏗️ 기본적인 스레드 생성
Rust에서는 표준 라이브러리의 `std::thread` 모듈을 사용하여 **스레드(Thread)** 를 생성할 수 있습니다.

```rust
use std::thread;
use std::time::Duration;

fn main() {
    thread::spawn(|| {
        for i in 1..5 {
            println!("새로운 스레드: {}", i);
            thread::sleep(Duration::from_millis(500));
        }
    });

    for i in 1..5 {
        println!("메인 스레드: {}", i);
        thread::sleep(Duration::from_millis(500));
    }
}
```

🔹 `thread::spawn`을 사용하여 새로운 스레드를 생성
🔹 `thread::sleep(Duration::from_millis(500))` 을 사용하여 실행을 잠시 중단
🔹 메인 스레드가 먼저 종료되면, 새로 생성된 스레드는 종료될 수도 있음

---

## 🏷️ 스레드 간 데이터 공유 (Move)
Rust에서는 **클로저(Closure)** 내에서 변수를 안전하게 사용하기 위해 `move` 키워드를 활용할 수 있습니다.

```rust
use std::thread;

fn main() {
    let data = vec![1, 2, 3, 4, 5];

    let handle = thread::spawn(move || {
        println!("데이터: {:?}", data);
    });

    handle.join().unwrap();
}
```

📌 **`move`를 사용하면, 클로저 내부에서 소유권을 가져올 수 있습니다.**

📌 `handle.join().unwrap();` 를 호출하여 메인 스레드가 새 스레드의 종료를 기다릴 수 있습니다.

---

## 🔄 채널을 이용한 메시지 전달
Rust에서는 `std::sync::mpsc` (Multiple Producer, Single Consumer)을 사용하여 **스레드 간 데이터를 안전하게 주고받을 수 있습니다.**

```rust
use std::sync::mpsc;
use std::thread;
use std::time::Duration;

fn main() {
    let (tx, rx) = mpsc::channel();

    thread::spawn(move || {
        let msg = String::from("안녕하세요!");
        tx.send(msg).unwrap();
    });

    let received = rx.recv().unwrap();
    println!("메시지 수신: {}", received);
}
```

📌 `mpsc::channel()` → 송신(tx)과 수신(rx) 채널 생성

📌 `tx.send(msg).unwrap();` → 메시지 전송

📌 `rx.recv().unwrap();` → 메시지를 기다렸다가 받음

---

## 🔄 `Arc`와 `Mutex`를 활용한 공유 상태
Rust에서는 여러 스레드가 동일한 데이터를 안전하게 공유할 수 있도록 `Arc`(Atomic Reference Counting) 및 `Mutex`(Mutual Exclusion)를 제공합니다.

```rust
use std::sync::{Arc, Mutex};
use std::thread;

fn main() {
    let counter = Arc::new(Mutex::new(0));
    let mut handles = vec![];

    for _ in 0..10 {
        let counter = Arc::clone(&counter);
        let handle = thread::spawn(move || {
            let mut num = counter.lock().unwrap();
            *num += 1;
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    println!("최종 카운트: {}", *counter.lock().unwrap());
}
```

📌 `Arc::new(Mutex::new(0))` → **스레드 간 공유할 데이터** 생성

📌 `counter.lock().unwrap()` → **뮤텍스를 이용해 안전하게 데이터 접근**

📌 `Arc::clone(&counter)` → 여러 스레드에서 안전하게 참조 가능

---

## 🚀 비동기(Async) 프로그래밍
Rust에서는 `async` / `await`을 사용하여 **비동기 코드**를 작성할 수 있습니다. 

비동기 실행을 위해서는 `tokio` 또는 `async-std` 같은 런타임이 필요합니다.

### 📌 `async` / `await` 기본 사용법

```rust
use tokio::time::{sleep, Duration};

#[tokio::main]
async fn main() {
    println!("비동기 실행 시작");
    sleep(Duration::from_secs(2)).await;
    println!("2초 후 실행됨");
}
```

🔹 `async fn main()` → 비동기 함수 정의
🔹 `sleep(Duration::from_secs(2)).await;` → **비동기적으로 2초 동안 대기**
🔹 `#[tokio::main]` → `tokio` 런타임 사용

---

## 🔄 `async` 함수와 `join!`
비동기 함수를 동시에 실행하려면 `tokio::join!`을 사용할 수 있습니다.

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

📌 `tokio::join!` 을 사용하여 여러 비동기 함수를 병렬 실행 가능

📌 `task1()`과 `task2()`가 동시에 실행됨

---

## 🎯 마무리

이 장에서는 **Rust의 동시성과 비동기 프로그래밍**에 대해 배웠습니다.

- `thread::spawn()`을 사용하여 **스레드 생성**
- `mpsc::channel()`을 이용하여 **스레드 간 메시지 전달**
- `Arc<Mutex<T>>`을 사용하여 **안전한 데이터 공유**
- `async` / `await`을 사용하여 **비동기 함수 실행**

다음 장에서는 **Rust의 입출력(IO) 및 파일 시스템**에 대해 배워보겠습니다! 🚀
