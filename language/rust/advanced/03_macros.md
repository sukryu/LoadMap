# 🦀 Rust의 매크로(Macro) 시스템

## 📌 개요
Rust의 **매크로(Macro)** 시스템은 반복적인 코드 생성을 줄이고, **컴파일 타임 코드 확장**을 가능하게 합니다.

Rust에서 지원하는 매크로 유형:
✅ **매크로_rules!** → 단순 텍스트 기반 매크로
✅ **프로시저 매크로(Procedural Macro)** → AST(추상 구문 트리)를 조작하여 복잡한 코드 생성
✅ **파생 매크로(Derive Macro)** → 구조체 및 열거형 자동 코드 생성
✅ **속성 매크로(Attribute Macro)** → 특정 속성 기반 코드 변환

이 장에서는 **Rust 매크로의 다양한 유형과 활용법**을 배워보겠습니다.

---

## 🚀 `macro_rules!` 기본 사용법
Rust의 기본 매크로 시스템은 `macro_rules!`을 사용하여 **코드를 자동 생성**할 수 있습니다.

### 🏷️ 기본적인 매크로 정의
```rust
macro_rules! say_hello {
    () => {
        println!("안녕하세요, Rust 매크로!");
    };
}

fn main() {
    say_hello!();
}
```
📌 `macro_rules!` → 매크로 정의

📌 `say_hello!();` → 매크로 호출

---

## 🔄 매개변수를 받는 매크로
매크로에 **인자를 전달**하여 더 유연하게 사용할 수도 있습니다.

```rust
macro_rules! repeat_message {
    ($msg:expr, $count:expr) => {
        for _ in 0..$count {
            println!("{}", $msg);
        }
    };
}

fn main() {
    repeat_message!("Rust는 강력하다!", 3);
}
```
📌 `$msg:expr` → **표현식(Expression) 매개변수**

📌 `$count:expr` → **반복 횟수를 지정하는 매개변수**

📌 `repeat_message!("Rust는 강력하다!", 3);` → 해당 메시지를 3번 출력

---

## 🏗️ 가변 매개변수를 받는 매크로
매크로에서 **가변 개수의 인자**를 받을 수도 있습니다.

```rust
macro_rules! sum {
    ($($num:expr),*) => {
        {
            let mut total = 0;
            $(total += $num;)*
            total
        }
    };
}

fn main() {
    let result = sum!(1, 2, 3, 4, 5);
    println!("합계: {}", result);
}
```
📌 `$($num:expr),*` → 여러 개의 값을 받을 수 있도록 설정

📌 `$(total += $num;)*` → 받은 값들을 반복해서 처리

📌 `sum!(1, 2, 3, 4, 5);` → 여러 숫자를 받아 합산 후 반환

---

## 🏗️ `derive`를 활용한 프로시저 매크로
Rust에서는 **구조체나 열거형에 자동으로 코드 생성을 적용**할 수 있습니다.

```rust
use serde::Serialize;

#[derive(Serialize)]
struct User {
    name: String,
    age: u8,
}
```
📌 `#[derive(Serialize)]` → `serde`를 사용하여 JSON 직렬화 가능

📌 `#[derive(Debug, Clone, Copy)]` → 자동으로 `Debug`, `Clone`, `Copy` 트레이트 구현

---

## 🛠️ 프로시저 매크로 작성하기
Rust에서는 **AST(Abstract Syntax Tree)을 조작하는 프로시저 매크로**를 작성할 수도 있습니다.

📌 `proc_macro` 크레이트를 사용하여 **사용자 정의 매크로**를 만들 수 있습니다.

### 🏗️ `derive` 프로시저 매크로 예제
```rust
use proc_macro;
use quote::quote;
use syn;

#[proc_macro_derive(HelloMacro)]
pub fn hello_macro_derive(input: proc_macro::TokenStream) -> proc_macro::TokenStream {
    let ast = syn::parse(input).unwrap();
    impl_hello_macro(&ast)
}

fn impl_hello_macro(ast: &syn::DeriveInput) -> proc_macro::TokenStream {
    let name = &ast.ident;
    let gen = quote! {
        impl HelloMacro for #name {
            fn hello_macro() {
                println!("Hello, {}!", stringify!(#name));
            }
        }
    };
    gen.into()
}
```
📌 `proc_macro_derive(HelloMacro)` → 사용자 정의 `derive` 매크로 생성

📌 `syn::parse(input)` → 입력된 코드(AST) 파싱

📌 `quote! {}` → 코드 조각 생성

📌 `stringify!(#name)` → 타입 이름을 문자열로 변환

---

## 🚀 속성(Attribute) 매크로 활용
속성 매크로는 **특정 속성을 가진 코드 조작**을 가능하게 합니다.

```rust
use proc_macro::TokenStream;

#[proc_macro_attribute]
pub fn log_function(_attr: TokenStream, item: TokenStream) -> TokenStream {
    let input = syn::parse_macro_input!(item as syn::ItemFn);
    let name = &input.sig.ident;
    let output = quote! {
        fn #name() {
            println!("{} 함수가 실행되었습니다!", stringify!(#name));
            #input
        }
    };
    output.into()
}
```
📌 `#[proc_macro_attribute]` → 속성 매크로 생성

📌 `log_function` → 특정 함수 실행 시 로그를 자동 출력

📌 `quote! {}` → **원본 코드 유지하면서 추가 동작을 삽입**

사용 예:
```rust
#[log_function]
fn my_function() {
    println!("Hello, Rust!");
}
```
📌 실행하면 `my_function()` 실행 전 **로그 출력 기능이 자동 추가됨**

---

## 🎯 마무리
이 장에서는 **Rust의 매크로 시스템**을 학습했습니다.

- `macro_rules!`를 사용하여 **간단한 매크로 정의 및 사용**
- 가변 매개변수를 활용한 **유연한 매크로 작성**
- `derive` 매크로로 **자동 트레이트 구현**
- `proc_macro`을 이용한 **고급 프로시저 매크로 작성**
- `#[proc_macro_attribute]` 속성을 활용한 **코드 변환 매크로**

다음 장에서는 **Rust의 FFI(외부 함수 인터페이스)와 C/C++ 연동**을 배워보겠습니다! 🚀
