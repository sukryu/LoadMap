# Docker & Kubernetes for Go Backend 🚢🔧

이 디렉토리는 **Docker**와 **Kubernetes**를 활용하여 Go 기반 애플리케이션을 컨테이너화하고, 클라우드 네이티브 환경에서 배포 및 운영하는 방법을 다룹니다.  
실제 서비스를 위한 컨테이너 이미지 생성, 로컬 클러스터 구축, 그리고 Kubernetes YAML 파일을 통한 배포 전략을 학습하고 실무에 적용할 수 있도록 구성되어 있습니다.

---

## What You'll Learn 🎯

- **Docker Fundamentals**:  
  - Docker 이미지 빌드, 컨테이너 실행, Dockerfile 작성법  
  - 멀티스테이지 빌드를 통한 경량 이미지 생성

- **Kubernetes Basics**:  
  - Kubernetes 클러스터 구성, Pod, 서비스, Deployment, ConfigMap, Secret 등의 기본 오브젝트 이해  
  - 로컬 개발 환경(Minikube, Docker Desktop)과 클라우드 기반 클러스터에서의 배포 방법

- **실무 배포 전략**:  
  - 롤링 업데이트, 무중단 배포, 자동 스케일링 등 Kubernetes의 운영 모범 사례
  - Helm Chart 또는 Kustomize를 활용한 애플리케이션 배포 자동화

---

## Directory Structure 📁

```plaintext
05-cloud-native/
└── docker-kubernetes/
    ├── Dockerfile             # 애플리케이션 Docker 이미지 빌드를 위한 설정 파일
    ├── deployment.yaml        # Kubernetes Deployment 예제 파일
    ├── service.yaml           # Kubernetes Service 예제 파일
    ├── ingress.yaml           # (선택 사항) Ingress 설정 예제 파일
    ├── helm/                  # (선택 사항) Helm Chart 템플릿 및 값 파일
    └── README.md              # 이 문서
```

- **Dockerfile**:  
  - Go 애플리케이션을 컨테이너 이미지로 빌드하는 방법을 설명합니다.
- **deployment.yaml, service.yaml, ingress.yaml**:  
  - Kubernetes 오브젝트를 사용하여 컨테이너화된 애플리케이션을 클러스터에 배포하는 예제입니다.
- **helm/**:  
  - Helm Chart를 이용하여 배포 자동화를 구현하는 방법을 포함할 수 있습니다.

---

## Getting Started 🚀

### 1. 필수 도구 설치
- **Docker**: [Docker 설치 가이드](https://docs.docker.com/get-docker/)
- **Kubernetes 클러스터**:  
  - 로컬 개발 환경: Minikube, Docker Desktop 내장 Kubernetes, Kind  
  - 클라우드 환경: GKE, EKS, AKS 등
- **kubectl**: [kubectl 설치](https://kubernetes.io/docs/tasks/tools/)
- (선택 사항) **Helm**: [Helm 설치](https://helm.sh/docs/intro/install/)

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
  - 브라우저에서 `http://localhost:8080`을 통해 애플리케이션이 정상 동작하는지 확인하세요.

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
  kubectl get pods,svc,ingress
  ```

---

## Example: Dockerfile

아래는 Go 애플리케이션을 위한 멀티스테이지 Dockerfile 예제입니다:
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

---

## Example: Kubernetes Deployment & Service

### deployment.yaml
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

### service.yaml
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

이 예제는 3개의 복제본으로 구성된 Deployment와 외부 접근을 위한 LoadBalancer 타입의 Service를 정의합니다.

---

## Best Practices & Tips 💡

- **멀티스테이지 빌드**:  
  - Dockerfile에서 빌드와 실행 환경을 분리하여 경량 이미지를 생성하세요.
  
- **자원 요청 및 제한 설정**:  
  - Kubernetes 오브젝트에서 CPU와 메모리의 요청/제한을 명확히 지정하여, 안정적인 클러스터 운영을 도모하세요.
  
- **롤링 업데이트**:  
  - Deployment의 업데이트 전략을 활용하여, 무중단 배포를 구현하세요.
  
- **Helm 사용 고려**:  
  - 복잡한 애플리케이션 배포를 위해 Helm Chart를 사용하면, 환경별 설정을 쉽게 관리할 수 있습니다.
  
- **모니터링 연계**:  
  - 배포 후 Prometheus, Grafana 등의 모니터링 도구와 연계하여, 서비스 상태를 지속적으로 점검하세요.

---

## References 📚

- [Docker Official Documentation](https://docs.docker.com/)
- [Kubernetes Official Documentation](https://kubernetes.io/docs/)
- [Helm Documentation](https://helm.sh/docs/)
- [Kubernetes Best Practices](https://kubernetes.io/docs/concepts/cluster-administration/manage-deployment/)
- [Go Docker Best Practices](https://www.ardanlabs.com/blog/2018/06/containerized-go.html)

---

Docker와 Kubernetes를 활용한 컨테이너화 및 클러스터 배포는 현대 클라우드 네이티브 애플리케이션의 핵심입니다.  
이 자료를 통해 효율적이고 안정적인 배포 파이프라인을 구축해 보세요! Happy Container Coding! 🚢🔧