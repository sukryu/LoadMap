# 자체 호스팅 러너 사용법

> **목표:**  
> - GitLab 자체 호스팅 러너 설치 및 구성 방법 습득
> - 러너 관리와 모니터링 방법 이해
> - 실제 환경에서의 러너 운영 전략 학습

---

## 1. 러너 설치

### 1.1 Linux 환경 설치
```bash
# 저장소 추가
curl -L "https://packages.gitlab.com/install/repositories/runner/gitlab-runner/script.deb.sh" | sudo bash

# 러너 설치
sudo apt-get install gitlab-runner

# 서비스 상태 확인
sudo systemctl status gitlab-runner
```

### 1.2 Docker 환경 설치
```bash
# Docker 컨테이너로 실행
docker run -d --name gitlab-runner --restart always \
    -v /srv/gitlab-runner/config:/etc/gitlab-runner \
    -v /var/run/docker.sock:/var/run/docker.sock \
    gitlab/gitlab-runner:latest
```

---

## 2. 러너 등록

### 2.1 대화형 등록
```bash
sudo gitlab-runner register

# 입력 정보
# 1. GitLab URL
# 2. Runner token
# 3. Runner description
# 4. Runner tags
# 5. Executor type
```

### 2.2 비대화형 등록
```bash
sudo gitlab-runner register \
  --non-interactive \
  --url "https://gitlab.example.com/" \
  --registration-token "PROJECT_REGISTRATION_TOKEN" \
  --executor "docker" \
  --docker-image alpine:latest \
  --description "docker-runner" \
  --tag-list "docker,aws" \
  --run-untagged="true" \
  --locked="false"
```

---

## 3. 러너 구성

### 3.1 기본 설정 (/etc/gitlab-runner/config.toml)
```toml
concurrent = 4
check_interval = 0

[[runners]]
  name = "docker-runner"
  url = "https://gitlab.example.com"
  token = "PROJECT_TOKEN"
  executor = "docker"
  [runners.docker]
    tls_verify = false
    image = "docker:latest"
    privileged = false
    disable_cache = false
    volumes = ["/cache"]
    shm_size = 0
```

### 3.2 고급 설정
```toml
[[runners]]
  [runners.docker]
    # 시스템 설정
    cpus = "2"
    memory = "2g"
    memory_swap = "2g"
    
    # 네트워크 설정
    dns = ["8.8.8.8", "8.8.4.4"]
    network_mode = "host"
    
    # 볼륨 마운트
    volumes = [
      "/var/run/docker.sock:/var/run/docker.sock",
      "/cache",
      "/builds:/builds:rw"
    ]
```

---

## 4. 운영 관리

### 4.1 서비스 관리
```bash
# 서비스 시작
sudo systemctl start gitlab-runner

# 서비스 중지
sudo systemctl stop gitlab-runner

# 서비스 재시작
sudo systemctl restart gitlab-runner

# 부팅 시 자동 시작
sudo systemctl enable gitlab-runner
```

### 4.2 러너 상태 확인
```bash
# 러너 상태
sudo gitlab-runner status

# 등록된 러너 목록
sudo gitlab-runner list

# 러너 검증
sudo gitlab-runner verify
```

---

## 5. 성능 최적화

### 5.1 캐시 설정
```toml
[[runners]]
  [runners.cache]
    Type = "s3"
    Shared = false
    [runners.cache.s3]
      ServerAddress = "s3.amazonaws.com"
      AccessKey = "ACCESS_KEY"
      SecretKey = "SECRET_KEY"
      BucketName = "runner-cache"
      BucketLocation = "eu-west-1"
```

### 5.2 작업 병렬화
```toml
# 전역 동시성 설정
concurrent = 10

[[runners]]
  limit = 4  # 러너별 동시 작업 수 제한
```

---

## 6. 보안 설정

### 6.1 권한 관리
```toml
[[runners]]
  [runners.docker]
    privileged = false
    cap_add = ["NET_ADMIN"]
    cap_drop = ["ALL"]
```

### 6.2 네트워크 보안
```toml
[[runners]]
  [runners.docker]
    allowed_images = ["ruby:*", "python:*", "node:*"]
    allowed_services = ["postgres:*", "mysql:*", "redis:*"]
```

---

## 7. 모니터링

### 7.1 로그 관리
```bash
# 로그 확인
sudo journalctl -u gitlab-runner

# 실시간 로그 모니터링
sudo journalctl -u gitlab-runner -f

# 로그 레벨 설정
[[runners]]
  log_level = "debug"
```

### 7.2 지표 수집
```toml
[[runners]]
  [runners.prometheus]
    listen_address = ":9252"
```

---

## 8. 문제 해결

### 8.1 일반적인 문제
- 러너 연결 실패
- 권한 문제
- 리소스 부족
- 네트워크 문제

### 8.2 디버깅
```bash
# 디버그 모드 활성화
sudo gitlab-runner --debug run

# 구성 파일 검증
sudo gitlab-runner verify --config /etc/gitlab-runner/config.toml
```

---

## 참고 자료

- [GitLab Runner 공식 문서](https://docs.gitlab.com/runner/)
- [Runner 등록 가이드](https://docs.gitlab.com/runner/register/)
- [Runner 설정 레퍼런스](https://docs.gitlab.com/runner/configuration/advanced-configuration.html)

---

## 마무리

자체 호스팅 러너를 통해 CI/CD 환경을 완벽하게 제어할 수 있습니다. 조직의 요구사항과 보안 정책에 맞게 러너를 구성하고 운영하세요.