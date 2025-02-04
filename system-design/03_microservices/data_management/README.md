# 📂 데이터 관리 - data_management

> **목표:**  
> - 마이크로서비스 아키텍처에서 데이터 관리의 핵심 개념과 전략을 학습한다.  
> - 서비스별 데이터 분리, CQRS, 이벤트 소싱 등의 기법을 이해하고 적용한다.  
> - 확장성과 성능을 고려한 데이터 관리 방식을 연구하고 실무에 적용한다.

---

## 📌 **디렉토리 구조**
```
data_management/                # 데이터 관리 학습
├── introduction.md             # 마이크로서비스 데이터 관리 개요
├── database_per_service.md     # 서비스별 데이터베이스 분리 전략
├── shared_database.md          # 공유 데이터베이스 접근 방식
├── cqrs.md                     # CQRS (Command Query Responsibility Segregation)
├── event_sourcing.md           # 이벤트 소싱 (Event Sourcing)
├── data_consistency.md         # 데이터 정합성 유지 전략
├── data_management_in_practice.md # 실무에서의 데이터 관리 적용
└── README.md
```

---

## 📖 **1. 개념 개요**
> **마이크로서비스 환경에서는 각 서비스가 독립적으로 데이터 관리를 수행해야 하며, 데이터 정합성을 유지하면서 확장성과 성능을 고려해야 한다.**

- ✅ **왜 중요한가?**  
  - 서비스 간 강한 결합을 줄이고 독립적인 확장을 가능하게 한다.
  - 데이터 정합성을 유지하면서 성능을 최적화할 수 있다.
  - 마이크로서비스 간의 데이터 통합 및 공유 문제를 해결할 수 있다.

- ✅ **어떤 문제를 해결하는가?**  
  - 단일 데이터베이스 사용으로 인해 발생하는 성능 병목 해결
  - 마이크로서비스 간의 데이터 일관성 유지
  - 확장성과 장애 복구를 고려한 데이터 저장 및 관리

- ✅ **실무에서 어떻게 적용하는가?**  
  - **서비스별 데이터베이스**를 독립적으로 관리하여 성능 최적화
  - **CQRS 및 이벤트 소싱**을 활용하여 읽기/쓰기 성능 분리 및 데이터 추적 가능성 향상
  - **분산 트랜잭션 패턴**을 적용하여 데이터 정합성 유지

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **마이크로서비스 데이터 관리 개요 (introduction.md)**
  - 데이터 저장 방식 및 주요 개념
  - 트랜잭션 처리와 정합성 유지 개념

- **서비스별 데이터베이스 분리 (database_per_service.md)**
  - 각 서비스가 자체 데이터베이스를 가지는 모델
  - 데이터 분할 전략 및 장단점 분석

- **공유 데이터베이스 접근 방식 (shared_database.md)**
  - 여러 서비스가 동일한 데이터베이스를 공유하는 모델
  - 단점: 서비스 간 결합도 증가, 성능 병목 발생 가능
  - 사용 사례 및 해결 방법

- **CQRS (cqrs.md)**
  - 명령(Command)과 조회(Query) 작업을 분리하여 성능 최적화
  - CQRS 적용 시 고려할 요소 및 구현 방식

- **이벤트 소싱 (event_sourcing.md)**
  - 데이터 변경 이력을 이벤트로 저장하여 상태를 추적 가능하게 함
  - 이벤트 로그 기반의 데이터 복구 및 롤백 전략

- **데이터 정합성 유지 전략 (data_consistency.md)**
  - 강한 정합성 vs 최종적 정합성
  - 분산 트랜잭션 (2PC, SAGA) 패턴 활용
  - 데이터 샤딩 및 복제 전략

- **실무에서의 데이터 관리 적용 (data_management_in_practice.md)**
  - 기업에서의 데이터 관리 전략 사례
  - 클라우드 환경(AWS, Google Cloud, Azure)에서의 데이터 관리 최적화
  - 성능 테스트 및 모니터링 적용 사례

---

## 🚀 **3. 실전 사례 분석**
> **대규모 서비스에서 데이터 관리 전략이 어떻게 활용되는가?**

- **Netflix** - NoSQL 데이터베이스를 활용한 확장 가능한 데이터 저장 전략
- **Amazon DynamoDB** - 이벤트 소싱과 CQRS를 활용한 데이터 처리
- **Uber** - 분산 트랜잭션 및 강한 정합성 유지 전략 적용

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ CQRS 및 이벤트 소싱 실습  
3️⃣ 실제 사례 연구  
4️⃣ 데이터 관리 방식 설계 및 코드 작성  

---

## 📚 **5. 추천 리소스**
- 📖 _Designing Data-Intensive Applications_ - Martin Kleppmann  
- 📖 _Building Microservices_ - Sam Newman  
- 📖 _Microservices Patterns_ - Chris Richardson  
- 📌 [CQRS Pattern Overview](https://martinfowler.com/bliki/CQRS.html)  
- 📌 [Event Sourcing Explained](https://martinfowler.com/eaaDev/EventSourcing.html)  

---

## ✅ **마무리**
이 문서는 **마이크로서비스 아키텍처에서 데이터 관리를 위한 다양한 전략을 학습하는 단계**입니다.
이론 → 데이터 저장 방식 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며,
확장성과 성능을 고려한 최적의 데이터 관리 방식을 설계할 수 있도록 합니다. 🚀

