# 병렬 실행 및 매트릭스 빌드

> **목표:**  
> - GitLab CI/CD의 병렬 실행과 매트릭스 빌드 개념을 이해한다.
> - 파이프라인 성능을 최적화하는 방법을 학습한다.
> - 실제 프로젝트에서 병렬 처리를 구현하는 방법을 익힌다.

---

## 1. 병렬 실행 기본 개념

### 1.1 병렬 실행이란?
- 여러 Job을 동시에 실행하여 파이프라인 실행 시간 단축
- 동일한 Job을 여러 인스턴스로 분할하여 처리
- 서로 다른 환경에서 테스트 동시 실행

### 1.2 기본 병렬 실행
```yaml
test:
  stage: test
  parallel: 3    # 3개의 병렬 Job 생성
  script:
    - npm test
```

---

## 2. 매트릭스 빌드

### 2.1 매트릭스 구성
```yaml
test:
  stage: test
  parallel:
    matrix:
      - NODE_VERSION: ["14", "16", "18"]
        ENV: ["development", "staging", "production"]
  script:
    - node --version
    - npm run test:$ENV
  image: node:${NODE_VERSION}
```

### 2.2 복합 매트릭스
```yaml
build:
  stage: build
  parallel:
    matrix:
      - PLATFORM: ["linux", "windows", "macos"]
        ARCH: ["amd64", "arm64"]
        exclude:
          - PLATFORM: "windows"
            ARCH: "arm64"
  script:
    - build-script.sh ${PLATFORM} ${ARCH}
```

---

## 3. 병렬 테스트 최적화

### 3.1 테스트 분할
```yaml
test:
  stage: test
  parallel: 4
  script:
    - echo "노드 인덱스: $CI_NODE_INDEX"
    - echo "전체 노드 수: $CI_NODE_TOTAL"
    - |
      case $CI_NODE_INDEX in
        1) npm run test:unit ;;
        2) npm run test:integration ;;
        3) npm run test:e2e:part1 ;;
        4) npm run test:e2e:part2 ;;
      esac
```

### 3.2 동적 테스트 분할
```yaml
test:
  stage: test
  parallel: 3
  script:
    # 테스트 파일 목록 생성
    - TEST_FILES=$(find tests -name '*_test.js')
    # 노드별로 테스트 파일 분배
    - node_tests=$(echo "$TEST_FILES" | awk "NR % $CI_NODE_TOTAL == $CI_NODE_INDEX")
    # 할당된 테스트 실행
    - for test in $node_tests; do npm test $test; done
```

---

## 4. 실제 활용 예제

### 4.1 다중 플랫폼 빌드
```yaml
build:
  stage: build
  parallel:
    matrix:
      - OS: ["ubuntu-latest", "windows-latest", "macos-latest"]
        ARCH: ["x64", "arm64"]
  script:
    - echo "OS: $OS, ARCH: $ARCH"
    - ./build.sh -o $OS -a $ARCH
  artifacts:
    paths:
      - dist/$OS/$ARCH/
```

### 4.2 크로스 브라우저 테스트
```yaml
test-browsers:
  stage: test
  parallel:
    matrix:
      - BROWSER: ["chrome", "firefox", "safari"]
        RESOLUTION: ["1920x1080", "1366x768"]
  script:
    - npm run test:e2e
  variables:
    BROWSER_TYPE: $BROWSER
    SCREEN_SIZE: $RESOLUTION
```

---

## 5. 성능 최적화 전략

### 5.1 캐시 활용
```yaml
test:
  stage: test
  parallel: 3
  cache:
    key: "$CI_JOB_NAME-$CI_COMMIT_REF_SLUG"
    paths:
      - node_modules/
  script:
    - npm ci
    - npm test
```

### 5.2 리소스 할당
```yaml
test:
  parallel: 2
  variables:
    FF_USE_FASTZIP: "true"
  script:
    - npm test
  resource_group: test_resources
```

---

## 6. 복잡한 매트릭스 구성

### 6.1 조건부 실행
```yaml
test:
  stage: test
  parallel:
    matrix:
      - VERSION: ["5.0", "6.0", "7.0"]
        DATABASE: ["mysql", "postgres"]
        exclude:
          - VERSION: "5.0"
            DATABASE: "postgres"
  rules:
    - if: $CI_COMMIT_TAG
      when: never
    - when: always
  script:
    - run-tests.sh $VERSION $DATABASE
```

### 6.2 환경별 매트릭스
```yaml
deploy:
  stage: deploy
  parallel:
    matrix:
      - ENVIRONMENT: ["dev", "staging", "prod"]
        REGION: ["us-east-1", "eu-west-1", "ap-northeast-1"]
        exclude:
          - ENVIRONMENT: "prod"
            REGION: "us-east-1"
  script:
    - deploy.sh $ENVIRONMENT $REGION
  rules:
    - if: $CI_COMMIT_BRANCH == "main"
      when: manual
```

---

## 7. 모니터링 및 디버깅

### 7.1 병렬 작업 모니터링
```yaml
test:
  parallel: 3
  script:
    - echo "시작 시간: $(date)"
    - npm test
    - echo "종료 시간: $(date)"
  after_script:
    - echo "노드 $CI_NODE_INDEX 완료"
```

### 7.2 실패 처리
```yaml
test:
  parallel: 3
  script:
    - |
      if ! npm test; then
        echo "테스트 실패: 노드 $CI_NODE_INDEX"
        exit 1
      fi
  after_script:
    - |
      if [ $CI_JOB_STATUS == "failed" ]; then
        collect-debug-info.sh
      fi
```

---

## 참고 자료

- [GitLab CI 병렬화 문서](https://docs.gitlab.com/ee/ci/yaml/#parallel)
- [GitLab CI 매트릭스 구성](https://docs.gitlab.com/ee/ci/yaml/#parallel-matrix)
- [GitLab CI 리소스 그룹](https://docs.gitlab.com/ee/ci/resource_groups/)

---

## 마무리

병렬 실행과 매트릭스 빌드를 활용하면 CI/CD 파이프라인의 실행 시간을 크게 단축할 수 있습니다. 프로젝트의 규모와 특성에 맞게 적절한 병렬화 전략을 선택하여 적용하세요.