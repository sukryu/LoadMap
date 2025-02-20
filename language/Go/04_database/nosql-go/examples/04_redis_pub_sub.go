package examples

import (
	"context"
	"encoding/json"
	"fmt"
	"log"
	"sync"
	"time"

	"github.com/go-redis/redis/v8"
)

// NotificationMessage represents a notification payload
type NotificationMessage struct {
	ID        string                 `json:"id"`
	Type      string                 `json:"type"`
	Channel   string                 `json:"channel"`
	Content   string                 `json:"content"`
	Metadata  map[string]interface{} `json:"metadata,omitempty"`
	CreatedAt time.Time              `json:"created_at"`
}

// NotificationSystem handles real-time notifications using Redis Pub/Sub
type NotificationSystem struct {
	redisClient   *redis.Client
	subscribers   map[string][]NotificationHandler
	subscribersMu sync.RWMutex
	done          chan struct{}
	wg            sync.WaitGroup
}

// NotificationHandler is a callback function type for handling notifications
type NotificationHandler func(msg *NotificationMessage) error

// NewNotificationSystem creates a new notification system instance
func NewNotificationSystem(ctx context.Context) (*NotificationSystem, error) {
	// Redis 클라이언트 초기화
	redisClient := redis.NewClient(&redis.Options{
		Addr:         "localhost:6379",
		Password:     "",
		DB:           0,
		DialTimeout:  5 * time.Second,
		ReadTimeout:  3 * time.Second,
		WriteTimeout: 3 * time.Second,
	})

	// Redis 연결 확인
	if err := redisClient.Ping(ctx).Err(); err != nil {
		return nil, fmt.Errorf("Redis 연결 실패: %v", err)
	}

	system := &NotificationSystem{
		redisClient: redisClient,
		subscribers: make(map[string][]NotificationHandler),
		done:        make(chan struct{}),
	}

	return system, nil
}

// Subscribe adds a new handler for a specific notification channel
func (ns *NotificationSystem) Subscribe(channel string, handler NotificationHandler) error {
	ns.subscribersMu.Lock()
	defer ns.subscribersMu.Unlock()

	ns.subscribers[channel] = append(ns.subscribers[channel], handler)

	// 새로운 구독자를 위한 Redis Pub/Sub 구독 시작
	if len(ns.subscribers[channel]) == 1 {
		ns.wg.Add(1)
		go ns.subscribeToChannel(channel)
	}

	return nil
}

// Publish sends a notification to a specific channel
func (ns *NotificationSystem) Publish(ctx context.Context, channel string, msg *NotificationMessage) error {
	if msg.CreatedAt.IsZero() {
		msg.CreatedAt = time.Now()
	}

	// 메시지 직렬화
	data, err := json.Marshal(msg)
	if err != nil {
		return fmt.Errorf("메시지 직렬화 실패: %v", err)
	}

	// Redis를 통해 메시지 발행
	err = ns.redisClient.Publish(ctx, channel, data).Err()
	if err != nil {
		return fmt.Errorf("메시지 발행 실패: %v", err)
	}

	return nil
}

// subscribeToChannel handles subscription to a Redis channel
func (ns *NotificationSystem) subscribeToChannel(channel string) {
	defer ns.wg.Done()

	pubsub := ns.redisClient.Subscribe(context.Background(), channel)
	defer pubsub.Close()

	// 구독 확인
	_, err := pubsub.Receive(context.Background())
	if err != nil {
		log.Printf("채널 %s 구독 실패: %v", channel, err)
		return
	}

	ch := pubsub.Channel()

	for {
		select {
		case msg := <-ch:
			if msg == nil {
				continue
			}

			var notification NotificationMessage
			err := json.Unmarshal([]byte(msg.Payload), &notification)
			if err != nil {
				log.Printf("메시지 역직렬화 실패: %v", err)
				continue
			}

			// 등록된 모든 핸들러에게 알림 전달
			ns.subscribersMu.RLock()
			handlers := ns.subscribers[channel]
			ns.subscribersMu.RUnlock()

			for _, handler := range handlers {
				go func(h NotificationHandler) {
					if err := h(&notification); err != nil {
						log.Printf("알림 처리 실패: %v", err)
					}
				}(handler)
			}

		case <-ns.done:
			return
		}
	}
}

// Unsubscribe removes a handler from a specific channel
func (ns *NotificationSystem) Unsubscribe(channel string, handler NotificationHandler) {
	ns.subscribersMu.Lock()
	defer ns.subscribersMu.Unlock()

	handlers := ns.subscribers[channel]
	for i, h := range handlers {
		if fmt.Sprintf("%p", h) == fmt.Sprintf("%p", handler) {
			ns.subscribers[channel] = append(handlers[:i], handlers[i+1:]...)
			break
		}
	}
}

// ListenChannels starts listening to multiple channels
func (ns *NotificationSystem) ListenChannels(channels ...string) error {
	for _, channel := range channels {
		if err := ns.Subscribe(channel, func(msg *NotificationMessage) error {
			log.Printf("채널 %s에서 메시지 수신: %+v", channel, msg)
			return nil
		}); err != nil {
			return fmt.Errorf("채널 %s 구독 실패: %v", channel, err)
		}
	}
	return nil
}

// Cleanup performs cleanup operations
func (ns *NotificationSystem) Cleanup() error {
	close(ns.done)
	ns.wg.Wait()

	if ns.redisClient != nil {
		if err := ns.redisClient.Close(); err != nil {
			return fmt.Errorf("Redis 연결 종료 실패: %v", err)
		}
	}

	return nil
}

// ExamplePubSub demonstrates the usage of the notification system
func ExamplePubSub() {
	ctx := context.Background()

	// 알림 시스템 초기화
	notificationSystem, err := NewNotificationSystem(ctx)
	if err != nil {
		log.Fatalf("알림 시스템 초기화 실패: %v", err)
	}
	defer notificationSystem.Cleanup()

	// 채널별 핸들러 등록
	channels := []string{"user_events", "system_events", "alerts"}
	if err := notificationSystem.ListenChannels(channels...); err != nil {
		log.Fatalf("채널 구독 실패: %v", err)
	}

	// 사용자 이벤트 채널에 대한 커스텀 핸들러 추가
	err = notificationSystem.Subscribe("user_events", func(msg *NotificationMessage) error {
		log.Printf("사용자 이벤트 처리: %s", msg.Content)
		// 여기에 사용자 이벤트에 대한 특별한 처리 로직을 추가할 수 있습니다
		return nil
	})
	if err != nil {
		log.Printf("사용자 이벤트 핸들러 등록 실패: %v", err)
	}

	// 테스트 메시지 발행
	testMessages := []*NotificationMessage{
		{
			ID:      "msg1",
			Type:    "USER_LOGIN",
			Channel: "user_events",
			Content: "사용자 로그인 감지",
			Metadata: map[string]interface{}{
				"user_id": "12345",
				"ip":      "192.168.1.1",
			},
		},
		{
			ID:      "msg2",
			Type:    "SYSTEM_UPDATE",
			Channel: "system_events",
			Content: "시스템 업데이트 시작",
		},
		{
			ID:      "msg3",
			Type:    "SECURITY_ALERT",
			Channel: "alerts",
			Content: "비정상적인 접근 시도 감지",
			Metadata: map[string]interface{}{
				"severity": "high",
				"source":   "firewall",
			},
		},
	}

	// 메시지 발행 및 처리 결과 확인
	for _, msg := range testMessages {
		if err := notificationSystem.Publish(ctx, msg.Channel, msg); err != nil {
			log.Printf("메시지 발행 실패: %v", err)
			continue
		}
		log.Printf("메시지 발행 성공: %s -> %s", msg.Channel, msg.Content)
	}

	// 메시지가 처리될 수 있도록 잠시 대기
	time.Sleep(2 * time.Second)
}
