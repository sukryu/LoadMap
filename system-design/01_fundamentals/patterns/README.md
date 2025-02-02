# 📂 디자인 패턴 - patterns

> **목표:**  
> - 소프트웨어 아키텍처와 시스템 설계에서 사용되는 디자인 패턴을 학습한다.  
> - 각 패턴의 동작 원리와 실무 적용 방안을 이해하고 활용한다.  
> - 유지보수성과 확장성을 고려한 최적의 설계 패턴을 연구한다.

---

## 📌 **디렉토리 구조**
```
patterns/                      # 디자인 패턴
├── creational/                # 생성 패턴
│   ├── singleton.md           # 싱글톤 패턴
│   ├── factory_method.md      # 팩토리 메서드 패턴
│   ├── abstract_factory.md    # 추상 팩토리 패턴
│   ├── builder.md             # 빌더 패턴
│   ├── prototype.md           # 프로토타입 패턴
│   └── README.md
│
├── structural/                # 구조 패턴
│   ├── adapter.md             # 어댑터 패턴
│   ├── bridge.md              # 브리지 패턴
│   ├── composite.md           # 컴포지트 패턴
│   ├── decorator.md           # 데코레이터 패턴
│   ├── facade.md              # 퍼사드 패턴
│   ├── flyweight.md           # 플라이웨이트 패턴
│   ├── proxy.md               # 프록시 패턴
│   └── README.md
│
├── behavioral/                # 행동 패턴
│   ├── chain_of_responsibility.md # 책임 연쇄 패턴
│   ├── command.md             # 커맨드 패턴
│   ├── iterator.md            # 이터레이터 패턴
│   ├── mediator.md            # 미디에이터 패턴
│   ├── memento.md             # 메멘토 패턴
│   ├── observer.md            # 옵저버 패턴
│   ├── state.md               # 상태 패턴
│   ├── strategy.md            # 전략 패턴
│   ├── template_method.md     # 템플릿 메서드 패턴
│   ├── visitor.md             # 방문자 패턴
│   └── README.md
│
└── README.md
```

---

## 📖 **1. 개념 개요**
> **디자인 패턴은 소프트웨어 설계를 보다 효율적이고 유지보수 가능하게 만드는 방법론이다.**

- ✅ **왜 중요한가?**  
  - 반복적으로 발생하는 설계 문제를 해결하는 최적의 방법을 제공한다.
  - 유지보수성과 확장성을 높여 코드의 품질을 향상시킨다.
  - 개발자가 공통적인 설계 언어를 통해 효율적으로 협업할 수 있도록 돕는다.

- ✅ **어떤 문제를 해결하는가?**  
  - 코드 중복 및 결합도 문제 해결
  - 객체 간의 관계를 효과적으로 관리
  - 확장 가능하고 변경이 용이한 아키텍처 구현

- ✅ **실무에서 어떻게 적용하는가?**  
  - 싱글톤 패턴을 사용해 객체 생성을 제한하고 자원 관리를 최적화
  - 팩토리 패턴을 활용하여 객체 생성을 추상화
  - 데코레이터 패턴을 이용해 런타임 시 객체 기능을 확장
  - 전략 패턴을 통해 런타임 시 알고리즘을 동적으로 변경

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **생성 패턴 (creational/)**
  - 싱글톤, 팩토리 메서드, 추상 팩토리, 빌더, 프로토타입 패턴

- **구조 패턴 (structural/)**
  - 어댑터, 브리지, 컴포지트, 데코레이터, 퍼사드, 플라이웨이트, 프록시 패턴

- **행동 패턴 (behavioral/)**
  - 책임 연쇄, 커맨드, 이터레이터, 미디에이터, 메멘토, 옵저버, 상태, 전략, 템플릿 메서드, 방문자 패턴

---

## 🚀 **3. 실전 사례 분석**
> **실제 기업들이 디자인 패턴을 어떻게 활용하는가?**

- **Netflix** - 전략 패턴을 활용한 추천 시스템
- **Amazon** - 팩토리 패턴을 적용한 주문 관리 시스템
- **Google** - 옵저버 패턴을 사용한 이벤트 기반 아키텍처 설계

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ 설계 패턴 학습  
3️⃣ 실제 사례 분석  
4️⃣ 코드 실습 진행  
5️⃣ 트레이드오프 분석  

---

## 📚 **5. 추천 리소스**
- 📖 _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- 📖 _Head First Design Patterns_ - Eric Freeman  
- 📖 _Refactoring to Patterns_ - Joshua Kerievsky  
- 📌 [Refactoring Guru - Design Patterns](https://refactoring.guru/design-patterns)  
- 📌 [Awesome Design Patterns](https://github.com/DovAmir/awesome-design-patterns)  

---

## ✅ **마무리**
이 문서는 **디자인 패턴의 개념과 실무 적용 방법을 학습하는 단계**입니다.
이론 → 패턴 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며,
소프트웨어의 유지보수성과 확장성을 고려한 최적의 설계를 적용할 수 있도록 합니다. 🚀

