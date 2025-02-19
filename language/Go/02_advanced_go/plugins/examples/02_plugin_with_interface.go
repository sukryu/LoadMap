/*
이 예제는 Go 플러그인 시스템에서 인터페이스를 활용하는 방법을 보여줍니다.
주요 기능:
1. 플러그인 인터페이스(Plugin)를 정의하여, 메인 애플리케이션과 플러그인 간의 명확한 계약을 수립합니다.
2. MyPlugin 구조체를 통해 Plugin 인터페이스를 구현합니다.
3. 인터페이스를 만족하는 인스턴스를 외부에 Export하여, 메인 애플리케이션이 동적으로 플러그인을 로드하고 해당 기능을 호출할 수 있도록 합니다.

빌드 방법:
- 이 파일을 플러그인으로 컴파일하려면 다음 명령어를 사용하세요.
  go build -buildmode=plugin -o plugin_with_interface.so 02_plugin_with_interface.go

사용 예:
- 메인 애플리케이션에서는 plugin.Open을 통해 plugin_with_interface.so를 로드한 후,
  Lookup("PluginInstance")를 호출하여 Plugin 인터페이스를 구현한 인스턴스를 얻어 동적 호출할 수 있습니다.
*/

package main

import "fmt"

// Plugin 인터페이스는 플러그인이 구현해야 할 기능을 정의합니다.
// 여기서는 단순히 입력 문자열을 처리하여 결과 문자열을 반환하는 Process 메서드를 포함합니다.
type Plugin interface {
	Process(input string) string
}

// MyPlugin 구조체는 Plugin 인터페이스를 구현하는 구체적인 타입입니다.
type MyPlugin struct{}

// Process 메서드는 Plugin 인터페이스의 요구 사항을 충족하며,
// 입력받은 문자열에 대해 간단한 처리를 수행한 후 결과를 반환합니다.
func (mp MyPlugin) Process(input string) string {
	// 예시: 입력 문자열에 접두사를 붙여서 반환합니다.
	return fmt.Sprintf("MyPlugin processed: %s", input)
}

// PluginInstance 변수는 Plugin 인터페이스를 구현한 인스턴스를 Export합니다.
// 메인 애플리케이션은 이 변수를 Lookup하여 플러그인의 기능을 동적으로 사용할 수 있습니다.
var PluginInstance Plugin = MyPlugin{}
