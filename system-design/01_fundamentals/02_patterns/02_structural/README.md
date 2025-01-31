# 📂 **01_fundamentals/patterns/structural/README.md**  
> **목표:**  
> - **객체 및 클래스의 구조를 효율적으로 설계하는 다양한 패턴(Structural Patterns)**을 학습한다.  
> - 코드의 **유지보수성과 확장성을 높이는 설계 기법**을 익힌다.  
> - 실무에서 **객체 간 관계를 최적화하고, 재사용성을 높이는 방법**을 적용한다.  

---

## 📌 **디렉토리 구조 및 학습 내용**  
```
structural/
├── adapter/          # 어댑터 패턴 (Adapter)
├── bridge/           # 브리지 패턴 (Bridge)
├── composite/        # 컴포지트 패턴 (Composite)
├── decorator/        # 데코레이터 패턴 (Decorator)
├── facade/           # 퍼사드 패턴 (Facade)
├── flyweight/        # 플라이웨이트 패턴 (Flyweight)
└── proxy/            # 프록시 패턴 (Proxy)
```

---

## 🔌 **1. 어댑터 패턴 (Adapter) (adapter/)**  
> **서로 다른 인터페이스를 연결하여 호환성을 높이는 패턴**  

### 📚 학습 내용  
- **Adapter Pattern 개념 및 필요성**  
  - 기존 코드와 새로운 코드 간의 호환성을 제공  
  - 실무 적용: **레거시 시스템과 최신 API 연동**  

- **위반 사례 분석**  
  - 직접적인 코드 변경 없이 외부 시스템과 연동할 때 발생하는 문제  
  - 실무 적용: **Java에서 기존 JDBC와 새로운 ORM 시스템을 연결하는 방법**  

- **Adapter Pattern 적용 방법**  
  - **클래스 기반 Adapter vs 객체 기반 Adapter 비교**  
  - **API Gateway에서 JSON 변환 및 통합 방식**  

> 📍 자세한 내용은 `adapter/README.md` 참고  

---

## 🌉 **2. 브리지 패턴 (Bridge) (bridge/)**  
> **추상화와 구현을 분리하여 독립적으로 확장할 수 있도록 하는 패턴**  

### 📚 학습 내용  
- **Bridge Pattern 개념 및 필요성**  
  - 클래스 계층을 독립적으로 확장할 수 있도록 분리하는 방식  
  - 실무 적용: **GUI 컴포넌트 렌더링 엔진 분리**  

- **위반 사례 분석**  
  - 다중 상속으로 인해 발생하는 유지보수 문제  
  - 실무 적용: **OS별 UI 렌더링 방식 분리 (Windows, Mac, Linux)**  

- **Bridge Pattern 적용 방법**  
  - **인터페이스 기반 분리 설계**  
  - **운영체제 별 드라이버 설계 사례 분석**  

> 📍 자세한 내용은 `bridge/README.md` 참고  

---

## 🌲 **3. 컴포지트 패턴 (Composite) (composite/)**  
> **객체를 트리 구조로 구성하여 계층적 관계를 표현하는 패턴**  

### 📚 학습 내용  
- **Composite Pattern 개념 및 필요성**  
  - 개별 객체와 그룹 객체를 동일하게 다루는 방법  
  - 실무 적용: **파일 시스템 구조 (디렉토리 & 파일 관리)**  

- **위반 사례 분석**  
  - 개별 요소와 그룹 요소를 개별적으로 처리해야 하는 문제  
  - 실무 적용: **React 컴포넌트 트리 구조 설계**  

- **Composite Pattern 적용 방법**  
  - **트리 구조를 활용한 계층적 데이터 표현**  
  - **HTML DOM 구조에서 적용되는 방식 분석**  

> 📍 자세한 내용은 `composite/README.md` 참고  

---

## 🎨 **4. 데코레이터 패턴 (Decorator) (decorator/)**  
> **객체에 동적으로 기능을 추가하는 패턴**  

### 📚 학습 내용  
- **Decorator Pattern 개념 및 필요성**  
  - 상속 없이 객체의 기능을 동적으로 확장하는 방법  
  - 실무 적용: **로깅, 인증, 트랜잭션 관리 (Spring AOP)**  

- **위반 사례 분석**  
  - 상속으로 인해 불필요한 코드 중복 발생  
  - 실무 적용: **Java의 I/O Stream, Python의 @decorator 활용 사례**  

- **Decorator Pattern 적용 방법**  
  - **프록시 패턴과의 차이점 분석**  
  - **동적 기능 확장 시 적용 사례 (GUI 컴포넌트 디자인)**  

> 📍 자세한 내용은 `decorator/README.md` 참고  

---

## 🏠 **5. 퍼사드 패턴 (Facade) (facade/)**  
> **복잡한 서브시스템을 단순화하여 사용하기 쉽게 만드는 패턴**  

### 📚 학습 내용  
- **Facade Pattern 개념 및 필요성**  
  - 여러 클래스나 모듈을 하나의 단순한 인터페이스로 감싸는 방식  
  - 실무 적용: **Spring Framework의 Bean Factory**  

- **위반 사례 분석**  
  - 시스템의 복잡도가 높아지면서 인터페이스가 난잡해지는 문제  
  - 실무 적용: **마이크로서비스 간 API 호출 단순화**  

- **Facade Pattern 적용 방법**  
  - **API Gateway 활용한 서비스 통합**  
  - **클라이언트 요청을 단순화하는 디자인 패턴 적용**  

> 📍 자세한 내용은 `facade/README.md` 참고  

---

## 🪶 **6. 플라이웨이트 패턴 (Flyweight) (flyweight/)**  
> **반복적으로 생성되는 객체를 공유하여 메모리 사용을 최적화하는 패턴**  

### 📚 학습 내용  
- **Flyweight Pattern 개념 및 필요성**  
  - 동일한 데이터를 반복적으로 저장하는 비용 절감  
  - 실무 적용: **폰트 렌더링, 캐싱 시스템**  

- **위반 사례 분석**  
  - 대량의 객체가 중복 생성되면서 발생하는 성능 문제  
  - 실무 적용: **데이터베이스 커넥션 풀, 메모리 캐싱 기법 적용**  

- **Flyweight Pattern 적용 방법**  
  - **객체 풀링(Object Pooling) 기법과 비교 분석**  
  - **게임 엔진에서 리소스 관리 최적화 사례**  

> 📍 자세한 내용은 `flyweight/README.md` 참고  

---

## 🛡 **7. 프록시 패턴 (Proxy) (proxy/)**  
> **객체에 대한 접근을 제어하는 패턴**  

### 📚 학습 내용  
- **Proxy Pattern 개념 및 필요성**  
  - 실제 객체에 대한 접근을 제어하는 방법  
  - 실무 적용: **데이터베이스 커넥션 프록시, API 캐싱**  

- **위반 사례 분석**  
  - 직접적인 객체 접근으로 인해 보안 및 성능 문제가 발생하는 경우  
  - 실무 적용: **Spring AOP를 활용한 로깅 및 트랜잭션 관리**  

- **Proxy Pattern 적용 방법**  
  - **Virtual Proxy, Protection Proxy, Remote Proxy 비교**  
  - **게으른 초기화(Lazy Initialization) 및 성능 최적화**  

> 📍 자세한 내용은 `proxy/README.md` 참고  

---

## 🔍 **학습 방법**  
1. **각 구조 패턴의 개념을 학습한다.**  
2. **위반 사례를 분석하여 실무에서 발생하는 문제를 이해한다.**  
3. **개선된 코드 예제를 통해 패턴을 적용하는 방법을 익힌다.**  
4. **실제 프로젝트에서 적절한 패턴을 선택하고 적용해 본다.**  

---

## 📚 **추천 학습 리소스**  
- **"Design Patterns: Elements of Reusable Object-Oriented Software" - GoF (Gang of Four)**  
- **"Head First Design Patterns" - Eric Freeman & Elisabeth Robson**  
- **Spring Framework의 Proxy 및 Facade 적용 사례**  

---

## ✅ **마무리**  
이 디렉토리는 **객체 간 관계를 최적화하는 다양한 디자인 패턴을 배우고, 실무에서 유지보수성이 뛰어난 코드를 작성하는 방법을 익히기 위한 공간**입니다. 🚀  