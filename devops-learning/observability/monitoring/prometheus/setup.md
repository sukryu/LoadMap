# Prometheus 설치 및 환경 설정 가이드

> **목표:**  
> - Prometheus를 다양한 환경에 설치하는 방법을 익힌다.
> - 기본적인 환경 설정 방법을 이해하고 적용한다.
> - Node Exporter 설치 및 연동 방법을 학습한다.
> - 실제 운영을 위한 보안 설정과 최적화 방법을 습득한다.

---

## 1. 설치 환경 준비

### 1.1 시스템 요구사항
- **운영체제:** Linux, Windows, macOS 지원
- **최소 사양:**
  - CPU: 2코어 이상
  - 메모리: 4GB RAM 이상
  - 디스크: 모니터링 규모에 따라 수십 GB에서 수백 GB
- **네트워크:** 모니터링 대상 시스템과의 연결성 확보

### 1.2 사전 설치 도구
- curl 또는 wget (다운로드용)
- tar (압축 해제용)
- systemd (서비스 관리용, Linux의 경우)

---

## 2. Prometheus 설치

### 2.1 Linux 환경 설치
```bash
# Prometheus 사용자 생성
sudo useradd --no-create-home --shell /bin/false prometheus

# 디렉토리 생성
sudo mkdir /etc/prometheus
sudo mkdir /var/lib/prometheus

# 최신 버전 다운로드 (버전은 실제 최신 버전으로 변경 필요)
wget https://github.com/prometheus/prometheus/releases/download/v2.45.0/prometheus-2.45.0.linux-amd64.tar.gz

# 압축 해제
tar xvfz prometheus-*.tar.gz

# 파일 이동
sudo cp prometheus-*/prometheus /usr/local/bin/
sudo cp prometheus-*/promtool /usr/local/bin/
sudo cp -r prometheus-*/consoles /etc/prometheus
sudo cp -r prometheus-*/console_libraries /etc/prometheus

# 소유권 설정
sudo chown -R prometheus:prometheus /etc/prometheus
sudo chown -R prometheus:prometheus /var/lib/prometheus
```

### 2.2 Docker 환경 설치
```yaml
# docker-compose.yml
version: '3.8'

services:
  prometheus:
    image: prom/prometheus:latest
    container_name: prometheus
    volumes:
      - ./prometheus.yml:/etc/prometheus/prometheus.yml
      - prometheus_data:/prometheus
    command:
      - '--config.file=/etc/prometheus/prometheus.yml'
      - '--storage.tsdb.path=/prometheus'
      - '--web.console.libraries=/usr/share/prometheus/console_libraries'
      - '--web.console.templates=/usr/share/prometheus/consoles'
    ports:
      - "9090:9090"
    restart: unless-stopped

volumes:
  prometheus_data:
```

---

## 3. 기본 설정

### 3.1 prometheus.yml 기본 설정
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
```

### 3.2 시스템 서비스 설정 (Linux)
```ini
# /etc/systemd/system/prometheus.service
[Unit]
Description=Prometheus
Wants=network-online.target
After=network-online.target

[Service]
User=prometheus
Group=prometheus
Type=simple
ExecStart=/usr/local/bin/prometheus \
    --config.file=/etc/prometheus/prometheus.yml \
    --storage.tsdb.path=/var/lib/prometheus \
    --web.console.templates=/etc/prometheus/consoles \
    --web.console.libraries=/etc/prometheus/console_libraries

[Install]
WantedBy=multi-user.target
```

---

## 4. Node Exporter 설치 및 연동

### 4.1 Node Exporter 설치 (Linux)
```bash
# Node Exporter 다운로드
wget https://github.com/prometheus/node_exporter/releases/download/v1.6.0/node_exporter-1.6.0.linux-amd64.tar.gz

# 압축 해제 및 설치
tar xvfz node_exporter-*.tar.gz
sudo cp node_exporter-*/node_exporter /usr/local/bin/

# 서비스 사용자 생성
sudo useradd --no-create-home --shell /bin/false node_exporter

# 서비스 파일 생성
sudo tee /etc/systemd/system/node_exporter.service<<EOF
[Unit]
Description=Node Exporter
Wants=network-online.target
After=network-online.target

[Service]
User=node_exporter
Group=node_exporter
Type=simple
ExecStart=/usr/local/bin/node_exporter

[Install]
WantedBy=multi-user.target
EOF

# 서비스 시작
sudo systemctl daemon-reload
sudo systemctl start node_exporter
sudo systemctl enable node_exporter
```

### 4.2 Node Exporter 연동 설정
```yaml
# prometheus.yml에 추가
scrape_configs:
  - job_name: 'node'
    static_configs:
      - targets: ['localhost:9100']
    metrics_path: '/metrics'
    scrape_interval: 5s
```

---

## 5. 보안 설정

### 5.1 기본 인증 설정
```yaml
# 기본 인증 설정 예시
basic_auth_users:
  admin: $2y$10$wJxVltK0LjHkJj3XmBUh7O8K5X8Yuv1T3RMwhKKYkH4QEfEgwqH2e

# prometheus.yml에 인증 설정 추가
scrape_configs:
  - job_name: 'secured_target'
    basic_auth:
      username: admin
      password: secure_password
```

### 5.2 TLS 설정
```yaml
# TLS 설정 예시
tls_config:
  cert_file: /etc/prometheus/cert.pem
  key_file: /etc/prometheus/key.pem
  ca_file: /etc/prometheus/ca.pem
```

---

## 6. 성능 최적화

### 6.1 저장소 설정
```yaml
# 스토리지 관련 설정
storage:
  tsdb:
    path: "/var/lib/prometheus"
    retention.time: 15d
    retention.size: 50GB
```

### 6.2 메모리 관리
```bash
# 메모리 제한 설정 (systemd)
[Service]
MemoryLimit=2G
```

---

## 7. 운영 체크리스트

### 7.1 설치 후 확인사항
1. 서비스 상태 확인
   ```bash
   sudo systemctl status prometheus
   sudo systemctl status node_exporter
   ```

2. 웹 인터페이스 접속 확인
   - http://localhost:9090 접속
   - Status > Targets 메뉴에서 타겟 상태 확인

3. 기본 메트릭 수집 확인
   - Graph 메뉴에서 `up` 쿼리 실행
   - Node Exporter 메트릭 확인 (예: `node_cpu_seconds_total`)

### 7.2 주기적 점검사항
- 디스크 사용량 모니터링
- 메모리 사용량 확인
- 로그 파일 관리
- 백업 상태 확인

---

## 참고 자료

- [Prometheus 공식 설치 가이드](https://prometheus.io/docs/prometheus/latest/installation/)
- [Node Exporter 가이드](https://prometheus.io/docs/guides/node-exporter/)
- [보안 설정 가이드](https://prometheus.io/docs/operating/security/)

---

## 마무리

이 가이드를 통해 Prometheus의 기본적인 설치와 설정을 완료할 수 있습니다. 실제 운영 환경에 맞춰 추가적인 설정과 최적화가 필요할 수 있으며, 지속적인 모니터링과 관리가 중요합니다.