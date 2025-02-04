# 📂 서비스 간 통신 - communication

> **목표:**  
> - 마이크로서비스 아키텍처에서 서비스 간 통신 방식과 원리를 학습한다.  
> - REST, gRPC, GraphQL, 메시지 큐(Kafka, RabbitMQ) 등의 다양한 통신 기법을 이해하고 비교한다.  
> - 동기 및 비동기 통신 방식의 장단점을 분석하고 실무 적용 방법을 연구한다.

---

## 📌 **디렉토리 구조**
```
communication/                   # 서비스 간 통신 학습
├── introduction.md               # 서비스 간 통신 개요
├── rest_vs_grpc.md               # REST vs gRPC 비교
├── graphql.md                    # GraphQL 개요 및 활용
├── message_queues.md             # 메시지 큐(Kafka, RabbitMQ)
├── synchronous_vs_asynchronous.md # 동기 vs 비동기 통신
├── service_communication_in_practice.md # 실무에서의 통신 적용
└── README.md
```

---

## 📖 **1. 개념 개요**
> **마이크로서비스 간 통신은 서비스 간의 데이터를 교환하고 비즈니스 로직을 실행하기 위한 필수적인 요소이다.**

- ✅ **왜 중요한가?**  
  - 분산 환경에서 서비스 간 데이터 공유 및 요청 처리를 효율적으로 수행할 수 있다.
  - 통신 방식에 따라 성능, 확장성, 유지보수성이 달라질 수 있다.
  - 다양한 통신 기법을 이해하고 적절한 선택이 필요하다.

- ✅ **어떤 문제를 해결하는가?**  
  - 서비스 간의 과도한 결합도를 줄이고 독립성을 유지
  - 네트워크 지연, 장애 발생 시의 대응 전략 제공
  - 요청 처리 속도 및 확장성을 최적화

- ✅ **실무에서 어떻게 적용하는가?**  
  - **REST API**를 활용한 기본적인 HTTP 기반 서비스 통신
  - **gRPC**를 사용하여 고성능 및 타입 안정성을 확보
  - **메시지 큐(Kafka, RabbitMQ)**를 통해 비동기 이벤트 처리 적용

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **서비스 간 통신 개요 (introduction.md)**
  - 서비스 간 데이터 교환 방식 개요
  - 네트워크 기반 통신의 기본 개념 및 원리

- **REST vs gRPC 비교 (rest_vs_grpc.md)**
  - RESTful API 개념 및 장점/단점
  - gRPC의 특징, 성능 비교, Protocol Buffers 개념
  - REST와 gRPC의 선택 기준

- **GraphQL (graphql.md)**
  - REST API와 GraphQL의 차이점
  - 클라이언트 중심 데이터 요청 방식
  - GraphQL 적용 시 고려해야 할 요소

- **메시지 큐 (message_queues.md)**
  - Apache Kafka, RabbitMQ 개요 및 활용 사례
  - 비동기 이벤트 기반 시스템 설계
  - 메시지 내구성, 순서 보장, 중복 처리 전략

- **동기 vs 비동기 통신 (synchronous_vs_asynchronous.md)**
  - 동기(Synchronous) 방식의 특징과 한계
  - 비동기(Asynchronous) 방식의 확장성 및 장점
  - 언제 어떤 방식이 적합한지 결정하는 방법

- **실무에서의 서비스 간 통신 적용 (service_communication_in_practice.md)**
  - 마이크로서비스에서 각 통신 방식을 조합하여 활용하는 방법
  - 트랜잭션 보장 및 데이터 정합성을 유지하는 기법
  - 네트워크 장애 대응 및 백프레셔(Backpressure) 적용 사례

---

## 🚀 **3. 실전 사례 분석**
> **대규모 서비스에서 서비스 간 통신 방식이 어떻게 활용되는가?**

- **Netflix** - gRPC를 활용한 고성능 마이크로서비스 통신
- **Uber** - Kafka 기반 비동기 이벤트 스트리밍 시스템
- **GitHub** - REST API와 GraphQL API를 활용한 데이터 제공 방식

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ REST, gRPC, 메시지 큐 실습 및 비교 분석  
3️⃣ 실제 사례 연구  
4️⃣ 서비스 간 통신 방식 설계 및 코드 작성  

---

## 📚 **5. 추천 리소스**
- 📖 _Designing Distributed Systems_ - Brendan Burns  
- 📖 _Building Microservices_ - Sam Newman  
- 📖 _Kafka: The Definitive Guide_ - Neha Narkhede  
- 📌 [Microservices.io - Communication Patterns](https://microservices.io/patterns/communication/)  
- 📌 [REST vs gRPC Comparison](https://www.grpc.io/docs/what-is-grpc/)  

---

## ✅ **마무리**
이 문서는 **마이크로서비스 아키텍처에서 서비스 간 통신을 위한 다양한 방식을 학습하는 단계**입니다. 
이론 → 통신 방식 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며, 
확장성과 성능을 고려한 최적의 통신 방식을 설계할 수 있도록 합니다. 🚀