# Argo CD: GitOps for Continuous Deployment 🚀

이 디렉토리는 Argo CD를 활용하여 Go 기반 애플리케이션의 지속적 배포(CD)를 자동화하는 방법을 다룹니다.  
GitOps 원칙에 따라 Git 리포지토리를 단일 소스의 진실(Source of Truth)으로 사용하고, 클러스터 상태를 Git과 동기화하여 자동 배포와 롤백을 구현하는 전략과 Best Practice를 학습할 수 있습니다.

---

## What You'll Learn 🎯

- **Argo CD 기본 개념**:  
  - GitOps의 원칙과 Argo CD가 제공하는 주요 기능 이해  
  - 애플리케이션 배포 상태와 Git 리포지토리 간의 동기화 방식

- **설치 및 설정**:  
  - Argo CD 설치, 초기 설정 및 CLI/웹 UI 사용법  
  - Git 리포지토리와 클러스터 간 애플리케이션 연결 방법

- **배포 및 관리**:  
  - 애플리케이션 배포, 업데이트, 롤백 및 자동 동기화 전략  
  - Helm, Kustomize 등의 템플릿 도구와 연동하여 인프라 관리

- **모니터링 및 보안**:  
  - 배포 상태 모니터링, 알림 설정 및 보안 모범 사례 적용

---

## Directory Structure 📁

```plaintext
09-ci-cd-devops/
└── argo-cd/
    ├── manifests/             # Argo CD 애플리케이션 및 설정 매니페스트 (YAML 파일)
    ├── docs/                  # Argo CD 설정 및 운영 가이드 문서
    └── README.md              # 이 문서
```

- **manifests/**:  
  - 애플리케이션 배포, 프로젝트, 리포지토리 및 클러스터 설정에 대한 YAML 파일들을 포함합니다.
- **docs/**:  
  - Argo CD 설치, 초기화, 구성 변경, 문제 해결 등에 대한 상세 문서를 포함할 수 있습니다.

---

## Getting Started 🚀

### 1. Prerequisites
- Kubernetes 클러스터 (Minikube, Kind, 또는 클라우드 기반 클러스터)
- Git 리포지토리: 애플리케이션 배포 YAML 파일이 포함된 리포지토리
- kubectl 및 Argo CD CLI 설치
  - [Argo CD CLI 설치 가이드](https://argo-cd.readthedocs.io/en/stable/cli_installation/)

### 2. Argo CD 설치
- 클러스터에 Argo CD를 설치합니다.
  ```bash
  kubectl create namespace argocd
  kubectl apply -n argocd -f https://raw.githubusercontent.com/argoproj/argo-cd/stable/manifests/install.yaml
  ```

### 3. Argo CD 접속 및 초기 설정
- Argo CD 서버의 웹 UI에 접속하거나 CLI를 사용하여 로그인합니다.
  ```bash
  # Argo CD CLI를 통한 로그인 예시
  argocd login <ARGO_CD_SERVER> --username admin --password <INITIAL_PASSWORD>
  ```
- Git 리포지토리를 Argo CD에 등록하고, 애플리케이션을 생성합니다.

### 4. 애플리케이션 배포 예제
- manifests/ 디렉토리에 있는 애플리케이션 YAML 파일을 사용해, GitOps 기반 배포를 수행합니다.
  ```bash
  # 예를 들어, 애플리케이션 생성:
  argocd app create my-go-app \
    --repo https://github.com/your-username/your-app-repo.git \
    --path deployment \
    --dest-server https://kubernetes.default.svc \
    --dest-namespace default
  ```

- 애플리케이션을 동기화하여, 클러스터에 배포합니다.
  ```bash
  argocd app sync my-go-app
  ```

---

## Example Snippet 📄

아래는 간단한 Argo CD 애플리케이션 매니페스트 예제입니다.

**manifests/my-go-app.yaml**
```yaml
apiVersion: argoproj.io/v1alpha1
kind: Application
metadata:
  name: my-go-app
  namespace: argocd
spec:
  project: default
  source:
    repoURL: 'https://github.com/your-username/your-app-repo.git'
    targetRevision: HEAD
    path: deployment
  destination:
    server: 'https://kubernetes.default.svc'
    namespace: default
  syncPolicy:
    automated:
      prune: true
      selfHeal: true
    retry:
      limit: 5
      backoff:
        duration: 5s
        factor: 2
        maxDuration: 3m
```

이 매니페스트는 Git 리포지토리의 `deployment` 경로에 있는 YAML 파일들을 사용해, `default` 네임스페이스에 애플리케이션을 배포하고, 자동 동기화 및 재시도 정책을 적용합니다.

---

## Best Practices & Tips 💡

- **자동 동기화 활용**:  
  - Argo CD의 자동 동기화 기능을 활용하여, Git 리포지토리와 클러스터 상태를 항상 일치시킵니다.
  
- **프로젝트 및 권한 관리**:  
  - 여러 애플리케이션을 관리할 때, Argo CD 프로젝트를 활용해 접근 권한 및 리소스 제한을 체계적으로 관리하세요.
  
- **Helm/Kustomize 연동**:  
  - 템플릿화된 YAML 파일 관리를 위해 Helm 차트나 Kustomize를 활용하면, 환경별 설정 관리가 용이합니다.
  
- **모니터링 및 알림 설정**:  
  - Argo CD의 상태 모니터링 기능과 외부 알림 시스템(Slack, 이메일 등)을 연계하여, 배포 실패나 이상 상태를 신속히 대응할 수 있도록 구성하세요.
  
- **GitOps 원칙 준수**:  
  - 모든 인프라 변경 사항은 Git을 통해 관리하고, 코드 리뷰 및 승인 프로세스를 통해 안정성을 확보하세요.

---

## Next Steps

- **고급 기능 학습**:  
  - Argo CD의 헬름 차트 통합, 멀티 클러스터 관리, 그리고 롤백 전략 등 고급 기능을 학습하세요.
- **CI/CD 연계**:  
  - GitHub Actions, Jenkins 등과 연계하여, Argo CD 기반 자동 배포 파이프라인을 구축해 보세요.
- **문제 해결 및 튜닝**:  
  - 대규모 애플리케이션 배포 시 발생할 수 있는 문제들을 해결하고, 성능 최적화 방안을 마련하세요.

---

## References 📚

- [Argo CD Official Documentation](https://argo-cd.readthedocs.io/en/stable/)
- [GitOps Concepts](https://www.weave.works/technologies/gitops/)
- [Helm Documentation](https://helm.sh/docs/)
- [Kustomize Documentation](https://kubectl.docs.kubernetes.io/references/kustomize/)

---

Argo CD를 활용한 GitOps 배포는 현대 클라우드 네이티브 애플리케이션의 안정적인 운영과 신속한 업데이트를 가능하게 합니다.  
이 자료를 통해 Go 기반 애플리케이션의 지속적 배포(CD)를 효과적으로 구현해 보세요! Happy GitOps! 🚀