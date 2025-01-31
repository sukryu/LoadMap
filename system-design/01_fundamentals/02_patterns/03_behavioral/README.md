# 📂 **01_fundamentals/patterns/behavioral/README.md**  
> **목표:**  
> - **객체 간의 상호작용과 책임을 정의하는 다양한 패턴(Behavioral Patterns)**을 학습한다.  
> - 코드의 **유연성과 확장성을 높이는 설계 기법**을 익힌다.  
> - 실무에서 **객체 간의 관계를 효과적으로 관리하고, 코드의 복잡성을 줄이는 방법**을 적용한다.  

---

## 📌 **디렉토리 구조 및 학습 내용**  
```
behavioral/
├── chain_of_responsibility/  # 책임 연쇄 패턴 (Chain of Responsibility)
├── command/                 # 커맨드 패턴 (Command)
├── iterator/                # 반복자 패턴 (Iterator)
├── mediator/                # 중재자 패턴 (Mediator)
├── memento/                 # 메멘토 패턴 (Memento)
├── observer/                # 옵저버 패턴 (Observer)
├── state/                   # 상태 패턴 (State)
├── strategy/                # 전략 패턴 (Strategy)
├── template_method/         # 템플릿 메서드 패턴 (Template Method)
└── visitor/                 # 방문자 패턴 (Visitor)
```

---

## 🔗 **1. 책임 연쇄 패턴 (Chain of Responsibility) (chain_of_responsibility/)**  
> **요청을 처리할 여러 객체를 체인으로 연결하여 순차적으로 처리하는 패턴**  

### 📚 학습 내용  
- **Chain of Responsibility Pattern 개념 및 필요성**  
  - 요청을 처리하는 여러 객체를 동적으로 연결하는 방법  
  - 실무 적용: **로그 필터링 시스템, 이벤트 핸들러 체인**  

- **위반 사례 분석**  
  - 요청 처리가 하드코딩된 경우 발생하는 문제  
  - 실무 적용: **Spring Security의 인증 체인 구현 사례**  

- **Chain of Responsibility 적용 방법**  
  - **동적 요청 처리 구조 설계**  
  - **디자인 원칙(SOLID)과의 관계 분석**  

> 📍 자세한 내용은 `chain_of_responsibility/README.md` 참고  

---

## 🖊 **2. 커맨드 패턴 (Command) (command/)**  
> **명령을 객체로 캡슐화하여 실행 취소(Undo) 기능을 제공하는 패턴**  

### 📚 학습 내용  
- **Command Pattern 개념 및 필요성**  
  - 실행 요청을 캡슐화하여 유연성을 높이는 방법  
  - 실무 적용: **UI 버튼 이벤트, 작업 취소(Undo) 기능**  

- **위반 사례 분석**  
  - 명령을 직접 실행하는 코드가 지나치게 분산된 경우  
  - 실무 적용: **게임에서 플레이어 액션 저장 및 재실행 방식**  

- **Command Pattern 적용 방법**  
  - **Invoker, Command, Receiver 개념 정리**  
  - **매크로 기능 구현 예제**  

> 📍 자세한 내용은 `command/README.md` 참고  

---

## 🔄 **3. 반복자 패턴 (Iterator) (iterator/)**  
> **컬렉션의 내부 구조를 숨기고 요소를 순차적으로 접근할 수 있도록 하는 패턴**  

### 📚 학습 내용  
- **Iterator Pattern 개념 및 필요성**  
  - 컬렉션을 순회하는 방법을 통일하는 설계 기법  
  - 실무 적용: **Java의 Iterator, Python의 Iterable 인터페이스**  

- **위반 사례 분석**  
  - 데이터 구조에 직접 접근하는 코드로 인해 발생하는 문제  
  - 실무 적용: **SQL ResultSet과 데이터 스트림 처리 방식 비교**  

- **Iterator Pattern 적용 방법**  
  - **Iterator 인터페이스 구현 사례 분석**  
  - **반복자 패턴과 Lazy Evaluation 기법 비교**  

> 📍 자세한 내용은 `iterator/README.md` 참고  

---

## 🔄 **4. 중재자 패턴 (Mediator) (mediator/)**  
> **객체 간의 복잡한 관계를 중재 객체를 통해 관리하는 패턴**  

### 📚 학습 내용  
- **Mediator Pattern 개념 및 필요성**  
  - 객체 간의 직접적인 의존성을 줄이는 방법  
  - 실무 적용: **채팅 시스템에서 메시지 라우팅 방식**  

- **위반 사례 분석**  
  - 객체 간의 상호 의존성이 증가하여 유지보수가 어려운 경우  
  - 실무 적용: **마이크로서비스 간 메시지 브로커(Kafka, RabbitMQ) 활용 사례**  

- **Mediator Pattern 적용 방법**  
  - **이벤트 기반 설계(Event-Driven Architecture)와의 관계 분석**  
  - **게임 엔진에서의 중재자 패턴 활용 예제**  

> 📍 자세한 내용은 `mediator/README.md` 참고  

---

## 🧠 **5. 옵저버 패턴 (Observer) (observer/)**  
> **객체의 상태 변경을 감지하고 자동으로 알림을 보내는 패턴**  

### 📚 학습 내용  
- **Observer Pattern 개념 및 필요성**  
  - 이벤트 기반 아키텍처에서 활용하는 방식  
  - 실무 적용: **이메일 알림 시스템, WebSockets 활용한 실시간 업데이트**  

- **위반 사례 분석**  
  - 상태 변경 감지를 직접 구현할 때 발생하는 문제  
  - 실무 적용: **Spring Event Listener, Pub-Sub 패턴 비교 분석**  

- **Observer Pattern 적용 방법**  
  - **Kafka, RabbitMQ와 같은 메시지 브로커에서 활용 방식**  
  - **MVC 패턴의 View-Model 데이터 바인딩 구현 사례**  

> 📍 자세한 내용은 `observer/README.md` 참고  

---

## 🏛 **6. 전략 패턴 (Strategy) (strategy/)**  
> **알고리즘을 런타임에 변경할 수 있도록 설계하는 패턴**  

### 📚 학습 내용  
- **Strategy Pattern 개념 및 필요성**  
  - 알고리즘을 동적으로 변경할 수 있는 구조  
  - 실무 적용: **결제 시스템에서 신용카드, 페이팔, 비트코인 등의 결제 방식 변경**  

- **위반 사례 분석**  
  - if-else 문이 많은 코드에서 발생하는 문제  
  - 실무 적용: **객체지향적인 설계로 코드 복잡성 줄이기**  

- **Strategy Pattern 적용 방법**  
  - **함수형 프로그래밍에서 전략 패턴 활용 예제**  
  - **디자인 원칙(SOLID)과의 관계 분석**  

> 📍 자세한 내용은 `strategy/README.md` 참고  

---

## 🔍 **학습 방법**  
1. **각 행위 패턴의 개념을 학습한다.**  
2. **위반 사례를 분석하여 실무에서 발생하는 문제를 이해한다.**  
3. **개선된 코드 예제를 통해 패턴을 적용하는 방법을 익힌다.**  
4. **실제 프로젝트에서 적절한 패턴을 선택하고 적용해 본다.**  

---

## 📚 **추천 학습 리소스**  
- **"Design Patterns: Elements of Reusable Object-Oriented Software" - GoF (Gang of Four)**  
- **"Head First Design Patterns" - Eric Freeman & Elisabeth Robson**  
- **Event-Driven Architecture와 Observer 패턴 적용 사례**  
- **Spring Framework의 Strategy 및 Observer 패턴 활용**  

---

## ✅ **마무리**  
이 디렉토리는 **객체 간의 상호작용을 최적화하는 다양한 디자인 패턴을 배우고, 실무에서 유지보수성이 뛰어난 코드를 작성하는 방법을 익히기 위한 공간**입니다.  
각 패턴이 **어떤 문제를 해결하는지, 왜 중요한지, 실무에서 어떻게 활용하는지 고민하면서 학습하는 것이 중요합니다.** 🚀