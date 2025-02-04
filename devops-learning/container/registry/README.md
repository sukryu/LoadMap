# 📂 Docker Registry 학습 개요

> **목표:**  
> - **Docker Registry의 개념과 실무 적용 방법을 학습**한다.  
> - **컨테이너 이미지를 저장, 관리 및 배포하는 방법을 익힌다.**  
> - **기본 개념과 명령어를 학습한 후, 고급 기능 및 실무 활용 전략을 학습한다.**  
> - **이론 → 도구 실습 → 프로젝트 적용 → 최적화의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **Docker Registry 학습을 Docker Hub 및 프라이빗 레지스트리로 나누어 진행합니다.**  

```
registry/
├── docker-hub.md  # Docker Hub 활용 방법
├── amazon-ecr.md  # AWS Elastic Container Registry 활용 방법
└── README.md
```

---

## 📖 **1. 기본 개념 개요**
> **Docker Registry는 컨테이너 이미지를 저장하고 배포할 수 있는 저장소 역할을 합니다.**

- ✅ **Docker Hub:** 공식적인 퍼블릭 레지스트리로, Docker 이미지를 공유 및 배포  
- ✅ **Private Registry:** 내부에서 관리하는 프라이빗 컨테이너 이미지 저장소  
- ✅ **Amazon ECR:** AWS에서 제공하는 관리형 컨테이너 이미지 저장소  
- ✅ **Image Tagging:** 컨테이너 이미지 버전을 관리하는 태깅 시스템  
- ✅ **Authentication & Authorization:** 프라이빗 레지스트리에서 보안 및 접근 제어  

---

## 🏗 **2. 학습 내용**
### 📌 Docker Hub (공식 레지스트리 활용)
- **Docker Hub 계정 생성 및 이미지 푸시/풀**
- **공개 및 비공개 레지스트리 활용 방법**
- **자동 빌드 및 웹훅을 활용한 이미지 배포 자동화**

### 📌 Amazon ECR (AWS 관리형 레지스트리 활용)
- **ECR 리포지토리 생성 및 이미지 푸시/풀**
- **IAM 권한 설정 및 인증 방식 이해**
- **ECR을 활용한 CI/CD 파이프라인 구축**

---

## 🚀 **3. 실전 예제**
> **Docker Registry를 활용하여 컨테이너 이미지를 업로드 및 배포하는 실습**

```sh
# Docker Hub 로그인
docker login

# 로컬에서 이미지 태깅 후 Docker Hub에 푸시
docker tag my-app:latest mydockerhubusername/my-app:latest
docker push mydockerhubusername/my-app:latest

# Amazon ECR 로그인 및 푸시
aws ecr get-login-password --region us-east-1 | docker login --username AWS --password-stdin <AWS_ACCOUNT_ID>.dkr.ecr.us-east-1.amazonaws.com

docker tag my-app:latest <AWS_ACCOUNT_ID>.dkr.ecr.us-east-1.amazonaws.com/my-app:latest
docker push <AWS_ACCOUNT_ID>.dkr.ecr.us-east-1.amazonaws.com/my-app:latest
```

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → Docker Registry 개념과 구조 이해  
2. **도구 실습** → 기본 및 고급 레지스트리 활용 실습  
3. **프로젝트 적용** → 실제 프로젝트에서 Docker Registry 활용  
4. **최적화 연구** → 성능, 보안, 자동화 최적화  

---

## 📚 **5. 추천 리소스**
- **Docker Registry 공식 문서:**  
  - [Docker Hub Docs](https://docs.docker.com/docker-hub/)  
  - [Amazon ECR Docs](https://docs.aws.amazon.com/AmazonECR/latest/userguide/what-is-ecr.html)  

- **Docker Registry 예제 및 템플릿:**  
  - [Awesome Docker](https://github.com/veggiemonk/awesome-docker)  
  - [Docker Samples](https://github.com/docker/docker-samples)  

---

## ✅ **마무리**
이 문서는 **Docker Registry의 기본 개념부터 실무 활용까지 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 최적화**의 단계로 학습하며, **실무에서 Docker Registry를 효과적으로 활용하는 방법**을 다룹니다. 🚀