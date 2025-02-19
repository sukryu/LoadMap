// middleware.go
// 이 파일은 RESTful API 서버에서 사용될 미들웨어들을 정의합니다.
// 미들웨어는 API 요청 전후에 공통 작업(로깅, CORS 처리, 인증 등)을 수행하여,
// 핸들러 코드의 중복을 줄이고, 보안 및 모니터링을 강화할 수 있습니다.

package main

import (
	"log"
	"net/http"
	"strings"
	"time"

	"github.com/gin-gonic/gin"
)

// LoggingMiddleware는 각 요청에 대해 로그를 남기는 미들웨어입니다.
// 요청 시작 시간, 요청 경로, 상태 코드, 처리 시간 등을 기록하여 디버깅과 모니터링에 활용할 수 있습니다.
func LoggingMiddleware() gin.HandlerFunc {
	return func(c *gin.Context) {
		// 요청 시작 시각을 기록합니다.
		startTime := time.Now()

		// 다음 핸들러나 미들웨어로 요청을 전달합니다.
		c.Next()

		// 요청 처리 완료 후 경과 시간을 계산합니다.
		elapsed := time.Since(startTime)

		// 요청 URL, 상태 코드, 처리 시간을 로그에 기록합니다.
		log.Printf("요청: %s | 상태: %d | 처리 시간: %v",
			c.Request.URL.Path, c.Writer.Status(), elapsed)
	}
}

// CORSMiddleware는 Cross-Origin Resource Sharing (CORS) 설정을 위한 미들웨어입니다.
// 모든 도메인에서의 요청을 허용하고, 특정 헤더와 메서드를 지원하도록 설정하여, 클라이언트와의 통신을 원활하게 합니다.
func CORSMiddleware() gin.HandlerFunc {
	return func(c *gin.Context) {
		// 모든 도메인에서의 요청 허용
		c.Writer.Header().Set("Access-Control-Allow-Origin", "*")
		// 쿠키 등 인증 정보를 포함한 요청 허용
		c.Writer.Header().Set("Access-Control-Allow-Credentials", "true")
		// 허용할 헤더 목록 설정
		c.Writer.Header().Set("Access-Control-Allow-Headers", "Content-Type, Authorization, Content-Length, X-Requested-With")
		// 허용할 HTTP 메서드 설정
		c.Writer.Header().Set("Access-Control-Allow-Methods", "GET, POST, PUT, PATCH, DELETE, OPTIONS")

		// OPTIONS 요청은 사전 플리핑(preflight) 요청으로, 별도로 처리 후 응답합니다.
		if c.Request.Method == "OPTIONS" {
			c.AbortWithStatus(http.StatusNoContent)
			return
		}

		// 다음 미들웨어 또는 핸들러로 요청 전달
		c.Next()
	}
}

// AuthMiddleware는 간단한 인증 미들웨어 예제입니다.
// 요청 헤더의 "Authorization" 값을 검사하여, 올바른 토큰이 포함되어 있는지 확인합니다.
func AuthMiddleware() gin.HandlerFunc {
	return func(c *gin.Context) {
		// "Authorization" 헤더 값을 가져옵니다.
		authHeader := c.GetHeader("Authorization")
		if authHeader == "" {
			c.JSON(http.StatusUnauthorized, gin.H{"error": "Authorization 헤더가 필요합니다"})
			c.Abort()
			return
		}

		// 헤더 값은 "Bearer {token}" 형식이어야 합니다.
		parts := strings.Split(authHeader, " ")
		if len(parts) != 2 || parts[0] != "Bearer" {
			c.JSON(http.StatusUnauthorized, gin.H{"error": "잘못된 Authorization 형식입니다"})
			c.Abort()
			return
		}

		token := parts[1]
		// 실제 환경에서는 JWT 검증 등 복잡한 인증 로직을 적용합니다.
		// 여기서는 단순 예제로 토큰이 "mysecrettoken"과 일치하는지 검사합니다.
		if token != "mysecrettoken" {
			c.JSON(http.StatusUnauthorized, gin.H{"error": "인증 실패: 잘못된 토큰입니다"})
			c.Abort()
			return
		}

		// 인증이 성공하면, 다음 핸들러로 요청을 전달합니다.
		c.Next()
	}
}
