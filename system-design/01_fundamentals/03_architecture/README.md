# 📂 **01_fundamentals/architecture/README.md**  
> **목표:**  
> - **시스템 아키텍처의 다양한 스타일과 설계 방식**을 익힌다.  
> - **각 아키텍처 스타일의 장단점 및 실무 적용 사례**를 학습한다.  
> - **확장성, 유지보수성, 성능을 고려한 최적의 아키텍처를 설계할 수 있도록 한다.**  

---

## 📌 **디렉토리 구조 및 학습 내용**  
```
architecture/
├── layered_architecture/       # 계층화 아키텍처
├── microservices/              # 마이크로서비스 아키텍처
├── event_driven/               # 이벤트 기반 아키텍처
├── serverless/                 # 서버리스 아키텍처
├── hexagonal_architecture/     # 헥사고날 아키텍처 (포트 & 어댑터)
├── distributed_architecture/   # 분산 시스템 아키텍처
└── real_world/                 # 실전 사례 분석
```

---

## 🏛️ **1. 계층화 아키텍처 (layered_architecture/)**  
> **전통적인 애플리케이션 설계 방식으로, 유지보수성이 높은 구조**  

### 📚 학습 내용  
- **3-Tier & N-Tier Architecture**  
  - Presentation Layer, Business Logic Layer, Data Layer  
  - 실무 적용: **웹 애플리케이션, 엔터프라이즈 시스템**  

- **MVC (Model-View-Controller) 패턴**  
  - UI, 비즈니스 로직, 데이터 처리 분리  
  - 실무 적용: **Django, Spring, .NET MVC Framework**  

- **Layered Architecture의 단점과 해결책**  
  - 성능 문제와 계층 간 의존성 관리  
  - 실무 적용: **CQRS 및 이벤트 기반 설계를 통한 최적화**  

> 📍 자세한 내용은 `layered_architecture/README.md` 참고  

---

## 🏗️ **2. 마이크로서비스 아키텍처 (microservices/)**  
> **독립적으로 배포 가능한 작은 서비스들로 구성된 아키텍처**  

### 📚 학습 내용  
- **Monolithic vs Microservices**  
  - 단일 애플리케이션과 마이크로서비스 비교  
  - 실무 적용: **Netflix, Amazon, Uber의 MSA 사례**  

- **Service Communication (서비스 간 통신)**  
  - REST, gRPC, Message Queue 기반 통신  
  - 실무 적용: **RabbitMQ, Kafka 활용한 비동기 메시징**  

- **Data Management in Microservices**  
  - 각 서비스별 DB 분리 vs 공유 DB  
  - 실무 적용: **CQRS 및 Event Sourcing 적용 방식**  

> 📍 자세한 내용은 `microservices/README.md` 참고  

---

## 🔄 **3. 이벤트 기반 아키텍처 (event_driven/)**  
> **이벤트 중심으로 시스템이 동작하는 구조로, 확장성과 유연성이 뛰어난 아키텍처**  

### 📚 학습 내용  
- **Event-Driven vs Request-Response**  
  - 동기 vs 비동기 아키텍처 차이점  
  - 실무 적용: **실시간 주문 처리 시스템, IoT 플랫폼**  

- **Message Broker (메시지 브로커) 활용**  
  - Kafka, RabbitMQ, AWS SNS/SQS  
  - 실무 적용: **이벤트 스트리밍 및 마이크로서비스 통합**  

- **Event Sourcing & CQRS**  
  - 이벤트 로그를 기반으로 상태를 관리하는 방식  
  - 실무 적용: **은행 트랜잭션, 블록체인 시스템**  

> 📍 자세한 내용은 `event_driven/README.md` 참고  

---

## ☁️ **4. 서버리스 아키텍처 (serverless/)**  
> **서버를 직접 운영하지 않고, 클라우드 서비스에서 이벤트 기반으로 실행되는 아키텍처**  

### 📚 학습 내용  
- **What is Serverless?**  
  - 서버리스의 개념과 장점  
  - 실무 적용: **AWS Lambda, Google Cloud Functions**  

- **Function as a Service (FaaS)**  
  - 코드 실행 단위로 배포하는 방식  
  - 실무 적용: **파일 업로드 → 이미지 변환 → 데이터베이스 저장 프로세스 자동화**  

- **Serverless vs Containerized Applications**  
  - 서버리스와 컨테이너 기반 아키텍처 비교  
  - 실무 적용: **Kubernetes + Knative 기반 하이브리드 서버리스 아키텍처**  

> 📍 자세한 내용은 `serverless/README.md` 참고  

---

## 🔳 **5. 헥사고날 아키텍처 (hexagonal_architecture/)**  
> **애플리케이션의 핵심 로직을 외부 인터페이스와 분리하여 유지보수성을 높이는 설계 방식**  

### 📚 학습 내용  
- **Ports & Adapters 패턴**  
  - 도메인 로직을 독립적으로 유지하는 방법  
  - 실무 적용: **마이크로서비스 간 API 변경 최소화**  

- **Dependency Inversion & Clean Architecture**  
  - 내부 비즈니스 로직을 외부 기술에서 독립적으로 설계  
  - 실무 적용: **Spring, NestJS 기반의 도메인 중심 설계**  

> 📍 자세한 내용은 `hexagonal_architecture/README.md` 참고  

---

## 🌍 **6. 분산 시스템 아키텍처 (distributed_architecture/)**  
> **여러 서버에 트래픽을 분산하여 처리하는 아키텍처 설계 기법**  

### 📚 학습 내용  
- **Single-Point-of-Failure (SPOF) 방지**  
  - 고가용성을 위한 설계 패턴  
  - 실무 적용: **Multi-Region Database, Global Load Balancing**  

- **Data Partitioning & Sharding**  
  - 데이터베이스를 효율적으로 분산 저장하는 방법  
  - 실무 적용: **Facebook의 Graph 데이터베이스 구조**  

- **CAP Theorem & Consistency Models**  
  - 분산 시스템에서 일관성, 가용성, 네트워크 분할 허용성  
  - 실무 적용: **Cassandra (AP 시스템) vs Google Spanner (CP 시스템) 비교**  

> 📍 자세한 내용은 `distributed_architecture/README.md` 참고  

---

## 🚀 **7. 실전 사례 분석 (real_world/)**  
> **실제 기업들의 시스템 설계를 분석하며 학습**  

### 📚 학습 내용  
- **Netflix의 마이크로서비스 아키텍처 설계 과정**  
- **Uber의 이벤트 기반 아키텍처 적용 방식**  
- **AWS Lambda를 활용한 서버리스 애플리케이션 사례**  
- **Google Spanner를 기반으로 한 글로벌 분산 데이터베이스 설계**  

> 📍 자세한 내용은 `real_world/README.md` 참고  

---

## 🔍 **학습 방법**  
1. 각 아키텍처 스타일의 **이론적 개념**을 학습한다.  
2. **예제 프로젝트**를 통해 설계 원리를 적용해본다.  
3. 대규모 시스템의 **실제 사례를 분석**하여 실무에서의 적용 방법을 익힌다.  
4. **트레이드오프**를 고려하여 어떤 아키텍처가 최적의 선택인지 판단하는 연습을 한다.  

---

## 📚 **추천 학습 리소스**  
- **"Designing Data-Intensive Applications" - Martin Kleppmann**  
- **"Building Microservices" - Sam Newman**  
- **"Clean Architecture" - Robert C. Martin**  
- **AWS, Google Cloud, Azure 아키텍처 문서**  

---

## ✅ **마무리**  
이 디렉토리는 **다양한 아키텍처 스타일을 배우고, 실무에서 최적의 설계를 선택하는 방법**을 익히기 위한 공간입니다.  
각 아키텍처가 **어떤 문제를 해결하는지, 트레이드오프는 무엇인지** 고민하며 학습하는 것이 중요합니다. 🚀