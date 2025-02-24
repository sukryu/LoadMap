// tls_server_client.go
//
// 이 파일은 Production 환경에서도 사용할 수 있을 정도로 고도화된 TLS/SSL 서버와 클라이언트 구현 예제입니다.
// 이 예제는 HTTPS 서버를 생성하고, TLS 클라이언트를 구성하는 기능을 각각의 함수로 분리하여 제공합니다.
// 각 함수는 하나의 기능만 담당하며, 변수명과 함수명은 다른 파일과의 충돌을 피하기 위해 고유하게 작성되었습니다.
// 주석은 한국어로 자세하게 작성되어 있어 초보자도 쉽게 이해할 수 있습니다.
//
// 주의: 이 예제는 인증서 파일(예: server.crt, server.key)이 사전에 준비되어 있고,
//       클라이언트가 신뢰할 수 있는 CA 인증서를 포함한 x509.CertPool을 사용한다고 가정합니다.

package examples

import (
	"crypto/tls"
	"crypto/x509"
	"errors"
	"fmt"
	"net/http"
	"os"
	"time"
)

// CreateSecureHTTPSServer_TLSSC는 주어진 주소, 핸들러, 인증서 및 개인키 파일 경로를 이용하여
// 안전한 HTTPS 서버(*http.Server)를 생성하는 함수입니다.
// Production 환경에 적합하도록 최소 TLS 버전, 안전한 암호 스위트 등을 설정합니다.
//
// 매개변수:
//   - serverAddr: 서버가 바인딩할 주소 (예: ":8443")
//   - httpHandler: 요청 처리를 담당할 http.Handler
//   - certPath: 서버 인증서 파일 경로 (PEM 형식)
//   - keyPath: 서버 개인키 파일 경로 (PEM 형식)
//
// 반환값:
//   - *http.Server: 구성된 HTTPS 서버 인스턴스
//   - error: 구성 과정 중 발생한 오류
func CreateSecureHTTPSServer_TLSSC(serverAddr string, httpHandler http.Handler, certPath, keyPath string) (*http.Server, error) {
	// 서버 인증서 및 개인키 로드
	cert, err := tls.LoadX509KeyPair(certPath, keyPath)
	if err != nil {
		return nil, fmt.Errorf("TLS 인증서 로드 실패: %v", err)
	}

	// TLS 설정 구성: 최소 TLS 버전을 TLS 1.2 이상으로 설정하고, 안전한 암호 스위트를 사용합니다.
	tlsConfiguration := &tls.Config{
		Certificates: []tls.Certificate{cert},
		MinVersion:   tls.VersionTLS12,
		// 안전한 암호 스위트 예시: TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256, TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384 등 필요 시 추가
		PreferServerCipherSuites: true,
	}

	// HTTPS 서버 구성
	secureServer := &http.Server{
		Addr:         serverAddr,
		Handler:      httpHandler,
		TLSConfig:    tlsConfiguration,
		ReadTimeout:  10 * time.Second,
		WriteTimeout: 10 * time.Second,
		IdleTimeout:  120 * time.Second,
	}

	return secureServer, nil
}

// CreateCustomTLSHTTPClient_TLSSC는 사용자 정의 TLS 설정을 가진 HTTP 클라이언트를 생성하는 함수입니다.
// 이 함수는 클라이언트가 신뢰할 수 있는 루트 인증서들을 포함하는 CertPool과 최소 TLS 버전을 설정할 수 있게 합니다.
//
// 매개변수:
//   - trustedCertPool: 클라이언트가 신뢰하는 CA 인증서를 포함하는 *x509.CertPool (nil인 경우 시스템 기본값 사용)
//   - minimumTLSVersion: 클라이언트가 사용할 최소 TLS 버전 (예: tls.VersionTLS12)
//
// 반환값:
//   - *http.Client: 구성된 HTTPS 클라이언트 인스턴스
//   - error: 클라이언트 구성 중 발생한 오류
func CreateCustomTLSHTTPClient_TLSSC(trustedCertPool *x509.CertPool, minimumTLSVersion uint16) (*http.Client, error) {
	// TLS 클라이언트 설정 구성
	tlsClientConfig := &tls.Config{
		MinVersion: minimumTLSVersion,
		// 클라이언트 측 인증서를 검증하기 위해 신뢰할 수 있는 루트 인증서를 설정
		RootCAs: trustedCertPool,
		// 추가 설정: 서버 이름 검증(SNI) 등 필요 시 추가
	}

	// HTTP Transport 구성: TLS 설정 적용
	customTransport := &http.Transport{
		TLSClientConfig: tlsClientConfig,
		// Connection 재사용, Keep-Alive 등 추가 최적화 설정 가능
	}

	// HTTP 클라이언트 구성
	httpClient := &http.Client{
		Transport: customTransport,
		Timeout:   15 * time.Second,
	}

	return httpClient, nil
}

// LoadCustomCertPool_TLSSC는 지정된 CA 인증서 파일 경로를 사용하여, 클라이언트가 신뢰하는
// x509.CertPool을 생성하는 헬퍼 함수입니다.
//
// 매개변수:
//   - caCertPath: 신뢰할 수 있는 CA 인증서 파일 경로 (PEM 형식)
//
// 반환값:
//   - *x509.CertPool: 생성된 인증서 풀
//   - error: 인증서 풀 생성 중 발생한 오류
func LoadCustomCertPool_TLSSC(caCertPath string) (*x509.CertPool, error) {
	caCertData, err := os.ReadFile(caCertPath)
	if err != nil {
		return nil, fmt.Errorf("CA 인증서 파일 읽기 오류: %v", err)
	}

	certPool := x509.NewCertPool()
	if ok := certPool.AppendCertsFromPEM(caCertData); !ok {
		return nil, errors.New("CA 인증서 PEM 데이터 파싱 실패")
	}

	return certPool, nil
}
