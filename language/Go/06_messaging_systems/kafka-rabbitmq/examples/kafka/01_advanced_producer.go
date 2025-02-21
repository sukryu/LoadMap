// 01_advanced_producer.go
//
// 이 파일은 Kafka 클러스터에 비동기 메시지를 전송하는 고급 예제입니다.
// Sarama 라이브러리를 사용하여 비동기 프로듀서를 생성하고,
// 커스텀 파티셔너(여기서는 기본 RandomPartitioner 사용) 및
// 성공/오류 채널을 통해 전송 결과를 모니터링하는 기능을 포함합니다.
//
// 사용 예:
//   go run 01_advanced_producer.go
//
// 주의: 모듈 경로 문제로 인해 최신 Sarama 라이브러리는 "github.com/IBM/sarama" 경로를 사용합니다.

package main

import (
	"fmt"
	"log"
	"time"

	"github.com/IBM/sarama"
)

// advancedProducerFunction은 Kafka 브로커에 비동기 메시지를 전송하는 함수입니다.
// brokerAddr: Kafka 브로커 주소 (예: "localhost:9092")
// topicIdentifier: 메시지를 전송할 Kafka 토픽 이름
func advancedProducerFunction(brokerAddr string, topicIdentifier string) {
	// Sarama 설정 생성: 기본 설정을 복사하여 사용하며, 비동기 프로듀서를 위한 옵션을 설정합니다.
	kafkaConfig := sarama.NewConfig()
	// 비동기 프로듀서의 성공 메시지와 오류 메시지를 리턴하도록 활성화합니다.
	kafkaConfig.Producer.Return.Successes = true
	kafkaConfig.Producer.Return.Errors = true

	// 파티셔너 설정: 여기서는 기본 제공 RandomPartitioner를 사용합니다.
	kafkaConfig.Producer.Partitioner = sarama.NewRandomPartitioner

	// Kafka 비동기 프로듀서 생성: 지정한 브로커 주소를 사용합니다.
	producerInstance, err := sarama.NewAsyncProducer([]string{brokerAddr}, kafkaConfig)
	if err != nil {
		log.Fatalf("Kafka 비동기 프로듀서 생성 실패: %v", err)
	}
	// 프로듀서를 종료할 때 안전하게 닫기 위한 지연 함수 등록
	defer func() {
		if closeErr := producerInstance.Close(); closeErr != nil {
			log.Printf("Kafka 프로듀서 종료 중 에러: %v", closeErr)
		}
	}()

	// 결과 모니터링을 위한 채널 종료용 채널 생성
	doneMonitoring := make(chan struct{})

	// 고루틴을 사용하여 성공 및 오류 채널을 모니터링합니다.
	go func() {
		for {
			select {
			case successMsg, ok := <-producerInstance.Successes():
				if ok {
					log.Printf("Kafka 메시지 전송 성공: 토픽=%s, 파티션=%d, 오프셋=%d",
						successMsg.Topic, successMsg.Partition, successMsg.Offset)
				}
			case errMsg, ok := <-producerInstance.Errors():
				if ok {
					log.Printf("Kafka 메시지 전송 오류: %v", errMsg.Err)
				}
			case <-doneMonitoring:
				// 모니터링 종료 신호 수신 시 고루틴 종료
				return
			}
		}
	}()

	// 여러 메시지를 순차적으로 전송합니다.
	for index := 0; index < 10; index++ {
		// 메시지 키와 값 생성: 고유한 값으로 생성
		customKey := fmt.Sprintf("custom-key-%d", index)
		customValue := fmt.Sprintf("Advanced Kafka message %d sent at %s", index, time.Now().Format(time.RFC3339))

		// Kafka 메시지 생성
		messageToSend := &sarama.ProducerMessage{
			Topic: topicIdentifier,
			Key:   sarama.StringEncoder(customKey),
			Value: sarama.StringEncoder(customValue),
		}

		// 생성된 메시지를 비동기 프로듀서의 입력 채널에 전송
		producerInstance.Input() <- messageToSend

		log.Printf("Kafka 메시지 전송 요청: 메시지 번호 %d", index)
		// 메시지 전송 간 간격을 둡니다.
		time.Sleep(500 * time.Millisecond)
	}

	// 모든 메시지가 전송될 시간을 확보하기 위해 잠시 대기합니다.
	time.Sleep(3 * time.Second)
	// 모니터링 고루틴 종료 신호 전송
	close(doneMonitoring)
}

func Start_kafka_producer() {
	// Kafka 브로커 주소와 토픽 이름 설정 (실제 환경에 맞게 수정)
	kafkaBroker := "localhost:9092"
	kafkaTopic := "advanced-example-topic"

	log.Println("Kafka 고급 프로듀서 예제 시작...")
	advancedProducerFunction(kafkaBroker, kafkaTopic)
	log.Println("Kafka 고급 프로듀서 예제 종료.")
}
