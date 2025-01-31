# 📂 **01_fundamentals/real_world/README.md**  
> **목표:**  
> - **실제 기업들이 시스템 설계를 어떻게 적용하는지 학습한다.**  
> - **설계 트레이드오프를 이해하고, 최적의 선택을 내리는 방법을 익힌다.**  
> - **대규모 트래픽 처리, 확장성, 장애 대응 전략 등 실무 사례를 분석한다.**  

---

## 📌 **디렉토리 구조 및 학습 내용**  
```
real_world/
├── case_studies/            # 시스템 설계 사례 연구
├── scalability_strategies/  # 확장성 전략
├── fault_tolerance/         # 장애 대응 전략
├── performance_optimization/# 성능 최적화 사례
└── architecture_decisions/  # 설계 결정 분석
```

---

## 🏗️ **1. 시스템 설계 사례 연구 (case_studies/)**  
> **실제 기업들의 아키텍처 설계를 분석하여 인사이트 얻기**  

### 📚 학습 내용  
- **Netflix의 마이크로서비스 전환 과정**  
  - Monolithic → Microservices 트랜스포메이션  
  - 실무 적용: **API Gateway, Eureka, Hystrix 활용**  

- **Uber의 실시간 데이터 처리 시스템**  
  - Kafka를 활용한 대규모 스트리밍 데이터 처리  
  - 실무 적용: **Geo-Partitioning을 통한 빠른 응답 시간 확보**  

- **Facebook의 GraphQL 도입 배경 및 성능 최적화**  
  - RESTful API의 한계와 GraphQL의 장점  
  - 실무 적용: **페이스북 뉴스피드 최적화 방식 분석**  

> 📍 자세한 내용은 `case_studies/README.md` 참고  

---

## 📈 **2. 확장성 전략 (scalability_strategies/)**  
> **대규모 트래픽을 처리하는 시스템의 확장성 전략 학습**  

### 📚 학습 내용  
- **Horizontal Scaling vs Vertical Scaling**  
  - 트래픽 증가 시 확장 방법 선택  
  - 실무 적용: **AWS Auto Scaling, Kubernetes HPA 활용**  

- **Database Scaling Strategies**  
  - 샤딩(Sharding), 리플리케이션(Replication), CQRS 적용  
  - 실무 적용: **MySQL, PostgreSQL, MongoDB 확장 전략**  

- **Global Load Balancing & Multi-Region Deployment**  
  - 여러 지역에 분산된 서버로 트래픽 자동 라우팅  
  - 실무 적용: **Cloudflare Anycast, AWS Route 53 활용**  

> 📍 자세한 내용은 `scalability_strategies/README.md` 참고  

---

## 🛠️ **3. 장애 대응 전략 (fault_tolerance/)**  
> **서비스 장애 발생 시 빠른 복구와 복원력을 높이는 기법 학습**  

### 📚 학습 내용  
- **Circuit Breaker Pattern (서킷 브레이커 패턴)**  
  - 장애 발생 시 전체 서비스 영향 방지  
  - 실무 적용: **Netflix Hystrix, Resilience4j 활용**  

- **Chaos Engineering & Fault Injection**  
  - 실제 장애를 시뮬레이션하여 복원력 테스트  
  - 실무 적용: **AWS Fault Injection Simulator, Netflix Chaos Monkey**  

- **Disaster Recovery Planning (DRP)**  
  - 장애 발생 시 복구 전략 설계  
  - 실무 적용: **RTO, RPO 기반 복구 전략 수립**  

> 📍 자세한 내용은 `fault_tolerance/README.md` 참고  

---

## ⚡ **4. 성능 최적화 사례 (performance_optimization/)**  
> **대규모 트래픽 환경에서 성능 최적화 전략 학습**  

### 📚 학습 내용  
- **Profiling & Bottleneck Analysis**  
  - 시스템 성능 병목 분석 및 최적화  
  - 실무 적용: **New Relic, Datadog, Jaeger 활용**  

- **Latency Optimization & CDN Usage**  
  - 응답 시간 단축 및 글로벌 성능 개선  
  - 실무 적용: **Cloudflare, AWS CloudFront 활용**  

- **Indexing & Query Optimization in Databases**  
  - 데이터베이스 쿼리 최적화 및 인덱스 전략  
  - 실무 적용: **SQL 튜닝, NoSQL 데이터 모델링 최적화**  

> 📍 자세한 내용은 `performance_optimization/README.md` 참고  

---

## 🔍 **5. 설계 결정 분석 (architecture_decisions/)**  
> **시스템 설계 과정에서의 주요 트레이드오프 분석**  

### 📚 학습 내용  
- **CAP Theorem in Real-World Applications**  
  - 일관성 vs 가용성 vs 네트워크 분할 허용성  
  - 실무 적용: **은행 서비스(강한 일관성) vs SNS(최종적 일관성)**  

- **Monolith vs Microservices: When to Choose?**  
  - MSA 도입 시 고려해야 할 트레이드오프  
  - 실무 적용: **스타트업과 엔터프라이즈 환경에서의 차이**  

- **Serverless vs Kubernetes vs Bare Metal**  
  - 각각의 장단점 및 적절한 사용 사례  
  - 실무 적용: **클라우드 네이티브 vs 온프레미스 비용 비교 분석**  

> 📍 자세한 내용은 `architecture_decisions/README.md` 참고  

---

## 🔍 **학습 방법**  
1. **기업 사례를 분석하여** 시스템 설계 원칙을 익힌다.  
2. **확장성, 성능 최적화, 장애 대응** 등의 주제를 실무 관점에서 이해한다.  
3. **설계 결정 과정에서의 트레이드오프를 분석**하여 최적의 선택을 내리는 방법을 배운다.  
4. 실제 프로젝트에 적용할 수 있는 **패턴과 전략을 도출**한다.  

---

## 📚 **추천 학습 리소스**  
- **"Designing Data-Intensive Applications" - Martin Kleppmann**  
- **"The Site Reliability Workbook" - Google SRE Team**  
- **"Building Microservices" - Sam Newman**  
- **AWS, Google Cloud, Azure 아키텍처 사례 연구**  

---

## ✅ **마무리**  
이 디렉토리는 **실제 기업들의 시스템 설계를 분석하고, 확장성과 성능을 고려한 최적의 설계를 익히기 위한 공간**입니다.  
각 사례를 **단순한 학습이 아니라, 트레이드오프를 고민하면서 적용할 수 있도록 학습하는 것이 중요합니다.** 🚀  