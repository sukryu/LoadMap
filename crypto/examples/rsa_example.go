// rsa_example.go
//
// 이 파일은 Production 환경에서도 사용할 수 있을 만큼 고도화된 RSA 키 쌍 생성, 암호화/복호화,
// 디지털 서명 및 검증 예제를 제공합니다. 각 함수는 하나의 기능만 담당하며, 변수명과 함수명은
// 다른 파일과의 충돌을 피하기 위해 고유하게 작성되었습니다. 주석은 한국어로 자세하게 작성되어
// 있어 초보자도 쉽게 이해할 수 있습니다.

package examples

import (
	"crypto"
	"crypto/rand"
	"crypto/rsa"
	"crypto/sha256"
	"crypto/x509"
	"encoding/pem"
	"errors"
	"fmt"
)

// GenerateRSAKeyPair_RSAEx는 Production 환경에 적합한 RSA 키 쌍을 생성하는 함수입니다.
// 매개변수 bits는 생성할 키의 비트 수로, 최소 2048비트 이상이어야 합니다.
// 반환값: 생성된 RSA 개인키(개인키 내부에 공개키 포함)와 발생한 오류.
func GenerateRSAKeyPair_RSAEx(bits int) (*rsa.PrivateKey, error) {
	if bits < 2048 {
		return nil, errors.New("키 길이는 최소 2048비트여야 합니다")
	}
	privKey, err := rsa.GenerateKey(rand.Reader, bits)
	if err != nil {
		return nil, fmt.Errorf("RSA 키 생성 오류: %v", err)
	}
	return privKey, nil
}

// RSAEncryptData_RSAEx는 RSA 공개키를 사용하여 평문 데이터를 암호화하는 함수입니다.
// 암호화에는 OAEP 패딩을 사용하며, SHA-256 해시 함수를 기반으로 합니다.
// 입력: rsaPubKey (*rsa.PublicKey), plainBytes ([]byte)
// 반환값: 암호문 ([]byte)와 발생한 오류.
func RSAEncryptData_RSAEx(rsaPubKey *rsa.PublicKey, plainBytes []byte) ([]byte, error) {
	hashInstance := sha256.New()
	cipherBytes, err := rsa.EncryptOAEP(hashInstance, rand.Reader, rsaPubKey, plainBytes, nil)
	if err != nil {
		return nil, fmt.Errorf("RSA 암호화 오류: %v", err)
	}
	return cipherBytes, nil
}

// RSADecryptData_RSAEx는 RSA 개인키를 사용하여 암호문을 복호화하는 함수입니다.
// 암호화에 사용된 OAEP 패딩을 기반으로 SHA-256 해시 함수를 사용하여 복호화를 수행합니다.
// 입력: rsaPrivKey (*rsa.PrivateKey), cipherBytes ([]byte)
// 반환값: 평문 ([]byte)와 발생한 오류.
func RSADecryptData_RSAEx(rsaPrivKey *rsa.PrivateKey, cipherBytes []byte) ([]byte, error) {
	hashInstance := sha256.New()
	plainBytes, err := rsa.DecryptOAEP(hashInstance, rand.Reader, rsaPrivKey, cipherBytes, nil)
	if err != nil {
		return nil, fmt.Errorf("RSA 복호화 오류: %v", err)
	}
	return plainBytes, nil
}

// RSASignData_RSAEx는 RSA 개인키를 사용하여 주어진 메시지에 대한 디지털 서명을 생성합니다.
// 서명 생성에는 PSS 패딩을 사용하며, SHA-256 해시 함수를 기반으로 합니다.
// 입력: rsaPrivKey (*rsa.PrivateKey), message ([]byte)
// 반환값: 생성된 서명 ([]byte)와 발생한 오류.
func RSASignData_RSAEx(rsaPrivKey *rsa.PrivateKey, message []byte) ([]byte, error) {
	// 메시지 해시 계산 (SHA-256)
	messageDigest := sha256.Sum256(message)
	signature, err := rsa.SignPSS(rand.Reader, rsaPrivKey, crypto.SHA256, messageDigest[:], nil)
	if err != nil {
		return nil, fmt.Errorf("RSA 서명 생성 오류: %v", err)
	}
	return signature, nil
}

// RSAVerifySignature_RSAEx는 RSA 공개키를 사용하여 주어진 메시지와 서명의 유효성을 검증합니다.
// 서명 검증은 PSS 패딩을 사용하며, SHA-256 해시 함수를 기반으로 합니다.
// 입력: rsaPubKey (*rsa.PublicKey), message ([]byte), signature ([]byte)
// 반환값: 검증 성공 시 nil, 실패 시 오류.
func RSAVerifySignature_RSAEx(rsaPubKey *rsa.PublicKey, message, signature []byte) error {
	messageDigest := sha256.Sum256(message)
	err := rsa.VerifyPSS(rsaPubKey, crypto.SHA256, messageDigest[:], signature, nil)
	if err != nil {
		return fmt.Errorf("RSA 서명 검증 실패: %v", err)
	}
	return nil
}

// ExportRSAPrivateKeyToPEM_RSAEx는 RSA 개인키를 PEM 형식의 문자열로 변환하여 반환합니다.
// 입력: rsaPrivKey (*rsa.PrivateKey)
// 반환값: PEM 인코딩된 개인키 (string)와 발생한 오류.
func ExportRSAPrivateKeyToPEM_RSAEx(rsaPrivKey *rsa.PrivateKey) (string, error) {
	privBytes := x509.MarshalPKCS1PrivateKey(rsaPrivKey)
	pemBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privBytes,
	}
	pemData := pem.EncodeToMemory(pemBlock)
	if pemData == nil {
		return "", errors.New("RSA 개인키 PEM 인코딩 실패")
	}
	return string(pemData), nil
}

// ExportRSAPublicKeyToPEM_RSAEx는 RSA 공개키를 PEM 형식의 문자열로 변환하여 반환합니다.
// 입력: rsaPubKey (*rsa.PublicKey)
// 반환값: PEM 인코딩된 공개키 (string)와 발생한 오류.
func ExportRSAPublicKeyToPEM_RSAEx(rsaPubKey *rsa.PublicKey) (string, error) {
	pubBytes, err := x509.MarshalPKIXPublicKey(rsaPubKey)
	if err != nil {
		return "", fmt.Errorf("RSA 공개키 인코딩 오류: %v", err)
	}
	pemBlock := &pem.Block{
		Type:  "RSA PUBLIC KEY",
		Bytes: pubBytes,
	}
	pemData := pem.EncodeToMemory(pemBlock)
	if pemData == nil {
		return "", errors.New("RSA 공개키 PEM 인코딩 실패")
	}
	return string(pemData), nil
}
