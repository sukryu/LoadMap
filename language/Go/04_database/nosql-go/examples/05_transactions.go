package examples

import (
	"context"
	"fmt"
	"log"
	"time"

	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/bson/primitive"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
	"go.mongodb.org/mongo-driver/mongo/readpref"
	"go.mongodb.org/mongo-driver/mongo/writeconcern"
)

// BankAccount represents a bank account in the system
type BankAccount struct {
	ID            primitive.ObjectID `bson:"_id,omitempty"`
	AccountNumber string             `bson:"account_number"`
	OwnerName     string             `bson:"owner_name"`
	Balance       float64            `bson:"balance"`
	Currency      string             `bson:"currency"`
	Status        string             `bson:"status"`
	LastUpdated   time.Time          `bson:"last_updated"`
}

// TransactionRecord represents a financial transaction record
type TransactionRecord struct {
	ID              primitive.ObjectID     `bson:"_id,omitempty"`
	TransactionType string                 `bson:"transaction_type"`
	FromAccount     string                 `bson:"from_account"`
	ToAccount       string                 `bson:"to_account"`
	Amount          float64                `bson:"amount"`
	Currency        string                 `bson:"currency"`
	Status          string                 `bson:"status"`
	Timestamp       time.Time              `bson:"timestamp"`
	MetaData        map[string]interface{} `bson:"metadata,omitempty"`
}

// BankingOperations handles financial transactions with MongoDB
type BankingOperations struct {
	client                 *mongo.Client
	accountsCollection     *mongo.Collection
	transactionsCollection *mongo.Collection
}

// NewBankingOperations initializes a new banking operations manager
func NewBankingOperations(ctx context.Context) (*BankingOperations, error) {
	// WriteConcern 구조체 리터럴을 직접 생성합니다.
	wc := &writeconcern.WriteConcern{
		W: "majority",
	}

	clientOptions := options.Client().
		ApplyURI("mongodb://localhost:27017").
		SetReadPreference(readpref.Primary()).
		SetWriteConcern(wc)

	client, err := mongo.Connect(ctx, clientOptions)
	if err != nil {
		return nil, fmt.Errorf("MongoDB 연결 실패: %v", err)
	}

	// 연결 확인
	if err = client.Ping(ctx, nil); err != nil {
		return nil, fmt.Errorf("MongoDB 연결 확인 실패: %v", err)
	}

	return &BankingOperations{
		client:                 client,
		accountsCollection:     client.Database("banking").Collection("accounts"),
		transactionsCollection: client.Database("banking").Collection("transactions"),
	}, nil
}

// TransferMoney performs a money transfer between two accounts using a transaction
func (bo *BankingOperations) TransferMoney(ctx context.Context, fromAccNum, toAccNum string, amount float64) error {
	// 세션 시작
	session, err := bo.client.StartSession()
	if err != nil {
		return fmt.Errorf("세션 시작 실패: %v", err)
	}
	defer session.EndSession(ctx)

	// 트랜잭션 콜백 정의
	callback := func(sessionContext mongo.SessionContext) (interface{}, error) {
		// 출금 계좌 확인
		var fromAccount BankAccount
		err := bo.accountsCollection.FindOne(sessionContext, bson.D{
			{Key: "account_number", Value: fromAccNum},
			{Key: "status", Value: "active"},
		}).Decode(&fromAccount)
		if err != nil {
			return nil, fmt.Errorf("출금 계좌 조회 실패: %v", err)
		}

		// 잔액 확인
		if fromAccount.Balance < amount {
			return nil, fmt.Errorf("잔액 부족: 현재 잔액 %.2f, 필요 금액 %.2f", fromAccount.Balance, amount)
		}

		// 입금 계좌 확인
		var toAccount BankAccount
		err = bo.accountsCollection.FindOne(sessionContext, bson.D{
			{Key: "account_number", Value: toAccNum},
			{Key: "status", Value: "active"},
		}).Decode(&toAccount)
		if err != nil {
			return nil, fmt.Errorf("입금 계좌 조회 실패: %v", err)
		}

		// 출금 계좌 업데이트
		_, err = bo.accountsCollection.UpdateOne(
			sessionContext,
			bson.D{{Key: "_id", Value: fromAccount.ID}},
			bson.D{
				{Key: "$set", Value: bson.D{
					{Key: "balance", Value: fromAccount.Balance - amount},
					{Key: "last_updated", Value: time.Now()},
				}},
			},
		)
		if err != nil {
			return nil, fmt.Errorf("출금 계좌 업데이트 실패: %v", err)
		}

		// 입금 계좌 업데이트
		_, err = bo.accountsCollection.UpdateOne(
			sessionContext,
			bson.D{{Key: "_id", Value: toAccount.ID}},
			bson.D{
				{Key: "$set", Value: bson.D{
					{Key: "balance", Value: toAccount.Balance + amount},
					{Key: "last_updated", Value: time.Now()},
				}},
			},
		)
		if err != nil {
			return nil, fmt.Errorf("입금 계좌 업데이트 실패: %v", err)
		}

		// 거래 기록 생성
		transactionRecord := TransactionRecord{
			TransactionType: "transfer",
			FromAccount:     fromAccNum,
			ToAccount:       toAccNum,
			Amount:          amount,
			Currency:        fromAccount.Currency,
			Status:          "completed",
			Timestamp:       time.Now(),
			MetaData: map[string]interface{}{
				"from_owner": fromAccount.OwnerName,
				"to_owner":   toAccount.OwnerName,
			},
		}

		_, err = bo.transactionsCollection.InsertOne(sessionContext, transactionRecord)
		if err != nil {
			return nil, fmt.Errorf("거래 기록 생성 실패: %v", err)
		}

		return nil, nil
	}

	// 트랜잭션 실행
	_, err = session.WithTransaction(ctx, callback)
	if err != nil {
		return fmt.Errorf("트랜잭션 실패: %v", err)
	}

	return nil
}

// CreateAccount creates a new bank account
func (bo *BankingOperations) CreateAccount(ctx context.Context, account *BankAccount) error {
	account.ID = primitive.NewObjectID()
	account.LastUpdated = time.Now()
	account.Status = "active"

	_, err := bo.accountsCollection.InsertOne(ctx, account)
	if err != nil {
		return fmt.Errorf("계좌 생성 실패: %v", err)
	}

	return nil
}

// GetAccountBalance retrieves the current balance of an account
func (bo *BankingOperations) GetAccountBalance(ctx context.Context, accountNumber string) (float64, error) {
	var account BankAccount
	err := bo.accountsCollection.FindOne(ctx, bson.D{
		{Key: "account_number", Value: accountNumber},
		{Key: "status", Value: "active"},
	}).Decode(&account)

	if err != nil {
		if err == mongo.ErrNoDocuments {
			return 0, fmt.Errorf("계좌를 찾을 수 없음: %s", accountNumber)
		}
		return 0, fmt.Errorf("계좌 조회 실패: %v", err)
	}

	return account.Balance, nil
}

// GetTransactionHistory retrieves the transaction history for an account
func (bo *BankingOperations) GetTransactionHistory(ctx context.Context, accountNumber string) ([]TransactionRecord, error) {
	filter := bson.D{
		{Key: "$or", Value: bson.A{
			bson.D{{Key: "from_account", Value: accountNumber}},
			bson.D{{Key: "to_account", Value: accountNumber}},
		}},
	}

	cursor, err := bo.transactionsCollection.Find(ctx, filter, options.Find().SetSort(bson.D{{Key: "timestamp", Value: -1}}))
	if err != nil {
		return nil, fmt.Errorf("거래 내역 조회 실패: %v", err)
	}
	defer cursor.Close(ctx)

	var transactions []TransactionRecord
	if err = cursor.All(ctx, &transactions); err != nil {
		return nil, fmt.Errorf("거래 내역 디코딩 실패: %v", err)
	}

	return transactions, nil
}

// Cleanup performs cleanup operations
func (bo *BankingOperations) Cleanup(ctx context.Context) error {
	if bo.client != nil {
		if err := bo.client.Disconnect(ctx); err != nil {
			return fmt.Errorf("MongoDB 연결 종료 실패: %v", err)
		}
	}
	return nil
}

// ExampleTransactions demonstrates the usage of MongoDB transactions
func ExampleTransactions() {
	ctx := context.Background()

	// 뱅킹 시스템 초기화
	bankingOps, err := NewBankingOperations(ctx)
	if err != nil {
		log.Fatalf("뱅킹 시스템 초기화 실패: %v", err)
	}
	defer bankingOps.Cleanup(ctx)

	// 테스트 계좌 생성
	accounts := []*BankAccount{
		{
			AccountNumber: "ACC001",
			OwnerName:     "John Doe",
			Balance:       1000.00,
			Currency:      "USD",
		},
		{
			AccountNumber: "ACC002",
			OwnerName:     "Jane Smith",
			Balance:       500.00,
			Currency:      "USD",
		},
	}

	for _, account := range accounts {
		if err := bankingOps.CreateAccount(ctx, account); err != nil {
			log.Printf("계좌 생성 실패: %v", err)
			continue
		}
		log.Printf("계좌 생성됨: %s (소유자: %s)", account.AccountNumber, account.OwnerName)
	}

	// 송금 테스트
	transferAmount := 200.00
	err = bankingOps.TransferMoney(ctx, "ACC001", "ACC002", transferAmount)
	if err != nil {
		log.Printf("송금 실패: %v", err)
	} else {
		log.Printf("%.2f USD가 ACC001에서 ACC002로 성공적으로 이체됨", transferAmount)
	}

	// 계좌 잔액 확인
	for _, accNum := range []string{"ACC001", "ACC002"} {
		balance, err := bankingOps.GetAccountBalance(ctx, accNum)
		if err != nil {
			log.Printf("잔액 조회 실패 (%s): %v", accNum, err)
			continue
		}
		log.Printf("계좌 %s의 현재 잔액: %.2f USD", accNum, balance)
	}

	// 거래 내역 조회
	transactions, err := bankingOps.GetTransactionHistory(ctx, "ACC001")
	if err != nil {
		log.Printf("거래 내역 조회 실패: %v", err)
	} else {
		log.Printf("ACC001의 거래 내역:")
		for _, tx := range transactions {
			log.Printf("- %s: %.2f USD (%s -> %s)",
				tx.TransactionType, tx.Amount, tx.FromAccount, tx.ToAccount)
		}
	}
}
