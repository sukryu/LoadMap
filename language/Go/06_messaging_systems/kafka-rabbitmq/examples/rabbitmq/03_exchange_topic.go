// 03_rabbitmq_exchange_topic.go
//
// 이 파일은 RabbitMQ에서 토픽 익스체인지를 사용하여 메시지를 라우팅하는 예제입니다.
// 이 예제에서는 "topic_logs_exchange"라는 이름의 토픽 익스체인지를 선언한 후,
// 두 개의 서로 다른 라우팅 키를 가진 메시지를 게시하고, 큐와 바인딩하여 메시지가 어떻게 라우팅되는지 확인합니다.
// 사용 예:
//   go run 03_rabbitmq_exchange_topic.go
//
// 주의: 실제 운영 환경에서는 연결 URL, 익스체인지 이름, 라우팅 키 등을 적절히 수정하여 사용하세요.

package main

import (
	"log"
	"time"

	"github.com/streadway/amqp"
)

// advancedRMQTopicExchangePublisher는 RabbitMQ 토픽 익스체인지를 사용하여 메시지를 게시합니다.
// 매개변수:
// - amqpURL: RabbitMQ 연결 URL (예: "amqp://guest:guest@localhost:5672/")
// - exchangeName: 토픽 익스체인지 이름 (예: "topic_logs_exchange")
// - routingKey1, routingKey2: 서로 다른 라우팅 키로 메시지를 게시하여 라우팅 동작을 확인합니다.
func advancedRMQTopicExchangePublisher(amqpURL, exchangeName, routingKey1, routingKey2 string) {
	// RabbitMQ 서버에 연결
	conn, err := amqp.Dial(amqpURL)
	if err != nil {
		log.Fatalf("RabbitMQ 서버 연결 실패: %v", err)
	}
	defer func() {
		if err := conn.Close(); err != nil {
			log.Printf("RabbitMQ 연결 종료 중 에러: %v", err)
		}
	}()

	// 연결으로부터 채널 생성
	ch, err := conn.Channel()
	if err != nil {
		log.Fatalf("RabbitMQ 채널 생성 실패: %v", err)
	}
	defer func() {
		if err := ch.Close(); err != nil {
			log.Printf("RabbitMQ 채널 종료 중 에러: %v", err)
		}
	}()

	// 토픽 익스체인지 선언: "topic" 타입 익스체인지로 설정하여 라우팅 키 기반 메시지 라우팅을 지원합니다.
	err = ch.ExchangeDeclare(
		exchangeName, // 익스체인지 이름
		"topic",      // 익스체인지 타입: topic
		true,         // 내구성: 재시작 후에도 유지
		false,        // 자동 삭제: false
		false,        // 내부 익스체인지: false
		false,        // no-wait: false (응답을 기다림)
		nil,          // 추가 인자 없음
	)
	if err != nil {
		log.Fatalf("토픽 익스체인지 선언 실패: %v", err)
	}

	// 예제용 큐 선언: 내구성 있는 큐 생성
	queueName := "advanced-topic-queue"
	q, err := ch.QueueDeclare(
		queueName, // 큐 이름
		true,      // 내구성 활성화
		false,     // 자동 삭제 비활성화
		false,     // 독점 사용 비활성화
		false,     // no-wait: false
		nil,       // 추가 인자 없음
	)
	if err != nil {
		log.Fatalf("큐 선언 실패: %v", err)
	}

	// 큐를 토픽 익스체인지에 바인딩
	// 예제에서는 routingKey1을 사용하여 바인딩합니다.
	err = ch.QueueBind(
		q.Name,       // 큐 이름
		routingKey1,  // 라우팅 키 (바인딩 패턴)
		exchangeName, // 익스체인지 이름
		false,        // no-wait: false
		nil,          // 추가 인자 없음
	)
	if err != nil {
		log.Fatalf("큐 바인딩 실패: %v", err)
	}

	// 두 개의 다른 라우팅 키를 사용하여 메시지를 게시합니다.
	// 첫 번째 메시지: routingKey1 사용 (큐에 바인딩된 패턴과 일치하므로 큐로 전달됨)
	message1 := "Message with routing key: " + routingKey1
	err = ch.Publish(
		exchangeName, // 익스체인지 이름
		routingKey1,  // 라우팅 키
		false,        // mandatory: false
		false,        // immediate: false
		amqp.Publishing{
			ContentType: "text/plain",
			Body:        []byte(message1),
		},
	)
	if err != nil {
		log.Fatalf("메시지 게시 실패 (라우팅키1): %v", err)
	}
	log.Printf("메시지 게시 성공: %s", message1)

	// 두 번째 메시지: routingKey2 사용 (큐 바인딩과 일치하지 않으므로, 라우팅되지 않음)
	message2 := "Message with routing key: " + routingKey2
	err = ch.Publish(
		exchangeName, // 익스체인지 이름
		routingKey2,  // 라우팅 키
		false,        // mandatory: false
		false,        // immediate: false
		amqp.Publishing{
			ContentType: "text/plain",
			Body:        []byte(message2),
		},
	)
	if err != nil {
		log.Fatalf("메시지 게시 실패 (라우팅키2): %v", err)
	}
	log.Printf("메시지 게시 성공: %s", message2)

	// 메시지 전송 후 잠시 대기하여, 게시 결과를 모니터링
	time.Sleep(2 * time.Second)
}

func Exchange_topic() {
	// RabbitMQ 연결 URL, 익스체인지 이름 및 라우팅 키 설정 (실제 환경에 맞게 수정)
	rabbitMQURL := "amqp://guest:guest@localhost:5672/"
	exchangeName := "topic_logs_exchange"
	// 첫 번째 라우팅 키: 큐에 바인딩된 패턴 (예: "logs.info")
	routingKeyA := "logs.info"
	// 두 번째 라우팅 키: 큐 바인딩과 일치하지 않는 패턴 (예: "logs.debug")
	routingKeyB := "logs.debug"

	log.Println("RabbitMQ 토픽 익스체인지 예제 시작...")
	advancedRMQTopicExchangePublisher(rabbitMQURL, exchangeName, routingKeyA, routingKeyB)
	log.Println("RabbitMQ 토픽 익스체인지 예제 종료.")
}
