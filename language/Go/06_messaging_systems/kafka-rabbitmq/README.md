# Kafka & RabbitMQ Messaging in Go 🚀

이 디렉토리는 Go 언어를 사용하여 **Kafka**와 **RabbitMQ**를 통한 메시징 시스템을 구현하는 방법을 다룹니다.  
메시지 기반 비동기 처리와 이벤트 기반 아키텍처를 구축하기 위해, Kafka와 RabbitMQ의 기본 개념, 프로듀서-컨슈머 패턴, 그리고 Go에서의 실제 구현 예제를 학습할 수 있습니다.

---

## What You'll Learn 🎯

- **메시징 시스템의 기본 개념**  
  - 프로듀서-컨슈머 패턴, 토픽, 큐, 파티션, 소비자 그룹 등의 핵심 개념 이해

- **Kafka 사용법**  
  - Kafka 클러스터, 토픽, 파티션, 메시지 전송 및 소비 방법 (예: Sarama 라이브러리 활용)

- **RabbitMQ 사용법**  
  - 큐, 익스체인지, 바인딩, 메시지 확인 및 ACK 등 RabbitMQ의 핵심 기능 이해 (예: streadway/amqp 라이브러리 활용)

- **실무 적용 전략**  
  - 오류 처리, 연결 및 채널 관리, 확장성 및 성능 최적화 전략

---

## Directory Structure 📁

```plaintext
06-messaging-systems/
└── kafka-rabbiqmq/
    ├── main.go                    # Kafka와 RabbitMQ의 기본 예제 코드 (간단한 메시지 전송/소비)
    ├── examples/                  # 고급 사용 사례 및 추가 실습 예제
    │   ├── 01_advanced_producer.go    # Kafka 고급 프로듀서: 비동기 메시지 전송 및 결과 모니터링
    │   ├── 02_advanced_consumer.go    # Kafka 고급 컨슈머: 컨슈머 그룹을 통한 지속적 메시지 소비
    │   ├── 03_streaming_processing.go # Kafka 스트리밍 처리: 메시지 변환 후 출력 토픽 전송
    │   ├── 04_rabbitmq_rpc_example.go # RabbitMQ RPC 패턴: RPC 서버와 클라이언트 구현
    │   ├── 01_rabbitmq_publisher.go   # RabbitMQ 고급 퍼블리셔: 큐에 메시지 게시
    │   ├── 02_rabbitmq_consumer.go    # RabbitMQ 고급 소비자: 수동 ACK를 통한 메시지 소비
    │   └── 03_rabbitmq_exchange_topic.go  # RabbitMQ 토픽 익스체인지: 라우팅 키 기반 메시지 라우팅
    └── README.md                  # 이 문서 (메시징 시스템 개요 및 예제 가이드)
```

- **main.go**: 기본적인 Kafka와 RabbitMQ 예제를 통해 메시지 전송 및 소비 과정을 시연합니다.
- **examples/**: 스트리밍, 멀티 컨슈머, Pub/Sub 패턴 등 고급 기능 예제들이 포함되어 있습니다.

---

## Getting Started 🚀

### 1. 필수 도구 설치
- **Go 최신 버전**: [Go 다운로드](https://go.dev/dl/)
- **Kafka**: Kafka 서버가 설치되어 있거나 Docker를 통해 실행 중인지 확인
- **RabbitMQ**: RabbitMQ 서버가 설치되어 있거나 Docker를 통해 실행 중인지 확인
- **Go 라이브러리 설치**:
  ```bash
  go get github.com/Shopify/sarama     # Kafka 라이브러리
  go get github.com/streadway/amqp       # RabbitMQ 라이브러리
  ```

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/06-messaging-systems/kafka-rabbiqmq
```

### 3. 예제 코드 실행
- Kafka 예제:
  ```bash
  go run main.go -broker "localhost:9092" -topic "example-topic"
  ```
- RabbitMQ 예제:
  ```bash
  go run main.go -amqp "amqp://guest:guest@localhost:5672/" -queue "example-queue"
  ```
(예제 실행 방식은 구현에 따라 다를 수 있으니, 코드 내 주석을 참고하세요.)

---

## Example Code Snippets 📄

### Kafka Producer 예제
```go
package main

import (
    "fmt"
    "log"

    "github.com/Shopify/sarama"
)

func kafkaProducerExample() {
    brokers := []string{"localhost:9092"}
    topic := "example-topic"

    config := sarama.NewConfig()
    config.Producer.Return.Successes = true

    producer, err := sarama.NewSyncProducer(brokers, config)
    if err != nil {
        log.Fatalf("Kafka 프로듀서 생성 실패: %v", err)
    }
    defer producer.Close()

    msg := &sarama.ProducerMessage{
        Topic: topic,
        Value: sarama.StringEncoder("Go에서 보내는 Kafka 메시지!"),
    }

    partition, offset, err := producer.SendMessage(msg)
    if err != nil {
        log.Fatalf("Kafka 메시지 전송 실패: %v", err)
    }
    fmt.Printf("Kafka 메시지 전송 성공 - 파티션: %d, 오프셋: %d\n", partition, offset)
}
```

### RabbitMQ Publisher 예제
```go
package main

import (
    "fmt"
    "log"

    "github.com/streadway/amqp"
)

func rabbitmqPublisherExample() {
    conn, err := amqp.Dial("amqp://guest:guest@localhost:5672/")
    if err != nil {
        log.Fatalf("RabbitMQ 연결 실패: %v", err)
    }
    defer conn.Close()

    ch, err := conn.Channel()
    if err != nil {
        log.Fatalf("RabbitMQ 채널 열기 실패: %v", err)
    }
    defer ch.Close()

    q, err := ch.QueueDeclare(
        "example-queue", // 큐 이름
        true,            // 내구성
        false,           // 자동 삭제 아님
        false,           // 독점 사용 아님
        false,           // no-wait
        nil,             // 추가 인자
    )
    if err != nil {
        log.Fatalf("큐 선언 실패: %v", err)
    }

    body := "Go에서 보내는 RabbitMQ 메시지!"
    err = ch.Publish(
        "",     // 익스체인지 (기본 익스체인지 사용)
        q.Name, // 라우팅 키 (큐 이름)
        false,  // mandatory
        false,  // immediate
        amqp.Publishing{
            ContentType: "text/plain",
            Body:        []byte(body),
        })
    if err != nil {
        log.Fatalf("RabbitMQ 메시지 전송 실패: %v", err)
    }
    fmt.Println("RabbitMQ 메시지 전송 성공!")
}
```

---

## Best Practices & Tips 💡

- **오류 처리**:  
  각 단계(연결, 채널 생성, 메시지 전송 등)에서 발생 가능한 오류를 철저하게 처리하여 안정성을 높이세요.
  
- **연결 및 채널 관리**:  
  Kafka와 RabbitMQ의 연결과 채널은 재사용하여 리소스 소모를 줄이세요.
  
- **메시지 신뢰성**:  
  RabbitMQ에서는 메시지 확인(acknowledgement)을 사용해 메시지 손실을 방지하고, Kafka에서는 파티션과 컨슈머 그룹을 적절히 활용하세요.
  
- **확장성**:  
  Kafka의 파티션을 활용하거나, RabbitMQ의 여러 큐/컨슈머를 설정하여 메시징 시스템의 확장성을 확보하세요.
  
- **모니터링**:  
  메시징 시스템의 상태와 성능을 모니터링하여, 장애 발생 시 신속하게 대응할 수 있도록 하세요.

---

## Next Steps

- **고급 패턴 실습**:  
  - 스트리밍, Pub/Sub, 멀티 컨슈머 패턴 등 고급 메시징 패턴을 추가로 학습하세요.
- **서비스 통합**:  
  - Kafka와 RabbitMQ를 마이크로서비스 아키텍처와 통합하여, 서비스 간 비동기 통신을 구현해 보세요.
- **성능 테스트**:  
  - 부하 테스트를 통해 메시징 시스템의 확장성과 내구성을 평가하고, 최적화 방안을 마련하세요.

---

## References 📚

- [Sarama: Go Library for Apache Kafka](https://github.com/Shopify/sarama)
- [RabbitMQ Go Client Documentation](https://pkg.go.dev/github.com/streadway/amqp)
- [Kafka Official Documentation](https://kafka.apache.org/documentation/)
- [RabbitMQ Official Documentation](https://www.rabbitmq.com/documentation.html)
- [Event-Driven Architecture Overview](https://martinfowler.com/articles/201701-event-driven.html)

---

Kafka와 RabbitMQ를 통한 메시징 시스템은 대규모 애플리케이션에서 비동기 처리와 이벤트 기반 아키텍처 구현의 핵심입니다.  
이 자료를 통해 Go 애플리케이션에 안정적이고 확장 가능한 메시징 솔루션을 구축해 보세요! Happy Messaging! 🚀