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