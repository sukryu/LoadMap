# GitLab CI/CD 개요 및 기본 개념

> **목표:**  
> - GitLab CI/CD의 핵심 개념과 작동 방식을 이해한다.
> - CI/CD 파이프라인의 기본 구성 요소와 실행 흐름을 파악한다.
> - .gitlab-ci.yml 파일의 구조와 작성 방법을 습득한다.
> - GitLab CI/CD를 실제 프로젝트에 적용할 수 있는 기초를 다진다.

---

## 1. GitLab CI/CD란?

### 정의
GitLab CI/CD는 소프트웨어 개발 과정에서 코드 통합(CI)과 배포(CD)를 자동화하는 도구입니다. 개발자가 코드를 저장소에 푸시하면 자동으로 빌드, 테스트, 배포 등의 작업을 수행할 수 있습니다.

### 왜 필요한가?
- **개발 효율성 향상:** 반복적인 작업을 자동화하여 개발자가 코드 작성에 집중할 수 있습니다.
- **품질 보장:** 자동화된 테스트로 버그를 조기에 발견할 수 있습니다.
- **배포 안정성:** 일관된 프로세스로 안정적인 배포가 가능합니다.
- **협업 강화:** 팀원들이 동일한 빌드/배포 환경을 공유할 수 있습니다.

---

## 2. 핵심 구성 요소

### 2.1 파이프라인(Pipeline)
- 코드를 빌드, 테스트, 배포하는 일련의 자동화된 프로세스입니다.
- 여러 개의 스테이지(Stage)로 구성되며, 각 스테이지는 순차적으로 실행됩니다.

```yaml
stages:
  - build    # 코드 빌드
  - test     # 테스트 실행
  - deploy   # 배포 수행
```

### 2.2 잡(Job)
- 파이프라인에서 실행되는 가장 기본적인 작업 단위입니다.
- 특정 스테이지에 속하며, 실제 명령어를 실행합니다.

```yaml
build-job:    # Job 이름
  stage: build  # 속한 스테이지
  script:      # 실행할 명령어
    - npm install
    - npm run build
```

### 2.3 러너(Runner)
- 파이프라인의 Job을 실제로 실행하는 에이전트입니다.
- Docker, Shell, SSH 등 다양한 실행 환경을 지원합니다.

---

## 3. .gitlab-ci.yml 파일

### 3.1 기본 구조
```yaml
# 스테이지 정의
stages:
  - build
  - test
  - deploy

# 변수 설정
variables:
  NODE_VERSION: "16"

# Job 정의
build-app:
  stage: build
  script:
    - echo "애플리케이션 빌드 중..."
    - npm install
    - npm run build
  artifacts:
    paths:
      - dist/

test-app:
  stage: test
  script:
    - echo "테스트 실행 중..."
    - npm run test

deploy-app:
  stage: deploy
  script:
    - echo "배포 진행 중..."
```

### 3.2 주요 키워드 설명
- **stages:** 파이프라인의 실행 단계를 정의
- **variables:** 파이프라인에서 사용할 전역 변수 설정
- **script:** Job에서 실행할 실제 명령어
- **artifacts:** Job 실행 후 저장할 결과물 지정

---

## 4. 실제 동작 예시

### 4.1 기본적인 워크플로우
1. 개발자가 코드를 GitLab 저장소에 푸시
2. GitLab이 .gitlab-ci.yml 파일 감지
3. 파이프라인 생성 및 Job 실행
4. 결과 확인 및 다음 단계 진행

### 4.2 간단한 파이프라인 예제
```yaml
# Node.js 프로젝트 예시
image: node:16

stages:
  - build
  - test
  - deploy

cache:
  paths:
    - node_modules/

install-dependencies:
  stage: build
  script:
    - npm install
  artifacts:
    paths:
      - node_modules/

run-tests:
  stage: test
  script:
    - npm run test

deploy-production:
  stage: deploy
  script:
    - echo "배포 시작..."
    - npm run deploy
  only:
    - main
```

---

## 5. 장단점

### 장점
- **자동화:** 반복적인 작업을 자동으로 처리
- **일관성:** 모든 개발자가 동일한 프로세스 사용
- **신뢰성:** 자동화된 테스트로 품질 보장
- **가시성:** 파이프라인 상태를 실시간으로 확인 가능

### 단점
- **초기 설정:** 파이프라인 구성에 시간과 노력 필요
- **러닝 커브:** YAML 문법과 CI/CD 개념 학습 필요
- **리소스:** 러너 실행에 필요한 컴퓨팅 자원 필요

---

## 6. 시작하기

### 6.1 기본 단계
1. GitLab 프로젝트 생성
2. .gitlab-ci.yml 파일 작성
3. 러너 설정 확인
4. 코드 푸시 및 파이프라인 실행 테스트

### 6.2 주의사항
- YAML 문법 정확히 사용
- 보안 관련 설정(시크릿, 토큰) 주의
- 리소스 사용량 모니터링

---

## 참고 자료

- [GitLab CI/CD 공식 문서](https://docs.gitlab.com/ee/ci/)
- [GitLab CI/CD 파이프라인 구성](https://docs.gitlab.com/ee/ci/yaml/)
- [GitLab Runner 설치 가이드](https://docs.gitlab.com/runner/)

---

## 마무리

GitLab CI/CD는 현대 소프트웨어 개발에서 필수적인 도구입니다. 기본 개념을 이해하고 실제 프로젝트에 적용하면서, 점진적으로 더 복잡한 파이프라인을 구성하고 최적화해 나갈 수 있습니다.