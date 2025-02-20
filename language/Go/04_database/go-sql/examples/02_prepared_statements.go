package examples

import (
	"context"
	"database/sql"
	"fmt"
	"log"
	"sync"
	"time"

	_ "github.com/lib/pq"
)

// PreparedStmtManager는 prepared statement를 관리하고 재사용하는 매니저입니다.
type PreparedStmtManager struct {
	db        *sql.DB
	stmtCache map[string]*sql.Stmt
	mu        sync.RWMutex
	metrics   *StmtMetrics
}

// StmtMetrics는 prepared statement의 사용 통계를 추적합니다.
type StmtMetrics struct {
	execCount     int64         // 실행 횟수
	totalExecTime time.Duration // 총 실행 시간
	cacheHits     int64         // 캐시 히트 수
	cacheMisses   int64         // 캐시 미스 수
}

// ProductData는 제품 정보를 저장하는 구조체입니다.
type ProductData struct {
	ID          int
	Name        string
	Price       float64
	StockLevel  int
	LastUpdated time.Time
}

// NewPreparedStmtManager는 새로운 PreparedStmtManager를 생성합니다.
func NewPreparedStmtManager(connStr string) (*PreparedStmtManager, error) {
	db, err := sql.Open("postgres", connStr)
	if err != nil {
		return nil, fmt.Errorf("데이터베이스 연결 실패: %v", err)
	}

	return &PreparedStmtManager{
		db:        db,
		stmtCache: make(map[string]*sql.Stmt),
		metrics:   &StmtMetrics{},
	}, nil
}

// prepareStmt는 SQL 쿼리에 대한 prepared statement를 생성하거나 캐시에서 가져옵니다.
func (psm *PreparedStmtManager) prepareStmt(ctx context.Context, query string) (*sql.Stmt, error) {
	psm.mu.RLock()
	stmt, exists := psm.stmtCache[query]
	psm.mu.RUnlock()

	if exists {
		psm.metrics.cacheHits++
		return stmt, nil
	}

	psm.metrics.cacheMisses++
	psm.mu.Lock()
	defer psm.mu.Unlock()

	// Double-check locking pattern
	if stmt, exists = psm.stmtCache[query]; exists {
		psm.metrics.cacheHits++
		return stmt, nil
	}

	// Prepared statement 생성
	stmt, err := psm.db.PrepareContext(ctx, query)
	if err != nil {
		return nil, fmt.Errorf("prepared statement 생성 실패: %v", err)
	}

	psm.stmtCache[query] = stmt
	return stmt, nil
}

// InitializeProductTable은 제품 테이블을 생성합니다.
func (psm *PreparedStmtManager) InitializeProductTable(ctx context.Context) error {
	query := `
		CREATE TABLE IF NOT EXISTS products (
			id SERIAL PRIMARY KEY,
			name VARCHAR(100) NOT NULL,
			price DECIMAL(10,2) NOT NULL,
			stock_level INTEGER NOT NULL,
			last_updated TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
		)
	`
	_, err := psm.db.ExecContext(ctx, query)
	if err != nil {
		return fmt.Errorf("테이블 생성 실패: %v", err)
	}
	return nil
}

// InsertProduct는 prepared statement를 사용하여 단일 제품을 삽입합니다.
func (psm *PreparedStmtManager) InsertProduct(ctx context.Context, product *ProductData) error {
	query := `
		INSERT INTO products (name, price, stock_level)
		VALUES ($1, $2, $3)
		RETURNING id
	`

	start := time.Now()
	defer func() {
		psm.metrics.execCount++
		psm.metrics.totalExecTime += time.Since(start)
	}()

	stmt, err := psm.prepareStmt(ctx, query)
	if err != nil {
		return err
	}

	var id int
	err = stmt.QueryRowContext(ctx, product.Name, product.Price, product.StockLevel).Scan(&id)
	if err != nil {
		return fmt.Errorf("제품 삽입 실패: %v", err)
	}

	product.ID = id
	return nil
}

// BatchInsertProducts는 여러 제품을 효율적으로 삽입합니다.
func (psm *PreparedStmtManager) BatchInsertProducts(ctx context.Context, products []*ProductData) error {
	query := `
		INSERT INTO products (name, price, stock_level)
		VALUES ($1, $2, $3)
	`

	start := time.Now()
	defer func() {
		psm.metrics.execCount += int64(len(products))
		psm.metrics.totalExecTime += time.Since(start)
	}()

	stmt, err := psm.prepareStmt(ctx, query)
	if err != nil {
		return err
	}

	// 트랜잭션 시작
	tx, err := psm.db.BeginTx(ctx, nil)
	if err != nil {
		return fmt.Errorf("트랜잭션 시작 실패: %v", err)
	}
	defer tx.Rollback()

	// 트랜잭션 내에서 prepared statement 사용
	for _, product := range products {
		_, err := tx.StmtContext(ctx, stmt).ExecContext(ctx,
			product.Name,
			product.Price,
			product.StockLevel,
		)
		if err != nil {
			return fmt.Errorf("배치 삽입 실패: %v", err)
		}
	}

	if err := tx.Commit(); err != nil {
		return fmt.Errorf("트랜잭션 커밋 실패: %v", err)
	}

	return nil
}

// UpdateProductStock은 제품의 재고 수준을 업데이트합니다.
func (psm *PreparedStmtManager) UpdateProductStock(ctx context.Context, id int, newStock int) error {
	query := `
		UPDATE products 
		SET stock_level = $1, last_updated = CURRENT_TIMESTAMP
		WHERE id = $2
	`

	start := time.Now()
	defer func() {
		psm.metrics.execCount++
		psm.metrics.totalExecTime += time.Since(start)
	}()

	stmt, err := psm.prepareStmt(ctx, query)
	if err != nil {
		return err
	}

	result, err := stmt.ExecContext(ctx, newStock, id)
	if err != nil {
		return fmt.Errorf("재고 업데이트 실패: %v", err)
	}

	rows, err := result.RowsAffected()
	if err != nil {
		return fmt.Errorf("영향받은 행 확인 실패: %v", err)
	}
	if rows == 0 {
		return fmt.Errorf("제품 ID %d를 찾을 수 없습니다", id)
	}

	return nil
}

// GetProductByID는 ID로 제품을 조회합니다.
func (psm *PreparedStmtManager) GetProductByID(ctx context.Context, id int) (*ProductData, error) {
	query := `
		SELECT id, name, price, stock_level, last_updated
		FROM products
		WHERE id = $1
	`

	start := time.Now()
	defer func() {
		psm.metrics.execCount++
		psm.metrics.totalExecTime += time.Since(start)
	}()

	stmt, err := psm.prepareStmt(ctx, query)
	if err != nil {
		return nil, err
	}

	product := &ProductData{}
	err = stmt.QueryRowContext(ctx, id).Scan(
		&product.ID,
		&product.Name,
		&product.Price,
		&product.StockLevel,
		&product.LastUpdated,
	)
	if err == sql.ErrNoRows {
		return nil, fmt.Errorf("제품 ID %d를 찾을 수 없습니다", id)
	}
	if err != nil {
		return nil, fmt.Errorf("제품 조회 실패: %v", err)
	}

	return product, nil
}

// GetMetrics는 현재 메트릭스를 반환합니다.
func (psm *PreparedStmtManager) GetMetrics() *StmtMetrics {
	return psm.metrics
}

// Close는 모든 prepared statement와 데이터베이스 연결을 정리합니다.
func (psm *PreparedStmtManager) Close() error {
	psm.mu.Lock()
	defer psm.mu.Unlock()

	for _, stmt := range psm.stmtCache {
		if err := stmt.Close(); err != nil {
			log.Printf("prepared statement 정리 중 에러: %v", err)
		}
	}

	return psm.db.Close()
}

// RunPreparedStatementsDemo는 prepared statements 예제를 실행합니다.
func RunPreparedStatementsDemo() {
	ctx, cancel := context.WithTimeout(context.Background(), 30*time.Second)
	defer cancel()

	connStr := "host=localhost port=5432 user=postgres password=postgres dbname=testdb sslmode=disable"
	psm, err := NewPreparedStmtManager(connStr)
	if err != nil {
		log.Fatalf("PreparedStmtManager 초기화 실패: %v", err)
	}
	defer psm.Close()

	// 테이블 초기화
	if err := psm.InitializeProductTable(ctx); err != nil {
		log.Fatalf("테이블 초기화 실패: %v", err)
	}

	// 단일 제품 삽입
	product := &ProductData{
		Name:       "Test Product",
		Price:      99.99,
		StockLevel: 100,
	}
	if err := psm.InsertProduct(ctx, product); err != nil {
		log.Printf("제품 삽입 실패: %v", err)
	}

	// 배치 삽입
	batchProducts := []*ProductData{
		{Name: "Product A", Price: 10.99, StockLevel: 50},
		{Name: "Product B", Price: 20.99, StockLevel: 30},
		{Name: "Product C", Price: 30.99, StockLevel: 20},
	}
	if err := psm.BatchInsertProducts(ctx, batchProducts); err != nil {
		log.Printf("배치 삽입 실패: %v", err)
	}

	// 제품 조회
	if product, err := psm.GetProductByID(ctx, 1); err != nil {
		log.Printf("제품 조회 실패: %v", err)
	} else {
		log.Printf("조회된 제품: ID=%d, Name=%s, Price=%.2f, Stock=%d",
			product.ID, product.Name, product.Price, product.StockLevel)
	}

	// 재고 업데이트
	if err := psm.UpdateProductStock(ctx, 1, 90); err != nil {
		log.Printf("재고 업데이트 실패: %v", err)
	}

	// 메트릭스 출력
	metrics := psm.GetMetrics()
	log.Printf("Prepared Statement 메트릭스:\n"+
		"실행 횟수: %d\n"+
		"총 실행 시간: %v\n"+
		"캐시 히트: %d\n"+
		"캐시 미스: %d\n",
		metrics.execCount,
		metrics.totalExecTime,
		metrics.cacheHits,
		metrics.cacheMisses)
}
