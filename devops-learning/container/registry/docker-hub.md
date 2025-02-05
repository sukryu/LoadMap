# Docker Hub 활용 가이드

> **목표:**  
> - Docker Hub의 기본 개념과 주요 기능을 이해한다.
> - 이미지의 저장, 공유, 관리 방법을 습득한다.
> - 자동화된 빌드와 배포 프로세스를 구성한다.
> - Docker Hub를 실무에서 효과적으로 활용하는 방법을 익힌다.

---

## 1. Docker Hub 개요

Docker Hub는 Docker의 공식 이미지 레지스트리로, 컨테이너 이미지를 저장하고 공유할 수 있는 클라우드 기반 서비스입니다. 개발자들은 Docker Hub를 통해 공식 이미지를 다운로드하거나 자신만의 이미지를 공유할 수 있으며, 자동화된 빌드 기능을 활용할 수 있습니다.

Docker Hub는 개인 개발자부터 대규모 팀까지 다양한 규모의 사용자를 지원하며, 무료 플랜과 유료 플랜을 제공합니다. 기본적인 이미지 호스팅과 공유 기능은 무료로 사용할 수 있으며, 프라이빗 저장소나 팀 협업 기능은 유료 플랜에서 제공됩니다.

---

## 2. Docker Hub 계정 설정 및 관리

### 2.1 계정 생성 및 설정

Docker Hub 계정을 생성하고 설정하는 과정은 다음과 같습니다:

1. Docker Hub 웹사이트(https://hub.docker.com)에서 계정 생성
2. 이메일 인증 완료
3. 보안 설정 구성 (2단계 인증 등)
4. 프로필 정보 설정

### 2.2 액세스 토큰 관리

보안을 강화하기 위해 액세스 토큰을 사용하는 것이 권장됩니다:

```bash
# Docker CLI에서 토큰으로 로그인
docker login -u username --password-stdin
```

---

## 3. 이미지 관리

### 3.1 이미지 푸시

로컬에서 생성한 이미지를 Docker Hub에 올리는 과정:

```bash
# 이미지 태깅
docker tag local-image:version username/repository-name:tag

# 이미지 푸시
docker push username/repository-name:tag
```

### 3.2 이미지 태그 관리

체계적인 이미지 버전 관리를 위한 태깅 전략:

```bash
# 개발 버전 태깅
docker tag myapp:latest username/myapp:dev

# 스테이징 버전 태깅
docker tag myapp:latest username/myapp:staging

# 프로덕션 버전 태깅
docker tag myapp:latest username/myapp:1.0.0
```

---

## 4. 저장소 관리

### 4.1 저장소 생성 및 설정

저장소의 효율적인 관리를 위한 설정:

1. 저장소 설명 작성
2. README 파일 관리
3. 태그 정책 수립
4. 접근 권한 설정

### 4.2 팀 협업 설정

팀 단위 작업을 위한 저장소 관리:

```yaml
# docker-compose.yml 예시
services:
  app:
    image: teamname/project-name:${VERSION}
    build:
      context: .
      args:
        BUILD_VERSION: ${VERSION}
```

---

## 5. 자동화된 빌드

### 5.1 GitHub 연동

GitHub 저장소와 Docker Hub 연동 설정:

1. GitHub 계정 연결
2. 빌드 규칙 설정
3. 자동 빌드 트리거 구성

### 5.2 자동 빌드 설정

```yaml
# GitHub Actions workflow 예시
name: Docker Build and Push

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v2
    
    - name: Login to Docker Hub
      uses: docker/login-action@v1
      with:
        username: ${{ secrets.DOCKERHUB_USERNAME }}
        password: ${{ secrets.DOCKERHUB_TOKEN }}
    
    - name: Build and push
      uses: docker/build-push-action@v2
      with:
        push: true
        tags: username/repository:latest
```

---

## 6. 고급 기능 활용

### 6.1 웹훅 설정

자동화된 배포 파이프라인 구성:

```json
{
  "name": "deployment-webhook",
  "image": "username/repository",
  "callbacks": [
    {
      "url": "https://your-deployment-server/webhook",
      "method": "POST",
      "headers": {
        "Content-Type": "application/json"
      }
    }
  ]
}
```

### 6.2 이미지 스캐닝

보안 취약점 검사 설정:

1. 자동 스캐닝 활성화
2. 취약점 리포트 검토
3. 보안 정책 설정

---

## 7. 모범 사례

### 7.1 이미지 최적화

효율적인 이미지 관리를 위한 전략:

1. 다단계 빌드 사용
2. 적절한 베이스 이미지 선택
3. 캐시 레이어 최적화
4. 이미지 크기 최소화

### 7.2 보안 강화

```dockerfile
# Dockerfile 보안 강화 예시
FROM node:16-alpine AS builder
WORKDIR /app
COPY package*.json ./
RUN npm ci --only=production
COPY . .

FROM node:16-alpine
USER node
WORKDIR /app
COPY --from=builder --chown=node:node /app ./
EXPOSE 3000
CMD ["npm", "start"]
```

---

## 8. 문제 해결 및 디버깅

### 8.1 일반적인 문제 해결

자주 발생하는 문제들의 해결 방법:

1. 권한 문제
2. 네트워크 연결 문제
3. 빌드 실패
4. 푸시 오류

### 8.2 로깅 및 모니터링

```bash
# 빌드 로그 확인
docker build --progress=plain .

# 푸시 상태 확인
docker push -v username/repository:tag
```

---

## 참고 자료

- [Docker Hub 공식 문서](https://docs.docker.com/docker-hub/)
- [Docker Hub API 문서](https://docs.docker.com/docker-hub/api/latest/)
- [Docker 보안 가이드](https://docs.docker.com/engine/security/)

---

## 마무리

Docker Hub는 컨테이너 이미지의 저장, 공유, 관리를 위한 핵심 서비스입니다. 이 문서에서 다룬 기본 개념부터 고급 기능까지의 내용을 바탕으로 실무에서 Docker Hub를 효과적으로 활용할 수 있습니다. 특히 자동화된 빌드와 배포 파이프라인을 구축하여 개발 프로세스를 최적화할 수 있습니다.