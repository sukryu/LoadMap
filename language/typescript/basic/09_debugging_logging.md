# 🛠 TypeScript 디버깅 및 로깅 (Debugging & Logging)

## 📌 개요
TypeScript에서는 **디버깅(debugging)** 과 **로깅(logging)** 을 활용하여 코드를 더 쉽게 분석하고 오류를 추적할 수 있습니다.
이번 강의에서는 **콘솔 디버깅, 브라우저 및 Node.js 디버깅, 로깅 시스템 구축**에 대해 다룹니다. 🚀

---

## 🛠 기본 디버깅 방법

### ✅ `console.log()` 활용
가장 기본적인 디버깅 방법은 `console.log()`를 활용하는 것입니다.
```typescript
const user = { name: "Alice", age: 25 };
console.log("User info:", user);
```
✅ 여러 값 출력 가능
```typescript
console.log("Debug Info:", { a: 10, b: 20, sum: 30 });
```
✅ 템플릿 문자열 활용
```typescript
const name = "Bob";
console.log(`Hello, ${name}!`);
```

### ✅ `console` 객체의 다양한 기능
| 메서드 | 설명 |
|--------|------|
| `console.log()` | 일반 로그 출력 |
| `console.warn()` | 경고 메시지 출력 (노란색 표시) |
| `console.error()` | 오류 메시지 출력 (빨간색 표시) |
| `console.table()` | 객체 또는 배열을 표 형식으로 출력 |
| `console.time()` / `console.timeEnd()` | 코드 실행 시간 측정 |

```typescript
console.warn("This is a warning!");
console.error("Something went wrong!");

const users = [
    { id: 1, name: "Alice" },
    { id: 2, name: "Bob" }
];
console.table(users);
```

---

## 🧐 브라우저 개발자 도구에서 디버깅
### ✅ Chrome DevTools 활용하기
1️⃣ **브라우저에서 F12 또는 `Ctrl + Shift + I`를 눌러 개발자 도구 열기**
2️⃣ **Console 탭에서 `console.log()` 메시지 확인**
3️⃣ **Sources 탭에서 TypeScript 파일을 디버깅**
4️⃣ **Breakpoints 설정하여 코드 실행 흐름 분석**

✅ **Breakpoints 설정**
```typescript
function add(a: number, b: number): number {
    debugger; // 코드 실행 중 브라우저 개발자 도구에서 중단됨
    return a + b;
}
console.log(add(3, 5));
```

✅ **Source Map 활성화** (`tsconfig.json` 설정 필요)
```json
{
    "compilerOptions": {
        "sourceMap": true
    }
}
```
- `sourceMap`을 활성화하면 브라우저에서 원본 TypeScript 코드로 디버깅 가능

---

## 🏗 Node.js 환경에서 디버깅
TypeScript 코드를 Node.js에서 실행할 때, **디버깅 도구**를 활용할 수 있습니다.

### ✅ VS Code에서 TypeScript 디버깅
1️⃣ **`.vscode/launch.json` 설정**
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "type": "node",
            "request": "launch",
            "name": "Launch Program",
            "program": "${workspaceFolder}/src/index.ts",
            "preLaunchTask": "tsc: build - tsconfig.json",
            "outFiles": ["${workspaceFolder}/dist/**/*.js"]
        }
    ]
}
```
2️⃣ **VS Code에서 F5를 눌러 디버깅 시작**

### ✅ `node --inspect` 사용
```bash
node --inspect dist/index.js
```
Chrome에서 `chrome://inspect`로 이동하여 디버깅 가능

---

## 🔄 로깅 시스템 구축
디버깅을 넘어서, **효율적인 로깅 시스템**을 구축하면 유지보수가 쉬워집니다.

### ✅ `winston`을 활용한 로깅
```bash
npm install winston
```
```typescript
import winston from "winston";

const logger = winston.createLogger({
    level: "info",
    format: winston.format.json(),
    transports: [
        new winston.transports.Console(),
        new winston.transports.File({ filename: "error.log", level: "error" })
    ]
});

logger.info("Info level log");
logger.error("Error occurred!");
```
- `winston.transports.Console()` → 콘솔에 로그 출력
- `winston.transports.File({ filename: "error.log" })` → 파일에 로그 저장

---

## 🔎 디버깅 및 로깅 다이어그램
```mermaid
graph TD;
    A[TypeScript 코드 실행] -->|console.log() 출력| B[개발자 도구 확인];
    A -->|VS Code 디버깅| C[Breakpoints 설정];
    A -->|로깅 시스템| D[파일 & 콘솔 로깅];
    D -->|winston 라이브러리| E[로그 저장];
```

---

## 🎯 정리 및 다음 단계
✅ **`console.log()`를 활용한 기본적인 디버깅 방법을 익혔습니다.**
✅ **브라우저 개발자 도구와 VS Code에서 디버깅을 설정하는 방법을 학습했습니다.**
✅ **Node.js 환경에서 `winston`을 활용하여 로깅 시스템을 구축하는 방법을 익혔습니다.**

👉 **다음 강의: [10-compilation-and-config.md](./10-compilation-and-config.md)**

