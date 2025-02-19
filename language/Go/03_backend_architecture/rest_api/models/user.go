// models/user.go
// 이 파일은 RESTful API 서버에서 사용되는 데이터 모델 중 'User' 모델을 정의합니다.
// User 모델은 사용자 정보를 표현하며, JSON 직렬화 및 데이터 검증을 위한 태그를 포함합니다.

package models

import (
	"fmt"
	"strings"
	"time"
)

// User 구조체는 사용자 정보를 담는 데이터 모델입니다.
// 실무에서는 이 모델을 기반으로 데이터베이스 CRUD 작업, API 요청/응답 데이터 모델로 활용합니다.
type User struct {
	// ID는 사용자의 고유 식별자입니다.
	// 데이터베이스에서는 자동 증가 필드로 사용될 수 있습니다.
	ID int64 `json:"id"`

	// Username은 사용자의 로그인 이름입니다.
	// 반드시 고유해야 하며, 최소 3자 이상, 최대 50자 이하로 제한됩니다.
	Username string `json:"username" validate:"required,min=3,max=50"`

	// Email은 사용자의 이메일 주소를 나타냅니다.
	// 올바른 이메일 형식인지 검증이 필요하며, 클라이언트와의 데이터 교환 시 JSON 직렬화됩니다.
	Email string `json:"email" validate:"required,email"`

	// Password는 사용자의 암호를 나타냅니다.
	// 보안을 위해 실제 운영 환경에서는 해시된 값을 저장하며, API 응답 시 제외하는 것이 일반적입니다.
	Password string `json:"-"`

	// CreatedAt은 사용자가 생성된 날짜 및 시간을 기록합니다.
	// 서버 측에서 자동으로 설정되며, 변경 불가능한 정보입니다.
	CreatedAt time.Time `json:"created_at"`

	// UpdatedAt은 사용자 정보가 마지막으로 업데이트된 날짜 및 시간을 기록합니다.
	// 업데이트 시 서버 측에서 자동으로 변경됩니다.
	UpdatedAt time.Time `json:"updated_at"`
}

// ValidateUser 함수는 User 구조체의 필수 필드 및 조건을 검증합니다.
// 실무에서는 외부 검증 라이브러리(예: go-playground/validator)를 사용할 수 있지만,
// 여기서는 간단한 로직으로 예제를 제공합니다.
func (u *User) ValidateUser() error {
	// Username 길이 검증: 최소 3자, 최대 50자
	if len(u.Username) < 3 || len(u.Username) > 50 {
		return fmt.Errorf("username은 3자 이상 50자 이하이어야 합니다")
	}
	// Email이 비어있는지 및 간단한 형식 검증
	if u.Email == "" || !isValidEmail(u.Email) {
		return fmt.Errorf("유효한 email 주소가 필요합니다")
	}
	// 추가 검증 로직 (예: Password 복잡도 등)을 여기에 추가할 수 있습니다.
	return nil
}

// isValidEmail 함수는 아주 단순한 방식으로 이메일 형식을 검증합니다.
// 실제 운영 환경에서는 정규표현식을 이용한 보다 정교한 검증을 권장합니다.
func isValidEmail(email string) bool {
	// '@' 문자가 포함되어 있는지만 확인
	return strings.Contains(email, "@")
}
