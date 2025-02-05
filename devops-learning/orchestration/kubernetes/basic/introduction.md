# Kubernetes 개요 및 기본 개념

> **목표:**  
> - Kubernetes의 핵심 개념과 작동 방식을 이해한다.
> - 기본적인 구성 요소와 아키텍처를 파악한다.
> - Kubernetes가 어떻게 컨테이너를 관리하는지 이해한다.
> - Kubernetes를 실제 프로젝트에 적용할 수 있는 기초를 다진다.

---

## 1. Kubernetes란?

### 정의
Kubernetes(쿠버네티스)는 컨테이너화된 애플리케이션을 자동으로 배포, 확장, 관리하는 오픈소스 플랫폼입니다. 컨테이너 오케스트레이션 도구로, 수많은 컨테이너를 효율적으로 관리할 수 있게 해줍니다.

### 왜 필요한가?
- **자동화된 운영:** 수동으로 관리하기 어려운 많은 컨테이너들을 자동으로 관리합니다.
- **확장성:** 트래픽 증가에 따라 자동으로 애플리케이션을 확장할 수 있습니다.
- **안정성:** 장애가 발생한 컨테이너를 자동으로 감지하고 복구합니다.
- **효율성:** 여러 서버의 자원을 효율적으로 활용할 수 있습니다.

---

## 2. 핵심 구성 요소

### 2.1 마스터 노드 (Control Plane)
마스터 노드는 Kubernetes 클러스터의 두뇌 역할을 합니다. 다음과 같은 구성 요소들이 포함됩니다:

- **API 서버:** 모든 구성 요소들 간의 통신을 관리하는 중심점
- **스케줄러:** 새로운 파드를 어떤 노드에 배치할지 결정
- **컨트롤러 매니저:** 다양한 컨트롤러들을 실행하고 관리
- **etcd:** 클러스터의 모든 설정과 상태 정보를 저장하는 데이터베이스

### 2.2 워커 노드 (Worker Node)
실제로 컨테이너가 실행되는 서버입니다. 각 워커 노드에는 다음 구성 요소들이 있습니다:

- **Kubelet:** 노드의 컨테이너들을 관리하는 에이전트
- **Container Runtime:** 컨테이너를 실행하는 소프트웨어 (예: Docker)
- **kube-proxy:** 네트워크 규칙을 관리하고 통신을 가능하게 함

---

## 3. 기본 오브젝트

### 3.1 파드 (Pod)
- Kubernetes에서 가장 작은 배포 단위
- 하나 이상의 컨테이너를 포함
- 같은 파드 내의 컨테이너들은 네트워크와 저장소를 공유

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: my-application
spec:
  containers:
  - name: my-app
    image: nginx:latest
    ports:
    - containerPort: 80
```

### 3.2 디플로이먼트 (Deployment)
- 파드의 복제본을 관리
- 롤링 업데이트와 롤백을 지원
- 선언적 업데이트를 가능하게 함

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: my-app-deployment
spec:
  replicas: 3
  selector:
    matchLabels:
      app: my-app
  template:
    metadata:
      labels:
        app: my-app
    spec:
      containers:
      - name: my-app
        image: nginx:latest
```

### 3.3 서비스 (Service)
- 파드들에 대한 단일 접근점 제공
- 로드 밸런싱 기능 제공
- 파드의 IP가 변경되어도 안정적인 연결 보장

```yaml
apiVersion: v1
kind: Service
metadata:
  name: my-app-service
spec:
  selector:
    app: my-app
  ports:
  - protocol: TCP
    port: 80
    targetPort: 8080
  type: LoadBalancer
```

---

## 4. 실제 동작 방식

### 4.1 기본 워크플로우
1. 사용자가 YAML 파일로 원하는 상태를 정의
2. API 서버가 요청을 받아 처리
3. 스케줄러가 적절한 노드 선택
4. Kubelet이 컨테이너 실행
5. 지속적으로 상태 모니터링 및 관리

### 4.2 자동 복구 예시
- 노드가 다운되면 다른 노드에 자동으로 파드 재생성
- 컨테이너 충돌 시 자동으로 재시작
- health check 실패 시 자동으로 복구 시도

---

## 5. 시작하기

### 5.1 로컬 환경 설정
1. Minikube 설치 (로컬 개발용 단일 노드 클러스터)
2. kubectl 설치 (명령줄 도구)
3. 기본 명령어 익히기

### 5.2 주요 kubectl 명령어
```bash
# 파드 목록 조회
kubectl get pods

# 디플로이먼트 생성
kubectl apply -f deployment.yaml

# 서비스 상태 확인
kubectl get services

# 로그 확인
kubectl logs pod-name
```

---

## 6. 장단점

### 장점
- 자동화된 운영으로 관리 효율성 증가
- 높은 확장성과 가용성
- 선언적 구성으로 일관된 환경 유지
- 활발한 커뮤니티와 생태계

### 단점
- 초기 학습 곡선이 가파름
- 작은 규모에서는 과도할 수 있음
- 복잡한 설정과 관리 필요

---

## 마무리

Kubernetes는 현대 클라우드 네이티브 애플리케이션 운영에 필수적인 도구입니다. 처음에는 복잡해 보일 수 있지만, 기본 개념을 이해하고 천천히 실습해 나가면서 점진적으로 학습할 수 있습니다. 이 문서에서 다룬 기본 개념들을 토대로, 실제 환경에서 Kubernetes를 활용할 수 있는 기초를 다질 수 있습니다.