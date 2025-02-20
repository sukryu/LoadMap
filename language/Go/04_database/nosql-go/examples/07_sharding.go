package examples

import (
	"context"
	"fmt"
	"log"
	"time"

	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/bson/primitive"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
	"go.mongodb.org/mongo-driver/mongo/readpref"
	"go.mongodb.org/mongo-driver/mongo/writeconcern"
)

// LogisticsData represents logistics data in the sharded collection
type LogisticsData struct {
	ID          primitive.ObjectID     `bson:"_id,omitempty"`
	RegionCode  string                 `bson:"region_code"`  // 샤드 키
	WarehouseID string                 `bson:"warehouse_id"` // 샤드 키
	ProductID   string                 `bson:"product_id"`
	Quantity    int                    `bson:"quantity"`
	LastUpdated time.Time              `bson:"last_updated"`
	Status      string                 `bson:"status"`
	Metadata    map[string]interface{} `bson:"metadata,omitempty"`
}

// ShardedDataManager handles operations in a sharded MongoDB environment
type ShardedDataManager struct {
	client      *mongo.Client
	collection  *mongo.Collection
	shardConfig *ShardConfiguration
}

// ShardConfiguration holds sharding-related settings
type ShardConfiguration struct {
	ShardKey       bson.D
	NumberOfShards int
	ChunkSize      int64
}

// NewShardedDataManager initializes a new sharded data manager
func NewShardedDataManager(ctx context.Context, shardConfig *ShardConfiguration) (*ShardedDataManager, error) {

	wc := &writeconcern.WriteConcern{
		W: "majority",
	}
	// MongoDB 클러스터에 연결 (실제 환경에서는 복수의 mongos 라우터 주소 사용)
	clientOpts := options.Client().
		ApplyURI("mongodb://localhost:27017").
		SetReadPreference(readpref.Primary()).
		SetWriteConcern(wc)

	client, err := mongo.Connect(ctx, clientOpts)
	if err != nil {
		return nil, fmt.Errorf("MongoDB 클러스터 연결 실패: %v", err)
	}

	// 연결 확인
	if err = client.Ping(ctx, nil); err != nil {
		return nil, fmt.Errorf("MongoDB 클러스터 연결 확인 실패: %v", err)
	}

	manager := &ShardedDataManager{
		client:      client,
		collection:  client.Database("logistics").Collection("inventory"),
		shardConfig: shardConfig,
	}

	// 컬렉션 샤딩 설정 (실제 환경에서는 이미 설정되어 있을 수 있음)
	if err := manager.setupSharding(ctx); err != nil {
		return nil, fmt.Errorf("샤딩 설정 실패: %v", err)
	}

	return manager, nil
}

// setupSharding configures sharding for the collection
func (sm *ShardedDataManager) setupSharding(ctx context.Context) error {
	// 데이터베이스 샤딩 활성화
	cmd := bson.D{{Key: "enableSharding", Value: "logistics"}}
	err := sm.client.Database("admin").RunCommand(ctx, cmd).Err()
	if err != nil {
		log.Printf("데이터베이스 샤딩 활성화 실패 (이미 활성화되어 있을 수 있음): %v", err)
	}

	// 컬렉션 샤딩 설정
	cmd = bson.D{
		{Key: "shardCollection", Value: "logistics.inventory"},
		{Key: "key", Value: sm.shardConfig.ShardKey},
	}
	err = sm.client.Database("admin").RunCommand(ctx, cmd).Err()
	if err != nil {
		log.Printf("컬렉션 샤딩 설정 실패 (이미 설정되어 있을 수 있음): %v", err)
	}

	return nil
}

// InsertLogisticsData inserts data with shard key awareness
func (sm *ShardedDataManager) InsertLogisticsData(ctx context.Context, data *LogisticsData) error {
	data.LastUpdated = time.Now()

	_, err := sm.collection.InsertOne(ctx, data)
	if err != nil {
		return fmt.Errorf("데이터 삽입 실패: %v", err)
	}

	return nil
}

// QueryByRegion performs a targeted query on a specific shard
func (sm *ShardedDataManager) QueryByRegion(ctx context.Context, regionCode string) ([]LogisticsData, error) {
	// 샤드 키를 포함한 쿼리는 특정 샤드로 직접 라우팅됨
	filter := bson.D{{Key: "region_code", Value: regionCode}}

	cursor, err := sm.collection.Find(ctx, filter)
	if err != nil {
		return nil, fmt.Errorf("지역별 쿼리 실패: %v", err)
	}
	defer cursor.Close(ctx)

	var results []LogisticsData
	if err = cursor.All(ctx, &results); err != nil {
		return nil, fmt.Errorf("결과 디코딩 실패: %v", err)
	}

	return results, nil
}

// AggregateByWarehouse performs an aggregation across shards
func (sm *ShardedDataManager) AggregateByWarehouse(ctx context.Context) ([]map[string]interface{}, error) {
	pipeline := mongo.Pipeline{
		{{Key: "$group", Value: bson.D{
			{Key: "_id", Value: "$warehouse_id"},
			{Key: "total_quantity", Value: bson.D{{Key: "$sum", Value: "$quantity"}}},
			{Key: "product_count", Value: bson.D{{Key: "$addToSet", Value: "$product_id"}}},
		}}},
		{{Key: "$project", Value: bson.D{
			{Key: "warehouse_id", Value: "$_id"},
			{Key: "total_quantity", Value: 1},
			{Key: "unique_products", Value: bson.D{{Key: "$size", Value: "$product_count"}}},
		}}},
		{{Key: "$sort", Value: bson.D{{Key: "total_quantity", Value: -1}}}},
	}

	cursor, err := sm.collection.Aggregate(ctx, pipeline)
	if err != nil {
		return nil, fmt.Errorf("창고별 집계 실패: %v", err)
	}
	defer cursor.Close(ctx)

	var results []map[string]interface{}
	if err = cursor.All(ctx, &results); err != nil {
		return nil, fmt.Errorf("집계 결과 디코딩 실패: %v", err)
	}

	return results, nil
}

// UpdateStockLevel updates inventory levels with shard awareness
func (sm *ShardedDataManager) UpdateStockLevel(ctx context.Context, regionCode, warehouseID, productID string, quantityChange int) error {
	filter := bson.D{
		{Key: "region_code", Value: regionCode},
		{Key: "warehouse_id", Value: warehouseID},
		{Key: "product_id", Value: productID},
	}

	update := bson.D{
		{Key: "$inc", Value: bson.D{
			{Key: "quantity", Value: quantityChange},
		}},
		{Key: "$set", Value: bson.D{
			{Key: "last_updated", Value: time.Now()},
		}},
	}

	result, err := sm.collection.UpdateOne(ctx, filter, update)
	if err != nil {
		return fmt.Errorf("재고 수준 업데이트 실패: %v", err)
	}

	if result.MatchedCount == 0 {
		return fmt.Errorf("매칭되는 재고 데이터를 찾을 수 없음")
	}

	return nil
}

// BulkUpdateStock performs bulk stock updates across shards
func (sm *ShardedDataManager) BulkUpdateStock(ctx context.Context, updates []LogisticsData) error {
	if len(updates) == 0 {
		return nil
	}

	operations := make([]mongo.WriteModel, len(updates))
	for i, update := range updates {
		filter := bson.D{
			{Key: "region_code", Value: update.RegionCode},
			{Key: "warehouse_id", Value: update.WarehouseID},
			{Key: "product_id", Value: update.ProductID},
		}

		updateDoc := bson.D{
			{Key: "$set", Value: bson.D{
				{Key: "quantity", Value: update.Quantity},
				{Key: "last_updated", Value: time.Now()},
			}},
		}

		operations[i] = mongo.NewUpdateOneModel().
			SetFilter(filter).
			SetUpdate(updateDoc).
			SetUpsert(true)
	}

	_, err := sm.collection.BulkWrite(ctx, operations)
	if err != nil {
		return fmt.Errorf("대량 재고 업데이트 실패: %v", err)
	}

	return nil
}

// Cleanup performs cleanup operations
func (sm *ShardedDataManager) Cleanup(ctx context.Context) error {
	if sm.client != nil {
		if err := sm.client.Disconnect(ctx); err != nil {
			return fmt.Errorf("MongoDB 연결 종료 실패: %v", err)
		}
	}
	return nil
}

// ExampleSharding demonstrates the usage of sharded operations
func ExampleSharding() {
	ctx := context.Background()

	// 샤딩 설정
	shardConfig := &ShardConfiguration{
		ShardKey: bson.D{
			{Key: "region_code", Value: 1},
			{Key: "warehouse_id", Value: 1},
		},
		NumberOfShards: 3,
		ChunkSize:      64,
	}

	// 샤드 매니저 초기화
	manager, err := NewShardedDataManager(ctx, shardConfig)
	if err != nil {
		log.Fatalf("샤드 매니저 초기화 실패: %v", err)
	}
	defer manager.Cleanup(ctx)

	// 테스트 데이터 생성
	testData := &LogisticsData{
		RegionCode:  "APAC",
		WarehouseID: "WH001",
		ProductID:   "PROD001",
		Quantity:    1000,
		Status:      "active",
		Metadata: map[string]interface{}{
			"location": "Seoul",
			"type":     "Electronics",
		},
	}

	// 데이터 삽입 테스트
	if err := manager.InsertLogisticsData(ctx, testData); err != nil {
		log.Printf("데이터 삽입 실패: %v", err)
	} else {
		log.Println("데이터 삽입 성공")
	}

	// 지역별 쿼리 테스트
	results, err := manager.QueryByRegion(ctx, "APAC")
	if err != nil {
		log.Printf("지역별 쿼리 실패: %v", err)
	} else {
		log.Printf("APAC 지역 데이터 수: %d", len(results))
	}

	// 창고별 집계 테스트
	aggregateResults, err := manager.AggregateByWarehouse(ctx)
	if err != nil {
		log.Printf("창고별 집계 실패: %v", err)
	} else {
		log.Printf("창고별 집계 결과: %+v", aggregateResults)
	}

	// 재고 수준 업데이트 테스트
	err = manager.UpdateStockLevel(ctx, "APAC", "WH001", "PROD001", -100)
	if err != nil {
		log.Printf("재고 수준 업데이트 실패: %v", err)
	} else {
		log.Println("재고 수준 업데이트 성공")
	}

	// 대량 업데이트 테스트
	bulkUpdates := []LogisticsData{
		{
			RegionCode:  "APAC",
			WarehouseID: "WH002",
			ProductID:   "PROD002",
			Quantity:    500,
		},
		{
			RegionCode:  "EMEA",
			WarehouseID: "WH003",
			ProductID:   "PROD003",
			Quantity:    750,
		},
	}

	err = manager.BulkUpdateStock(ctx, bulkUpdates)
	if err != nil {
		log.Printf("대량 재고 업데이트 실패: %v", err)
	} else {
		log.Println("대량 재고 업데이트 성공")
	}
}
