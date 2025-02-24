// cmac_example.go
//
// 이 파일은 Production 환경에서도 사용할 수 있을 만큼 고도화된 CMAC 구현 및 사용 사례 예제입니다.
// 본 예제는 외부 라이브러리 "github.com/aead/cmac"을 활용하여 AES 블록 암호를 기반으로 CMAC 값을 생성하고 검증하는 기능을 제공합니다.
// 각 함수는 하나의 기능만 담당하며, 변수명과 함수명은 다른 파일과의 충돌을 피하기 위해 고유하게 작성되었습니다.
// 주석은 한국어로 자세하게 작성되어 있어 초보자도 쉽게 이해할 수 있습니다.
//
// 참고: 이 예제는 AES 블록 암호를 기반으로 CMAC을 계산합니다.
//        AES 키는 16, 24, 또는 32바이트여야 하며, AES 블록 크기는 16바이트입니다.

package examples

import (
	"crypto/aes"
	"encoding/hex"
	"errors"
	"fmt"

	"github.com/aead/cmac"
)

// ComputeCMAC_CMACEx는 주어진 평문 데이터(plainData)와 AES 키(aesKey)를 사용하여
// CMAC 값을 계산하는 함수입니다.
// 입력:
//   - plainData: CMAC을 계산할 평문 데이터 ([]byte)
//   - aesKey: AES 키 ([]byte), 유효한 키 길이는 16, 24, 또는 32바이트입니다.
//
// 반환값:
//   - string: 16진수로 인코딩된 CMAC 값
//   - error: 계산 과정 중 발생한 오류
func ComputeCMAC_CMACEx(plainData, aesKey []byte) (string, error) {
	// AES 키 길이 검증: AES 키는 16, 24, 32바이트 중 하나여야 합니다.
	keyLen := len(aesKey)
	if keyLen != 16 && keyLen != 24 && keyLen != 32 {
		return "", errors.New("유효하지 않은 AES 키 길이: 키는 16, 24, 또는 32바이트여야 합니다")
	}

	// AES 블록 암호 생성
	aesBlock, err := aes.NewCipher(aesKey)
	if err != nil {
		return "", fmt.Errorf("AES 블록 생성 오류: %v", err)
	}

	// CMAC 계산: 외부 라이브러리 "github.com/aead/cmac"을 사용합니다.
	// aesBlock과 블록 크기(16바이트)를 인자로 전달하여 평문 데이터의 CMAC 값을 계산합니다.
	cmacBytes, err := cmac.Sum(plainData, aesBlock, aesBlock.BlockSize())
	if err != nil {
		return "", fmt.Errorf("CMAC 계산 오류: %v", err)
	}

	// 계산된 CMAC 값을 16진수 문자열로 인코딩하여 반환합니다.
	return hex.EncodeToString(cmacBytes), nil
}

// VerifyCMAC_CMACEx는 주어진 평문 데이터(plainData)와 AES 키(aesKey)를 사용하여 계산된 CMAC 값이
// 기대하는 CMAC 값(expectedCMACHex)과 일치하는지 검증하는 함수입니다.
// 입력:
//   - plainData: 검증할 평문 데이터 ([]byte)
//   - aesKey: AES 키 ([]byte)
//   - expectedCMACHex: 기대하는 CMAC 값 (16진수 문자열)
//
// 반환값:
//   - bool: 계산된 CMAC 값과 기대 CMAC 값이 일치하면 true, 아니면 false
//   - error: 검증 과정 중 발생한 오류
func VerifyCMAC_CMACEx(plainData, aesKey []byte, expectedCMACHex string) (bool, error) {
	// ComputeCMAC_CMACEx 함수를 사용하여 평문 데이터의 CMAC 값을 계산
	computedCMACHex, err := ComputeCMAC_CMACEx(plainData, aesKey)
	if err != nil {
		return false, fmt.Errorf("CMAC 계산 실패: %v", err)
	}

	// 16진수 문자열을 비교하여 CMAC 값이 일치하는지 확인합니다.
	// 상수 시간 비교를 위해 비교 연산은 직접 수행합니다.
	if len(computedCMACHex) != len(expectedCMACHex) {
		return false, nil
	}

	// 직접 상수 시간 비교를 구현하거나, crypto/subtle 패키지의 ConstantTimeCompare를 사용할 수 있습니다.
	// 여기서는 간단하게 직접 구현한 예시를 제공합니다.
	var diff int
	for i := 0; i < len(computedCMACHex); i++ {
		diff |= int(computedCMACHex[i] ^ expectedCMACHex[i])
	}

	// diff가 0이면 두 문자열이 일치하는 것입니다.
	return diff == 0, nil
}
