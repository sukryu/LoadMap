// hmac_example.go
//
// 이 파일은 Production 환경에서도 사용할 수 있을 만큼 고도화된 HMAC 생성 및 검증 예제 코드입니다.
// 본 예제는 HMAC 생성, 검증, 그리고 상수 시간 비교 기능을 별도의 함수로 구현합니다.
// 각 함수는 하나의 기능만 담당하며, 변수명과 함수명은 다른 파일과 충돌을 피하기 위해 고유하게 작성되었습니다.
// 주석은 한국어로 상세하게 작성되어 있어, 초보자도 쉽게 이해할 수 있습니다.
//
// HMAC 생성 및 검증에는 crypto/hmac, crypto/sha256, crypto/subtle, encoding/hex 패키지를 사용합니다.

package examples

import (
	"crypto/hmac"
	"crypto/sha256"
	"crypto/subtle"
	"encoding/hex"
	"errors"
	"fmt"
)

// HMACGenerate_HMACEx는 주어진 메시지와 비밀 키를 사용하여 SHA-256 기반의 HMAC 값을 생성하는 함수입니다.
// 입력 매개변수:
//   - msgData: HMAC을 생성할 메시지 ([]byte)
//   - secretKey: 비밀 키 ([]byte)
//
// 반환값:
//   - string: 16진수로 인코딩된 HMAC 값
//   - error: HMAC 생성 과정에서 발생한 오류
func HMACGenerate_HMACEx(msgData, secretKey []byte) (string, error) {
	// 입력 검증: 메시지와 비밀 키는 nil이 아니어야 합니다.
	if msgData == nil {
		return "", errors.New("메시지 데이터가 nil입니다")
	}
	if secretKey == nil || len(secretKey) == 0 {
		return "", errors.New("비밀 키가 nil이거나 빈 값입니다")
	}

	// SHA-256 해시 함수를 기반으로 하는 HMAC 객체 생성
	hmacInstance := hmac.New(sha256.New, secretKey)

	// 메시지 데이터를 HMAC 객체에 기록합니다.
	_, err := hmacInstance.Write(msgData)
	if err != nil {
		return "", fmt.Errorf("HMAC 데이터 처리 오류: %v", err)
	}

	// 최종 HMAC 값 계산
	hmacBytes := hmacInstance.Sum(nil)

	// HMAC 값을 16진수 문자열로 인코딩하여 반환합니다.
	return hex.EncodeToString(hmacBytes), nil
}

// HMACVerify_HMACEx는 주어진 메시지와 비밀 키를 사용하여 생성한 HMAC 값과
// 기대하는 HMAC 값(expectedHMACHex)이 일치하는지 상수 시간 비교를 통해 검증하는 함수입니다.
// 입력 매개변수:
//   - msgData: 검증할 메시지 ([]byte)
//   - secretKey: 비밀 키 ([]byte)
//   - expectedHMACHex: 기대하는 HMAC 값 (16진수 문자열, string)
//
// 반환값:
//   - bool: HMAC 값이 일치하면 true, 불일치하면 false
//   - error: 검증 과정 중 발생한 오류
func HMACVerify_HMACEx(msgData, secretKey []byte, expectedHMACHex string) (bool, error) {
	// 입력 검증: 메시지, 비밀 키, 기대 HMAC 값이 모두 유효해야 합니다.
	if msgData == nil {
		return false, errors.New("메시지 데이터가 nil입니다")
	}
	if secretKey == nil || len(secretKey) == 0 {
		return false, errors.New("비밀 키가 nil이거나 빈 값입니다")
	}
	if expectedHMACHex == "" {
		return false, errors.New("기대하는 HMAC 값이 빈 문자열입니다")
	}

	// HMAC 생성 함수 호출
	computedHMACHex, err := HMACGenerate_HMACEx(msgData, secretKey)
	if err != nil {
		return false, fmt.Errorf("HMAC 생성 실패: %v", err)
	}

	// 16진수 문자열을 바이트 슬라이스로 변환
	computedHMACBytes, err := hex.DecodeString(computedHMACHex)
	if err != nil {
		return false, fmt.Errorf("HMAC 16진수 디코딩 오류: %v", err)
	}
	expectedHMACBytes, err := hex.DecodeString(expectedHMACHex)
	if err != nil {
		return false, fmt.Errorf("기대 HMAC 16진수 디코딩 오류: %v", err)
	}

	// crypto/subtle 패키지의 ConstantTimeCompare를 사용하여 상수 시간 비교 수행
	if subtle.ConstantTimeCompare(computedHMACBytes, expectedHMACBytes) == 1 {
		return true, nil
	}
	return false, nil
}
