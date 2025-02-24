// crypto_best_practices_example.go
//
// 이 파일은 Production 환경에서도 사용할 수 있을 정도로 고도화된 안전한 암호화 구현, 접근 제어, 그리고 감사 로그 기록 모범 사례를 코드로 구현한 예제입니다.
// 본 예제는 다음 세 가지 핵심 기능을 제공합니다:
//   1. 안전한 암호화 및 복호화 (AES-GCM 모드 사용)
//   2. 접근 제어 체크 (RBAC 개념의 간단한 시뮬레이션)
//   3. 보안 감사 로그 기록 (구조화된 JSON 형식의 로그 기록)
// 각 기능은 하나의 역할만 담당하며, 변수 및 함수명은 다른 파일과 충돌을 피하기 위해 고유하게 작성되었습니다.
// 주석은 한국어로 자세하게 작성되어 있어 초보자도 쉽게 이해할 수 있습니다.

package examples

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"crypto/subtle"
	"encoding/json"
	"errors"
	"fmt"
	"io"
	"os"
	"time"
)

// ===============================
// 1. 안전한 암호화 및 복호화 (AES-GCM)
// ===============================

// SecureEncrypt_CBE는 AES-GCM 모드를 사용하여 평문 데이터를 암호화하는 함수입니다.
// Production 환경에서도 사용 가능한 안전한 난수 생성, 키 길이 검증, 에러 처리를 포함합니다.
// 입력:
//   - plaintextData: 암호화할 평문 데이터 ([]byte)
//   - aesKey: 32바이트 길이의 AES 키 ([]byte)
//   - additionalData: 추가 인증 데이터 ([]byte), 필요 시 사용 (nil 가능)
//
// 반환값:
//   - []byte: nonce와 암호문이 결합된 최종 암호문
//   - error: 암호화 과정 중 발생한 오류
func SecureEncrypt_CBE(plaintextData, aesKey, additionalData []byte) ([]byte, error) {
	// AES-GCM은 32바이트(256비트) 키가 필요합니다.
	if len(aesKey) != 32 {
		return nil, errors.New("유효하지 않은 AES 키 길이: 키는 32바이트여야 합니다")
	}

	// AES 블록 암호 인스턴스 생성
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, fmt.Errorf("AES 블록 생성 오류: %v", err)
	}

	// AES-GCM AEAD 인스턴스 생성
	aesGCM, err := cipher.NewGCM(block)
	if err != nil {
		return nil, fmt.Errorf("AES-GCM 초기화 오류: %v", err)
	}

	// 안전한 난수를 이용해 nonce 생성 (AES-GCM에서 nonce 크기는 aesGCM.NonceSize()로 결정)
	nonceSize := aesGCM.NonceSize()
	nonce, err := generateRandomBytes_CBE(nonceSize)
	if err != nil {
		return nil, fmt.Errorf("Nonce 생성 오류: %v", err)
	}

	// 암호화 수행: Seal 함수는 nonce를 별도의 인자로 받아 암호문을 생성하며, 추가 인증 데이터(additionalData)를 검증에 사용합니다.
	ciphertext := aesGCM.Seal(nil, nonce, plaintextData, additionalData)

	// 최종 암호문: nonce와 암호문을 결합하여 반환 (복호화 시 nonce를 분리해야 함)
	return append(nonce, ciphertext...), nil
}

// SecureDecrypt_CBE는 SecureEncrypt_CBE로 암호화된 데이터를 복호화하는 함수입니다.
// 입력 데이터는 nonce와 암호문이 결합된 형태여야 하며, 복호화 시에는 해당 nonce를 추출하여 사용합니다.
// 입력:
//   - cipherCombined: nonce와 암호문이 결합된 데이터 ([]byte)
//   - aesKey: 32바이트 길이의 AES 키 ([]byte)
//   - additionalData: 암호화 시 사용한 추가 인증 데이터 ([]byte), 필요 시 사용 (nil 가능)
//
// 반환값:
//   - []byte: 복호화된 평문 데이터
//   - error: 복호화 과정 중 발생한 오류
func SecureDecrypt_CBE(cipherCombined, aesKey, additionalData []byte) ([]byte, error) {
	// AES 키 길이 검증
	if len(aesKey) != 32 {
		return nil, errors.New("유효하지 않은 AES 키 길이: 키는 32바이트여야 합니다")
	}

	// AES 블록 생성
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, fmt.Errorf("AES 블록 생성 오류: %v", err)
	}

	// AES-GCM 인스턴스 생성
	aesGCM, err := cipher.NewGCM(block)
	if err != nil {
		return nil, fmt.Errorf("AES-GCM 초기화 오류: %v", err)
	}

	nonceSize := aesGCM.NonceSize()
	if len(cipherCombined) < nonceSize {
		return nil, errors.New("암호문 데이터가 너무 짧습니다: nonce 크기 부족")
	}

	// 암호문에서 nonce와 실제 암호문 분리
	nonce := cipherCombined[:nonceSize]
	actualCiphertext := cipherCombined[nonceSize:]

	// 복호화 수행: Open 함수는 nonce와 추가 인증 데이터를 사용하여 평문 데이터를 복원합니다.
	plaintext, err := aesGCM.Open(nil, nonce, actualCiphertext, additionalData)
	if err != nil {
		return nil, fmt.Errorf("AES-GCM 복호화 오류: %v", err)
	}

	return plaintext, nil
}

// generateRandomBytes_CBE는 암호학적으로 안전한 난수를 생성하여 바이트 슬라이스로 반환하는 헬퍼 함수입니다.
// 입력:
//   - n: 생성할 바이트 수 (int)
//
// 반환값:
//   - []byte: 생성된 난수
//   - error: 난수 생성 중 발생한 오류
func generateRandomBytes_CBE(n int) ([]byte, error) {
	randomBytes := make([]byte, n)
	if _, err := io.ReadFull(rand.Reader, randomBytes); err != nil {
		return nil, err
	}
	return randomBytes, nil
}

// ===============================
// 2. 접근 제어 체크 (Access Control)
// ===============================

// CheckUserAccess_CBE는 단순화된 접근 제어 로직을 시뮬레이션하는 함수입니다.
// Production 환경에서는 실제 권한 관리 시스템(RBAC, LDAP, OAuth 등)과 연동하여 사용합니다.
// 입력:
//   - userRole: 사용자의 역할 (string)
//   - requiredPermission: 요구되는 권한 (string)
//
// 반환값:
//   - bool: 사용자가 요구 권한을 보유하면 true, 그렇지 않으면 false
func CheckUserAccess_CBE(userRole, requiredPermission string) bool {
	// 예시 RBAC 규칙:
	// 관리자("admin")는 모든 권한을 가지고 있으며, 일반 사용자("user")는 "read" 권한만 가지고 있다고 가정합니다.
	switch userRole {
	case "admin":
		return true
	case "user":
		// 일반 사용자는 오직 "read" 권한만 허용
		if requiredPermission == "read" {
			return true
		}
		return false
	default:
		return false
	}
}

// ===============================
// 3. 보안 감사 로그 기록 (Audit Logging)
// ===============================

// SecurityEvent_CBE는 보안 관련 이벤트 정보를 저장하는 구조체입니다.
type SecurityEvent_CBE struct {
	Timestamp time.Time `json:"timestamp"` // 이벤트 발생 시각
	UserID    string    `json:"user_id"`   // 이벤트와 관련된 사용자 ID
	Action    string    `json:"action"`    // 수행된 작업 (예: "login", "file_access" 등)
	Resource  string    `json:"resource"`  // 대상 리소스
	Outcome   string    `json:"outcome"`   // 결과 (예: "success", "failure")
	Details   string    `json:"details"`   // 추가 설명 또는 오류 메시지
}

// LogSecurityEvent_CBE는 보안 이벤트를 JSON 형식으로 파일에 기록하는 함수입니다.
// Production 환경에서는 중앙 집중식 로깅 시스템(예: ELK, Splunk)과 연동하여 사용 가능합니다.
// 입력:
//   - event: 보안 이벤트 정보 (SecurityEvent_CBE)
//   - logFilePath: 로그 파일 경로 (string)
//
// 반환값:
//   - error: 로그 기록 중 발생한 오류
func LogSecurityEvent_CBE(event SecurityEvent_CBE, logFilePath string) error {
	// JSON 인코딩: 보안 이벤트를 보기 쉽게 포맷팅하여 인코딩합니다.
	eventJSON, err := json.MarshalIndent(event, "", "  ")
	if err != nil {
		return fmt.Errorf("보안 이벤트 JSON 인코딩 오류: %v", err)
	}

	// 로그 파일 열기: 파일이 없으면 생성, 있으면 append 모드로 엽니다.
	logFile, err := os.OpenFile(logFilePath, os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0600)
	if err != nil {
		return fmt.Errorf("로그 파일 열기 오류: %v", err)
	}
	defer logFile.Close()

	// 로그 기록: JSON 문자열과 개행 문자를 파일에 기록합니다.
	logEntry := fmt.Sprintf("%s\n", string(eventJSON))
	if _, err := logFile.WriteString(logEntry); err != nil {
		return fmt.Errorf("로그 기록 실패: %v", err)
	}

	return nil
}

// ===============================
// 4. 상수 시간 비교 (Constant Time Comparison)
// ===============================

// ConstantTimeCompare_CBE는 두 16진수 문자열을 상수 시간으로 비교하여, 타이밍 공격을 방지하는 함수입니다.
// 입력:
//   - hexStr1: 첫 번째 16진수 문자열 (string)
//   - hexStr2: 두 번째 16진수 문자열 (string)
//
// 반환값:
//   - bool: 두 문자열이 동일하면 true, 아니면 false
func ConstantTimeCompare_CBE(hexStr1, hexStr2 string) bool {
	// 길이가 다르면 바로 false 반환
	if len(hexStr1) != len(hexStr2) {
		return false
	}
	// 두 문자열을 바이트 슬라이스로 변환 후, crypto/subtle 패키지의 ConstantTimeCompare 함수를 사용
	return (subtle.ConstantTimeCompare([]byte(hexStr1), []byte(hexStr2)) == 1)
}

/*
-------------------------------------------
암호화 모범 사례 예제 개요

1. 안전한 암호화 구현:
   - SecureEncrypt_CBE와 SecureDecrypt_CBE 함수는 AES-GCM 모드를 사용하여 데이터를 암호화 및 복호화합니다.
   - 안전한 난수 생성 및 키 길이 검증을 포함합니다.

2. 접근 제어:
   - CheckUserAccess_CBE 함수는 간단한 RBAC 시뮬레이션을 통해 사용자의 역할에 따른 접근 권한을 체크합니다.

3. 보안 감사 로그 기록:
   - SecurityEvent_CBE 구조체와 LogSecurityEvent_CBE 함수는 보안 이벤트를 JSON 형식으로 기록합니다.
   - 중앙 집중식 로깅과 상수 시간 비교 등을 통해 보안을 강화합니다.

4. 상수 시간 비교:
   - ConstantTimeCompare_CBE 함수는 타이밍 공격을 방지하기 위한 상수 시간 비교 기능을 제공합니다.

Production 환경에서는 위 기능들을 통합하여 안전하고 효율적인 보안 시스템을 구축할 수 있습니다.
-------------------------------------------
*/
