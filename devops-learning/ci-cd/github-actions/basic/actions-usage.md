## 1. 문제/질문 분석

- **핵심 포인트:**  
  - GitHub Actions에서 **액션(Action)** 이란 무엇이며, 어떻게 사용하는지 이해  
  - **공식 액션**과 **커스텀 액션**의 사용법 차이 및 선택 기준 파악  
  - 실무에서 자주 사용하는 액션 예제를 통해, 자동화 파이프라인 내에서 액션을 활용하는 방법 습득

- **기술적 컨텍스트:**  
  - **액션(Action):** GitHub Actions에서 하나의 스텝으로 동작하는 재사용 가능한 단위로, 코드 체크아웃, 환경 설정, 배포 등 다양한 작업을 수행  
  - **공식 액션:** GitHub에서 제공하거나, 커뮤니티에서 검증된 액션들을 사용하여 안정적인 파이프라인 구성  
  - **커스텀 액션:** 프로젝트의 특성이나 고유 기능에 맞게 직접 작성한 액션으로, 재사용성과 확장성을 높일 수 있음

---

## 2. 해결 방안 제시

### 방안 1: 공식 액션 활용
- **장점:**  
  - 유지보수와 업데이트가 잘 관리된 안정적인 액션 사용 가능  
  - 간단한 설정으로 다양한 기능을 바로 적용할 수 있음
- **단점:**  
  - 기능이나 동작 방식이 제한적일 수 있음  
  - 프로젝트에 맞지 않는 경우 커스터마이징이 필요함

### 방안 2: 커스텀 액션 개발
- **장점:**  
  - 프로젝트에 특화된 요구사항을 정확히 반영 가능  
  - 액션 내부의 로직을 직접 제어할 수 있어 유연함
- **단점:**  
  - 초기 개발 및 유지보수에 추가적인 시간이 필요함  
  - 다른 팀원과의 협업 시, 코드 리뷰 및 문서화가 필수

### 방안 3: 외부 액션과 커스텀 스크립트 혼합
- **장점:**  
  - 기존에 검증된 외부 액션을 기본으로 사용하면서, 필요한 부분은 커스텀 스크립트로 보완  
  - 확장성과 유지보수성 측면에서 균형 잡힌 접근
- **단점:**  
  - 구성 요소가 여러 종류로 분산되어 있어, 전체적인 흐름 파악이 어려울 수 있음

---

## 3. 구체적 구현 방법

### 3.1 공식 액션 사용 예제

**예제 1: 코드 체크아웃 및 Node.js 환경 설정**  
GitHub에서 제공하는 공식 액션을 활용하여 기본적인 CI 파이프라인 스텝을 구성합니다.

```yaml
name: CI with Official Actions

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
      # 코드 체크아웃: 저장소의 최신 코드를 가져옴
      - name: Checkout repository
        uses: actions/checkout@v3

      # Node.js 환경 설정: 필요한 Node 버전을 설정
      - name: Setup Node.js
        uses: actions/setup-node@v3
        with:
          node-version: '16'

      # 의존성 설치
      - name: Install dependencies
        run: npm install

      # 테스트 실행
      - name: Run tests
        run: npm test
```

**핵심 포인트:**  
- `uses` 키워드를 활용하여 공식 액션(`actions/checkout`, `actions/setup-node`)을 간단하게 적용  
- 버전 고정을 통해 예기치 않은 업데이트로 인한 문제를 예방

---

### 3.2 커스텀 액션 개발 및 사용 예제

**예제 2: 커스텀 액션 작성 (JavaScript 기반)**

1. **액션 코드 작성:**  
   - 액션 디렉토리(`.github/actions/my-custom-action`)를 생성하고, 아래와 같이 JavaScript 액션 코드를 작성합니다.

   ```javascript
   // .github/actions/my-custom-action/index.js
   const core = require('@actions/core');

   try {
     // 인풋 값 읽기
     const name = core.getInput('who-to-greet');
     console.log(`Hello ${name}!`);
     
     // 결과 출력
     core.setOutput("time", new Date().toTimeString());
   } catch (error) {
     core.setFailed(error.message);
   }
   ```

2. **액션 메타데이터 작성:**  
   - `action.yml` 파일을 생성하여 액션의 입력 값과 동작 정보를 정의합니다.

   ```yaml
   # .github/actions/my-custom-action/action.yml
   name: 'My Custom Action'
   description: 'Greets a person and returns the current time.'
   inputs:
     who-to-greet:
       description: 'The name of the person to greet'
       required: true
       default: 'World'
   outputs:
     time:
       description: 'The current time'
   runs:
     using: 'node12'
     main: 'index.js'
   ```

3. **워크플로우에서 커스텀 액션 사용:**  
   - 아래 예제처럼 워크플로우 내에서 커스텀 액션을 호출할 수 있습니다.

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

         # 커스텀 액션 실행
         - name: Greet and Get Time
           uses: ./.github/actions/my-custom-action
           with:
             who-to-greet: 'GitHub Actions'

         # 커스텀 액션의 출력값 활용
         - name: Display Current Time
           run: echo "The current time is ${{ steps.greet.outputs.time }}"
           # 주의: steps 이름은 앞 스텝에서 name을 지정하거나 id를 지정하여 참조
   ```

**핵심 포인트:**  
- **커스텀 액션 개발:** 프로젝트 내부에 필요한 기능을 직접 구현할 수 있으며, Node.js, Docker 등 다양한 환경으로 작성 가능  
- **메타데이터 파일(`action.yml`) 작성:** 액션의 인터페이스를 정의하여, 사용법을 명확하게 문서화  
- **로컬 액션 사용:** 리포지토리 내 경로를 사용하여 손쉽게 액션 호출 가능

---

### 3.3 외부 액션과 커스텀 스크립트 혼합 사용 예제

**예제 3: 린트 및 테스트 실행 워크플로우**

```yaml
name: Lint & Test

on: [push, pull_request]

jobs:
  lint-and-test:
    runs-on: ubuntu-latest
    steps:
      # 저장소 체크아웃
      - name: Checkout code
        uses: actions/checkout@v3

      # Node.js 환경 설정
      - name: Setup Node.js
        uses: actions/setup-node@v3
        with:
          node-version: '16'

      # 린트 실행: 외부 액션 대신 커스텀 스크립트를 활용
      - name: Run Lint
        run: npm run lint

      # 테스트 실행: 공식 액션이 아닌 단순 스크립트로 처리
      - name: Run tests
        run: npm test
```

**핵심 포인트:**  
- 프로젝트 내 린트 스크립트(`npm run lint`)와 테스트 스크립트를 커스텀 스크립트로 작성하여, 외부 액션과 혼합 활용  
- 공식 액션(`actions/checkout`, `actions/setup-node`)을 사용하여 기본 환경 구성은 안정적으로 진행

---

## 4. 추가 고려 사항

- **버전 관리:**  
  - 공식 액션 사용 시 버전을 명시(`@v3`, `@v2` 등)하여 예기치 않은 업데이트로 인한 문제를 방지  
- **비밀 값 관리:**  
  - API 키나 민감한 정보는 GitHub Secrets를 통해 전달하고, 액션 내에서는 직접 노출하지 않도록 주의
- **테스트 및 디버깅:**  
  - 커스텀 액션은 로컬에서 충분히 테스트한 후 워크플로우에 통합하고, 실행 로그를 통해 문제를 신속하게 파악  
- **문서화:**  
  - 커스텀 액션은 사용 방법, 입력 및 출력 값에 대한 문서화를 철저히 하여, 팀원과의 협업 및 유지보수를 용이하게 함

---

## 5. 마무리

GitHub Actions의 **액션 사용법 및 예제**는 다음과 같은 포인트를 포함합니다:

- **공식 액션 활용:** 안정적이고 검증된 액션을 통해 기본적인 CI/CD 작업(코드 체크아웃, 환경 설정, 테스트 실행 등)을 빠르게 구현
- **커스텀 액션 개발:** 프로젝트에 특화된 기능을 직접 구현하여 재사용성과 확장성을 높임
- **혼합 사용:** 공식 액션과 커스텀 스크립트를 조합하여, 필요한 작업을 유연하게 처리

이를 통해 **자동화 파이프라인**의 구성 요소를 효과적으로 설계하고, 지속적인 통합 및 배포 환경을 구축할 수 있습니다.  