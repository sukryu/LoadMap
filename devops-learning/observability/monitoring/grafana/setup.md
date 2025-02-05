# 🛠 Grafana 설치 및 환경 설정 가이드

> **목표:**  
> - Grafana를 다양한 환경에 설치하는 방법을 이해한다.
> - 기본적인 환경 설정과 보안 설정 방법을 습득한다.
> - 데이터 소스 연결과 초기 대시보드 구성 방법을 학습한다.
> - 실제 운영 환경에서 필요한 설정들을 파악한다.

---

## 1. 설치 준비

### 시스템 요구사항
- **최소 하드웨어 사양:**
  - CPU: 2코어 이상
  - 메모리: 4GB RAM 이상
  - 디스크: 10GB 이상의 여유 공간

- **지원 운영체제:**
  - Linux (Ubuntu, CentOS, RHEL 등)
  - Windows Server 2016 이상
  - macOS 10.13 이상

### 사전 설치 항목
- 웹 서버 (선택사항)
- 데이터베이스 (MySQL, PostgreSQL 등)
- SSL 인증서 (프로덕션 환경의 경우)

---

## 2. 설치 방법

### 2.1 Ubuntu/Debian 환경 설치
```bash
# APT 저장소 추가
sudo apt-get install -y software-properties-common wget
sudo wget -q -O /usr/share/keyrings/grafana.key https://apt.grafana.com/gpg.key

# 저장소 등록
echo "deb [signed-by=/usr/share/keyrings/grafana.key] https://apt.grafana.com stable main" | sudo tee -a /etc/apt/sources.list.d/grafana.list

# Grafana 설치
sudo apt-get update
sudo apt-get install grafana

# 서비스 시작 및 자동 시작 설정
sudo systemctl start grafana-server
sudo systemctl enable grafana-server
```

### 2.2 Docker를 이용한 설치
```bash
# 최신 버전 설치
docker run -d -p 3000:3000 grafana/grafana

# 볼륨 마운트를 통한 데이터 영구 저장
docker run -d -p 3000:3000 \
  -v grafana-storage:/var/lib/grafana \
  grafana/grafana
```

### 2.3 Windows 환경 설치
1. Grafana 공식 웹사이트에서 Windows 설치 파일 다운로드
2. 설치 파일 실행 및 설치 마법사 따라하기
3. Windows 서비스로 등록 및 시작

---

## 3. 초기 환경 설정

### 3.1 기본 설정 파일 (grafana.ini)
```ini
[server]
protocol = http
http_port = 3000
domain = localhost

[database]
type = sqlite3
path = grafana.db

[security]
admin_user = admin
admin_password = admin

[auth]
disable_login_form = false
```

### 3.2 주요 환경 변수 설정
```bash
# 데이터베이스 설정
GF_DATABASE_TYPE=mysql
GF_DATABASE_HOST=localhost:3306
GF_DATABASE_NAME=grafana
GF_DATABASE_USER=grafana
GF_DATABASE_PASSWORD=password

# 보안 설정
GF_SECURITY_ADMIN_PASSWORD=your_password
GF_SECURITY_SECRET_KEY=your_secret_key
```

---

## 4. 보안 설정

### 4.1 관리자 계정 설정
1. 초기 관리자 비밀번호 변경
2. 관리자 권한 설정
3. 인증 방식 구성 (LDAP, OAuth 등)

### 4.2 접근 제어 설정
```ini
[auth.anonymous]
enabled = false

[auth.basic]
enabled = true

[auth.proxy]
enabled = false

[security]
allow_embedding = false
cookie_secure = true
```

---

## 5. 데이터 소스 연결

### 5.1 Prometheus 연결 설정
```yaml
datasource_settings:
  url: http://localhost:9090
  access: server
  scrape_interval: 15s
  http_method: GET
```

### 5.2 MySQL 연결 설정
```yaml
connection_settings:
  host: localhost:3306
  database: your_database
  user: grafana_user
  password: your_password
  tls_settings: required/skip-verify/disable
```

---

## 6. 운영 환경 최적화

### 6.1 성능 튜닝
- 캐시 설정 최적화
- 쿼리 성능 개선
- 리소스 사용량 모니터링

### 6.2 백업 설정
```bash
# 데이터 디렉토리 백업
tar -zcvf grafana-backup-$(date +%Y%m%d).tar.gz /var/lib/grafana

# 설정 파일 백업
cp /etc/grafana/grafana.ini /backup/grafana.ini.$(date +%Y%m%d)
```

---

## 7. 문제 해결 가이드

### 일반적인 문제 해결
1. 로그 확인: `/var/log/grafana/grafana.log`
2. 서비스 상태 확인: `systemctl status grafana-server`
3. 포트 사용 확인: `netstat -tulpn | grep 3000`

### 데이터베이스 연결 문제
1. 데이터베이스 서비스 상태 확인
2. 연결 문자열 검증
3. 권한 설정 확인

---

## 8. 성능 모니터링

### 8.1 시스템 모니터링
- CPU 사용량 모니터링
- 메모리 사용량 확인
- 디스크 I/O 모니터링

### 8.2 애플리케이션 모니터링
- 쿼리 성능 분석
- 응답 시간 모니터링
- 에러율 확인

---

## 참고 자료

- [Grafana 공식 설치 가이드](https://grafana.com/docs/grafana/latest/installation/)
- [Grafana 보안 설정 가이드](https://grafana.com/docs/grafana/latest/administration/security/)
- [Grafana 데이터 소스 설정](https://grafana.com/docs/grafana/latest/datasources/)

---

## 마무리

Grafana의 설치와 환경 설정은 시스템 모니터링의 첫 걸음입니다. 이 가이드를 통해 기본적인 설치부터 운영 환경에서의 최적화까지 단계적으로 진행할 수 있습니다. 각 환경에 맞는 적절한 설정을 선택하고, 보안과 성능을 고려하여 구성하시기 바랍니다.