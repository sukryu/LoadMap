# 🎯 TypeScript 제네릭 (Generics)

## 📌 개요
제네릭(Generics)은 **코드의 재사용성과 타입 안전성을 높이는 기능**으로, 다양한 타입을 지원하는 **유연한 함수, 클래스, 인터페이스**를 만들 수 있습니다. 제네릭을 사용하면 **코드를 한 번만 작성하고 여러 타입에 대해 동작하도록 할 수 있습니다.** 🚀

---

## 🏗 제네릭 기본 문법
제네릭을 사용하면 특정 타입을 지정하지 않고, 함수나 클래스에서 **타입 변수를 활용**할 수 있습니다.

### ✅ 제네릭 함수
```typescript
function identity<T>(arg: T): T {
    return arg;
}

console.log(identity<string>("Hello, TypeScript!")); // 출력: "Hello, TypeScript!"
console.log(identity<number>(42)); // 출력: 42
```
- `<T>`: 제네릭 타입 변수 `T`를 선언
- `identity<T>(arg: T): T`: 입력값의 타입과 반환 타입이 동일하도록 보장
- 함수 호출 시 `identity<string>` 또는 `identity<number>`처럼 명시적으로 타입 지정 가능

### ✅ 타입 추론을 활용한 제네릭 함수
```typescript
function wrap<T>(value: T) {
    return { value };
}

let wrappedString = wrap("Hello");
let wrappedNumber = wrap(100);
console.log(wrappedString, wrappedNumber);
```
- TypeScript가 `T`의 타입을 자동으로 추론할 수 있음

---

## 📌 제네릭 인터페이스
```typescript
interface Box<T> {
    content: T;
}

let stringBox: Box<string> = { content: "Hello" };
let numberBox: Box<number> = { content: 42 };
```
- `interface Box<T>`: 제네릭 인터페이스 선언
- `stringBox`, `numberBox`는 각각 `string`과 `number` 타입을 가진 객체

---

## 🔄 제네릭 클래스
```typescript
class Pair<T, U> {
    constructor(public first: T, public second: U) {}

    getPair(): [T, U] {
        return [this.first, this.second];
    }
}

let pair = new Pair("Alice", 30);
console.log(pair.getPair()); // 출력: ["Alice", 30]
```
- `class Pair<T, U>`: 제네릭 클래스에서 두 개의 타입 변수(`T`, `U`) 사용 가능
- `getPair()` 메서드는 `[T, U]` 튜플을 반환

---

## 📌 제네릭 타입 제한 (`extends`)
제네릭을 사용할 때 특정 타입을 제한(`extends`)할 수 있습니다.

### ✅ 제네릭 타입 제한
```typescript
function getLength<T extends { length: number }>(item: T): number {
    return item.length;
}

console.log(getLength("Hello")); // ✅ 문자열은 length 속성이 있음
console.log(getLength([1, 2, 3])); // ✅ 배열도 length 속성이 있음
// console.log(getLength(42)); // ❌ 오류: number에는 length 속성이 없음
```
- `<T extends { length: number }>`: `T` 타입은 반드시 `length` 속성을 가져야 함

---

## 🔄 제네릭과 키(`keyof`)
`keyof`를 활용하여 제네릭을 객체의 속성 타입으로 제한할 수 있습니다.

```typescript
function getProperty<T, K extends keyof T>(obj: T, key: K) {
    return obj[key];
}

let user = { name: "Alice", age: 30 };
console.log(getProperty(user, "name")); // ✅ Alice
console.log(getProperty(user, "age")); // ✅ 30
// console.log(getProperty(user, "email")); // ❌ 오류: email 속성은 존재하지 않음
```
- `K extends keyof T`: `K`는 반드시 `T`의 키 중 하나여야 함

---

## 📌 제네릭 유틸리티 타입
TypeScript에는 자주 사용되는 제네릭 유틸리티 타입이 내장되어 있습니다.

| 유틸리티 타입 | 설명 |
|--------------|------|
| `Partial<T>` | 모든 속성을 선택적으로 만듦 |
| `Readonly<T>` | 모든 속성을 읽기 전용으로 만듦 |
| `Pick<T, K>` | 특정 속성만 선택하여 새로운 타입 생성 |
| `Omit<T, K>` | 특정 속성을 제외하여 새로운 타입 생성 |

### ✅ 유틸리티 타입 예제
```typescript
interface User {
    name: string;
    age: number;
    email: string;
}

let partialUser: Partial<User> = { name: "Alice" };
let readonlyUser: Readonly<User> = { name: "Bob", age: 30, email: "bob@email.com" };
// readonlyUser.age = 35; // ❌ 오류 발생 (읽기 전용 속성)
```
- `Partial<User>` → 모든 속성이 선택적으로 변환됨
- `Readonly<User>` → 모든 속성이 읽기 전용(`readonly`)으로 설정됨

---

## 🔎 제네릭 다이어그램
```mermaid
graph TD;
    A[제네릭 함수] -->|T 타입 변수| B(identity<T>(arg: T): T);
    A -->|T 추론| C(identity(42));
    A -->|제네릭 인터페이스| D(Box<T>);
    A -->|제네릭 클래스| E(Pair<T, U>);
    A -->|제네릭 제한| F(T extends { length: number });
```

---

## 🎯 정리 및 다음 단계
✅ **제네릭을 사용하면 코드의 재사용성을 높이고 타입 안정성을 유지**할 수 있습니다.
✅ **제네릭 함수, 인터페이스, 클래스, 타입 제한, 키 제한 등을 활용하여 유연한 코드**를 작성할 수 있습니다.
✅ **내장 유틸리티 타입(`Partial`, `Readonly`, `Pick`, `Omit`)을 활용하면 더욱 효율적인 프로그래밍이 가능**합니다.

👉 **다음 강의: [07-modules-and-namespaces.md](./07-modules-and-namespaces.md)**

