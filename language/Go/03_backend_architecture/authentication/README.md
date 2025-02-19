# Authentication & Authorization for APIs in Go 🔐

이 디렉토리는 Go를 사용하여 안전한 API 인증 및 인가 시스템을 설계하고 구현하는 방법을 다룹니다.  
여기서는 JWT 기반 토큰 인증, OAuth 2.0 플로우, 그리고 역할 기반 접근 제어(RBAC) 등을 통해, 실제 서비스에서 보안을 강화하는 전략과 모범 사례를 학습할 수 있습니다.

---

## What You'll Learn 🎯

- **기본 개념**:  
  - 인증(Authentication) vs. 인가(Authorization)의 차이와 중요성
- **토큰 기반 인증**:  
  - JWT를 사용한 토큰 생성, 검증 및 갱신 전략
- **OAuth 2.0 및 OpenID Connect**:  
  - 표준화된 인증 플로우와 타사 제공자 연동 방법
- **RBAC 설계**:  
  - 사용자 역할과 권한 관리로 API 보안을 강화하는 방법
- **미들웨어 구현**:  
  - 인증 및 인가 로직을 미들웨어로 분리하여 코드 중복을 줄이고 유지보수를 용이하게 만드는 방법

---

## Directory Structure 📁

```plaintext
03-backend-architecture/
└── authentication/
    ├── main.go           # JWT/OAuth 2.0 기반 인증 예제 코드
    ├── middleware.go     # 인증/인가 미들웨어 구현 (JWT 검증, RBAC 등)
    ├── auth.go           # 토큰 생성 및 검증 로직, 헬퍼 함수들
    ├── models/           # 사용자, 토큰 등 데이터 모델 정의
    └── README.md         # 이 문서
```

- **main.go**: 인증 관련 엔드포인트(예: 로그인, 토큰 갱신 등)를 제공하는 예제 코드가 포함되어 있습니다.
- **middleware.go**: 모든 API 요청에 대해 JWT 검증과 RBAC 체크를 수행하는 미들웨어가 구현되어 있습니다.
- **auth.go**: JWT 토큰 생성, 검증 및 기타 인증 관련 로직을 포함합니다.
- **models/**: 사용자 및 토큰과 관련된 데이터 구조체를 정의합니다.

---

## Getting Started 🚀

### 1. Prerequisites
- Go 최신 버전 설치: [Download Go](https://go.dev/dl/)
- 기본 Go 문법 및 RESTful API 개발에 익숙해지기

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/03-backend-architecture/authentication
```

### 3. 예제 코드 실행
```bash
go run main.go
```
- Postman 또는 curl을 사용하여 `/login` 등 인증 엔드포인트를 테스트해 보세요.

---

## Example Code Snippet 📄

아래는 JWT 기반 로그인 핸들러의 간단한 예제입니다:

```go
package main

import (
    "net/http"
    "time"

    "github.com/dgrijalva/jwt-go"
    "github.com/gin-gonic/gin"
)

// 비밀 키 (실제 환경에서는 환경 변수 또는 안전한 저장소를 사용)
var jwtSecret = []byte("your-secret-key")

// JWT 토큰 생성 함수
func GenerateJWT(username string) (string, error) {
    token := jwt.NewWithClaims(jwt.SigningMethodHS256, jwt.MapClaims{
        "username": username,
        "exp":      time.Now().Add(time.Hour * 1).Unix(), // 1시간 유효
    })
    return token.SignedString(jwtSecret)
}

// 로그인 핸들러: 사용자 인증 후 JWT 발급
func loginHandler(c *gin.Context) {
    var user struct {
        Username string `json:"username"`
        Password string `json:"password"`
    }
    if err := c.BindJSON(&user); err != nil {
        c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid input"})
        return
    }

    // 간단한 인증 로직 (실제 환경에서는 데이터베이스와 연동)
    if user.Username != "admin" || user.Password != "password" {
        c.JSON(http.StatusUnauthorized, gin.H{"error": "Unauthorized"})
        return
    }

    token, err := GenerateJWT(user.Username)
    if err != nil {
        c.JSON(http.StatusInternalServerError, gin.H{"error": "Could not generate token"})
        return
    }
    c.JSON(http.StatusOK, gin.H{"token": token})
}

func main() {
    router := gin.Default()
    router.POST("/login", loginHandler)
    router.Run(":8080")
}
```

이 예제는 간단한 로그인 엔드포인트를 제공하며, 올바른 자격 증명을 입력하면 JWT 토큰을 발급합니다.

---

## Best Practices & Tips 💡

- **비밀 키 관리**:  
  - 비밀 키는 소스 코드에 하드코딩하지 말고, 환경 변수나 별도의 비밀 관리 도구를 사용해 관리하세요.
  
- **HTTPS 사용**:  
  - 인증 토큰 전송 시 반드시 HTTPS를 사용하여 데이터 노출 위험을 줄이세요.
  
- **토큰 만료 및 갱신**:  
  - Access Token의 만료 시간을 적절하게 설정하고, Refresh Token을 통한 재발급 전략을 고려하세요.
  
- **RBAC 적용**:  
  - 인증 후, 사용자 역할과 권한을 기반으로 세밀한 접근 제어를 구현하세요.
  
- **미들웨어 통합**:  
  - 인증 및 인가 로직은 미들웨어로 분리하여, 모든 API 요청에 일관되게 적용하세요.

---

## Next Steps

- **OAuth 2.0 통합**:  
  - 타사 인증 제공자와 연동하거나, OAuth 2.0 플로우를 직접 구현해 보세요.
- **고급 RBAC 구현**:  
  - 사용자 역할 및 권한에 따라 접근 제어 정책을 정교하게 구성해 보세요.
- **테스트 및 문서화**:  
  - API 테스트 자동화 도구와 Swagger/OpenAPI를 활용해, API 문서를 생성하고 유지보수하세요.

---

## References 📚

- [JWT Introduction](https://jwt.io/introduction)
- [OAuth 2.0 Specification](https://oauth.net/2/)
- [Gin Middleware Documentation](https://github.com/gin-gonic/gin#using-middleware)
- [Go Security Best Practices](https://github.com/OWASP/Go-SCP)

---

API의 보안은 사용자의 신뢰를 구축하는 핵심 요소입니다.  
이 자료를 통해 강력하고 확장 가능한 인증/인가 시스템을 구축하여, 안전한 백엔드 서비스를 제공해 보세요! Happy Securing! 🔐🚀