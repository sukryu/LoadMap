// 04_rabbitmq_rpc_example.go
//
// 이 파일은 RabbitMQ를 이용한 RPC 패턴 예제입니다.
// - RPC 서버: 지정된 RPC 큐에서 메시지를 수신하고, 요청을 처리한 후 응답 메시지를 전송합니다.
// - RPC 클라이언트: RPC 서버로 요청 메시지를 보내고, 응답 큐에서 해당 응답을 기다립니다.
//
// 사용 예:
//   go run 04_rabbitmq_rpc_example.go server
//   go run 04_rabbitmq_rpc_example.go client
//
// 주의: 실제 환경에서는 연결 URL, 큐 이름, 그리고 RPC 처리 로직을 상황에 맞게 수정하여 사용하세요.

package main

import (
	"context"
	"fmt"
	"log"
	"math/rand"
	"os"
	"strconv"
	"time"

	"github.com/streadway/amqp"
)

// advancedRMQRPCServer는 RabbitMQ를 이용한 RPC 서버를 구현합니다.
// 서버는 "rpc_queue_custom" 큐에서 RPC 요청을 수신하고, 요청 본문을 처리한 후,
// 응답을 요청 메시지의 reply-to 큐로 전송합니다.
func advancedRMQRPCServer(amqpURL string) {
	// RabbitMQ 서버에 연결
	conn, err := amqp.Dial(amqpURL)
	if err != nil {
		log.Fatalf("RPC 서버: RabbitMQ 연결 실패: %v", err)
	}
	defer conn.Close()

	// 채널 생성
	ch, err := conn.Channel()
	if err != nil {
		log.Fatalf("RPC 서버: 채널 생성 실패: %v", err)
	}
	defer ch.Close()

	// RPC 큐 선언 (내구성 큐)
	queue, err := ch.QueueDeclare(
		"rpc_queue_custom", // 큐 이름
		true,               // 내구성 활성화
		false,              // 자동 삭제 비활성화
		false,              // 독점 사용 비활성화
		false,              // no-wait 비활성화
		nil,                // 추가 인자 없음
	)
	if err != nil {
		log.Fatalf("RPC 서버: 큐 선언 실패: %v", err)
	}

	// 큐에서 메시지 소비 시작 (autoAck false: 수동 ACK 사용)
	msgs, err := ch.Consume(
		queue.Name,            // 큐 이름
		"rpc_server_consumer", // 소비자 태그
		false,                 // autoAck 비활성화
		false,                 // 독점 사용 비활성화
		false,                 // no-local
		false,                 // no-wait
		nil,                   // 추가 인자 없음
	)
	if err != nil {
		log.Fatalf("RPC 서버: 소비자 등록 실패: %v", err)
	}

	log.Println("RPC 서버: 요청 대기 중...")

	// 메시지 처리 루프
	for msg := range msgs {
		// 요청 메시지의 본문을 정수로 파싱 (예: 두 수의 합을 계산하는 경우)
		requestStr := string(msg.Body)
		log.Printf("RPC 서버: 요청 수신: %s", requestStr)

		// 간단한 RPC 로직: 요청 메시지가 "a,b" 형태라면, 두 수의 합을 계산하여 반환
		var result int
		parts := splitAndTrim(requestStr, ",")
		if len(parts) == 2 {
			a, errA := strconv.Atoi(parts[0])
			b, errB := strconv.Atoi(parts[1])
			if errA == nil && errB == nil {
				result = a + b
			} else {
				log.Printf("RPC 서버: 숫자 변환 오류: %v, %v", errA, errB)
				result = 0
			}
		} else {
			// 잘못된 요청 형식인 경우, 기본값 0 반환
			result = 0
		}

		// 응답 메시지 생성: 결과 값을 문자열로 변환
		response := fmt.Sprintf("%d", result)

		// 응답 메시지를 요청 메시지의 ReplyTo 큐로 전송
		err = ch.Publish(
			"",          // 기본 익스체인지 사용
			msg.ReplyTo, // 요청 메시지의 ReplyTo 필드 사용
			false,       // mandatory
			false,       // immediate
			amqp.Publishing{
				ContentType:   "text/plain",
				CorrelationId: msg.CorrelationId, // 요청과 동일한 CorrelationId 사용
				Body:          []byte(response),
			},
		)
		if err != nil {
			log.Printf("RPC 서버: 응답 메시지 전송 실패: %v", err)
		} else {
			log.Printf("RPC 서버: 응답 전송 성공: %s", response)
		}

		// 메시지 처리 완료 후 수동 ACK 전송
		msg.Ack(false)
	}
}

// advancedRMQRPCClient는 RabbitMQ를 이용한 RPC 클라이언트를 구현합니다.
// 클라이언트는 "rpc_queue_custom" 큐로 요청 메시지를 전송하고, 임시 Reply 큐에서 응답을 기다립니다.
func advancedRMQRPCClient(amqpURL string, request string) {
	// RabbitMQ 서버에 연결
	conn, err := amqp.Dial(amqpURL)
	if err != nil {
		log.Fatalf("RPC 클라이언트: RabbitMQ 연결 실패: %v", err)
	}
	defer conn.Close()

	// 채널 생성
	ch, err := conn.Channel()
	if err != nil {
		log.Fatalf("RPC 클라이언트: 채널 생성 실패: %v", err)
	}
	defer ch.Close()

	// 임시로 사용할 독점 Reply 큐 선언 (자동 삭제)
	replyQueue, err := ch.QueueDeclare(
		"",    // 빈 문자열을 사용하면 임시 큐 생성
		false, // 내구성 비활성화
		true,  // 자동 삭제 활성화
		true,  // 독점 큐 활성화
		false, // no-wait 비활성화
		nil,   // 추가 인자 없음
	)
	if err != nil {
		log.Fatalf("RPC 클라이언트: 임시 Reply 큐 선언 실패: %v", err)
	}

	// 소비자 등록: Reply 큐에서 응답 메시지를 소비 (autoAck 활성화)
	msgs, err := ch.Consume(
		replyQueue.Name,       // 임시 큐 이름
		"rpc_client_consumer", // 소비자 태그
		true,                  // autoAck 활성화: 응답을 수신하면 자동 ACK
		false,                 // 독점 사용 비활성화
		false,                 // no-local
		false,                 // no-wait
		nil,                   // 추가 인자 없음
	)
	if err != nil {
		log.Fatalf("RPC 클라이언트: Reply 큐 소비자 등록 실패: %v", err)
	}

	// 고유한 CorrelationId 생성
	corrID := randomString(32)

	// 요청 메시지 게시: RPC 요청 큐("rpc_queue_custom")에 메시지 전송
	err = ch.Publish(
		"",                 // 기본 익스체인지 사용
		"rpc_queue_custom", // RPC 요청 큐 이름
		false,              // mandatory
		false,              // immediate
		amqp.Publishing{
			ContentType:   "text/plain",
			CorrelationId: corrID,          // 고유 CorrelationId 설정
			ReplyTo:       replyQueue.Name, // 응답을 받을 큐 지정
			Body:          []byte(request),
		},
	)
	if err != nil {
		log.Fatalf("RPC 클라이언트: 요청 메시지 전송 실패: %v", err)
	}

	// 응답 대기: 일정 시간 동안 응답 메시지 수신
	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	// 응답 처리 루프: CorrelationId가 일치하는 메시지를 찾습니다.
	for {
		select {
		case d := <-msgs:
			if d.CorrelationId == corrID {
				log.Printf("RPC 클라이언트: 응답 수신: %s", d.Body)
				return
			}
		case <-ctx.Done():
			log.Fatalf("RPC 클라이언트: 응답 대기 시간 초과")
		}
	}
}

// randomString은 지정한 길이의 무작위 문자열을 생성합니다.
func randomString(length int) string {
	const charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
	result := make([]byte, length)
	seededRand := rand.New(rand.NewSource(time.Now().UnixNano()))
	for i := range result {
		result[i] = charset[seededRand.Intn(len(charset))]
	}
	return string(result)
}

// splitAndTrim은 주어진 문자열을 구분자(delim)로 분리한 후, 각 요소의 앞뒤 공백을 제거하여 반환합니다.
func splitAndTrim(input, delim string) []string {
	rawParts := []string{}
	for _, part := range split(input, delim) {
		rawParts = append(rawParts, trim(part))
	}
	return rawParts
}

// split 함수는 기본 문자열 분할 기능을 제공합니다.
func split(s, delim string) []string {
	return []string{} // 실제 구현 시 strings.Split(s, delim) 사용
}

// trim 함수는 문자열 앞뒤 공백을 제거합니다.
func trim(s string) string {
	return s // 실제 구현 시 strings.TrimSpace(s) 사용
}

func Rpc_example() {
	// 커맨드라인 인수를 통해 모드를 결정합니다.
	// 사용 예:
	//   go run 04_rabbitmq_rpc_example.go server
	//   go run 04_rabbitmq_rpc_example.go client "12,30"
	if len(os.Args) < 2 {
		fmt.Println("Usage: go run 04_rabbitmq_rpc_example.go [server|client] [request]")
		os.Exit(1)
	}

	mode := os.Args[1]
	amqpURL := "amqp://guest:guest@localhost:5672/"

	switch mode {
	case "server":
		log.Println("RPC 서버 모드 시작...")
		advancedRMQRPCServer(amqpURL)
	case "client":
		if len(os.Args) < 3 {
			log.Fatalf("RPC 클라이언트 모드 실행 시 요청 메시지를 제공해야 합니다. 예: \"12,30\"")
		}
		requestMessage := os.Args[2]
		log.Println("RPC 클라이언트 모드 시작...")
		advancedRMQRPCClient(amqpURL, requestMessage)
	default:
		fmt.Printf("알 수 없는 모드: %s\n", mode)
		os.Exit(1)
	}
}
