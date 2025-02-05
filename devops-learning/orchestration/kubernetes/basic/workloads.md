# Kubernetes 워크로드 관리: 파드, 디플로이먼트, 서비스

> **목표:**  
> - Kubernetes의 기본 워크로드 단위인 파드의 개념과 관리 방법을 이해한다.
> - 디플로이먼트를 통한 애플리케이션 배포와 관리 방법을 습득한다.
> - 서비스를 통한 네트워크 연결과 로드밸런싱 구성 방법을 학습한다.
> - 실제 운영 환경에서 필요한 관리 기법을 익힌다.

---

## 1. 파드(Pod) 관리

파드는 Kubernetes에서 가장 기본적인 배포 단위입니다. 하나 이상의 컨테이너를 포함하며, 같은 파드 내의 컨테이너들은 네트워크와 스토리지 자원을 공유합니다.

### 1.1 파드 생성

다음은 간단한 nginx 웹 서버 파드를 생성하는 예시입니다:

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: nginx-pod
  labels:
    app: nginx
spec:
  containers:
  - name: nginx
    image: nginx:1.17.1
    ports:
    - containerPort: 80
    resources:
      requests:
        memory: "64Mi"
        cpu: "250m"
      limits:
        memory: "128Mi"
        cpu: "500m"
```

파드 생성 및 확인 명령어:

```bash
# YAML 파일로 파드 생성
kubectl apply -f nginx-pod.yaml

# 파드 상태 확인
kubectl get pods
kubectl describe pod nginx-pod

# 파드 로그 확인
kubectl logs nginx-pod
```

### 1.2 다중 컨테이너 파드

실제 운영 환경에서는 여러 컨테이너를 하나의 파드에서 실행해야 할 때가 있습니다:

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: web-app
spec:
  containers:
  - name: web
    image: nginx:1.17.1
    ports:
    - containerPort: 80
  - name: log-collector
    image: fluentd:v1.7
    volumeMounts:
    - name: log-volume
      mountPath: /var/log
  volumes:
  - name: log-volume
    emptyDir: {}
```

---

## 2. 디플로이먼트(Deployment) 관리

디플로이먼트는 파드의 선언적 업데이트와 스케일링을 제공합니다. 실제 운영 환경에서는 대부분 디플로이먼트를 통해 애플리케이션을 관리합니다.

### 2.1 디플로이먼트 생성

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: nginx-deployment
  labels:
    app: nginx
spec:
  replicas: 3
  selector:
    matchLabels:
      app: nginx
  template:
    metadata:
      labels:
        app: nginx
    spec:
      containers:
      - name: nginx
        image: nginx:1.17.1
        ports:
        - containerPort: 80
        readinessProbe:
          httpGet:
            path: /
            port: 80
          initialDelaySeconds: 5
          periodSeconds: 5
        livenessProbe:
          httpGet:
            path: /
            port: 80
          initialDelaySeconds: 15
          periodSeconds: 15
```

### 2.2 디플로이먼트 관리

```bash
# 디플로이먼트 생성
kubectl apply -f nginx-deployment.yaml

# 상태 확인
kubectl get deployments
kubectl describe deployment nginx-deployment

# 스케일링
kubectl scale deployment nginx-deployment --replicas=5

# 롤링 업데이트
kubectl set image deployment/nginx-deployment nginx=nginx:1.17.2
```

### 2.3 롤백 관리

```bash
# 업데이트 히스토리 확인
kubectl rollout history deployment nginx-deployment

# 특정 버전으로 롤백
kubectl rollout undo deployment nginx-deployment --to-revision=1

# 롤아웃 상태 확인
kubectl rollout status deployment nginx-deployment
```

---

## 3. 서비스(Service) 관리

서비스는 파드들에 대한 단일 접근점을 제공하고 로드밸런싱을 담당합니다.

### 3.1 서비스 유형

1. ClusterIP: 클러스터 내부에서만 접근 가능한 서비스
2. NodePort: 각 노드의 IP에서 특정 포트로 접근 가능
3. LoadBalancer: 클라우드 제공자의 로드밸런서를 사용
4. ExternalName: 외부 서비스에 대한 별칭을 제공

### 3.2 서비스 생성

```yaml
apiVersion: v1
kind: Service
metadata:
  name: nginx-service
spec:
  type: LoadBalancer
  selector:
    app: nginx
  ports:
  - protocol: TCP
    port: 80
    targetPort: 80
  sessionAffinity: ClientIP
  sessionAffinityConfig:
    clientIP:
      timeoutSeconds: 1800
```

### 3.3 서비스 관리

```bash
# 서비스 생성
kubectl apply -f nginx-service.yaml

# 서비스 목록 확인
kubectl get services

# 서비스 상세 정보 확인
kubectl describe service nginx-service

# 엔드포인트 확인
kubectl get endpoints nginx-service
```

---

## 4. 실전 운영 팁

### 4.1 리소스 관리

효율적인 리소스 사용을 위한 권장사항:

```yaml
spec:
  containers:
  - name: app
    resources:
      requests:
        memory: "64Mi"
        cpu: "250m"
      limits:
        memory: "128Mi"
        cpu: "500m"
```

### 4.2 헬스 체크 구성

안정적인 운영을 위한 프로브 설정:

```yaml
spec:
  containers:
  - name: app
    livenessProbe:
      httpGet:
        path: /healthz
        port: 8080
      initialDelaySeconds: 15
      periodSeconds: 10
    readinessProbe:
      httpGet:
        path: /ready
        port: 8080
      initialDelaySeconds: 5
      periodSeconds: 5
```

### 4.3 로깅 및 모니터링

중요 메트릭 수집을 위한 설정:

```bash
# 리소스 사용량 모니터링
kubectl top pods
kubectl top nodes

# 로그 수집
kubectl logs -f deployment/nginx-deployment
```

---

## 5. 문제 해결 가이드

### 5.1 일반적인 문제 해결

```bash
# 파드 상태 확인
kubectl get pods -o wide

# 파드 상세 정보 확인
kubectl describe pod <pod-name>

# 이벤트 확인
kubectl get events --sort-by='.lastTimestamp'
```

### 5.2 디버깅 기법

```bash
# 파드 내부 접속
kubectl exec -it <pod-name> -- /bin/bash

# 임시 디버깅 파드 생성
kubectl run debug-pod --rm -it --image=busybox -- /bin/sh
```

---

## 마무리

Kubernetes의 워크로드 관리는 파드, 디플로이먼트, 서비스의 올바른 구성과 관리에서 시작합니다. 각 구성 요소의 특성을 이해하고 적절히 활용하면 안정적이고 확장 가능한 애플리케이션 운영이 가능합니다. 특히 운영 환경에서는 리소스 관리, 헬스 체크, 모니터링 설정이 매우 중요하며, 이를 통해 애플리케이션의 안정성을 보장할 수 있습니다.