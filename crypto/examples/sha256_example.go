// sha256_example.go
//
// 이 파일은 Production 환경에서도 사용할 수 있을 만큼 고도화된 SHA-256 해시 함수 적용 및 해시값 검증 예제입니다.
// 본 예제는 하나의 기능(해시 계산, 해시 검증)을 각각의 함수로 분리하여 작성되었으며,
// 변수명과 함수명은 다른 파일과의 충돌을 피하기 위해 고유하게 지정되었습니다.
// 주석은 한국어로 자세하게 작성되어 있어 초보자도 쉽게 이해할 수 있습니다.
//
// 이 코드는 "crypto/sha256" 및 "encoding/hex" 패키지를 활용하여 주어진 데이터의 SHA-256 해시를 계산하고,
// 계산된 해시값을 16진수 문자열 형식으로 반환합니다.
// 또한, 주어진 데이터에 대해 기대하는 해시값과 비교하여 검증하는 기능을 제공합니다.

package examples

import (
	"crypto/sha256"
	"encoding/hex"
	"errors"
)

// ComputeSHA256Digest_SHAEx는 입력 데이터(plainData)에 대해 SHA-256 해시 함수를 적용하여
// 16진수 문자열 형식의 해시값을 반환하는 함수입니다.
// 이 함수는 Production 환경에서도 안전하게 사용할 수 있도록 입력 데이터에 대한 유효성 검사와
// 에러 처리를 포함하고 있습니다.
//
// 입력 매개변수:
//   - plainData: 해시를 계산할 원본 데이터 ([]byte)
//
// 반환값:
//   - string: 16진수 인코딩된 SHA-256 해시값
//   - error: 입력 데이터가 nil이거나 해시 계산 중 오류 발생 시 반환되는 오류
func ComputeSHA256Digest_SHAEx(plainData []byte) (string, error) {
	// 입력 데이터 검증
	if plainData == nil {
		return "", errors.New("입력 데이터가 nil입니다")
	}

	// SHA-256 해시 함수 객체 생성
	hasher := sha256.New()

	// 입력 데이터를 해시 객체에 기록합니다.
	_, err := hasher.Write(plainData)
	if err != nil {
		return "", err
	}

	// 해시 계산 완료: 최종 해시값을 바이트 슬라이스로 반환
	hashBytes := hasher.Sum(nil)

	// 해시값을 16진수 문자열로 인코딩하여 반환합니다.
	hashHex := hex.EncodeToString(hashBytes)
	return hashHex, nil
}

// ValidateSHA256Digest_SHAEx는 주어진 데이터(plainData)에 대해 SHA-256 해시 함수를 적용하여
// 계산된 해시값이 제공된 기대 해시값(expectedHashHex)과 일치하는지 검증하는 함수입니다.
// 이 함수는 입력 데이터와 기대 해시값의 유효성을 검사하고, 일치 여부를 boolean 값으로 반환합니다.
//
// 입력 매개변수:
//   - plainData: 해시를 계산할 원본 데이터 ([]byte)
//   - expectedHashHex: 기대하는 SHA-256 해시값 (16진수 문자열, string)
//
// 반환값:
//   - bool: 계산된 해시값과 기대 해시값이 일치하면 true, 그렇지 않으면 false
//   - error: 입력 데이터나 기대 해시값이 유효하지 않거나, 해시 계산 중 오류 발생 시 반환되는 오류
func ValidateSHA256Digest_SHAEx(plainData []byte, expectedHashHex string) (bool, error) {
	// 입력 데이터와 기대 해시값에 대한 유효성 검사
	if plainData == nil {
		return false, errors.New("입력 데이터가 nil입니다")
	}
	if expectedHashHex == "" {
		return false, errors.New("기대 해시값이 빈 문자열입니다")
	}

	// 주어진 데이터에 대해 SHA-256 해시값 계산
	computedHashHex, err := ComputeSHA256Digest_SHAEx(plainData)
	if err != nil {
		return false, err
	}

	// 계산된 해시값과 기대 해시값을 비교하여 결과 반환
	return computedHashHex == expectedHashHex, nil
}
