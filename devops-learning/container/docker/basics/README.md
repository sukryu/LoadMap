# 📂 Docker - Basics 학습 개요

> **목표:**  
> - **Docker의 기본 개념과 사용법을 학습**한다.  
> - **컨테이너와 이미지의 개념을 이해하고 활용 방법을 익힌다.**  
> - **기본적인 Docker 명령어를 익히고 실습을 진행한다.**  
> - **이론 → 실습 → 프로젝트 적용의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **Docker의 기초 개념을 이해하고 기본 명령어를 학습합니다.**  

```
basics/
├── introduction.md    # Docker 개요 및 기본 개념
├── installation.md    # Docker 설치 및 환경 설정
├── commands.md        # 주요 Docker 명령어
└── README.md
```

---

## 📖 **1. 기본 개념 개요**
> **Docker는 애플리케이션을 컨테이너로 패키징하여 실행하는 경량 가상화 기술입니다.**

- ✅ **컨테이너(Container):** 애플리케이션과 종속성을 포함하는 독립적인 실행 환경  
- ✅ **이미지(Image):** 컨테이너 실행을 위한 불변의 패키지  
- ✅ **Dockerfile:** 컨테이너 이미지를 빌드하는 데 사용되는 설정 파일  
- ✅ **볼륨(Volumes):** 데이터 지속성을 위한 저장소  
- ✅ **네트워크(Networking):** 컨테이너 간 통신을 위한 네트워크 설정  

---

## 🏗 **2. 학습 내용**
### 📌 Introduction (Docker 소개)
- **Docker란 무엇인가?**
- **컨테이너 기술이 기존 가상화 기술과 다른 점**

### 📌 Installation (Docker 설치 및 환경 설정)
- **Windows, Mac, Linux에서 Docker 설치하기**
- **Docker Daemon 및 CLI 개념 이해**

### 📌 Commands (주요 Docker 명령어)
- **컨테이너 실행 및 관리 (`docker run`, `docker ps`, `docker stop`)**
- **이미지 검색 및 다운로드 (`docker pull`, `docker images`)**
- **컨테이너 내부 접속 (`docker exec`, `docker attach`)**
- **볼륨 및 네트워크 관리 (`docker volume`, `docker network`)**

---

## 🚀 **3. 실전 예제**
> **Docker의 기본 명령어를 실습하며 컨테이너 환경을 익힙니다.**

```sh
# Docker 이미지 다운로드
docker pull nginx

# 컨테이너 실행
docker run --name my-nginx -d -p 8080:80 nginx

# 실행 중인 컨테이너 확인
docker ps

# 컨테이너 내부 접속
docker exec -it my-nginx /bin/sh

# 컨테이너 정지 및 삭제
docker stop my-nginx
docker rm my-nginx
```

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → Docker의 개념과 기본 구조 이해  
2. **기본 실습** → Docker 명령어 실습 및 컨테이너 실행  
3. **프로젝트 적용** → 실제 프로젝트에서 Docker 활용  

---

## 📚 **5. 추천 리소스**
- **Docker 공식 문서:**  
  - [Docker Docs](https://docs.docker.com/)  

- **예제 및 템플릿:**  
  - [Awesome Docker](https://github.com/veggiemonk/awesome-docker)  
  - [Docker Samples](https://github.com/docker/docker-samples)  

---

## ✅ **마무리**
이 문서는 **Docker의 기본 개념을 이해하고 간단한 컨테이너 실행 및 관리 방법을 실습하는 가이드**입니다.  
다음 단계로 **Docker Compose 및 네트워크 설정 등을 학습하여 멀티 컨테이너 환경을 구성할 수 있습니다.** 🚀