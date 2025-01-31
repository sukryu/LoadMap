# 📂 **04_data_management (데이터 관리)**
> **목표:**  
> - **대규모 데이터**를 안정적으로 관리하는 방법을 익힌다.  
> - **데이터 저장, 캐싱, 스트리밍, 복제 및 분산 처리** 등 핵심 개념을 실무 관점에서 학습한다.  
> - **데이터 일관성 모델 및 이벤트 소싱(CQRS)** 같은 고급 패턴을 적용하는 방법을 익힌다.

---

## 📌 **디렉토리 구조 및 학습 내용**
```
data_management/
├── storage/                    # 데이터 저장소 설계
├── caching/                    # 캐싱 전략
├── streaming/                  # 스트리밍 데이터 처리
├── replication/                # 데이터 복제 및 샤딩
├── consistency_models/         # 데이터 일관성 모델
├── event_sourcing_cqrs/        # 이벤트 소싱 및 CQRS
└── real_world_examples/        # 실전 사례 분석
```

---

## 📖 **1. 데이터 저장소 설계 (storage/)**
> 데이터를 저장하고 관리하는 다양한 방식 학습  

### 📚 학습 내용
- **Relational Database (RDBMS) vs NoSQL**
  - MySQL, PostgreSQL vs MongoDB, Cassandra 비교
  - 실무 적용: **트랜잭션이 중요한 경우 vs 확장성이 중요한 경우**

- **Sharding & Partitioning (샤딩 및 파티셔닝)**
  - 데이터베이스를 수평적으로 분산하는 방식
  - 실무 적용: **Facebook, Twitter의 대규모 사용자 데이터 처리 방식**

- **Polyglot Persistence (다양한 저장소 활용)**
  - 특정 목적에 맞는 데이터베이스 선택
  - 실무 적용: **검색(Elasticsearch) + 로그(Kafka) + 트랜잭션(MySQL) 조합**

---

## 📖 **2. 캐싱 전략 (caching/)**
> 데이터 액세스 속도를 높이기 위한 캐싱 활용법 학습  

### 📚 학습 내용
- **Client-Side Caching (클라이언트 사이드 캐싱)**
  - 브라우저, 모바일 앱에서 캐싱 적용
  - 실무 적용: **CDN을 활용한 정적 파일 캐싱**

- **Application-Level Caching (애플리케이션 캐싱)**
  - Redis, Memcached 활용
  - 실무 적용: **세션 관리, API 응답 캐싱**

- **Database Caching (데이터베이스 캐싱)**
  - 데이터베이스 질의 성능 최적화
  - 실무 적용: **Write-Through, Write-Behind, Cache-Aside 패턴**

- **Cache Expiration & Invalidation (캐시 무효화)**
  - TTL(Time-To-Live), LRU(Least Recently Used) 적용
  - 실무 적용: **쇼핑몰의 재고 관리 캐싱 최적화**

---

## 📖 **3. 스트리밍 데이터 처리 (streaming/)**
> 실시간 데이터 처리 및 로그 분석 기술 학습  

### 📚 학습 내용
- **Message Queue vs Event Streaming**
  - Kafka, RabbitMQ, AWS Kinesis 비교
  - 실무 적용: **이벤트 기반 아키텍처에서의 활용 사례**

- **Real-Time vs Batch Processing**
  - Apache Flink, Spark Streaming vs Hadoop Batch
  - 실무 적용: **금융 트랜잭션 모니터링 및 사기 탐지**

- **Change Data Capture (CDC)**
  - 데이터 변경 이벤트 감지
  - 실무 적용: **Debezium을 활용한 DB 이벤트 스트리밍**

---

## 📖 **4. 데이터 복제 및 샤딩 (replication/)**
> 데이터 가용성과 성능을 위한 **복제 및 샤딩 전략** 학습  

### 📚 학습 내용
- **Replication (데이터 복제)**
  - Master-Slave vs Multi-Master 복제 방식
  - 실무 적용: **MySQL Read Replica 활용**

- **Partitioning (파티셔닝)**
  - Key-Based(해싱), Range-Based, Geo-Partitioning 방식
  - 실무 적용: **Global 서비스에서 사용자 데이터를 지역별로 저장**

- **Consistency vs Availability Tradeoff**
  - CAP 이론과 데이터 복제 방식
  - 실무 적용: **Cassandra의 eventual consistency 적용 방식**

---

## 📖 **5. 데이터 일관성 모델 (consistency_models/)**
> 분산 환경에서 데이터의 **일관성을 보장하는 방식** 학습  

### 📚 학습 내용
- **ACID vs BASE 모델**
  - 강한 일관성(ACID) vs 최종적 일관성(BASE) 비교
  - 실무 적용: **온라인 결제 시스템 vs SNS 뉴스피드 일관성 요구 사항**

- **Strong Consistency (강한 일관성)**
  - 모든 노드에서 즉시 동일한 데이터 제공
  - 실무 적용: **은행 계좌 잔액 정보 처리**

- **Eventual Consistency (최종적 일관성)**
  - 시간이 지나면 모든 노드가 동일한 데이터를 가짐
  - 실무 적용: **DynamoDB, Cassandra 기반 분산 시스템**

- **Causal Consistency (인과적 일관성)**
  - A가 B보다 먼저 일어나야 한다는 보장
  - 실무 적용: **SNS 댓글 정렬 방식**

---

## 📖 **6. 이벤트 소싱 및 CQRS (event_sourcing_cqrs/)**
> 데이터 변경을 이벤트 기반으로 관리하는 고급 패턴 학습  

### 📚 학습 내용
- **What is Event Sourcing? (이벤트 소싱이란?)**
  - 데이터를 현재 상태가 아닌 변경 이벤트로 저장
  - 실무 적용: **금융 트랜잭션 기록 보관 시스템**

- **CQRS (Command Query Responsibility Segregation)**
  - 읽기/쓰기 모델을 분리하여 성능 향상
  - 실무 적용: **온라인 쇼핑몰의 주문 처리 최적화**

- **Saga Pattern (분산 트랜잭션 관리)**
  - 여러 마이크로서비스 간 데이터 일관성을 유지하는 방법
  - 실무 적용: **주문-결제-배송 프로세스에서 롤백 처리**

---

## 📖 **7. 실전 사례 분석 (real_world_examples/)**
> 실제 기업들이 데이터 관리 전략을 어떻게 적용하는지 학습  

### 📚 학습 내용
- **Netflix의 데이터 관리 아키텍처**
- **Uber의 실시간 데이터 스트리밍**
- **Amazon DynamoDB의 일관성 모델 적용 방식**
- **Airbnb의 예약 시스템에서 CQRS 활용**
- **Google Spanner의 글로벌 데이터베이스 설계**