# 기본적인 파이프라인 구성 및 실행

> **목표:**  
> - GitLab CI/CD 파이프라인의 기본 구성 방법을 이해한다.
> - .gitlab-ci.yml 파일을 작성하고 실행하는 방법을 배운다.
> - 파이프라인의 실행 결과를 확인하고 문제를 해결하는 방법을 익힌다.

---

## 1. 파이프라인 기본 구조

### 1.1 기본 구성요소
```yaml
# .gitlab-ci.yml의 기본 구조
stages:          # 실행 단계 정의
  - build
  - test
  - deploy

variables:       # 전역 변수 설정
  APP_VERSION: "1.0.0"

before_script:   # 모든 작업 전에 실행
  - echo "작업 시작"

after_script:    # 모든 작업 후에 실행
  - echo "작업 완료"

build-job:       # 실제 작업(Job) 정의
  stage: build
  script:
    - echo "빌드 중..."
```

### 1.2 주요 속성 설명
- **stages:** 파이프라인의 실행 단계를 순서대로 정의
- **variables:** 파이프라인에서 사용할 전역 변수 설정
- **before_script:** 각 작업 실행 전에 수행할 명령어
- **after_script:** 각 작업 실행 후에 수행할 명령어

---

## 2. 실제 파이프라인 예제

### 2.1 Node.js 프로젝트 예제
```yaml
image: node:16

stages:
  - install
  - build
  - test
  - deploy

variables:
  NPM_TOKEN: ${NPM_AUTH_TOKEN}  # CI/CD 변수에서 설정

cache:
  paths:
    - node_modules/

install-deps:
  stage: install
  script:
    - npm ci
  artifacts:
    paths:
      - node_modules/

build-app:
  stage: build
  script:
    - npm run build
  artifacts:
    paths:
      - dist/

test-app:
  stage: test
  script:
    - npm run test
  coverage: '/코드 커버리지: \d+\.\d+/'

deploy-staging:
  stage: deploy
  script:
    - echo "스테이징 환경에 배포"
  environment:
    name: staging
  only:
    - develop
```

### 2.2 Spring Boot 프로젝트 예제
```yaml
image: openjdk:17-jdk

stages:
  - build
  - test
  - deploy

variables:
  GRADLE_OPTS: "-Dorg.gradle.daemon=false"

before_script:
  - chmod +x gradlew

build:
  stage: build
  script:
    - ./gradlew clean build -x test
  artifacts:
    paths:
      - build/libs/*.jar

test:
  stage: test
  script:
    - ./gradlew test
  artifacts:
    reports:
      junit: build/test-results/test/**/TEST-*.xml

deploy:
  stage: deploy
  script:
    - echo "배포 진행"
  only:
    - main
```

---

## 3. 주요 기능 설명

### 3.1 캐시(Cache)와 아티팩트(Artifacts)
```yaml
cache:
  key: ${CI_COMMIT_REF_SLUG}
  paths:
    - node_modules/    # 캐시할 디렉토리

artifacts:
  paths:
    - dist/           # 다음 작업에서 사용할 파일
  expire_in: 1 week   # 보관 기간
```

### 3.2 조건부 실행
```yaml
deploy-prod:
  stage: deploy
  script:
    - echo "운영 환경 배포"
  only:
    - main           # main 브랜치에서만 실행
  when: manual       # 수동 승인 후 실행
```

### 3.3 환경 변수 활용
```yaml
variables:
  # 전역 변수 설정
  DATABASE_URL: "postgresql://localhost:5432/mydb"
  
test-job:
  variables:
    # Job 레벨 변수 설정
    TEST_ENV: "staging"
  script:
    - echo $DATABASE_URL
    - echo $TEST_ENV
```

---

## 4. 파이프라인 실행 및 모니터링

### 4.1 파이프라인 실행 방법
1. 코드를 GitLab 저장소에 푸시
2. GitLab UI에서 파이프라인 상태 확인
3. 필요한 경우 수동 실행 또는 재실행

### 4.2 실행 결과 확인
- GitLab UI의 CI/CD → Pipelines 메뉴에서 확인
- 각 Job의 로그 확인
- 실패한 Job의 원인 분석

### 4.3 문제 해결 방법
1. Job 로그 상세 확인
2. 환경 변수 설정 검증
3. Runner 상태 확인
4. YAML 문법 오류 검사

---

## 5. 실무 활용 팁

### 5.1 파이프라인 최적화
```yaml
build:
  stage: build
  script:
    - npm ci
    - npm run build
  # 캐시 활용으로 빌드 시간 단축
  cache:
    key:
      files:
        - package-lock.json
    paths:
      - node_modules/
```

### 5.2 병렬 실행
```yaml
test:
  parallel: 3  # 3개의 병렬 작업으로 분할
  script:
    - npm test
```

### 5.3 환경별 배포 구성
```yaml
deploy-staging:
  stage: deploy
  script:
    - deploy-script.sh staging
  environment:
    name: staging
  only:
    - develop

deploy-production:
  stage: deploy
  script:
    - deploy-script.sh production
  environment:
    name: production
  when: manual
  only:
    - main
```

---

## 6. 파이프라인 디버깅

### 6.1 로컬 테스트
```bash
# GitLab Runner 로컬 실행
gitlab-runner exec docker job-name
```

### 6.2 디버깅 팁
1. 각 단계별 로그 출력 추가
2. 변수값 확인
3. 실행 환경 정보 출력

```yaml
debug-job:
  script:
    - echo "현재 브랜치: $CI_COMMIT_BRANCH"
    - echo "Git 해시: $CI_COMMIT_SHA"
    - env | sort  # 모든 환경변수 출력
```

---

## 참고 자료

- [GitLab CI/CD 파이프라인 설정](https://docs.gitlab.com/ee/ci/yaml/)
- [GitLab CI/CD 환경변수](https://docs.gitlab.com/ee/ci/variables/)
- [GitLab CI/CD 모범 사례](https://docs.gitlab.com/ee/ci/yaml/yaml_optimization.html)

---

## 마무리

이제 GitLab CI/CD 파이프라인의 기본 구성과 실행 방법을 이해했습니다. 실제 프로젝트에 적용하면서 점진적으로 파이프라인을 개선하고 최적화해 나갈 수 있습니다.