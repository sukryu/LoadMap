# 📂 Prometheus 학습 개요

> **목표:**  
> - **Prometheus를 활용하여 시스템 및 애플리케이션의 성능 메트릭을 수집하고 분석하는 방법을 학습**한다.  
> - **PromQL을 활용하여 실시간 모니터링 및 경고(Alerting) 시스템을 구축한다.**  
> - **Exporter를 활용한 메트릭 수집 및 Grafana와 연동하여 대시보드를 구성한다.**  
> - **이론 → 도구 실습 → 프로젝트 적용 → 사례 분석의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **Prometheus 학습을 기본 개념과 실습 중심으로 구성하며, 주요 기능별 학습 디렉토리를 포함합니다.**  

```
prometheus/
├── introduction.md  # Prometheus 개요 및 기본 개념
├── setup.md         # Prometheus 설치 및 환경 설정
├── promql.md        # PromQL을 활용한 메트릭 쿼리 작성
├── alerting.md      # AlertManager를 활용한 알림 설정
├── exporters.md     # Exporter를 활용한 메트릭 수집
├── best_practices.md # Prometheus 성능 최적화 및 운영 전략
└── README.md
```

---

## 📖 **1. Prometheus 개요**
> **Prometheus는 시계열(time-series) 기반의 오픈소스 모니터링 및 경고 시스템입니다.**

- ✅ **Time-Series Data (시계열 데이터):** 시간과 함께 측정된 메트릭 데이터 저장  
- ✅ **Pull-Based Architecture (풀 기반 아키텍처):** 모니터링 대상이 Prometheus 서버에서 주기적으로 데이터를 가져감  
- ✅ **PromQL (Prometheus Query Language):** Prometheus의 강력한 쿼리 언어  
- ✅ **Exporters (익스포터):** 외부 시스템에서 메트릭을 수집하는 도구  
- ✅ **AlertManager (알림 매니저):** 특정 조건이 충족될 때 경고 전송  

---

## 🏗 **2. 학습 내용**
### 📌 Prometheus 기본 개념 및 설치
- **Prometheus 아키텍처 및 개념 이해**
- **Prometheus 설치 및 환경 설정**
- **스크래핑 설정 및 타겟 구성**

### 📌 PromQL을 활용한 데이터 분석
- **PromQL 기본 문법 및 사용법**
- **시계열 데이터 집계 및 필터링**
- **Grafana와 연동하여 대시보드 구성**

### 📌 AlertManager를 활용한 경고 시스템 구축
- **AlertManager 개념 및 역할 이해**
- **경고(Alerting) 규칙 작성 및 알림 전송**
- **Slack, Email, PagerDuty 등의 알림 채널 연동**

### 📌 Exporters를 활용한 모니터링
- **Node Exporter를 활용한 시스템 모니터링**
- **Custom Exporter 개발 및 활용**
- **Application Metrics (애플리케이션 메트릭) 수집 방법**

### 📌 Prometheus 운영 및 최적화
- **Prometheus 데이터 보존 및 성능 최적화**
- **장애 복구 및 백업 전략**
- **고가용성을 위한 Prometheus Federation 구성**

---

## 🚀 **3. 실전 사례 분석**
> **Prometheus를 활용하여 대규모 시스템을 운영하는 실제 사례를 분석합니다.**

- **Netflix** - 대규모 스트리밍 시스템에서 Prometheus 모니터링 활용
- **Uber** - 마이크로서비스 환경에서 Prometheus 기반 모니터링 구축
- **Red Hat OpenShift** - Kubernetes 클러스터에서 Prometheus 사용 사례

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → Prometheus 개념과 아키텍처 이해  
2. **도구 실습** → Prometheus 설치 및 PromQL 실습  
3. **프로젝트 적용** → 실제 시스템에 Prometheus 기반 모니터링 적용  
4. **사례 분석** → 다양한 기업의 Prometheus 운영 전략 연구  

---

## 📚 **5. 추천 리소스**
- **공식 문서:**  
  - [Prometheus Docs](https://prometheus.io/docs/)  
  - [Prometheus Best Practices](https://prometheus.io/docs/practices/)  
- **GitHub 레포지토리:**  
  - [Prometheus Exporters](https://github.com/prometheus)  
  - [Awesome Prometheus](https://github.com/roaldnefs/awesome-prometheus)  
- **책:**  
  - _Monitoring with Prometheus_ - James Turnbull  
  - _Cloud Native Monitoring with Prometheus_ - Sayantika Banik  

---

## ✅ **마무리**
이 문서는 **Prometheus의 개념과 실무 활용법을 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 사례 분석**의 단계로 학습하며, **실무에서 Prometheus를 활용하여 효과적으로 시스템을 모니터링하는 방법**을 다룹니다. 🚀

