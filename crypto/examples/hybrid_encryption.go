// hybrid_encryption.go
//
// 이 파일은 Production 환경에서도 사용할 수 있을 정도로 고도화된 하이브리드 암호화 예제 코드입니다.
// 하이브리드 암호화는 대칭키 암호화를 통해 실제 데이터를 암호화하고, 비대칭키 암호화를 통해 대칭키를 안전하게 전달하는 방식입니다.
// 본 예제에서는 AES-GCM 모드를 사용하여 데이터를 암호화하고, RSA-OAEP를 사용하여 대칭키를 암호화합니다.
// 각 함수는 하나의 기능만 담당하며, 변수명과 함수명은 다른 파일들과의 충돌을 피하기 위해 고유하게 작성되었습니다.
// 주석은 한국어로 자세하게 작성되어 있어 초보자도 쉽게 이해할 수 있습니다.

package examples

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"crypto/rsa"
	"crypto/sha256"
	"errors"
	"fmt"
	"io"
)

// HybridCiphertext_HE는 하이브리드 암호화의 결과를 담는 구조체입니다.
// EncryptedSymKey: RSA-OAEP로 암호화된 대칭키
// SymCiphertext: AES-GCM으로 암호화된 데이터 (nonce와 함께 결합됨)
type HybridCiphertext_HE struct {
	EncryptedSymKey []byte // RSA로 암호화된 대칭키
	SymCiphertext   []byte // AES-GCM 암호화된 데이터 (nonce 포함)
}

// generateRandomBytes_HE는 암호학적으로 안전한 난수를 생성하는 헬퍼 함수입니다.
// 입력: 생성할 바이트 수 (n)
// 출력: 생성된 난수 ([]byte)와 발생한 오류 (error)
func generateRandomBytes_HE(n int) ([]byte, error) {
	bytesBuf := make([]byte, n)
	if _, err := io.ReadFull(rand.Reader, bytesBuf); err != nil {
		return nil, fmt.Errorf("안전한 난수 생성 오류: %v", err)
	}
	return bytesBuf, nil
}

// encryptWithAESGCM_HE는 AES-GCM 모드를 사용하여 평문 데이터를 암호화하는 함수입니다.
// 입력:
//   - plainData: 암호화할 평문 데이터 ([]byte)
//   - symKey: 32바이트 길이의 대칭키 ([]byte)
//   - aadData: 추가 인증 데이터 ([]byte), 필요 없는 경우 nil 사용
//
// 출력:
//   - 암호문: nonce와 암호문이 결합된 형태 ([]byte)
//   - 오류: 암호화 중 발생한 오류 (error)
func encryptWithAESGCM_HE(plainData, symKey, aadData []byte) ([]byte, error) {
	// AES-GCM은 32바이트(256비트) 키를 필요로 합니다.
	if len(symKey) != 32 {
		return nil, errors.New("유효하지 않은 대칭키 길이: AES-GCM 키는 32바이트여야 합니다")
	}

	// AES 블록 암호 생성
	aesBlock, err := aes.NewCipher(symKey)
	if err != nil {
		return nil, fmt.Errorf("AES 블록 생성 오류: %v", err)
	}

	// AES-GCM AEAD 인스턴스 생성
	aesGCMInstance, err := cipher.NewGCM(aesBlock)
	if err != nil {
		return nil, fmt.Errorf("AES-GCM 모드 초기화 오류: %v", err)
	}

	nonceSize := aesGCMInstance.NonceSize()
	nonceVal, err := generateRandomBytes_HE(nonceSize)
	if err != nil {
		return nil, err
	}

	// 암호화 수행: Seal 함수는 nonce를 첫 인자로 사용하여 암호문을 생성합니다.
	cipherData := aesGCMInstance.Seal(nil, nonceVal, plainData, aadData)
	// 최종 암호문은 nonce와 암호문을 결합하여 반환합니다.
	return append(nonceVal, cipherData...), nil
}

// decryptWithAESGCM_HE는 AES-GCM 모드를 사용하여 암호화된 데이터를 복호화하는 함수입니다.
// 입력:
//   - cipherCombined: nonce와 암호문이 결합된 데이터 ([]byte)
//   - symKey: 32바이트 길이의 대칭키 ([]byte)
//   - aadData: 암호화 시 사용된 추가 인증 데이터 ([]byte), 필요 없는 경우 nil 사용
//
// 출력:
//   - 평문 데이터 ([]byte)
//   - 오류: 복호화 중 발생한 오류 (error)
func decryptWithAESGCM_HE(cipherCombined, symKey, aadData []byte) ([]byte, error) {
	// AES-GCM 키 길이 검증
	if len(symKey) != 32 {
		return nil, errors.New("유효하지 않은 대칭키 길이: AES-GCM 키는 32바이트여야 합니다")
	}

	aesBlock, err := aes.NewCipher(symKey)
	if err != nil {
		return nil, fmt.Errorf("AES 블록 생성 오류: %v", err)
	}

	aesGCMInstance, err := cipher.NewGCM(aesBlock)
	if err != nil {
		return nil, fmt.Errorf("AES-GCM 모드 초기화 오류: %v", err)
	}

	nonceSize := aesGCMInstance.NonceSize()
	if len(cipherCombined) < nonceSize {
		return nil, errors.New("암호문 데이터가 너무 짧습니다: nonce 길이 부족")
	}

	nonceVal := cipherCombined[:nonceSize]
	actualCipherData := cipherCombined[nonceSize:]
	plainData, err := aesGCMInstance.Open(nil, nonceVal, actualCipherData, aadData)
	if err != nil {
		return nil, fmt.Errorf("AES-GCM 복호화 오류: %v", err)
	}

	return plainData, nil
}

// encryptSymKeyWithRSA_HE는 RSA 공개키를 사용하여 대칭키를 암호화하는 함수입니다.
// RSA-OAEP를 사용하며, SHA-256 해시 함수를 기반으로 합니다.
// 입력:
//   - symKeyData: 암호화할 대칭키 ([]byte)
//   - rsaPubKey: RSA 공개키 (*rsa.PublicKey)
//
// 출력:
//   - 암호화된 대칭키 ([]byte)
//   - 오류: 암호화 중 발생한 오류 (error)
func encryptSymKeyWithRSA_HE(symKeyData []byte, rsaPubKey *rsa.PublicKey) ([]byte, error) {
	hashFunc := sha256.New()
	encryptedSymKey, err := rsa.EncryptOAEP(hashFunc, rand.Reader, rsaPubKey, symKeyData, nil)
	if err != nil {
		return nil, fmt.Errorf("RSA-OAEP를 사용한 대칭키 암호화 오류: %v", err)
	}
	return encryptedSymKey, nil
}

// decryptSymKeyWithRSA_HE는 RSA 개인키를 사용하여 암호화된 대칭키를 복호화하는 함수입니다.
// 입력:
//   - encSymKey: RSA로 암호화된 대칭키 ([]byte)
//   - rsaPrivKey: RSA 개인키 (*rsa.PrivateKey)
//
// 출력:
//   - 복호화된 대칭키 ([]byte)
//   - 오류: 복호화 중 발생한 오류 (error)
func decryptSymKeyWithRSA_HE(encSymKey []byte, rsaPrivKey *rsa.PrivateKey) ([]byte, error) {
	hashFunc := sha256.New()
	decryptedKey, err := rsa.DecryptOAEP(hashFunc, rand.Reader, rsaPrivKey, encSymKey, nil)
	if err != nil {
		return nil, fmt.Errorf("RSA-OAEP를 사용한 대칭키 복호화 오류: %v", err)
	}
	return decryptedKey, nil
}

// HybridEncrypt_HE는 대칭키와 비대칭키를 혼합하여 데이터를 암호화하는 하이브리드 암호화 함수입니다.
// 이 함수는 다음 과정을 수행합니다:
//  1. 32바이트 길이의 대칭키 (AES-GCM용)를 안전하게 생성합니다.
//  2. 대칭키를 사용해 평문 데이터를 암호화합니다.
//  3. RSA 공개키를 사용해 대칭키를 암호화합니다.
//
// 반환값은 암호화된 대칭키와 AES-GCM 암호문을 포함하는 HybridCiphertext_HE 구조체입니다.
func HybridEncrypt_HE(plainData []byte, rsaPubKey *rsa.PublicKey, aadData []byte) (*HybridCiphertext_HE, error) {
	// 1. 대칭키 생성 (AES-256용, 32바이트)
	symKey, err := generateRandomBytes_HE(32)
	if err != nil {
		return nil, fmt.Errorf("대칭키 생성 실패: %v", err)
	}

	// 2. AES-GCM을 사용하여 평문 데이터 암호화 (nonce가 결합된 암호문 반환)
	symCiphertext, err := encryptWithAESGCM_HE(plainData, symKey, aadData)
	if err != nil {
		return nil, fmt.Errorf("대칭키 암호화 실패: %v", err)
	}

	// 3. RSA 공개키를 사용하여 대칭키 암호화
	encSymKey, err := encryptSymKeyWithRSA_HE(symKey, rsaPubKey)
	if err != nil {
		return nil, fmt.Errorf("대칭키 RSA 암호화 실패: %v", err)
	}

	// 하이브리드 암호문 구성
	hybridResult := &HybridCiphertext_HE{
		EncryptedSymKey: encSymKey,
		SymCiphertext:   symCiphertext,
	}
	return hybridResult, nil
}

// HybridDecrypt_HE는 HybridEncrypt_HE 함수로 생성된 하이브리드 암호문을 복호화하는 함수입니다.
// 이 함수는 다음 과정을 수행합니다:
//  1. RSA 개인키를 사용하여 암호화된 대칭키를 복호화합니다.
//  2. 복호화된 대칭키를 사용하여 AES-GCM 암호문을 복호화합니다.
//
// 반환값은 복호화된 평문 데이터입니다.
func HybridDecrypt_HE(hybridData *HybridCiphertext_HE, rsaPrivKey *rsa.PrivateKey, aadData []byte) ([]byte, error) {
	// 1. RSA 개인키를 사용하여 대칭키 복호화
	symKey, err := decryptSymKeyWithRSA_HE(hybridData.EncryptedSymKey, rsaPrivKey)
	if err != nil {
		return nil, fmt.Errorf("대칭키 RSA 복호화 실패: %v", err)
	}

	// 2. AES-GCM 암호문을 복호화하여 평문 데이터 복원
	plainData, err := decryptWithAESGCM_HE(hybridData.SymCiphertext, symKey, aadData)
	if err != nil {
		return nil, fmt.Errorf("대칭키 복호화 실패: %v", err)
	}
	return plainData, nil
}
