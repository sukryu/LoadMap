// 02_pull_example.go
//
// 이 파일은 Google Cloud Pub/Sub의 Pull Subscription 방식을 이용하여,
// 지정된 구독(subscription)에서 메시지를 수신하는 예제입니다.
// Pub/Sub 클라이언트를 생성하고, 환경 변수로부터 프로젝트 ID를 읽어온 후,
// 지정된 구독에서 메시지를 Pull 방식으로 받아 처리하며, 각 메시지에 대해 ACK를 전송합니다.
//
// 사용 예:
//   go run 02_pull_example.go
//
// 주의: 이 예제를 실행하려면 "GOOGLE_CLOUD_PROJECT" 및 "GOOGLE_APPLICATION_CREDENTIALS" 환경 변수가 올바르게 설정되어 있어야 합니다.

package main

import (
	"context"
	"fmt"
	"log"
	"os"
	"time"

	"cloud.google.com/go/pubsub"
)

// pullPubSubMessages는 지정된 구독(subscriptionID)에서 메시지를 Pull 방식으로 수신하는 함수입니다.
// projectID: Google Cloud 프로젝트 ID
// subscriptionID: 메시지를 수신할 구독 이름
func pullPubSubMessages(projectID, subscriptionID string) {
	// 기본 Context 생성: API 호출 및 메시지 수신에 사용
	ctx := context.Background()

	// Pub/Sub 클라이언트 생성: 지정한 프로젝트 ID로 초기화합니다.
	pubsubClient, err := pubsub.NewClient(ctx, projectID)
	if err != nil {
		log.Fatalf("Pub/Sub 클라이언트 생성 실패: %v", err)
	}
	// 클라이언트 종료를 위해 main 종료 시 Close 호출
	defer pubsubClient.Close()

	// 지정된 구독 ID로 구독 객체를 가져옵니다.
	subscription := pubsubClient.Subscription(subscriptionID)

	// Pull 방식 메시지 수신을 위한 타임아웃 설정: 30초 동안 수신 대기
	ctxWithTimeout, cancel := context.WithTimeout(ctx, 30*time.Second)
	defer cancel()

	// 메시지 수신을 시작합니다.
	// sub.Receive()는 내부적으로 병렬 처리를 수행하며, 각 메시지에 대해 콜백 함수를 호출합니다.
	err = subscription.Receive(ctxWithTimeout, func(ctx context.Context, msg *pubsub.Message) {
		// 수신된 메시지 출력: 메시지 ID와 데이터(바이트 배열을 문자열로 변환)
		log.Printf("Pull 방식 메시지 수신 - 메시지 ID: %s, 데이터: %s", msg.ID, string(msg.Data))

		// 메시지 속성이 있는 경우 출력 (예: 사용자 정의 속성)
		if len(msg.Attributes) > 0 {
			log.Printf("메시지 속성: %v", msg.Attributes)
		}

		// 메시지 처리 완료 후 ACK 전송하여, 해당 메시지가 재전송되지 않도록 함
		msg.Ack()
	})
	if err != nil {
		// Receive가 타임아웃 또는 기타 오류로 종료된 경우 로그 출력
		log.Printf("메시지 수신 중 오류 발생: %v", err)
	} else {
		log.Println("메시지 Pull 방식 수신 완료")
	}
}

func Pull_example() {
	// 환경 변수 "GOOGLE_CLOUD_PROJECT"에서 프로젝트 ID를 읽어옵니다.
	projectID := os.Getenv("GOOGLE_CLOUD_PROJECT")
	if projectID == "" {
		log.Fatal("GOOGLE_CLOUD_PROJECT 환경 변수가 설정되지 않았습니다. 프로젝트 ID를 설정하세요.")
	}

	// 구독 ID를 설정합니다. 이 값은 실제 Pub/Sub 구독 이름으로 수정해야 합니다.
	subscriptionID := "example-subscription-pull"

	fmt.Println("Pub/Sub Pull Subscription 예제 시작...")
	pullPubSubMessages(projectID, subscriptionID)
	fmt.Println("Pub/Sub Pull Subscription 예제 종료.")
}
