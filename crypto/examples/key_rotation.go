// key_rotation.go
//
// 이 파일은 Production 환경에서도 사용할 수 있을 만큼 고도화된 키 순환 및 수명주기 관리 시뮬레이션 예제 코드입니다.
// 본 예제는 대칭키의 수명주기를 관리하는 기본적인 시뮬레이션 기능을 제공합니다.
// - 키 생성: 암호학적으로 안전한 난수를 사용하여 대칭키를 생성합니다.
// - 키 순환: 주어진 순환 주기(rotationPeriod)가 경과한 경우, 새로운 키로 교체하고 기존 키는 폐기합니다.
// 각 함수는 하나의 기능만 담당하며, 변수명과 함수명은 다른 파일과의 충돌을 피하기 위해 고유하게 작성되었습니다.
// 주석은 한국어로 상세하게 작성되어 있어, 초보자도 쉽게 이해할 수 있습니다.

package examples

import (
	"crypto/rand"
	"encoding/base64"
	"errors"
	"fmt"
	"io"
	"time"
)

// KeyRecord_KR는 대칭키와 해당 키의 생성 시간을 기록하는 구조체입니다.
type KeyRecord_KR struct {
	SymKey    []byte    // 대칭키 (예: AES 키)
	CreatedAt time.Time // 키 생성 시간
}

// GenerateSymmetricKey_KR는 주어진 길이(keyLen 바이트)의 암호학적으로 안전한 대칭키를 생성하는 함수입니다.
// Production 환경에서는 AES-256을 위해 32바이트 키를 사용하는 것이 권장됩니다.
// 반환값:
//   - []byte: 생성된 대칭키
//   - error: 키 생성 중 발생한 오류
func GenerateSymmetricKey_KR(keyLen int) ([]byte, error) {
	// 유효한 키 길이 검증 (예: 16, 24, 32바이트)
	if keyLen != 16 && keyLen != 24 && keyLen != 32 {
		return nil, errors.New("유효하지 않은 키 길이: 키는 16, 24 또는 32바이트여야 합니다")
	}

	newKey := make([]byte, keyLen)
	if _, err := io.ReadFull(rand.Reader, newKey); err != nil {
		return nil, fmt.Errorf("대칭키 생성 실패: %v", err)
	}
	return newKey, nil
}

// RotateKeyIfExpired_KR는 기존의 KeyRecord_KR를 확인하여, 지정된 rotationDuration이 경과한 경우 새로운 키로 교체하는 함수입니다.
// 입력:
//   - currentRecord: 현재 저장된 키 기록 (*KeyRecord_KR)
//   - rotationDuration: 키 순환 주기 (time.Duration)
//   - keyLength: 생성할 대칭키의 길이 (예: 32바이트)
//
// 반환값:
//   - *KeyRecord_KR: 갱신된 키 기록 (새로운 키가 생성된 경우), 기존 레코드 그대로 반환될 수 있음
//   - bool: 키가 교체되었으면 true, 그렇지 않으면 false
//   - error: 키 생성 또는 순환 과정 중 발생한 오류
func RotateKeyIfExpired_KR(currentRecord *KeyRecord_KR, rotationDuration time.Duration, keyLength int) (*KeyRecord_KR, bool, error) {
	if currentRecord == nil {
		return nil, false, errors.New("현재 키 기록이 nil입니다")
	}

	// 현재 키가 순환 주기를 초과했는지 확인
	if time.Since(currentRecord.CreatedAt) < rotationDuration {
		// 순환 주기 미만이면 키 교체 없음
		return currentRecord, false, nil
	}

	// 새로운 대칭키 생성
	newKey, err := GenerateSymmetricKey_KR(keyLength)
	if err != nil {
		return nil, false, fmt.Errorf("새 대칭키 생성 실패: %v", err)
	}

	// 새로운 키 기록 생성 및 반환
	updatedRecord := &KeyRecord_KR{
		SymKey:    newKey,
		CreatedAt: time.Now(),
	}
	return updatedRecord, true, nil
}

// ExportKeyToPEM_KR는 대칭키를 Base64 인코딩된 문자열 형태로 변환하여 반환하는 함수입니다.
// 이 함수는 키를 안전하게 파일에 저장하거나 로그 기록 시 활용할 수 있도록 합니다.
// 입력:
//   - symKey: 대칭키 ([]byte)
//
// 반환값:
//   - string: Base64 인코딩된 대칭키 문자열
func ExportKeyToPEM_KR(symKey []byte) string {
	// Base64 인코딩을 사용하여 키를 문자열로 변환
	return base64.StdEncoding.EncodeToString(symKey)
}

/*
-------------------------------------------
키 순환 및 수명주기 관리 시뮬레이션 개요

1. KeyRecord_KR 구조체는 대칭키와 생성 시간을 저장합니다.
2. GenerateSymmetricKey_KR 함수는 암호학적으로 안전한 난수를 사용하여 대칭키를 생성합니다.
3. RotateKeyIfExpired_KR 함수는 주어진 순환 주기(rotationDuration)가 경과한 경우,
   새로운 대칭키를 생성하여 기존 키를 교체합니다.
4. ExportKeyToPEM_KR 함수는 대칭키를 Base64 문자열로 변환하여, 파일 저장이나 로그 기록에 활용할 수 있도록 합니다.

Production 환경에서는 키 순환 주기를 조직의 보안 정책에 맞게 설정하고,
자동화된 도구와 함께 사용하여 키의 안전성과 효율성을 유지해야 합니다.
-------------------------------------------
*/
