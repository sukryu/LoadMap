package main

import (
	customerrors "error-handling/errors"
	"errors"
	"fmt"
)

// main은 이 프로그램의 진입점(entry point)입니다.
// 커스텀 에러, 에러 체인, 다중 에러 집계를 포함한 에러 처리 데모를 실행합니다.
// K8s 스타일: 프로그램의 전체 흐름을 명확히 드러냄.
func main() {
	// 프로그램 시작 메시지 출력.
	// K8s 스타일: 프로그램 상태를 로깅으로 추적 가능.
	fmt.Println("=== Go Error Handling Demo 시작 ===")

	// 1. 기본 커스텀 에러 데모.
	demonstrateCustomError()

	// 2. 에러 체인 데모.
	demonstrateErrorChain()

	// 3. 다중 에러 집계 데모.
	demonstrateMultipleErrors()

	// 프로그램 종료 메시지 출력.
	fmt.Println("\n=== Go Error Handling Demo 종료 ===")
}

// demonstrateCustomError는 CustomError와 ValidationError의 사용법을 보여줍니다.
// K8s 스타일: 기본 에러 처리 흐름을 명확히 주석으로 설명.
func demonstrateCustomError() {
	// CustomError 생성.
	// K8s 스타일: 에러 생성과 사용을 명시적으로 구분.
	customErr := customerrors.NewCustomError(400, "잘못된 요청", nil)
	fmt.Printf("기본 CustomError: %v\n", customErr)

	// ValidationError 생성.
	validationErr := customerrors.NewValidationError("username", "", "필수 필드가 비어 있습니다")
	fmt.Printf("ValidationError: %v\n", validationErr)

	// 에러 처리 예시.
	// K8s 스타일: 에러 발생 시 처리 로직을 상세히 로깅.
	if err := performTaskWithError(); err != nil {
		fmt.Printf("작업 실패: %v\n", err)
	} else {
		fmt.Println("작업 성공")
	}
}

// performTaskWithError는 에러를 발생시키는 작업을 시뮬레이션합니다.
// K8s 스타일: 의도적 에러 발생으로 테스트 용이성 제공.
func performTaskWithError() error {
	// 의도적 에러 발생.
	return customerrors.NewCustomError(500, "서버 내부 오류", fmt.Errorf("데이터베이스 연결 실패"))
}

// demonstrateErrorChain는 에러 체인과 errors.Is, errors.As의 사용법을 보여줍니다.
// K8s 스타일: 에러 체인의 생성과 분석 과정을 상세히 설명.
func demonstrateErrorChain() {
	// 루트 에러 생성.
	rootErr := fmt.Errorf("파일 열기 실패")
	wrappedErr := customerrors.WrapWithCustomError(rootErr, 404, "리소스를 찾을 수 없음")

	// 에러 체인 출력.
	// K8s 스타일: 에러 메시지를 통해 디버깅 정보 제공.
	fmt.Printf("래핑된 에러: %v\n", wrappedErr)

	// errors.Is로 루트 에러 확인.
	// K8s 스타일: 특정 에러 식별 로직 명시.
	if errors.Is(wrappedErr, rootErr) {
		fmt.Println("래핑된 에러가 '파일 열기 실패'를 포함함")
	} else {
		fmt.Println("errors.Is() 실패: '파일 열기 실패'가 감지되지 않음")
	}

	// errors.As로 타입 단언.
	// K8s 스타일: 타입 단언으로 커스텀 에러 정보 추출.
	var customErr *customerrors.CustomError
	if errors.As(wrappedErr, &customErr) {
		fmt.Printf("CustomError 추출: 코드=%d, 메시지=%q\n", customErr.Code, customErr.Message)
	} else {
		fmt.Println("errors.As() 실패: CustomError로 변환 불가")
	}

	// Unwrap으로 체인 풀기.
	// K8s 스타일: 에러 체인의 각 레벨을 단계별로 확인.
	unwrapped := errors.Unwrap(wrappedErr)
	if unwrapped != nil {
		fmt.Printf("Unwrap 결과: %v\n", unwrapped)
	}
}

// demonstrateMultipleErrors는 errors.Join을 사용한 다중 에러 집계를 보여줍니다.
// K8s 스타일: 다중 에러 처리 시나리오와 결과를 상세히 로깅.
func demonstrateMultipleErrors() {
	// 여러 에러 생성.
	// K8s 스타일: 다양한 에러 타입을 혼합하여 현실적 시나리오 시뮬레이션.
	err1 := customerrors.NewCustomError(400, "잘못된 입력", nil)
	err2 := customerrors.NewValidationError("email", "invalid@domain", "유효한 이메일 형식이 아님")
	err3 := fmt.Errorf("네트워크 타임아웃")

	// errors.Join으로 에러 집계.
	// K8s 스타일: 집계된 에러를 한 번에 처리.
	joinedErr := customerrors.JoinErrors(err1, err2, err3, nil) // nil 포함 테스트.
	if joinedErr != nil {
		fmt.Printf("다중 에러 집계 결과:\n%v\n", joinedErr)
	}

	// 집계된 에러 분석.
	// K8s 스타일: 개별 에러 확인으로 디버깅 용이성 확보.
	var customErr *customerrors.CustomError
	if errors.As(joinedErr, &customErr) {
		fmt.Printf("집계된 에러에서 CustomError 추출: 코드=%d\n", customErr.Code)
	}
	var validationErr *customerrors.ValidationError
	if errors.As(joinedErr, &validationErr) {
		fmt.Printf("집계된 에러에서 ValidationError 추출: 필드=%s\n", validationErr.Field)
	}
}
