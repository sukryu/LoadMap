# 📂 **01_fundamentals/patterns/creational/README.md**  
> **목표:**  
> - **객체를 생성하는 다양한 패턴(Creational Patterns)**을 학습한다.  
> - 객체 생성 로직을 **효율적이고 유연하게 설계하는 방법**을 익힌다.  
> - 실무에서 **코드 재사용성을 높이고 유지보수성을 개선하는 디자인 패턴**을 적용한다.  

---

## 📌 **디렉토리 구조 및 학습 내용**  
```
creational/
├── factory_method/       # 팩토리 메서드 패턴 (Factory Method)
├── abstract_factory/     # 추상 팩토리 패턴 (Abstract Factory)
├── builder/             # 빌더 패턴 (Builder)
├── prototype/           # 프로토타입 패턴 (Prototype)
└── singleton/           # 싱글턴 패턴 (Singleton)
```

---

## 🏭 **1. 팩토리 메서드 패턴 (Factory Method) (factory_method/)**  
> **객체 생성을 캡슐화하여 유연성을 높이는 패턴**  

### 📚 학습 내용  
- **Factory Method 개념 및 필요성**  
  - 객체 생성을 직접 하지 않고, 서브클래스에서 구현하도록 하는 방식  
  - 실무 적용: **데이터베이스 커넥션, 로깅 프레임워크 등**  

- **위반 사례 분석**  
  - 객체를 직접 생성하는 코드의 문제점  
  - 실무 적용: **객체 생성을 인터페이스화하여 코드 변경 최소화**  

- **Factory Method 적용 방법**  
  - **다형성을 활용한 객체 생성 관리**  
  - **Spring의 Bean Factory 예제**  

> 📍 자세한 내용은 `factory_method/README.md` 참고  

---

## 🏗️ **2. 추상 팩토리 패턴 (Abstract Factory) (abstract_factory/)**  
> **관련된 객체들을 그룹으로 생성하는 패턴**  

### 📚 학습 내용  
- **Abstract Factory 개념 및 필요성**  
  - 여러 관련 객체를 하나의 팩토리에서 생성하는 방법  
  - 실무 적용: **UI 테마(다크 모드, 라이트 모드) 설정**  

- **위반 사례 분석**  
  - 서로 다른 객체 생성을 위한 코드 중복 문제  
  - 실무 적용: **데이터베이스 드라이버 선택(Java JDBC, ORM 등)**  

- **Abstract Factory 적용 방법**  
  - **팩토리 인터페이스를 활용한 다양한 제품군 생성**  
  - **의존성 주입(DI)과 함께 사용하는 방법**  

> 📍 자세한 내용은 `abstract_factory/README.md` 참고  

---

## 🏗️ **3. 빌더 패턴 (Builder) (builder/)**  
> **복잡한 객체 생성을 유연하게 처리하는 패턴**  

### 📚 학습 내용  
- **Builder Pattern 개념 및 필요성**  
  - 생성자 인자가 많을 때 가독성을 높이는 방법  
  - 실무 적용: **JSON 객체, SQL 쿼리 빌더, HTTP 요청 생성 등**  

- **위반 사례 분석**  
  - 생성자의 매개변수가 너무 많아지는 문제  
  - 실무 적용: **객체 생성 과정을 단계적으로 분리하여 가독성 향상**  

- **Builder Pattern 적용 방법**  
  - **체이닝(Chaining) 기법을 활용한 빌더 구현**  
  - **Lombok @Builder 어노테이션을 활용한 간소화**  

> 📍 자세한 내용은 `builder/README.md` 참고  

---

## 🌀 **4. 프로토타입 패턴 (Prototype) (prototype/)**  
> **객체를 복사하여 생성하는 패턴**  

### 📚 학습 내용  
- **Prototype Pattern 개념 및 필요성**  
  - 기존 객체를 복사하여 새로운 객체를 생성하는 방법  
  - 실무 적용: **게임 엔진에서 오브젝트 복제, 문서 편집기 템플릿 기능**  

- **위반 사례 분석**  
  - new 키워드를 사용한 직접 객체 생성의 문제점  
  - 실무 적용: **메모리 최적화 및 객체 복제 속도 향상**  

- **Prototype Pattern 적용 방법**  
  - **Deep Copy vs Shallow Copy 개념 정리**  
  - **Cloneable 인터페이스를 활용한 객체 복제**  

> 📍 자세한 내용은 `prototype/README.md` 참고  

---

## 🔄 **5. 싱글턴 패턴 (Singleton) (singleton/)**  
> **전역에서 하나의 인스턴스만 유지하는 패턴**  

### 📚 학습 내용  
- **Singleton Pattern 개념 및 필요성**  
  - 애플리케이션에서 단 하나의 인스턴스만 존재해야 하는 경우  
  - 실무 적용: **데이터베이스 연결 풀, 로깅 시스템, 설정 관리 객체**  

- **위반 사례 분석**  
  - 여러 인스턴스가 생성될 경우 발생하는 문제점  
  - 실무 적용: **멀티스레드 환경에서 싱글턴을 안전하게 구현하는 방법**  

- **Singleton Pattern 적용 방법**  
  - **Lazy Initialization vs Eager Initialization**  
  - **Thread-safe Singleton 구현 방법 (Double-Checked Locking)**  
  - **Spring의 Singleton Scope 활용**  

> 📍 자세한 내용은 `singleton/README.md` 참고  

---

## 🔍 **학습 방법**  
1. **각 생성 패턴의 개념을 학습한다.**  
2. **위반 사례를 분석하여 실무에서 발생하는 문제를 이해한다.**  
3. **개선된 코드 예제를 통해 패턴을 적용하는 방법을 익힌다.**  
4. **실제 프로젝트에서 적절한 패턴을 선택하고 적용해 본다.**  

---

## 📚 **추천 학습 리소스**  
- **"Design Patterns: Elements of Reusable Object-Oriented Software" - GoF (Gang of Four)**  
- **"Head First Design Patterns" - Eric Freeman & Elisabeth Robson**  
- **"Refactoring: Improving the Design of Existing Code" - Martin Fowler**  
- **Spring Framework의 Bean Factory 및 Singleton 적용 사례**  

---

## ✅ **마무리**  
이 디렉토리는 **객체 생성과 관련된 다양한 디자인 패턴을 배우고, 실무에서 유지보수성이 뛰어난 코드를 작성하는 방법을 익히기 위한 공간**입니다.  
각 패턴이 **어떤 문제를 해결하는지, 왜 중요한지, 실무에서 어떻게 활용하는지 고민하면서 학습하는 것이 중요합니다.** 🚀  