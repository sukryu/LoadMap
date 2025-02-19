/*
이 예제는 Go의 plugin 패키지를 사용할 때 발생할 수 있는 다양한 오류 상황을 처리하는 방법을 보여줍니다.
주요 기능:
1. 플러그인 파일 로드 시, 파일이 존재하지 않거나 열리지 않을 경우의 에러 처리
2. 플러그인 내 심볼(Lookup) 검색 시, 심볼이 존재하지 않거나 타입이 일치하지 않을 경우의 에러 처리
3. 동적 함수 호출 시 발생할 수 있는 오류를 적절하게 처리하고 로그를 남기는 방법
4. 에러 발생 시, fallback 로직이나 사용자에게 명확한 오류 메시지를 제공하는 모범 사례를 제시

이 예제는 플러그인 로딩 과정에서의 견고한 에러 처리 전략을 수립하는 데 도움을 줍니다.
*/

package main

import (
	"fmt"
	"log"
	"plugin"
)

// loadPluginWithErrorHandling는 지정한 플러그인 파일을 로드하고, "Process" 심볼을 조회합니다.
// 오류 발생 시, 적절한 에러 메시지를 반환합니다.
func loadPluginWithErrorHandling(pluginPath string) (func(string) string, error) {
	// 플러그인 파일 열기
	plug, err := plugin.Open(pluginPath)
	if err != nil {
		return nil, fmt.Errorf("플러그인 로드 실패 (%s): %w", pluginPath, err)
	}

	// "Process" 심볼 조회
	symProcess, err := plug.Lookup("Process")
	if err != nil {
		return nil, fmt.Errorf("심볼 'Process' 조회 실패: %w", err)
	}

	// 심볼 타입 단언: 이 예제에서는 Process 함수가 string 인수를 받아 string을 반환한다고 가정합니다.
	processFunc, ok := symProcess.(func(string) string)
	if !ok {
		return nil, fmt.Errorf("심볼 'Process'의 타입이 예상과 다릅니다")
	}

	return processFunc, nil
}

func main5() {
	fmt.Println("=== Plugin Error Handling Demo ===")

	// --------------------------------------------------------------------
	// 1. 존재하지 않는 플러그인 파일을 로드하여 오류 처리 예제
	// --------------------------------------------------------------------
	fmt.Println("\n-- 예제 1: 존재하지 않는 플러그인 파일 로드 --")
	nonExistentPath := "nonexistent.so"
	_, err := loadPluginWithErrorHandling(nonExistentPath)
	if err != nil {
		log.Printf("[예제 1] 예상 오류 발생: %v\n", err)
	} else {
		log.Println("[예제 1] 오류 없이 플러그인 로드됨 (예상치 않음)")
	}

	// --------------------------------------------------------------------
	// 2. 존재하는 플러그인 파일에서 잘못된 심볼을 조회하여 오류 처리 예제
	// --------------------------------------------------------------------
	// 이 예제는 올바른 플러그인 파일(예: versionedplugin.so)이 준비되어 있어야 합니다.
	// 빌드 예: go build -buildmode=plugin -o versionedplugin.so examples/myplugin.go
	fmt.Println("\n-- 예제 2: 잘못된 심볼 조회 --")
	pluginPath := "versionedplugin.so"
	plug, err := plugin.Open(pluginPath)
	if err != nil {
		log.Fatalf("플러그인 로드 실패: %v\n", err)
	}
	// 존재하지 않는 심볼 "NonExistentSymbol"을 조회 시도합니다.
	_, err = plug.Lookup("NonExistentSymbol")
	if err != nil {
		log.Printf("[예제 2] 예상 오류 발생: %v\n", err)
	} else {
		log.Println("[예제 2] 잘못된 심볼이 조회되었습니다 (예상치 않음)")
	}

	// --------------------------------------------------------------------
	// 3. 올바른 플러그인 로드 및 타입 단언 오류 처리
	// --------------------------------------------------------------------
	fmt.Println("\n-- 예제 3: 올바른 플러그인 로드 및 타입 단언 검증 --")
	processFunc, err := loadPluginWithErrorHandling(pluginPath)
	if err != nil {
		log.Fatalf("플러그인 로드 또는 심볼 단언 실패: %v\n", err)
	}
	// 정상적으로 로드된 경우, Process 함수를 호출하여 결과를 출력합니다.
	input := "Test Input for Process Function"
	result := processFunc(input)
	fmt.Printf("Process 함수 호출 결과: %s\n", result)

	fmt.Println("\n=== Plugin Error Handling Demo 종료 ===")
}
