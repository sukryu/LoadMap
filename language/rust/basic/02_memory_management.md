# 🦀 Rust 메모리 관리 기초

## 📌 개요
Rust의 강점 중 하나는 **메모리 안전성**을 보장하면서도 **GC(Garbage Collector) 없이 메모리를 효율적으로 관리**하는 것입니다. 

이 장에서는 **스택(Stack)과 힙(Heap)**, **소유권(Ownership)**, **참조(Reference)와 차용(Borrowing)** 개념을 다룹니다. 

---

## 🏗️ 메모리 구조 이해하기

Rust에서는 변수들이 저장되는 위치에 따라 **스택(Stack)**과 **힙(Heap)** 메모리로 구분됩니다.

```mermaid
graph TD;
    A[프로그램 실행] -->|정적 메모리| B[데이터 영역]
    A -->|빠른 접근| C[스택(Stack)]
    A -->|동적 할당| D[힙(Heap)]
```

### 🔹 스택 (Stack)
✅ **LIFO(Last In, First Out)** 구조로 데이터가 저장됨
✅ **고정된 크기의 데이터**만 저장 가능 (예: 정수, 실수, 불리언 등)
✅ 빠른 메모리 할당 및 해제
✅ 함수 호출 시 지역 변수 저장

**예제**
```rust
fn main() {
    let x = 10; // x는 스택에 저장됨
    let y = 20; // y도 스택에 저장됨
    println!("x: {}, y: {}", x, y);
}
```

### 🔹 힙 (Heap)
✅ **동적으로 크기가 변하는 데이터** 저장 (예: String, Vec<T>)
✅ 속도가 느리지만, 유연한 메모리 관리 가능
✅ 명시적으로 할당 및 해제 필요 (Rust에서는 자동 관리됨)

**예제**
```rust
fn main() {
    let s = String::from("Hello, Rust!"); // 힙에 저장됨
    println!("{}", s);
}
```

---

## 🔑 소유권 (Ownership)
Rust의 가장 중요한 개념은 **소유권(Ownership)** 입니다.

📌 **소유권 규칙**
1️⃣ **각 값은 오직 하나의 변수만 소유**할 수 있다.
2️⃣ **소유자가 범위를 벗어나면, 메모리는 자동 해제**된다.
3️⃣ **값을 다른 변수에 할당하면, 소유권이 이동(Move)된다.**

### 🏷️ 이동(Move)과 복사(Copy)
```rust
fn main() {
    let s1 = String::from("Rust");
    let s2 = s1; // s1의 소유권이 s2로 이동 (Move)
    println!("{}", s2);
    // println!("{}", s1); // ❌ 컴파일 에러 발생!
}
```

📌 **스택 데이터 (i32, f64, bool 등)은 복사(Copy)**
```rust
fn main() {
    let x = 10;
    let y = x; // x가 복사됨
    println!("x: {}, y: {}", x, y); // ✅ 정상 실행
}
```

---

## 🔄 참조(Reference)와 차용(Borrowing)

소유권을 이동하지 않고 **값을 참조(Reference)**할 수도 있습니다.

✅ `&`를 사용하여 참조를 생성하면, 값의 소유권을 넘기지 않고 접근할 수 있습니다.

```rust
fn main() {
    let s1 = String::from("Rust");
    let len = calculate_length(&s1); // s1을 참조로 전달 (Borrowing)
    println!("문자열 길이: {}", len);
}

fn calculate_length(s: &String) -> usize {
    s.len() // 소유권을 넘기지 않음
}
```

📌 **불변 참조 (Immutable Reference)**
- 여러 개의 불변 참조(`&T`)는 동시에 존재할 수 있습니다.

📌 **가변 참조 (Mutable Reference)**
- 한 번에 하나의 가변 참조(`&mut T`)만 허용됩니다.

```rust
fn main() {
    let mut s = String::from("Hello");
    change(&mut s);
    println!("{}", s);
}

fn change(s: &mut String) {
    s.push_str(", Rust!");
}
```

🚨 **가변 참조 규칙**: 
- 한 번에 **오직 하나의 가변 참조**만 허용됩니다.
- 불변 참조와 가변 참조를 동시에 사용할 수 없습니다.

```rust
fn main() {
    let mut s = String::from("Rust");
    let r1 = &s; // 불변 참조 ✅
    let r2 = &s; // 불변 참조 ✅
    // let r3 = &mut s; // ❌ 불변 참조가 존재하는 동안 가변 참조 불가!
    println!("{} and {}", r1, r2);
}
```

---

## 🎯 마무리

이 장에서는 **메모리 구조, 소유권, 참조와 차용**을 배웠습니다.
다음 장에서는 **소유권과 라이프타임(Lifetime) 개념**을 심화 학습하겠습니다! 🚀
