# NodeJS #

## NodeJS 소개 ##

1. NodeJS의 특징
    - NodeJS는 서버 사이드 JavaScript 런타임 환경으로, 다음과 같은 특징을 가지고 있습니다.

    1. 비동기 I/O: NodeJS는 비차단(non-blocking)I/O 모델을 사용합니다. 이는 I/O 작업이 완료될 때까지 기다리지 않고
    다음 작업을 수행할 수 있게 해줍니다.

    - 예시:
        ```javascript
        const fs = require('fs');

        fs.readFile('example.txt', 'utf8', (err, data) => {
        if (err) throw err;
        console.log(data);
        });
        console.log('This will be printed first');
        ```

    2. 이벤트 기반 아키텍처: NodeJS는 이벤트 루프를 사용하여 비동기 작업을 효율적으로 처리합니다.
    3. 단일 스레드 모델: NodeJS는 기본적으로 단일 스레드에서 동작하지만, 이벤트 루프를 통해 높은 동시성을 제공합니다.
    4. 크로스 플랫폼: Windows, macOS, Linux등 다양한 운영체제에서 실행 가능합니다.

2. NodeJS의 주요 사용 사례:
    1. 웹 서버 및 API: Express.js와 같은 프레임워크를 사용하여 빠르고 확장 가능한 웹 서버와 RESTful API를 구축할 수 있습니다.
    2. 실시간 애플리케이션: 채팅 앱, 게임 서버 등 실시간 데이터 처리가 필요한 애플리케이션에 적합합니다.
    3. 마이크로서비스: 경량화된 마이크로서비스 아키텍처를 구현하는 데 이상적입니다.
    4. CLI도구: npm, yarn등의 명령줄 도구를 개발하는 데 사용됩니다.
    5. 데이터 스트리밍: 대용량 데이터를 효율적으로 스트리밍 하는 애플리케이션에 적합합니다.


3. JavaScript 런타임으로서의 NodeJS
    - NodeJS는 Chrome의 V8 JavaScript 엔진을 기반으로 하지만, 브라우저 환경과는 다른 특징을 가집니다:

    1. 글로벌 객체: 브라우저의 `window`대신 `global`객체를 사용합니다.
        ```javascript
        console.log(global); // NodeJS의 글로벌 객체
        ```

    2. 모듈 시스템: 브라우저의 `<script>` 태그 대신 CommonJS 또는 ES 모듈 시스템을 사용합니다.
        ```javascript
        // CommonJS
        const fs = require('fs');

        // ES Modules (with .mjs extension or "type": "module" in package.json)
        import fs from 'fs';
        ```

    3. 파일 시스템 접근: NodeJS는 로컬 파일 시스템에 접근할 수 있습니다.
        ```javascript
        const fs = require('fs');
        fs.writeFileSync('example.txt', 'Hello, Node.js!');
        ```

    4. 서버 사이드 기능: 네트워크 소켓, HTTP 서버 생성 등 서버 사이드 기능을 제공합니다.

4. NodeJS의 아키텍처 (V8엔진, libuv)
    - NodeJS의 핵심 아키텍처는 두 가지 주요 컴포넌트로 구성됩니다:

    1. V8엔진:
        - Google이 개발한 오픈 소스 JavaScript 엔진입니다.
        - JavaScript 코드를 기계어로 컴파일하고 실행합니다.
        - Just-In-Time(JIT) 컴파일을 사용하여 성능을 최적화합니다.

    2. libuv:
        - 비동기 I/O를 처리하는 크로스 플랫폼 라이브러리입니다.
        - 이벤트 루프를 구현하여 비동기 작업을 관리합니다.
        - 파일 시스템, 네트워크, 동시성 등을 처리합니다.

    3. NodeJS 아키텍처의 주요 특징:
        - 이벤트 루프: 비동기 작업을 관리하고 콜백을 처리합니다.
        - 스레드 풀: libuv가 관리하는 스레드 풀을 사용하여 파일 I/O 등의 작업을 처리합니다.
        - 비차단 I/O: 시스템 커널의 비차단 작업을 활용하여 I/O 작업을 효율적으로 처리합니다.

    - NodeJS의 아키텍처를 이해하는 것은 효율적인 애플리케이션 개발에 중요합니다. 예를 들어,
    CPU 집약적인 작업은 이벤트 루프를 차단할 수 있으므로, 워커 스레드나 자식 프로세스를 사용하여 처리하는 것이 좋습니다.

    ```javascript
    const crypto = require('crypto');
    const { Worker, isMainThread, parentPort } = require('worker_threads');

    if (isMainThread) {
        const worker = new Worker(__filename);
        worker.on('message', (hash) => {
            console.log('Hash:', hash);
        });
    worker.postMessage('Calculate hash');
    } else {
    parentPort.on('message', () => {
        const hash = crypto.pbkdf2Sync('password', 'salt', 100000, 512, 'sha512');
        parentPort.postMessage(hash.toString('hex'));
    });
    }
    ```

    이 예제는 CPU 집약적인 해시 계산을 워커 스레드에서 수행하여 메인 이벤트 루프의 차단을 방지합니다.


### 모듈 시스템 ###

NodeJS의 모듈 시스템은 코드를 구조화하고 재사용성을 높이는 핵심 기능입니다.

1. CommonJS
    1. 동작 방식:
        - 모듈은 파일 단위로 캡슐화됩니다.
        - 모듈 내의 변수와 함수는 기본적으로 비공개입니다.
        - `require` 함수는 동기적으로 작동합니다.

    2. 순환 의존성 처리:
        - CommonJS는 부분적으로 평가된 객체를 반환하여 순환 의존성을 해결합니다.
        - 예시:
        ```javascript
        // a.js
        console.log('a starting');
        exports.done = false;
        const b = require('./b.js');
        console.log('in a, b.done = %j', b.done);
        exports.done = true;
        console.log('a done');

        // b.js
        console.log('b starting');
        exports.done = false;
        const a = require('./a.js');
        console.log('in b, a.done = %j', a.done);
        exports.done = true;
        console.log('b done');

        // main.js
        console.log('main starting');
        const a = require('./a.js');
        const b = require('./b.js');
        console.log('in main, a.done = %j, b.done = %j', a.done, b.done);
        ```
        - 이 예제를 실행하면 순환 의존성에도 불구하고 오류 없이 실행됩니다.

    3. 모듈 캐싱: `require`로 불러온 모듈은 캐시되어 여러 번 호출해도 한 번만 실행됩니다.

2. ES Modules:
    1. 동적 임포트: ES Modules는 동적 임포트를 지원합니다.
        ```javascript
        (async () => {
            if (someCondition) {
                const { default: myModule } = await import('./myModule.js');
                myModule.doSomething();
            }
        })();
        ```
    2. 정적 분석: ES Modules는 정적 구조를 가지므로 정적 분석이 가능합니다. 이는 트리 쉐이킹과 같은 최적화를 가능하게 합니다.

    3. 최상위 await: ES Modules에서는 최상위 레벨에서 `await`를 사용할 수 있습니다.

### 전역 객체(global, process) ###

1. global객체:
    1. 암시적 전역 변수: `var`로 선언된 변수나 함수 선언문은 암시적으로 `global` 객체의 속성이 됩니다.

        ```javascript
        var implicitGlobal = 'I am global';
        function implicitGlobalFunction() {}

        console.log(global.implicitGlobal); // 'I am global'
        console.log(global.implicitGlobalFunction); // [Function: implicitGlobalFunction]
        ```

    2. 주의사항: `let`과 `const`로 선언된 변수는 `global` 객체의 속성이 되지 않습니다.

2. process 객체:
    1. 표준 스트림:
        - `process.stdin`: 표준 입력
        - `process.stdout`: 표준 출력
        - `process.stderr`:  표준 에러

        ```javascript
        process.stdout.write('Hello, ');
        process.stdout.write('World!\n');

        process.stdin.on('data', (data) => {
            console.log(`You typed: ${data.toString().trim()}`);
        });
        ```

    2. 시그널 처리:
        ```javascript
        process.on('SIGINT', () => {
            console.log('Received SIGINT. Press Control-D to exit.');
        });
        ```

    3. 메모리 사용량:
        ```javascript
        console.log(process.memoryUsage());
        ```

### Buffer와 스트림 ###

1. Buffer:
    1. 버퍼 조작:
        ```javascript
        const buf = Buffer.from([0x62, 0x75, 0x66, 0x66, 0x65, 0x72]);
        console.log(buf.toString()); // 'buffer'

        buf.write('BUFFER');
        console.log(buf.toString()); // 'BUFFER'
        ```

    2. 버퍼 슬라이싱:
        ```javascript
        const buf = Buffer.from('Hello World');
        console.log(buf.slice(0, 5).toString()); // 'Hello'
        ```

2. 스트림:
    1. Transform 스트림:
        ```javascript
        const { Transform } = require('stream');

        const upperCaseTr = new Transform({
        transform(chunk, encoding, callback) {
            this.push(chunk.toString().toUpperCase());
            callback();
        }
        });

        process.stdin.pipe(upperCaseTr).pipe(process.stdout);
        ```

    2. 백프레셔 처리:
        ```javascript
        const fs = require('fs');
        const server = require('http').createServer();

        server.on('request', (req, res) => {
            const src = fs.createReadStream('large-file.txt');
            src.pipe(res);
        });

        server.listen(8000);
        ```

### 이벤트 이미터 ###

1. 오류 처리:
    ```javascript
    const myEmitter = new MyEmitter();

    myEmitter.on('error', (err) => {
        console.error('Whoops! There was an error');
    });

    myEmitter.emit('error', new Error('Something went wrong'));
    ```

2. 한 번만 실행되는 리스너:
    ```javascript
    myEmitter.once('event', () => {
        console.log('This will be called only once');
    });
    ```

3. 비동기 vs 동기 이벤트:
    ```javascript
    const myEmitter = new MyEmitter();

    myEmitter.on('event', (a, b) => {
        setImmediate(() => {
            console.log('this happens asynchronously');
        });
    });

    myEmitter.emit('event', 'a', 'b');
    ```
    - `setImmediate`를 사용하면 이벤트 핸들러가 비동기적으로 실행됩니다.

### 파일 시스템 작업 ###

NodeJS의 `fs`(File System) 모듈은 파일 시스템과 상호 작용할 수 있는 API를 제공합니다.
이 모듈을 사용하여 파일을 읽고, 쓰고, 수정하며, 디렉토리를 관리할 수 있습니다.

1. 동기 vs 비동기 파일 연산
    - NodeJS의 `fs`모듈은 대부분의 작업에 대해 동기와 비동기 버전을 모두 제공합니다.

    1. 동기 작업:
        - 파일 작업이 완료될 때까지 다음 코드 실행을 차단합니다.
        - 주로 애플리케이션 초기화 단계나 간단한 스크립트에서 사용됩니다.

        - 예시:
        ```javascript
        const fs = require('fs');

        try {
            const data = fs.readFileSync('example.txt', 'utf8');
            console.log(data);
        } catch (err) {
            console.error('Error reading file:', err);
        }
        ```

    2. 비동기 작업:
        - 파일 작업을 백그라운드에서 실행하고, 완료 시 콜백 함수를 호출합니다.
        - 대부분의 상황에서 권장되는 방식입니다.
        
        - 예시 (콜백 방식):
        ```javascript
        const fs = require('fs');

        fs.readFile('example.txt', 'utf8', (err, data) => {
        if (err) {
            console.error('Error reading file:', err);
            return;
        }
        console.log(data);
        });
        ```

        - 예시(Promise 방식):
        ```javascript
        const fs = require('fs').promises;

        fs.readFile('example.txt', 'utf8')
            .then(data => console.log(data))
            .catch(err => console.error('Error reading file:', err));
        ```

        - 예시 (async/await 방식):
        ```javascript
        const fs = require('fs').promises;

        async function readFile() {
            try {
                const data = await fs.readFile('example.txt', 'utf8');
                console.log(data);
            } catch (err) {
                console.error('Error reading file:', err);
            }
        }

        readFile();
        ```

2. 디렉토리 조작
    - `fs`모듈을 사용하여 디렉토리를 생성, 읽기, 삭제할 수 있습니다.

    1. 디렉토리 생성:
        ```javascript
        const fs = require('fs').promises;

        async function createDirectory() {
            try {
                await fs.mkdir('newDir');
                console.log('Directory created successfully');
            } catch (err) {
                if (err.code === 'EEXIST') {
                console.log('Directory already exists');
                } else {
                console.error('Error creating directory:', err);
                }
            }
        }

        createDirectory();
        ```

    2. 디렉토리 내용 읽기:
        ```javascript
        const fs = require('fs').promises;
        const path = require('path');

        async function readDirectory(dirPath) {
            try {
                const files = await fs.readdir(dirPath);
                for (const file of files) {
                const filePath = path.join(dirPath, file);
                const stats = await fs.stat(filePath);
                if (stats.isDirectory()) {
                    console.log(`${file} is a directory`);
                } else {
                    console.log(`${file} is a file`);
                }
                }
            } catch (err) {
                console.error('Error reading directory:', err);
            }
        }

        readDirectory('.');
        ```

    3. 디렉토리 삭제:
        ```javascript
        const fs = require('fs').promises;

        async function removeDirectory(dirPath) {
            try {
                await fs.rmdir(dirPath, { recursive: true });
                console.log(`${dirPath} is deleted!`);
            } catch (err) {
                console.error('Error removing directory:', err);
            }
        }

        removeDirectory('dirToDelete');
        ```

3. 파일 감시와 변경 감지
    - `fs.watch()`메서드를 사용하여 파일이나 디렉토리의 변경 사항을 감지할 수 있습니다.

    ```javascript
    const fs = require('fs');

    fs.watch('example.txt', (eventType, filename) => {
        if (filename) {
            console.log(`${filename} file Changed`);
            if (eventType === 'rename') {
            console.log('File was renamed or deleted');
            } else if (eventType === 'change') {
            console.log('File content was modified');
            }
        }
    });
    ```

    - 주의사항:
        - `fs.watch()`는 운영 체제에 따라 동작이 다를 수 있습니다.
        - 일부 시스템에서는 변경 이벤트가 여러 번 발생할 수 있습니다.
        - 대규모 애플리케이션에서는 `chokidar`와 같은 써드파티 라이브러리를 사용하는 것이 더 안정적일 수 있습니다.

4. 고급 파일 시스템 작업:
    1. 스트림을 이용한 대용량 파일 처리:
        ```javascript
        const fs = require('fs');

        const readStream = fs.createReadStream('largefile.txt');
        const writeStream = fs.createWriteStream('output.txt');

        readStream.pipe(writeStream);

        readStream.on('end', () => {
            console.log('File copy completed');
        });
        ```

    2. 임시 파일 및 디렉토리 생성
        ```javascript
        const fs = require('fs').promises;
        const os = require('os');
        const path = require('path');

        async function createTempFile() {
        const tempDir = os.tmpdir();
        const tempFilePath = path.join(tempDir, 'tempfile-' + Math.random().toString(36).substr(2, 9));
        
        await fs.writeFile(tempFilePath, 'This is temporary content');
        console.log(`Temporary file created at: ${tempFilePath}`);
        
        return tempFilePath;
        }

        createTempFile().then(tempFile => {
        console.log(`You can find the temp file at: ${tempFile}`);
        });
        ```

### 네트워킹 ###

NodeJS는 강력한 네트워킹 기능을 제공하며, 이를 통해 다양한 네트워크 애플리케이션을 개발할 수 있습니다.
주요 모듈로는 `net`, `dgram`, `http`, `https`, 그리고 `dns`가 있습니다.

1. TCP 서버 및 클라이언트 생성
    - TCP(Transmission Control Protocol)는 신뢰성 있는 데이터 전송을 보장하는 연결 지향적 프로토콜입니다.
    NodeJS의 `net` 모듈을 사용하여 TCP 서버와 클라이언트를 구현할 수 있습니다.

    1. TCP 서버 생성:
        ```javascript
        const net = require('net');

        const server = net.createServer((socket) => {
            console.log('Client connected');
            
            socket.on('data', (data) => {
                console.log('Received data:', data.toString());
                socket.write('Server received: ' + data);
            });
            
            socket.on('end', () => {
                console.log('Client disconnected');
            });
        });

        const PORT = 3000;
        server.listen(PORT, () => {
            console.log(`Server listening on port ${PORT}`);
        });
        ```

    2. TCP 클라이언트 생성:
        ```javascript
        const net = require('net');

        const client = new net.Socket();
        const PORT = 3000;
        const HOST = '127.0.0.1';

        client.connect(PORT, HOST, () => {
            console.log('Connected to server');
            client.write('Hello, server!');
        });

        client.on('data', (data) => {
            console.log('Received from server:', data.toString());
            client.destroy(); // 데이터를 받은 후 연결 종료
        });

        client.on('close', () => {
            console.log('Connection closed');
        });
        ```

    - 이 예제에서 서버는 클라이언트의 연결을 수신하고, 데이터를 받아 응답합니다. 클라이언트는 서버에 연결하여 메시지를 보내고 응답을 받습니다.

2. UDP 소켓 프로그래밍
    - UDP(User Datagram Protocol)는 연결 없는 프로토콜로, 빠른 데이터 전송이 필요하지만 신뢰성이 덜 중요한 경우에 사용됩니다.
    NodeJS의 `dgram` 모듈을 사용하여 UDP 통신을 구현할 수 있습니다.

    1. UDP 서버:
        ```javascript
        const dgram = require('dgram');
        const server = dgram.createSocket('udp4');

        server.on('error', (err) => {
            console.log(`Server error:\n${err.stack}`);
            server.close();
        });

        server.on('message', (msg, rinfo) => {
            console.log(`Server received: ${msg} from ${rinfo.address}:${rinfo.port}`);
        });

        server.on('listening', () => {
            const address = server.address();
            console.log(`Server listening ${address.address}:${address.port}`);
        });

        server.bind(41234);
        ```

    2. UDP 클라이언트:
        ```javascript
        const dgram = require('dgram');
        const message = Buffer.from('Hello, UDP server!');
        const client = dgram.createSocket('udp4');

        client.send(message, 41234, 'localhost', (err) => {
            if (err) {
                console.log(err);
                client.close();
            } else {
                console.log('UDP message sent');
                client.close();
            }
        });
        ```
    - UDP는 연결 설정 과정이 없어 TCP보다 빠르지만, 메시지 전달의 신뢰성은 보장되지 않습니다.

3. DNS 모듈 사용
    - DNS(Domain Name System)조회를 수행하기 위해 NodeJS의 `dns`모듈을 사용할 수 있습니다.

    1. 호스트 이름으로 IP주소 조회:
        ```javascript
        const dns = require('dns');

        dns.lookup('www.example.com', (err, address, family) => {
            if (err) throw err;
            console.log('address: %j family: IPv%s', address, family);
        });
        ```

    2. DNS 레코드 조회:
        ```javascript
        const dns = require('dns');

        dns.resolve4('www.example.com', (err, addresses) => {
        if (err) throw err;
        
        console.log(`IP addresses: ${JSON.stringify(addresses)}`);

        addresses.forEach((a) => {
            dns.reverse(a, (err, hostnames) => {
                if (err) {
                    throw err;
                }
                console.log(`IP address: ${a} reverse for: ${JSON.stringify(hostnames)}`);
            });
        });
        });
        ```
    
    3. Promise API 사용:
        ```javascript
        const dns = require('dns').promises;

        async function resolveDNS() {
            try {
                const result = await dns.resolve('www.example.com', 'A');
                console.log('A records:', result);
                
                const mxRecords = await dns.resolve('example.com', 'MX');
                console.log('MX records:', mxRecords);
            } catch (err) {
                console.error('DNS resolution error:', err);
            }
        }

        resolveDNS();
        ```

### HTTP/HTTPS 서버 ###

NodeJS는 `http`및 `https`모듈을 통해 웹 서버를 쉽게 생성할 수 있게 해줍니다. 이 모듈들은
HTTP/HTTPS 프로토콜을 사용하여 클라이언트와 서버 간의 통신을 가능하게 합니다.

1. 기본 HTTP 서버 생성
    - NodeJS의 `http` 모듈을 사용하여 간단한 HTTP 서버를 만들 수 있습니다.

    ```javascript
    const http = require('http');

    const server = http.createServer((req, res) => {
        res.statusCode = 200;
        res.setHeader('Content-Type', 'text/plain');
        res.end('Hello, World!');
    });

    const PORT = 3000;
    server.listen(PORT, () => {
        console.log(`Server running at http://localhost:${PORT}/`);
    });
    ```

    - 이 예제는 기본적인 HTTP 서버를 생성하고, 모든 요청에 대해 "Hello, World!"라는 응답을 반환합니다.

    - 요청 객체(`req`)와 응답 객체(`res`)를 더 자세히 살펴보겠습니다:
        1. 요청 객체(`req`)의 주요 속성/메서드:
            - `req.url`: 요청된 URL
            - `req.method`: HTTP 메서드 (GET, POST 등)
            - `req.headers`: 요청 헤더
            - `req.on('data', callback)`: 요청 본문 데이터 수신

        2. 응답 객체(`res`)의 주요 메서드:
            - `res.writeHead(statusCode, headers)`: 상태 코드와 헤더 설정
            - `res.write(data)`: 응답 본문 작성
            - `res.end([data])`: 응답 종료

2. 라우팅 구현
    - 서버에서 다양한 URL 경로에 대해 다른 응답을 제공하려면 라우팅을 구현해야 합니다.

    ```javascript
    const http = require('http');
    const url = require('url');

    const server = http.createServer((req, res) => {
        const parsedUrl = url.parse(req.url, true);
        const path = parsedUrl.pathname;

        res.setHeader('Content-Type', 'text/plain');

        switch (path) {
            case '/':
            res.statusCode = 200;
            res.end('Home Page');
            break;
            case '/about':
            res.statusCode = 200;
            res.end('About Page');
            break;
            default:
            res.statusCode = 404;
            res.end('404 Not Found');
        }
    });

    server.listen(3000, () => {
        console.log('Server running on port 3000');
    });
    ```

    - 이 예제는 기본적인 라우팅을 구현하여 다른 URL 경로에 대해 다른 응답을 제공합니다.

3. HTTPS 서버 설정
    - HTTPS 서버를 설정하려면 SSL/TLS 인증서가 필요합니다. 개발 목적으로는 자체 서명된 인증서를 사용할 수 있습니다.
    
    1. 자체 서명 인증서 생성:
        ```bash
        openssl req -nodes -new -x509 -keyout server.key -out server.cert
        ```

    2. HTTPS 서버 생성:
        ```javascript
        const https = require('https');
        const fs = require('fs');

        const options = {
            key: fs.readFileSync('server.key'),
            cert: fs.readFileSync('server.cert')
        };

        const server = https.createServer(options, (req, res) => {
            res.statusCode = 200;
            res.setHeader('Content-Type', 'text/plain');
            res.end('Hello, secure world!');
        });

        server.listen(443, () => {
            console.log('HTTPS server running on port 443');
        });
        ```
        - 이 예제는 HTTPS 서버를 생성하고 SSL/TLS 인증서를 사용하여 암호화된 연결을 제공합니다.

4. 추가 고급 주제:
    1. 미들웨어 패턴: Express.js와 같은 프레임워크에서 널리 사용되는 미들웨어 패턴을 직접 구현할 수 있습니다.

    ```javascript
    function logger(req, res, next) {
        console.log(`${req.method} ${req.url}`);
        next();
    }

    function errorHandler(err, req, res, next) {
        console.error(err.stack);
        res.status(500).send('Something broke!');
    }

    // 미들웨어 사용
    const server = http.createServer((req, res) => {
        logger(req, res, () => {
            // 라우팅 로직
        });
    });
    ```

    2. 스트리밍 응답: 대용량 파일을 효율적으로 전송하기 위해 스트리밍을 사용할 수 있습니다.

    ```javascript
    const http = require('http');
    const fs = require('fs');

    const server = http.createServer((req, res) => {
        if (req.url === '/video' && req.method === 'GET') {
            const videoPath = './video.mp4';
            const stat = fs.statSync(videoPath);
            
            res.writeHead(200, {
            'Content-Type': 'video/mp4',
            'Content-Length': stat.size
            });

            const stream = fs.createReadStream(videoPath);
            stream.pipe(res);
        }
    });
    ```

    3. WebSocket 지원: HTTP 서버에 WebSocket 지원을 추가하여 실시간 양방향 통신을 구현할 수 있습니다.

    ```javascript
    const http = require('http');
    const WebSocket = require('ws');

    const server = http.createServer((req, res) => {
        res.end('HTTP Server');
    });

    const wss = new WebSocket.Server({ server });

    wss.on('connection', (ws) => {
        ws.on('message', (message) => {
            console.log('Received: %s', message);
            ws.send(`Echo: ${message}`);
        });
    });

    server.listen(8080, () => {
        console.log('Server is running on http://localhost:8080');
    });
    ```