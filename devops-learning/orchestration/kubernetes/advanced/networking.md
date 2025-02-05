# Kubernetes 네트워크, 인그레스 및 보안 정책

> **목표:**  
> - Kubernetes의 네트워크 아키텍처와 통신 원리를 이해한다.
> - 인그레스 컨트롤러를 통한 외부 트래픽 관리 방법을 습득한다.
> - 네트워크 정책과 보안 설정을 통한 트래픽 제어 방법을 학습한다.
> - 실제 운영 환경에서의 보안 베스트 프랙티스를 익힌다.

---

## 1. Kubernetes 네트워크 기본

Kubernetes 네트워크는 파드 간 통신, 서비스 디스커버리, 외부 접근 등 여러 계층의 네트워킹을 제공합니다.

### 1.1 네트워크 모델

Kubernetes 네트워크는 다음과 같은 기본 원칙을 따릅니다:

- 모든 파드는 고유한 IP 주소를 가집니다.
- 파드 간 NAT 없이 직접 통신이 가능합니다.
- 노드와 파드 간 NAT 없이 통신이 가능합니다.
- 파드가 보는 자신의 IP는 다른 파드가 보는 해당 파드의 IP와 동일합니다.

### 1.2 CNI(Container Network Interface) 구성

```yaml
apiVersion: v1
kind: ConfigMap
metadata:
  name: calico-config
  namespace: kube-system
data:
  calico_backend: "bird"
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
          "mtu": 1500,
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

## 2. 인그레스(Ingress) 구성

인그레스는 클러스터 외부에서 내부 서비스로의 HTTP/HTTPS 트래픽을 관리합니다.

### 2.1 인그레스 컨트롤러 설치

Nginx 인그레스 컨트롤러 설치 예시:

```bash
# Nginx 인그레스 컨트롤러 설치
kubectl apply -f https://raw.githubusercontent.com/kubernetes/ingress-nginx/controller-v1.1.0/deploy/static/provider/cloud/deploy.yaml

# 설치 확인
kubectl get pods -n ingress-nginx
```

### 2.2 인그레스 규칙 설정

```yaml
apiVersion: networking.k8s.io/v1
kind: Ingress
metadata:
  name: example-ingress
  annotations:
    nginx.ingress.kubernetes.io/rewrite-target: /
    nginx.ingress.kubernetes.io/ssl-redirect: "true"
spec:
  ingressClassName: nginx
  tls:
  - hosts:
    - example.com
    secretName: tls-secret
  rules:
  - host: example.com
    http:
      paths:
      - path: /app1
        pathType: Prefix
        backend:
          service:
            name: app1-service
            port:
              number: 80
      - path: /app2
        pathType: Prefix
        backend:
          service:
            name: app2-service
            port:
              number: 80
```

---

## 3. 네트워크 정책(Network Policy)

네트워크 정책은 파드 간의 통신을 제어하는 방화벽 규칙을 정의합니다.

### 3.1 기본 네트워크 정책

모든 트래픽을 차단하는 기본 정책:

```yaml
apiVersion: networking.k8s.io/v1
kind: NetworkPolicy
metadata:
  name: default-deny-all
spec:
  podSelector: {}
  policyTypes:
  - Ingress
  - Egress
```

### 3.2 세부 트래픽 제어

특정 애플리케이션 간 통신만 허용하는 정책:

```yaml
apiVersion: networking.k8s.io/v1
kind: NetworkPolicy
metadata:
  name: api-allow-frontend
spec:
  podSelector:
    matchLabels:
      app: api
  policyTypes:
  - Ingress
  ingress:
  - from:
    - podSelector:
        matchLabels:
          app: frontend
    ports:
    - protocol: TCP
      port: 8080
```

---

## 4. 보안 정책 구성

### 4.1 파드 보안 컨텍스트

파드 레벨의 보안 설정:

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: security-context-pod
spec:
  securityContext:
    runAsUser: 1000
    runAsGroup: 3000
    fsGroup: 2000
  containers:
  - name: secured-container
    image: nginx
    securityContext:
      allowPrivilegeEscalation: false
      capabilities:
        drop:
        - ALL
      readOnlyRootFilesystem: true
```

### 4.2 파드 보안 정책(PodSecurityPolicy)

클러스터 수준의 보안 정책:

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
  volumes:
  - 'configMap'
  - 'emptyDir'
  - 'projected'
  - 'secret'
  - 'downwardAPI'
  - 'persistentVolumeClaim'
```

---

## 5. SSL/TLS 인증서 관리

### 5.1 cert-manager 설치

```bash
# cert-manager 설치
kubectl apply -f https://github.com/jetstack/cert-manager/releases/download/v1.7.0/cert-manager.yaml

# 상태 확인
kubectl get pods -n cert-manager
```

### 5.2 인증서 발급 설정

```yaml
apiVersion: cert-manager.io/v1
kind: ClusterIssuer
metadata:
  name: letsencrypt-prod
spec:
  acme:
    server: https://acme-v02.api.letsencrypt.org/directory
    email: admin@example.com
    privateKeySecretRef:
      name: letsencrypt-prod
    solvers:
    - http01:
        ingress:
          class: nginx
```

---

## 6. 모니터링 및 로깅

### 6.1 네트워크 모니터링

```bash
# 네트워크 트래픽 분석
kubectl exec -it <pod-name> -- tcpdump -i any

# 서비스 연결성 테스트
kubectl run test-connection --rm -it --image=busybox -- wget -O- http://service-name:port
```

### 6.2 보안 감사 로깅

```yaml
apiVersion: audit.k8s.io/v1
kind: Policy
rules:
- level: Metadata
  resources:
  - group: ""
    resources: ["pods"]
```

---

## 7. 보안 베스트 프랙티스

네트워크와 보안 구성 시 고려해야 할 주요 사항들:

1. 최소 권한 원칙을 적용하여 필요한 통신만 허용합니다.
2. 모든 외부 통신은 TLS를 사용하여 암호화합니다.
3. 네트워크 정책을 사용하여 파드 간 통신을 명시적으로 제어합니다.
4. 정기적으로 보안 설정을 검토하고 업데이트합니다.
5. 컨테이너는 항상 비특권 사용자로 실행합니다.
6. 컨테이너 이미지는 정기적으로 보안 취약점을 스캔합니다.

---

## 마무리

Kubernetes의 네트워크와 보안 설정은 애플리케이션의 안전한 운영을 위한 핵심 요소입니다. 인그레스를 통한 외부 트래픽 관리, 네트워크 정책을 통한 파드 간 통신 제어, 그리고 다양한 보안 정책의 적용은 모두 세심한 계획과 구성이 필요합니다. 이러한 설정들을 제대로 이해하고 구성함으로써, 안전하고 신뢰할 수 있는 Kubernetes 환경을 구축할 수 있습니다.