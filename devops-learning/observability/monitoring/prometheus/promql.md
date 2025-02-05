# PromQL을 활용한 메트릭 쿼리 작성 가이드

> **목표:**  
> - PromQL의 기본 문법과 사용 방법을 이해한다.
> - 다양한 메트릭 타입별 쿼리 작성 방법을 습득한다.
> - 실제 모니터링 상황에서 필요한 쿼리를 작성할 수 있다.
> - 성능 최적화를 위한 쿼리 작성 방법을 학습한다.

---

## 1. PromQL 기본 개념

### 1.1 PromQL이란?
PromQL(Prometheus Query Language)은 Prometheus에서 시계열 데이터를 조회하고 처리하기 위한 전용 쿼리 언어입니다. 시계열 데이터를 효과적으로 분석하고 집계할 수 있는 다양한 함수와 연산자를 제공합니다.

### 1.2 기본 데이터 타입
- **인스턴트 벡터:** 같은 시간대의 시계열 집합
- **레인지 벡터:** 일정 기간 동안의 시계열 데이터
- **스칼라:** 단순 숫자 값
- **문자열:** 텍스트 데이터

---

## 2. 기본 쿼리 작성

### 2.1 메트릭 조회
가장 기본적인 형태의 쿼리입니다.

```promql
# 기본 메트릭 조회
http_requests_total

# 레이블 선택자 사용
http_requests_total{job="api-server"}

# 레이블 다중 선택
http_requests_total{job="api-server", method="POST"}

# 정규식 사용
http_requests_total{job=~"api.*"}
```

### 2.2 시간 범위 선택
특정 시간 범위의 데이터를 조회합니다.

```promql
# 최근 5분간의 데이터
http_requests_total[5m]

# 1시간 동안의 HTTP 요청 수
rate(http_requests_total[1h])

# 특정 시점 기준 데이터
http_requests_total offset 5m
```

---

## 3. 연산자 활용

### 3.1 산술 연산자
기본적인 수학 연산을 수행합니다.

```promql
# 메모리 사용률 계산
(node_memory_Active_bytes / node_memory_MemTotal_bytes) * 100

# CPU 사용률 계산
rate(node_cpu_seconds_total{mode="user"}[5m]) * 100
```

### 3.2 비교 연산자
조건에 따른 필터링을 수행합니다.

```promql
# 500ms 이상 걸린 요청 필터링
http_request_duration_seconds > 0.5

# 에러율이 5% 이상인 서비스 찾기
(rate(http_requests_total{status="500"}[5m]) / 
 rate(http_requests_total[5m])) * 100 > 5
```

---

## 4. 집계 함수 사용

### 4.1 기본 집계 함수
데이터를 그룹화하고 집계합니다.

```promql
# 전체 HTTP 요청 합계
sum(http_requests_total)

# 엔드포인트별 평균 응답 시간
avg(rate(http_request_duration_seconds_sum[5m])) by (endpoint)

# 서비스별 최대 메모리 사용량
max(container_memory_usage_bytes) by (service_name)
```

### 4.2 시계열 집계 함수
시간에 따른 데이터 변화를 분석합니다.

```promql
# 초당 요청 수 계산
rate(http_requests_total[5m])

# 증가량 계산
increase(http_requests_total[1h])

# 이동 평균 계산
avg_over_time(http_requests_total[1h])
```

---

## 5. 실전 활용 사례

### 5.1 시스템 모니터링
시스템 리소스 사용량을 모니터링하는 쿼리입니다.

```promql
# CPU 사용률 모니터링
100 - (avg by (instance) (rate(node_cpu_seconds_total{mode="idle"}[5m])) * 100)

# 메모리 사용률 모니터링
(1 - (node_memory_MemAvailable_bytes / node_memory_MemTotal_bytes)) * 100

# 디스크 사용률 모니터링
(node_filesystem_size_bytes - node_filesystem_free_bytes) 
  / node_filesystem_size_bytes * 100
```

### 5.2 애플리케이션 모니터링
애플리케이션 성능을 모니터링하는 쿼리입니다.

```promql
# 에러율 계산
sum(rate(http_requests_total{status=~"5.."}[5m]))
  / sum(rate(http_requests_total[5m])) * 100

# 응답시간 분포 확인
histogram_quantile(0.95, sum(rate(http_request_duration_seconds_bucket[5m])) 
  by (le, service))

# 초당 트랜잭션 처리량
sum(rate(application_transactions_total[5m])) by (service)
```

---

## 6. 성능 최적화 팁

### 6.1 쿼리 최적화
쿼리 성능을 개선하는 방법입니다.

1. 필요한 레이블만 선택하여 데이터 양 줄이기
2. 적절한 시간 범위 설정하기
3. 복잡한 계산은 미리 기록 규칙으로 저장하기

```promql
# 비효율적인 쿼리
sum(rate(http_requests_total[5m])) by (job, instance, method, path)

# 최적화된 쿼리
sum(rate(http_requests_total[5m])) by (job, method)
```

### 6.2 기록 규칙 사용
자주 사용되는 복잡한 쿼리는 기록 규칙으로 저장합니다.

```yaml
# rules.yml
groups:
  - name: example
    rules:
      - record: job:http_requests:rate5m
        expr: sum(rate(http_requests_total[5m])) by (job)
```

---

## 7. 문제 해결과 디버깅

### 7.1 일반적인 문제 해결
- 데이터가 없는 경우 확인할 사항
- 레이블 매칭이 잘못된 경우
- 시간 범위 설정 오류

### 7.2 디버깅 팁
```promql
# 메트릭 존재 여부 확인
up

# 레이블 확인
label_values(http_requests_total, job)

# 데이터 샘플 확인
http_requests_total limit 5
```

---

## 참고 자료

- [PromQL 공식 문서](https://prometheus.io/docs/prometheus/latest/querying/basics/)
- [PromQL 쿼리 예제 모음](https://prometheus.io/docs/prometheus/latest/querying/examples/)
- [PromQL 최적화 가이드](https://prometheus.io/docs/practices/rules/)

---

## 마무리

PromQL은 강력한 쿼리 언어이지만, 실제 활용을 위해서는 많은 연습이 필요합니다. 이 가이드에서 다룬 기본 개념과 예제를 바탕으로 실제 환경에서 다양한 쿼리를 작성해보면서 실력을 향상시키시기 바랍니다.