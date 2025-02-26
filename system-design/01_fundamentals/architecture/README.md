# 📂 아키텍처 스타일 - architecture

> **목표:**  
> - 다양한 소프트웨어 아키텍처 스타일을 학습하고 실무에서 활용할 수 있도록 한다.  
> - 모놀리식, 마이크로서비스, 클린 아키텍처 등 다양한 아키텍처의 원리와 적용 방법을 이해한다.  
> - 확장성과 유지보수성을 고려한 최적의 아키텍처 설계를 연구한다.

---

## 📌 **디렉토리 구조**
```
architecture/                  # 아키텍처 스타일
├── monolithic.md              # 모놀리식 아키텍처
├── microservices.md           # 마이크로서비스 아키텍처
├── event_driven.md            # 이벤트 기반 아키텍처
├── layered.md                 # 레이어드 아키텍처
├── hexagonal.md               # 헥사고날 아키텍처
├── clean.md                   # 클린 아키텍처
├── serverless.md              # 서버리스 아키텍처
└── README.md
```

---

## 📖 **1. 개념 개요**
> **아키텍처 스타일은 소프트웨어 시스템의 구조를 정의하고, 유지보수성과 확장성을 높이기 위한 설계 방식이다.**

- ✅ **왜 중요한가?**  
  - 소프트웨어의 유지보수성과 확장성에 직접적인 영향을 미친다.
  - 요구사항 변화에 유연하게 대응할 수 있도록 설계를 최적화한다.
  - 성능, 비용, 개발 속도를 고려한 적절한 아키텍처 선택이 필요하다.

- ✅ **어떤 문제를 해결하는가?**  
  - 코드 복잡성을 줄이고 모듈화된 설계를 제공
  - 서비스 간의 독립성을 유지하면서 확장 가능한 구조 설계
  - 변경 사항을 최소한의 영향으로 반영할 수 있도록 구조화

- ✅ **실무에서 어떻게 적용하는가?**  
  - 모놀리식 아키텍처를 활용한 초기 스타트업 제품 개발
  - 마이크로서비스 아키텍처로 시스템을 분할하여 확장성 극대화
  - 이벤트 기반 아키텍처를 통해 비동기 데이터 흐름 관리
  - 서버리스 아키텍처로 비용 최적화 및 운영 부담 감소

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **모놀리식 아키텍처 (monolithic.md)**
  - 단일 코드베이스로 구성된 애플리케이션 아키텍처
  - 빠른 개발 속도를 위한 간단한 설계 방식
  - 배포 및 확장성의 한계를 고려한 전환 전략

- **마이크로서비스 아키텍처 (microservices.md)**
  - 독립적인 서비스 단위로 구성된 분산 아키텍처
  - 서비스 간 통신 방식 (REST, gRPC, 메시지 브로커 활용)
  - 데이터 관리 및 트랜잭션 처리 전략

- **이벤트 기반 아키텍처 (event_driven.md)**
  - 비동기 이벤트 흐름을 활용한 아키텍처 스타일
  - Kafka, RabbitMQ 등을 활용한 메시지 중심 시스템 설계
  - 이벤트 소싱 및 CQRS 패턴 적용 사례

- **레이어드 아키텍처 (layered.md)**
  - UI, 비즈니스 로직, 데이터 액세스 레이어로 나뉜 구조
  - 전통적인 엔터프라이즈 애플리케이션에서 널리 사용됨
  - 의존성 관리 및 테스트 용이성 확보

- **헥사고날 아키텍처 (hexagonal.md)**
  - 내부 도메인 로직과 외부 인터페이스를 분리하는 설계 패턴
  - 애플리케이션의 유연성과 확장성을 높이는 구조
  - 포트와 어댑터 패턴을 활용한 인터페이스 설계

- **클린 아키텍처 (clean.md)**
  - 엔터프라이즈 시스템에서 유지보수성을 극대화하는 구조
  - 의존성 역전을 통한 독립적인 비즈니스 로직 구성
  - 도메인 중심 설계와의 연계

- **서버리스 아키텍처 (serverless.md)**
  - 서버 관리 없이 클라우드 환경에서 실행되는 애플리케이션 구조
  - AWS Lambda, Google Cloud Functions 등을 활용한 설계
  - 비용 최적화 및 확장성 극대화 전략

---

## 🚀 **3. 실전 사례 분석**
> **대규모 시스템에서 아키텍처 스타일이 어떻게 활용되는가?**

- **Netflix** - 마이크로서비스 아키텍처 기반의 확장형 스트리밍 서비스
- **Amazon** - 이벤트 기반 아키텍처를 통한 주문 처리 시스템
- **Uber** - 헥사고날 아키텍처를 활용한 독립적 서비스 관리
- **Google Cloud Functions** - 서버리스 아키텍처를 활용한 비용 최적화 서비스

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ 각 아키텍처별 코드 작성 및 실습  
3️⃣ 실제 사례 분석  
4️⃣ 아키텍처 비교 및 트레이드오프 분석  

---

## 📚 **5. 추천 리소스**
- 📖 _Software Architecture in Practice_ - Len Bass  
- 📖 _Building Microservices_ - Sam Newman  
- 📖 _Clean Architecture_ - Robert C. Martin  
- 📌 [Awesome Architecture](https://github.com/davideuler/awesome-software-architecture)  
- 📌 [Microservices.io](https://microservices.io/)  

---

## ✅ **마무리**
이 문서는 **아키텍처 스타일의 개념과 실무 적용 방법을 학습하는 단계**입니다.
이론 → 아키텍처 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며,
각 상황에 적합한 아키텍처를 선택하고 설계할 수 있도록 합니다. 🚀