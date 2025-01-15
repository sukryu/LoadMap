# 클라우드 보안 (Cloud Security)

이 디렉토리는 **AWS/GCP/Azure 등 퍼블릭 클라우드** 환경에서 **인프라 보안**을 다루는 문서들을 담고 있습니다.  
**IAM**(Identity & Access Management), **네트워크 보안(VPC/서브넷/보안그룹)**, **WAF/DDoS** 등 각종 솔루션과 설정 방법을 중심으로 설명하며, 클라우드를 운용하는 엔지니어가 반드시 알아야 할 핵심을 다룹니다.

---

## 디렉토리 구성 (Files Overview)

```plaintext
cloud/
├── 01_iam.md                           # 클라우드 IAM(AWS/GCP/Azure Role/Policy)
├── 02_network_security.md              # VPC/서브넷/보안 그룹/NAT, DDoS, CloudFirewall
├── 03_waf_ddos.md                      # WAF 설정, Rate Limiting, DDoS 방어
└── README.md                           # cloud/ 폴더 개요
```


1. **`01_iam.md`**  
   - **클라우드 IAM**(AWS, GCP, Azure) 기본 개념  
   - 사용자/역할(Roles)과 정책(Policy) 설계  
   - 최소 권한 원칙(Principle of Least Privilege) 적용 사례  
   - 자격 증명(Access Key, Secret Key) 관리, MFA 설정, GitHub Action OIDC 연동 예시

2. **`02_network_security.md`**  
   - **VPC(가상 사설망) 설계**: 퍼블릭/프라이빗 Subnet, NAT 게이트웨이, Bastion Host  
   - **보안 그룹/Security Group**, **NACL**(Network ACL) 설정  
   - DDoS 방어(Shield, Cloud Armor 등), 클라우드 방화벽 활용  
   - 인터넷 게이트웨이, VPC Endpoint 구성

3. **`03_waf_ddos.md`**  
   - **WAF(Web Application Firewall)**: AWS WAF, GCP Cloud Armor, Azure WAF  
   - Rate Limiting, SQLi/XSS 필터링 등 규칙 설정  
   - **DDoS** 보호 솔루션(Shield Advanced, Cloudflare, Arbor) 및 구성 전략  
   - 로깅/알림(CloudWatch, Stackdriver)으로 공격 징후 모니터링

---

## 학습 순서 (Recommended Reading Path)

1. **`01_iam.md`**  
   - 클라우드에서 가장 기초이자 필수적인 보안 요소: **IAM**  
   - 사용자, 그룹, 역할(Role), 정책(Policy) 개념과 **Access Key** 관리  
   - MFA, STS, 임시 자격증명 등 고급 기능도 순차적으로 학습

2. **`02_network_security.md`**  
   - VPC/Subnet을 어떻게 나누고, NAT/Bastion Host를 운영하며, 보안 그룹/NACL을 세팅하는지 이해  
   - 퍼블릭 서브넷(로드밸런서 등)과 프라이빗 서브넷(DB, 내부 서비스) 분리 패턴  
   - DDoS 방어, 방화벽 정책 등 네트워크 기반 보안

3. **`03_waf_ddos.md`**  
   - **WAF**로 웹 계층(HTTP/HTTPS) 공격 방어  
   - **DDoS** 대응 솔루션과 Rate Limiting, IP 차단 목록 관리  
   - 실시간 로그 모니터링, 알림 설정으로 공격 징후 조기 발견

---

## 문서 활용 팁 (How to Use)

- **실무 시나리오별 접근**  
  - “클라우드 접근 권한을 최소화하고 싶다” → `01_iam.md`  
  - “VPC를 안전하게 설계하고 Bastion Host로 SSH 접근 통제” → `02_network_security.md`  
  - “WAF 설정, DDoS 방어가 궁금하다” → `03_waf_ddos.md`

- **공유 & 협업**  
  - 팀 내 클라우드 보안 지침을 수립할 때, 이 디렉토리 내용과 함께 **Terraform**/**CloudFormation** 예시를 참고  
  - IAM 정책, 보안 그룹 템플릿을 표준화해 버전 관리

- **상호 참조**  
  - **백엔드 보안**(`../backend/`)에서 다룬 웹/서버 하드닝과 **클라우드 보안**이 맞물릴 수 있음  
  - **쿠버네티스 보안**(`../kubernetes/`)에서의 클러스터 네트워크 정책도 VPC 설계와 연계 가능

---

## 대상 독자 (Who Is This For?)

- **클라우드 엔지니어/DevOps**:  
  - AWS/GCP/Azure 네트워킹, IAM 정책, VPC 설정, DDoS 방어가 필요한 분  
- **인프라/시스템 엔지니어**:  
  - 온프레에서 클라우드로 이전, 하이브리드 클라우드 운영  
  - NAT/Bastion, 보안 그룹/NACL, 로깅 체계 확립
- **백엔드 개발자**:  
  - RDS나 S3 등 클라우드 리소스 접근 시 필요한 IAM, 네트워크 보안 설정 이해  
  - 서버리스(Lambda, Cloud Functions) 환경의 보안 구성

---

## 다음 학습 단계 (Next Steps)

1. **클라우드 보안 심화**  
   - 멀티 클라우드 보안, 하이브리드 아키텍처 VPN/DirectConnect, 종합 DevSecOps 파이프라인  
   - CSPM(Cloud Security Posture Management) 등 자동화 검사 툴

2. **쿠버네티스 보안**(`../kubernetes/`)  
   - Docker 컨테이너 취약점 스캐닝, K8s RBAC, NetworkPolicy, PodSecurity  
   - Istio, Linkerd 같은 Service Mesh 보안

3. **서버리스 보안**  
   - Lambda, Cloud Functions, Azure Functions에서 함수 권한/환경변수 관리  
   - API Gateway + Lambda 시나리오에서 JWT 검증, WAF 연동

---

안전하고 효율적인 **클라우드 인프라**를 만들어나가세요!  
**IAM**을 통해 권한을 세밀하게 제어하고, **VPC/네트워크 보안**으로 외부 공격을 차단하며, **WAF/DDoS** 방어로 웹 레이어 공격까지 대응한다면, 클라우드 환경에서 안정적인 서비스를 운영할 수 있습니다.
