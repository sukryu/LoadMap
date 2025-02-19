package examples

import (
	"context"
	"fmt"
	"time"
)

// UserID is a custom type for context values
type UserID string

// SimulateAPI simulates a long-running API call
func SimulateAPI(ctx context.Context) (string, error) {
	// 컨텍스트에서 사용자 ID 추출
	userID, ok := ctx.Value(UserID("user_id")).(string)
	if !ok {
		userID = "unknown"
	}

	select {
	case <-time.After(2 * time.Second):
		return fmt.Sprintf("API 호출 성공 (사용자: %s)", userID), nil
	case <-ctx.Done():
		return "", fmt.Errorf("API 호출 중단: %w", ctx.Err())
	}
}

// DatabaseQuery simulates a database query
func DatabaseQuery(ctx context.Context) (string, error) {
	select {
	case <-time.After(1 * time.Second):
		return "데이터베이스 쿼리 성공", nil
	case <-ctx.Done():
		return "", fmt.Errorf("데이터베이스 쿼리 중단: %w", ctx.Err())
	}
}

// ProcessRequest simulates a complete request handling
func ProcessRequest(userID string) {
	// 기본 컨텍스트 생성 및 값 설정
	ctx := context.WithValue(context.Background(), UserID("user_id"), userID)

	// 타임아웃 설정
	ctx, cancel := context.WithTimeout(ctx, 3*time.Second)
	defer cancel()

	// 첫 번째 작업: API 호출
	fmt.Println("=== API 호출 시작 ===")
	result, err := SimulateAPI(ctx)
	if err != nil {
		fmt.Printf("API 에러: %v\n", err)
		return
	}
	fmt.Printf("API 결과: %s\n", result)

	// 두 번째 작업: 데이터베이스 쿼리
	fmt.Println("\n=== 데이터베이스 쿼리 시작 ===")
	dbResult, err := DatabaseQuery(ctx)
	if err != nil {
		fmt.Printf("데이터베이스 에러: %v\n", err)
		return
	}
	fmt.Printf("데이터베이스 결과: %s\n", dbResult)
}

// CancelExample demonstrates manual cancellation
func CancelExample() {
	ctx, cancel := context.WithCancel(context.Background())

	// 고루틴에서 작업 실행
	go func() {
		result, err := SimulateAPI(ctx)
		if err != nil {
			fmt.Printf("고루틴 에러: %v\n", err)
			return
		}
		fmt.Printf("고루틴 결과: %s\n", result)
	}()

	// 1초 후 작업 취소
	time.Sleep(1 * time.Second)
	cancel()
	time.Sleep(500 * time.Millisecond) // 고루틴이 종료되기를 기다림
}

// ContextExamples demonstrates various context usage patterns
func ContextExamples() {
	fmt.Println("1. 기본 요청 처리 (타임아웃 3초)")
	ProcessRequest("user123")

	fmt.Println("\n2. 수동 취소 예제")
	CancelExample()

	fmt.Println("\n3. 짧은 타임아웃 테스트 (1초)")
	ctx, cancel := context.WithTimeout(context.Background(), 1*time.Second)
	defer cancel()

	result, err := SimulateAPI(ctx)
	if err != nil {
		fmt.Printf("타임아웃 테스트 에러: %v\n", err)
	} else {
		fmt.Printf("타임아웃 테스트 결과: %s\n", result)
	}
}
