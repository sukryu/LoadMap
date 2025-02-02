# 📂 SRE & 모니터링 - 06_sre_observability

> **목표:**  
> - 사이트 신뢰성 엔지니어링(SRE) 원칙과 운영 기법을 학습한다.  
> - 모니터링, 로깅, 트레이싱을 포함한 관찰 가능성(Observability) 전략을 이해하고 실무에서 활용한다.  
> - 시스템의 가용성과 성능을 최적화하기 위한 장애 대응 및 신뢰성 설계를 연구한다.

---

## 📌 **디렉토리 구조**
```
06_sre_observability/          # SRE 및 모니터링 개념 학습
├── sre_principles/            # SRE 원칙 및 운영
├── monitoring/                # 모니터링 및 로깅
├── tracing/                   # 분산 트레이싱
├── alerting/                  # 알람 시스템
├── chaos_engineering/         # 장애 실험 (Chaos Engineering)
├── reliability_patterns/      # 신뢰성 설계 패턴
├── performance_optimization/  # 성능 최적화
└── README.md
```

---

## 📖 **1. 개념 개요**
> **SRE는 소프트웨어 엔지니어링을 활용하여 대규모 시스템의 신뢰성을 보장하는 운영 방식이다.**

- ✅ **왜 중요한가?**  
  - 시스템 가용성과 성능을 보장하기 위해 필수적이다.
  - 장애 대응 및 복구 전략을 수립하여 비즈니스 연속성을 확보할 수 있다.
  - 운영 비용을 최적화하고, 시스템의 자동화를 통해 효율성을 향상시킨다.

- ✅ **어떤 문제를 해결하는가?**  
  - 예기치 않은 장애 및 성능 저하 문제 해결
  - 실시간 모니터링을 통해 문제를 사전에 감지 및 대응
  - 신뢰성을 유지하면서 지속적인 배포 및 운영을 가능하게 함

- ✅ **실무에서 어떻게 적용하는가?**  
  - SLO(Service Level Objective), SLI(Service Level Indicator), SLA(Service Level Agreement)를 설정하여 운영 지표 관리
  - 로그 및 트레이싱을 활용하여 장애 원인 분석 및 대응
  - 알람 시스템과 자동화된 장애 대응을 통한 운영 최적화

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **SRE 원칙 및 운영 (sre_principles/)**
  - Google SRE 원칙
  - SLO/SLI/SLA 개념 및 적용 사례

- **모니터링 및 로깅 (monitoring/)**
  - Prometheus, Grafana, New Relic을 활용한 시스템 모니터링
  - 로그 분석 및 중앙 집중식 로깅 (ELK, Loki, Fluentd)

- **분산 트레이싱 (tracing/)**
  - OpenTelemetry, Jaeger, Zipkin을 활용한 트랜잭션 추적
  - 마이크로서비스 환경에서 성능 병목 분석

- **알람 시스템 (alerting/)**
  - Prometheus Alertmanager, PagerDuty, OpsGenie 등의 알람 시스템 구축
  - 자동화된 장애 감지 및 대응 전략

- **장애 실험 (chaos_engineering/)**
  - Netflix Chaos Monkey를 활용한 장애 시뮬레이션
  - 무작위 장애 테스트를 통한 내결함성(Fault Tolerance) 강화

- **신뢰성 설계 패턴 (reliability_patterns/)**
  - Circuit Breaker, Bulkhead, Retry 패턴 적용
  - 가용성 극대화를 위한 Blue-Green Deployment 및 Canary Deployment

- **성능 최적화 (performance_optimization/)**
  - 시스템 부하 테스트 및 성능 프로파일링
  - 캐싱 및 데이터베이스 최적화 전략

---

## 🚀 **3. 실전 사례 분석**
> **대규모 서비스가 SRE 및 모니터링을 어떻게 활용하는가?**

- **Google** - SRE 원칙 기반의 운영 및 장애 대응 사례
- **Netflix** - Chaos Engineering을 활용한 장애 대응 및 복구 전략
- **Facebook** - 분산 트레이싱 및 로깅을 활용한 성능 최적화

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ 운영 패턴 학습  
3️⃣ 실제 사례 분석  
4️⃣ 코드 실습 진행  
5️⃣ 트레이드오프 분석  

---

## 📚 **5. 추천 리소스**
- 📖 _Site Reliability Engineering_ - Google SRE 팀  
- 📖 _The Practice of Cloud System Administration_ - Thomas Limoncelli  
- 📖 _Chaos Engineering_ - Casey Rosenthal  
- 📌 [Google SRE Book](https://sre.google/books/)  
- 📌 [Awesome SRE](https://github.com/dastergon/awesome-sre)  

---

## ✅ **마무리**
이 문서는 **SRE 및 모니터링의 핵심 개념을 학습하는 단계**입니다.
이론 → 패턴 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며,
실무에서 신뢰성과 성능을 고려한 운영 및 장애 대응을 설계할 수 있도록 합니다. 🚀

