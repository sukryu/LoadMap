package examples

import (
	"context"
	"encoding/json"
	"errors"
	"fmt"
	"log"
	"time"

	"github.com/go-redis/redis/v8"
	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/bson/primitive"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
	"go.mongodb.org/mongo-driver/mongo/readpref"
	"go.mongodb.org/mongo-driver/mongo/writeconcern"
)

// StorageError represents custom error types for storage operations
type StorageError struct {
	Operation   string
	Detail      string
	Recoverable bool
	Timestamp   time.Time
	OriginalErr error
}

func (e *StorageError) Error() string {
	return fmt.Sprintf("[%s] %s (Recoverable: %v, Time: %v): %v",
		e.Operation, e.Detail, e.Recoverable, e.Timestamp.Format(time.RFC3339), e.OriginalErr)
}

// DataRecord represents a data record in the storage system
type DataRecord struct {
	ID          primitive.ObjectID `bson:"_id,omitempty" json:"id"`
	Key         string             `bson:"key" json:"key"`
	Value       interface{}        `bson:"value" json:"value"`
	Version     int                `bson:"version" json:"version"`
	LastUpdated time.Time          `bson:"last_updated" json:"last_updated"`
	Status      string             `bson:"status" json:"status"`
}

// DataStorageOperations handles data storage operations with error handling
type DataStorageOperations struct {
	mongoClient *mongo.Client
	redisClient *redis.Client
	collection  *mongo.Collection
	maxRetries  int
	retryDelay  time.Duration
}

// NewDataStorageOperations initializes a new data storage operations manager
func NewDataStorageOperations(ctx context.Context) (*DataStorageOperations, error) {

	wc := &writeconcern.WriteConcern{
		W: "majority",
	}
	// MongoDB 클라이언트 설정
	mongoOpts := options.Client().
		ApplyURI("mongodb://localhost:27017").
		SetReadPreference(readpref.Primary()).
		SetWriteConcern(wc)

	mongoClient, err := mongo.Connect(ctx, mongoOpts)
	if err != nil {
		return nil, &StorageError{
			Operation:   "Initialize",
			Detail:      "MongoDB 연결 실패",
			Recoverable: true,
			Timestamp:   time.Now(),
			OriginalErr: err,
		}
	}

	// Redis 클라이언트 설정
	redisClient := redis.NewClient(&redis.Options{
		Addr:     "localhost:6379",
		Password: "",
		DB:       0,
	})

	return &DataStorageOperations{
		mongoClient: mongoClient,
		redisClient: redisClient,
		collection:  mongoClient.Database("storage").Collection("records"),
		maxRetries:  3,
		retryDelay:  1 * time.Second,
	}, nil
}

// StoreData stores data with error handling and retry mechanism
func (ds *DataStorageOperations) StoreData(ctx context.Context, key string, value interface{}) error {
	var lastErr error
	for attempt := 0; attempt < ds.maxRetries; attempt++ {
		err := ds.storeDataAttempt(ctx, key, value)
		if err == nil {
			return nil
		}

		lastErr = err
		var storageErr *StorageError
		if errors.As(err, &storageErr) && !storageErr.Recoverable {
			return err
		}

		log.Printf("저장 시도 %d 실패: %v, 재시도 중...", attempt+1, err)
		time.Sleep(ds.retryDelay)
	}

	return fmt.Errorf("최대 재시도 횟수 초과: %v", lastErr)
}

func (ds *DataStorageOperations) storeDataAttempt(ctx context.Context, key string, value interface{}) error {
	// MongoDB에 저장
	record := DataRecord{
		Key:         key,
		Value:       value,
		Version:     1,
		LastUpdated: time.Now(),
		Status:      "active",
	}

	_, err := ds.collection.InsertOne(ctx, record)
	if err != nil {
		if mongo.IsDuplicateKeyError(err) {
			return &StorageError{
				Operation:   "Store",
				Detail:      "중복된 키",
				Recoverable: false,
				Timestamp:   time.Now(),
				OriginalErr: err,
			}
		}
		return &StorageError{
			Operation:   "Store",
			Detail:      "MongoDB 저장 실패",
			Recoverable: true,
			Timestamp:   time.Now(),
			OriginalErr: err,
		}
	}

	// Redis 캐시 업데이트
	cacheData, err := json.Marshal(record)
	if err != nil {
		return &StorageError{
			Operation:   "Store",
			Detail:      "JSON 직렬화 실패",
			Recoverable: false,
			Timestamp:   time.Now(),
			OriginalErr: err,
		}
	}

	err = ds.redisClient.Set(ctx, key, cacheData, 30*time.Minute).Err()
	if err != nil {
		log.Printf("Redis 캐시 업데이트 실패 (비중단 오류): %v", err)
	}

	return nil
}

// RetrieveData retrieves data with error handling and cache management
func (ds *DataStorageOperations) RetrieveData(ctx context.Context, key string) (*DataRecord, error) {
	// Redis 캐시 확인
	cacheData, err := ds.redisClient.Get(ctx, key).Result()
	if err == nil {
		var record DataRecord
		if err := json.Unmarshal([]byte(cacheData), &record); err == nil {
			return &record, nil
		}
		// 캐시 역직렬화 실패는 무시하고 MongoDB에서 조회
		log.Printf("캐시 데이터 역직렬화 실패: %v", err)
	}

	// MongoDB에서 조회
	var record DataRecord
	err = ds.collection.FindOne(ctx, bson.D{{Key: "key", Value: key}}).Decode(&record)
	if err != nil {
		if err == mongo.ErrNoDocuments {
			return nil, &StorageError{
				Operation:   "Retrieve",
				Detail:      "데이터를 찾을 수 없음",
				Recoverable: false,
				Timestamp:   time.Now(),
				OriginalErr: err,
			}
		}
		return nil, &StorageError{
			Operation:   "Retrieve",
			Detail:      "MongoDB 조회 실패",
			Recoverable: true,
			Timestamp:   time.Now(),
			OriginalErr: err,
		}
	}

	// 성공적으로 조회된 데이터를 Redis에 캐시
	jsonData, err := json.Marshal(record)
	if err == nil {
		// []byte를 string으로 변환
		if err := ds.redisClient.Set(ctx, key, string(jsonData), 30*time.Minute).Err(); err != nil {
			log.Printf("Redis 캐시 업데이트 실패 (비중단 오류): %v", err)
		}
	}

	return &record, nil
}

// UpdateData updates data with optimistic locking
func (ds *DataStorageOperations) UpdateData(ctx context.Context, key string, value interface{}, expectedVersion int) error {
	var lastErr error
	for attempt := 0; attempt < ds.maxRetries; attempt++ {
		err := ds.updateDataAttempt(ctx, key, value, expectedVersion)
		if err == nil {
			return nil
		}

		lastErr = err
		var storageErr *StorageError
		if errors.As(err, &storageErr) && !storageErr.Recoverable {
			return err
		}

		log.Printf("업데이트 시도 %d 실패: %v, 재시도 중...", attempt+1, err)
		time.Sleep(ds.retryDelay)
	}

	return fmt.Errorf("최대 재시도 횟수 초과: %v", lastErr)
}

func (ds *DataStorageOperations) updateDataAttempt(ctx context.Context, key string, value interface{}, expectedVersion int) error {
	// 낙관적 락킹을 사용한 업데이트
	result, err := ds.collection.UpdateOne(
		ctx,
		bson.D{
			{Key: "key", Value: key},
			{Key: "version", Value: expectedVersion},
		},
		bson.D{
			{Key: "$set", Value: bson.D{
				{Key: "value", Value: value},
				{Key: "version", Value: expectedVersion + 1},
				{Key: "last_updated", Value: time.Now()},
			}},
		},
	)

	if err != nil {
		return &StorageError{
			Operation:   "Update",
			Detail:      "MongoDB 업데이트 실패",
			Recoverable: true,
			Timestamp:   time.Now(),
			OriginalErr: err,
		}
	}

	if result.MatchedCount == 0 {
		return &StorageError{
			Operation:   "Update",
			Detail:      "버전 불일치 또는 데이터를 찾을 수 없음",
			Recoverable: false,
			Timestamp:   time.Now(),
			OriginalErr: fmt.Errorf("no document matched the update criteria"),
		}
	}

	// Redis 캐시 무효화
	err = ds.redisClient.Del(ctx, key).Err()
	if err != nil {
		log.Printf("Redis 캐시 무효화 실패 (비중단 오류): %v", err)
	}

	return nil
}

// DeleteData deletes data with error handling
func (ds *DataStorageOperations) DeleteData(ctx context.Context, key string) error {
	// MongoDB에서 삭제
	result, err := ds.collection.DeleteOne(ctx, bson.D{{Key: "key", Value: key}})
	if err != nil {
		return &StorageError{
			Operation:   "Delete",
			Detail:      "MongoDB 삭제 실패",
			Recoverable: true,
			Timestamp:   time.Now(),
			OriginalErr: err,
		}
	}

	if result.DeletedCount == 0 {
		return &StorageError{
			Operation:   "Delete",
			Detail:      "데이터를 찾을 수 없음",
			Recoverable: false,
			Timestamp:   time.Now(),
			OriginalErr: fmt.Errorf("no document matched the delete criteria"),
		}
	}

	// Redis 캐시 삭제
	err = ds.redisClient.Del(ctx, key).Err()
	if err != nil {
		log.Printf("Redis 캐시 삭제 실패 (비중단 오류): %v", err)
	}

	return nil
}

// Cleanup performs cleanup operations
func (ds *DataStorageOperations) Cleanup(ctx context.Context) error {
	var errors []error

	if ds.redisClient != nil {
		if err := ds.redisClient.Close(); err != nil {
			errors = append(errors, fmt.Errorf("Redis 연결 종료 실패: %v", err))
		}
	}

	if ds.mongoClient != nil {
		if err := ds.mongoClient.Disconnect(ctx); err != nil {
			errors = append(errors, fmt.Errorf("MongoDB 연결 종료 실패: %v", err))
		}
	}

	if len(errors) > 0 {
		return fmt.Errorf("정리 작업 중 오류 발생: %v", errors)
	}
	return nil
}

// ExampleErrorHandling demonstrates the usage of error handling mechanisms
func ExampleErrorHandling() {
	ctx := context.Background()

	// 스토리지 연산 초기화
	storage, err := NewDataStorageOperations(ctx)
	if err != nil {
		log.Fatalf("스토리지 초기화 실패: %v", err)
	}
	defer storage.Cleanup(ctx)

	// 데이터 저장 테스트
	testData := map[string]interface{}{
		"name":     "Test Item",
		"quantity": 100,
		"tags":     []string{"test", "example"},
	}

	err = storage.StoreData(ctx, "test_key", testData)
	if err != nil {
		log.Printf("데이터 저장 실패: %v", err)
	} else {
		log.Println("데이터 저장 성공")
	}

	// 데이터 조회 테스트
	record, err := storage.RetrieveData(ctx, "test_key")
	if err != nil {
		log.Printf("데이터 조회 실패: %v", err)
	} else {
		log.Printf("조회된 데이터: %+v", record)
	}

	// 데이터 업데이트 테스트
	updatedData := map[string]interface{}{
		"name":     "Updated Item",
		"quantity": 150,
		"tags":     []string{"test", "example", "updated"},
	}

	err = storage.UpdateData(ctx, "test_key", updatedData, 1)
	if err != nil {
		log.Printf("데이터 업데이트 실패: %v", err)
	} else {
		log.Println("데이터 업데이트 성공")
	}

	// 데이터 삭제 테스트
	err = storage.DeleteData(ctx, "test_key")
	if err != nil {
		log.Printf("데이터 삭제 실패: %v", err)
	} else {
		log.Println("데이터 삭제 성공")
	}
}
