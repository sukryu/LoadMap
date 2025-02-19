/*
main.go
이 파일은 RESTful API 서버의 진입점(entry point)입니다.
주요 기능:
1. Gin 엔진을 초기화하고, 전역 미들웨어(로깅, CORS, 인증 등)를 설정합니다.
2. 라우팅 설정 파일(routes.go)에 정의된 엔드포인트를 등록합니다.
3. 서버를 지정된 포트에서 실행하여 클라이언트 요청을 처리합니다.

실제 운영 환경에서는 환경 변수, 구성 파일 등을 활용해 포트 번호 및 기타 설정을 관리할 수 있습니다.
*/

package main

import (
	"log"

	"github.com/gin-gonic/gin"
)

// main 함수는 서버를 초기화하고 실행합니다.
func main() {
	// 1. Gin 엔진 초기화
	// gin.Default()는 기본 미들웨어(로깅, Recovery)를 포함한 Gin 엔진 인스턴스를 생성합니다.
	router := gin.Default()

	// 2. 전역 미들웨어 설정
	// 미들웨어는 모든 요청에 대해 공통 기능(로깅, CORS, 인증 등)을 수행합니다.
	// middleware.go에 정의된 함수를 사용합니다.
	router.Use(LoggingMiddleware()) // 요청 로깅 미들웨어
	router.Use(CORSMiddleware())    // CORS 설정 미들웨어
	// 필요 시 AuthMiddleware() 같은 인증 미들웨어를 추가할 수 있습니다.
	// router.Use(AuthMiddleware())

	// 3. 라우팅 설정
	// routes.go에 정의된 setupRoutes 함수를 호출하여, 엔드포인트와 핸들러를 등록합니다.
	setupRoutes(router)

	// 4. 서버 실행
	// 실제 운영 환경에서는 포트 번호와 기타 설정을 환경 변수 또는 설정 파일로 관리합니다.
	port := ":8080"
	log.Printf("RESTful API 서버가 %s 포트에서 실행 중입니다...", port)
	if err := router.Run(port); err != nil {
		log.Fatalf("서버 실행 실패: %v", err)
	}
}
