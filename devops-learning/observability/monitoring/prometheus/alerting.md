# AlertManager를 활용한 알림 설정 가이드

> **목표:**  
> - AlertManager의 기본 개념과 작동 방식을 이해한다.
> - 효과적인 알림 규칙을 작성하고 설정하는 방법을 익힌다.
> - 다양한 알림 채널 연동 방법을 습득한다.
> - 알림 그룹화와 억제 규칙을 활용하여 효율적인 알림 관리 방법을 학습한다.

---

## 1. AlertManager 개요

### 1.1 AlertManager란?
AlertManager는 Prometheus에서 생성된 알림을 처리하고 관리하는 도구입니다. 알림의 그룹화, 억제, 전송을 담당하며, 다양한 알림 채널(이메일, Slack, 문자메시지 등)을 지원합니다.

### 1.2 주요 기능
- 알림 그룹화: 유사한 알림을 하나로 묶어 관리
- 알림 억제: 특정 조건에서 알림 발송 방지
- 알림 라우팅: 조건에 따라 다른 채널로 알림 전송
- 알림 순위: 중요도에 따른 알림 우선순위 설정

---

## 2. AlertManager 설치 및 설정

### 2.1 설치 방법
```bash
# 바이너리 다운로드
wget https://github.com/prometheus/alertmanager/releases/download/v0.25.0/alertmanager-0.25.0.linux-amd64.tar.gz

# 압축 해제
tar xvfz alertmanager-*.tar.gz

# 실행 파일 이동
sudo cp alertmanager-*/alertmanager /usr/local/bin/
```

### 2.2 기본 설정 파일
```yaml
# alertmanager.yml
global:
  resolve_timeout: 5m
  slack_api_url: 'https://hooks.slack.com/services/XXXXXX/YYYYYYY/ZZZZZZZ'

route:
  group_by: ['alertname']
  group_wait: 30s
  group_interval: 5m
  repeat_interval: 4h
  receiver: 'slack-notifications'

receivers:
- name: 'slack-notifications'
  slack_configs:
  - channel: '#alerts'
    send_resolved: true
```

---

## 3. 알림 규칙 설정

### 3.1 Prometheus 알림 규칙
```yaml
# rules/alert.rules.yml
groups:
- name: example
  rules:
  - alert: HighCPUUsage
    expr: 100 - (avg by(instance) (rate(node_cpu_seconds_total{mode="idle"}[5m])) * 100) > 80
    for: 5m
    labels:
      severity: warning
    annotations:
      summary: "High CPU usage detected"
      description: "CPU usage is above 80% for 5 minutes on {{ $labels.instance }}"

  - alert: HighMemoryUsage
    expr: (node_memory_MemTotal_bytes - node_memory_MemAvailable_bytes) / node_memory_MemTotal_bytes * 100 > 90
    for: 5m
    labels:
      severity: critical
    annotations:
      summary: "High memory usage detected"
      description: "Memory usage is above 90% on {{ $labels.instance }}"
```

### 3.2 알림 템플릿 설정
```yaml
# templates/custom.tmpl
{{ define "slack.custom.title" }}
[{{ .Status | toUpper }}] {{ .AlertName }}
{{ end }}

{{ define "slack.custom.text" }}
*Alert:* {{ .CommonAnnotations.summary }}
*Description:* {{ .CommonAnnotations.description }}
*Severity:* {{ .CommonLabels.severity }}
*Instance:* {{ .CommonLabels.instance }}
{{ end }}
```

---

## 4. 알림 채널 연동

### 4.1 Slack 연동
```yaml
receivers:
- name: 'slack-alerts'
  slack_configs:
  - api_url: 'https://hooks.slack.com/services/XXXXXX/YYYYYYY/ZZZZZZZ'
    channel: '#alerts'
    send_resolved: true
    title: '{{ template "slack.custom.title" . }}'
    text: '{{ template "slack.custom.text" . }}'
    color: '{{ if eq .Status "firing" }}danger{{ else }}good{{ end }}'
```

### 4.2 이메일 연동
```yaml
global:
  smtp_smarthost: 'smtp.gmail.com:587'
  smtp_from: 'alertmanager@example.com'
  smtp_auth_username: 'your-email@gmail.com'
  smtp_auth_password: 'your-password'

receivers:
- name: 'email-alerts'
  email_configs:
  - to: 'team@example.com'
    send_resolved: true
```

---

## 5. 알림 그룹화 및 라우팅

### 5.1 그룹화 설정
```yaml
route:
  group_by: ['alertname', 'cluster', 'service']
  group_wait: 30s
  group_interval: 5m
  repeat_interval: 4h
  routes:
  - match:
      severity: critical
    receiver: 'pager-duty-critical'
    group_wait: 10s
  - match:
      severity: warning
    receiver: 'slack-warnings'
```

### 5.2 억제 규칙 설정
```yaml
inhibit_rules:
- source_match:
    severity: 'critical'
  target_match:
    severity: 'warning'
  equal: ['alertname', 'cluster']
```

---

## 6. 운영 모범 사례

### 6.1 알림 설계 원칙
- 알림은 실제 조치가 필요한 상황에만 발생하도록 설정
- 알림 메시지는 명확하고 조치 가능한 정보 포함
- 중요도에 따른 적절한 알림 채널 선택
- 불필요한 반복 알림 방지

### 6.2 알림 임계값 설정
```yaml
# 단계적 경고 레벨 설정 예시
groups:
- name: resource-alerts
  rules:
  - alert: CPUUsageWarning
    expr: cpu_usage_percent > 70
    labels:
      severity: warning
  - alert: CPUUsageCritical
    expr: cpu_usage_percent > 90
    labels:
      severity: critical
```

---

## 7. 문제 해결과 디버깅

### 7.1 일반적인 문제 해결
- AlertManager 서비스 상태 확인
```bash
systemctl status alertmanager
```

- 알림 전송 상태 확인
```bash
curl -X GET http://localhost:9093/api/v2/alerts
```

### 7.2 로그 확인 및 디버깅
```bash
# 로그 확인
journalctl -u alertmanager -f

# 설정 파일 유효성 검사
amtool check-config alertmanager.yml
```

---

## 참고 자료

- [AlertManager 공식 문서](https://prometheus.io/docs/alerting/latest/alertmanager/)
- [알림 규칙 작성 가이드](https://prometheus.io/docs/practices/alerting/)
- [알림 템플릿 레퍼런스](https://prometheus.io/docs/alerting/latest/notification_examples/)

---

## 마무리

AlertManager는 효과적인 모니터링 시스템 구축을 위한 핵심 구성 요소입니다. 이 가이드에서 다룬 내용을 바탕으로 실제 환경에 맞는 알림 시스템을 구축하고, 지속적인 개선을 통해 더 효율적인 운영이 가능할 것입니다.