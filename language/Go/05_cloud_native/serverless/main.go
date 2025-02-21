// main.go
//
// 이 파일은 AWS Lambda에서 실행될 Go 기반 서버리스 애플리케이션의 진입점입니다.
// AWS Lambda는 이 main 함수에서 lambda.Start() 호출을 통해 등록된 핸들러 함수를 실행합니다.
// 본 예제에서는 이벤트 데이터를 받아 "name" 필드를 확인한 후 인사말 메시지를 반환하는 간단한 핸들러를 사용합니다.

package main

import (
	// AWS Lambda Go SDK를 임포트합니다.
	"github.com/aws/aws-lambda-go/lambda"

	// 로그 출력을 위해 표준 log 패키지를 임포트합니다.
	"log"
)

// Handler 함수는 Lambda 이벤트를 처리하는 핵심 함수입니다.
// 이 함수는 AWS Lambda가 호출할 때 전달받은 이벤트 데이터를 처리하고 결과를 반환합니다.
// 예제에서는 event 객체(맵 형태)에서 "name" 필드를 읽어 인사말 메시지를 생성합니다.
func Handler1(event map[string]interface{}) (string, error) {
	// 이벤트에서 "name" 값을 추출합니다.
	// 만약 "name" 필드가 없거나 빈 문자열이면 기본값 "Gopher"를 사용합니다.
	name, ok := event["name"].(string)
	if !ok || name == "" {
		name = "Gopher"
	}

	// 인사말 메시지 생성
	message := "Hello, " + name + "! Welcome to Serverless with Go."

	// 처리 결과를 로그에 기록 (운영 중 모니터링 및 디버깅에 유용)
	log.Printf("Processed event for name: %s", name)

	// 생성된 인사말 메시지를 반환합니다.
	return message, nil
}

// main 함수는 Lambda 런타임에 핸들러 함수를 등록합니다.
// lambda.Start() 함수는 AWS Lambda 런타임이 이 함수를 통해 전달된 핸들러를 호출하도록 합니다.
func main() {
	// Handler 함수를 AWS Lambda 런타임에 등록합니다.
	// 이 호출 이후 main 함수는 종료되지만, Lambda 런타임은 등록된 핸들러를 계속 호출합니다.
	lambda.Start(Handler1)
}
