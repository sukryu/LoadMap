# 06 Messaging Systems & Event Processing 📩

이 디렉토리는 **메시징 시스템**과 이벤트 기반 아키텍처를 실무에서 어떻게 활용할 수 있는지에 대해 다룹니다.  
Kafka, RabbitMQ, Google Pub/Sub, SNS/SQS 등 다양한 메시지 브로커를 통해, 분산 시스템 간의 비동기 통신, 이벤트 스트리밍, 데이터 파이프라인 구축 방법을 학습하고 실제 서비스에 적용하는 방법을 소개합니다.

---

## 디렉토리 구성 📁

```plaintext
06-messaging-systems/
├── kafka-rabbitmq/    # Kafka와 RabbitMQ를 활용한 메시지 큐 및 이벤트 스트리밍 예제
└── pubsub/            # Google Pub/Sub, AWS SNS/SQS 등 퍼블리시/서브스크립션 모델 예제
```

- **kafka-rabbitmq/**:  
  - Kafka와 RabbitMQ의 개념 및 주요 차이점  
  - Go 클라이언트 라이브러리를 활용한 메시지 생산자(producer)와 소비자(consumer) 구현 예제  
  - 이벤트 스트리밍, 파티셔닝, 리플리케이션, 컨슈머 그룹 등의 운영 모범 사례
  
- **pubsub/**:  
  - 퍼블리시/서브스크립션 모델의 개념과 사용 사례  
  - Google Pub/Sub, AWS SNS/SQS 등의 플랫폼에서의 메시지 처리 방법  
  - Go 기반의 API 연동 및 이벤트 드리븐 아키텍처 구축 방법

---

## 실무 활용 목표 🎯

- **비동기 통신 구현**:  
  - 분산 시스템 간의 데이터 전달 및 이벤트 스트리밍을 통해, 시스템의 확장성과 응답성을 높입니다.
  
- **이벤트 기반 아키텍처**:  
  - 메시징 시스템을 활용해, 마이크로서비스 간의 느슨한 결합과 실시간 데이터 처리, 장애 격리 및 복구 전략을 구현합니다.
  
- **운영 자동화 및 모니터링**:  
  - 메시지 큐의 모니터링, 리트라이 메커니즘, 소비자 그룹 관리 등 실제 운영 환경에서 필요한 기능을 적용합니다.

---

## 실무 활용 사례 🚀

1. **Kafka 기반 이벤트 스트리밍**  
   - 대용량 로그 및 트랜잭션 데이터를 실시간으로 수집하고 처리  
   - 파티셔닝과 컨슈머 그룹을 이용해 부하 분산 및 장애 격리 구현

2. **RabbitMQ를 통한 메시지 큐**  
   - 주문 처리, 이메일 전송, 작업 스케줄링 등 비동기 작업 처리  
   - 메시지 신뢰성, ACK, 재전송 등의 기능을 활용해 안정적인 메시지 전달 보장

3. **Pub/Sub 모델 적용**  
   - Google Pub/Sub 또는 AWS SNS/SQS를 이용한 실시간 알림 서비스  
   - 이벤트 드리븐 아키텍처에서 클라우드 서비스와 연동하여 확장성 높은 시스템 구축

---

## 실무 적용 방법 및 팁 💡

- **Go 클라이언트 라이브러리 활용**:  
  - Kafka: [confluent-kafka-go](https://github.com/confluentinc/confluent-kafka-go) 또는 [sarama](https://github.com/Shopify/sarama)  
  - RabbitMQ: [streadway/amqp](https://github.com/streadway/amqp)  
  - Pub/Sub: [Google Cloud Pub/Sub Go Client](https://pkg.go.dev/cloud.google.com/go/pubsub) 및 [AWS SDK for Go](https://aws.amazon.com/sdk-for-go/)

- **메시지 신뢰성 관리**:  
  - 메시지 ACK, 재전송 및 중복 제거 정책을 반드시 구현하여 데이터 무결성을 확보하세요.
  
- **스케일링 및 파티셔닝**:  
  - Kafka의 경우 파티션 수, 컨슈머 그룹 전략을 통해 부하 분산을 최적화하고, RabbitMQ에서는 큐 분산과 클러스터링을 고려하세요.
  
- **모니터링 및 로깅**:  
  - 메시지 큐의 상태와 처리량, 실패율 등을 Prometheus, Grafana 등 모니터링 도구와 연계해 지속적으로 확인하세요.

- **에러 핸들링**:  
  - 메시지 처리 중 발생할 수 있는 에러를 적절히 로깅하고, 재처리 메커니즘을 구현하여 안정성을 높이세요.

---

## 시작하기 🚀

### 1. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/06-messaging-systems
```

### 2. Kafka & RabbitMQ 예제 실행
```bash
cd kafka-rabbitmq
# 예제 실행: 메시지 생산자 및 소비자 실행
go run producer.go
go run consumer.go
```

### 3. Pub/Sub 예제 실행
```bash
cd ../pubsub
# Google Pub/Sub 또는 AWS SNS/SQS를 활용한 예제 실행
go run main.go
```

---

## 참고 자료 📚

- [Confluent Kafka Go Client](https://github.com/confluentinc/confluent-kafka-go)
- [Sarama Kafka Client](https://github.com/Shopify/sarama)
- [RabbitMQ Go Client](https://github.com/streadway/amqp)
- [Google Cloud Pub/Sub Go Client](https://pkg.go.dev/cloud.google.com/go/pubsub)
- [AWS SNS & SQS with Go](https://aws.amazon.com/sdk-for-go/)

---

메시징 시스템을 활용한 비동기 통신과 이벤트 기반 아키텍처는 현대 백엔드 시스템의 핵심입니다.  
이 자료를 통해 다양한 메시징 시스템의 실제 운영 방법을 익히고, 실무에 바로 적용해 보세요! Happy Messaging! 🚀