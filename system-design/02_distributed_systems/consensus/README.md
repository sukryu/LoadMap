# 📂 합의 알고리즘 - consensus

> **목표:**  
> - 분산 시스템에서의 합의(consensus) 개념과 필요성을 이해한다.  
> - Paxos, Raft 등의 대표적인 합의 알고리즘을 학습하고 비교한다.  
> - 리더 선출, 장애 복구, 분산 트랜잭션에서의 합의 문제를 해결하는 방법을 연구한다.

---

## 📌 **디렉토리 구조**
```
consensus/                     # 합의 알고리즘 학습
├── introduction.md             # 합의 알고리즘 개요
├── paxos.md                    # Paxos 알고리즘
├── raft.md                     # Raft 알고리즘
├── leader_election.md          # 리더 선출 기법
├── consensus_in_blockchain.md  # 블록체인에서의 합의 알고리즘
└── README.md
```

---

## 📖 **1. 개념 개요**
> **합의 알고리즘은 분산 시스템에서 노드들이 하나의 일관된 결정을 내리도록 보장하는 기법이다.**

- ✅ **왜 중요한가?**  
  - 노드 간 데이터 일관성을 유지하기 위한 핵심 요소이다.
  - 장애 발생 시에도 신뢰할 수 있는 결정을 내릴 수 있도록 보장한다.
  - 블록체인, 분산 데이터베이스, 마이크로서비스 환경에서 필수적인 개념이다.

- ✅ **어떤 문제를 해결하는가?**  
  - 네트워크 단절, 메시지 지연, 장애 발생 시 데이터 불일치 문제 해결
  - 분산 환경에서 신뢰할 수 있는 단일 결정을 내리는 방법 제공
  - 리더 선출 및 데이터 복제 과정에서의 충돌 방지

- ✅ **실무에서 어떻게 적용하는가?**  
  - **Paxos, Raft**를 활용한 분산 데이터베이스 트랜잭션 처리
  - **Kafka, ZooKeeper**에서 리더 선출 및 분산 환경 동기화
  - **블록체인**에서 PoW, PoS 등의 합의 알고리즘을 활용하여 신뢰성 보장

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **합의 알고리즘 개요 (introduction.md)**
  - 합의 문제(Consensus Problem)란 무엇인가?
  - CAP 이론과 합의 알고리즘의 역할

- **Paxos 알고리즘 (paxos.md)**
  - 분산 환경에서의 합의를 위한 최초의 알고리즘 중 하나
  - 프로포저(Proposer), 어셉터(Acceptor), 러너(Learner) 역할
  - Paxos 변형(Simple Paxos, Multi-Paxos) 비교

- **Raft 알고리즘 (raft.md)**
  - 리더 기반 합의 알고리즘으로 Paxos보다 이해하기 쉬운 구조
  - 리더 선출 및 로그 복제 과정
  - Raft와 Paxos의 비교 분석

- **리더 선출 기법 (leader_election.md)**
  - 분산 시스템에서 리더 선출이 필요한 이유
  - ZooKeeper의 ZAB 프로토콜과 Kafka의 리더 선출 방식
  - 선출된 리더의 장애 처리 전략

- **블록체인에서의 합의 알고리즘 (consensus_in_blockchain.md)**
  - PoW(Proof of Work), PoS(Proof of Stake), BFT(Byzantine Fault Tolerance)
  - 비잔틴 장애 허용과 합의 알고리즘의 관계
  - 블록체인 환경에서 합의 알고리즘의 역할과 적용

---

## 🚀 **3. 실전 사례 분석**
> **대규모 시스템에서 합의 알고리즘이 어떻게 활용되는가?**

- **Google Spanner** - Paxos를 활용한 글로벌 데이터베이스 동기화
- **Apache Kafka** - 리더 선출을 위한 ZooKeeper 활용
- **Ethereum** - PoS 기반 블록체인 합의 알고리즘 적용

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ 주요 합의 알고리즘 비교 및 실습  
3️⃣ 실제 사례 분석  
4️⃣ 코드 실습 진행 및 트레이드오프 분석  

---

## 📚 **5. 추천 리소스**
- 📖 _Understanding Distributed Systems_ - Roberto Vitillo  
- 📖 _Distributed Systems: Principles and Paradigms_ - Andrew S. Tanenbaum  
- 📖 _Raft: In Search of an Understandable Consensus Algorithm_ - Diego Ongaro  
- 📌 [The Raft Consensus Algorithm](https://raft.github.io/)  
- 📌 [Paxos vs. Raft: Comparing Consensus Protocols](https://www.oreilly.com/library/view/designing-data-intensive-applications/9781491903063/)  

---

## ✅ **마무리**
이 문서는 **분산 시스템에서 합의 알고리즘의 핵심 개념과 실무 적용 방법을 학습하는 단계**입니다.
이론 → 합의 알고리즘 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며,
분산 환경에서 신뢰할 수 있는 합의를 수행하는 방법을 익힐 수 있도록 합니다. 🚀

