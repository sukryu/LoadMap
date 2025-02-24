# 보안(Security) 디렉토리

현대 **백엔드 + 클라우드 엔지니어**가 알아야 할 **핵심 보안 주제**들을 모아 놓은 디렉토리입니다.  
**웹 애플리케이션(Backend) 보안**, **클라우드 인프라(Cloud) 보안**, **쿠버네티스(Kubernetes) 보안**처럼 영역별로 문서를 분리하여, 체계적으로 학습하고 참고할 수 있게 구성했습니다.

추가로 아래와 같은 항목들을 보완했습니다:
- **실습 환경 가이드**: 학습에 필요한 환경(Docker, Kubernetes 클러스터, 클라우드 계정 등)을 소개합니다.
- **취약점 진단 및 자동화 도구**: OWASP ZAP, Burp Suite, Trivy, Snyk, Lynis, Auditd, Falco, Kube-bench 등 실무에서 사용할 수 있는 도구들을 추천합니다.
- **DevSecOps 및 보안 자동화**: CI/CD 파이프라인에서의 보안 검사 도구 연동 방법을 소개합니다.
- **보안 사고 대응**: 실제 보안 사고 발생 시 SIEM, 로그 분석, IDS/IPS 활용 등 사고 대응(IR) 방법에 대해 다룹니다.
- **최신 보안 트렌드 및 미래 발전 방향**: Zero Trust, 공급망 보안(Supply Chain Security), Confidential Computing 등 최신 이슈를 포함합니다.

---

## 디렉토리 구성 (Files & Folders)

```plaintext
security/
├── README.md                                # 보안 디렉토리 전체 개요 및 실습/자동화/사고 대응 가이드 추가
├── backend/
│   ├── 01_web_app_owasp.md                 # 웹 애플리케이션 보안(OWASP Top 10 등)
│   ├── 02_api_auth.md                      # API 인증/인가(JWT, OAuth2, RBAC 등)
│   ├── 03_server_hardening.md              # 서버/시스템 하드닝(SSH, OS권한, 로깅 등)
│   └── README.md                           # backend/ 폴더 개요
├── cloud/
│   ├── 01_iam.md                           # 클라우드 IAM(AWS/GCP/Azure Role/Policy)
│   ├── 02_network_security.md              # VPC/서브넷/보안 그룹/NAT, DDoS, CloudFirewall
│   ├── 03_waf_ddos.md                      # WAF 설정, Rate Limiting, DDoS 방어
│   └── README.md                           # cloud/ 폴더 개요
└── kubernetes/
    ├── 01_container_security.md            # Docker 컨테이너 보안(이미지 스캐닝, non-root 등)
    ├── 02_k8s_cluster_security.md          # K8s RBAC, NetworkPolicy, PodSecurity, ETCD암호화
    ├── 03_service_mesh_security.md         # Istio/Linkerd mTLS, 사이드카 보안, 정책
    └── README.md                           # kubernetes/ 폴더 개요
```

- **루트 README.md**는 전체 보안 문서 개요와 학습 순서를 안내하며,  
  **실습 환경 가이드**, **자동화 도구 추천**, **보안 사고 대응** 및 **최신 보안 트렌드** 관련 추가 내용을 포함합니다.

---

## 학습 및 활용 가이드

### 1. 학습 순서 및 우선순위

1. **백엔드 보안**(`backend/`)
   - **01_web_app_owasp.md**: OWASP Top 10 및 대표 공격 기법(Injection, XSS, CSRF, 인증/세션 관리 등)과 방어 기법을 학습
   - **02_api_auth.md**: API 인증/인가 (JWT, OAuth2, Refresh Token, RBAC/ABAC) 및 토큰 관리 방법 습득
   - **03_server_hardening.md**: 서버/시스템 보안 강화 (SSH 키 기반 인증, 방화벽, 환경변수 관리, 로깅/모니터링)

2. **클라우드 보안**(`cloud/`)
   - **01_iam.md**: 클라우드 IAM 정책, 최소 권한 원칙, 자격 증명 관리, MFA 등 기초부터 고급 기능까지
   - **02_network_security.md**: VPC, 서브넷, NAT, Bastion Host, 보안 그룹 및 NACL 구성 방법
   - **03_waf_ddos.md**: WAF 설정, DDoS 방어 솔루션 및 실시간 로그/알림 설정

3. **쿠버네티스 보안**(`kubernetes/`)
   - **01_container_security.md**: Docker 이미지 보안, non-root 실행, 컨테이너 런타임 보안
   - **02_k8s_cluster_security.md**: K8s 클러스터 보안(Cluster RBAC, 네트워크 정책, PodSecurity, ETCD 암호화)
   - **03_service_mesh_security.md**: Istio/Linkerd를 통한 Service Mesh 보안, mTLS 및 트래픽 정책 설정

---

### 2. 추가 학습 자료 및 실습 환경

#### 실습 환경 가이드
- **필수 도구**: Docker, Kubernetes 클러스터(로컬 Minikube 또는 클라우드 클러스터), VM 또는 클라우드 계정(AWS/GCP/Azure)
- **실습 환경 구성**: 
  - 로컬에서 Docker와 Kubernetes(Minikube, Kind) 설치
  - 클라우드 계정으로 IAM, VPC, WAF 등 실제 환경 설정 및 실습
  - Terraform, CloudFormation 등을 이용한 IaC 실습

#### 취약점 진단 및 자동화 도구 추천
- **웹/애플리케이션**: OWASP ZAP, Burp Suite
- **컨테이너/인프라**: Trivy, Snyk, Lynis, Auditd, Falco, Kube-bench
- **CI/CD 연동**: GitHub Actions, Jenkins, GitLab CI/CD에 보안 검사 도구 통합

#### DevSecOps 및 보안 자동화
- **CI/CD 파이프라인**: 소스코드, 컨테이너 이미지, 인프라 코드(Terraform, CloudFormation)에 대한 자동 보안 스캔
- **보안 테스트 도구 연동**: SAST, DAST, 이미지 스캐닝 도구 연동
- **자동화 스크립트**: 보안 구성 관리 및 취약점 스캐닝 자동화

#### 보안 사고 대응 (IR: Incident Response)
- **사고 탐지**: SIEM(예, ELK Stack, Splunk), 로그 분석, IDS/IPS 활용
- **알림 체계**: CloudWatch, Prometheus+Grafana, Slack/Webhook, 이메일 알림 등
- **사고 대응 프로세스**: 침해 사고 탐지, 초기 대응, 영향 평가, 복구 및 사후 분석

#### 최신 보안 트렌드 및 미래 발전 방향
- **Zero Trust 보안 모델**: 내부 네트워크에도 세밀한 인증 및 접근 제어 적용
- **공급망 보안 (Supply Chain Security)**: SLSA, Sigstore 등을 통한 소프트웨어 공급망 보호
- **Confidential Computing**: 데이터 처리 시 암호화된 상태 유지
- **AI/ML 기반 보안 탐지**: 이상 징후 자동 탐지 및 대응

---

### 3. 보안 체크리스트

각 문서 별로 제공되는 체크리스트 외에, 아래와 같이 전체 점검용 체크리스트를 활용해 실무 적용 시 빠짐없이 보안 설정을 점검할 수 있습니다.

#### 웹/애플리케이션 보안 체크리스트
- [ ] SQL Injection 방어 (PreparedStatement, ORM safe query)
- [ ] XSS 방어 (입출력 이스케이프, CSP 헤더)
- [ ] CSRF 토큰 적용 및 SameSite 쿠키 설정
- [ ] 안전한 세션 관리 (HttpOnly, Secure)

#### API 인증/인가 체크리스트
- [ ] JWT 서명 및 만료 관리 (Access/Refresh Token 전략)
- [ ] RBAC/ABAC 기반 접근 제어 구현
- [ ] OAuth2 흐름 보안 (PKCE, 인가 코드 보호)

#### 서버 하드닝 체크리스트
- [ ] SSH 키 기반 인증 및 root 로그인 비활성화
- [ ] 방화벽 규칙(UFW, iptables) 및 포트 제한
- [ ] 시스템 업데이트 및 패치 자동화
- [ ] 민감 정보(환경변수, 설정 파일) 암호화 및 Vault 연동
- [ ] 로깅/모니터링 설정 및 정기 감사

---

### 4. 향후 발전 방향 및 참고 자료

#### 발전 방향 (Future Extensions)
1. **CI/CD & DevSecOps**  
   - 소스코드, 컨테이너 이미지, 인프라 코드에 대한 보안 스캔 자동화  
   - 보안 구성 관리 도구(Terraform, CloudFormation) 및 IaC 보안 점검

2. **Zero Trust/SASE**  
   - 네트워크 경계가 사라진 환경에서 아이덴티티 기반 접근 제어 적용  
   - BeyondCorp 접근 제어 모델 도입

3. **대규모 엔터프라이즈 보안**  
   - SOC, SIEM, IDS/IPS 운영 및 보안 사고 대응 체계 구축  
   - BGP/OSPF 라우팅 보안 및 클라우드 연결 시 DDoS 방어 강화

4. **암호화 및 키 관리**  
   - KMS, Vault, HSM을 통한 데이터 암호화(At-rest, In-transit)  
   - SSL 인증서 자동화 및 공급망 보안(SLSA, Sigstore) 대응

5. **최신 보안 트렌드**  
   - Confidential Computing, AI/ML 기반 이상 탐지 도입  
   - 공급망 공격 대응, Zero Trust 네트워크 구현

#### 참고 자료
- **공식 보안 가이드라인**: OWASP, NIST, CIS Benchmarks 등
- **보안 도구 및 테스트**: OWASP ZAP, Burp Suite, Trivy, Snyk, Lynis, Auditd, Falco, Kube-bench
- **온라인 강좌 및 커뮤니티**: SANS, Offensive Security, Reddit r/netsec 등

---

### 5. 문서 활용 팁

- **실습 환경**: 각 영역별로 제시한 실습 환경 가이드를 참고하여 Docker, Kubernetes, 클라우드 계정 등을 준비한 후 실습 진행
- **자동화 도구**: 제시한 도구들을 직접 설치 및 연동해 보며, CI/CD 파이프라인에 보안 스캔을 포함시키세요.
- **사고 대응 사례**: 실제 보안 사고 사례와 대응 방법을 참고해, 사고 발생 시 대응 프로세스를 마련하세요.
- **팀 협업**: 이 문서를 바탕으로 팀 내 보안 가이드라인을 수립하고, 정기적인 보안 점검 및 업데이트를 실시하세요.

---

**좋은 학습 되세요!**  
이 `security/` 디렉토리의 문서들은 **"백엔드/클라우드/쿠버네티스 보안"**을 체계적으로 정리하여, 실습과 실무 적용에 도움이 되도록 구성되었습니다.  
각 영역의 기초부터 고급 기능까지 단계별로 학습하고, 실습 환경과 자동화 도구, 보안 사고 대응 등을 통해 실무에 바로 적용해 보시길 바랍니다.