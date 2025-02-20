package main

import (
	"context"
	"crypto/sha256"
	"database/sql"
	"encoding/hex"
	"encoding/json"
	"fmt"
	"log"
	"sync"
	"time"

	_ "github.com/lib/pq"
)

// CacheControlConfig contains configuration for the cache controller
type CacheControlConfig struct {
	DbHost              string
	DbPort              int
	DbUser              string
	DbPassword          string
	DbName              string
	StorageLimit        int
	ItemExpiration      time.Duration
	MaintenanceInterval time.Duration
}

// CacheController manages database query result caching
type CacheController struct {
	dbConn              *sql.DB
	controlCtx          context.Context
	cancelFunc          context.CancelFunc
	storageMap          map[string]*CacheStorageItem
	storageMutex        sync.RWMutex
	maxStorageSize      int
	itemLifetime        time.Duration
	cleanupFrequency    time.Duration
	performanceTracking *CachePerformanceStats
}

// CacheStorageItem represents a cached query result
type CacheStorageItem struct {
	HashKey      string
	StoredData   interface{}
	CreationTime time.Time
	ExpiryTime   time.Time
	LastUsedTime time.Time
	UsageCounter int64
	StorageSpace int
}

// CachePerformanceStats tracks cache operation statistics
type CachePerformanceStats struct {
	CacheRetrievals    int64
	CacheMisses        int64
	ItemRemovals       int64
	QueryExecutions    int64
	CurrentStorageUsed int64
	CleanupDuration    time.Duration
	statMutex          sync.RWMutex
}

// CacheQueryResult represents the result of a database query
type CacheQueryResult struct {
	FieldNames []string
	DataRows   []map[string]interface{}
}

// NewCacheController creates a new instance of CacheController
func NewCacheController(cfg CacheControlConfig) (*CacheController, error) {
	dbConnStr := fmt.Sprintf(
		"host=%s port=%d user=%s password=%s dbname=%s sslmode=disable",
		cfg.DbHost, cfg.DbPort, cfg.DbUser, cfg.DbPassword, cfg.DbName,
	)

	dbConn, err := sql.Open("postgres", dbConnStr)
	if err != nil {
		return nil, fmt.Errorf("database connection failed: %v", err)
	}

	ctrlCtx, cancelFunc := context.WithCancel(context.Background())

	controller := &CacheController{
		dbConn:              dbConn,
		controlCtx:          ctrlCtx,
		cancelFunc:          cancelFunc,
		storageMap:          make(map[string]*CacheStorageItem),
		maxStorageSize:      cfg.StorageLimit,
		itemLifetime:        cfg.ItemExpiration,
		cleanupFrequency:    cfg.MaintenanceInterval,
		performanceTracking: &CachePerformanceStats{},
	}

	go controller.scheduledMaintenance()

	return controller, nil
}

// generateStorageKey creates a unique hash for a query and its parameters
func (cc *CacheController) generateStorageKey(queryText string, queryParams ...interface{}) string {
	keyComponents := queryText
	for _, param := range queryParams {
		keyComponents += fmt.Sprintf(":%v", param)
	}

	hashValue := sha256.Sum256([]byte(keyComponents))
	return hex.EncodeToString(hashValue[:])
}

// retrieveCachedItem fetches an item from cache
func (cc *CacheController) retrieveCachedItem(hashKey string) (interface{}, bool) {
	cc.storageMutex.RLock()
	item, exists := cc.storageMap[hashKey]
	cc.storageMutex.RUnlock()

	if !exists {
		cc.performanceTracking.statMutex.Lock()
		cc.performanceTracking.CacheMisses++
		cc.performanceTracking.statMutex.Unlock()
		return nil, false
	}

	if time.Now().After(item.ExpiryTime) {
		cc.storageMutex.Lock()
		delete(cc.storageMap, hashKey)
		cc.storageMutex.Unlock()

		cc.performanceTracking.statMutex.Lock()
		cc.performanceTracking.ItemRemovals++
		cc.performanceTracking.statMutex.Unlock()

		return nil, false
	}

	item.LastUsedTime = time.Now()
	item.UsageCounter++

	cc.performanceTracking.statMutex.Lock()
	cc.performanceTracking.CacheRetrievals++
	cc.performanceTracking.statMutex.Unlock()

	return item.StoredData, true
}

// storeQueryResult saves a query result in cache
func (cc *CacheController) storeQueryResult(hashKey string, queryResult interface{}, expiration time.Duration) error {
	if expiration == 0 {
		expiration = cc.itemLifetime
	}

	serializedData, err := json.Marshal(queryResult)
	if err != nil {
		return fmt.Errorf("result serialization failed: %v", err)
	}

	itemSize := len(serializedData)

	cc.manageStorageSpace(itemSize)

	storageItem := &CacheStorageItem{
		HashKey:      hashKey,
		StoredData:   queryResult,
		CreationTime: time.Now(),
		ExpiryTime:   time.Now().Add(expiration),
		LastUsedTime: time.Now(),
		StorageSpace: itemSize,
	}

	cc.storageMutex.Lock()
	cc.storageMap[hashKey] = storageItem
	cc.storageMutex.Unlock()

	cc.performanceTracking.statMutex.Lock()
	cc.performanceTracking.CurrentStorageUsed += int64(itemSize)
	cc.performanceTracking.statMutex.Unlock()

	return nil
}

// executeQueryWithCaching performs a query with caching
func (cc *CacheController) executeQueryWithCaching(queryText string, expiration time.Duration, queryParams ...interface{}) (*CacheQueryResult, error) {
	hashKey := cc.generateStorageKey(queryText, queryParams...)

	if cachedResult, found := cc.retrieveCachedItem(hashKey); found {
		if result, ok := cachedResult.(*CacheQueryResult); ok {
			return result, nil
		}
	}

	queryRows, err := cc.dbConn.QueryContext(cc.controlCtx, queryText, queryParams...)
	if err != nil {
		return nil, fmt.Errorf("query execution error: %v", err)
	}
	defer queryRows.Close()

	fieldNames, err := queryRows.Columns()
	if err != nil {
		return nil, fmt.Errorf("column retrieval error: %v", err)
	}

	queryResult := &CacheQueryResult{
		FieldNames: fieldNames,
		DataRows:   make([]map[string]interface{}, 0),
	}

	fieldValues := make([]interface{}, len(fieldNames))
	fieldPointers := make([]interface{}, len(fieldNames))
	for i := range fieldNames {
		fieldPointers[i] = &fieldValues[i]
	}

	for queryRows.Next() {
		if err := queryRows.Scan(fieldPointers...); err != nil {
			return nil, fmt.Errorf("row scan error: %v", err)
		}

		rowData := make(map[string]interface{})
		for i, colName := range fieldNames {
			rowData[colName] = fieldValues[i]
		}
		queryResult.DataRows = append(queryResult.DataRows, rowData)
	}

	if err := cc.storeQueryResult(hashKey, queryResult, expiration); err != nil {
		log.Printf("Cache storage failed: %v", err)
	}

	return queryResult, nil
}

// manageStorageSpace removes items if cache size exceeds limit
func (cc *CacheController) manageStorageSpace(newItemSize int) {
	cc.storageMutex.Lock()
	defer cc.storageMutex.Unlock()

	startTime := time.Now()
	currentSize := cc.calculateCurrentStorage()

	for currentSize+newItemSize > cc.maxStorageSize && len(cc.storageMap) > 0 {
		lruKey := cc.findLeastRecentlyUsed()
		if lruKey != "" {
			removedSize := cc.storageMap[lruKey].StorageSpace
			delete(cc.storageMap, lruKey)
			currentSize -= removedSize

			cc.performanceTracking.statMutex.Lock()
			cc.performanceTracking.ItemRemovals++
			cc.performanceTracking.CurrentStorageUsed -= int64(removedSize)
			cc.performanceTracking.statMutex.Unlock()
		}
	}

	cc.performanceTracking.statMutex.Lock()
	cc.performanceTracking.CleanupDuration += time.Since(startTime)
	cc.performanceTracking.statMutex.Unlock()
}

// calculateCurrentStorage computes total size of cached items
func (cc *CacheController) calculateCurrentStorage() int {
	totalSize := 0
	for _, item := range cc.storageMap {
		totalSize += item.StorageSpace
	}
	return totalSize
}

// findLeastRecentlyUsed identifies the least recently accessed item
func (cc *CacheController) findLeastRecentlyUsed() string {
	var lruKey string
	var oldestAccess time.Time

	for key, item := range cc.storageMap {
		if lruKey == "" || item.LastUsedTime.Before(oldestAccess) {
			lruKey = key
			oldestAccess = item.LastUsedTime
		}
	}

	return lruKey
}

// scheduledMaintenance performs periodic cache cleanup
func (cc *CacheController) scheduledMaintenance() {
	maintenanceTimer := time.NewTicker(cc.cleanupFrequency)
	defer maintenanceTimer.Stop()

	for {
		select {
		case <-cc.controlCtx.Done():
			return
		case <-maintenanceTimer.C:
			cc.storageMutex.Lock()
			currentTime := time.Now()
			for key, item := range cc.storageMap {
				if currentTime.After(item.ExpiryTime) {
					cc.performanceTracking.statMutex.Lock()
					cc.performanceTracking.CurrentStorageUsed -= int64(item.StorageSpace)
					cc.performanceTracking.ItemRemovals++
					cc.performanceTracking.statMutex.Unlock()

					delete(cc.storageMap, key)
				}
			}
			cc.storageMutex.Unlock()
		}
	}
}

// retrievePerformanceStats returns current cache statistics
func (cc *CacheController) retrievePerformanceStats() CachePerformanceStats {
	cc.performanceTracking.statMutex.RLock()
	defer cc.performanceTracking.statMutex.RUnlock()

	return CachePerformanceStats{
		CacheRetrievals:    cc.performanceTracking.CacheRetrievals,
		CacheMisses:        cc.performanceTracking.CacheMisses,
		ItemRemovals:       cc.performanceTracking.ItemRemovals,
		QueryExecutions:    cc.performanceTracking.QueryExecutions,
		CurrentStorageUsed: cc.performanceTracking.CurrentStorageUsed,
		CleanupDuration:    cc.performanceTracking.CleanupDuration,
	}
}

func query_caching() {
	cfg := CacheControlConfig{
		DbHost:              "localhost",
		DbPort:              5432,
		DbUser:              "postgres",
		DbPassword:          "your_password",
		DbName:              "testdb",
		StorageLimit:        1024 * 1024 * 100, // 100MB
		ItemExpiration:      10 * time.Minute,
		MaintenanceInterval: 1 * time.Minute,
	}

	cacheCtrl, err := NewCacheController(cfg)
	if err != nil {
		log.Fatalf("Cache controller initialization failed: %v", err)
	}
	defer cacheCtrl.dbConn.Close()

	// Example: Execute queries with caching
	testQueries := []string{
		"SELECT * FROM users WHERE department = $1",
		"SELECT * FROM tasks WHERE status = $1",
		"SELECT * FROM reports WHERE type = $1",
	}

	for i := 0; i < 5; i++ {
		for _, queryText := range testQueries {
			result, err := cacheCtrl.executeQueryWithCaching(queryText, 5*time.Minute, i+1)
			if err != nil {
				log.Printf("Query execution failed: %v", err)
				continue
			}
			log.Printf("Query returned %d rows", len(result.DataRows))
		}
	}

	// Print performance statistics
	stats := cacheCtrl.retrievePerformanceStats()
	log.Printf(`
Cache Performance Metrics:
Cache Hits: %d
Cache Misses: %d
Items Removed: %d
Total Queries: %d
Current Storage Used: %d bytes
Average Cleanup Time: %v
`,
		stats.CacheRetrievals,
		stats.CacheMisses,
		stats.ItemRemovals,
		stats.QueryExecutions,
		stats.CurrentStorageUsed,
		stats.CleanupDuration/time.Duration(stats.ItemRemovals+1),
	)
}
