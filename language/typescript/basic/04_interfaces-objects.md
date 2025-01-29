# 🎯 TypeScript 인터페이스 및 객체 (Interfaces & Objects)

## 📌 개요
TypeScript에서는 **인터페이스(Interface)** 를 사용하여 객체의 구조를 정의할 수 있습니다. 인터페이스를 활용하면 코드의 **일관성 유지**, **자동 완성 지원**, **정적 타입 체크**가 가능해집니다. 또한 **선택적 속성, 읽기 전용 속성, 확장(extends), 함수 타입** 등 다양한 기능도 제공합니다. 🚀

---

## 🛠 객체 타입 기본
객체를 정의할 때 타입을 직접 명시할 수 있습니다.

```typescript
let user: { name: string; age: number } = {
    name: "Alice",
    age: 25
};

console.log(user.name); // 출력: Alice
```

- `{ name: string; age: number }` → 객체의 타입을 정의함
- `user.name` → 자동 완성 기능을 통해 `name` 속성을 쉽게 확인 가능

하지만 여러 객체에서 동일한 구조를 사용할 경우 **인터페이스**를 활용하는 것이 좋습니다.

---

## 📌 인터페이스 (Interface)
### ✅ 기본 인터페이스 선언
```typescript
interface User {
    name: string;
    age: number;
}

let user1: User = {
    name: "Bob",
    age: 30
};

console.log(user1.name); // 출력: Bob
```
- `interface User` → 객체 구조를 정의하는 인터페이스
- 여러 객체에서 `User` 인터페이스를 재사용 가능

### ✅ 선택적 속성 (`?` 사용)
```typescript
interface Car {
    brand: string;
    model?: string;
}

let car1: Car = { brand: "Tesla" };
let car2: Car = { brand: "BMW", model: "X5" };
```
- `model?` → 선택적 속성이므로 있어도 되고 없어도 됨

### ✅ 읽기 전용 속성 (`readonly` 사용)
```typescript
interface Person {
    readonly id: number;
    name: string;
}

let person: Person = { id: 1, name: "Charlie" };
// person.id = 2; // 오류 발생! (읽기 전용 속성 변경 불가)
```
- `readonly id: number;` → 한 번 설정된 값은 변경할 수 없음

---

## 📌 인터페이스 확장 (Extends)
하나의 인터페이스를 다른 인터페이스에서 확장할 수 있습니다.

```typescript
interface Animal {
    name: string;
}

interface Dog extends Animal {
    breed: string;
}

let myDog: Dog = { name: "Buddy", breed: "Golden Retriever" };
```
- `interface Dog extends Animal` → `Dog`는 `Animal`의 속성을 상속받음
- `myDog` 객체는 `name`과 `breed` 속성을 가져야 함

---

## 📌 함수 타입을 가진 인터페이스
인터페이스는 함수의 타입도 정의할 수 있습니다.

```typescript
interface MathOperation {
    (x: number, y: number): number;
}

let add: MathOperation = (a, b) => a + b;
let multiply: MathOperation = (a, b) => a * b;

console.log(add(10, 5)); // 출력: 15
console.log(multiply(10, 5)); // 출력: 50
```
- `interface MathOperation` → 두 개의 숫자를 입력받아 숫자를 반환하는 함수 타입을 정의
- 여러 함수에서 이 타입을 공유 가능

---

## 🔎 인터페이스 다이어그램

```mermaid
graph TD;
    A[인터페이스 정의] -->|객체 타입| B{name, age};
    A -->|선택적 속성| C{? 사용};
    A -->|읽기 전용 속성| D{readonly 사용};
    A -->|확장| E{extends 사용};
    A -->|함수 타입| F{(x:number, y:number) => number};
```

---

## 🎯 정리 및 다음 단계
✅ 인터페이스를 사용하여 **객체의 구조를 정의**할 수 있습니다.
✅ 선택적 속성(`?`), 읽기 전용 속성(`readonly`), 확장(`extends`)을 활용하여 **유연한 인터페이스 설계**가 가능합니다.
✅ 함수 타입을 인터페이스로 정의하면 **일관된 함수 시그니처**를 유지할 수 있습니다.

👉 **다음 강의: [05-classes-oop.md](./05-classes-oop.md)**

