# 📂 GitLab CI/CD 학습 개요

> **목표:**  
> - **GitLab CI/CD의 개념과 실무 적용 방법을 학습**한다.  
> - **CI/CD 파이프라인을 설정하고 자동화하여 애플리케이션을 효과적으로 배포하는 방법을 익힌다.**  
> - **기본 개념과 명령어를 학습한 후, 고급 기능 및 실무 활용 전략을 학습한다.**  
> - **이론 → 도구 실습 → 프로젝트 적용 → 사례 분석의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **GitLab CI/CD 학습을 기본(Basic)과 고급(Advanced)으로 나누어 진행합니다.**  

```
gitlab-ci/
├── basic
│   ├── introduction.md    # GitLab CI/CD 개요 및 기본 개념
│   ├── pipeline-basics.md # 기본적인 파이프라인 구성 및 실행
│   ├── jobs-and-stages.md # Job 및 Stage 개념 이해
│   └── README.md
│
├── advanced
│   ├── custom-executors.md  # 사용자 정의 실행기
│   ├── parallel-execution.md # 병렬 실행 및 매트릭스 빌드
│   ├── self-hosted-runners.md # 자체 호스팅 러너 사용법
│   ├── security-best-practices.md # 보안 및 권한 관리
│   ├── deployment-strategies.md # 실무 CI/CD 배포 전략
│   └── README.md
```

---

## 📖 **1. 기본 개념 개요**
> **GitLab CI/CD는 GitLab 저장소에서 자동으로 실행되는 CI/CD 파이프라인을 제공합니다.**

- ✅ **GitLab CI/CD의 동작 방식 이해**  
- ✅ **.gitlab-ci.yml 파일을 활용한 파이프라인 설정**  
- ✅ **Job, Stage, Runner 개념 이해**  
- ✅ **CI/CD의 기본적인 빌드, 테스트, 배포 구성**  

---

## 🏗 **2. 학습 내용**
### 📌 Basic (기본 개념 및 활용)
- **GitLab CI/CD의 기본 개념 이해**
- **기본적인 .gitlab-ci.yml 파일 작성 및 실행**
- **Pipeline의 Job, Stage 개념 및 실행 방식**

### 📌 Advanced (고급 개념 및 실무 적용)
- **사용자 정의 실행기(Custom Executors) 구성**
- **매트릭스 빌드를 활용한 병렬 실행**
- **자체 호스팅 러너를 활용한 성능 최적화**
- **보안 및 권한 관리, 비밀값 처리**
- **실무에서의 CI/CD 배포 전략 (Blue-Green, Canary 배포 등)**

---

## 🚀 **3. 실전 사례 분석**
> **GitLab CI/CD를 활용하여 실제 프로젝트에서 CI/CD를 운영하는 사례를 분석합니다.**

- **GitLab Inc.** - 자체 CI/CD 플랫폼을 활용한 DevOps 최적화  
- **Red Hat** - GitLab CI/CD 기반의 컨테이너 빌드 및 배포  
- **Siemens** - 대규모 엔터프라이즈 프로젝트의 CI/CD 적용 사례  

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → GitLab CI/CD 개념과 구조 이해  
2. **도구 실습** → 기본 및 고급 기능을 실습하며 익히기  
3. **프로젝트 적용** → 실제 프로젝트에 GitLab CI/CD 적용  
4. **사례 분석** → 다양한 기업의 GitLab CI/CD 활용 사례 연구  

---

## 📚 **5. 추천 리소스**
- **GitLab CI/CD 공식 문서:**  
  - [GitLab CI/CD Docs](https://docs.gitlab.com/ee/ci/)  
  - [Pipeline Configuration Reference](https://docs.gitlab.com/ee/ci/yaml/)  

- **GitLab CI/CD 예제:**  
  - [Awesome GitLab CI/CD](https://gitlab.com/awesome-ci-cd)  
  - [GitLab CI/CD Templates](https://gitlab.com/gitlab-org/gitlab-ci-yaml)  

---

## ✅ **마무리**
이 문서는 **GitLab CI/CD의 기본 개념부터 실무 활용까지 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 사례 분석**의 단계로 학습하며, **실무에서 GitLab CI/CD를 효과적으로 활용하는 방법**을 다룹니다. 🚀