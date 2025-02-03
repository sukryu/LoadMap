# 📂 확장성 - scalability

> **목표:**  
> - 시스템 확장성(Scalability)의 개념과 설계 원칙을 학습한다.  
> - 수평적/수직적 확장, 로드 밸런싱, 멀티 리전 아키텍처 등의 기법을 이해하고 적용한다.  
> - 확장성을 고려한 최적의 시스템 설계를 연구하여 실무에 적용한다.

---

## 📌 **디렉토리 구조**
```
scalability/                    # 확장성 개념 학습
├── horizontal_scaling.md       # 수평적 확장
├── vertical_scaling.md         # 수직적 확장
├── load_balancing.md           # 로드 밸런싱
├── caching.md                  # 캐싱 전략
├── multi_region.md             # 멀티 리전 아키텍처
├── edge_computing.md           # 엣지 컴퓨팅
├── serverless_scaling.md       # 서버리스 확장성
└── README.md
```

---

## 📖 **1. 개념 개요**
> **확장성은 시스템이 증가하는 부하를 효율적으로 처리할 수 있도록 설계하는 방법이다.**

- ✅ **왜 중요한가?**  
  - 서비스 성장에 따라 유연하게 대응할 수 있는 인프라 구축이 필요하다.
  - 성능 저하 없이 더 많은 사용자와 데이터를 처리할 수 있어야 한다.
  - 비용 효율성과 장애 대응 능력을 극대화할 수 있다.

- ✅ **어떤 문제를 해결하는가?**  
  - 트래픽 급증 시 성능 저하 문제 해결
  - 데이터 증가에 따른 저장 및 검색 성능 유지
  - 글로벌 서비스 확장을 위한 지연 시간 최적화

- ✅ **실무에서 어떻게 적용하는가?**  
  - 로드 밸런서를 활용하여 트래픽을 효율적으로 분산
  - 데이터 샤딩 및 캐싱 전략으로 성능 최적화
  - 멀티 리전 아키텍처를 통해 장애 대응 및 글로벌 확장

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **수평적 확장 (horizontal_scaling.md)**
  - 여러 대의 서버를 추가하여 성능을 확장하는 방법
  - 데이터베이스 샤딩 및 리플리케이션 기법

- **수직적 확장 (vertical_scaling.md)**
  - 서버 자체의 성능을 증가시키는 방식 (CPU, RAM 업그레이드)
  - 단일 노드에서의 확장성과 한계 분석

- **로드 밸런싱 (load_balancing.md)**
  - 트래픽 분산을 위한 로드 밸런서(LB) 개념
  - DNS 라운드 로빈, 리버스 프록시, L7/L4 LB 기법 적용

- **캐싱 전략 (caching.md)**
  - CDN(Content Delivery Network) 적용 방법
  - Redis, Memcached 등을 활용한 데이터 캐싱
  - 캐시 일관성 및 무효화 기법

- **멀티 리전 아키텍처 (multi_region.md)**
  - 여러 데이터센터를 활용한 글로벌 확장 전략
  - 트래픽 라우팅 및 재해 복구(Disaster Recovery) 설계

- **엣지 컴퓨팅 (edge_computing.md)**
  - 사용자와 가까운 위치에서 데이터 처리하여 응답 속도 향상
  - IoT 및 실시간 데이터 처리에 적용

- **서버리스 확장성 (serverless_scaling.md)**
  - AWS Lambda, Google Cloud Functions을 활용한 확장성 극대화
  - 이벤트 기반 서비스 아키텍처 구축

---

## 🚀 **3. 실전 사례 분석**
> **대규모 서비스가 확장성을 어떻게 활용하는가?**

- **Netflix** - AWS 기반 확장 가능한 마이크로서비스 인프라
- **Instagram** - 데이터 샤딩 및 캐싱을 활용한 성능 최적화
- **Amazon** - 글로벌 멀티 리전 배포 및 로드 밸런싱 기법 적용

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ 설계 패턴 학습  
3️⃣ 실제 사례 분석  
4️⃣ 코드 실습 진행  
5️⃣ 트레이드오프 분석  

---

## 📚 **5. 추천 리소스**
- 📖 _Designing Data-Intensive Applications_ - Martin Kleppmann  
- 📖 _Site Reliability Engineering_ - Google SRE 팀  
- 📖 _The Art of Scalability_ - Martin L. Abbott  
- 📌 [Awesome Scalability](https://github.com/binhnguyennus/awesome-scalability)  
- 📌 [AWS Well-Architected Framework](https://aws.amazon.com/architecture/well-architected/)  

---

## ✅ **마무리**
이 문서는 **확장성을 고려한 시스템 설계의 핵심 개념을 학습하는 단계**입니다.
이론 → 패턴 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며,
실무에서 성능과 확장성을 고려한 아키텍처를 설계할 수 있도록 합니다. 🚀

