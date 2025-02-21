// 04_custom_partitioner.go
//
// 이 파일은 Kafka에서 사용자 정의 파티셔너(Custom Partitioner)를 구현한 예제입니다.
// 사용자가 정의한 파티셔너는 메시지의 키를 기반으로 파티션을 결정합니다.
// 예제에서는 메시지 키의 바이트 합계를 파티션 수로 나눈 나머지를 파티션 번호로 사용합니다.
// 사용 예:
//   go run 04_custom_partitioner.go
//
// 주의: 최신 Sarama 라이브러리는 "github.com/IBM/sarama" 경로를 사용합니다.

package main

import (
	"fmt"
	"log"

	"github.com/IBM/sarama"
)

// MyCustomPartitioner는 Sarama의 Partitioner 인터페이스를 구현하는 사용자 정의 파티셔너입니다.
type MyCustomPartitioner struct {
	// partitionCount는 토픽의 파티션 총 개수를 저장합니다.
	partitionCount int32
}

// Partition 메서드는 메시지의 키를 기반으로 파티션을 결정합니다.
// 만약 메시지 키가 없으면 기본적으로 0번 파티션을 반환합니다.
func (p *MyCustomPartitioner) Partition(message *sarama.ProducerMessage, numPartitions int32) (int32, error) {
	// 파티션 수는 메시지 발행 시 제공된 값(numPartitions)과 일치해야 합니다.
	p.partitionCount = numPartitions

	// 메시지 키가 존재하는 경우, 바이트 합계를 계산하여 파티션 번호 결정
	if message.Key != nil {
		keyBytes, err := message.Key.Encode()
		if err != nil {
			return 0, fmt.Errorf("메시지 키 인코딩 실패: %v", err)
		}

		var sum int32
		for _, b := range keyBytes {
			sum += int32(b)
		}
		// 바이트 합계를 파티션 수로 나눈 나머지를 반환
		partition := sum % p.partitionCount
		return partition, nil
	}

	// 메시지 키가 없으면 기본 파티션(0번)을 반환
	return 0, nil
}

// RequiresConsistency 메서드는 메시지의 파티션이 일관되게 결정되어야 함을 나타냅니다.
func (p *MyCustomPartitioner) RequiresConsistency() bool {
	return true
}

// myCustomPartitionerConstructor는 새로운 MyCustomPartitioner 인스턴스를 생성합니다.
func myCustomPartitionerConstructor(topic string) sarama.Partitioner {
	return &MyCustomPartitioner{}
}

// customPartitionerDemo는 사용자 정의 파티셔너를 사용하여 Kafka에 메시지를 전송하는 예제 함수입니다.
// brokerAddr: Kafka 브로커 주소 (예: "localhost:9092")
// topicName: 메시지를 전송할 Kafka 토픽 이름
func customPartitionerDemo(brokerAddr, topicName string) {
	// Sarama 설정 생성
	config := sarama.NewConfig()
	// 비동기 프로듀서가 아닌 동기 프로듀서를 사용 (전송 결과를 바로 받기 위함)
	config.Producer.Return.Successes = true
	// 사용자 정의 파티셔너를 사용하도록 Partitioner 설정 함수 지정
	config.Producer.Partitioner = myCustomPartitionerConstructor

	// 동기 프로듀서 생성
	producer, err := sarama.NewSyncProducer([]string{brokerAddr}, config)
	if err != nil {
		log.Fatalf("Kafka 동기 프로듀서 생성 실패: %v", err)
	}
	defer func() {
		if err := producer.Close(); err != nil {
			log.Printf("Kafka 프로듀서 종료 중 에러: %v", err)
		}
	}()

	// 여러 메시지를 전송하며 사용자 정의 파티셔너가 각 메시지의 키를 기반으로 파티션을 결정하는지 확인합니다.
	for i := 0; i < 5; i++ {
		// 메시지 키를 고유하게 생성 (예: "customKey_i")
		msgKey := fmt.Sprintf("customKey_%d", i)
		// 메시지 값: 단순 문자열 메시지
		msgValue := fmt.Sprintf("Custom partitioner message number %d", i)

		message := &sarama.ProducerMessage{
			Topic: topicName,
			Key:   sarama.StringEncoder(msgKey),
			Value: sarama.StringEncoder(msgValue),
		}

		// 메시지 전송 및 전송 결과(파티션, 오프셋) 받기
		partition, offset, err := producer.SendMessage(message)
		if err != nil {
			log.Printf("메시지 전송 실패: %v", err)
			continue
		}

		// 전송 결과 로그 출력
		log.Printf("메시지 전송 성공 - 키: %s, 파티션: %d, 오프셋: %d", msgKey, partition, offset)
	}
}

func Custom_partitioner() {
	// Kafka 브로커 주소 및 토픽 이름 설정 (실제 환경에 맞게 조정)
	kafkaBroker := "localhost:9092"
	kafkaTopic := "custom-partitioner-topic"

	log.Println("사용자 정의 파티셔너 예제 시작...")
	customPartitionerDemo(kafkaBroker, kafkaTopic)
	log.Println("사용자 정의 파티셔너 예제 종료.")
}
