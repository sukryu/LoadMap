# 📂 **03_microservices (마이크로서비스)**
> **목표:**  
> - 모놀리식 시스템과 마이크로서비스 아키텍처(MSA)의 차이를 이해한다.  
> - MSA의 주요 패턴과 **서비스 간 통신, 데이터 관리, 보안, 장애 대응**을 학습한다.  
> - 실무에서 **도메인 주도 설계(DDD)** 및 **고급 패턴**을 활용하여 **확장 가능하고 유지보수성이 높은** 시스템을 설계하는 방법을 익힌다.

---

## 📌 **디렉토리 구조 및 학습 내용**
```
microservices/
├── fundamentals/              # 마이크로서비스 개요
├── patterns/                  # MSA 패턴
├── communication/             # 서비스 간 통신
├── data_management/           # 데이터 관리 전략
├── deployment/                # 배포 및 운영 전략
├── security/                  # 마이크로서비스 보안
├── observability/             # 모니터링 및 트레이싱
├── resilience/                # 장애 대응 및 복원력
├── event_driven_architecture/ # 이벤트 기반 아키텍처
├── ddd/                       # 도메인 주도 설계 (DDD)
├── advanced_patterns/         # 고급 마이크로서비스 패턴
└── real_world_examples/       # 실전 사례 분석
```

---

## 📖 **1. 마이크로서비스 개요 (fundamentals/)**
> 마이크로서비스가 **무엇인지** 이해하고, 기존 모놀리식 아키텍처와 비교

### 📚 학습 내용
- **What is Microservices? (마이크로서비스란?)**
  - Monolithic vs Microservices 비교
  - 실무 적용: **MSA를 도입하는 이유와 장단점**

- **When to Use Microservices? (언제 MSA를 사용할까?)**
  - 적절한 사용 사례 (ex. 대규모 확장이 필요한 경우)
  - 실무 적용: **Netflix, Amazon의 MSA 도입 과정**

---

## 📖 **2. MSA 패턴 (patterns/)**
> 서비스 분해 전략과 아키텍처 패턴을 학습

### 📚 학습 내용
- **Service Decomposition (서비스 분해)**
  - 도메인별 서비스 나누기 (Bounded Context)
  - 실무 적용: **DDD를 활용한 마이크로서비스 설계**

- **Database per Service (서비스별 데이터베이스)**
  - 각 서비스가 독립적인 DB를 가져야 하는 이유
  - 실무 적용: **Banking 시스템에서 데이터 일관성 유지**

- **API Gateway Pattern (API 게이트웨이 패턴)**
  - 서비스 요청을 단일 진입점으로 통합
  - 실무 적용: **Netflix API Gateway (Zuul) 사례**

---

## 📖 **3. 서비스 간 통신 (communication/)**
> 마이크로서비스 간 데이터를 주고받는 다양한 방식 학습

### 📚 학습 내용
- **Synchronous vs Asynchronous Communication (동기 vs 비동기 통신)**
  - REST vs gRPC vs Message Queue 비교
  - 실무 적용: **Kafka, RabbitMQ 활용**

- **Service Mesh (서비스 메시)**
  - Istio, Linkerd와 같은 서비스 메시의 역할
  - 실무 적용: **Envoy 기반 트래픽 관리**

---

## 📖 **4. 데이터 관리 전략 (data_management/)**
> 분산 환경에서 데이터를 일관되게 유지하는 방법 학습

### 📚 학습 내용
- **Eventual Consistency (최종적 일관성)**
  - 분산 시스템에서 강한 일관성을 유지하는 것이 어려운 이유
  - 실무 적용: **DynamoDB, Cassandra 등의 NoSQL 활용**

- **CQRS (Command Query Responsibility Segregation)**
  - 읽기/쓰기 분리하여 성능 최적화
  - 실무 적용: **고성능 검색 시스템에서 CQRS 적용**

- **Event Sourcing (이벤트 소싱)**
  - 변경 이력을 이벤트로 저장하고 재현하는 방법
  - 실무 적용: **결제 시스템의 트랜잭션 처리**

---

## 📖 **5. 배포 및 운영 전략 (deployment/)**
> CI/CD 및 MSA 운영 전략 학습

### 📚 학습 내용
- **Continuous Integration & Continuous Deployment (CI/CD)**
  - MSA 환경에서 지속적 배포 자동화
  - 실무 적용: **GitOps (ArgoCD, FluxCD) 활용**

- **Blue-Green Deployment & Canary Release**
  - 무중단 배포 전략과 롤백 방식
  - 실무 적용: **Kubernetes에서 Canary 배포 적용**

---

## 📖 **6. 마이크로서비스 보안 (security/)**
> 각 서비스의 보안성을 유지하는 방법

### 📚 학습 내용
- **Authentication & Authorization (인증 및 인가)**
  - OAuth2, OpenID Connect 활용
  - 실무 적용: **JWT 기반 보안 토큰 사용**

- **Zero Trust Security (제로 트러스트 보안)**
  - 서비스 간 인증 및 접근 제어 강화
  - 실무 적용: **mTLS (Mutual TLS) 적용**

- **API Security (API 보안)**
  - API Key, Rate Limiting, WAF 적용 방법
  - 실무 적용: **Cloudflare, AWS API Gateway 활용**

---

## 📖 **7. 모니터링 및 트레이싱 (observability/)**
> 마이크로서비스 환경에서 시스템을 가시적으로 관리하는 방법

### 📚 학습 내용
- **Distributed Tracing (분산 트레이싱)**
  - 요청이 여러 서비스에서 어떻게 처리되는지 추적
  - 실무 적용: **Jaeger, OpenTelemetry 활용**

- **Log Aggregation (로그 수집 및 분석)**
  - 중앙 집중형 로그 관리 방식
  - 실무 적용: **ELK Stack (Elasticsearch, Logstash, Kibana)**

- **Alerting & Monitoring (알람 및 모니터링)**
  - Prometheus, Grafana 기반 실시간 모니터링
  - 실무 적용: **SLI/SLO/SLA 정의 및 관리**

---

## 📖 **8. 장애 대응 및 복원력 (resilience/)**
> 장애가 발생했을 때 시스템을 빠르게 복구하는 방법

### 📚 학습 내용
- **Circuit Breaker Pattern (서킷 브레이커 패턴)**
  - 장애가 발생한 서비스에 대한 요청 차단
  - 실무 적용: **Resilience4j 활용**

- **Bulkhead Pattern (벌크헤드 패턴)**
  - 특정 서비스 장애가 전체 시스템에 영향을 주지 않도록 격리
  - 실무 적용: **멀티 스레드 풀 사용**

- **Retry & Fallback Mechanism**
  - 실패 시 자동 재시도 및 대체 경로 제공
  - 실무 적용: **Spring Retry, Polly 활용**

---

## 📖 **9. 도메인 주도 설계 (DDD/)**
> 도메인을 중심으로 서비스 경계를 나누는 전략 학습

### 📚 학습 내용
- **Bounded Context (경계 문맥)**
  - 하나의 도메인은 독립적인 서비스로 분리
  - 실무 적용: **유저 관리 서비스 vs 결제 서비스 분리**

- **Entity, Aggregate, Value Object**
  - 데이터 구조를 도메인 중심으로 모델링
  - 실무 적용: **Hexagonal Architecture 적용**

---

## 📖 **10. 고급 마이크로서비스 패턴 (advanced_patterns/)**
> 대규모 시스템에서 활용되는 패턴 학습

### 📚 학습 내용
- **Sidecar Pattern (사이드카 패턴)**
  - 보안, 로깅, 모니터링을 개별 컨테이너로 분리
  - 실무 적용: **Istio 서비스 메시 활용**

- **Saga Pattern**
  - 분산 트랜잭션을 관리하는 방식
  - 실무 적용: **AWS Step Functions 활용**

---

## 📖 **11. 실전 사례 분석 (real_world_examples/)**
> 실제 기업들이 MSA를 어떻게 활용하는지 학습

### 📚 학습 내용
- **Netflix의 MSA 전환 과정**
- **Uber의 서비스 간 통신 방식**
- **Amazon의 API Gateway 적용 사례**
- **Spotify의 MSA 기반 추천 시스템**
- **eBay의 CQRS & Event Sourcing 적용 사례**