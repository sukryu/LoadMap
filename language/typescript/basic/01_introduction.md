# 📌 TypeScript 소개

## 🧐 TypeScript란?
TypeScript는 **Microsoft에서 개발한 오픈 소스 프로그래밍 언어**로, **JavaScript의 상위 집합(Superset)**입니다. 즉, 모든 JavaScript 코드는 유효한 TypeScript 코드이지만, TypeScript는 추가적인 **정적 타입 시스템**과 **객체 지향 프로그래밍 기능**을 제공합니다.

---

## 🎯 TypeScript의 주요 특징

✅ **정적 타입 지원**: 변수, 함수, 객체 등에 명시적인 타입을 지정하여 코드의 안정성을 높입니다.

✅ **객체 지향 프로그래밍(OOP) 기능 지원**: 클래스, 인터페이스, 모듈을 활용하여 더 체계적인 코드를 작성할 수 있습니다.

✅ **컴파일 시 오류 감지**: JavaScript는 런타임에서 오류를 찾지만, TypeScript는 컴파일 시점에서 오류를 발견하여 빠르게 수정할 수 있습니다.

✅ **최신 JavaScript 기능 지원**: 최신 ECMAScript(ES6+) 문법을 사용하고, 구버전(ES5)으로 트랜스파일할 수 있습니다.

✅ **강력한 개발 도구 지원**: Visual Studio Code와 같은 IDE에서 자동 완성(IntelliSense), 코드 네비게이션 등의 기능을 제공합니다.

✅ **Node.js 및 웹 프레임워크와 완벽한 호환**: Express.js, NestJS 등 백엔드 개발에서 광범위하게 사용됩니다.

---

## 🔍 TypeScript vs JavaScript 비교

| 구분 | JavaScript | TypeScript |
|------|-----------|------------|
| 타입 시스템 | 동적(Dynamic) 타입 | 정적(Static) 타입 지원 |
| 오류 검출 | 런타임에서 오류 발견 | 컴파일 시 오류 감지 |
| 코드 가독성 | 자유로운 문법 | 엄격한 문법으로 가독성 향상 |
| 객체 지향 | ES6에서 클래스 지원 | 클래스, 인터페이스, 제네릭 등 확장된 OOP 기능 |
| 개발 도구 | 기본적인 IDE 지원 | 강력한 타입 지원을 통한 자동 완성 및 오류 검출 |

🚀 TypeScript는 JavaScript의 **안정성, 유지보수성, 생산성을 크게 향상**시킵니다!

---

## 🛠 TypeScript 설치 및 환경 설정

### 1️⃣ TypeScript 설치 (Node.js 필요)
먼저, Node.js가 설치되어 있어야 합니다. Node.js가 없다면 [Node.js 공식 홈페이지](https://nodejs.org/)에서 다운로드하세요.

이제 터미널에서 다음 명령어를 실행하여 TypeScript를 전역(Global)으로 설치합니다:
```bash
npm install -g typescript
```
설치가 완료되면 버전을 확인해 보세요:
```bash
tsc -v
```

### 2️⃣ 프로젝트에 TypeScript 설정하기
프로젝트 폴더를 만들고 `tsconfig.json` 파일을 생성합니다:
```bash
mkdir my-typescript-project
cd my-typescript-project
npm init -y  # 기본 package.json 생성
npm install typescript --save-dev  # TypeScript를 프로젝트 종속성으로 설치
npx tsc --init  # 기본 tsconfig.json 생성
```

이제 `tsconfig.json` 파일을 열어 주요 옵션을 확인할 수 있습니다. 예제 설정:
```json
{
  "compilerOptions": {
    "target": "ES6",  
    "module": "CommonJS",
    "strict": true,  
    "outDir": "dist",  
    "rootDir": "src"  
  }
}
```
이 설정은 TypeScript를 **ES6 문법으로 컴파일하고, 소스 파일은 `src/`, 결과 파일은 `dist/`에 저장**하도록 합니다.

### 3️⃣ 첫 번째 TypeScript 코드 작성
📂 프로젝트 폴더 구조:
```
my-typescript-project/
 ├── src/
 │   ├── index.ts  # TypeScript 코드 작성
 ├── dist/  # 컴파일된 JavaScript 파일이 저장될 폴더
 ├── package.json
 ├── tsconfig.json
```

✍️ `src/index.ts` 파일을 만들고 다음 코드를 입력하세요:
```typescript
function greet(name: string): string {
    return `Hello, ${name}!`;
}

const user: string = "TypeScript Learner";
console.log(greet(user));
```

### 4️⃣ TypeScript 코드 실행
TypeScript 코드를 컴파일하려면 터미널에서 다음을 실행하세요:
```bash
npx tsc
```
그러면 `dist/index.js` 파일이 생성됩니다. 이제 Node.js로 실행하면 됩니다:
```bash
node dist/index.js
```
출력 결과:
```bash
Hello, TypeScript Learner!
```

---

## 📌 TypeScript 컴파일 과정 다이어그램

```mermaid
graph TD;
    A[TypeScript 코드 (index.ts)] -->|컴파일| B[TypeScript Compiler (tsc)];
    B -->|JavaScript 코드 생성| C[index.js];
    C -->|Node.js 실행| D[출력: "Hello, TypeScript Learner!"];
```

---

## 🔥 마무리 및 다음 단계
이제 TypeScript의 기본 개념과 설정 방법을 이해했습니다! 🎉
다음으로, TypeScript의 **기본 타입**과 활용법을 자세히 살펴보겠습니다. 🚀

👉 **다음 강의: [02-basic-types.md](./02-basic-types.md)**

