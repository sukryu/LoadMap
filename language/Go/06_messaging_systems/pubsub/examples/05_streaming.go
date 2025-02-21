// 05_streaming_example.go
//
// 이 파일은 Google Cloud Pub/Sub를 사용하여 실시간 스트리밍 처리를 구현하는 예제입니다.
// 주요 기능:
// 1. Pub/Sub 클라이언트를 생성하고, 지정된 구독에서 메시지를 지속적으로 Pull 방식으로 수신합니다.
// 2. 수신된 각 메시지는 별도의 고루틴(워커 풀)을 통해 병렬로 처리됩니다.
// 3. 메시지 처리 로직은 간단한 예제로, 메시지 데이터를 대문자로 변환한 후 로그로 출력합니다.
// 4. 처리 완료 후 각 메시지에 대해 ACK를 전송하여, 중복 처리를 방지합니다.
//
// 사용 예:
//   go run 05_streaming_example.go
//
// 주의: 이 예제를 실행하려면 "GOOGLE_CLOUD_PROJECT" 및 "GOOGLE_APPLICATION_CREDENTIALS" 환경 변수가 올바르게 설정되어 있어야 합니다.

package main

import (
	"context"
	"log"
	"os"
	"strings"
	"sync"
	"time"

	"cloud.google.com/go/pubsub"
)

// workerPoolSize는 동시에 실행할 워커의 최대 수를 정의합니다.
const workerPoolSize = 5

// processStreamMessage는 수신된 Pub/Sub 메시지를 처리하는 워커 함수입니다.
// workerID: 각 워커를 식별하기 위한 고유 ID
// msg: 처리할 Pub/Sub 메시지
func processStreamMessage(workerID int, msg *pubsub.Message) {
	// 메시지 수신 로그 출력
	log.Printf("[Worker %d] 수신된 메시지 ID: %s, 데이터: %s", workerID, msg.ID, string(msg.Data))

	// 예제 처리 로직: 메시지 데이터를 대문자로 변환
	processedData := strings.ToUpper(string(msg.Data))
	log.Printf("[Worker %d] 처리 결과: %s", workerID, processedData)

	// 메시지 처리 완료 후 ACK 전송하여, 해당 메시지가 재전송되지 않도록 함
	msg.Ack()
	log.Printf("[Worker %d] ACK 전송 완료: 메시지 ID %s", workerID, msg.ID)
}

// streamingReceiver는 지정된 Pub/Sub 구독에서 메시지를 지속적으로 Pull 방식으로 수신하고,
// 각 메시지를 워커 풀을 통해 병렬로 처리합니다.
// projectID: Google Cloud 프로젝트 ID
// subscriptionID: 메시지를 Pull할 구독 이름
func streamingReceiver(projectID, subscriptionID string) {
	ctx := context.Background()

	// Pub/Sub 클라이언트 생성
	client, err := pubsub.NewClient(ctx, projectID)
	if err != nil {
		log.Fatalf("Pub/Sub 클라이언트 생성 실패: %v", err)
	}
	defer client.Close()

	// 구독 객체 가져오기
	sub := client.Subscription(subscriptionID)
	// 수신 설정 조정: 한 번에 처리할 최대 메시지 수 설정
	sub.ReceiveSettings.MaxOutstandingMessages = 20

	log.Printf("스트리밍 수신 시작: 구독 %q", subscriptionID)

	// 워커 풀을 위한 WaitGroup 생성
	var wg sync.WaitGroup

	// Pub/Sub 메시지 수신 및 처리 (sub.Receive는 블록 함수)
	err = sub.Receive(ctx, func(ctx context.Context, msg *pubsub.Message) {
		// WaitGroup에 추가 후, 고루틴에서 메시지 처리
		wg.Add(1)
		go func(receivedMsg *pubsub.Message) {
			// 워커 ID는 간단한 카운터 대신 현재 시간의 나노초 값을 이용하여 생성 (예시)
			workerID := int(time.Now().UnixNano() % 1000)
			processStreamMessage(workerID, receivedMsg)
			wg.Done()
		}(msg)
	})
	if err != nil {
		log.Printf("스트리밍 수신 중 오류 발생: %v", err)
	}

	// 모든 워커가 메시지 처리를 완료할 때까지 대기
	wg.Wait()
	log.Println("모든 메시지 처리 완료. 스트리밍 수신 종료.")
}

func Streaming() {
	// 환경 변수 "GOOGLE_CLOUD_PROJECT"에서 프로젝트 ID를 읽어옵니다.
	projectID := os.Getenv("GOOGLE_CLOUD_PROJECT")
	if projectID == "" {
		log.Fatal("GOOGLE_CLOUD_PROJECT 환경 변수가 설정되지 않았습니다. 프로젝트 ID를 설정하세요.")
	}

	// 구독 ID 설정: 실제 Pub/Sub 구독 이름으로 수정 필요
	subscriptionID := "streaming-example-subscription"

	log.Println("Pub/Sub 스트리밍 처리 예제 시작...")
	streamingReceiver(projectID, subscriptionID)
	log.Println("Pub/Sub 스트리밍 처리 예제 종료.")
}
