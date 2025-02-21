다음은 지금까지 제공해 주신 파일들과 대화 내용을 기반으로 업데이트한 README.md 예시입니다.

---

# Docker & Kubernetes for Go Backend 🚢🔧

이 디렉토리는 **Docker**와 **Kubernetes**를 활용하여 Go 기반 애플리케이션을 컨테이너화하고, 클라우드 네이티브 환경에서 배포 및 운영하는 방법을 다룹니다.  
실제 서비스를 위한 컨테이너 이미지 생성, 로컬 클러스터 구축, 그리고 다양한 Kubernetes 오브젝트와 Helm 차트를 통한 배포 전략을 학습하고 실무에 적용할 수 있도록 구성되어 있습니다.

---

## What You'll Learn 🎯

- **Docker Fundamentals**  
  - Docker 이미지 빌드, 컨테이너 실행, Dockerfile 작성법  
  - 멀티스테이지 빌드를 통한 경량 이미지 생성 및 보안 강화

- **Kubernetes Basics**  
  - Kubernetes 클러스터 구성, Pod, Deployment, Service, ConfigMap, Secret, Ingress 등의 기본 오브젝트 이해  
  - 로컬 개발 환경(Minikube, Docker Desktop, Kind)과 클라우드 기반 클러스터(GKE, EKS, AKS 등)에서의 배포 방법

- **실무 배포 전략**  
  - 롤링 업데이트, 무중단 배포, 자동 스케일링(HPA) 등 Kubernetes의 운영 모범 사례  
  - RBAC, 서비스 어카운트, 볼륨 마운트 등 보안 및 리소스 관리 방안

- **Helm Chart를 활용한 배포 자동화**  
  - Helm Chart 구성 파일(Chart.yaml, values.yaml, 템플릿 파일들)의 역할과 사용법  
  - 환경별 구성 오버라이드 및 CI/CD 파이프라인 통합

- **클라우드 네이티브 활용 사례**  
  - Docker 및 Kubernetes를 통한 컨테이너화와 클러스터 운영 전략  
  - Helm 및 Ingress를 활용한 외부 접근성 구성  
  - 프로메테우스 모니터링, 로그 수집, 서버리스 및 IaC와 연계한 배포 자동화

---

## Directory Structure 📁

```plaintext
05-cloud-native/
└── docker-kubernetes/
    ├── Dockerfile             # 멀티스테이지 빌드를 통한 Go 애플리케이션 Docker 이미지 생성 설정 파일
    ├── deployment.yaml        # Kubernetes Deployment 템플릿 (Pod, 컨테이너, 프로브, 리소스 등 상세 구성)
    ├── service.yaml           # Kubernetes Service 템플릿 (LoadBalancer, ClusterIP 등)
    ├── ingress.yaml           # (선택 사항) Ingress 템플릿 (외부 트래픽 라우팅, TLS 종료 등)
    ├── helm/                  # Helm Chart 디렉토리
    │   ├── Chart.yaml         # 차트 메타데이터 (이름, 버전, 의존성 등)
    │   ├── README.md          # Helm 차트 사용 및 구성 안내서
    │   ├── values.yaml        # 기본 구성 값 (이미지, 리소스, 환경 변수, HPA, Ingress, DB, 캐시 등)
    │   └── templates/         # Kubernetes 리소스 템플릿 (Deployment, Service, Ingress, ConfigMap, Secret, ServiceAccount, HPA, _helpers.tpl 등)
    │       ├── deployment.yaml
    │       ├── service.yaml
    │       ├── ingress.yaml
    │       ├── configmap.yaml
    │       ├── secret.yaml
    │       ├── serviceaccount.yaml
    │       ├── hpa.yaml
    │       └── _helpers.tpl
    ├── .helmignore            # Helm 패키징 시 제외할 파일 및 디렉토리 목록
    └── NOTES.txt              # 설치 후 사용자 안내 메시지 (접근 방법, 리소스 상태 확인, HPA, 로그 확인 등)
```

---

## Getting Started 🚀

### 1. 필수 도구 설치
- **Docker**: [Docker 설치 가이드](https://docs.docker.com/get-docker/)
- **Kubernetes 클러스터**:  
  - 로컬 개발 환경: Minikube, Docker Desktop 내장 Kubernetes, Kind  
  - 클라우드 환경: GKE, EKS, AKS 등
- **kubectl**: [kubectl 설치](https://kubernetes.io/docs/tasks/tools/)
- **Helm**: [Helm 설치](https://helm.sh/docs/intro/install/)

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/05-cloud-native/docker-kubernetes
```

### 3. Docker 이미지 빌드 및 컨테이너 실행
- **Docker 이미지 빌드**
  ```bash
  docker build -t my-go-app .
  ```
- **로컬 컨테이너 실행**
  ```bash
  docker run -d -p 8080:8080 my-go-app
  ```
  - 브라우저에서 `http://localhost:8080`을 통해 애플리케이션이 정상 동작하는지 확인합니다.

### 4. Kubernetes 클러스터에 배포
- **Deployment 생성**
  ```bash
  kubectl apply -f deployment.yaml
  ```
- **Service 생성**
  ```bash
  kubectl apply -f service.yaml
  ```
- (선택 사항) **Ingress 생성**
  ```bash
  kubectl apply -f ingress.yaml
  ```

- **상태 확인**
  ```bash
  kubectl get pods,svc,ingress -n <네임스페이스>
  ```

### 5. Helm Chart를 활용한 배포 (선택 사항)
Helm 차트를 사용하면 환경별로 설정을 쉽게 오버라이드하여 배포할 수 있습니다.
- 기본 설치
  ```bash
  helm install my-api ./helm
  ```
- 사용자 정의 값 파일 사용
  ```bash
  helm install my-api ./helm -f values-production.yaml
  ```
- 업그레이드
  ```bash
  helm upgrade my-api ./helm -f values-production.yaml
  ```
- 테스트 후 삭제
  ```bash
  helm uninstall my-api
  ```

---

## Example Files

### Dockerfile
```dockerfile
# Build stage
FROM golang:1.20-alpine AS builder
WORKDIR /app
COPY go.mod go.sum ./
RUN go mod download
COPY . .
RUN CGO_ENABLED=0 go build -o my-go-app .

# Final stage
FROM alpine:latest
RUN apk --no-cache add ca-certificates
WORKDIR /root/
COPY --from=builder /app/my-go-app .
EXPOSE 8080
CMD ["./my-go-app"]
```

### Kubernetes Deployment & Service

#### deployment.yaml
```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: my-go-app-deployment
  labels:
    app: my-go-app
spec:
  replicas: 3
  selector:
    matchLabels:
      app: my-go-app
  template:
    metadata:
      labels:
        app: my-go-app
    spec:
      containers:
      - name: my-go-app
        image: my-go-app:latest
        ports:
        - containerPort: 8080
        resources:
          requests:
            memory: "128Mi"
            cpu: "250m"
          limits:
            memory: "256Mi"
            cpu: "500m"
```

#### service.yaml
```yaml
apiVersion: v1
kind: Service
metadata:
  name: my-go-app-service
spec:
  selector:
    app: my-go-app
  ports:
    - protocol: TCP
      port: 80
      targetPort: 8080
  type: LoadBalancer
```

---

## Best Practices & Tips 💡

- **멀티스테이지 빌드**:  
  - Dockerfile에서 빌드와 실행 환경을 분리하여 최종 이미지 크기를 최소화하고 보안을 강화하세요.
  
- **리소스 요청/제한 설정**:  
  - Deployment, Service, HPA 등 Kubernetes 오브젝트에서 CPU와 메모리 요청/제한을 명확히 설정하여 안정적인 클러스터 운영을 도모하세요.
  
- **롤링 업데이트 & 무중단 배포**:  
  - Deployment의 롤링 업데이트 전략을 활용하여 업데이트 중에도 서비스 가용성을 유지하세요.
  
- **Helm 차트 활용**:  
  - Helm을 사용하면 환경별 설정 오버라이드, 템플릿 재사용, CI/CD 파이프라인 통합 등이 용이합니다.
  
- **모니터링 및 로깅 연계**:  
  - 배포 후 Prometheus, Grafana, EFK 스택 등과 연계하여 애플리케이션의 상태와 로그를 지속적으로 모니터링하세요.
  
- **보안 강화**:  
  - RBAC, 서비스 어카운트, Secret, ConfigMap, Ingress TLS 설정 등 보안 관련 설정을 꼼꼼히 구성하세요.

---

## References 📚

- [Docker Official Documentation](https://docs.docker.com/)
- [Kubernetes Official Documentation](https://kubernetes.io/docs/)
- [Helm Documentation](https://helm.sh/docs/)
- [Kubernetes Best Practices](https://kubernetes.io/docs/concepts/cluster-administration/manage-deployment/)
- [Go Docker Best Practices](https://www.ardanlabs.com/blog/2018/06/containerized-go.html)

---

Docker와 Kubernetes, 그리고 Helm을 활용한 컨테이너화 및 클러스터 배포는 현대 클라우드 네이티브 애플리케이션 운영의 핵심입니다.  
이 자료를 통해 효율적이고 안정적인 배포 파이프라인을 구축하고, 다양한 환경에 맞게 애플리케이션을 최적화해 보세요!

Happy Container Coding! 🚢🔧