// examples/07_migration_patterns.go

package examples

import (
	"context"
	"database/sql"
	"fmt"
	"log"
	"sort"
	"strings"
	"sync"
	"time"

	_ "github.com/lib/pq"
)

// MigrationManager는 데이터베이스 마이그레이션을 관리하는 구조체입니다.
type MigrationManager struct {
	db         *sql.DB
	migrations map[int64]*Migration
	metrics    *MigrationMetrics
	mu         sync.RWMutex
}

// Migration은 개별 마이그레이션 스크립트를 나타냅니다.
type Migration struct {
	Version     int64
	Description string
	UpSQL       string
	DownSQL     string
	AppliedAt   *time.Time
}

// MigrationMetrics는 마이그레이션 실행에 대한 메트릭을 추적합니다.
type MigrationMetrics struct {
	TotalMigrations      int64
	SuccessfulMigrations int64
	FailedMigrations     int64
	RollbackCount        int64
	LastMigrationAt      time.Time
}

// NewMigrationManager는 새로운 MigrationManager를 생성합니다.
func NewMigrationManager(connStr string) (*MigrationManager, error) {
	db, err := sql.Open("postgres", connStr)
	if err != nil {
		return nil, fmt.Errorf("데이터베이스 연결 실패: %v", err)
	}

	return &MigrationManager{
		db:         db,
		migrations: make(map[int64]*Migration),
		metrics:    &MigrationMetrics{},
	}, nil
}

// InitializeMigrationTable은 마이그레이션 이력을 추적하는 테이블을 생성합니다.
func (mm *MigrationManager) InitializeMigrationTable(ctx context.Context) error {
	query := `
		CREATE TABLE IF NOT EXISTS schema_migrations (
			version BIGINT PRIMARY KEY,
			description TEXT NOT NULL,
			applied_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
			checksum TEXT NOT NULL
		)
	`
	_, err := mm.db.ExecContext(ctx, query)
	if err != nil {
		return fmt.Errorf("마이그레이션 테이블 생성 실패: %v", err)
	}
	return nil
}

// RegisterMigration은 새로운 마이그레이션을 등록합니다.
func (mm *MigrationManager) RegisterMigration(version int64, description string, upSQL, downSQL string) error {
	mm.mu.Lock()
	defer mm.mu.Unlock()

	if _, exists := mm.migrations[version]; exists {
		return fmt.Errorf("버전 %d의 마이그레이션이 이미 존재합니다", version)
	}

	mm.migrations[version] = &Migration{
		Version:     version,
		Description: description,
		UpSQL:       upSQL,
		DownSQL:     downSQL,
	}
	return nil
}

// MigrateUp은 지정된 버전까지 마이그레이션을 수행합니다.
func (mm *MigrationManager) MigrateUp(ctx context.Context, targetVersion int64) error {
	// 현재 적용된 마이그레이션 버전 확인
	currentVersion, err := mm.getCurrentVersion(ctx)
	if err != nil {
		return err
	}

	if currentVersion >= targetVersion {
		return nil
	}

	// 실행할 마이그레이션 목록 생성
	versions := mm.getSortedVersions()
	tx, err := mm.db.BeginTx(ctx, nil)
	if err != nil {
		return fmt.Errorf("트랜잭션 시작 실패: %v", err)
	}
	defer tx.Rollback()

	for _, version := range versions {
		if version <= currentVersion || version > targetVersion {
			continue
		}

		migration := mm.migrations[version]
		log.Printf("마이그레이션 실행 중: %s (버전 %d)", migration.Description, version)

		// 마이그레이션 실행
		if _, err := tx.ExecContext(ctx, migration.UpSQL); err != nil {
			mm.mu.Lock()
			mm.metrics.FailedMigrations++
			mm.mu.Unlock()
			return fmt.Errorf("마이그레이션 실행 실패 (버전 %d): %v", version, err)
		}

		// 마이그레이션 이력 기록
		if err := mm.recordMigration(ctx, tx, migration); err != nil {
			return err
		}

		mm.mu.Lock()
		mm.metrics.SuccessfulMigrations++
		mm.metrics.LastMigrationAt = time.Now()
		mm.mu.Unlock()
	}

	return tx.Commit()
}

// MigrateDown은 지정된 버전까지 롤백을 수행합니다.
func (mm *MigrationManager) MigrateDown(ctx context.Context, targetVersion int64) error {
	currentVersion, err := mm.getCurrentVersion(ctx)
	if err != nil {
		return err
	}

	if currentVersion <= targetVersion {
		return nil
	}

	versions := mm.getSortedVersions()
	sort.Slice(versions, func(i, j int) bool {
		return versions[j] < versions[i]
	})

	tx, err := mm.db.BeginTx(ctx, nil)
	if err != nil {
		return fmt.Errorf("트랜잭션 시작 실패: %v", err)
	}
	defer tx.Rollback()

	for _, version := range versions {
		if version <= targetVersion || version > currentVersion {
			continue
		}

		migration := mm.migrations[version]
		log.Printf("롤백 실행 중: %s (버전 %d)", migration.Description, version)

		// 롤백 실행
		if _, err := tx.ExecContext(ctx, migration.DownSQL); err != nil {
			mm.mu.Lock()
			mm.metrics.FailedMigrations++
			mm.mu.Unlock()
			return fmt.Errorf("롤백 실행 실패 (버전 %d): %v", version, err)
		}

		// 마이그레이션 이력 삭제
		if err := mm.removeMigrationRecord(ctx, tx, version); err != nil {
			return err
		}

		mm.mu.Lock()
		mm.metrics.RollbackCount++
		mm.metrics.LastMigrationAt = time.Now()
		mm.mu.Unlock()
	}

	return tx.Commit()
}

// getCurrentVersion은 현재 적용된 최신 마이그레이션 버전을 반환합니다.
func (mm *MigrationManager) getCurrentVersion(ctx context.Context) (int64, error) {
	var version sql.NullInt64
	err := mm.db.QueryRowContext(ctx,
		"SELECT MAX(version) FROM schema_migrations").Scan(&version)
	if err != nil {
		return 0, fmt.Errorf("현재 버전 조회 실패: %v", err)
	}
	return version.Int64, nil
}

// recordMigration은 마이그레이션 실행 이력을 기록합니다.
func (mm *MigrationManager) recordMigration(ctx context.Context, tx *sql.Tx, migration *Migration) error {
	query := `
		INSERT INTO schema_migrations (version, description, checksum)
		VALUES ($1, $2, $3)
	`
	checksum := calculateChecksum(migration.UpSQL) // 실제로는 더 강력한 체크섬 알고리즘 사용
	_, err := tx.ExecContext(ctx, query, migration.Version, migration.Description, checksum)
	if err != nil {
		return fmt.Errorf("마이그레이션 이력 기록 실패: %v", err)
	}
	return nil
}

// removeMigrationRecord는 마이그레이션 이력을 삭제합니다.
func (mm *MigrationManager) removeMigrationRecord(ctx context.Context, tx *sql.Tx, version int64) error {
	_, err := tx.ExecContext(ctx,
		"DELETE FROM schema_migrations WHERE version = $1", version)
	if err != nil {
		return fmt.Errorf("마이그레이션 이력 삭제 실패: %v", err)
	}
	return nil
}

// getSortedVersions는 마이그레이션 버전을 정렬하여 반환합니다.
func (mm *MigrationManager) getSortedVersions() []int64 {
	mm.mu.RLock()
	defer mm.mu.RUnlock()

	versions := make([]int64, 0, len(mm.migrations))
	for version := range mm.migrations {
		versions = append(versions, version)
	}
	sort.Slice(versions, func(i, j int) bool {
		return versions[i] < versions[j]
	})
	return versions
}

// GetMetrics는 현재 마이그레이션 메트릭을 반환합니다.
func (mm *MigrationManager) GetMetrics() MigrationMetrics {
	mm.mu.RLock()
	defer mm.mu.RUnlock()
	return *mm.metrics
}

// calculateChecksum은 SQL 스크립트의 체크섬을 계산합니다.
func calculateChecksum(sql string) string {
	// 실제 구현에서는 더 강력한 해시 알고리즘 사용
	return fmt.Sprintf("%x", len(strings.TrimSpace(sql)))
}

// Close는 데이터베이스 연결을 정리합니다.
func (mm *MigrationManager) Close() error {
	return mm.db.Close()
}

// RunMigrationPatternsDemo는 마이그레이션 패턴 예제를 실행합니다.
func RunMigrationPatternsDemo() {
	ctx := context.Background()
	connStr := "host=localhost port=5432 user=postgres password=postgres dbname=testdb sslmode=disable"

	mm, err := NewMigrationManager(connStr)
	if err != nil {
		log.Fatalf("MigrationManager 초기화 실패: %v", err)
	}
	defer mm.Close()

	// 마이그레이션 테이블 초기화
	if err := mm.InitializeMigrationTable(ctx); err != nil {
		log.Fatalf("마이그레이션 테이블 초기화 실패: %v", err)
	}

	// 마이그레이션 스크립트 등록
	migrations := []struct {
		version     int64
		description string
		upSQL       string
		downSQL     string
	}{
		{
			version:     20240101,
			description: "사용자 테이블 생성",
			upSQL: `
				CREATE TABLE users (
					id SERIAL PRIMARY KEY,
					username VARCHAR(50) NOT NULL UNIQUE,
					email VARCHAR(255) NOT NULL UNIQUE,
					created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
				)`,
			downSQL: "DROP TABLE users",
		},
		{
			version:     20240102,
			description: "프로필 컬럼 추가",
			upSQL: `
				ALTER TABLE users
				ADD COLUMN profile_image VARCHAR(255),
				ADD COLUMN bio TEXT`,
			downSQL: `
				ALTER TABLE users
				DROP COLUMN profile_image,
				DROP COLUMN bio`,
		},
		{
			version:     20240103,
			description: "인덱스 추가",
			upSQL: `
				CREATE INDEX idx_users_email ON users(email);
				CREATE INDEX idx_users_created_at ON users(created_at)`,
			downSQL: `
				DROP INDEX idx_users_email;
				DROP INDEX idx_users_created_at`,
		},
	}

	for _, m := range migrations {
		if err := mm.RegisterMigration(m.version, m.description, m.upSQL, m.downSQL); err != nil {
			log.Printf("마이그레이션 등록 실패: %v", err)
			continue
		}
	}

	// 마이그레이션 실행
	targetVersion := int64(20240103)
	if err := mm.MigrateUp(ctx, targetVersion); err != nil {
		log.Printf("마이그레이션 업 실패: %v", err)
	}

	// 일부 롤백 실행
	rollbackVersion := int64(20240101)
	if err := mm.MigrateDown(ctx, rollbackVersion); err != nil {
		log.Printf("마이그레이션 다운 실패: %v", err)
	}

	// 메트릭스 출력
	metrics := mm.GetMetrics()
	log.Printf("\n마이그레이션 메트릭스:\n"+
		"총 마이그레이션: %d\n"+
		"성공한 마이그레이션: %d\n"+
		"실패한 마이그레이션: %d\n"+
		"롤백 횟수: %d\n"+
		"마지막 마이그레이션 시간: %v",
		metrics.TotalMigrations,
		metrics.SuccessfulMigrations,
		metrics.FailedMigrations,
		metrics.RollbackCount,
		metrics.LastMigrationAt)
}
