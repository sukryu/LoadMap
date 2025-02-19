# Cryptography in Go: Secure Data & Communication 🔐

이 디렉토리는 Go 언어에서 **암호화 및 복호화**, **디지털 서명**, **해싱**, **대칭/비대칭 암호화** 등의 보안 기술을 구현하는 방법을 다룹니다.  
Go의 표준 라이브러리와 검증된 암호화 패키지를 활용하여, 데이터 무결성, 기밀성, 인증 및 보안을 강화하는 다양한 기법을 실무에 적용할 수 있습니다.

---

## What You'll Learn 🎯

- **기본 암호화 개념**:  
  - 대칭 암호화와 비대칭 암호화의 차이 및 용도  
  - 해시 함수, 디지털 서명, 키 관리의 기본 원리

- **Go의 암호화 라이브러리 활용**:  
  - `crypto/aes`, `crypto/cipher`를 통한 대칭 암호화 구현  
  - `crypto/rsa`, `crypto/ecdsa`를 통한 비대칭 암호화와 디지털 서명  
  - `crypto/sha256` 등의 해시 함수 활용

- **실무 적용 및 Best Practices**:  
  - 안전한 키 생성, 저장 및 관리 전략  
  - 암호화 모드(CBC, GCM 등) 선택과 구현 시 주의사항  
  - 보안 취약점을 예방하기 위한 암호화 Best Practice

---

## Directory Structure 📁

```plaintext
08-security/
└── cryptography/
    ├── main.go         # 암호화 및 복호화 관련 기본 예제 코드
    ├── examples/       # 다양한 암호화 기법 및 실무 적용 사례 예제
    └── README.md       # 이 문서
```

- **main.go**: 기본적인 대칭 및 비대칭 암호화, 해싱, 디지털 서명 등의 예제 코드가 포함되어 있습니다.
- **examples/**: 실제 애플리케이션에서 활용할 수 있는 암호화 패턴, 키 관리, 그리고 보안 취약점 예방 관련 추가 예제들을 제공합니다.

---

## Getting Started 🚀

### 1. Prerequisites
- Go 최신 버전 설치: [Download Go](https://go.dev/dl/)
- 암호화 및 보안 관련 기본 개념 숙지 (예: 대칭/비대칭 암호화, 해싱)

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/08-security/cryptography
```

### 3. 예제 코드 실행
```bash
go run main.go
```
- 실행 결과를 통해 암호화, 복호화, 해싱 등의 동작을 확인하고, 실습해 보세요.

---

## Example Code Snippet 📄

아래는 AES 대칭 암호화를 사용한 간단한 예제입니다:

```go
package main

import (
    "crypto/aes"
    "crypto/cipher"
    "crypto/rand"
    "fmt"
    "io"
)

// encryptAES는 주어진 평문을 AES-GCM 모드로 암호화합니다.
func encryptAES(key, plaintext []byte) ([]byte, error) {
    block, err := aes.NewCipher(key)
    if err != nil {
        return nil, err
    }
    aead, err := cipher.NewGCM(block)
    if err != nil {
        return nil, err
    }
    nonce := make([]byte, aead.NonceSize())
    if _, err := io.ReadFull(rand.Reader, nonce); err != nil {
        return nil, err
    }
    ciphertext := aead.Seal(nonce, nonce, plaintext, nil)
    return ciphertext, nil
}

// decryptAES는 AES-GCM 모드로 암호화된 데이터를 복호화합니다.
func decryptAES(key, ciphertext []byte) ([]byte, error) {
    block, err := aes.NewCipher(key)
    if err != nil {
        return nil, err
    }
    aead, err := cipher.NewGCM(block)
    if err != nil {
        return nil, err
    }
    nonceSize := aead.NonceSize()
    if len(ciphertext) < nonceSize {
        return nil, fmt.Errorf("암호문이 너무 짧습니다")
    }
    nonce, ciphertext := ciphertext[:nonceSize], ciphertext[nonceSize:]
    plaintext, err := aead.Open(nil, nonce, ciphertext, nil)
    if err != nil {
        return nil, err
    }
    return plaintext, nil
}

func main() {
    key := []byte("thisis32bitlongpassphraseimusing") // 32바이트 키 (AES-256)
    plaintext := []byte("Hello, Cryptography in Go!")

    // 암호화
    ciphertext, err := encryptAES(key, plaintext)
    if err != nil {
        fmt.Println("암호화 실패:", err)
        return
    }
    fmt.Printf("암호화된 데이터: %x\n", ciphertext)

    // 복호화
    decrypted, err := decryptAES(key, ciphertext)
    if err != nil {
        fmt.Println("복호화 실패:", err)
        return
    }
    fmt.Printf("복호화된 데이터: %s\n", decrypted)
}
```

이 예제는 AES-GCM 모드를 사용하여 데이터를 암호화하고, 복호화하는 기본 과정을 보여줍니다.

---

## Best Practices & Tips 💡

- **키 관리**:  
  - 암호화 키는 절대로 소스 코드에 하드코딩하지 않고, 환경 변수나 안전한 비밀 관리 시스템(예: Vault, AWS KMS)을 통해 관리하세요.
  
- **모드 선택**:  
  - AES와 같은 대칭 암호화 시, GCM과 같은 인증된 암호화 모드를 사용하여 데이터 무결성도 함께 보장하세요.
  
- **해싱 알고리즘**:  
  - SHA-256, SHA-3와 같은 강력한 해시 알고리즘을 사용하여 데이터 무결성과 디지털 서명을 구현하세요.
  
- **비대칭 암호화 활용**:  
  - RSA, ECDSA 등 비대칭 암호화를 활용하여, 안전한 키 교환 및 디지털 서명을 구현하세요.
  
- **성능 고려**:  
  - 암호화 연산이 성능에 미치는 영향을 파악하고, 필요한 경우 하드웨어 가속 기능을 고려하세요.
  
- **테스트 및 검증**:  
  - 암호화, 복호화, 서명 검증 등의 보안 로직에 대해 충분한 단위 테스트와 통합 테스트를 수행하세요.

---

## Next Steps

- **고급 암호화 기법**:  
  - 디지털 서명, 인증서 기반 암호화, 키 순환 및 관리 전략 등 고급 보안 기술을 추가로 학습해 보세요.
- **실무 적용**:  
  - 암호화 로직을 실제 애플리케이션에 통합하여, 데이터 보호와 기밀성 확보를 강화하세요.
- **보안 감사**:  
  - 주기적인 코드 감사와 보안 테스트를 통해, 암호화 구현의 취약점을 점검하고 개선하세요.

---

## References 📚

- [Go Cryptography Package Documentation](https://pkg.go.dev/crypto)
- [OWASP Cryptographic Storage Cheat Sheet](https://cheatsheetseries.owasp.org/cheatsheets/Cryptographic_Storage_Cheat_Sheet.html)
- [NIST Guidelines for Cryptographic Algorithms](https://www.nist.gov/topics/cryptography)
- [Practical Cryptography in Go](https://blog.gopheracademy.com/advent-2016/practical-cryptography-in-go/)

---

암호화는 데이터 보안의 핵심이며, 안전한 통신 및 데이터 저장을 위해 필수적인 요소입니다.  
이 자료를 통해 Go 애플리케이션에 강력한 암호화 기법을 적용하고, 실무 보안 수준을 높여 보세요! Happy Cryptography Coding! 🔐🚀