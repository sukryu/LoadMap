# Go 언어 개요 (Introduction)

1. 개요 및 역사
    - Go 언어는 2007년 Google에서 Robert Griesemer, Rob Pike, Ken Thompson이 설계를 시작하여 2009년에 공개된 프로그래밍 언어입니다. 개발 배경에는 다음과 같은 동기가 있었습니다:
        - 기존 언어들의 한계: C++의 복잡성, Java의 장황함, Python의 성능 등 기존 언어들의 제약사항 극복
        - 멀티코어 시대 대응: 동시성 프로그래밍의 필요성 증가
        - 빌드 시간 개선: 대규모 소프트웨어의 긴 컴파일 시간 문제 해결

2. 설계 철학
    - Go는 다음과 같은 핵심 철학을 바탕으로 설계되었습니다:
        1. 단순성 (Simplicity)
            - 최소한의 키워드(25개)
            - 명시적인 코드 작성 강조
            - "Less is more"접근 방식

        2. 실용성 (Practicality)
            - 빠른 컴파일 속도
            - 효율적인 가비지 컬렉션
            - 내장된 동시성 지원(goroutines, channels)

        3. 가독성 (Readability)
            - 코드 포맷팅 도구 (gofmt)기본 제공
            - 일관된 코딩 스타일 강제
            - 명확하고 간결한 문법

3. Go 언어의 주요 특징
    1. 정적 타입 시스템
        - 컴파일 시점 타입 검사
        - 타입 추론 지원
        - 제네릭 프로그래밍 지원(Go 1.18+)

    2. 동시성 프로그래밍
        - 고루틴(Goroutine): 경량 스레드
        - 채널(Channel): 통신을 통한 동기화
        - "Do not communicate by sharing memory; share memory by communicating" 철학

    3. 내장 도구
        - 테스트 프레임워크 내장
        - 문서화 도구(godoc)
        - 성능 프로파일링

4. 다른 언어와의 비교
    1. C/C++ 대비
        - 더 단순한 문법
        - 내장 가비지 컬렉션
        - 더 안전한 메모리 관리
        - 더 빠른 컴파일

    2. Python 대비
        - 더 나은 성능
        - 정적 타입 시스템
        - 컴파일 언어의 이점

    3. Java 대비
        - 더 가벼운 런타임
        - 더 간결한 문법
        - 더 효율적인 동시성 모델

5. 버전별 주요 변화
    * Go 1.18(2022)
        - 제네릭 프로그래밍 도입
        - Fuzzing 테스트 지원
        - Workspaces 기능 추가

    * Go 1.19(2022)
        - 메모리 모델 개선
        - 성능 향상
        - 타입 추론 개선

    * Go 1.20(2023)
        - 에러 처리 기능 개선
        - 슬라이스 to array 변환 개선
        - 프로파일링 도구 강화

6. Key Points
    - Go는 현대적이고 효율적인 시스템 프로그래밍 언어입니다.
    - 동시성과 단순성에 중점을 둔 설계가 특징입니다.
    - 빠른 컴파일, 쉬운 배포, 훌륭한 표준 라이브러리를 제공합니다.
    - 클라우드 네이티브 애플리케이션 개발에 특히 적합합니다.

## Go 개발 환경 설정 (Environment Setup)

1. Go 설치
    1. 공식 배포판 설치
        * Windows
            1. Go 다운로드 페이지에서 Windows MSI 인스톨러 다운로드
            2. 인스톨러 실행 및 기본 설정으로 설치
            3. 설치 확인:
                ```bash
                go version
                ```
        
        * macOS
            1. Homebrew를 통한 설치:
                ```bash
                brew install go
                ```

            2. 또는 공식 패키지 다운로드 후 설치
            3. 설치 확인:
                ```bash
                go version
                ```

        * Linux (Ubuntu/Debian)
            ```bash
            # apt를 통한 설치
            sudo apt update
            sudo apt install golang

            # 설치 확인
            go version
            ```

    2. 버전 관리 도구 설치 (선택사항)
        - goenv를 사용하여 여러 Go 버전을 관리할 수 있습니다:
            ```bash
            # macOS (Homebrew)
            brew install goenv

            # Linux
            git clone https://github.com/syndbg/goenv.git ~/.goenv
            ```

2. 환경 변수 설정
    1. 주요 환경 변수
        - GOROOT: Go 설치 위치
        - GOPATH: 작업 공간 위치
        - GOBIN: Go 바이너리 설치 위치

    2. 환경 변수 설정 방법
        * Windows
            1. 시스템 환경 변수에 추가
                ```
                GOPATH=%USERPROFILE%\go
                PATH=%PATH%;%GOROOT%\bin;%GOPATH%\bin
                ```

        * Linux/macOS (bash)
            ```bash
            # ~/.bashrc 또는 ~/.zshrc에 추가
            export GOPATH=$HOME/go
            export PATH=$PATH:$GOROOT/bin:$GOPATH/bin
            ```

    3. 환경 확인
        ```bash
        # 모든 Go 환경 변수 확인
        go env

        # 특정 변수 확인
        go env GOPATH
        ```

3. Go Modules 설정
    - Go 1.11부터 도입된 Go Modules는 의존성 관리를 위한 공식 방법입니다.

    1. 새 프로젝트 시작
        ```bash
        # 새 디렉토리 생성 및 이동
        mkdir myproject
        cd myproject

        # 모듈 초기화
        go mod init github.com/username/myproject

        # go.mod 파일이 생성됨
        ```

    2. 기존 프로젝트에 모듈 추가
        ```bash
        # 현재 디렉토리에서 모듈 초기화
        go mod init

        # 의존성 정리
        go mod tidy
        ```

4. IDE/에디터 설정
    1. VSC
        1. VSCode 설치
        2. Go 확장 설치:
            - VSCode 확장 마켓플레이스에서 "Go"검색
            - 또는 커맨드라인에서:
                ```bash
                code --install-extension golang.go
                ```

        3. 필요한 Go 도구 자동 설치:
            - `Ctrl + Shift + P`(또는 `Cmd + Shift + P`)
            - "Go: Install/Update Tools" 선택
            - 모든 도구 선택 후 설치

        * 주요 기능:
            - 자동 완성
            - 코드 네비게이션
            - 실시간 오류 검사
            - 자동 포맷팅(gofmt)
            - 디버깅 지원

    2. GoLand
        - JetBrains의 Go 전용 IDE:
            1. GoLand 다운로드
            2. 설치 및 실행
            3. 새 프로젝트 생성 시 Go Modules 사용 선택

        - 주요 기능:
            - 강력한 코드 완성
            - 리팩토링 도구
            - 통합 디버거
            - 데이터베이스 도구
            - 버전 관리 통합

    3. Vim/Neovim 설정
        - vim-go 플러그인 설치:
            ```vim
            " vim-plug 사용 시
            Plug 'fatih/vim-go'

            " 설치 후 실행
            :GoInstallBinaries
            ```

5. 기본 개발 도구
    1. 필수 Go 도구
        ```bash
        # 코드 포맷팅
        go fmt ./...

        # 코드 검사
        go vet ./...

        # 테스트 실행
        go test ./...

        # 의존성 관리
        go mod tidy
        ```
    

    2. 추가 개발 도구 설치
        ```bash
        # golangci-lint 설치
        go install github.com/golangci/golangci-lint/cmd/golangci-lint@latest

        # 문서화 도구
        go install golang.org/x/tools/cmd/godoc@latest

        # 의존성 그래프 시각화
        go install golang.org/x/tools/cmd/godepgraph@latest
        ```

6. 프로젝트 구조 예시
    - 기본적인 Go 프로젝트 구조

    ```
    myproject/
    ├── cmd/
    │   └── myapp/
    │       └── main.go
    ├── internal/
    │   └── pkg/
    ├── pkg/
    ├── go.mod
    ├── go.sum
    └── README.md
    ```

7. Key Points
    - Go 1.11 이상에서는 Go Modules를 사용하여 의존성 관리
    - GOPATH는 더 이상 필수가 아님(Go Modules 사용 시)
    - VSC 또는 GoLand가 가장 많이 사용되는 IDE
    - `go fmt`, `go vet`등의 도구를 적극 활용
    - 프로젝트는 모듈 기반으로 구성

8. 문제 해결
    1. 일반적인 문제
        1. GOPATH 관련 오류
            ```bash
            # GOPATH 확인
            go env GOPATH

            # 필요한 경우 설정
            export GOPATH=$HOME/go
            ```

        2. 모듈 관련 오류
            ```bash
            # 모듈 캐시 정리
            go clean -modcache

            # 의존성 다시 다운로드
            go mod download
            ```

    2. IDE 문제 해결
        1. VSC Go 확장 도구 재설치
        2. GOROOT, GOPATH 환경 변수 확인
        3. Go Modules 활성화 확인(`GO111MODULE` 환경변수)

## Go 기초 문법 (Basic Syntax)

1. 프로그램 구조

    1. 기본 구조
        - 모든 Go 프로그램은 다음과 같은 기본 구조를 가집니다.

        ```go
        // 패키지 선언
        package main

        // 필요한 패키지 import
        import (
            "fmt"
        )

        // main 함수 - 프로그램의 진입점
        func main() {
            fmt.Println("Hello, World!")
        }
        ```

    2. 패키지 선언
        - 모든 Go 파일은 패키지 선언으로 시작
        - 실행 가능한 프로그램은 반드시 `package main`으로 시작
        - 패키지명은 소문자로 작성

    3. Import 문
        - 여러 패키지를 import하는 방법:
            ```go
            // 방법 1: 괄호 사용 (권장)
            import (
                "fmt"
                "strings"
            )

            // 방법 2: 개별 import
            import "fmt"
            import "strings"
            ```

        - Import 별칭 사용:
            ```go
            import (
                "fmt"
                str "strings"  // strings 패키지를 str로 사용
                . "math"      // 패키지명 없이 직접 사용 (권장하지 않음)
                _ "database/sql"  // init() 함수만 실행
            )
            ```

2. 기본 출력과 주석
    1. 출력 함수
        - fmt 패키지의 주요 출력 함수들:
            ```go
            func main() {
                // 기본 출력 (줄바꿈 포함)
                fmt.Println("Hello, World!")

                // 형식화된 출력
                name := "Alice"
                age := 25
                fmt.Printf("Name: %s, Age: %d\n", name, age)

                // 문자열 반환 (출력하지 않음)
                s := fmt.Sprintf("Name: %s, Age: %d", name, age)
            }
            ```
        
        - 주요 형식 지정자:
            - %v: 기본 형식
            - %T: 타입
            - %d: 정수
            - %f: 실수
            - %s: 문자열
            - %t: 불리언
            - %p: 포인터

    2. 주석
        - Go는 두 가지 형태의 주석을 지원합니다.
            ```go
            // 한 줄 주석

            /*
            여러 줄 주석
            여러 줄에 걸쳐
            작성할 수 있습니다.
            */
            ```

3. 기본 입력
    1. 표준 입력 받기
        ```go
        func main() {
            var name string
            var age int

            // 기본 입력
            fmt.Print("Enter name: ")
            fmt.Scan(&name)

            // 형식화된 입력
            fmt.Print("Enter age: ")
            fmt.Scanf("%d", &age)

            // 한 줄 입력
            var line string
            fmt.Print("Enter a line: ")
            fmt.Scanln(&line)
        }
        ```
    
    2. 버퍼를 사용한 입력
        ```go
        import "bufio"
        import "os"

        func main() {
            scanner := bufio.NewScanner(os.Stdin)
                
            fmt.Print("Enter a line: ")
            if scanner.Scan() {
                line := scanner.Text()
                fmt.Println("You entered:", line)
            }

            if err := scanner.Err(); err != nil {
                fmt.Fprintln(os.Stderr, "reading standard input:", err)
            }
        }
        ```

4. 명명 규칙
    1. 식별자 규칙
        - 문자나 밑줄로 시작
        - 대소문자 구분
        - 키워드는 사용 불가
        - Unicode 문자 혀용

        ```go
        // 유효한 식별자
        name
        _name
        userName
        用户名  // Unicode 허용

        // 유효하지 않은 식별자
        1name     // 숫자로 시작
        user-name // 하이픈 사용 불가
        ```

    2. 가시성 규칙
        - 대문자로 시작: 외부 패키지에서 접근 가능(Exported)
        - 소문자로 시작: 패키지 내부에서만 접근 가능

        ```go
        // 외부에서 접근 가능
        func PrintMessage() {
            fmt.Println("This is exported")
        }

        // 패키지 내부에서만 접근 가능
        func printMessage() {
            fmt.Println("This is not exported")
        }
        ```

5. Go 프로그램 실행
    1. 직접 실행
        ```bash
        # 소스 파일 직접 실행
        go run main.go

        # 여러 파일 실행
        go run main.go utils.go
        ```

    2. 빌드 후 실행
        ```bash
        # 빌드
        go build main.go

        # 실행
        ./main  # Linux/macOS
        main.exe  # Windows
        ```

    3. 패키지 실행
        ```bash
        # 현재 디렉토리의 패키지 실행
        go run .

        # 특정 패키지 실행
        go run github.com/username/project
        ```

6. 코드 포맷팅
    1. gofmt 사용
        - Go는 공식 코드 포맷터를 제공합니다:
            ```bash
            # 파일 포맷팅
            gofmt -w file.go

            # 디렉토리 내 모든 파일 포맷팅
            gofmt -w .
            ```

    2. go fmt 사용
        ```bash
        # 현재 패키지의 모든 파일 포맷팅
        go fmt

        # 하위 패키지 포함 모든 패키지 포맷팅
        go fmt ./...
        ```

7. Key Points
    - Go 프로그램은 항상 `package main`으로 시작
    - 내장된 코드 포맷터(gofmt)로 일관된 스타일 유지
    - 대소문자로 가시성 제어(대문자 시작은 exported)
    - 불필요한 세미콜론 사용하지 않음
    - UTF-8 인코딩 사용

8. 기본 문법 관련 팁
    1. 사용하지 않는 import는 컴파일 에러를 발생시킴
    2. 선언된 변수를 사용하지 않으면 컴파일 에러 발생
    3. 패키지명은 소문자로 작성
    4. 공개 함수/변수는 문서화 주석 작성 권장

## Go 변수와 상수 (Variable and Constants)

1. 변수 (Variables)
    1. 변수 선언 방식
        1. var 키워드를 사용한 기본 선언:
            ```go
            var name string
            var age int
            var isActive bool
            ```

        2. 초기값과 함께 선언:
            ```go
            var name string = "Alice"
            var age int = 25
            var isActive bool = true
            ```

        3. 타입 생략(타입 추론):
            ```go
            var name = "Alice" // string으로 추론
            var age = 25 // int로 추론
            var pi = 3.14 // float64로 추론
            ```

        4. 짧은 선언 (:=):
            ```go
            name := "Alice" // var name string = "Alice"와 동일
            age := 25 // var age int = 25와 동일
            ```

        5. 여러 변수 동시 선언:
            ```go
            var x, y int
            var name, age = "Alice", 25
            x, y := 10, 20
            ```

    2. 기본 데이터 타입
        1. 숫자형:
            ```go
            // 정수형
            var i int         // 플랫폼에 따라 32비트 또는 64비트
            var i8 int8       // -128 ~ 127
            var i16 int16     // -32768 ~ 32767
            var i32 int32     // -2^31 ~ 2^31-1
            var i64 int64     // -2^63 ~ 2^63-1

            // 부호 없는 정수형
            var ui uint       // 플랫폼에 따라 32비트 또는 64비트
            var ui8 uint8     // 0 ~ 255
            var ui16 uint16   // 0 ~ 65535
            var ui32 uint32   // 0 ~ 2^32-1
            var ui64 uint64   // 0 ~ 2^64-1

            // 실수형
            var f32 float32   // IEEE-754 32비트 실수
            var f64 float64   // IEEE-754 64비트 실수

            // 복소수형
            var c64 complex64   // 실수부와 허수부가 float32
            var c128 complex128 // 실수부와 허수부가 float64

            // 기타
            var b byte   // uint8의 별칭
            var r rune   // int32의 별칭 (Unicode 코드 포인트)
            ```

        2. 문자열형:
            ```go
            var str string = "Hello, World"
            var multiLine = `This is a
            multi-line
            string`
            ```

        3. 불리언형:
            ```go
            var isTrue bool = true
            var isFalse bool = false
            ```

    3. 제로값 (Zero Values)
        - Go에서 변수를 선언하고 초기화하지 않으면 자동으로 제로값이 할당됩니다:
            ```go
            var i int     // 0
            var f float64 // 0.0
            var b bool    // false
            var s string  // ""
            var p *int    // nil
            ```

    4. 변수의 범위 (Scope)
        1. 지역 변수:
            ```go
            func main() {
                x := 10  // 지역 변수
                {
                    y := 20  // 블록 범위 변수
                    x = 15   // 외부 변수 접근 가능
                }
                // y는 여기서 접근 불가
            }
            ```

        2. 패키지 수준 변수:
            ```go
            package main

            var globalVar = "접근 가능"  // 패키지 내에서 접근 가능
            var GlobalVar = "외부 접근 가능"  // 다른 패키지에서도 접근 가능
            ```

2. 상수 (Constants)
    1. 상수 선언
        1. 기본 선언:
            ```go
            const pi = 3.14159
            const hello = "Hello, World"
            ```

        2. 여러 상수 동시 선언:
            ```go
            const (
                StatusOK = 200
                StatusNotFound = 404
                StatusServerError = 500
            )
            ```

        3. 타입이 있는 상수:
            ```go
            const timeout time.Duration = 30 * time.Second
            const pi float64 = 3.14159265359
        ```

    2. iota를 사용한 열거형 상수
        1. 기본 사용:
            ```go
            const (
                Sunday = iota    // 0
                Monday          // 1
                Tuesday         // 2
                Wednesday       // 3
                Thursday        // 4
                Friday         // 5
                Saturday        // 6
            )
            ```

        2. iota 조작:
            ```go
            const (
                _           = iota             // 0 무시
                KB = 1 << (10 * iota)         // 1 << 10 = 1024
                MB                            // 1 << 20
                GB                            // 1 << 30
                TB                            // 1 << 40
            )
            ```

        3. 복잡한 iota 패턴:
            ```go
            const (
                Write = 1 << iota  // 1
                Read              // 2
                Execute           // 4
            )

            const (
                FlagNone = 0
                FlagRead = 1 << iota  // 1
                FlagWrite            // 2
                FlagExecute         // 4
            )
            ```

    3. 타입 추론과 상수
        - 상수는 타입이 지정되지 않은 경우 문맥에 따라 필요한 타입으로 변환됩니다:
            ```go
            const x = 12345       // 타입 없는 상수
            var i int = x        // int로 사용
            var f float64 = x    // float64로 사용
            var b byte = x       // byte로 사용 (값이 범위 내인 경우)
            ```

    4. 상수 표현식
        - 상수는 컴파일 시점에 평가되는 표현식만 사용할 수 있습니다:
            ```go
            const (
                a = 1
                b = 2
                c = a + b        // 가능
                d = math.Sqrt(4) // 불가능 (런타임 함수)
            )
            ```

3. 타입 변환
    1. 명시적 타입 변환
        - Go는 암시적 타입 변환을 허용하지 않습니다:
            ```go
            var i int = 42
            var f float64 = float64(i)  // 명시적 변환 필요
            var u uint = uint(f)        // 명시적 변환 필요

            // 문자열 변환
            s1 := strconv.Itoa(i)      // int를 string으로
            s2 := strconv.FormatFloat(f, 'f', 2, 64)  // float64를 string으로

            // 문자열을 숫자로
            if num, err := strconv.Atoi("42"); err == nil {
                fmt.Printf("숫자: %d\n", num)
            }
            ```

    2. 타입 단언 (Type Assertion)
        - 인터페이스 타입에서 구체적인 타입으로 변환:
            ```go
            var i interface{} = "hello"

            s, ok := i.(string)
            if ok {
                fmt.Printf("문자열: %s\n", s)
            } else {
                fmt.Println("문자열이 아님")
            }
            ```

4. Key Points
    - Go는 정적 타입 언어이지만 타입 추론을 지원함
    - 변수는 선언과 동시에 초기화하지 않아도 됨 (제로값 할당)
    - 상수는 컴파일 타입에 평가되어야 함
    - iota를 사용하여 열거형 상수를 쉽게 정의할 수 있음
    - 암시적 타입 변환을 허용하지 않음
    - 선언된 변수는 반드시 사용해야 함

5. Best Practices
    1. 가능한 한 짧은 변수 선언(:=)사용
    2. 변수는 가능한 한 작은 범위에서 선언
    3. 상수는 대문자로 시작하는 것이 관례
    4. iota는 연관된 상수 그룹에 사용
    5. 불필요한 타입 지정 피하기(타입 추론 활용)

## Go 제어구조 (Control Flow)

1. 조건문 (if Statements)
    1. 기본 if문
        ```go
        if condition {
            // condition이 true일 때 실행
        }

        // 예시
        if x > 0 {
            fmt.Println("양수입니다")
        }
        ```

    2. 