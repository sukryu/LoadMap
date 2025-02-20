package main

import (
	"context"
	"encoding/json"
	"fmt"
	"log"
	"time"

	"github.com/go-redis/redis/v8"
	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/bson/primitive"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
)

// User 구조체는 MongoDB에 저장될 사용자 정보를 정의합니다.
type User struct {
	ID        primitive.ObjectID `bson:"_id,omitempty" json:"id"`
	Username  string             `bson:"username" json:"username"`
	Email     string             `bson:"email" json:"email"`
	CreatedAt time.Time          `bson:"created_at" json:"created_at"`
	UpdatedAt time.Time          `bson:"updated_at" json:"updated_at"`
}

// MongoDB 클라이언트와 Redis 클라이언트를 전역 변수로 선언합니다.
var (
	mongoClient *mongo.Client
	redisClient *redis.Client
)

// init 함수에서 MongoDB와 Redis 연결을 초기화합니다.
func init() {
	// MongoDB 연결 설정
	mongoCtx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	// MongoDB 클라이언트 생성
	// 실제 운영 환경에서는 환경 변수나 설정 파일에서 연결 문자열을 가져와야 합니다.
	clientOptions := options.Client().ApplyURI("mongodb://localhost:27017")
	client, err := mongo.Connect(mongoCtx, clientOptions)
	if err != nil {
		log.Fatal("MongoDB 연결 실패:", err)
	}

	// 연결 확인
	err = client.Ping(mongoCtx, nil)
	if err != nil {
		log.Fatal("MongoDB 연결 확인 실패:", err)
	}

	mongoClient = client

	// Redis 클라이언트 초기화
	redisClient = redis.NewClient(&redis.Options{
		Addr:     "localhost:6379", // Redis 서버 주소
		Password: "",               // 비밀번호가 있는 경우 설정
		DB:       0,                // 기본 DB
	})

	// Redis 연결 확인
	_, err = redisClient.Ping(context.Background()).Result()
	if err != nil {
		log.Fatal("Redis 연결 실패:", err)
	}

	log.Println("MongoDB와 Redis 연결이 성공적으로 설정되었습니다.")
}

// createUser는 새로운 사용자를 MongoDB에 생성합니다.
func createUser(ctx context.Context, user *User) error {
	collection := mongoClient.Database("testdb").Collection("users")

	// 생성 시간과 수정 시간을 현재 시간으로 설정
	now := time.Now()
	user.CreatedAt = now
	user.UpdatedAt = now

	// MongoDB에 사용자 정보 삽입
	result, err := collection.InsertOne(ctx, user)
	if err != nil {
		return fmt.Errorf("사용자 생성 실패: %v", err)
	}

	// 삽입된 ID를 구조체에 설정
	user.ID = result.InsertedID.(primitive.ObjectID)

	// Redis 캐시 무효화 (사용자 목록이 변경되었으므로)
	err = redisClient.Del(ctx, "users:all").Err()
	if err != nil {
		log.Printf("Redis 캐시 무효화 실패: %v", err)
	}

	return nil
}

// getUserByID는 ID를 기반으로 사용자를 조회합니다.
// Redis 캐시를 먼저 확인하고, 없는 경우 MongoDB에서 조회합니다.
func getUserByID(ctx context.Context, id primitive.ObjectID) (*User, error) {
	// Redis 캐시 키 생성
	cacheKey := fmt.Sprintf("user:%s", id.Hex())

	// Redis에서 먼저 확인
	cachedUser, err := redisClient.Get(ctx, cacheKey).Result()
	if err == nil {
		// 캐시 히트: Redis에서 데이터를 찾은 경우
		var user User
		err = json.Unmarshal([]byte(cachedUser), &user)
		if err == nil {
			return &user, nil
		}
		log.Printf("캐시된 데이터 역직렬화 실패: %v", err)
	}

	// MongoDB에서 사용자 조회
	collection := mongoClient.Database("testdb").Collection("users")
	var user User
	err = collection.FindOne(ctx, bson.M{"_id": id}).Decode(&user)
	if err != nil {
		if err == mongo.ErrNoDocuments {
			return nil, fmt.Errorf("사용자를 찾을 수 없음: %s", id.Hex())
		}
		return nil, fmt.Errorf("사용자 조회 실패: %v", err)
	}

	// 조회된 데이터를 Redis에 캐시
	userData, err := json.Marshal(user)
	if err == nil {
		// 1시간 동안 캐시 유지
		err = redisClient.Set(ctx, cacheKey, userData, time.Hour).Err()
		if err != nil {
			log.Printf("Redis 캐시 저장 실패: %v", err)
		}
	}

	return &user, nil
}

// updateUser는 사용자 정보를 업데이트합니다.
func updateUser(ctx context.Context, user *User) error {
	collection := mongoClient.Database("testdb").Collection("users")

	// 수정 시간 업데이트
	user.UpdatedAt = time.Now()

	// MongoDB 업데이트 수행
	filter := bson.M{"_id": user.ID}
	update := bson.M{"$set": user}
	_, err := collection.UpdateOne(ctx, filter, update)
	if err != nil {
		return fmt.Errorf("사용자 정보 업데이트 실패: %v", err)
	}

	// Redis 캐시 업데이트
	cacheKey := fmt.Sprintf("user:%s", user.ID.Hex())
	userData, err := json.Marshal(user)
	if err == nil {
		err = redisClient.Set(ctx, cacheKey, userData, time.Hour).Err()
		if err != nil {
			log.Printf("Redis 캐시 업데이트 실패: %v", err)
		}
	}

	return nil
}

// deleteUser는 사용자를 삭제합니다.
func deleteUser(ctx context.Context, id primitive.ObjectID) error {
	collection := mongoClient.Database("testdb").Collection("users")

	// MongoDB에서 사용자 삭제
	_, err := collection.DeleteOne(ctx, bson.M{"_id": id})
	if err != nil {
		return fmt.Errorf("사용자 삭제 실패: %v", err)
	}

	// Redis 캐시에서도 사용자 정보 삭제
	cacheKey := fmt.Sprintf("user:%s", id.Hex())
	err = redisClient.Del(ctx, cacheKey).Err()
	if err != nil {
		log.Printf("Redis 캐시 삭제 실패: %v", err)
	}

	// 사용자 목록 캐시도 무효화
	err = redisClient.Del(ctx, "users:all").Err()
	if err != nil {
		log.Printf("사용자 목록 캐시 무효화 실패: %v", err)
	}

	return nil
}

// getAllUsers는 모든 사용자 목록을 반환합니다.
func getAllUsers(ctx context.Context) ([]User, error) {
	// Redis 캐시에서 먼저 확인
	cachedUsers, err := redisClient.Get(ctx, "users:all").Result()
	if err == nil {
		// 캐시 히트
		var users []User
		err = json.Unmarshal([]byte(cachedUsers), &users)
		if err == nil {
			return users, nil
		}
		log.Printf("캐시된 사용자 목록 역직렬화 실패: %v", err)
	}

	// MongoDB에서 모든 사용자 조회
	collection := mongoClient.Database("testdb").Collection("users")
	cursor, err := collection.Find(ctx, bson.M{})
	if err != nil {
		return nil, fmt.Errorf("사용자 목록 조회 실패: %v", err)
	}
	defer cursor.Close(ctx)

	var users []User
	if err = cursor.All(ctx, &users); err != nil {
		return nil, fmt.Errorf("사용자 목록 디코딩 실패: %v", err)
	}

	// 결과를 Redis에 캐시
	usersData, err := json.Marshal(users)
	if err == nil {
		// 15분 동안 캐시 유지
		err = redisClient.Set(ctx, "users:all", usersData, 15*time.Minute).Err()
		if err != nil {
			log.Printf("사용자 목록 캐시 저장 실패: %v", err)
		}
	}

	return users, nil
}

// cleanup 함수는 프로그램 종료 시 데이터베이스 연결을 정리합니다.
func cleanup() {
	if mongoClient != nil {
		if err := mongoClient.Disconnect(context.Background()); err != nil {
			log.Printf("MongoDB 연결 종료 실패: %v", err)
		}
	}
	if redisClient != nil {
		if err := redisClient.Close(); err != nil {
			log.Printf("Redis 연결 종료 실패: %v", err)
		}
	}
}

func main() {
	// 프로그램 종료 시 정리 작업 수행
	defer cleanup()

	// 컨텍스트 생성
	ctx := context.Background()

	// 예제: 새 사용자 생성
	newUser := &User{
		Username: "testuser",
		Email:    "test@example.com",
	}
	err := createUser(ctx, newUser)
	if err != nil {
		log.Printf("사용자 생성 실패: %v", err)
		return
	}
	log.Printf("새 사용자가 생성되었습니다. ID: %s", newUser.ID.Hex())

	// 예제: 사용자 조회
	user, err := getUserByID(ctx, newUser.ID)
	if err != nil {
		log.Printf("사용자 조회 실패: %v", err)
		return
	}
	log.Printf("조회된 사용자: %+v", user)

	// 예제: 사용자 정보 업데이트
	user.Email = "updated@example.com"
	err = updateUser(ctx, user)
	if err != nil {
		log.Printf("사용자 정보 업데이트 실패: %v", err)
		return
	}
	log.Println("사용자 정보가 업데이트되었습니다.")

	// 예제: 모든 사용자 조회
	users, err := getAllUsers(ctx)
	if err != nil {
		log.Printf("사용자 목록 조회 실패: %v", err)
		return
	}
	log.Printf("전체 사용자 수: %d", len(users))

	// 예제: 사용자 삭제
	err = deleteUser(ctx, user.ID)
	if err != nil {
		log.Printf("사용자 삭제 실패: %v", err)
		return
	}
	log.Println("사용자가 삭제되었습니다.")
}
