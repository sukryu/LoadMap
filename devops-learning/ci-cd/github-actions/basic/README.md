# 📂 GitHub Actions - Basic 학습 개요

> **목표:**  
> - **GitHub Actions의 기본 개념과 기초적인 사용법을 학습**한다.  
> - **워크플로우 실행 방식과 주요 개념(Job, Step, Runner 등)을 이해한다.**  
> - **기본적인 CI/CD 파이프라인을 설정하고 실행하는 방법을 익힌다.**  
> - **이론 → 실습 → 프로젝트 적용의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **GitHub Actions의 기초 개념을 이해하고 기본 명령어를 학습합니다.**  

```
basic/
├── introduction.md    # GitHub Actions 개요 및 기본 개념
├── workflow-basics.md # 기본적인 워크플로우 구성 및 실행
├── actions-usage.md   # Actions 사용법 및 예제
└── README.md
```

---

## 📖 **1. 기본 개념 개요**
> **GitHub Actions는 저장소에서 이벤트가 발생할 때 자동으로 실행되는 CI/CD 파이프라인을 제공합니다.**

- ✅ **워크플로우(Workflow):** 자동화 프로세스를 정의하는 YAML 파일  
- ✅ **이벤트(Event):** GitHub Actions를 트리거하는 특정 작업(push, pull request 등)  
- ✅ **잡(Job):** 하나 이상의 스텝(Step)으로 구성되는 실행 단위  
- ✅ **스텝(Step):** 개별적인 작업 단위(예: 스크립트 실행, 테스트 수행)  
- ✅ **러너(Runner):** GitHub Actions 워크플로우를 실행하는 가상 머신 또는 컨테이너  

---

## 🏗 **2. 학습 내용**
### 📌 Introduction (GitHub Actions 소개)
- **GitHub Actions란 무엇인가?**
- **CI/CD란 무엇이며, GitHub Actions에서 어떻게 활용되는가?**

### 📌 Workflow Basics (워크플로우 기초)
- **YAML을 활용한 기본적인 워크플로우 구성**
- **트리거 이벤트 설정(push, pull_request 등)**
- **기본적인 잡(Job)과 스텝(Step) 구성**

### 📌 Actions Usage (기본 명령어 및 실행)
- **기본적인 GitHub Actions 실행 예제**
- **커스텀 액션 및 기본 제공 액션 사용법**
- **환경 변수 및 비밀값 관리**

---

## 🚀 **3. 실전 예제**
> **GitHub Actions를 활용한 간단한 CI/CD 예제를 실습합니다.**

```yaml
name: Basic GitHub Actions Example

on: [push]

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - name: 저장소 체크아웃
        uses: actions/checkout@v3
      
      - name: Node.js 설정
        uses: actions/setup-node@v3
        with:
          node-version: '16'
      
      - name: 의존성 설치 및 테스트 실행
        run: |
          npm install
          npm test
```

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → GitHub Actions의 개념과 기본 구조 이해  
2. **기본 실습** → YAML을 작성하고 간단한 CI/CD 파이프라인 실행  
3. **프로젝트 적용** → 실제 프로젝트에 GitHub Actions 적용  

---

## 📚 **5. 추천 리소스**
- **GitHub Actions 공식 문서:**  
  - [GitHub Actions Docs](https://docs.github.com/en/actions)  
  - [Workflow Syntax](https://docs.github.com/en/actions/using-workflows/workflow-syntax-for-github-actions)  

- **예제 및 템플릿:**  
  - [GitHub Actions Samples](https://github.com/actions)  
  - [Awesome GitHub Actions](https://github.com/sdras/awesome-actions)  

---

## ✅ **마무리**
이 문서는 **GitHub Actions의 기본 개념을 이해하고 간단한 워크플로우를 작성하는 방법을 학습하기 위한 가이드**입니다.  
다음 단계로 **고급 개념(Advanced)에서 매트릭스 빌드, 자체 호스팅 러너, 보안 강화 등**을 학습할 수 있습니다. 🚀