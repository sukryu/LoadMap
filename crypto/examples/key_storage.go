// key_storage.go
//
// 이 파일은 Production 환경에서도 사용할 수 있을 만큼 고도화된 예제 코드로,
// 생성된 키를 암호화하여 안전하게 파일 시스템 또는 KMS에 저장하는 기능을 구현합니다.
// 본 예제에서는 AES-GCM 모드를 사용하여 대칭키(예: AES 키)를 암호화한 후,
// 암호화된 키를 파일로 저장하는 방법을 보여줍니다.
// Production 환경에서는 KMS (예: AWS KMS, Azure Key Vault 등)와 연동하여 더욱 강화된 보안 관리를 적용할 수 있습니다.
//
// 각 함수는 하나의 기능만 담당하며, 변수명과 함수명은 다른 파일과 충돌을 피하기 위해 고유하게 작성되었습니다.
// 주석은 한국어로 자세하게 작성되어 있어 초보자도 쉽게 이해할 수 있습니다.

package examples

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/base64"
	"errors"
	"fmt"
	"io"
	"io/ioutil"
	"os"
)

// encryptDataWithAESGCM_KS는 주어진 평문 데이터를 AES-GCM 모드를 사용하여 암호화하는 함수입니다.
// 이 함수는 암호화에 필요한 nonce를 안전하게 생성하고, nonce와 암호문을 결합하여 반환합니다.
// 입력:
//   - plainData: 암호화할 평문 데이터 ([]byte)
//   - encKey: AES-GCM 암호화에 사용할 32바이트 길이의 대칭키 ([]byte)
//
// 반환값:
//   - []byte: nonce와 암호문이 결합된 최종 암호문
//   - error: 암호화 과정 중 발생한 오류
func encryptDataWithAESGCM_KS(plainData, encKey []byte) ([]byte, error) {
	// AES-GCM은 32바이트 키 (AES-256)를 필요로 함.
	if len(encKey) != 32 {
		return nil, errors.New("유효하지 않은 암호화 키 길이: 키는 32바이트여야 합니다")
	}

	// AES 블록 암호 생성
	aesBlock, err := aes.NewCipher(encKey)
	if err != nil {
		return nil, fmt.Errorf("AES 블록 생성 오류: %v", err)
	}

	// AES-GCM AEAD 인스턴스 생성
	aesGCM, err := cipher.NewGCM(aesBlock)
	if err != nil {
		return nil, fmt.Errorf("AES-GCM 초기화 오류: %v", err)
	}

	nonceSize := aesGCM.NonceSize()
	nonce, err := generateRandomBytes_KS(nonceSize)
	if err != nil {
		return nil, fmt.Errorf("Nonce 생성 오류: %v", err)
	}

	// 암호화 수행: Seal 함수는 nonce와 추가 데이터를 사용하여 암호문을 생성
	cipherText := aesGCM.Seal(nil, nonce, plainData, nil)

	// 반환 값은 nonce와 암호문을 결합한 형태입니다.
	return append(nonce, cipherText...), nil
}

// decryptDataWithAESGCM_KS는 암호화된 데이터를 AES-GCM 모드를 사용하여 복호화하는 함수입니다.
// 입력 데이터는 nonce와 암호문이 결합된 형태여야 하며, 복호화 시에는 해당 nonce를 추출하여 사용합니다.
// 입력:
//   - cipherCombined: nonce와 암호문이 결합된 데이터 ([]byte)
//   - encKey: AES-GCM 복호화에 사용할 32바이트 길이의 대칭키 ([]byte)
//
// 반환값:
//   - []byte: 복호화된 평문 데이터
//   - error: 복호화 과정 중 발생한 오류
func decryptDataWithAESGCM_KS(cipherCombined, encKey []byte) ([]byte, error) {
	// 키 길이 검증
	if len(encKey) != 32 {
		return nil, errors.New("유효하지 않은 암호화 키 길이: 키는 32바이트여야 합니다")
	}

	// AES 블록 암호 생성
	aesBlock, err := aes.NewCipher(encKey)
	if err != nil {
		return nil, fmt.Errorf("AES 블록 생성 오류: %v", err)
	}

	aesGCM, err := cipher.NewGCM(aesBlock)
	if err != nil {
		return nil, fmt.Errorf("AES-GCM 초기화 오류: %v", err)
	}

	nonceSize := aesGCM.NonceSize()
	if len(cipherCombined) < nonceSize {
		return nil, errors.New("암호문 데이터가 너무 짧습니다: nonce 길이 부족")
	}

	// nonce와 실제 암호문 분리
	nonce := cipherCombined[:nonceSize]
	actualCipherText := cipherCombined[nonceSize:]

	// 복호화 수행
	plainData, err := aesGCM.Open(nil, nonce, actualCipherText, nil)
	if err != nil {
		return nil, fmt.Errorf("AES-GCM 복호화 오류: %v", err)
	}

	return plainData, nil
}

// generateRandomBytes_KS는 암호학적으로 안전한 난수를 생성하여 바이트 슬라이스로 반환하는 헬퍼 함수입니다.
// 입력:
//   - n: 생성할 바이트 수 (int)
//
// 반환값:
//   - []byte: 생성된 난수
//   - error: 난수 생성 중 발생한 오류
func generateRandomBytes_KS(n int) ([]byte, error) {
	bytesBuf := make([]byte, n)
	if _, err := io.ReadFull(rand.Reader, bytesBuf); err != nil {
		return nil, err
	}
	return bytesBuf, nil
}

// EncryptAndStoreKey_FS_KS는 생성된 대칭 키를 주어진 마스터 키로 암호화하여 파일 시스템에 안전하게 저장하는 함수입니다.
// Production 환경에서는 KMS를 사용할 수 있지만, 이 예제는 파일 시스템에 안전하게 키를 저장하는 방법을 보여줍니다.
// 입력:
//   - symKey: 암호화할 대칭 키 ([]byte)
//   - masterKey: 키를 암호화할 마스터 키 ([]byte) (32바이트, AES-GCM 사용)
//   - filePath: 암호화된 키를 저장할 파일 경로 (string)
//
// 반환값:
//   - error: 저장 과정 중 발생한 오류
func EncryptAndStoreKey_FS_KS(symKey, masterKey []byte, filePath string) error {
	// 마스터 키 길이 검증: AES-GCM은 32바이트 키를 필요로 함.
	if len(masterKey) != 32 {
		return fmt.Errorf("유효하지 않은 마스터 키 길이: 키는 32바이트여야 합니다")
	}

	// 대칭 키를 암호화
	encryptedKey, err := encryptDataWithAESGCM_KS(symKey, masterKey)
	if err != nil {
		return fmt.Errorf("대칭 키 암호화 오류: %v", err)
	}

	// 암호화된 키를 Base64 인코딩하여 파일에 저장 (추가 보안을 위해 파일 권한 0600 설정)
	encodedKey := base64.StdEncoding.EncodeToString(encryptedKey)
	if err := ioutil.WriteFile(filePath, []byte(encodedKey), 0600); err != nil {
		return fmt.Errorf("암호화된 키 저장 실패: %v", err)
	}
	return nil
}

// LoadAndDecryptKey_FS_KS는 파일 시스템에 저장된 암호화된 키를 읽어와, 주어진 마스터 키로 복호화하는 함수입니다.
// 입력:
//   - filePath: 암호화된 키가 저장된 파일 경로 (string)
//   - masterKey: 키 복호화에 사용할 마스터 키 ([]byte) (32바이트, AES-GCM 사용)
//
// 반환값:
//   - []byte: 복호화된 대칭 키
//   - error: 복호화 과정 중 발생한 오류
func LoadAndDecryptKey_FS_KS(filePath string, masterKey []byte) ([]byte, error) {
	// 마스터 키 길이 검증
	if len(masterKey) != 32 {
		return nil, fmt.Errorf("유효하지 않은 마스터 키 길이: 키는 32바이트여야 합니다")
	}

	// 파일에서 암호화된 키 읽기
	encodedKeyData, err := os.ReadFile(filePath)
	if err != nil {
		return nil, fmt.Errorf("암호화된 키 파일 읽기 오류: %v", err)
	}

	// Base64 디코딩
	encryptedKey, err := base64.StdEncoding.DecodeString(string(encodedKeyData))
	if err != nil {
		return nil, fmt.Errorf("암호화된 키 Base64 디코딩 오류: %v", err)
	}

	// 암호화된 키 복호화
	decryptedKey, err := decryptDataWithAESGCM_KS(encryptedKey, masterKey)
	if err != nil {
		return nil, fmt.Errorf("암호화된 키 복호화 오류: %v", err)
	}

	return decryptedKey, nil
}
