# 보안(Security) 디렉토리

현대 **백엔드 + 클라우드 엔지니어**가 알아야 할 **핵심 보안 주제**들을 모아 놓은 디렉토리입니다.  
**웹 애플리케이션(Backend) 보안**, **클라우드 인프라(Cloud) 보안**, **쿠버네티스(Kubernetes) 보안**처럼 영역별로 문서를 분리하여, 체계적으로 학습하고 참고할 수 있게 구성했습니다.

---

## 디렉토리 구성 (Files & Folders)

```plaintext
security/
├── README.md                                # 보안 디렉토리 전체 개요
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
- `README.md`(루트): `security/` 최상위 문서로, 전체 보안 문서의 개요/학습 순서 안내
- `backend/`: 웹/애플리케이션(API) 레벨의 보안, 서버 하드닝 관련 자료
- `cloud/`: 클라우드 인프라(IAM, 네트워크 설계, WAF/DDoS) 보안
- `kubernetes/`: Docker/K8s 컨테이너 보안, 클러스터/RBAC, Service Mesh 보안

### 1) `backend/`
- **01_web_app_owasp.md**  
  - **OWASP Top 10**을 중심으로 한 웹 취약점(Injection, XSS, CSRF, 인증/세션 관리, 민감 정보 노출 등)
  - 예시 코드(PreparedStatement, escaping)와 실무 방지 기법

- **02_api_auth.md**  
  - **API 인증/인가**(JWT, OAuth2, Refresh Token 전략)
  - RBAC/ABAC 설계, 권한 검증(백엔드 레벨/게이트웨이 레벨)
  - 실무 팁: 만료·갱신, 비밀키 관리

- **03_server_hardening.md**  
  - **서버/시스템 보안**: OS 권한, SSH 설정, Fail2ban/OS 업데이트
  - 환경변수/설정 파일에 민감정보 넣지 않기, Vault 연동
  - 로깅/모니터링(접속 로그, 에러 로그 등)

### 2) `cloud/`
- **01_iam.md**  
  - **클라우드 IAM**(AWS, GCP, Azure)
  - 최소 권한 원칙, 역할(Role)/정책(Policy) 설계
  - 자격 증명(Access Key), OIDC, MFA

- **02_network_security.md**  
  - **VPC 설계**(퍼블릭/프라이빗 Subnet, NAT/Bastion)
  - **보안 그룹/NACL**, 인터넷 게이트웨이/엔드포인트
  - DDoS 방어(Shield, Cloud Armor), Firewall

- **03_waf_ddos.md**  
  - Cloud WAF 설정(AWS WAF, GCP Cloud Armor 등)
  - Rate limiting, SQLi/XSS 필터링
  - DDoS 방어 솔루션(Shield Advanced, Cloudflare, Arbor)

### 3) `kubernetes/`
- **01_container_security.md**  
  - **Docker 보안**(이미지 스캐닝, non-root, read-only filesystem)
  - Secrets 관리(AWS Secrets Manager, Vault), CI/CD에서 이미지 검사

- **02_k8s_cluster_security.md**  
  - **Kubernetes RBAC**, PodSecurity/Admission, ETCD 암호화
  - 네트워크 정책(NetworkPolicy)으로 Pod 간 통신 제한
  - kubelet 인증, audit logs 등

- **03_service_mesh_security.md**  
  - **Istio/Linkerd**: mTLS, 트래픽 라우팅, 사이드카 보안
  - 인증/인가(Policy, PeerAuthentication), Observability
  - 분산 트레이싱, 로그, 성능 모니터링

---

## 학습 & 활용 팁

1. **백엔드 보안**(`backend/`)  
   - 먼저 웹 앱 안전성(OWASP Top 10)과 API 인증/인가, 서버 하드닝을 숙지  
   - 웹 서버/애플리케이션 레벨의 취약점 및 방어 기법을 탄탄히

2. **클라우드 보안**(`cloud/`)  
   - IAM(Identity & Access Management)로 시작해, **네트워크 설계(VPC, 보안 그룹)**, WAF/DDoS 방어 등을 순차적으로  
   - 실제 AWS/GCP/Azure 콘솔 또는 Terraform 등 IaC를 통해 실습하면 효과 극대화

3. **쿠버네티스 보안**(`kubernetes/`)  
   - Docker 컨테이너 보안을 먼저 챙기고, K8s 클러스터 보안(RBAC, NetworkPolicy, PodSecurity) → Service Mesh 보안(mTLS, Policy)로 확장  
   - 마이크로서비스 환경에서 **각 Pod/Service**가 안전하게 통신하도록 설계

4. **우선순위**  
   - "웹/API 보안을 빨리 알고 싶다"면 `backend/` 먼저,  
   - "클라우드 네트워크"나 "AWS VPC 보안"이 급하면 `cloud/` 폴더부터,  
   - "쿠버네티스 환경" 위주면 `kubernetes/` 문서로 바로 가도 무방

5. **실무 적용**  
   - 각 문서에 포함된 **코드 예시**, **CLI 명령어**, **Terraform 설정**, **YAML 스니펫** 등을 실제 프로젝트에 응용  
   - 팀 내 보안 가이드라인을 세울 때 레퍼런스로 활용 가능

---

## 독자 대상 (Who Is This For?)

- **백엔드 개발자**: 웹/REST API 보안, 인증/인가, 서버 하드닝에 관심 있는 분  
- **클라우드 엔지니어/DevOps**: AWS/GCP/Azure 보안, VPC 설계, IAM, DDoS 방어에 집중  
- **쿠버네티스 사용자**: 컨테이너/클러스터/Service Mesh 보안 심화  
- **팀/조직 보안 담당자**: 전체 인프라(백엔드+클라우드+K8s) 보안 정책 수립 시 참고

---

## 발전 방향 (Future Extensions)

1. **CI/CD & DevSecOps**  
   - 소스코드/컨테이너 이미지 취약점 스캐닝(SAST, DAST)  
   - IaC 보안(Terraform, CloudFormation) 점검, 보안 자동화

2. **Zero Trust/SASE**  
   - 네트워크 경계가 사라진 환경에서의 아이덴티티 기반 접근  
   - BeyondCorp 접근 제어 모델

3. **대규모 엔터프라이즈 보안**  
   - SOC(Security Operations Center), SIEM, IDS/IPS 운영  
   - BGP/OSPF 라우팅 보안, IX 연결 시 DDoS 방어

4. **암호화 & 키 관리**  
   - Key Management Service(KMS), Vault, HSM(Hardware Security Module)  
   - 데이터 암호화(At-rest, In-transit), SSL Cert 자동화

---

## 같이 보면 좋은 문서

- **`basic/` 디렉토리**: TCP/IP, HTTP/HTTPS, DNS 등 기초 프로토콜 지식  
- **`advanced/06_proxy.md`**: 역방향 프록시, 보안 필터링, SSL 오프로딩  
- **`advanced/07_loadbalancing.md`**: 로드 밸런서(L4/L7) + WAF 등과 연계  
- **RPC/gRPC 보안**: gRPC TLS/mTLS, Auth Interceptor

---

**좋은 학습 되세요!**  
- 이 `security/` 디렉토리의 문서들은 **"백엔드/클라우드 보안"**을 체계적으로 정리하기 위한 것입니다.  
- **초심자는 `backend/`**(웹 보안, API 인증)부터 살펴보고,  
- **클라우드 인프라** 설계가 필요하면 `cloud/` 폴더,  
- **쿠버네티스** 환경 보안을 다뤄야 한다면 `kubernetes/` 폴더 문서로 넘어가시면 됩니다.

---
