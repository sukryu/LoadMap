# 📂 Jenkins - Basic 학습 개요

> **목표:**  
> - **Jenkins의 기본 개념과 기초적인 사용법을 학습**한다.  
> - **파이프라인 실행 방식과 주요 개념(Job, Stage, Node 등)을 이해한다.**  
> - **기본적인 CI/CD 파이프라인을 설정하고 실행하는 방법을 익힌다.**  
> - **이론 → 실습 → 프로젝트 적용의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **Jenkins의 기초 개념을 이해하고 기본 명령어를 학습합니다.**  

```
basic/
├── introduction.md    # Jenkins 개요 및 기본 개념
├── pipeline-basics.md # 기본적인 파이프라인 구성 및 실행
├── job-management.md  # Job 및 빌드 관리
└── README.md
```

---

## 📖 **1. 기본 개념 개요**
> **Jenkins는 DevOps에서 CI/CD 파이프라인을 자동화하는 데 널리 사용되는 도구입니다.**

- ✅ **파이프라인(Pipeline):** 코드 변경 사항을 자동으로 빌드, 테스트, 배포하는 프로세스  
- ✅ **잡(Job):** 특정 빌드 및 테스트 작업을 수행하는 개별 실행 단위  
- ✅ **노드(Node):** 빌드 및 배포를 실행하는 실행 환경  
- ✅ **플러그인(Plugin):** Jenkins의 기능을 확장하는 모듈  

---

## 🏗 **2. 학습 내용**
### 📌 Introduction (Jenkins 소개)
- **Jenkins란 무엇인가?**
- **CI/CD 개념과 Jenkins의 역할**

### 📌 Pipeline Basics (기본 파이프라인 이해)
- **Jenkins Pipeline 기본 구성 및 실행**
- **Declarative Pipeline과 Scripted Pipeline 비교**
- **간단한 CI/CD 파이프라인 실행**

### 📌 Job Management (Job 및 빌드 구성)
- **Freestyle Job과 Pipeline Job의 차이**
- **빌드 트리거 및 실행 전략 설정**
- **워크스페이스 및 빌드 아티팩트 관리**

---

## 🚀 **3. 실전 예제**
> **Jenkins를 활용한 간단한 파이프라인 예제를 실습합니다.**

```groovy
pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                echo 'Building the project...'
            }
        }
        stage('Test') {
            steps {
                echo 'Running tests...'
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying application...'
            }
        }
    }
}
```

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → Jenkins의 개념과 기본 구조 이해  
2. **기본 실습** → Pipeline 및 Job을 작성하고 간단한 CI/CD 실행  
3. **프로젝트 적용** → 실제 프로젝트에 Jenkins 파이프라인 적용  

---

## 📚 **5. 추천 리소스**
- **Jenkins 공식 문서:**  
  - [Jenkins Docs](https://www.jenkins.io/doc/)  
  - [Pipeline Syntax](https://www.jenkins.io/doc/book/pipeline/syntax/)  

- **예제 및 템플릿:**  
  - [Jenkins Pipeline Examples](https://github.com/jenkinsci/pipeline-examples)  
  - [Awesome Jenkins](https://github.com/jenkinsci/awesome-jenkins)  

---

## ✅ **마무리**
이 문서는 **Jenkins의 기본 개념을 이해하고 간단한 CI/CD 파이프라인을 작성하는 방법을 학습하기 위한 가이드**입니다.  
다음 단계로 **고급 개념(Advanced)에서 분산 빌드, 보안 강화 등을 학습할 수 있습니다.** 🚀

