// 03_streaming_processing.go
//
// 이 파일은 Kafka 스트리밍 처리 파이프라인 예제입니다.
// 이 예제에서는 지정된 입력 토픽(input-stream-topic)에서 메시지를 소비하고,
// 메시지 본문을 간단하게 변환(대문자 변환)한 후, 출력 토픽(output-stream-topic)으로 전송합니다.
// Kafka의 Sarama 라이브러리를 활용하여 비동기 프로듀서와 파티션 소비자를 사용합니다.
// 사용 예: go run 03_streaming_processing.go
//
// 주의: 최신 Sarama 라이브러리는 모듈 경로가 "github.com/IBM/sarama"로 선언되어 있으므로,
// 해당 경로를 사용해야 합니다.

package main

import (
	"context"
	"fmt"
	"log"
	"strings"
	"time"

	"github.com/IBM/sarama"
)

// streamProcessor는 입력 토픽에서 메시지를 읽어 처리한 후 출력 토픽으로 전송하는 함수입니다.
// brokerAddress: Kafka 브로커 주소 (예: "localhost:9092")
// inputTopicName: 메시지를 소비할 입력 토픽 이름
// outputTopicName: 처리된 메시지를 전송할 출력 토픽 이름
func streamProcessor(brokerAddress, inputTopicName, outputTopicName string) {
	// 1. Kafka Consumer 생성: 입력 토픽의 파티션 0에서 메시지를 소비합니다.
	consumerInstance, err := sarama.NewConsumer([]string{brokerAddress}, nil)
	if err != nil {
		log.Fatalf("Kafka Consumer 생성 실패: %v", err)
	}
	defer func() {
		if err := consumerInstance.Close(); err != nil {
			log.Printf("Consumer 종료 중 에러: %v", err)
		}
	}()

	// 파티션 소비자 생성: 최신 메시지부터 읽기 시작
	partitionConsumer, err := consumerInstance.ConsumePartition(inputTopicName, 0, sarama.OffsetNewest)
	if err != nil {
		log.Fatalf("파티션 Consumer 생성 실패: %v", err)
	}
	defer func() {
		if err := partitionConsumer.Close(); err != nil {
			log.Printf("Partition Consumer 종료 중 에러: %v", err)
		}
	}()

	// 2. Kafka 비동기 Producer 생성: 출력 토픽으로 메시지를 전송합니다.
	producerConfig := sarama.NewConfig()
	producerConfig.Producer.Return.Successes = true // 전송 성공 메시지 활성화
	producerConfig.Producer.Return.Errors = true    // 전송 오류 메시지 활성화
	producerConfig.Producer.Partitioner = sarama.NewRandomPartitioner

	producerInstance, err := sarama.NewAsyncProducer([]string{brokerAddress}, producerConfig)
	if err != nil {
		log.Fatalf("Kafka Producer 생성 실패: %v", err)
	}
	defer func() {
		if err := producerInstance.Close(); err != nil {
			log.Printf("Producer 종료 중 에러: %v", err)
		}
	}()

	// 3. 비동기 Producer 결과 모니터링: 성공 및 오류 메시지를 처리하는 고루틴 실행
	doneSignal := make(chan struct{})
	go func() {
		for {
			select {
			case successMsg, ok := <-producerInstance.Successes():
				if ok {
					log.Printf("메시지 전송 성공: 토픽=%s, 파티션=%d, 오프셋=%d",
						successMsg.Topic, successMsg.Partition, successMsg.Offset)
				}
			case errMsg, ok := <-producerInstance.Errors():
				if ok {
					log.Printf("메시지 전송 오류: %v", errMsg.Err)
				}
			case <-doneSignal:
				return
			}
		}
	}()

	// 4. 메시지 처리: 입력 토픽에서 메시지를 읽어 변환 후 출력 토픽으로 전송
	// 30초 동안 메시지를 처리하도록 설정 (실제 환경에서는 지속적으로 실행)
	timeoutCtx, cancel := context.WithTimeout(context.Background(), 30*time.Second)
	defer cancel()

	for {
		select {
		case msg := <-partitionConsumer.Messages():
			// 원본 메시지 추출 및 로그 기록
			originalText := string(msg.Value)
			log.Printf("입력 메시지 수신: %s", originalText)

			// 메시지 변환: 예를 들어, 메시지 본문을 대문자로 변환
			transformedText := strings.ToUpper(originalText)
			log.Printf("변환된 메시지: %s", transformedText)

			// 출력 토픽으로 전송할 메시지 생성 (키는 메시지 오프셋 사용)
			newProducerMsg := &sarama.ProducerMessage{
				Topic: outputTopicName,
				Key:   sarama.StringEncoder(fmt.Sprintf("key-%d", msg.Offset)),
				Value: sarama.StringEncoder(transformedText),
			}

			// 메시지 전송 요청: Producer의 입력 채널에 메시지 전송
			producerInstance.Input() <- newProducerMsg

		case <-timeoutCtx.Done():
			log.Println("메시지 스트리밍 처리 시간이 종료되었습니다.")
			close(doneSignal)
			return
		}
	}
}

func Streaming_processing() {
	// Kafka 브로커 주소와 입력/출력 토픽 이름 설정 (실제 환경에 맞게 조정)
	kafkaBrokerAddr := "localhost:9092"
	inputTopic := "stream-input-topic"
	outputTopic := "stream-output-topic"

	log.Println("Kafka 스트리밍 처리 예제 시작...")
	streamProcessor(kafkaBrokerAddr, inputTopic, outputTopic)
	log.Println("Kafka 스트리밍 처리 예제 종료.")
}
