// key_generation.go
//
// 이 파일은 Production 환경에서도 사용할 수 있을 만큼 고도화된 안전한 키 생성 예제입니다.
// 본 예제는 대칭키(예: AES용)와 비대칭키(예: RSA용) 생성 기능을 각각의 함수로 분리하여 구현합니다.
// 각 함수는 하나의 기능만 담당하며, 변수명 및 함수명은 다른 파일들과의 충돌을 피하기 위해 고유하게 작성되었습니다.
// 주석은 한국어로 상세하게 작성되어 있어 초보자도 쉽게 이해할 수 있습니다.

package examples

import (
	"crypto/rand"
	"crypto/rsa"
	"errors"
	"fmt"
)

// GenerateSymmetricKey_SKGEx는 Production 환경에 적합한 암호학적으로 안전한 대칭키를 생성하는 함수입니다.
// 이 함수는 AES와 같은 대칭키 암호화에 사용할 수 있는 키를 생성하며, 유효한 키 길이는 16, 24, 또는 32 바이트입니다.
// 매개변수:
//   - keyLen: 생성할 대칭키의 길이 (바이트 단위, 예: 16, 24, 32)
//
// 반환값:
//   - []byte: 생성된 대칭키
//   - error: 키 생성 과정 중 발생한 오류
func GenerateSymmetricKey_SKGEx(keyLen int) ([]byte, error) {
	// 유효한 키 길이 검증: AES는 16, 24, 32 바이트 키를 사용합니다.
	if keyLen != 16 && keyLen != 24 && keyLen != 32 {
		return nil, errors.New("유효하지 않은 대칭키 길이: 키는 16, 24 또는 32 바이트여야 합니다")
	}

	// 암호학적으로 안전한 난수 생성기를 사용하여 keyLen 바이트의 대칭키 생성
	symKey := make([]byte, keyLen)
	if _, err := rand.Read(symKey); err != nil {
		return nil, fmt.Errorf("대칭키 생성 실패: %v", err)
	}
	return symKey, nil
}

// GenerateRSAKeyPair_SKGEx는 Production 환경에 적합한 RSA 키 쌍(비대칭키)을 생성하는 함수입니다.
// 이 함수는 주어진 비트 수(예: 2048, 3072, 4096)를 사용하여 RSA 개인키를 생성하며,
// RSA 개인키 내부에 공개키도 포함되어 반환됩니다.
// 매개변수:
//   - bits: 생성할 RSA 키의 비트 수 (최소 2048비트 권장)
//
// 반환값:
//   - *rsa.PrivateKey: 생성된 RSA 개인키 (내부에 공개키 포함)
//   - error: 키 생성 과정 중 발생한 오류
func GenerateRSAKeyPair_SKGEx(bits int) (*rsa.PrivateKey, error) {
	// 최소 RSA 키 길이 검증: 보안상 최소 2048비트 이상이어야 합니다.
	if bits < 2048 {
		return nil, errors.New("RSA 키 길이는 최소 2048비트 이상이어야 합니다")
	}

	// 암호학적으로 안전한 난수 생성기를 사용하여 RSA 키 쌍 생성
	rsaPrivKey, err := rsa.GenerateKey(rand.Reader, bits)
	if err != nil {
		return nil, fmt.Errorf("RSA 키 쌍 생성 실패: %v", err)
	}

	// 생성된 RSA 키 쌍은 rsaPrivKey에 저장되며, rsaPrivKey.PublicKey를 통해 공개키에 접근할 수 있습니다.
	return rsaPrivKey, nil
}
