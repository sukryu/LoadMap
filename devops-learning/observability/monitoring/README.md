# 📂 Monitoring 학습 개요

> **목표:**  
> - **모니터링(Monitoring)의 개념과 실무 적용 방법을 학습**한다.  
> - **Prometheus 및 Grafana를 활용하여 시스템의 성능 및 상태를 실시간으로 분석하는 방법을 익힌다.**  
> - **메트릭 수집, 알림 설정, 대시보드 시각화 등의 기술을 실습을 통해 익힌다.**  
> - **이론 → 도구 실습 → 프로젝트 적용 → 사례 분석의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **Monitoring 학습을 Prometheus와 Grafana 중심으로 진행하며, 각각의 주요 개념과 실습 내용을 포함합니다.**  

```
monitoring/
├── prometheus
│   ├── introduction.md  # Prometheus 개요 및 기본 개념
│   ├── setup.md         # Prometheus 설치 및 환경 설정
│   ├── promql.md        # PromQL을 활용한 메트릭 쿼리 작성
│   ├── alerting.md      # 알림(Alerting) 설정
│   ├── exporters.md     # Exporter를 활용한 메트릭 수집
│   └── README.md
│
└── grafana
    ├── introduction.md  # Grafana 개요 및 기본 개념
    ├── setup.md         # Grafana 설치 및 환경 설정
    ├── dashboards.md    # Grafana 대시보드 시각화
    ├── integrations.md  # Prometheus 및 기타 도구와의 통합
    └── README.md
```

---

## 📖 **1. Monitoring 개요**
> **Monitoring은 시스템과 애플리케이션의 성능 및 상태를 실시간으로 측정하고 분석하는 과정입니다.**

- ✅ **Metrics (메트릭):** 시스템 상태를 수량화한 데이터 (예: CPU 사용량, 메모리 사용률)  
- ✅ **Alerting (알림):** 임계값을 초과하는 경우 자동으로 경고 전송  
- ✅ **Visualization (시각화):** 대시보드를 통해 메트릭을 실시간으로 모니터링  
- ✅ **Data Retention (데이터 보존):** 장기적인 분석을 위한 데이터 저장  

---

## 🏗 **2. 학습 내용**
### 📌 Prometheus
- **Prometheus 아키텍처 및 개념 이해**
- **Prometheus 설치 및 설정**
- **PromQL을 활용한 메트릭 쿼리 작성**
- **Exporter를 활용한 데이터 수집 및 커스텀 메트릭 작성**
- **AlertManager를 활용한 알림 설정**

### 📌 Grafana
- **Grafana의 역할과 기본 개념**
- **Grafana 설치 및 Prometheus 데이터 소스 연결**
- **커스텀 대시보드 구성 및 시각화**
- **다양한 데이터 소스(MySQL, Elasticsearch 등)와의 통합**

---

## 🚀 **3. 실전 사례 분석**
> **Observability 도구를 활용하여 대규모 시스템을 운영하는 실제 사례를 분석합니다.**

- **Netflix** - 실시간 스트리밍 서비스에서의 메트릭 모니터링
- **Google** - Kubernetes 기반의 대규모 모니터링 시스템 구축
- **Uber** - Prometheus와 Grafana를 활용한 서비스 성능 분석

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → Monitoring 개념과 도구 원리 이해  
2. **도구 실습** → Prometheus 및 Grafana 설정 및 활용  
3. **프로젝트 적용** → 실제 프로젝트에서 모니터링 도입 및 운영  
4. **사례 분석** → 다양한 기업의 모니터링 운영 전략 연구  

---

## 📚 **5. 추천 리소스**
- **공식 문서:**  
  - [Prometheus Docs](https://prometheus.io/docs/)  
  - [Grafana Docs](https://grafana.com/docs/)  
- **GitHub 레포지토리:**  
  - [Awesome Prometheus](https://github.com/roaldnefs/awesome-prometheus)  
  - [Awesome Grafana Dashboards](https://github.com/monitoringartist/grafana-dashboards)  
- **책:**  
  - _Monitoring with Prometheus_ - James Turnbull  
  - _Practical Monitoring_ - Mike Julian  

---

## ✅ **마무리**
이 문서는 **Monitoring의 핵심 개념과 Prometheus, Grafana의 활용 방법을 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 사례 분석**의 단계로 학습하며, **실무에서 효과적으로 모니터링을 운영하는 방법**을 다룹니다. 🚀

