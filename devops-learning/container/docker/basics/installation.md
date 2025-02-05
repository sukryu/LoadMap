# Docker 설치 및 환경 설정 가이드

> **목표:**  
> - 운영체제별 Docker 설치 방법을 이해한다.
> - Docker 환경 설정 방법을 습득한다.
> - 설치 후 정상 작동 여부를 확인한다.
> - 기본적인 문제 해결 방법을 파악한다.

---

## 1. 설치 전 준비사항

### 시스템 요구사항
운영체제별로 다음과 같은 요구사항을 충족해야 합니다.

**Windows의 경우:**
- Windows 10 Pro, Enterprise 또는 Education (64-bit)
- WSL 2 (Windows Subsystem for Linux 2)
- 가상화 기능 활성화 (BIOS에서 설정)
- 최소 4GB RAM

**macOS의 경우:**
- macOS Catalina 10.15 이상
- Apple Silicon(M1/M2) 또는 Intel 프로세서
- 최소 4GB RAM

**Linux의 경우:**
- 64-bit 버전의 Ubuntu, Debian, CentOS 등
- 3.10 버전 이상의 Linux 커널
- 최소 4GB RAM

### 사전 설정
**Windows 사용자:**
1. Windows 기능에서 'Hyper-V' 활성화
2. WSL 2 설치 및 설정
3. BIOS에서 가상화 기능 활성화 확인

**Linux 사용자:**
1. 이전 버전의 Docker 제거
```bash
sudo apt-get remove docker docker-engine docker.io containerd runc
```

2. 필요한 패키지 설치
```bash
sudo apt-get update
sudo apt-get install \
    apt-transport-https \
    ca-certificates \
    curl \
    gnupg \
    lsb-release
```

---

## 2. Docker 설치 방법

### 2.1 Windows에서 설치
1. [Docker Desktop for Windows](https://www.docker.com/products/docker-desktop) 다운로드

2. 설치 파일 실행
   - 설치 과정에서 'Use WSL 2 instead of Hyper-V' 옵션 선택
   - 'Add to PATH' 옵션 선택

3. 설치 완료 후 시스템 재시작

4. Docker Desktop 실행 및 초기 설정
   - WSL 2 통합 설정
   - 리소스 할당 설정

### 2.2 macOS에서 설치
1. [Docker Desktop for Mac](https://www.docker.com/products/docker-desktop) 다운로드
   - Apple Silicon 또는 Intel 칩셋 버전 선택

2. .dmg 파일 실행
   - Applications 폴더로 Docker.app 드래그

3. Docker Desktop 실행
   - 초기 설정 진행
   - 리소스 할당 설정

### 2.3 Linux(Ubuntu)에서 설치
1. Docker 레포지토리 설정
```bash
# Docker의 공식 GPG키 추가
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg

# 레포지토리 추가
echo \
  "deb [arch=amd64 signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu \
  $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
```

2. Docker Engine 설치
```bash
sudo apt-get update
sudo apt-get install docker-ce docker-ce-cli containerd.io
```

3. Docker 서비스 시작
```bash
sudo systemctl start docker
sudo systemctl enable docker
```

---

## 3. 설치 후 환경 설정

### 3.1 기본 설정
1. Docker 그룹에 사용자 추가 (Linux)
```bash
sudo usermod -aG docker $USER
newgrp docker
```

2. Docker Desktop 설정 (Windows/Mac)
- 메모리 할당: 기본 2GB
- CPU 할당: 기본 2개
- 디스크 이미지 위치 설정
- 프록시 설정 (필요한 경우)

### 3.2 네트워크 설정
1. 기본 네트워크 확인
```bash
docker network ls
```

2. 프록시 설정 (필요한 경우)
```json
{
  "proxies": {
    "default": {
      "httpProxy": "http://proxy.example.com:8080",
      "httpsProxy": "http://proxy.example.com:8080",
      "noProxy": "localhost,127.0.0.1"
    }
  }
}
```

### 3.3 스토리지 설정
1. 기본 저장 위치 확인
2. 디스크 공간 관리 설정
3. 컨테이너 로그 관리 설정

---

## 4. 설치 확인 및 테스트

### 4.1 버전 확인
```bash
docker --version
docker-compose --version
```

### 4.2 Docker 동작 테스트
1. Hello World 실행
```bash
docker run hello-world
```

2. Nginx 테스트
```bash
docker run -d -p 80:80 nginx
```

3. 실행 중인 컨테이너 확인
```bash
docker ps
```

---

## 5. 문제 해결

### 5.1 일반적인 문제
1. Docker 데몬이 시작되지 않는 경우
```bash
# Docker 서비스 상태 확인
sudo systemctl status docker

# Docker 서비스 재시작
sudo systemctl restart docker
```

2. 권한 문제
```bash
# Docker 그룹 확인
groups $USER

# Docker 그룹에 사용자 추가
sudo usermod -aG docker $USER
```

3. WSL 2 관련 문제 (Windows)
```powershell
# WSL 버전 확인
wsl --status

# WSL 업데이트
wsl --update
```

### 5.2 리소스 문제
1. 메모리 부족
- Docker Desktop의 리소스 설정 조정
- 불필요한 컨테이너와 이미지 정리

2. 디스크 공간 부족
```bash
# 사용하지 않는 컨테이너 삭제
docker container prune

# 사용하지 않는 이미지 삭제
docker image prune
```

---

## 6. 보안 설정

### 6.1 기본 보안 설정
1. Docker 데몬 보안
- TLS 인증 설정
- API 엔드포인트 보호

2. 컨테이너 보안
- 권한 제한
- 리소스 제한 설정

### 6.2 네트워크 보안
1. 기본 네트워크 정책 설정
2. 컨테이너 간 통신 제어

---

## 참고 자료

- [Docker 공식 설치 가이드](https://docs.docker.com/engine/install/)
- [Docker Desktop 설치 가이드](https://docs.docker.com/desktop/)
- [WSL 2 설치 가이드](https://docs.microsoft.com/windows/wsl/install)
- [Docker 보안 가이드](https://docs.docker.com/engine/security/)

---

## 마무리

Docker의 성공적인 설치와 환경 설정은 컨테이너 기반 개발의 첫걸음입니다. 이 문서에서 다룬 내용을 바탕으로 안정적인 Docker 환경을 구축하고, 필요에 따라 설정을 조정하며 사용할 수 있습니다. 문제가 발생할 경우 문제 해결 섹션을 참고하여 해결할 수 있습니다.