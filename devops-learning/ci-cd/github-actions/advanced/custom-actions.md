## 1. 문제/질문 분석

- **핵심 포인트:**  
  - 기본 액션(공식 또는 외부 액션)과 달리, 프로젝트에 특화된 기능을 구현하기 위해 **자체 액션(Custom Action)** 을 개발하는 방법 이해  
  - JavaScript(Node.js), Docker, 또는 Composite Action 방식 등 다양한 개발 방식 중 선택 및 활용  
  - 액션의 입력(Input), 출력(Output), 오류 처리 등 인터페이스 정의와 문서화 필요

- **기술적 컨텍스트:**  
  - GitHub Actions에서 사용자 정의 액션은 YAML 파일(`action.yml`)을 통해 액션의 인터페이스와 동작 방식을 정의하고, 실제 로직은 JavaScript, Shell 스크립트 또는 Docker 컨테이너를 이용하여 구현  
  - 재사용성과 유지보수를 고려하여, 액션을 모듈화하고 명확하게 문서화하는 것이 중요

---

## 2. 해결 방안 제시

### 방안 1: JavaScript 기반 사용자 정의 액션 개발
- **장점:**  
  - Node.js 생태계를 활용한 다양한 라이브러리 사용 가능  
  - 빠른 개발 및 디버깅 지원 (로컬에서 테스트 가능)
- **단점:**  
  - Node.js 런타임 환경 의존성이 있음

### 방안 2: Docker 기반 사용자 정의 액션 개발
- **장점:**  
  - 실행 환경을 컨테이너로 완벽하게 제어 가능하여, 특정 언어나 런타임에 구애받지 않음  
  - 복잡한 의존성이 있는 경우에도 안정적으로 실행 가능
- **단점:**  
  - Docker 이미지 빌드 및 배포 관리 필요, 초기 설정이 다소 복잡할 수 있음

### 방안 3: Composite Actions 사용
- **장점:**  
  - 기존의 여러 액션(공식/커스텀 액션)을 하나의 워크플로우 스텝으로 묶어 재사용성 및 가독성 향상  
  - 별도의 스크립트 작성 없이 YAML 만으로 구성 가능
- **단점:**  
  - 복잡한 로직을 구현하기에는 한계가 있음

---

## 3. 구체적 구현 방법

### 3.1 JavaScript 기반 사용자 정의 액션

1. **프로젝트 구조 구성:**  
   프로젝트 내 특정 디렉토리(예: `.github/actions/my-custom-action`)를 생성하여 액션 관련 파일을 관리합니다.

   ```plaintext
   .github/
     └── actions/
         └── my-custom-action/
             ├── action.yml
             ├── index.js
             └── package.json
   ```

2. **액션 메타데이터 작성 (`action.yml`):**

   ```yaml
   # .github/actions/my-custom-action/action.yml
   name: 'My Custom Action'
   description: '프로젝트 특화 기능을 수행하는 사용자 정의 액션'
   inputs:
     example-input:
       description: '액션에 전달할 입력 값'
       required: true
       default: 'Hello'
   outputs:
     example-output:
       description: '액션 실행 결과로 생성된 값'
   runs:
     using: 'node16'  # Node.js 런타임 버전 명시
     main: 'index.js'
   ```

3. **실제 액션 로직 작성 (`index.js`):**

   ```javascript
   // .github/actions/my-custom-action/index.js
   const core = require('@actions/core');

   try {
     // 입력값 읽기
     const inputValue = core.getInput('example-input');
     core.info(`입력값: ${inputValue}`);

     // 예시 로직: 문자열을 대문자로 변환
     const result = inputValue.toUpperCase();
     core.info(`변환 결과: ${result}`);

     // 결과값 출력
     core.setOutput('example-output', result);
   } catch (error) {
     core.setFailed(`액션 실행 중 오류 발생: ${error.message}`);
   }
   ```

4. **package.json 설정:**  
   Node.js 라이브러리(예: `@actions/core`)를 사용하기 위해 의존성을 명시합니다.

   ```json
   {
     "name": "my-custom-action",
     "version": "1.0.0",
     "main": "index.js",
     "dependencies": {
       "@actions/core": "^1.10.0"
     }
   }
   ```

5. **로컬 테스트 및 디버깅:**  
   - Node.js 환경에서 직접 실행하거나, [act](https://github.com/nektos/act)와 같은 도구를 활용하여 GitHub Actions 환경을 로컬에서 테스트할 수 있습니다.
   - 실행 전 `npm install`로 의존성을 설치합니다.

6. **워크플로우에서 액션 사용 예제:**

   ```yaml
   name: CI with Custom Action

   on:
     push:
       branches: [ main ]

   jobs:
     build:
       runs-on: ubuntu-latest

       steps:
         - name: Checkout repository
           uses: actions/checkout@v3

         - name: Run My Custom Action
           id: custom_action
           uses: ./.github/actions/my-custom-action
           with:
             example-input: 'hello github actions'

         - name: Display Action Output
           run: echo "Action Output: ${{ steps.custom_action.outputs.example-output }}"
   ```

---

### 3.2 Docker 기반 사용자 정의 액션 (간략 예제)

1. **프로젝트 구조 구성:**

   ```plaintext
   .github/
     └── actions/
         └── docker-action/
             ├── Dockerfile
             ├── entrypoint.sh
             └── action.yml
   ```

2. **Dockerfile 작성:**

   ```dockerfile
   # .github/actions/docker-action/Dockerfile
   FROM alpine:3.14

   # 필요한 패키지 설치 (예: bash)
   RUN apk add --no-cache bash

   # 액션 실행 스크립트 복사
   COPY entrypoint.sh /entrypoint.sh
   RUN chmod +x /entrypoint.sh

   ENTRYPOINT ["/entrypoint.sh"]
   ```

3. **액션 실행 스크립트 작성 (`entrypoint.sh`):**

   ```bash
   #!/bin/bash
   set -e

   # 입력값 가져오기 (환경 변수 형태로 전달됨)
   INPUT_MESSAGE=${INPUT_MESSAGE:-"Hello from Docker Action"}
   echo "입력 메시지: $INPUT_MESSAGE"

   # 간단한 처리 예시 (대문자 변환)
   RESULT=$(echo "$INPUT_MESSAGE" | tr '[:lower:]' '[:upper:]')
   echo "결과 메시지: $RESULT"

   # GitHub Actions 출력값 설정
   echo "::set-output name=result::$RESULT"
   ```

4. **액션 메타데이터 작성 (`action.yml`):**

   ```yaml
   # .github/actions/docker-action/action.yml
   name: 'Docker Custom Action'
   description: 'Docker 컨테이너를 기반으로 실행되는 사용자 정의 액션'
   inputs:
     message:
       description: '처리할 메시지'
       required: false
       default: 'Hello from Docker Action'
   outputs:
     result:
       description: '대문자로 변환된 메시지'
   runs:
     using: 'docker'
     image: 'Dockerfile'
     args:
       - ${{ inputs.message }}
   ```

5. **워크플로우에서 Docker 액션 사용 예제:**

   ```yaml
   name: CI with Docker Action

   on:
     push:
       branches: [ main ]

   jobs:
     build:
       runs-on: ubuntu-latest

       steps:
         - name: Checkout repository
           uses: actions/checkout@v3

         - name: Run Docker Custom Action
           id: docker_action
           uses: ./.github/actions/docker-action
           with:
             message: 'hello docker'

         - name: Display Docker Action Output
           run: echo "Docker Action Output: ${{ steps.docker_action.outputs.result }}"
   ```

---

### 3.3 Composite Actions 사용 예

1. **프로젝트 구조 구성:**

   ```plaintext
   .github/
     └── actions/
         └── composite-action/
             └── action.yml
   ```

2. **Composite 액션 작성 (`action.yml`):**

   ```yaml
   # .github/actions/composite-action/action.yml
   name: 'Composite Action'
   description: '여러 액션을 묶어 하나의 단위로 실행하는 Composite Action'
   inputs:
     name:
       description: '인사할 대상'
       required: true
       default: 'World'
   outputs:
     greeting:
       description: '인사 메시지'
   runs:
     using: 'composite'
     steps:
       - name: Generate Greeting
         id: greet
         run: echo "Hello, ${{ inputs.name }}!" > greeting.txt

       - name: Set output
         run: echo "::set-output name=greeting::$(cat greeting.txt)"
   ```

3. **워크플로우에서 Composite 액션 사용 예제:**

   ```yaml
   name: CI with Composite Action

   on:
     push:
       branches: [ main ]

   jobs:
     build:
       runs-on: ubuntu-latest

       steps:
         - name: Checkout repository
           uses: actions/checkout@v3

         - name: Run Composite Action
           id: composite
           uses: ./.github/actions/composite-action
           with:
             name: 'GitHub'

         - name: Display Greeting
           run: echo "Greeting: ${{ steps.composite.outputs.greeting }}"
   ```

---

## 4. 추가 고려 사항

- **문서화:**  
  - 각 사용자 정의 액션의 `action.yml` 파일에 입력, 출력, 실행 환경 등을 명확하게 문서화하여 팀 내 공유 및 유지보수를 용이하게 함  
  - README 파일이나 Wiki를 활용하여 사용 예제와 사용법을 함께 제공

- **버전 관리:**  
  - 사용자 정의 액션도 버전 태깅을 통해 변경 사항을 관리하고, 워크플로우에서는 특정 버전을 참조하여 예기치 않은 업데이트 문제를 방지

- **테스트 및 디버깅:**  
  - 로컬 테스트 도구(예: [act](https://github.com/nektos/act))를 활용하여, 실제 GitHub Actions 환경에 배포하기 전에 충분히 테스트  
  - 로그 출력을 통해 실행 과정 및 오류를 신속하게 파악하고 수정

- **보안:**  
  - Docker 기반 액션의 경우, 컨테이너 이미지 내 불필요한 패키지 제거 및 최소 권한 원칙을 준수  
  - 비밀 값(Secrets) 처리 시 GitHub Secrets 기능을 활용하여 민감 정보를 안전하게 관리

---

## 5. 마무리

사용자 정의 액션 개발은 **GitHub Actions**의 강력한 확장 기능으로,  
- **프로젝트 특화 기능**을 직접 구현할 수 있으며,  
- **재사용성**과 **유연성**을 극대화하여 CI/CD 파이프라인의 품질을 높일 수 있습니다.

JavaScript 기반, Docker 기반, 또는 Composite 방식 등 다양한 방법을 상황에 맞게 선택하여 개발할 수 있으며,  
철저한 **문서화**와 **버전 관리**, **테스트 전략**을 통해 안정적인 액션을 구축하는 것이 중요합니다.