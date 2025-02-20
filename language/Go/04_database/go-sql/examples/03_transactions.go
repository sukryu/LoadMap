package examples

import (
	"context"
	"database/sql"
	"fmt"
	"log"
	"sync"
	"time"

	_ "github.com/lib/pq"
)

// TransactionManager는 데이터베이스 트랜잭션을 관리하는 구조체입니다.
type TransactionManager struct {
	db             *sql.DB
	isolationLevel sql.IsolationLevel
	metrics        *TransactionMetrics
	mu             sync.RWMutex
}

// TransactionMetrics는 트랜잭션 실행에 대한 메트릭을 추적합니다.
type TransactionMetrics struct {
	TotalTransactions int64
	CommittedTx       int64
	RolledBackTx      int64
	TotalDuration     time.Duration
	DeadlockCount     int64
	RetryCount        int64
}

// BankAccount는 은행 계좌 정보를 나타내는 구조체입니다.
type BankAccount struct {
	ID        int
	AccountNo string
	Balance   float64
	Version   int // 낙관적 잠금을 위한 버전
}

// NewTransactionManager는 새로운 TransactionManager를 생성합니다.
func NewTransactionManager(connStr string) (*TransactionManager, error) {
	db, err := sql.Open("postgres", connStr)
	if err != nil {
		return nil, fmt.Errorf("데이터베이스 연결 실패: %v", err)
	}

	return &TransactionManager{
		db:             db,
		isolationLevel: sql.LevelSerializable,
		metrics:        &TransactionMetrics{},
	}, nil
}

// InitializeBankSchema는 은행 관련 테이블을 초기화합니다.
func (tm *TransactionManager) InitializeBankSchema(ctx context.Context) error {
	queries := []string{
		`DROP TABLE IF EXISTS transactions`,
		`DROP TABLE IF EXISTS accounts`,
		`CREATE TABLE accounts (
			id SERIAL PRIMARY KEY,
			account_no VARCHAR(20) UNIQUE NOT NULL,
			balance DECIMAL(15,2) NOT NULL,
			version INTEGER NOT NULL DEFAULT 1
		)`,
		`CREATE TABLE transactions (
			id SERIAL PRIMARY KEY,
			from_account_id INTEGER REFERENCES accounts(id),
			to_account_id INTEGER REFERENCES accounts(id),
			amount DECIMAL(15,2) NOT NULL,
			transaction_time TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
		)`,
	}

	tx, err := tm.db.BeginTx(ctx, &sql.TxOptions{Isolation: tm.isolationLevel})
	if err != nil {
		return fmt.Errorf("트랜잭션 시작 실패: %v", err)
	}
	defer tx.Rollback()

	for _, query := range queries {
		if _, err := tx.ExecContext(ctx, query); err != nil {
			return fmt.Errorf("스키마 초기화 실패: %v", err)
		}
	}

	return tx.Commit()
}

// CreateAccount는 새로운 은행 계좌를 생성합니다.
func (tm *TransactionManager) CreateAccount(ctx context.Context, accountNo string, initialBalance float64) (*BankAccount, error) {
	start := time.Now()
	defer func() {
		tm.mu.Lock()
		tm.metrics.TotalTransactions++
		tm.metrics.TotalDuration += time.Since(start)
		tm.mu.Unlock()
	}()

	tx, err := tm.db.BeginTx(ctx, &sql.TxOptions{Isolation: tm.isolationLevel})
	if err != nil {
		return nil, fmt.Errorf("트랜잭션 시작 실패: %v", err)
	}
	defer tx.Rollback()

	account := &BankAccount{
		AccountNo: accountNo,
		Balance:   initialBalance,
		Version:   1,
	}

	query := `
		INSERT INTO accounts (account_no, balance, version)
		VALUES ($1, $2, $3)
		RETURNING id
	`
	err = tx.QueryRowContext(ctx, query, account.AccountNo, account.Balance, account.Version).Scan(&account.ID)
	if err != nil {
		return nil, fmt.Errorf("계좌 생성 실패: %v", err)
	}

	if err := tx.Commit(); err != nil {
		return nil, fmt.Errorf("트랜잭션 커밋 실패: %v", err)
	}

	tm.mu.Lock()
	tm.metrics.CommittedTx++
	tm.mu.Unlock()

	return account, nil
}

// TransferMoney는 계좌 간 송금을 처리합니다.
func (tm *TransactionManager) TransferMoney(ctx context.Context, fromAccNo, toAccNo string, amount float64) error {
	maxRetries := 3
	var lastErr error

	for attempt := 0; attempt < maxRetries; attempt++ {
		if err := tm.executeTransfer(ctx, fromAccNo, toAccNo, amount); err != nil {
			lastErr = err
			tm.mu.Lock()
			tm.metrics.RetryCount++
			tm.mu.Unlock()

			if attempt < maxRetries-1 {
				time.Sleep(time.Duration(attempt+1) * 100 * time.Millisecond)
				continue
			}
			return fmt.Errorf("송금 실패 (최대 재시도 횟수 초과): %v", err)
		}
		return nil
	}

	return lastErr
}

// executeTransfer는 실제 송금 트랜잭션을 실행합니다.
func (tm *TransactionManager) executeTransfer(ctx context.Context, fromAccNo, toAccNo string, amount float64) error {
	start := time.Now()
	defer func() {
		tm.mu.Lock()
		tm.metrics.TotalTransactions++
		tm.metrics.TotalDuration += time.Since(start)
		tm.mu.Unlock()
	}()

	tx, err := tm.db.BeginTx(ctx, &sql.TxOptions{Isolation: tm.isolationLevel})
	if err != nil {
		return fmt.Errorf("트랜잭션 시작 실패: %v", err)
	}
	defer tx.Rollback()

	// 송금 계좌 조회 및 잠금
	var fromAcc BankAccount
	query := `
		SELECT id, balance, version 
		FROM accounts 
		WHERE account_no = $1 
		FOR UPDATE
	`
	err = tx.QueryRowContext(ctx, query, fromAccNo).Scan(&fromAcc.ID, &fromAcc.Balance, &fromAcc.Version)
	if err != nil {
		return fmt.Errorf("송금 계좌 조회 실패: %v", err)
	}

	// 잔액 확인
	if fromAcc.Balance < amount {
		tm.mu.Lock()
		tm.metrics.RolledBackTx++
		tm.mu.Unlock()
		return fmt.Errorf("잔액 부족: 현재 잔액 %.2f, 필요 금액 %.2f", fromAcc.Balance, amount)
	}

	// 수취 계좌 조회 및 잠금
	var toAcc BankAccount
	err = tx.QueryRowContext(ctx, query, toAccNo).Scan(&toAcc.ID, &toAcc.Balance, &toAcc.Version)
	if err != nil {
		return fmt.Errorf("수취 계좌 조회 실패: %v", err)
	}

	// 송금 계좌에서 금액 차감
	updateQuery := `
		UPDATE accounts 
		SET balance = balance - $1, version = version + 1
		WHERE id = $2 AND version = $3
	`
	result, err := tx.ExecContext(ctx, updateQuery, amount, fromAcc.ID, fromAcc.Version)
	if err != nil {
		return fmt.Errorf("송금 계좌 업데이트 실패: %v", err)
	}

	rows, err := result.RowsAffected()
	if err != nil {
		return fmt.Errorf("영향받은 행 확인 실패: %v", err)
	}
	if rows != 1 {
		return fmt.Errorf("낙관적 잠금 충돌 발생")
	}

	// 수취 계좌에 금액 추가
	updateQuery = `
		UPDATE accounts 
		SET balance = balance + $1, version = version + 1
		WHERE id = $2 AND version = $3
	`
	result, err = tx.ExecContext(ctx, updateQuery, amount, toAcc.ID, toAcc.Version)
	if err != nil {
		return fmt.Errorf("수취 계좌 업데이트 실패: %v", err)
	}

	rows, err = result.RowsAffected()
	if err != nil {
		return fmt.Errorf("영향받은 행 확인 실패: %v", err)
	}
	if rows != 1 {
		return fmt.Errorf("낙관적 잠금 충돌 발생")
	}

	// 거래 내역 기록
	logQuery := `
		INSERT INTO transactions (from_account_id, to_account_id, amount)
		VALUES ($1, $2, $3)
	`
	_, err = tx.ExecContext(ctx, logQuery, fromAcc.ID, toAcc.ID, amount)
	if err != nil {
		return fmt.Errorf("거래 내역 기록 실패: %v", err)
	}

	// 트랜잭션 커밋
	if err := tx.Commit(); err != nil {
		tm.mu.Lock()
		tm.metrics.RolledBackTx++
		tm.mu.Unlock()
		return fmt.Errorf("트랜잭션 커밋 실패: %v", err)
	}

	tm.mu.Lock()
	tm.metrics.CommittedTx++
	tm.mu.Unlock()

	return nil
}

// GetAccountBalance는 계좌 잔액을 조회합니다.
func (tm *TransactionManager) GetAccountBalance(ctx context.Context, accountNo string) (float64, error) {
	query := "SELECT balance FROM accounts WHERE account_no = $1"
	var balance float64
	err := tm.db.QueryRowContext(ctx, query, accountNo).Scan(&balance)
	if err != nil {
		return 0, fmt.Errorf("잔액 조회 실패: %v", err)
	}
	return balance, nil
}

// GetMetrics는 현재 트랜잭션 메트릭을 반환합니다.
func (tm *TransactionManager) GetMetrics() TransactionMetrics {
	tm.mu.RLock()
	defer tm.mu.RUnlock()
	return *tm.metrics
}

// Close는 데이터베이스 연결을 정리합니다.
func (tm *TransactionManager) Close() error {
	return tm.db.Close()
}

// RunTransactionsDemo는 트랜잭션 예제를 실행합니다.
func RunTransactionsDemo() {
	ctx := context.Background()
	connStr := "host=localhost port=5432 user=postgres password=postgres dbname=testdb sslmode=disable"

	tm, err := NewTransactionManager(connStr)
	if err != nil {
		log.Fatalf("TransactionManager 초기화 실패: %v", err)
	}
	defer tm.Close()

	// 스키마 초기화
	if err := tm.InitializeBankSchema(ctx); err != nil {
		log.Fatalf("스키마 초기화 실패: %v", err)
	}

	// 테스트 계좌 생성
	acc1, err := tm.CreateAccount(ctx, "ACC001", 1000.0)
	if err != nil {
		log.Printf("계좌1 생성 실패: %v", err)
	}

	log.Printf("ACC1 ID: %d\n", acc1.ID)

	acc2, err := tm.CreateAccount(ctx, "ACC002", 500.0)
	if err != nil {
		log.Printf("계좌2 생성 실패: %v", err)
	}

	log.Printf("ACC2 ID: %d\n", acc2.ID)

	// 송금 테스트
	if err := tm.TransferMoney(ctx, "ACC001", "ACC002", 300.0); err != nil {
		log.Printf("송금 실패: %v", err)
	}

	// 잔액 확인
	balance1, err := tm.GetAccountBalance(ctx, "ACC001")
	if err != nil {
		log.Printf("잔액 조회 실패 (ACC001): %v", err)
	}
	balance2, err := tm.GetAccountBalance(ctx, "ACC002")
	if err != nil {
		log.Printf("잔액 조회 실패 (ACC002): %v", err)
	}

	log.Printf("계좌 잔액 - ACC001: %.2f, ACC002: %.2f", balance1, balance2)

	// 메트릭스 출력
	metrics := tm.GetMetrics()
	log.Printf("트랜잭션 메트릭스:\n"+
		"총 트랜잭션: %d\n"+
		"커밋된 트랜잭션: %d\n"+
		"롤백된 트랜잭션: %d\n"+
		"총 실행 시간: %v\n"+
		"재시도 횟수: %d\n"+
		"데드락 발생 횟수: %d",
		metrics.TotalTransactions,
		metrics.CommittedTx,
		metrics.RolledBackTx,
		metrics.TotalDuration,
		metrics.RetryCount,
		metrics.DeadlockCount)
}
