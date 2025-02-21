// 04_custom_retry.go
//
// 이 파일은 Google Cloud Pub/Sub의 Pull Subscription을 사용하여,
// 수신된 메시지 처리 시 사용자 정의 재시도 로직(custom retry logic)을 적용하는 예제입니다.
//
// 주요 기능:
// 1. Pub/Sub 클라이언트를 생성하고, 지정된 구독에서 메시지를 Pull 방식으로 수신합니다.
// 2. 각 메시지에 대해 최대 재시도 횟수(maxRetryCount)만큼 처리 시도를 수행합니다.
//    - 메시지 처리에 실패하면, 재시도 횟수를 증가시키고, 일정 시간 대기 후 재시도합니다.
//    - 재시도 후에도 실패할 경우, 메시지를 NACK 처리하여 Pub/Sub가 재전송할 수 있도록 합니다.
// 3. 성공적으로 처리된 메시지는 ACK를 전송하여 중복 처리를 방지합니다.
//
// 사용 예:
//   go run 04_custom_retry.go
//
// 주의: 이 예제를 실행하려면 "GOOGLE_CLOUD_PROJECT" 환경 변수와
//        "GOOGLE_APPLICATION_CREDENTIALS" 환경 변수가 올바르게 설정되어 있어야 합니다.

package main

import (
	"context"
	"errors"
	"fmt"
	"log"
	"math/rand"
	"os"
	"strconv"
	"time"

	"cloud.google.com/go/pubsub"
)

// processMessageWithRetry는 단일 메시지에 대해 사용자 정의 재시도 로직을 수행하는 함수입니다.
// msgData: 처리할 메시지 데이터 (문자열)
// maxRetry: 최대 재시도 횟수
// Returns: 처리 성공 시 nil, 최종 실패 시 에러 반환
func processMessageWithRetry(msgData string, maxRetry int) error {
	// 재시도 카운터 초기화
	var attempt int
	// 무작위 실패 시뮬레이션을 위해 시드 초기화
	rand.New(rand.NewSource(time.Now().UnixNano()))

	// 최대 재시도 횟수까지 루프 수행
	for attempt = 1; attempt <= maxRetry; attempt++ {
		// 예제 처리 로직: 메시지 데이터를 정수로 변환하여 2배 값을 계산하는 작업
		// 여기서는 50% 확률로 처리 실패를 시뮬레이션합니다.
		if rand.Intn(100) < 50 {
			// 실패 시 에러 반환
			log.Printf("처리 시도 #%d 실패 (메시지: %s)", attempt, msgData)
		} else {
			// 성공 시 처리 결과를 로그로 출력
			num, err := strconv.Atoi(msgData)
			if err != nil {
				// 문자열을 정수로 변환하는 데 실패하면 재시도
				log.Printf("정수 변환 실패 시도 #%d: %v", attempt, err)
			} else {
				result := num * 2
				log.Printf("처리 성공 (시도 #%d): 입력=%d, 결과=%d", attempt, num, result)
				return nil
			}
		}
		// 재시도 전 일정 시간 대기 (ex: 1초)
		time.Sleep(1 * time.Second)
	}
	return errors.New("최대 재시도 횟수 초과로 메시지 처리 실패")
}

// customRetryReceiver는 Pub/Sub 구독에서 메시지를 Pull 방식으로 수신하고,
// 각 메시지에 대해 processMessageWithRetry 함수를 호출하여 재시도 로직을 적용합니다.
// projectID: Google Cloud 프로젝트 ID
// subscriptionID: 메시지를 수신할 구독 이름
func customRetryReceiver(projectID, subscriptionID string) {
	ctx := context.Background()

	// Pub/Sub 클라이언트 생성
	client, err := pubsub.NewClient(ctx, projectID)
	if err != nil {
		log.Fatalf("Pub/Sub 클라이언트 생성 실패: %v", err)
	}
	defer client.Close()

	// 구독 객체 가져오기
	sub := client.Subscription(subscriptionID)
	// 수신 설정 조정 (필요에 따라)
	sub.ReceiveSettings.MaxOutstandingMessages = 10

	log.Printf("재시도 로직 적용 메시지 수신 시작: 구독 %q", subscriptionID)

	// 수신 컨텍스트 생성: 60초 동안 메시지 수신
	ctxWithTimeout, cancel := context.WithTimeout(ctx, 60*time.Second)
	defer cancel()

	// 메시지 수신 및 처리
	err = sub.Receive(ctxWithTimeout, func(ctx context.Context, msg *pubsub.Message) {
		// 메시지 처리 시도: 최대 3회 재시도
		const maxRetryCount = 3
		messageText := string(msg.Data)
		log.Printf("수신된 메시지: ID=%s, 데이터=%s", msg.ID, messageText)

		err := processMessageWithRetry(messageText, maxRetryCount)
		if err != nil {
			// 최종 처리 실패 시, 메시지를 NACK 처리하여 재전송 요청
			log.Printf("메시지 처리 실패 (ID=%s): %v", msg.ID, err)
			msg.Nack()
		} else {
			// 성공적으로 처리된 경우, 메시지 ACK 전송
			msg.Ack()
		}
	})
	if err != nil {
		log.Printf("메시지 수신 중 오류 발생: %v", err)
	} else {
		log.Println("재시도 로직 적용 메시지 수신 완료")
	}
}

func Custom_retry() {
	// 환경 변수 "GOOGLE_CLOUD_PROJECT"에서 프로젝트 ID를 가져옵니다.
	projectID := os.Getenv("GOOGLE_CLOUD_PROJECT")
	if projectID == "" {
		log.Fatal("GOOGLE_CLOUD_PROJECT 환경 변수가 설정되지 않았습니다. 프로젝트 ID를 설정하세요.")
	}

	// 구독 ID 설정: 실제 Pub/Sub 구독 이름으로 수정 필요
	subscriptionID := "custom-retry-subscription"

	fmt.Println("Pub/Sub Custom Retry 예제 시작...")
	customRetryReceiver(projectID, subscriptionID)
	fmt.Println("Pub/Sub Custom Retry 예제 종료.")
}
