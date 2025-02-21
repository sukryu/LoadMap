// 01_rabbitmq_publisher.go
//
// 이 파일은 RabbitMQ 서버에 고급 메시지를 게시하는 예제입니다.
// 이 예제에서는 streadway/amqp 라이브러리를 사용하여 RabbitMQ 서버와 연결을 수립하고,
// 내구성 있는 큐를 선언한 후, 반복문을 통해 여러 메시지를 큐에 전송합니다.
// 각 메시지는 전송 후 성공 또는 오류 메시지를 로그로 출력합니다.
//
// 사용 예:
//   go run 01_rabbitmq_publisher.go
//
// 주의: 실제 운영 환경에서는 연결 URL, 큐 이름, 메시지 내용 등을 적절히 수정하여 사용하세요.

package main

import (
	"fmt"
	"log"
	"time"

	"github.com/streadway/amqp"
)

// advancedRabbitmqPublisher는 RabbitMQ 서버에 연결하여 지정된 큐에 여러 메시지를 게시합니다.
// 매개변수:
// - amqpConnURL: RabbitMQ 연결 URL (예: "amqp://guest:guest@localhost:5672/")
// - targetQueueName: 메시지를 게시할 큐의 이름
func advancedRabbitmqPublisher(amqpConnURL, targetQueueName string) {
	// RabbitMQ 서버에 연결을 시도합니다.
	conn, err := amqp.Dial(amqpConnURL)
	if err != nil {
		log.Fatalf("RabbitMQ 서버 연결 실패: %v", err)
	}
	// 함수 종료 시 연결을 안전하게 종료합니다.
	defer func() {
		if err := conn.Close(); err != nil {
			log.Printf("RabbitMQ 연결 종료 중 에러: %v", err)
		}
	}()

	// 연결로부터 채널 생성: 메시지 전송에 필요한 채널을 엽니다.
	channel, err := conn.Channel()
	if err != nil {
		log.Fatalf("RabbitMQ 채널 생성 실패: %v", err)
	}
	defer func() {
		if err := channel.Close(); err != nil {
			log.Printf("RabbitMQ 채널 종료 중 에러: %v", err)
		}
	}()

	// 내구성 있는 큐 선언: 메시지 보존 및 서버 재시작 후에도 큐가 유지됩니다.
	queue, err := channel.QueueDeclare(
		targetQueueName, // 큐 이름
		true,            // 내구성 활성화: 서버 재시작 후에도 큐 유지
		false,           // 자동 삭제 비활성화
		false,           // 독점 사용 비활성화
		false,           // no-wait: 서버 응답을 기다림
		nil,             // 추가 매개변수 없음
	)
	if err != nil {
		log.Fatalf("RabbitMQ 큐 선언 실패: %v", err)
	}

	// 10개의 메시지를 반복하여 큐에 게시합니다.
	for msgIndex := 0; msgIndex < 10; msgIndex++ {
		// 고유한 메시지 본문 생성: 메시지 번호와 타임스탬프 포함
		messageContent := fmt.Sprintf("Advanced RabbitMQ message #%d sent at %s", msgIndex, time.Now().Format(time.RFC3339))
		// amqp.Publishing 구조체에 메시지 설정
		pubMessage := amqp.Publishing{
			ContentType: "text/plain",           // 메시지 형식: 텍스트
			Body:        []byte(messageContent), // 메시지 본문 (바이트 배열)
		}

		// 메시지 게시: 기본 익스체인지를 사용하고, 라우팅 키로 큐 이름을 지정합니다.
		err = channel.Publish(
			"",         // 익스체인지 (빈 문자열은 기본 익스체인지 사용)
			queue.Name, // 라우팅 키: 선언된 큐 이름 사용
			false,      // mandatory 플래그 (메시지가 라우팅되지 않을 경우 반환하지 않음)
			false,      // immediate 플래그 (즉시 전송되지 않을 경우 반환하지 않음)
			pubMessage, // 게시할 메시지
		)
		if err != nil {
			log.Printf("RabbitMQ 메시지 전송 실패 (메시지 #%d): %v", msgIndex, err)
		} else {
			log.Printf("RabbitMQ 메시지 전송 성공: %s", messageContent)
		}

		// 각 메시지 전송 사이에 500밀리초 대기
		time.Sleep(500 * time.Millisecond)
	}
}

func Publisher_confirm() {
	// RabbitMQ 연결 URL과 대상 큐 이름을 설정합니다.
	// 실제 운영 환경에 맞게 해당 값을 수정하세요.
	rabbitmqURL := "amqp://guest:guest@localhost:5672/"
	queueName := "advanced-publisher-queue"

	log.Println("RabbitMQ 고급 퍼블리셔 예제 시작...")
	advancedRabbitmqPublisher(rabbitmqURL, queueName)
	log.Println("RabbitMQ 고급 퍼블리셔 예제 종료.")
}
