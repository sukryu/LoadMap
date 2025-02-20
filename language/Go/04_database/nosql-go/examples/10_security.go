package examples

import (
	"context"
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/json"
	"fmt"
	"io"
	"log"
	"time"

	"github.com/go-redis/redis/v8"
	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
)

// SecurityEvent represents a security-related event log
type SecurityEvent struct {
	Timestamp    time.Time              `bson:"timestamp"`
	EventType    string                 `bson:"event_type"`
	UserID       string                 `bson:"user_id"`
	Action       string                 `bson:"action"`
	ResourceType string                 `bson:"resource_type"`
	ResourceID   string                 `bson:"resource_id"`
	Status       string                 `bson:"status"`
	IPAddress    string                 `bson:"ip_address"`
	Metadata     map[string]interface{} `bson:"metadata,omitempty"`
}

// AccessPolicy defines access control rules
type AccessPolicy struct {
	RoleID      string    `bson:"role_id"`
	Permissions []string  `bson:"permissions"`
	Resources   []string  `bson:"resources"`
	AllowedIPs  []string  `bson:"allowed_ips,omitempty"`
	ValidUntil  time.Time `bson:"valid_until"`
}

// EncryptedData represents encrypted sensitive data
type EncryptedData struct {
	Data      []byte    `bson:"data"`
	Nonce     []byte    `bson:"nonce"`
	CreatedAt time.Time `bson:"created_at"`
	UpdatedAt time.Time `bson:"updated_at"`
}

// SecurityManager handles security-related operations
type SecurityManager struct {
	mongoClient    *mongo.Client
	redisClient    *redis.Client
	auditLog       *mongo.Collection
	accessPolicies *mongo.Collection
	encryptedData  *mongo.Collection
	encryptionKey  []byte
}

// NewSecurityManager initializes a new security manager
func NewSecurityManager(ctx context.Context, encryptionKey []byte) (*SecurityManager, error) {
	// MongoDB 클라이언트 초기화
	mongoOpts := options.Client().ApplyURI("mongodb://localhost:27017").
		SetAuth(options.Credential{
			Username: "admin",
			Password: "secure_password",
		})

	mongoClient, err := mongo.Connect(ctx, mongoOpts)
	if err != nil {
		return nil, fmt.Errorf("MongoDB 연결 실패: %v", err)
	}

	// Redis 클라이언트 초기화 (TLS 설정 포함)
	redisOpts := &redis.Options{
		Addr:      "localhost:6379",
		Password:  "secure_redis_password",
		DB:        0,
		TLSConfig: nil, // 실제 환경에서는 TLS 설정 필요
	}
	redisClient := redis.NewClient(redisOpts)

	manager := &SecurityManager{
		mongoClient:    mongoClient,
		redisClient:    redisClient,
		auditLog:       mongoClient.Database("security").Collection("audit_log"),
		accessPolicies: mongoClient.Database("security").Collection("access_policies"),
		encryptedData:  mongoClient.Database("security").Collection("encrypted_data"),
		encryptionKey:  encryptionKey,
	}

	// 보안 인덱스 생성
	if err := manager.createSecurityIndexes(ctx); err != nil {
		return nil, err
	}

	return manager, nil
}

// createSecurityIndexes creates necessary indexes for security collections
func (sm *SecurityManager) createSecurityIndexes(ctx context.Context) error {
	// 감사 로그 인덱스
	auditIndexes := []mongo.IndexModel{
		{
			Keys: bson.D{
				{Key: "timestamp", Value: -1},
				{Key: "event_type", Value: 1},
			},
		},
		{
			Keys: bson.D{
				{Key: "user_id", Value: 1},
				{Key: "timestamp", Value: -1},
			},
		},
	}

	// 접근 정책 인덱스
	policyIndexes := []mongo.IndexModel{
		{
			Keys: bson.D{
				{Key: "role_id", Value: 1},
			},
			Options: options.Index().SetUnique(true),
		},
	}

	// 인덱스 생성
	if _, err := sm.auditLog.Indexes().CreateMany(ctx, auditIndexes); err != nil {
		return fmt.Errorf("감사 로그 인덱스 생성 실패: %v", err)
	}

	if _, err := sm.accessPolicies.Indexes().CreateMany(ctx, policyIndexes); err != nil {
		return fmt.Errorf("접근 정책 인덱스 생성 실패: %v", err)
	}

	return nil
}

// LogSecurityEvent records a security event in the audit log
func (sm *SecurityManager) LogSecurityEvent(ctx context.Context, event *SecurityEvent) error {
	event.Timestamp = time.Now()

	_, err := sm.auditLog.InsertOne(ctx, event)
	if err != nil {
		return fmt.Errorf("보안 이벤트 기록 실패: %v", err)
	}

	// 중요 이벤트의 경우 Redis에 캐시하여 실시간 모니터링 지원
	if isHighPriorityEvent(event.EventType) {
		eventJSON, _ := json.Marshal(event)
		cacheKey := fmt.Sprintf("security_event:%s:%s", event.EventType, event.Timestamp.Format(time.RFC3339))
		err = sm.redisClient.Set(ctx, cacheKey, eventJSON, 24*time.Hour).Err()
		if err != nil {
			log.Printf("보안 이벤트 캐시 실패: %v", err)
		}
	}

	return nil
}

// CreateAccessPolicy creates a new access policy
func (sm *SecurityManager) CreateAccessPolicy(ctx context.Context, policy *AccessPolicy) error {
	if policy.ValidUntil.Before(time.Now()) {
		return fmt.Errorf("유효 기간이 이미 만료됨")
	}

	_, err := sm.accessPolicies.InsertOne(ctx, policy)
	if err != nil {
		return fmt.Errorf("접근 정책 생성 실패: %v", err)
	}

	// Redis에 정책 캐시
	policyJSON, _ := json.Marshal(policy)
	cacheKey := fmt.Sprintf("access_policy:%s", policy.RoleID)
	err = sm.redisClient.Set(ctx, cacheKey, policyJSON, time.Until(policy.ValidUntil)).Err()
	if err != nil {
		log.Printf("정책 캐시 실패: %v", err)
	}

	return nil
}

// CheckAccess verifies if an access is allowed based on policies
func (sm *SecurityManager) CheckAccess(ctx context.Context, userID, roleID, resource, action, ip string) (bool, error) {
	// Redis 캐시에서 정책 확인
	cacheKey := fmt.Sprintf("access_policy:%s", roleID)
	cachedPolicy, err := sm.redisClient.Get(ctx, cacheKey).Result()
	if err == nil {
		var policy AccessPolicy
		if err := json.Unmarshal([]byte(cachedPolicy), &policy); err == nil {
			return sm.evaluatePolicy(&policy, resource, action, ip)
		}
	}

	// MongoDB에서 정책 조회
	var policy AccessPolicy
	err = sm.accessPolicies.FindOne(ctx, bson.D{{Key: "role_id", Value: roleID}}).Decode(&policy)
	if err != nil {
		if err == mongo.ErrNoDocuments {
			return false, nil
		}
		return false, fmt.Errorf("정책 조회 실패: %v", err)
	}

	// 접근 검증 결과 기록
	sm.LogSecurityEvent(ctx, &SecurityEvent{
		EventType:    "access_check",
		UserID:       userID,
		Action:       action,
		ResourceType: resource,
		Status:       "checked",
		IPAddress:    ip,
		Metadata: map[string]interface{}{
			"role_id": roleID,
		},
	})

	return sm.evaluatePolicy(&policy, resource, action, ip)
}

// evaluatePolicy checks if the access is allowed based on a specific policy
func (sm *SecurityManager) evaluatePolicy(policy *AccessPolicy, resource, action, ip string) (bool, error) {
	// 정책 만료 확인
	if policy.ValidUntil.Before(time.Now()) {
		return false, nil
	}

	// IP 제한 확인
	if len(policy.AllowedIPs) > 0 {
		ipAllowed := false
		for _, allowedIP := range policy.AllowedIPs {
			if allowedIP == ip {
				ipAllowed = true
				break
			}
		}
		if !ipAllowed {
			return false, nil
		}
	}

	// 리소스 및 권한 확인
	resourceAllowed := false
	for _, r := range policy.Resources {
		if r == resource || r == "*" {
			resourceAllowed = true
			break
		}
	}

	if !resourceAllowed {
		return false, nil
	}

	for _, p := range policy.Permissions {
		if p == action || p == "*" {
			return true, nil
		}
	}

	return false, nil
}

// EncryptSensitiveData encrypts sensitive data
func (sm *SecurityManager) EncryptSensitiveData(ctx context.Context, data []byte) (*EncryptedData, error) {
	block, err := aes.NewCipher(sm.encryptionKey)
	if err != nil {
		return nil, fmt.Errorf("암호화 초기화 실패: %v", err)
	}

	gcm, err := cipher.NewGCM(block)
	if err != nil {
		return nil, fmt.Errorf("GCM 모드 초기화 실패: %v", err)
	}

	nonce := make([]byte, gcm.NonceSize())
	if _, err := io.ReadFull(rand.Reader, nonce); err != nil {
		return nil, fmt.Errorf("nonce 생성 실패: %v", err)
	}

	encryptedData := &EncryptedData{
		Data:      gcm.Seal(nil, nonce, data, nil),
		Nonce:     nonce,
		CreatedAt: time.Now(),
		UpdatedAt: time.Now(),
	}

	_, err = sm.encryptedData.InsertOne(ctx, encryptedData)
	if err != nil {
		return nil, fmt.Errorf("암호화된 데이터 저장 실패: %v", err)
	}

	return encryptedData, nil
}

// DecryptSensitiveData decrypts encrypted data
func (sm *SecurityManager) DecryptSensitiveData(ctx context.Context, encryptedData *EncryptedData) ([]byte, error) {
	block, err := aes.NewCipher(sm.encryptionKey)
	if err != nil {
		return nil, fmt.Errorf("복호화 초기화 실패: %v", err)
	}

	gcm, err := cipher.NewGCM(block)
	if err != nil {
		return nil, fmt.Errorf("GCM 모드 초기화 실패: %v", err)
	}

	plaintext, err := gcm.Open(nil, encryptedData.Nonce, encryptedData.Data, nil)
	if err != nil {
		return nil, fmt.Errorf("데이터 복호화 실패: %v", err)
	}

	return plaintext, nil
}

// Cleanup performs cleanup operations
func (sm *SecurityManager) Cleanup(ctx context.Context) error {
	var errors []error

	if sm.redisClient != nil {
		if err := sm.redisClient.Close(); err != nil {
			errors = append(errors, fmt.Errorf("redis 연결 종료 실패: %v", err))
		}
	}

	if sm.mongoClient != nil {
		if err := sm.mongoClient.Disconnect(ctx); err != nil {
			errors = append(errors, fmt.Errorf("MongoDB 연결 종료 실패: %v", err))
		}
	}

	if len(errors) > 0 {
		return fmt.Errorf("정리 작업 중 오류 발생: %v", errors)
	}
	return nil
}

// isHighPriorityEvent determines if an event type is high priority
func isHighPriorityEvent(eventType string) bool {
	highPriorityEvents := map[string]bool{
		"unauthorized_access":    true,
		"authentication_failure": true,
		"policy_violation":       true,
		"data_breach":            true,
	}
	return highPriorityEvents[eventType]
}

// ExampleSecurity demonstrates the usage of security features
func ExampleSecurity() {
	ctx := context.Background()

	// 암호화 키 생성 (실제 환경에서는 안전하게 관리되어야 함)
	encryptionKey := make([]byte, 32)
	if _, err := io.ReadFull(rand.Reader, encryptionKey); err != nil {
		log.Fatalf("암호화 키 생성 실패: %v", err)
	}

	// 보안 매니저 초기화
	manager, err := NewSecurityManager(ctx, encryptionKey)
	if err != nil {
		log.Fatalf("보안 매니저 초기화 실패: %v", err)
	}
	defer manager.Cleanup(ctx)

	// 접근 정책 생성 예제
	policy := &AccessPolicy{
		RoleID:      "admin_role",
		Permissions: []string{"read", "write", "delete"},
		Resources:   []string{"users", "documents"},
		AllowedIPs:  []string{"192.168.1.100", "10.0.0.1"},
		ValidUntil:  time.Now().Add(24 * time.Hour),
	}

	// 정책 저장
	err = manager.CreateAccessPolicy(ctx, policy)
	if err != nil {
		log.Printf("정책 생성 실패: %v", err)
	} else {
		log.Println("접근 정책이 성공적으로 생성됨")
	}

	// 접근 권한 확인 테스트
	allowed, err := manager.CheckAccess(ctx, "user123", "admin_role", "users", "read", "192.168.1.100")
	if err != nil {
		log.Printf("접근 권한 확인 실패: %v", err)
	} else {
		log.Printf("접근 권한 상태: %v", allowed)
	}

	// 민감한 데이터 암호화 테스트
	sensitiveData := []byte("이것은 매우 민감한 정보입니다")
	encryptedData, err := manager.EncryptSensitiveData(ctx, sensitiveData)
	if err != nil {
		log.Printf("데이터 암호화 실패: %v", err)
	} else {
		log.Println("데이터가 성공적으로 암호화됨")

		// 암호화된 데이터 복호화 테스트
		decryptedData, err := manager.DecryptSensitiveData(ctx, encryptedData)
		if err != nil {
			log.Printf("데이터 복호화 실패: %v", err)
		} else {
			log.Printf("복호화된 데이터: %s", string(decryptedData))
		}
	}

	// 보안 이벤트 로깅 테스트
	securityEvent := &SecurityEvent{
		EventType:    "unauthorized_access",
		UserID:       "user123",
		Action:       "delete",
		ResourceType: "users",
		Status:       "blocked",
		IPAddress:    "192.168.1.200",
		Metadata: map[string]interface{}{
			"attempt_count": 3,
			"browser":       "Chrome",
		},
	}

	err = manager.LogSecurityEvent(ctx, securityEvent)
	if err != nil {
		log.Printf("보안 이벤트 기록 실패: %v", err)
	} else {
		log.Println("보안 이벤트가 성공적으로 기록됨")
	}

	// 감사 로그 조회 예시
	filter := bson.D{
		{Key: "event_type", Value: "unauthorized_access"},
		{Key: "timestamp", Value: bson.D{
			{Key: "$gte", Value: time.Now().Add(-24 * time.Hour)},
		}},
	}

	cursor, err := manager.auditLog.Find(ctx, filter)
	if err != nil {
		log.Printf("감사 로그 조회 실패: %v", err)
	} else {
		defer cursor.Close(ctx)

		var events []SecurityEvent
		if err = cursor.All(ctx, &events); err != nil {
			log.Printf("감사 로그 디코딩 실패: %v", err)
		} else {
			log.Printf("최근 24시간 동안의 무단 접근 시도: %d건", len(events))
			for _, event := range events {
				log.Printf("- 시간: %v, 사용자: %s, IP: %s",
					event.Timestamp, event.UserID, event.IPAddress)
			}
		}
	}

	log.Println("보안 기능 테스트 완료")
}
