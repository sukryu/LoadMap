# Plugins in Go: Dynamic Loading & Extensibility 🚀

이 디렉토리는 Go의 **플러그인 시스템**을 활용하여, 애플리케이션을 동적으로 확장하고 모듈화하는 방법을 다룹니다.  
Go의 `plugin` 패키지를 사용하면, 별도의 공유 라이브러리(.so 파일)로 컴파일된 모듈을 런타임에 로드하여 기능을 동적으로 추가할 수 있습니다.

---

## What You'll Learn 🎯

- **플러그인의 기본 개념**  
  - Go에서 플러그인이란 무엇인지, 언제 활용하는지 이해합니다.
- **플러그인 컴파일 및 로딩**  
  - 코드를 공유 라이브러리로 컴파일하는 방법과, `plugin.Open` 함수를 통해 런타임에 로드하는 방법을 학습합니다.
- **동적 함수 호출 및 인터페이스 활용**  
  - 플러그인에서 제공하는 함수와 변수를 동적으로 호출하는 패턴을 익힙니다.
- **실무 적용 사례 및 주의사항**  
  - 플러그인 사용 시 고려해야 할 성능, 보안, 코드 유지보수 측면의 Best Practice를 다룹니다.

---

## 디렉토리 구조 📁

```plaintext
02-advanced-go/
└── plugins/
    ├── main.go        # 플러그인 로더 및 데모 애플리케이션 예제
    ├── examples/      # 플러그인 컴파일 및 로드 예제 코드들
    └── README.md      # 이 문서
```

- **main.go**: 플러그인을 동적으로 로드하고, 해당 모듈의 함수를 호출하는 기본 예제 코드가 포함되어 있습니다.
- **examples/**: 다양한 플러그인 예제와, 플러그인 인터페이스 설계 및 확장 사례를 포함합니다.
  - 예를 들어, `01_simple_plugin.go`, `02_plugin_with_interface.go`, `03_plugin_dynamic_loading_and_versioning.go`, `04_plugin_concurrency_example.go`, `05_plugin_error_handling.go`, `06_plugin_hot_reload.go`, `07_multi_plugin_loading.go` 등의 예제가 포함될 수 있습니다.

---

## Getting Started 🚀

### 1. 플러그인 개발 환경 준비
- Go 최신 버전 설치: [Download Go](https://go.dev/dl/)
- 플러그인 컴파일은 Linux 환경에서 지원되며, 현재는 Windows에서는 제한적으로 동작합니다.

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/02-advanced-go/plugins
```

### 3. 플러그인 컴파일 및 실행 예제
- 먼저, 플러그인 예제 코드를 빌드하여 공유 라이브러리(.so 파일)로 컴파일합니다.
  ```bash
  go build -buildmode=plugin -o myplugin.so examples/myplugin.go
  ```
- 이후, main.go를 실행하여 플러그인을 로드하고 동적으로 함수를 호출합니다.
  ```bash
  go run main.go
  ```

---

## Example Code Snippet 📄

아래는 간단한 플러그인 예제입니다.

**플러그인 파일 (예: examples/myplugin.go):**
```go
package main

import "fmt"

// 플러그인에서 공개할 함수 (Exported function)
func Hello(name string) {
    fmt.Printf("Hello, %s! This is a plugin speaking.\n", name)
}
```

**플러그인 로더 (main.go):**
```go
package main

import (
    "fmt"
    "plugin"
)

func main() {
    // 플러그인 파일 열기
    plug, err := plugin.Open("myplugin.so")
    if err != nil {
        fmt.Println("Error loading plugin:", err)
        return
    }

    // 플러그인에서 "Hello" 함수 심볼 찾기
    helloSymbol, err := plug.Lookup("Hello")
    if err != nil {
        fmt.Println("Error looking up Hello:", err)
        return
    }

    // 함수 타입으로 변환 후 호출
    helloFunc, ok := helloSymbol.(func(string))
    if !ok {
        fmt.Println("Unexpected type from module symbol")
        return
    }
    helloFunc("Gopher")
}
```

이 예제는 플러그인 파일을 동적으로 로드한 후, `Hello` 함수를 찾아 호출하는 과정을 보여줍니다.

---

## Best Practices & Tips 💡

- **최소한으로 사용하기**:  
  - 플러그인은 동적 로딩을 가능하게 하지만, 잘못 사용할 경우 코드 복잡성 증가 및 디버깅 어려움이 발생할 수 있으므로 꼭 필요한 경우에만 사용하세요.

- **명확한 인터페이스 설계**:  
  - 플러그인과 메인 애플리케이션 간에 명확한 계약(인터페이스)을 정의하여, 버전 관리 및 코드 호환성을 유지하세요.

- **에러 처리 강화**:  
  - 플러그인 로딩 및 함수 호출 시 발생할 수 있는 오류를 꼼꼼하게 처리하여, 런타임 장애를 예방하세요.

- **보안 고려**:  
  - 외부 플러그인을 로드하는 경우, 신뢰할 수 있는 소스에서 제공된 플러그인만 사용하고, 코드 서명 등을 통해 무결성을 검증하세요.

- **성능 측면**:  
  - 플러그인 사용 시 초기 로딩 비용이 발생하므로, 캐싱이나 초기화 전략을 통해 성능 최적화를 고려하세요.

---

## Next Steps

- 동적 메서드 호출, 복잡한 인터페이스 확장, 플러그인 기반 모듈 시스템 구축 등 고급 사례를 추가 실습해 보세요.
- 실제 프로젝트에서 플러그인 패턴을 도입하여, 기능 확장 및 모듈화를 어떻게 효과적으로 구현할 수 있는지 연구해 보세요.

Happy Plugin Coding! 🚀