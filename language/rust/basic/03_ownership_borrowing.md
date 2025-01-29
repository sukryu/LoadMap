# 🦀 Rust의 소유권(Ownership)과 차용(Borrowing)

## 📌 개요
Rust의 가장 핵심적인 개념 중 하나가 **소유권(Ownership)** 입니다. Rust에서는 **소유권 시스템**을 통해 메모리를 자동으로 관리하면서도 **GC(Garbage Collector) 없이 안전한 프로그래밍**을 가능하게 합니다.

이 장에서는 **소유권(Ownership)**, **차용(Borrowing)**, 그리고 **라이프타임(Lifetime)** 개념을 배우고 이를 실습해 보겠습니다.

---

## 🎯 소유권(Ownership)이란?
Rust에서는 모든 값이 특정 변수에 의해 **소유**되며, 이 소유자가 범위를 벗어나면 해당 메모리는 자동으로 해제됩니다.

📌 **소유권의 3가지 규칙**
1️⃣ **각 값은 단 하나의 변수만 소유할 수 있다.**
2️⃣ **소유자가 범위를 벗어나면 메모리는 자동으로 해제된다.**
3️⃣ **값을 다른 변수에 할당하면 소유권이 이동(Move)된다.**

```rust
fn main() {
    let s1 = String::from("Rust"); // s1이 소유권을 가짐
    let s2 = s1; // s1의 소유권이 s2로 이동(Move)
    // println!("{}", s1); // ❌ 오류 발생: s1은 더 이상 유효하지 않음
    println!("{}", s2);
}
```

📌 **스택 데이터 (Copy)**
일반적으로 정수, 실수, 불리언과 같은 **스택 데이터**는 복사(Copy)됩니다.

```rust
fn main() {
    let x = 10;
    let y = x; // x는 복사됨
    println!("x: {}, y: {}", x, y); // ✅ 정상 실행
}
```

---

## 🔄 참조(Reference)와 차용(Borrowing)
소유권을 이동하지 않고도 **값을 참조**할 수 있습니다.

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

## ⏳ 라이프타임(Lifetime) 개념
Rust에서는 **참조자가 항상 유효해야 한다는 원칙**을 지킵니다. 이를 위해 **라이프타임(lifetime) 시스템**이 도입되었습니다.

📌 **라이프타임 표기법**
- `'a`, `'b` 등의 기호를 사용하여 라이프타임을 명시할 수 있습니다.

```rust
fn longest<'a>(s1: &'a str, s2: &'a str) -> &'a str {
    if s1.len() > s2.len() { s1 } else { s2 }
}

fn main() {
    let str1 = String::from("Rust");
    let str2 = String::from("Programming");
    let result = longest(&str1, &str2);
    println!("더 긴 문자열: {}", result);
}
```

📌 **라이프타임의 원칙**
1️⃣ **라이프타임이 짧은 변수가 더 긴 변수보다 오래 참조될 수 없다.**
2️⃣ **컴파일러가 자동으로 라이프타임을 추론하지만, 명시적으로 지정할 수도 있다.**

```rust
fn main() {
    let r;
    {
        let x = 5;
        r = &x; // ❌ x는 이 블록이 끝나면 해제됨
    }
    // println!("r: {}", r); // 컴파일 오류 발생
}
```

✅ **올바른 라이프타임 사용 예제**
```rust
fn main() {
    let x = 5;
    let r = &x; // r은 x보다 오래 살아야 함
    println!("r: {}", r); // ✅ 정상 실행
}
```

---

## 🎯 마무리

이 장에서는 **소유권(Ownership), 차용(Borrowing), 라이프타임(Lifetime)** 개념을 배웠습니다.
다음 장에서는 **Rust의 구조체(Struct)와 열거형(Enum)** 에 대해 배워보겠습니다! 🚀
