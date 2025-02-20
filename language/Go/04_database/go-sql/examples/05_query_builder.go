package examples

import (
	"context"
	"database/sql"
	"fmt"
	"log"
	"strings"
	"sync"
	"time"

	_ "github.com/lib/pq"
)

// QueryBuilder는 동적 SQL 쿼리 생성을 관리하는 구조체입니다.
type QueryBuilder struct {
	db      *sql.DB
	metrics *QueryMetrics
	mu      sync.RWMutex
}

// QueryMetrics는 쿼리 실행에 관한 메트릭을 추적합니다.
type QueryMetrics struct {
	TotalQueries      int64
	SuccessfulQueries int64
	FailedQueries     int64
	TotalDuration     time.Duration
	AverageQueryTime  time.Duration
}

// SearchParams는 제품 검색을 위한 매개변수를 정의합니다.
type SearchParams struct {
	Category string
	MinPrice *float64
	MaxPrice *float64
	InStock  *bool
	OrderBy  string
	OrderDir string
	Limit    int
	Offset   int
}

// ProductInfo는 제품 정보를 저장하는 구조체입니다.
type ProductInfo struct {
	ID          int
	Name        string
	Category    string
	Price       float64
	StockLevel  int
	IsAvailable bool
	CreatedAt   time.Time
}

// NewQueryBuilder는 새로운 QueryBuilder 인스턴스를 생성합니다.
func NewQueryBuilder(connStr string) (*QueryBuilder, error) {
	db, err := sql.Open("postgres", connStr)
	if err != nil {
		return nil, fmt.Errorf("데이터베이스 연결 실패: %v", err)
	}

	return &QueryBuilder{
		db:      db,
		metrics: &QueryMetrics{},
	}, nil
}

// InitializeProductSchema는 제품 테이블을 생성합니다.
func (qb *QueryBuilder) InitializeProductSchema(ctx context.Context) error {
	query := `
		CREATE TABLE IF NOT EXISTS products (
			id SERIAL PRIMARY KEY,
			name VARCHAR(100) NOT NULL,
			category VARCHAR(50) NOT NULL,
			price DECIMAL(10,2) NOT NULL,
			stock_level INTEGER NOT NULL DEFAULT 0,
			is_available BOOLEAN NOT NULL DEFAULT true,
			created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
		)
	`
	_, err := qb.db.ExecContext(ctx, query)
	if err != nil {
		return fmt.Errorf("테이블 생성 실패: %v", err)
	}
	return nil
}

// buildSearchQuery는 검색 매개변수를 기반으로 동적 쿼리를 생성합니다.
func (qb *QueryBuilder) buildSearchQuery(params SearchParams) (string, []interface{}, error) {
	var conditions []string
	var args []interface{}
	argPosition := 1

	// 기본 쿼리 구조
	queryBuilder := strings.Builder{}
	queryBuilder.WriteString("SELECT id, name, category, price, stock_level, is_available, created_at FROM products WHERE 1=1")

	// 카테고리 필터
	if params.Category != "" {
		conditions = append(conditions, fmt.Sprintf(" AND category = $%d", argPosition))
		args = append(args, params.Category)
		argPosition++
	}

	// 가격 범위 필터
	if params.MinPrice != nil {
		conditions = append(conditions, fmt.Sprintf(" AND price >= $%d", argPosition))
		args = append(args, *params.MinPrice)
		argPosition++
	}
	if params.MaxPrice != nil {
		conditions = append(conditions, fmt.Sprintf(" AND price <= $%d", argPosition))
		args = append(args, *params.MaxPrice)
		argPosition++
	}

	// 재고 상태 필터
	if params.InStock != nil {
		if *params.InStock {
			conditions = append(conditions, " AND stock_level > 0")
		} else {
			conditions = append(conditions, " AND stock_level = 0")
		}
	}

	// 조건절 추가
	queryBuilder.WriteString(strings.Join(conditions, ""))

	// 정렬 추가
	if params.OrderBy != "" {
		// SQL 인젝션 방지를 위한 허용된 정렬 필드 검증
		allowedFields := map[string]bool{
			"price": true, "created_at": true, "name": true,
		}
		if !allowedFields[params.OrderBy] {
			return "", nil, fmt.Errorf("잘못된 정렬 필드: %s", params.OrderBy)
		}

		// 정렬 방향 검증
		orderDir := strings.ToUpper(params.OrderDir)
		if orderDir != "ASC" && orderDir != "DESC" {
			orderDir = "ASC"
		}

		queryBuilder.WriteString(fmt.Sprintf(" ORDER BY %s %s", params.OrderBy, orderDir))
	}

	// 페이지네이션 추가
	if params.Limit > 0 {
		queryBuilder.WriteString(fmt.Sprintf(" LIMIT $%d", argPosition))
		args = append(args, params.Limit)
		argPosition++

		if params.Offset > 0 {
			queryBuilder.WriteString(fmt.Sprintf(" OFFSET $%d", argPosition))
			args = append(args, params.Offset)
		}
	}

	return queryBuilder.String(), args, nil
}

// SearchProducts는 주어진 매개변수로 제품을 검색합니다.
func (qb *QueryBuilder) SearchProducts(ctx context.Context, params SearchParams) ([]ProductInfo, error) {
	startTime := time.Now()
	defer func() {
		duration := time.Since(startTime)
		qb.mu.Lock()
		qb.metrics.TotalQueries++
		qb.metrics.TotalDuration += duration
		qb.metrics.AverageQueryTime = time.Duration(
			int64(qb.metrics.TotalDuration) / qb.metrics.TotalQueries,
		)
		qb.mu.Unlock()
	}()

	// 동적 쿼리 생성
	query, args, err := qb.buildSearchQuery(params)
	if err != nil {
		qb.mu.Lock()
		qb.metrics.FailedQueries++
		qb.mu.Unlock()
		return nil, fmt.Errorf("쿼리 생성 실패: %v", err)
	}

	// 쿼리 실행
	rows, err := qb.db.QueryContext(ctx, query, args...)
	if err != nil {
		qb.mu.Lock()
		qb.metrics.FailedQueries++
		qb.mu.Unlock()
		return nil, fmt.Errorf("쿼리 실행 실패: %v", err)
	}
	defer rows.Close()

	// 결과 처리
	var products []ProductInfo
	for rows.Next() {
		var product ProductInfo
		err := rows.Scan(
			&product.ID,
			&product.Name,
			&product.Category,
			&product.Price,
			&product.StockLevel,
			&product.IsAvailable,
			&product.CreatedAt,
		)
		if err != nil {
			return nil, fmt.Errorf("결과 스캔 실패: %v", err)
		}
		products = append(products, product)
	}

	if err = rows.Err(); err != nil {
		qb.mu.Lock()
		qb.metrics.FailedQueries++
		qb.mu.Unlock()
		return nil, fmt.Errorf("결과 처리 중 에러: %v", err)
	}

	qb.mu.Lock()
	qb.metrics.SuccessfulQueries++
	qb.mu.Unlock()

	return products, nil
}

// InsertSampleProducts는 테스트를 위한 샘플 제품을 삽입합니다.
func (qb *QueryBuilder) InsertSampleProducts(ctx context.Context) error {
	sampleProducts := []struct {
		name     string
		category string
		price    float64
		stock    int
	}{
		{"Laptop Pro", "Electronics", 1299.99, 50},
		{"Wireless Mouse", "Electronics", 29.99, 100},
		{"Coffee Maker", "Appliances", 79.99, 30},
		{"Running Shoes", "Sports", 89.99, 75},
		{"Yoga Mat", "Sports", 19.99, 120},
	}

	query := `
		INSERT INTO products (name, category, price, stock_level)
		VALUES ($1, $2, $3, $4)
	`

	for _, product := range sampleProducts {
		_, err := qb.db.ExecContext(ctx, query,
			product.name,
			product.category,
			product.price,
			product.stock,
		)
		if err != nil {
			return fmt.Errorf("샘플 제품 삽입 실패: %v", err)
		}
	}

	return nil
}

// GetMetrics는 현재 쿼리 메트릭을 반환합니다.
func (qb *QueryBuilder) GetMetrics() QueryMetrics {
	qb.mu.RLock()
	defer qb.mu.RUnlock()
	return *qb.metrics
}

// Close는 데이터베이스 연결을 정리합니다.
func (qb *QueryBuilder) Close() error {
	return qb.db.Close()
}

// RunQueryBuilderDemo는 쿼리 빌더 예제를 실행합니다.
func RunQueryBuilderDemo() {
	ctx := context.Background()
	connStr := "host=localhost port=5432 user=postgres password=postgres dbname=testdb sslmode=disable"

	qb, err := NewQueryBuilder(connStr)
	if err != nil {
		log.Fatalf("QueryBuilder 초기화 실패: %v", err)
	}
	defer qb.Close()

	// 스키마 초기화 및 샘플 데이터 삽입
	if err := qb.InitializeProductSchema(ctx); err != nil {
		log.Fatalf("스키마 초기화 실패: %v", err)
	}

	if err := qb.InsertSampleProducts(ctx); err != nil {
		log.Fatalf("샘플 데이터 삽입 실패: %v", err)
	}

	// 다양한 검색 조건으로 테스트
	searchTests := []struct {
		name   string
		params SearchParams
	}{
		{
			name: "Electronics 카테고리 검색",
			params: SearchParams{
				Category: "Electronics",
				OrderBy:  "price",
				OrderDir: "DESC",
			},
		},
		{
			name: "가격 범위로 검색",
			params: SearchParams{
				MinPrice: ptr(50.0),
				MaxPrice: ptr(100.0),
				OrderBy:  "price",
				OrderDir: "ASC",
			},
		},
		{
			name: "재고 있는 제품만 검색",
			params: SearchParams{
				InStock: ptr(true),
				Limit:   3,
			},
		},
	}

	for _, test := range searchTests {
		log.Printf("\n%s 실행:", test.name)
		products, err := qb.SearchProducts(ctx, test.params)
		if err != nil {
			log.Printf("검색 실패: %v", err)
			continue
		}

		log.Printf("검색 결과 (%d개 항목):", len(products))
		for _, p := range products {
			log.Printf("- %s (카테고리: %s, 가격: $%.2f, 재고: %d)",
				p.Name, p.Category, p.Price, p.StockLevel)
		}
	}

	// 메트릭스 출력
	metrics := qb.GetMetrics()
	log.Printf("\n쿼리 빌더 메트릭스:\n"+
		"총 쿼리 수: %d\n"+
		"성공한 쿼리 수: %d\n"+
		"실패한 쿼리 수: %d\n"+
		"총 실행 시간: %v\n"+
		"평균 쿼리 시간: %v",
		metrics.TotalQueries,
		metrics.SuccessfulQueries,
		metrics.FailedQueries,
		metrics.TotalDuration,
		metrics.AverageQueryTime)
}

// ptr는 값의 포인터를 반환하는 유틸리티 함수입니다.
func ptr[T any](v T) *T {
	return &v
}
