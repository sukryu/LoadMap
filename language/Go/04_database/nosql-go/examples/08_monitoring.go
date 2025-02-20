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
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
)

// PerformanceMetrics represents database performance metrics
type PerformanceMetrics struct {
	Timestamp     time.Time              `json:"timestamp"`
	DatabaseType  string                 `json:"database_type"`
	OperationType string                 `json:"operation_type"`
	ExecutionTime float64                `json:"execution_time_ms"`
	Success       bool                   `json:"success"`
	ErrorMessage  string                 `json:"error_message,omitempty"`
	Details       map[string]interface{} `json:"details,omitempty"`
}

// AlertConfig defines alert thresholds and conditions
type AlertConfig struct {
	SlowQueryThreshold   float64 // milliseconds
	ErrorRateThreshold   float64 // percentage
	HighLatencyThreshold float64 // milliseconds
	AlertInterval        time.Duration
}

// DatabaseMonitor handles monitoring of MongoDB and Redis operations
type DatabaseMonitor struct {
	mongoClient       *mongo.Client
	redisClient       *redis.Client
	metricsCollection *mongo.Collection
	alertConfig       AlertConfig
	alertChan         chan string
	stopChan          chan struct{}
	wg                sync.WaitGroup
}

// NewDatabaseMonitor initializes a new database monitoring system
func NewDatabaseMonitor(ctx context.Context, alertConfig AlertConfig) (*DatabaseMonitor, error) {
	// MongoDB 클라이언트 초기화
	mongoOpts := options.Client().ApplyURI("mongodb://localhost:27017")
	mongoClient, err := mongo.Connect(ctx, mongoOpts)
	if err != nil {
		return nil, fmt.Errorf("MongoDB 연결 실패: %v", err)
	}

	// Redis 클라이언트 초기화
	redisClient := redis.NewClient(&redis.Options{
		Addr: "localhost:6379",
		DB:   0,
	})

	monitor := &DatabaseMonitor{
		mongoClient:       mongoClient,
		redisClient:       redisClient,
		metricsCollection: mongoClient.Database("monitoring").Collection("metrics"),
		alertConfig:       alertConfig,
		alertChan:         make(chan string, 100),
		stopChan:          make(chan struct{}),
	}

	// 모니터링 인덱스 생성
	if err := monitor.createMonitoringIndexes(ctx); err != nil {
		return nil, err
	}

	// 알림 처리기 시작
	monitor.startAlertHandler()

	return monitor, nil
}

// createMonitoringIndexes creates necessary indexes for monitoring data
func (dm *DatabaseMonitor) createMonitoringIndexes(ctx context.Context) error {
	indexes := []mongo.IndexModel{
		{
			Keys: bson.D{
				{Key: "timestamp", Value: -1},
				{Key: "database_type", Value: 1},
			},
			Options: options.Index().SetExpireAfterSeconds(7 * 24 * 60 * 60), // 7일 후 만료
		},
		{
			Keys: bson.D{
				{Key: "operation_type", Value: 1},
				{Key: "execution_time_ms", Value: 1},
			},
		},
	}

	_, err := dm.metricsCollection.Indexes().CreateMany(ctx, indexes)
	if err != nil {
		return fmt.Errorf("모니터링 인덱스 생성 실패: %v", err)
	}

	return nil
}

// RecordMetrics records performance metrics for a database operation
func (dm *DatabaseMonitor) RecordMetrics(ctx context.Context, metrics *PerformanceMetrics) error {
	// 메트릭 저장
	_, err := dm.metricsCollection.InsertOne(ctx, metrics)
	if err != nil {
		return fmt.Errorf("메트릭 저장 실패: %v", err)
	}

	// 알림 조건 확인
	if metrics.ExecutionTime > dm.alertConfig.SlowQueryThreshold {
		dm.alertChan <- fmt.Sprintf("슬로우 쿼리 감지: %s 작업이 %.2fms 소요됨",
			metrics.OperationType, metrics.ExecutionTime)
	}

	// Redis에 실시간 메트릭 캐시
	metricsJSON, _ := json.Marshal(metrics)
	cacheKey := fmt.Sprintf("metrics:%s:%s:%d",
		metrics.DatabaseType, metrics.OperationType, metrics.Timestamp.Unix())

	err = dm.redisClient.Set(ctx, cacheKey, metricsJSON, 24*time.Hour).Err()
	if err != nil {
		log.Printf("메트릭 캐시 저장 실패: %v", err)
	}

	return nil
}

// AnalyzePerformance analyzes database performance over a time period
func (dm *DatabaseMonitor) AnalyzePerformance(ctx context.Context, startTime, endTime time.Time) (map[string]interface{}, error) {
	pipeline := mongo.Pipeline{
		{{Key: "$match", Value: bson.D{
			{Key: "timestamp", Value: bson.D{
				{Key: "$gte", Value: startTime},
				{Key: "$lte", Value: endTime},
			}},
		}}},
		{{Key: "$group", Value: bson.D{
			{Key: "_id", Value: bson.D{
				{Key: "database_type", Value: "$database_type"},
				{Key: "operation_type", Value: "$operation_type"},
			}},
			{Key: "avg_execution_time", Value: bson.D{{Key: "$avg", Value: "$execution_time_ms"}}},
			{Key: "max_execution_time", Value: bson.D{{Key: "$max", Value: "$execution_time_ms"}}},
			{Key: "total_operations", Value: bson.D{{Key: "$sum", Value: 1}}},
			{Key: "error_count", Value: bson.D{
				{Key: "$sum", Value: bson.D{
					{Key: "$cond", Value: bson.A{bson.D{{Key: "$eq", Value: bson.A{"$success", false}}}, 1, 0}},
				}},
			}},
		}}},
	}

	cursor, err := dm.metricsCollection.Aggregate(ctx, pipeline)
	if err != nil {
		return nil, fmt.Errorf("성능 분석 실패: %v", err)
	}
	defer cursor.Close(ctx)

	var results []bson.M
	if err = cursor.All(ctx, &results); err != nil {
		return nil, fmt.Errorf("분석 결과 디코딩 실패: %v", err)
	}

	// 분석 결과 가공
	analysis := map[string]interface{}{
		"period_start":    startTime,
		"period_end":      endTime,
		"metrics_by_type": results,
	}

	return analysis, nil
}

// GetRealtimeMetrics retrieves real-time metrics from Redis cache
func (dm *DatabaseMonitor) GetRealtimeMetrics(ctx context.Context, databaseType, operationType string) ([]*PerformanceMetrics, error) {
	pattern := fmt.Sprintf("metrics:%s:%s:*", databaseType, operationType)
	keys, err := dm.redisClient.Keys(ctx, pattern).Result()
	if err != nil {
		return nil, fmt.Errorf("실시간 메트릭 키 조회 실패: %v", err)
	}

	var metrics []*PerformanceMetrics
	for _, key := range keys {
		data, err := dm.redisClient.Get(ctx, key).Result()
		if err != nil {
			continue
		}

		var metric PerformanceMetrics
		if err := json.Unmarshal([]byte(data), &metric); err != nil {
			continue
		}

		metrics = append(metrics, &metric)
	}

	return metrics, nil
}

// MonitorOperation wraps a database operation with performance monitoring
func (dm *DatabaseMonitor) MonitorOperation(ctx context.Context, databaseType, operationType string, operation func() error) error {
	startTime := time.Now()
	err := operation()
	executionTime := time.Since(startTime).Milliseconds()

	metrics := &PerformanceMetrics{
		Timestamp:     time.Now(),
		DatabaseType:  databaseType,
		OperationType: operationType,
		ExecutionTime: float64(executionTime),
		Success:       err == nil,
		Details: map[string]interface{}{
			"duration_ms": executionTime,
		},
	}

	if err != nil {
		metrics.ErrorMessage = err.Error()
	}

	// 비동기적으로 메트릭 기록
	go func() {
		if recordErr := dm.RecordMetrics(context.Background(), metrics); recordErr != nil {
			log.Printf("메트릭 기록 실패: %v", recordErr)
		}
	}()

	return err
}

// startAlertHandler starts the alert processing goroutine
func (dm *DatabaseMonitor) startAlertHandler() {
	dm.wg.Add(1)
	go func() {
		defer dm.wg.Done()
		for {
			select {
			case alert := <-dm.alertChan:
				log.Printf("알림: %s", alert)
				// 여기에 실제 알림 전송 로직 구현 (이메일, Slack 등)
			case <-dm.stopChan:
				return
			}
		}
	}()
}

// Cleanup performs cleanup operations
func (dm *DatabaseMonitor) Cleanup(ctx context.Context) error {
	close(dm.stopChan)
	dm.wg.Wait()

	var errors []error

	if dm.redisClient != nil {
		if err := dm.redisClient.Close(); err != nil {
			errors = append(errors, fmt.Errorf("Redis 연결 종료 실패: %v", err))
		}
	}

	if dm.mongoClient != nil {
		if err := dm.mongoClient.Disconnect(ctx); err != nil {
			errors = append(errors, fmt.Errorf("MongoDB 연결 종료 실패: %v", err))
		}
	}

	if len(errors) > 0 {
		return fmt.Errorf("정리 작업 중 오류 발생: %v", errors)
	}
	return nil
}

// ExampleMonitoring demonstrates the usage of database monitoring
func ExampleMonitoring() {
	ctx := context.Background()

	// 모니터링 시스템 초기화
	alertConfig := AlertConfig{
		SlowQueryThreshold:   200.0, // 200ms
		ErrorRateThreshold:   5.0,   // 5%
		HighLatencyThreshold: 500.0, // 500ms
		AlertInterval:        5 * time.Minute,
	}

	monitor, err := NewDatabaseMonitor(ctx, alertConfig)
	if err != nil {
		log.Fatalf("모니터링 시스템 초기화 실패: %v", err)
	}
	defer monitor.Cleanup(ctx)

	// 모니터링 테스트
	// MongoDB 작업 모니터링 예제
	err = monitor.MonitorOperation(ctx, "MongoDB", "find", func() error {
		// 샘플 MongoDB 작업
		_, err := monitor.metricsCollection.Find(ctx, bson.D{})
		return err
	})
	if err != nil {
		log.Printf("MongoDB 작업 실패: %v", err)
	}

	// Redis 작업 모니터링 예제
	err = monitor.MonitorOperation(ctx, "Redis", "get", func() error {
		// 샘플 Redis 작업
		return monitor.redisClient.Get(ctx, "test_key").Err()
	})
	if err != nil {
		log.Printf("Redis 작업 실패: %v", err)
	}

	// 성능 분석 예제
	startTime := time.Now().Add(-1 * time.Hour)
	endTime := time.Now()
	analysis, err := monitor.AnalyzePerformance(ctx, startTime, endTime)
	if err != nil {
		log.Printf("성능 분석 실패: %v", err)
	} else {
		log.Printf("성능 분석 결과: %+v", analysis)
	}

	// 실시간 메트릭 조회 예제
	realtimeMetrics, err := monitor.GetRealtimeMetrics(ctx, "MongoDB", "find")
	if err != nil {
		log.Printf("실시간 메트릭 조회 실패: %v", err)
	} else {
		log.Printf("MongoDB find 작업의 실시간 메트릭: %+v", realtimeMetrics)
	}
}
