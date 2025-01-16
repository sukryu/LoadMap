# 서버/시스템 하드닝(Server Hardening)

현대 IT 환경에서 **서버 보안 강화(Server Hardening)**는 필수적인 요소입니다. 이 문서에서는 리눅스와 윈도우 서버의 보안을 강화하는 구체적인 방법과 베스트 프랙티스를 다룹니다.

> 최근 업데이트: 2025-01-16

## 1. 들어가기 (Introduction)

### 1.1 서버 하드닝의 중요성

서버 하드닝은 시스템의 공격 표면을 최소화하고 잠재적인 보안 위협으로부터 서버를 보호하는 과정입니다. 최근 증가하는 사이버 공격과 제로데이 취약점으로 인해 그 중요성이 더욱 부각되고 있습니다.

주요 위협 요소:
- SSH 브루트포스 공격
- 알려진 취약점을 이용한 원격 코드 실행
- 권한 상승 공격
- 구성 오류를 통한 무단 접근
- 패치되지 않은 소프트웨어의 취약점 악용

### 1.2 문서의 목적

이 문서는 다음을 목표로 합니다:
- 서버 수준의 보안 강화 방법 제시
- OS 및 애플리케이션 레벨 보안 설정 가이드 제공
- 자동화된 보안 강화 방안 소개
- 모니터링과 감사 체계 구축 방법 설명

### 1.3 적용 범위

- 리눅스 서버 (Ubuntu, CentOS)
- 윈도우 서버
- 클라우드 인프라 (AWS, GCP, Azure)
- 컨테이너 환경
- 웹 서버 및 애플리케이션 서버

> 💡 **중요 사항**  
> 서버 하드닝은 일회성 작업이 아닌 지속적인 프로세스입니다. 보안 패치 적용, 구성 변경, 모니터링 등이 정기적으로 수행되어야 합니다.

---

## 2. 운영체제 하드닝(OS-Level Hardening)

### 2.1 사용자/권한 분리 (Least Privilege)

최소 권한 원칙(Principle of Least Privilege)은 서버 보안의 기본입니다. 각 사용자와 프로세스는 필요한 최소한의 권한만을 가져야 합니다.

#### 2.1.1 리눅스 사용자 관리

1. **루트 계정 직접 사용 제한**
```bash
# root 로그인 비활성화
sudo sed -i '/^PermitRootLogin/c\PermitRootLogin no' /etc/ssh/sshd_config
sudo systemctl restart sshd
```

2. **전용 서비스 계정 생성**
```bash
# 애플리케이션용 시스템 계정 생성
sudo useradd -r -s /sbin/nologin appuser
sudo usermod -aG appgroup appuser

# 홈 디렉터리 권한 설정
sudo chmod 750 /home/appuser
```

3. **sudo 권한 제한적 부여**
```bash
# sudo 설정 파일 편집
sudo visudo

# 특정 명령만 허용
appuser ALL=(ALL) NOPASSWD: /usr/bin/systemctl status appname
appuser ALL=(ALL) NOPASSWD: /usr/bin/systemctl restart appname
```

#### 2.1.2 윈도우 사용자 관리

1. **관리자 계정 보안 강화**
```powershell
# 관리자 계정 이름 변경
Rename-LocalUser -Name "Administrator" -NewName "Admin123"

# 게스트 계정 비활성화
Disable-LocalUser -Name "Guest"
```

2. **그룹 정책 설정**
```powershell
# 암호 정책 강화
secedit /export /cfg c:\secpol.cfg
(gc C:\secpol.cfg).replace("PasswordComplexity = 0", "PasswordComplexity = 1") | Out-File C:\secpol.cfg
secedit /configure /db c:\windows\security\local.sdb /cfg c:\secpol.cfg /areas SECURITYPOLICY
```

### 2.2 SSH 보안 (Key, root 차단)

SSH는 원격 서버 관리의 기본 수단이지만, 동시에 주요 공격 대상이 되기도 합니다.

#### 2.2.1 SSH 기본 보안 설정

1. **SSH 설정 파일 보안 강화**
```bash
# /etc/ssh/sshd_config 설정
Protocol 2
PermitRootLogin no
PasswordAuthentication no
PermitEmptyPasswords no
MaxAuthTries 3
ClientAliveInterval 300
ClientAliveCountMax 0
```

2. **SSH 키 기반 인증 설정**
```bash
# 키 생성
ssh-keygen -t ed25519 -f ~/.ssh/id_ed25519

# 공개키 배포
ssh-copy-id -i ~/.ssh/id_ed25519.pub user@remote-server
```

#### 2.2.2 SSH 접근 제한

1. **허용 IP 제한**
```bash
# TCP Wrappers 설정
echo "sshd: 192.168.1.0/24" >> /etc/hosts.allow
echo "sshd: ALL" >> /etc/hosts.deny
```

2. **포트 변경**
```bash
# SSH 포트 변경
sudo sed -i 's/#Port 22/Port 2222/' /etc/ssh/sshd_config
sudo systemctl restart sshd
```

### 2.3 패키지 없데이트/보안 패치

시스템과 패키지를 최신 상태로 유지하는 것은 보안의 기본입니다.

#### 2.3.1 리눅스 시스템 업데이트

1. **자동 업데이트 설정 (Ubuntu)**
```bash
# unattended-upgrades 설치
sudo apt install unattended-upgrades
sudo dpkg-reconfigure --priority=low unattended-upgrades

# 설정 파일 수정
sudo vi /etc/apt/apt.conf.d/50unattended-upgrades

Unattended-Upgrade::Allowed-Origins {
    "${distro_id}:${distro_codename}-security";
    "${distro_id}:${distro_codename}-updates";
};
```

2. **수동 업데이트 절차**
```bash
# Ubuntu/Debian
sudo apt update
sudo apt upgrade -y
sudo apt autoremove -y

# CentOS/RHEL
sudo yum check-update
sudo yum update -y
sudo yum autoremove -y
```

### 2.4 방화벽(UFW/iptables) 설정

방화벽은 서버의 첫 번째 방어선입니다. 기본적으로 모든 포트를 차단하고, 필요한 포트만 선별적으로 허용해야 합니다.

#### 2.4.1 UFW (Uncomplicated Firewall) 설정

1. **기본 정책 설정**
```bash
# UFW 활성화 및 기본 정책 설정
sudo ufw default deny incoming
sudo ufw default allow outgoing

# 기본 서비스 허용
sudo ufw allow 22/tcp  # SSH
sudo ufw allow 80/tcp  # HTTP
sudo ufw allow 443/tcp # HTTPS

# 방화벽 활성화
sudo ufw enable
```

2. **고급 규칙 설정**
```bash
# 특정 IP 대역 허용
sudo ufw allow from 192.168.1.0/24 to any port 3306

# 속도 제한 설정
sudo ufw limit ssh

# 규칙 확인
sudo ufw status verbose
```

#### 2.4.2 iptables 설정

1. **기본 iptables 규칙**
```bash
# 기본 체인 정책 설정
iptables -P INPUT DROP
iptables -P FORWARD DROP
iptables -P OUTPUT ACCEPT

# 기존 연결 허용
iptables -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT

# 로컬호스트 허용
iptables -A INPUT -i lo -j ACCEPT

# SSH 허용
iptables -A INPUT -p tcp --dport 22 -j ACCEPT
```

2. **규칙 저장 및 복원**
```bash
# 규칙 저장
sudo iptables-save > /etc/iptables/rules.v4

# 규칙 복원
sudo iptables-restore < /etc/iptables/rules.v4
```

---

## 3. 서버 구성 보안 (Application-Level)

### 3.1 웹/애플리케이션 서버 설정

#### 3.1.1 Nginx 보안 설정

1. **기본 보안 설정**
```nginx
# /etc/nginx/nginx.conf
http {
    # 버전 정보 숨기기
    server_tokens off;
    
    # 클라이언트 본문 크기 제한
    client_max_body_size 10M;
    
    # 타임아웃 설정
    client_body_timeout 12;
    client_header_timeout 12;
    
    # XSS 방어 헤더
    add_header X-XSS-Protection "1; mode=block";
    add_header X-Frame-Options "SAMEORIGIN";
    add_header X-Content-Type-Options nosniff;
    
    # SSL 설정
    ssl_protocols TLSv1.2 TLSv1.3;
    ssl_prefer_server_ciphers on;
    ssl_ciphers ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256;
}
```

2. **가상 호스트 설정**
```bash
server {
    listen 443 ssl http2;
    server_name example.com;
    
    # SSL 인증서
    ssl_certificate /etc/nginx/ssl/cert.pem;
    ssl_certificate_key /etc/nginx/ssl/key.pem;
    
    # HSTS 활성화
    add_header Strict-Transport-Security "max-age=31536000" always;
    
    # 접근 로그 설정
    access_log /var/log/nginx/access.log combined buffer=512k flush=1m;
    error_log /var/log/nginx/error.log warn;
}
```

#### 3.1.2 Apache 보안 설정

1. **기본 보안 설정**
```apache
# /etc/apache2/apache2.conf
ServerTokens Prod
ServerSignature Off
TraceEnable Off

# 디렉터리 접근 제한
<Directory />
    Options None
    Require all denied
</Directory>

# 특정 디렉터리 허용
<Directory /var/www/html>
    Options FollowSymLinks
    AllowOverride None
    Require all granted
</Directory>
```

2. **ModSecurity 설정**
```apache
# ModSecurity 활성화
LoadModule security2_module modules/mod_security2.so

# OWASP CRS 규칙 적용
Include modsecurity.d/activated_rules/*.conf

SecRuleEngine On
SecRequestBodyAccess On
SecResponseBodyAccess On
```

### 3.2 계정/프로세스 분리

서비스별로 전용 계정을 사용하고 프로세스를 분리하면 보안 사고 발생 시 영향 범위를 제한할 수 있습니다.

#### 3.2.1 서비스 계정 설정

1. **웹 서버 전용 계정 생성**
```bash
# Nginx 전용 계정 생성
sudo useradd -r -s /sbin/nologin nginx
sudo groupadd nginx

# 디렉터리 권한 설정
sudo chown -R nginx:nginx /var/www/html
sudo chmod -R 750 /var/www/html
```

2. **데이터베이스 전용 계정**
```bash
# MySQL 전용 계정 생성
sudo useradd -r -s /sbin/nologin mysql
sudo groupadd mysql

# 데이터 디렉터리 권한 설정
sudo chown -R mysql:mysql /var/lib/mysql
sudo chmod -R 750 /var/lib/mysql
```

#### 3.2.2 프로세스 분리 및 제한

1. **systemd 서비스 설정**
```ini
# /etc/systemd/system/myapp.service
[Unit]
Description=My Application Service
After=network.target

[Service]
Type=simple
User=myapp
Group=myapp
PrivateTmp=true
ProtectSystem=full
ProtectHome=true
NoNewPrivileges=true
ExecStart=/usr/local/bin/myapp
Restart=on-failure

[Install]
WantedBy=multi-user.target
```

2. **리소스 제한 설정**
```bash
# 프로세스별 리소스 제한
ulimit -n 65535      # 파일 디스크립터 제한
ulimit -u 100        # 최대 프로세스 수 제한

# systemd 서비스 리소스 제한
[Service]
LimitNOFILE=65535
LimitNPROC=100
MemoryMax=2G
CPUQuota=50%
```

### 3.3 SSL/TLS 인증서 설정

강력한 SSL/TLS 설정은 데이터 전송 보안의 기본입니다.

#### 3.3.1 Let`s Encrypt 인증서 발급

1. **Certbot 설치 및 인증서 발급**
```bash
# Certbot 설치
sudo apt install certbot python3-certbot-nginx

# Nginx용 인증서 발급
sudo certbot --nginx -d example.com -d www.example.com

# 자동 갱신 설정
sudo systemctl enable certbot.timer
sudo systemctl start certbot.timer
```

2. **수동 인증서 갱신 테스트**
```bash
sudo certbot renew --dry-run
```

#### 3.3.2 강력한 SSL/TLS 설정

1. **Nginx SSL 설정**
```nginx
# /etc/nginx/conf.d/ssl.conf
ssl_protocols TLSv1.2 TLSv1.3;
ssl_prefer_server_ciphers on;
ssl_ciphers ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256;
ssl_ecdh_curve secp384r1;
ssl_session_timeout 10m;
ssl_session_cache shared:SSL:10m;
ssl_session_tickets off;
ssl_stapling on;
ssl_stapling_verify on;
resolver 8.8.8.8 8.8.4.4 valid=300s;
resolver_timeout 5s;

# HSTS 설정
add_header Strict-Transport-Security "max-age=63072000" always;
```

2. **Apache SSL 설정**
```apache
# /etc/apache2/mods-available/ssl.conf
SSLProtocol all -SSLv3 -TLSv1 -TLSv1.1
SSLCipherSuite ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256
SSLHonorCipherOrder on
SSLCompression off
SSLSessionTickets off

# OCSP Stapling
SSLUseStapling on
SSLStaplingCache "shmcb:logs/stapling-cache(150000)"
SSLStaplingResponseMaxAge 900
```

3. **OpenSSL 설정 검증**
```bash
# SSL/TLS 설정 검사
openssl s_client -connect example.com:443 -tls1_2
openssl s_client -connect example.com:443 -tls1_3

# 인증서 정보 확인
openssl x509 -in certificate.crt -text -noout
```

---

## 4. 환경변수/설정 파일 보안

### 4.1 .env 파일 관리

환경 변수와 설정 파일에는 민감한 정보가 포함되어 있으므로 특별한 관리가 필요합니다.

#### 4.1.1 환경 변수 보안 설정

1. **.env 파일 보안**
```bash
# .env 파일 권한 설정
chmod 600 .env
chown root:root .env

# .env 예시
DB_HOST=localhost
DB_PORT=3306
DB_USER=${MYSQL_USER}
DB_PASS=${MYSQL_PASS}
```

2. **환경 변수 암호화**
```bash
# 환경 변수 암호화 도구 설치
pip install ansible-vault

# 환경 변수 파일 암호화
ansible-vault encrypt .env

# 암호화된 파일 복호화하여 사용
ansible-vault decrypt .env --output=.env.decrypted
```

#### 4.1.2 설정 파일 보안

1. **설정 파일 권한 관리**
```bash
# 중요 설정 파일 권한 설정
sudo chmod 644 /etc/passwd
sudo chmod 400 /etc/shadow
sudo chmod 644 /etc/group
sudo chmod 644 /etc/hosts

# 설정 디렉터리 권한 설정
sudo chmod 755 /etc/
sudo chmod 700 /etc/ssl/private/
```

### 4.2 Secret Manager/Vault 연동

#### 4.2.1 HashiCorp Vault 설정

1. **Vault 서버 설정**
```bash
# Vault 설치 및 초기화
vault server -config=config.hcl

# 초기화
vault operator init

# 언실링
vault operator unseal
```

2. **시크릿 관리**
```bash
# 시크릿 저장
vault kv put secret/myapp/config \
    db.username=dbuser \
    db.password=dbpass

# 시크릿 조회
vault kv get secret/myapp/config
```

#### 4.2.2 클라우드 Secret Manager 연동

1. **AWS Secrets Manager 사용**
```python
import boto3

def get_secret():
    client = boto3.client('secretsmanager')
    response = client.get_secret_value(
        SecretId='myapp/production/database'
    )
    return response['SecretString']
```

2. **GCP Secret Manager 사용**
```python
from google.cloud import secretmanager

def get_secret():
    client = secretmanager.SecretManagerServiceClient()
    name = f"projects/project-id/secrets/my-secret/versions/latest"
    response = client.access_secret_version(request={"name": name})
    return response.payload.data.decode("UTF-8")
```

### 4.3 자격 증명 로테이션

#### 4.3.1 자동 자격 증명 로테이션

1. **데이터베이스 비밀번호 로테이션**
```python
import secrets
import mysql.connector

def rotate_db_password():
    new_password = secrets.token_urlsafe(32)
    
    # 데이터베이스 비밀번호 변경
    connection = mysql.connector.connect(
        host="localhost",
        user="admin",
        password=current_password
    )
    cursor = connection.cursor()
    
    # 새 비밀번호 설정
    cursor.execute(f"ALTER USER 'user'@'localhost' IDENTIFIED BY '{new_password}'")
    
    # Secret Manager 업데이트
    update_secret_manager("db_password", new_password)
```

2. **API 키 로테이션**
```python
def rotate_api_keys():
    # 새 API 키 생성
    new_key = generate_api_key()
    
    # 이전 키를 일정 기간 유지
    mark_key_for_deprecation(current_key)
    
    # 새 키 활성화
    activate_new_key(new_key)
    
    # 만료된 키 정리
    cleanup_deprecated_keys()
```

---

## 5. 로깅/모니터링

### 5.1 액세스/에러 로그 분석

#### 5.1.1 중앙 로깅 시스템 구축

1. **Elasticsearch + Logstash + Kibana (ELK) 설정**
```yaml
# logstash.conf
input {
  filebeat {
    hosts => ["localhost:5044"]
    index => "filebeat-%{+YYYY.MM.dd}"
  }
}

filter {
  if [type] == "nginx-access" {
    grok {
      match => { "message" => "%{COMBINEDAPACHELOG}" }
    }
  }
}

output {
  elasticsearch {
    hosts => ["localhost:9200"]
    index => "logstash-%{+YYYY.MM.dd}"
  }
}
```

2. **로그 수집 설정**
```yaml
# filebeat.yml
filebeat.inputs:
- type: log
  enabled: true
  paths:
    - /var/log/nginx/access.log
  fields:
    type: nginx-access

output.logstash:
  hosts: ["localhost:5044"]
```

### 5.2 OS 보안 로그(로그인 시도, sudo 이력)

#### 5.2.1 시스템 로그 모니터링

1. **주요 로그 파일 설정**
```bash
# rsyslog 설정 강화
cat << EOF > /etc/rsyslog.d/security.conf
auth,authpriv.*   /var/log/auth.log
*.info;auth.none  /var/log/messages
kern.*            /var/log/kern.log
daemon.*          /var/log/daemon.log
EOF

# 로그 순환 설정
cat << EOF > /etc/logrotate.d/security
/var/log/auth.log {
    rotate 30
    daily
    compress
    delaycompress
    missingok
    notifempty
    create 0640 syslog adm
}
EOF
```

2. **auditd 설정**
```bash
# 감사 규칙 설정
cat << EOF >> /etc/audit/rules.d/audit.rules
# 파일 시스템 변경 감사
-w /etc/passwd -p wa -k identity
-w /etc/group -p wa -k identity
-w /etc/shadow -p wa -k identity

# sudo 명령어 감사
-a exit,always -F arch=b64 -F euid=0 -S execve -k sudo_log

# 설정 파일 변경 감사
-w /etc/ssh/sshd_config -p wa -k sshd_config
EOF

# auditd 재시작
systemctl restart auditd
```

#### 5.2.2 로그 분석 도구

1. **fail2ban 설정**
```ini
# /etc/fail2ban/jail.local
[sshd]
enabled = true
port = ssh
filter = sshd
logpath = /var/log/auth.log
maxretry = 3
bantime = 3600
findtime = 600

[nginx-http-auth]
enabled = true
filter = nginx-http-auth
logpath = /var/log/nginx/error.log
maxretry = 3
```

2. **OSSEC 설정**
```xml
<!-- /var/ossec/etc/ossec.conf -->
<ossec_config>
  <syscheck>
    <directories check_all="yes">/etc,/usr/bin,/usr/sbin</directories>
    <ignore>/etc/mtab</ignore>
    <ignore>/etc/hosts.deny</ignore>
  </syscheck>

  <rootcheck>
    <rootkit_files>/var/ossec/etc/shared/rootkit_files.txt</rootkit_files>
    <rootkit_trojans>/var/ossec/etc/shared/rootkit_trojans.txt</rootkit_trojans>
  </rootcheck>
</ossec_config>
```

### 5.3 자동화된 알림 설정

#### 5.3.1 알림 시스템 구축

1. **Slack 웹훅 통합**
```python
import requests
import json

def send_slack_alert(message, severity="info"):
    webhook_url = "https://hooks.slack.com/services/YOUR/WEBHOOK/URL"
    
    color_map = {
        "info": "#36a64f",
        "warning": "#ff9400",
        "critical": "#ff0000"
    }
    
    payload = {
        "attachments": [
            {
                "color": color_map.get(severity, "#36a64f"),
                "title": "보안 알림",
                "text": message,
                "fields": [
                    {
                        "title": "서버",
                        "value": "prod-web-01",
                        "short": True
                    },
                    {
                        "title": "심각도",
                        "value": severity.upper(),
                        "short": True
                    }
                ]
            }
        ]
    }
    
    requests.post(webhook_url, data=json.dumps(payload))
```

2. **이메일 알림 설정**
```python
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

def send_email_alert(subject, message, to_email):
    smtp_server = "smtp.gmail.com"
    smtp_port = 587
    smtp_user = "alerts@yourdomain.com"
    smtp_password = "your-app-specific-password"
    
    msg = MIMEMultipart()
    msg['From'] = smtp_user
    msg['To'] = to_email
    msg['Subject'] = subject
    
    msg.attach(MIMEText(message, 'plain'))
    
    try:
        server = smtplib.SMTP(smtp_server, smtp_port)
        server.starttls()
        server.login(smtp_user, smtp_password)
        server.send_message(msg)
        server.quit()
    except Exception as e:
        print(f"Failed to send email: {str(e)}")
```

#### 5.3.2 알림 규칙 설정

1. **임계값 기반 알림**
```python
def check_login_attempts():
    # auth.log 분석
    with open('/var/log/auth.log', 'r') as f:
        failed_attempts = sum(1 for line in f if 'Failed password' in line)
        
    if failed_attempts > 10:
        send_slack_alert(
            f"높은 로그인 실패 횟수 감지: {failed_attempts}회",
            severity="warning"
        )
```

2. **패턴 기반 알림**
```python
def monitor_system_changes():
    critical_files = [
        '/etc/passwd',
        '/etc/shadow',
        '/etc/ssh/sshd_config'
    ]
    
    for file in critical_files:
        if check_file_changes(file):
            send_slack_alert(
                f"중요 시스템 파일 변경 감지: {file}",
                severity="critical"
            )
```

---

## 6. 자동화/DevSecOps 관점

### 6.1 Ansible, Chef, Puppet을 통한 하드닝

#### 6.1.1 Ansible 보안 자동화

1. **기본 보안 플레이북 작성**
```yaml
# security-hardening.yml
---
- name: Security Hardening Playbook
  hosts: all
  become: yes
  
  tasks:
    # 패키지 업데이트
    - name: Update all packages
      apt:
        update_cache: yes
        upgrade: yes
        
    # SSH 보안 설정
    - name: Configure SSH
      template:
        src: templates/sshd_config.j2
        dest: /etc/ssh/sshd_config
        mode: '0600'
      notify: restart ssh
    
    # 방화벽 설정
    - name: Configure UFW
      ufw:
        state: enabled
        policy: deny
        rule: allow
        port: "{{ item }}"
      loop:
        - 22
        - 80
        - 443
        
    # 시스템 감사 설정
    - name: Install auditd
      apt:
        name: auditd
        state: present
        
  handlers:
    - name: restart ssh
      service:
        name: sshd
        state: restarted
```

2. **보안 템플릿 관리**
```yaml
# templates/sshd_config.j2
Protocol 2
PermitRootLogin no
PasswordAuthentication no
X11Forwarding no
MaxAuthTries 3
ClientAliveInterval 300
ClientAliveCountMax 0
UsePAM yes
AllowGroups ssh-users

# 환경별 변수 적용
Port {{ ssh_port | default(22) }}
AllowUsers {% for user in allowed_users %}{{user}} {% endfor %}
```

#### 6.1.2 Chef를 통한 보안 구성

1. **보안 쿡북 작성**
```ruby
# cookbooks/security/recipes/default.rb
package 'fail2ban'
package 'ufw'
package 'auditd'

# 방화벽 설정
firewall 'default' do
  action :install
end

firewall_rule 'ssh' do
  port 22
  protocol :tcp
  action :allow
end

# 파일 권한 설정
file '/etc/shadow' do
  mode '0600'
  owner 'root'
  group 'root'
end

# 보안 설정 적용
template '/etc/security/limits.conf' do
  source 'limits.conf.erb'
  mode '0644'
  owner 'root'
  group 'root'
end
```

### 6.2 Immutable Infrastructure 패턴

#### 6.2.1 Docker 컨테이너 보안

1. **보안 Dockerfile 작성**
```dockerfile
# 최신 보안 패치가 적용된 베이스 이미지 사용
FROM ubuntu:22.04

# 시스템 업데이트 및 필요한 패키지 설치
RUN apt-get update && apt-get upgrade -y \
    && apt-get install -y \
        curl \
        nginx \
        openssl \
    && rm -rf /var/lib/apt/lists/*

# 비특권 사용자 생성 및 전환
RUN useradd -r -s /sbin/nologin webuser
USER webuser

# 보안 설정 파일 복사
COPY --chown=webuser:webuser configs/nginx.conf /etc/nginx/nginx.conf
COPY --chown=webuser:webuser configs/security.conf /etc/nginx/conf.d/

# 헬스체크 추가
HEALTHCHECK --interval=30s --timeout=3s \
    CMD curl -f http://localhost/ || exit 1

# 컨테이너 실행
CMD ["nginx", "-g", "daemon off;"]
```

2. **Docker 컴포즈 보안 설정**
```yaml
# docker-compose.yml
version: '3.8'

services:
  webapp:
    build: .
    read_only: true
    security_opt:
      - no-new-privileges:true
    cap_drop:
      - ALL
    cap_add:
      - NET_BIND_SERVICE
    healthcheck:
      test: ["CMD", "curl", "-f", "http://localhost/"]
      interval: 30s
      timeout: 3s
      retries: 3
    volumes:
      - type: tmpfs
        target: /tmp
      - type: volume
        source: logs
        target: /var/log
    networks:
      - backend
```

### 6.3 CI/CD 파이프라인 통합

#### 6.3.1 보안 스캔 통합

1. **Github Actions 보안 파이프라인**
```yaml
# .github/workflows/security-scan.yml
name: Security Scan

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  security:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      
      # 의존성 취약점 스캔
      - name: Run Snyk
        uses: snyk/actions/node@master
        env:
          SNYK_TOKEN: ${{ secrets.SNYK_TOKEN }}
          
      # 컨테이너 이미지 스캔
      - name: Run Trivy
        uses: aquasecurity/trivy-action@master
        with:
          image-ref: 'myapp:latest'
          format: 'table'
          exit-code: '1'
          severity: 'CRITICAL,HIGH'
          
      # 인프라 코드 보안 검사
      - name: Run tfsec
        uses: aquasecurity/tfsec-action@v1.0.0
```

---

## 7. 일반적인 문제해결 (Troubleshooting)

### 7.1 SSH 접속 실패, 권한 거부

#### 7.1.1 일반적인 SSH 문제 해결

1. **SSH 연결 진단**
```bash
# SSH 상세 디버그 모드로 연결 시도
ssh -vvv user@hostname

# SSH 서비스 상태 확인
sudo systemctl status sshd

# SSH 설정 문법 검사
sudo sshd -t
```

2. **일반적인 해결 방법**
```bash
# 권한 확인 및 수정
chmod 700 ~/.ssh
chmod 600 ~/.ssh/authorized_keys

# SSH 키 재생성
ssh-keygen -t ed25519 -f ~/.ssh/id_ed25519

# known_hosts 초기화
rm ~/.ssh/known_hosts
```

#### 7.1.2 SELinux 관련 문제
```bash
# SELinux 문맥 확인
ls -Z ~/.ssh/authorized_keys

# SSH 관련 SELinux 설정 수정
restorecon -Rv ~/.ssh/

# SELinux 정책 확인
sesearch --allow -s sshd_t
```

### 7.2 방화벽 규칙 충돌

#### 7.2.1 UFW 문제 해결

1. **방화벽 규칙 진단**
```bash
# 현재 규칙 확인
sudo ufw status verbose

# 특정 포트 테스트
sudo ufw status | grep 80

# 로그 확인
tail -f /var/log/ufw.log
```

2. **규칙 재설정**
```bash
# 방화벽 초기화
sudo ufw reset

# 기본 규칙 재설정
sudo ufw default deny incoming
sudo ufw default allow outgoing

# 필요한 포트만 허용
sudo ufw allow ssh
sudo ufw allow http
sudo ufw allow https
```

#### 7.2.2 iptables 문제 해결
```bash
# 현재 규칙 확인
sudo iptables -L -v -n

# 특정 체인 규칙 확인
sudo iptables -S INPUT

# 규칙 초기화
sudo iptables -F
sudo iptables -P INPUT ACCEPT
sudo iptables -P FORWARD ACCEPT
sudo iptables -P OUTPUT ACCEPT
```

### 7.3 패키지 업데이트 시 충돌/오류

#### 7.3.1 APT 문제 해결

1. **패키지 시스템 복구**
```bash
# 패키지 상태 확인
dpkg --audit

# 깨진 의존성 수정
sudo apt-get -f install

# 패키지 캐시 정리
sudo apt-get clean
sudo apt-get autoclean
```

2. **저장소 문제 해결**
```bash
# 저장소 인덱스 재구성
sudo rm -rf /var/lib/apt/lists/*
sudo apt-get update

# 특정 패키지 재설치
sudo apt-get install --reinstall package-name
```

## 8. 보안 체크리스트

### 8.1 초기 설정 체크리스트
- [ ] 루트 로그인 비활성화
- [ ] SSH 키 기반 인증 설정
- [ ] 불필요한 서비스 비활성화
- [ ] 방화벽 규칙 설정
- [ ] 시스템 업데이트 및 패치
- [ ] 보안 로깅 활성화
- [ ] 파일 시스템 권한 설정
- [ ] 주요 포트 보안 설정

### 8.2 정기 점검 체크리스트

#### 8.2.1 일일 점검 항목
- [ ] 시스템 로그 검토
- [ ] 실패한 로그인 시도 확인
- [ ] 디스크 사용량 모니터링
- [ ] 백업 상태 확인
- [ ] 보안 알림 검토

#### 8.2.2 주간 점검 항복
- [ ] 시스템 업데이트 확인
- [ ] 사용자 계정 감사
- [ ] 방화벽 규칙 검토
- [ ] 서비스 상태 점검
- [ ] 보안 패치 적용 상태 확인

#### 8.2.3 월간 점검 항목
- [ ] 전체 시스템 보안 감사
- [ ] 사용자 권한 검토
- [ ] SSL 인증서 만료 확인
- [ ] 백업 복구 테스트
- [ ] 보안 정책 검토 및 업데이트

---

## 9. 요약 (Summary)

서버 하드닝은 지속적이고 다층적인 보안 강화 프로세스입니다. 이 문서에서 다룬 주요 내용을 정리하면 다음과 같습니다.

### 9.1 핵심 보안 영역

1. **OS 레벨 보안**
   - 사용자 및 권한 관리
   - SSH 보안 설정
   - 시스템 업데이트 및 패치 관리
   - 방화벽 구성

2. **애플리케이션 레벨 보안**
   - 웹 서버 보안 설정
   - SSL/TLS 구성
   - 서비스 격리
   - 프로세스 분리

3. **모니터링 및 감사**
   - 중앙 로깅 시스템
   - 보안 이벤트 모니터링
   - 자동화된 알림
   - 정기적인 보안 감사

### 9.2 모범 사례

1. **최소 권한 원칙**
   - 필요한 최소한의 권한만 부여
   - 서비스별 전용 계정 사용
   - root 접근 제한

2. **심층 방어**
   - 다중 보안 계층 구현
   - 방화벽과 접근 제어 결합
   - 암호화와 인증 병행

3. **자동화와 표준화**
   - 구성 관리 도구 활용
   - 자동화된 보안 검사
   - 표준화된 배포 프로세스

## 10. 참고 자료 (References)

### 10.1 공식 보안 가이드라인

1. **운영체제 보안 가이드**
   - [Ubuntu Security Guide](https://ubuntu.com/security/certifications)
   - [Red Hat Security Hardening](https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/8/html/security_hardening/index)
   - [CIS Benchmarks](https://www.cisecurity.org/cis-benchmarks/)

2. **클라우드 보안 가이드**
   - [AWS Security Best Practices](https://aws.amazon.com/architecture/security-identity-compliance)
   - [Google Cloud Security Blueprint](https://cloud.google.com/architecture/security-foundations)
   - [Azure Security Best Practices](https://docs.microsoft.com/azure/security/fundamentals/)

### 10.2 보안 도구 및 프레임워크

1. **시스템 하드닝 도구**
   - [Lynis](https://cisofy.com/lynis/)
   - [OpenSCAP](https://www.open-scap.org/)
   - [Ansible Security Automation](https://www.ansible.com/use-cases/security-automation)

2. **모니터링 도구**
   - [ELK Stack](https://www.elastic.co/elastic-stack)
   - [Nagios](https://www.nagios.org/)
   - [Prometheus](https://prometheus.io/)

### 10.3 보안 커뮤니티 및 리소스

1. **보안 정보 공유**
   - [US-CERT](https://www.cisa.gov/uscert)
   - [NIST National Vulnerability Database](https://nvd.nist.gov/)
   - [MITRE ATT&CK](https://attack.mitre.org/)

2. **보안 트레이닝**
   - [Linux Foundation Security Training](https://training.linuxfoundation.org/security-training/)
   - [SANS Institute](https://www.sans.org/)
   - [Offensive Security](https://www.offensive-security.com/)

### 10.4 정기 업데이트 소스

- [Security Weekly Newsletter](https://securityweekly.com/)
- [US-CERT Bulletins](https://www.cisa.gov/uscert/ncas/bulletins)
- [NIST Security Publications](https://csrc.nist.gov/publications)

> 💡 **유지 관리 노트**  
> 이 문서는 정기적으로 업데이트되어야 합니다. 새로운 보안 위협과 대응 방안이 계속해서 등장하므로, 최소 분기별로 내용을 검토하고 업데이트하는 것을 권장합니다.