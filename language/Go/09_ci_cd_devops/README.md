# 09 CI/CD & DevOps 🚀

이 디렉토리는 **CI/CD 및 DevOps** 전략을 통해 애플리케이션 배포와 운영 자동화를 실무에서 구현하는 방법을 다룹니다.  
GitHub Actions를 활용한 CI/CD 파이프라인 구축, ArgoCD를 통한 GitOps 배포, 그리고 Blue-Green, Canary 등 다양한 배포 전략을 실제 프로젝트에 적용하는 방법을 학습하고 활용할 수 있습니다.

---

## 디렉토리 구조 📁

```plaintext
09-ci-cd-devops/
├── github-actions/            # GitHub Actions를 활용한 CI/CD 파이프라인 예제 및 설정 파일
├── argo-cd/                   # ArgoCD를 통한 GitOps 워크플로우 및 배포 자동화 예제
└── deployment-strategies/     # Blue-Green, Canary 등 다양한 배포 전략 및 사례
```

- **github-actions/**:  
  - CI/CD 워크플로우 파일(YAML)과 함께, 빌드, 테스트, 린트, 패키징, 도커 이미지 빌드 및 배포 과정을 자동화하는 예제들을 포함합니다.
  
- **argo-cd/**:  
  - GitOps 개념에 기반해, ArgoCD를 사용하여 애플리케이션을 선언적으로 배포하는 방법과, 클러스터 상태 동기화 및 롤백 전략을 다룹니다.
  
- **deployment-strategies/**:  
  - Blue-Green 배포, Canary 배포 등 무중단 배포를 위한 전략과 실제 구현 사례를 소개하며, 서비스 안정성을 확보하는 방법을 제시합니다.

---

## 실무 활용 목표 🎯

- **자동화된 빌드 및 테스트**:  
  - GitHub Actions를 통해 소스 코드의 변경사항이 있을 때마다 자동으로 빌드, 테스트, 린트 및 패키징을 실행하여 품질을 유지합니다.
  
- **GitOps 기반 배포**:  
  - ArgoCD를 활용해 선언적 방식으로 클러스터 배포를 관리하고, Git 리포지토리와 클러스터 상태를 동기화하여 안정적인 운영 환경을 구현합니다.
  
- **무중단 배포 전략**:  
  - Blue-Green 및 Canary 배포 전략을 적용하여, 배포 중에도 서비스 가용성을 유지하고, 문제 발생 시 빠르게 롤백할 수 있도록 합니다.

---

## 실무 적용 사례 🚀

1. **GitHub Actions를 활용한 CI/CD 파이프라인 구축**  
   - 코드 커밋 시 자동으로 테스트 및 빌드가 진행되고, 도커 이미지를 생성하여 레지스트리에 푸시  
   - 린트 및 보안 스캔 도구를 통해 코드 품질을 보장
  
2. **ArgoCD를 통한 GitOps 배포**  
   - Kubernetes 클러스터에 애플리케이션을 배포하기 위해, Git 리포지토리의 선언적 설정(YAML 파일)을 자동으로 동기화  
   - 배포 상태 모니터링 및 롤백 전략을 통해 장애 상황에 빠르게 대응
  
3. **Blue-Green/Canary 배포 전략 적용**  
   - 새로운 버전의 애플리케이션을 별도의 환경에 배포한 후, 트래픽을 점진적으로 전환하여 무중단 배포를 실현  
   - 실시간 모니터링을 통해 이상 징후 발생 시 빠르게 롤백

---

## 시작하기 🚀

### 1. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/09-ci-cd-devops
```

### 2. GitHub Actions 예제 실행
- `github-actions/` 폴더 내의 워크플로우 파일(.yml)을 확인하고, CI/CD 파이프라인이 어떻게 구성되어 있는지 살펴보세요.
- GitHub 리포지토리 내에서 변경사항이 발생하면 자동으로 빌드 및 테스트가 실행되는 것을 모니터링해 보세요.

### 3. ArgoCD 예제 실행
- `argo-cd/` 폴더 내의 설정 파일과 배포 YAML 파일을 활용하여, ArgoCD를 통해 클러스터에 애플리케이션을 배포합니다.
- ArgoCD 웹 UI를 통해 클러스터 상태와 동기화 상태를 확인하세요.

### 4. 배포 전략 실습
- `deployment-strategies/` 폴더의 문서를 참고하여, Blue-Green 또는 Canary 배포 전략을 구현해 보세요.
- 실제 배포 환경에서 트래픽 전환 및 롤백 시나리오를 실습해 보며, 무중단 배포의 원리를 체험해 보세요.

---

## Best Practices & Tips 💡

- **CI/CD 파이프라인 최적화**:  
  - 병렬 빌드, 캐시 활용 및 단계별 실패 대응 전략을 적용하여 파이프라인 효율을 높이세요.
  
- **GitOps 관리**:  
  - 선언적 배포 파일을 철저히 관리하고, 클러스터 상태와 Git 리포지토리의 일관성을 유지하는 것이 중요합니다.
  
- **배포 전략 테스트**:  
  - 새로운 배포 전략을 소규모로 테스트하여, 실제 트래픽 전환 시 문제가 없는지 사전 검증하세요.
  
- **모니터링 통합**:  
  - CI/CD 및 배포 후에는 Prometheus, Grafana, Jaeger 등 모니터링 도구와 연계하여, 서비스 상태를 지속적으로 점검하세요.

---

## 참고 자료 📚

- [GitHub Actions Documentation](https://docs.github.com/en/actions)
- [ArgoCD Documentation](https://argo-cd.readthedocs.io/en/stable/)
- [Blue-Green Deployment Guide](https://martinfowler.com/bliki/BlueGreenDeployment.html)
- [Canary Deployment Explained](https://www.nginx.com/blog/canary-deployments-with-nginx-plus/)
- [GitOps Principles](https://www.weave.works/technologies/gitops/)

---

CI/CD와 DevOps는 지속적 배포와 안정적인 서비스 운영을 위한 핵심 전략입니다.  
이 자료를 통해 자동화된 파이프라인과 무중단 배포 전략을 실무에 적용하여, 효율적이고 안정적인 운영 환경을 구축해 보세요! Happy DevOps! 🚀