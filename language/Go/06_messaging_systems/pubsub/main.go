// main.go
//
// 이 파일은 Google Cloud Pub/Sub를 활용한 Go 기반 서버리스 메시징 예제입니다.
// 주요 기능:
// 1. Google Cloud 프로젝트 ID를 기반으로 Pub/Sub 클라이언트 생성
// 2. 지정된 토픽이 존재하는지 확인하고, 없으면 생성
// 3. 지정된 구독이 존재하는지 확인하고, 없으면 생성
// 4. 토픽에 메시지를 게시 (Publish)
// 5. 구독을 통해 메시지를 Pull 방식으로 수신 (Receive)
// 각 단계별로 상세한 주석을 추가하여, 코드의 동작 원리와 설정 목적을 명확하게 설명합니다.

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
	// 1. Context 생성
	// 모든 Pub/Sub API 호출에 사용할 기본 Context를 생성합니다.
	ctx := context.Background()

	// 2. Google Cloud 프로젝트 ID 설정
	// 환경 변수 "GOOGLE_CLOUD_PROJECT"에 프로젝트 ID가 설정되어 있어야 합니다.
	projectID := os.Getenv("GOOGLE_CLOUD_PROJECT")
	if projectID == "" {
		log.Fatal("GOOGLE_CLOUD_PROJECT 환경 변수가 설정되지 않았습니다. 프로젝트 ID를 설정하세요.")
	}

	// 3. Pub/Sub 클라이언트 생성
	// 지정한 프로젝트 ID를 사용하여 Pub/Sub 클라이언트를 초기화합니다.
	client, err := pubsub.NewClient(ctx, projectID)
	if err != nil {
		log.Fatalf("Pub/Sub 클라이언트 생성 실패: %v", err)
	}
	// 클라이언트 종료를 위해 main 함수 종료 시 Close 호출
	defer client.Close()

	// 4. 토픽 이름과 구독 이름 설정
	topicName := "example-topic"               // 메시지를 게시할 토픽 이름
	subscriptionName := "example-subscription" // 메시지를 구독할 구독 이름

	// 5. 토픽 존재 여부 확인 및 생성
	// 기존 토픽이 있는지 확인한 후, 없으면 새로 생성합니다.
	topic := client.Topic(topicName)
	topicExists, err := topic.Exists(ctx)
	if err != nil {
		log.Fatalf("토픽 존재 여부 확인 실패: %v", err)
	}
	if !topicExists {
		// 토픽 생성: 성공 시 토픽 객체 반환
		topic, err = client.CreateTopic(ctx, topicName)
		if err != nil {
			log.Fatalf("토픽 생성 실패: %v", err)
		}
		log.Printf("토픽 %q 생성 완료.", topicName)
	} else {
		log.Printf("토픽 %q 이미 존재합니다.", topicName)
	}

	// 6. 구독 존재 여부 확인 및 생성
	// 지정된 구독이 있는지 확인하고, 없으면 새로 생성합니다.
	sub := client.Subscription(subscriptionName)
	subExists, err := sub.Exists(ctx)
	if err != nil {
		log.Fatalf("구독 존재 여부 확인 실패: %v", err)
	}
	if !subExists {
		// 구독 생성: 토픽과 구독 설정(예: ACK 대기 시간) 지정
		sub, err = client.CreateSubscription(ctx, subscriptionName, pubsub.SubscriptionConfig{
			Topic:       topic,
			AckDeadline: 10 * time.Second, // 메시지 ACK 대기 시간 설정
		})
		if err != nil {
			log.Fatalf("구독 생성 실패: %v", err)
		}
		log.Printf("구독 %q 생성 완료.", subscriptionName)
	} else {
		log.Printf("구독 %q 이미 존재합니다.", subscriptionName)
	}

	// 7. 메시지 게시 (Publish)
	// 현재 시간 정보를 포함한 메시지를 생성하여 토픽에 게시합니다.
	messageText := fmt.Sprintf("Hello from Go Pub/Sub at %s", time.Now().Format(time.RFC3339))
	result := topic.Publish(ctx, &pubsub.Message{
		Data: []byte(messageText), // 메시지 데이터 (바이트 배열)
	})
	// 게시 결과 대기: 메시지 ID가 반환되면 게시가 성공한 것으로 간주합니다.
	messageID, err := result.Get(ctx)
	if err != nil {
		log.Fatalf("메시지 게시 실패: %v", err)
	}
	log.Printf("메시지 게시 성공, 메시지 ID: %s", messageID)

	// 8. 메시지 수신 (Receive)
	// 일정 시간 동안 구독에서 메시지를 Pull 방식으로 수신합니다.
	// 타임아웃 컨텍스트를 생성하여, 응답 대기 시간을 제한합니다.
	pullCtx, cancel := context.WithTimeout(ctx, 20*time.Second)
	defer cancel()

	// sub.Receive() 함수는 메시지가 도착할 때까지 블록되며, 콜백 함수에서 메시지 처리를 수행합니다.
	err = sub.Receive(pullCtx, func(ctx context.Context, m *pubsub.Message) {
		// 수신된 메시지 데이터 출력
		log.Printf("수신된 메시지: %s", string(m.Data))
		// 메시지 처리 후 반드시 ACK를 호출하여 재전송을 방지합니다.
		m.Ack()
		// 여기서는 첫 번째 메시지 수신 후 바로 종료하도록 컨텍스트 취소
		cancel()
	})
	if err != nil {
		log.Printf("메시지 수신 중 오류 발생: %v", err)
	} else {
		log.Println("메시지 수신 완료.")
	}
}
