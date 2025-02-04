# 📂 서비스 패턴 - service_patterns

> **목표:**  
> - 마이크로서비스 아키텍처에서 서비스 설계를 위한 핵심 패턴을 학습한다.  
> - API Gateway, Backend for Frontend(BFF), 서비스 디스커버리 등의 주요 패턴을 이해하고 적용한다.  
> - 서비스 간 통합 및 관리의 효율성을 극대화하는 패턴을 실무에 적용하는 방법을 연구한다.

---

## 📌 **디렉토리 구조**
```
service_patterns/               # 서비스 패턴 학습
├── introduction.md              # 서비스 패턴 개요
├── api_gateway.md               # API Gateway 패턴
├── backend_for_frontend.md      # Backend for Frontend (BFF) 패턴
├── service_discovery.md         # 서비스 디스커버리 패턴
├── circuit_breaker.md           # Circuit Breaker 패턴
├── sidecar_pattern.md           # 사이드카 패턴
├── service_patterns_in_practice.md  # 실무에서의 서비스 패턴 적용
└── README.md
```

---

## 📖 **1. 개념 개요**
> **서비스 패턴은 마이크로서비스 아키텍처에서 개별 서비스의 관리 및 운영을 최적화하는 설계 기법이다.**

- ✅ **왜 중요한가?**  
  - 서비스 간의 상호작용을 표준화하고 복잡성을 줄일 수 있다.
  - 확장성과 장애 복구 능력을 강화하여 운영 효율성을 높인다.
  - 분산 환경에서 서비스 간 통합을 원활하게 한다.

- ✅ **어떤 문제를 해결하는가?**  
  - 서비스 간 과도한 결합도를 줄이고 유지보수를 용이하게 함
  - 네트워크 장애 및 서비스 실패 시의 복구 전략 제공
  - API 게이트웨이를 통한 클라이언트 요청 관리 및 보안 강화

- ✅ **실무에서 어떻게 적용하는가?**  
  - **API Gateway**를 활용하여 클라이언트 요청을 중앙에서 관리
  - **서비스 디스커버리**를 적용하여 동적으로 서비스 위치를 탐색
  - **Circuit Breaker** 패턴을 활용하여 장애 전파를 방지

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **서비스 패턴 개요 (introduction.md)**
  - 마이크로서비스 설계에서 서비스 패턴이 필요한 이유
  - 주요 서비스 패턴 개요 및 분류

- **API Gateway 패턴 (api_gateway.md)**
  - API 요청을 중앙에서 관리하고 라우팅하는 패턴
  - 요청/응답 최적화 및 보안 필터링 역할
  - 실무 적용 사례 (Kong, Nginx, AWS API Gateway)

- **Backend for Frontend(BFF) 패턴 (backend_for_frontend.md)**
  - 각 프론트엔드 별 맞춤형 백엔드 서비스 제공
  - 단일 API Gateway의 단점 보완 및 성능 최적화
  - Netflix 및 Spotify에서의 적용 사례

- **서비스 디스커버리 패턴 (service_discovery.md)**
  - 동적으로 서비스의 위치를 탐색하는 기법
  - 클라이언트-사이드 vs 서버-사이드 서비스 디스커버리 비교
  - Consul, Eureka, Kubernetes DNS를 활용한 구현

- **Circuit Breaker 패턴 (circuit_breaker.md)**
  - 장애가 발생한 서비스를 자동으로 감지하고 요청 차단
  - 장애 전파 방지 및 자동 복구 메커니즘
  - Netflix Hystrix 및 Resilience4j를 활용한 구현

- **사이드카 패턴 (sidecar_pattern.md)**
  - 보안, 로깅, 모니터링 기능을 개별 서비스에 부가하는 패턴
  - 서비스가 변경 없이 추가 기능을 확장할 수 있음
  - Istio, Envoy Proxy를 활용한 마이크로서비스 적용 사례

- **실무에서의 서비스 패턴 적용 (service_patterns_in_practice.md)**
  - 마이크로서비스에서 각 패턴을 조합하여 설계하는 방법
  - 트레이드오프 및 패턴 선택 기준
  - 사례 분석 및 코드 예제

---

## 🚀 **3. 실전 사례 분석**
> **대규모 시스템에서 서비스 패턴이 어떻게 활용되는가?**

- **Netflix** - API Gateway 및 Circuit Breaker를 활용한 장애 대응 전략
- **Uber** - 서비스 디스커버리를 통한 동적 스케일링 적용
- **Airbnb** - BFF 패턴을 적용하여 프론트엔드 맞춤형 API 제공

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ 서비스 패턴별 코드 실습  
3️⃣ 실제 사례 분석  
4️⃣ 마이크로서비스 설계 실습 및 트레이드오프 분석  

---

## 📚 **5. 추천 리소스**
- 📖 _Building Microservices_ - Sam Newman  
- 📖 _Microservices Patterns_ - Chris Richardson  
- 📖 _Cloud Native Patterns_ - Cornelia Davis  
- 📌 [Microservices.io Patterns](https://microservices.io/)  
- 📌 [Awesome Microservices](https://github.com/mfornos/awesome-microservices)  

---

## ✅ **마무리**
이 문서는 **마이크로서비스 아키텍처에서 서비스 설계를 위한 핵심 패턴을 학습하는 단계**입니다.
이론 → 패턴 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며,
확장성과 유지보수성을 고려한 최적의 마이크로서비스 패턴을 설계할 수 있도록 합니다. 🚀

