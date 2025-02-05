# Job 및 Stage 개념 이해

> **목표:**  
> - GitLab CI/CD의 Job과 Stage 개념을 이해한다.
> - Job과 Stage를 효과적으로 구성하는 방법을 학습한다.
> - 실제 프로젝트에서 Job과 Stage를 활용하는 방법을 익힌다.

---

## 1. Job 개념

### 1.1 Job이란?
- CI/CD 파이프라인의 가장 기본적인 실행 단위
- 특정 작업(빌드, 테스트, 배포 등)을 수행하는 독립적인 단위
- .gitlab-ci.yml 파일에서 정의

### 1.2 Job 구성 요소
```yaml
build-job:            # Job 이름
  stage: build        # 소속 Stage
  image: node:16      # 실행 환경
  variables:          # Job 레벨 변수
    NODE_ENV: "development"
  before_script:      # 사전 실행 스크립트
    - npm install
  script:            # 주요 실행 스크립트
    - npm run build
  after_script:      # 사후 실행 스크립트
    - echo "빌드 완료"
  artifacts:         # 결과물 저장
    paths:
      - dist/
  cache:            # 캐시 설정
    paths:
      - node_modules/
  only:             # 실행 조건
    - main
```

---

## 2. Stage 개념

### 2.1 Stage란?
- 여러 Job을 논리적으로 그룹화하는 단위
- 파이프라인의 실행 단계를 정의
- 순차적으로 실행되며, 이전 Stage가 성공해야 다음 Stage 실행

### 2.2 Stage 구성
```yaml
stages:              # Stage 정의
  - prepare
  - build
  - test
  - deploy

prepare-deps:        # prepare Stage의 Job
  stage: prepare
  script:
    - npm install

build-app:          # build Stage의 Job
  stage: build
  script:
    - npm run build

test-unit:          # test Stage의 Job
  stage: test
  script:
    - npm run test:unit

test-integration:   # 같은 Stage의 다른 Job
  stage: test
  script:
    - npm run test:integration

deploy-staging:     # deploy Stage의 Job
  stage: deploy
  script:
    - deploy-to-staging.sh
```

---

## 3. Job과 Stage의 실행 규칙

### 3.1 기본 실행 규칙
1. 같은 Stage의 Job들은 병렬로 실행
2. 다음 Stage는 이전 Stage의 모든 Job이 성공해야 실행
3. Stage가 실패하면 이후 Stage는 실행되지 않음

### 3.2 실행 제어
```yaml
test-job:
  stage: test
  script:
    - npm test
  rules:            # 실행 조건 설정
    - if: $CI_PIPELINE_SOURCE == "merge_request_event"
      when: always  # 항상 실행
    - if: $CI_COMMIT_BRANCH == "main"
      when: manual  # 수동 실행
    - when: never   # 실행하지 않음
```

---

## 4. 실제 활용 예제

### 4.1 프론트엔드 프로젝트
```yaml
stages:
  - setup
  - build
  - test
  - deploy

install:
  stage: setup
  script:
    - npm ci
  cache:
    key: 
      files:
        - package-lock.json
    paths:
      - node_modules/

lint:
  stage: build
  script:
    - npm run lint
  dependencies:
    - install

build:
  stage: build
  script:
    - npm run build
  artifacts:
    paths:
      - dist/
  dependencies:
    - install

test-unit:
  stage: test
  script:
    - npm run test:unit
  dependencies:
    - install

test-e2e:
  stage: test
  script:
    - npm run test:e2e
  dependencies:
    - build

deploy-staging:
  stage: deploy
  script:
    - deploy-staging.sh
  environment:
    name: staging
  only:
    - develop
```

### 4.2 백엔드 프로젝트
```yaml
stages:
  - build
  - test
  - quality
  - deploy

build:
  stage: build
  script:
    - ./gradlew clean build -x test
  artifacts:
    paths:
      - build/libs/*.jar

test:
  stage: test
  parallel: 3
  script:
    - ./gradlew test
  artifacts:
    reports:
      junit: build/test-results/test/**/TEST-*.xml

code-quality:
  stage: quality
  script:
    - ./gradlew sonarqube
  allow_failure: true

security-scan:
  stage: quality
  script:
    - run-security-scan.sh
  allow_failure: true

deploy-staging:
  stage: deploy
  script:
    - deploy-to-staging.sh
  environment:
    name: staging
  when: manual
```

---

## 5. 고급 기능

### 5.1 Job 상속
```yaml
.build-template:  # 템플릿 Job
  stage: build
  before_script:
    - npm ci
  cache:
    paths:
      - node_modules/

build-web:       # 템플릿 상속
  extends: .build-template
  script:
    - npm run build:web

build-admin:     # 템플릿 상속
  extends: .build-template
  script:
    - npm run build:admin
```

### 5.2 병렬 처리
```yaml
test:
  stage: test
  parallel: 3    # 3개의 병렬 Job 생성
  script:
    - npm test
```

### 5.3 매트릭스 Job
```yaml
test:
  stage: test
  parallel:
    matrix:
      - NODE_VERSION: ["14", "16", "18"]
        ENV: ["development", "production"]
  script:
    - npm run test:$ENV
  image: node:${NODE_VERSION}
```

---

## 6. 모범 사례

### 6.1 Job 구성 원칙
- 각 Job은 단일 책임을 가지도록 구성
- 관련 있는 Job들은 같은 Stage에 그룹화
- 적절한 의존성(dependencies) 설정

### 6.2 Stage 구성 원칙
- 논리적인 실행 순서에 따라 Stage 구성
- 중요도와 실행 시간을 고려한 Stage 순서 설정
- 필요한 경우 Stage 건너뛰기 옵션 활용

---

## 참고 자료

- [GitLab CI/CD 작업(Jobs) 설정](https://docs.gitlab.com/ee/ci/jobs/)
- [GitLab CI/CD 스테이지(Stages) 구성](https://docs.gitlab.com/ee/ci/yaml/#stages)
- [GitLab CI/CD 병렬 실행](https://docs.gitlab.com/ee/ci/yaml/#parallel)

---

## 마무리

Job과 Stage는 GitLab CI/CD 파이프라인의 핵심 구성 요소입니다. 이들을 효과적으로 구성하고 활용함으로써 효율적이고 안정적인 CI/CD 파이프라인을 구축할 수 있습니다.