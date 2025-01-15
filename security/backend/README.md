# 백엔드 보안 (Backend Security)

이 디렉토리는 **웹/백엔드 애플리케이션 보안**을 다루는 문서들을 모아 놓은 곳입니다.  
**OWASP Top 10**, **API 인증/인가**, **서버 하드닝** 같은 핵심 주제를 심도 있게 살펴볼 수 있습니다.

---

## 디렉토리 구성 (Files Overview)

```plaintext
backend/
├── 01_web_app_owasp.md                 # 웹 애플리케이션 보안(OWASP Top 10 등)
├── 02_api_auth.md                      # API 인증/인가(JWT, OAuth2, RBAC 등)
├── 03_server_hardening.md              # 서버/시스템 하드닝(SSH, OS권한, 로깅 등)
└── README.md                           # backend/ 폴더 개요
```


1. **`01_web_app_owasp.md`**  
   - OWASP Top 10 중심 웹 취약점: Injection, XSS, CSRF, 취약 인증/세션 관리 등  
   - 방어 기법(PreparedStatement, escaping, CSRF 토큰 등)  
   - 민감 정보 노출 방지

2. **`02_api_auth.md`**  
   - API 인증/인가(JWT, OAuth2, Refresh Token 등)  
   - RBAC/ABAC, 토큰 만료/재발급 설계  
   - 실무 구현 예시(서버 코드, JWT 서명 검증 로직)

3. **`03_server_hardening.md`**  
   - 서버/시스템 보안(SSH, OS 권한 최소화, Fail2ban 등)  
   - 환경변수 보안(.env)와 시크릿 관리  
   - 로깅/모니터링 & 보안 사고 대응

---

## 학습 순서 (Recommended Reading Path)

1. **`01_web_app_owasp.md`**  
   - **OWASP Top 10** 문제 이해 → Injection, XSS, CSRF 등 대표 공격 기법 파악
   - 웹 애플리케이션 기초 보안 대비

2. **`02_api_auth.md`**  
   - **API 인증/인가** 체계, JWT/OAuth2, RBAC/ABAC  
   - Access/Refresh Token 전략, 만료·갱신 등

3. **`03_server_hardening.md`**  
   - **서버 운영체제(OS) 보안**: SSH 키 인증, 방화벽, 환경변수 관리  
   - 로깅/모니터링으로 보안 사고 조기 발견

---

## 보안 체크리스트 (Security Checklist)

아래 체크박스를 통해, 각 영역별 핵심 보안 포인트를 빠르게 점검할 수 있습니다.

1. **웹 애플리케이션 보안**
   - [ ] SQL Injection 방어 (PreparedStatement 사용, ORM safe query)
   - [ ] XSS 방어 (입출력 이스케이프, CSP 헤더 고려)
   - [ ] CSRF 토큰 구현 (Form Token, SameSite 쿠키 등)
   - [ ] 안전한 세션 관리 (쿠키 설정: `HttpOnly`, `Secure`, `SameSite`)

2. **API 인증/인가**
   - [ ] JWT 서명 검증(비밀키/공개키 안전 보관)
   - [ ] 토큰 만료 관리(Access/Refresh Token 주기적 회전)
   - [ ] RBAC 구현(역할 기반 권한 설정)
   - [ ] OAuth2 흐름 보안(인증 코드 노출 방지, PKCE 등)

3. **서버 하드닝**
   - [ ] SSH 키 기반 인증, root 로그인 비활성화
   - [ ] 방화벽/포트 제한 (ufw, iptables 등)
   - [ ] 로그 모니터링 (액세스 로그, 에러 로그)
   - [ ] 환경변수 보안 (민감정보 .env, Vault, Secrets Manager 연동)

---

## 일반적인 문제 해결 (Common Troubleshooting)

1. **토큰 관련 이슈**
   - JWT 만료 처리 실패 → Refresh Token 로직 재확인  
   - Refresh Token 순환(reuse detection)  
   - 토큰 취소 전략(블랙리스트, 짧은 만료 + 자주 재발급)

2. **권한 설정 문제**
   - RBAC 디버깅 (유저/그룹/역할 매칭)  
   - 접근 제어 로그(누가 어느 리소스 접근 실패?) 분석  
   - API 요청 경로 별 권한 검사 로직 점검

3. **서버 보안 이슈**
   - SSH 접속 실패 → auth.log 확인, IP 차단(브루트포스), 키·퍼미션 재확인  
   - 로그 분석(에러 패턴, 4xx/5xx 급증)  
   - 서드파티 라이브러리 취약점/버전 확인(npm audit, pip list --outdated)

---

## 실제 사례 연구 (Case Studies)

1. **JWT 토큰 탈취 사고와 대응**
   - 공격 시나리오: 악성 스크립트로 쿠키/토큰 훔침  
   - 대응: `HttpOnly`, `Secure`, 만료·재발급 강화, suspicious IP 즉시 차단

2. **SQL Injection 공격 사례와 방어**
   - 공격자: URL 파라미터에 SQL 구문 삽입, DB 레코드 유출  
   - 방어: PreparedStatement, ORM Parameter Binding, WAF 필터

3. **무차별 대입 공격(Brute Force)과 Fail2ban 설정**
   - 공격 시나리오: SSH/로그인 폼에 무작위 시도  
   - 대응: Fail2ban, IP 차단, 백오피스 접근 제한(IP allowlist)

---

## 문서 활용 팁 (How to Use)

- **체크리스트**로 빠른 점검  
  - 새 프로젝트나 리팩토링 시 한 번에 확인(“XSS 방어 했는가?”, “JWT 만료 정책 있는가?”)

- **트러블슈팅** 사례로 현장 문제 해결  
  - 실제로 발생하는 인증, 권한, 서버 접근 이슈를 재현하고, 문서 속 해결책 참고

- **실제 사고 사례**를 통해 경각심  
  - JWT 유출, SQL Injection 사례에서 **어떤 미비점**이 있었고 **어떻게 보강**했는지 참고

---

## 다음 학습 단계 (Next Steps)

- **클라우드 보안**(`../cloud/`): IAM, VPC, WAF, DDoS 방어  
- **쿠버네티스 보안**(`../kubernetes/`): Docker/K8s 컨테이너, RBAC, NetworkPolicy  
- **DevSecOps** 관점: CI/CD 파이프라인에서 소스/이미지 취약점 스캐닝, Terraform 보안 검사  
- **애플리케이션 레벨**: gRPC/GraphQL 등의 통신 프로토콜 보안, mTLS 등

---

안전하고 신뢰할 수 있는 **백엔드 서비스**를 만들어나가길 바랍니다!  
**OWASP 취약점**부터 **API 인증/인가**, **서버 하드닝**까지 **체계적**으로 점검하면,  
취약점을 줄이고, 확신을 가지고 시스템을 운영할 수 있습니다.
