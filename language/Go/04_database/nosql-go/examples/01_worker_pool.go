package examples

import (
	"context"
	"fmt"
	"log"
	"sync"
	"time"

	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/bson/primitive"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
)

// Product는 작업할 제품 데이터의 구조를 정의합니다.
type Product struct {
	ID          primitive.ObjectID `bson:"_id,omitempty"`
	Name        string             `bson:"name"`
	Price       float64            `bson:"price"`
	Stock       int                `bson:"stock"`
	LastUpdated time.Time          `bson:"last_updated"`
}

// WorkerPool은 MongoDB 작업을 위한 워커 풀을 관리합니다.
type WorkerPool struct {
	client      *mongo.Client
	numWorkers  int
	jobsChan    chan Product
	resultsChan chan error
	collection  *mongo.Collection
	wg          sync.WaitGroup
}

// NewWorkerPool은 새로운 워커 풀을 생성합니다.
func NewWorkerPool(ctx context.Context, numWorkers int) (*WorkerPool, error) {
	// MongoDB 클라이언트 초기화
	clientOptions := options.Client().ApplyURI("mongodb://localhost:27017")
	client, err := mongo.Connect(ctx, clientOptions)
	if err != nil {
		return nil, fmt.Errorf("MongoDB 연결 실패: %v", err)
	}

	// 연결 확인
	err = client.Ping(ctx, nil)
	if err != nil {
		return nil, fmt.Errorf("MongoDB 연결 확인 실패: %v", err)
	}

	pool := &WorkerPool{
		client:      client,
		numWorkers:  numWorkers,
		jobsChan:    make(chan Product, numWorkers*2), // 버퍼 크기는 워커 수의 2배
		resultsChan: make(chan error, numWorkers),
		collection:  client.Database("inventory").Collection("products"),
	}

	return pool, nil
}

// StartWorkers는 지정된 수의 워커를 시작합니다.
func (wp *WorkerPool) StartWorkers(ctx context.Context) {
	for i := 0; i < wp.numWorkers; i++ {
		wp.wg.Add(1)
		workerID := i + 1
		go wp.worker(ctx, workerID)
	}
}

// worker는 개별 워커의 작업을 처리합니다.
func (wp *WorkerPool) worker(ctx context.Context, id int) {
	defer wp.wg.Done()
	log.Printf("Worker %d 시작", id)

	for product := range wp.jobsChan {
		// 제품 재고 업데이트 및 마지막 업데이트 시간 기록
		filter := bson.M{"_id": product.ID}
		update := bson.M{
			"$set": bson.M{
				"stock":        product.Stock,
				"last_updated": time.Now(),
			},
		}

		// 업데이트 작업 수행
		_, err := wp.collection.UpdateOne(ctx, filter, update)
		if err != nil {
			wp.resultsChan <- fmt.Errorf("Worker %d - 제품 업데이트 실패 (ID: %s): %v",
				id, product.ID.Hex(), err)
			continue
		}

		log.Printf("Worker %d - 제품 업데이트 완료 (ID: %s)", id, product.ID.Hex())
		wp.resultsChan <- nil
	}

	log.Printf("Worker %d 종료", id)
}

// ProcessProducts는 제품 목록을 워커 풀을 통해 처리합니다.
func (wp *WorkerPool) ProcessProducts(ctx context.Context, products []Product) error {
	// 결과 수집을 위한 고루틴
	resultsDone := make(chan bool)
	var processingError error
	go func() {
		for i := 0; i < len(products); i++ {
			if err := <-wp.resultsChan; err != nil {
				processingError = err
			}
		}
		resultsDone <- true
	}()

	// 작업 분배
	for _, product := range products {
		select {
		case <-ctx.Done():
			return ctx.Err()
		case wp.jobsChan <- product:
			// 작업이 성공적으로 큐에 추가됨
		}
	}

	// 모든 작업이 완료될 때까지 대기
	close(wp.jobsChan)
	wp.wg.Wait()
	<-resultsDone

	return processingError
}

// Cleanup은 워커 풀의 리소스를 정리합니다.
func (wp *WorkerPool) Cleanup(ctx context.Context) error {
	if wp.client != nil {
		if err := wp.client.Disconnect(ctx); err != nil {
			return fmt.Errorf("MongoDB 연결 종료 실패: %v", err)
		}
	}
	close(wp.resultsChan)
	return nil
}

// ExampleWorkerPool은 워커 풀 사용 예제를 보여줍니다.
func ExampleWorkerPool() {
	ctx, cancel := context.WithTimeout(context.Background(), 30*time.Second)
	defer cancel()

	// 5개의 워커로 구성된 풀 생성
	pool, err := NewWorkerPool(ctx, 5)
	if err != nil {
		log.Fatalf("워커 풀 생성 실패: %v", err)
	}
	defer pool.Cleanup(ctx)

	// 워커 시작
	pool.StartWorkers(ctx)

	// 테스트용 제품 데이터 생성
	products := []Product{
		{
			ID:    primitive.NewObjectID(),
			Name:  "Laptop",
			Price: 1299.99,
			Stock: 50,
		},
		{
			ID:    primitive.NewObjectID(),
			Name:  "Smartphone",
			Price: 699.99,
			Stock: 100,
		},
		// 필요한 만큼 제품 추가
	}

	// 초기 제품 데이터 삽입
	for _, product := range products {
		_, err := pool.collection.InsertOne(ctx, product)
		if err != nil {
			log.Printf("제품 삽입 실패: %v", err)
		}
	}

	// 워커 풀을 통한 제품 처리
	if err := pool.ProcessProducts(ctx, products); err != nil {
		log.Printf("제품 처리 중 오류 발생: %v", err)
	}

	log.Println("모든 제품 처리 완료")
}
