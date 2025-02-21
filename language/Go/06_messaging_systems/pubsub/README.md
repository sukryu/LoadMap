# Pub/Sub Messaging in Go: Real-Time Event Distribution ☁️

이 디렉토리는 Go를 사용하여 **Pub/Sub 시스템**과 상호작용하는 방법을 다룹니다.  
주로 Google Cloud Pub/Sub를 예시로 들어, 토픽 생성, 메시지 게시 및 구독, 그리고 비동기 이벤트 처리와 관련된 실습 및 Best Practice를 학습할 수 있습니다.

---

## What You'll Learn 🎯

- **Pub/Sub 기본 개념**:  
  - Pub/Sub 모델의 개요, 토픽(topic)과 구독(subscription)의 역할 및 메시지 흐름 이해

- **Go에서의 Pub/Sub 연동**:  
  - Google Cloud Pub/Sub Go 클라이언트를 사용하여, 토픽에 메시지 게시(publish) 및 구독(subscription) 기능 구현
  - 메시지 처리, 재시도 및 ACK/NACK 메커니즘 활용

- **실무 적용 전략**:  
  - 분산 환경에서 실시간 이벤트 기반 처리를 위한 설계 및 구현 기법  
  - 에러 처리, 동시성 제어, 성능 최적화 및 모니터링 전략

---

## Directory Structure 📁

```plaintext
06-messaging-systems/
└── pubsub/
    ├── main.go           # 기본 Pub/Sub 예제 (토픽에 메시지 게시 및 구독하여 수신)
    ├── examples/         # 고급 예제들이 포함된 폴더
    │   ├── 01_push_example.go       # Push Subscription을 활용한 HTTP 서버 예제
    │   ├── 02_pull_example.go       # Pull Subscription을 통한 메시지 수신 예제
    │   ├── 03_streaming_example.go  # 스트리밍 처리: 메시지 수신 후 변환 및 병렬 처리 예제
    │   ├── 04_custom_retry.go       # 사용자 정의 재시도 로직 적용 예제
    └── README.md         # 이 문서

```

- **main.go**: Google Cloud Pub/Sub를 활용하여 토픽에 메시지를 게시하고, 구독을 통해 메시지를 처리하는 기본 예제가 포함되어 있습니다.
- **examples/**: Push 및 Pull 방식, 멀티 구독, 동시성 처리 등 다양한 Pub/Sub 시나리오를 다룬 예제 코드들이 포함되어 있습니다.

---

## Getting Started 🚀

### 1. Prerequisites
- Go 최신 버전 설치: [Download Go](https://go.dev/dl/)
- Google Cloud Pub/Sub를 사용하기 위한 Google Cloud 계정 및 프로젝트 설정
- Pub/Sub API 활성화 및 인증 파일(JSON) 설정 (환경 변수 `GOOGLE_APPLICATION_CREDENTIALS` 사용)
- 필요한 라이브러리 설치:
  ```bash
  go get -u cloud.google.com/go/pubsub
  ```

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/06-messaging-systems/pubsub
```

### 3. 예제 코드 실행
```bash
go run main.go
```
- 예제 코드를 실행하여, Pub/Sub 토픽에 메시지를 게시하고, 구독자가 해당 메시지를 받아 처리하는 과정을 확인하세요.

---

## Example Code Snippet 📄

아래는 간단한 Google Cloud Pub/Sub 예제입니다.

**main.go**
```go
package main

import (
    "context"
    "fmt"
    "log"
    "os"
    "time"

    "cloud.google.com/go/pubsub"
)

func main() {
    ctx := context.Background()

    // Google Cloud 프로젝트 ID (환경 변수 또는 직접 지정)
    projectID := os.Getenv("GOOGLE_CLOUD_PROJECT")
    if projectID == "" {
        log.Fatal("GOOGLE_CLOUD_PROJECT 환경 변수를 설정하세요.")
    }

    // Pub/Sub 클라이언트 생성
    client, err := pubsub.NewClient(ctx, projectID)
    if err != nil {
        log.Fatalf("Pub/Sub 클라이언트 생성 실패: %v", err)
    }
    defer client.Close()

    // 토픽과 구독 설정
    topicName := "example-topic"
    subName := "example-subscription"

    topic := client.Topic(topicName)
    // 토픽이 존재하지 않으면 생성
    exists, err := topic.Exists(ctx)
    if err != nil {
        log.Fatalf("토픽 확인 실패: %v", err)
    }
    if !exists {
        topic, err = client.CreateTopic(ctx, topicName)
        if err != nil {
            log.Fatalf("토픽 생성 실패: %v", err)
        }
    }

    sub := client.Subscription(subName)
    exists, err = sub.Exists(ctx)
    if err != nil {
        log.Fatalf("구독 확인 실패: %v", err)
    }
    if !exists {
        sub, err = client.CreateSubscription(ctx, subName, pubsub.SubscriptionConfig{
            Topic: topic,
        })
        if err != nil {
            log.Fatalf("구독 생성 실패: %v", err)
        }
    }

    // 메시지 게시 예제
    result := topic.Publish(ctx, &pubsub.Message{
        Data: []byte("Hello from Go Pub/Sub!"),
    })
    id, err := result.Get(ctx)
    if err != nil {
        log.Fatalf("메시지 게시 실패: %v", err)
    }
    fmt.Printf("메시지 게시 성공, 메시지 ID: %s\n", id)

    // 구독을 통한 메시지 수신 예제 (단일 메시지 처리 후 종료)
    ctx, cancel := context.WithTimeout(ctx, 10*time.Second)
    defer cancel()
    err = sub.Receive(ctx, func(ctx context.Context, msg *pubsub.Message) {
        fmt.Printf("메시지 수신: %s\n", string(msg.Data))
        msg.Ack() // 메시지 확인
        cancel()  // 한 건 처리 후 종료
    })
    if err != nil {
        log.Fatalf("메시지 수신 실패: %v", err)
    }
}
```

이 예제는 Pub/Sub 토픽에 메시지를 게시하고, 지정된 구독을 통해 메시지를 수신하는 기본적인 흐름을 보여줍니다.

---

## Best Practices & Tips 💡

- **인증 관리**:  
  - Google Cloud 인증 파일을 안전하게 관리하고, `GOOGLE_APPLICATION_CREDENTIALS` 환경 변수를 활용하여 애플리케이션에 적용하세요.
  
- **메시지 처리**:  
  - 구독자에서는 반드시 메시지 확인(`Ack`)을 수행하여, 중복 처리나 메시지 손실을 방지하세요.
  
- **동시성 제어**:  
  - Pub/Sub는 높은 동시성을 지원하므로, 메시지 처리 시 적절한 동시성 제어를 구현하여 시스템 부하를 분산하세요.
  
- **오류 및 재시도 전략**:  
  - 게시 및 구독 작업에서 발생하는 오류에 대해 적절한 재시도 로직을 구현하세요.
  
- **모니터링**:  
  - Pub/Sub 메시지 흐름과 지연 시간을 모니터링하여, 시스템 성능과 신뢰성을 지속적으로 점검하세요.

---

## Next Steps

- **고급 사용 사례**:  
  - Push 구독, 멀티 구독자 및 메시지 필터링 등의 고급 기능을 학습하고 실습해 보세요.
  
- **통합 적용**:  
  - Pub/Sub를 마이크로서비스 아키텍처와 통합하여, 이벤트 기반 시스템을 구현하고 확장성을 확보하세요.
  
- **성능 테스트**:  
  - 부하 테스트 도구를 활용해 Pub/Sub 시스템의 성능과 확장성을 평가하고, 최적화 전략을 마련하세요.

---

## References 📚

- [Google Cloud Pub/Sub Documentation](https://cloud.google.com/pubsub/docs)
- [Cloud Pub/Sub Go Client Library](https://pkg.go.dev/cloud.google.com/go/pubsub)
- [Event-Driven Architecture Overview](https://martinfowler.com/articles/201701-event-driven.html)
- [Google Cloud Authentication Guide](https://cloud.google.com/docs/authentication)

---

Google Cloud Pub/Sub를 통한 이벤트 기반 메시징은 대규모 분산 시스템에서 실시간 데이터 처리를 가능하게 합니다.  
이 자료를 통해 Go 애플리케이션에 Pub/Sub를 효과적으로 통합하고, 확장 가능한 이벤트 처리 시스템을 구축해 보세요! Happy Pub/Sub Coding! ☁️🚀