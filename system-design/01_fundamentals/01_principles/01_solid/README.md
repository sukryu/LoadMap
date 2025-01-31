# 📂 **01_fundamentals/principles/solid/**  
> **목표:**  
> - SOLID 원칙의 개념과 중요성을 이해한다.  
> - 각 원칙이 어떤 문제를 해결하는지 학습하고, 실제 코드 예제와 함께 익힌다.  
> - 실무에서 SOLID 원칙을 적용하는 방법을 익혀 **유지보수성이 높은 시스템을 설계**한다.  

---

## 📌 **디렉토리 구조 및 학습 내용**  
```
solid/
├── srp/     # 단일 책임 원칙 (Single Responsibility Principle)
├── ocp/     # 개방-폐쇄 원칙 (Open-Closed Principle)
├── lsp/     # 리스코프 치환 원칙 (Liskov Substitution Principle)
├── isp/     # 인터페이스 분리 원칙 (Interface Segregation Principle)
└── dip/     # 의존성 역전 원칙 (Dependency Inversion Principle)
```

---

## 🏗️ **1. 단일 책임 원칙 (Single Responsibility Principle, SRP) (srp/)**  
> **각 클래스(또는 모듈)는 단 하나의 책임만 가져야 한다.**  

### 📚 학습 내용  
- **SRP 개념 및 중요성**  
  - 하나의 클래스가 하나의 기능만 담당해야 하는 이유  
  - 실무 적용: **UserService와 EmailService를 분리하는 사례**  

- **위반 사례 분석**  
  - 한 클래스에서 너무 많은 역할을 수행하는 문제  
  - 실무 적용: **데이터 처리 + 로깅 + 네트워크 요청이 한 클래스에서 동작하는 문제 해결**  

- **SOLID 원칙을 적용한 개선 코드 예제**  
  - 기존 코드 vs 개선된 코드 비교  

> 📍 자세한 내용은 `srp/README.md` 참고  

---

## 🔄 **2. 개방-폐쇄 원칙 (Open-Closed Principle, OCP) (ocp/)**  
> **코드는 확장에는 열려 있고, 변경에는 닫혀 있어야 한다.**  

### 📚 학습 내용  
- **OCP 개념 및 필요성**  
  - 기존 코드를 변경하지 않고 새로운 기능을 추가하는 방법  
  - 실무 적용: **결제 시스템에서 결제 방식(카드, 페이팔, 암호화폐 등) 추가하기**  

- **위반 사례 분석**  
  - 새로운 기능 추가 시 기존 코드를 수정해야 하는 문제  
  - 실무 적용: **if-else 문이 많은 코드 개선하기**  

- **SOLID 원칙을 적용한 개선 코드 예제**  
  - 전략 패턴(Strategy Pattern)을 활용한 OCP 적용 방법  

> 📍 자세한 내용은 `ocp/README.md` 참고  

---

## 🔀 **3. 리스코프 치환 원칙 (Liskov Substitution Principle, LSP) (lsp/)**  
> **자식 클래스는 언제나 부모 클래스를 대체할 수 있어야 한다.**  

### 📚 학습 내용  
- **LSP 개념 및 필요성**  
  - 상속 관계에서 부모 클래스의 기능을 자식 클래스가 올바르게 유지해야 하는 이유  
  - 실무 적용: **Rectangle-Square 문제 해결하기**  

- **위반 사례 분석**  
  - 부모 클래스가 제공하는 기능을 자식 클래스가 올바르게 지원하지 않는 경우  
  - 실무 적용: **REST API 확장 시 기존 인터페이스를 깨뜨리는 문제 해결**  

- **SOLID 원칙을 적용한 개선 코드 예제**  
  - 상속 대신 **컴포지션(Composition) 활용하기**  

> 📍 자세한 내용은 `lsp/README.md` 참고  

---

## 📜 **4. 인터페이스 분리 원칙 (Interface Segregation Principle, ISP) (isp/)**  
> **하나의 거대한 인터페이스보다 여러 개의 작은 인터페이스를 만들어야 한다.**  

### 📚 학습 내용  
- **ISP 개념 및 필요성**  
  - 클라이언트가 자신이 사용하지 않는 기능에 의존하지 않도록 설계하는 방법  
  - 실무 적용: **REST API 설계에서 너무 많은 기능을 가진 API 피하기**  

- **위반 사례 분석**  
  - 단일 인터페이스가 너무 많은 역할을 하는 문제  
  - 실무 적용: **UserService를 AuthService와 ProfileService로 분리하기**  

- **SOLID 원칙을 적용한 개선 코드 예제**  
  - 역할별로 인터페이스를 분리하는 방식  

> 📍 자세한 내용은 `isp/README.md` 참고  

---

## 🏛️ **5. 의존성 역전 원칙 (Dependency Inversion Principle, DIP) (dip/)**  
> **상위 모듈(고수준 모듈)은 하위 모듈(저수준 모듈)에 의존하지 않아야 한다.**  

### 📚 학습 내용  
- **DIP 개념 및 필요성**  
  - 유연하고 테스트 가능한 코드를 만들기 위한 원칙  
  - 실무 적용: **데이터베이스 접근을 직접 하지 않고, Repository 패턴 사용하기**  

- **위반 사례 분석**  
  - 특정 구현 클래스에 직접 의존하여 코드 변경이 어려운 문제  
  - 실무 적용: **DI(Dependency Injection)와 IoC 컨테이너 활용하기**  

- **SOLID 원칙을 적용한 개선 코드 예제**  
  - 인터페이스를 활용하여 느슨한 결합(Loose Coupling) 유지하기  

> 📍 자세한 내용은 `dip/README.md` 참고  

---

## 🔍 **학습 방법**  
1. **각 SOLID 원칙의 개념을 이론적으로 학습한다.**  
2. **실제 개발에서 발생하는 문제 사례를 분석한다.**  
3. **SOLID 원칙을 적용한 개선 코드 예제를 작성한다.**  
4. **각 원칙을 실무에서 어떻게 적용할지 고민하고, 토론한다.**  

---

## 📚 **추천 학습 리소스**  
- **"Clean Code" - Robert C. Martin**  
- **"The Principles of Object-Oriented JavaScript" - Nicholas C. Zakas**  
- **"Design Patterns: Elements of Reusable Object-Oriented Software" - GoF (Gang of Four)**  
- **SOLID 원칙을 활용한 코드 리팩토링 사례 (GitHub, Medium)**  

---

## ✅ **마무리**  
이 디렉토리는 **SOLID 원칙을 체계적으로 학습하고, 실무에서 유지보수성이 뛰어난 소프트웨어를 개발하기 위한 기반을 다지는 공간**입니다.  
각 원칙이 **어떤 문제를 해결하는지, 왜 중요한지, 실무에서 어떻게 활용하는지 고민하면서 학습하는 것이 중요합니다.** 🚀  