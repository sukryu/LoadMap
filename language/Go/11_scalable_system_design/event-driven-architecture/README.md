# Event-Driven Architecture for Scalable Systems ⚡️

이 디렉토리는 **이벤트 기반 아키텍처 (EDA)**를 활용하여, 확장 가능하고 반응성이 뛰어난 시스템을 설계하는 방법을 다룹니다.  
이 자료에서는 이벤트 소싱(Event Sourcing), CQRS(Command Query Responsibility Segregation) 등의 패턴을 비롯하여, 메시지 버스와 이벤트 스트리밍을 통한 서비스 간 비동기 통신 설계 기법을 학습할 수 있습니다.

---

## What You'll Learn 🎯

- **이벤트 기반 아키텍처 개념**:  
  - EDA의 기본 원리와 장점: 확장성, 느슨한 결합, 실시간 데이터 처리  
  - 이벤트 소싱과 CQRS 패턴의 핵심 아이디어와 차이점 이해

- **핵심 구성 요소**:  
  - 이벤트 버스, 토픽, 메시지 브로커, 이벤트 스토어 등 주요 구성 요소 소개  
  - Go 애플리케이션에서 이벤트를 생성, 전파 및 처리하는 방법

- **실무 적용 전략**:  
  - 마이크로서비스 아키텍처 내에서 이벤트 기반 통신 구현  
  - 시스템 복원력, 장애 대응 및 실시간 분석을 위한 이벤트 처리 전략
  - Kafka, NATS, RabbitMQ 등의 메시지 브로커와의 연계

- **Best Practices**:  
  - 이벤트 설계 시 일관성 유지, 중복 처리 방지, 이벤트 스키마 관리 등 실무 모범 사례  
  - 모니터링과 로깅을 통한 이벤트 흐름 추적 및 분석 전략

---

## Directory Structure 📁

```plaintext
11-scalable-system-design/
└── event-driven-architecture/
    ├── examples/             # EDA 패턴 적용 예제 코드 (이벤트 소싱, CQRS 등)
    ├── docs/                 # 설계 가이드, 참고 자료 및 아키텍처 다이어그램
    └── README.md             # 이 문서
```

- **examples/**:  
  - 이벤트 생성, 전파, 처리에 대한 Go 코드 예제와 마이크로서비스 간의 통신 샘플 코드 제공
- **docs/**:  
  - EDA 관련 설계 가이드, 아키텍처 다이어그램 및 구현 시 고려사항을 정리한 문서

---

## Getting Started 🚀

### 1. Prerequisites
- 최신 Go 버전 설치: [Download Go](https://go.dev/dl/)
- 메시지 브로커(Kafka, NATS, RabbitMQ 등) 환경 구성 (로컬 또는 클라우드)
- 이벤트 소싱과 CQRS 패턴에 대한 기본 개념 이해

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/11-scalable-system-design/event-driven-architecture
```

### 3. 예제 코드 실행
- **예제 코드 확인 및 실행**:  
  예제 디렉토리 내의 샘플 코드를 통해 이벤트 생성 및 소비 흐름을 실습해 보세요.
  ```bash
  go run examples/main.go
  ```
  - 각 예제는 이벤트 생성, 전파, 그리고 처리 과정을 보여주며, 이벤트 기반 통신의 효과를 확인할 수 있습니다.

---

## Key Concepts & Patterns 📚

### 1. Event Sourcing
- **개념**:  
  - 시스템의 상태를 이벤트의 시퀀스로 저장하여, 현재 상태를 이벤트들을 재생(Replaying)하여 복원합니다.
- **장점**:  
  - 모든 상태 변경 기록 보존, 감사 및 복원 가능
- **고려사항**:  
  - 이벤트 스키마 관리, 데이터 저장소 확장성

### 2. CQRS (Command Query Responsibility Segregation)
- **개념**:  
  - 읽기(쿼리)와 쓰기(커맨드)를 분리하여 각각 다른 모델로 처리합니다.
- **장점**:  
  - 읽기와 쓰기 성능 최적화, 복잡한 비즈니스 로직 분리
- **고려사항**:  
  - 데이터 일관성 유지, 이벤트 전파 전략

### 3. 메시지 브로커 활용
- **예시**:  
  - Kafka, NATS, RabbitMQ를 통해 이벤트를 토픽/큐로 전파하고, 다수의 소비자가 이를 처리하는 구조
- **장점**:  
  - 높은 처리량, 확장성, 내결함성 제공

---

## Best Practices & Tips 💡

- **이벤트 스키마 관리**:  
  - 스키마 레지스트리 사용 또는 버전 관리를 통해 이벤트 포맷 변화를 효과적으로 관리하세요.
- **중복 처리 방지**:  
  - 각 이벤트에 고유 식별자를 부여하고, 소비자가 중복 이벤트를 무시하도록 구현하세요.
- **모니터링과 로깅**:  
  - 이벤트 흐름, 소비율, 실패율 등을 모니터링하여 시스템 건강 상태를 지속적으로 확인하세요.
- **비동기 처리 최적화**:  
  - 이벤트 소비자 간의 병렬 처리 및 큐 길이 관리로, 높은 트래픽에도 안정적인 처리가 가능하도록 설계하세요.
- **장애 복구**:  
  - 이벤트 저장소 및 브로커의 내결함성(fault-tolerance)을 고려한 설계를 적용하고, 롤백 전략을 마련하세요.

---

## Next Steps

- **심화 학습**:  
  - EDA를 활용한 실제 시스템 아키텍처 사례 연구 및 고급 이벤트 패턴(예: Saga 패턴, Outbox 패턴) 학습
- **프로젝트 적용**:  
  - 마이크로서비스 환경에서 EDA를 적용해 보고, 각 서비스 간 이벤트 전파 및 처리 흐름을 최적화하세요.
- **도구 통합**:  
  - Prometheus, Grafana 등을 통해 이벤트 기반 시스템의 성능 및 상태를 모니터링하는 방법을 추가로 연구하세요.

---

## References 📚

- [Martin Fowler - Event Sourcing](https://martinfowler.com/eaaDev/EventSourcing.html)
- [CQRS Pattern Explained](https://martinfowler.com/bliki/CQRS.html)
- [Kafka Documentation](https://kafka.apache.org/documentation/)
- [NATS Documentation](https://docs.nats.io/)
- [RabbitMQ Documentation](https://www.rabbitmq.com/documentation.html)
- [Distributed Systems Observability](https://www.oreilly.com/library/view/designing-distributed-systems/9781491983638/)

---

Event-driven architecture는 현대 분산 시스템의 핵심 패러다임으로, 시스템 확장성과 실시간 데이터 처리를 가능하게 합니다.  
이 자료를 통해 Go 애플리케이션에 EDA 패턴을 효과적으로 적용하고, 안정적이고 확장 가능한 시스템을 구축해 보세요! Happy Event-Driven Coding! ⚡️🚀