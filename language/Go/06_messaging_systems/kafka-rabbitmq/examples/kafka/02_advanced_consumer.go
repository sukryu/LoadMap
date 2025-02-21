// 02_advanced_consumer.go
//
// 이 파일은 Kafka 클러스터로부터 메시지를 소비하는 고급 예제입니다.
// Sarama 라이브러리의 컨슈머 그룹 기능을 사용하여, 지정된 토픽에서 메시지를 수신하고 처리합니다.
// 이 예제는 컨슈머 그룹 핸들러를 통해 메시지 소비 로직을 정의하며,
// 일정 시간 동안 메시지를 소비한 후 종료합니다.
//
// 사용 예:
//   go run 02_advanced_consumer.go
//
// 주의: 모듈 경로 문제로 인해 최신 Sarama 라이브러리는 "github.com/IBM/sarama" 경로를 사용합니다.

package main

import (
	"context"
	"fmt"
	"log"
	"time"

	"github.com/IBM/sarama"
)

// AdvancedConsumerHandler는 Sarama의 ConsumerGroupHandler 인터페이스를 구현하여,
// Kafka 토픽에서 메시지를 소비하는 로직을 정의합니다.
type AdvancedConsumerHandler struct{}

// Setup은 컨슈머 그룹이 시작될 때 호출되며, 초기화 작업을 수행합니다.
func (h *AdvancedConsumerHandler) Setup(session sarama.ConsumerGroupSession) error {
	// 초기화 작업 (필요한 경우)
	log.Println("AdvancedConsumerHandler: Setup - 컨슈머 그룹 초기화 완료")
	return nil
}

// Cleanup은 컨슈머 그룹이 종료될 때 호출되며, 정리 작업을 수행합니다.
func (h *AdvancedConsumerHandler) Cleanup(session sarama.ConsumerGroupSession) error {
	log.Println("AdvancedConsumerHandler: Cleanup - 컨슈머 그룹 정리 완료")
	return nil
}

// ConsumeClaim은 컨슈머 그룹에서 각 파티션의 메시지를 실제로 소비하는 함수입니다.
func (h *AdvancedConsumerHandler) ConsumeClaim(session sarama.ConsumerGroupSession, claim sarama.ConsumerGroupClaim) error {
	// claim.Messages() 채널을 통해 지속적으로 메시지를 수신합니다.
	for msg := range claim.Messages() {
		// 수신한 메시지 로그 출력 및 처리
		fmt.Printf("AdvancedConsumerHandler: 메시지 수신 - 파티션: %d, 오프셋: %d, 메시지: %s\n",
			msg.Partition, msg.Offset, string(msg.Value))
		// 메시지 처리가 완료되었음을 표시하여, 중복 소비를 방지합니다.
		session.MarkMessage(msg, "")
	}
	return nil
}

// advancedKafkaConsumerFunction은 Kafka 컨슈머 그룹을 생성하여 메시지를 소비하는 함수입니다.
// brokerAddr: Kafka 브로커 주소 (예: "localhost:9092")
// topicName: 메시지를 소비할 토픽 이름
// consumerGroupID: 컨슈머 그룹 ID (여러 인스턴스가 동일한 그룹으로 메시지를 분담하여 소비)
func advancedKafkaConsumerFunction(brokerAddr, topicName, consumerGroupID string) {
	// Sarama 설정 생성 및 초기화
	consumerConfig := sarama.NewConfig()
	// Kafka 버전 설정 (필요에 따라 조정)
	consumerConfig.Version = sarama.V2_1_0_0
	// 컨슈머 그룹 재분배 전략 설정: Range 전략 사용
	consumerConfig.Consumer.Group.Rebalance.Strategy = sarama.BalanceStrategyRange
	// 초기 오프셋은 가장 오래된 메시지부터 소비
	consumerConfig.Consumer.Offsets.Initial = sarama.OffsetOldest

	// Kafka 컨슈머 그룹 생성
	consumerGroup, err := sarama.NewConsumerGroup([]string{brokerAddr}, consumerGroupID, consumerConfig)
	if err != nil {
		log.Fatalf("Kafka 컨슈머 그룹 생성 실패: %v", err)
	}
	defer func() {
		if err := consumerGroup.Close(); err != nil {
			log.Printf("Kafka 컨슈머 그룹 종료 중 에러: %v", err)
		}
	}()

	// AdvancedConsumerHandler 인스턴스 생성
	consumerHandler := &AdvancedConsumerHandler{}

	// 컨슈머 그룹을 관리하기 위한 컨텍스트 생성 (취소 가능한 컨텍스트)
	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()

	// 고루틴을 사용하여 컨슈머 그룹에서 메시지 소비를 시작합니다.
	go func() {
		for {
			// 지정한 토픽의 메시지를 소비합니다.
			err := consumerGroup.Consume(ctx, []string{topicName}, consumerHandler)
			if err != nil {
				log.Fatalf("Kafka 메시지 소비 중 에러: %v", err)
			}
			// 컨텍스트가 취소되면 종료합니다.
			if ctx.Err() != nil {
				return
			}
		}
	}()

	// 일정 시간(예: 15초) 동안 메시지 소비 후 컨슈머 종료
	time.Sleep(15 * time.Second)
	cancel() // 컨텍스트 취소를 통해 소비 종료

	// 소비 종료 후 잠시 대기하여 모든 처리가 완료되도록 함
	time.Sleep(2 * time.Second)
	fmt.Println("Advanced Kafka Consumer 예제 종료")
}

func Start_kafka_consumer() {
	// Kafka 브로커, 토픽, 컨슈머 그룹 ID 설정 (실제 환경에 맞게 수정)
	kafkaBroker := "localhost:9092"
	consumerTopic := "advanced-example-topic"
	consumerGroupID := "advanced-consumer-group"

	log.Println("Advanced Kafka Consumer 예제 시작...")
	advancedKafkaConsumerFunction(kafkaBroker, consumerTopic, consumerGroupID)
	log.Println("Advanced Kafka Consumer 예제 메인 종료.")
}
