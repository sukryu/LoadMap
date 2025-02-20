package main

import (
	"context"
	"database/sql"
	"encoding/json"
	"fmt"
	"log"
	"regexp"
	"strings"
	"time"

	_ "github.com/lib/pq"
)

// ProfilerConfig contains configuration for the query profiler
type ProfilerConfig struct {
	Host               string
	Port               int
	User               string
	Password           string
	DBName             string
	SlowQueryThreshold time.Duration
}

// QueryProfiler handles query analysis and profiling
type QueryProfiler struct {
	db            *sql.DB
	ctx           context.Context
	slowThreshold time.Duration
}

// QueryMetrics stores performance metrics for a query
type QueryMetrics struct {
	Query         string
	ExecutionTime time.Duration
	PlanningTime  time.Duration
	RowsAffected  int64
	BufferHits    int64
	BufferReads   int64
	CostEstimate  float64
	ActualLoops   int
	ActualRows    int64
	ExplainPlan   map[string]interface{}
}

// PlanNode represents a node in the query execution plan
type PlanNode struct {
	NodeType    string
	ActualTime  float64
	PlanRows    int64
	ActualRows  int64
	Loops       int
	BufferUsage BufferUsage
	Children    []PlanNode
}

// BufferUsage tracks buffer statistics for query execution
type BufferUsage struct {
	Shared    BufferMetrics
	Local     BufferMetrics
	Temporary BufferMetrics
}

// BufferMetrics contains detailed buffer statistics
type BufferMetrics struct {
	Hit   int64
	Read  int64
	Write int64
	Total int64
}

// NewQueryProfiler creates a new instance of QueryProfiler
func NewQueryProfiler(config ProfilerConfig) (*QueryProfiler, error) {
	connStr := fmt.Sprintf(
		"host=%s port=%d user=%s password=%s dbname=%s sslmode=disable",
		config.Host, config.Port, config.User, config.Password, config.DBName,
	)

	db, err := sql.Open("postgres", connStr)
	if err != nil {
		return nil, fmt.Errorf("failed to connect to database: %v", err)
	}

	// Enable query statistics collection
	if _, err := db.Exec("SET track_io_timing = ON"); err != nil {
		return nil, fmt.Errorf("failed to enable IO timing: %v", err)
	}

	return &QueryProfiler{
		db:            db,
		ctx:           context.Background(),
		slowThreshold: config.SlowQueryThreshold,
	}, nil
}

// ProfileQuery analyzes a query's performance characteristics
func (qp *QueryProfiler) ProfileQuery(query string, args ...interface{}) (*QueryMetrics, error) {
	metrics := &QueryMetrics{Query: query}

	// Get query plan with timing information
	explainQuery := fmt.Sprintf("EXPLAIN (ANALYZE, BUFFERS, FORMAT JSON) %s", query)
	var planJSON []byte

	err := qp.db.QueryRowContext(qp.ctx, explainQuery, args...).Scan(&planJSON)
	if err != nil {
		return nil, fmt.Errorf("failed to get query plan: %v", err)
	}

	// Parse the execution plan
	var plan []map[string]interface{}
	if err := json.Unmarshal(planJSON, &plan); err != nil {
		return nil, fmt.Errorf("failed to parse query plan: %v", err)
	}

	metrics.ExplainPlan = plan[0]
	metrics.extractMetricsFromPlan(plan[0])

	// Check if this is a slow query
	if metrics.ExecutionTime > qp.slowThreshold {
		qp.logSlowQuery(metrics)
	}

	return metrics, nil
}

// extractMetricsFromPlan processes the execution plan to extract metrics
func (qm *QueryMetrics) extractMetricsFromPlan(plan map[string]interface{}) {
	if plan == nil {
		return
	}

	// Extract execution metrics
	if planStats, ok := plan["Plan"].(map[string]interface{}); ok {
		qm.ActualRows = int64(planStats["Actual Rows"].(float64))
		qm.CostEstimate = planStats["Total Cost"].(float64)
		qm.ActualLoops = int(planStats["Actual Loops"].(float64))
	}

	// Extract timing information
	if timing, ok := plan["Planning Time"].(float64); ok {
		qm.PlanningTime = time.Duration(timing * float64(time.Millisecond))
	}
	if timing, ok := plan["Execution Time"].(float64); ok {
		qm.ExecutionTime = time.Duration(timing * float64(time.Millisecond))
	}
}

// AnalyzeQueryPattern examines query patterns and suggests optimizations
func (qp *QueryProfiler) AnalyzeQueryPattern(query string) ([]string, error) {
	var suggestions []string

	// Check for common anti-patterns
	patterns := map[string]*regexp.Regexp{
		"SELECT *":                   regexp.MustCompile(`SELECT\s+\*\s+FROM`),
		"Missing WHERE clause":       regexp.MustCompile(`FROM\s+\w+\s*(?:ORDER|GROUP|LIMIT|$)`),
		"IN with large lists":        regexp.MustCompile(`IN\s*\([^)]{1000,}\)`),
		"LIKE with leading wildcard": regexp.MustCompile(`LIKE\s*'%\w+'`),
	}

	for pattern, regex := range patterns {
		if regex.MatchString(query) {
			suggestions = append(suggestions, fmt.Sprintf(
				"Found anti-pattern: %s. Consider optimizing this part of the query.",
				pattern,
			))
		}
	}

	return suggestions, nil
}

// GetTableStatistics retrieves statistical information about table usage
func (qp *QueryProfiler) GetTableStatistics() error {
	query := `
		SELECT
			schemaname || '.' || relname as table_name,
			seq_scan,
			seq_tup_read,
			idx_scan,
			n_tup_ins,
			n_tup_upd,
			n_tup_del,
			n_live_tup,
			n_dead_tup
		FROM
			pg_stat_user_tables
		ORDER BY
			seq_tup_read DESC;
	`

	rows, err := qp.db.QueryContext(qp.ctx, query)
	if err != nil {
		return fmt.Errorf("failed to get table statistics: %v", err)
	}
	defer rows.Close()

	fmt.Println("\nTable Statistics:")
	fmt.Printf("%-30s %-10s %-12s %-10s %-10s %-10s %-10s %-10s %-10s\n",
		"Table", "Seq Scans", "Rows Read", "Idx Scans", "Inserts", "Updates",
		"Deletes", "Live Rows", "Dead Rows")
	fmt.Println(strings.Repeat("-", 120))

	for rows.Next() {
		var tableName string
		var seqScan, seqTupRead, idxScan, tupIns, tupUpd, tupDel, liveTup, deadTup int64

		err := rows.Scan(&tableName, &seqScan, &seqTupRead, &idxScan, &tupIns,
			&tupUpd, &tupDel, &liveTup, &deadTup)
		if err != nil {
			return fmt.Errorf("failed to scan row: %v", err)
		}

		fmt.Printf("%-30s %-10d %-12d %-10d %-10d %-10d %-10d %-10d %-10d\n",
			tableName, seqScan, seqTupRead, idxScan, tupIns, tupUpd, tupDel,
			liveTup, deadTup)
	}

	return nil
}

// logSlowQuery records information about slow queries for analysis
func (qp *QueryProfiler) logSlowQuery(metrics *QueryMetrics) {
	log.Printf(`
Slow Query Detected:
Query: %s
Execution Time: %v
Planning Time: %v
Rows Affected: %d
Cost Estimate: %.2f
Actual Rows: %d
`,
		metrics.Query,
		metrics.ExecutionTime,
		metrics.PlanningTime,
		metrics.RowsAffected,
		metrics.CostEstimate,
		metrics.ActualRows,
	)
}

// GetQueryStatistics retrieves overall query statistics from pg_stat_statements
func (qp *QueryProfiler) GetQueryStatistics() error {
	// Enable pg_stat_statements if not already enabled
	_, err := qp.db.ExecContext(qp.ctx, `
		CREATE EXTENSION IF NOT EXISTS pg_stat_statements;
	`)
	if err != nil {
		return fmt.Errorf("failed to enable pg_stat_statements: %v", err)
	}

	query := `
		SELECT
			query,
			calls,
			total_time / 1000 as total_time_ms,
			mean_time / 1000 as mean_time_ms,
			rows
		FROM
			pg_stat_statements
		ORDER BY
			total_time DESC
		LIMIT 10;
	`

	rows, err := qp.db.QueryContext(qp.ctx, query)
	if err != nil {
		return fmt.Errorf("failed to get query statistics: %v", err)
	}
	defer rows.Close()

	fmt.Println("\nTop 10 Time-Consuming Queries:")
	fmt.Printf("%-50s %-10s %-15s %-15s %-10s\n",
		"Query", "Calls", "Total Time(ms)", "Mean Time(ms)", "Rows")
	fmt.Println(strings.Repeat("-", 100))

	for rows.Next() {
		var query string
		var calls, rowCount int64
		var totalTime, meanTime float64

		err := rows.Scan(&query, &calls, &totalTime, &meanTime, &rowCount)
		if err != nil {
			return fmt.Errorf("failed to scan row: %v", err)
		}

		// Truncate long queries for display
		if len(query) > 47 {
			query = query[:47] + "..."
		}

		fmt.Printf("%-50s %-10d %-15.2f %-15.2f %-10d\n",
			query, calls, totalTime, meanTime, rows)
	}

	return nil
}

func query_profiling() {
	config := ProfilerConfig{
		Host:               "localhost",
		Port:               5432,
		User:               "postgres",
		Password:           "your_password",
		DBName:             "testdb",
		SlowQueryThreshold: 100 * time.Millisecond,
	}

	profiler, err := NewQueryProfiler(config)
	if err != nil {
		log.Fatalf("Failed to create query profiler: %v", err)
	}
	defer profiler.db.Close()

	// Example query to profile
	query := `
		SELECT u.name, COUNT(o.id) as order_count
		FROM users u
		LEFT JOIN orders o ON u.id = o.user_id
		GROUP BY u.name
		ORDER BY order_count DESC;
	`

	// Profile the query
	metrics, err := profiler.ProfileQuery(query)
	if err != nil {
		log.Printf("Failed to profile query: %v", err)
	} else {
		fmt.Printf("Query Execution Time: %v\n", metrics.ExecutionTime)
		fmt.Printf("Query Planning Time: %v\n", metrics.PlanningTime)
		fmt.Printf("Rows Affected: %d\n", metrics.RowsAffected)
	}

	// Analyze query patterns
	suggestions, err := profiler.AnalyzeQueryPattern(query)
	if err != nil {
		log.Printf("Failed to analyze query pattern: %v", err)
	} else {
		fmt.Println("\nQuery Analysis Suggestions:")
		for _, suggestion := range suggestions {
			fmt.Printf("- %s\n", suggestion)
		}
	}

	// Get table statistics
	if err := profiler.GetTableStatistics(); err != nil {
		log.Printf("Failed to get table statistics: %v", err)
	}

	// Get query statistics
	if err := profiler.GetQueryStatistics(); err != nil {
		log.Printf("Failed to get query statistics: %v", err)
	}
}
