# 📂 Nexus Repository - Basic 학습 개요

> **목표:**  
> - **Nexus Repository의 기본 개념과 기초적인 사용법을 학습**한다.  
> - **패키지 및 아티팩트 관리 방식을 이해하고 활용 방법을 익힌다.**  
> - **기본적인 리포지토리 생성 및 운영 방법을 실습한다.**  
> - **이론 → 실습 → 프로젝트 적용의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **Nexus의 기초 개념을 이해하고 기본 명령어를 학습합니다.**  

```
basic/
├── introduction.md    # Nexus 개요 및 기본 개념
├── repository-basics.md # 기본적인 리포지토리 설정 및 운영
├── artifact-management.md  # 아티팩트 관리 및 저장소 활용
└── README.md
```

---

## 📖 **1. 기본 개념 개요**
> **Nexus Repository는 패키지 및 아티팩트를 중앙에서 관리하는 저장소 역할을 합니다.**

- ✅ **리포지토리(Repository):** 패키지를 저장하는 공간  
- ✅ **아티팩트(Artifact):** 빌드된 결과물(예: JAR, Docker 이미지)  
- ✅ **호스팅 리포지토리(Hosted Repository):** 내부에서 직접 관리하는 저장소  
- ✅ **프록시 리포지토리(Proxy Repository):** 외부 저장소를 캐싱하여 성능 향상  
- ✅ **그룹 리포지토리(Group Repository):** 여러 개의 리포지토리를 하나의 엔드포인트로 통합  

---

## 🏗 **2. 학습 내용**
### 📌 Introduction (Nexus 소개)
- **Nexus Repository란 무엇인가?**
- **CI/CD 환경에서의 Nexus의 역할**

### 📌 Repository Basics (기본 리포지토리 이해)
- **Nexus에서 리포지토리 생성 및 관리 방법**
- **Hosted, Proxy, Group Repository의 차이점**
- **리포지토리 접근 제어 및 권한 설정**

### 📌 Artifact Management (아티팩트 관리)
- **Maven, npm, Docker 등 다양한 패키지 관리 방법**
- **아티팩트 업로드 및 다운로드 실습**
- **리포지토리 정리 및 유지 관리**

---

## 🚀 **3. 실전 예제**
> **Nexus Repository를 활용한 간단한 패키지 업로드 및 다운로드 실습을 진행합니다.**

```sh
# Nexus에 Maven 아티팩트 업로드
mvn deploy -DaltDeploymentRepository=nexus-releases::default::http://localhost:8081/repository/maven-releases/

# Nexus에서 아티팩트 다운로드
curl -O http://localhost:8081/repository/maven-releases/com/example/app/1.0.0/app-1.0.0.jar
```

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → Nexus의 개념과 기본 구조 이해  
2. **기본 실습** → 리포지토리를 생성하고 패키지 업로드 및 다운로드  
3. **프로젝트 적용** → 실제 프로젝트에서 Nexus 활용  

---

## 📚 **5. 추천 리소스**
- **Nexus Repository 공식 문서:**  
  - [Nexus Repository Docs](https://help.sonatype.com/repomanager3)  

- **예제 및 템플릿:**  
  - [Awesome Nexus](https://github.com/sonatype/awesome-nexus)  
  - [Nexus Repository Examples](https://github.com/sonatype/nexus-examples)  

---

## ✅ **마무리**
이 문서는 **Nexus Repository의 기본 개념을 이해하고 간단한 리포지토리 운영 및 아티팩트 관리를 실습하는 방법을 학습하기 위한 가이드**입니다.  
다음 단계로 **고급 개념(Advanced)에서 사용자 정의 리포지토리 설정, 프록시 리포지토리 운영 등을 학습할 수 있습니다.** 🚀

