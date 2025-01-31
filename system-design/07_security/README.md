# 📂 **07_security (보안)**
> **목표:**  
> - **소프트웨어 및 인프라 보안**의 기본 개념을 익힌다.  
> - **인증 및 인가, API 보안, 데이터 암호화, DevSecOps** 등의 보안 기법을 학습한다.  
> - 실무에서 **안전한 시스템을 설계하고 공격을 방어하는 방법**을 배운다.

---

## 📌 **디렉토리 구조 및 학습 내용**
```
security/
├── authentication/            # 인증 및 인가
├── api_security/              # API 보안
├── data_encryption/           # 데이터 암호화
├── devsecops/                 # DevSecOps & 보안 자동화
├── zero_trust/                # Zero Trust 아키텍처
├── infrastructure_security/   # 인프라 보안
├── identity_management/       # IAM & 권한 관리
├── compliance_gdpr/           # 데이터 규제 및 GDPR 대응
└── real_world_examples/       # 실전 사례 분석
```

---

## 📖 **1. 인증 및 인가 (authentication/)**
> **사용자 인증 및 접근 제어 시스템 설계**  

### 📚 학습 내용
- **Authentication vs Authorization**
  - 인증(Authentication)과 인가(Authorization)의 차이
  - 실무 적용: **OAuth2, OpenID Connect, JWT 활용**

- **Single Sign-On (SSO)**
  - 여러 서비스에서 한 번의 로그인으로 인증
  - 실무 적용: **Google, Facebook SSO 방식 분석**

- **Multi-Factor Authentication (MFA)**
  - 추가 보안 레이어 적용 (OTP, 생체인증)
  - 실무 적용: **은행, 금융 시스템에서 MFA 적용**

---

## 📖 **2. API 보안 (api_security/)**
> **API를 안전하게 보호하는 방법 학습**  

### 📚 학습 내용
- **Rate Limiting & Throttling**
  - DDoS 공격 방지를 위한 요청 제한
  - 실무 적용: **AWS API Gateway Rate Limiting 설정**

- **OAuth2 & API Keys**
  - 클라이언트가 API를 안전하게 호출하는 방법
  - 실무 적용: **OAuth2.0 Authorization Code Flow 적용**

- **HMAC & Digital Signatures**
  - 요청의 무결성을 검증하는 방법
  - 실무 적용: **Webhook 서명 검증 방식**

---

## 📖 **3. 데이터 암호화 (data_encryption/)**
> **데이터를 안전하게 저장하고 전송하는 방법 학습**  

### 📚 학습 내용
- **Symmetric vs Asymmetric Encryption**
  - 대칭키 vs 비대칭키 암호화 비교
  - 실무 적용: **AES, RSA, ECC 암호화 방식 분석**

- **TLS & HTTPS**
  - 데이터 전송 시 보안 유지
  - 실무 적용: **SSL/TLS 인증서 적용 및 HSTS 설정**

- **Database Encryption**
  - 저장된 데이터의 보안 유지 방법
  - 실무 적용: **MySQL TDE(Transparent Data Encryption) 활용**

---

## 📖 **4. DevSecOps & 보안 자동화 (devsecops/)**
> **CI/CD 파이프라인에서 보안을 자동화하는 방법 학습**  

### 📚 학습 내용
- **Shift-Left Security**
  - 개발 초기 단계부터 보안 적용
  - 실무 적용: **코드 분석 도구 활용 (Snyk, SonarQube)**

- **Container Security**
  - Docker, Kubernetes 환경에서 보안 강화
  - 실무 적용: **Kubernetes Network Policies 활용**

- **Security as Code**
  - 코드로 보안 정책을 관리하는 방식
  - 실무 적용: **Terraform 및 AWS Security Hub 적용**

---

## 📖 **5. Zero Trust 아키텍처 (zero_trust/)**
> **신뢰할 수 없는 네트워크에서도 보안을 유지하는 방법 학습**  

### 📚 학습 내용
- **What is Zero Trust?**
  - 기본적으로 모든 트래픽을 신뢰하지 않는 보안 모델
  - 실무 적용: **Google BeyondCorp 사례 분석**

- **Identity-Based Security**
  - 사용자 및 디바이스 인증 기반 접근 제어
  - 실무 적용: **IAM 기반 Zero Trust 환경 구축**

- **Microsegmentation**
  - 네트워크를 세분화하여 접근 통제
  - 실무 적용: **Cloud Firewall & VPC Security 적용**

---

## 📖 **6. 인프라 보안 (infrastructure_security/)**
> **서버 및 네트워크 보안을 강화하는 방법 학습**  

### 📚 학습 내용
- **Firewalls & Security Groups**
  - 네트워크 보안을 위한 기본적인 접근 통제
  - 실무 적용: **AWS Security Group & NACL 설정**

- **DDoS Protection**
  - 분산 서비스 거부 공격 방어 전략
  - 실무 적용: **Cloudflare, AWS Shield 활용**

- **Log & Intrusion Detection**
  - 시스템 로그 분석 및 침입 탐지 시스템(IDS) 적용
  - 실무 적용: **Wazuh, OSSEC 기반 침입 탐지**

---

## 📖 **7. IAM & 권한 관리 (identity_management/)**
> **권한 및 역할 기반 접근 제어(RBAC)를 설계하는 방법 학습**  

### 📚 학습 내용
- **Role-Based Access Control (RBAC)**
  - 역할 기반 권한 관리 방식
  - 실무 적용: **AWS IAM Role & Policy 설정**

- **Attribute-Based Access Control (ABAC)**
  - 속성 기반 접근 제어 모델
  - 실무 적용: **Azure AD ABAC 활용**

- **Least Privilege Principle (최소 권한 원칙)**
  - 불필요한 권한 부여 방지
  - 실무 적용: **클라우드 환경에서 IAM 정책 최적화**

---

## 📖 **8. 데이터 규제 및 GDPR 대응 (compliance_gdpr/)**
> **데이터 보호 및 개인정보 처리 법률 준수 전략 학습**  

### 📚 학습 내용
- **GDPR & CCPA Compliance**
  - 유럽(EU) 및 미국(캘리포니아) 데이터 보호법 비교
  - 실무 적용: **사용자 데이터 삭제 요청 처리**

- **Data Masking & Anonymization**
  - 개인정보 보호를 위한 데이터 변환 기술
  - 실무 적용: **Tokenization vs Pseudonymization 비교**

- **Audit Logging & Compliance Monitoring**
  - 데이터 액세스 기록 유지 및 감사 로그 관리
  - 실무 적용: **AWS CloudTrail을 활용한 감사 로그 관리**

---

## 📖 **9. 실전 사례 분석 (real_world_examples/)**
> **실제 기업들의 보안 사례 및 공격 대응 방식 학습**  

### 📚 학습 내용
- **Google의 Zero Trust 보안 모델 (BeyondCorp)**
- **Facebook의 OAuth 인증 및 API 보안 전략**
- **Amazon의 IAM 정책 및 보안 자동화 적용 사례**
- **Apple의 개인정보 보호 정책 및 데이터 암호화 기법**
- **Cloudflare의 DDoS 방어 시스템 구축 사례**