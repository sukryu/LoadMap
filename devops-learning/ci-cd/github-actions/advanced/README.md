# 📂 GitHub Actions - Advanced 학습 개요

> **목표:**  
> - **GitHub Actions의 고급 개념과 실무 활용법을 학습**한다.  
> - **매트릭스 빌드, 커스텀 액션, 자체 호스팅 러너 등을 활용하여 효율적인 CI/CD 파이프라인을 구축한다.**  
> - **보안 및 권한 관리, 배포 전략을 익혀 실무에서 활용할 수 있도록 한다.**  
> - **이론 → 실습 → 프로젝트 적용 → 최적화의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **GitHub Actions의 고급 개념을 체계적으로 학습합니다.**  

```
advanced/
├── custom-actions.md    # 사용자 정의 Actions 개발
├── matrix-builds.md     # 매트릭스 빌드 및 병렬 실행
├── self-hosted-runners.md # 자체 호스팅 러너 사용법
├── security-best-practices.md # 보안 및 권한 관리
├── deployment-strategies.md # 실무 CI/CD 배포 전략
└── README.md
```

---

## 📖 **1. 고급 개념 개요**
> **GitHub Actions의 고급 기능을 활용하면 대규모 프로젝트에서도 자동화된 CI/CD를 더욱 강력하게 운영할 수 있습니다.**

- ✅ **커스텀 액션(Custom Actions):** 자체 제작한 GitHub Actions을 만들어 재사용  
- ✅ **매트릭스 빌드(Matrix Builds):** 다양한 환경에서 동시 테스트 수행  
- ✅ **자체 호스팅 러너(Self-Hosted Runners):** 로컬 또는 클라우드에서 커스텀 실행 환경 활용  
- ✅ **보안 강화(Security Best Practices):** CI/CD 파이프라인 보안 및 접근 제어  
- ✅ **배포 전략(Deployment Strategies):** Blue-Green, Canary, Rolling 배포 적용  

---

## 🏗 **2. 학습 내용**
### 📌 Custom Actions (사용자 정의 액션)
- **Docker 기반 및 JavaScript 기반 커스텀 액션 개발**
- **GitHub Marketplace에 액션 배포하기**
- **커스텀 액션을 활용한 반복 작업 자동화**

### 📌 Matrix Builds (매트릭스 빌드)
- **다양한 OS 및 환경에서 테스트 실행**
- **Node.js, Python, Java 등 멀티 플랫폼 빌드 전략**
- **병렬 실행을 통한 테스트 최적화**

### 📌 Self-Hosted Runners (자체 호스팅 러너)
- **자체 호스팅 러너 설치 및 구성**
- **온프레미스 또는 클라우드에서 실행 환경 구축**
- **성능 및 비용 최적화 전략**

### 📌 Security Best Practices (보안 및 권한 관리)
- **GitHub Secrets 및 환경 변수 관리**
- **워크플로우 권한 제어 및 보안 설정**
- **GitHub Actions의 안전한 실행을 위한 모범 사례**

### 📌 Deployment Strategies (배포 전략)
- **Blue-Green 배포, Canary 배포, Rolling 업데이트 적용**
- **GitHub Actions를 활용한 Kubernetes 배포 자동화**
- **AWS, Azure, GCP를 활용한 멀티 클라우드 배포**

---

## 🚀 **3. 실전 예제**
> **고급 GitHub Actions 기능을 활용한 실전 예제를 학습합니다.**

```yaml
name: Advanced GitHub Actions Example

on: [push]

jobs:
  build:
    runs-on: ubuntu-latest
    strategy:
      matrix:
        node-version: [14, 16, 18]
        os: [ubuntu-latest, windows-latest]
    steps:
      - name: 저장소 체크아웃
        uses: actions/checkout@v3
      
      - name: Node.js 설정
        uses: actions/setup-node@v3
        with:
          node-version: ${{ matrix.node-version }}
      
      - name: 의존성 설치 및 테스트 실행
        run: |
          npm install
          npm test
```

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → GitHub Actions의 고급 기능 이해  
2. **실습 진행** → 매트릭스 빌드, 커스텀 액션, 보안 설정 실습  
3. **프로젝트 적용** → 실무 CI/CD 파이프라인 구축 및 최적화  
4. **최적화 연구** → 성능, 보안, 비용 측면에서 효율성 개선  

---

## 📚 **5. 추천 리소스**
- **GitHub Actions 공식 문서:**  
  - [GitHub Actions Docs](https://docs.github.com/en/actions)  
  - [Workflow Syntax](https://docs.github.com/en/actions/using-workflows/workflow-syntax-for-github-actions)  

- **고급 GitHub Actions 예제:**  
  - [Awesome GitHub Actions](https://github.com/sdras/awesome-actions)  
  - [GitHub Actions Advanced Templates](https://github.com/actions)  

---

## ✅ **마무리**
이 문서는 **GitHub Actions의 고급 기능을 학습하고 실무에 적용할 수 있도록 구성된 가이드**입니다.  
기본 개념을 익힌 후, **매트릭스 빌드, 자체 호스팅 러너, 보안 설정, 배포 전략 등 고급 기능을 활용하여 CI/CD를 최적화**할 수 있습니다. 🚀