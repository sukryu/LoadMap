# RESTful API Design & Best Practices in Go 🌐

이 디렉토리는 **Go** 언어를 사용하여 RESTful API를 설계하고 구축하는 방법에 대해 다룹니다.  
REST의 기본 원칙, 엔드포인트 설계, HTTP 메서드와 상태 코드 사용, 에러 핸들링 및 미들웨어 적용 등 실무에 바로 적용할 수 있는 베스트 프랙티스를 소개합니다.

---

## What You'll Learn 🎯

- **RESTful 아키텍처의 기본 원칙**:  
  - Stateless, Resource-Based, Uniform Interface 등의 핵심 개념 이해

- **엔드포인트 설계**:  
  - HTTP 메서드(GET, POST, PUT, DELETE)와 URL 설계 전략  
  - API 버전 관리 및 명확한 리소스 명명 규칙

- **에러 핸들링 & 응답 포맷**:  
  - 적절한 상태 코드 사용, 에러 메시지 포맷, JSON 응답 구조 설계

- **미들웨어 활용**:  
  - 인증, 로깅, CORS, 요청 유효성 검사 등 공통 기능 구현

- **테스트 및 문서화**:  
  - API 테스트 도구 활용, Swagger/OpenAPI 문서 자동화

---

## Directory Structure 📁

```plaintext
03-backend-architecture/
└── rest-api/
    ├── main.go         # 기본 REST API 서버 예제 (예: Gin 또는 Fiber 활용)
    ├── handlers.go     # API 엔드포인트 핸들러 구현
    ├── middleware.go   # 인증, 로깅, CORS 등의 미들웨어 구현
    ├── routes.go       # 라우팅 및 엔드포인트 설정
    ├── models/         # 데이터 모델 정의 (예: DTO, Request/Response 구조체)
    └── README.md       # 이 문서
```

- **main.go**: 애플리케이션의 진입점으로, 서버 초기화 및 라우터 구성이 포함됩니다.
- **handlers.go**: 각 엔드포인트의 실제 로직을 구현합니다.
- **middleware.go**: 공통 미들웨어(인증, 로깅 등)를 정의하여, 요청 전후에 처리할 작업을 수행합니다.
- **routes.go**: RESTful 엔드포인트와 HTTP 메서드를 설정하는 라우팅 로직이 포함됩니다.
- **models/**: API에서 사용되는 데이터 구조체와 DTO(Data Transfer Object)를 정의합니다.

---

## Getting Started 🚀

### 1. 필수 도구 설치
- Go 최신 버전: [Download Go](https://go.dev/dl/)
- API 프레임워크: Gin 또는 Fiber (예제에서는 Gin 사용)

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/03-backend-architecture/rest-api
```

### 3. 예제 코드 실행
```bash
go run main.go
```
- 브라우저 또는 API 테스트 도구(Postman, curl 등)를 사용해 엔드포인트를 호출해 보세요.

---

## Example Code Snippet 📄

아래는 Gin을 활용한 간단한 REST API 예제입니다:

```go
package main

import (
    "net/http"

    "github.com/gin-gonic/gin"
)

// User represents a simple user model
type User struct {
    ID   int    `json:"id"`
    Name string `json:"name"`
}

// getUsers 핸들러: 모든 사용자 목록을 반환
func getUsers(c *gin.Context) {
    users := []User{
        {ID: 1, Name: "Alice"},
        {ID: 2, Name: "Bob"},
    }
    c.JSON(http.StatusOK, gin.H{"users": users})
}

func main() {
    router := gin.Default()

    // 라우팅 설정
    api := router.Group("/api/v1")
    {
        api.GET("/users", getUsers)
        // POST, PUT, DELETE 등의 엔드포인트 추가 가능
    }

    // 서버 실행 (기본 포트 8080)
    router.Run(":8080")
}
```

이 예제는 `/api/v1/users` 엔드포인트를 통해 간단한 사용자 목록을 JSON 형식으로 반환합니다.

---

## Best Practices & Tips 💡

- **명확한 리소스 명명 규칙**:  
  - REST API 설계 시 리소스(예: `/users`, `/orders`)를 명확하게 정의하고, HTTP 메서드에 따라 적절한 동작을 매핑합니다.

- **상태 코드 사용**:  
  - 200, 201, 400, 401, 404, 500 등의 HTTP 상태 코드를 상황에 맞게 사용하여 클라이언트에 명확한 피드백을 제공합니다.

- **미들웨어 활용**:  
  - 인증, 로깅, CORS 등 반복적인 작업은 미들웨어로 분리하여 코드 중복을 줄이고 유지보수를 쉽게 합니다.

- **API 문서화**:  
  - Swagger/OpenAPI를 활용해 API 문서를 자동으로 생성하고, 팀원 및 사용자와 공유하세요.

- **에러 핸들링**:  
  - 에러 발생 시 일관된 응답 구조를 사용하고, 민감 정보 노출을 방지하세요.

---

## Next Steps

- **고급 주제**:  
  - API 버전 관리, rate limiting, 캐싱 및 로드 밸런싱 전략 등 고급 API 설계 기법을 추가로 학습하세요.
- **테스트**:  
  - 단위 테스트와 통합 테스트를 통해 API의 신뢰성을 높이고, CI/CD 파이프라인에 통합하세요.
- **보안**:  
  - API 인증 및 인가, 입력값 검증, 데이터 암호화 등 보안 모범 사례를 확립하세요.

---

## 참고 자료 📚

- [RESTful API Design Guide](https://restfulapi.net/)
- [Gin Framework Documentation](https://gin-gonic.com/docs/)
- [OpenAPI/Swagger Documentation](https://swagger.io/specification/)
- [HTTP Status Codes Reference](https://developer.mozilla.org/en-US/docs/Web/HTTP/Status)

---

RESTful API 설계는 현대 백엔드 개발의 핵심입니다.  
이 자료를 통해 견고하고 확장 가능한 API를 설계하고, 실무에 바로 적용해 보세요! Happy API Building! 🚀