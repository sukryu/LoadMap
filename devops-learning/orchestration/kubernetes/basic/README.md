# 📂 Kubernetes - Basic 학습 개요

> **목표:**  
> - **Kubernetes의 기본 개념과 사용법을 학습**한다.  
> - **컨테이너 오케스트레이션의 핵심 개념을 익히고 활용 방법을 익힌다.**  
> - **기본적인 Kubernetes 명령어 및 오브젝트를 실습한다.**  
> - **이론 → 실습 → 프로젝트 적용의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **Kubernetes의 기초 개념을 이해하고 기본 명령어를 학습합니다.**  

```
basic/
├── introduction.md  # Kubernetes 개요 및 기본 개념
├── setup.md         # Kubernetes 설치 및 환경 설정
├── workloads.md     # 기본적인 파드, 디플로이먼트, 서비스 관리
└── README.md
```

---

## 📖 **1. 기본 개념 개요**
> **Kubernetes는 컨테이너화된 애플리케이션을 배포, 운영, 확장할 수 있도록 설계된 컨테이너 오케스트레이션 도구입니다.**

- ✅ **Pods:** 컨테이너가 실행되는 최소 배포 단위  
- ✅ **Deployments:** 애플리케이션의 선언적 배포 및 롤백 관리  
- ✅ **Services:** 클러스터 내 애플리케이션의 네트워크 접근을 관리  
- ✅ **ConfigMaps & Secrets:** 환경 변수 및 보안 데이터를 관리  
- ✅ **Persistent Volumes:** 데이터 지속성을 제공하는 스토리지 관리  

---

## 🏗 **2. 학습 내용**
### 📌 Introduction (Kubernetes 소개)
- **Kubernetes란 무엇인가?**
- **컨테이너 오케스트레이션이 필요한 이유**

### 📌 Setup (Kubernetes 설치 및 환경 설정)
- **Minikube 및 Kind를 활용한 로컬 Kubernetes 클러스터 실행**
- **kubectl을 활용한 Kubernetes 관리 명령어 실습**

### 📌 Workloads (기본 오브젝트 개념 이해 및 활용)
- **Pod, Deployment, ReplicaSet 개념 이해**
- **서비스(Service) 및 Ingress를 활용한 네트워크 설정**
- **ConfigMaps 및 Secrets를 활용한 환경 변수 관리**

---

## 🚀 **3. 실전 예제**
> **Kubernetes를 활용하여 간단한 애플리케이션 배포하기**

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

# 배포된 애플리케이션 확인
kubectl get pods
```

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → Kubernetes의 기본 개념과 구조 이해  
2. **기본 실습** → Kubernetes 오브젝트 생성 및 관리  
3. **프로젝트 적용** → 실제 프로젝트에서 Kubernetes 활용  

---

## 📚 **5. 추천 리소스**
- **Kubernetes 공식 문서:**  
  - [Kubernetes Docs](https://kubernetes.io/docs/)  

- **Kubernetes 예제 및 템플릿:**  
  - [Awesome Kubernetes](https://github.com/ramitsurana/awesome-kubernetes)  
  - [Kubernetes Examples](https://github.com/kubernetes/examples)  

---

## ✅ **마무리**
이 문서는 **Kubernetes의 기본 개념을 이해하고 간단한 배포 및 운영 방법을 실습하는 가이드**입니다.  
다음 단계로 **고급 개념(Advanced)에서 네트워킹, 스토리지 관리 및 클러스터 최적화를 학습할 수 있습니다.** 🚀