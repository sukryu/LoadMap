# Erlang 학습 가이드

이 디렉토리는 Erlang을 체계적으로 학습하기 위한 자료들을 모아둔 공간입니다.  
Erlang은 고신뢰성, 분산 및 실시간 시스템 구축에 강력한 언어이며, Elixir의 기반이 되는 언어입니다.  
본 가이드를 통해 기본 문법과 개념부터 OTP 및 고급 동시성 패턴까지 차근차근 익혀나가길 바랍니다.

---

## 학습 목표

- **기본 문법과 개념 체화:**  
  Erlang의 역사, 문법, 함수형 프로그래밍 스타일을 이해하고 간단한 코드 예제를 통해 실습합니다.
  
- **OTP와 고급 동시성 개념 학습:**  
  Supervisor, GenServer 등 OTP 패턴을 심화 학습하여, 고신뢰성 시스템 및 분산 시스템 설계 능력을 키웁니다.
  
- **실전 프로젝트 경험:**  
  소규모 프로젝트를 통해 이론을 실제 코드로 구현하며, 실무에서 활용 가능한 역량을 배양합니다.

---

## 디렉토리 구조

```
/Learn_Erlang_Elixir
├── erlang
│   ├── basics
│   │   ├── introduction.md        # Erlang 소개 및 기본 문법 정리
│   │   ├── syntax_examples.erl    # 간단한 코드 예제
│   │   └── exercises              # 기초 연습 문제들
│   │       └── exercise1.erl
│   ├── advanced
│   │   ├── otp_concepts.md        # OTP 심화 및 고급 동시성 개념
│   │   ├── advanced_topics.erl    # 고급 기능 및 패턴 구현 예제
│   │   └── projects               # 고급 OTP 및 실전 프로젝트
│   │       └── project1.erl
│   └── resources                  # 참고 자료, 튜토리얼, 책 목록 등
│       ├── books.md
│       └── tutorials.md
└── shared
    └── comparison.md              # Erlang과 Elixir의 차이, 공통 개념 및 학습 팁 정리
```

---

## Erlang Basics

- **Introduction (introduction.md):**  
  Erlang의 역사, 철학, 기본 문법 및 함수형 프로그래밍의 특징을 소개합니다.
  
- **Syntax Examples (syntax_examples.erl):**  
  간단한 코드 예제를 통해 Erlang의 문법과 함수형 스타일을 직접 체험해 봅니다.
  
- **Exercises:**  
  다양한 기초 연습 문제를 통해 문법과 기본 개념을 복습하고 실력을 다집니다.

---

## Advanced Topics in Erlang

- **OTP Concepts (otp_concepts.md):**  
  Supervisor, GenServer 등 Erlang OTP의 핵심 개념을 심도 있게 학습합니다.
  
- **Advanced Topics (advanced_topics.erl):**  
  고급 동시성, 분산 시스템 구현 및 패턴(예: 이벤트 처리, 오류 격리) 등 실무에서 활용 가능한 주제를 다룹니다.
  
- **Projects:**  
  소규모 프로젝트를 통해 실제 응용 사례를 구현하고, Erlang의 강력한 기능들을 경험합니다.

---

## Resources

- **Books (books.md):**  
  Erlang 학습에 도움이 되는 도서 및 참고 문헌 목록을 정리합니다.
  
- **Tutorials (tutorials.md):**  
  온라인 튜토리얼, 동영상 강의, 블로그 포스트 등 유용한 자료들을 모아두었습니다.

---

## 마무리

이 가이드를 통해 Erlang의 기본부터 심화 주제까지 체계적으로 학습하여,  
고신뢰성 및 실시간 시스템 구축에 필요한 핵심 역량을 갖출 수 있기를 바랍니다.  
Erlang을 깊이 이해하면, Elixir와 같은 현대적 언어로의 확장도 자연스럽게 이루어질 것입니다.

행복한 학습 되세요!