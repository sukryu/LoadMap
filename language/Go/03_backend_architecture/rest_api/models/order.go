// models/order.go
// 이 파일은 RESTful API 서버에서 사용되는 데이터 모델 중 'Order' 모델을 정의합니다.
// Order 모델은 주문 정보를 표현하며, JSON 직렬화 및 데이터 검증을 위한 태그를 포함합니다.

package models

import (
	"fmt"
	"time"
)

// OrderItem 구조체는 주문 항목을 나타냅니다.
// 각 주문 항목은 상품 ID, 상품 이름, 수량, 단가 등의 정보를 포함합니다.
type OrderItem struct {
	// ProductID는 주문 항목에 해당하는 상품의 고유 식별자입니다.
	ProductID int64 `json:"product_id" validate:"required"`

	// ProductName은 상품의 이름입니다.
	ProductName string `json:"product_name" validate:"required"`

	// Quantity는 주문된 상품의 수량입니다.
	Quantity int `json:"quantity" validate:"required,gte=1"`

	// UnitPrice는 상품의 단가입니다.
	UnitPrice float64 `json:"unit_price" validate:"required,gt=0"`
}

// Order 구조체는 전체 주문 정보를 나타냅니다.
// 주문은 여러 주문 항목(OrderItem)과 주문자, 주문 총액, 생성/업데이트 시간 등의 정보를 포함합니다.
type Order struct {
	// ID는 주문의 고유 식별자입니다.
	ID int64 `json:"id"`

	// UserID는 주문을 생성한 사용자의 고유 식별자입니다.
	UserID int64 `json:"user_id" validate:"required"`

	// Items는 주문에 포함된 주문 항목들의 리스트입니다.
	Items []OrderItem `json:"items" validate:"required,dive,required"`

	// TotalAmount는 주문의 총 금액을 나타냅니다.
	// 일반적으로 모든 주문 항목의 (Quantity * UnitPrice)의 합계로 계산됩니다.
	TotalAmount float64 `json:"total_amount" validate:"required,gt=0"`

	// CreatedAt은 주문이 생성된 날짜 및 시간을 기록합니다.
	// 서버 측에서 자동으로 설정되며, 변경 불가능한 정보입니다.
	CreatedAt time.Time `json:"created_at"`

	// UpdatedAt은 주문 정보가 마지막으로 업데이트된 날짜 및 시간을 기록합니다.
	// 주문 수정 시 서버 측에서 자동으로 변경됩니다.
	UpdatedAt time.Time `json:"updated_at"`
}

// CalculateTotalAmount 함수는 주문에 포함된 모든 항목의 총 금액을 계산하여 반환합니다.
// 이 함수는 주문 생성 또는 업데이트 시 호출되어, TotalAmount 필드를 설정하는 데 사용될 수 있습니다.
func (o *Order) CalculateTotalAmount() float64 {
	var total float64 = 0
	for _, item := range o.Items {
		total += float64(item.Quantity) * item.UnitPrice
	}
	return total
}

// ValidateOrder 함수는 Order 구조체의 각 필드에 대해 간단한 검증을 수행합니다.
// 필수 필드의 존재, 주문 항목이 비어있지 않은지, 총 금액 계산이 올바른지 등을 확인합니다.
func (o *Order) ValidateOrder() error {
	// UserID는 반드시 0보다 커야 합니다.
	if o.UserID <= 0 {
		return fmt.Errorf("유효하지 않은 UserID: %d", o.UserID)
	}
	// 주문 항목이 최소 하나 이상 존재해야 합니다.
	if len(o.Items) == 0 {
		return fmt.Errorf("주문 항목이 하나 이상 필요합니다")
	}
	// 각 주문 항목에 대해 검증 (여기서는 간단한 예시로, Quantity와 UnitPrice만 검사)
	for i, item := range o.Items {
		if item.Quantity < 1 {
			return fmt.Errorf("주문 항목 %d의 수량은 최소 1 이상이어야 합니다", i)
		}
		if item.UnitPrice <= 0 {
			return fmt.Errorf("주문 항목 %d의 단가는 0보다 커야 합니다", i)
		}
	}
	// 총 금액이 올바른지 계산 후 비교 (총 금액이 0이면 오류 처리)
	calculatedTotal := o.CalculateTotalAmount()
	if calculatedTotal <= 0 {
		return fmt.Errorf("계산된 총 금액이 올바르지 않습니다: %.2f", calculatedTotal)
	}
	return nil
}
