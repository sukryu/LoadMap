# 📂 Kubernetes 심화 학습 로드맵

> **목표:**  
> - **Kubernetes의 핵심 개념과 내부 동작 원리를 깊이 이해**한다.  
> - **containerd와 CoreDNS의 역할을 학습하여 Kubernetes가 컨테이너를 실행하고 네트워크를 처리하는 원리를 탐구**한다.  
> - **기본 개념 → 실습 → 프로젝트 적용 → 최적화의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **기본(Basic)과 고급(Advanced) 학습을 포함하며, containerd와 CoreDNS 심화 학습을 추가합니다.**  

```
kubernetes/
├── basic
│   ├── introduction.md  # Kubernetes 개요 및 기본 개념
│   ├── setup.md         # Kubernetes 설치 및 환경 설정
│   ├── workloads.md     # 기본적인 파드, 디플로이먼트, 서비스 관리
│   └── README.md
│
├── advanced
│   ├── networking.md      # 네트워크, 인그레스 및 보안 정책
│   ├── storage.md         # 퍼시스턴트 볼륨 및 스토리지 관리
│   ├── scaling.md         # HPA 및 클러스터 오토스케일링
│   ├── containerd.md      # Kubernetes 컨테이너 런타임
│   ├── coredns.md         # 클러스터 네트워크 및 서비스 디스커버리
│   └── README.md
└── README.md
```

---

## 📖 **1. Kubernetes 개요**
> **Kubernetes(K8s)는 컨테이너화된 애플리케이션을 배포, 관리 및 확장할 수 있도록 설계된 오픈소스 오케스트레이션 도구입니다.**

- ✅ **Pods:** 컨테이너가 실행되는 최소 배포 단위  
- ✅ **Deployments:** 애플리케이션의 선언적 배포 및 롤백 관리  
- ✅ **Services:** 클러스터 내 애플리케이션의 네트워크 접근을 관리  
- ✅ **Ingress:** 외부 트래픽을 클러스터 내부 서비스로 라우팅  
- ✅ **containerd:** Kubernetes의 컨테이너 런타임 관리  
- ✅ **CoreDNS:** 클러스터 내 네트워크 및 서비스 검색(DNS) 관리  

---

## 🏗 **2. containerd와 CoreDNS 심화 학습**
### 🐳 containerd: Kubernetes의 컨테이너 런타임
> **Kubernetes가 CRI(Container Runtime Interface)를 통해 containerd와 상호작용하는 원리**

- **containerd의 역할과 내부 구조**
- **Pod가 생성될 때 containerd에서 컨테이너를 실행하는 과정**
- **컨테이너 이미지 레이어 관리 및 캐싱**
- **containerd CLI(`ctr`)를 활용한 디버깅과 튜닝**

### 🌐 CoreDNS: Kubernetes의 네트워크 및 서비스 검색
> **Kubernetes 내부 네트워크와 DNS 이름 해석 원리**

- **CoreDNS가 클러스터 내부에서 DNS 요청을 처리하는 방식**
- **서비스 검색(Service Discovery) 및 클러스터 네트워크 동작 원리**
- **CoreDNS 설정(ConfigMap) 분석 및 문제 해결**
- **CoreDNS를 활용한 커스텀 DNS 정책 적용**

---

## 🚀 **3. 실전 예제**
> **Kubernetes를 활용하여 간단한 애플리케이션을 배포하고, containerd와 CoreDNS 동작을 확인합니다.**

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: my-app
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
        ports:
        - containerPort: 80
```

```sh
# Kubernetes 배포 실행
kubectl apply -f deployment.yaml

# containerd를 통한 컨테이너 상태 확인
ctr -n k8s.io containers list

# CoreDNS 설정 확인
kubectl get configmap coredns -n kube-system -o yaml
```

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → Kubernetes 개념과 containerd, CoreDNS의 원리 이해  
2. **도구 실습** → containerd, CoreDNS를 활용한 실습 진행  
3. **프로젝트 적용** → 실제 프로젝트에서 Kubernetes 및 containerd 활용  
4. **최적화 연구** → 성능, 보안, 네트워크 설정 최적화  

---

## 📚 **5. 추천 리소스**
- **Kubernetes 공식 문서:**  
  - [Kubernetes Docs](https://kubernetes.io/docs/)  
- **containerd 공식 문서:**  
  - [containerd.io](https://containerd.io/)  
- **CoreDNS 공식 문서:**  
  - [CoreDNS.io](https://coredns.io/)  
- **Kubernetes 예제 및 템플릿:**  
  - [Awesome Kubernetes](https://github.com/ramitsurana/awesome-kubernetes)  
  - [Kubernetes Examples](https://github.com/kubernetes/examples)  

---

## ✅ **마무리**
이 문서는 **Kubernetes의 기본 개념부터 containerd와 CoreDNS를 활용한 실무 적용까지 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 최적화**의 단계로 학습하며, **실무에서 Kubernetes를 효과적으로 활용하는 방법**을 다룹니다. 🚀

