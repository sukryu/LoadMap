# 22. Go 암호화와 보안 (Cryptography and Security)

## 1. 해시 함수

### 1.1 SHA-2 해시
```go
import (
    "crypto/sha256"
    "crypto/sha512"
    "fmt"
)

func HashExamples() {
    data := []byte("hello world")
    hash := sha256.Sum256(data)
    fmt.Printf("SHA-256: %x\n", hash)
}
```

### 1.2 HMAC
```go
import "crypto/hmac"

func ComputeHMAC(message, key []byte) []byte {
    h := hmac.New(sha256.New, key)
    h.Write(message)
    return h.Sum(nil)
}
```

---

## 2. 대칭키 암호화

### 2.1 AES 암호화
```go
import (
    "crypto/aes"
    "crypto/cipher"
    "crypto/rand"
)

func Encrypt(plaintext []byte, key []byte) ([]byte, error) {
    block, err := aes.NewCipher(key)
    if err != nil {
        return nil, err
    }

    gcm, err := cipher.NewGCM(block)
    if err != nil {
        return nil, err
    }

    nonce := make([]byte, gcm.NonceSize())
    if _, err := io.ReadFull(rand.Reader, nonce); err != nil {
        return nil, err
    }

    return gcm.Seal(nonce, nonce, plaintext, nil), nil
}
```

---

## 3. 비대칭키 암호화

### 3.1 RSA 암호화
```go
import "crypto/rsa"

func GenerateRSAKeys() (*rsa.PrivateKey, error) {
    privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
    if err != nil {
        return nil, err
    }
    return privateKey, nil
}
```

### 3.2 전자서명
```go
func Sign(privateKey *rsa.PrivateKey, message []byte) ([]byte, error) {
    hashed := sha256.Sum256(message)
    return rsa.SignPKCS1v15(rand.Reader, privateKey, crypto.SHA256, hashed[:])
}
```

---

## 4. TLS/SSL

### 4.1 HTTPS 서버
```go
func HTTPSServer() {
    srv := &http.Server{
        Addr:      ":443",
        TLSConfig: &tls.Config{MinVersion: tls.VersionTLS12},
    }
    log.Fatal(srv.ListenAndServeTLS("cert.pem", "key.pem"))
}
```

### 4.2 HTTPS 클라이언트
```go
func HTTPSClient() *http.Client {
    return &http.Client{Transport: &http.Transport{TLSClientConfig: &tls.Config{MinVersion: tls.VersionTLS12}}}
}
```

---

## 5. 보안 난수 생성

### 5.1 보안 토큰 생성
```go
import "crypto/rand"

func GenerateToken(length int) (string, error) {
    b := make([]byte, length)
    _, err := rand.Read(b)
    return hex.EncodeToString(b), err
}
```

---

## 6. 안전한 패스워드 처리

### 6.1 패스워드 해싱
```go
import "golang.org/x/crypto/bcrypt"

func HashPassword(password string) (string, error) {
    bytes, err := bcrypt.GenerateFromPassword([]byte(password), bcrypt.DefaultCost)
    return string(bytes), err
}
```

---

## 7. 실용적인 예제

### 7.1 안전한 세션 관리
```go
type Session struct {
    ID        string
    UserID    string
    CreatedAt time.Time
    ExpiresAt time.Time
}
```

### 7.2 안전한 쿠키 설정
```go
func SetSecureCookie(w http.ResponseWriter, name, value string) {
    http.SetCookie(w, &http.Cookie{
        Name:     name,
        Value:    value,
        Secure:   true,
        HttpOnly: true,
        MaxAge:   3600,
    })
}
```

---

## 8. Best Practices

### 8.1 암호화
- 검증된 암호화 알고리즘 사용
- 적절한 키 길이 선택
- 안전한 키 관리

### 8.2 보안 설정
- TLS 1.2 이상 사용
- 강력한 암호화 스위트 선택

### 8.3 입력 검증
- 모든 사용자 입력 검증
- SQL 인젝션 방지
- XSS 공격 방지

### 8.4 세션 관리
- 안전한 세션ID 생성
- 적절한 세션 만료 설정
- 세션 하이재킹 방지

---

## 9. 주의사항
- 자체 암호화 알고리즘 구현 금지
- 암호화 키의 안전한 관리
- 중요 정보 로깅 주의

---

Go의 암호화 및 보안 기능을 활용하여 안전한 애플리케이션을 개발할 수 있습니다! 🚀

