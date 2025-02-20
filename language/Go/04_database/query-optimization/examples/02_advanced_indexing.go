package main

import (
	"context"
	"database/sql"
	"fmt"
	"log"
	"strings"
	"time"

	_ "github.com/lib/pq"
)

// IndexDBConfig holds database configuration for indexing examples
type IndexDBConfig struct {
	Host     string
	Port     int
	User     string
	Password string
	DBName   string
}

// IndexAnalyzer manages database connections and provides index analysis tools
type IndexAnalyzer struct {
	db  *sql.DB
	ctx context.Context
}

// CustomerOrder represents a customer order with various attributes for indexing
type CustomerOrder struct {
	ID            int64
	CustomerID    int64
	OrderDate     time.Time
	TotalAmount   float64
	Status        string
	Region        string
	LastUpdated   time.Time
	PaymentMethod string
}

// NewIndexAnalyzer creates a new instance of IndexAnalyzer
func NewIndexAnalyzer(config IndexDBConfig) (*IndexAnalyzer, error) {
	connStr := fmt.Sprintf(
		"host=%s port=%d user=%s password=%s dbname=%s sslmode=disable",
		config.Host, config.Port, config.User, config.Password, config.DBName,
	)

	db, err := sql.Open("postgres", connStr)
	if err != nil {
		return nil, fmt.Errorf("failed to connect to database: %v", err)
	}

	// Verify connection
	if err = db.Ping(); err != nil {
		return nil, fmt.Errorf("failed to ping database: %v", err)
	}

	return &IndexAnalyzer{
		db:  db,
		ctx: context.Background(),
	}, nil
}

// InitializeSchema creates tables with various types of indexes
func (ia *IndexAnalyzer) InitializeSchema() error {
	// Create orders table with different types of indexes
	createTableQuery := `
		CREATE TABLE IF NOT EXISTS customer_orders (
			id BIGSERIAL PRIMARY KEY,
			customer_id BIGINT NOT NULL,
			order_date TIMESTAMP WITH TIME ZONE NOT NULL,
			total_amount DECIMAL(10,2) NOT NULL,
			status VARCHAR(50) NOT NULL,
			region VARCHAR(100) NOT NULL,
			last_updated TIMESTAMP WITH TIME ZONE NOT NULL,
			payment_method VARCHAR(50) NOT NULL
		);

		-- B-tree index for exact matches and range queries
		CREATE INDEX IF NOT EXISTS idx_orders_customer_id ON customer_orders(customer_id);

		-- Composite index for multi-column queries
		CREATE INDEX IF NOT EXISTS idx_orders_region_date ON customer_orders(region, order_date);

		-- Partial index for specific conditions
		CREATE INDEX IF NOT EXISTS idx_orders_pending ON customer_orders(order_date)
		WHERE status = 'pending';

		-- Expression index for function-based queries
		CREATE INDEX IF NOT EXISTS idx_orders_date_trunc ON customer_orders(DATE_TRUNC('month', order_date));

		-- Covering index including frequently accessed columns
		CREATE INDEX IF NOT EXISTS idx_orders_status_covering ON customer_orders(status)
		INCLUDE (total_amount, payment_method);
	`

	_, err := ia.db.ExecContext(ia.ctx, createTableQuery)
	if err != nil {
		return fmt.Errorf("failed to create schema: %v", err)
	}

	return nil
}

// AnalyzeIndexUsage examines index usage statistics
func (ia *IndexAnalyzer) AnalyzeIndexUsage() error {
	query := `
		SELECT
			schemaname || '.' || tablename as table_name,
			indexname,
			idx_scan as number_of_scans,
			idx_tup_read as tuples_read,
			idx_tup_fetch as tuples_fetched
		FROM
			pg_stat_user_indexes
		WHERE
			schemaname = 'public'
		ORDER BY
			number_of_scans DESC;
	`

	rows, err := ia.db.QueryContext(ia.ctx, query)
	if err != nil {
		return fmt.Errorf("failed to analyze index usage: %v", err)
	}
	defer rows.Close()

	fmt.Println("\nIndex Usage Statistics:")
	fmt.Printf("%-30s %-30s %-15s %-15s %-15s\n",
		"Table", "Index", "Scans", "Tuples Read", "Tuples Fetched")
	fmt.Println(strings.Repeat("-", 105))

	for rows.Next() {
		var tableName, indexName string
		var scans, tuplesRead, tuplesFetched int64
		err := rows.Scan(&tableName, &indexName, &scans, &tuplesRead, &tuplesFetched)
		if err != nil {
			return fmt.Errorf("failed to scan row: %v", err)
		}

		fmt.Printf("%-30s %-30s %-15d %-15d %-15d\n",
			tableName, indexName, scans, tuplesRead, tuplesFetched)
	}

	return nil
}

// DemonstrateIndexEffectiveness shows query performance with different indexes
func (ia *IndexAnalyzer) DemonstrateIndexEffectiveness() error {
	queries := []struct {
		name  string
		query string
		args  []interface{}
	}{
		{
			name: "Simple B-tree Index",
			query: `
				EXPLAIN ANALYZE
				SELECT * FROM customer_orders
				WHERE customer_id = $1
			`,
			args: []interface{}{1},
		},
		{
			name: "Composite Index",
			query: `
				EXPLAIN ANALYZE
				SELECT * FROM customer_orders
				WHERE region = $1 AND order_date > $2
			`,
			args: []interface{}{"North", time.Now().AddDate(0, -1, 0)},
		},
		{
			name: "Partial Index",
			query: `
				EXPLAIN ANALYZE
				SELECT * FROM customer_orders
				WHERE status = 'pending' AND order_date > $1
			`,
			args: []interface{}{time.Now().AddDate(0, -1, 0)},
		},
		{
			name: "Expression Index",
			query: `
				EXPLAIN ANALYZE
				SELECT * FROM customer_orders
				WHERE DATE_TRUNC('month', order_date) = DATE_TRUNC('month', $1)
			`,
			args: []interface{}{time.Now()},
		},
	}

	for _, q := range queries {
		fmt.Printf("\nAnalyzing: %s\n", q.name)
		fmt.Println(strings.Repeat("-", 80))

		rows, err := ia.db.QueryContext(ia.ctx, q.query, q.args...)
		if err != nil {
			return fmt.Errorf("failed to execute query %s: %v", q.name, err)
		}

		for rows.Next() {
			var planLine string
			if err := rows.Scan(&planLine); err != nil {
				return fmt.Errorf("failed to scan plan line: %v", err)
			}
			fmt.Println(planLine)
		}
		rows.Close()
	}

	return nil
}

// IdentifyMissingIndexes analyzes queries that might benefit from indexes
func (ia *IndexAnalyzer) IdentifyMissingIndexes() error {
	query := `
		SELECT 
			schemaname || '.' || relname as table_name,
			seq_scan,
			seq_tup_read,
			idx_scan,
			n_live_tup
		FROM 
			pg_stat_user_tables
		WHERE 
			seq_scan > 0
		ORDER BY 
			seq_tup_read DESC;
	`

	rows, err := ia.db.QueryContext(ia.ctx, query)
	if err != nil {
		return fmt.Errorf("failed to identify missing indexes: %v", err)
	}
	defer rows.Close()

	fmt.Println("\nPotential Missing Indexes:")
	fmt.Printf("%-30s %-15s %-15s %-15s %-15s\n",
		"Table", "Seq Scans", "Rows Read", "Idx Scans", "Live Rows")
	fmt.Println(strings.Repeat("-", 90))

	for rows.Next() {
		var tableName string
		var seqScan, seqTupRead, idxScan, liveTup int64
		err := rows.Scan(&tableName, &seqScan, &seqTupRead, &idxScan, &liveTup)
		if err != nil {
			return fmt.Errorf("failed to scan row: %v", err)
		}

		fmt.Printf("%-30s %-15d %-15d %-15d %-15d\n",
			tableName, seqScan, seqTupRead, idxScan, liveTup)
	}

	return nil
}

// CleanupIndexes removes unused or redundant indexes
func (ia *IndexAnalyzer) CleanupIndexes() error {
	query := `
		SELECT
			schemaname || '.' || tablename as table_name,
			indexname,
			idx_scan,
			pg_size_pretty(pg_relation_size(indexrelid)) as index_size
		FROM
			pg_stat_user_indexes
		WHERE
			idx_scan = 0
			AND indexrelid NOT IN (
				SELECT conindid
				FROM pg_constraint
			);
	`

	rows, err := ia.db.QueryContext(ia.ctx, query)
	if err != nil {
		return fmt.Errorf("failed to identify unused indexes: %v", err)
	}
	defer rows.Close()

	fmt.Println("\nUnused Indexes:")
	fmt.Printf("%-30s %-30s %-15s %-15s\n",
		"Table", "Index", "Scans", "Size")
	fmt.Println(strings.Repeat("-", 90))

	for rows.Next() {
		var tableName, indexName, indexSize string
		var scans int64
		err := rows.Scan(&tableName, &indexName, &scans, &indexSize)
		if err != nil {
			return fmt.Errorf("failed to scan row: %v", err)
		}

		fmt.Printf("%-30s %-30s %-15d %-15s\n",
			tableName, indexName, scans, indexSize)
	}

	return nil
}

func advanced_indexing() {
	// Initialize configuration
	config := IndexDBConfig{
		Host:     "localhost",
		Port:     5432,
		User:     "postgres",
		Password: "your_password",
		DBName:   "testdb",
	}

	// Create index analyzer
	analyzer, err := NewIndexAnalyzer(config)
	if err != nil {
		log.Fatalf("Failed to create index analyzer: %v", err)
	}
	defer analyzer.db.Close()

	// Initialize schema with various indexes
	if err := analyzer.InitializeSchema(); err != nil {
		log.Fatalf("Failed to initialize schema: %v", err)
	}

	// Demonstrate index effectiveness
	if err := analyzer.DemonstrateIndexEffectiveness(); err != nil {
		log.Printf("Failed to demonstrate index effectiveness: %v", err)
	}

	// Analyze index usage
	if err := analyzer.AnalyzeIndexUsage(); err != nil {
		log.Printf("Failed to analyze index usage: %v", err)
	}

	// Identify potentially missing indexes
	if err := analyzer.IdentifyMissingIndexes(); err != nil {
		log.Printf("Failed to identify missing indexes: %v", err)
	}

	// Find unused indexes
	if err := analyzer.CleanupIndexes(); err != nil {
		log.Printf("Failed to analyze unused indexes: %v", err)
	}
}
