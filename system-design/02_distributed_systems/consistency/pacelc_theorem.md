# PACELC 이론

> **목표:**  
> - PACELC 이론의 기본 개념과 필요성을 이해한다.  
> - 네트워크 파티션 발생 여부에 따른 지연(Latency)과 일관성(Consistency) 사이의 트레이드오프를 분석한다.  
> - 분산 시스템 설계 시, CAP 이론을 보완하는 추가 고려사항으로 PACELC 이론을 적용하는 방법을 학습한다.

---

## 1. 개념 개요

PACELC 이론은 Eric Brewer의 CAP 이론을 확장한 모델로, 네트워크 파티션이 발생할 때(Partition)와 발생하지 않을 때(Else)에 각각 다른 트레이드오프를 고려해야 함을 설명합니다.

- **P – Partition Tolerance (파티션 허용성):**  
  - 네트워크 분할 상황에서는 시스템이 계속 동작하기 위해 파티션 허용성을 전제로 해야 합니다.

- **A – Availability (가용성):**  
  - 파티션 상황에서 시스템이 응답을 계속 제공해야 하며, 일관성을 어느 정도 희생할 수 있습니다.

- **C – Consistency (일관성):**  
  - 파티션 상황에서 모든 노드가 동일한 상태를 유지하는 것을 목표로 할 수 있으나, 그에 따른 응답 지연이 발생할 수 있습니다.

- **EL – Else Latency (정상 상황의 지연):**  
  - 네트워크 파티션이 발생하지 않는 정상 상황에서는, 일관성을 유지하기 위해 발생하는 지연(Latency)을 고려해야 합니다.

- **C – Consistency (일관성):**  
  - 정상 상황에서도 강한 일관성을 유지할 경우 추가적인 지연이 발생할 수 있으며, 이를 포기하고 최종적 일관성을 선택할 수도 있습니다.

> **핵심 메시지:**  
> 네트워크 파티션이 발생할 때는 Availability와 Consistency 사이의 트레이드오프가, 파티션이 발생하지 않는 정상 상황에서는 Latency와 Consistency 사이의 트레이드오프가 존재한다는 점을 강조합니다.

---

## 2. PACELC 이론의 트레이드오프 분석

PACELC 이론은 두 가지 상황으로 나눕니다:

### 2.1 Partition 상황 (P)

- **P → A or C:**  
  - 네트워크 파티션이 발생했을 때, 시스템은 일관성을 우선할지(Consistency, CP 모델) 혹은 가용성을 우선할지(Availability, AP 모델)를 선택해야 합니다.
  - **예시:**  
    - 금융 시스템은 파티션 상황에서도 일관성을 유지(CP)해야 하는 반면, 소셜 네트워크 서비스는 가용성(AP)을 선택할 수 있습니다.

### 2.2 Else 상황 (EL)

- **EL → L or C:**  
  - 네트워크 파티션이 발생하지 않는 정상 상황에서는, 일관성을 강화하면 응답 지연(Latency)이 증가할 수 있습니다.
  - 즉, 시스템은 **더 낮은 지연(Low Latency, sacrificing consistency)** 또는 **강한 일관성(High Consistency, 수용 가능한 지연)** 중 하나를 선택해야 합니다.
  - **예시:**  
    - 실시간 데이터 처리 시스템은 낮은 지연을 위해 약한 일관성을 채택할 수 있고, 반대로 일부 금융 거래 시스템은 강한 일관성을 유지하여 추가적인 지연을 감수할 수 있습니다.

---

## 3. 실무 적용 및 고려 사항

- **설계 시 선택 기준:**  
  - 서비스의 특성과 사용 사례에 따라 파티션 발생 시와 정상 상황에서 각각 어떤 요소(Availability vs. Consistency, Latency vs. Consistency)를 우선할지 결정해야 합니다.
  
- **시스템 요구사항 분석:**  
  - 높은 일관성이 필수적인 서비스라면 파티션 상황에서도 일관성을 유지하고, 정상 상황에서도 추가 지연을 감수해야 합니다.
  - 반면, 빠른 응답이 중요한 서비스라면 가용성과 낮은 지연을 선택할 수 있습니다.

- **운영 환경 고려:**  
  - 클라우드 환경에서는 네트워크 안정성이 중요한 요소이므로, PACELC 이론에 따른 트레이드오프를 실제 모니터링 및 테스트를 통해 검증해야 합니다.

- **보완적 전략:**  
  - PACELC 이론을 통해, 단순히 CAP 이론만으로는 설명할 수 없는 정상 상황의 지연 문제를 추가적으로 고려함으로써 보다 세밀한 시스템 설계가 가능합니다.

---

## 4. 참고 자료

- **서적:**  
  - _Designing Data-Intensive Applications_ - Martin Kleppmann  
  - _Distributed Systems: Principles and Paradigms_ - Andrew S. Tanenbaum
- **온라인 자료:**  
  - [PACELC Theorem Overview](https://dbmsmusings.blogspot.com/2010/04/problems-with-cap-and-yahoos-little.html)  
  - [Understanding the PACELC Theorem](https://www.scnsoft.com/blog/cap-theorem)

---

## 5. 마무리

PACELC 이론은 분산 시스템 설계에서 네트워크 파티션 상황 뿐만 아니라 정상 상황에서의 지연(Latency)과 일관성(Consistency) 간의 트레이드오프를 명확하게 이해할 수 있도록 도와줍니다.  
이를 통해 시스템 설계자는 서비스의 요구사항에 따라 일관성과 응답 지연 사이의 균형을 보다 세밀하게 조정할 수 있습니다.  
실제 프로젝트에서는 PACELC 이론을 기반으로, CAP 이론의 한계를 보완하며 최적의 설계 결정을 내리는 것이 중요합니다.