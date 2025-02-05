# Exporter를 활용한 메트릭 수집 가이드

> **목표:**  
> - Prometheus Exporter의 개념과 동작 원리를 이해한다.
> - 다양한 Exporter의 설치와 구성 방법을 익힌다.
> - 커스텀 Exporter 개발 방법을 학습한다.
> - 실제 환경에서 Exporter를 효과적으로 운영하는 방법을 습득한다.

---

## 1. Exporter 개요

### 1.1 Exporter란?
Exporter는 Prometheus가 직접 수집하기 어려운 시스템이나 서비스의 메트릭을 수집하여 Prometheus가 이해할 수 있는 형식으로 변환하는 도구입니다. 다양한 시스템과 서비스에 대한 메트릭을 수집할 수 있으며, HTTP 엔드포인트를 통해 메트릭을 노출합니다.

### 1.2 주요 Exporter 종류
1. 시스템 메트릭 수집
   - Node Exporter: 호스트 시스템의 하드웨어 및 OS 메트릭
   - Windows Exporter: Windows 시스템 메트릭

2. 데이터베이스 메트릭 수집
   - MySQL Exporter: MySQL 서버 메트릭
   - PostgreSQL Exporter: PostgreSQL 데이터베이스 메트릭
   - MongoDB Exporter: MongoDB 메트릭

3. 웹 서버 및 프록시 메트릭
   - NGINX Exporter: NGINX 웹 서버 메트릭
   - Apache Exporter: Apache 웹 서버 메트릭
   - HAProxy Exporter: HAProxy 로드 밸런서 메트릭

---

## 2. Node Exporter 설치 및 구성

### 2.1 설치 방법
```bash
# 최신 버전 다운로드
wget https://github.com/prometheus/node_exporter/releases/download/v1.6.0/node_exporter-1.6.0.linux-amd64.tar.gz

# 압축 해제
tar xvfz node_exporter-*.tar.gz

# 실행 파일 이동
sudo mv node_exporter-*/node_exporter /usr/local/bin/

# 시스템 서비스 생성
sudo tee /etc/systemd/system/node_exporter.service<<EOF
[Unit]
Description=Node Exporter
After=network.target

[Service]
Type=simple
ExecStart=/usr/local/bin/node_exporter \
    --collector.filesystem.mount-points-exclude=^/(sys|proc|dev|host|etc)($$|/) \
    --collector.systemd \
    --collector.processes

[Install]
WantedBy=multi-user.target
EOF

# 서비스 시작
sudo systemctl daemon-reload
sudo systemctl start node_exporter
sudo systemctl enable node_exporter
```

### 2.2 Prometheus 설정
```yaml
# prometheus.yml
scrape_configs:
  - job_name: 'node'
    static_configs:
      - targets: ['localhost:9100']
    scrape_interval: 15s
    metrics_path: '/metrics'
```

---

## 3. MySQL Exporter 설치 및 구성

### 3.1 MySQL 사용자 설정
```sql
CREATE USER 'exporter'@'localhost' IDENTIFIED BY 'password';
GRANT PROCESS, REPLICATION CLIENT, SELECT ON *.* TO 'exporter'@'localhost';
FLUSH PRIVILEGES;
```

### 3.2 설치 및 설정
```bash
# MySQL Exporter 설치
wget https://github.com/prometheus/mysqld_exporter/releases/download/v0.14.0/mysqld_exporter-0.14.0.linux-amd64.tar.gz
tar xvfz mysqld_exporter-*.tar.gz
sudo mv mysqld_exporter-*/mysqld_exporter /usr/local/bin/

# 설정 파일 생성
sudo tee /etc/.mysqld_exporter.cnf<<EOF
[client]
user=exporter
password=password
EOF

# 서비스 설정
sudo tee /etc/systemd/system/mysqld_exporter.service<<EOF
[Unit]
Description=MySQL Exporter
After=network.target

[Service]
Type=simple
Environment=DATA_SOURCE_NAME=file:/etc/.mysqld_exporter.cnf
ExecStart=/usr/local/bin/mysqld_exporter

[Install]
WantedBy=multi-user.target
EOF

# 서비스 시작
sudo systemctl daemon-reload
sudo systemctl start mysqld_exporter
sudo systemctl enable mysqld_exporter
```

---

## 4. 커스텀 Exporter 개발

### 4.1 Go를 사용한 기본 Exporter 개발
```go
package main

import (
    "net/http"
    "github.com/prometheus/client_golang/prometheus"
    "github.com/prometheus/client_golang/prometheus/promhttp"
)

var (
    customMetric = prometheus.NewGauge(prometheus.GaugeOpts{
        Name: "custom_metric",
        Help: "This is a custom metric example",
    })
)

func init() {
    prometheus.MustRegister(customMetric)
}

func main() {
    // 메트릭 값 설정
    customMetric.Set(123.45)

    // HTTP 서버 설정
    http.Handle("/metrics", promhttp.Handler())
    http.ListenAndServe(":9100", nil)
}
```

### 4.2 Python을 사용한 커스텀 Exporter
```python
from prometheus_client import start_http_server, Gauge
import time
import random

# 메트릭 정의
RANDOM_VALUE = Gauge('random_value', 'A random value between 0 and 100')

def generate_metrics():
    while True:
        # 메트릭 값 생성
        RANDOM_VALUE.set(random.uniform(0, 100))
        time.sleep(5)

if __name__ == '__main__':
    # 메트릭 서버 시작
    start_http_server(8000)
    generate_metrics()
```

---

## 5. Exporter 운영 관리

### 5.1 모니터링 지표
주요 모니터링 대상 메트릭입니다.

1. 시스템 메트릭
   - CPU 사용률: `node_cpu_seconds_total`
   - 메모리 사용량: `node_memory_MemTotal_bytes`
   - 디스크 사용량: `node_filesystem_size_bytes`

2. MySQL 메트릭
   - 연결 수: `mysql_global_status_threads_connected`
   - 쿼리 실행량: `mysql_global_status_queries`
   - 슬로우 쿼리: `mysql_global_status_slow_queries`

### 5.2 성능 최적화
```yaml
# prometheus.yml
scrape_configs:
  - job_name: 'node'
    scrape_interval: 15s
    scrape_timeout: 10s
    static_configs:
      - targets: ['localhost:9100']
```

---

## 6. 문제 해결과 디버깅

### 6.1 일반적인 문제 해결
1. 연결 문제 확인
```bash
curl http://localhost:9100/metrics
```

2. 로그 확인
```bash
journalctl -u node_exporter -f
```

### 6.2 메트릭 검증
```bash
# 메트릭 형식 검증
curl http://localhost:9100/metrics | grep "^#"

# 특정 메트릭 확인
curl http://localhost:9100/metrics | grep "node_cpu"
```

---

## 7. 보안 설정

### 7.1 기본 인증 설정
```yaml
basic_auth_users:
  prometheus: $2y$10$wJxVltK0LjHkJj3XmBUh7O8K5X8Yuv1T3RMwhKKYkH4QEfEgwqH2e
```

### 7.2 TLS 설정
```yaml
tls_config:
  cert_file: /etc/prometheus/cert.pem
  key_file: /etc/prometheus/key.pem
```

---

## 참고 자료

- [Prometheus Exporters 공식 문서](https://prometheus.io/docs/instrumenting/exporters/)
- [Node Exporter 가이드](https://prometheus.io/docs/guides/node-exporter/)
- [Writing Exporters 가이드](https://prometheus.io/docs/instrumenting/writing_exporters/)

---

## 마무리

Exporter는 Prometheus 모니터링 시스템의 핵심 구성 요소입니다. 이 가이드에서 다룬 내용을 바탕으로 다양한 시스템과 서비스의 메트릭을 효과적으로 수집하고 모니터링할 수 있습니다. 실제 환경에 맞는 Exporter를 선택하고 구성하여 효율적인 모니터링 시스템을 구축하시기 바랍니다.