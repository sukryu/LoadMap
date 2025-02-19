package examples

import (
	"errors"
	"fmt"
)

// CustomError 사용자 정의 에러 타입
type CustomError struct {
	Code    int
	Message string
}

// Error CustomError의 에러 메시지 구현
func (e *CustomError) Error() string {
	return fmt.Sprintf("에러 코드 %d: %s", e.Code, e.Message)
}

// DivideNumbers demonstrates error handling in Go
func DivideNumbers(a, b float64) (float64, error) {
	if b == 0 {
		return 0, &CustomError{
			Code:    100,
			Message: "0으로 나눌 수 없습니다",
		}
	}
	return a / b, nil
}

// ErrorHandlingExamples shows various error handling patterns
func ErrorHandlingExamples() {
	// 기본적인 에러 처리
	result, err := DivideNumbers(10, 0)
	if err != nil {
		// 사용자 정의 에러 타입 확인
		if customErr, ok := err.(*CustomError); ok {
			fmt.Printf("사용자 정의 에러 발생: %v\n", customErr)
		} else {
			fmt.Printf("일반 에러 발생: %v\n", err)
		}
		return
	}
	fmt.Printf("나눗셈 결과: %f\n", result)

	// errors.Is와 errors.As 사용
	var targetErr *CustomError
	if errors.As(err, &targetErr) {
		fmt.Printf("CustomError 발견: %v\n", targetErr)
	}
}
