# 📂 마이크로서비스 보안 - security

> **목표:**  
> - 마이크로서비스 아키텍처에서 보안의 중요성과 핵심 개념을 학습한다.  
> - 서비스 간 인증 및 인가, 데이터 보호, 보안 패턴을 이해하고 적용한다.  
> - Zero Trust 아키텍처와 보안 자동화 기법을 연구하고 실무에 적용한다.

---

## 📌 **디렉토리 구조**
```
security/                       # 보안 학습
├── introduction.md              # 보안 개요 및 원칙
├── authentication.md            # 인증(Authentication) 개념 및 구현
├── authorization.md             # 인가(Authorization) 및 RBAC
├── api_security.md              # API 보안 및 인증 토큰 관리
├── secure_communication.md      # 서비스 간 보안 통신 (mTLS, OAuth2)
├── data_protection.md           # 데이터 보호 및 암호화 전략
├── zero_trust_architecture.md   # Zero Trust 보안 모델
├── security_in_practice.md      # 실무에서의 보안 적용 사례
└── README.md
```

---

## 📖 **1. 개념 개요**
> **마이크로서비스 환경에서는 보안이 필수적이며, 서비스 간 통신 및 데이터 보호를 위한 전략이 필요하다.**

- ✅ **왜 중요한가?**  
  - 마이크로서비스는 분산된 환경에서 운영되므로 보안 위협에 노출될 가능성이 높다.
  - 네트워크를 통한 서비스 간 통신에서 인증 및 암호화가 필요하다.
  - 보안 취약점이 발생할 경우 전체 시스템의 무결성이 손상될 수 있다.

- ✅ **어떤 문제를 해결하는가?**  
  - 서비스 간 안전한 통신 보장
  - 무단 접근 및 권한 상승 공격 방지
  - 민감한 데이터 보호 및 안전한 저장 관리

- ✅ **실무에서 어떻게 적용하는가?**  
  - **OAuth2 및 JWT**를 활용한 인증 및 세션 관리
  - **RBAC(Role-Based Access Control)**을 이용한 접근 제어
  - **mTLS(Mutual TLS)**를 활용한 안전한 서비스 간 통신 구축

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **보안 개요 및 원칙 (introduction.md)**
  - 보안의 3대 요소(CIA: 기밀성, 무결성, 가용성)
  - 마이크로서비스에서 고려해야 할 보안 원칙

- **인증 (authentication.md)**
  - OAuth2, OpenID Connect, JWT 기반 인증 방식
  - 인증 토큰 및 세션 관리

- **인가 (authorization.md)**
  - RBAC(Role-Based Access Control), ABAC(Attribute-Based Access Control)
  - 서비스 간 권한 관리 및 액세스 제어 정책

- **API 보안 및 인증 토큰 관리 (api_security.md)**
  - API Gateway 보안 필터 적용
  - API Rate Limiting 및 Throttling 기법
  - HMAC 및 서명 기반 인증

- **서비스 간 보안 통신 (secure_communication.md)**
  - TLS 및 mTLS(Mutual TLS) 적용
  - OAuth2를 이용한 서비스 간 인증 및 토큰 관리
  - 보안 프로토콜(HTTPS, gRPC Secure 등)

- **데이터 보호 및 암호화 전략 (data_protection.md)**
  - 민감한 데이터 암호화 및 저장 전략
  - 데이터 전송 중 보호(TLS, VPN, 서비스 메시 보안)
  - 데이터 무결성을 보장하는 해싱 및 서명 기법

- **Zero Trust 보안 모델 (zero_trust_architecture.md)**
  - 경계 없는 보안 모델의 개념
  - 지속적인 인증 및 최소 권한 접근 적용
  - Zero Trust 기반의 네트워크 및 서비스 아키텍처 설계

- **실무에서의 보안 적용 사례 (security_in_practice.md)**
  - 대규모 서비스에서 보안 적용 전략 분석
  - 클라우드 환경(AWS, Google Cloud, Azure)에서의 보안 최적화
  - DevSecOps 및 보안 자동화 도구 활용

---

## 🚀 **3. 실전 사례 분석**
> **대규모 서비스에서 보안 전략이 어떻게 활용되는가?**

- **Netflix** - OAuth2 기반 인증 및 서비스 간 mTLS 적용
- **Google** - Zero Trust 보안 모델 적용 (BeyondCorp)
- **AWS** - IAM을 활용한 최소 권한 원칙 적용 및 보안 강화

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ OAuth2 및 인증 시스템 실습  
3️⃣ 실제 사례 연구  
4️⃣ 보안 자동화 코드 작성 및 실무 적용  

---

## 📚 **5. 추천 리소스**
- 📖 _Zero Trust Networks_ - Evan Gilman & Doug Barth  
- 📖 _OAuth 2 in Action_ - Justin Richer  
- 📖 _Practical Cryptography for Developers_ - Svetlin Nakov  
- 📌 [OWASP API Security Top 10](https://owasp.org/www-project-api-security/)  
- 📌 [Google BeyondCorp - Zero Trust Model](https://cloud.google.com/beyondcorp)  

---

## ✅ **마무리**
이 문서는 **마이크로서비스 아키텍처에서 보안 강화를 위한 다양한 전략을 학습하는 단계**입니다. 
이론 → 보안 기법 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며, 
확장성과 안정성을 고려한 최적의 보안 아키텍처를 설계할 수 있도록 합니다. 🚀