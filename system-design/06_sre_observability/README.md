# 📂 **06_sre_observability (SRE & 모니터링)**
> **목표:**  
> - **Site Reliability Engineering (SRE)**의 핵심 개념을 익힌다.  
> - **모니터링, 로깅, 트레이싱, 알람 시스템, 장애 실험** 등을 학습한다.  
> - 실무에서 **안정적이고 신뢰할 수 있는 시스템을 운영하는 방법**을 배운다.

---

## 📌 **디렉토리 구조 및 학습 내용**
```
sre_observability/
├── sre_principles/            # SRE 원칙 및 운영 기법
├── monitoring_logging/        # 모니터링 및 로깅
├── tracing/                   # 분산 트레이싱
├── alerting/                  # 알람 시스템
├── chaos_engineering/         # 장애 실험 (Chaos Engineering)
├── error_budgeting/           # 에러 예산 및 SLA 관리
├── reliability_patterns/      # 신뢰성 설계 패턴
├── performance_optimization/  # 성능 최적화
└── real_world_examples/       # 실전 사례 분석
```

---

## 📖 **1. SRE 원칙 및 운영 기법 (sre_principles/)**
> **SRE의 개념과 Google이 제시한 운영 모델 학습**  

### 📚 학습 내용
- **What is SRE? (SRE란?)**
  - DevOps vs SRE 비교
  - 실무 적용: **Google SRE 팀의 운영 방식**

- **Toil Reduction (반복 작업 최소화)**
  - 반복적인 수작업을 자동화하는 방법
  - 실무 적용: **Terraform, Ansible을 활용한 자동화**

- **SLI/SLO/SLA 개념**
  - 서비스 수준 지표(SLI), 목표(SLO), 계약(SLA)
  - 실무 적용: **SLO 기반 장애 대응 전략**

---

## 📖 **2. 모니터링 및 로깅 (monitoring_logging/)**
> **서비스 상태를 실시간으로 파악하는 방법 학습**  

### 📚 학습 내용
- **What to Monitor? (무엇을 모니터링할 것인가?)**
  - 애플리케이션, 인프라, 네트워크 모니터링 항목
  - 실무 적용: **4 Golden Signals (Latency, Traffic, Errors, Saturation)**

- **Log Aggregation (로그 수집 및 분석)**
  - 중앙 집중형 로그 관리 시스템 구축
  - 실무 적용: **ELK Stack (Elasticsearch, Logstash, Kibana) 활용**

- **Metric-Based Monitoring (메트릭 기반 모니터링)**
  - Prometheus, Grafana를 활용한 실시간 모니터링
  - 실무 적용: **대규모 분산 시스템의 지표 수집 및 시각화**

---

## 📖 **3. 분산 트레이싱 (tracing/)**
> **마이크로서비스 환경에서 요청 흐름을 추적하는 방법 학습**  

### 📚 학습 내용
- **Why Tracing? (왜 트레이싱이 필요한가?)**
  - 마이크로서비스 간 호출을 분석하는 중요성
  - 실무 적용: **서비스 병목 지점 및 성능 최적화**

- **OpenTelemetry & Jaeger**
  - 분산 트레이싱을 위한 오픈소스 도구
  - 실무 적용: **Jaeger를 활용한 전체 요청 흐름 추적**

- **Trace ID & Sampling**
  - 요청별로 추적 ID를 부여하여 흐름 분석
  - 실무 적용: **고트래픽 서비스에서 샘플링 기법 활용**

---

## 📖 **4. 알람 시스템 (alerting/)**
> **장애를 빠르게 감지하고 대응하는 방법 학습**  

### 📚 학습 내용
- **Threshold-Based vs Anomaly Detection**
  - 정적 임계값과 AI 기반 이상 탐지 비교
  - 실무 적용: **Prometheus AlertManager 활용**

- **PagerDuty & On-Call Management**
  - 엔지니어 온콜 대응 체계 구축
  - 실무 적용: **Slack, SMS를 통한 실시간 알람 전파**

- **Runbook & Incident Response**
  - 장애 발생 시 대응 절차 문서화
  - 실무 적용: **장애 대응 체크리스트 자동화**

---

## 📖 **5. 장애 실험 (chaos_engineering/)**
> **실제 장애를 발생시켜 시스템의 복원력을 검증하는 기법 학습**  

### 📚 학습 내용
- **What is Chaos Engineering? (카오스 엔지니어링이란?)**
  - 예상치 못한 장애 상황을 실험적으로 유도
  - 실무 적용: **Netflix의 Chaos Monkey 사례 분석**

- **Failure Injection & Fault Tolerance**
  - 네트워크 지연, 서비스 다운 시뮬레이션
  - 실무 적용: **AWS Fault Injection Simulator 활용**

- **Steady State Hypothesis**
  - 정상 상태를 정의하고 비교하는 방식
  - 실무 적용: **SRE 팀이 장애 실험을 설계하는 방법**

---

## 📖 **6. 에러 예산 및 SLA 관리 (error_budgeting/)**
> **서비스 안정성과 개발 속도 간 균형을 맞추는 전략 학습**  

### 📚 학습 내용
- **Error Budgeting (에러 예산이란?)**
  - 일정 수준의 장애를 허용하고 혁신 가속
  - 실무 적용: **SLO 기반 배포 전략 결정**

- **SLA 계약 및 고객 대응**
  - SLA 미준수 시 보상 및 법적 대응 방안
  - 실무 적용: **AWS, Google Cloud의 SLA 정책 비교**

- **Blameless Postmortem (책임 추궁 없는 사후 분석)**
  - 장애 분석에서 사람을 비난하지 않는 문화
  - 실무 적용: **사고 보고서(Incident Report) 작성 방법**

---

## 📖 **7. 신뢰성 설계 패턴 (reliability_patterns/)**
> **안정적인 시스템을 구축하기 위한 디자인 패턴 학습**  

### 📚 학습 내용
- **Retry & Backoff Strategy (재시도 및 백오프)**
  - 네트워크 장애 발생 시 재시도 전략
  - 실무 적용: **Exponential Backoff 적용 방법**

- **Circuit Breaker Pattern (서킷 브레이커)**
  - 특정 서비스 장애 시 빠르게 차단하여 전체 장애 방지
  - 실무 적용: **Resilience4j, Netflix Hystrix 활용**

- **Graceful Degradation (우아한 성능 저하)**
  - 장애 발생 시 최소한의 기능 유지
  - 실무 적용: **캐시 백업, 기능 토글 활용 사례**

---

## 📖 **8. 성능 최적화 (performance_optimization/)**
> **시스템 성능을 분석하고 최적화하는 방법 학습**  

### 📚 학습 내용
- **Profiling & Bottleneck Detection**
  - 성능 병목 지점 찾기
  - 실무 적용: **New Relic, Datadog 활용**

- **Latency Optimization**
  - 네트워크 및 DB 지연시간 단축 방법
  - 실무 적용: **CDN 활용 및 데이터베이스 튜닝**

- **Scaling Strategies (확장 전략)**
  - 수평 확장 vs 수직 확장 최적화
  - 실무 적용: **Kubernetes 자동 확장(Auto Scaling)**

---

## 📖 **9. 실전 사례 분석 (real_world_examples/)**
> **SRE 및 모니터링 기법을 활용한 실제 기업 사례 학습**  

### 📚 학습 내용
- **Google의 SRE 문화와 운영 방식**
- **Netflix의 Chaos Engineering 적용 사례**
- **Amazon의 장애 대응 및 자동 복구 전략**
- **Uber의 분산 트레이싱 및 모니터링 시스템**
- **Facebook의 로그 수집 및 분석 아키텍처**