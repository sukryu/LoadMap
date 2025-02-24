// hsm_kms_integration.go
//
// 이 파일은 Production 환경에서도 사용할 수 있을 만큼 고도화된 예제 코드로, HSM 또는 클라우드 기반 KMS와 연동하여
// 키 관리 작업을 자동화하는 개념 증명을 제공합니다.
// 본 예제에서는 AWS KMS를 사용하여 데이터 키를 생성하고, 암호화 및 복호화를 수행하는 방법을 보여줍니다.
// 각 함수는 하나의 기능만 담당하며, 변수명과 함수명은 다른 파일과의 충돌을 피하기 위해 고유하게 작성되었습니다.
// 주석은 한국어로 상세하게 작성되어 있어, 초보자도 쉽게 이해할 수 있습니다.
//
// 참고: Production 환경에서는 AWS SDK v2를 사용하며, 적절한 IAM 권한과 구성 파일을 통해 KMS와 통신해야 합니다.

package examples

import (
	"context"
	"encoding/base64"
	"fmt"
	"log"

	"github.com/aws/aws-sdk-go-v2/aws"
	"github.com/aws/aws-sdk-go-v2/config"
	"github.com/aws/aws-sdk-go-v2/service/kms"
	"github.com/aws/aws-sdk-go-v2/service/kms/types"
)

// GenerateDataKey_KMSEx는 AWS KMS를 사용하여 데이터 키를 생성하는 함수입니다.
// 이 함수는 암호화되지 않은 평문 데이터 키(Plaintext Data Key)와, KMS로 암호화된 데이터 키(CiphertextBlob)를 함께 반환합니다.
// Production 환경에서는 평문 데이터 키를 메모리 내에서만 사용하고, 저장 시에는 암호화된 키만 보관하는 것이 안전합니다.
// 매개변수:
//   - keyID: 데이터 키 생성을 위해 사용할 KMS 키의 ID 또는 앨리어스 (예: "alias/my-key")
//   - keySpec: 생성할 데이터 키의 스펙 ("AES_256" 등)
//
// 반환값:
//   - *kms.GenerateDataKeyOutput: KMS로부터 반환된 데이터 키 생성 결과 (평문 및 암호화된 데이터 키 포함)
//   - error: 키 생성 과정 중 발생한 오류
func GenerateDataKey_KMSEx(keyID, keySpec string) (*kms.GenerateDataKeyOutput, error) {
	// AWS 기본 구성 로드 (환경 변수 또는 구성 파일 사용)
	cfg, err := config.LoadDefaultConfig(context.TODO())
	if err != nil {
		return nil, fmt.Errorf("AWS 구성 로드 실패: %v", err)
	}

	// KMS 클라이언트 생성
	kmsClient := kms.NewFromConfig(cfg)

	// 데이터 키 생성 입력 파라미터 설정
	input := &kms.GenerateDataKeyInput{
		KeyId:   aws.String(keyID),       // 사용할 KMS 키의 ID 또는 앨리어스
		KeySpec: types.DataKeySpecAes256, // 예: "AES_256"
	}

	// 데이터 키 생성 API 호출
	output, err := kmsClient.GenerateDataKey(context.TODO(), input)
	if err != nil {
		return nil, fmt.Errorf("데이터 키 생성 오류: %v", err)
	}

	return output, nil
}

// DecryptDataKey_KMSEx는 AWS KMS를 사용하여 암호화된 데이터 키(CiphertextBlob)를 복호화하는 함수입니다.
// 이 함수는 암호화된 데이터 키를 평문 데이터 키(Plaintext Data Key)로 복원합니다.
// 매개변수:
//   - encryptedKey: KMS에서 암호화된 데이터 키 ([]byte)
//
// 반환값:
//   - []byte: 복호화된 평문 데이터 키
//   - error: 복호화 과정 중 발생한 오류
func DecryptDataKey_KMSEx(encryptedKey []byte) ([]byte, error) {
	// AWS 기본 구성 로드
	cfg, err := config.LoadDefaultConfig(context.TODO())
	if err != nil {
		return nil, fmt.Errorf("AWS 구성 로드 실패: %v", err)
	}

	// KMS 클라이언트 생성
	kmsClient := kms.NewFromConfig(cfg)

	// 데이터 키 복호화 입력 파라미터 설정
	input := &kms.DecryptInput{
		CiphertextBlob: encryptedKey,
	}

	// 데이터 키 복호화 API 호출
	output, err := kmsClient.Decrypt(context.TODO(), input)
	if err != nil {
		return nil, fmt.Errorf("데이터 키 복호화 오류: %v", err)
	}

	return output.Plaintext, nil
}

// ExampleUsage_KMSEx는 HSM/KMS 연동을 통해 데이터 키를 생성하고, 복호화하는 개념 증명을 위한 예제 함수입니다.
// Production 환경에서는 main 함수 대신 별도의 테스트나 워크플로우에서 호출하여 사용할 수 있습니다.
// 이 함수는 평문 데이터 키를 직접 노출하지 않고, 암호화된 키만 저장하거나 전송하는 방식을 시연합니다.
func ExampleUsage_KMSEx() {
	// 예제: KMS 키 식별자 및 스펙 설정
	kmsKeyID := "alias/my-production-key" // 실제 환경에서는 적절한 KMS 키 ID 또는 앨리어스를 사용
	dataKeySpec := "AES_256"

	// 1. 데이터 키 생성
	dataKeyOutput, err := GenerateDataKey_KMSEx(kmsKeyID, dataKeySpec)
	if err != nil {
		log.Fatalf("데이터 키 생성 실패: %v", err)
	}
	// dataKeyOutput.Plaintext: 평문 데이터 키 (메모리 내에서만 사용해야 함)
	// dataKeyOutput.CiphertextBlob: 암호화된 데이터 키 (저장, 전송 용도)

	fmt.Printf("생성된 평문 데이터 키 (Base64): %s\n",
		aws.ToString(aws.String(base64Encode(dataKeyOutput.Plaintext))))
	fmt.Printf("생성된 암호화된 데이터 키 (Base64): %s\n",
		aws.ToString(aws.String(base64Encode(dataKeyOutput.CiphertextBlob))))

	// 2. 암호화된 데이터 키 복호화 (필요 시)
	plaintextKey, err := DecryptDataKey_KMSEx(dataKeyOutput.CiphertextBlob)
	if err != nil {
		log.Fatalf("데이터 키 복호화 실패: %v", err)
	}
	fmt.Printf("복호화된 평문 데이터 키 (Base64): %s\n",
		aws.ToString(aws.String(base64Encode(plaintextKey))))
}

// base64Encode는 바이트 슬라이스를 Base64 문자열로 인코딩하는 헬퍼 함수입니다.
func base64Encode(data []byte) string {
	return base64.StdEncoding.EncodeToString(data)
}

/*
-------------------------------------------
HSM/KMS 연동 개념 증명 개요

1. GenerateDataKey_KMSEx 함수:
   - AWS KMS를 사용하여 지정된 KMS 키로 데이터 키를 생성합니다.
   - 반환된 결과에는 평문 데이터 키와 암호화된 데이터 키가 포함됩니다.
   - 평문 데이터 키는 메모리 내에서만 사용하고, 저장 또는 전송 시에는 암호화된 키만 사용해야 합니다.

2. DecryptDataKey_KMSEx 함수:
   - 암호화된 데이터 키를 AWS KMS를 통해 복호화하여 평문 데이터 키를 얻습니다.

3. ExampleUsage_KMSEx 함수:
   - 위 두 함수를 통합하여 데이터 키 생성 및 복호화 과정을 시연합니다.
   - Production 환경에서는 평문 키 노출을 최소화하고, 암호화된 키를 안전하게 관리해야 합니다.

Production 환경에서는 이와 같은 HSM/KMS 연동을 통해 키 관리 작업을 자동화하고, 보안을 강화할 수 있습니다.
-------------------------------------------
*/
