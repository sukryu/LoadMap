// 02_rabbitmq_consumer.go
//
// 이 파일은 RabbitMQ 서버에서 고급 소비자 기능을 구현한 예제입니다.
// streadway/amqp 라이브러리를 사용하여 RabbitMQ 서버에 연결한 후,
// 내구성 있는 큐를 선언하고, 해당 큐에서 메시지를 소비합니다.
// 메시지 처리는 수동 ACK 방식을 사용하여, 각 메시지의 처리 결과를 RabbitMQ에 전달합니다.
//
// 사용 예:
//   go run 02_rabbitmq_consumer.go
//
// 주의: 실제 운영 환경에서는 연결 URL, 큐 이름, 그리고 메시지 처리 로직을 상황에 맞게 수정하여 사용하세요.

package main

import (
	"log"
	"time"

	"github.com/streadway/amqp"
)

// advancedRMQConsumer는 RabbitMQ 서버에 연결하여 지정된 큐에서 메시지를 소비하는 함수입니다.
// 매개변수:
// - amqpURL: RabbitMQ 연결 URL (예: "amqp://guest:guest@localhost:5672/")
// - consumerQueueName: 메시지를 소비할 큐의 이름
func advancedRMQConsumer(amqpURL string, consumerQueueName string) {
	// RabbitMQ 서버에 연결
	conn, err := amqp.Dial(amqpURL)
	if err != nil {
		log.Fatalf("RabbitMQ 서버 연결 실패: %v", err)
	}
	// 함수 종료 시 연결 종료
	defer func() {
		if err := conn.Close(); err != nil {
			log.Printf("RabbitMQ 연결 종료 중 에러: %v", err)
		}
	}()

	// 연결으로부터 채널 생성 (메시지 소비에 필요)
	channel, err := conn.Channel()
	if err != nil {
		log.Fatalf("RabbitMQ 채널 생성 실패: %v", err)
	}
	defer func() {
		if err := channel.Close(); err != nil {
			log.Printf("RabbitMQ 채널 종료 중 에러: %v", err)
		}
	}()

	// 내구성 있는 큐 선언: 메시지 보존 및 서버 재시작 후에도 큐 유지
	queue, err := channel.QueueDeclare(
		consumerQueueName, // 큐 이름
		true,              // 내구성: true
		false,             // 자동 삭제 비활성화
		false,             // 독점 사용 비활성화
		false,             // no-wait: false (서버 응답을 기다림)
		nil,               // 추가 인자 없음
	)
	if err != nil {
		log.Fatalf("RabbitMQ 큐 선언 실패: %v", err)
	}

	// 큐에서 메시지 소비 시작 (autoAck false: 수동 ACK 사용)
	messages, err := channel.Consume(
		queue.Name,         // 큐 이름
		"advancedConsumer", // 소비자 태그 (고유한 값)
		false,              // autoAck 비활성화
		false,              // 독점 사용 비활성화
		false,              // no-local (RabbitMQ 전용, 사용 안함)
		false,              // no-wait 비활성화
		nil,                // 추가 인자 없음
	)
	if err != nil {
		log.Fatalf("RabbitMQ 소비자 등록 실패: %v", err)
	}

	// 종료 신호를 위한 채널 생성
	doneChannel := make(chan bool)

	// 고루틴을 사용하여 메시지 수신 및 처리
	go func() {
		for msg := range messages {
			// 수신된 메시지 로그 출력
			log.Printf("RabbitMQ 메시지 수신: %s", msg.Body)

			// 메시지 처리 시뮬레이션: 처리 시간 대기 (실제 로직으로 대체 가능)
			time.Sleep(1 * time.Second)

			// 메시지 수동 ACK: 메시지가 성공적으로 처리되었음을 RabbitMQ에 알림
			if err := msg.Ack(false); err != nil {
				log.Printf("메시지 ACK 실패: %v", err)
			} else {
				log.Printf("메시지 ACK 성공: %s", msg.Body)
			}
		}
		// 메시지 채널이 닫히면 완료 신호 전송
		doneChannel <- true
	}()

	// 소비자 실행 시간: 예를 들어 30초 동안 메시지를 소비한 후 종료
	log.Println("RabbitMQ 고급 소비자 예제 실행 중... 메시지 수신 대기")
	select {
	case <-doneChannel:
		log.Println("메시지 소비 완료")
	case <-time.After(30 * time.Second):
		log.Println("지정된 소비 시간 종료, 소비자 종료")
	}
}

func Consumer_manual_ack() {
	// RabbitMQ 연결 URL 및 소비할 큐 이름 설정 (실제 환경에 맞게 수정)
	rmqURL := "amqp://guest:guest@localhost:5672/"
	consumerQueue := "advanced-consumer-queue"

	log.Println("RabbitMQ 고급 소비자 예제 시작...")
	advancedRMQConsumer(rmqURL, consumerQueue)
	log.Println("RabbitMQ 고급 소비자 예제 종료.")
}
