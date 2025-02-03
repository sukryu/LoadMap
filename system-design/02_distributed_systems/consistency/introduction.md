# 일관성 모델 (consistency)

> **목표:**  
> - 분산 시스템에서 데이터 일관성(consistency)의 개념과 중요성을 학습한다.  
> - CAP 이론과 PACELC 이론을 이해하고, 실무에서 적용하는 방법을 연구한다.  
> - 강한 일관성(Strong Consistency)과 최종적 일관성(Eventual Consistency)의 트레이드오프를 분석한다.

---

## 1. 개념 개요

> **일관성 모델은 분산 시스템 내 여러 노드 간의 데이터 정합성을 유지하는 방법을 정의하는 개념이다.**

- **왜 중요한가?**  
  - 데이터 일관성이 보장되지 않으면 애플리케이션의 신뢰성이 떨어집니다.  
  - 네트워크 장애나 지연 상황에서도 올바른 데이터 제공이 필요합니다.  
  - 분산 데이터베이스, 마이크로서비스, 블록체인 등 다양한 환경에서 필수적으로 고려해야 할 요소입니다.

- **어떤 문제를 해결하는가?**  
  - 여러 노드에서 동일한 데이터를 일관되게 조회할 수 있도록 보장  
  - 네트워크 파티션 발생 시에도 안정적인 데이터 제공  
  - 지연(Latency)과 가용성(Availability) 사이의 균형을 맞추는 문제 해결

- **실무에서 어떻게 적용하는가?**  
  - **CAP 이론**을 기반으로 일관성 모델을 선택하여 시스템 설계  
  - **PACELC 이론**을 통해 성능과 일관성 간의 트레이드오프를 고려  
  - **분산 데이터베이스**(예: Cassandra, DynamoDB, Google Spanner)에서 실제 일관성 적용 사례를 분석

---

## 2. 학습 내용

### 주요 학습 주제

- **일관성 개요 (introduction.md):**  
  - 데이터 정합성을 유지하는 다양한 방법  
  - 일관성이 깨지는 원인과 이를 해결하는 전략

- **CAP 이론 (cap_theorem.md):**  
  - **Consistency (일관성):** 모든 노드가 동일한 데이터를 갖는 것  
  - **Availability (가용성):** 각 요청에 대해 항상 응답하는 것  
  - **Partition Tolerance (네트워크 파티션 허용):** 네트워크 분할 상황에서도 시스템이 동작하는 것  
  - CAP 정리가 분산 데이터베이스 설계에 미치는 영향과 실제 적용 사례

- **PACELC 이론 (pacelc_theorem.md):**  
  - CAP 이론을 보완하여, 네트워크 파티션이 발생하지 않는 정상 상황에서도 **Latency (지연)**와 **Consistency (일관성)** 사이의 트레이드오프를 고려하는 모델  
  - 실제 아키텍처 설계 시 PACELC 이론을 활용하는 방법

- **강한 일관성 (strong_consistency.md):**  
  - 모든 노드에서 즉각적으로 동일한 데이터를 제공하여, 읽기 작업 시 항상 최신 데이터를 보장  
  - 단점: 높은 네트워크 지연, 성능 저하 가능성  
  - Google Spanner, ZooKeeper 등에서 적용하는 사례

- **최종적 일관성 (eventual_consistency.md):**  
  - 시간이 지나면 데이터가 결국 모든 노드에서 일관되게 유지되는 모델  
  - 장점: 높은 성능과 가용성, 분산 시스템 확장에 유리  
  - 단점: 일시적으로 읽기 시 데이터 불일치 가능성  
  - Amazon DynamoDB, Apache Cassandra에서 적용된 사례

- **실무에서의 일관성 적용 (consistency_in_practice.md):**  
  - 일관성과 가용성 사이의 트레이드오프를 고려한 시스템 설계 방법  
  - 클라우드 환경(AWS, Google Cloud, Azure)에서의 일관성 구현 및 설정 방법  
  - 실제 프로젝트에서 일관성 모델을 어떻게 선택하고 적용하는지에 대한 사례 분석

---

## 3. 실전 사례 분석

> **대규모 시스템에서 일관성 모델이 어떻게 활용되는가?**

- **Google Spanner:**  
  - 강한 일관성을 유지하는 글로벌 데이터베이스로, 분산 트랜잭션 처리와 동기화에 중점을 둡니다.

- **Amazon DynamoDB:**  
  - 최종적 일관성을 적용하여 높은 성능과 확장성을 확보하는 NoSQL 데이터베이스로, 사용자가 일관성 수준을 선택할 수 있도록 지원합니다.

- **Apache Cassandra:**  
  - 튜너블 일관성을 제공하여, 사용자가 읽기 및 쓰기 작업에 대해 원하는 일관성 수준을 설정할 수 있도록 합니다.

---

## 4. 학습 방법

1. **개념 이론 학습:**  
   - 각 Markdown 파일(introduction.md, cap_theorem.md, pacelc_theorem.md, strong_consistency.md, eventual_consistency.md, consistency_in_practice.md)을 정독하여 기본 개념을 이해합니다.

2. **CAP & PACELC 이론 비교 분석:**  
   - 두 이론의 차이점과 각각의 트레이드오프를 분석하여, 시스템 설계 시 어떤 모델을 선택할지 결정합니다.

3. **실제 사례 분석:**  
   - Google Spanner, DynamoDB, Cassandra 등의 사례를 통해, 각 일관성 모델이 실제 서비스에서 어떻게 구현되고 있는지 학습합니다.

4. **실습:**  
   - 분산 데이터베이스 시뮬레이션이나, 간단한 클라우드 기반 프로젝트를 통해 일관성 모델을 적용해보고, 성능과 가용성에 미치는 영향을 체험합니다.

---

## 5. 추천 리소스

- 📖 _Designing Data-Intensive Applications_ - Martin Kleppmann  
- 📖 _Distributed Systems: Principles and Paradigms_ - Andrew S. Tanenbaum  
- 📖 _Google Spanner White Paper_ - Jeff Dean 외  
- 📌 [CAP Theorem Explained](https://www.scnsoft.com/blog/cap-theorem)  
- 📌 [PACELC Theorem Overview](https://dbmsmusings.blogspot.com/2010/04/problems-with-cap-and-yahoos-little.html)

---

## 6. 마무리

이 문서는 **분산 시스템에서 일관성을 유지하는 핵심 개념과 실무 적용 방법**을 학습하는 단계입니다.  
이론 학습, CAP 및 PACELC 이론 비교, 실전 사례 분석, 그리고 실습을 통해, 성능과 확장성을 고려한 최적의 일관성 모델을 설계할 수 있도록 합니다.  
분산 시스템 환경에서 데이터 정합성 유지가 얼마나 중요한지, 그리고 이를 위해 어떤 모델과 전략을 채택할 수 있는지 명확하게 이해하는 데 도움이 되기를 바랍니다.