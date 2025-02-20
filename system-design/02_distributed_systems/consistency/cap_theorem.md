# CAP 이론

> **목표:**  
> - 분산 시스템에서 데이터 정합성을 유지하기 위해 고려해야 할 세 가지 핵심 요소(Consistency, Availability, Partition Tolerance)를 이해한다.  
> - CAP 이론을 통해 분산 시스템 설계 시 발생하는 트레이드오프를 분석하고, 요구사항에 따른 최적의 설계 방향을 결정한다.

---

## 1. 개념 개요

CAP 이론은 Eric Brewer가 제시한 분산 시스템의 기본 원칙으로, 세 가지 속성—일관성(Consistency), 가용성(Availability), 네트워크 파티션 허용성(Partition Tolerance)—중에서 동시에 세 가지를 모두 완벽하게 보장할 수 없다는 점을 강조합니다.

- **Consistency (일관성):**  
  - 모든 노드가 동일한 데이터 상태를 유지해야 합니다.  
  - 클라이언트가 어떤 노드에 접근하더라도 같은 결과를 받아야 함을 의미합니다.

- **Availability (가용성):**  
  - 모든 요청에 대해 항상 응답을 제공해야 합니다.  
  - 일부 노드가 장애가 발생해도 전체 시스템은 계속해서 서비스를 제공해야 합니다.

- **Partition Tolerance (네트워크 파티션 허용성):**  
  - 네트워크 분할(파티션) 상황이 발생하더라도 시스템은 계속 동작해야 합니다.  
  - 분산 시스템에서는 네트워크 장애가 불가피하므로, 파티션 허용성은 필수적인 요소입니다.

---

## 2. CAP 이론의 트레이드오프

CAP 이론에 따르면, 네트워크 파티션이 발생할 경우 시스템은 **일관성(Consistency)**과 **가용성(Availability)** 중 하나를 선택해야 합니다.

- **CP (Consistency + Partition Tolerance):**  
  - 네트워크 파티션 상황에서도 데이터 일관성을 유지하는 데 초점을 맞춥니다.  
  - 단, 일부 요청에 대해 응답이 지연되거나 실패할 수 있습니다.  
  - 예: 전통적인 관계형 데이터베이스나 Google Spanner의 일부 구성

- **AP (Availability + Partition Tolerance):**  
  - 네트워크 파티션 상황에서도 모든 요청에 대해 응답을 제공하는 데 초점을 맞춥니다.  
  - 단, 응답 데이터가 최신 상태가 아닐 가능성이 있습니다(일시적인 불일치 발생).  
  - 예: 일부 NoSQL 데이터베이스(예: Cassandra, DynamoDB의 설정에 따라)

> **주의:**  
> 실제 분산 시스템 설계에서는 CAP 이론만으로 모든 요구사항을 해결하기 어려우며, PACELC 이론 등 추가적인 모델을 통해 지연(Latency)과 일관성의 균형을 더욱 세밀하게 고려할 필요가 있습니다.

---

## 3. 실무 적용 및 고려 사항

- **시스템 요구사항 분석:**  
  - 서비스의 특성과 사용 사례에 따라, 일관성을 우선할 것인지 가용성을 우선할 것인지 결정해야 합니다.
  
- **네트워크 환경:**  
  - 분산 시스템에서는 네트워크 장애나 지연이 불가피하므로, 파티션 허용성을 전제로 한 설계가 필요합니다.
  
- **트레이드오프 결정:**  
  - 금융 거래와 같이 높은 일관성이 요구되는 경우 CP 모델을, 소셜 네트워크나 캐싱 시스템 등에서는 AP 모델을 고려할 수 있습니다.
  
- **보완 이론:**  
  - PACELC 이론을 활용하여, 네트워크가 정상일 때의 지연(Latency)와 일관성 간의 트레이드오프도 함께 분석하는 것이 중요합니다.

---

## 4. 참고 자료

- **서적:**  
  - _Designing Data-Intensive Applications_ - Martin Kleppmann  
  - _Distributed Systems: Principles and Paradigms_ - Andrew S. Tanenbaum
- **온라인 자료:**  
  - [CAP Theorem Explained](https://www.scnsoft.com/blog/cap-theorem)  
  - [Understanding the CAP Theorem](https://www.infoq.com/articles/cap-twelve-years-later/)

---

## 5. 마무리

CAP 이론은 분산 시스템 설계의 핵심 개념으로, 일관성, 가용성, 그리고 네트워크 파티션 허용성 간의 본질적인 트레이드오프를 이해하는 데 도움을 줍니다.  
실제 시스템 설계 시, 서비스의 요구사항과 운영 환경을 고려하여 CP와 AP 중 어느 방향으로 균형을 맞출지 결정하고, 추가적으로 PACELC 이론을 통해 지연과 일관성의 균형도 세밀하게 조정할 필요가 있습니다.