# Kubernetes 설치 및 환경 설정 가이드

> **목표:**  
> - 개발 및 운영 환경에 Kubernetes를 설치하고 구성하는 방법을 이해한다.
> - 로컬 개발 환경부터 프로덕션 환경까지 단계별 설정 방법을 습득한다.
> - 기본적인 문제 해결 및 환경 구성 방법을 파악한다.

---

## 1. 로컬 개발 환경 구성

### 1.1 사전 준비사항

먼저 시스템에 다음 도구들이 설치되어 있어야 합니다:

```bash
# Windows의 경우 Chocolatey를 통한 설치
choco install docker-desktop
choco install minikube
choco install kubectl

# macOS의 경우 Homebrew를 통한 설치
brew install docker
brew install minikube
brew install kubectl

# Linux(Ubuntu)의 경우 apt를 통한 설치
sudo apt-get update
sudo apt-get install docker.io
sudo apt-get install minikube
sudo snap install kubectl --classic
```

### 1.2 Minikube 설정 및 시작

Minikube는 로컬 개발 환경에서 단일 노드 Kubernetes 클러스터를 실행할 수 있게 해주는 도구입니다.

```bash
# Minikube 시작
minikube start --driver=docker

# 상태 확인
minikube status

# 대시보드 활성화
minikube dashboard
```

### 1.3 kubectl 구성

kubectl은 Kubernetes 클러스터를 제어하는 명령줄 도구입니다.

```bash
# kubectl 설정 확인
kubectl config view

# 클러스터 정보 확인
kubectl cluster-info

# 노드 상태 확인
kubectl get nodes
```

---

## 2. 프로덕션 환경 구성

### 2.1 클라우드 환경 선택

주요 클라우드 제공자별 관리형 Kubernetes 서비스:

- AWS: Amazon EKS (Elastic Kubernetes Service)
- Azure: AKS (Azure Kubernetes Service)
- Google Cloud: GKE (Google Kubernetes Engine)

예시로 AWS EKS 설정 과정을 살펴보겠습니다:

```bash
# AWS CLI 설치 및 구성
aws configure

# eksctl 설치 (EKS 클러스터 관리 도구)
brew install eksctl  # macOS
choco install eksctl # Windows

# EKS 클러스터 생성
eksctl create cluster \
  --name my-cluster \
  --version 1.24 \
  --region ap-northeast-2 \
  --nodegroup-name standard-workers \
  --node-type t3.medium \
  --nodes 3 \
  --nodes-min 1 \
  --nodes-max 4
```

### 2.2 네트워크 구성

Kubernetes 클러스터의 네트워크 설정:

```bash
# Calico 네트워크 플러그인 설치
kubectl apply -f https://docs.projectcalico.org/manifests/calico.yaml

# 네트워크 정책 예시
apiVersion: networking.k8s.io/v1
kind: NetworkPolicy
metadata:
  name: default-deny
spec:
  podSelector: {}
  policyTypes:
  - Ingress
  - Egress
```

### 2.3 스토리지 구성

영구 스토리지 설정:

```yaml
# StorageClass 정의
apiVersion: storage.k8s.io/v1
kind: StorageClass
metadata:
  name: standard
provisioner: kubernetes.io/aws-ebs
parameters:
  type: gp2
reclaimPolicy: Retain
```

---

## 3. 보안 설정

### 3.1 인증 및 권한 설정

RBAC(Role-Based Access Control) 구성:

```yaml
# Role 생성
apiVersion: rbac.authorization.k8s.io/v1
kind: Role
metadata:
  namespace: default
  name: pod-reader
rules:
- apiGroups: [""]
  resources: ["pods"]
  verbs: ["get", "list", "watch"]

# RoleBinding 설정
apiVersion: rbac.authorization.k8s.io/v1
kind: RoleBinding
metadata:
  name: read-pods
  namespace: default
subjects:
- kind: User
  name: jane
  apiGroup: rbac.authorization.k8s.io
roleRef:
  kind: Role
  name: pod-reader
  apiGroup: rbac.authorization.k8s.io
```

### 3.2 보안 정책 설정

Pod 보안 정책 구성:

```yaml
apiVersion: policy/v1beta1
kind: PodSecurityPolicy
metadata:
  name: restricted
spec:
  privileged: false
  seLinux:
    rule: RunAsAny
  runAsUser:
    rule: MustRunAsNonRoot
  fsGroup:
    rule: RunAsAny
```

---

## 4. 모니터링 설정

### 4.1 Prometheus 및 Grafana 설치

```bash
# Helm 설치 (패키지 관리자)
curl https://raw.githubusercontent.com/helm/helm/master/scripts/get-helm-3 | bash

# Prometheus 설치
helm repo add prometheus-community https://prometheus-community.github.io/helm-charts
helm install prometheus prometheus-community/kube-prometheus-stack
```

### 4.2 로깅 시스템 구성

EFK(Elasticsearch, Fluentd, Kibana) 스택 설치:

```bash
# Elasticsearch 설치
kubectl apply -f elasticsearch.yaml

# Fluentd 설치
kubectl apply -f fluentd-daemonset.yaml

# Kibana 설치
kubectl apply -f kibana.yaml
```

---

## 5. 문제 해결 및 디버깅

### 5.1 일반적인 문제 해결 방법

```bash
# 파드 상태 확인
kubectl describe pod <pod-name>

# 로그 확인
kubectl logs <pod-name>

# 이벤트 확인
kubectl get events

# 노드 상태 확인
kubectl describe node <node-name>
```

### 5.2 성능 문제 해결

```bash
# 리소스 사용량 확인
kubectl top pods
kubectl top nodes

# 파드 상세 메트릭 확인
kubectl describe pod <pod-name> | grep -A 5 Requests
```

---

## 6. 운영 체크리스트

설치 완료 후 확인해야 할 항목들:

1. 노드 상태 및 건강성 확인
2. 네트워크 연결성 테스트
3. 스토리지 프로비저닝 확인
4. 보안 정책 적용 상태 점검
5. 모니터링 시스템 동작 확인
6. 로깅 시스템 정상 작동 확인
7. 백업 시스템 구성 확인

---

## 마무리

Kubernetes 환경 구성은 처음에는 복잡해 보일 수 있지만, 단계별로 차근차근 진행하면 충분히 관리 가능합니다. 특히 로컬 개발 환경에서 충분한 테스트를 거친 후 프로덕션 환경으로 이전하는 것이 중요합니다. 환경 설정 후에는 정기적인 업데이트와 모니터링을 통해 안정적인 운영을 보장해야 합니다.