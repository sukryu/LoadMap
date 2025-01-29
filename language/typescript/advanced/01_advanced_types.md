# 🎯 TypeScript 고급 타입 (Advanced Types)

## 📌 개요
TypeScript는 강력한 타입 시스템을 제공하며, **유니온 타입(Union Types), 교차 타입(Intersection Types), 조건부 타입(Conditional Types), 맵드 타입(Mapped Types)** 등의 고급 개념을 지원합니다. 이 장에서는 **더 정교한 타입 설계 기법**을 학습합니다. 🚀

---

## 🔀 유니온 타입 (Union Types)
여러 타입을 허용하고 싶을 때 **유니온 타입(`|`)** 을 사용합니다.

### ✅ 유니온 타입 예제
```typescript
function printId(id: number | string) {
    console.log("ID:", id);
}
printId(123);
printId("ABC123");
```
- `number | string` → `id`는 숫자 또는 문자열을 가질 수 있음

### ✅ 유니온 타입과 타입 가드
```typescript
function formatValue(value: number | string) {
    if (typeof value === "number") {
        return value.toFixed(2);
    }
    return value.toUpperCase();
}
console.log(formatValue(42)); // "42.00"
console.log(formatValue("hello")); // "HELLO"
```
- `typeof`를 사용하여 타입에 따라 적절한 동작을 수행할 수 있음

---

## 🔗 교차 타입 (Intersection Types)
여러 타입을 결합할 때 **교차 타입(`&`)** 을 사용합니다.

### ✅ 교차 타입 예제
```typescript
interface Person {
    name: string;
    age: number;
}
interface Employee {
    company: string;
}
type Worker = Person & Employee;

const worker: Worker = {
    name: "Alice",
    age: 30,
    company: "Tech Corp"
};
```
- `Worker` 타입은 `Person`과 `Employee` 속성을 모두 가짐

---

## 🔄 조건부 타입 (Conditional Types)
조건부 타입은 **`extends` 키워드를 이용하여 특정 조건에 따라 타입을 결정**합니다.

### ✅ 조건부 타입 예제
```typescript
type IsString<T> = T extends string ? "Yes" : "No";
type Result1 = IsString<string>;  // "Yes"
type Result2 = IsString<number>;  // "No"
```
- `T extends string ? "Yes" : "No"` → `T`가 `string`이면 "Yes", 아니면 "No" 반환

### ✅ 제네릭과 함께 사용
```typescript
type ConvertToArray<T> = T extends any ? T[] : never;
type StringArray = ConvertToArray<string>; // string[]
type NumberArray = ConvertToArray<number>; // number[]
```

---

## 🔄 맵드 타입 (Mapped Types)
맵드 타입은 **기존 타입을 변형하여 새로운 타입을 생성**하는 기능을 제공합니다.

### ✅ `Partial<T>`: 모든 속성을 선택적으로 변환
```typescript
interface User {
    name: string;
    age: number;
}
type PartialUser = Partial<User>;
const user: PartialUser = { name: "Bob" }; // age는 생략 가능
```

### ✅ `Readonly<T>`: 모든 속성을 읽기 전용으로 변환
```typescript
type ReadonlyUser = Readonly<User>;
const user: ReadonlyUser = { name: "Alice", age: 30 };
// user.age = 31; // ❌ 오류 발생 (읽기 전용 속성)
```

### ✅ `Record<K, T>`: 특정 키와 값을 매핑하여 타입 생성
```typescript
type UserRoles = "admin" | "user" | "guest";
const roles: Record<UserRoles, number> = {
    admin: 1,
    user: 2,
    guest: 3
};
```

---

## 🔎 고급 타입 다이어그램
```mermaid
graph TD;
    A[유니온 타입] -->|A | B| B(여러 타입 중 하나 선택 가능);
    A -->|A & B| C(교차 타입 - 모든 속성 포함);
    A -->|조건부 타입| D(타입이 특정 조건을 만족하면 다른 타입 할당);
    A -->|맵드 타입| E(기존 타입을 변형하여 새로운 타입 생성);
```

---

## 🎯 정리 및 다음 단계
✅ **유니온 타입과 교차 타입을 활용하여 더 유연한 타입을 설계할 수 있습니다.**
✅ **조건부 타입을 사용하여 타입을 동적으로 결정할 수 있습니다.**
✅ **맵드 타입을 활용하여 기존 타입을 변형할 수 있습니다.**

👉 **다음 강의: [02-type-guards.md](./02-type-guards.md)**

