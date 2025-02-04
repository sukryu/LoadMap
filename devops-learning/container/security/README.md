# 📂 Docker Security 학습 개요

> **목표:**  
> - **Docker 컨테이너 보안의 개념과 실무 적용 방법을 학습**한다.  
> - **컨테이너 이미지, 네트워크, 실행 환경의 보안 강화를 익힌다.**  
> - **기본 개념과 도구 활용을 학습한 후, 고급 보안 기법 및 실무 적용 전략을 학습한다.**  
> - **이론 → 도구 실습 → 프로젝트 적용 → 최적화의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **Docker Security 학습을 기본(Basic)과 고급(Advanced)으로 나누어 진행합니다.**  

```
security/
├── trivy.md  # Trivy를 활용한 컨테이너 이미지 보안 검사
└── README.md
```

---

## 📖 **1. 기본 개념 개요**
> **Docker 보안은 컨테이너 환경에서 애플리케이션 및 데이터를 보호하는 핵심 요소입니다.**

- ✅ **이미지 보안:** 취약점 검사 및 신뢰할 수 있는 소스 활용  
- ✅ **컨테이너 실행 보안:** 권한 최소화 및 사용자 권한 관리  
- ✅ **네트워크 보안:** 컨테이너 간 안전한 통신 구성  
- ✅ **호스트 보안:** 컨테이너와 호스트 OS 간 격리 유지  
- ✅ **취약점 검사:** 보안 스캐너를 통한 정기적인 보안 점검  

---

## 🏗 **2. 학습 내용**
### 📌 Container Image Security (컨테이너 이미지 보안)
- **신뢰할 수 있는 공식 이미지 사용하기**
- **Trivy, Clair 등의 취약점 검사 도구 활용**
- **Dockerfile 작성 시 보안 모범 사례 적용**

### 📌 Container Runtime Security (컨테이너 실행 보안)
- **rootless 컨테이너 실행**
- **Linux Capabilities 및 seccomp 설정 활용**
- **Docker AppArmor 및 SELinux 정책 적용**

### 📌 Network Security (네트워크 보안)
- **컨테이너 간 통신 제한 및 네트워크 정책 적용**
- **암호화된 네트워크(overlay network) 구성**
- **Docker Compose 및 Kubernetes에서 네트워크 보안 강화**

### 📌 Host Security (호스트 보안)
- **Docker Daemon의 최소 권한 실행**
- **Docker 그룹 및 사용자 권한 관리**
- **호스트 OS 업데이트 및 보안 패치 적용**

---

## 🚀 **3. 실전 예제**
> **Trivy를 활용한 컨테이너 이미지 취약점 검사**

```sh
# Trivy 설치
sudo apt install trivy

# 컨테이너 이미지 보안 검사
trivy image nginx:latest
```

> **Docker 컨테이너 실행 시 보안 강화 설정 적용**

```sh
# 권한을 제한한 상태로 컨테이너 실행
docker run --rm -it --user 1001 nginx

# seccomp 프로필을 적용하여 컨테이너 실행
docker run --rm -it --security-opt seccomp=default.json nginx
```

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → Docker 보안 개념과 중요성 이해  
2. **도구 실습** → Trivy, AppArmor, Seccomp 등 보안 도구 활용  
3. **프로젝트 적용** → 실제 프로젝트에서 컨테이너 보안 강화  
4. **최적화 연구** → 성능과 보안의 균형 유지  

---

## 📚 **5. 추천 리소스**
- **Docker 보안 공식 문서:**  
  - [Docker Security Docs](https://docs.docker.com/engine/security/)  
  - [CIS Docker Benchmark](https://www.cisecurity.org/benchmark/docker/)  

- **보안 도구 및 예제:**  
  - [Trivy](https://aquasecurity.github.io/trivy/)  
  - [Awesome Docker Security](https://github.com/shieldfy/awesome-docker-security)  

---

## ✅ **마무리**
이 문서는 **Docker Security의 기본 개념부터 실무 활용까지 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 최적화**의 단계로 학습하며, **실무에서 Docker 보안을 효과적으로 관리하는 방법**을 다룹니다. 🚀