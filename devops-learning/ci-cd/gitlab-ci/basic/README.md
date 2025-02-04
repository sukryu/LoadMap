# 📂 GitLab CI/CD - Basic 학습 개요

> **목표:**  
> - **GitLab CI/CD의 기본 개념과 기초적인 사용법을 학습**한다.  
> - **파이프라인 실행 방식과 주요 개념(Job, Stage, Runner 등)을 이해한다.**  
> - **기본적인 CI/CD 파이프라인을 설정하고 실행하는 방법을 익힌다.**  
> - **이론 → 실습 → 프로젝트 적용의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **GitLab CI/CD의 기초 개념을 이해하고 기본 명령어를 학습합니다.**  

```
basic/
├── introduction.md    # GitLab CI/CD 개요 및 기본 개념
├── pipeline-basics.md # 기본적인 파이프라인 구성 및 실행
├── jobs-and-stages.md # Job 및 Stage 개념 이해
└── README.md
```

---

## 📖 **1. 기본 개념 개요**
> **GitLab CI/CD는 GitLab 저장소에서 이벤트가 발생할 때 자동으로 실행되는 CI/CD 파이프라인을 제공합니다.**

- ✅ **파이프라인(Pipeline):** Job의 집합으로, 코드를 자동화하여 실행하는 프로세스  
- ✅ **잡(Job):** 특정 작업을 수행하는 개별 실행 단위  
- ✅ **스테이지(Stage):** 여러 Job을 그룹화하여 순차적 실행을 제어  
- ✅ **러너(Runner):** GitLab CI/CD 파이프라인을 실행하는 환경(클라우드, 온프레미스)  

---

## 🏗 **2. 학습 내용**
### 📌 Introduction (GitLab CI/CD 소개)
- **GitLab CI/CD란 무엇인가?**
- **CI/CD의 필요성과 GitLab에서의 적용 방식**

### 📌 Pipeline Basics (기본 파이프라인 이해)
- **.gitlab-ci.yml 파일을 활용한 기본 파이프라인 설정**
- **Job과 Stage의 개념 및 실행 흐름**
- **간단한 CI/CD 파이프라인 실행**

### 📌 Jobs & Stages (Job 및 Stage 구성)
- **Job과 Stage의 역할 및 실행 순서 이해**
- **병렬 및 순차적 실행 방식 적용**
- **파이프라인 실행 결과 분석 및 디버깅**

---

## 🚀 **3. 실전 예제**
> **GitLab CI/CD를 활용한 간단한 파이프라인 예제를 실습합니다.**

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
  script:
    - echo "테스트 실행 중..."
    - cat build/output.txt || echo "빌드 파일이 없습니다."

deploy-job:
  stage: deploy
  script:
    - echo "배포 진행 중..."
```

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → GitLab CI/CD의 개념과 기본 구조 이해  
2. **기본 실습** → .gitlab-ci.yml을 작성하고 간단한 CI/CD 파이프라인 실행  
3. **프로젝트 적용** → 실제 프로젝트에 GitLab CI/CD 적용  

---

## 📚 **5. 추천 리소스**
- **GitLab CI/CD 공식 문서:**  
  - [GitLab CI/CD Docs](https://docs.gitlab.com/ee/ci/)  
  - [Pipeline Configuration Reference](https://docs.gitlab.com/ee/ci/yaml/)  

- **예제 및 템플릿:**  
  - [Awesome GitLab CI/CD](https://gitlab.com/awesome-ci-cd)  
  - [GitLab CI/CD Templates](https://gitlab.com/gitlab-org/gitlab-ci-yaml)  

---

## ✅ **마무리**
이 문서는 **GitLab CI/CD의 기본 개념을 이해하고 간단한 파이프라인을 작성하는 방법을 학습하기 위한 가이드**입니다.  
다음 단계로 **고급 개념(Advanced)에서 병렬 실행, 자체 호스팅 러너, 보안 강화 등을 학습할 수 있습니다.** 🚀

