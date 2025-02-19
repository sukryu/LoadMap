/*
이 예제는 플러그인 핫 리로드(Hot Reload) 기법을 보여줍니다.
핫 리로드는 실행 중인 애플리케이션에서 플러그인 파일이 업데이트되었을 때,
변경된 플러그인을 동적으로 다시 로드하여 최신 기능을 적용하는 기법입니다.

주요 기능:
1. 플러그인 파일의 마지막 수정 시간을 주기적으로 확인합니다.
2. 파일 수정 시간이 변경되면, 플러그인을 재로드하여 최신 버전의 기능을 반영합니다.
3. 재로드한 플러그인에서 제공하는 함수를 동적으로 호출하여 결과를 출력합니다.

주의:
- 플러그인 파일은 미리 빌드되어 있어야 하며(예: go build -buildmode=plugin -o versionedplugin.so examples/versionedplugin.go),
  업데이트 시 기존 플러그인의 리소스 정리가 필요할 수 있습니다.
- 핫 리로드를 구현할 때, 동시 호출되는 플러그인 함수가 스레드 안전한지 확인해야 합니다.
*/

package main

import (
	"fmt"
	"log"
	"os"
	"plugin"
	"sync"
	"time"
)

// loadProcessFunction는 지정된 플러그인 파일에서 "Process" 심볼을 조회하여,
// string 인수를 받아 string을 반환하는 함수를 반환합니다.
func loadProcessFunction(pluginPath string) (func(string) string, error) {
	plug, err := plugin.Open(pluginPath)
	if err != nil {
		return nil, fmt.Errorf("플러그인 로드 실패 (%s): %w", pluginPath, err)
	}

	// "Process" 심볼을 조회합니다.
	symProcess, err := plug.Lookup("Process")
	if err != nil {
		return nil, fmt.Errorf("심볼 'Process' 조회 실패: %w", err)
	}

	// 심볼을 함수 타입으로 단언합니다.
	processFunc, ok := symProcess.(func(string) string)
	if !ok {
		return nil, fmt.Errorf("심볼 'Process'의 타입이 예상과 다릅니다")
	}
	return processFunc, nil
}

// watchPluginFile는 주어진 플러그인 파일의 마지막 수정 시간을 주기적으로 모니터링합니다.
// 수정 시간이 변경되면, reloadChan을 통해 true 신호를 보냅니다.
func watchPluginFile(pluginPath string, interval time.Duration, reloadChan chan<- bool, stopChan <-chan struct{}) {
	var lastModTime time.Time

	for {
		select {
		case <-stopChan:
			// 모니터링 종료 신호 수신 시 종료합니다.
			return
		default:
			// 파일의 상태를 확인합니다.
			info, err := os.Stat(pluginPath)
			if err != nil {
				log.Printf("플러그인 파일 상태 확인 실패: %v", err)
				time.Sleep(interval)
				continue
			}
			currentModTime := info.ModTime()
			// 만약 마지막 수정 시간과 다르면, 파일이 업데이트된 것으로 간주하고 reload 신호를 보냅니다.
			if currentModTime.After(lastModTime) {
				log.Printf("플러그인 파일 변경 감지: 이전 수정 시간=%v, 현재 수정 시간=%v", lastModTime, currentModTime)
				lastModTime = currentModTime
				reloadChan <- true
			}
			time.Sleep(interval)
		}
	}
}

func main6() {
	pluginPath := "versionedplugin.so" // 플러그인 파일 경로 (미리 빌드되어 있어야 함)
	reloadInterval := 5 * time.Second  // 플러그인 파일 변경 감시 간격

	// reloadChan: 파일 변경 시 재로드 신호를 전달하는 채널
	reloadChan := make(chan bool)
	// stopChan: 모니터링을 중지하기 위한 채널
	stopChan := make(chan struct{})

	// 초기 플러그인 로드
	processFunc, err := loadProcessFunction(pluginPath)
	if err != nil {
		log.Fatalf("초기 플러그인 로드 실패: %v", err)
	}
	log.Println("초기 플러그인 로드 성공!")

	// WaitGroup을 사용해 메인 루프의 동시성 제어 (예제에서는 간단히 데모를 위해 사용)
	var wg sync.WaitGroup
	wg.Add(1)

	// 플러그인 파일 변경 감시를 별도의 고루틴에서 시작합니다.
	go func() {
		defer wg.Done()
		watchPluginFile(pluginPath, reloadInterval, reloadChan, stopChan)
	}()

	// 메인 데모 루프: 일정 간격으로 플러그인 함수를 호출하며, 파일 변경 신호가 오면 플러그인을 재로드합니다.
	ticker := time.NewTicker(3 * time.Second)
	defer ticker.Stop()

	demoDuration := 30 * time.Second
	timeout := time.After(demoDuration)
	log.Printf("핫 리로드 데모 시작 (총 %v 동안 실행)", demoDuration)

	for {
		select {
		case <-ticker.C:
			// 플러그인 함수 호출
			input := "Hot Reload Test"
			result := processFunc(input)
			fmt.Printf("Process 함수 호출 결과: %s\n", result)
		case <-reloadChan:
			// 파일 변경 신호 수신: 플러그인을 재로드합니다.
			log.Println("플러그인 재로드 시도...")
			newProcessFunc, err := loadProcessFunction(pluginPath)
			if err != nil {
				log.Printf("플러그인 재로드 실패: %v", err)
			} else {
				processFunc = newProcessFunc
				log.Println("플러그인 재로드 성공!")
			}
		case <-timeout:
			// 데모 종료
			close(stopChan) // 변경 감시 고루틴 종료
			log.Println("핫 리로드 데모 종료")
			wg.Wait()
			return
		}
	}
}
