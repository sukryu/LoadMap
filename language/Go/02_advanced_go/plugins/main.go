/*
이 예제는 Go의 plugin 패키지를 활용하여 동적 플러그인 로딩을 시연합니다.
주요 기능:
1. 플러그인 파일(.so 파일)을 동적으로 로드합니다.
   - plugin.Open 함수를 사용하여 지정된 플러그인 파일을 열고, *plugin.Plugin 객체를 반환받습니다.
2. 플러그인 내의 심볼(함수나 변수 등)을 조회합니다.
   - plugin.Lookup을 통해 공개(Exported) 심볼을 검색합니다.
3. 동적 함수 호출을 수행합니다.
   - 조회한 심볼을 실제 함수 타입으로 변환한 후, 인수를 전달하여 호출합니다.
4. 동적 로딩을 통해 런타임에 애플리케이션의 기능을 확장하는 방법을 학습합니다.

주의:
- 플러그인은 주로 Linux 환경에서 지원되며, Windows에서는 제한적으로 동작합니다.
- 플러그인 파일은 별도의 빌드 모드(예: go build -buildmode=plugin)를 사용하여 컴파일해야 합니다.
*/

package main

import (
	"fmt"
	"log"
	"plugin"
)

func main() {
	fmt.Println("=== Plugin Dynamic Loading Demo ===")

	// 1. 플러그인 파일 열기
	// "myplugin.so" 파일은 플러그인 예제 파일로, 먼저 해당 플러그인을 컴파일해야 합니다.
	// 컴파일 방법 예시: go build -buildmode=plugin -o myplugin.so examples/myplugin.go
	plug, err := plugin.Open("myplugin.so")
	if err != nil {
		log.Fatalf("플러그인 로드 실패: %v", err)
	}
	fmt.Println("플러그인 파일 로드 성공!")

	// 2. 플러그인에서 함수 심볼 조회
	// 플러그인 파일에서 공개된 함수는 첫 글자가 대문자여야 합니다.
	// 여기서는 "Hello"라는 함수 심볼을 찾습니다.
	symHello, err := plug.Lookup("Hello")
	if err != nil {
		log.Fatalf("심볼 'Hello' 조회 실패: %v", err)
	}
	fmt.Println("심볼 'Hello' 조회 성공!")

	// 3. 심볼 타입 단언 및 동적 함수 호출 준비
	// 조회된 심볼은 interface{} 타입이므로, 실제 함수 타입으로 단언해야 합니다.
	// 예제에서는 Hello 함수가 string 인수를 받아 인사 메시지를 출력하는 함수라고 가정합니다.
	helloFunc, ok := symHello.(func(string))
	if !ok {
		log.Fatalf("심볼 'Hello'의 타입이 예상과 다릅니다. 올바른 함수 타입으로 단언할 수 없습니다.")
	}

	// 4. 동적 함수 호출
	// helloFunc를 호출하여 플러그인에서 제공하는 기능을 실행합니다.
	fmt.Println("동적 함수 호출: Hello('Gopher')")
	helloFunc("Gopher")

	fmt.Println("=== Plugin Dynamic Loading Demo 종료 ===")
}
