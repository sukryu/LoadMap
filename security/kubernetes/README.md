# 쿠버네티스 보안 (Kubernetes Security)

이 디렉토리는 **Kubernetes(쿠버네티스) 환경에서** 보안을 다루는 문서들을 모아 놓았습니다.  
**Docker 컨테이너 보안**부터 시작해, **K8s 클러스터 레벨의 RBAC/네트워크 정책**, 그리고 **Service Mesh(mTLS, Policy 등)**까지,  
마이크로서비스 아키텍처를 안전하게 운영하기 위한 핵심 주제들을 정리합니다.

---

## 디렉토리 구성 (Files Overview)

```plaintext
kubernetes/
├── 01_container_security.md            # Docker 컨테이너 보안(이미지 스캐닝, non-root 등)
├── 02_k8s_cluster_security.md          # K8s RBAC, NetworkPolicy, PodSecurity, ETCD암호화
├── 03_service_mesh_security.md         # Istio/Linkerd mTLS, 사이드카 보안, 정책
└── README.md          
```


1. **`01_container_security.md`**  
   - **Docker 컨테이너 보안** 개념: 이미지 취약점 스캐닝, `USER` non-root, read-only filesystem 등  
   - **CI/CD 파이프라인**에서 이미지 검사(Snyk, Trivy, Clair)  
   - Secrets & 환경변수 관리(민감 정보 노출 방지), Docker runtime 권한 제한(AppArmor, SELinux)

2. **`02_k8s_cluster_security.md`**  
   - **Kubernetes RBAC(Role-Based Access Control)**: 사용자/ServiceAccount/ClusterRole 바인딩  
   - **NetworkPolicy**: Pod 간 통신 제한, microsegmentation  
   - **PodSecurity**(Admission Controller, PodSecurity Standard), ETCD 암호화, kubelet 인증  
   - 클러스터 노드 하드닝, Sysctl 제한, audit logs 모니터링

3. **`03_service_mesh_security.md`**  
   - **Service Mesh**(Istio, Linkerd) 보안을 중점적으로 설명  
   - mTLS(양방향 TLS)로 Pod 간 암호화, Peer Authentication, AuthorizationPolicy 설정  
   - 사이드카 프록시(Envoy 등) 기반 트래픽 라우팅, 보안 정책, Observability(분산 트레이싱, 로깅)

---

## 학습 순서 (Recommended Reading Path)

1. **`01_container_security.md`**  
   - **Docker 컨테이너 보안** 기초를 탄탄히 잡아야, K8s 환경에서도 안전한 이미지를 배포 가능  
   - 이미지 스캐닝, non-root 실행, Secret 관리 등 **기초 안전망** 구축

2. **`02_k8s_cluster_security.md`**  
   - 클러스터 레벨 보안: **RBAC**, **네트워크 정책**, **PodSecurity**  
   - 쿠버네티스 API 접근 제어, ETCD 보호(암호화), kubelet 인증 등 **운영 레벨** 보안 기법  
   - 노드 하드닝, 모니터링(Logs, Audit)으로 쿠버네티스 전반을 관리

3. **`03_service_mesh_security.md`**  
   - 마이크로서비스 확장 시 **Service Mesh** 사용으로 **mTLS**, **보안 정책**, **트래픽 관찰** 등 고급 기능  
   - Istio/Linkerd 예시로 배포 패턴, 정책 설정, Observability 등을 체득  
   - Pod 간 암호화·인증/인가로 **Zero Trust**에 가까운 내부 네트워크 구축

---

## 문서 활용 팁 (How to Use)

- **실무 시나리오별 접근**  
  - "Docker 이미지부터 안전하게 만들고 싶다" → `01_container_security.md`  
  - "K8s 클러스터 RBAC/네트워크 정책" → `02_k8s_cluster_security.md`  
  - "Istio로 mTLS 적용, 사이드카 보안" → `03_service_mesh_security.md`

- **학습 순서**  
  - 보통 **컨테이너(Docker)** 보안 → **쿠버네티스 클러스터** 전반 → **Service Mesh** 순으로 익히면 자연스러움  
  - 필요에 따라 Mesh부터 먼저 살펴봐도 무방

- **상호 참조**  
  - **Cloud 보안**(`../cloud/`)에서 VPC, 서브넷, IAM 등을 이미 설정하고, 그 위에 K8s 클러스터가 동작  
  - **Backend 보안**(`../backend/`) 문서에서 다룬 API 인증/인가, OWASP 취약점도 쿠버네티스 위 컨테이너에 그대로 적용 가능

---

## 대상 독자 (Who Is This For?)

- **클라우드 네이티브 개발자/DevOps**  
  - 컨테이너 기반 배포를 안전하게 운영하고자 하는 분  
- **플랫폼/인프라 엔지니어**  
  - K8s 클러스터 운영 시 RBAC, PodSecurityPolicy(또는 Pod Security Admission) 등 모범 사례를 찾는 분  
- **보안 담당자**  
  - Docker/K8s 환경에서 발생 가능한 취약점을 미리 파악하고 방어 대책을 세우는 분  
- **마이크로서비스 아키텍처**  
  - Istio/Linkerd 등 Service Mesh 보안, mTLS, 정책 설정으로 내부 트래픽을 보호하고 싶은 분

---

## 다음 학습 단계 (Next Steps)

1. **CI/CD & DevSecOps**  
   - 컨테이너 빌드 파이프라인에서 이미지 검사 + 보안 스캐닝 자동화  
   - Kubernetes 배포 전 Helm 차트/Manifest 보안 검사(Terraform, OPA Gatekeeper)

2. **멀티 클러스터/하이브리드**  
   - 여러 클러스터 간 보안 정책 공유, Vault 통합, Mesh 페더레이션  
   - 클라우드 간 Pod Networking, Ingress를 글로벌하게 운영

3. **고급 운영(Zero Trust)**  
   - Pod 간 mTLS + Istio Policy로 세밀한 접근 제어  
   - Secret Rotation, Identity Management(Spiffe/SPIRE)  
   - 쿠버네티스 위 Stateful Services, Data Encryption(ETCD, PV)

---

안전하고 안정적인 쿠버네티스 운영을 위해, **컨테이너 보안 → K8s 클러스터 보안 → Service Mesh 보안**의 단계를 차근차근 살펴보세요.  
민감 정보를 안전하게 관리하고, 네트워크 정책을 잘 설정한다면, 쿠버네티스 환경에서도 **기업 수준**의 보안을 달성할 수 있습니다.
