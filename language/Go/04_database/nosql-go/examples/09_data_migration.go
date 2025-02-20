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

// MigrationRecord represents a migration task record
type MigrationRecord struct {
	TaskID         string                 `bson:"task_id"`
	SourceDB       string                 `bson:"source_db"`
	TargetDB       string                 `bson:"target_db"`
	Collection     string                 `bson:"collection"`
	Status         string                 `bson:"status"`
	StartTime      time.Time              `bson:"start_time"`
	EndTime        time.Time              `bson:"end_time,omitempty"`
	TotalRecords   int64                  `bson:"total_records"`
	ProcessedCount int64                  `bson:"processed_count"`
	ErrorCount     int64                  `bson:"error_count"`
	Metadata       map[string]interface{} `bson:"metadata,omitempty"`
}

// MigrationProgress represents the current progress of a migration task
type MigrationProgress struct {
	TaskID          string    `json:"task_id"`
	Status          string    `json:"status"`
	ProgressPercent float64   `json:"progress_percent"`
	TimeElapsed     float64   `json:"time_elapsed_seconds"`
	TimeRemaining   float64   `json:"time_remaining_seconds,omitempty"`
	ErrorCount      int64     `json:"error_count"`
	LastUpdateTime  time.Time `json:"last_update_time"`
}

// DataMigrationManager handles data migration between databases
type DataMigrationManager struct {
	sourceClient           *mongo.Client
	targetClient           *mongo.Client
	redisClient            *redis.Client
	migrationRecords       *mongo.Collection
	batchSize              int
	workerCount            int
	progressUpdateInterval time.Duration
	wg                     sync.WaitGroup
}

// NewDataMigrationManager initializes a new data migration manager
func NewDataMigrationManager(ctx context.Context, sourceURI, targetURI string) (*DataMigrationManager, error) {
	// 소스 MongoDB 클라이언트 초기화
	sourceClient, err := mongo.Connect(ctx, options.Client().ApplyURI(sourceURI))
	if err != nil {
		return nil, fmt.Errorf("소스 DB 연결 실패: %v", err)
	}

	// 타겟 MongoDB 클라이언트 초기화
	targetClient, err := mongo.Connect(ctx, options.Client().ApplyURI(targetURI))
	if err != nil {
		return nil, fmt.Errorf("타겟 DB 연결 실패: %v", err)
	}

	// Redis 클라이언트 초기화 (진행 상황 추적용)
	redisClient := redis.NewClient(&redis.Options{
		Addr: "localhost:6379",
		DB:   0,
	})

	manager := &DataMigrationManager{
		sourceClient:           sourceClient,
		targetClient:           targetClient,
		redisClient:            redisClient,
		migrationRecords:       targetClient.Database("admin").Collection("migration_records"),
		batchSize:              1000,
		workerCount:            5,
		progressUpdateInterval: 5 * time.Second,
	}

	return manager, nil
}

// StartMigration initiates a data migration process
func (dm *DataMigrationManager) StartMigration(ctx context.Context, sourceDB, targetDB, collection string) (string, error) {
	taskID := fmt.Sprintf("migration_%s_%s", collection, time.Now().Format("20060102_150405"))

	// 컬렉션 통계 조회
	sourceCollection := dm.sourceClient.Database(sourceDB).Collection(collection)
	count, err := sourceCollection.CountDocuments(ctx, bson.D{})
	if err != nil {
		return "", fmt.Errorf("소스 컬렉션 통계 조회 실패: %v", err)
	}

	// 마이그레이션 기록 생성
	record := &MigrationRecord{
		TaskID:       taskID,
		SourceDB:     sourceDB,
		TargetDB:     targetDB,
		Collection:   collection,
		Status:       "running",
		StartTime:    time.Now(),
		TotalRecords: count,
	}

	_, err = dm.migrationRecords.InsertOne(ctx, record)
	if err != nil {
		return "", fmt.Errorf("마이그레이션 기록 생성 실패: %v", err)
	}

	// 마이그레이션 작업 시작
	go dm.runMigration(taskID, sourceDB, targetDB, collection)

	return taskID, nil
}

// runMigration performs the actual migration process
func (dm *DataMigrationManager) runMigration(taskID, sourceDB, targetDB, collection string) {
	ctx := context.Background()
	sourceCollection := dm.sourceClient.Database(sourceDB).Collection(collection)
	targetCollection := dm.targetClient.Database(targetDB).Collection(collection)

	// 작업 채널 생성
	workChan := make(chan []bson.D, dm.workerCount)
	errorChan := make(chan error, dm.workerCount)

	// 작업자 시작
	for i := 0; i < dm.workerCount; i++ {
		dm.wg.Add(1)
		go dm.migrationWorker(taskID, targetCollection, workChan, errorChan)
	}

	// 진행 상황 모니터링 고루틴 시작
	go dm.monitorProgress(taskID)

	// 데이터 배치 처리
	options := options.Find().SetBatchSize(int32(dm.batchSize))
	cursor, err := sourceCollection.Find(ctx, bson.D{}, options)
	if err != nil {
		dm.updateMigrationStatus(ctx, taskID, "failed", fmt.Sprintf("데이터 조회 실패: %v", err))
		return
	}
	defer cursor.Close(ctx)

	var batch []bson.D
	for cursor.Next(ctx) {
		var doc bson.D
		if err := cursor.Decode(&doc); err != nil {
			errorChan <- fmt.Errorf("문서 디코딩 실패: %v", err)
			continue
		}

		batch = append(batch, doc)
		if len(batch) >= dm.batchSize {
			workChan <- batch
			batch = make([]bson.D, 0, dm.batchSize)
		}
	}

	// 남은 배치 처리
	if len(batch) > 0 {
		workChan <- batch
	}

	// 작업 채널 닫기
	close(workChan)
	dm.wg.Wait()
	close(errorChan)

	// 최종 상태 업데이트
	dm.finalizeMigration(ctx, taskID)
}

// migrationWorker handles batch processing of documents
func (dm *DataMigrationManager) migrationWorker(taskID string, targetCollection *mongo.Collection, workChan <-chan []bson.D, errorChan chan<- error) {
	defer dm.wg.Done()

	ctx := context.Background()
	for batch := range workChan {
		if len(batch) == 0 {
			continue
		}

		operations := make([]mongo.WriteModel, len(batch))
		for i, doc := range batch {
			operations[i] = mongo.NewInsertOneModel().SetDocument(doc)
		}

		_, err := targetCollection.BulkWrite(ctx, operations)
		if err != nil {
			errorChan <- fmt.Errorf("벌크 쓰기 실패: %v", err)
			continue
		}

		// 진행 상황 업데이트
		dm.incrementProcessedCount(ctx, taskID, int64(len(batch)))
	}
}

// monitorProgress monitors and updates migration progress
func (dm *DataMigrationManager) monitorProgress(taskID string) {
	ctx := context.Background()
	ticker := time.NewTicker(dm.progressUpdateInterval)
	defer ticker.Stop()

	for range ticker.C {
		record := dm.getMigrationRecord(ctx, taskID)
		if record == nil {
			continue
		}

		if record.Status != "running" {
			break
		}

		progress := &MigrationProgress{
			TaskID:          taskID,
			Status:          record.Status,
			ProgressPercent: float64(record.ProcessedCount) / float64(record.TotalRecords) * 100,
			TimeElapsed:     time.Since(record.StartTime).Seconds(),
			ErrorCount:      record.ErrorCount,
			LastUpdateTime:  time.Now(),
		}

		// Redis에 진행 상황 저장
		progressJSON, _ := json.Marshal(progress)
		dm.redisClient.Set(ctx, fmt.Sprintf("migration_progress:%s", taskID), progressJSON, 24*time.Hour)
	}
}

// getMigrationRecord retrieves the current migration record
func (dm *DataMigrationManager) getMigrationRecord(ctx context.Context, taskID string) *MigrationRecord {
	var record MigrationRecord
	err := dm.migrationRecords.FindOne(ctx, bson.D{{Key: "task_id", Value: taskID}}).Decode(&record)
	if err != nil {
		return nil
	}
	return &record
}

// incrementProcessedCount atomically increments the processed count
func (dm *DataMigrationManager) incrementProcessedCount(ctx context.Context, taskID string, count int64) {
	_, err := dm.migrationRecords.UpdateOne(
		ctx,
		bson.D{{Key: "task_id", Value: taskID}},
		bson.D{{Key: "$inc", Value: bson.D{{Key: "processed_count", Value: count}}}},
	)
	if err != nil {
		log.Printf("진행 상황 업데이트 실패: %v", err)
	}
}

// updateMigrationStatus updates the migration status
func (dm *DataMigrationManager) updateMigrationStatus(ctx context.Context, taskID, status, message string) {
	update := bson.D{
		{Key: "$set", Value: bson.D{
			{Key: "status", Value: status},
			{Key: "metadata.last_message", Value: message},
			{Key: "end_time", Value: time.Now()},
		}},
	}

	_, err := dm.migrationRecords.UpdateOne(ctx, bson.D{{Key: "task_id", Value: taskID}}, update)
	if err != nil {
		log.Printf("상태 업데이트 실패: %v", err)
	}
}

// finalizeMigration performs final checks and updates for the migration
func (dm *DataMigrationManager) finalizeMigration(ctx context.Context, taskID string) {
	record := dm.getMigrationRecord(ctx, taskID)
	if record == nil {
		return
	}

	status := "completed"
	if record.ErrorCount > 0 {
		status = "completed_with_errors"
	}

	dm.updateMigrationStatus(ctx, taskID, status, "마이그레이션 완료")
}

// GetMigrationProgress retrieves the current progress of a migration task
func (dm *DataMigrationManager) GetMigrationProgress(ctx context.Context, taskID string) (*MigrationProgress, error) {
	progressJSON, err := dm.redisClient.Get(ctx, fmt.Sprintf("migration_progress:%s", taskID)).Result()
	if err != nil {
		return nil, fmt.Errorf("진행 상황 조회 실패: %v", err)
	}

	var progress MigrationProgress
	if err := json.Unmarshal([]byte(progressJSON), &progress); err != nil {
		return nil, fmt.Errorf("진행 상황 파싱 실패: %v", err)
	}

	return &progress, nil
}

// Cleanup performs cleanup operations
func (dm *DataMigrationManager) Cleanup(ctx context.Context) error {
	var errors []error

	if dm.redisClient != nil {
		if err := dm.redisClient.Close(); err != nil {
			errors = append(errors, fmt.Errorf("Redis 연결 종료 실패: %v", err))
		}
	}

	if dm.sourceClient != nil {
		if err := dm.sourceClient.Disconnect(ctx); err != nil {
			errors = append(errors, fmt.Errorf("소스 MongoDB 연결 종료 실패: %v", err))
		}
	}

	if dm.targetClient != nil {
		if err := dm.targetClient.Disconnect(ctx); err != nil {
			errors = append(errors, fmt.Errorf("타겟 MongoDB 연결 종료 실패: %v", err))
		}
	}

	if len(errors) > 0 {
		return fmt.Errorf("정리 작업 중 오류 발생: %v", errors)
	}
	return nil
}

// ExampleMigration demonstrates the usage of data migration
func ExampleMigration() {
	ctx := context.Background()

	// 마이그레이션 매니저 초기화
	manager, err := NewDataMigrationManager(ctx,
		"mongodb://localhost:27017", // 소스 DB
		"mongodb://localhost:27018") // 타겟 DB
	if err != nil {
		log.Fatalf("마이그레이션 매니저 초기화 실패: %v", err)
	}
	defer manager.Cleanup(ctx)

	// 마이그레이션 시작
	taskID, err := manager.StartMigration(ctx, "sourceDB", "targetDB", "users")
	if err != nil {
		log.Fatalf("마이그레이션 시작 실패: %v", err)
	}

	// 진행 상황 모니터링
	for {
		progress, err := manager.GetMigrationProgress(ctx, taskID)
		if err != nil {
			log.Printf("진행 상황 조회 실패: %v", err)
			break
		}

		log.Printf("마이그레이션 진행 상황: %.2f%% 완료", progress.ProgressPercent)
		log.Printf("처리된 시간: %.2f초", progress.TimeElapsed)
		if progress.ErrorCount > 0 {
			log.Printf("발생한 오류 수: %d", progress.ErrorCount)
		}

		if progress.Status != "running" {
			log.Printf("마이그레이션 최종 상태: %s", progress.Status)
			break
		}

		// 5초마다 진행 상황 확인
		time.Sleep(5 * time.Second)
	}

	// 마이그레이션 기록 조회
	record := manager.getMigrationRecord(ctx, taskID)
	if record != nil {
		log.Printf("마이그레이션 요약:")
		log.Printf("- 총 레코드 수: %d", record.TotalRecords)
		log.Printf("- 처리된 레코드 수: %d", record.ProcessedCount)
		log.Printf("- 오류 발생 수: %d", record.ErrorCount)
		log.Printf("- 소요 시간: %v", record.EndTime.Sub(record.StartTime))
		log.Printf("- 최종 상태: %s", record.Status)

		if record.Metadata != nil {
			if lastMessage, ok := record.Metadata["last_message"].(string); ok {
				log.Printf("- 마지막 메시지: %s", lastMessage)
			}
		}
	}
}
