package main

import (
	"context"
	"database/sql"
	"fmt"
	"log"
	"sync"
	"time"

	"github.com/lib/pq"
	_ "github.com/lib/pq"
)

// ErrorHandlingSettings contains configuration for the error handling system
type ErrorHandlingSettings struct {
	PostgresHost     string
	PostgresPort     int
	PostgresUser     string
	PostgresPassword string
	PostgresDBName   string
	RetryLimit       int
	RetryBackoff     time.Duration
	LogRetention     time.Duration
}

// ErrorManagementSystem handles database operation errors and recovery
type ErrorManagementSystem struct {
	postgresConn     *sql.DB
	supervisionCtx   context.Context
	supervisionStop  context.CancelFunc
	errorHistory     []*OperationErrorRecord
	historyGuard     sync.RWMutex
	retryThreshold   int
	retryInterval    time.Duration
	errorLogLifetime time.Duration
	errorStats       *ErrorTrackingMetrics
}

// OperationErrorRecord represents a database operation error
type OperationErrorRecord struct {
	ErrorID        string
	OperationType  string
	ErrorMessage   string
	SQLState       string
	Timestamp      time.Time
	RetryCount     int
	RecoveryStatus string
	QueryDetails   *QueryErrorInfo
}

// QueryErrorInfo contains detailed information about the failed query
type QueryErrorInfo struct {
	QueryText    string
	Parameters   []interface{}
	AffectedRows int64
	Duration     time.Duration
}

// ErrorTrackingMetrics maintains error statistics
type ErrorTrackingMetrics struct {
	TotalErrors     int64
	RecoveredErrors int64
	PermanentErrors int64
	RetryAttempts   int64
	AvgRecoveryTime time.Duration
	metricsGuard    sync.RWMutex
}

// InitializeErrorSystem creates a new error handling system
func InitializeErrorSystem(settings ErrorHandlingSettings) (*ErrorManagementSystem, error) {
	connectionStr := fmt.Sprintf(
		"host=%s port=%d user=%s password=%s dbname=%s sslmode=disable",
		settings.PostgresHost, settings.PostgresPort,
		settings.PostgresUser, settings.PostgresPassword,
		settings.PostgresDBName,
	)

	dbConnection, err := sql.Open("postgres", connectionStr)
	if err != nil {
		return nil, fmt.Errorf("database connection creation failed: %v", err)
	}

	systemCtx, cancelFunc := context.WithCancel(context.Background())

	errorSystem := &ErrorManagementSystem{
		postgresConn:     dbConnection,
		supervisionCtx:   systemCtx,
		supervisionStop:  cancelFunc,
		retryThreshold:   settings.RetryLimit,
		retryInterval:    settings.RetryBackoff,
		errorLogLifetime: settings.LogRetention,
		errorStats:       &ErrorTrackingMetrics{},
	}

	go errorSystem.initializeErrorTracking()
	go errorSystem.startErrorLogMaintenance()

	return errorSystem, nil
}

// HandleDatabaseError processes and attempts to recover from database errors
func (ems *ErrorManagementSystem) HandleDatabaseError(operationType string, err error, queryInfo *QueryErrorInfo) error {
	if err == nil {
		return nil
	}

	errorRecord := &OperationErrorRecord{
		ErrorID:       fmt.Sprintf("ERR_%d", time.Now().UnixNano()),
		OperationType: operationType,
		ErrorMessage:  err.Error(),
		Timestamp:     time.Now(),
		QueryDetails:  queryInfo,
	}

	// Extract PostgreSQL error code if available
	if pgErr, ok := err.(*pq.Error); ok {
		errorRecord.SQLState = string(pgErr.Code)
	}

	ems.logErrorRecord(errorRecord)

	// Attempt recovery based on error type
	if ems.isRecoverableError(errorRecord) {
		return ems.attemptErrorRecovery(errorRecord)
	}

	ems.errorStats.metricsGuard.Lock()
	ems.errorStats.PermanentErrors++
	ems.errorStats.metricsGuard.Unlock()

	return fmt.Errorf("unrecoverable error: %v", err)
}

// attemptErrorRecovery tries to recover from a database error
func (ems *ErrorManagementSystem) attemptErrorRecovery(record *OperationErrorRecord) error {
	startTime := time.Now()

	for attempt := 0; attempt < ems.retryThreshold; attempt++ {
		ems.errorStats.metricsGuard.Lock()
		ems.errorStats.RetryAttempts++
		ems.errorStats.metricsGuard.Unlock()

		record.RetryCount++

		// Wait before retry
		time.Sleep(ems.retryInterval * time.Duration(attempt+1))

		// Attempt to execute the query again
		if err := ems.reexecuteQuery(record.QueryDetails); err == nil {
			record.RecoveryStatus = "recovered"
			ems.updateErrorStats(true, time.Since(startTime))
			return nil
		}
	}

	record.RecoveryStatus = "failed"
	ems.updateErrorStats(false, time.Since(startTime))
	return fmt.Errorf("recovery failed after %d attempts", ems.retryThreshold)
}

// reexecuteQuery attempts to execute a failed query again
func (ems *ErrorManagementSystem) reexecuteQuery(queryInfo *QueryErrorInfo) error {
	if queryInfo == nil {
		return fmt.Errorf("no query information available")
	}

	ctx, cancel := context.WithTimeout(ems.supervisionCtx, 30*time.Second)
	defer cancel()

	_, err := ems.postgresConn.ExecContext(ctx, queryInfo.QueryText, queryInfo.Parameters...)
	return err
}

// isRecoverableError determines if an error can be recovered from
func (ems *ErrorManagementSystem) isRecoverableError(record *OperationErrorRecord) bool {
	// List of recoverable PostgreSQL error codes
	recoverableCodes := map[string]bool{
		"40001": true, // serialization_failure
		"40P01": true, // deadlock_detected
		"55P03": true, // lock_not_available
		"08006": true, // connection_failure
		"57P01": true, // admin_shutdown
	}

	return recoverableCodes[record.SQLState]
}

// logErrorRecord stores an error record in the history
func (ems *ErrorManagementSystem) logErrorRecord(record *OperationErrorRecord) {
	ems.historyGuard.Lock()
	defer ems.historyGuard.Unlock()

	ems.errorHistory = append(ems.errorHistory, record)

	ems.errorStats.metricsGuard.Lock()
	ems.errorStats.TotalErrors++
	ems.errorStats.metricsGuard.Unlock()
}

// updateErrorStats updates error tracking metrics
func (ems *ErrorManagementSystem) updateErrorStats(recovered bool, recoveryTime time.Duration) {
	ems.errorStats.metricsGuard.Lock()
	defer ems.errorStats.metricsGuard.Unlock()

	if recovered {
		ems.errorStats.RecoveredErrors++
		ems.errorStats.AvgRecoveryTime = (ems.errorStats.AvgRecoveryTime + recoveryTime) / 2
	}
}

// initializeErrorTracking sets up error monitoring tables
func (ems *ErrorManagementSystem) initializeErrorTracking() {
	createTableQuery := `
		CREATE TABLE IF NOT EXISTS error_tracking (
			error_id VARCHAR(50) PRIMARY KEY,
			operation_type VARCHAR(100) NOT NULL,
			error_message TEXT NOT NULL,
			sql_state VARCHAR(5),
			timestamp TIMESTAMP WITH TIME ZONE NOT NULL,
			retry_count INT NOT NULL,
			recovery_status VARCHAR(20) NOT NULL,
			query_details JSONB
		)
	`

	if _, err := ems.postgresConn.ExecContext(ems.supervisionCtx, createTableQuery); err != nil {
		log.Printf("Failed to create error tracking table: %v", err)
	}
}

// startErrorLogMaintenance periodically cleans up old error records
func (ems *ErrorManagementSystem) startErrorLogMaintenance() {
	maintenanceTicker := time.NewTicker(24 * time.Hour)
	defer maintenanceTicker.Stop()

	for {
		select {
		case <-ems.supervisionCtx.Done():
			return
		case <-maintenanceTicker.C:
			ems.cleanupOldErrors()
		}
	}
}

// cleanupOldErrors removes expired error records
func (ems *ErrorManagementSystem) cleanupOldErrors() {
	ems.historyGuard.Lock()
	defer ems.historyGuard.Unlock()

	cutoffTime := time.Now().Add(-ems.errorLogLifetime)
	var activeRecords []*OperationErrorRecord

	for _, record := range ems.errorHistory {
		if record.Timestamp.After(cutoffTime) {
			activeRecords = append(activeRecords, record)
		}
	}

	ems.errorHistory = activeRecords
}

// retrieveErrorStatistics returns current error handling metrics
func (ems *ErrorManagementSystem) retrieveErrorStatistics() ErrorTrackingMetrics {
	ems.errorStats.metricsGuard.RLock()
	defer ems.errorStats.metricsGuard.RUnlock()

	return ErrorTrackingMetrics{
		TotalErrors:     ems.errorStats.TotalErrors,
		RecoveredErrors: ems.errorStats.RecoveredErrors,
		PermanentErrors: ems.errorStats.PermanentErrors,
		RetryAttempts:   ems.errorStats.RetryAttempts,
		AvgRecoveryTime: ems.errorStats.AvgRecoveryTime,
	}
}

func error_handling() {
	settings := ErrorHandlingSettings{
		PostgresHost:     "localhost",
		PostgresPort:     5432,
		PostgresUser:     "postgres",
		PostgresPassword: "your_password",
		PostgresDBName:   "testdb",
		RetryLimit:       3,
		RetryBackoff:     time.Second * 2,
		LogRetention:     time.Hour * 24 * 7, // 7 days
	}

	errorSystem, err := InitializeErrorSystem(settings)
	if err != nil {
		log.Fatalf("Error system initialization failed: %v", err)
	}
	defer errorSystem.postgresConn.Close()

	// Example: Handle a database operation error
	queryInfo := &QueryErrorInfo{
		QueryText:  "INSERT INTO users (name, email) VALUES ($1, $2)",
		Parameters: []interface{}{"John Doe", "john@example.com"},
		Duration:   time.Millisecond * 100,
	}

	if err := errorSystem.HandleDatabaseError(
		"insert_user",
		fmt.Errorf("simulation of a deadlock error"),
		queryInfo,
	); err != nil {
		log.Printf("Error handling failed: %v", err)
	}

	// Print error statistics
	stats := errorSystem.retrieveErrorStatistics()
	log.Printf(`
Error Handling Statistics:
Total Errors: %d
Recovered Errors: %d
Permanent Errors: %d
Retry Attempts: %d
Average Recovery Time: %v
`,
		stats.TotalErrors,
		stats.RecoveredErrors,
		stats.PermanentErrors,
		stats.RetryAttempts,
		stats.AvgRecoveryTime,
	)
}
