# ⏳ TypeScript 비동기 프로그래밍 (Asynchronous Programming)

## 📌 개요
비동기 프로그래밍은 **네트워크 요청, 파일 읽기, 타이머 처리** 등 실행 시간이 오래 걸리는 작업을 효율적으로 처리하는 데 필수적입니다. TypeScript는 **콜백(Callbacks), 프로미스(Promises), async/await**을 지원하여 비동기 코드 작성을 더 쉽게 만듭니다. 🚀

---

## 🔄 콜백 (Callbacks)
콜백 함수는 **비동기 작업이 완료된 후 실행되는 함수**입니다.

### ✅ 기본 콜백 예제
```typescript
function fetchData(callback: (data: string) => void) {
    setTimeout(() => {
        callback("Data received");
    }, 1000);
}

fetchData((data) => {
    console.log(data); // "Data received"
});
```
- `fetchData` 함수는 1초 후에 콜백 함수를 호출
- 콜백 패턴은 간단하지만 **콜백 지옥(Callback Hell)** 문제가 발생할 수 있음

---

## 🏗 프로미스 (Promises)
프로미스는 **비동기 작업의 성공/실패를 처리할 수 있는 객체**입니다.

### ✅ 기본 프로미스 예제
```typescript
function fetchData(): Promise<string> {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            resolve("Data received");
        }, 1000);
    });
}

fetchData()
    .then((data) => console.log(data)) // "Data received"
    .catch((error) => console.error(error));
```
- `resolve(data)` → 작업 성공 시 데이터를 반환
- `reject(error)` → 작업 실패 시 오류 반환

### ✅ `Promise.all`과 `Promise.race`
```typescript
const promise1 = new Promise((resolve) => setTimeout(() => resolve("First Done"), 1000));
const promise2 = new Promise((resolve) => setTimeout(() => resolve("Second Done"), 2000));

Promise.all([promise1, promise2]).then((results) => console.log(results));
// 출력: ["First Done", "Second Done"] (모두 완료 후 실행)

Promise.race([promise1, promise2]).then((result) => console.log(result));
// 출력: "First Done" (가장 먼저 완료된 프로미스 반환)
```
- `Promise.all()` → 모든 프로미스가 완료될 때까지 기다림
- `Promise.race()` → 가장 먼저 완료된 프로미스를 반환

---

## 🏗 `async/await` 패턴
`async/await`는 **프로미스를 더 직관적으로 사용할 수 있도록 도와줍니다**.

### ✅ `async/await` 기본 예제
```typescript
async function fetchDataAsync(): Promise<string> {
    return new Promise((resolve) => setTimeout(() => resolve("Data received"), 1000));
}

async function processData() {
    const data = await fetchDataAsync();
    console.log(data);
}

processData(); // "Data received" (1초 후 출력)
```
- `await` → 프로미스가 완료될 때까지 대기
- `async` → 함수 내부에서 `await`을 사용할 수 있도록 함

### ✅ `try/catch`를 사용한 에러 핸들링
```typescript
async function fetchWithError(): Promise<string> {
    return new Promise((_, reject) => setTimeout(() => reject("Fetch failed"), 1000));
}

async function handleError() {
    try {
        const data = await fetchWithError();
        console.log(data);
    } catch (error) {
        console.error("Error caught:", error);
    }
}

handleError(); // "Error caught: Fetch failed"
```
- `try/catch`를 사용하여 **비동기 코드의 오류를 처리**

---

## ⚡ 병렬 처리 vs. 직렬 처리

### ✅ 직렬 처리 (Sequential Processing)
```typescript
async function sequentialProcessing() {
    const result1 = await fetchDataAsync();
    console.log(result1);
    const result2 = await fetchDataAsync();
    console.log(result2);
}
```
- **첫 번째 작업이 완료된 후** 두 번째 작업이 시작됨

### ✅ 병렬 처리 (Parallel Processing)
```typescript
async function parallelProcessing() {
    const [result1, result2] = await Promise.all([fetchDataAsync(), fetchDataAsync()]);
    console.log(result1, result2);
}
```
- **두 개의 작업을 동시에 실행**하여 성능 향상 가능

---

## 🔎 비동기 흐름 다이어그램
```mermaid
graph TD;
    A[비동기 요청] -->|Promise 생성| B[작업 수행];
    B -->|성공| C[resolve() 호출];
    B -->|실패| D[reject() 호출];
    C -->|await or .then()| E[결과 반환];
    D -->|await try/catch or .catch()| F[에러 처리];
```

---

## 🎯 정리 및 다음 단계
✅ **콜백, 프로미스, async/await을 사용하여 비동기 코드를 처리할 수 있습니다.**
✅ **`Promise.all()`과 `Promise.race()`를 활용하여 효율적인 비동기 처리가 가능합니다.**
✅ **비동기 코드의 예외 처리는 `try/catch`를 사용하여 안정성을 높일 수 있습니다.**
✅ **병렬 처리와 직렬 처리의 차이를 이해하고 적절한 방식으로 적용할 수 있습니다.**

👉 **다음 강의: [07-performance-optimization.md](./07-performance-optimization.md)**