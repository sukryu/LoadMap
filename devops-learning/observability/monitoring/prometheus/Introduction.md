# Prometheus 개요 및 기본 개념

> **목표:**  
> - Prometheus의 핵심 개념과 작동 방식을 이해한다.
> - 메트릭 수집과 모니터링의 기본 구성 요소를 파악한다.
> - prometheus.yml 파일의 구조와 작성 방법을 습득한다.
> - Prometheus를 실제 프로젝트에 적용할 수 있는 기초를 다진다.

---

## 1. Prometheus란?

### 정의
Prometheus는 시스템과 서비스의 메트릭을 수집하고 저장하여 모니터링하는 오픈소스 도구입니다. 시계열 데이터베이스를 기반으로 하며, 강력한 쿼리 언어(PromQL)를 제공하여 수집된 데이터를 효과적으로 분석할 수 있습니다.

### 왜 필요한가?
- **실시간 모니터링:** 시스템의 현재 상태를 실시간으로 파악할 수 있습니다.
- **성능 분석:** 시스템의 병목 현상과 성능 이슈를 조기에 발견할 수 있습니다.
- **장애 예측:** 비정상적인 패턴을 감지하여 장애를 사전에 예방할 수 있습니다.
- **확장성:** 마이크로서비스 아키텍처와 같은 분산 환경에서도 효과적으로 작동합니다.

---

## 2. 핵심 구성 요소

### 2.1 메트릭(Metrics)
- 시스템의 상태를 수치화한 측정값입니다.
- CPU 사용률, 메모리 사용량, 요청 처리 시간 등을 포함합니다.
- 네 가지 기본 메트릭 타입을 제공합니다:
  - Counter: 증가만 하는 값 (예: 총 요청 수)
  - Gauge: 증가하거나 감소할 수 있는 값 (예: 메모리 사용량)
  - Histogram: 값의 분포를 측정 (예: 요청 처리 시간의 분포)
  - Summary: Histogram과 유사하나 계산 방식이 다름

### 2.2 스크레이핑(Scraping)
- Prometheus가 메트릭을 수집하는 과정입니다.
- 일정 주기로 타겟 시스템의 HTTP 엔드포인트에 접근하여 메트릭을 가져옵니다.
- 기본적으로 '/metrics' 경로에서 메트릭을 수집합니다.

### 2.3 익스포터(Exporter)
- Prometheus가 이해할 수 있는 형식으로 메트릭을 노출하는 도구입니다.
- 다양한 시스템의 메트릭을 수집할 수 있게 해줍니다.
- 주요 익스포터 예시:
  - Node Exporter: 호스트 시스템 메트릭
  - MySQL Exporter: MySQL 서버 메트릭
  - Blackbox Exporter: HTTP, HTTPS, DNS 등의 프로브

---

## 3. prometheus.yml 파일

### 3.1 기본 구조
```yaml
global:
  scrape_interval: 15s
  evaluation_interval: 15s

scrape_configs:
  - job_name: 'prometheus'
    static_configs:
      - targets: ['localhost:9090']

  - job_name: 'node'
    static_configs:
      - targets: ['localhost:9100']

alerting:
  alertmanagers:
    - static_configs:
        - targets: ['localhost:9093']

rule_files:
  - 'rules/*.yml'
```

### 3.2 주요 설정 항목 설명
- **global:** 전역 설정을 정의
  - scrape_interval: 메트릭 수집 주기
  - evaluation_interval: 규칙 평가 주기
- **scrape_configs:** 메트릭을 수집할 타겟 정의
- **alerting:** 알림 관리자 설정
- **rule_files:** 규칙 파일 위치 지정

---

## 4. 실제 동작 예시

### 4.1 기본적인 워크플로우
1. Prometheus 서버 시작
2. 설정된 간격으로 타겟 시스템의 메트릭 수집
3. 수집된 데이터를 시계열 데이터베이스에 저장
4. PromQL을 통한 데이터 조회 및 분석

### 4.2 간단한 설정 예제
```yaml
# 기본적인 Node Exporter 모니터링 설정
global:
  scrape_interval: 15s

scrape_configs:
  - job_name: 'node'
    static_configs:
      - targets: ['localhost:9100']
    metrics_path: '/metrics'
    scheme: 'http'
```

---

## 5. 장단점

### 장점
- **풀 방식:** 중앙 집중식 구성으로 관리가 용이
- **강력한 쿼리:** PromQL을 통한 유연한 데이터 분석
- **확장성:** 다양한 익스포터와 통합 가능
- **시각화:** Grafana 등과 쉽게 연동

### 단점
- **학습 곡선:** PromQL과 시계열 데이터 개념 이해 필요
- **장기 저장:** 대규모 시계열 데이터 저장에 별도 솔루션 필요
- **푸시 미지원:** 기본적으로 풀 방식만 지원

---

## 6. 시작하기

### 6.1 기본 단계
1. Prometheus 설치
2. prometheus.yml 파일 구성
3. 필요한 익스포터 설치
4. 서비스 시작 및 웹 UI 확인

### 6.2 주의사항
- 메트릭 수집 주기 적절히 설정
- 저장 용량 고려
- 보안 설정 주의 (인증/인가)

---

## 참고 자료

- [Prometheus 공식 문서](https://prometheus.io/docs/introduction/overview/)
- [Prometheus 설치 가이드](https://prometheus.io/docs/prometheus/latest/getting_started/)
- [PromQL 쿼리 가이드](https://prometheus.io/docs/prometheus/latest/querying/basics/)

---

## 마무리

Prometheus는 현대 시스템 모니터링에서 필수적인 도구입니다. 이 문서에서 다룬 기본 개념을 이해하고 실제 환경에서 점진적으로 적용하면서, 더 복잡한 모니터링 시스템을 구축해 나갈 수 있습니다.