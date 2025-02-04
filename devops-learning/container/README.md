# 📂 컨테이너 학습 개요

> **목표:**  
> - **컨테이너 기술의 기본 개념과 실무 적용 방법을 학습**한다.  
> - **Docker, Docker Compose, 컨테이너 네트워킹, 보안 및 레지스트리 운영을 익힌다.**  
> - **컨테이너화된 애플리케이션을 구축하고 배포하는 방법을 실습한다.**  
> - **이론 → 도구 실습 → 프로젝트 적용 → 사례 분석의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **각 디렉토리는 컨테이너의 핵심 개념과 도구를 포함하며, 하위 디렉토리는 보다 상세한 학습 주제를 다룹니다.**  

```
container/
├── docker
│   ├── basics
│   ├── compose
│   └── networking
│
├── security
│   └── trivy
│
└── registry
    ├── docker-hub
    ├── amazon-ecr
```

---

## 📖 **1. 핵심 개념 개요**
> **컨테이너 기술은 소프트웨어를 독립적이고 일관된 환경에서 실행할 수 있도록 지원하는 가상화 기술입니다.**

- ✅ **Docker 기본 개념 및 아키텍처**  
- ✅ **Docker Compose를 활용한 멀티 컨테이너 애플리케이션 구축**  
- ✅ **컨테이너 네트워킹 및 보안 설정**  
- ✅ **컨테이너 이미지를 저장하고 배포하기 위한 레지스트리 운영 (Docker Hub, Amazon ECR)**  

---

## 🏗 **2. 학습 내용**
### 📌 Docker
- **Docker 설치 및 기본 사용법**
- **Dockerfile을 활용한 컨테이너 이미지 생성**
- **컨테이너 실행 및 관리 명령어 학습**

### 📌 Docker Compose
- **docker-compose.yml을 활용한 멀티 컨테이너 환경 구성**
- **서비스 간 네트워크 설정 및 볼륨 활용**

### 📌 컨테이너 네트워킹
- **Docker 브리지 네트워크, 오버레이 네트워크 이해**
- **컨테이너 간 통신 및 포트 매핑 전략**

### 📌 보안 (Trivy 활용)
- **컨테이너 이미지 보안 분석 및 취약점 스캐닝**
- **이미지 서명 및 신뢰할 수 있는 빌드 구성**

### 📌 컨테이너 레지스트리
- **Docker Hub 및 Amazon ECR을 활용한 이미지 저장 및 배포**
- **프라이빗 레지스트리 운영 전략**

---

## 🚀 **3. 실전 사례 분석**
> **컨테이너 기술을 활용하여 확장성과 이식성이 높은 애플리케이션을 운영하는 실제 기업 사례를 분석합니다.**

- **Netflix** - 마이크로서비스 아키텍처와 컨테이너 활용  
- **Spotify** - 컨테이너 기반 CI/CD 파이프라인 운영  
- **Google** - Kubernetes 기반 컨테이너 오케스트레이션  

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → 컨테이너 개념과 원리 이해  
2. **도구 실습** → Docker, Docker Compose, 네트워킹, 보안 및 레지스트리 실습 진행  
3. **프로젝트 적용** → 실전 환경에서 컨테이너를 활용한 애플리케이션 배포  
4. **사례 분석** → 다양한 기업의 컨테이너 운영 전략 연구  

---

## 📚 **5. 추천 리소스**
- **책:**  
  - _Docker Deep Dive_ - Nigel Poulton  
  - _Kubernetes Up & Running_ - Kelsey Hightower  

- **GitHub 레포지토리:**  
  - [Awesome Docker](https://github.com/veggiemonk/awesome-docker)  
  - [Docker Samples](https://github.com/docker/docker-samples)  

- **공식 문서:**  
  - [Docker Docs](https://docs.docker.com/)  
  - [Docker Compose Docs](https://docs.docker.com/compose/)  
  - [Amazon ECR Docs](https://docs.aws.amazon.com/AmazonECR/latest/userguide/what-is-ecr.html)  
  - [Trivy Docs](https://aquasecurity.github.io/trivy/)  

---

## ✅ **마무리**
이 문서는 **컨테이너 기술의 필수 개념과 도구를 효과적으로 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 사례 분석**의 단계로 학습하며, **실무에서 컨테이너를 효과적으로 운영하는 방법**을 다룹니다. 🚀

