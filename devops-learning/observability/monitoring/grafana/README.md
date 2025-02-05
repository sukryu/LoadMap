# 📂 Grafana 학습 개요

> **목표:**  
> - **Grafana를 활용하여 시스템 및 애플리케이션 메트릭을 시각화하고 분석하는 방법을 학습**한다.  
> - **Prometheus, Elasticsearch, Loki 등의 데이터 소스와 통합하여 모니터링 환경을 구축한다.**  
> - **Grafana 대시보드 구성 및 알림 설정을 익히고, 실전 환경에서 운영하는 방법을 학습한다.**  
> - **이론 → 도구 실습 → 프로젝트 적용 → 사례 분석의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **Grafana 학습을 기본 개념과 실습 중심으로 구성하며, 주요 기능별 학습 디렉토리를 포함합니다.**  

```
grafana/
├── introduction.md  # Grafana 개요 및 기본 개념
├── setup.md         # Grafana 설치 및 환경 설정
├── dashboards.md    # Grafana 대시보드 구성 및 시각화
├── integrations.md  # Prometheus 및 기타 데이터 소스와의 통합
├── alerting.md      # Grafana를 활용한 알림(Alerting) 설정
├── templating.md    # 대시보드 템플릿 활용 및 커스텀 변수를 통한 동적 시각화
└── README.md
```

---

## 📖 **1. Grafana 개요**
> **Grafana는 다양한 데이터 소스를 통합하여 대시보드 형태로 시각화하는 오픈소스 모니터링 도구입니다.**

- ✅ **Dashboards (대시보드):** 시스템 메트릭을 실시간으로 시각화  
- ✅ **Panels (패널):** 개별 메트릭을 그래프, 테이블, 게이지 등 다양한 방식으로 표시  
- ✅ **Data Sources (데이터 소스):** Prometheus, Elasticsearch, Loki 등과 연동  
- ✅ **Alerts (알림):** 특정 조건이 충족될 때 알림을 생성하여 운영 안정성 향상  
- ✅ **Templating (템플릿):** 변수 기반의 동적 대시보드 구성  

---

## 🏗 **2. 학습 내용**
### 📌 Grafana 기본 개념 및 설치
- **Grafana 아키텍처 및 개념 이해**
- **Grafana 설치 및 기본 환경 설정**
- **사용자 관리 및 권한 설정**

### 📌 데이터 소스 통합
- **Prometheus와 Grafana 연동**
- **Elasticsearch를 데이터 소스로 활용**
- **Loki를 통한 로그 데이터 시각화**
- **Cloud 데이터 소스(AWS CloudWatch, Google Stackdriver 등) 연동**

### 📌 대시보드 및 패널 구성
- **커스텀 대시보드 생성 및 패널 추가**
- **Panel 유형별 활용법 (Graph, Table, Gauge 등)**
- **Query 및 변수를 활용한 동적 대시보드 구성**

### 📌 알림 설정 (Alerting)
- **Grafana Alerting 기본 개념**
- **임계값 기반 경고 생성 및 알림 설정**
- **Slack, Email, PagerDuty 등의 알림 채널 연동**

---

## 🚀 **3. 실전 사례 분석**
> **Observability 도구를 활용하여 대규모 시스템을 운영하는 실제 사례를 분석합니다.**

- **Netflix** - Grafana를 활용한 대규모 스트리밍 서비스 모니터링
- **Uber** - 마이크로서비스 모니터링을 위한 Grafana 대시보드 구축
- **LinkedIn** - Grafana와 Prometheus를 통한 분산 시스템 모니터링

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → Grafana 개념과 데이터 시각화 원리 이해  
2. **도구 실습** → Grafana 설정 및 데이터 소스 연동  
3. **프로젝트 적용** → 실전 환경에서 Grafana 대시보드 운영  
4. **사례 분석** → 다양한 기업의 Grafana 운영 전략 연구  

---

## 📚 **5. 추천 리소스**
- **공식 문서:**  
  - [Grafana Docs](https://grafana.com/docs/)  
  - [Prometheus + Grafana 사용법](https://prometheus.io/docs/visualization/grafana/)  
- **GitHub 레포지토리:**  
  - [Awesome Grafana Dashboards](https://github.com/monitoringartist/grafana-dashboards)  
  - [Grafana Loki](https://github.com/grafana/loki)  
- **책:**  
  - _Practical Monitoring_ - Mike Julian  
  - _Observability Engineering_ - Charity Majors  

---

## ✅ **마무리**
이 문서는 **Grafana의 개념과 실무 활용법을 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 사례 분석**의 단계로 학습하며, **실무에서 Grafana를 활용하여 효과적으로 데이터 시각화를 수행하는 방법**을 다룹니다. 🚀

