# 📂 CI/CD 학습 개요

> **목표:**  
> - **지속적 통합(Continuous Integration) 및 지속적 배포(Continuous Deployment)의 개념과 실무 적용 방법을 학습**한다.  
> - **Jenkins, GitHub Actions, GitLab CI, Nexus, Artifactory 등의 도구를 활용한 CI/CD 파이프라인 구축 방법을 익힌다.**  
> - **코드 자동화, 빌드 최적화, 배포 자동화를 통해 DevOps 문화를 효과적으로 실현하는 방법을 학습한다.**  
> - **이론 → 도구 실습 → 실전 프로젝트 적용 → 사례 분석의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **각 디렉토리는 CI/CD의 핵심 개념과 도구를 포함하며, 하위 디렉토리는 보다 상세한 학습 주제를 다룹니다.**  

```
ci-cd/
├── jenkins
├── github-actions
├── gitlab-ci
├── nexus
└── artifactory
```

---

## 📖 **1. 핵심 개념 개요**
> **CI/CD는 소프트웨어 개발 프로세스의 자동화를 목표로 하며, 코드 변경 사항을 빠르고 안정적으로 배포할 수 있도록 지원합니다.**

- ✅ **CI (지속적 통합):** 코드 변경 사항을 자동으로 빌드하고 테스트하여 문제를 조기에 발견  
- ✅ **CD (지속적 배포):** 안정적인 빌드가 프로덕션 환경으로 자동 배포  
- ✅ **CI/CD 파이프라인:** 자동화된 테스트 및 배포 워크플로우  
- ✅ **빌드 아티팩트 관리:** Nexus 및 Artifactory를 활용한 패키지 및 컨테이너 이미지 저장소 운영  

---

## 🏗 **2. 학습 내용**
### 📌 Jenkins
- **Jenkins 기본 개념 및 설치**
- **파이프라인을 활용한 CI/CD 구축**
- **플러그인을 활용한 기능 확장**

### 📌 GitHub Actions
- **워크플로우 정의 및 실행**
- **GitHub Actions를 활용한 빌드 및 배포 자동화**
- **Self-hosted Runner 활용**

### 📌 GitLab CI/CD
- **.gitlab-ci.yml을 활용한 파이프라인 구축**
- **멀티스테이지 빌드 및 배포 전략**
- **GitLab Registry를 활용한 컨테이너 이미지 관리**

### 📌 Nexus & Artifactory
- **아티팩트 저장소 개념 및 필요성**
- **Maven, NPM, Docker 리포지토리 운영**
- **보안 및 접근 제어 전략**

---

## 🚀 **3. 실전 사례 분석**
> **CI/CD 도구를 활용한 자동화된 배포 프로세스를 운영하는 실제 기업 사례를 분석합니다.**

- **Google** - Kubernetes 기반 GitOps 및 CI/CD  
- **Netflix** - Spinnaker를 활용한 멀티클라우드 배포  
- **Facebook** - 수천 개의 배포 파이프라인 운영 사례  

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → CI/CD 개념과 원리 이해  
2. **도구 실습** → Jenkins, GitHub Actions, GitLab CI, Nexus, Artifactory 실습 진행  
3. **프로젝트 적용** → 실전 환경에서 CI/CD 파이프라인 구축  
4. **사례 분석** → 다양한 기업의 CI/CD 운영 전략 연구  

---

## 📚 **5. 추천 리소스**
- **책:**  
  - _Continuous Delivery_ - Jez Humble & David Farley  
  - _The DevOps Handbook_ - Gene Kim  

- **GitHub 레포지토리:**  
  - [Awesome CI/CD](https://github.com/ci-cd-dev/awesome-ci-cd)  
  - [Jenkins Pipeline Examples](https://github.com/jenkinsci/pipeline-examples)  

- **공식 문서:**  
  - [Jenkins Docs](https://www.jenkins.io/doc/)  
  - [GitHub Actions Docs](https://docs.github.com/en/actions)  
  - [GitLab CI/CD Docs](https://docs.gitlab.com/ee/ci/)  
  - [Nexus Repository Docs](https://help.sonatype.com/repomanager3)  
  - [Artifactory Docs](https://www.jfrog.com/confluence/display/JFROG/Artifactory)  

---

## ✅ **마무리**
이 문서는 **CI/CD의 필수 개념과 도구를 효과적으로 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 사례 분석**의 단계로 학습하며, **실무에서 CI/CD를 효과적으로 운영하는 방법**을 다룹니다. 🚀