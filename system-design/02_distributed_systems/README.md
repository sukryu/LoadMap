# 📂 분산 시스템 - 02_distributed_systems

> **목표:**  
> - 분산 시스템의 핵심 개념과 아키텍처를 학습하고 실무에 적용할 수 있도록 한다.  
> - 합의 알고리즘, 일관성 모델, 분산 트랜잭션, 이벤트 기반 아키텍처 등을 이해하고 활용한다.  
> - 확장성과 가용성을 극대화하는 분산 시스템 설계를 연구한다.

---

## 📌 **디렉토리 구조**
```
02_distributed_systems/        # 분산 시스템 개념 학습
├── fundamentals/              # 분산 시스템 기초
├── consensus/                 # 합의 알고리즘
├── consistency/               # 일관성 모델
├── transactions/              # 분산 트랜잭션
├── event_driven/              # 이벤트 기반 아키텍처
├── distributed_storage/       # 분산 저장소
└── README.md
```

---

## 📖 **1. 개념 개요**
> **분산 시스템은 여러 개의 독립적인 컴퓨터가 네트워크를 통해 협력하여 하나의 시스템처럼 동작하는 구조이다.**

- ✅ **왜 중요한가?**  
  - 단일 서버 환경의 한계를 극복하고 대규모 트래픽을 처리하기 위해 필요하다.
  - 가용성, 확장성, 장애 복구 능력을 향상시키는 핵심 아키텍처이다.
  - 금융, 소셜 네트워크, 클라우드 서비스 등에서 필수적인 개념이다.

- ✅ **어떤 문제를 해결하는가?**  
  - 중앙 집중 시스템의 성능 한계 극복
  - 데이터 일관성 및 네트워크 장애 문제 해결
  - 확장성과 고가용성을 확보하여 트래픽 증가 대응

- ✅ **실무에서 어떻게 적용하는가?**  
  - 마이크로서비스 간의 데이터 공유 및 일관성 유지
  - 글로벌 서비스 운영을 위한 멀티 데이터센터 아키텍처 구축
  - 대규모 데이터 처리 및 분석을 위한 분산 저장소 활용

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **분산 시스템 기초 (fundamentals/)**
  - 분산 시스템의 정의 및 기본 원리
  - 분산 시스템의 장점과 단점

- **합의 알고리즘 (consensus/)**
  - Paxos, Raft 등 분산 환경에서의 합의 프로토콜
  - 리더 선출과 장애 복구 메커니즘

- **일관성 모델 (consistency/)**
  - CAP 이론과 PACELC 이론
  - 강한 일관성 vs 최종적 일관성
  - Eventual Consistency 적용 사례

- **분산 트랜잭션 (transactions/)**
  - 2PC (Two-Phase Commit), 3PC (Three-Phase Commit)
  - SAGA 패턴을 활용한 분산 트랜잭션 관리

- **이벤트 기반 아키텍처 (event_driven/)**
  - 메시지 큐(Kafka, RabbitMQ)를 활용한 비동기 시스템 설계
  - 이벤트 소싱(Event Sourcing)과 CQRS 패턴

- **분산 저장소 (distributed_storage/)**
  - NoSQL 데이터베이스(Cassandra, DynamoDB) 활용
  - 분산 파일 시스템(HDFS, Ceph) 구조와 활용 사례

---

## 🚀 **3. 실전 사례 분석**
> **대규모 서비스가 분산 시스템을 어떻게 활용하는가?**

- **Netflix** - 분산 시스템을 활용한 스트리밍 서비스 아키텍처
- **Google Spanner** - 글로벌 데이터 일관성을 유지하는 분산 데이터베이스
- **Amazon DynamoDB** - 확장성과 가용성을 극대화한 NoSQL 데이터베이스

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ 설계 패턴 학습  
3️⃣ 실제 사례 분석  
4️⃣ 코드 실습 진행  
5️⃣ 트레이드오프 분석  

---

## 📚 **5. 추천 리소스**
- 📖 _Designing Data-Intensive Applications_ - Martin Kleppmann  
- 📖 _Distributed Systems: Principles and Paradigms_ - Andrew S. Tanenbaum  
- 📖 _Site Reliability Engineering_ - Google SRE 팀  
- 📌 [The Raft Consensus Algorithm](https://raft.github.io/)  
- 📌 [Kafka: The Definitive Guide](https://www.confluent.io/resources/kafka-the-definitive-guide/)  

---

## ✅ **마무리**
이 문서는 **분산 시스템의 핵심 개념을 체계적으로 학습하는 단계**입니다.
이론 → 패턴 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며,
실무에서 확장성과 일관성을 고려한 분산 시스템을 설계할 수 있도록 합니다. 🚀

