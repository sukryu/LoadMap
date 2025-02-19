# Deployment Strategies for Go Applications 🚀

이 디렉토리는 Go 애플리케이션의 배포 전략에 대해 다룹니다.  
실무에서 애플리케이션 업데이트 시 서비스 중단 없이, 또는 최소한의 영향으로 안전하게 배포하기 위한 다양한 방법(롤링 업데이트, 블루/그린, 카나리 배포 등)을 학습하고 적용하는 데 중점을 둡니다.

---

## What You'll Learn 🎯

- **배포 전략의 기본 개념**:  
  - 롤링 업데이트, 블루/그린 배포, 카나리 배포 등의 핵심 배포 모델과 각 전략의 장단점 이해

- **실무 적용 사례**:  
  - Go 애플리케이션에 배포 전략을 적용하여, 업데이트 시 다운타임을 최소화하고 장애 발생 시 빠른 롤백을 구현하는 방법

- **자동화 및 모니터링**:  
  - 배포 자동화 도구(예: Argo CD, Helm)를 활용한 전략적 배포와 모니터링, 롤백 프로세스 구현
  - 배포 후 성능 모니터링 및 알림 체계를 통한 신속한 문제 대응

- **최적의 전략 선택**:  
  - 애플리케이션 특성과 운영 환경에 따라 어떤 배포 전략이 적합한지 판단하는 방법

---

## Directory Structure 📁

```plaintext
11-scalable-system-design/
└── deployment-strategies/
    ├── blue-green/         # 블루/그린 배포 전략 관련 문서 및 예제
    ├── canary/             # 카나리 배포 전략 관련 문서 및 예제
    ├── rolling/            # 롤링 업데이트 배포 전략 관련 문서 및 예제
    ├── README.md           # 이 문서
```

- **blue-green/**:  
  - 전체 애플리케이션의 두 환경(블루/그린)을 유지하면서, 새로운 버전을 배포하고 전환하는 전략에 대해 다룹니다.
  
- **canary/**:  
  - 소수의 사용자에게 새 버전을 배포해 모니터링하고, 점진적으로 전체 사용자로 확산하는 카나리 배포 전략을 설명합니다.
  
- **rolling/**:  
  - 순차적으로 기존 인스턴스를 업데이트하면서 배포하는 롤링 업데이트 방식을 다룹니다.

---

## Deployment Strategies Overview

### 1. Rolling Update
- **개념**:  
  - 인스턴스 또는 파드 단위로 순차적으로 업데이트하여, 전체 시스템의 가용성을 유지하는 전략입니다.
  
- **장점**:  
  - 배포 중에도 기존 서비스 유지  
  - 자동 스케일링과 쉽게 연동
  
- **단점**:  
  - 업데이트 완료 전까지 새로운 버전이 완전히 적용되지 않음

### 2. Blue/Green Deployment
- **개념**:  
  - 두 개의 별도 환경(블루와 그린)을 운영하며, 새로운 버전을 한 환경에 배포 후 전환하는 전략입니다.
  
- **장점**:  
  - 완전한 롤백이 용이  
  - 새로운 버전의 안정성을 충분히 검증 가능
  
- **단점**:  
  - 두 환경을 동시에 운영해야 하므로 리소스 비용이 증가할 수 있음

### 3. Canary Deployment
- **개념**:  
  - 소수의 사용자(또는 인스턴스)에게 새로운 버전을 먼저 배포하여 모니터링한 후, 점진적으로 전체로 확산하는 방식입니다.
  
- **장점**:  
  - 초기 문제를 조기에 발견할 수 있음  
  - 점진적 배포로 리스크 최소화
  
- **단점**:  
  - 복잡한 트래픽 라우팅 및 모니터링 필요

---

## Getting Started 🚀

### 1. Prerequisites
- Kubernetes 클러스터 또는 원하는 배포 플랫폼
- 배포 자동화 도구 (Argo CD, Helm, 또는 기타 CI/CD 도구)
- 모니터링 도구 (Prometheus, Grafana 등)

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/11-scalable-system-design/deployment-strategies
```

### 3. 배포 전략 예제 실습
- **롤링 업데이트**:  
  - `rolling/` 디렉토리 내 예제 YAML 파일을 사용해, 기존 파드를 순차적으로 업데이트하며 배포합니다.
  
- **블루/그린 배포**:  
  - `blue-green/` 디렉토리 내 예제 파일을 통해, 새로운 환경을 생성하고 전환하는 과정을 실습합니다.
  
- **카나리 배포**:  
  - `canary/` 디렉토리 내 예제 파일로 소수의 사용자에게 먼저 배포한 후, 전체 배포로 확장하는 전략을 체험해 보세요.

---

## Best Practices & Tips 💡

- **모니터링 강화**:  
  - 배포 전후에 애플리케이션의 성능과 오류를 면밀히 모니터링하여, 문제가 발생하면 즉각 롤백할 수 있는 체계를 마련하세요.
  
- **자동화 도구 활용**:  
  - Argo CD, Helm 등 도구를 활용해, 배포 프로세스를 코드로 관리하고, GitOps 원칙을 준수하세요.
  
- **트래픽 라우팅**:  
  - 카나리 배포 시, 트래픽 분산(예: 서비스 메시, Ingress 컨트롤러)을 적절하게 구성하여, 새 버전이 안정적으로 작동하는지 확인하세요.
  
- **리소스 관리**:  
  - 배포 전략에 따라 두 환경(블루/그린)이나 추가 인스턴스를 운영할 때, 리소스 비용과 사용량을 철저히 관리하세요.
  
- **롤백 전략**:  
  - 모든 배포 전략에서 롤백 계획을 마련해, 문제가 발생할 경우 신속하게 이전 안정 버전으로 전환할 수 있도록 하세요.

---

## Next Steps

- **실제 프로젝트 적용**:  
  - 각 배포 전략을 실제 서비스에 적용하여, 효과와 문제점을 분석하고 개선하세요.
  
- **CI/CD 통합**:  
  - GitHub Actions, Argo CD 등을 연계하여, 자동화된 배포 파이프라인에 배포 전략을 통합하세요.
  
- **고급 전략 연구**:  
  - 트래픽 분산, A/B 테스트, 다중 클러스터 배포 등의 고급 배포 전략도 추가로 학습하세요.

---

## References 📚

- [Kubernetes Deployment Strategies](https://kubernetes.io/docs/concepts/workloads/controllers/deployment/#strategy)
- [Blue/Green Deployment Explained](https://martinfowler.com/bliki/BlueGreenDeployment.html)
- [Canary Deployment Pattern](https://martinfowler.com/bliki/CanaryRelease.html)
- [GitOps and Continuous Deployment](https://www.weave.works/technologies/gitops/)
- [Argo CD Documentation](https://argo-cd.readthedocs.io/en/stable/)

---

각 배포 전략은 애플리케이션 업데이트와 장애 복구를 위한 중요한 방법입니다.  
이 자료를 통해 Go 애플리케이션에 적합한 배포 전략을 선정하고, 실무에 적용하여 안정적이고 효율적인 서비스를 운영해 보세요! Happy Deploying! 🚀