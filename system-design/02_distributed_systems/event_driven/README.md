# 📂 이벤트 기반 아키텍처 - event_driven

> **목표:**  
> - 이벤트 기반(Event-Driven) 아키텍처의 개념과 핵심 원리를 학습한다.  
> - 메시지 큐, 이벤트 소싱, CQRS 패턴을 활용한 비동기 시스템 설계를 이해한다.  
> - 확장성과 가용성을 고려한 이벤트 중심 아키텍처를 실무에 적용하는 방법을 연구한다.

---

## 📌 **디렉토리 구조**
```
event_driven/                   # 이벤트 기반 아키텍처 학습
├── introduction.md              # 이벤트 기반 아키텍처 개요
├── message_queues.md            # 메시지 큐(Kafka, RabbitMQ)
├── event_sourcing.md            # 이벤트 소싱(Event Sourcing)
├── cqrs_pattern.md              # CQRS 패턴
├── event_driven_in_practice.md  # 실무에서의 이벤트 기반 아키텍처 적용
└── README.md
```

---

## 📖 **1. 개념 개요**
> **이벤트 기반 아키텍처는 시스템 구성 요소 간의 비동기 이벤트를 통해 상태를 변경하고 통신하는 방식이다.**

- ✅ **왜 중요한가?**  
  - 마이크로서비스 간의 통합을 유연하게 설계할 수 있다.
  - 시스템 성능을 높이고 확장성을 극대화할 수 있다.
  - 고가용성을 요구하는 서비스(결제, 주문 처리, 로그 처리 등)에서 널리 사용된다.

- ✅ **어떤 문제를 해결하는가?**  
  - 동기 요청-응답 모델의 확장성 문제 해결
  - 서비스 간의 결합도를 낮춰 유지보수성을 향상
  - 이벤트 로그를 활용하여 데이터 일관성을 보장

- ✅ **실무에서 어떻게 적용하는가?**  
  - **메시지 큐(Kafka, RabbitMQ)**를 활용한 서비스 간 비동기 통신
  - **이벤트 소싱(Event Sourcing)**을 통해 데이터 변경 이력을 이벤트로 저장
  - **CQRS(Command Query Responsibility Segregation)** 패턴을 사용하여 읽기/쓰기 분리

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **이벤트 기반 아키텍처 개요 (introduction.md)**
  - 이벤트의 정의와 흐름
  - 이벤트 기반 설계의 장점과 단점

- **메시지 큐 (message_queues.md)**
  - Apache Kafka, RabbitMQ, Amazon SQS 비교 분석
  - 메시지 브로커를 활용한 비동기 메시지 전달
  - 메시지 내구성과 재시도 메커니즘

- **이벤트 소싱 (event_sourcing.md)**
  - 이벤트 소싱 개념 및 적용 방법
  - 전통적인 CRUD 기반 데이터 저장 방식과의 차이점
  - 이벤트 로그 저장소 및 복구 전략

- **CQRS 패턴 (cqrs_pattern.md)**
  - 명령(Command)과 조회(Query) 역할 분리
  - 읽기 성능 최적화를 위한 CQRS 적용 방법
  - Event Sourcing과 CQRS의 결합 사례

- **실무에서의 이벤트 기반 아키텍처 적용 (event_driven_in_practice.md)**
  - 이벤트 드리븐 시스템 설계 시 고려할 사항
  - 이벤트 중복 처리 및 순서 보장 전략
  - Kafka Streams, Flink 등을 활용한 실시간 데이터 처리

---

## 🚀 **3. 실전 사례 분석**
> **대규모 서비스에서 이벤트 기반 아키텍처가 어떻게 활용되는가?**

- **Uber** - Kafka를 활용한 실시간 차량 배차 시스템 구축
- **Netflix** - 마이크로서비스 간 이벤트 기반 통신을 통한 확장성 확보
- **Amazon** - SQS와 Lambda를 활용한 서버리스 이벤트 처리

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ 메시지 큐 및 이벤트 소싱 실습  
3️⃣ CQRS 패턴 적용 사례 분석  
4️⃣ 이벤트 기반 아키텍처 설계 실습 및 코드 작성  

---

## 📚 **5. 추천 리소스**
- 📖 _Designing Event-Driven Systems_ - Ben Stopford  
- 📖 _Building Event-Driven Microservices_ - Adam Bellemare  
- 📖 _Kafka: The Definitive Guide_ - Neha Narkhede 외  
- 📌 [Event Sourcing Explained](https://martinfowler.com/eaaDev/EventSourcing.html)  
- 📌 [CQRS and Event Sourcing](https://microservices.io/patterns/data/cqrs.html)  

---

## ✅ **마무리**
이 문서는 **이벤트 기반 아키텍처의 핵심 개념과 실무 적용 방법을 학습하는 단계**입니다.
이론 → 이벤트 모델 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며,
확장성과 성능을 고려한 이벤트 기반 시스템을 설계할 수 있도록 합니다. 🚀

