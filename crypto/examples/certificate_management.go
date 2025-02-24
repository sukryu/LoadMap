// certificate_management.go
//
// 이 파일은 Production 환경에서도 사용할 수 있을 정도로 고도화된 X.509 인증서 생성, 자체 서명 인증서 발급 및 저장 예제 코드입니다.
// 본 예제는 RSA 키를 사용하여 자체 서명 인증서를 생성하고, 해당 인증서와 개인키를 PEM 형식으로 인코딩하여 저장하는 기능을 제공합니다.
// 각 함수는 하나의 기능만 담당하며, 변수명과 함수명은 다른 파일과의 충돌을 피하기 위해 고유하게 작성되었습니다.
// 주석은 한국어로 자세하게 작성되어 있어, 초보자도 쉽게 이해할 수 있도록 구성되었습니다.

package examples

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"crypto/x509/pkix"
	"encoding/pem"
	"fmt"
	"math/big"
	"time"
)

// CreateSelfSignedCert_CMEx는 RSA 키 쌍을 사용하여 자체 서명 X.509 인증서를 생성하는 함수입니다.
// 이 함수는 Production 환경에서도 사용할 수 있도록 다양한 보안 설정(키 길이, 유효 기간, KeyUsage 등)을 포함합니다.
// 매개변수:
//   - orgName: 인증서에 기재할 조직명 (예: "Example Inc.")
//   - commonName: 인증서의 주체 이름 (예: "example.com")
//   - validFor: 인증서의 유효 기간 (시간.Duration)
//   - rsaBits: RSA 키 길이 (예: 2048, 3072, 4096)
//
// 반환값:
//   - *x509.Certificate: 생성된 X.509 인증서 객체
//   - *rsa.PrivateKey: 인증서에 사용된 RSA 개인키 (인증서에 포함된 공개키와 쌍을 이룹니다)
//   - error: 인증서 생성 과정에서 발생한 오류
func CreateSelfSignedCert_CMEx(orgName, commonName string, validFor time.Duration, rsaBits int) (*x509.Certificate, *rsa.PrivateKey, error) {
	// RSA 키 쌍 생성: rsa.GenerateKey는 암호학적으로 안전한 난수 생성기를 사용합니다.
	privKey, err := rsa.GenerateKey(rand.Reader, rsaBits)
	if err != nil {
		return nil, nil, fmt.Errorf("RSA 키 쌍 생성 오류: %v", err)
	}

	// 고유한 시리얼 번호 생성: 시리얼 번호는 양의 정수로 생성합니다.
	serialNumberLimit := new(big.Int).Lsh(big.NewInt(1), 128) // 128비트 시리얼 번호 범위
	serialNumber, err := rand.Int(rand.Reader, serialNumberLimit)
	if err != nil {
		return nil, nil, fmt.Errorf("시리얼 번호 생성 오류: %v", err)
	}

	// 인증서 템플릿 구성
	certTemplate := x509.Certificate{
		SerialNumber: serialNumber,
		Subject: pkix.Name{
			Organization: []string{orgName},
			CommonName:   commonName,
		},
		NotBefore: time.Now(),
		NotAfter:  time.Now().Add(validFor), // 유효 기간 설정

		// KeyUsage: 인증서의 사용 용도를 정의 (예: 디지털 서명, 키 암호화 등)
		KeyUsage:              x509.KeyUsageDigitalSignature | x509.KeyUsageKeyEncipherment,
		ExtKeyUsage:           []x509.ExtKeyUsage{x509.ExtKeyUsageServerAuth, x509.ExtKeyUsageClientAuth},
		BasicConstraintsValid: true,
	}

	// 자체 서명 인증서 생성: 부모와 대상 인증서를 동일하게 설정하여 자체 서명으로 만듭니다.
	certDERBytes, err := x509.CreateCertificate(rand.Reader, &certTemplate, &certTemplate, &privKey.PublicKey, privKey)
	if err != nil {
		return nil, nil, fmt.Errorf("자체 서명 인증서 생성 오류: %v", err)
	}

	// 생성된 인증서를 파싱하여 x509.Certificate 객체로 변환
	selfSignedCert, err := x509.ParseCertificate(certDERBytes)
	if err != nil {
		return nil, nil, fmt.Errorf("생성된 인증서 파싱 오류: %v", err)
	}

	return selfSignedCert, privKey, nil
}

// ExportCertToPEM_CMEx는 주어진 X.509 인증서를 PEM 형식의 문자열로 인코딩하여 반환하는 함수입니다.
// 입력:
//   - certObj: 인코딩할 X.509 인증서 (*x509.Certificate)
//
// 반환값:
//   - string: PEM 인코딩된 인증서
//   - error: 인코딩 중 발생한 오류
func ExportCertToPEM_CMEx(certObj *x509.Certificate) (string, error) {
	if certObj == nil {
		return "", fmt.Errorf("인증서 객체가 nil입니다")
	}

	pemBlock := &pem.Block{
		Type:  "CERTIFICATE",
		Bytes: certObj.Raw,
	}
	pemData := pem.EncodeToMemory(pemBlock)
	if pemData == nil {
		return "", fmt.Errorf("인증서 PEM 인코딩 실패")
	}
	return string(pemData), nil
}

// ExportRSAPrivateKeyToPEM_CMEx는 주어진 RSA 개인키를 PEM 형식의 문자열로 인코딩하여 반환하는 함수입니다.
// 입력:
//   - rsaPrivKey: 인코딩할 RSA 개인키 (*rsa.PrivateKey)
//
// 반환값:
//   - string: PEM 인코딩된 RSA 개인키
//   - error: 인코딩 중 발생한 오류
func ExportRSAPrivateKeyToPEM_CMEx(rsaPrivKey *rsa.PrivateKey) (string, error) {
	if rsaPrivKey == nil {
		return "", fmt.Errorf("RSA 개인키 객체가 nil입니다")
	}

	privBytes := x509.MarshalPKCS1PrivateKey(rsaPrivKey)
	pemBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privBytes,
	}
	pemData := pem.EncodeToMemory(pemBlock)
	if pemData == nil {
		return "", fmt.Errorf("RSA 개인키 PEM 인코딩 실패")
	}
	return string(pemData), nil
}
