package customerrors

import (
	"errors"
	"fmt"
)

// CustomError는 기본 커스텀 에러 타입입니다.
// K8s 스타일: 에러에 필요한 필드를 구조체로 정의하여 컨텍스트 제공.
type CustomError struct {
	Code    int    // 에러 코드 (예: HTTP 상태 코드와 유사).
	Message string // 사용자에게 보여줄 메시지.
	Cause   error  // 원인 에러 (에러 체인용).
}

// Error는 error 인터페이스를 구현하여 CustomError를 에러로 사용 가능하게 합니다.
// K8s 스타일: 표준 에러 인터페이스 구현으로 호환성 보장.
func (e *CustomError) Error() string {
	if e.Cause != nil {
		return fmt.Sprintf("CustomError(code=%d): %s (cause: %v)", e.Code, e.Message, e.Cause)
	}
	return fmt.Sprintf("CustomError(code=%d): %s", e.Code, e.Message)
}

// Unwrap은 에러 체인을 풀기 위한 메서드로, 원인 에러를 반환합니다.
// K8s 스타일: errors.Unwrap과 통합되도록 설계.
func (e *CustomError) Unwrap() error {
	return e.Cause
}

// NewCustomError는 새로운 CustomError 인스턴스를 생성합니다.
// code: 에러 코드, message: 에러 메시지, cause: 원인 에러 (nil 가능).
// K8s 스타일: 생성자 함수로 초기화 캡슐화.
func NewCustomError(code int, message string, cause error) *CustomError {
	return &CustomError{
		Code:    code,
		Message: message,
		Cause:   cause,
	}
}

// ValidationError는 유효성 검사 실패를 나타내는 커스텀 에러 타입입니다.
// K8s 스타일: 특정 도메인에 특화된 에러 정의.
type ValidationError struct {
	Field   string // 유효성 검사 실패한 필드 이름.
	Value   any    // 잘못된 값.
	Details string // 추가 세부 정보.
}

// Error는 ValidationError를 에러로 사용 가능하게 합니다.
// K8s 스타일: 메시지를 구체적으로 작성하여 디버깅 용이성 확보.
func (e *ValidationError) Error() string {
	return fmt.Sprintf("ValidationError: field '%s' with value '%v' failed - %s", e.Field, e.Value, e.Details)
}

// NewValidationError는 새로운 ValidationError 인스턴스를 생성합니다.
// K8s 스타일: 도메인별 에러를 위한 생성자 제공.
func NewValidationError(field string, value any, details string) *ValidationError {
	return &ValidationError{
		Field:   field,
		Value:   value,
		Details: details,
	}
}

// WrapWithCustomError는 기존 에러를 CustomError로 래핑합니다.
// K8s 스타일: 에러 체인을 위한 헬퍼 함수 제공.
func WrapWithCustomError(err error, code int, message string) error {
	if err == nil {
		return nil // 입력 에러가 없으면 nil 반환.
	}
	return NewCustomError(code, message, err)
}

// JoinErrors는 여러 에러를 하나로 합칩니다.
// K8s 스타일: errors.Join을 활용한 다중 에러 집계.
func JoinErrors(errs ...error) error {
	// nil 에러 제거.
	var filteredErrs []error
	for _, err := range errs {
		if err != nil {
			filteredErrs = append(filteredErrs, err)
		}
	}
	if len(filteredErrs) == 0 {
		return nil // 유효한 에러가 없으면 nil 반환.
	}
	return errors.Join(filteredErrs...)
}
