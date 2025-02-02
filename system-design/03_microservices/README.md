# 📂 마이크로서비스 아키텍처 - 03_microservices

> **목표:**  
> - 마이크로서비스 아키텍처(MSA)의 개념과 설계 원칙을 학습한다.  
> - 서비스 분리 전략, 서비스 간 통신 방식, 데이터 관리 기법을 이해하고 활용한다.  
> - 실무에서 확장 가능하고 유지보수하기 쉬운 마이크로서비스 시스템을 설계하는 방법을 익힌다.

---

## 📌 **디렉토리 구조**
```
03_microservices/              # 마이크로서비스 개념 학습
├── fundamentals/              # 마이크로서비스 개요
├── service_patterns/          # 서비스 패턴
├── communication/             # 서비스 간 통신
├── data_management/           # 데이터 관리
├── deployment/                # 배포 및 운영
├── security/                  # 보안
├── observability/             # 모니터링 및 트레이싱
├── event_driven_architecture/ # 이벤트 기반 아키텍처
├── ddd/                       # 도메인 주도 설계
├── advanced_patterns/         # 고급 패턴
└── README.md
```

---

## 📖 **1. 개념 개요**
> **마이크로서비스 아키텍처는 독립적으로 배포 가능한 작은 서비스들의 집합으로 구성된 분산 시스템이다.**

- ✅ **왜 중요한가?**  
  - 서비스 간 결합도를 낮추고 독립적인 배포가 가능하게 한다.
  - 확장성과 유지보수성을 향상시키며, DevOps 및 CI/CD 파이프라인과 잘 어울린다.
  - 빠른 기능 배포 및 유연한 개발이 가능하다.

- ✅ **어떤 문제를 해결하는가?**  
  - 모놀리식 아키텍처의 한계를 극복하고 팀 간 협업을 용이하게 함
  - 대규모 시스템의 서비스 확장과 장애 격리를 효율적으로 관리
  - 서비스 간 데이터 공유 및 복잡한 비즈니스 로직 분리를 가능하게 함

- ✅ **실무에서 어떻게 적용하는가?**  
  - 각 도메인별 독립적인 마이크로서비스 설계 및 배포
  - API Gateway를 활용한 서비스 통합 및 보안 강화
  - 컨테이너 및 쿠버네티스를 통한 자동 확장 및 운영 효율화

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **마이크로서비스 개요 (fundamentals/)**
  - 모놀리식 vs 마이크로서비스 비교
  - 마이크로서비스 도입의 장단점

- **서비스 패턴 (service_patterns/)**
  - API Gateway, BFF (Backend for Frontend)
  - 서비스 레지스트리 및 서비스 디스커버리

- **서비스 간 통신 (communication/)**
  - REST, gRPC, GraphQL, 메시지 큐 (Kafka, RabbitMQ)
  - 동기 vs 비동기 통신 방식

- **데이터 관리 (data_management/)**
  - 데이터 분할 전략 (Database per Service, Shared Database)
  - CQRS 및 이벤트 소싱 적용

- **배포 및 운영 (deployment/)**
  - CI/CD 파이프라인 구축
  - Canary Deployment, Blue-Green Deployment

- **보안 (security/)**
  - 서비스 간 인증 및 인가 (OAuth, JWT, mTLS)
  - Zero Trust 아키텍처 적용

- **모니터링 및 트레이싱 (observability/)**
  - 분산 로깅 및 트레이싱 (OpenTelemetry, Zipkin, Jaeger)
  - 장애 분석 및 실시간 모니터링 (Prometheus, Grafana)

- **이벤트 기반 아키텍처 (event_driven_architecture/)**
  - 이벤트 소싱과 CQRS 패턴
  - 메시지 브로커(Kafka, RabbitMQ)를 활용한 비동기 아키텍처

- **도메인 주도 설계 (ddd/)**
  - Bounded Context 개념
  - Aggregate 및 Repository 패턴 적용

- **고급 패턴 (advanced_patterns/)**
  - Sidecar 패턴, Circuit Breaker 패턴
  - Strangler Fig 패턴을 활용한 단계적 마이그레이션

---

## 🚀 **3. 실전 사례 분석**
> **대규모 서비스가 마이크로서비스 아키텍처를 어떻게 활용하는가?**

- **Netflix** - API Gateway 및 서비스 디스커버리를 활용한 확장성 극대화
- **Uber** - 이벤트 기반 아키텍처 및 CQRS 패턴 적용 사례
- **Amazon** - 독립적 서비스 운영을 위한 마이크로서비스 및 서버리스 활용

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ 설계 패턴 학습  
3️⃣ 실제 사례 분석  
4️⃣ 코드 실습 진행  
5️⃣ 트레이드오프 분석  

---

## 📚 **5. 추천 리소스**
- 📖 _Building Microservices_ - Sam Newman  
- 📖 _Microservices Patterns_ - Chris Richardson  
- 📖 _The Kubernetes Book_ - Nigel Poulton  
- 📌 [Microservices.io Patterns](https://microservices.io/)  
- 📌 [Awesome Microservices](https://github.com/mfornos/awesome-microservices)  

---

## ✅ **마무리**
이 문서는 **마이크로서비스 아키텍처의 개념과 실무 적용 방법을 체계적으로 학습하기 위한 단계**입니다. 
이론 → 패턴 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며, 
실무에서 확장성과 유지보수성을 고려한 마이크로서비스 시스템을 설계할 수 있도록 합니다. 🚀