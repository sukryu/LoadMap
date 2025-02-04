# 📂 GitHub Actions 학습 개요

> **목표:**  
> - **GitHub Actions의 기본 개념과 실무 적용 방법을 학습**한다.  
> - **CI/CD 파이프라인을 구축하고 자동화하는 방법을 익힌다.**  
> - **기본 개념과 명령어를 학습한 후, 고급 기능 및 실무 활용 전략을 학습한다.**  
> - **이론 → 도구 실습 → 프로젝트 적용 → 사례 분석의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **GitHub Actions 학습을 기본(Basic)과 고급(Advanced)으로 나누어 진행합니다.**  

```
github-actions/
├── basic
│   ├── introduction.md    # GitHub Actions 개요 및 기본 개념
│   ├── workflow-basics.md # 기본적인 워크플로우 구성 및 실행
│   ├── actions-usage.md   # Actions 사용법 및 예제
│   └── README.md
│
├── advanced
│   ├── custom-actions.md    # 사용자 정의 Actions 개발
│   ├── matrix-builds.md     # 매트릭스 빌드 및 병렬 실행
│   ├── self-hosted-runners.md # 자체 호스팅 러너 사용법
│   ├── security-best-practices.md # 보안 및 권한 관리
│   ├── deployment-strategies.md # 실무 CI/CD 배포 전략
│   └── README.md
```

---

## 📖 **1. 기본 개념 개요**
> **GitHub Actions는 GitHub 저장소에서 자동화된 CI/CD 워크플로우를 설정할 수 있도록 지원하는 기능입니다.**

- ✅ **GitHub Actions의 동작 방식**  
- ✅ **워크플로우(Workflow), 이벤트(Event), 잡(Job), 스텝(Step)의 개념 이해**  
- ✅ **YAML을 활용한 기본적인 GitHub Actions 스크립트 작성**  
- ✅ **기본적인 CI/CD 구축 (코드 빌드, 테스트, 배포)**  

---

## 🏗 **2. 학습 내용**
### 📌 Basic (기본 개념 및 활용)
- **GitHub Actions의 기본 개념 이해**
- **워크플로우 구성 요소 및 기본 실행 방법**
- **기본적인 YAML 작성 및 실행 테스트**

### 📌 Advanced (고급 개념 및 실무 적용)
- **커스텀 액션 개발 및 재사용성 증가**
- **매트릭스 빌드를 활용한 다중 환경 테스트**
- **자체 호스팅 러너를 활용한 성능 최적화**
- **보안 및 권한 관리, 비밀값 처리**
- **실무에서의 CI/CD 배포 전략 (Blue-Green, Canary 배포 등)**

---

## 🚀 **3. 실전 사례 분석**
> **GitHub Actions를 활용하여 실제 프로젝트에서 CI/CD를 운영하는 사례를 분석합니다.**

- **Netflix** - GitHub Actions를 활용한 마이크로서비스 빌드 자동화  
- **Shopify** - GitHub Actions 기반의 CI/CD 파이프라인 운영  
- **Microsoft** - 다중 환경을 지원하는 매트릭스 빌드 적용  

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → GitHub Actions 개념과 구조 이해  
2. **도구 실습** → 기본 및 고급 기능을 실습하며 익히기  
3. **프로젝트 적용** → 실제 프로젝트에 GitHub Actions 적용  
4. **사례 분석** → 다양한 기업의 GitHub Actions 활용 사례 연구  

---

## 📚 **5. 추천 리소스**
- **GitHub Actions 공식 문서:**  
  - [GitHub Actions Docs](https://docs.github.com/en/actions)  
  - [Workflow Syntax](https://docs.github.com/en/actions/using-workflows/workflow-syntax-for-github-actions)  

- **GitHub Actions 예제:**  
  - [Awesome GitHub Actions](https://github.com/sdras/awesome-actions)  
  - [GitHub Actions Templates](https://github.com/actions)  

---

## ✅ **마무리**
이 문서는 **GitHub Actions의 기본 개념부터 실무 활용까지 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 사례 분석**의 단계로 학습하며, **실무에서 GitHub Actions를 효과적으로 활용하는 방법**을 다룹니다. 🚀