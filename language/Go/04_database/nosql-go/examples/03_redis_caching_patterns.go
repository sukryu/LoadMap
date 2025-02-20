package examples

import (
	"context"
	"encoding/json"
	"fmt"
	"log"
	"sync"
	"time"

	"github.com/go-redis/redis/v8"
	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/bson/primitive"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
)

// OrderDetails represents an e-commerce order
type OrderDetails struct {
	ID          primitive.ObjectID `bson:"_id" json:"id"`
	CustomerID  string             `bson:"customer_id" json:"customer_id"`
	Status      string             `bson:"status" json:"status"`
	TotalAmount float64            `bson:"total_amount" json:"total_amount"`
	ItemCount   int                `bson:"item_count" json:"item_count"`
	CreatedAt   time.Time          `bson:"created_at" json:"created_at"`
	LastUpdated time.Time          `bson:"last_updated" json:"last_updated"`
}

// OrderCacheManager handles different caching strategies for order data
type OrderCacheManager struct {
	redisClient  *redis.Client
	mongoClient  *mongo.Client
	collection   *mongo.Collection
	writeBufSize int
	writeBufChan chan *OrderDetails
	wg           sync.WaitGroup
}

// NewOrderCacheManager initializes a new order cache manager
func NewOrderCacheManager(ctx context.Context, writeBufSize int) (*OrderCacheManager, error) {
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

	// MongoDB 클라이언트 초기화
	mongoClient, err := mongo.Connect(ctx, options.Client().ApplyURI("mongodb://localhost:27017"))
	if err != nil {
		return nil, fmt.Errorf("MongoDB 연결 실패: %v", err)
	}

	// MongoDB 연결 확인
	if err := mongoClient.Ping(ctx, nil); err != nil {
		return nil, fmt.Errorf("MongoDB 연결 확인 실패: %v", err)
	}

	manager := &OrderCacheManager{
		redisClient:  redisClient,
		mongoClient:  mongoClient,
		collection:   mongoClient.Database("ecommerce").Collection("orders"),
		writeBufSize: writeBufSize,
		writeBufChan: make(chan *OrderDetails, writeBufSize),
	}

	// Write-Behind 워커 시작
	manager.startWriteBehindWorker(ctx)

	return manager, nil
}

// getCacheKey generates a Redis key for an order
func (m *OrderCacheManager) getCacheKey(orderID primitive.ObjectID) string {
	return fmt.Sprintf("order:%s", orderID.Hex())
}

// CacheAside implements the Cache-Aside pattern
func (m *OrderCacheManager) CacheAside(ctx context.Context, orderID primitive.ObjectID) (*OrderDetails, error) {
	cacheKey := m.getCacheKey(orderID)

	// Redis에서 먼저 조회
	cachedOrder, err := m.redisClient.Get(ctx, cacheKey).Result()
	if err == nil {
		var order OrderDetails
		if err := json.Unmarshal([]byte(cachedOrder), &order); err == nil {
			log.Printf("Cache hit for order: %s", orderID.Hex())
			return &order, nil
		}
	}

	// Cache miss: MongoDB에서 조회
	var order OrderDetails
	err = m.collection.FindOne(ctx, bson.D{{Key: "_id", Value: orderID}}).Decode(&order)
	if err != nil {
		if err == mongo.ErrNoDocuments {
			return nil, fmt.Errorf("주문을 찾을 수 없음: %s", orderID.Hex())
		}
		return nil, fmt.Errorf("주문 조회 실패: %v", err)
	}

	// Redis에 캐시 저장 (30분 유효)
	orderJSON, err := json.Marshal(order)
	if err == nil {
		err = m.redisClient.Set(ctx, cacheKey, orderJSON, 30*time.Minute).Err()
		if err != nil {
			log.Printf("캐시 저장 실패: %v", err)
		}
	}

	return &order, nil
}

// WriteThrough implements the Write-Through pattern
func (m *OrderCacheManager) WriteThrough(ctx context.Context, order *OrderDetails) error {
	// MongoDB에 먼저 저장
	if order.ID.IsZero() {
		order.ID = primitive.NewObjectID()
	}
	order.LastUpdated = time.Now()

	_, err := m.collection.UpdateOne(
		ctx,
		bson.D{{Key: "_id", Value: order.ID}},
		bson.D{{Key: "$set", Value: order}},
		options.Update().SetUpsert(true),
	)
	if err != nil {
		return fmt.Errorf("MongoDB 저장 실패: %v", err)
	}

	// Redis 캐시 업데이트
	orderJSON, err := json.Marshal(order)
	if err != nil {
		return fmt.Errorf("주문 데이터 직렬화 실패: %v", err)
	}

	err = m.redisClient.Set(ctx, m.getCacheKey(order.ID), orderJSON, 30*time.Minute).Err()
	if err != nil {
		log.Printf("Redis 캐시 업데이트 실패: %v", err)
	}

	return nil
}

// WriteBehind implements the Write-Behind pattern
func (m *OrderCacheManager) WriteBehind(ctx context.Context, order *OrderDetails) error {
	// Redis에 즉시 저장
	orderJSON, err := json.Marshal(order)
	if err != nil {
		return fmt.Errorf("주문 데이터 직렬화 실패: %v", err)
	}

	err = m.redisClient.Set(ctx, m.getCacheKey(order.ID), orderJSON, 30*time.Minute).Err()
	if err != nil {
		return fmt.Errorf("Redis 캐시 저장 실패: %v", err)
	}

	// 비동기 MongoDB 저장을 위해 채널에 추가
	select {
	case m.writeBufChan <- order:
		return nil
	default:
		return fmt.Errorf("쓰기 버퍼가 가득 참")
	}
}

// startWriteBehindWorker starts a background worker for the Write-Behind pattern
func (m *OrderCacheManager) startWriteBehindWorker(ctx context.Context) {
	m.wg.Add(1)
	go func() {
		defer m.wg.Done()
		ticker := time.NewTicker(5 * time.Second)
		defer ticker.Stop()

		buffer := make([]*OrderDetails, 0, m.writeBufSize)

		for {
			select {
			case <-ctx.Done():
				// 남은 버퍼 처리
				if len(buffer) > 0 {
					m.flushBuffer(context.Background(), buffer)
				}
				return

			case order := <-m.writeBufChan:
				buffer = append(buffer, order)
				if len(buffer) >= m.writeBufSize {
					m.flushBuffer(ctx, buffer)
					buffer = make([]*OrderDetails, 0, m.writeBufSize)
				}

			case <-ticker.C:
				if len(buffer) > 0 {
					m.flushBuffer(ctx, buffer)
					buffer = make([]*OrderDetails, 0, m.writeBufSize)
				}
			}
		}
	}()
}

// flushBuffer writes buffered orders to MongoDB
func (m *OrderCacheManager) flushBuffer(ctx context.Context, buffer []*OrderDetails) {
	if len(buffer) == 0 {
		return
	}

	operations := make([]mongo.WriteModel, len(buffer))
	for i, order := range buffer {
		order.LastUpdated = time.Now()
		operations[i] = mongo.NewUpdateOneModel().
			SetFilter(bson.D{{Key: "_id", Value: order.ID}}).
			SetUpdate(bson.D{{Key: "$set", Value: order}}).
			SetUpsert(true)
	}

	_, err := m.collection.BulkWrite(ctx, operations)
	if err != nil {
		log.Printf("벌크 쓰기 실패: %v", err)
		// 실패한 작업 재시도 로직을 여기에 구현할 수 있습니다
	}
}

// InvalidateCache removes an order from the cache
func (m *OrderCacheManager) InvalidateCache(ctx context.Context, orderID primitive.ObjectID) error {
	return m.redisClient.Del(ctx, m.getCacheKey(orderID)).Err()
}

// Cleanup performs cleanup operations
func (m *OrderCacheManager) Cleanup(ctx context.Context) error {
	// Write-Behind 워커가 남은 작업을 처리할 때까지 대기
	m.wg.Wait()

	// Redis 연결 종료
	if err := m.redisClient.Close(); err != nil {
		log.Printf("Redis 연결 종료 실패: %v", err)
	}

	// MongoDB 연결 종료
	if err := m.mongoClient.Disconnect(ctx); err != nil {
		log.Printf("MongoDB 연결 종료 실패: %v", err)
	}

	return nil
}

// ExampleCachingPatterns demonstrates the usage of different caching patterns
func ExampleCachingPatterns() {
	ctx, cancel := context.WithTimeout(context.Background(), 1*time.Minute)
	defer cancel()

	// 캐시 매니저 초기화
	manager, err := NewOrderCacheManager(ctx, 100)
	if err != nil {
		log.Fatalf("캐시 매니저 초기화 실패: %v", err)
	}
	defer manager.Cleanup(ctx)

	// 예제 주문 생성
	order := &OrderDetails{
		ID:          primitive.NewObjectID(),
		CustomerID:  "CUST123",
		Status:      "PENDING",
		TotalAmount: 299.99,
		ItemCount:   3,
		CreatedAt:   time.Now(),
	}

	// Write-Through 패턴 테스트
	log.Println("Write-Through 패턴 테스트 시작...")
	if err := manager.WriteThrough(ctx, order); err != nil {
		log.Printf("Write-Through 실패: %v", err)
	}

	// Cache-Aside 패턴 테스트
	log.Println("Cache-Aside 패턴 테스트 시작...")
	retrievedOrder, err := manager.CacheAside(ctx, order.ID)
	if err != nil {
		log.Printf("Cache-Aside 실패: %v", err)
	} else {
		log.Printf("조회된 주문: %+v", retrievedOrder)
	}

	// Write-Behind 패턴 테스트
	log.Println("Write-Behind 패턴 테스트 시작...")
	order.Status = "PROCESSING"
	if err := manager.WriteBehind(ctx, order); err != nil {
		log.Printf("Write-Behind 실패: %v", err)
	}

	// 캐시 무효화 테스트
	log.Println("캐시 무효화 테스트 시작...")
	if err := manager.InvalidateCache(ctx, order.ID); err != nil {
		log.Printf("캐시 무효화 실패: %v", err)
	}

	// 변경사항이 적용되도록 잠시 대기
	time.Sleep(6 * time.Second)
}
