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

// MonitoringEnvironment contains configuration for the monitoring system
type MonitoringEnvironment struct {
	DatabaseHost     string
	DatabasePort     int
	DatabaseUser     string
	DatabasePassword string
	DatabaseName     string
	SampleInterval   time.Duration
	HistoryRetention time.Duration
	AlertThresholds  PerformanceThresholds
}

// PerformanceThresholds defines alert thresholds for various metrics
type PerformanceThresholds struct {
	MaxQueryDuration  time.Duration
	MaxConnections    int
	MinFreeMemory     int64
	MaxCPUUtilization float64
}

// ObservationSystem manages database performance monitoring
type ObservationSystem struct {
	databaseInstance *sql.DB
	observationCtx   context.Context
	terminateWatch   context.CancelFunc
	performanceData  []*PerformanceSnapshot
	snapshotLock     sync.RWMutex
	samplePeriod     time.Duration
	retentionPeriod  time.Duration
	alertLimits      PerformanceThresholds
	monitoringStats  *ObservationMetrics
}

// PerformanceSnapshot represents a point-in-time performance measurement
type PerformanceSnapshot struct {
	CaptureTime     time.Time
	ActiveQueries   int
	ConnectionCount int
	IdleConnections int
	QueryStatistics QueryPerformanceData
	SystemResources ResourceUtilization
	SlowQueryCount  int
	AlertsTriggered []string
}

// QueryPerformanceData contains query execution statistics
type QueryPerformanceData struct {
	TotalExecutions int64
	AverageLatency  time.Duration
	MaxLatency      time.Duration
	CachedPlanRatio float64
	IndexUsageRatio float64
}

// ResourceUtilization tracks system resource usage
type ResourceUtilization struct {
	CPUUsage         float64
	MemoryUsage      int64
	DiskIOOperations int64
	NetworkTraffic   int64
}

// ObservationMetrics maintains monitoring statistics
type ObservationMetrics struct {
	SnapshotCount     int64
	AlertCount        int64
	TotalQueries      int64
	PerformanceIssues int64
	metricsLock       sync.RWMutex
}

// InitializeMonitoring creates a new monitoring system
func InitializeMonitoring(env MonitoringEnvironment) (*ObservationSystem, error) {
	connectionString := fmt.Sprintf(
		"host=%s port=%d user=%s password=%s dbname=%s sslmode=disable",
		env.DatabaseHost, env.DatabasePort,
		env.DatabaseUser, env.DatabasePassword,
		env.DatabaseName,
	)

	dbInstance, err := sql.Open("postgres", connectionString)
	if err != nil {
		return nil, fmt.Errorf("database connection establishment failed: %v", err)
	}

	observeCtx, cancelFunc := context.WithCancel(context.Background())

	monitorSystem := &ObservationSystem{
		databaseInstance: dbInstance,
		observationCtx:   observeCtx,
		terminateWatch:   cancelFunc,
		samplePeriod:     env.SampleInterval,
		retentionPeriod:  env.HistoryRetention,
		alertLimits:      env.AlertThresholds,
		monitoringStats:  &ObservationMetrics{},
	}

	go monitorSystem.beginPerformanceTracking()
	go monitorSystem.startDataMaintenance()

	return monitorSystem, nil
}

// beginPerformanceTracking starts periodic performance monitoring
func (os *ObservationSystem) beginPerformanceTracking() {
	monitorTicker := time.NewTicker(os.samplePeriod)
	defer monitorTicker.Stop()

	for {
		select {
		case <-os.observationCtx.Done():
			return
		case <-monitorTicker.C:
			os.capturePerformanceSnapshot()
		}
	}
}

// capturePerformanceSnapshot takes a performance measurement
func (os *ObservationSystem) capturePerformanceSnapshot() {
	snapshot := &PerformanceSnapshot{
		CaptureTime: time.Now(),
	}

	var alerts []string

	// Capture database statistics
	dbStats := os.databaseInstance.Stats()
	snapshot.ConnectionCount = dbStats.OpenConnections
	snapshot.IdleConnections = dbStats.Idle

	// Check connection threshold
	if snapshot.ConnectionCount >= os.alertLimits.MaxConnections {
		alerts = append(alerts, "High connection count detected")
	}

	// Gather query statistics
	queryStats, err := os.gatherQueryStatistics()
	if err != nil {
		log.Printf("Failed to gather query statistics: %v", err)
	} else {
		snapshot.QueryStatistics = queryStats

		if queryStats.MaxLatency >= os.alertLimits.MaxQueryDuration {
			alerts = append(alerts, "Slow query detected")
		}
	}

	// Monitor system resources
	resourceStats, err := os.monitorSystemResources()
	if err != nil {
		log.Printf("Failed to monitor system resources: %v", err)
	} else {
		snapshot.SystemResources = resourceStats

		if resourceStats.CPUUsage >= os.alertLimits.MaxCPUUtilization {
			alerts = append(alerts, "High CPU utilization")
		}
	}

	snapshot.AlertsTriggered = alerts

	os.storePerformanceSnapshot(snapshot)
	os.evaluatePerformanceIssues(snapshot)
}

// gatherQueryStatistics collects query performance data
func (os *ObservationSystem) gatherQueryStatistics() (QueryPerformanceData, error) {
	var stats QueryPerformanceData

	// Query pg_stat_statements for query statistics
	query := `
		SELECT 
			count(*) as total_executions,
			avg(total_time) as avg_latency,
			max(total_time) as max_latency,
			sum(CASE WHEN calls > 0 THEN 1 ELSE 0 END)::float / count(*) as cached_plan_ratio,
			sum(CASE WHEN idx_scan > 0 THEN 1 ELSE 0 END)::float / count(*) as index_usage_ratio
		FROM pg_stat_statements
	`

	row := os.databaseInstance.QueryRowContext(os.observationCtx, query)
	err := row.Scan(
		&stats.TotalExecutions,
		&stats.AverageLatency,
		&stats.MaxLatency,
		&stats.CachedPlanRatio,
		&stats.IndexUsageRatio,
	)

	return stats, err
}

// monitorSystemResources gathers system resource utilization
func (os *ObservationSystem) monitorSystemResources() (ResourceUtilization, error) {
	var stats ResourceUtilization

	// Query system statistics
	query := `
		SELECT 
			(SELECT value FROM pg_sysstat WHERE name = 'cpu_usage') as cpu_usage,
			(SELECT value FROM pg_sysstat WHERE name = 'memory_usage') as memory_usage,
			(SELECT value FROM pg_sysstat WHERE name = 'disk_io_ops') as disk_io_ops,
			(SELECT value FROM pg_sysstat WHERE name = 'network_traffic') as network_traffic
	`

	row := os.databaseInstance.QueryRowContext(os.observationCtx, query)
	err := row.Scan(
		&stats.CPUUsage,
		&stats.MemoryUsage,
		&stats.DiskIOOperations,
		&stats.NetworkTraffic,
	)

	return stats, err
}

// storePerformanceSnapshot saves a performance snapshot
func (os *ObservationSystem) storePerformanceSnapshot(snapshot *PerformanceSnapshot) {
	os.snapshotLock.Lock()
	defer os.snapshotLock.Unlock()

	os.performanceData = append(os.performanceData, snapshot)

	os.monitoringStats.metricsLock.Lock()
	os.monitoringStats.SnapshotCount++
	os.monitoringStats.AlertCount += int64(len(snapshot.AlertsTriggered))
	os.monitoringStats.metricsLock.Unlock()
}

// evaluatePerformanceIssues analyzes performance data for issues
func (os *ObservationSystem) evaluatePerformanceIssues(snapshot *PerformanceSnapshot) {
	issueCount := 0

	// Check for various performance issues
	if snapshot.QueryStatistics.AverageLatency > os.alertLimits.MaxQueryDuration/2 {
		issueCount++
		log.Printf("Warning: High average query latency detected")
	}

	if snapshot.QueryStatistics.IndexUsageRatio < 0.5 {
		issueCount++
		log.Printf("Warning: Low index usage ratio detected")
	}

	if snapshot.SystemResources.CPUUsage > os.alertLimits.MaxCPUUtilization*0.8 {
		issueCount++
		log.Printf("Warning: High CPU utilization detected")
	}

	os.monitoringStats.metricsLock.Lock()
	os.monitoringStats.PerformanceIssues += int64(issueCount)
	os.monitoringStats.metricsLock.Unlock()
}

// startDataMaintenance performs periodic cleanup of old data
func (os *ObservationSystem) startDataMaintenance() {
	cleanupTicker := time.NewTicker(24 * time.Hour)
	defer cleanupTicker.Stop()

	for {
		select {
		case <-os.observationCtx.Done():
			return
		case <-cleanupTicker.C:
			os.cleanupOldData()
		}
	}
}

// cleanupOldData removes expired performance data
func (os *ObservationSystem) cleanupOldData() {
	os.snapshotLock.Lock()
	defer os.snapshotLock.Unlock()

	retentionCutoff := time.Now().Add(-os.retentionPeriod)
	var retainedData []*PerformanceSnapshot

	for _, snapshot := range os.performanceData {
		if snapshot.CaptureTime.After(retentionCutoff) {
			retainedData = append(retainedData, snapshot)
		}
	}

	os.performanceData = retainedData
}

// retrieveMonitoringStatistics returns current monitoring metrics
func (os *ObservationSystem) retrieveMonitoringStatistics() ObservationMetrics {
	os.monitoringStats.metricsLock.RLock()
	defer os.monitoringStats.metricsLock.RUnlock()

	return ObservationMetrics{
		SnapshotCount:     os.monitoringStats.SnapshotCount,
		AlertCount:        os.monitoringStats.AlertCount,
		TotalQueries:      os.monitoringStats.TotalQueries,
		PerformanceIssues: os.monitoringStats.PerformanceIssues,
	}
}

func monitoring_metrics() {
	env := MonitoringEnvironment{
		DatabaseHost:     "localhost",
		DatabasePort:     5432,
		DatabaseUser:     "postgres",
		DatabasePassword: "your_password",
		DatabaseName:     "testdb",
		SampleInterval:   time.Second * 30,
		HistoryRetention: time.Hour * 24 * 7, // 7 days
		AlertThresholds: PerformanceThresholds{
			MaxQueryDuration:  time.Second * 5,
			MaxConnections:    100,
			MinFreeMemory:     1024 * 1024 * 1024, // 1GB
			MaxCPUUtilization: 80.0,
		},
	}

	monitorSystem, err := InitializeMonitoring(env)
	if err != nil {
		log.Fatalf("Monitoring system initialization failed: %v", err)
	}
	defer monitorSystem.databaseInstance.Close()

	// Let the monitoring system run for a while
	time.Sleep(time.Minute * 5)

	// Print monitoring statistics
	stats := monitorSystem.retrieveMonitoringStatistics()
	log.Printf(`
Monitoring System Statistics:
Total Snapshots: %d
Total Alerts: %d
Total Queries: %d
Performance Issues: %d
`,
		stats.SnapshotCount,
		stats.AlertCount,
		stats.TotalQueries,
		stats.PerformanceIssues,
	)
}
