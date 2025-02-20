package examples

import (
	"context"
	"database/sql"
	"encoding/csv"
	"fmt"
	"io"
	"log"
	"strings"
	"sync"
	"time"

	_ "github.com/lib/pq"
)

// BatchProcessor는 대량 데이터 처리를 관리하는 구조체입니다.
type BatchProcessor struct {
	db          *sql.DB
	batchSize   int
	workerCount int
	metrics     *BatchMetrics
	mu          sync.RWMutex
}

// BatchMetrics는 배치 작업의 성능 지표를 추적합니다.
type BatchMetrics struct {
	TotalRecords     int64
	ProcessedRecords int64
	FailedRecords    int64
	TotalDuration    time.Duration
	BatchCount       int64
	AverageBatchTime time.Duration
}

// CustomerRecord는 고객 데이터를 나타내는 구조체입니다.
type CustomerRecord struct {
	ID        int
	Name      string
	Email     string
	Phone     string
	Address   string
	CreatedAt time.Time
}

// NewBatchProcessor는 새로운 BatchProcessor를 생성합니다.
func NewBatchProcessor(connStr string, batchSize, workerCount int) (*BatchProcessor, error) {
	db, err := sql.Open("postgres", connStr)
	if err != nil {
		return nil, fmt.Errorf("데이터베이스 연결 실패: %v", err)
	}

	// 연결 풀 설정 최적화
	db.SetMaxOpenConns(workerCount * 2)
	db.SetMaxIdleConns(workerCount)
	db.SetConnMaxLifetime(time.Hour)

	return &BatchProcessor{
		db:          db,
		batchSize:   batchSize,
		workerCount: workerCount,
		metrics:     &BatchMetrics{},
	}, nil
}

// InitializeSchema는 필요한 테이블을 생성합니다.
func (bp *BatchProcessor) InitializeSchema(ctx context.Context) error {
	query := `
		CREATE TABLE IF NOT EXISTS customers (
			id SERIAL PRIMARY KEY,
			name VARCHAR(100) NOT NULL,
			email VARCHAR(255) NOT NULL UNIQUE,
			phone VARCHAR(20),
			address TEXT,
			created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
		)
	`
	_, err := bp.db.ExecContext(ctx, query)
	if err != nil {
		return fmt.Errorf("테이블 생성 실패: %v", err)
	}
	return nil
}

// ProcessCSVData는 CSV 데이터를 병렬로 처리합니다.
func (bp *BatchProcessor) ProcessCSVData(ctx context.Context, reader *csv.Reader) error {
	startTime := time.Now()
	defer func() {
		bp.mu.Lock()
		bp.metrics.TotalDuration = time.Since(startTime)
		bp.mu.Unlock()
	}()

	// 작업 채널 생성
	records := make(chan []string, bp.workerCount*2)
	errors := make(chan error, bp.workerCount)
	var wg sync.WaitGroup

	// 워커 고루틴 시작
	for i := 0; i < bp.workerCount; i++ {
		wg.Add(1)
		go bp.batchWorker(ctx, records, errors, &wg)
	}

	// CSV 데이터 읽기 고루틴
	go func() {
		defer close(records)
		for {
			record, err := reader.Read()
			if err == io.EOF {
				break
			}
			if err != nil {
				errors <- fmt.Errorf("CSV 읽기 실패: %v", err)
				return
			}
			select {
			case records <- record:
				bp.mu.Lock()
				bp.metrics.TotalRecords++
				bp.mu.Unlock()
			case <-ctx.Done():
				return
			}
		}
	}()

	// 워커 완료 대기
	wg.Wait()
	close(errors)

	// 에러 수집
	for err := range errors {
		if err != nil {
			return fmt.Errorf("배치 처리 중 에러 발생: %v", err)
		}
	}

	return nil
}

// batchWorker는 개별 워커 고루틴으로 배치 처리를 수행합니다.
func (bp *BatchProcessor) batchWorker(ctx context.Context, records chan []string, errors chan error, wg *sync.WaitGroup) {
	defer wg.Done()

	batch := make([]CustomerRecord, 0, bp.batchSize)
	for record := range records {
		select {
		case <-ctx.Done():
			return
		default:
			customer := CustomerRecord{
				Name:    record[0],
				Email:   record[1],
				Phone:   record[2],
				Address: record[3],
			}
			batch = append(batch, customer)

			if len(batch) >= bp.batchSize {
				if err := bp.insertBatch(ctx, batch); err != nil {
					errors <- err
					return
				}
				batch = batch[:0]
			}
		}
	}

	// 남은 레코드 처리
	if len(batch) > 0 {
		if err := bp.insertBatch(ctx, batch); err != nil {
			errors <- err
		}
	}
}

// insertBatch는 단일 배치를 데이터베이스에 삽입합니다.
func (bp *BatchProcessor) insertBatch(ctx context.Context, batch []CustomerRecord) error {
	if len(batch) == 0 {
		return nil
	}

	startTime := time.Now()
	defer func() {
		duration := time.Since(startTime)
		bp.mu.Lock()
		bp.metrics.BatchCount++
		bp.metrics.AverageBatchTime = time.Duration(
			(int64(bp.metrics.AverageBatchTime)*(bp.metrics.BatchCount-1) +
				int64(duration)) / bp.metrics.BatchCount,
		)
		bp.mu.Unlock()
	}()

	// 벌크 삽입 쿼리 생성
	valueStrings := make([]string, 0, len(batch))
	valueArgs := make([]interface{}, 0, len(batch)*4)
	for i, customer := range batch {
		valueStrings = append(valueStrings, fmt.Sprintf("($%d, $%d, $%d, $%d)",
			i*4+1, i*4+2, i*4+3, i*4+4))
		valueArgs = append(valueArgs,
			customer.Name,
			customer.Email,
			customer.Phone,
			customer.Address)
	}

	stmt := fmt.Sprintf("INSERT INTO customers (name, email, phone, address) VALUES %s",
		strings.Join(valueStrings, ","))

	// 트랜잭션 시작
	tx, err := bp.db.BeginTx(ctx, nil)
	if err != nil {
		return fmt.Errorf("트랜잭션 시작 실패: %v", err)
	}
	defer tx.Rollback()

	// 배치 삽입 실행
	_, err = tx.ExecContext(ctx, stmt, valueArgs...)
	if err != nil {
		bp.mu.Lock()
		bp.metrics.FailedRecords += int64(len(batch))
		bp.mu.Unlock()
		return fmt.Errorf("배치 삽입 실패: %v", err)
	}

	// 트랜잭션 커밋
	if err := tx.Commit(); err != nil {
		return fmt.Errorf("트랜잭션 커밋 실패: %v", err)
	}

	bp.mu.Lock()
	bp.metrics.ProcessedRecords += int64(len(batch))
	bp.mu.Unlock()

	return nil
}

// GetMetrics는 현재 배치 처리 메트릭을 반환합니다.
func (bp *BatchProcessor) GetMetrics() BatchMetrics {
	bp.mu.RLock()
	defer bp.mu.RUnlock()
	return *bp.metrics
}

// Close는 데이터베이스 연결을 정리합니다.
func (bp *BatchProcessor) Close() error {
	return bp.db.Close()
}

// RunBatchOperationsDemo는 배치 처리 예제를 실행합니다.
func RunBatchOperationsDemo() {
	ctx := context.Background()
	connStr := "host=localhost port=5432 user=postgres password=postgres dbname=testdb sslmode=disable"

	// BatchProcessor 초기화
	bp, err := NewBatchProcessor(connStr, 1000, 4)
	if err != nil {
		log.Fatalf("BatchProcessor 초기화 실패: %v", err)
	}
	defer bp.Close()

	// 스키마 초기화
	if err := bp.InitializeSchema(ctx); err != nil {
		log.Fatalf("스키마 초기화 실패: %v", err)
	}

	// CSV 데이터 시뮬레이션
	csvData := `John Doe,john@example.com,123-456-7890,123 Main St
Jane Smith,jane@example.com,098-765-4321,456 Oak Ave
Bob Wilson,bob@example.com,111-222-3333,789 Pine Rd`

	reader := csv.NewReader(strings.NewReader(csvData))

	// 배치 처리 실행
	if err := bp.ProcessCSVData(ctx, reader); err != nil {
		log.Printf("배치 처리 중 에러 발생: %v", err)
	}

	// 메트릭스 출력
	metrics := bp.GetMetrics()
	log.Printf("배치 처리 메트릭스:\n"+
		"총 레코드 수: %d\n"+
		"처리된 레코드 수: %d\n"+
		"실패한 레코드 수: %d\n"+
		"총 실행 시간: %v\n"+
		"배치 수: %d\n"+
		"평균 배치 처리 시간: %v",
		metrics.TotalRecords,
		metrics.ProcessedRecords,
		metrics.FailedRecords,
		metrics.TotalDuration,
		metrics.BatchCount,
		metrics.AverageBatchTime)
}
