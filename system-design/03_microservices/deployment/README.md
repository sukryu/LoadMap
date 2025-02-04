# 📂 배포 및 운영 - deployment

> **목표:**  
> - 마이크로서비스 아키텍처에서 배포 및 운영 전략을 학습한다.  
> - CI/CD 파이프라인, Canary Deployment, Blue-Green Deployment 등의 배포 전략을 이해하고 적용한다.  
> - Kubernetes, Docker, 서비스 메쉬를 활용한 마이크로서비스 배포 방법을 연구하고 실무에 적용한다.

---

## 📌 **디렉토리 구조**
```
deployment/                     # 배포 및 운영 학습
├── introduction.md              # 배포 및 운영 개요
├── ci_cd_pipeline.md            # CI/CD 파이프라인 구축
├── containerization.md          # 컨테이너화 및 오케스트레이션
├── blue_green_deployment.md     # 블루-그린 배포 전략
├── canary_deployment.md         # 카나리아 배포 전략
├── rolling_updates.md           # 롤링 업데이트
├── service_mesh.md              # 서비스 메쉬를 활용한 배포 및 운영
├── deployment_in_practice.md    # 실무에서의 배포 및 운영 적용
└── README.md
```

---

## 📖 **1. 개념 개요**
> **마이크로서비스 배포 및 운영은 서비스의 가용성을 유지하면서 새로운 기능을 신속하고 안전하게 배포하는 과정이다.**

- ✅ **왜 중요한가?**  
  - 서비스의 지속적인 변경과 확장을 원활하게 관리할 수 있다.
  - 배포 과정에서 다운타임을 최소화하고 롤백을 쉽게 수행할 수 있다.
  - 안정적인 운영과 자동화를 통해 DevOps 문화와 CI/CD 파이프라인을 최적화할 수 있다.

- ✅ **어떤 문제를 해결하는가?**  
  - 단일 배포로 인해 발생하는 서비스 중단 방지
  - 장애 발생 시 롤백 및 빠른 복구 전략 제공
  - 대규모 트래픽을 대비한 확장성과 안정성 확보

- ✅ **실무에서 어떻게 적용하는가?**  
  - **CI/CD 파이프라인**을 구축하여 자동 배포 및 테스트 수행
  - **컨테이너화 및 오케스트레이션(Kubernetes, Docker)**을 활용하여 운영 최적화
  - **배포 전략(Blue-Green, Canary, Rolling Update)**을 적용하여 안정성 확보

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **배포 및 운영 개요 (introduction.md)**
  - 마이크로서비스 배포의 기본 개념
  - 지속적 배포(Continuous Deployment)와 지속적 전달(Continuous Delivery) 차이

- **CI/CD 파이프라인 구축 (ci_cd_pipeline.md)**
  - GitHub Actions, GitLab CI/CD, Jenkins를 활용한 자동 배포
  - 코드 테스트, 빌드, 배포 자동화

- **컨테이너화 및 오케스트레이션 (containerization.md)**
  - Docker 컨테이너의 역할과 장점
  - Kubernetes를 이용한 마이크로서비스 배포 및 확장

- **블루-그린 배포 전략 (blue_green_deployment.md)**
  - 기존 환경(Blue)과 새로운 환경(Green)을 동시에 운영하여 배포 안정성 확보
  - 롤백이 용이하고 서비스 중단을 최소화하는 방식

- **카나리아 배포 전략 (canary_deployment.md)**
  - 트래픽의 일부를 새로운 버전에 보내어 안정성을 확인하는 방식
  - 점진적 배포 및 성능 모니터링 기법

- **롤링 업데이트 (rolling_updates.md)**
  - 한 번에 일부 노드만 업데이트하여 전체 시스템에 미치는 영향을 최소화
  - Kubernetes Deployment 전략을 활용한 무중단 배포

- **서비스 메쉬를 활용한 배포 및 운영 (service_mesh.md)**
  - Istio, Linkerd와 같은 서비스 메쉬를 활용한 배포 최적화
  - 트래픽 관리, A/B 테스팅, 장애 감지 자동화

- **실무에서의 배포 및 운영 적용 (deployment_in_practice.md)**
  - 기업 환경에서의 배포 전략 사례 연구
  - 클라우드 환경(AWS, Google Cloud, Azure)에서의 배포 자동화
  - 로그 모니터링 및 성능 분석을 통한 운영 최적화

---

## 🚀 **3. 실전 사례 분석**
> **대규모 서비스에서 배포 및 운영 전략이 어떻게 활용되는가?**

- **Netflix** - Spinnaker를 활용한 지속적 배포 및 자동 롤백 시스템
- **Amazon** - AWS CodeDeploy를 이용한 Blue-Green 배포 및 무중단 업데이트
- **Google** - Kubernetes 기반의 Canary Deployment 및 트래픽 관리 적용

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ CI/CD 및 배포 전략 실습  
3️⃣ 실제 사례 연구  
4️⃣ 배포 및 운영 자동화 코드 작성  

---

## 📚 **5. 추천 리소스**
- 📖 _The Phoenix Project_ - Gene Kim  
- 📖 _Kubernetes Up & Running_ - Kelsey Hightower  
- 📖 _Continuous Delivery_ - Jez Humble  
- 📌 [Kubernetes Deployment Strategies](https://kubernetes.io/docs/concepts/workloads/controllers/deployment/)  
- 📌 [GitHub Actions Documentation](https://docs.github.com/en/actions)  

---

## ✅ **마무리**
이 문서는 **마이크로서비스 아키텍처에서 배포 및 운영을 위한 다양한 전략을 학습하는 단계**입니다.
이론 → 배포 방식 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며,
확장성과 안정성을 고려한 최적의 배포 및 운영 방식을 설계할 수 있도록 합니다. 🚀

