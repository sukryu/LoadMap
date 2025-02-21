// handler.go
//
// 이 파일은 AWS Lambda에서 호출될 함수 핸들러를 정의합니다.
// Lambda 런타임은 이 함수를 통해 전달된 이벤트 데이터를 처리하고, 결과를 반환합니다.
// 본 핸들러는 이벤트 객체에서 "name" 필드를 읽어 인사말 메시지를 생성하는 간단한 예제를 보여줍니다.

package main

import (
	"context" // Lambda 함수의 실행 컨텍스트를 제공
	"fmt"     // 문자열 포매팅을 위해 사용
	"log"     // 로그 출력 (CloudWatch Logs 등과 연동 가능)
)

// Handler 함수는 AWS Lambda 함수의 진입점입니다.
// context.Context: Lambda 실행 컨텍스트, 타임아웃, 취소 신호 등을 포함합니다.
// event: Lambda 함수로 전달된 이벤트 데이터를 나타내는 map. JSON 형식의 이벤트가 파싱되어 전달됩니다.
// 반환값: 생성된 메시지와 에러 (에러 발생 시 non-nil 값 반환)
func Handler(ctx context.Context, event map[string]interface{}) (string, error) {
	// 이벤트 객체에서 "name" 값을 추출합니다.
	// 만약 "name" 필드가 없거나 값이 비어 있으면 기본값 "Gopher"를 사용합니다.
	name, ok := event["name"].(string)
	if !ok || name == "" {
		name = "Gopher"
	}

	// 인사말 메시지를 생성합니다.
	// fmt.Sprintf를 사용하여 동적으로 메시지를 포맷합니다.
	message := fmt.Sprintf("Hello, %s! Welcome to Serverless with Go.", name)

	// 로그에 처리 결과를 기록합니다.
	// 이는 디버깅 및 모니터링에 유용하며, CloudWatch Logs 등으로 전송될 수 있습니다.
	log.Printf("Handler processed event for name: %s", name)

	// 생성된 메시지와 nil 에러를 반환합니다.
	return message, nil
}
