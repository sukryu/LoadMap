# 📂 일관성 모델 - consistency

> **목표:**  
> - 분산 시스템에서 데이터 일관성(consistency)의 개념과 중요성을 학습한다.  
> - CAP 이론과 PACELC 이론을 이해하고 실무에서 적용하는 방법을 연구한다.  
> - 강한 일관성(Strong Consistency)과 최종적 일관성(Eventual Consistency)의 트레이드오프를 분석한다.

---

## 📌 **디렉토리 구조**
```
consistency/                    # 일관성 모델 학습
├── introduction.md              # 일관성 개요
├── cap_theorem.md               # CAP 이론
├── pacelc_theorem.md            # PACELC 이론
├── strong_consistency.md        # 강한 일관성
├── eventual_consistency.md      # 최종적 일관성
├── consistency_in_practice.md   # 실무에서의 일관성 적용
└── README.md
```

---

## 📖 **1. 개념 개요**
> **일관성 모델은 분산 시스템에서 여러 노드 간의 데이터 정합성을 유지하는 방법을 정의하는 개념이다.**

- ✅ **왜 중요한가?**  
  - 데이터 일관성이 보장되지 않으면 애플리케이션의 신뢰성이 낮아진다.
  - 네트워크 장애나 지연이 발생했을 때, 일관성을 유지하는 방법이 필요하다.
  - 분산 데이터베이스, 마이크로서비스, 블록체인에서 필수적인 개념이다.

- ✅ **어떤 문제를 해결하는가?**  
  - 여러 노드에서 동일한 데이터를 일관되게 조회할 수 있도록 보장
  - 네트워크 파티션이 발생할 경우에도 안정적인 데이터 제공
  - 지연 시간(Latency)과 가용성(Availability) 사이의 균형 유지

- ✅ **실무에서 어떻게 적용하는가?**  
  - **CAP 이론**을 기반으로 일관성 모델을 선택하여 시스템 설계
  - **PACELC 이론**을 통해 성능과 일관성 간의 트레이드오프 고려
  - **분산 데이터베이스**(Cassandra, DynamoDB, Spanner)에서 적용 사례 학습

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **일관성 개요 (introduction.md)**
  - 데이터 정합성을 유지하는 방법
  - 일관성이 깨지는 원인과 해결 방법

- **CAP 이론 (cap_theorem.md)**
  - Consistency(일관성), Availability(가용성), Partition Tolerance(네트워크 파티션 허용)
  - CAP 정리와 분산 데이터베이스에서의 적용 사례

- **PACELC 이론 (pacelc_theorem.md)**
  - CAP 이론을 보완하여 성능과 일관성 간의 균형을 분석하는 모델
  - PACELC의 실제 적용 예제 및 아키텍처 설계 고려 사항

- **강한 일관성 (strong_consistency.md)**
  - 모든 노드에서 동일한 데이터 보장을 위한 모델
  - 단점: 높은 네트워크 지연 및 성능 저하 가능성
  - Google Spanner, ZooKeeper의 강한 일관성 유지 기법

- **최종적 일관성 (eventual_consistency.md)**
  - 시간이 지나면 데이터가 결국 일관되게 유지되는 모델
  - 성능과 가용성이 높지만, 읽기 시 일관성이 깨질 가능성 존재
  - DynamoDB, Cassandra에서 적용 사례 분석

- **실무에서의 일관성 적용 (consistency_in_practice.md)**
  - 일관성과 가용성 사이의 트레이드오프 고려
  - 시스템 설계 시 어떤 일관성 모델을 선택할지 결정하는 방법
  - 클라우드 환경(AWS, Google Cloud, Azure)에서의 일관성 구현

---

## 🚀 **3. 실전 사례 분석**
> **대규모 시스템에서 일관성 모델이 어떻게 활용되는가?**

- **Google Spanner** - 강한 일관성을 유지하는 글로벌 데이터베이스
- **Amazon DynamoDB** - 최종적 일관성을 적용하여 확장성과 성능 확보
- **Apache Cassandra** - 튜너블 일관성(Tunable Consistency) 제공

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ CAP & PACELC 이론 비교 분석  
3️⃣ 실제 사례 분석  
4️⃣ 분산 데이터베이스에서의 일관성 모델 적용 실습  

---

## 📚 **5. 추천 리소스**
- 📖 _Designing Data-Intensive Applications_ - Martin Kleppmann  
- 📖 _Distributed Systems: Principles and Paradigms_ - Andrew S. Tanenbaum  
- 📖 _Google Spanner White Paper_ - Jeff Dean 외  
- 📌 [CAP Theorem Explained](https://www.scnsoft.com/blog/cap-theorem)  
- 📌 [PACELC Theorem Overview](https://dbmsmusings.blogspot.com/2010/04/problems-with-cap-and-yahoos-little.html)  

---

## ✅ **마무리**
이 문서는 **분산 시스템에서 일관성을 유지하는 핵심 개념과 실무 적용 방법을 학습하는 단계**입니다.
이론 → 일관성 모델 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며,
확장성과 성능을 고려한 최적의 일관성 모델을 설계할 수 있도록 합니다. 🚀

