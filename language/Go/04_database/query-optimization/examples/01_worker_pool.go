package main

import (
	"context"
	"database/sql"
	"fmt"
	"log"
	"sync"
	"time"

	_ "github.com/lib/pq"
)

// WorkerDBConfig contains database configuration for the worker pool
type WorkerDBConfig struct {
	Host     string
	Port     int
	User     string
	Password string
	DBName   string
	PoolSize int
}

// QueryTask represents a database query task to be processed
type QueryTask struct {
	Query  string
	Params []interface{}
	Result chan QueryResult
}

// QueryResult represents the result of a database query
type QueryResult struct {
	Data  interface{}
	Error error
}

// WorkerPool manages a pool of database workers
type WorkerPool struct {
	db          *sql.DB
	taskQueue   chan QueryTask
	workerCount int
	wg          sync.WaitGroup
	ctx         context.Context
	cancel      context.CancelFunc
}

// NewWorkerPool creates and initializes a new worker pool
func NewWorkerPool(config WorkerDBConfig) (*WorkerPool, error) {
	// Initialize database connection with optimized settings
	connStr := fmt.Sprintf(
		"host=%s port=%d user=%s password=%s dbname=%s sslmode=disable",
		config.Host, config.Port, config.User, config.Password, config.DBName,
	)

	db, err := sql.Open("postgres", connStr)
	if err != nil {
		return nil, fmt.Errorf("failed to open database connection: %v", err)
	}

	// Configure connection pool settings
	db.SetMaxOpenConns(config.PoolSize)
	db.SetMaxIdleConns(config.PoolSize / 2)
	db.SetConnMaxLifetime(30 * time.Minute)

	// Create context with cancellation for graceful shutdown
	ctx, cancel := context.WithCancel(context.Background())

	return &WorkerPool{
		db:          db,
		taskQueue:   make(chan QueryTask, config.PoolSize*2), // Buffer size is twice the worker count
		workerCount: config.PoolSize,
		ctx:         ctx,
		cancel:      cancel,
	}, nil
}

// Start launches the worker pool
func (wp *WorkerPool) Start() {
	log.Printf("Starting worker pool with %d workers", wp.workerCount)

	// Launch workers
	for i := 0; i < wp.workerCount; i++ {
		wp.wg.Add(1)
		go wp.worker(i)
	}
}

// worker processes database queries from the task queue
func (wp *WorkerPool) worker(id int) {
	defer wp.wg.Done()

	log.Printf("Worker %d started", id)

	for {
		select {
		case <-wp.ctx.Done():
			log.Printf("Worker %d shutting down", id)
			return

		case task := <-wp.taskQueue:
			// Execute query with timeout context
			queryCtx, cancel := context.WithTimeout(wp.ctx, 10*time.Second)
			result := wp.executeQuery(queryCtx, task)
			cancel()

			// Send result back through the result channel
			task.Result <- result
		}
	}
}

// executeQuery performs the actual database query
func (wp *WorkerPool) executeQuery(ctx context.Context, task QueryTask) QueryResult {
	rows, err := wp.db.QueryContext(ctx, task.Query, task.Params...)
	if err != nil {
		return QueryResult{Error: fmt.Errorf("query execution failed: %v", err)}
	}
	defer rows.Close()

	// Process query results
	var results []map[string]interface{}
	columns, err := rows.Columns()
	if err != nil {
		return QueryResult{Error: fmt.Errorf("failed to get columns: %v", err)}
	}

	for rows.Next() {
		// Create a slice of interface{} to hold the row values
		values := make([]interface{}, len(columns))
		valuePtrs := make([]interface{}, len(columns))
		for i := range columns {
			valuePtrs[i] = &values[i]
		}

		// Scan the row into the values slice
		if err := rows.Scan(valuePtrs...); err != nil {
			return QueryResult{Error: fmt.Errorf("row scan failed: %v", err)}
		}

		// Convert the row into a map
		row := make(map[string]interface{})
		for i, col := range columns {
			row[col] = values[i]
		}
		results = append(results, row)
	}

	return QueryResult{Data: results}
}

// SubmitQuery adds a query to the task queue
func (wp *WorkerPool) SubmitQuery(query string, params ...interface{}) chan QueryResult {
	resultChan := make(chan QueryResult, 1)
	task := QueryTask{
		Query:  query,
		Params: params,
		Result: resultChan,
	}
	wp.taskQueue <- task
	return resultChan
}

// Shutdown gracefully stops the worker pool
func (wp *WorkerPool) Shutdown() {
	log.Println("Initiating worker pool shutdown")
	wp.cancel()  // Signal all workers to stop
	wp.wg.Wait() // Wait for all workers to finish
	close(wp.taskQueue)
	wp.db.Close()
	log.Println("Worker pool shutdown complete")
}

func worker_pool() {
	// Initialize worker pool configuration
	config := WorkerDBConfig{
		Host:     "localhost",
		Port:     5432,
		User:     "postgres",
		Password: "your_password",
		DBName:   "testdb",
		PoolSize: 5,
	}

	// Create and start worker pool
	pool, err := NewWorkerPool(config)
	if err != nil {
		log.Fatalf("Failed to create worker pool: %v", err)
	}
	pool.Start()

	// Example queries
	queries := []string{
		"SELECT * FROM users WHERE id = $1",
		"SELECT * FROM users WHERE email = $1",
		"SELECT * FROM users WHERE last_name = $1",
	}
	params := []interface{}{1, "john@example.com", "Doe"}

	// Submit queries and collect results
	results := make([]chan QueryResult, len(queries))
	for i, query := range queries {
		results[i] = pool.SubmitQuery(query, params[i])
	}

	// Process results
	for i, resultChan := range results {
		result := <-resultChan
		if result.Error != nil {
			log.Printf("Query %d failed: %v", i+1, result.Error)
			continue
		}

		if data, ok := result.Data.([]map[string]interface{}); ok {
			log.Printf("Query %d returned %d rows", i+1, len(data))
			// Process the data as needed
		}
	}

	// Graceful shutdown
	pool.Shutdown()
}
