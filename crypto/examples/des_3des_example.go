// des_3des_example.go
//
// 이 파일은 DES 및 3DES 알고리즘의 기본 동작, 단점 및 사용 사례를 비교하기 위한 Production 수준의 고도화된 예제 코드입니다.
// 본 예제는 CBC 모드와 PKCS#7 패딩을 사용하여 DES와 3DES 암호화 및 복호화를 수행합니다.
// DES는 8바이트 블록 암호이며, 3DES는 DES 알고리즘을 세 번 적용하여 보안을 강화한 방식입니다.
//
// [DES]
// - 단점: 짧은 키 길이(56비트 실효 키)로 인해 브루트포스 공격에 취약하며, 이미 여러 보안 취약점이 보고되었습니다.
// - 사용 사례: 구식 시스템 및 레거시 애플리케이션에서 제한적으로 사용 (보안성이 높은 환경에서는 권장되지 않음)
//
// [3DES]
// - 장점: DES를 세 번 적용하여 보안을 강화함 (2-키: 112비트, 3-키: 168비트 실효 키)
// - 단점: 처리 속도가 느리고, 최신 표준에 비해 보안성이 떨어지며, 효율성이 낮음.
// - 사용 사례: 레거시 시스템에서 여전히 호환성을 위해 사용됨
//
// 각 함수는 하나의 기능만 담당하며, 변수명과 함수명은 고유하게 작성되어 있습니다.
// Production 환경에서의 안전한 암호화 및 복호화를 위해, 키 길이 검증, 안전한 난수 생성, PKCS#7 패딩/언패딩, 오류 처리 등을 포함합니다.

package examples

import (
	"bytes"
	"crypto/cipher"
	"crypto/des"
	"crypto/rand"
	"errors"
	"io"
)

// pkcs7PadData는 PKCS#7 패딩을 적용하여 데이터의 길이를 블록 크기의 배수로 맞춥니다.
// 입력: 원본 데이터와 블록 크기
// 출력: 패딩이 적용된 데이터
func pkcs7PadData(inputData []byte, blockSize int) []byte {
	paddingLen := blockSize - (len(inputData) % blockSize)
	padding := bytes.Repeat([]byte{byte(paddingLen)}, paddingLen)
	return append(inputData, padding...)
}

// pkcs7UnpadData는 PKCS#7 패딩을 제거하여 원본 데이터를 복원합니다.
// 입력: 패딩이 적용된 데이터와 블록 크기
// 출력: 원본 데이터 (패딩 제거됨)
func pkcs7UnpadData(paddedData []byte, blockSize int) ([]byte, error) {
	dataLen := len(paddedData)
	if dataLen == 0 || dataLen%blockSize != 0 {
		return nil, errors.New("유효하지 않은 패딩: 데이터 길이가 블록 크기의 배수가 아님")
	}

	paddingLen := int(paddedData[dataLen-1])
	if paddingLen <= 0 || paddingLen > blockSize {
		return nil, errors.New("유효하지 않은 패딩 길이")
	}

	// 패딩이 올바른지 확인
	for i := 0; i < paddingLen; i++ {
		if paddedData[dataLen-1-i] != byte(paddingLen) {
			return nil, errors.New("패딩 값이 일치하지 않음")
		}
	}
	return paddedData[:dataLen-paddingLen], nil
}

// DesCbcEncrypt는 DES 알고리즘을 사용하여 평문을 CBC 모드와 PKCS#7 패딩 방식으로 암호화합니다.
// desKey는 정확히 8바이트여야 하며, 평문이 블록 크기의 배수가 아니면 자동으로 패딩됩니다.
// 암호화 결과는 초기화 벡터(IV)와 암호문이 결합된 형태로 반환됩니다.
func DesCbcEncrypt(plainText []byte, desKey []byte) ([]byte, error) {
	// DES 키 길이 검증: DES 키는 8바이트여야 함
	if len(desKey) != 8 {
		return nil, errors.New("DES 키는 8바이트여야 합니다")
	}

	// DES 블록 암호 생성
	desCipher, err := des.NewCipher(desKey)
	if err != nil {
		return nil, err
	}

	blockSize := desCipher.BlockSize() // 일반적으로 8바이트

	// PKCS#7 패딩 적용
	paddedPlainText := pkcs7PadData(plainText, blockSize)

	// 안전한 초기화 벡터(IV) 생성
	ivValue := make([]byte, blockSize)
	if _, err := io.ReadFull(rand.Reader, ivValue); err != nil {
		return nil, err
	}

	// CBC 모드 암호화 인스턴스 생성
	cbcEncrypter := cipher.NewCBCEncrypter(desCipher, ivValue)

	encryptedData := make([]byte, len(paddedPlainText))
	cbcEncrypter.CryptBlocks(encryptedData, paddedPlainText)

	// 최종 암호문: IV와 암호문 결합 (복호화 시 IV 추출 필요)
	return append(ivValue, encryptedData...), nil
}

// DesCbcDecrypt는 DesCbcEncrypt로 암호화된 DES 암호문을 복호화합니다.
// 입력 암호문은 IV와 실제 암호문이 결합된 형태여야 하며, 복호화 후 PKCS#7 패딩을 제거합니다.
func DesCbcDecrypt(cipherCombined []byte, desKey []byte) ([]byte, error) {
	// DES 키 길이 검증
	if len(desKey) != 8 {
		return nil, errors.New("DES 키는 8바이트여야 합니다")
	}

	desCipher, err := des.NewCipher(desKey)
	if err != nil {
		return nil, err
	}

	blockSize := desCipher.BlockSize()
	if len(cipherCombined) < blockSize {
		return nil, errors.New("암호문 데이터가 너무 짧습니다")
	}

	// 암호문에서 IV와 실제 암호문 분리
	ivValue := cipherCombined[:blockSize]
	actualCipherText := cipherCombined[blockSize:]

	// CBC 모드 복호화 인스턴스 생성
	cbcDecrypter := cipher.NewCBCDecrypter(desCipher, ivValue)
	decryptedPadded := make([]byte, len(actualCipherText))
	cbcDecrypter.CryptBlocks(decryptedPadded, actualCipherText)

	// PKCS#7 패딩 제거
	plainText, err := pkcs7UnpadData(decryptedPadded, blockSize)
	if err != nil {
		return nil, err
	}
	return plainText, nil
}

// TripleDesCbcEncrypt는 3DES 알고리즘을 사용하여 평문을 CBC 모드와 PKCS#7 패딩 방식으로 암호화합니다.
// tripleKey는 16바이트(2-키) 또는 24바이트(3-키)여야 하며, 암호화 결과는 IV와 암호문이 결합된 형태로 반환됩니다.
func TripleDesCbcEncrypt(plainData []byte, tripleKey []byte) ([]byte, error) {
	// 3DES 키 길이 검증: 16바이트 또는 24바이트여야 함
	keyLen := len(tripleKey)
	if keyLen != 16 && keyLen != 24 {
		return nil, errors.New("3DES 키는 16 또는 24바이트여야 합니다")
	}

	// 3DES 블록 암호 생성
	tripleDesCipher, err := des.NewTripleDESCipher(tripleKey)
	if err != nil {
		return nil, err
	}

	blockSize := tripleDesCipher.BlockSize() // 8바이트

	// PKCS#7 패딩 적용
	paddedData := pkcs7PadData(plainData, blockSize)

	// 안전한 초기화 벡터(IV) 생성
	ivTriple := make([]byte, blockSize)
	if _, err := io.ReadFull(rand.Reader, ivTriple); err != nil {
		return nil, err
	}

	// CBC 모드 암호화 인스턴스 생성
	cbcTripleEncrypter := cipher.NewCBCEncrypter(tripleDesCipher, ivTriple)
	encryptedResult := make([]byte, len(paddedData))
	cbcTripleEncrypter.CryptBlocks(encryptedResult, paddedData)

	// 최종 암호문: IV와 암호문 결합
	return append(ivTriple, encryptedResult...), nil
}

// TripleDesCbcDecrypt는 TripleDesCbcEncrypt로 암호화된 3DES 암호문을 복호화합니다.
// 입력 암호문은 IV와 실제 암호문이 결합된 형태여야 하며, 복호화 후 PKCS#7 패딩을 제거합니다.
func TripleDesCbcDecrypt(cipherBundle []byte, tripleKey []byte) ([]byte, error) {
	// 3DES 키 길이 검증
	keyLen := len(tripleKey)
	if keyLen != 16 && keyLen != 24 {
		return nil, errors.New("3DES 키는 16 또는 24바이트여야 합니다")
	}

	tripleDesCipher, err := des.NewTripleDESCipher(tripleKey)
	if err != nil {
		return nil, err
	}

	blockSize := tripleDesCipher.BlockSize()
	if len(cipherBundle) < blockSize {
		return nil, errors.New("암호문 데이터가 너무 짧습니다")
	}

	// 암호문에서 IV와 실제 암호문 분리
	ivTriple := cipherBundle[:blockSize]
	actualEncrypted := cipherBundle[blockSize:]

	// CBC 모드 복호화 인스턴스 생성
	cbcTripleDecrypter := cipher.NewCBCDecrypter(tripleDesCipher, ivTriple)
	decryptedPadded := make([]byte, len(actualEncrypted))
	cbcTripleDecrypter.CryptBlocks(decryptedPadded, actualEncrypted)

	// PKCS#7 패딩 제거
	plainData, err := pkcs7UnpadData(decryptedPadded, blockSize)
	if err != nil {
		return nil, err
	}
	return plainData, nil
}

/*
-----------------------------------------------------------
DES 및 3DES 알고리즘 비교 및 단점

[DES]
- 블록 크기: 8바이트
- 키 길이: 8바이트 (실제 56비트 사용)
- 단점: 짧은 키 길이로 인해 브루트포스 공격에 취약하며, 현대 보안 기준에는 미치지 못함.
- 사용 사례: 구식 시스템, 레거시 환경에서 제한적으로 사용

[3DES]
- 블록 크기: DES와 동일하게 8바이트
- 키 길이: 16바이트 (2-키 모드) 또는 24바이트 (3-키 모드)
- 장점: DES를 세 번 적용하여 보안을 강화함
- 단점: 처리 속도가 느리고, 최신 암호화 표준(AES 등)에 비해 효율성이 떨어짐
- 사용 사례: 레거시 시스템과 하위 호환성이 필요한 환경에서 사용

Production 환경에서는 최신 표준(예: AES-GCM, ChaCha20 등)을 사용하는 것이 권장되지만,
특정 레거시 시스템에서는 DES 또는 3DES가 여전히 필요할 수 있습니다.
-----------------------------------------------------------
*/
