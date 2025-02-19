/*
이 예제는 동적 플러그인 로딩 및 버전 관리를 위한 기본적인 패턴을 보여줍니다.
주요 기능:
1. 플러그인 파일(.so 파일)을 런타임에 로드하고, 그 내부에 정의된 함수들을 조회합니다.
2. 플러그인에서 버전 정보를 제공하는 "Version" 함수와, 데이터를 처리하는 "Process" 함수를 Lookup합니다.
3. 런타임에 플러그인의 버전을 확인하고, 적절한 함수를 호출하여 데이터를 처리하는 방법을 시연합니다.

빌드 방법:
- 플러그인 예제 파일(예: examples/versionedplugin.go)을 플러그인 모드로 빌드합니다.
  예: go build -buildmode=plugin -o versionedplugin.so examples/versionedplugin.go

사용 예:
- 메인 애플리케이션에서는 plugin.Open을 통해 플러그인을 동적으로 로드한 후,
  Lookup을 통해 "Version" 및 "Process" 심볼을 조회하여 해당 기능을 호출할 수 있습니다.
*/

package main

import (
	"fmt"
	"log"
	"plugin"
)

// loadPlugin 동적 로딩과 버전 확인을 수행하는 함수입니다.
// pluginPath: 플러그인 파일의 경로를 입력받습니다.
// 반환값: 플러그인 버전 문자열, Process 함수를 (string 인수를 받아 string을 반환), 그리고 오류 정보.
func loadPlugin(pluginPath string) (string, func(string) string, error) {
	// 1. 플러그인 파일을 동적으로 로드합니다.
	plug, err := plugin.Open(pluginPath)
	if err != nil {
		return "", nil, fmt.Errorf("플러그인 로드 실패: %w", err)
	}

	// 2. 플러그인 내에서 버전 정보를 제공하는 "Version" 심볼을 조회합니다.
	//    이 함수는 인수가 없고, 플러그인의 버전을 나타내는 문자열을 반환한다고 가정합니다.
	vSym, err := plug.Lookup("Version")
	if err != nil {
		return "", nil, fmt.Errorf("Version 심볼 조회 실패: %w", err)
	}
	// 심볼을 실제 함수 타입으로 단언합니다.
	versionFunc, ok := vSym.(func() string)
	if !ok {
		return "", nil, fmt.Errorf("Version 심볼의 타입이 예상과 다릅니다")
	}
	// 플러그인 버전 정보를 가져옵니다.
	pluginVersion := versionFunc()

	// 3. 플러그인 내에서 데이터를 처리하는 "Process" 심볼을 조회합니다.
	//    이 함수는 string 인수를 받아 처리 후 결과 문자열을 반환한다고 가정합니다.
	pSym, err := plug.Lookup("Process")
	if err != nil {
		return "", nil, fmt.Errorf("Process 심볼 조회 실패: %w", err)
	}
	// 심볼을 실제 함수 타입으로 단언합니다.
	processFunc, ok := pSym.(func(string) string)
	if !ok {
		return "", nil, fmt.Errorf("Process 심볼의 타입이 예상과 다릅니다")
	}

	return pluginVersion, processFunc, nil
}

func main() {
	fmt.Println("=== Plugin Dynamic Loading and Versioning Demo ===")

	// 플러그인 파일 경로를 지정합니다.
	// 이 파일은 미리 빌드되어 있어야 하며, 예: versionedplugin.so
	pluginPath := "versionedplugin.so"

	// 동적으로 플러그인을 로드하고, 버전 정보와 Process 함수를 획득합니다.
	version, process, err := loadPlugin(pluginPath)
	if err != nil {
		log.Fatalf("플러그인 로드 오류: %v", err)
	}

	// 플러그인에서 제공하는 버전 정보를 출력합니다.
	fmt.Printf("로드된 플러그인 버전: %s\n", version)

	// 플러그인의 Process 함수를 사용하여 문자열 데이터를 처리합니다.
	input := "Dynamic Plugin Example"
	output := process(input)
	fmt.Printf("Process 함수 호출 결과: %s\n", output)

	fmt.Println("=== Plugin Dynamic Loading and Versioning Demo 종료 ===")
}
