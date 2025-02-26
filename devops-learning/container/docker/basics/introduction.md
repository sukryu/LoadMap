# Docker 개요 및 기본 개념

> **목표:**  
> - Docker의 핵심 개념과 작동 방식을 이해한다.
> - 컨테이너와 이미지의 관계를 파악한다.
> - Docker의 기본 명령어와 사용 방법을 습득한다.
> - Docker를 실제 개발 환경에 적용할 수 있는 기초를 다진다.

---

## 1. Docker란?

### 정의
Docker는 애플리케이션을 컨테이너라는 표준화된 단위로 패키징하여 어디서든 실행할 수 있게 해주는 플랫폼입니다. 마치 실제 물류 시스템에서 다양한 화물을 동일한 규격의 컨테이너에 담아 운송하는 것처럼, 소프트웨어도 Docker 컨테이너에 담아 어떤 환경에서든 동일하게 실행할 수 있습니다.

### 왜 필요한가?
- **환경 일관성:** "내 컴퓨터에서는 잘 되는데..."라는 문제를 해결합니다.
- **빠른 배포:** 애플리케이션과 필요한 모든 것을 하나의 패키지로 배포할 수 있습니다.
- **자원 효율성:** 가상 머신보다 가볍고 빠르게 실행됩니다.
- **확장성:** 필요에 따라 컨테이너를 쉽게 복제하고 배포할 수 있습니다.

---

## 2. 핵심 구성 요소

### 2.1 Docker 이미지
- 애플리케이션 실행에 필요한 모든 것을 포함하는 '설계도'입니다.
- 코드, 런타임, 시스템 도구, 시스템 라이브러리 등을 포함합니다.
- 변경이 불가능한(Immutable) 읽기 전용 템플릿입니다.

예시: nginx 이미지의 구조
```plaintext
nginx 이미지
├── Ubuntu 베이스 이미지
├── nginx 웹 서버
├── 설정 파일
└── 기타 필요한 라이브러리
```

### 2.2 Docker 컨테이너
- 이미지를 실행한 인스턴스입니다.
- 호스트 시스템과 격리된 환경에서 동작합니다.
- 각 컨테이너는 독립적으로 실행됩니다.

예시: 하나의 이미지로 여러 컨테이너 실행
```plaintext
nginx 이미지 ──┬── 컨테이너 1 (웹서버 A)
               ├── 컨테이너 2 (웹서버 B)
               └── 컨테이너 3 (웹서버 C)
```

### 2.3 Dockerfile
- Docker 이미지를 생성하기 위한 '조립 설명서'입니다.
- 이미지 생성 과정을 코드로 작성할 수 있습니다.

```dockerfile
# 간단한 Node.js 애플리케이션을 위한 Dockerfile 예시
FROM node:14
WORKDIR /app
COPY package*.json ./
RUN npm install
COPY . .
EXPOSE 3000
CMD ["npm", "start"]
```

---

## 3. Docker의 작동 방식

### 3.1 기본 아키텍처
Docker는 클라이언트-서버 아키텍처를 사용합니다:
- **Docker 데몬:** 이미지와 컨테이너를 관리하는 서버
- **Docker 클라이언트:** 사용자가 Docker와 상호작용하는 도구
- **Docker 레지스트리:** 이미지를 저장하고 공유하는 저장소

### 3.2 컨테이너 생명주기
1. 이미지 다운로드 (Pull)
2. 컨테이너 생성 (Create)
3. 컨테이너 시작 (Start)
4. 컨테이너 실행 (Run)
5. 컨테이너 중지 (Stop)
6. 컨테이너 삭제 (Remove)

---

## 4. 기본 명령어

### 4.1 이미지 관련 명령어
```bash
# 이미지 검색
docker search nginx

# 이미지 다운로드
docker pull nginx

# 이미지 목록 확인
docker images

# 이미지 삭제
docker rmi nginx
```

### 4.2 컨테이너 관련 명령어
```bash
# 컨테이너 생성 및 시작
docker run nginx

# 실행 중인 컨테이너 목록 확인
docker ps

# 모든 컨테이너 목록 확인
docker ps -a

# 컨테이너 중지
docker stop [컨테이너ID]

# 컨테이너 삭제
docker rm [컨테이너ID]
```

---

## 5. Docker의 장단점

### 장점
- **이식성:** 어디서든 동일하게 실행
- **가벼움:** 가상머신보다 적은 자원 사용
- **빠른 시작:** seconds 단위의 실행 시간
- **버전 관리:** 이미지 버전 관리 용이

### 단점
- **초기 학습 필요:** 새로운 개념과 도구 학습 필요
- **GUI 애플리케이션:** GUI 앱 실행이 복잡
- **보안:** 컨테이너 보안 설정 주의 필요

---

## 6. 시작하기

### 6.1 설치 단계
1. Docker Desktop 다운로드 (운영체제에 맞는 버전)
2. 설치 파일 실행
3. 설치 완료 후 Docker 데몬 실행
4. 터미널에서 `docker --version` 으로 설치 확인

### 6.2 주의사항
- Windows의 경우 WSL2 설치 필요
- 가상화 기능 활성화 확인
- 시스템 요구사항 확인

---

## 참고 자료

- [Docker 공식 문서](https://docs.docker.com/)
- [Docker Hub](https://hub.docker.com/)
- [Docker 시작하기 가이드](https://docs.docker.com/get-started/)

---

## 마무리

Docker는 현대 소프트웨어 개발에서 필수적인 도구가 되었습니다. 기본 개념을 이해하고 실제 프로젝트에 적용하면서, 점진적으로 더 복잡한 컨테이너 환경을 구성하고 최적화해 나갈 수 있습니다. 이 문서에서 다룬 기본 개념들은 Docker를 시작하는 데 있어 중요한 기초가 될 것입니다.