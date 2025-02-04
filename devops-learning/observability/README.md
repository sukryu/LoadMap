# 📂 Observability 학습 개요

> **목표:**  
> - **Observability(가시성)의 개념과 실무 적용 방법을 학습**한다.  
> - **모니터링, 로깅, 트레이싱 도구를 활용하여 시스템 성능 및 안정성을 분석한다.**  
> - **Prometheus, Grafana, ELK Stack, Jaeger 등의 도구를 익히고, 실전 환경에서 운영하는 방법을 학습한다.**  
> - **이론 → 도구 실습 → 프로젝트 적용 → 사례 분석의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **각 디렉토리는 Observability의 핵심 개념과 도구를 포함하며, 하위 디렉토리는 보다 상세한 학습 주제를 다룹니다.**  

```
observability/
├── monitoring
│   ├── prometheus
│   └── grafana
│
├── logging
│   └── elk-stack
│
└── tracing
    └── jaeger
```

---

## 📖 **1. 핵심 개념 개요**
> **Observability는 시스템의 내부 상태를 효과적으로 파악할 수 있도록 모니터링, 로깅, 트레이싱을 포함하는 개념입니다.**

- ✅ **Monitoring (모니터링):** 시스템 및 애플리케이션의 성능을 실시간으로 추적  
- ✅ **Logging (로깅):** 애플리케이션 및 시스템 이벤트를 기록하여 분석  
- ✅ **Tracing (트레이싱):** 분산 시스템에서 요청 흐름을 추적하여 성능 병목 분석  

---

## 🏗 **2. 학습 내용**
### 📌 Monitoring (Prometheus & Grafana)
- **Prometheus 기본 개념 및 설치**
- **PromQL을 활용한 메트릭 쿼리 작성**
- **Grafana를 활용한 대시보드 시각화**

### 📌 Logging (ELK Stack)
- **Elasticsearch, Logstash, Kibana 기본 개념**
- **로그 수집 및 분석 파이프라인 구축**
- **로그 필터링 및 인덱싱 전략**

### 📌 Tracing (Jaeger)
- **분산 트레이싱 개념 및 필요성**
- **Jaeger를 활용한 요청 흐름 분석**
- **서비스 성능 최적화를 위한 트레이스 데이터 활용**

---

## 🚀 **3. 실전 사례 분석**
> **Observability 도구를 활용하여 대규모 분산 시스템을 운영하는 실제 기업 사례를 분석합니다.**

- **Netflix** - 분산 환경에서의 트레이싱 및 로깅  
- **Uber** - Jaeger를 활용한 마이크로서비스 성능 분석  
- **LinkedIn** - Prometheus를 통한 실시간 시스템 모니터링  

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → Observability 개념과 원리 이해  
2. **도구 실습** → Prometheus, Grafana, ELK Stack, Jaeger 실습 진행  
3. **프로젝트 적용** → 실전 환경에서 Observability 도입 및 운영  
4. **사례 분석** → 다양한 기업의 Observability 운영 전략 연구  

---

## 📚 **5. 추천 리소스**
- **책:**  
  - _Observability Engineering_ - Charity Majors  
  - _Distributed Systems Observability_ - Cindy Sridharan  

- **GitHub 레포지토리:**  
  - [Awesome Prometheus](https://github.com/roaldnefs/awesome-prometheus)  
  - [Awesome Logging](https://github.com/ozlerhakan/awesome-logging)  

- **공식 문서:**  
  - [Prometheus Docs](https://prometheus.io/docs/)  
  - [Grafana Docs](https://grafana.com/docs/)  
  - [ELK Stack Docs](https://www.elastic.co/what-is/elk-stack)  
  - [Jaeger Docs](https://www.jaegertracing.io/docs/)  

---

## ✅ **마무리**
이 문서는 **Observability의 필수 개념과 도구를 효과적으로 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 사례 분석**의 단계로 학습하며, **실무에서 Observability를 효과적으로 운영하는 방법**을 다룹니다. 🚀

