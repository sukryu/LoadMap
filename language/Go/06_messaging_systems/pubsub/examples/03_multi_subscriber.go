// 03_streaming_example.go
//
// 이 파일은 Google Cloud Pub/Sub를 사용하여 실시간 스트리밍 처리를 구현하는 예제입니다.
// 이 예제에서는 지정된 구독(subscription)에서 메시지를 지속적으로 Pull 방식으로 수신하고,
// 각 메시지를 간단하게 처리(예: 텍스트 변환 및 로그 출력)하는 스트리밍 파이프라인을 구현합니다.
// 메시지 수신은 별도의 고루틴에서 처리되어, 응답 시간 지연 없이 동시에 여러 메시지를 처리할 수 있습니다.
//
// 사용 예:
//   go run 03_streaming_example.go
//
// 주의: 이 예제를 실행하려면 "GOOGLE_CLOUD_PROJECT" 및 "GOOGLE_APPLICATION_CREDENTIALS" 환경 변수가 올바르게 설정되어 있어야 합니다.

package main

import (
	"context"
	"fmt"
	"log"
	"os"
	"strings"
	"time"

	"cloud.google.com/go/pubsub"
)

// streamProcessMessage는 수신된 메시지를 처리하는 함수입니다.
// 메시지의 데이터를 대문자로 변환한 후, 처리 결과를 로그에 출력합니다.
func streamProcessMessage(msg *pubsub.Message) {
	// 원본 메시지 데이터 로그 출력
	log.Printf("수신된 메시지 ID: %s, 데이터: %s", msg.ID, string(msg.Data))

	// 메시지 데이터 변환: 예제에서는 대문자로 변환
	transformedData := strings.ToUpper(string(msg.Data))
	log.Printf("변환된 메시지 데이터: %s", transformedData)

	// 추가 처리가 필요한 경우 이 부분에서 구현할 수 있습니다.
	// 예: 데이터 집계, 외부 API 호출 등

	// 메시지 처리 완료 후 반드시 ACK 전송하여 재전송 방지
	msg.Ack()
}

// streamReceiver continuously pulls messages from the given subscription
// and processes them using streamProcessMessage.
// projectID: Google Cloud 프로젝트 ID
// subscriptionID: 메시지를 수신할 구독 이름
func streamReceiver(projectID, subscriptionID string) {
	// 기본 Context 생성: API 호출에 사용
	ctx := context.Background()

	// Pub/Sub 클라이언트 생성
	client, err := pubsub.NewClient(ctx, projectID)
	if err != nil {
		log.Fatalf("Pub/Sub 클라이언트 생성 실패: %v", err)
	}
	defer client.Close()

	// 지정된 구독 객체 가져오기
	sub := client.Subscription(subscriptionID)

	// ReceiveSettings 조정: 스트리밍 처리에 적합한 설정 적용
	sub.ReceiveSettings.MaxOutstandingMessages = 10
	sub.ReceiveSettings.MaxExtension = 20 * time.Second

	log.Printf("스트리밍 처리 시작: 구독 %q에서 메시지 수신 대기 중...", subscriptionID)

	// subscription.Receive는 내부적으로 다수의 고루틴을 생성하여 메시지를 병렬 처리합니다.
	// 이 함수는 컨텍스트가 취소되거나 오류가 발생할 때까지 계속 실행됩니다.
	err = sub.Receive(ctx, func(ctx context.Context, msg *pubsub.Message) {
		// 수신된 메시지를 처리하는 함수 호출
		streamProcessMessage(msg)
	})
	if err != nil {
		log.Fatalf("메시지 스트리밍 처리 중 오류 발생: %v", err)
	}
}

func Multi_subscriber() {
	// 환경 변수 "GOOGLE_CLOUD_PROJECT"에서 프로젝트 ID를 읽어옵니다.
	projectID := os.Getenv("GOOGLE_CLOUD_PROJECT")
	if projectID == "" {
		log.Fatal("GOOGLE_CLOUD_PROJECT 환경 변수가 설정되지 않았습니다. 프로젝트 ID를 설정하세요.")
	}

	// 구독 ID를 설정합니다. 이 값은 실제 Pub/Sub 구독 이름으로 수정해야 합니다.
	subscriptionID := "streaming-subscription"

	fmt.Println("Pub/Sub 스트리밍 처리 예제 시작...")
	// 스트리밍 메시지 수신 및 처리 함수 호출 (무한 실행됨)
	streamReceiver(projectID, subscriptionID)
	fmt.Println("Pub/Sub 스트리밍 처리 예제 종료.")
}
