/*
이 예제는 Go의 플러그인 시스템과 동시성(Concurrency)을 결합한 사용 사례를 보여줍니다.
주요 기능:
1. 플러그인 파일(.so 파일)을 동적으로 로드하여, 플러그인 내의 특정 함수("Process")를 획득합니다.
2. 하나의 플러그인 인스턴스를 여러 고루틴에서 동시에 호출하여, 동시 작업을 수행합니다.
3. 각 고루틴은 플러그인의 Process 함수를 호출하고, 결과를 출력합니다.
4. 동시 호출의 결과를 WaitGroup을 통해 기다리고, 전체 수행 시간을 측정합니다.

빌드 방법:
- 플러그인 파일(예: versionedplugin.so)은 미리 빌드되어 있어야 합니다.
  예: go build -buildmode=plugin -o versionedplugin.so examples/versionedplugin.go

주의:
- 플러그인 함수는 동시 호출에 안전해야 합니다.
- 플러그인 로딩은 한 번만 수행하고, 해당 인스턴스를 모든 고루틴에서 공유합니다.
*/

package main

import (
	"fmt"
	"log"
	"plugin"
	"sync"
	"time"
)

// loadPlugin는 지정한 플러그인 파일에서 "Process" 함수를 동적으로 로드합니다.
// 이 함수는 플러그인의 Process 함수를 반환하며, 오류 발생 시 이를 함께 반환합니다.
func loadPlugin1(pluginPath string) (func(string) string, error) {
	// 플러그인 파일을 동적으로 로드
	plug, err := plugin.Open(pluginPath)
	if err != nil {
		return nil, fmt.Errorf("플러그인 로드 실패: %w", err)
	}

	// 플러그인에서 "Process" 심볼 조회
	symProcess, err := plug.Lookup("Process")
	if err != nil {
		return nil, fmt.Errorf("심볼 'Process' 조회 실패: %w", err)
	}

	// 심볼을 실제 함수 타입으로 단언 (함수는 string 인수를 받아 string 반환)
	processFunc, ok := symProcess.(func(string) string)
	if !ok {
		return nil, fmt.Errorf("심볼 'Process'의 타입이 예상과 다릅니다")
	}

	return processFunc, nil
}

func main4() {
	fmt.Println("=== Plugin Concurrency Example Demo ===")

	// 플러그인 파일 경로 지정 (플러그인 파일은 미리 빌드되어 있어야 합니다)
	pluginPath := "versionedplugin.so"

	// 플러그인 로드: 한 번만 로드하여 모든 고루틴에서 공유합니다.
	processFunc, err := loadPlugin1(pluginPath)
	if err != nil {
		log.Fatalf("플러그인 로드 오류: %v", err)
	}
	fmt.Println("플러그인 로드 성공: Process 함수 획득")

	// 동시 호출을 위한 설정
	numWorkers := 5         // 동시에 실행할 고루틴 수
	numCallsPerWorker := 10 // 각 고루틴이 호출할 횟수

	// WaitGroup을 사용하여 모든 고루틴의 완료를 기다립니다.
	var wg sync.WaitGroup
	startTime := time.Now()

	// 각 고루틴에서 플러그인의 Process 함수를 동시 호출합니다.
	for i := 0; i < numWorkers; i++ {
		wg.Add(1)
		go func(workerID int) {
			defer wg.Done()
			for j := 0; j < numCallsPerWorker; j++ {
				// 입력 문자열 생성: 각 호출마다 고유한 값을 전달합니다.
				input := fmt.Sprintf("Worker %d - call %d", workerID, j)
				// 플러그인의 Process 함수를 호출하고, 결과를 받습니다.
				result := processFunc(input)
				// 결과 출력 (동시 호출 결과 확인)
				fmt.Printf("[Worker %d] Input: '%s' -> Result: '%s'\n", workerID, input, result)
			}
		}(i + 1)
	}

	// 모든 고루틴 완료 대기
	wg.Wait()
	duration := time.Since(startTime)
	fmt.Printf("총 실행 시간: %v (총 호출 횟수: %d)\n", duration, numWorkers*numCallsPerWorker)

	fmt.Println("=== Plugin Concurrency Example Demo 종료 ===")
}
