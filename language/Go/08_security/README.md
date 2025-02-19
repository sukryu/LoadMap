# 08 Security & Cryptography 🔒

이 디렉토리는 **Go 백엔드 애플리케이션**의 보안을 강화하기 위한 자료들을 제공합니다.  
여기서는 HTTPS 및 mTLS 설정, 암호화 기법(AES, RSA, HMAC 등), 그리고 보안 코딩 및 취약점 분석 등 실무에서 바로 활용 가능한 보안 전략과 모범 사례를 다룹니다.

---

## 디렉토리 구성 📁

```plaintext
08-security/
├── tls-ssl/             # HTTPS 및 mTLS 설정 예제, SSL/TLS 보안 모범 사례
├── cryptography/        # Go에서 AES, RSA, HMAC 등 암호화 기법 활용법
└── secure-coding/       # 안전한 코딩 원칙, 취약점 분석 및 방어 기법, 보안 코드 예제
```

- **tls-ssl/**:  
  - Go에서 TLS 설정, mTLS 인증, 인증서 관리 방법 및 안전한 통신 채널 구축을 위한 예제와 모범 사례를 제공합니다.
  
- **cryptography/**:  
  - Go의 `crypto` 패키지를 활용해 데이터 암호화, 복호화, 디지털 서명, 해시 함수(HMAC) 등을 사용하는 방법을 학습할 수 있습니다.
  
- **secure-coding/**:  
  - 입력값 검증, SQL 인젝션, XSS 등 일반적인 웹 보안 취약점 방어와 함께, 안전한 API 설계, 에러 처리 및 민감 정보 보호 전략을 다룹니다.

---

## 보안 활용 목표 🎯

- **안전한 통신 채널 구축**:  
  - HTTPS 및 mTLS 설정을 통해 외부 공격으로부터 데이터를 보호하고, 클라이언트와 서버 간의 통신 무결성을 보장합니다.
  
- **데이터 암호화 및 무결성 검증**:  
  - AES, RSA, HMAC 등의 암호화 기법을 적용해 민감 데이터를 안전하게 저장하고, 전송 중 위변조를 방지합니다.
  
- **보안 코딩 실천**:  
  - 입력값 검증, 에러 처리, 로그 보안 등 안전한 코딩 원칙을 통해 보안 취약점을 최소화합니다.

---

## 실무 활용 사례 🚀

1. **HTTPS 및 mTLS를 통한 보안 통신**  
   - Go의 `crypto/tls` 패키지를 활용해 서버와 클라이언트 간의 암호화된 통신 채널을 구축합니다.
   - Secure Bootstrapping 및 인증서 관리 방법을 적용하여, 안전한 API 호출을 구현할 수 있습니다.

2. **암호화 기능 구현**  
   - `crypto/aes`, `crypto/rsa`, `crypto/hmac` 등을 이용해 데이터 암호화 및 디지털 서명을 구현, 민감 데이터 보호와 무결성 검증에 활용할 수 있습니다.

3. **안전한 API 및 입력값 검증**  
   - 보안 코딩 가이드라인을 적용하여, SQL 인젝션, XSS 등 흔한 공격 벡터를 사전에 차단합니다.
   - Go의 표준 라이브러리와 서드파티 라이브러리를 활용한 안전한 에러 처리와 로그 관리를 통해, 문제 발생 시 빠른 대응이 가능합니다.

---

## 시작하기 🚀

### 1. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/08-security
```

### 2. TLS/SSL 예제 실행
```bash
cd tls-ssl
# 예제: 간단한 HTTPS 서버 실행
go run main.go
```
- 예제 서버를 통해 HTTPS 통신이 정상적으로 이루어지는지 확인하세요.

### 3. 암호화 예제 실행
```bash
cd ../cryptography
# 예제: AES 암호화 및 복호화 실행
go run main.go
```
- 암호화 함수와 해시 함수(HMAC) 등을 테스트해 보세요.

### 4. 보안 코딩 실습
```bash
cd ../secure-coding
# 예제: 안전한 입력값 검증 및 SQL 인젝션 방어 코드 실행
go run main.go
```
- 다양한 보안 취약점 방어 기법을 직접 확인하고, 코드 리뷰를 통해 개선점을 찾아보세요.

---

## Best Practices & Tips 💡

- **인증서 관리**:  
  - 인증서 갱신 및 체인 관리 자동화를 고려하세요.
  
- **암호화 기법 선택**:  
  - 민감 데이터에 적절한 암호화 알고리즘(AES-256, RSA-2048 등)을 선택하고, 키 관리 솔루션(예: AWS KMS, HashiCorp Vault)을 활용하세요.
  
- **보안 취약점 테스트**:  
  - 정기적으로 보안 스캔 도구(예: gosec)를 사용해 코드의 취약점을 점검하고, CI/CD 파이프라인에 통합하세요.
  
- **안전한 API 설계**:  
  - 입력값 검증, 에러 메시지 최소화, 로그 보안 등 기본 보안 원칙을 준수하세요.

---

## 참고 자료 📚

- [Go TLS Documentation](https://pkg.go.dev/crypto/tls)
- [Go Cryptography Packages](https://pkg.go.dev/crypto)
- [OWASP Secure Coding Practices](https://owasp.org/www-project-secure-coding-practices/)
- [Golang Security Best Practices](https://github.com/OWASP/Go-SCP)
- [Let's Encrypt Documentation](https://letsencrypt.org/docs/)

---

안전하고 신뢰할 수 있는 백엔드 시스템 구축을 위해, 이 자료를 기반으로 보안 기술을 실무에 적용해 보세요. Happy Secure Coding! 🔒🚀