# 📂 보안 - 07_security

> **목표:**  
> - 애플리케이션 및 인프라 보안의 핵심 개념을 학습한다.  
> - 인증, 인가, 데이터 암호화, API 보안 및 인프라 보안 원칙을 이해하고 실무에 적용한다.  
> - 최신 보안 위협 및 대응 방안을 연구하여 안전한 시스템을 설계한다.

---

## 📌 **디렉토리 구조**
```
07_security/                   # 보안 개념 학습
├── authentication/            # 인증 및 인가
├── api_security/              # API 보안
├── data_encryption/           # 데이터 암호화
├── devsecops/                 # DevSecOps & 보안 자동화
├── zero_trust/                # Zero Trust 아키텍처
├── infrastructure_security/   # 인프라 보안
├── compliance_gdpr/           # 데이터 규제 및 GDPR 대응
└── README.md
```

---

## 📖 **1. 개념 개요**
> **보안(Security)은 시스템의 기밀성, 무결성, 가용성을 보장하기 위한 필수 요소이다.**

- ✅ **왜 중요한가?**  
  - 데이터 유출 및 해킹 공격을 방지하기 위해 필수적이다.
  - 기업의 신뢰성과 법적 규정을 준수하는 데 중요한 역할을 한다.
  - 클라우드 환경에서의 보안 강화가 필수적으로 요구된다.

- ✅ **어떤 문제를 해결하는가?**  
  - 인증 및 인가 오류로 인한 데이터 유출 문제 해결
  - API 및 인프라의 보안 취약점 방지
  - 규정 준수 및 보안 정책을 체계적으로 관리

- ✅ **실무에서 어떻게 적용하는가?**  
  - OAuth 2.0, JWT, SAML을 활용한 인증 및 권한 부여
  - API 게이트웨이를 통한 보안 강화 및 WAF(Web Application Firewall) 적용
  - TLS, AES, RSA를 이용한 데이터 암호화 및 무결성 유지

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **인증 및 인가 (authentication/)**
  - OAuth 2.0, OpenID Connect, SAML 개념 및 적용
  - MFA(Multi-Factor Authentication)와 SSO(Single Sign-On)

- **API 보안 (api_security/)**
  - API Gateway 및 WAF(Web Application Firewall) 적용
  - Rate Limiting 및 API Key 관리 전략
  - 보안 헤더 및 HTTPS 적용

- **데이터 암호화 (data_encryption/)**
  - 대칭 및 비대칭 암호화 (AES, RSA, ECC)
  - 전송 중/저장 시 데이터 보호 (TLS, HSM 활용)
  - 해시 알고리즘 및 디지털 서명 적용

- **DevSecOps 및 보안 자동화 (devsecops/)**
  - 보안 CI/CD 파이프라인 구축 (SAST, DAST, IAST 적용)
  - 코드 보안 분석 및 자동화된 취약점 스캐닝
  - 컨테이너 및 쿠버네티스 보안 강화

- **Zero Trust 아키텍처 (zero_trust/)**
  - 네트워크 기반 접근 제어 및 무신뢰 모델 적용
  - 마이크로세그멘테이션 및 지속적 인증 원칙
  - ID 기반 보안 정책 및 정책 실행

- **인프라 보안 (infrastructure_security/)**
  - 클라우드 보안 원칙 (AWS, GCP, Azure 보안 베스트 프랙티스)
  - 네트워크 보안 (VPC, 방화벽, IDS/IPS 적용)
  - 컨테이너 및 서버리스 보안

- **데이터 규제 및 GDPR 대응 (compliance_gdpr/)**
  - GDPR, CCPA 등 개인 정보 보호법 준수 전략
  - 데이터 보존 및 삭제 정책 수립
  - ISO 27001 및 SOC 2 보안 인증 이해

---

## 🚀 **3. 실전 사례 분석**
> **대기업 및 클라우드 서비스에서 보안을 어떻게 강화하는가?**

- **Google** - Zero Trust 보안 모델(BeyondCorp) 적용 사례
- **Netflix** - AWS 보안 및 IAM(Identity Access Management) 적용 사례
- **Facebook** - OAuth 및 API 보안 정책 운영

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ 보안 패턴 학습  
3️⃣ 실제 사례 분석  
4️⃣ 코드 실습 진행  
5️⃣ 트레이드오프 분석  

---

## 📚 **5. 추천 리소스**
- 📖 _The Web Application Hacker’s Handbook_ - Dafydd Stuttard  
- 📖 _Security Engineering_ - Ross Anderson  
- 📖 _Zero Trust Networks_ - Evan Gilman & Doug Barth  
- 📌 [OWASP Top 10 Security Risks](https://owasp.org/www-project-top-ten/)  
- 📌 [Google Cloud Security Best Practices](https://cloud.google.com/security/best-practices)  

---

## ✅ **마무리**
이 문서는 **보안의 핵심 개념과 실무 적용 방법을 학습하는 단계**입니다.
이론 → 패턴 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며,
실무에서 보안 강화를 위한 전략을 효과적으로 적용할 수 있도록 합니다. 🚀

