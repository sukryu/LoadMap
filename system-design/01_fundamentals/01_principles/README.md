# 📂 **01_fundamentals/principles (설계 원칙)**
> **목표:**  
> - 시스템 설계에서 필수적으로 알아야 하는 원칙을 익힌다.  
> - 각 원칙이 **어떤 문제를 해결하는지** 실무 사례와 함께 이해한다.  
> - 원칙을 적용하여 **올바른 설계를 결정하는 방법**을 배운다.

---

## 📌 **디렉토리 구조 및 학습 내용**
```
principles/
├── solid/                   # SOLID 원칙
├── design_principles/       # 일반적인 설계 원칙
├── scalability_principles/  # 확장성을 고려한 설계 원칙
├── maintainability/         # 유지보수성과 관련된 원칙
└── real_world_examples/     # 실전 사례 분석
```

---

## 🏗️ **1. SOLID 원칙 (solid/)**
> 개념 설명 → 예제 코드 → 실무 적용 사례  
✅ 객체지향 설계를 기반으로 한 **유지보수성 높은 시스템 구축** 방법

### 📖 학습 내용
- **SRP (Single Responsibility Principle) - 단일 책임 원칙**
  - 하나의 클래스는 단 하나의 기능만 가져야 한다.
  - 예제: `사용자 관리(UserService)` vs `이메일 발송(EmailService)`
  - 실무 적용: **모놀리식 구조 → 마이크로서비스 전환 시 역할 분리**
  
- **OCP (Open-Closed Principle) - 개방-폐쇄 원칙**
  - 기존 코드를 변경하지 않고 확장이 가능해야 한다.
  - 예제: `추가적인 결제 수단 지원 (Strategy 패턴)`
  - 실무 적용: **결제 시스템, API 버전 관리 등**
  
- **LSP (Liskov Substitution Principle) - 리스코프 치환 원칙**
  - 하위 클래스가 상위 클래스를 대체해도 프로그램이 정상 동작해야 한다.
  - 예제: `사각형 vs 정사각형 문제 (Rectangle-Square Problem)`
  - 실무 적용: **REST API 확장 시 기존 인터페이스 호환 유지**
  
- **ISP (Interface Segregation Principle) - 인터페이스 분리 원칙**
  - 하나의 인터페이스가 너무 많은 기능을 포함하면 안 된다.
  - 예제: `UserService → AuthService, ProfileService 분리`
  - 실무 적용: **API 설계 시 지나치게 거대한 인터페이스 피하기**
  
- **DIP (Dependency Inversion Principle) - 의존성 역전 원칙**
  - 상위 모듈이 하위 모듈에 의존하지 않도록 한다.
  - 예제: `DB 접근을 직접 하지 않고 Repository 패턴 사용`
  - 실무 적용: **DI(Dependency Injection)와 IoC 컨테이너 활용**

---

## 🎯 **2. 일반적인 설계 원칙 (design_principles/)**
> SOLID 외에도 시스템 설계를 할 때 고려해야 할 **일반적인 설계 원칙**

### 📖 학습 내용
- **DRY (Don't Repeat Yourself) - 중복을 최소화하라**
  - 코드, 데이터베이스, API에서 중복이 있으면 유지보수가 어렵다.
  - 실무 적용: **공통 유틸리티 모듈 작성, API 공통 응답 포맷 설계**

- **KISS (Keep It Simple, Stupid) - 단순하게 설계하라**
  - 지나치게 복잡한 설계는 유지보수성을 떨어뜨린다.
  - 실무 적용: **너무 깊은 계층 구조 지양, 간단한 인터페이스 유지**

- **YAGNI (You Aren't Gonna Need It) - 필요할 때만 구현하라**
  - 미래의 필요를 예상해서 코드를 작성하는 것은 시간 낭비다.
  - 실무 적용: **"나중에 필요할 것 같아서"라는 이유로 기능 추가 금지**

- **Separation of Concerns (관심사 분리)**
  - 한 가지 역할만 담당하는 모듈을 만들어 유지보수성을 높인다.
  - 실무 적용: **MVC 패턴, MSA(Service 분리) 적용**

- **Fail Fast (빠른 실패)**
  - 문제가 발생하면 가능한 빨리 감지하고 처리해야 한다.
  - 실무 적용: **API 요청 검증, 예외 처리 로직 명확하게 작성**

---

## 📊 **3. 확장성을 고려한 설계 원칙 (scalability_principles/)**
> 대규모 트래픽을 처리할 수 있도록 **확장 가능한 시스템**을 설계하는 방법

### 📖 학습 내용
- **Horizontal Scaling vs. Vertical Scaling (수평 확장 vs. 수직 확장)**
  - 실무 적용: **마이크로서비스 분리, 로드 밸런싱 적용**
  
- **Stateless Design (무상태 설계)**
  - 서버가 상태를 관리하지 않도록 설계해야 확장성이 좋아진다.
  - 실무 적용: **JWT 기반 인증, 세션 클러스터링**

- **Asynchronous Processing (비동기 처리)**
  - 실무 적용: **메시지 큐(Kafka, RabbitMQ) 활용**

- **Data Sharding & Partitioning (데이터 샤딩 및 파티셔닝)**
  - 실무 적용: **사용자 데이터 분산 저장 (ex. MySQL 샤딩)**

- **Caching Strategy (캐싱 전략)**
  - 실무 적용: **Redis, CDN을 활용한 성능 최적화**

---

## 🛠️ **4. 유지보수성을 고려한 원칙 (maintainability/)**
> 코드가 **쉽게 변경될 수 있도록 설계**하는 원칙

### 📖 학습 내용
- **Modularity (모듈화)**
  - 기능별로 모듈을 나누어 독립적으로 관리 가능하도록 한다.
  - 실무 적용: **레거시 코드 리팩토링 시 모듈화 진행**

- **Code Readability (코드 가독성)**
  - 실무 적용: **Clean Code 원칙 적용 (의미 있는 변수명 사용)**

- **Backward Compatibility (하위 호환성 유지)**
  - 실무 적용: **API 버전 관리 (ex. v1, v2 API)**

---

## 📌 **5. 실전 사례 분석 (real_world_examples/)**
> 실제 프로젝트에서 위 원칙들을 어떻게 적용하는지 살펴본다.

### 📖 학습 내용
- **Netflix의 MSA 전환 사례**
- **Uber의 확장성 문제 해결 방법**
- **AWS Lambda를 활용한 서버리스 아키텍처**
- **마이크로서비스 설계에서 SOLID 원칙 적용 예제**
- **REST API vs GraphQL 설계 트레이드오프**