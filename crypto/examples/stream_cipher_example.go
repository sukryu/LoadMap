// stream_cipher_example.go
//
// 이 파일은 ChaCha20-Poly1305 AEAD 모드를 사용하여 스트림 암호화 및 복호화를 수행하는 Production 환경 수준의 고도화된 예제 코드입니다.
// ChaCha20-Poly1305는 빠르면서도 안전한 스트림 암호화 알고리즘으로, 추가 인증 데이터를 통한 무결성 검증 기능(AEAD)을 제공합니다.
// 각 함수는 하나의 기능만 담당하며, 변수명과 함수명은 다른 파일과 충돌을 피하기 위해 고유하게 작성되었습니다.
// 이 코드는 Production 환경에서 사용할 수 있도록 안전한 난수 생성, 키 길이 검증, 오류 처리 등을 포함하고 있습니다.
//
// 참고: ChaCha20-Poly1305는 32바이트(256비트) 길이의 키를 필요로 하며, nonce는 12바이트 길이로 생성됩니다.

package examples

import (
	"crypto/rand"
	"errors"
	"io"

	"golang.org/x/crypto/chacha20poly1305"
)

// EncryptChaCha20PolyAEAD는 ChaCha20-Poly1305 AEAD 모드를 사용하여 평문(plainData)을 암호화하는 함수입니다.
// 추가 인증 데이터(aadData)를 입력받아, 암호화된 결과물에 대한 무결성 검증을 강화할 수 있습니다.
// 이 함수는 안전하게 생성된 12바이트 nonce와 암호문을 결합하여 반환합니다.
//
// 입력 매개변수:
//   - plainData: 암호화할 평문 데이터 ([]byte)
//   - aeadKey: 32바이트 길이의 암호화 키 ([]byte)
//   - aadData: 추가 인증 데이터 ([]byte) - 복호화 시 동일한 값 필요
//
// 반환값:
//   - []byte: nonce와 암호문이 결합된 최종 암호문
//   - error: 암호화 과정에서 발생한 오류
func EncryptChaCha20PolyAEAD(plainData, aeadKey, aadData []byte) ([]byte, error) {
	// 키 길이 검증: ChaCha20-Poly1305는 32바이트 키가 필요함.
	if len(aeadKey) != chacha20poly1305.KeySize {
		return nil, errors.New("유효하지 않은 키 길이: 키는 32바이트여야 합니다")
	}

	// AEAD 인스턴스 생성: chacha20poly1305.New 함수 호출
	aeadCipher, err := chacha20poly1305.New(aeadKey)
	if err != nil {
		return nil, err
	}

	// nonce 생성: AEAD 인스턴스의 nonce 길이만큼 암호학적으로 안전한 난수를 생성
	nonceLength := aeadCipher.NonceSize()
	uniqueNonce := make([]byte, nonceLength)
	if _, err := io.ReadFull(rand.Reader, uniqueNonce); err != nil {
		return nil, err
	}

	// 암호화 수행: Seal 함수는 nonce를 별도로 사용하여 암호문을 생성
	encryptedOutput := aeadCipher.Seal(nil, uniqueNonce, plainData, aadData)

	// 최종 암호문: nonce와 암호문을 결합하여 반환 (복호화 시 nonce를 추출)
	return append(uniqueNonce, encryptedOutput...), nil
}

// DecryptChaCha20PolyAEAD는 EncryptChaCha20PolyAEAD 함수로 암호화된 데이터를 복호화하는 함수입니다.
// 입력 데이터는 nonce와 암호문이 결합된 형태여야 하며, 복호화 시 동일한 추가 인증 데이터(aadData)가 필요합니다.
//
// 입력 매개변수:
//   - cipherCombined: nonce와 암호문이 결합된 암호문 ([]byte)
//   - aeadKey: 32바이트 길이의 암호화 키 ([]byte)
//   - aadData: 암호화 시 사용한 추가 인증 데이터 ([]byte)
//
// 반환값:
//   - []byte: 복호화된 평문 데이터
//   - error: 복호화 과정에서 발생한 오류
func DecryptChaCha20PolyAEAD(cipherCombined, aeadKey, aadData []byte) ([]byte, error) {
	// 키 길이 검증: 키는 반드시 32바이트여야 합니다.
	if len(aeadKey) != chacha20poly1305.KeySize {
		return nil, errors.New("유효하지 않은 키 길이: 키는 32바이트여야 합니다")
	}

	// AEAD 인스턴스 생성
	aeadCipher, err := chacha20poly1305.New(aeadKey)
	if err != nil {
		return nil, err
	}

	// nonce 크기 확인 및 분리: 암호문 앞부분에 nonce가 포함되어 있음
	nonceLength := aeadCipher.NonceSize()
	if len(cipherCombined) < nonceLength {
		return nil, errors.New("암호문 데이터가 너무 짧습니다")
	}

	// nonce와 실제 암호문 분리
	extractedNonce := cipherCombined[:nonceLength]
	actualCipherText := cipherCombined[nonceLength:]

	// 복호화 수행: Open 함수는 복호화와 함께 추가 인증 데이터(aadData)를 검증합니다.
	decryptedData, err := aeadCipher.Open(nil, extractedNonce, actualCipherText, aadData)
	if err != nil {
		return nil, err
	}

	return decryptedData, nil
}
