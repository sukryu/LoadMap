# 📖 시스템 설계 기초 (01_fundamentals)

## 🏆 목표
- 시스템 설계의 **핵심 원칙과 개념**을 익힌다.
- **설계 패턴, 아키텍처 스타일, 성능 및 확장성** 등의 기본적인 지식을 학습한다.
- 실무에서 **안정적이고 확장 가능한 시스템을 설계할 수 있는 기반**을 마련한다.

---

## 📌 디렉토리 구조 및 학습 내용
```
01_fundamentals/
├── principles/        # 설계 원칙
├── patterns/          # 디자인 패턴
├── architecture/      # 아키텍처 스타일
├── scalability/       # 성능 및 확장성
└── real_world/        # 실전 설계 사례
```

---

## 🏗️ **1. 설계 원칙 (principles/)**
> **소프트웨어 설계에서 필수적으로 알아야 할 원칙을 익힌다.**  
✅ **개념 → 코드 예제 → 실무 적용 방법** 순서로 학습  

### 📚 학습 내용
- **SOLID 원칙** (SRP, OCP, LSP, ISP, DIP)  
- **DRY, KISS, YAGNI** 등 일반적인 설계 원칙  
- **관심사 분리(Separation of Concerns)**  
- **Fail Fast & Graceful Degradation (빠른 실패 & 우아한 성능 저하)**  

> 📍 자세한 내용은 `principles/README.md` 참고

---

## 🎨 **2. 디자인 패턴 (patterns/)**
> **소프트웨어 개발에서 자주 사용되는 설계 패턴을 익힌다.**  

### 📚 학습 내용
- **생성 패턴**: Factory, Singleton, Builder  
- **구조 패턴**: Adapter, Proxy, Decorator  
- **행위 패턴**: Observer, Strategy, Command  

> 📍 자세한 내용은 `patterns/README.md` 참고

---

## 🏛️ **3. 아키텍처 스타일 (architecture/)**
> **시스템 설계에서 활용되는 다양한 아키텍처 스타일 학습**  

### 📚 학습 내용
- **계층화 아키텍처 (Layered Architecture)**
- **이벤트 기반 아키텍처 (Event-Driven Architecture)**
- **마이크로서비스 아키텍처 (Microservices Architecture)**
- **서버리스 아키텍처 (Serverless Architecture)**

> 📍 자세한 내용은 `architecture/README.md` 참고

---

## 📈 **4. 성능 및 확장성 (scalability/)**
> **성능 최적화 및 확장성 고려한 시스템 설계 기법 학습**  

### 📚 학습 내용
- **수평적 확장 (Horizontal Scaling) vs 수직적 확장 (Vertical Scaling)**
- **로드 밸런싱 (Load Balancing)**
- **데이터베이스 성능 최적화 (Indexing, Caching, Partitioning)**
- **분산 시스템에서의 성능 고려 사항**

> 📍 자세한 내용은 `scalability/README.md` 참고

---

## 🏆 **5. 실전 설계 사례 (real_world/)**
> **실제 기업들의 시스템 설계를 분석하며 학습**  

### 📚 학습 내용
- **Netflix의 아키텍처 설계 원칙**
- **Uber의 마이크로서비스 적용 사례**
- **Airbnb의 확장성 고려한 데이터베이스 설계**
- **AWS의 서버리스 아키텍처 활용 사례**

> 📍 자세한 내용은 `real_world/README.md` 참고

---

## 🔍 학습 방법
1. 각 개념을 이론적으로 학습한다.
2. 작은 규모의 예제 코드를 작성하여 원리를 이해한다.
3. 실제 사례를 분석하여 실무 적용 방식을 익힌다.
4. 설계 결정을 문서화하고 피드백을 받는다.

---

## 📚 추천 학습 리소스
- **"Designing Data-Intensive Applications" - Martin Kleppmann**
- **"Clean Architecture" - Robert C. Martin**
- **"System Design Interview" - Alex Xu**
- **System Design Primer (GitHub)**

---

## ✅ 마무리
이 디렉토리는 시스템 설계의 **기본 개념을 익히는 입문 단계**입니다.  
모든 설계 원칙과 패턴이 실무에서 어떻게 적용되는지 고민하며 학습하는 것이 중요합니다. 🚀

```

---

이 문서는 **01_fundamentals** 디렉토리의 전체적인 개요를 제공하며,  
각 서브 디렉토리(설계 원칙, 패턴, 아키텍처 스타일 등)에 대한 학습 내용을 소개합니다.  

필요한 추가 사항이나 수정할 부분이 있다면 알려주세요! 😊