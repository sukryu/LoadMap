# Kubernetes 클러스터 네트워크 및 서비스 디스커버리

> **목표:**  
> - Kubernetes 클러스터의 네트워크 아키텍처와 작동 원리를 이해한다.
> - CoreDNS를 통한 서비스 디스커버리 메커니즘을 파악한다.
> - 네트워크 통신 및 서비스 검색 문제 해결 방법을 습득한다.
> - 실제 운영 환경에서의 네트워크 최적화 방법을 익힌다.

---

## 1. Kubernetes 네트워크 기본 원리

Kubernetes 네트워크는 파드 간 통신, 서비스 디스커버리, 외부 접근 등을 위한 복잡한 네트워크 계층을 제공합니다. 모든 파드는 고유한 IP 주소를 가지며, 클러스터 내의 모든 파드는 NAT 없이 서로 통신할 수 있어야 합니다.

### 1.1 네트워크 모델

Kubernetes는 다음과 같은 네트워크 요구사항을 가집니다:

```plaintext
클러스터 네트워크 요구사항:
- 모든 파드는 고유한 IP 주소를 가짐
- 파드는 노드의 IP와 관계없이 다른 파드와 통신 가능
- 노드의 에이전트(kubelet 등)는 해당 노드의 파드와 통신 가능
```

### 1.2 CNI(Container Network Interface) 설정

Calico CNI 구성 예시:

```yaml
apiVersion: v1
kind: ConfigMap
metadata:
  name: calico-config
  namespace: kube-system
data:
  cni_network_config: |-
    {
      "name": "k8s-pod-network",
      "cniVersion": "0.3.1",
      "plugins": [
        {
          "type": "calico",
          "log_level": "info",
          "datastore_type": "kubernetes",
          "nodename": "__KUBERNETES_NODE_NAME__",
          "ipam": {
            "type": "calico-ipam"
          },
          "policy": {
            "type": "k8s"
          },
          "kubernetes": {
            "kubeconfig": "__KUBECONFIG_FILEPATH__"
          }
        }
      ]
    }
```

---

## 2. CoreDNS 서비스 디스커버리

CoreDNS는 Kubernetes의 기본 DNS 서버로, 서비스 디스커버리의 핵심 역할을 수행합니다.

### 2.1 CoreDNS 설정

기본 CoreDNS Corefile 구성:

```yaml
apiVersion: v1
kind: ConfigMap
metadata:
  name: coredns
  namespace: kube-system
data:
  Corefile: |
    .:53 {
        errors
        health {
            lameduck 5s
        }
        ready
        kubernetes cluster.local in-addr.arpa ip6.arpa {
            pods insecure
            fallthrough in-addr.arpa ip6.arpa
            ttl 30
        }
        prometheus :9153
        forward . /etc/resolv.conf
        cache 30
        loop
        reload
        loadbalance
    }
```

### 2.2 DNS 레코드 유형

Kubernetes의 DNS 레코드 형식:

```plaintext
# 서비스 DNS 레코드
<service-name>.<namespace>.svc.cluster.local

# 파드 DNS 레코드
<pod-ip>.<namespace>.pod.cluster.local

# Headless 서비스의 파드 DNS 레코드
<pod-name>.<service-name>.<namespace>.svc.cluster.local
```

---

## 3. 서비스 디스커버리 메커니즘

### 3.1 서비스 등록 및 검색 과정

서비스가 생성되면 다음과 같은 프로세스가 진행됩니다:

```yaml
apiVersion: v1
kind: Service
metadata:
  name: my-service
spec:
  selector:
    app: my-app
  ports:
    - protocol: TCP
      port: 80
      targetPort: 8080
```

CoreDNS는 이 서비스에 대해 자동으로 다음 DNS 레코드를 생성합니다:
- A 레코드: my-service.default.svc.cluster.local
- SRV 레코드: _tcp.my-service.default.svc.cluster.local

### 3.2 서비스 엔드포인트 관리

```yaml
apiVersion: v1
kind: Endpoints
metadata:
  name: my-service
subsets:
  - addresses:
      - ip: 10.244.0.11
      - ip: 10.244.0.12
    ports:
      - port: 8080
```

---

## 4. 네트워크 정책 및 보안

### 4.1 네트워크 정책 설정

특정 네임스페이스의 DNS 트래픽 제어:

```yaml
apiVersion: networking.k8s.io/v1
kind: NetworkPolicy
metadata:
  name: allow-dns-access
spec:
  podSelector: {}
  policyTypes:
  - Egress
  egress:
  - to:
    - namespaceSelector:
        matchLabels:
          kubernetes.io/metadata.name: kube-system
    ports:
    - protocol: UDP
      port: 53
    - protocol: TCP
      port: 53
```

### 4.2 DNS 보안 설정

DNSSEC 활성화 예시:

```yaml
apiVersion: v1
kind: ConfigMap
metadata:
  name: coredns
  namespace: kube-system
data:
  Corefile: |
    .:53 {
        dnssec {
            cache 3600
        }
        kubernetes cluster.local in-addr.arpa ip6.arpa {
            pods insecure
            fallthrough in-addr.arpa ip6.arpa
        }
    }
```

---

## 5. 성능 최적화 및 문제 해결

### 5.1 CoreDNS 성능 튜닝

캐시 및 동시성 설정:

```yaml
.:53 {
    cache {
        success 10000
        denial 5000
        prefetch 10
        serve_stale
    }
    health {
        lameduck 5s
    }
    ready
    kubernetes cluster.local in-addr.arpa ip6.arpa {
        pods insecure
        fallthrough in-addr.arpa ip6.arpa
        ttl 30
    }
}
```

### 5.2 문제 해결 도구 및 명령어

```bash
# DNS 해결 테스트
kubectl run dnsutils --image=gcr.io/kubernetes-e2e-test-images/dnsutils:1.3 -- sleep 3600

kubectl exec -i -t dnsutils -- nslookup kubernetes.default

# CoreDNS 로그 확인
kubectl logs -n kube-system -l k8s-app=kube-dns

# DNS 쿼리 메트릭 확인
kubectl port-forward -n kube-system service/kube-dns 9153:9153
curl localhost:9153/metrics
```

---

## 6. 운영 환경 모범 사례

### 6.1 고가용성 구성

CoreDNS의 고가용성을 위한 설정:

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: coredns
  namespace: kube-system
spec:
  replicas: 2
  strategy:
    type: RollingUpdate
    rollingUpdate:
      maxUnavailable: 1
  template:
    spec:
      affinity:
        podAntiAffinity:
          requiredDuringSchedulingIgnoredDuringExecution:
          - labelSelector:
              matchLabels:
                k8s-app: kube-dns
            topologyKey: kubernetes.io/hostname
```

### 6.2 모니터링 및 알림 설정

Prometheus를 통한 모니터링 설정:

```yaml
apiVersion: monitoring.coreos.com/v1
kind: ServiceMonitor
metadata:
  name: coredns
  namespace: monitoring
spec:
  selector:
    matchLabels:
      k8s-app: kube-dns
  endpoints:
  - port: metrics
    interval: 15s
```

---

## 마무리

클러스터 네트워크와 서비스 디스커버리는 Kubernetes 환경에서 애플리케이션의 안정적인 운영을 위한 핵심 요소입니다. CoreDNS를 통한 효율적인 서비스 디스커버리 구성과 네트워크 정책의 적절한 설정은 안정적이고 보안이 강화된 클러스터 운영의 기반이 됩니다.

특히 운영 환경에서는 성능 최적화, 고가용성 구성, 모니터링 체계 구축이 매우 중요합니다. 이러한 요소들을 적절히 구성하고 관리함으로써, 안정적이고 효율적인 Kubernetes 네트워크 환경을 구축할 수 있습니다.