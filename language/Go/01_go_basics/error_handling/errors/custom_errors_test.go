package customerrors

import (
	"errors"
	"fmt"
	"testing"
)

// TestCustomError_Error는 CustomError의 Error 메서드 동작을 검증합니다.
// K8s 스타일: 기본 에러 메시지 출력 테스트.
func TestCustomError_Error(t *testing.T) {
	tests := []struct {
		name     string
		err      *CustomError
		expected string
	}{
		{
			name:     "NoCause",
			err:      NewCustomError(400, "잘못된 요청", nil),
			expected: "CustomError(code=400): 잘못된 요청",
		},
		{
			name:     "WithCause",
			err:      NewCustomError(500, "서버 오류", fmt.Errorf("내부 문제")),
			expected: "CustomError(code=500): 서버 오류 (cause: 내부 문제)",
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := tt.err.Error(); got != tt.expected {
				t.Errorf("CustomError.Error() 불일치:\n- 기대: %q\n- 실제: %q", tt.expected, got)
			}
		})
	}
}

// TestCustomError_Unwrap는 CustomError의 Unwrap 메서드 동작을 검증합니다.
// K8s 스타일: 에러 체인 풀기 기능 테스트.
func TestCustomError_Unwrap(t *testing.T) {
	cause := fmt.Errorf("원인 에러")
	err := NewCustomError(404, "찾을 수 없음", cause)

	// Unwrap 호출.
	unwrapped := err.Unwrap()
	if unwrapped != cause {
		t.Errorf("CustomError.Unwrap() 불일치:\n- 기대: %v\n- 실제: %v", cause, unwrapped)
	}

	// errors.Unwrap과 통합 확인.
	if got := errors.Unwrap(err); got != cause {
		t.Errorf("errors.Unwrap() 불일치:\n- 기대: %v\n- 실제: %v", cause, got)
	}
}

// TestValidationError_Error는 ValidationError의 Error 메서드 동작을 검증합니다.
// K8s 스타일: 도메인별 에러 메시지 테스트.
func TestValidationError_Error(t *testing.T) {
	err := NewValidationError("age", 15, "최소 나이는 18이어야 합니다")
	expected := "ValidationError: field 'age' with value '15' failed - 최소 나이는 18이어야 합니다"

	if got := err.Error(); got != expected {
		t.Errorf("ValidationError.Error() 불일치:\n- 기대: %q\n- 실제: %q", expected, got)
	}
}

// TestWrapWithCustomError는 WrapWithCustomError 헬퍼 함수를 검증합니다.
// K8s 스타일: 에러 래핑 기능 테스트.
func TestWrapWithCustomError(t *testing.T) {
	cause := fmt.Errorf("데이터베이스 연결 실패")
	err := WrapWithCustomError(cause, 503, "서비스 사용 불가")

	// 래핑된 에러 확인.
	if err == nil {
		t.Fatal("WrapWithCustomError()는 nil을 반환하면 안 됩니다")
	}
	expected := "CustomError(code=503): 서비스 사용 불가 (cause: 데이터베이스 연결 실패)"
	if got := err.Error(); got != expected {
		t.Errorf("WrapWithCustomError() 출력 불일치:\n- 기대: %q\n- 실제: %q", expected, got)
	}

	// nil 입력 테스트.
	if nilErr := WrapWithCustomError(nil, 400, "잘못된 입력"); nilErr != nil {
		t.Errorf("WrapWithCustomError(nil)은 nil을 반환해야 합니다, 실제: %v", nilErr)
	}
}

// TestJoinErrors는 JoinErrors 헬퍼 함수를 검증합니다.
// K8s 스타일: 다중 에러 집계 기능 테스트.
func TestJoinErrors(t *testing.T) {
	tests := []struct {
		name     string
		errs     []error
		expected string
	}{
		{
			name:     "SingleError",
			errs:     []error{fmt.Errorf("단일 에러")},
			expected: "단일 에러",
		},
		{
			name:     "MultipleErrors",
			errs:     []error{fmt.Errorf("에러 1"), NewCustomError(400, "에러 2", nil)},
			expected: "에러 1\nCustomError(code=400): 에러 2",
		},
		{
			name:     "WithNil",
			errs:     []error{nil, fmt.Errorf("에러 3"), nil},
			expected: "에러 3",
		},
		{
			name:     "AllNil",
			errs:     []error{nil, nil},
			expected: "",
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			joined := JoinErrors(tt.errs...)
			if tt.expected == "" {
				if joined != nil {
					t.Errorf("JoinErrors()는 nil을 반환해야 합니다, 실제: %v", joined)
				}
			} else {
				if joined == nil {
					t.Fatal("JoinErrors()는 nil이 아니어야 합니다")
				}
				if got := joined.Error(); got != tt.expected {
					t.Errorf("JoinErrors() 출력 불일치:\n- 기대: %q\n- 실제: %q", tt.expected, got)
				}
			}
		})
	}
}

// TestErrorChain는 에러 체인의 동작을 검증합니다.
// K8s 스타일: errors.Is와 errors.As 활용 테스트.
func TestErrorChain(t *testing.T) {
	cause := fmt.Errorf("루트 에러")
	wrapped := WrapWithCustomError(cause, 500, "래핑된 에러")

	// errors.Is로 원인 에러 확인.
	if !errors.Is(wrapped, cause) {
		t.Errorf("errors.Is() 실패: wrapped 에러가 cause를 포함해야 함")
	}

	// errors.As로 타입 단언.
	var customErr *CustomError
	if !errors.As(wrapped, &customErr) {
		t.Errorf("errors.As() 실패: wrapped 에러가 CustomError 타입이어야 함")
	}
	if customErr.Code != 500 || customErr.Message != "래핑된 에러" {
		t.Errorf("CustomError 필드 불일치:\n- 기대: code=500, message='래핑된 에러'\n- 실제: code=%d, message=%q", customErr.Code, customErr.Message)
	}
}
