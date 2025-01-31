# 📂 **01_fundamentals/scalability/README.md**  
> **목표:**  
> - **확장성(Scalability)의 개념과 설계 기법**을 학습한다.  
> - **수평 확장(Horizontal Scaling)과 수직 확장(Vertical Scaling)의 차이**를 이해한다.  
> - **로드 밸런싱, 데이터 파티셔닝, 캐싱 등 실무에서 활용되는 확장성 패턴**을 익힌다.  
> - **대규모 트래픽을 처리하는 시스템 설계 방법**을 분석한다.  

---

## 📌 **디렉토리 구조 및 학습 내용**  
```
scalability/
├── horizontal_scaling/        # 수평적 확장 (Scaling Out)
├── vertical_scaling/          # 수직적 확장 (Scaling Up)
├── load_balancing/            # 로드 밸런싱
├── caching/                   # 캐싱 전략
├── database_scaling/          # 데이터베이스 확장성
├── distributed_systems/       # 분산 시스템 확장성
└── real_world/                # 실전 사례 분석
```

---

## 📈 **1. 수평적 확장 (horizontal_scaling/)**  
> **여러 개의 서버를 추가하여 성능을 높이는 확장 기법**  

### 📚 학습 내용  
- **What is Horizontal Scaling?**  
  - 서버 개수를 늘려 확장성을 높이는 방법  
  - 실무 적용: **Kubernetes 클러스터 확장, AWS Auto Scaling 활용**  

- **Stateful vs Stateless Services**  
  - 상태 유지(Stateful)와 무상태(Stateless) 서비스 비교  
  - 실무 적용: **세션 클러스터링, JWT 기반 인증**  

- **Auto-Scaling Mechanisms**  
  - 동적인 확장을 위한 오토스케일링 기법  
  - 실무 적용: **AWS EC2 Auto Scaling, Kubernetes HPA**  

> 📍 자세한 내용은 `horizontal_scaling/README.md` 참고  

---

## 🏗️ **2. 수직적 확장 (vertical_scaling/)**  
> **서버의 성능을 높여 확장하는 방식**  

### 📚 학습 내용  
- **What is Vertical Scaling?**  
  - CPU, RAM, 디스크 업그레이드를 통해 성능 향상  
  - 실무 적용: **데이터베이스 서버의 수직 확장 사례**  

- **Scaling Up vs Scaling Out**  
  - 수직 확장과 수평 확장의 트레이드오프  
  - 실무 적용: **Monolithic 서비스의 한계 해결 방법**  

- **Hardware Optimization & Performance Tuning**  
  - 서버 성능 최적화 기법  
  - 실무 적용: **프로파일링 도구 활용 (New Relic, Datadog)**  

> 📍 자세한 내용은 `vertical_scaling/README.md` 참고  

---

## ⚖️ **3. 로드 밸런싱 (load_balancing/)**  
> **서버 간 부하를 분산하여 성능을 최적화하는 기술**  

### 📚 학습 내용  
- **Layer 4 vs Layer 7 Load Balancing**  
  - 네트워크 계층별 로드 밸런싱 방식  
  - 실무 적용: **NGINX, AWS ALB, Google Load Balancer 활용**  

- **Load Balancing Algorithms**  
  - Round Robin, Least Connections, IP Hash 비교  
  - 실무 적용: **클라우드 로드 밸런서 설정 방법**  

- **Global Load Balancing & Multi-Region Deployment**  
  - 여러 지역에 분산된 서버로 트래픽 자동 라우팅  
  - 실무 적용: **Cloudflare Anycast, AWS Route 53 활용**  

> 📍 자세한 내용은 `load_balancing/README.md` 참고  

---

## 🚀 **4. 캐싱 전략 (caching/)**  
> **데이터 액세스를 최적화하여 성능을 향상하는 방법**  

### 📚 학습 내용  
- **What is Caching?**  
  - 자주 사용되는 데이터를 빠르게 제공하는 기술  
  - 실무 적용: **Redis, Memcached 활용**  

- **Cache Invalidation Strategies**  
  - TTL(Time-To-Live), LRU(Least Recently Used) 정책  
  - 실무 적용: **CDN 캐싱, 애플리케이션 캐싱**  

- **Cache Patterns (Cache-Aside, Write-Through, Write-Behind)**  
  - 데이터베이스와 캐시 간의 데이터 일관성 유지  
  - 실무 적용: **고성능 웹 애플리케이션 캐싱 전략**  

> 📍 자세한 내용은 `caching/README.md` 참고  

---

## 📊 **5. 데이터베이스 확장성 (database_scaling/)**  
> **대규모 데이터 처리를 위한 데이터베이스 확장 기법**  

### 📚 학습 내용  
- **Database Partitioning & Sharding**  
  - 데이터를 여러 개의 DB로 나누어 저장  
  - 실무 적용: **MySQL 샤딩, MongoDB 파티셔닝 활용**  

- **Read-Write Splitting (읽기-쓰기 분리)**  
  - 읽기 요청과 쓰기 요청을 다른 DB로 처리  
  - 실무 적용: **Master-Slave Replication 활용**  

- **Eventual Consistency & CAP Theorem**  
  - 일관성 vs 가용성 트레이드오프  
  - 실무 적용: **Cassandra (AP 시스템) vs Google Spanner (CP 시스템) 비교**  

> 📍 자세한 내용은 `database_scaling/README.md` 참고  

---

## 🌍 **6. 분산 시스템 확장성 (distributed_systems/)**  
> **여러 개의 노드에서 트래픽을 분산 처리하는 기술**  

### 📚 학습 내용  
- **Distributed System Fundamentals**  
  - CAP 이론, BASE 모델  
  - 실무 적용: **SNS, 금융 시스템에서의 확장성 적용 사례**  

- **Data Replication Across Regions**  
  - 데이터 동기화 및 복제 방식  
  - 실무 적용: **AWS Aurora Multi-Region DB 활용**  

- **Scalability Bottlenecks & Optimization**  
  - 확장성을 저해하는 요인 분석 및 해결책  
  - 실무 적용: **Queue 기반 비동기 아키텍처 활용**  

> 📍 자세한 내용은 `distributed_systems/README.md` 참고  

---

## 🏆 **7. 실전 사례 분석 (real_world/)**  
> **대규모 트래픽을 처리하는 실제 기업들의 확장 전략 분석**  

### 📚 학습 내용  
- **Netflix의 대규모 트래픽 처리 방식**  
- **Amazon의 글로벌 로드 밸런싱 전략**  
- **Google Spanner의 멀티 리전 데이터베이스 설계**  
- **Uber의 수평 확장 및 자동 스케일링 적용 사례**  
- **Cloudflare의 엣지 네트워크 아키텍처**  

> 📍 자세한 내용은 `real_world/README.md` 참고  

---

## 🔍 **학습 방법**  
1. **확장성 개념**을 이해한다.  
2. **각 확장 기법(수평, 수직, 로드 밸런싱, 캐싱 등)**을 실무 사례와 비교 분석한다.  
3. **성능 병목을 해결하는 패턴과 도구**를 학습하고 적용한다.  
4. **기업 사례를 분석하여** 실제 운영 환경에서의 확장성 기법을 익힌다.  

---

## 📚 **추천 학습 리소스**  
- **"Designing Data-Intensive Applications" - Martin Kleppmann**  
- **"Scalability Rules: Principles for Scaling Web Sites" - Martin Abbott**  
- **AWS, Google Cloud, Azure 아키텍처 문서**  

---

## ✅ **마무리**  
이 디렉토리는 **확장성을 고려한 시스템 설계를 배우고, 실무에서 최적의 확장성 전략을 선택하는 방법**을 익히기 위한 공간입니다.  
**각 확장 기법의 장단점과 트레이드오프를 고려하면서 학습하는 것이 중요합니다.** 🚀  
