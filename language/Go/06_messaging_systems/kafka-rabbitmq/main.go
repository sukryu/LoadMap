// main.go
//
// 이 파일은 Kafka와 RabbitMQ를 활용한 메시징 예제입니다.
// 프로그램 실행 시 커맨드라인 인수에 따라 "kafka" 또는 "rabbitmq" 모드를 선택하여,
// 해당 메시징 시스템의 프로듀서와 컨슈머 기능을 시연합니다.
//
// 사용 예:
//   go run main.go kafka
//   go run main.go rabbitmq

package main

import (
	"context"
	"fmt"
	"log"
	"os"
	"time"

	// Kafka 클라이언트 라이브러리: IBM의 Sarama 사용
	"github.com/IBM/sarama"

	// RabbitMQ 클라이언트 라이브러리: streadway/amqp 사용
	"github.com/streadway/amqp"
)

// --------------------------------------------------------------------
// Kafka 관련 함수들
// --------------------------------------------------------------------

// kafkaProducerExample는 주어진 브로커와 토픽으로 Kafka 메시지를 동기적으로 전송합니다.
func kafkaProducerExample(broker string, topic string) {
	// Sarama 설정 생성: 기본 설정 사용 및 성공 리턴 활성화
	config := sarama.NewConfig()
	config.Producer.Return.Successes = true

	// Kafka Sync Producer 생성: 지정된 브로커 목록을 사용
	producer, err := sarama.NewSyncProducer([]string{broker}, config)
	if err != nil {
		log.Fatalf("Kafka 프로듀서 생성 실패: %v", err)
	}
	defer func() {
		if err := producer.Close(); err != nil {
			log.Printf("Kafka 프로듀서 종료 중 에러: %v", err)
		}
	}()

	// 메시지 생성: 토픽에 전송할 간단한 문자열 메시지
	msg := &sarama.ProducerMessage{
		Topic: topic,
		Value: sarama.StringEncoder("Hello from Kafka via Go!"),
	}

	// 메시지 전송 및 결과 수신: 파티션 번호와 오프셋을 반환
	partition, offset, err := producer.SendMessage(msg)
	if err != nil {
		log.Fatalf("Kafka 메시지 전송 실패: %v", err)
	}
	fmt.Printf("Kafka 메시지 전송 성공 - 파티션: %d, 오프셋: %d\n", partition, offset)
}

// ConsumerGroupHandler는 Sarama의 ConsumerGroupHandler 인터페이스를 구현하여,
// Kafka 메시지를 소비하는 로직을 정의합니다.
type ConsumerGroupHandler struct{}

// Setup은 컨슈머 그룹 초기화 시 호출됩니다.
func (ConsumerGroupHandler) Setup(session sarama.ConsumerGroupSession) error {
	return nil
}

// Cleanup은 컨슈머 그룹 종료 시 호출됩니다.
func (ConsumerGroupHandler) Cleanup(session sarama.ConsumerGroupSession) error {
	return nil
}

// ConsumeClaim은 실제 메시지 소비를 수행하는 함수입니다.
func (h ConsumerGroupHandler) ConsumeClaim(session sarama.ConsumerGroupSession, claim sarama.ConsumerGroupClaim) error {
	for message := range claim.Messages() {
		fmt.Printf("Kafka 메시지 수신 - 파티션: %d, 오프셋: %d, 메시지: %s\n",
			message.Partition, message.Offset, string(message.Value))
		// 메시지 처리 후 컨슈머 그룹에 ACK 표시
		session.MarkMessage(message, "")
	}
	return nil
}

// kafkaConsumerExample는 Kafka 컨슈머 그룹을 생성하여 주어진 토픽의 메시지를 소비합니다.
func kafkaConsumerExample(broker string, topic string, groupID string) {
	// Sarama 설정 생성: Kafka 클러스터 버전 및 컨슈머 그룹 옵션 설정
	config := sarama.NewConfig()
	// 사용 가능한 최신 Kafka 버전을 사용하도록 설정 (필요에 따라 조정)
	config.Version = sarama.V2_1_0_0
	// 컨슈머 그룹 재분배 전략 설정 (여기서는 Range 전략 사용)
	config.Consumer.Group.Rebalance.Strategy = sarama.BalanceStrategyRange
	// 초기 오프셋을 가장 오래된 메시지부터 읽도록 설정
	config.Consumer.Offsets.Initial = sarama.OffsetOldest

	// Kafka 컨슈머 그룹 생성
	consumerGroup, err := sarama.NewConsumerGroup([]string{broker}, groupID, config)
	if err != nil {
		log.Fatalf("Kafka 컨슈머 그룹 생성 실패: %v", err)
	}
	defer func() {
		if err := consumerGroup.Close(); err != nil {
			log.Printf("Kafka 컨슈머 그룹 종료 중 에러: %v", err)
		}
	}()

	consumer := ConsumerGroupHandler{}
	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()

	// 컨슈머 그룹을 고루틴에서 실행하여 메시지 소비 시작
	go func() {
		for {
			err := consumerGroup.Consume(ctx, []string{topic}, &consumer)
			if err != nil {
				log.Fatalf("Kafka 메시지 소비 중 에러: %v", err)
			}
			// 컨텍스트 취소가 발생하면 종료
			if ctx.Err() != nil {
				return
			}
		}
	}()

	// 일정 시간 동안 메시지 소비 후 종료 (예: 10초 후 종료)
	time.Sleep(10 * time.Second)
	fmt.Println("Kafka 소비 예제 종료")
}

// --------------------------------------------------------------------
// RabbitMQ 관련 함수들
// --------------------------------------------------------------------

// rabbitmqPublisherExample는 RabbitMQ에 메시지를 게시(publish)합니다.
func rabbitmqPublisherExample(amqpURL string, queueName string) {
	// RabbitMQ 서버에 연결
	conn, err := amqp.Dial(amqpURL)
	if err != nil {
		log.Fatalf("RabbitMQ 연결 실패: %v", err)
	}
	defer conn.Close()

	// 채널 생성: 메시지 전송을 위한 채널 열기
	ch, err := conn.Channel()
	if err != nil {
		log.Fatalf("RabbitMQ 채널 생성 실패: %v", err)
	}
	defer ch.Close()

	// 큐 선언: 지정된 큐 이름으로 내구성이 있는 큐 생성
	q, err := ch.QueueDeclare(
		queueName, // 큐 이름
		true,      // 내구성
		false,     // 자동 삭제 비활성화
		false,     // 독점 사용 비활성화
		false,     // no-wait 비활성화
		nil,       // 추가 설정 없음
	)
	if err != nil {
		log.Fatalf("RabbitMQ 큐 선언 실패: %v", err)
	}

	// 게시할 메시지 본문 생성
	body := "Hello from RabbitMQ via Go!"
	// 메시지 게시: 기본 익스체인지("")를 사용하여 큐에 메시지 전송
	err = ch.Publish(
		"",     // 익스체인지 (기본 익스체인지 사용)
		q.Name, // 라우팅 키 (큐 이름)
		false,  // mandatory
		false,  // immediate
		amqp.Publishing{
			ContentType: "text/plain",
			Body:        []byte(body),
		},
	)
	if err != nil {
		log.Fatalf("RabbitMQ 메시지 게시 실패: %v", err)
	}
	fmt.Println("RabbitMQ 메시지 게시 성공!")
}

// rabbitmqConsumerExample는 RabbitMQ 큐에서 메시지를 소비(consume)합니다.
func rabbitmqConsumerExample(amqpURL string, queueName string) {
	// RabbitMQ 서버에 연결
	conn, err := amqp.Dial(amqpURL)
	if err != nil {
		log.Fatalf("RabbitMQ 연결 실패: %v", err)
	}
	defer conn.Close()

	// 채널 생성
	ch, err := conn.Channel()
	if err != nil {
		log.Fatalf("RabbitMQ 채널 생성 실패: %v", err)
	}
	defer ch.Close()

	// 큐 선언: 소비할 큐를 선언합니다.
	q, err := ch.QueueDeclare(
		queueName, // 큐 이름
		true,      // 내구성
		false,     // 자동 삭제 비활성화
		false,     // 독점 사용 비활성화
		false,     // no-wait 비활성화
		nil,       // 추가 설정 없음
	)
	if err != nil {
		log.Fatalf("RabbitMQ 큐 선언 실패: %v", err)
	}

	// 큐로부터 메시지 수신 시작 (autoAck를 false로 설정하여 수동 ACK 사용)
	msgs, err := ch.Consume(
		q.Name, // 큐 이름
		"",     // 소비자 태그 (빈 문자열은 자동 생성)
		false,  // autoAck 비활성화
		false,  // 독점 사용 비활성화
		false,  // no-local (RabbitMQ 전용, 사용 안함)
		false,  // no-wait 비활성화
		nil,    // 추가 설정 없음
	)
	if err != nil {
		log.Fatalf("RabbitMQ 소비자 등록 실패: %v", err)
	}

	// 메시지 수신 및 처리: 첫 번째 메시지를 소비한 후 종료
	for msg := range msgs {
		fmt.Printf("RabbitMQ 메시지 수신: %s\n", string(msg.Body))
		// 메시지 확인(ack): 성공적으로 처리했음을 RabbitMQ에 알림
		if err := msg.Ack(false); err != nil {
			log.Printf("메시지 ACK 실패: %v", err)
		}
		// 한 건 처리 후 루프 종료 (실제 사용 시 계속해서 처리하도록 구성)
		break
	}

	fmt.Println("RabbitMQ 소비 예제 종료")
}

// --------------------------------------------------------------------
// main 함수: 실행 모드에 따라 Kafka 또는 RabbitMQ 예제를 실행합니다.
// --------------------------------------------------------------------
func main() {
	// 커맨드라인 인수로 모드를 결정합니다.
	// 사용 예: go run main.go kafka 또는 go run main.go rabbitmq
	if len(os.Args) < 2 {
		fmt.Println("Usage: go run main.go [kafka|rabbitmq]")
		os.Exit(1)
	}

	mode := os.Args[1]

	switch mode {
	case "kafka":
		// Kafka 관련 예제 실행
		broker := "localhost:9092"
		topic := "example-topic"
		groupID := "example-group"
		fmt.Println("Kafka 예제 실행 시작...")
		kafkaProducerExample(broker, topic)
		kafkaConsumerExample(broker, topic, groupID)
	case "rabbitmq":
		// RabbitMQ 관련 예제 실행
		amqpURL := "amqp://guest:guest@localhost:5672/"
		queueName := "example-queue"
		fmt.Println("RabbitMQ 예제 실행 시작...")
		rabbitmqPublisherExample(amqpURL, queueName)
		rabbitmqConsumerExample(amqpURL, queueName)
	default:
		fmt.Printf("알 수 없는 모드: %s\n", mode)
		os.Exit(1)
	}
}
