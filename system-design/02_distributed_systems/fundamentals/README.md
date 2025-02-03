# 📂 분산 시스템 기초 - fundamentals

> **목표:**  
> - 분산 시스템의 기본 개념과 원리를 이해한다.  
> - 분산 환경에서의 주요 설계 원칙과 문제점을 학습한다.  
> - 확장성과 가용성을 고려한 시스템 설계를 위한 기초 지식을 습득한다.

---

## 📌 **디렉토리 구조**
```
fundamentals/                   # 분산 시스템 기초
├── introduction.md             # 분산 시스템 개요
├── advantages_disadvantages.md # 분산 시스템의 장점과 단점
├── design_principles.md        # 분산 시스템 설계 원칙
├── failure_models.md           # 장애 모델 및 장애 대응 전략
└── README.md
```

---

## 📖 **1. 개념 개요**
> **분산 시스템은 여러 개의 독립적인 컴퓨터가 네트워크를 통해 협력하여 하나의 시스템처럼 동작하는 구조이다.**

- ✅ **왜 중요한가?**  
  - 단일 서버의 한계를 극복하고 대규모 트래픽을 처리하기 위해 필요하다.
  - 시스템 가용성을 높이고 장애 복구 능력을 강화할 수 있다.
  - 금융, 소셜 네트워크, 클라우드 서비스 등에서 필수적으로 사용된다.

- ✅ **어떤 문제를 해결하는가?**  
  - 중앙 집중형 시스템의 성능 및 확장성 한계를 극복
  - 네트워크 장애 및 서버 장애 시 데이터 손실을 최소화
  - 전 세계적으로 일관된 데이터 처리를 위한 아키텍처 제공

- ✅ **실무에서 어떻게 적용하는가?**  
  - 데이터베이스 샤딩 및 복제 전략을 활용한 고성능 데이터 저장소 설계
  - 클라우드 환경에서의 분산 컴퓨팅을 통해 글로벌 서비스 운영
  - 장애 대응 및 복구를 위한 페일오버(Failover) 및 로드 밸런싱 적용

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **분산 시스템 개요 (introduction.md)**
  - 분산 시스템의 정의 및 기본 개념
  - 중앙 집중 시스템과의 비교

- **분산 시스템의 장점과 단점 (advantages_disadvantages.md)**
  - 확장성, 가용성 증가 등의 이점
  - 네트워크 지연, 데이터 일관성 문제 등 단점 분석

- **분산 시스템 설계 원칙 (design_principles.md)**
  - CAP 이론 및 PACELC 이론
  - 강한 일관성 vs 최종적 일관성
  - 데이터 샤딩 및 복제 전략

- **장애 모델 및 장애 대응 전략 (failure_models.md)**
  - 네트워크 파티션과 장애 모델(Fail-stop, Byzantine)
  - 장애 감지 및 복구 방법
  - 시스템 신뢰성을 높이는 디자인 패턴

---

## 🚀 **3. 실전 사례 분석**
> **대규모 서비스에서 분산 시스템 기초 개념이 어떻게 활용되는가?**

- **Google** - 전 세계적으로 데이터 일관성을 유지하는 Google Spanner 활용
- **Amazon DynamoDB** - 최종적 일관성을 적용한 NoSQL 데이터베이스
- **Netflix** - 클라우드 네이티브 분산 아키텍처를 통한 글로벌 확장성 확보

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ 분산 시스템 설계 원칙 및 트레이드오프 이해  
3️⃣ 실제 사례 분석  
4️⃣ 코드 실습 진행  

---

## 📚 **5. 추천 리소스**
- 📖 _Designing Data-Intensive Applications_ - Martin Kleppmann  
- 📖 _Distributed Systems: Principles and Paradigms_ - Andrew S. Tanenbaum  
- 📖 _Site Reliability Engineering_ - Google SRE 팀  
- 📌 [CAP Theorem Explained](https://www.scnsoft.com/blog/cap-theorem)  
- 📌 [Distributed Systems Theory](https://distributed.systems/)  

---

## ✅ **마무리**
이 문서는 **분산 시스템의 기초 개념과 실무 적용 방법을 학습하는 단계**입니다. 
이론 → 설계 원칙 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며, 
확장성과 가용성을 고려한 분산 시스템 설계를 할 수 있도록 합니다. 🚀