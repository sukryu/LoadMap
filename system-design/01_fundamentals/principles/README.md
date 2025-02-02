# 📂 설계 원칙 - principles

> **목표:**  
> - 소프트웨어 아키텍처 및 시스템 설계의 핵심 원칙을 학습한다.  
> - SOLID 원칙, CAP 정리, ACID vs BASE 모델 등 주요 개념을 이해하고 적용한다.  
> - 확장성과 유지보수성을 고려한 최적의 설계 패턴을 연구한다.

---

## 📌 **디렉토리 구조**
```
principles/                     # 설계 원칙
├── solid/                      # SOLID 원칙
│   ├── single_responsibility.md # 단일 책임 원칙 (SRP)
│   ├── open_closed.md          # 개방-폐쇄 원칙 (OCP)
│   ├── liskov_substitution.md  # 리스코프 치환 원칙 (LSP)
│   ├── interface_segregation.md # 인터페이스 분리 원칙 (ISP)
│   ├── dependency_inversion.md # 의존성 역전 원칙 (DIP)
│   └── README.md
│
├── cap_theorem.md              # CAP 정리
├── acid_vs_base.md             # ACID vs BASE 모델
├── twelve_factor_app.md        # 12-Factor App 원칙
├── design_patterns_basics.md   # 디자인 패턴 개요
└── README.md
```

---

## 📖 **1. 개념 개요**
> **설계 원칙은 유지보수성과 확장성을 갖춘 소프트웨어 시스템을 만들기 위한 핵심 개념이다.**

- ✅ **왜 중요한가?**  
  - 잘 설계된 시스템은 유지보수가 쉽고 확장성이 뛰어나다.
  - 복잡한 시스템에서 일관성을 유지하고 장애를 줄이는 데 도움이 된다.
  - 성능 최적화 및 비용 절감을 위해 필수적인 원칙을 적용할 수 있다.

- ✅ **어떤 문제를 해결하는가?**  
  - 의존성 문제를 줄이고 코드 변경에 유연하게 대응
  - 확장성을 고려한 시스템 설계를 가능하게 함
  - 데이터 일관성과 가용성 간의 균형을 유지하는 전략 제공

- ✅ **실무에서 어떻게 적용하는가?**  
  - SOLID 원칙을 준수하여 객체지향 프로그래밍 적용
  - CAP 정리를 이해하여 분산 시스템에서의 트레이드오프 결정
  - ACID와 BASE 모델을 비교하여 적절한 데이터베이스 설계

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **SOLID 원칙 (solid/)**
  - 단일 책임 원칙 (SRP)
  - 개방-폐쇄 원칙 (OCP)
  - 리스코프 치환 원칙 (LSP)
  - 인터페이스 분리 원칙 (ISP)
  - 의존성 역전 원칙 (DIP)

- **CAP 정리 (cap_theorem.md)**
  - Consistency (일관성), Availability (가용성), Partition Tolerance (파티션 허용성)의 관계
  - 분산 시스템 설계에서의 트레이드오프 분석

- **ACID vs BASE 모델 (acid_vs_base.md)**
  - 데이터베이스 트랜잭션의 ACID 모델과 분산 환경에서의 BASE 모델 비교
  - 언제 어떤 모델을 선택해야 하는지 이해

- **12-Factor App 원칙 (twelve_factor_app.md)**
  - 클라우드 네이티브 애플리케이션 설계 원칙
  - 확장 가능하고 유지보수하기 쉬운 애플리케이션을 설계하는 방법

- **디자인 패턴 개요 (design_patterns_basics.md)**
  - 주요 소프트웨어 디자인 패턴 정리
  - 싱글톤, 팩토리, 리포지토리 패턴 등의 개념과 활용 사례

---

## 🚀 **3. 실전 사례 분석**
> **실제 기업들이 설계 원칙을 어떻게 활용하는가?**

- **Netflix** - CAP 정리 기반의 분산 데이터베이스 전략
- **Uber** - SOLID 원칙을 활용한 마이크로서비스 설계
- **Google** - 12-Factor App 원칙을 적용한 클라우드 네이티브 시스템 구축

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ 설계 패턴 학습  
3️⃣ 실제 사례 분석  
4️⃣ 코드 실습 진행  
5️⃣ 트레이드오프 분석  

---

## 📚 **5. 추천 리소스**
- 📖 _Clean Code_ - Robert C. Martin  
- 📖 _Designing Data-Intensive Applications_ - Martin Kleppmann  
- 📖 _Domain-Driven Design_ - Eric Evans  
- 📌 [Awesome Design Principles](https://github.com/robinschneider/awesome-design-principles)  
- 📌 [Refactoring Guru - Design Patterns](https://refactoring.guru/design-patterns)  

---

## ✅ **마무리**
이 문서는 **설계 원칙의 핵심 개념과 실무 적용 방법을 학습하는 단계**입니다.
이론 → 패턴 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며,
유지보수성과 확장성을 고려한 소프트웨어 시스템을 설계할 수 있도록 합니다. 🚀

