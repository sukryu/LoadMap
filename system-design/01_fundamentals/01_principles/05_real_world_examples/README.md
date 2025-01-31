# 📂 **01_fundamentals/principles/real_world_examples/README.md**  
> **목표:**  
> - 시스템 설계 원칙이 **실제 서비스에서 어떻게 적용되는지** 학습한다.  
> - SOLID, DRY, KISS, 확장성 원칙 등의 **실전 사례를 분석**하고, 설계 트레이드오프를 이해한다.  
> - 대규모 시스템에서 발생하는 문제와 그 해결 방법을 익힌다.  

---

## 📌 **디렉토리 구조 및 학습 내용**  
```
real_world_examples/
├── netflix_architecture/         # Netflix의 확장성 및 마이크로서비스 아키텍처
├── uber_scalability/             # Uber의 확장성 및 실시간 데이터 처리
├── facebook_consistency/         # Facebook의 데이터 일관성 및 GraphQL 설계
├── google_sre/                   # Google의 SRE 및 장애 대응 전략
├── amazon_microservices/         # Amazon의 마이크로서비스 및 서버리스 적용
└── spotify_event_driven/         # Spotify의 이벤트 기반 아키텍처
```

---

## 🎬 **1. Netflix의 확장성 및 마이크로서비스 아키텍처 (netflix_architecture/)**  
> **Netflix는 어떻게 글로벌 스트리밍 서비스를 운영할까?**  

### 📚 학습 내용  
- **Netflix의 아키텍처 개요**  
  - 마이크로서비스 전환 과정  
  - 실무 적용: **MSA 도입 시 고려해야 할 트레이드오프**  

- **확장성을 위한 설계 패턴**  
  - API Gateway와 서비스 간 통신 방식  
  - 실무 적용: **Zuul, Eureka, Hystrix 활용 사례**  

- **장애 대응 및 복원력**  
  - Netflix의 **Chaos Engineering** 전략  
  - 실무 적용: **실제 장애 테스트 방법 및 트래픽 분산 전략**  

> 📍 자세한 내용은 `netflix_architecture/README.md` 참고  

---

## 🚖 **2. Uber의 확장성 및 실시간 데이터 처리 (uber_scalability/)**  
> **Uber는 수백만 개의 실시간 요청을 어떻게 처리할까?**  

### 📚 학습 내용  
- **Uber의 실시간 시스템 개요**  
  - 확장성과 낮은 지연 시간을 보장하는 방법  
  - 실무 적용: **Geo-Partitioning 및 로드 밸런싱 활용**  

- **Kafka를 활용한 데이터 스트리밍**  
  - 실시간 위치 추적 및 데이터 동기화  
  - 실무 적용: **메시지 큐 기반 데이터 처리 방식**  

- **요금 계산 및 최적 경로 탐색 알고리즘**  
  - GPS 데이터 기반 실시간 요금 계산  
  - 실무 적용: **Dijkstra 알고리즘 및 A* 탐색 적용 사례**  

> 📍 자세한 내용은 `uber_scalability/README.md` 참고  

---

## 🌐 **3. Facebook의 데이터 일관성 및 GraphQL 설계 (facebook_consistency/)**  
> **Facebook은 전 세계 수십억 사용자의 데이터를 어떻게 관리할까?**  

### 📚 학습 내용  
- **Facebook의 Graph 데이터 모델**  
  - GraphQL을 활용한 데이터 쿼리 최적화  
  - 실무 적용: **REST API 대비 GraphQL의 장점 분석**  

- **일관성 모델 및 분산 데이터베이스 설계**  
  - CAP 이론을 적용한 Facebook의 일관성 전략  
  - 실무 적용: **최종적 일관성과 강한 일관성 비교 사례**  

- **피드 정렬 및 추천 알고리즘**  
  - 머신러닝을 활용한 개인화 추천 시스템  
  - 실무 적용: **Engagement 최적화를 위한 Graph Ranking 알고리즘**  

> 📍 자세한 내용은 `facebook_consistency/README.md` 참고  

---

## 🔧 **4. Google의 SRE 및 장애 대응 전략 (google_sre/)**  
> **Google은 어떻게 SRE(Site Reliability Engineering)를 운영할까?**  

### 📚 학습 내용  
- **Google의 SRE 원칙**  
  - 서비스 신뢰성을 보장하는 핵심 전략  
  - 실무 적용: **SLI, SLO, SLA 개념 및 적용 방법**  

- **장애 대응 및 복구 전략**  
  - Google의 **Blameless Postmortem** 프로세스  
  - 실무 적용: **장애 발생 후 분석 및 개선 방법**  

- **에러 예산(Error Budget) 관리 기법**  
  - SRE와 개발 팀 간 균형을 맞추는 방법  
  - 실무 적용: **서비스 배포 속도 조절 및 안정성 유지 방법**  

> 📍 자세한 내용은 `google_sre/README.md` 참고  

---

## 🛒 **5. Amazon의 마이크로서비스 및 서버리스 적용 (amazon_microservices/)**  
> **Amazon은 어떻게 초대형 이커머스 시스템을 운영할까?**  

### 📚 학습 내용  
- **Amazon의 마이크로서비스 도입 사례**  
  - AWS 기반 MSA 설계 방식  
  - 실무 적용: **Lambda, DynamoDB, API Gateway 활용 사례**  

- **추천 시스템 및 개인화 엔진**  
  - 사용자 행동 데이터를 활용한 최적 추천  
  - 실무 적용: **AWS Personalize 및 머신러닝 모델 활용**  

- **서버리스 아키텍처 적용 사례**  
  - 주문 처리 시스템을 서버리스로 구축한 방식  
  - 실무 적용: **Event-Driven Architecture 기반 주문 처리 최적화**  

> 📍 자세한 내용은 `amazon_microservices/README.md` 참고  

---

## 🎵 **6. Spotify의 이벤트 기반 아키텍처 (spotify_event_driven/)**  
> **Spotify는 실시간 음악 스트리밍을 어떻게 운영할까?**  

### 📚 학습 내용  
- **Spotify의 이벤트 기반 마이크로서비스**  
  - Kafka 기반 비동기 메시징 아키텍처  
  - 실무 적용: **고가용성을 위한 멀티 리전 이벤트 처리**  

- **음악 추천 및 데이터 분석 파이프라인**  
  - 실시간 추천 엔진 및 데이터 분석 모델  
  - 실무 적용: **Spark, Flink 기반 실시간 데이터 처리**  

- **사용자 세션 및 동기화 기술**  
  - 여러 디바이스에서 동기화되는 음악 재생 시스템  
  - 실무 적용: **WebSockets 및 gRPC 활용한 실시간 동기화**  

> 📍 자세한 내용은 `spotify_event_driven/README.md` 참고  

---

## 🔍 **학습 방법**  
1. **각 기업의 시스템 설계를 분석한다.**  
2. **설계 원칙과 패턴이 어떻게 적용되었는지 파악한다.**  
3. **각 시스템에서 발생한 문제와 해결 방법을 학습한다.**  
4. **유사한 문제를 해결하는 실습 프로젝트를 진행한다.**  

---

## 📚 **추천 학습 리소스**  
- **"Site Reliability Engineering" - Google SRE Team**  
- **"Building Microservices" - Sam Newman**  
- **"Designing Data-Intensive Applications" - Martin Kleppmann**  
- **Netflix, Uber, Facebook, Amazon, Google의 기술 블로그 및 아키텍처 문서**  

---

## ✅ **마무리**  
이 디렉토리는 **실제 기업들의 시스템 설계를 분석하고, 확장성과 성능을 고려한 최적의 설계를 익히기 위한 공간**입니다.  
각 사례를 **단순한 학습이 아니라, 트레이드오프를 고민하면서 적용할 수 있도록 학습하는 것이 중요합니다.** 🚀  