# 📂 분산 트랜잭션 - transactions

> **목표:**  
> - 분산 시스템에서 트랜잭션의 개념과 중요성을 학습한다.  
> - Two-Phase Commit (2PC), Three-Phase Commit (3PC) 등의 분산 트랜잭션 알고리즘을 이해한다.  
> - SAGA 패턴을 활용한 트랜잭션 관리 및 실무 적용 방법을 연구한다.

---

## 📌 **디렉토리 구조**
```
transactions/                   # 분산 트랜잭션 학습
├── introduction.md              # 분산 트랜잭션 개요
├── two_phase_commit.md          # 2PC (Two-Phase Commit)
├── three_phase_commit.md        # 3PC (Three-Phase Commit)
├── saga_pattern.md              # SAGA 패턴
├── transaction_isolation.md      # 트랜잭션 격리 수준
├── transactions_in_practice.md   # 실무에서의 분산 트랜잭션 적용
└── README.md
```

---

## 📖 **1. 개념 개요**
> **분산 트랜잭션은 여러 개의 독립적인 노드에서 원자성(Atomicity)을 유지하며 데이터 변경을 수행하는 기법이다.**

- ✅ **왜 중요한가?**  
  - 분산 환경에서 데이터 정합성을 유지하는 핵심 요소이다.
  - 장애 발생 시 데이터 무결성을 보장해야 한다.
  - 금융, 전자상거래, 클라우드 기반 애플리케이션 등에서 필수적인 개념이다.

- ✅ **어떤 문제를 해결하는가?**  
  - 분산 환경에서 원자성(Atomicity) 보장
  - 트랜잭션 간 충돌 방지 및 데이터 정합성 유지
  - 장애 복구 및 롤백을 통해 데이터 무결성 유지

- ✅ **실무에서 어떻게 적용하는가?**  
  - **2PC/3PC**를 활용한 금융 및 결제 시스템 설계
  - **SAGA 패턴**을 활용하여 마이크로서비스 간 트랜잭션 관리
  - **트랜잭션 격리 수준**을 고려하여 동시성 문제 해결

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **분산 트랜잭션 개요 (introduction.md)**
  - 트랜잭션의 기본 원칙(ACID)
  - 단일 데이터베이스 트랜잭션과 분산 트랜잭션의 차이

- **Two-Phase Commit (2PC) (two_phase_commit.md)**
  - 분산 환경에서 트랜잭션을 커밋하는 2단계 프로토콜
  - Coordinator와 Participant의 역할
  - 단점: Coordinator 장애 시 블로킹 문제 발생

- **Three-Phase Commit (3PC) (three_phase_commit.md)**
  - 2PC의 블로킹 문제를 해결하기 위해 추가된 3단계 프로토콜
  - 네트워크 파티션 발생 시의 대처 방법
  - 단점: 네트워크 비용 증가

- **SAGA 패턴 (saga_pattern.md)**
  - 롱 러닝 트랜잭션을 관리하기 위한 분산 트랜잭션 패턴
  - 보상 트랜잭션(Compensating Transaction) 개념
  - 마이크로서비스에서 SAGA 패턴 활용 방법

- **트랜잭션 격리 수준 (transaction_isolation.md)**
  - Read Uncommitted, Read Committed, Repeatable Read, Serializable 비교
  - 분산 환경에서의 트랜잭션 격리 고려 사항
  - 데이터 충돌 방지 및 동시성 문제 해결

- **실무에서의 분산 트랜잭션 적용 (transactions_in_practice.md)**
  - 분산 데이터베이스에서 트랜잭션 처리 전략
  - 글로벌 트랜잭션 vs 로컬 트랜잭션 비교
  - Kafka, RabbitMQ 등을 활용한 이벤트 기반 트랜잭션 처리

---

## 🚀 **3. 실전 사례 분석**
> **대규모 시스템에서 분산 트랜잭션이 어떻게 활용되는가?**

- **Google Spanner** - 글로벌 분산 트랜잭션을 위한 강한 일관성 제공
- **Amazon DynamoDB** - SAGA 패턴을 활용한 트랜잭션 관리
- **Uber** - 마이크로서비스 간 분산 트랜잭션 처리 전략

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ 2PC & 3PC 비교 분석  
3️⃣ SAGA 패턴 적용 사례 연구  
4️⃣ 분산 트랜잭션 코드 실습 및 트레이드오프 분석  

---

## 📚 **5. 추천 리소스**
- 📖 _Designing Data-Intensive Applications_ - Martin Kleppmann  
- 📖 _Distributed Systems: Principles and Paradigms_ - Andrew S. Tanenbaum  
- 📖 _Database Internals_ - Alex Petrov  
- 📌 [Two-Phase Commit Explained](https://www.ibm.com/docs/en/cics-ts/5.3?topic=processing-two-phase-commit)
- 📌 [SAGA Pattern in Microservices](https://microservices.io/patterns/data/saga.html)  

---

## ✅ **마무리**
이 문서는 **분산 시스템에서 트랜잭션을 유지하는 핵심 개념과 실무 적용 방법을 학습하는 단계**입니다.
이론 → 트랜잭션 모델 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며,
확장성과 성능을 고려한 분산 트랜잭션 설계를 할 수 있도록 합니다. 🚀

