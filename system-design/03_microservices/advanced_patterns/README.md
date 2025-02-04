# 📂 고급 패턴 - advanced_patterns

> **목표:**  
> - 마이크로서비스 아키텍처에서 활용되는 고급 패턴을 학습한다.  
> - 서비스 간 장애를 방지하고 회복력을 높이는 패턴을 이해하고 적용한다.  
> - 마이크로서비스 전환 및 운영을 최적화하는 전략을 연구하고 실무에 적용한다.

---

## 📌 **디렉토리 구조**
```
advanced_patterns/               # 고급 패턴 학습
├── introduction.md               # 고급 패턴 개요
├── circuit_breaker.md            # Circuit Breaker 패턴
├── sidecar_pattern.md            # 사이드카 패턴
├── saga_pattern.md               # SAGA 패턴 (분산 트랜잭션)
├── strangler_fig.md              # Strangler Fig 패턴
├── bulkhead_pattern.md           # 벌크헤드 패턴
├── advanced_patterns_in_practice.md # 실무에서의 고급 패턴 적용
└── README.md
```

---

## 📖 **1. 개념 개요**
> **고급 패턴은 마이크로서비스 환경에서 복잡성을 해결하고 서비스의 안정성과 확장성을 극대화하는 설계 기법이다.**

- ✅ **왜 중요한가?**  
  - 마이크로서비스 환경에서는 다양한 장애 상황을 고려한 설계가 필요하다.
  - 높은 트래픽과 부하를 처리하는 데 있어 효율적인 전략을 제공한다.
  - 기존 시스템을 마이크로서비스로 점진적으로 전환하는 데 유용하다.

- ✅ **어떤 문제를 해결하는가?**  
  - 서비스 간 장애 전파를 방지하고 복구 가능성을 높임
  - 네트워크 부하를 분산하고 성능 최적화를 수행
  - 기존 모놀리식 시스템을 무중단으로 마이크로서비스로 전환

- ✅ **실무에서 어떻게 적용하는가?**  
  - **Circuit Breaker**를 활용한 장애 감지 및 자동 복구
  - **Sidecar 패턴**을 사용하여 마이크로서비스 기능을 확장
  - **SAGA 패턴**을 적용하여 분산 트랜잭션을 관리

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **고급 패턴 개요 (introduction.md)**
  - 마이크로서비스 아키텍처에서 활용되는 주요 고급 패턴
  - 각 패턴의 장단점 및 활용 사례

- **Circuit Breaker 패턴 (circuit_breaker.md)**
  - 장애가 발생한 서비스를 자동으로 감지하고 요청 차단
  - Netflix Hystrix, Resilience4j를 활용한 구현
  - 장애 전파를 방지하는 방법

- **Sidecar 패턴 (sidecar_pattern.md)**
  - 서비스의 보안, 로깅, 모니터링 기능을 독립적인 사이드카 컨테이너로 분리
  - Istio, Envoy Proxy와 같은 서비스 메쉬 적용 사례

- **SAGA 패턴 (saga_pattern.md)**
  - 분산 환경에서의 트랜잭션 관리 방법
  - 보상 트랜잭션(Compensating Transaction) 개념
  - Kafka, RabbitMQ 기반의 이벤트 중심 SAGA 구현

- **Strangler Fig 패턴 (strangler_fig.md)**
  - 모놀리식 애플리케이션을 단계적으로 마이크로서비스로 전환
  - 서비스 리팩토링 및 단계적 마이그레이션 전략
  - API Gateway를 활용한 트래픽 라우팅 적용

- **벌크헤드 패턴 (bulkhead_pattern.md)**
  - 리소스를 논리적으로 분리하여 장애가 특정 영역에만 영향을 미치도록 함
  - 컨테이너 및 멀티 테넌시 환경에서의 활용 사례

- **실무에서의 고급 패턴 적용 (advanced_patterns_in_practice.md)**
  - 대규모 시스템에서 고급 패턴을 조합하여 활용하는 방법
  - 트레이드오프 및 패턴 선택 기준
  - 사례 분석 및 코드 예제

---

## 🚀 **3. 실전 사례 분석**
> **대규모 서비스에서 고급 패턴이 어떻게 활용되는가?**

- **Netflix** - Circuit Breaker 패턴을 활용한 장애 대응 전략
- **Uber** - SAGA 패턴을 통한 분산 트랜잭션 처리
- **Amazon** - Strangler Fig 패턴을 이용한 모놀리식 시스템의 마이크로서비스 전환

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ 각 패턴별 코드 실습  
3️⃣ 실제 사례 연구  
4️⃣ 마이크로서비스 설계 실습 및 트레이드오프 분석  

---

## 📚 **5. 추천 리소스**
- 📖 _Building Microservices_ - Sam Newman  
- 📖 _Microservices Patterns_ - Chris Richardson  
- 📖 _Cloud Native Patterns_ - Cornelia Davis  
- 📌 [Circuit Breaker Explained](https://martinfowler.com/bliki/CircuitBreaker.html)  
- 📌 [SAGA Pattern in Microservices](https://microservices.io/patterns/data/saga.html)  
- 📌 [Strangler Fig Pattern](https://martinfowler.com/bliki/StranglerFigApplication.html)  

---

## ✅ **마무리**
이 문서는 **마이크로서비스 아키텍처에서 장애 대응, 운영 최적화, 마이그레이션을 위한 다양한 고급 패턴을 학습하는 단계**입니다. 
이론 → 패턴 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며, 
확장성과 유지보수성을 고려한 최적의 마이크로서비스 패턴을 설계할 수 있도록 합니다. 🚀