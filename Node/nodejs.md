# Node.js 핵심 개념 및 API #

### Node.js의 이벤트 루프 ###

* 이벤트 루프의 6단계.

  1. timers: setTimeout()과 setInterval()로 예약된 콜백 함수 실행.
  2. pending callbacks: 이전 이벤트 루프에서 연기된 I/O 콜백 함수 실행.
  3. idle, prepare: 내부용으로 사용.
  4. poll: 새로운 I/O 이벤트 가져오기, I/O 관련 콜백 실행.
  5. check: setImmediate()로 예약된 콜백 함수 실행.
  6. close callbacks: 일부 close 이벤트 콜백 함수 실행 (예: socket.on('close'), ...))

* 마이크로태스크와 매크로태스크
  - 마이크로태스크: process.nextTick(), Promise 콜백, queueMicrotask() 등.
  - 매크로태스크: setTimeout(), setInterval(), setImmediate() 등.
  - 각 단계 사이와 각 단계 내에서 마이크로태스크 큐 우선 실행.

```javascript
// 마이크로태스크와 매크로태스크 예제
console.log("Start");

setTimeout(() => {
  console.log("Timeout 1");
  Promise.resolve().then(() => {
    console.log("Promise 1");
  });
}, 0);

setTimeout(() => {
  console.log("Timeout 2");
  process.nextTick(() => {
    console.log("Process.nextTick 1");
  });
}, 0);

Promise.resolve().then(() => {
  console.log("Promise 2");
  process.nextTick(() => {
    console.log("Process.nextTick 2");
  });
});

console.log("End");

// 출력 결과
// Start
// End
// Promise 2
// Process.nextTick 2
// Timeout 1
// Promise 1
// Timeout 2
// Process.nextTick 1
```

### Node.js 모듈 시스템 ###

* Node.js 모듈 시스템.
  - 모듈 유형
    - 내장 모듈: Node.js에 기본적으로 포함돈 모듈(fs, path, http 등).
    - 로컬 모듈: 사용자가 직접 작성한 모듈.
    - 써드 파티 모듈: npm을 통해 설치한 외부 모듈.
  - 모듈 캐싱: 한 번 로드된 모듈은 캐시되어 재사용됨.
  - 모듈 순환 참조: 모듈 간 순환 참조 시 순환 참조되는 부분은 빈 객체로 처리됨.

```javascript
// 모듈 캐싱 예제
// counter.js
let count = 0;
function increment() {
  count++;
}
module.exports = {
  getCount: function () {
    return count;
  },
  increment: increment,
};

// main.js
const counter1 = require("./counter");
const counter2 = require("./counter");

counter1.increment();
console.log(counter1.getCount()); // 1
console.log(counter2.getCount()); // 1

// 모듈 순환 참조 예제
// a.js
exports.a = 1;
require("./b");

// b.js
exports.b = 2;
const a = require("./a");
console.log(a); // { a: 1 }

// main.js
const a = require("./a");
const b = require("./b");
console.log(a); // { a: 1 }
console.log(b); // { b: 2 }
```

### Node.js 내장 모듈 ###

* Node.js 내장 모듈
  - fs 모듈:
    - 동기 메서드와 비동기 메서드 제공.
    - 파일 읽기/쓰기, 디렉토리 생성/삭제, 파일 스트림 등.
  - path 모듈:
    - 파일 경로 관련 유틸리티 메서드 제공.
    - 경로 구성요소 추출, 경로 생성, 경로 정규화 등.
  - http 모듈:
    - HTTP 서버 생성 및 요청 처리.
    - HTTP 클라이언트 요청 생성 및 응답 처리.
  - events 모듈:
    - 이벤트 이미터 클래스 제공.
    - 사용자 정의 이벤트 생성 및 처리.

```javascript
// fs 모듈 - 비동기 파일 읽기 예제
const fs = require("fs");

fs.readFile("file.txt", "utf8", (err, data) => {
  if (err) {
    console.error(err);
    return;
  }
  console.log(data);
});

// fs 모듈 - 동기 파일 쓰기 예제
const fs = require("fs");

try {
  fs.writeFileSync("file.txt", "Hello, Node.js!", "utf8");
  console.log("File saved.");
} catch (err) {
  console.error(err);
}

// fs 모듈 - 파일 스트림 예제
const fs = require("fs");

const readStream = fs.createReadStream("input.txt", "utf8");
const writeStream = fs.createWriteStream("output.txt", "utf8");

readStream.on("data", (chunk) => {
  writeStream.write(chunk);
});

readStream.on("end", () => {
  writeStream.end();
  console.log("File copied.");
});

// path 모듈 예제
const path = require("path");

const filePath = "/Users/john/Documents/file.txt";
console.log(path.dirname(filePath)); // /Users/john/Documents
console.log(path.basename(filePath)); // file.txt
console.log(path.extname(filePath)); // .txt

const newFilePath = path.join("/Users/john", "Documents", "new_file.txt");
console.log(newFilePath); // /Users/john/Documents/new_file.txt

// http 모듈 - 서버 예제
const http = require("http");

const server = http.createServer((req, res) => {
  res.writeHead(200, { "Content-Type": "text/html" });
  res.end("<h1>Hello, World!</h1>");
});

server.listen(3000, () => {
  console.log("Server running at http://localhost:3000/");
});

// http 모듈 - 클라이언트 예제
const http = require("http");

const options = {
  hostname: "api.example.com",
  path: "/data",
  method: "GET",
};

const req = http.request(options, (res) => {
  let data = "";

  res.on("data", (chunk) => {
    data += chunk;
  });

  res.on("end", () => {
    console.log(JSON.parse(data));
  });
});

req.on("error", (err) => {
  console.error(err);
});

req.end();

// events 모듈 - 이벤트 에미터 상속 예제
const EventEmitter = require("events");

class MyEmitter extends EventEmitter {}

const myEmitter = new MyEmitter();
myEmitter.on("event", (data) => {
  console.log(data);
});

myEmitter.emit("event", "Hello, Events!");

// events 모듈 - 오류 이벤트 처리 예제
const EventEmitter = require("events");

class MyEmitter extends EventEmitter {}

const myEmitter = new MyEmitter();
myEmitter.on("error", (err) => {
  console.error("Error occurred:", err);
});

myEmitter.emit("error", new Error("Something went wrong!"));
```

### npm (Node Package Manager) ###

* npm (Node Package Manager)
  - package.json 파일
    - name: 패키지 이름.
    - version: 패키지 버전.
    - description: 패키지 설명.
    - main: 패키지 진입점 파일
    - scripts: 자동화된 스크립트 명령어.
    - dependencies: 프로덕션 환경에서 필요한 의존 패키지
    - devDependencies: 개발 환경에서만 필요한 의존 패키지
  - npm 명령어
    - npm init: package.json 파일 생성.
    - npm install (npm i): 패키지 설치.
    - npm update: 패키지 업데이트.
    - npm uninstall: 패키지 삭제.
    - npm run: package.json의 scripts 명령어 실행.
    - npm publish: 패키지 배포.
  - Semantic Versioning(SemVer)
    - 패키지 버전 관리를 위한 명세.
    - "Major.Minor.Patch" 형식(예: 1.2.3)
    - Major: 기존 버전과 호환되지 않는 변경사항.
    - Minor: 기존 버전과 호환되는 기능 추가.
    - Patch: 기존 버전과 호환되는 버그 수정.

```json
// package.json 예제
{
  "name": "my-package",
  "version": "1.0.0",
  "description": "A sample Node.js package",
  "main": "index.js",
  "scripts": {
    "start": "node index.js",
    "test": "jest"
  },
  "dependencies": {
    "express": "^4.17.1",
    "mongoose": "^6.0.0"
  },
  "devDependencies": {
    "jest": "^27.0.0"
  }
}
```

### 환경 변수와 프로세스 관리 ###

* 환경 변수와 프로세스 관리.
  - 환경 변수:
    - process.env 객체를 통해 접근.
    - NODE_ENV: 애플리케이션 실행 환경 (development, production, test 등).
    - PORT: 애플리케이션 실행 포트.
    - DATABASE_URL: 데이터베이스 연결 URL
  - process 객체:
    - process.pid: 현재 프로세스 ID.
    - process.cwd(): 현재 프로세스의 작업 디렉토리.
    - process.argv: 프로세스 실행 시 전달된 명령행 인수.
    - process.exit(): 프로그램 종료.
    - process.on(): 프로세스 이벤트 처리.
  - 프로세스 관리:
    - 프로세스 생성: child_process 모듈 사용.
    - 프로세스 간 통신: IPC(Inter-Process Communication)사용
    - 프로세스 모니터링: process 이벤트 및 종료 코드 처리.

```javascript
// 환경 변수 예제
console.log(process.env.NODE_ENV); // development
console.log(process.env.PORT); // 3000

// process 객체 예제
console.log(process.pid); // 1234
console.log(process.cwd()); // /Users/john/project
console.log(process.argv); // ['/usr/local/bin/node', 'app.js', '--port', '3000']

process.on("exit", (code) => {
  console.log(`Process exited with code: ${code}`);
});

process.exit(1);

// 프로세스 생성 예제
const { spawn } = require("child_process");

const child = spawn("ls", ["-lh", "/usr"]);

child.stdout.on("data", (data) => {
  console.log(`stdout: ${data}`);
});

child.stderr.on("data", (data) => {
  console.error(`stderr: ${data}`);
});

child.on("close", (code) => {
  console.log(`child process exited with code ${code}`);
});

// 프로세스 간 통신 예제
// parent.js
const { fork } = require("child_process");

const child = fork("child.js");

child.on("message", (msg) => {
  console.log("Message from child:", msg);
});

child.send({ hello: "world" });

// child.js
process.on("message", (msg) => {
  console.log("Message from parent:", msg);
  process.send({ foo: "bar" });
});
```