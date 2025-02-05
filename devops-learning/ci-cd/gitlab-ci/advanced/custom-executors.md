# 사용자 정의 실행기 (Custom Executors)

> **목표:**  
> - GitLab Runner의 사용자 정의 실행기 개념을 이해한다.
> - 다양한 실행 환경에 맞는 실행기를 구성하는 방법을 학습한다.
> - 실제 프로젝트에 적용할 수 있는 실행기 설정 방법을 익힌다.

---

## 1. 사용자 정의 실행기 개요

### 1.1 실행기(Runner)란?
- GitLab CI/CD 파이프라인의 Job을 실행하는 에이전트
- 다양한 실행 환경(Docker, Shell, SSH 등)을 지원
- 프로젝트나 그룹 단위로 설정 가능

### 1.2 실행기 유형
```plaintext
1. Docker 실행기
   - 격리된 컨테이너 환경에서 Job 실행
   - 환경 일관성 보장

2. Shell 실행기
   - 호스트 시스템에서 직접 명령어 실행
   - 시스템 리소스 직접 접근 가능

3. SSH 실행기
   - 원격 시스템에서 Job 실행
   - 별도 서버 환경 활용

4. Kubernetes 실행기
   - K8s 클러스터에서 Job 실행
   - 확장성과 관리 용이성 제공
```

---

## 2. Docker 실행기 구성

### 2.1 기본 설정
```toml
[[runners]]
  name = "docker-runner"
  url = "https://gitlab.com"
  token = "PROJECT_TOKEN"
  executor = "docker"
  [runners.docker]
    tls_verify = false
    image = "ubuntu:20.04"
    privileged = false
    disable_cache = false
    volumes = ["/cache"]
    shm_size = 0
```

### 2.2 고급 설정
```toml
[[runners]]
  [runners.docker]
    # 볼륨 마운트
    volumes = [
      "/var/run/docker.sock:/var/run/docker.sock",
      "/cache",
      "/builds:/builds:rw"
    ]
    # 네트워크 설정
    network_mode = "host"
    # DNS 설정
    dns = ["8.8.8.8"]
    # 환경 변수
    environment = ["DOCKER_AUTH_CONFIG"]
```

---

## 3. Shell 실행기 구성

### 3.1 기본 설정
```toml
[[runners]]
  name = "shell-runner"
  url = "https://gitlab.com"
  token = "PROJECT_TOKEN"
  executor = "shell"
  shell = "bash"
```

### 3.2 스크립트 예제
```yaml
build-job:
  script:
    - echo "Shell 실행기에서 실행"
    - ./build.sh
  tags:
    - shell
```

---

## 4. Kubernetes 실행기 구성

### 4.1 기본 설정
```toml
[[runners]]
  name = "kubernetes-runner"
  url = "https://gitlab.com"
  token = "PROJECT_TOKEN"
  executor = "kubernetes"
  [runners.kubernetes]
    host = "https://kubernetes.default.svc"
    namespace = "gitlab"
    service_account = "gitlab-runner"
```

### 4.2 Pod 설정
```yaml
[[runners]]
  [runners.kubernetes]
    [runners.kubernetes.pod_labels]
      "app" = "gitlab-runner"
    [[runners.kubernetes.volumes.empty_dir]]
      name = "empty-dir"
      mount_path = "/cache"
      medium = "Memory"
```

---

## 5. 실행기 최적화

### 5.1 캐시 설정
```toml
[[runners]]
  [runners.cache]
    Type = "s3"
    Path = "cache"
    Shared = false
    [runners.cache.s3]
      ServerAddress = "s3.amazonaws.com"
      AccessKey = "ACCESS_KEY"
      SecretKey = "SECRET_KEY"
      BucketName = "runner-cache"
      BucketLocation = "eu-west-1"
```

### 5.2 리소스 제한
```toml
[[runners]]
  [runners.docker]
    cpus = "2"
    memory = "2g"
    memory_swap = "2g"
    memory_reservation = "1g"
```

---

## 6. 실제 활용 예제

### 6.1 다중 실행기 구성
```yaml
# .gitlab-ci.yml
build-docker:
  script:
    - docker build -t myapp .
  tags:
    - docker

deploy-shell:
  script:
    - ./deploy.sh
  tags:
    - shell

test-kubernetes:
  script:
    - kubectl apply -f test/
  tags:
    - kubernetes
```

### 6.2 환경별 실행기
```yaml
stages:
  - build
  - test
  - deploy

build:
  script:
    - npm ci
    - npm run build
  tags:
    - node-docker

test:
  script:
    - npm run test
  tags:
    - node-docker

deploy-staging:
  script:
    - deploy-staging.sh
  tags:
    - shell-staging
  environment:
    name: staging

deploy-prod:
  script:
    - deploy-prod.sh
  tags:
    - shell-production
  environment:
    name: production
  when: manual
```

---

## 7. 문제 해결과 디버깅

### 7.1 로그 설정
```toml
[[runners]]
  log_level = "debug"
  log_format = "json"
  debug_trace = true
```

### 7.2 상태 확인
```bash
# Runner 상태 확인
gitlab-runner status

# 등록된 Runner 목록
gitlab-runner list

# Runner 검증
gitlab-runner verify
```

---

## 참고 자료

- [GitLab Runner 설치 가이드](https://docs.gitlab.com/runner/install/)
- [Runner 구성 참조](https://docs.gitlab.com/runner/configuration/advanced-configuration.html)
- [Kubernetes Runner 설정](https://docs.gitlab.com/runner/executors/kubernetes.html)

---

## 마무리

사용자 정의 실행기를 통해 프로젝트의 특성에 맞는 CI/CD 환경을 구성할 수 있습니다. 실행기 유형과 설정을 적절히 선택하여 효율적이고 안정적인 파이프라인을 구축하세요.