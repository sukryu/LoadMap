package main

import (
	"context"
	"database/sql"
	"fmt"
	"log"
	"sync"
	"sync/atomic"
	"time"

	_ "github.com/lib/pq"
)

// PoolManagerConfig contains configuration for the connection pool manager
type PoolManagerConfig struct {
	Host              string
	Port              int
	User              string
	Password          string
	DBName            string
	MaxOpenConns      int
	MaxIdleConns      int
	ConnMaxLifetime   time.Duration
	ConnMaxIdleTime   time.Duration
	HealthCheckPeriod time.Duration
}

// PoolManager handles database connection pool optimization
type PoolManager struct {
	db              *sql.DB
	ctx             context.Context
	cancel          context.CancelFunc
	activeConns     int32
	healthCheckDone chan struct{}
	metrics         *PoolMetrics
	mutex           sync.RWMutex
}

// PoolMetrics tracks various connection pool statistics
type PoolMetrics struct {
	TotalConnections    int64
	ActiveConnections   int64
	IdleConnections     int64
	WaitCount           int64
	WaitDuration        time.Duration
	MaxIdleTimeClosed   int64
	MaxLifetimeClosed   int64
	HealthCheckFailures int64
}

// ConnectionStats represents current connection statistics
type ConnectionStats struct {
	MaxOpenConnections int
	OpenConnections    int
	InUseConnections   int
	IdleConnections    int
	WaitingQueries     int64
	WaitDuration       time.Duration
}

// NewPoolManager creates and initializes a new connection pool manager
func NewPoolManager(config PoolManagerConfig) (*PoolManager, error) {
	connStr := fmt.Sprintf(
		"host=%s port=%d user=%s password=%s dbname=%s sslmode=disable",
		config.Host, config.Port, config.User, config.Password, config.DBName,
	)

	db, err := sql.Open("postgres", connStr)
	if err != nil {
		return nil, fmt.Errorf("failed to create database connection: %v", err)
	}

	// Configure connection pool settings
	db.SetMaxOpenConns(config.MaxOpenConns)
	db.SetMaxIdleConns(config.MaxIdleConns)
	db.SetConnMaxLifetime(config.ConnMaxLifetime)
	db.SetConnMaxIdleTime(config.ConnMaxIdleTime)

	ctx, cancel := context.WithCancel(context.Background())

	pm := &PoolManager{
		db:              db,
		ctx:             ctx,
		cancel:          cancel,
		healthCheckDone: make(chan struct{}),
		metrics:         &PoolMetrics{},
	}

	// Start background health check routine
	go pm.performHealthChecks(config.HealthCheckPeriod)

	return pm, nil
}

// performHealthChecks periodically checks connection health
func (pm *PoolManager) performHealthChecks(period time.Duration) {
	ticker := time.NewTicker(period)
	defer ticker.Stop()
	defer close(pm.healthCheckDone)

	for {
		select {
		case <-pm.ctx.Done():
			return
		case <-ticker.C:
			pm.checkConnectionHealth()
		}
	}
}

// checkConnectionHealth verifies the health of connections in the pool
func (pm *PoolManager) checkConnectionHealth() {
	stats := pm.db.Stats()

	// Test a connection from the pool
	ctx, cancel := context.WithTimeout(pm.ctx, 5*time.Second)
	defer cancel()

	err := pm.db.PingContext(ctx)
	if err != nil {
		atomic.AddInt64(&pm.metrics.HealthCheckFailures, 1)
		log.Printf("Health check failed: %v", err)
		return
	}

	// Update metrics
	atomic.StoreInt64(&pm.metrics.TotalConnections, int64(stats.OpenConnections))
	atomic.StoreInt64(&pm.metrics.ActiveConnections, int64(stats.InUse))
	atomic.StoreInt64(&pm.metrics.IdleConnections, int64(stats.Idle))
	atomic.StoreInt64(&pm.metrics.WaitCount, stats.WaitCount)
	atomic.StoreInt64(&pm.metrics.MaxIdleTimeClosed, stats.MaxIdleTimeClosed)
	atomic.StoreInt64(&pm.metrics.MaxLifetimeClosed, stats.MaxLifetimeClosed)
}

// ExecuteWithConnPool executes a query using a connection from the pool
func (pm *PoolManager) ExecuteWithConnPool(query string, args ...interface{}) error {
	atomic.AddInt32(&pm.activeConns, 1)
	defer atomic.AddInt32(&pm.activeConns, -1)

	ctx, cancel := context.WithTimeout(pm.ctx, 30*time.Second)
	defer cancel()

	// Execute query with timeout
	_, err := pm.db.ExecContext(ctx, query, args...)
	if err != nil {
		return fmt.Errorf("query execution failed: %v", err)
	}

	return nil
}

// GetConnectionStats retrieves current connection pool statistics
func (pm *PoolManager) GetConnectionStats() ConnectionStats {
	stats := pm.db.Stats()

	return ConnectionStats{
		MaxOpenConnections: stats.MaxOpenConnections,
		OpenConnections:    stats.OpenConnections,
		InUseConnections:   stats.InUse,
		IdleConnections:    stats.Idle,
		WaitingQueries:     stats.WaitCount,
		WaitDuration:       stats.WaitDuration,
	}
}

// OptimizePoolSize adjusts the pool size based on current usage patterns
func (pm *PoolManager) OptimizePoolSize() {
	stats := pm.db.Stats()

	// Calculate optimal pool size based on usage patterns
	inUseRatio := float64(stats.InUse) / float64(stats.MaxOpenConnections)
	waitRatio := float64(stats.WaitCount) / float64(stats.MaxOpenConnections)

	// Adjust pool size based on metrics
	if inUseRatio > 0.8 && waitRatio > 0.1 {
		// High connection usage and wait times - increase pool size
		newMax := int(float64(stats.MaxOpenConnections) * 1.2)
		pm.db.SetMaxOpenConns(newMax)
		log.Printf("Increasing max connections to %d", newMax)
	} else if inUseRatio < 0.2 && stats.MaxOpenConnections > 10 {
		// Low connection usage - decrease pool size
		newMax := int(float64(stats.MaxOpenConnections) * 0.8)
		if newMax < 10 {
			newMax = 10 // Maintain minimum pool size
		}
		pm.db.SetMaxOpenConns(newMax)
		log.Printf("Decreasing max connections to %d", newMax)
	}
}

// MonitorPoolHealth starts monitoring pool health metrics
func (pm *PoolManager) MonitorPoolHealth(interval time.Duration) {
	ticker := time.NewTicker(interval)
	defer ticker.Stop()

	for {
		select {
		case <-pm.ctx.Done():
			return
		case <-ticker.C:
			stats := pm.GetConnectionStats()
			log.Printf(`
Connection Pool Health:
Max Open Connections: %d
Current Open Connections: %d
In Use Connections: %d
Idle Connections: %d
Waiting Queries: %d
Wait Duration: %v
`,
				stats.MaxOpenConnections,
				stats.OpenConnections,
				stats.InUseConnections,
				stats.IdleConnections,
				stats.WaitingQueries,
				stats.WaitDuration,
			)

			// Optimize pool size if needed
			pm.OptimizePoolSize()
		}
	}
}

// SimulateLoad generates test load on the connection pool
func (pm *PoolManager) SimulateLoad(numQueries int, concurrency int) {
	var wg sync.WaitGroup
	queries := make(chan int, numQueries)

	// Fill query channel
	for i := 0; i < numQueries; i++ {
		queries <- i
	}
	close(queries)

	// Start worker goroutines
	for i := 0; i < concurrency; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for queryNum := range queries {
				query := fmt.Sprintf("SELECT pg_sleep(0.1) -- Query %d", queryNum)
				if err := pm.ExecuteWithConnPool(query); err != nil {
					log.Printf("Query %d failed: %v", queryNum, err)
				}
			}
		}()
	}

	wg.Wait()
}

func connection_pooling() {
	config := PoolManagerConfig{
		Host:              "localhost",
		Port:              5432,
		User:              "postgres",
		Password:          "your_password",
		DBName:            "testdb",
		MaxOpenConns:      25,
		MaxIdleConns:      5,
		ConnMaxLifetime:   30 * time.Minute,
		ConnMaxIdleTime:   10 * time.Minute,
		HealthCheckPeriod: 30 * time.Second,
	}

	poolManager, err := NewPoolManager(config)
	if err != nil {
		log.Fatalf("Failed to create pool manager: %v", err)
	}
	defer poolManager.db.Close()

	// Start health monitoring in background
	go poolManager.MonitorPoolHealth(5 * time.Second)

	// Simulate some load on the connection pool
	log.Println("Simulating database load...")
	go poolManager.SimulateLoad(100, 10)

	// Keep program running to observe metrics
	time.Sleep(1 * time.Minute)
}
