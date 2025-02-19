/*
이 예제 플러그인은 Go의 plugin 패키지를 활용한 가장 기본적인 플러그인 구현 방법을 보여줍니다.
주요 기능:
1. 단일 함수 "Hello"를 정의하여 외부에 노출합니다.
   - 이 함수는 문자열 인수를 받아, 인사 메시지를 출력합니다.
2. 플러그인으로 컴파일하기 위해, 패키지 이름은 반드시 main이어야 하며,
   - 플러그인 파일은 첫 글자가 대문자인 Exported 심볼을 제공해야 합니다.

빌드 방법:
- 이 파일을 플러그인으로 컴파일하려면 아래 명령어를 사용하세요.
  go build -buildmode=plugin -o simpleplugin.so 01_simple_plugin.go

사용 예:
- 메인 애플리케이션에서는 plugin.Open을 통해 simpleplugin.so를 로드하고,
  Lookup을 통해 "Hello" 심볼을 검색한 후, 동적으로 함수를 호출할 수 있습니다.
*/

package main

import "fmt"

// Hello 함수는 플러그인에서 외부에 공개(Export)된 함수입니다.
// 이 함수는 입력받은 이름을 사용하여 인사 메시지를 출력합니다.
// 플러그인 시스템에서 함수가 Export되기 위해서는 함수 이름의 첫 글자가 대문자여야 합니다.
func Hello(name string) {
	fmt.Printf("Hello, %s! This is a simple plugin speaking.\n", name)
}
