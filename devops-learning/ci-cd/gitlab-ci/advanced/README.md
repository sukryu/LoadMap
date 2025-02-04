# 📂 GitLab CI/CD - Advanced 학습 개요

> **목표:**  
> - **GitLab CI/CD의 고급 개념과 실무 활용법을 학습**한다.  
> - **병렬 실행, 커스텀 실행기, 자체 호스팅 러너 등을 활용하여 효율적인 CI/CD 파이프라인을 구축한다.**  
> - **보안 및 권한 관리, 배포 전략을 익혀 실무에서 활용할 수 있도록 한다.**  
> - **이론 → 실습 → 프로젝트 적용 → 최적화의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **GitLab CI/CD의 고급 개념을 체계적으로 학습합니다.**  

```
advanced/
├── custom-executors.md  # 사용자 정의 실행기
├── parallel-execution.md # 병렬 실행 및 매트릭스 빌드
├── self-hosted-runners.md # 자체 호스팅 러너 사용법
├── security-best-practices.md # 보안 및 권한 관리
├── deployment-strategies.md # 실무 CI/CD 배포 전략
└── README.md
```

---

## 📖 **1. 고급 개념 개요**
> **GitLab CI/CD의 고급 기능을 활용하면 대규모 프로젝트에서도 자동화된 CI/CD를 더욱 강력하게 운영할 수 있습니다.**

- ✅ **커스텀 실행기(Custom Executors):** 특정 환경에 맞춘 실행기 설정  
- ✅ **병렬 실행(Parallel Execution):** 빌드 및 테스트 속도를 최적화  
- ✅ **자체 호스팅 러너(Self-Hosted Runners):** 클라우드 또는 온프레미스에서 실행 환경 관리  
- ✅ **보안 강화(Security Best Practices):** CI/CD 파이프라인 보안 및 접근 제어  
- ✅ **배포 전략(Deployment Strategies):** Blue-Green, Canary, Rolling 배포 적용  

---

## 🏗 **2. 학습 내용**
### 📌 Custom Executors (사용자 정의 실행기)
- **Docker 기반 실행기 및 SSH 실행기 설정**
- **고유한 환경에 맞춘 실행기 커스터마이징**

### 📌 Parallel Execution (병렬 실행)
- **다양한 환경에서 테스트를 병렬로 수행하는 방법**
- **매트릭스 빌드를 활용한 최적화**

### 📌 Self-Hosted Runners (자체 호스팅 러너)
- **GitLab 러너 설치 및 설정**
- **온프레미스 및 클라우드 환경에서 실행**
- **러너 최적화 및 성능 관리**

### 📌 Security Best Practices (보안 및 권한 관리)
- **GitLab CI/CD의 보안 강화 전략**
- **토큰 및 환경 변수 보안 관리**
- **권한 및 액세스 제어**

### 📌 Deployment Strategies (배포 전략)
- **Blue-Green 배포, Canary 배포, Rolling 업데이트 적용**
- **GitLab CI/CD를 활용한 Kubernetes 배포 자동화**
- **AWS, Azure, GCP를 활용한 멀티 클라우드 배포**

---

## 🚀 **3. 실전 예제**
> **고급 GitLab CI/CD 기능을 활용한 실전 예제를 학습합니다.**

```yaml
stages:
  - build
  - test
  - deploy

build-job:
  stage: build
  script:
    - echo "빌드 실행 중..."
    - mkdir build
    - touch build/output.txt

test-job:
  stage: test
  parallel:
    matrix:
      - NODE_VERSION: [14, 16, 18]
  script:
    - echo "Node.js 버전 $NODE_VERSION에서 테스트 실행 중..."

deploy-job:
  stage: deploy
  script:
    - echo "배포 진행 중..."
```

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → GitLab CI/CD의 고급 기능 이해  
2. **실습 진행** → 병렬 실행, 커스텀 실행기, 보안 설정 실습  
3. **프로젝트 적용** → 실무 CI/CD 파이프라인 구축 및 최적화  
4. **최적화 연구** → 성능, 보안, 비용 측면에서 효율성 개선  

---

## 📚 **5. 추천 리소스**
- **GitLab CI/CD 공식 문서:**  
  - [GitLab CI/CD Docs](https://docs.gitlab.com/ee/ci/)  
  - [Pipeline Configuration Reference](https://docs.gitlab.com/ee/ci/yaml/)  

- **고급 GitLab CI/CD 예제:**  
  - [Awesome GitLab CI/CD](https://gitlab.com/awesome-ci-cd)  
  - [GitLab CI/CD Advanced Templates](https://gitlab.com/gitlab-org/gitlab-ci-yaml)  

---

## ✅ **마무리**
이 문서는 **GitLab CI/CD의 고급 기능을 학습하고 실무에 적용할 수 있도록 구성된 가이드**입니다.  
기본 개념을 익힌 후, **병렬 실행, 자체 호스팅 러너, 보안 설정, 배포 전략 등 고급 기능을 활용하여 CI/CD를 최적화**할 수 있습니다. 🚀