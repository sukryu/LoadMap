// main.go
package main

import (
	"context"
	"database/sql"
	"fmt"
	"log"
	"time"

	_ "github.com/lib/pq" // PostgreSQL 드라이버를 익명으로 임포트합니다.
)

// User 구조체는 데이터베이스의 users 테이블과 매핑됩니다.
type User struct {
	ID        int       `db:"id"`         // 사용자 고유 식별자
	Username  string    `db:"username"`   // 사용자명
	Email     string    `db:"email"`      // 이메일 주소
	CreatedAt time.Time `db:"created_at"` // 계정 생성일
}

// Database 구조체는 데이터베이스 연결과 관련된 설정을 포함합니다.
type Database struct {
	db *sql.DB
}

// NewDatabase는 새로운 데이터베이스 연결을 생성하고 초기화합니다.
func NewDatabase(connStr string) (*Database, error) {
	// sql.Open은 실제로 연결을 수립하지 않습니다.
	// 대신 database/sql 패키지에 대한 설정을 초기화합니다.
	db, err := sql.Open("postgres", connStr)
	if err != nil {
		return nil, fmt.Errorf("데이터베이스 연결 초기화 실패: %v", err)
	}

	// 데이터베이스 연결 설정을 구성합니다.
	db.SetMaxOpenConns(25)                 // 최대 동시 연결 수
	db.SetMaxIdleConns(25)                 // 유휴 연결 풀 크기
	db.SetConnMaxLifetime(5 * time.Minute) // 연결 최대 수명

	// 실제 연결이 가능한지 확인합니다.
	if err := db.Ping(); err != nil {
		return nil, fmt.Errorf("데이터베이스 연결 확인 실패: %v", err)
	}

	return &Database{db: db}, nil
}

// CreateUsersTable은 users 테이블을 생성합니다.
func (d *Database) CreateUsersTable(ctx context.Context) error {
	// heredoc 문법을 사용하여 SQL 쿼리를 가독성 있게 작성합니다.
	query := `
		CREATE TABLE IF NOT EXISTS users (
			id SERIAL PRIMARY KEY,
			username VARCHAR(50) NOT NULL UNIQUE,
			email VARCHAR(255) NOT NULL UNIQUE,
			created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
		)
	`

	// ExecContext를 사용하여 쿼리를 실행하고 컨텍스트를 통한 취소/타임아웃을 지원합니다.
	_, err := d.db.ExecContext(ctx, query)
	if err != nil {
		return fmt.Errorf("테이블 생성 실패: %v", err)
	}

	return nil
}

// CreateUser는 새로운 사용자를 데이터베이스에 추가합니다.
func (d *Database) CreateUser(ctx context.Context, username, email string) error {
	// Prepared Statement를 사용하여 SQL 인젝션을 방지합니다.
	query := `
		INSERT INTO users (username, email)
		VALUES ($1, $2)
		RETURNING id
	`

	// QueryRowContext를 사용하여 단일 행을 반환하는 쿼리를 실행합니다.
	var id int
	err := d.db.QueryRowContext(ctx, query, username, email).Scan(&id)
	if err != nil {
		return fmt.Errorf("사용자 생성 실패: %v", err)
	}

	log.Printf("새로운 사용자가 생성되었습니다. ID: %d", id)
	return nil
}

// GetUser는 사용자명으로 사용자 정보를 조회합니다.
func (d *Database) GetUser(ctx context.Context, username string) (*User, error) {
	query := `
		SELECT id, username, email, created_at
		FROM users
		WHERE username = $1
	`

	user := &User{}
	err := d.db.QueryRowContext(ctx, query, username).Scan(
		&user.ID,
		&user.Username,
		&user.Email,
		&user.CreatedAt,
	)

	if err == sql.ErrNoRows {
		return nil, fmt.Errorf("사용자를 찾을 수 없습니다: %s", username)
	}
	if err != nil {
		return nil, fmt.Errorf("사용자 조회 실패: %v", err)
	}

	return user, nil
}

// UpdateUserEmail은 트랜잭션을 사용하여 사용자의 이메일을 안전하게 업데이트합니다.
func (d *Database) UpdateUserEmail(ctx context.Context, username, newEmail string) error {
	// 트랜잭션을 시작합니다.
	tx, err := d.db.BeginTx(ctx, nil)
	if err != nil {
		return fmt.Errorf("트랜잭션 시작 실패: %v", err)
	}

	// 함수 종료 시 트랜잭션을 롤백하거나 커밋합니다.
	defer func() {
		if err != nil {
			tx.Rollback()
			return
		}
	}()

	// 사용자가 존재하는지 확인합니다.
	query := "SELECT id FROM users WHERE username = $1"
	var id int
	err = tx.QueryRowContext(ctx, query, username).Scan(&id)
	if err == sql.ErrNoRows {
		return fmt.Errorf("사용자를 찾을 수 없습니다: %s", username)
	}
	if err != nil {
		return fmt.Errorf("사용자 확인 실패: %v", err)
	}

	// 이메일을 업데이트합니다.
	updateQuery := "UPDATE users SET email = $1 WHERE username = $2"
	result, err := tx.ExecContext(ctx, updateQuery, newEmail, username)
	if err != nil {
		return fmt.Errorf("이메일 업데이트 실패: %v", err)
	}

	// 영향받은 행의 수를 확인합니다.
	rows, err := result.RowsAffected()
	if err != nil {
		return fmt.Errorf("영향받은 행 확인 실패: %v", err)
	}
	if rows != 1 {
		return fmt.Errorf("예상치 못한 업데이트 행 수: %d", rows)
	}

	// 트랜잭션을 커밋합니다.
	if err = tx.Commit(); err != nil {
		return fmt.Errorf("트랜잭션 커밋 실패: %v", err)
	}

	return nil
}

// Close는 데이터베이스 연결을 정리합니다.
func (d *Database) Close() error {
	return d.db.Close()
}

func main() {
	// 컨텍스트를 생성하고 타임아웃을 설정합니다.
	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	// 데이터베이스 연결 문자열을 설정합니다.
	// 실제 환경에서는 환경 변수나 설정 파일에서 이 정보를 가져와야 합니다.
	connStr := "host=localhost port=5432 user=postgres password=postgres dbname=testdb sslmode=disable"

	// 데이터베이스 연결을 초기화합니다.
	db, err := NewDatabase(connStr)
	if err != nil {
		log.Fatalf("데이터베이스 초기화 실패: %v", err)
	}
	defer db.Close()

	// users 테이블을 생성합니다.
	if err := db.CreateUsersTable(ctx); err != nil {
		log.Fatalf("테이블 생성 실패: %v", err)
	}

	// 새로운 사용자를 생성합니다.
	if err := db.CreateUser(ctx, "gopher", "gopher@example.com"); err != nil {
		log.Printf("사용자 생성 실패: %v", err)
	}

	// 사용자 정보를 조회합니다.
	user, err := db.GetUser(ctx, "gopher")
	if err != nil {
		log.Printf("사용자 조회 실패: %v", err)
	} else {
		log.Printf("조회된 사용자: ID=%d, Username=%s, Email=%s, CreatedAt=%v",
			user.ID, user.Username, user.Email, user.CreatedAt)
	}

	// 사용자의 이메일을 업데이트합니다.
	if err := db.UpdateUserEmail(ctx, "gopher", "updated@example.com"); err != nil {
		log.Printf("이메일 업데이트 실패: %v", err)
	}

	log.Println("프로그램이 성공적으로 완료되었습니다.")
}
