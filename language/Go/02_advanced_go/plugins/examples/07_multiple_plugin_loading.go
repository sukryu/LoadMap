/*
이 예제는 다중 플러그인 로딩(Multi Plugin Loading)을 구현합니다.
목표:
1. 지정된 폴더(예: "plugins/") 내의 모든 .so 파일 목록을 Glob 함수를 통해 가져옵니다.
2. 각 플러그인 파일을 고루틴을 사용하여 동시에 로드합니다.
3. 각 플러그인에서 "Hello"와 같은 공개 함수 심볼을 Lookup하여, 동적으로 함수를 호출합니다.
4. 각 플러그인 로딩 결과 및 함수 호출 결과를 출력합니다.

주의:
- 각 플러그인의 함수가 동시 호출에 안전한지 확인해야 합니다.
- 플러그인 파일은 미리 빌드되어 있어야 하며, 각 파일은 Exported 함수(예: Hello)가 있어야 합니다.
*/

package main

import (
	"fmt"
	"log"
	"path/filepath"
	"plugin"
	"sync"
	"time"
)

// loadPluginAndCall는 주어진 플러그인 파일을 로드하고, "Hello" 심볼을 조회한 후 동적으로 호출하는 함수입니다.
// 플러그인 내 "Hello" 함수는 string 인수를 받아 인사 메시지를 출력한다고 가정합니다.
func loadPluginAndCall(pluginPath string, wg *sync.WaitGroup) {
	defer wg.Done()

	// 플러그인 파일 로드
	plug, err := plugin.Open(pluginPath)
	if err != nil {
		log.Printf("[Error] 플러그인 로드 실패 (%s): %v\n", pluginPath, err)
		return
	}
	log.Printf("플러그인 로드 성공: %s\n", pluginPath)

	// "Hello" 심볼 조회: 플러그인 파일은 반드시 Hello 함수(Exported)가 있어야 합니다.
	symHello, err := plug.Lookup("Hello")
	if err != nil {
		log.Printf("[Error] 심볼 'Hello' 조회 실패 (%s): %v\n", pluginPath, err)
		return
	}

	// 심볼의 타입 단언: 함수 타입은 func(string) string으로 가정
	helloFunc, ok := symHello.(func(string) string)
	if !ok {
		log.Printf("[Error] 플러그인 (%s)의 'Hello' 심볼 타입이 예상과 다릅니다.\n", pluginPath)
		return
	}

	// 함수 호출: 예제 입력값 "Gopher" 전달
	result := helloFunc("Gopher")
	log.Printf("플러그인 (%s) 호출 결과: %s\n", pluginPath, result)
}

func main7() {
	fmt.Println("=== Multi Plugin Loading Demo ===")

	// 1. 플러그인 파일 목록 가져오기: plugins 폴더 내 모든 .so 파일
	pluginFiles, err := filepath.Glob("plugins/*.so")
	if err != nil {
		log.Fatalf("플러그인 파일 목록 검색 실패: %v\n", err)
	}
	if len(pluginFiles) == 0 {
		log.Fatalf("플러그인 파일이 존재하지 않습니다. 'plugins/*.so' 파일을 확인하세요.\n")
	}

	fmt.Printf("총 %d개의 플러그인 파일을 찾았습니다.\n", len(pluginFiles))

	// 2. 각 플러그인을 동시에 로드하기 위해 WaitGroup 사용
	var wg sync.WaitGroup
	startTime := time.Now()

	for _, pluginPath := range pluginFiles {
		wg.Add(1)
		// 각 플러그인 파일에 대해 고루틴을 시작합니다.
		go loadPluginAndCall(pluginPath, &wg)
	}

	// 모든 고루틴이 완료될 때까지 대기
	wg.Wait()
	duration := time.Since(startTime)
	fmt.Printf("모든 플러그인 로드 및 함수 호출 완료 (총 소요 시간: %v)\n", duration)

	fmt.Println("=== Multi Plugin Loading Demo 종료 ===")
}
