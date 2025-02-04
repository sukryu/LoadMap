# 📂 Kubernetes - Advanced 학습 개요

> **목표:**  
> - **Kubernetes의 고급 개념과 실무 활용법을 학습**한다.  
> - **네트워크, 스토리지, 오토스케일링 등 클러스터 최적화 기법을 익힌다.**  
> - **고급 Kubernetes 오브젝트와 운영 전략을 실습한다.**  
> - **이론 → 실습 → 프로젝트 적용 → 최적화의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **Kubernetes의 고급 개념을 이해하고 실무에 적용하는 방법을 학습합니다.**  

```
advanced/
├── networking.md      # 네트워크, 인그레스 및 보안 정책
├── storage.md         # 퍼시스턴트 볼륨 및 스토리지 관리
├── scaling.md         # HPA 및 클러스터 오토스케일링
└── README.md
```

---

## 📖 **1. 고급 개념 개요**
> **Kubernetes는 컨테이너 오케스트레이션을 위한 강력한 기능을 제공하며, 이를 활용하여 인프라를 최적화할 수 있습니다.**

- ✅ **Network Policies:** 클러스터 내 트래픽 제어 및 보안 정책 설정  
- ✅ **Ingress Controllers:** 외부 트래픽을 내부 서비스로 라우팅  
- ✅ **Persistent Volumes:** 데이터를 유지하는 다양한 스토리지 방식 이해  
- ✅ **Horizontal Pod Autoscaler (HPA):** 부하에 따른 자동 확장  
- ✅ **Vertical Pod Autoscaler (VPA):** 개별 Pod의 리소스 자동 최적화  

---

## 🏗 **2. 학습 내용**
### 📌 Advanced Networking (네트워크 고급 개념)
- **서비스(Service), 네트워크 정책(Network Policy) 설정**
- **Ingress를 활용한 외부 트래픽 관리**
- **Service Mesh (Istio, Linkerd) 개요 및 적용**

### 📌 Advanced Storage (스토리지 고급 개념)
- **Persistent Volume (PV) 및 Persistent Volume Claim (PVC) 활용**
- **Storage Class를 활용한 동적 볼륨 프로비저닝**
- **다양한 클라우드 스토리지 드라이버 활용 (EBS, NFS, Ceph 등)**

### 📌 Kubernetes Scaling (클러스터 확장 및 최적화)
- **Horizontal Pod Autoscaler (HPA) 설정 및 실습**
- **Vertical Pod Autoscaler (VPA) 적용 및 튜닝**
- **Cluster Autoscaler를 활용한 노드 자동 확장**

---

## 🚀 **3. 실전 예제**
> **Kubernetes를 활용하여 HPA와 Ingress를 설정하는 예제**

```yaml
apiVersion: autoscaling/v2beta2
kind: HorizontalPodAutoscaler
metadata:
  name: my-app-hpa
spec:
  scaleTargetRef:
    apiVersion: apps/v1
    kind: Deployment
    name: my-app
  minReplicas: 2
  maxReplicas: 10
  metrics:
  - type: Resource
    resource:
      name: cpu
      target:
        type: Utilization
        averageUtilization: 50
```

```sh
# HPA 적용 및 모니터링
kubectl apply -f hpa.yaml
kubectl get hpa
```

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → Kubernetes의 고급 기능과 운영 원리 이해  
2. **실습 진행** → 네트워크, 스토리지, 오토스케일링 설정 실습  
3. **프로젝트 적용** → 실무 환경에서 Kubernetes 고급 기능 활용  
4. **최적화 연구** → 성능, 보안, 비용 최적화 전략 연구  

---

## 📚 **5. 추천 리소스**
- **Kubernetes 공식 문서:**  
  - [Kubernetes Docs](https://kubernetes.io/docs/)  

- **Kubernetes 고급 예제 및 템플릿:**  
  - [Awesome Kubernetes](https://github.com/ramitsurana/awesome-kubernetes)  
  - [Kubernetes Advanced Examples](https://github.com/kubernetes/examples)  

---

## ✅ **마무리**
이 문서는 **Kubernetes의 고급 개념을 이해하고 실무에 적용할 수 있도록 구성된 가이드**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 최적화**의 단계로 학습하며, **실무에서 Kubernetes를 효과적으로 운영하는 방법**을 다룹니다. 🚀

