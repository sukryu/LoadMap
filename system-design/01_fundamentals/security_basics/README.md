# 📂 보안 기초 - security_basics

> **목표:**  
> - 보안의 핵심 개념과 원칙을 학습하고 이해한다.  
> - 기밀성, 무결성, 가용성(CIA Triad)과 같은 보안의 기본 원칙을 익힌다.  
> - 인증(AuthN)과 인가(AuthZ), 네트워크 보안, 암호화 기법 등의 필수 개념을 학습한다.

---

## 📌 **디렉토리 구조**
```
security_basics/                # 보안 기초 개념 학습
├── cia_triad.md                # 기밀성, 무결성, 가용성(CIA Triad)
├── authentication_vs_authorization.md # 인증과 인가의 차이(AuthN vs AuthZ)
├── network_security.md         # 네트워크 보안(방화벽, IDS/IPS, VPN)
├── encryption_basics.md        # 암호화 기초(대칭키, 비대칭키, 해싱)
├── security_best_practices.md  # 보안 모범 사례 및 정책
└── README.md
```

---

## 📖 **1. 개념 개요**
> **보안 기초(Security Basics)는 시스템과 데이터를 보호하기 위한 필수적인 개념과 원칙을 배우는 과정이다.**

- ✅ **왜 중요한가?**  
  - 모든 시스템은 외부 및 내부 위협으로부터 보호되어야 한다.
  - 보안 개념을 이해하면 더 안전한 애플리케이션과 인프라를 구축할 수 있다.
  - 실무에서 API 보안, 클라우드 보안, 쿠버네티스 보안을 적용하기 위한 기초가 된다.

- ✅ **어떤 문제를 해결하는가?**  
  - 데이터 유출 및 무단 접근 방지
  - 신뢰할 수 있는 사용자 인증 및 접근 제어 구현
  - 보안 위협(Man-in-the-Middle 공격, 피싱, SQL Injection 등) 예방

- ✅ **실무에서 어떻게 적용하는가?**  
  - 암호화(TLS, AES, RSA)를 활용하여 데이터 보호
  - 방화벽 및 네트워크 보안 정책 설정을 통해 악성 트래픽 차단
  - 역할 기반 접근 제어(RBAC)를 활용하여 사용자 권한 관리

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **기밀성, 무결성, 가용성(CIA Triad) (cia_triad.md)**
  - 기밀성(Confidentiality): 민감한 데이터 보호
  - 무결성(Integrity): 데이터 변조 방지
  - 가용성(Availability): 시스템이 항상 정상적으로 작동하도록 보장

- **인증 vs 인가 (authentication_vs_authorization.md)**
  - 인증(Authentication): 사용자가 누구인지 확인 (예: 비밀번호, 2FA, 생체 인증)
  - 인가(Authorization): 사용자에게 어떤 권한이 있는지 확인 (예: RBAC, ABAC)

- **네트워크 보안 (network_security.md)**
  - 방화벽(Firewall)과 IDS/IPS 개념
  - VPN, 프록시 서버를 통한 보안 통신
  - 공용 네트워크에서 보안을 유지하는 방법

- **암호화 기초 (encryption_basics.md)**
  - 대칭키 vs 비대칭키 암호화 (AES, RSA, ECC)
  - 해싱 알고리즘 (SHA-256, bcrypt) 및 무결성 보장
  - HTTPS와 TLS/SSL을 통한 안전한 데이터 전송

- **보안 모범 사례 (security_best_practices.md)**
  - 최소 권한 원칙 (Principle of Least Privilege)
  - 보안 로그 및 모니터링 (SIEM, Audit Logs)
  - 보안 정책 및 대응 계획 수립

---

## 🚀 **3. 실전 사례 분석**
> **실제 기업에서 보안 기초 개념이 어떻게 활용되는가?**

- **Google** - Zero Trust 보안 모델 적용 (BeyondCorp)
- **AWS** - IAM을 활용한 최소 권한 원칙 적용
- **Facebook** - 데이터 암호화 및 API 보안 정책 강화

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ 실전 사례 분석  
3️⃣ 보안 정책 및 원칙을 코드에 적용  
4️⃣ 지속적인 보안 개선 및 트레이드오프 분석  

---

## 📚 **5. 추천 리소스**
- 📖 _The Web Application Hacker’s Handbook_ - Dafydd Stuttard  
- 📖 _Computer Security: Principles and Practice_ - William Stallings  
- 📖 _Practical Cryptography_ - Bruce Schneier  
- 📌 [OWASP Top 10 Security Risks](https://owasp.org/www-project-top-ten/)  
- 📌 [Google Security Blog](https://security.googleblog.com/)  

---

## ✅ **마무리**
이 문서는 **보안의 핵심 개념과 실무 적용 방법을 학습하는 단계**입니다.
이론 → 보안 개념 학습 → 실전 사례 → 실습의 흐름을 따라 학습하며,
보안의 기초를 탄탄히 쌓고 실무에서 보안 정책을 효과적으로 적용할 수 있도록 합니다. 🚀

