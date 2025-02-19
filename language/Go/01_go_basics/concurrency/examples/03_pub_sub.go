/*
이 예제는 Go에서 발행-구독(pub/sub) 패턴을 구현한 포괄적인 예시를 제공합니다. 이 패턴은 메시지 기반의 비동기 통신을 구현할 때 특히 유용합니다. 주요 컴포넌트와 특징은 다음과 같습니다:

메시지 시스템: Message 구조체는 시스템에서 전달되는 메시지를 표현하며, 메시지 ID, 토픽, 내용, 타임스탬프, 메타데이터 등을 포함합니다.
구독자 관리: Subscriber 구조체는 개별 구독자의 상태와 설정을 관리하며, 메시지 수신 채널과 처리 통계를 포함합니다.
발행-구독 시스템: PubSub 구조체는 전체 시스템의 상태를 관리하며, 다음과 같은 주요 기능을 제공합니다:

구독자 등록 및 해지
메시지 발행
토픽 기반 메시지 라우팅
시스템 상태 모니터링


동시성 제어: 시스템은 다음과 같은 동시성 제어 메커니즘을 구현합니다:

뮤텍스를 통한 구독자 목록 보호
컨텍스트를 통한 정상 종료 지원
채널을 통한 비동기 메시지 전달


에러 처리: 시스템은 다양한 에러 상황을 처리합니다:

채널이 가득 찬 경우의 메시지 드롭
존재하지 않는 토픽에 대한 발행 시도
시스템 종료 중 발생하는 상황



이 패턴은 다음과 같은 상황에서 특히 유용합니다:

이벤트 기반 아키텍처
마이크로서비스 간 통신
실시간 알림 시스템
로그 및 모니터링 시스템

발행-구독 패턴의 주요 장점은 다음과 같습니다:

발행자와 구독자 간의 느슨한 결합
확장성 있는 메시지 전달
유연한 토픽 기반 라우팅
비동기 통신 지원

이 구현은 실제 프로덕션 환경에서 사용할 수 있는 기본적인 기능을 모두 갖추고 있으며, 필요에 따라 추가 기능(예: 메시지 지속성, QoS 레벨, 메시지 필터링 등)을 확장할 수 있습니다.
*/

package examples

import (
	"context"
	"fmt"
	"log"
	"sync"
	"time"
)

// Message represents a message in the pub/sub system
// 시스템에서 전달되는 메시지의 구조를 정의합니다.
type Message struct {
	ID        string
	Topic     string
	Content   interface{}
	Timestamp time.Time
	// 메시지 추적을 위한 메타데이터
	Metadata map[string]string
}

// Subscriber represents a message subscriber
// 메시지 구독자의 정보와 상태를 관리합니다.
type Subscriber struct {
	ID       string
	Topics   []string
	Messages chan Message
	// 구독자의 메시지 처리 상태를 추적합니다.
	Stats struct {
		ReceivedCount int
		ErrorCount    int
	}
}

// PubSub implements the publish-subscribe messaging pattern
// 전체 발행-구독 시스템의 상태와 동작을 관리합니다.
type PubSub struct {
	mu          sync.RWMutex
	subscribers map[string][]*Subscriber
	// 시스템 전체의 메시지 처리 통계를 관리합니다.
	stats struct {
		PublishedCount  int
		SubscriberCount int
	}
	ctx    context.Context
	cancel context.CancelFunc
}

// NewPubSub creates a new publish-subscribe message broker
// 새로운 발행-구독 시스템을 생성하고 초기화합니다.
func NewPubSub() *PubSub {
	ctx, cancel := context.WithCancel(context.Background())
	return &PubSub{
		subscribers: make(map[string][]*Subscriber),
		ctx:         ctx,
		cancel:      cancel,
	}
}

// Subscribe adds a new subscriber for the specified topics
// 새로운 구독자를 등록하고 구독 채널을 생성합니다.
func (ps *PubSub) Subscribe(id string, topics []string, bufferSize int) *Subscriber {
	ps.mu.Lock()
	defer ps.mu.Unlock()

	// 새 구독자 생성
	subscriber := &Subscriber{
		ID:       id,
		Topics:   topics,
		Messages: make(chan Message, bufferSize),
	}

	// 각 토픽에 구독자 등록
	for _, topic := range topics {
		ps.subscribers[topic] = append(ps.subscribers[topic], subscriber)
	}

	ps.stats.SubscriberCount++
	log.Printf("New subscriber '%s' registered for topics: %v", id, topics)

	return subscriber
}

// Unsubscribe removes a subscriber from all its topics
// 구독자를 시스템에서 제거하고 관련 리소스를 정리합니다.
func (ps *PubSub) Unsubscribe(subscriber *Subscriber) {
	ps.mu.Lock()
	defer ps.mu.Unlock()

	// 각 토픽에서 구독자 제거
	for _, topic := range subscriber.Topics {
		subscribers := ps.subscribers[topic]
		for i, sub := range subscribers {
			if sub.ID == subscriber.ID {
				// 슬라이스에서 구독자 제거
				ps.subscribers[topic] = append(subscribers[:i], subscribers[i+1:]...)
				break
			}
		}
	}

	// 구독자의 메시지 채널 닫기
	close(subscriber.Messages)
	ps.stats.SubscriberCount--
	log.Printf("Subscriber '%s' unsubscribed", subscriber.ID)
}

// Publish sends a message to all subscribers of the specified topic
// 메시지를 특정 토픽의 모든 구독자에게 전달합니다.
func (ps *PubSub) Publish(topic string, content interface{}) error {
	ps.mu.RLock()
	subscribers, exists := ps.subscribers[topic]
	ps.mu.RUnlock()

	if !exists {
		return fmt.Errorf("no subscribers for topic: %s", topic)
	}

	// 메시지 생성
	msg := Message{
		ID:        fmt.Sprintf("msg-%d", time.Now().UnixNano()),
		Topic:     topic,
		Content:   content,
		Timestamp: time.Now(),
		Metadata:  make(map[string]string),
	}

	// 모든 구독자에게 메시지 전송
	for _, subscriber := range subscribers {
		select {
		case <-ps.ctx.Done():
			return fmt.Errorf("pubsub system is shutting down")
		case subscriber.Messages <- msg:
			subscriber.Stats.ReceivedCount++
		default:
			// 채널이 가득 찬 경우 처리
			subscriber.Stats.ErrorCount++
			log.Printf("Warning: Drop message for subscriber '%s' - channel full", subscriber.ID)
		}
	}

	ps.stats.PublishedCount++
	log.Printf("Message published to topic '%s': %v", topic, content)
	return nil
}

// ProcessMessages handles message processing for a subscriber
// 구독자의 메시지 처리 로직을 구현합니다.
func (s *Subscriber) ProcessMessages(ctx context.Context) {
	for {
		select {
		case <-ctx.Done():
			log.Printf("Subscriber '%s' shutting down", s.ID)
			return
		case msg, ok := <-s.Messages:
			if !ok {
				log.Printf("Subscriber '%s' message channel closed", s.ID)
				return
			}
			// 메시지 처리 로직
			log.Printf("Subscriber '%s' received message: %v (Topic: %s)",
				s.ID, msg.Content, msg.Topic)
		}
	}
}

// Stop gracefully shuts down the pub/sub system
// 시스템을 정상적으로 종료하고 리소스를 정리합니다.
func (ps *PubSub) Stop() {
	ps.cancel()
	ps.mu.Lock()
	defer ps.mu.Unlock()

	// 모든 구독자의 채널 닫기
	for _, subscribers := range ps.subscribers {
		for _, subscriber := range subscribers {
			close(subscriber.Messages)
		}
	}

	// 구독자 맵 초기화
	ps.subscribers = make(map[string][]*Subscriber)
	log.Println("PubSub system stopped")
}

// PubSubExample demonstrates the usage of the publish-subscribe pattern
func PubSubExample() {
	// 시스템 생성
	pubsub := NewPubSub()
	defer pubsub.Stop()

	// 컨텍스트 생성
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	// 구독자 등록
	subscriber1 := pubsub.Subscribe("sub1", []string{"news", "updates"}, 10)
	subscriber2 := pubsub.Subscribe("sub2", []string{"news"}, 10)

	// 메시지 처리 고루틴 시작
	go subscriber1.ProcessMessages(ctx)
	go subscriber2.ProcessMessages(ctx)

	// 메시지 발행
	pubsub.Publish("news", "Breaking news: Go 2.0 announced!")
	pubsub.Publish("updates", "System update scheduled")
	pubsub.Publish("news", "Tech conference next week")

	// 처리 시간 대기
	time.Sleep(2 * time.Second)

	// 구독 해지
	pubsub.Unsubscribe(subscriber1)
	pubsub.Unsubscribe(subscriber2)

	// 시스템 상태 출력
	log.Printf("Total messages published: %d", pubsub.stats.PublishedCount)
	log.Printf("Final subscriber count: %d", pubsub.stats.SubscriberCount)
}
