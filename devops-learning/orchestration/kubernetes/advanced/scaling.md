# Kubernetes 오토스케일링: HPA 및 클러스터 스케일링

> **목표:**  
> - Kubernetes의 오토스케일링 메커니즘과 작동 원리를 이해한다.
> - HPA(Horizontal Pod Autoscaler)의 설정 및 운영 방법을 습득한다.
> - 클러스터 오토스케일링의 구성과 관리 방법을 학습한다.
> - 실제 운영 환경에서의 스케일링 전략과 베스트 프랙티스를 익힌다.

---

## 1. Horizontal Pod Autoscaler (HPA) 이해

HPA는 워크로드의 리소스 사용량을 모니터링하여 파드의 개수를 자동으로 조절하는 Kubernetes의 기본 기능입니다. CPU 사용률, 메모리 사용량, 사용자 정의 메트릭 등을 기반으로 동작합니다.

### 1.1 HPA 기본 구성

기본적인 CPU 기반 HPA 설정:

```yaml
apiVersion: autoscaling/v2
kind: HorizontalPodAutoscaler
metadata:
  name: web-app-hpa
spec:
  scaleTargetRef:
    apiVersion: apps/v1
    kind: Deployment
    name: web-app
  minReplicas: 2
  maxReplicas: 10
  metrics:
  - type: Resource
    resource:
      name: cpu
      target:
        type: Utilization
        averageUtilization: 80
```

### 1.2 메모리 기반 HPA 설정

메모리 사용량을 기준으로 한 스케일링:

```yaml
apiVersion: autoscaling/v2
kind: HorizontalPodAutoscaler
metadata:
  name: web-app-memory-hpa
spec:
  scaleTargetRef:
    apiVersion: apps/v1
    kind: Deployment
    name: web-app
  minReplicas: 2
  maxReplicas: 10
  metrics:
  - type: Resource
    resource:
      name: memory
      target:
        type: Utilization
        averageUtilization: 75
```

---

## 2. 사용자 정의 메트릭 기반 스케일링

Prometheus와 같은 모니터링 시스템의 메트릭을 활용한 스케일링 설정이 가능합니다.

### 2.1 Prometheus 어댑터 설정

```yaml
apiVersion: autoscaling/v2
kind: HorizontalPodAutoscaler
metadata:
  name: web-app-custom-hpa
spec:
  scaleTargetRef:
    apiVersion: apps/v1
    kind: Deployment
    name: web-app
  minReplicas: 2
  maxReplicas: 10
  metrics:
  - type: Pods
    pods:
      metric:
        name: http_requests_per_second
      target:
        type: AverageValue
        averageValue: 1k
```

### 2.2 복합 메트릭 설정

여러 메트릭을 동시에 고려한 스케일링:

```yaml
apiVersion: autoscaling/v2
kind: HorizontalPodAutoscaler
metadata:
  name: web-app-combined-hpa
spec:
  scaleTargetRef:
    apiVersion: apps/v1
    kind: Deployment
    name: web-app
  minReplicas: 2
  maxReplicas: 10
  metrics:
  - type: Resource
    resource:
      name: cpu
      target:
        type: Utilization
        averageUtilization: 80
  - type: Resource
    resource:
      name: memory
      target:
        type: Utilization
        averageUtilization: 75
  - type: Pods
    pods:
      metric:
        name: http_requests_per_second
      target:
        type: AverageValue
        averageValue: 1k
```

---

## 3. 클러스터 오토스케일링

클러스터 오토스케일러는 워크로드의 요구사항에 따라 노드의 수를 자동으로 조절합니다.

### 3.1 클러스터 오토스케일러 설정

AWS EKS의 경우:

```yaml
apiVersion: v1
kind: ConfigMap
metadata:
  name: cluster-autoscaler-config
  namespace: kube-system
data:
  config: |
    {
      "cluster-name": "my-eks-cluster",
      "node-group-auto-discovery": [
        "asg:tag=k8s.io/cluster-autoscaler/enabled,k8s.io/cluster-autoscaler/my-eks-cluster"
      ],
      "scale-down-enabled": true,
      "scale-down-delay-after-add": "10m",
      "scale-down-unneeded-time": "10m"
    }
```

### 3.2 노드 그룹 설정

```yaml
apiVersion: eksctl.io/v1alpha5
kind: ClusterConfig
metadata:
  name: my-eks-cluster
  region: ap-northeast-2
nodeGroups:
  - name: standard-workers
    instanceType: t3.medium
    minSize: 2
    maxSize: 10
    desiredCapacity: 3
    iam:
      withAddonPolicies:
        autoScaler: true
```

---

## 4. 스케일링 전략 및 최적화

### 4.1 스케일링 임계값 설정

효과적인 스케일링을 위한 임계값 설정:

```yaml
apiVersion: autoscaling/v2
kind: HorizontalPodAutoscaler
metadata:
  name: web-app-optimized-hpa
spec:
  scaleTargetRef:
    apiVersion: apps/v1
    kind: Deployment
    name: web-app
  minReplicas: 2
  maxReplicas: 10
  behavior:
    scaleUp:
      stabilizationWindowSeconds: 60
      policies:
      - type: Percent
        value: 100
        periodSeconds: 15
    scaleDown:
      stabilizationWindowSeconds: 300
      policies:
      - type: Percent
        value: 10
        periodSeconds: 15
```

### 4.2 리소스 요청 및 제한 설정

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: web-app
spec:
  template:
    spec:
      containers:
      - name: web-app
        resources:
          requests:
            cpu: "250m"
            memory: "512Mi"
          limits:
            cpu: "500m"
            memory: "1Gi"
```

---

## 5. 모니터링 및 문제 해결

### 5.1 HPA 모니터링

```bash
# HPA 상태 확인
kubectl get hpa

# 상세 정보 확인
kubectl describe hpa web-app-hpa

# 메트릭 서버 상태 확인
kubectl get --raw "/apis/metrics.k8s.io/v1beta1/nodes"
```

### 5.2 클러스터 오토스케일러 모니터링

```bash
# 노드 상태 확인
kubectl get nodes

# 오토스케일러 로그 확인
kubectl logs -n kube-system -l app=cluster-autoscaler

# 노드 그룹 상태 확인
eksctl get nodegroup --cluster=my-eks-cluster
```

---

## 6. 운영 베스트 프랙티스

스케일링 운영에서 고려해야 할 주요 사항들:

### 6.1 성능 최적화

스케일링 성능을 최적화하기 위한 핵심 고려사항:

1. 적절한 메트릭 선택: 워크로드 특성에 맞는 스케일링 메트릭을 선택합니다.
2. 안정화 기간 설정: 불필요한 스케일링을 방지하기 위한 적절한 안정화 기간을 설정합니다.
3. 리소스 요청 최적화: 정확한 리소스 요청을 통해 효율적인 스케일링을 가능하게 합니다.

### 6.2 비용 최적화

비용 효율적인 스케일링을 위한 전략:

1. 최소/최대 레플리카 수 적절히 설정
2. 불필요한 스케일업 방지를 위한 임계값 조정
3. 노드 그룹의 인스턴스 타입 최적화

---

## 마무리

Kubernetes의 오토스케일링 기능은 애플리케이션의 가용성과 효율성을 보장하는 핵심 요소입니다. HPA를 통한 파드 레벨의 스케일링과 클러스터 오토스케일러를 통한 노드 레벨의 스케일링을 적절히 구성하고 관리함으로써, 워크로드의 요구사항에 따라 자동으로 확장되고 축소되는 탄력적인 인프라를 구축할 수 있습니다. 

효과적인 오토스케일링을 위해서는 워크로드의 특성을 잘 이해하고, 적절한 메트릭과 임계값을 설정하며, 지속적인 모니터링과 최적화가 필요합니다. 이를 통해 비용 효율적이면서도 안정적인 Kubernetes 환경을 운영할 수 있습니다.