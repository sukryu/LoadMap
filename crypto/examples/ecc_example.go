// ecc_example.go
//
// 이 파일은 Production 환경에서도 사용할 수 있을 만큼 고도화된 ECC (타원곡선 암호) 기반
// 키 생성 및 ECDSA 디지털 서명/검증 예제를 제공합니다.
// 본 코드는 각 기능(키 생성, 서명, 검증)이 별도의 함수로 분리되어 있으며, 변수명과 함수명은
// 다른 파일과 충돌을 피하기 위해 고유하게 작성되었습니다.
// 주석은 한국어로 자세하게 작성되어 있어 초보자도 이해하기 쉽도록 구성되어 있습니다.
//
// 이 예제에서는 NIST P-256 (secp256r1) 타원곡선을 사용하며, SHA-256 해시 함수를 이용하여
// 메시지를 서명하고, ASN.1 인코딩을 통해 서명을 직렬화합니다.

package examples

import (
	"crypto/ecdsa"
	"crypto/elliptic"
	"crypto/rand"
	"crypto/sha256"
	"crypto/x509"
	"encoding/asn1"
	"encoding/pem"
	"errors"
	"fmt"
	"math/big"
)

// ECDSASignatureStruct는 ECDSA 서명의 구성요소를 담기 위한 구조체입니다.
// 이 구조체는 서명 값 r과 s를 ASN.1으로 인코딩/디코딩하는 데 사용됩니다.
type ECDSASignatureStruct struct {
	R, S *big.Int
}

// GenerateECDSAKeyPair_ECEx는 NIST P-256 (secp256r1) 타원곡선을 사용하여
// ECDSA 키 쌍(개인키와 공개키)을 생성하는 함수입니다.
// 반환값은 생성된 개인키(개인키 내부에 공개키 포함)와 발생한 오류입니다.
func GenerateECDSAKeyPair_ECEx() (*ecdsa.PrivateKey, error) {
	// NIST P-256 곡선을 사용하여 ECDSA 개인키 생성
	privKey, err := ecdsa.GenerateKey(elliptic.P256(), rand.Reader)
	if err != nil {
		return nil, fmt.Errorf("ECDSA 키 쌍 생성 오류: %v", err)
	}
	return privKey, nil
}

// ECDSASignData_ECEx는 주어진 메시지 데이터를 ECDSA 개인키를 사용하여 디지털 서명하는 함수입니다.
// 서명 과정은 SHA-256 해시 함수로 메시지 다이제스트를 계산한 후, PSS 패딩 대신
// ECDSA 서명 방식을 사용하여 r, s 값을 생성하고 ASN.1으로 인코딩합니다.
// 입력:
//   - privKey: ECDSA 개인키 (*ecdsa.PrivateKey)
//   - msgData: 서명할 메시지 데이터 ([]byte)
//
// 반환값:
//   - ASN.1으로 인코딩된 서명 ([]byte)
//   - 발생한 오류 (error)
func ECDSASignData_ECEx(privKey *ecdsa.PrivateKey, msgData []byte) ([]byte, error) {
	// 메시지 데이터를 SHA-256 해시 함수를 사용하여 다이제스트 계산
	msgDigest := sha256.Sum256(msgData)

	// ECDSA 서명 생성: ecdsa.Sign은 서명 값 r과 s를 반환함
	rValue, sValue, err := ecdsa.Sign(rand.Reader, privKey, msgDigest[:])
	if err != nil {
		return nil, fmt.Errorf("ECDSA 서명 생성 오류: %v", err)
	}

	// 서명 값을 ASN.1으로 인코딩하여 직렬화
	signatureStruct := ECDSASignatureStruct{R: rValue, S: sValue}
	encodedSignature, err := asn1.Marshal(signatureStruct)
	if err != nil {
		return nil, fmt.Errorf("ECDSA 서명 ASN.1 인코딩 오류: %v", err)
	}

	return encodedSignature, nil
}

// ECDSAVerifySignature_ECEx는 주어진 메시지와 ASN.1으로 인코딩된 ECDSA 서명을
// ECDSA 공개키를 사용하여 검증하는 함수입니다.
// 입력:
//   - pubKey: ECDSA 공개키 (*ecdsa.PublicKey)
//   - msgData: 원본 메시지 데이터 ([]byte)
//   - asn1Signature: ASN.1 인코딩된 서명 ([]byte)
//
// 반환값:
//   - 검증 성공 시 nil, 실패 시 오류 (error)
func ECDSAVerifySignature_ECEx(pubKey *ecdsa.PublicKey, msgData, asn1Signature []byte) error {
	// 메시지 데이터를 SHA-256 해시 함수를 사용하여 다이제스트 계산
	msgDigest := sha256.Sum256(msgData)

	// ASN.1으로 인코딩된 서명을 디코딩하여 ECDSASignatureStruct 구조체로 변환
	var sigStruct ECDSASignatureStruct
	_, err := asn1.Unmarshal(asn1Signature, &sigStruct)
	if err != nil {
		return fmt.Errorf("ECDSA 서명 ASN.1 디코딩 오류: %v", err)
	}

	// ECDSA 서명 검증: ecdsa.Verify 함수는 서명이 유효하면 true, 아니면 false를 반환합니다.
	if !ecdsa.Verify(pubKey, msgDigest[:], sigStruct.R, sigStruct.S) {
		return errors.New("ECDSA 서명 검증 실패: 서명이 유효하지 않습니다")
	}
	return nil
}

// ExportECDSAPrivateKeyToPEM_ECEx는 ECDSA 개인키를 PEM 형식의 문자열로 변환하여 반환하는 함수입니다.
// 입력: privKey (*ecdsa.PrivateKey)
// 반환값: PEM 인코딩된 개인키 (string) 및 발생한 오류 (error)
func ExportECDSAPrivateKeyToPEM_ECEx(privKey *ecdsa.PrivateKey) (string, error) {
	privBytes, err := x509.MarshalECPrivateKey(privKey)
	if err != nil {
		return "", fmt.Errorf("ECDSA 개인키 인코딩 오류: %v", err)
	}
	pemBlock := &pem.Block{
		Type:  "EC PRIVATE KEY",
		Bytes: privBytes,
	}
	pemData := pem.EncodeToMemory(pemBlock)
	if pemData == nil {
		return "", errors.New("ECDSA 개인키 PEM 인코딩 실패")
	}
	return string(pemData), nil
}

// ExportECDSAPublicKeyToPEM_ECEx는 ECDSA 공개키를 PEM 형식의 문자열로 변환하여 반환하는 함수입니다.
// 입력: pubKey (*ecdsa.PublicKey)
// 반환값: PEM 인코딩된 공개키 (string) 및 발생한 오류 (error)
func ExportECDSAPublicKeyToPEM_ECEx(pubKey *ecdsa.PublicKey) (string, error) {
	pubBytes, err := x509.MarshalPKIXPublicKey(pubKey)
	if err != nil {
		return "", fmt.Errorf("ECDSA 공개키 인코딩 오류: %v", err)
	}
	pemBlock := &pem.Block{
		Type:  "EC PUBLIC KEY",
		Bytes: pubBytes,
	}
	pemData := pem.EncodeToMemory(pemBlock)
	if pemData == nil {
		return "", errors.New("ECDSA 공개키 PEM 인코딩 실패")
	}
	return string(pemData), nil
}
