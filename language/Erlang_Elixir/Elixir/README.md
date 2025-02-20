# Elixir 학습 가이드

이 디렉토리는 Elixir를 체계적으로 학습하기 위한 자료들을 모아둔 공간입니다.  
Elixir는 Erlang의 강력한 기반 위에 구축된 함수형 프로그래밍 언어로, 높은 동시성, 분산 시스템, 실시간 애플리케이션 개발에 매우 적합합니다.  
이 가이드를 통해 기본 문법과 Elixir의 철학을 익히고, OTP 및 고급 동시성 패턴을 학습하며, 실제 프로젝트를 구현해 보는 경험을 쌓으시길 바랍니다.

---

## 학습 목표

- **기본 문법과 개념 체화:**  
  Elixir의 역사, 문법, 함수형 프로그래밍의 특징과 모듈 시스템을 이해하고, 간단한 코드 예제를 통해 실습합니다.
  
- **OTP와 고급 동시성 패턴 학습:**  
  Supervisor, GenServer 등 Elixir에서 OTP를 활용한 패턴을 심도 있게 학습하여, 고신뢰성 시스템 및 분산 시스템 설계 능력을 키웁니다.
  
- **실전 프로젝트 경험:**  
  소규모 프로젝트를 통해 이론을 실제 코드로 구현하고, 실무에서 활용 가능한 역량을 배양합니다.

---

## 디렉토리 구조

```
/Learn_Erlang_Elixir
├── elixir
│   ├── basics
│   │   ├── introduction.md        # Elixir 소개 및 기본 문법 정리
│   │   ├── syntax_examples.ex     # 간단한 코드 예제
│   │   └── exercises              # 기초 연습 문제들
│   │       └── exercise1.ex
│   ├── advanced
│   │   ├── otp_concepts.md        # OTP 심화 및 고급 Elixir 패턴
│   │   ├── advanced_topics.ex     # 고급 동시성, 분산 시스템 구현 예제
│   │   └── projects               # 고급 OTP 및 실전 프로젝트
│   │       └── project1.ex
│   └── resources                  # 참고 자료, 튜토리얼, 책 목록 등
│       ├── books.md
│       └── tutorials.md
└── shared
    └── comparison.md              # Erlang과 Elixir의 차이, 공통 개념 및 학습 팁 정리
```

---

## Elixir Basics

- **Introduction (introduction.md):**  
  Elixir의 철학, 역사, 기본 문법 및 함수형 프로그래밍의 특징을 소개합니다.
  
- **Syntax Examples (syntax_examples.ex):**  
  간단한 예제 코드를 통해 Elixir의 모듈, 함수, 패턴 매칭, 파이프라인 연산자 등을 직접 체험해 봅니다.
  
- **Exercises:**  
  다양한 기초 연습 문제를 통해 문법과 기본 개념을 복습하고, 실력을 다질 수 있습니다.

---

## Advanced Topics in Elixir

- **OTP Concepts (otp_concepts.md):**  
  Elixir에서의 Supervisor, GenServer, Task 등 OTP 패턴의 원리와 활용법을 심도 있게 학습합니다.
  
- **Advanced Topics (advanced_topics.ex):**  
  고급 동시성, 분산 시스템 설계, 오류 격리, 리트라이 패턴 등 실무에서 활용할 수 있는 고급 기능을 다룹니다.
  
- **Projects:**  
  소규모 프로젝트를 통해 실제 응용 사례를 구현하며, Elixir의 강력한 동시성 및 분산 처리 기능을 체험합니다.

---

## Resources

- **Books (books.md):**  
  Elixir 학습에 도움이 되는 도서 및 참고 문헌 목록을 정리합니다.
  
- **Tutorials (tutorials.md):**  
  온라인 튜토리얼, 동영상 강의, 블로그 포스트 등 유용한 자료들을 모아두었습니다.

---

## 마무리

이 가이드를 통해 Elixir의 기본부터 심화 주제까지 체계적으로 학습하여,  
실시간 시스템과 분산 애플리케이션 개발에 필요한 핵심 역량을 갖추시길 바랍니다.  
Elixir를 깊이 이해하면, 높은 동시성과 안정성을 요구하는 현대 백엔드 및 클라우드 시스템 구축에 큰 도움이 될 것입니다.

행복한 학습 되세요!