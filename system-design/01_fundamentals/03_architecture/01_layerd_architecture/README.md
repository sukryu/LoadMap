# 📂 **03_architecture/layered_architecture/README.md**  
> **목표:**  
> - **레이어드 아키텍처(Layered Architecture)**의 개념과 필요성을 이해한다.  
> - 소프트웨어 시스템을 **계층별로 분리하여 모듈화하고 유지보수성을 높이는 방법**을 익힌다.  
> - 실무에서 **웹 애플리케이션, 엔터프라이즈 시스템 등에서 레이어드 아키텍처를 적용하는 방법**을 학습한다.  

---

## 📌 **디렉토리 구조 및 학습 내용**  
```
layered_architecture/
├── introduction/         # 레이어드 아키텍처 개요
├── presentation_layer/   # 프레젠테이션 계층 (Presentation Layer)
├── application_layer/    # 애플리케이션 계층 (Application Layer)
├── domain_layer/         # 도메인 계층 (Domain Layer)
├── infrastructure_layer/ # 인프라스트럭처 계층 (Infrastructure Layer)
├── pros_and_cons/        # 장점과 단점
└── real_world_examples/  # 실전 사례 분석
```

---

## 🏛 **1. 레이어드 아키텍처 개요 (introduction/)**  
> **소프트웨어 시스템을 여러 계층으로 나누어 설계하는 아키텍처 패턴**  

### 📚 학습 내용  
- **Layered Architecture 개념 및 필요성**  
  - 시스템을 계층별로 분리하여 **모듈화와 유지보수성**을 높이는 방법  
  - 실무 적용: **대규모 엔터프라이즈 애플리케이션 및 마이크로서비스 설계**  

- **레이어드 아키텍처의 주요 원칙**  
  - **Separation of Concerns (관심사 분리)**  
  - **Dependency Rule (의존성 규칙)**  
  - **Loose Coupling (느슨한 결합)과 High Cohesion (높은 응집도)**  

- **레이어드 아키텍처의 일반적인 구성**  
  - 프레젠테이션 계층 (Presentation Layer)  
  - 애플리케이션 계층 (Application Layer)  
  - 도메인 계층 (Domain Layer)  
  - 인프라스트럭처 계층 (Infrastructure Layer)  

> 📍 자세한 내용은 `introduction/README.md` 참고  

---

## 🎨 **2. 프레젠테이션 계층 (Presentation Layer) (presentation_layer/)**  
> **사용자 인터페이스 및 요청 처리를 담당하는 계층**  

### 📚 학습 내용  
- **Presentation Layer의 역할**  
  - UI 및 API 요청을 처리하는 역할  
  - 실무 적용: **웹 프레임워크(React, Angular, Vue) 및 REST API 컨트롤러(Spring, Express, Flask)**  

- **MVC(Model-View-Controller) 패턴 적용**  
  - Model: 데이터 처리  
  - View: 사용자 인터페이스  
  - Controller: 요청을 받고 응답을 반환  

- **RESTful API 및 GraphQL API에서의 역할**  
  - 실무 적용: **Express.js, Django, Spring MVC에서의 컨트롤러 역할 분석**  

> 📍 자세한 내용은 `presentation_layer/README.md` 참고  

---

## ⚙ **3. 애플리케이션 계층 (Application Layer) (application_layer/)**  
> **비즈니스 로직과 유스케이스를 담당하는 계층**  

### 📚 학습 내용  
- **Application Layer의 역할**  
  - 비즈니스 로직을 처리하고, 다른 계층과 상호작용하는 역할  
  - 실무 적용: **Service 클래스와 Use Case 패턴 적용 방식**  

- **Transaction Management 및 이벤트 처리**  
  - 트랜잭션을 유지하면서 여러 서비스 호출을 조정하는 방법  
  - 실무 적용: **CQRS(Command Query Responsibility Segregation) 패턴과의 관계**  

- **서비스 계층에서의 의존성 관리**  
  - DIP(Dependency Inversion Principle) 적용  
  - 실무 적용: **Spring Service, NestJS Provider 패턴 활용**  

> 📍 자세한 내용은 `application_layer/README.md` 참고  

---

## 📦 **4. 도메인 계층 (Domain Layer) (domain_layer/)**  
> **핵심 비즈니스 로직과 엔티티(Entity)를 담당하는 계층**  

### 📚 학습 내용  
- **Domain Layer의 역할**  
  - 애플리케이션의 핵심 비즈니스 규칙을 담당하는 계층  
  - 실무 적용: **DDD(Domain-Driven Design)에서의 Aggregate Root 설계**  

- **Entity vs Value Object vs Aggregate**  
  - 실무 적용: **유저, 주문, 결제 시스템 모델링 사례 분석**  

- **도메인 계층에서의 데이터 변환 및 검증**  
  - 실무 적용: **Python의 Pydantic, Java의 Hibernate Validator 활용 사례**  

> 📍 자세한 내용은 `domain_layer/README.md` 참고  

---

## 🏗 **5. 인프라스트럭처 계층 (Infrastructure Layer) (infrastructure_layer/)**  
> **데이터베이스, 외부 API, 로깅, 메시징 등을 담당하는 계층**  

### 📚 학습 내용  
- **Infrastructure Layer의 역할**  
  - 데이터 저장, 네트워크 통신, 캐싱, 메시징 시스템과의 상호작용 담당  
  - 실무 적용: **MySQL, PostgreSQL, Redis, RabbitMQ, Kafka 활용 사례**  

- **Repository 패턴 적용**  
  - 데이터 액세스를 추상화하여 유연성 제공  
  - 실무 적용: **Spring Data JPA, TypeORM, Prisma 활용 사례**  

- **인프라 계층과의 의존성 최소화**  
  - DIP(의존성 역전 원칙) 적용  
  - 실무 적용: **Cloud Storage(AWS S3, GCP Storage)와의 연결 최적화**  

> 📍 자세한 내용은 `infrastructure_layer/README.md` 참고  

---

## ⚖ **6. 레이어드 아키텍처의 장점과 단점 (pros_and_cons/)**  
> **각 계층을 나누어 설계하는 것이 항상 좋은 선택은 아니다.**  

### 📚 학습 내용  
- **장점**  
  - 유지보수성 증가  
  - 역할 분리로 코드 가독성 향상  
  - 테스트 용이  

- **단점**  
  - 성능 오버헤드 (각 계층을 거치는 추가 비용)  
  - 계층 간 의존성이 많아질 경우 변경이 어렵다  
  - 지나친 분리로 인해 복잡성이 증가할 수 있음  

- **레이어드 아키텍처가 적절한 경우와 그렇지 않은 경우**  
  - 실무 적용: **스타트업 초기 단계 vs 대규모 엔터프라이즈 시스템**  

> 📍 자세한 내용은 `pros_and_cons/README.md` 참고  

---

## 🚀 **7. 실전 사례 분석 (real_world_examples/)**  
> **실제 기업들의 아키텍처 설계를 분석하고, 장점과 단점을 학습한다.**  

### 📚 학습 내용  
- **Netflix의 MSA 및 API Gateway 활용 사례**  
- **Uber의 계층적 설계 및 Geo-Partitioning 적용 방식**  
- **Amazon의 주문 처리 시스템에서의 레이어드 아키텍처 적용 사례**  
- **Google의 SRE 원칙이 레이어드 아키텍처에 미친 영향 분석**  

> 📍 자세한 내용은 `real_world_examples/README.md` 참고  

---

## 🔍 **학습 방법**  
1. **레이어드 아키텍처의 개념을 학습한다.**  
2. **각 계층의 역할과 설계 원칙을 분석한다.**  
3. **실무 사례를 통해 적용 방식을 익힌다.**  
4. **적절한 프로젝트에서 레이어드 아키텍처를 실습한다.**  

---

## 📚 **추천 학습 리소스**  
- **"Clean Architecture" - Robert C. Martin**  
- **"Patterns of Enterprise Application Architecture" - Martin Fowler**  
- **Spring Framework 및 NestJS의 계층적 설계 문서**  

---

## ✅ **마무리**  
이 디렉토리는 **레이어드 아키텍처를 배우고, 실무에서 유지보수성이 뛰어난 시스템을 설계하는 방법을 익히기 위한 공간**입니다.  
각 계층의 역할을 **실제 프로젝트에서 어떻게 적용할지 고민하며 학습하는 것이 중요합니다.** 🚀  

```

이제 다음 단계로 넘어갈까요? 😊