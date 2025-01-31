# 📂 **08_real_world (실전 설계)**  
> **목표:**  
> - 실제 서비스 및 대규모 시스템 설계를 학습한다.  
> - 다양한 사례 연구를 통해 **설계 트레이드오프와 최적의 아키텍처**를 이해한다.  
> - **클라우드 네이티브, 서버리스, 멀티 테넌트 아키텍처** 등 최신 기술을 활용한 설계 기법을 익힌다.  

---

## 📌 **디렉토리 구조 및 학습 내용**  
```
real_world/
├── case_studies/               # 사례 연구
├── best_practices/             # 모범 사례
├── trade_offs/                 # 설계 트레이드오프
├── large_scale_architecture/   # 대규모 시스템 설계
├── cloud_native_design/        # 클라우드 네이티브 설계
├── serverless_edge_computing/  # 서버리스 & 엣지 컴퓨팅
├── sre_real_world/             # 실전 SRE 사례
└── multi_tenant_architecture/  # 멀티 테넌트 아키텍처
```

---

## 📖 **1. 사례 연구 (case_studies/)**  
> **대형 IT 기업의 실제 시스템 설계를 분석하여 인사이트를 얻기**  

### 📚 학습 내용  
- **Netflix의 마이크로서비스 아키텍처 전환 과정**  
  - MSA 도입 배경 및 확장 전략  
  - 실무 적용: **API Gateway, Eureka, Hystrix 활용**  

- **Uber의 실시간 데이터 처리 시스템**  
  - Kafka를 활용한 대규모 데이터 스트리밍  
  - 실무 적용: **Geo-Partitioning을 통한 빠른 응답 시간 확보**  

- **Facebook의 GraphQL 도입 배경 및 성능 최적화**  
  - RESTful API의 한계와 GraphQL의 장점  
  - 실무 적용: **페이스북 피드 최적화 방식 분석**  

---

## 📖 **2. 모범 사례 (best_practices/)**  
> **성공적인 시스템 설계를 위한 아키텍처 및 운영 원칙 학습**  

### 📚 학습 내용  
- **RESTful API vs GraphQL vs gRPC 설계**  
  - 각각의 장단점 및 최적 사용 사례  
  - 실무 적용: **실시간 데이터 서비스에서는 gRPC를 선택하는 이유**  

- **데이터베이스 스키마 설계 모범 사례**  
  - 정규화 vs 비정규화 트레이드오프  
  - 실무 적용: **OLTP(트랜잭션) vs OLAP(분석) 아키텍처 비교**  

- **CI/CD 파이프라인 구축 Best Practices**  
  - GitOps를 활용한 배포 자동화  
  - 실무 적용: **ArgoCD, FluxCD, Jenkins 활용 사례**  

---

## 📖 **3. 설계 트레이드오프 (trade_offs/)**  
> **설계 시 발생하는 다양한 선택지와 트레이드오프 분석**  

### 📚 학습 내용  
- **Consistency vs Availability (CAP Theorem)**  
  - CP vs AP 시스템 선택 기준  
  - 실무 적용: **은행 서비스(강한 일관성) vs SNS 뉴스피드(최종적 일관성)**  

- **Latency vs Throughput**  
  - 지연 시간 최적화 vs 처리량 극대화  
  - 실무 적용: **Redis 캐싱 vs 멀티 리전 DB 설계 비교**  

- **Serverless vs Kubernetes vs Bare Metal**  
  - 각각의 장단점 및 적절한 사용 사례  
  - 실무 적용: **스타트업 초기 단계에서는 서버리스를 선택하는 이유**  

---

## 📖 **4. 대규모 시스템 설계 (large_scale_architecture/)**  
> **트래픽이 많은 서비스를 위한 확장 가능한 아키텍처 설계**  

### 📚 학습 내용  
- **Global Load Balancing (글로벌 로드 밸런싱)**  
  - 트래픽을 여러 리전으로 분산  
  - 실무 적용: **Cloudflare Anycast, AWS Route 53 활용**  

- **Multi-Region Database Replication**  
  - 데이터 동기화 및 복제 방식  
  - 실무 적용: **Google Spanner, AWS Aurora Multi-Region 활용**  

- **Event-Driven Architecture at Scale**  
  - 이벤트 기반 확장성과 장애 대응  
  - 실무 적용: **Kafka, RabbitMQ, Pulsar 비교 분석**  

---

## 📖 **5. 클라우드 네이티브 설계 (cloud_native_design/)**  
> **클라우드 환경에서 최적화된 아키텍처 패턴 학습**  

### 📚 학습 내용  
- **What is Cloud-Native?**  
  - 컨테이너, 마이크로서비스, DevOps 통합  
  - 실무 적용: **Kubernetes 기반 운영 환경 구성**  

- **Service Mesh (Istio, Linkerd)**  
  - 마이크로서비스 간 통신 및 보안 강화  
  - 실무 적용: **Istio 기반 트래픽 관리**  

- **Serverless & FaaS (Function as a Service)**  
  - 서버 관리 없이 코드 실행  
  - 실무 적용: **AWS Lambda, Google Cloud Functions**  

---

## 📖 **6. 서버리스 & 엣지 컴퓨팅 (serverless_edge_computing/)**  
> **최신 컴퓨팅 기술을 활용한 확장 가능한 서비스 설계**  

### 📚 학습 내용  
- **Serverless vs Containers**  
  - 서버리스 환경에서의 한계와 해결책  
  - 실무 적용: **Kubernetes와 Knative 비교 분석**  

- **Edge Computing & CDN Optimization**  
  - 사용자와 가까운 곳에서 데이터 처리  
  - 실무 적용: **Cloudflare Workers, AWS Lambda@Edge 활용**  

- **Low Latency Architectures**  
  - 실시간 서비스의 지연 시간 최적화  
  - 실무 적용: **5G 네트워크 기반 IoT 설계**  

---

## 📖 **7. 실전 SRE 사례 (sre_real_world/)**  
> **실제 장애 사례 분석 및 SRE 대응 전략 학습**  

### 📚 학습 내용  
- **Google의 SRE 운영 방식**  
  - 장애 예측 및 대응 전략  
  - 실무 적용: **SLI, SLO 기반 서비스 운영**  

- **Netflix의 Chaos Engineering 사례**  
  - 실전 장애 실험을 통한 시스템 안정성 강화  
  - 실무 적용: **Chaos Monkey 활용법**  

- **Amazon의 자동 복구 시스템**  
  - 대규모 장애 발생 시 빠른 복구  
  - 실무 적용: **AWS Auto Healing 아키텍처 적용**  

---

## 📖 **8. 멀티 테넌트 아키텍처 (multi_tenant_architecture/)**  
> **SaaS(Software as a Service) 환경에서 멀티 테넌트 설계**  

### 📚 학습 내용  
- **Single-Tenant vs Multi-Tenant**  
  - 각각의 장단점 및 적절한 사용 사례  
  - 실무 적용: **Slack, Shopify의 멀티 테넌트 설계 방식**  

- **Database Partitioning for Multi-Tenancy**  
  - 테넌트별 데이터 격리 방식  
  - 실무 적용: **Schema-per-Tenant vs Shared Database 방식 비교**  

- **Security & Isolation in Multi-Tenant Systems**  
  - 각 테넌트 간 보안 유지 방법  
  - 실무 적용: **RBAC & ABAC 기반 권한 관리**  