// routes.go
// 이 파일은 RESTful API 서버의 라우팅 설정을 담당합니다.
// Gin 프레임워크를 사용하여, API 버전 및 그룹별로 엔드포인트를 구성합니다.
// 핸들러 함수들은 handlers.go 파일에 정의되어 있으며, 여기서 각 핸들러와 HTTP 메서드를 연결합니다.

package main

import (
	"github.com/gin-gonic/gin"
)

// setupRoutes 함수는 전체 API 라우터 설정을 수행합니다.
// 이 함수는 API 버전 관리와 관련 엔드포인트를 그룹화하여 설정합니다.
func setupRoutes(router *gin.Engine) {
	// API 버전을 관리하기 위해 "/api/v1" 그룹을 생성합니다.
	apiV1 := router.Group("/api/v1")
	{
		// 사용자 관련 엔드포인트 설정
		// GET /api/v1/users: 모든 사용자 목록을 조회합니다.
		apiV1.GET("/users", getUsers)
		// GET /api/v1/users/:id: URL 파라미터로 전달된 사용자 ID에 해당하는 사용자를 조회합니다.
		apiV1.GET("/users/:id", getUserByID)
		// POST /api/v1/users: 요청 바디의 JSON 데이터를 이용하여 새로운 사용자를 생성합니다.
		apiV1.POST("/users", createUser)

		// 주문 관련 엔드포인트 설정
		// GET /api/v1/orders: 모든 주문 정보를 조회합니다.
		apiV1.GET("/orders", getOrders)
		// GET /api/v1/orders/:id: URL 파라미터로 전달된 주문 ID에 해당하는 주문을 조회합니다.
		apiV1.GET("/orders/:id", getOrderByID)
		// POST /api/v1/orders: 요청 바디의 JSON 데이터를 기반으로 새로운 주문을 생성합니다.
		apiV1.POST("/orders", createOrder)
	}
}
