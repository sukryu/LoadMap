# 📂 **02_distributed_systems (분산 시스템)**
> **목표:**  
> - 분산 시스템의 기본 개념을 익히고, 트레이드오프를 이해한다.  
> - 실제 분산 시스템 설계에서 발생하는 **일관성, 가용성, 확장성 문제**를 해결하는 방법을 배운다.  
> - **CAP 이론, 합의 알고리즘, 글로벌 시스템 구축** 등 실무에서 자주 접하는 개념을 다룬다.

---

## 📌 **디렉토리 구조 및 학습 내용**
```
distributed_systems/
├── basics/                     # 분산 시스템 기초
├── consistency/                # 일관성 모델
├── consensus/                  # 합의 알고리즘
├── distributed_transactions/   # 분산 트랜잭션
├── event_driven_architecture/  # 이벤트 기반 아키텍처
├── distributed_storage/        # 분산 저장소
├── global_distributed_systems/ # 글로벌 분산 시스템 설계
└── real_world_examples/        # 실전 사례 분석
```

---

## 📖 **1. 분산 시스템 기초 (basics/)**
> 분산 시스템이 **왜 필요한지**, 어떤 문제를 해결하는지부터 학습

### 📚 학습 내용
- **What is Distributed System? (분산 시스템이란?)**
  - 단일 서버 vs 분산 시스템 비교
  - 실무 사례: **Netflix, Google, Facebook의 분산 시스템**

- **CAP Theorem (CAP 이론)**
  - Consistency (일관성) / Availability (가용성) / Partition Tolerance (네트워크 분할 허용성)  
  - 현실적인 트레이드오프: **CP vs AP 시스템**
  - 실무 적용: **NoSQL (MongoDB, Cassandra)에서 CAP 선택**

- **Scalability (확장성)**
  - Scale Up vs Scale Out (수직 vs 수평 확장)
  - 실무 적용: **로드 밸런서, 캐싱, 데이터 파티셔닝**

- **Reliability & Fault Tolerance (신뢰성과 장애 허용성)**
  - 장애 발생 시 복구 전략 (Replication, Failover)
  - 실무 적용: **RAID, DB 복제, Leader-Follower 구조**

---

## 📖 **2. 일관성 모델 (consistency/)**
> 데이터가 여러 노드에서 동기화되는 방식과 트레이드오프를 학습

### 📚 학습 내용
- **Strong Consistency (강한 일관성)**
  - 언제나 최신 데이터를 보장하지만 속도가 느림
  - 실무 적용: **RDBMS 트랜잭션 (ACID), Paxos/Raft 기반 시스템**

- **Eventual Consistency (최종적 일관성)**
  - 시간이 지나면 데이터가 동기화됨, 성능은 빠름
  - 실무 적용: **DynamoDB, Cassandra, Redis Cache**

- **Causal Consistency (인과적 일관성)**
  - 특정 이벤트 순서는 유지하지만, 전체 순서는 보장하지 않음
  - 실무 적용: **SNS 피드 정렬 (ex. Facebook 타임라인)**

- **Session Consistency (세션 일관성)**
  - 같은 사용자가 같은 서버에 연결하면 최신 데이터 유지
  - 실무 적용: **사용자 프로필 업데이트 반영 방식**

---

## 📖 **3. 합의 알고리즘 (consensus/)**
> 분산 환경에서 노드 간 데이터 동기화를 위한 **합의 알고리즘** 학습

### 📚 학습 내용
- **Paxos 알고리즘**
  - 분산 환경에서 합의를 이루는 가장 전통적인 방식
  - 실무 적용: **Google Chubby (분산 락 서비스)**

- **Raft 알고리즘**
  - Paxos보다 이해하기 쉬운 리더 기반 합의 알고리즘
  - 실무 적용: **Etcd (Kubernetes의 상태 관리)**

- **Gossip Protocol (가십 프로토콜)**
  - 노드 간 데이터 전파 방식
  - 실무 적용: **Cassandra, DynamoDB에서 노드 간 동기화**

---

## 📖 **4. 분산 트랜잭션 (distributed_transactions/)**
> 여러 노드에 걸쳐 트랜잭션을 수행하는 방법과 문제 해결 방식 학습

### 📚 학습 내용
- **Two-Phase Commit (2PC)**
  - 모든 노드가 "예/아니오"를 결정한 후 커밋
  - 실무 적용: **은행 시스템, 글로벌 데이터베이스 트랜잭션**

- **Three-Phase Commit (3PC)**
  - 2PC의 단점을 보완하여 장애 발생 시 대비
  - 실무 적용: **기업용 분산 데이터베이스**

- **SAGA Pattern**
  - 분산 시스템에서 롤백을 가능하게 하는 방법
  - 실무 적용: **마이크로서비스에서 데이터 일관성 유지**

---

## 📖 **5. 이벤트 기반 아키텍처 (event_driven_architecture/)**
> 비동기 이벤트를 중심으로 설계하는 **고성능 분산 시스템**

### 📚 학습 내용
- **Publish-Subscribe (Pub/Sub) 패턴**
  - 메시지 브로커 (Kafka, RabbitMQ) 활용
  - 실무 적용: **이메일 알림, 주문 처리 시스템**

- **Event Sourcing (이벤트 소싱)**
  - 데이터 상태가 변경될 때 이벤트 로그 저장
  - 실무 적용: **CQRS (Command Query Responsibility Segregation)**

- **Idempotency (멱등성)**
  - 같은 요청을 여러 번 실행해도 결과가 동일해야 함
  - 실무 적용: **결제 시스템에서 중복 요청 방지**

---

## 📖 **6. 분산 저장소 (distributed_storage/)**
> 대용량 데이터를 여러 서버에 나누어 저장하는 방법 학습

### 📚 학습 내용
- **Partitioning (데이터 파티셔닝)**
  - Key-based (Hashing), Range-based, Geo-partitioning 방식
  - 실무 적용: **Facebook Graph 데이터 저장 방식**

- **Replication (데이터 복제)**
  - Master-Slave vs Multi-Master 복제 방식
  - 실무 적용: **MySQL Read Replica, MongoDB Sharding**

- **Consistency & Availability Tradeoff**
  - CAP 이론을 적용한 데이터 저장 전략
  - 실무 적용: **NoSQL (DynamoDB, Cassandra) vs SQL 비교**

---

## 📖 **7. 글로벌 분산 시스템 설계 (global_distributed_systems/)**
> 전 세계 사용자에게 서비스를 제공할 때 고려해야 할 아키텍처 패턴

### 📚 학습 내용
- **Geo-replication (지리적 복제)**
  - 여러 데이터 센터에 데이터를 동기화하는 방법
  - 실무 적용: **Google Spanner, AWS Aurora Global Database**

- **CDN (Content Delivery Network)**
  - 정적 콘텐츠를 글로벌 엣지 서버에 배포
  - 실무 적용: **Cloudflare, Akamai, AWS CloudFront**

- **Multi-Region Database (멀티 리전 데이터베이스)**
  - 글로벌 시스템에서 일관성 유지 방법
  - 실무 적용: **Stripe의 글로벌 금융 시스템**

---

## 📖 **8. 실전 사례 분석 (real_world_examples/)**
> **실제 서비스에서 분산 시스템이 어떻게 활용되는지 살펴보기**

### 📚 학습 내용
- **Netflix의 분산 시스템 아키텍처**
- **Uber의 글로벌 서비스 운영 방식**
- **AWS DynamoDB의 일관성 모델 적용 사례**
- **Google Spanner의 글로벌 트랜잭션 적용 방식**
- **Airbnb의 이벤트 기반 아키텍처 활용 사례**