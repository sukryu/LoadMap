# 백엔드 + 클라우드 엔지니어 관점에서의 보안

1. 백엔드/클라우드 엔지니어에게 필요한 보안 핵심
    1. 웹 애플리케이션 보안 (OWASP Top 10)
        * 주요 취약점:
            - SQL Injection, XSS, CSRF, 인젝션(Injection) 전반, 취약한 인증/세션 관리, 민감 정보 노출 등

        * 실무 예시:
            - 데이터베이스 접근 시 PreparedStatement(파라미터 바인딩) 사용
            - 템플릿 렌더링 시 XSS 방지(escaping) 처리
            - 쿠키 설정 시 `HttpOnly`, `Secure` 옵션, CSRF 토큰 적용


    2. API 인증/인가
        * 인증(Authentication)
            - 세션 기반 인증 / 토큰 기반 인증(JWT, OAuth2)
            - 주의할 점: 토큰 저장 위치(쿠키 vs 로컬 스토리지), 토큰 탈취 위험, 토큰 만료 처리

        * 인가(Autorization)
            - RBAC(Role-Based Access Control), ABAC(Attribute-Based Access Control) 등
            - API Gateway 혹은 백엔드 레벨에서 사용자 권한 검증 로직

        * 실무 팁:
            - 만료 시간이 짧은 Access Token + 갱신용 Refresh Token 조합 사용
            - JWT 서명(HS256, RS256) 시 비밀키/개인키 안전 관리

    3. 서버/시스템 보안
        * 서버 구성 시 주의사항
            - 운영체제(리눅스) 사용자/권한 분리: `root` 최소 사용, 일반 계정 + `sudo` 구성
            - SSH 접근 보안: 비밀번호 인증 지양, SSH 키 인증, Fail2ban 등으로 브루트포스 차단
            - 패키지 업데이트/보안 패치 주기적 적용

        * 환경변수/설정 파일 보안
            - `.env`나 설정 파일에 평문 비밀번호/API Key 노출 금지
            - 비밀 관리 솔루션(AWS Secrets Manager, HashiCorp Vault) 도입 고려

        * 로깅/모니터링
            - 액세스 로그(이상 HTTP 요청, 에러 발생 내역) 주기적 분석
            - OS 보안 로그(로그인 시도, sudo 사용 이력) 모니터링
            - 자동 알림(Alert) 설정: 과도한 로그인 실패, 디스크/CPU/메모리 급격한 사용 증가 등

2. 클라우드 인프라 보안
    1. 클라우드 IAM(Identity And Access Management)
        * AWS IAM, GCP IAM
            - 사용자/역할(Role)/정책(Policy) 개념
            - 최소 권한 원칙(Principle of Least Privilege): 필요한 권한만 부여
            - 자격 증명(Access Key, Secret Key)은 절대 코드 저장소에 노출 금지

        * 예시:
            - AWS에서 특정 S3 버킷에만 읽기 권한이 필요한 EC2 인스턴스 -> Instance Role 할당 + 정밀한 Policy 설정
            - Github Action나 Jenkins 연동 시, OIDC (OpenID Connect)나 임시 자격 증명 사용

    2. 네트워크 설계와 보안
        * VPC(가상 사설망), 서브넷 분리
            - 퍼플릭 서브넷(인터넷에 직접 노출) vs 프라이빗 서브넷(DB나 내부 서비스) 분리
            - NAT 게이트웨이, Bastion Host를 통해 외부 접근 통제

        * 보안 그룹 / 방화벽
            - 최소한의 인/아웃바운드 트래픽만 허용
            - SSH, RDP, DB 포트 등 외부 노출 최소화, 특정 IP만 접근 가능하도록 제한

        * Cloud WAF / DDoS 방어
            - AWS WAF, CloudFront, GCP Cloud Armor 등으로 웹 레이어 보호
            - DDoS 감지/방어 솔루션(AWS Shield 등) 고려

    3. 클라우드 서비스별 보안 모범 사례
        - AWS S3: 버킷 공개 설정 주의, Public ACL 사용 지양, 버킷 정책으로 접근 제어, 서버사이드 암호화 활성화
        - AWS RDS: VPC 내에서만 접근되도록 설정, SSL/TLS 연결 사용, DB 계정 분리(읽기/쓰기/관리)
        - AWS EC2: Key Pair 관리 철저, 해당 키(.pem) 권한 설정, EC2 Metadata 노출 위험 방지
        - GCP: GKE나 Compute Engine에서도 마찬가지로 IAM Roles, VPC Service Control, Secret Manager, Cloud Armor 활용

3. 쿠버네티스 보안
    1. Docker 보안
        * 컨테이너 이미지 취약점 스캐닝
            - Snyk, Trivy, Clair 등 툴 사용
            - 베이스 이미지로 Alpine, Distroless 등 경량 이미지 사용 -> 공격 표면 축소

        * 최소 권한 실행
            - Dockerfile에서 `USER` 지시자를 통해 non-root 실행
            - `CAP_DROP`, `read-only` 루트 파일 시스템, AppArmor/SELinux 프로필 설정

        * Secrets 관리
            - Docker 환경변수에 민감정보 직접 넣지 말고, Vault나 AWS Secrets Manager 등 연동

    2. Kubernetes 클러스터 보안
        * RBAC(Role-Based Access Control)
            - K8s 리소스 접근을 역할/권한 바인딩으로 제한
            - 불필요한 ClusterAdmin 권한 사용 지양

        * 네트워크 정책(Kubernetes NetworkPolicy)
            - Pod 간 통신 규칙 정의, "Pod A는 Pod B에만 접근 가능, 나머지는 차단" 등 미세 설정
            - CNI 플러그인(Calico, Weave 등)과 연계해 마이크로세그멘테이션 실현

        * PodSecurity / Admission
            - Pod가 root 권한 사용 금지, 특정 레이블 필수화, 불륨 마운트 제한 등 정책 적용
            - Pod Security Admission(PSA) 또는 Getekeeper(OPA) 등을 이용한 정책 엔진

        * ETCD 암호화
            - ETCD 안에 모든 클러스터 상태 정보(Pod spec, Secret 등) 저장 -> at-rest 암호화 설정
            - ETCD 접근 통제(보안 그룹, 방화벽)도 필수

3. CI/CD 및 DevSecOps
    1. 코드/이미지 취약점 스캐닝
        * SAST(Static Application Security Testing)
            - SonarQube, Checkmarx 등으로 정적 분석, SQL Injection 등 코드 레벨 취약점 검사
        
        * Dependency Scanning
            - npm, pip, Maven 등 의존성 라이브러리의 CVE 체크
            - Github Dependbot, Snyk 등을 CI 파이프라인에 연동

        * Container 이미지 스캐닝
            - 빌드 후 도커 이미지에 포함된 패키지의 취약점 여부를 자동 검사 (Trivy, Anchore 등)

    2. 인프라스트럭처 코드(IaC) 보안
        * Terraform, CloudFormation 보안 검사
            - tfsec, checkov, Terrascan 등으로 구성을 사전에 점검 (예: S3 공개 설정 여부, 불필요한 포트 오픈 등)

        * 파이프라인 시크릿 관리
            - CI 환경에서 환경변수/시크릿 안전 보관 (Github Actions의 Secret, Jenkins, Credentials 등)
            - External Vault 연동 가능 고려

    3. 배포 파이프라인 무결성
        * 서명/검증
            - 컨테이너 이미지 서명(Cosign, Notary V2) -> 배포 시 검증
            - 파이프라인 자체가 중간에 변조되지 않도록, GitOps 방식(ArgoCD, Flux) + 암호화된 Git 리포지토리

        * 릴리즈 권한과 승인
            - 프로덕션 배포 전, 2인 승인 정책(Peer Review, Pull Request Review)
            - 롤백(rollback) 시 자동화된 승인 절차차