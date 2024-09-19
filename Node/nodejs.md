# NodeJS #

## NodeJS란? ##

NodeJS는 Chrome V8 JavaScript 엔진으로 빌드된 JavaScript 런타임 환경입니다.
이는 JavaScript를 서버 사이드에서 실행할 수 있게 해주는 플랫폼으로, 웹 애플리케이션 개발에 주로 사용됩니다.

- 주요 특징:
    - 비동기 I/O 처리
    - 이벤트 기반 아키텍처
    - 단일 스레드 모델

## NodeJS의 특징과 장점 ##

1. 비동기 및 이벤트 기반: NodeJS는 비동기 프로그래밍 모델을 사용합니다. 이는 I/O 작업이 완료될 때까지
기다리지 않고 다음 작업을 수행할 수 있게 해줍니다. 이로 인해 높은 동시성과 효율적인 리소스 사용이 가능합니다.

    ```javascript
    const fs = require('fs');

    fs.readFile('example.txt', 'utf8', (err, data) => {
    if (err) throw err;
    console.log(data);
    });
    console.log('This will be printed first');
    ```

2. 빠른 실행 속도: V8엔진을 사용하여 JavaScript 코드를 빠르게 실행합니다.
3. 풍부한 생태계: npm(Node Package Manager)을 통해 수많은 오픈 소스 라이브러리와 도구를 사용할 수 있습니다.
4. 크로스 플랫폼: Windows, macOS, Linux 등 모든 운영 체제에서 실행 가능합니다.
5. 풀스택 개발: 프론트엔드와 백엔드 모두에서 JavaScript를 사용할 수 있어 개발 효율성이 높아집니다.

## NodeJS의 역사와 발전 ##

1. 2009년: Ryan Dahl에 의해 처음 소개됨
2. 20011년: npm(Node Package Manager)도입
3. 2015년: io.js와의 병합으로 Node.js 4.0.0 출시
4. 현재: 지속적인 업데이트와 개선이 이루어지고 있음.

주요 버전 변화:
    - Node.js 6.0: 성능 개선 및 ES6 기능 지원'
    - Node.js 8.0: async/await 지원
    - Node.js 10.0: HTTP/2 지원
    - Node.js 12.0: V8엔진 업그레이드, 보안 강화
    - Node.js 14.0: 진단 보고 도구 개선, ES 모듈 지원 강화

## NodeJS 설치 및 환경 설정 ##

1. 다양한 운영 체제에서의 설치 방법
    1. Windows:
        - NodeJS 공식 웹 사이트(https://nodejs.org/)에서 설치 파일 다운로드
        - 다운로드 한 .msi 파일 실행 및 설치 마법사 따라하기

    2. macOS:
        - Homebrew를 사용한 설치:
        ```bash
        brew install node
        ```

        - 또는 공식 웹사이트에서 .pkg 파일 다운로드 및 설치

    3. Linux(Ubuntu/Debian)
        ```bash
        sudo apt update
        sudo apt install nodejs npm
        ```

    - 설치 확인:
    ```bash
    node --version
    npm --version
    ```

2. NVM(Node Version Manager)사용
    - NVM은 여러 버전의 Node.js를 관리할 수 있게 해주는 도구입니다.

    - 설치 (Unix, macOS):
    ```bash
    curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.0/install.sh | bash
    ```

    - 주요 NVM 명령어:
        - 특정 버전 설치: `nvm install 14.17.0`
        - 특정 버전 사용: `nvm use 14.17.0`
        - 설치된 버전 목록 확인: `nvm ls`

3. 기본 개발 환경 설정

    1. 코드 에디터 설치:
        - Visual Studio Code, Sublime Text, WebStorm 등

    2. 버전 관리 시스템 설정:
        - Git 설치 및 구성

    3. 프로젝트 초기화:
        ```bash
        mkdir my-node-project
        cd my-node-project
        npm init -y
        ```

    4. .gitignore 파일 생성:
        ```bash
        node_modules/
        .env
        ```

    5. ESLint 설정 (코드 품질 관리):
        ```bash
        npm install eslint --save-dev
        npx eslint --init
        ```

    6. 첫 번째 NodeJS 스크립트 작성 및 실행:
        ```javascript
        // index.js
        console.log('Hello, Node.js!');
        ```
        실행:
        ```bash
        node index.js
        ```