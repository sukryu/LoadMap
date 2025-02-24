// aes_example.go
//
// 이 파일은 AES 암호화 및 복호화를 위한 고도화된 예제 코드입니다.
// 이 예제는 AES-GCM 모드를 사용하여 데이터를 암호화하며, GCM 모드에서는 별도의 패딩이 필요하지 않습니다.
// Production 환경에서도 사용할 수 있도록 안전한 난수 생성, 키 길이 검증, 오류 처리 등을 포함하고 있습니다.
//
// 각 함수는 하나의 기능만 담당하며, 변수명과 함수명은 고유하게 작성되었습니다.
// 주석은 한국어로 자세하게 작성되어 있어 초보자도 쉽게 이해할 수 있습니다.

package examples

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// EncryptDataAESGCM은 AES-GCM 모드를 사용하여 평문(plainData)을 암호화하는 함수입니다.
// 이 함수는 암호화에 필요한 nonce를 안전하게 생성하고, nonce와 암호문을 결합하여 반환합니다.
// additionalInfo는 추가 인증 데이터(AAD)로, 데이터 무결성을 추가로 검증하는 용도로 사용됩니다.
// GCM 모드에서는 패딩이 필요하지 않습니다.
func EncryptDataAESGCM(plainData, aesKey []byte, additionalInfo []byte) ([]byte, error) {
	// AES 키 길이 검증: 유효한 키 길이는 16, 24, 32 바이트 (AES-128, AES-192, AES-256)
	keyLen := len(aesKey)
	if keyLen != 16 && keyLen != 24 && keyLen != 32 {
		return nil, errors.New("유효하지 않은 AES 키 길이: 키는 16, 24, 또는 32 바이트여야 합니다")
	}

	// AES 블록 암호 인스턴스 생성
	blockCipher, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, err
	}

	// GCM 모드의 AEAD 인스턴스 생성 (GCM: Galois/Counter Mode)
	aesGCMInstance, err := cipher.NewGCM(blockCipher)
	if err != nil {
		return nil, err
	}

	// GCM 모드에서 사용되는 nonce의 길이 설정
	nonceLen := aesGCMInstance.NonceSize()

	// 암호화에 사용할 nonce를 암호학적으로 안전하게 생성
	nonceValue := make([]byte, nonceLen)
	if _, err := io.ReadFull(rand.Reader, nonceValue); err != nil {
		return nil, err
	}

	// GCM 모드 암호화 수행: gcm.Seal 함수는 nonce를 첫번째 인자로 사용하여 암호문을 생성합니다.
	// 생성된 암호문에는 추가 인증 데이터(additionalInfo)를 사용해 무결성 검증이 함께 이루어집니다.
	cipherData := aesGCMInstance.Seal(nil, nonceValue, plainData, additionalInfo)

	// 반환 값은 nonce와 암호문을 결합한 결과입니다.
	// 복호화 시에는 앞부분 nonce의 길이만큼을 추출하여 사용합니다.
	return append(nonceValue, cipherData...), nil
}

// DecryptDataAESGCM은 EncryptDataAESGCM 함수로 암호화된 데이터를 복호화하는 함수입니다.
// 입력 암호문(cipherCombined)은 nonce와 실제 암호문이 결합된 형식이어야 하며,
// additionalInfo는 암호화 시 사용한 추가 인증 데이터(AAD)와 동일해야 합니다.
func DecryptDataAESGCM(cipherCombined, aesKey []byte, additionalInfo []byte) ([]byte, error) {
	// AES 키 길이 검증: 유효한 키 길이는 16, 24, 32 바이트 (AES-128, AES-192, AES-256)
	keyLen := len(aesKey)
	if keyLen != 16 && keyLen != 24 && keyLen != 32 {
		return nil, errors.New("유효하지 않은 AES 키 길이: 키는 16, 24, 또는 32 바이트여야 합니다")
	}

	// AES 블록 암호 인스턴스 생성
	blockCipher, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, err
	}

	// GCM 모드의 AEAD 인스턴스 생성
	aesGCMInstance, err := cipher.NewGCM(blockCipher)
	if err != nil {
		return nil, err
	}

	nonceLen := aesGCMInstance.NonceSize()

	// 입력 암호문 길이가 nonce 크기보다 짧은 경우 오류 처리
	if len(cipherCombined) < nonceLen {
		return nil, errors.New("암호문 길이가 nonce 길이보다 짧습니다")
	}

	// 암호문에서 nonce와 실제 암호문을 분리합니다.
	nonceValue := cipherCombined[:nonceLen]
	actualCipherData := cipherCombined[nonceLen:]

	// GCM 모드 복호화 수행: gcm.Open 함수는 nonce와 추가 인증 데이터(additionalInfo)를 사용합니다.
	plainData, err := aesGCMInstance.Open(nil, nonceValue, actualCipherData, additionalInfo)
	if err != nil {
		return nil, err
	}

	return plainData, nil
}
