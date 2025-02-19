# 05 Cloud Native Utilization ☁️

이 디렉토리는 클라우드 네이티브 기술을 **실무에서 어떻게 활용할 수 있는지**에 초점을 맞춘 가이드입니다.  
컨테이너화, 서버리스 아키텍처, 그리고 인프라스트럭처 코드(IaC)를 활용하여 실제 서비스 환경을 구축, 배포, 운영하는 방법을 제시합니다.

---

## 디렉토리 구조 및 활용 방법 📁

```plaintext
05-cloud-native/
├── docker-kubernetes/         # Docker와 Kubernetes를 활용하여 컨테이너 기반 애플리케이션을 구축 및 운영하는 방법
├── serverless/                # 서버리스 아키텍처를 통해 비용 효율적이고 확장 가능한 애플리케이션 구축 및 이벤트 기반 처리
└── infrastructure-as-code/    # Terraform, Pulumi를 활용해 클라우드 리소스를 코드로 관리하고 자동화하는 전략
```

### docker-kubernetes/
- **목적**:  
  실제 애플리케이션을 컨테이너화하고, Kubernetes 클러스터에 배포하여 스케일링 및 운영 자동화를 구현합니다.
- **활용 방법**:  
  - Docker를 사용해 애플리케이션 이미지를 생성하고, 최적화된 멀티스테이지 빌드 전략을 적용합니다.
  - Kubernetes YAML 파일과 Helm Chart를 통해 애플리케이션을 배포하고, 롤링 업데이트, 자동 스케일링, 자원 제한 설정 등 클러스터 운영 모범 사례를 적용합니다.
  - 로컬(Minikube, Docker Desktop)과 클라우드 기반 클러스터 간의 차이점을 이해하여, 실제 서비스 환경에 맞게 클러스터를 구성합니다.

### serverless/
- **목적**:  
  서버 관리 부담 없이 함수 단위로 애플리케이션 로직을 실행하여, 이벤트 기반, 비용 효율적인 아키텍처를 구현합니다.
- **활용 방법**:  
  - AWS Lambda, Google Cloud Functions 등의 플랫폼에서 간단한 함수를 작성하고 배포하는 방법을 학습합니다.
  - API Gateway, 이벤트 소스(예: S3, DynamoDB Streams)와 연계하여 서버리스 애플리케이션을 설계합니다.
  - 서버리스 환경에서의 함수 타임아웃, 메모리 설정, 비용 최적화 전략을 실제 예제를 통해 적용해 봅니다.

### infrastructure-as-code/
- **목적**:  
  클라우드 리소스를 코드로 관리하여 재현 가능하고, 버전 관리가 용이한 인프라 환경을 구축합니다.
- **활용 방법**:  
  - Terraform과 Pulumi를 사용하여 AWS, GCP, Azure 등의 클라우드 리소스를 자동으로 프로비저닝하는 방법을 학습합니다.
  - 모듈화된 IaC 템플릿을 통해 인프라 변경 사항을 코드 리뷰와 CI/CD 파이프라인에 통합하여 운영 자동화를 구현합니다.
  - GitOps와 같은 최신 DevOps 패러다임과 연계하여, 인프라 변경 이력을 체계적으로 관리하고, 재현 가능한 환경을 구축합니다.

---

## 실무 활용 사례 🚀

1. **컨테이너 기반 배포**  
   - Docker와 Kubernetes를 사용해 마이크로서비스 아키텍처를 구현하고, 자동 스케일링 및 롤링 업데이트로 무중단 배포를 실현합니다.

2. **서버리스 애플리케이션**  
   - AWS Lambda를 통해 이벤트 기반 데이터 처리를 구현하여, 비용 효율적이고 확장 가능한 백엔드를 구축합니다.

3. **인프라 자동화**  
   - Terraform을 이용해 VPC, EC2, RDS 등 클라우드 리소스를 코드로 정의하고, GitOps를 적용해 안정적인 운영 환경을 마련합니다.

---

## 시작하기 🚀

### 1. 필수 도구 설치
- **Docker**: [Docker 설치](https://www.docker.com/)
- **Kubernetes**: Minikube 또는 Docker Desktop 내장 Kubernetes 활용
- **서버리스 플랫폼 CLI**: AWS CLI, Google Cloud SDK 등
- **Terraform / Pulumi**: [Terraform 다운로드](https://www.terraform.io/downloads.html), [Pulumi 설치](https://www.pulumi.com/docs/get-started/install/)
- **Git**: 버전 관리 도구 설치

### 2. 프로젝트 클론하기
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/05-cloud-native
```

### 3. 예제 실행 및 실습
#### a. Docker & Kubernetes 예제
```bash
cd docker-kubernetes
# Docker 이미지를 빌드하고, Kubernetes 클러스터에 배포
docker build -t my-go-app .
kubectl apply -f deployment.yaml
```

#### b. 서버리스 예제
```bash
cd ../serverless
# 예제 함수를 배포 (Serverless Framework 또는 SAM CLI 활용)
serverless deploy
```

#### c. 인프라스트럭처 코드 예제
```bash
cd ../infrastructure-as-code
terraform init
terraform apply
```

---

## Best Practices & Tips 💡

- **컨테이너와 클러스터 운영**: 리소스 요청/제한, 헬스 체크, 자동 스케일링 등 운영 모범 사례를 적용하여 클러스터 효율성을 극대화하세요.
- **서버리스 비용 관리**: 함수의 타임아웃, 메모리 설정을 최적화하여 비용과 성능의 균형을 유지하세요.
- **IaC 관리**: 인프라 변경 사항을 코드로 관리하고, CI/CD 파이프라인에 통합해 재현 가능한 환경 구축에 힘쓰세요.
- **모니터링과 로깅**: 클라우드 네이티브 환경에서는 Prometheus, Grafana 등으로 시스템 상태를 지속적으로 모니터링하여 운영 자동화에 반영하세요.

---

## 참고 자료 📚

- [Docker 공식 문서](https://docs.docker.com/)
- [Kubernetes 공식 문서](https://kubernetes.io/docs/)
- [AWS Lambda Documentation](https://docs.aws.amazon.com/lambda/)
- [Terraform 공식 문서](https://www.terraform.io/docs/)
- [Pulumi Documentation](https://www.pulumi.com/docs/)

---

클라우드 네이티브 기술을 실무에 효과적으로 활용하여, 효율적이고 확장 가능한 시스템을 구축해 보세요! Happy Cloud Coding! 🚀