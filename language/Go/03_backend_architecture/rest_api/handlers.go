// handlers.go
// 이 파일은 RESTful API 서버의 각 엔드포인트에 대한 핸들러 로직을 구현합니다.
// 예제에서는 사용자(User)와 주문(Order) 관련 기본 CRUD 동작을 수행하는 핸들러를 제공합니다.
// 실제 환경에서는 데이터베이스 연동 및 비즈니스 로직을 추가하여 확장할 수 있습니다.

package main

import (
	"net/http"
	"rest_api/models"
	"strconv"
	"time"

	"github.com/gin-gonic/gin"
)

// 예제 데이터: 메모리 상에서 사용자 정보를 관리하기 위한 슬라이스
var users = []models.User{
	{
		ID:        1,
		Username:  "alice",
		Email:     "alice@example.com",
		Password:  "hashed_password", // 실제 환경에서는 해시된 비밀번호를 저장
		CreatedAt: time.Now().Add(-48 * time.Hour),
		UpdatedAt: time.Now().Add(-24 * time.Hour),
	},
	{
		ID:        2,
		Username:  "bob",
		Email:     "bob@example.com",
		Password:  "hashed_password",
		CreatedAt: time.Now().Add(-72 * time.Hour),
		UpdatedAt: time.Now().Add(-12 * time.Hour),
	},
}

// 예제 데이터: 메모리 상에서 주문 정보를 관리하기 위한 슬라이스
var orders = []models.Order{
	{
		ID:     1,
		UserID: 1,
		Items: []models.OrderItem{
			{ProductID: 101, ProductName: "Product A", Quantity: 2, UnitPrice: 15.50},
			{ProductID: 102, ProductName: "Product B", Quantity: 1, UnitPrice: 25.00},
		},
		TotalAmount: 56.00, // (2*15.50 + 1*25.00)
		CreatedAt:   time.Now().Add(-24 * time.Hour),
		UpdatedAt:   time.Now().Add(-2 * time.Hour),
	},
}

// getUsers 핸들러는 모든 사용자를 조회하여 JSON 형태로 반환합니다.
func getUsers(c *gin.Context) {
	// 예제에서는 메모리 상의 사용자 슬라이스를 그대로 반환합니다.
	c.JSON(http.StatusOK, gin.H{"users": users})
}

// getUserByID 핸들러는 URL 파라미터로 전달된 ID를 기반으로 특정 사용자를 조회합니다.
func getUserByID(c *gin.Context) {
	// URL 파라미터로부터 사용자 ID를 문자열로 읽어온 후, 정수로 변환합니다.
	idStr := c.Param("id")
	id, err := strconv.ParseInt(idStr, 10, 64)
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "유효하지 않은 사용자 ID"})
		return
	}

	// 메모리 상의 사용자 슬라이스에서 해당 ID의 사용자를 검색합니다.
	for _, u := range users {
		if u.ID == id {
			c.JSON(http.StatusOK, u)
			return
		}
	}
	// 해당 사용자가 없는 경우 404 상태 코드 반환
	c.JSON(http.StatusNotFound, gin.H{"error": "사용자를 찾을 수 없습니다"})
}

// createUser 핸들러는 POST 요청으로 전달된 사용자 정보를 기반으로 새로운 사용자를 생성합니다.
func createUser(c *gin.Context) {
	var newUser models.User

	// 요청 바디를 JSON으로 파싱하여 newUser 구조체에 바인딩합니다.
	if err := c.ShouldBindJSON(&newUser); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "잘못된 입력 데이터"})
		return
	}

	// 사용자 데이터 검증: 실제로는 models.User의 ValidateUser() 같은 함수를 사용할 수 있습니다.
	if err := newUser.ValidateUser(); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	// 새로운 사용자의 ID는 현재 최대 ID + 1로 설정 (예제에서는 단순히 메모리 상에서 관리)
	newUser.ID = int64(len(users) + 1)
	newUser.CreatedAt = time.Now()
	newUser.UpdatedAt = time.Now()

	// 메모리 상의 사용자 슬라이스에 추가
	users = append(users, newUser)
	c.JSON(http.StatusCreated, newUser)
}

// getOrders 핸들러는 모든 주문 정보를 조회하여 JSON으로 반환합니다.
func getOrders(c *gin.Context) {
	c.JSON(http.StatusOK, gin.H{"orders": orders})
}

// getOrderByID 핸들러는 주문 ID를 기반으로 특정 주문을 조회합니다.
func getOrderByID(c *gin.Context) {
	idStr := c.Param("id")
	id, err := strconv.ParseInt(idStr, 10, 64)
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "유효하지 않은 주문 ID"})
		return
	}

	for _, o := range orders {
		if o.ID == id {
			c.JSON(http.StatusOK, o)
			return
		}
	}
	c.JSON(http.StatusNotFound, gin.H{"error": "주문을 찾을 수 없습니다"})
}

// createOrder 핸들러는 새로운 주문을 생성합니다.
// 요청 바디에서 주문 정보를 읽어, 총 금액을 계산한 후 주문을 저장합니다.
func createOrder(c *gin.Context) {
	var newOrder models.Order

	// 요청 데이터를 JSON으로 바인딩
	if err := c.ShouldBindJSON(&newOrder); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "잘못된 입력 데이터"})
		return
	}

	// 주문 검증 (실제 검증 로직은 models.Order의 ValidateOrder() 등을 활용)
	if err := newOrder.ValidateOrder(); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	// 주문의 총 금액 계산 (CalculateTotalAmount 메서드 활용)
	newOrder.TotalAmount = newOrder.CalculateTotalAmount()
	newOrder.ID = int64(len(orders) + 1)
	newOrder.CreatedAt = time.Now()
	newOrder.UpdatedAt = time.Now()

	orders = append(orders, newOrder)
	c.JSON(http.StatusCreated, newOrder)
}
