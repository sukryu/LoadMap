# 🦀 Rust의 컨테이너화 및 Kubernetes 배포

## 📌 개요
Rust 애플리케이션을 **Docker 컨테이너로 패키징하고 Kubernetes(K8s)에 배포**하면 **확장성, 이식성, 관리 효율성**이 향상됩니다.

이 장에서는 **Rust 애플리케이션의 Docker 컨테이너화 및 Kubernetes 배포** 방법을 학습하겠습니다.

---

## 🚀 Rust 애플리케이션 컨테이너화

### 🏗️ Dockerfile 작성
```dockerfile
# 1. Rust 빌드 이미지
FROM rust:1.73 as builder
WORKDIR /app
COPY . .
RUN cargo build --release

# 2. 런타임 환경 설정
FROM debian:bullseye-slim
WORKDIR /app
COPY --from=builder /app/target/release/my_app /app/
CMD ["/app/my_app"]
```
📌 `FROM rust:1.73 as builder` → Rust 공식 이미지 사용하여 빌드

📌 `cargo build --release` → 최적화된 실행 파일 생성

📌 `FROM debian:bullseye-slim` → 경량 런타임 환경 구성

📌 `COPY --from=builder` → 빌드된 실행 파일만 복사하여 이미지 크기 최소화

---

### 🏷️ Docker 이미지 빌드 및 실행
```sh
docker build -t rust-app .
docker run -p 8080:8080 rust-app
```
📌 `docker build -t rust-app .` → 이미지 빌드

📌 `docker run -p 8080:8080 rust-app` → 컨테이너 실행 및 포트 매핑

---

## 🔄 Docker Compose를 활용한 관리
`docker-compose`를 사용하면 여러 컨테이너를 효율적으로 관리할 수 있습니다.

### 🏗️ `docker-compose.yml` 작성
```yaml
version: '3.8'
services:
  rust-app:
    build: .
    ports:
      - "8080:8080"
    depends_on:
      - postgres
  postgres:
    image: postgres:15
    environment:
      POSTGRES_USER: user
      POSTGRES_PASSWORD: password
      POSTGRES_DB: rust_db
    ports:
      - "5432:5432"
```
📌 `depends_on` → Rust 애플리케이션이 PostgreSQL 컨테이너 이후 실행됨

📌 `environment` → PostgreSQL 환경 변수 설정

📌 `ports` → 외부 접근을 위한 포트 매핑

---

### 🏷️ 컨테이너 실행
```sh
docker-compose up -d
```
📌 `docker-compose up -d` → 백그라운드에서 컨테이너 실행

📌 `docker-compose down` → 컨테이너 중지 및 삭제

---

## 🚀 Kubernetes 배포

### 🏗️ Kubernetes 매니페스트 파일 작성

#### `deployment.yaml`
```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: rust-app
spec:
  replicas: 3
  selector:
    matchLabels:
      app: rust-app
  template:
    metadata:
      labels:
        app: rust-app
    spec:
      containers:
      - name: rust-app
        image: rust-app:latest
        ports:
        - containerPort: 8080
```
📌 `replicas: 3` → 3개의 인스턴스로 확장 배포

📌 `matchLabels` → `rust-app` 레이블을 가진 모든 Pod 선택

📌 `containerPort: 8080` → 컨테이너 내부 서비스 포트 지정

---

#### `service.yaml`
```yaml
apiVersion: v1
kind: Service
metadata:
  name: rust-app-service
spec:
  selector:
    app: rust-app
  ports:
  - protocol: TCP
    port: 80
    targetPort: 8080
  type: LoadBalancer
```
📌 `selector: app: rust-app` → `rust-app` 레이블을 가진 Pod와 연결

📌 `type: LoadBalancer` → 외부에서 접근 가능하도록 서비스 노출

---

### 🏷️ Kubernetes 배포 실행
```sh
kubectl apply -f deployment.yaml
kubectl apply -f service.yaml
```
📌 `kubectl apply -f` → Kubernetes에 매니페스트 적용

📌 `kubectl get pods` → 실행 중인 Pod 목록 확인

📌 `kubectl get services` → 서비스 URL 확인

---

## 🔄 지속적인 배포(CI/CD) 설정
Rust 애플리케이션을 **GitHub Actions와 Kubernetes**를 이용해 자동 배포할 수 있습니다.

### 🏗️ GitHub Actions 설정 (`.github/workflows/deploy.yml`)
```yaml
name: Deploy Rust App
on:
  push:
    branches:
      - main
jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - uses: actions-rs/toolchain@v1
        with:
          toolchain: stable
      - name: Build Docker Image
        run: docker build -t my-dockerhub/rust-app .
      - name: Push to Docker Hub
        run: |
          echo "${{ secrets.DOCKER_PASSWORD }}" | docker login -u "${{ secrets.DOCKER_USERNAME }}" --password-stdin
          docker push my-dockerhub/rust-app
      - name: Deploy to Kubernetes
        run: |
          kubectl apply -f deployment.yaml
          kubectl apply -f service.yaml
```
📌 `docker build -t my-dockerhub/rust-app .` → Docker 이미지 빌드

📌 `docker push my-dockerhub/rust-app` → Docker Hub에 푸시

📌 `kubectl apply -f deployment.yaml` → Kubernetes 클러스터에 배포

---

## 🎯 마무리
이 장에서는 **Rust 애플리케이션의 컨테이너화 및 Kubernetes 배포**를 배웠습니다.

- `Docker`를 활용한 **Rust 애플리케이션 컨테이너화**
- `docker-compose`를 이용한 **데이터베이스 및 애플리케이션 관리**
- `Kubernetes`를 이용한 **확장 가능한 Rust 애플리케이션 배포**
- `GitHub Actions` 기반 **CI/CD 파이프라인 구축**

다음 장에서는 **Rust의 시스템 설계 및 대규모 애플리케이션 개발 기법**을 배워보겠습니다! 🚀