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
)

// SalesTransaction은 판매 거래 데이터를 표현합니다.
type SalesTransaction struct {
	ID           primitive.ObjectID `bson:"_id,omitempty"`
	CustomerID   string             `bson:"customer_id"`
	ProductID    string             `bson:"product_id"`
	Amount       float64            `bson:"amount"`
	Quantity     int                `bson:"quantity"`
	Category     string             `bson:"category"`
	Region       string             `bson:"region"`
	TransactedAt time.Time          `bson:"transacted_at"`
}

// SalesAnalytics는 판매 데이터 분석을 위한 기능을 제공합니다.
type SalesAnalytics struct {
	client     *mongo.Client
	collection *mongo.Collection
}

// MonthlySalesResult는 월별 매출 집계 결과를 표현합니다.
type MonthlySalesResult struct {
	Year          int     `bson:"_id.year"`
	Month         int     `bson:"_id.month"`
	TotalSales    float64 `bson:"total_sales"`
	OrderCount    int     `bson:"order_count"`
	AvgOrderValue float64 `bson:"avg_order_value"`
}

// CategoryAnalysis는 카테고리별 분석 결과를 표현합니다.
type CategoryAnalysis struct {
	Category     string  `bson:"_id"`
	TotalSales   float64 `bson:"total_sales"`
	ItemsSold    int     `bson:"items_sold"`
	AvgUnitPrice float64 `bson:"avg_unit_price"`
}

// RegionalPerformance는 지역별 성과 분석 결과를 표현합니다.
type RegionalPerformance struct {
	Region      string  `bson:"_id"`
	Revenue     float64 `bson:"revenue"`
	OrderCount  int     `bson:"order_count"`
	TopCategory string  `bson:"top_category"`
}

// NewSalesAnalytics는 새로운 SalesAnalytics 인스턴스를 생성합니다.
func NewSalesAnalytics(ctx context.Context) (*SalesAnalytics, error) {
	clientOptions := options.Client().ApplyURI("mongodb://localhost:27017")
	client, err := mongo.Connect(ctx, clientOptions)
	if err != nil {
		return nil, fmt.Errorf("MongoDB 연결 실패: %v", err)
	}

	// 연결 확인
	if err = client.Ping(ctx, nil); err != nil {
		return nil, fmt.Errorf("MongoDB 연결 확인 실패: %v", err)
	}

	return &SalesAnalytics{
		client:     client,
		collection: client.Database("sales").Collection("transactions"),
	}, nil
}

// AnalyzeMonthlyTrends는 월별 매출 트렌드를 분석합니다.
func (sa *SalesAnalytics) AnalyzeMonthlyTrends(ctx context.Context, year int) ([]MonthlySalesResult, error) {
	pipeline := mongo.Pipeline{
		bson.D{
			{Key: "$match", Value: bson.D{
				{Key: "transacted_at", Value: bson.D{
					{Key: "$gte", Value: time.Date(year, 1, 1, 0, 0, 0, 0, time.UTC)},
					{Key: "$lt", Value: time.Date(year+1, 1, 1, 0, 0, 0, 0, time.UTC)},
				}},
			}},
		},
		bson.D{
			{Key: "$group", Value: bson.D{
				{Key: "_id", Value: bson.D{
					{Key: "year", Value: bson.D{{Key: "$year", Value: "$transacted_at"}}},
					{Key: "month", Value: bson.D{{Key: "$month", Value: "$transacted_at"}}},
				}},
				{Key: "total_sales", Value: bson.D{{Key: "$sum", Value: "$amount"}}},
				{Key: "order_count", Value: bson.D{{Key: "$sum", Value: 1}}},
				{Key: "avg_order_value", Value: bson.D{{Key: "$avg", Value: "$amount"}}},
			}},
		},
		bson.D{
			{Key: "$sort", Value: bson.D{
				{Key: "_id.year", Value: 1},
				{Key: "_id.month", Value: 1},
			}},
		},
	}

	cursor, err := sa.collection.Aggregate(ctx, pipeline)
	if err != nil {
		return nil, fmt.Errorf("월별 트렌드 분석 실패: %v", err)
	}
	defer cursor.Close(ctx)

	var results []MonthlySalesResult
	if err = cursor.All(ctx, &results); err != nil {
		return nil, fmt.Errorf("결과 디코딩 실패: %v", err)
	}

	return results, nil
}

// AnalyzeCategoryPerformance는 카테고리별 성과를 분석합니다.
func (sa *SalesAnalytics) AnalyzeCategoryPerformance(ctx context.Context) ([]CategoryAnalysis, error) {
	pipeline := mongo.Pipeline{
		bson.D{
			{Key: "$group", Value: bson.D{
				{Key: "_id", Value: "$category"},
				{Key: "total_sales", Value: bson.D{{Key: "$sum", Value: "$amount"}}},
				{Key: "items_sold", Value: bson.D{{Key: "$sum", Value: "$quantity"}}},
				{Key: "avg_unit_price", Value: bson.D{
					{Key: "$avg", Value: bson.D{
						{Key: "$divide", Value: []interface{}{"$amount", "$quantity"}},
					}},
				}},
			}},
		},
		bson.D{
			{Key: "$sort", Value: bson.D{
				{Key: "total_sales", Value: -1},
			}},
		},
	}

	cursor, err := sa.collection.Aggregate(ctx, pipeline)
	if err != nil {
		return nil, fmt.Errorf("카테고리 성과 분석 실패: %v", err)
	}
	defer cursor.Close(ctx)

	var results []CategoryAnalysis
	if err = cursor.All(ctx, &results); err != nil {
		return nil, fmt.Errorf("결과 디코딩 실패: %v", err)
	}

	return results, nil
}

// AnalyzeRegionalPerformance는 지역별 성과를 분석합니다.
func (sa *SalesAnalytics) AnalyzeRegionalPerformance(ctx context.Context) ([]RegionalPerformance, error) {
	pipeline := mongo.Pipeline{
		bson.D{
			{Key: "$group", Value: bson.D{
				{Key: "_id", Value: "$region"},
				{Key: "revenue", Value: bson.D{{Key: "$sum", Value: "$amount"}}},
				{Key: "order_count", Value: bson.D{{Key: "$sum", Value: 1}}},
				{Key: "categories", Value: bson.D{{Key: "$push", Value: "$category"}}},
			}},
		},
		bson.D{
			{Key: "$addFields", Value: bson.D{
				{Key: "top_category", Value: bson.D{
					{Key: "$arrayElemAt", Value: []interface{}{"$categories", 0}},
				}},
			}},
		},
		bson.D{
			{Key: "$project", Value: bson.D{
				{Key: "revenue", Value: 1},
				{Key: "order_count", Value: 1},
				{Key: "top_category", Value: 1},
			}},
		},
		bson.D{
			{Key: "$sort", Value: bson.D{
				{Key: "revenue", Value: -1},
			}},
		},
	}

	cursor, err := sa.collection.Aggregate(ctx, pipeline)
	if err != nil {
		return nil, fmt.Errorf("지역별 성과 분석 실패: %v", err)
	}
	defer cursor.Close(ctx)

	var results []RegionalPerformance
	if err = cursor.All(ctx, &results); err != nil {
		return nil, fmt.Errorf("결과 디코딩 실패: %v", err)
	}

	return results, nil
}

// Cleanup은 SalesAnalytics 인스턴스의 리소스를 정리합니다.
func (sa *SalesAnalytics) Cleanup(ctx context.Context) error {
	if sa.client != nil {
		if err := sa.client.Disconnect(ctx); err != nil {
			return fmt.Errorf("MongoDB 연결 종료 실패: %v", err)
		}
	}
	return nil
}

// ExampleAggregation은 집계 파이프라인 사용 예제를 보여줍니다.
func ExampleAggregation() {
	ctx, cancel := context.WithTimeout(context.Background(), 30*time.Second)
	defer cancel()

	// SalesAnalytics 인스턴스 생성
	analytics, err := NewSalesAnalytics(ctx)
	if err != nil {
		log.Fatalf("SalesAnalytics 초기화 실패: %v", err)
	}
	defer analytics.Cleanup(ctx)

	// 샘플 데이터 생성 및 삽입
	sampleTransactions := []SalesTransaction{
		{
			CustomerID:   "CUST001",
			ProductID:    "PROD001",
			Amount:       299.99,
			Quantity:     2,
			Category:     "Electronics",
			Region:       "East",
			TransactedAt: time.Now().Add(-24 * time.Hour),
		},
		{
			CustomerID:   "CUST002",
			ProductID:    "PROD002",
			Amount:       159.99,
			Quantity:     1,
			Category:     "Books",
			Region:       "West",
			TransactedAt: time.Now(),
		},
		// 필요한 만큼 샘플 데이터 추가
	}

	for _, transaction := range sampleTransactions {
		_, err := analytics.collection.InsertOne(ctx, transaction)
		if err != nil {
			log.Printf("거래 데이터 삽입 실패: %v", err)
		}
	}

	// 월별 트렌드 분석
	currentYear := time.Now().Year()
	monthlyTrends, err := analytics.AnalyzeMonthlyTrends(ctx, currentYear)
	if err != nil {
		log.Printf("월별 트렌드 분석 실패: %v", err)
	} else {
		log.Println("월별 매출 트렌드:")
		for _, trend := range monthlyTrends {
			log.Printf("%d년 %d월: 총 매출 %.2f, 주문 수 %d, 평균 주문액 %.2f",
				trend.Year, trend.Month, trend.TotalSales, trend.OrderCount, trend.AvgOrderValue)
		}
	}

	// 카테고리별 성과 분석
	categoryAnalysis, err := analytics.AnalyzeCategoryPerformance(ctx)
	if err != nil {
		log.Printf("카테고리 성과 분석 실패: %v", err)
	} else {
		log.Println("\n카테고리별 성과:")
		for _, analysis := range categoryAnalysis {
			log.Printf("카테고리: %s, 총 매출: %.2f, 판매 수량: %d, 평균 단가: %.2f",
				analysis.Category, analysis.TotalSales, analysis.ItemsSold, analysis.AvgUnitPrice)
		}
	}

	// 지역별 성과 분석
	regionalPerformance, err := analytics.AnalyzeRegionalPerformance(ctx)
	if err != nil {
		log.Printf("지역별 성과 분석 실패: %v", err)
	} else {
		log.Println("\n지역별 성과:")
		for _, performance := range regionalPerformance {
			log.Printf("지역: %s, 매출: %.2f, 주문 수: %d, 주력 카테고리: %s",
				performance.Region, performance.Revenue, performance.OrderCount, performance.TopCategory)
		}
	}
}
