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

    2. if-else 문
        ```go
        if condition {
            // condition이 true일 때 실행
        } else {
            // condition이 false일 때 실행
        }

        // 예시
        if age >= 18 {
            fmt.Println("성인입니다")
        } else {
            fmt.Println("미성년자입니다")
        }
        ```

    3. if-else if 문
        ```go
        if condition1 {
            // condition1이 true일 때 실행
        } else if condition2 {
            // condition2가 true일 때 실행
        } else {
            // 모든 조건이 false일 때 실행
        }

        // 예시
        if score >= 90 {
            grade = "A"
        } else if score >= 80 {
            grade = "B"
        } else if score >= 70 {
            grade = "C"
        } else {
            grade = "D"
        }
        ```

    4. 초기문이 있는 if(Go의 특별한 기능)
        ```go
        if initialization; condition {
            // condition이 true일 때 실행
        }

        // 예시
        if err := doSomething(); err != nil {
            fmt.Println("에러 발생:", err)
            return
        }

        // 파일 읽기 예시
        if file, err := os.Open("file.txt"); err == nil {
            defer file.Close()
            // 파일 처리
        } else {
            fmt.Println("파일을 열 수 없습니다:", err)
        }
        ```

2. switch 문
    1. 기본 switch 문
        ```go
        switch variable {
        case value1:
            // value1일 때 실행
        case value2:
            // value2일 때 실행
        default:
            // 어떤 case도 일치하지 않을 때 실행
        }

        // 예시
        switch day {
        case "monday":
            fmt.Println("월요일")
        case "tuesday":
            fmt.Println("화요일")
        default:
            fmt.Println("다른 요일")
        }
        ```

    2. 조건식이 있는 switch
        ```go
        switch {
        case condition1:
            // condition1이 true일 때 실행
        case condition2:
            // condition2가 true일 때 실행
        default:
            // 모든 조건이 false일 때 실행
        }

        // 예시
        switch {
        case score >= 90:
            grade = "A"
        case score >= 80:
            grade = "B"
        case score >= 70:
            grade = "C"
        default:
            grade = "D"
        }
        ```

    3. 초기문이 있는 switch
        ```go
        switch initialization; variable {
        case value1:
            // value1일 때 실행
        case value2:
            // value2일 때 실행
        }

        // 예시
        switch os := runtime.GOOS; os {
        case "darwin":
            fmt.Println("OS X")
        case "linux":
            fmt.Println("Linux")
        default:
            fmt.Printf("%s\n", os)
        }
        ```

    4. fallthrough
        ```go
        switch n := 3; n {
        case 1:
            fmt.Println("1 이하")
            fallthrough
        case 2:
            fmt.Println("2 이하")
            fallthrough
        case 3:
            fmt.Println("3 이하")
        }
        // 출력:
        // 3 이하
        ```

    5. 여러 값을 처리하는 case
        ```go
        switch char {
        case 'a', 'e', 'i', 'o', 'u':
            fmt.Println("모음")
        default:
            fmt.Println("자음")
        }
        ```

3. 반복문 (for 루프)
    1. 기본 for 루프
        ```go
        for initialization; condition; post {
            // 반복할 코드
        }

        // 예시
        for i := 0; i < 5; i++ {
            fmt.Println(i)
        }
        ```

    2. while 스타일의 for 루프
        ```go
        for condition {
            // 반복할 코드
        }

        // 예시
        count := 0
        for count < 5 {
            fmt.Println(count)
            count++
        }
        ```

    3. 무한 루프
        ```go
        for {
            // 무한히 반복할 코드
            if condition {
                break    // 조건을 만족하면 루프 탈출
            }
        }

        // 예시
        sum := 0
        for {
            sum++
            if sum > 100 {
                break
            }
        }
        ```

    4. range를 사용한 반복
        ```go
        // 슬라이스나 배열의 반복
        for index, value := range slice {
            // 인덱스와 값을 사용하는 코드
        }

        // 문자열의 반복 (룬 단위)
        for index, char := range str {
            // 인덱스와 문자를 사용하는 코드
        }

        // 맵의 반복
        for key, value := range map {
            // 키와 값을 사용하는 코드
        }

        // 채널의 반복
        for item := range channel {
            // 채널에서 받은 값을 사용하는 코드
        }

        // 예시
        numbers := []int{1, 2, 3, 4, 5}
        for i, num := range numbers {
            fmt.Printf("인덱스: %d, 값: %d\n", i, num)
        }
        ```

    5. 레이블과 break/continue
        ```go
        OuterLoop:
        for i := 0; i < 5; i++ {
            for j := 0; j < 5; j++ {
                if i*j > 10 {
                    break OuterLoop
                }
                fmt.Printf("i=%d, j=%d\n", i, j)
            }
        }
        ```

4. 제어문 활용 예시
    1. 에러 처리 패턴
        ```go
        if result, err := someFunction(); err != nil {
            // 에러 처리
            return err
        } else {
            // 결과 처리
            processResult(result)
        }
        ```

    2. 타입 스위치
        ```go
        switch v := interface{}.(type) {
        case int:
            fmt.Printf("정수: %d\n", v)
        case string:
            fmt.Printf("문자열: %s\n", v)
        case bool:
            fmt.Printf("불리언: %t\n", v)
        default:
            fmt.Printf("알 수 없는 타입: %T\n", v)
        }
        ```

    3. 중첩된 제어문
        ```go
        for i := 0; i < 5; i++ {
            if i%2 == 0 {
                switch i {
                case 0:
                    fmt.Println("시작")
                case 2:
                    continue
                case 4:
                    fmt.Println("끝")
                }
            }
        }
        ```

5. Key Points
    - Go는 while 키워드가 없음 (for로 대체)
    - switch문은 자동으로 break 됨 (fallthrough로 override 가능)
    - if와 switch문에서 초기화 구문 사용 가능
    - range로 컬렉션 순회 가능
    - 중첩 루프에서 레이블 사용 가능

6. Best Practices
    1. 가능한 한 제어문을 단순하게 유지
    2. 깊은 중첩은 피하고 필요시 함수로 분리
    3. early return 패턴 활용 (에러 처리 시)
    4. switch문 활용 (if-else 체인보다 가독성이 좋음)
    5. 무한 루프 사용 시 반드시 탈출 조건 확인

## Go의 함수 (Functions)

1. 함수 기본
    1. 함수 선언
        ```go
        func functionName(parameter1 type1, parameter2 type2) returnType {
            // 함수 본문
            return value
        }

        // 예시
        func add(x int, y int) int {
            return x + y
        }

        // 같은 타입의 매개변수는 타입을 한 번만 명시 가능
        func add(x, y int) int {
            return x + y
        }
        ```

    2. 다중 반환값
        ```go
        func divide(x, y float64) (float64, error) {
            if y == 0 {
                return 0, errors.New("0으로 나눌 수 없습니다")
            }
            return x / y, nil
        }

        // 사용 예
        result, err := divide(10, 2)
        if err != nil {
            fmt.Println("에러:", err)
            return
        }
        fmt.Println("결과:", result)
        ```

    3. 명명된 반환값
        ```go
        func split(sum int) (x, y int) {
            x = sum * 4 / 9
            y = sum - x
            return  // 'naked' return
        }

        // 아래와 동일
        func split(sum int) (int, int) {
            x := sum * 4 / 9
            y := sum - x
            return x, y
        }
        ```

2. 매개변수
    1. 가변 인자 함수
        ```go
        func sum(nums ...int) int {
            total := 0
            for _, num := range nums {
                total += num
            }
            return total
        }

        // 사용 예
        fmt.Println(sum(1, 2))          // 3
        fmt.Println(sum(1, 2, 3, 4))    // 10

        // 슬라이스 전달
        numbers := []int{1, 2, 3, 4}
        fmt.Println(sum(numbers...))    // 10
        ```

    2. 함수 값 전달 vs 참조 전달
        ```go
        // 값 전달
        func modifyValue(x int) {
            x = 42  // 원본 값에 영향 없음
        }

        // 포인터를 통한 참조 전달
        func modifyPointer(x *int) {
            *x = 42  // 원본 값이 변경됨
        }

        func main() {
            a := 10
            modifyValue(a)
            fmt.Println(a)  // 출력: 10

            modifyPointer(&a)
            fmt.Println(a)  // 출력: 42
        }
        ```

3. 특별한 함수 유형
    1. 익명 함수와 클로저
        ```go
        // 익명 함수
        func() {
            fmt.Println("Hello from anonymous function")
        }()

        // 클로저
        func adder() func(int) int {
            sum := 0
            return func(x int) int {
                sum += x
                return sum
            }
        }

        func main() {
            pos := adder()
            fmt.Println(pos(1))  // 1
            fmt.Println(pos(2))  // 3
            fmt.Println(pos(3))  // 6
        }
        ```

    2. 메서드 (Methods)
        ```go
        type Rectangle struct {
            width, height float64
        }

        // 값 리시버
        func (r Rectangle) Area() float64 {
            return r.width * r.height
        }

        // 포인터 리시버
        func (r *Rectangle) Scale(factor float64) {
            r.width *= factor
            r.height *= factor
        }
        ```

    3. 함수 타입
        ```go
        type Operation func(x, y int) int

        func calculate(op Operation, a, b int) int {
            return op(a, b)
        }

        func main() {
            add := func(x, y int) int { return x + y }
            multiply := func(x, y int) int { return x * y }

            fmt.Println(calculate(add, 5, 3))      // 8
            fmt.Println(calculate(multiply, 5, 3))  // 15
        }
        ```

4. defer 문
    1. 기본 사용법
        ```go
        func readFile(filename string) error {
            f, err := os.Open(filename)
            if err != nil {
                return err
            }
            defer f.Close()  // 함수 종료 시 실행

            // 파일 처리 로직
            return nil
        }
        ```

    2. defer 스택
        ```go
        func deferOrder() {
            fmt.Println("시작")
            defer fmt.Println("1")
            defer fmt.Println("2")
            defer fmt.Println("3")
            fmt.Println("끝")
        }
        // 출력:
        // 시작
        // 끝
        // 3
        // 2
        // 1
        ```

    3. defer와 인자 평가
        ```go
        func deferArgEval() {
            i := 0
            defer fmt.Println(i)  // 0 출력
            i++
        }
        ```

5. 패닉과 복구
    1. panic
        ```go
        func divide(x, y int) int {
            if y == 0 {
                panic("0으로 나눌 수 없습니다")
            }
            return x / y
        }
        ```

    2. recover
        ```go
        func safeOperation() (err error) {
            defer func() {
                if r := recover(); r != nil {
                    err = fmt.Errorf("panic 발생: %v", r)
                }
            }()

            // 위험한 연산 수행
            panic("something went wrong")
        }
        ```

6. 함수형 프로그래밍 패턴
    1. Map 함수 구현
        ```go
        func Map(vs []int, f func(int) int) []int {
            vsm := make([]int, len(vs))
            for i, v := range vs {
                vsm[i] = f(v)
            }
            return vsm
        }

        // 사용 예
        nums := []int{1, 2, 3, 4}
        doubled := Map(nums, func(x int) int {
            return x * 2
        })
        ```

    2. Filter 함수 구현
        ```go
        func Filter(vs []int, f func(int) bool) []int {
            filtered := make([]int, 0)
            for _, v := range vs {
                if f(v) {
                    filtered = append(filtered, v)
                }
            }
            return filtered
        }

        // 사용 예
        nums := []int{1, 2, 3, 4, 5, 6}
        evens := Filter(nums, func(x int) bool {
            return x%2 == 0
        })
        ```

7. 함수 설계 원칙
    1. 에러 처리
        ```go
        // 좋은 예시
        func readConfig(path string) (*Config, error) {
            file, err := os.Open(path)
            if err != nil {
                return nil, fmt.Errorf("설정 파일 열기 실패: %w", err)
            }
            defer file.Close()

            // 설정 파일 처리
            return config, nil
        }
        ```

    2. 인터페이스 설계
        ```go
        type Reader interface {
            Read(p []byte) (n int, err error)
        }

        func processReader(r Reader) error {
            buf := make([]byte, 1024)
            n, err := r.Read(buf)
            if err != nil {
                return err
            }
            // 데이터 처리
            return nil
        }
        ```

8. Key Points
    1. 함수는 여러 값을 반환할 수 있음
    2. defer를 사용하여 리소스 정리
    3. 패닉은 예외적인 상황에서만 사용
    4. 클로저를 통한 상태 캡처 가능
    5. 에러는 명시적으로 처리

9. Best Practices
    1. 함수는 한 가지 일만 수행하도록 설계
    2. 에러는 항상 검사하고 처리
    3. defer를 사용하여 리소스 관리
    4. 가능한 작은 함수로 분리
    5. 명확한 네이밍 사용 

## Go 동시성 프로그래밍 (Goroutines and Channels)

1. 고루틴 (Goroutines)
    1. 고루틴 기본
        - 고루틴은 Go의 경량 실행 스레드입니다.

        ```go
        // 기본 고루틴 생성
        go func() {
            // 동시에 실행될 코드
        }()

        // 기존 함수를 고루틴으로 실행
        func printNumbers() {
            for i := 0; i < 5; i++ {
                fmt.Printf("%d ", i)
                time.Sleep(100 * time.Millisecond)
            }
        }

        func main() {
            go printNumbers()
            time.Sleep(1 * time.Second) // 메인 함수가 너무 일찍 종료되는 것을 방지
        }
        ```

    2. 다중 고루틴
        ```go
        func main() {
            for i := 0; i < 3; i++ {
                go func(id int) {
                    fmt.Printf("Goroutine %d\n", id)
                }(i)
            }
            time.Sleep(1 * time.Second)
        }
        ```

2. 채널 (Channels)
    1. 채널 기본
        ```go
        // 채널 생성
        ch := make(chan int)    // 무버퍼 채널
        ch := make(chan int, 3) // 버퍼 크기가 3인 채널

        // 채널로 데이터 보내기
        ch <- 42

        // 채널에서 데이터 받기
        value := <-ch

        // 채널 닫기
        close(ch)
        ```

    2. 버퍼 vs 무버퍼 채널
        ```go
        // 무버퍼 채널 (동기)
        func unbufferedChannel() {
            ch := make(chan int)
            go func() {
                ch <- 1 // 수신자가 준비될 때까지 블록
            }()
            fmt.Println(<-ch)
        }

        // 버퍼 채널 (비동기)
        func bufferedChannel() {
            ch := make(chan int, 2)
            ch <- 1 // 버퍼가 가득 차지 않았으므로 블록되지 않음
            ch <- 2
            fmt.Println(<-ch, <-ch)
        }
        ```

    3. 채널 방향
        ```go
        // 송신 전용 채널
        func send(ch chan<- int) {
            ch <- 42
        }

        // 수신 전용 채널
        func receive(ch <-chan int) {
            val := <-ch
            fmt.Println(val)
        }

        func main() {
            ch := make(chan int)
            go send(ch)
            receive(ch)
        }
        ```

3. Select 문
    1. 기본 select
        ```go
        func main() {
            ch1 := make(chan string)
            ch2 := make(chan string)

            go func() { ch1 <- "from channel 1" }()
            go func() { ch2 <- "from channel 2" }()

            select {
            case msg1 := <-ch1:
                fmt.Println(msg1)
            case msg2 := <-ch2:
                fmt.Println(msg2)
            }
        }
        ```

    2. 타임아웃 처리
        ```go
        select {
        case msg := <-ch:
            fmt.Println("받은 메시지:", msg)
        case <-time.After(1 * time.Second):
            fmt.Println("타임아웃")
        }
        ```

    3. 기본 케이스
        ```go
        select {
        case msg := <-ch:
            fmt.Println("메시지 수신:", msg)
        case <-time.After(1 * time.Second):
            fmt.Println("타임아웃")
        default:
            fmt.Println("수신된 메시지 없음")
        }
        ```

4. 동시성 패턴
    1. 워커 풀 패턴
        ```go
        func worker(id int, jobs <-chan int, results chan<- int) {
            for job := range jobs {
                fmt.Printf("worker %d started job %d\n", id, job)
                time.Sleep(time.Second) // 작업 시뮬레이션
                fmt.Printf("worker %d finished job %d\n", id, job)
                results <- job * 2
            }
        }

        func main() {
            jobs := make(chan int, 100)
            results := make(chan int, 100)

            // 워커 시작
            for w := 1; w <= 3; w++ {
                go worker(w, jobs, results)
            }

            // 작업 전송
            for j := 1; j <= 5; j++ {
                jobs <- j
            }
            close(jobs)

            // 결과 수집
            for a := 1; a <= 5; a++ {
                <-results
            }
        }
        ```

    2. 파이프라인 패턴
        ```go
        func gen(nums ...int) <-chan int {
            out := make(chan int)
            go func() {
                for _, n := range nums {
                    out <- n
                }
                close(out)
            }()
            return out
        }

        func sq(in <-chan int) <-chan int {
            out := make(chan int)
            go func() {
                for n := range in {
                    out <- n * n
                }
                close(out)
            }()
            return out
        }

        func main() {
            // 파이프라인 생성 및 실행
            c := gen(2, 3)
            out := sq(c)

            // 결과 출력
            fmt.Println(<-out) // 4
            fmt.Println(<-out) // 9
        }
        ```

    3. Fan-out, Fan-in 패턴
        ```go
        func fanOut(in <-chan int, n int) []<-chan int {
            chs := make([]<-chan int, n)
            for i := 0; i < n; i++ {
                chs[i] = sq(in)
            }
            return chs
        }

        func fanIn(chs ...<-chan int) <-chan int {
            out := make(chan int)
            var wg sync.WaitGroup

            wg.Add(len(chs))
            for _, ch := range chs {
                go func(c <-chan int) {
                    for n := range c {
                        out <- n
                    }
                    wg.Done()
                }(ch)
            }

            go func() {
                wg.Wait()
                close(out)
            }()

            return out
        }
        ```

5. 동기화 프리미티브
    1. WaitGroup
        ```go
        func main() {
            var wg sync.WaitGroup

            for i := 0; i < 5; i++ {
                wg.Add(1)
                go func(id int) {
                    defer wg.Done()
                    fmt.Printf("Worker %d doing work\n", id)
                    time.Sleep(time.Second)
                }(i)
            }

            wg.Wait()
            fmt.Println("All workers done")
        }
        ```

    2. Mutex
        ```go
        type Counter struct {
            mu    sync.Mutex
            value int
        }

        func (c *Counter) Increment() {
            c.mu.Lock()
            defer c.mu.Unlock()
            c.value++
        }

        func (c *Counter) Value() int {
            c.mu.Lock()
            defer c.mu.Unlock()
            return c.value
        }
        ```

6. Context 패키지
    1. 기본 사용
        ```go
        func worker(ctx context.Context) {
            for {
                select {
                case <-ctx.Done():
                    fmt.Println("작업 중단")
                    return
                default:
                    fmt.Println("작업 수행 중...")
                    time.Sleep(time.Second)
                }
            }
        }

        func main() {
            ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
            defer cancel()

            go worker(ctx)
            time.Sleep(3 * time.Second)
            cancel()
            time.Sleep(1 * time.Second)
        }
        ```

    2. 값 전달
        ```go
        type key string

        func worker(ctx context.Context) {
            if value, ok := ctx.Value(key("user")).(string); ok {
                fmt.Printf("User: %s\n", value)
            }
        }

        func main() {
            ctx := context.WithValue(context.Background(), key("user"), "alice")
            go worker(ctx)
            time.Sleep(time.Second)
        }
        ```

7. Best Practices
    1. 고루틴 누수 방지
        ```go
        // 잘못된 예
        go func() {
            // 종료 조건 없음
            for {
                process()
            }
        }()

        // 좋은 예
        go func() {
            for {
                select {
                case <-ctx.Done():
                    return
                default:
                    process()
                }
            }
        }()
        ```

    2. 채널 크기 설계
        ```go
        // 일반적으로 무버퍼 채널 사용
        ch := make(chan int)

        // 성능이 중요한 경우에만 버퍼 채널 사용
        ch := make(chan int, numberOfWorkers)
        ```

    3. 에러 처리
        ```go
        type Result struct {
            Value int
            Err   error
        }

        ch := make(chan Result)
        go func() {
            value, err := doWork()
            ch <- Result{Value: value, Err: err}
        }()
        ```

8. Key Points
    1. 고루틴은 경량 스레드이며, 시스템 스레드와 다름
    2. 채널을 통한 통신으로 동시성 제어
    3. select를 사용하여 다중 채널 관리
    4. context로 고루틴 수명 관리
    5. 공유 메모리 대신 채널 통신 선호

## Go 구조체와 메서드 (Structs and Methods)

1. 구조체 기본 (Structs)
    1. 구조체 정의
        ```go
        // 기본 구조체 정의
        type Person struct {
            Name string
            Age  int
        }

        // 중첩 구조체
        type Address struct {
            Street  string
            City    string
            Country string
        }

        type Employee struct {
            Person    // 임베디드 필드
            Address   // 임베디드 필드
            Company string
            Salary  float64
        }
        ```

    2. 구조체 초기화
        ```go
        // 방법 1: 필드 순서대로 초기화
        p1 := Person{"Bob", 25}

        // 방법 2: 필드 이름 지정 초기화 (권장)
        p2 := Person{
            Name: "Alice",
            Age:  30,
        }

        // 방법 3: new 키워드 사용
        p3 := new(Person)  // &Person{} 와 동일
        p3.Name = "Charlie"
        p3.Age = 35

        // 중첩 구조체 초기화
        emp := Employee{
            Person: Person{
                Name: "Bob",
                Age:  25,
            },
            Address: Address{
                Street:  "123 Main St",
                City:    "Seoul",
                Country: "Korea",
            },
            Company: "TechCorp",
            Salary:  50000,
        }
        ```

    3. 구조체 필드 접근
        ```go
        // 직접 접근
        fmt.Println(emp.Name)        // 임베디드 필드 직접 접근
        fmt.Println(emp.Person.Name) // 명시적 접근도 가능
        fmt.Println(emp.Street)      // 임베디드 필드 직접 접근
        fmt.Println(emp.Company)     // 일반 필드 접근

        // 포인터를 통한 접근
        empPtr := &emp
        fmt.Println(empPtr.Name)     // (*empPtr).Name과 동일
        ```

2. 메서드 (Methods)
    1. 메서드 정의
        ```go
        // 값 리시버
        func (p Person) GetName() string {
            return p.Name
        }

        // 포인터 리시버
        func (p *Person) SetName(name string) {
            p.Name = name
        }
        ```

    2. 값 리시버 vs 포인터 리시버
        ```go
        type Rectangle struct {
            width, height float64
        }

        // 값 리시버 (원본 변경 안됨)
        func (r Rectangle) Area() float64 {
            return r.width * r.height
        }

        // 포인터 리시버 (원본 변경됨)
        func (r *Rectangle) Scale(factor float64) {
            r.width *= factor
            r.height *= factor
        }

        func main() {
            r := Rectangle{width: 10, height: 5}
            fmt.Println(r.Area())  // 50
            
            r.Scale(2)
            fmt.Println(r.Area())  // 200
        }
        ```

    3. 함수형 필드
        ```go
        type Calculator struct {
            Operation func(int, int) int
        }

        func main() {
            calc := Calculator{
                Operation: func(a, b int) int {
                    return a + b
                },
            }
            
            result := calc.Operation(5, 3)
            fmt.Println(result)  // 8
        }
        ```

3. 구조체 컴포지션
    1. 기본 컴포지션
        ```go
        type Animal struct {
            Name string
        }

        func (a Animal) Speak() string {
            return fmt.Sprintf("My name is %s", a.Name)
        }

        type Dog struct {
            Animal  // 임베디드 구조체
            Breed string
        }

        func main() {
            d := Dog{
                Animal: Animal{Name: "Rover"},
                Breed:  "Corgi",
            }
            
            fmt.Println(d.Speak())  // "My name is Rover"
            fmt.Println(d.Name)     // "Rover"
        }
        ```

    2. 메서드 오버라이딩
        ```go
        func (d Dog) Speak() string {
            return fmt.Sprintf("%s and I am a %s", d.Animal.Speak(), d.Breed)
        }

        func main() {
            d := Dog{
                Animal: Animal{Name: "Rover"},
                Breed:  "Corgi",
            }
            
            fmt.Println(d.Speak())  // "My name is Rover and I am a Corgi"
        }
        ```

4. 구조체 태그
    1. 기본 태그 사용
        ```go
        type User struct {
            Name     string `json:"name"`
            Age      int    `json:"age"`
            Email    string `json:"email,omitempty"`
            Password string `json:"-"`  // JSON 직렬화에서 제외
        }

        func main() {
            user := User{
                Name:     "Alice",
                Age:      30,
                Email:    "alice@example.com",
                Password: "secret",
            }
            
            jsonData, _ := json.Marshal(user)
            fmt.Println(string(jsonData))
        }
        ```

    2. 커스텀 태그 사용
        ```go
        type Field struct {
            Name  string `validate:"required"`
            Value string `validate:"email"`
        }

        func validateField(f Field) error {
            t := reflect.TypeOf(f)
            v := reflect.ValueOf(f)
            
            for i := 0; i < t.NumField(); i++ {
                field := t.Field(i)
                value := v.Field(i).String()
                
                if tag := field.Tag.Get("validate"); tag == "required" && value == "" {
                    return fmt.Errorf("%s is required", field.Name)
                }
            }
            return nil
        }
        ```

5. 메서드 집합
    1. 인터페이스 구현
        ```go
        type Stringer interface {
            String() string
        }

        func (p Person) String() string {
            return fmt.Sprintf("%s (%d years old)", p.Name, p.Age)
        }

        func main() {
            var s Stringer = Person{"Alice", 30}
            fmt.Println(s.String())  // "Alice (30 years old)"
        }
        ```

    2. 메서드 표현식
        ```go
        type Person struct {
            Name string
            Age  int
        }

        func (p Person) Greet() {
            fmt.Printf("Hello, I'm %s\n", p.Name)
        }

        func main() {
            p := Person{"Alice", 30}
            greet := Person.Greet
            greet(p)  // "Hello, I'm Alice"
        }
        ```

6. 고급 패턴
    1. 옵션 패턴
        ```go
        type Server struct {
            host    string
            port    int
            timeout time.Duration
        }

        type Option func(*Server)

        func WithPort(port int) Option {
            return func(s *Server) {
                s.port = port
            }
        }

        func WithTimeout(timeout time.Duration) Option {
            return func(s *Server) {
                s.timeout = timeout
            }
        }

        func NewServer(host string, options ...Option) *Server {
            server := &Server{
                host: host,
                port: 8080,  // 기본값
                timeout: time.Second * 30,  // 기본값
            }
            
            for _, option := range options {
                option(server)
            }
            
            return server
        }

        func main() {
            server := NewServer("localhost",
                WithPort(9000),
                WithTimeout(time.Minute),
            )
        }
        ```

    2. 빌더 패턴
        ```go
        type PersonBuilder struct {
            person Person
        }

        func NewPersonBuilder() *PersonBuilder {
            return &PersonBuilder{person: Person{}}
        }

        func (b *PersonBuilder) Name(name string) *PersonBuilder {
            b.person.Name = name
            return b
        }

        func (b *PersonBuilder) Age(age int) *PersonBuilder {
            b.person.Age = age
            return b
        }

        func (b *PersonBuilder) Build() Person {
            return b.person
        }

        func main() {
            person := NewPersonBuilder().
                Name("Alice").
                Age(30).
                Build()
        }
        ```

7. Best Practices
    1. 구조체 필드 순서 최적화
        ```go
        // 잘못된 예 (패딩으로 인한 메모리 낭비)
        type BadStruct struct {
            a byte
            b int64
            c byte
        }

        // 좋은 예 (메모리 효율적)
        type GoodStruct struct {
            b int64
            a byte
            c byte
        }
        ```

    2. 메서드 리시버 선택
        ```go
        // 값이 큰 구조체는 포인터 리시버 사용
        type BigStruct struct {
            Data [1024]byte
        }

        func (b *BigStruct) Process() { // 포인터 리시버
            // ...
        }

        // 작은 구조체는 값 리시버 가능
        type Point struct {
            X, Y float64
        }

        func (p Point) Distance() float64 { // 값 리시버
            return math.Sqrt(p.X*p.X + p.Y*p.Y)
        }
        ```

8. Key Points
    1. 구조체는 Go의 타입 시스템의 기본 구성 요소
    2. 메서드를 통해 구조체에 행위 추가 가능
    3. 컴포지션을 통한 코드 재사용
    4. 태그를 통한 메타데이터 추가
    5. 값 리시버와 포인터 리시버의 적절한 선택 중요

## Go 인터페이스 (Interfaces)

1. 인터페이스 기본
    1. 인터페이스 정의
        ```go
        // 기본 인터페이스 정의
        type Reader interface {
            Read(p []byte) (n int, err error)
        }

        type Writer interface {
            Write(p []byte) (n int, err error)
        }

        // 인터페이스 조합
        type ReadWriter interface {
            Reader
            Writer
        }
        ```

    2. 인터페이스 구현
        ```go
        // File 타입이 Reader와 Writer 인터페이스 구현
        type File struct {
            // ...
        }

        func (f *File) Read(p []byte) (n int, err error) {
            // 구현...
            return len(p), nil
        }

        func (f *File) Write(p []byte) (n int, err error) {
            // 구현...
            return len(p), nil
        }
        ```

    3. 암시적 인터페이스 구현
        ```go
        // Stringer 인터페이스
        type Stringer interface {
            String() string
        }

        // Person 타입이 Stringer 인터페이스 암시적 구현
        type Person struct {
            Name string
            Age  int
        }

        func (p Person) String() string {
            return fmt.Sprintf("%s (%d years old)", p.Name, p.Age)
        }
        ```

2. 인터페이스 활용
    1. 빈 인터페이스
        ```go
        // 모든 타입을 받을 수 있는 빈 인터페이스
        func PrintAnything(v interface{}) {
            fmt.Printf("타입: %T, 값: %v\n", v, v)
        }

        // 사용 예
        PrintAnything(42)          // 타입: int, 값: 42
        PrintAnything("Hello")     // 타입: string, 값: Hello
        PrintAnything(Person{...}) // 타입: Person, 값: Person{...}
        ```

    2. 타입 단언
        ```go
        func process(i interface{}) {
            // 타입 단언 기본
            str, ok := i.(string)
            if ok {
                fmt.Printf("문자열: %s\n", str)
            }

            // switch를 사용한 타입 단언
            switch v := i.(type) {
            case string:
                fmt.Printf("문자열: %s\n", v)
            case int:
                fmt.Printf("정수: %d\n", v)
            case Person:
                fmt.Printf("사람: %s\n", v.Name)
            default:
                fmt.Printf("알 수 없는 타입: %T\n", v)
            }
        }
        ```

    3. 인터페이스 값
        ```go
        type MyInterface interface {
            Method()
        }

        type MyType struct{}

        func (t *MyType) Method() {
            fmt.Println("MyType's method")
        }

        func main() {
            var i MyInterface     // 인터페이스 제로값: (nil, nil)
            var t *MyType = nil  // 타입은 있지만 값이 nil
            i = t               // 인터페이스는 nil이 아님! (타입이 있음)
            
            if i == nil {
                fmt.Println("is nil") // 실행되지 않음
            } else {
                fmt.Println("not nil") // 이것이 실행됨
            }
        }
        ```

3. 인터페이스 패턴
    1. io.Reader와 io.Writer 활용
        ```go
        func CopyData(r io.Reader, w io.Writer) error {
            // 버퍼 생성
            buf := make([]byte, 1024)
            
            for {
                // Reader에서 읽기
                n, err := r.Read(buf)
                if err != nil && err != io.EOF {
                    return err
                }
                if n == 0 {
                    break
                }
                
                // Writer에 쓰기
                if _, err := w.Write(buf[:n]); err != nil {
                    return err
                }
            }
            return nil
        }
        ```

    2. 인터페이스 분리 원칙
        ```go
        // 큰 인터페이스 대신 작은 인터페이스들로 분리
        type Reader interface {
            Read(p []byte) (n int, err error)
        }

        type Writer interface {
            Write(p []byte) (n int, err error)
        }

        type Closer interface {
            Close() error
        }

        // 필요에 따라 조합
        type ReadWriter interface {
            Reader
            Writer
        }

        type ReadWriteCloser interface {
            Reader
            Writer
            Closer
        }
        ```

    3. 어댑터 패턴
        ```go
        // 기존 타입
        type LegacyWriter struct{}

        func (w *LegacyWriter) WriteString(s string) error {
            // 구현...
            return nil
        }

        // 어댑터
        type WriterAdapter struct {
            legacy *LegacyWriter
        }

        func (wa *WriterAdapter) Write(p []byte) (n int, err error) {
            err = wa.legacy.WriteString(string(p))
            if err != nil {
                return 0, err
            }
            return len(p), nil
        }
        ```

4. 고급 인터페이스 패턴
    1. 인터페이스를 이용한 데코레이터 패턴
        ```go
        type Logger interface {
            Log(message string)
        }

        // 기본 로거
        type BaseLogger struct{}

        func (l *BaseLogger) Log(message string) {
            fmt.Println(message)
        }

        // 데코레이터
        type TimestampLogger struct {
            logger Logger
        }

        func (t *TimestampLogger) Log(message string) {
            t.logger.Log(fmt.Sprintf("[%v] %s", time.Now(), message))
        }
        ```

    2. 컨텍스트 패턴
        ```go
        type Service interface {
            DoSomething(ctx context.Context) error
        }

        type MyService struct{}

        func (s *MyService) DoSomething(ctx context.Context) error {
            select {
            case <-ctx.Done():
                return ctx.Err()
            default:
                // 작업 수행
                return nil
            }
        }
        ```

    3. 옵저버 패턴
        ```go
        type Observer interface {
            Update(message string)
        }

        type Subject struct {
            observers []Observer
        }

        func (s *Subject) Attach(o Observer) {
            s.observers = append(s.observers, o)
        }

        func (s *Subject) Notify(message string) {
            for _, observer := range s.observers {
                observer.Update(message)
            }
        }
        ```

5. 테스트와 모킹
    1. 인터페이스를 이용한 테스트
        ```go
        type DataStore interface {
            Get(id string) ([]byte, error)
            Set(id string, data []byte) error
        }

        // 실제 구현
        type RealDataStore struct {
            // 실제 구현 필드
        }

        // 테스트용 Mock
        type MockDataStore struct {
            data map[string][]byte
        }

        func (m *MockDataStore) Get(id string) ([]byte, error) {
            if data, ok := m.data[id]; ok {
                return data, nil
            }
            return nil, fmt.Errorf("not found")
        }
        ```

    2. 테스트 헬퍼
        ```go
        func TestService(t *testing.T) {
            mock := &MockDataStore{
                data: make(map[string][]byte),
            }
            
            service := NewService(mock)
            
            // 테스트 수행
            err := service.ProcessData("test-id", []byte("test-data"))
            if err != nil {
                t.Errorf("예상치 못한 에러: %v", err)
            }
        }
        ```

6. 인터페이스 안티패턴
    1. 불필요하게 큰 인터페이스
        ```go
        // 나쁜 예
        type BigInterface interface {
            Method1()
            Method2()
            Method3()
            // ... 20개 이상의 메서드
        }

        // 좋은 예
        type SmallInterface1 interface {
            Method1()
        }

        type SmallInterface2 interface {
            Method2()
        }
        ```

    2. 구체적인 타입 노출
        ```go
        // 나쁜 예
        func NewService() *ConcreteService {
            return &ConcreteService{}
        }

        // 좋은 예
        type Service interface {
            Process() error
        }

        func NewService() Service {
            return &ConcreteService{}
        }
        ```

7. Best Practices
    1. 인터페이스는 작게 유지
        ```go
        // 좋은 예
        type Reader interface {
            Read(p []byte) (n int, err error)
        }

        type Writer interface {
            Write(p []byte) (n int, err error)
        }
        ```

    2. 인터페이스는 사용하는 쪽에서 정의
        ```go
        // 패키지 user
        type DataProcessor interface {
            Process(data []byte) error
        }

        // 패키지 storage에서는 인터페이스만 알면 됨
        func (s *Storage) UseProcessor(p DataProcessor) {
            // ...
        }
        ```

    3. 명확한 인터페이스 이름 사용
        ```go
        // 좋은 예
        type Fetcher interface {
            Fetch() error
        }

        // 나쁜 예
        type FetcherInterface interface {
            Fetch() error
        }
        ```

8. Key Points
    1. 인터페이스는 암시적으로 구현됨
    2. 작은 인터페이스가 더 유용함
    3. 인터페이스는 추상화와 테스트를 용이하게 함
    4. 빈 인터페이스는 신중하게 사용
    5. 인터페이스 값은 타입과 값 두 가지 요소로 구성

## Go 메모리 관리와 기본 데이터 구조

1. 메모리 관리
    1. 가비지 컬렉션
        - Go는 자동 메모리 관리를 제공하는 가비지 컬렉션을 사용
        - 동시성 가비지 컬렉터를 사용하여 프로그램 실행 중에도 메모리 회수
        - Mark-and-Sweep 알고리즘 사용
            - Mark: 도달 가능한 객체 표시
            - Sweep: 도달할 수 없는 객체 제거

    2. 메모리 할당
        ```go
        // 스택 할당 (빠름)
        x := 42

        // 힙 할당 (가비지 컬렉션 대상)
        p := new(int) // new는 거의 쓰이지 않음.
        *p = 42
        ```

    3. 이스케이프 분석
        - 컴파일러가 변수의 수명을 분석하여 스택 또는 힙 할당 결정
        - 함수를 벗어나는 참조가 있는 경우 힙에 할당

2. 배열 (Arrays)
    1. 기본 배열
        ```go
        // 고정 크기 배열 선언
        var arr [5]int

        // 초기화와 함께 선언
        arr := [5]int{1, 2, 3, 4, 5}

        // 크기 추론
        arr := [...]int{1, 2, 3, 4, 5}
        ```

    2. 다차원 배열
        ```go
        // 2차원 배열
        var matrix [3][4]int

        // 초기화
        matrix := [2][3]int{
            {1, 2, 3},
            {4, 5, 6},
        }
        ```

3. 슬라이스 (Slices)
    1. 기본 슬라이스
        ```go
        // 슬라이스 선언
        var s []int

        // make를 사용한 초기화
        s := make([]int, 5)    // 길이 5
        s := make([]int, 5, 10) // 길이 5, 용량 10

        // 리터럴로 초기화
        s := []int{1, 2, 3, 4, 5}
        ```

    2. 슬라이스 연산
        ```go
        // 슬라이싱
        arr := [5]int{1, 2, 3, 4, 5}
        s := arr[1:4] // [2, 3, 4]

        // append
        s = append(s, 6)

        // copy
        dst := make([]int, len(s))
        copy(dst, s)
        ```

    3. 슬라이스 내부 구조
        ```go
        type slice struct {
            array unsafe.Pointer // 기본 배열에 대한 포인터
            len   int           // 길이
            cap   int           // 용량
        }
        ```

4. make와 new
    1. make 함수
        - 슬라이스, 맵, 채널 생성에 사용
        - 초기화된 (제로값이 아닌)데이터 구조 변환

        ```go
        // 슬라이스 생성
        s := make([]int, 5, 10)

        // 맵 생성
        m := make(map[string]int)

        // 채널 생성
        ch := make(chan int, 100)
        ```

    2. new 함수
        - 모든 타입의 포인터 할당에 사용
        - 제로값으로 초기화된 포인터 반환

        ```go
        // int 포인터 생성
        p := new(int)

        // 구조체 포인터 생성
        type Person struct {
            Name string
            Age  int
        }
        p := new(Person)
        ```

5. 메모리 최적화 기법
    1. 슬라이스 최적화
        ```go
        // 용량 미리 할당
        s := make([]int, 0, 1000)
        for i := 0; i < 1000; i++ {
            s = append(s, i)
        }

        // 사용하지 않는 참조 제거
        s = append(s[:i], s[i+1:]...)
        s = s[:len(s)-1] // 마지막 요소 제거
        ```

    2. 메모리 재사용
        ```go
        // 버퍼 재사용
        var bufferPool = sync.Pool{
            New: func() interface{} {
                return make([]byte, 4096)
            },
        }

        func Process() {
            buf := bufferPool.Get().([]byte)
            defer bufferPool.Put(buf)
            // 버퍼 사용
        }
        ```

6. 주의사항과 모범 사례
    1. 슬라이스 사용 시 주의사항
        - 큰 배열의 작은 슬라이스를 유지하면 메모리 누수 발생 가능
        - 필요한 경우 copy를 사용하여 새로운 슬라이스 생성

    2. 메모리 효율적인 코드 작성
        ```go
        // 구조체 필드 정렬
        type Efficient struct {
            a int64  // 8바이트
            b int64  // 8바이트
            c int32  // 4바이트
            d int16  // 2바이트
            e int8   // 1바이트
        }

        // 비효율적인 구조체
        type Inefficient struct {
            a int8   // 1바이트 + 7바이트 패딩
            b int64  // 8바이트
            c int16  // 2바이트 + 6바이트 패딩
            d int32  // 4바이트 + 4바이트 패딩
            e int64  // 8바이트
        }
        ```

7. Key Points
    1. Go의 메모리 관리는 자동화되어 있지만 이해가 필요
    2. 배열은 고정 크기, 슬라이스는 동적 크기
    3. make는 슬라이스, 맵, 채널용, new는 포인터용
    4. 메모리 최적화는 성능에 중요한 영향을 미침
    5. 구조체 필드 순서는 메모리 사용에 영향을 줌

## Go 패키지와 모듈 (Packages and Moduels)

1. 패키지 기본 (Packages)
    1. 패키지 정의
        ```go
        // math/calculator.go
        package math

        func Add(a, b int) int {
            return a + b
        }

        func Subtract(a, b int) int {
            return a - b
        }

        // main.go
        package main

        import (
            "myapp/math"
            "fmt"
        )

        func main() {
            result := math.Add(5, 3)
            fmt.Println(result)
        }
        ```

    2. 패키지와 가시성
        ```go
        package mypackage

        // 외부에서 접근 가능 (대문자로 시작)
        func ExportedFunction() {
            // ...
        }

        // 패키지 내부에서만 접근 가능 (소문자로 시작)
        func privateFunction() {
            // ...
        }

        // 외부에서 접근 가능한 변수/상수
        var ExportedVar = 42
        const ExportedConst = "visible"

        // 패키지 내부에서만 접근 가능한 변수/상수
        var privateVar = "hidden"
        const privateConst = "hidden"
        ```

2. 패키지 구성
    1. 디렉토리 구조
        ```
        myapp/
        ├── main.go
        ├── internal/       # 내부 패키지
        │   └── auth/
        │       └── auth.go
        ├── pkg/           # 외부에서 사용 가능한 패키지
        │   ├── models/
        │   │   └── user.go
        │   └── utils/
        │       └── helper.go
        └── go.mod
        ```

    2. internal 패키지
        ```go
        // myapp/internal/auth/auth.go
        package auth

        func ValidateToken(token string) bool {
            // ...
        }

        // myapp/main.go
        package main

        import "myapp/internal/auth"

        func main() {
            auth.ValidateToken("token")  // 같은 모듈 내에서만 가능
        }
        ```

    3. 패키지 초기화
        ```go
        package database

        import "fmt"

        // 패키지 레벨 변수
        var db *Database

        // init 함수는 패키지가 임포트될 때 자동으로 실행
        func init() {
            fmt.Println("데이터베이스 초기화 중...")
            db = NewDatabase()
        }

        func init() {
            // 여러 init 함수 가능
            fmt.Println("추가 초기화...")
        }
        ```

3. 모듈 (Modules)
    1. 모듈 초기화
        ```go
        # 새 모듈 생성
        go mod init github.com/username/project

        # 의존성 다운로드
        go mod download

        # 의존성 정리
        go mod tidy
        ```

    2. go.mod 파일
        ```go
        module github.com/username/project

        go 1.20

        require (
            github.com/gin-gonic/gin v1.7.4
            github.com/go-sql-driver/mysql v1.6.0
        )

        // 간접 의존성
        require github.com/stretchr/testify v1.7.0 // indirect
        ```

    3. 버전 관리
        ```go
        # 특정 버전 추가
        go get github.com/some/package@v1.2.3

        # 최신 버전 사용
        go get -u github.com/some/package

        # 특정 의존성 제거
        go get github.com/some/package@none
        ```

4. 의존성 관리
    1. 직접 의존성
        ```go
        // go.mod
        module myapp

        require (
            github.com/gin-gonic/gin v1.7.4
            github.com/go-redis/redis/v8 v8.11.4
        )
        ```

    2. 간접 의존성 관리
        ```go
        // go.mod
        require github.com/indirect/dependency v1.2.3 // indirect

        // 의존성 교체
        replace github.com/original/package => github.com/fork/package v1.2.3
        ```

    3. 벤더링
        ```go
        # 벤더 디렉토리 생성
        go mod vendor

        # 벤더 디렉토리 사용하여 빌드
        go build -mod=vendor
        ```

5. 작업 공간 (Workspaces)
    1. 다중 모듈 작업 공간
        ```go
        # 작업 공간 초기화
        go work init ./module1 ./module2

        # go.work 파일 생성됨
        ```

    2. go.work 파일
        ```go
        go 1.20

        use (
            ./module1
            ./module2
        )

        replace github.com/original/package => ../local/package
        ```

6. 패키지 설계 패턴
    1. 인터페이스 분리
        ```go
        // interfaces/storage.go
        package interfaces

        type Storage interface {
            Save(data []byte) error
            Load() ([]byte, error)
        }

        // implementations/file/storage.go
        package file

        type FileStorage struct {
            path string
        }

        func (fs *FileStorage) Save(data []byte) error {
            // 구현
        }

        func (fs *FileStorage) Load() ([]byte, error) {
            // 구현
        }
        ```

    2. 팩토리 패턴
        ```go
        // factory/storage.go
        package factory

        import (
            "myapp/interfaces"
            "myapp/implementations/file"
            "myapp/implementations/memory"
        )

        func NewStorage(storageType string) interfaces.Storage {
            switch storageType {
            case "file":
                return &file.FileStorage{}
            case "memory":
                return &memory.MemoryStorage{}
            default:
                return nil
            }
        }
        ```

7. 테스트 구성
    1. 테스트 파일 구조
        ```go
        package/
        ├── code.go
        ├── code_test.go
        └── testdata/
            └── test.json
        ```

    2. 테스트 패키지
        ```go
        // code_test.go
        package mypackage_test  // 별도의 패키지로 테스트

        import (
            "testing"
            "myapp/mypackage"
        )

        func TestSomething(t *testing.T) {
            // 테스트 코드
        }
        ```

8. Best Practices
    1. 패키지 구조화
        ```
        myapp/
        ├── cmd/                    # 실행 파일
        │   └── server/
        │       └── main.go
        ├── internal/               # 내부 패키지
        │   ├── auth/
        │   └── config/
        ├── pkg/                    # 공개 패키지
        │   ├── models/
        │   └── utils/
        ├── api/                    # API 정의
        │   └── proto/
        ├── docs/                   # 문서
        ├── scripts/                # 스크립트
        ├── test/                   # 통합 테스트
        └── go.mod
        ```

    2. 의존성 관리 원칙
        1. 순환 의존성 피하기
        2. 의존성은 최소한으로 유지
        3. go.mod는 정기적으로 정리 (go mod tidy)
        4. 버전 제약은 최소한으로 설정

    3. 모듈 버전 관리
        ```bash
        # 태그 기반 버전 관리
        git tag v1.0.0
        git push --tags

        # 주요 버전 업그레이드
        git tag v2.0.0
        ```

9. Key Points
    1. 패키지명은 간단하고 명확하게
    2. internal 패키지로 비공개 코드 보호
    3. go.mod로 의존성 명시적 관리
    4. 작은 패키지, 명확한 책임
    5. 순환 의존성 방지

## Go 에러 처리 (Error handling)

1. 기본 에러 처리
    1. error 인터페이스
        ```go
        // error 인터페이스 정의
        type error interface {
            Error() string
        }

        // 기본 에러 생성
        err := errors.New("something went wrong")

        // fmt.Errorf를 사용한 에러 생성
        name := "file.txt"
        err := fmt.Errorf("failed to open %s", name)
        ```

    2. 에러 감사
        ```go
        // 기본 에러 체크 패턴
        if err != nil {
            return err
        }

        // 여러 반환값이 있는 경우
        result, err := someFunction()
        if err != nil {
            return nil, err  // 결과값과 함께 에러 반환
        }
        ```

    3. 사용자 정의 에러
        ```go
        // 커스텀 에러 타입
        type ValidationError struct {
            Field string
            Message string
        }

        // Error 인터페이스 구현
        func (e *ValidationError) Error() string {
            return fmt.Sprintf("validation failed on %s: %s", e.Field, e.Message)
        }

        // 사용 예
        func validateAge(age int) error {
            if age < 0 {
                return &ValidationError{
                    Field: "age",
                    Message: "age cannot be negative",
                }
            }
            return nil
        }
        ```

2. 에러 래핑 (Error Wrapping)
    1. 기본 에러 래핑
        ```go
        // fmt.Errorf와 %w를 사용한 에러 래핑
        originalErr := errors.New("original error")
        wrappedErr := fmt.Errorf("failed to process: %w", originalErr)

        // errors.Unwrap을 사용한 래핑 해제
        unwrappedErr := errors.Unwrap(wrappedErr)

        // errors.Is를 사용한 에러 비교
        if errors.Is(wrappedErr, originalErr) {
            fmt.Println("errors match")
        }
        ```

    2. 에러 체인
        ```go
        func readConfig() error {
            err := readFile()
            if err != nil {
                return fmt.Errorf("config error: %w", err)
            }
            return nil
        }

        func readFile() error {
            err := openFile()
            if err != nil {
                return fmt.Errorf("file error: %w", err)
            }
            return nil
        }
        ```

    3. 에러 타입 검사
        ```go
        // errors.As를 사용한 타입 단언
        var validationErr *ValidationError
        if errors.As(err, &validationErr) {
            fmt.Printf("Validation error: %s\n", validationErr.Message)
        }

        // 여러 에러 타입 처리
        func handleError(err error) {
            var netErr *net.OpError
            var pathErr *os.PathError

            switch {
            case errors.As(err, &netErr):
                fmt.Println("network error:", netErr.Error())
            case errors.As(err, &pathErr):
                fmt.Println("path error:", pathErr.Error())
            default:
                fmt.Println("unknown error:", err)
            }
        }
        ```

3. 에러 처리 패턴
    1. 함수 시그니처 패턴
        ```go
        // 에러를 마지막 반환값으로
        func DoSomething() (Result, error)

        // 에러만 반환
        func Validate() error

        // 여러 결과와 에러
        func Process() (int, string, error)
        ```

    2. 에러 타입 계층
        ```go
        // 기본 에러 타입
        type AppError struct {
            Err     error
            Message string
            Code    int
        }

        func (e *AppError) Error() string {
            return e.Message
        }

        func (e *AppError) Unwrap() error {
            return e.Err
        }

        // 특정 에러 타입들
        type NotFoundError struct {
            *AppError
        }

        type ValidationError struct {
            *AppError
        }

        // 팩토리 함수
        func NewNotFoundError(message string) error {
            return &NotFoundError{
                AppError: &AppError{
                    Message: message,
                    Code:    404,
                },
            }
        }
        ```

    3. 에러 핸들러 패턴
        ```go
        type ErrorHandler struct {
            handlers map[error]func(error) error
        }

        func (eh *ErrorHandler) Handle(err error) error {
            for baseErr, handler := range eh.handlers {
                if errors.Is(err, baseErr) {
                    return handler(err)
                }
            }
            return err
        }

        // 사용 예
        handler := &ErrorHandler{
            handlers: map[error]func(error) error{
                io.EOF: func(err error) error {
                    return fmt.Errorf("end of file reached: %w", err)
                },
                os.ErrNotExist: func(err error) error {
                    return fmt.Errorf("file not found: %w", err)
                },
            },
        }
        ```

4. panic과 recover
    1. panic 기본
        ```go
        func doSomething() {
            panic("something went terribly wrong")
        }

        // recover를 사용한 panic 처리
        func handlePanic() {
            if r := recover(); r != nil {
                fmt.Printf("Recovered from panic: %v\n", r)
            }
        }

        func main() {
            defer handlePanic()
            doSomething()
        }
        ```

    2. panic vs error
        ```go
        // panic 사용이 적절한 경우
        func init() {
            if err := loadConfig(); err != nil {
                panic(fmt.Sprintf("failed to load config: %v", err))
            }
        }

        // error 반환이 적절한 경우
        func processUserData(data []byte) error {
            if len(data) == 0 {
                return errors.New("empty data")
            }
            return nil
        }
        ```

5. 실용적인 에러 처리 예제
    1. 데이터베이스 에러 처리
        ```go
        type DBError struct {
            Err     error
            Query   string
            Message string
        }

        func (e *DBError) Error() string {
            return fmt.Sprintf("database error: %s: %v", e.Message, e.Err)
        }

        func (e *DBError) Unwrap() error {
            return e.Err
        }

        func queryDB(query string) error {
            err := db.Exec(query)
            if err != nil {
                return &DBError{
                    Err:     err,
                    Query:   query,
                    Message: "failed to execute query",
                }
            }
            return nil
        }
        ```

    2. HTTP 에러 처리
        ```go
        type HTTPError struct {
            StatusCode int
            Err        error
        }

        func (e *HTTPError) Error() string {
            return fmt.Sprintf("HTTP %d: %v", e.StatusCode, e.Err)
        }

        func (e *HTTPError) Unwrap() error {
            return e.Err
        }

        func handleRequest(w http.ResponseWriter, r *http.Request) {
            err := processRequest(r)
            if err != nil {
                var httpErr *HTTPError
                if errors.As(err, &httpErr) {
                    http.Error(w, httpErr.Error(), httpErr.StatusCode)
                    return
                }
                http.Error(w, err.Error(), http.StatusInternalServerError)
            }
        }
        ```

6. 에러 로깅과 모니터링
    1. 구조화된 로깅
        ```go
        type LoggedError struct {
            error
            Time    time.Time
            Context map[string]interface{}
        }

        func NewLoggedError(err error, context map[string]interface{}) *LoggedError {
            return &LoggedError{
                error:   err,
                Time:    time.Now(),
                Context: context,
            }
        }

        func (e *LoggedError) Log() {
            log.Printf("Error: %v\nTime: %v\nContext: %+v\n",
                e.error, e.Time, e.Context)
        }
        ```

    2. 에러 메트릭
        ```go
        type MetricError struct {
            error
            MetricName string
        }

        func (e *MetricError) Record() {
            metrics.Increment(e.MetricName)
        }

        // 사용 예
        func processWithMetrics() error {
            err := process()
            if err != nil {
                return &MetricError{
                    error:      err,
                    MetricName: "process_errors",
                }
            }
            return nil
        }
        ```

7. Best Practices
    1. 에러 처리는 명시적으로
        ```go
        // 좋은 예
        err := doSomething()
        if err != nil {
            return fmt.Errorf("failed to do something: %w", err)
        }

        // 나쁜 예
        if doSomething() != nil {  // 에러 무시
            // ...
        }
        ```

    2. 의미 있는 에러 메시지
        ```go
        // 좋은 예
        return fmt.Errorf("failed to open config file %q: %w", filename, err)

        // 나쁜 예
        return fmt.Errorf("failed: %w", err)
        ```

    3. 적절한 추상화 레벨
        ```go
        // 좋은 예
        type StorageError struct {
            Operation string
            Path      string
            Err       error
        }

        // 나쁜 예
        type Error struct {
            Message string
        }
        ```

8. Key Points
    1. 에러는 값이다: 에러를 일급 시민으로 취급
    2. 명시적 에러 처리: 에러를 무시하지 않음
    3. 에러 래핑: 컨텍스트 추가하여 에러 전파
    4. panic은 예외적인 상황에만 사용
    5. 적절한 에러 타입 설계가 중요

## Go 테스팅 (Testing)

1. 기본 테스트
    1. 테스트 파일 작성
        ```go
        // calculator.go
        package calculator

        func Add(a, b int) int {
            return a + b
        }

        // calculator_test.go
        package calculator

        import "testing"

        func TestAdd(t *testing.T) {
            result := Add(2, 3)
            if result != 5 {
                t.Errorf("Add(2, 3) = %d; want 5", result)
            }
        }
        ```

    2. 테스트 실행
        ```bash
        # 모든 테스트 실행
        go test ./...

        # 특정 패키지 테스트 실행
        go test ./calculator

        # 특정 테스트 실행
        go test -run TestAdd

        # 상세 출력
        go test -v ./...
        ```

    3. 테이블 주도 테스트
        ```go
        func TestAdd(t *testing.T) {
            tests := []struct {
                name     string
                a, b     int
                expected int
            }{
                {"positive numbers", 2, 3, 5},
                {"zero and positive", 0, 1, 1},
                {"negative numbers", -2, -3, -5},
            }

            for _, tt := range tests {
                t.Run(tt.name, func(t *testing.T) {
                    result := Add(tt.a, tt.b)
                    if result != tt.expected {
                        t.Errorf("Add(%d, %d) = %d; want %d", 
                            tt.a, tt.b, result, tt.expected)
                    }
                })
            }
        }
        ```

2. 테스트 도구
    1. 서브테스트와 병렬 테스트
        ```go
        func TestParallel(t *testing.T) {
            tests := []struct {
                name string
                fn   func(t *testing.T)
            }{
                {
                    name: "test1",
                    fn: func(t *testing.T) {
                        // test code
                    },
                },
                {
                    name: "test2",
                    fn: func(t *testing.T) {
                        // test code
                    },
                },
            }

            for _, tt := range tests {
                tt := tt // 변수 캡처를 위한 복사
                t.Run(tt.name, func(t *testing.T) {
                    t.Parallel() // 병렬 실행
                    tt.fn(t)
                })
            }
        }
        ```

    2. 테스트 헬퍼
        ```go
        func setupTestCase(t *testing.T) func() {
            t.Helper() // 이 함수가 헬퍼임을 표시

            // 테스트 셋업
            db := setupDatabase()

            // cleanup 함수 반환
            return func() {
                db.Close()
            }
        }

        func TestWithSetup(t *testing.T) {
            cleanup := setupTestCase(t)
            defer cleanup()

            // 테스트 코드
        }
        ```

3. 테스트 커버리지
    1. 커버리지 측정
        ```bash
        # 커버리지 측정
        go test -cover ./...

        # 커버리지 프로필 생성
        go test -coverprofile=coverage.out ./...

        # HTML 보고서 생성
        go tool cover -html=coverage.out
        ```

    2. 커버리지 목표 설정
        ```bash
        # 최소 커버리지 비율 설정
        go test -cover -covermode=atomic -coverpkg=./... -coverprofile=coverage.out -minimum=80
        ```

4. 벤치마크
    1. 기본 벤치마크
        ```go
        func BenchmarkAdd(b *testing.B) {
            for i := 0; i < b.N; i++ {
                Add(2, 3)
            }
        }
        ```

    2. 벤치마크 실행
        ```bash
        # 벤치마크 실행
        go test -bench=.

        # 자세한 메모리 통계
        go test -bench=. -benchmem
        ```

    3. 벤치마크 비교
        ```go
        func BenchmarkMethod1(b *testing.B) {
            for i := 0; i < b.N; i++ {
                method1()
            }
        }

        func BenchmarkMethod2(b *testing.B) {
            for i := 0; i < b.N; i++ {
                method2()
            }
        }
        ```

5. 모의 객체 (Mocking)
    1. 인터페이스를 활용한 모킹
        ```go
        type Database interface {
            Get(id string) (string, error)
            Set(id string, value string) error
        }

        type MockDB struct {
            GetFunc func(id string) (string, error)
            SetFunc func(id string, value string) error
        }

        func (m *MockDB) Get(id string) (string, error) {
            return m.GetFunc(id)
        }

        func (m *MockDB) Set(id string, value string) error {
            return m.SetFunc(id, value)
        }

        func TestWithMock(t *testing.T) {
            mock := &MockDB{
                GetFunc: func(id string) (string, error) {
                    return "test_value", nil
                },
            }

            // 테스트 코드
            result, err := mock.Get("123")
            if err != nil {
                t.Errorf("unexpected error: %v", err)
            }
            if result != "test_value" {
                t.Errorf("got %q, want %q", result, "test_value")
            }
        }
        ```

    2. 테스트 더블
        ```go
        type StubUserRepository struct {
            users map[string]User
        }

        func NewStubUserRepository() *StubUserRepository {
            return &StubUserRepository{
                users: make(map[string]User),
            }
        }

        func (s *StubUserRepository) GetUser(id string) (User, error) {
            user, ok := s.users[id]
            if !ok {
                return User{}, fmt.Errorf("user not found")
            }
            return user, nil
        }
        ```

6. HTTP 테스트
    1. HTTP 핸들러 테스트
        ```go
        func TestHandler(t *testing.T) {
            req, err := http.NewRequest("GET", "/api/users", nil)
            if err != nil {
                t.Fatal(err)
            }

            rr := httptest.NewRecorder()
            handler := http.HandlerFunc(UserHandler)

            handler.ServeHTTP(rr, req)

            if status := rr.Code; status != http.StatusOK {
                t.Errorf("handler returned wrong status code: got %v want %v",
                    status, http.StatusOK)
            }

            expected := `{"message":"success"}`
            if rr.Body.String() != expected {
                t.Errorf("handler returned unexpected body: got %v want %v",
                    rr.Body.String(), expected)
            }
        }
        ```

    2. 테스트 서버
        ```go
        func TestServer(t *testing.T) {
            ts := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
                fmt.Fprintln(w, "Hello, client")
            }))
            defer ts.Close()

            resp, err := http.Get(ts.URL)
            if err != nil {
                t.Fatal(err)
            }
            defer resp.Body.Close()

            body, err := ioutil.ReadAll(resp.Body)
            if err != nil {
                t.Fatal(err)
            }

            expected := "Hello, client\n"
            if string(body) != expected {
                t.Errorf("got %q, want %q", string(body), expected)
            }
        }
        ```

7. 종합적인 테스트 전략
    1. 통합 테스트
        ```go
        func TestIntegration(t *testing.T) {
            if testing.Short() {
                t.Skip("skipping integration test in short mode")
            }

            // 데이터베이스 연결
            db := setupTestDatabase(t)
            defer db.Close()

            // API 클라이언트 설정
            client := setupTestClient(t)

            // 테스트 실행
            t.Run("database operations", func(t *testing.T) {
                // DB 테스트
            })

            t.Run("api calls", func(t *testing.T) {
                // API 테스트
            })
        }
        ```

    2. 테스트 환경 설정
        ```go
        func TestMain(m *testing.M) {
            // 테스트 전 설정
            setup()

            // 테스트 실행
            code := m.Run()

            // 테스트 후 정리
            cleanup()

            // 종료 코드 반환
            os.Exit(code)
        }
        ```

8. 테스트 모범 사례
    1. 테스트 구조화
        ```go
        // 각 테스트는 독립적이어야 함
        func TestFeature(t *testing.T) {
            // Arrange
            input := "test input"
            expected := "expected output"

            // Act
            result := processInput(input)

            // Assert
            if result != expected {
                t.Errorf("got %q, want %q", result, expected)
            }
        }
        ```

    2. 테스트 가독성
        ```go
        // 헬퍼 함수 사용
        func assertNoError(t *testing.T, err error) {
            t.Helper()
            if err != nil {
                t.Fatalf("unexpected error: %v", err)
            }
        }

        func assertEqual(t *testing.T, got, want interface{}) {
            t.Helper()
            if got != want {
                t.Errorf("got %v, want %v", got, want)
            }
        }
        ```

9. Key Points
    1. Go의 테스트는 간단하고 내장되어 있음
    2. 테이블 주도 테스트를 활용하여 다양한 케이스 테스트
    3. 벤치마크로 성능 측정
    4. 모의 객체는 인터페이스를 활용
    5. 테스트 커버리지를 통한 품질 관리

## Go 동시성 패턴과 실제 사례 (Concurrency Patterns and Examples)

1. 워커 풀 패턴 (Worker Pool)
    1. 기본 워커 풀
        ```go
        func worker(id int, jobs <-chan int, results chan<- int) {
            for j := range jobs {
                fmt.Printf("worker %d started job %d\n", id, j)
                time.Sleep(time.Second) // 작업 시뮬레이션
                results <- j * 2
            }
        }

        func main() {
            const numJobs = 5
            jobs := make(chan int, numJobs)
            results := make(chan int, numJobs)

            // 워커 시작
            for w := 1; w <= 3; w++ {
                go worker(w, jobs, results)
            }

            // 작업 전송
            for j := 1; j <= numJobs; j++ {
                jobs <- j
            }
            close(jobs)

            // 결과 수집
            for a := 1; a <= numJobs; a++ {
                <-results
            }
        }
        ```

    2. 워커 풀 관리자
        ```go
        type WorkerPool struct {
            maxWorkers int
            jobs       chan Job
            results    chan Result
            done       chan bool
        }

        func NewWorkerPool(maxWorkers int) *WorkerPool {
            return &WorkerPool{
                maxWorkers: maxWorkers,
                jobs:       make(chan Job),
                results:    make(chan Result),
                done:       make(chan bool),
            }
        }

        func (p *WorkerPool) Start() {
            for i := 0; i < p.maxWorkers; i++ {
                go p.worker()
            }
        }

        func (p *WorkerPool) Stop() {
            close(p.jobs)
            for i := 0; i < p.maxWorkers; i++ {
                <-p.done
            }
            close(p.results)
        }
        ```

2. 파이프라인 패턴
    1. 기본 파이프라인
        ```go
        func generator(nums ...int) <-chan int {
            out := make(chan int)
            go func() {
                for _, n := range nums {
                    out <- n
                }
                close(out)
            }()
            return out
        }

        func square(in <-chan int) <-chan int {
            out := make(chan int)
            go func() {
                for n := range in {
                    out <- n * n
                }
                close(out)
            }()
            return out
        }

        func main() {
            // 파이프라인 구성
            c := generator(2, 3)
            out := square(c)

            // 결과 소비
            fmt.Println(<-out) // 4
            fmt.Println(<-out) // 9
        }
        ```

    2. 다단계 파이프라인
        ```go
        type PipelineStage func(<-chan interface{}) <-chan interface{}

        func Pipeline(source <-chan interface{}, stages ...PipelineStage) <-chan interface{} {
            current := source
            for _, stage := range stages {
                current = stage(current)
            }
            return current
        }

        // 사용 예
        func main() {
            source := make(chan interface{})
            result := Pipeline(
                source,
                filterStage,
                transformStage,
                aggregateStage,
            )
            
            // 파이프라인 사용
            go func() {
                for i := 0; i < 100; i++ {
                    source <- i
                }
                close(source)
            }()

            for v := range result {
                fmt.Println(v)
            }
        }
        ```

3. Fan-out, Fan-in 패턴
    1. 기본 구현
        ```go
        func fanOut(ch <-chan int, n int) []<-chan int {
            channels := make([]<-chan int, n)
            for i := 0; i < n; i++ {
                channels[i] = processChannel(ch)
            }
            return channels
        }

        func fanIn(channels ...<-chan int) <-chan int {
            var wg sync.WaitGroup
            multiplexed := make(chan int)

            wg.Add(len(channels))
            for _, ch := range channels {
                go func(c <-chan int) {
                    defer wg.Done()
                    for i := range c {
                        multiplexed <- i
                    }
                }(ch)
            }

            go func() {
                wg.Wait()
                close(multiplexed)
            }()

            return multiplexed
        }
        ```

    2. 실제 사용 사례
        ```go
        func processImage(filename string) error {
            // 이미지 로드
            img, err := loadImage(filename)
            if err != nil {
                return err
            }

            // 작업을 여러 고루틴으로 분산
            parts := splitImage(img, 4)
            channels := fanOut(parts, 4)
            
            // 결과 취합
            results := fanIn(channels...)
            
            // 최종 결과 처리
            for result := range results {
                // 처리된 이미지 부분 조합
            }
            
            return nil
        }
        ```

4. 시간 제한 패턴 (Timeout Patterns)
    1. 컨텍스트 사용
        ```go
        func processWithTimeout(ctx context.Context, data string) (string, error) {
            resultCh := make(chan string)
            
            go func() {
                result := heavyProcess(data)
                resultCh <- result
            }()

            select {
            case result := <-resultCh:
                return result, nil
            case <-ctx.Done():
                return "", ctx.Err()
            }
        }

        func main() {
            ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)
            defer cancel()

            result, err := processWithTimeout(ctx, "input")
            if err != nil {
                log.Printf("Processing failed: %v", err)
                return
            }
            fmt.Println("Result:", result)
        }
        ```

    2. 타임아웃 채널
        ```go
        func timeoutPattern(timeout time.Duration) error {
            done := make(chan bool)
            
            go func() {
                // 장시간 작업
                time.Sleep(time.Second * 2)
                done <- true
            }()

            select {
            case <-done:
                return nil
            case <-time.After(timeout):
                return errors.New("operation timed out")
            }
        }
        ```

5. 취소 패턴
    1. 컨텍스트 기반 취소
        ```go
        func processingWorker(ctx context.Context, jobs <-chan int) {
            for {
                select {
                case <-ctx.Done():
                    fmt.Println("Worker cancelled")
                    return
                case job, ok := <-jobs:
                    if !ok {
                        return
                    }
                    // 작업 처리
                    process(job)
                }
            }
        }

        func main() {
            ctx, cancel := context.WithCancel(context.Background())
            defer cancel()

            jobs := make(chan int)
            go processingWorker(ctx, jobs)

            // 일정 시간 후 작업 취소
            time.Sleep(time.Second * 5)
            cancel()
        }
        ```

    2. 채널 기반 취소
        ```go
        func worker(done <-chan struct{}, inputs <-chan int) <-chan int {
            results := make(chan int)
            go func() {
                defer close(results)
                for {
                    select {
                    case <-done:
                        return
                    case input, ok := <-inputs:
                        if !ok {
                            return
                        }
                        results <- process(input)
                    }
                }
            }()
            return results
        }
        ```

6. 속도 제한 패턴 (Rate Limiting)
    1. 토큰 버킷 제한하기
        ```go
        type RateLimiter struct {
            rate  time.Duration
            burst int
            tokens chan struct{}
        }

        func NewRateLimiter(rate time.Duration, burst int) *RateLimiter {
            rl := &RateLimiter{
                rate:   rate,
                burst:  burst,
                tokens: make(chan struct{}, burst),
            }
            
            go func() {
                ticker := time.NewTicker(rate)
                defer ticker.Stop()
                
                for range ticker.C {
                    select {
                    case rl.tokens <- struct{}{}:
                    default:
                    }
                }
            }()
            
            return rl
        }

        func (rl *RateLimiter) Allow() bool {
            select {
            case <-rl.tokens:
                return true
            default:
                return false
            }
        }
        ```

    2. 시간 기반 제한기
        ```go
        func rateLimitedWorker(requests <-chan int) {
            limiter := time.Tick(200 * time.Millisecond)
            for req := range requests {
                <-limiter // 200ms마다 하나의 요청 처리
                processRequest(req)
            }
        }
        ```

7. 리소스 풀 패턴
    1. 연결 풀
        ```go
        type Pool struct {
            resources chan *Resource
        }

        func NewPool(size int) *Pool {
            return &Pool{
                resources: make(chan *Resource, size),
            }
        }

        func (p *Pool) Acquire() (*Resource, error) {
            select {
            case r := <-p.resources:
                return r, nil
            default:
                return NewResource()
            }
        }

        func (p *Pool) Release(r *Resource) {
            select {
            case p.resources <- r:
            default:
                r.Close()
            }
        }
        ```

    2. 데이터베이스 연결 풀
        ```go
        type DBPool struct {
            conns chan *sql.DB
            url   string
        }

        func NewDBPool(url string, maxConns int) (*DBPool, error) {
            pool := &DBPool{
                conns: make(chan *sql.DB, maxConns),
                url:   url,
            }
            
            for i := 0; i < maxConns; i++ {
                conn, err := sql.Open("postgres", url)
                if err != nil {
                    return nil, err
                }
                pool.conns <- conn
            }
            
            return pool, nil
        }
        ```

8. 실제 응용 사례
    1. 웹 크롤러
        ```go
        type Crawler struct {
            visited map[string]bool
            mutex   sync.Mutex
            wg      sync.WaitGroup
            semaphore chan struct{}
        }

        func (c *Crawler) Crawl(url string, depth int) {
            c.wg.Add(1)
            go c.crawl(url, depth)
            c.wg.Wait()
        }

        func (c *Crawler) crawl(url string, depth int) {
            defer c.wg.Done()
            
            if depth <= 0 {
                return
            }
            
            c.semaphore <- struct{}{} // 동시 요청 제한
            defer func() { <-c.semaphore }()
            
            c.mutex.Lock()
            if c.visited[url] {
                c.mutex.Unlock()
                return
            }
            c.visited[url] = true
            c.mutex.Unlock()
            
            // URL 처리 및 하위 URL 크롤링
            links := processURL(url)
            for _, link := range links {
                c.wg.Add(1)
                go c.crawl(link, depth-1)
            }
        }
        ```

    2. API 서버
        ```go
        type Server struct {
            router     *mux.Router
            workerPool *WorkerPool
            rateLimiter *RateLimiter
        }

        func (s *Server) handleRequest(w http.ResponseWriter, r *http.Request) {
            if !s.rateLimiter.Allow() {
                http.Error(w, "Too Many Requests", http.StatusTooManyRequests)
                return
            }

            job := NewJob(r)
            result := make(chan Result, 1)
            
            s.workerPool.Submit(job, result)
            
            select {
            case res := <-result:
                respondWithJSON(w, res)
            case <-time.After(5 * time.Second):
                http.Error(w, "Request Timeout", http.StatusRequestTimeout)
            }
        }
        ```

9. Best Practices
    1. 고루틴 누수 방지
        ```go
        func doWorkWithCleanup() {
            done := make(chan struct{})
            defer close(done)

            go func() {
                select {
                case <-done:
                    return
                default:
                    // 작업 수행
                }
            }()
        }
        ```

    2. 에러 처리
        ```go
        func processWithErrors(ctx context.Context, data []string) error {
            errs := make(chan error, len(data))
            
            for _, item := range data {
                go func(item string) {
                    if err := process(item); err != nil {
                        errs <- err
                        return
                    }
                    errs <- nil
                }(item)
            }
            
            // 모든 에러 수집
            var errList []error
            for range data {
                if err := <-errs; err != nil {
                    errList = append(errList, err)
                }
            }
            
            if len(errList) > 0 {
                return fmt.Errorf("multiple errors occurred: %v", errList)
            }
            return nil
        }
        ```

10. Key Points
    1. 적절한 동시성 패턴 선택이 중요
    2. 리소스 제한과 타임아웃 항상 고려
    3. 컨텍스트를 통한 취소 처리
    4. 고루틴 누수 방지
    5. 에러 처리와 리소스 정리

## 최신 기능과 고급 활용

1. 제네릭 프로그래밍 (Go 1.18+)
    1. 기본 제네릭 함수
        ```go
        import "golang.org/x/exp/constraints"

        // 제네릭 타입 파라미터
        func Min[T constraints.Ordered](x, y T) T {
            if x < y {
                return x
            }
            return y
        }

        // 사용 예시
        minInt := Min[int](10, 20)
        minFloat := Min[float64](3.14, 2.71)

        // 타입 추론
        minInferred := Min(10, 20) // 타입 파라미터 생략 가능
        ```

    2. 제네릭 자료구조
        ```go
        // 제네릭 스택
        type Stack[T any] struct {
            items []T
        }

        func (s *Stack[T]) Push(item T) {
            s.items = append(s.items, item)
        }

        func (s *Stack[T]) Pop() (T, bool) {
            var zero T
            if len(s.items) == 0 {
                return zero, false
            }
            item := s.items[len(s.items)-1]
            s.items = s.items[:len(s.items)-1]
            return item, true
        }

        // 사용 예시
        stack := &Stack[int]{}
        stack.Push(1)
        stack.Push(2)
        value, ok := stack.Pop()
        ```

    3. 제네릭 제약조건
        ```go
        // 커스텀 제약조건
        type Number interface {
            constraints.Integer | constraints.Float
        }

        // 제약조건을 사용한 함수
        func Sum[T Number](numbers []T) T {
            var sum T
            for _, n := range numbers {
                sum += n
            }
            return sum
        }

        // 복합 제약조건
        type Printable interface {
            String() string
        }

        func PrintAll[T Printable](items []T) {
            for _, item := range items {
                fmt.Println(item.String())
            }
        }
        ```

2. Fuzzing 테스트 (Go 1.18+)
    1. 기본 Fuzz 테스트
        ```go
        // 테스트 대상 함수
        func Reverse(s string) string {
            runes := []rune(s)
            for i, j := 0, len(runes)-1; i < j; i, j = i+1, j-1 {
                runes[i], runes[j] = runes[j], runes[i]
            }
            return string(runes)
        }

        // Fuzz 테스트
        func FuzzReverse(f *testing.F) {
            // 시드 케이스 추가
            testcases := []string{"Hello, world", "!12345"}
            for _, tc := range testcases {
                f.Add(tc)
            }

            // Fuzz 테스트 실행
            f.Fuzz(func(t *testing.T, orig string) {
                rev := Reverse(orig)
                doubleRev := Reverse(rev)
                if orig != doubleRev {
                    t.Errorf("Before: %q, after: %q", orig, doubleRev)
                }
                if utf8.ValidString(orig) && !utf8.ValidString(rev) {
                    t.Errorf("Reverse produced invalid UTF-8 string %q", rev)
                }
            })
        }
        ```

3. Workspaces
    1. Workspace 설정
        ```go
        # go.work 파일
        go 1.18

        use (
            ./module1
            ./module2
            ./shared
        )

        replace example.com/original => example.com/fork v1.1.0
        ```

    2. 멀티 모듈 프로젝트 구조
        ```plaintext
        myproject/
        ├── go.work
        ├── module1/
        │   ├── go.mod
        │   └── main.go
        ├── module2/
        │   ├── go.mod
        │   └── main.go
        └── shared/
            ├── go.mod
            └── utils.go
        ```

4. CGO와 외부 라이브러리 연동
    1. 기본 CGO 사용
        ```go
        /*
        #include <stdio.h>
        #include <stdlib.h>

        void printMessage(const char* message) {
            printf("%s\n", message);
        }
        */
        import "C"
        import "unsafe"

        func PrintFromC(message string) {
            cMessage := C.CString(message)
            defer C.free(unsafe.Pointer(cMessage))
            C.printMessage(cMessage)
        }
        ```

    2. CGO 빌드 설정
        ```go
        // #cgo CFLAGS: -I${SRCDIR}/include
        // #cgo LDFLAGS: -L${SRCDIR}/lib -lmylib
        // #include <mylib.h>
        import "C"

        func UseExternalLib() {
            C.mylib_function()
        }
        ```

5. 고급 동시성 패턴
    1. errgroup 사용
        ```go
        import (
            "context"
            "golang.org/x/sync/errgroup"
        )

        func ParallelTasks(ctx context.Context) error {
            g, ctx := errgroup.WithContext(ctx)

            // 첫 번째 작업
            g.Go(func() error {
                return task1(ctx)
            })

            // 두 번째 작업
            g.Go(func() error {
                return task2(ctx)
            })

            // 모든 작업 완료 대기
            return g.Wait()
        }
        ```

    2. sync.Map 활용
        ```go
        // 동시성 안전 Map
        var cache sync.Map

        func GetOrCompute(key string) (interface{}, error) {
            // 캐시된 값 확인
            if value, ok := cache.Load(key); ok {
                return value, nil
            }

            // 값 계산
            value, err := computeExpensiveValue(key)
            if err != nil {
                return nil, err
            }

            // 캐시에 저장 (이미 있으면 기존 값 반환)
            actual, loaded := cache.LoadOrStore(key, value)
            if loaded {
                return actual, nil
            }
            return value, nil
        }
        ```

6. 프로파일링과 디버깅
    1. pprof 프로파일링
        ```go
        import (
            "net/http"
            _ "net/http/pprof"
            "runtime"
            "runtime/pprof"
        )

        func StartProfiler() {
            // HTTP 프로파일러
            go func() {
                http.ListenAndServe("localhost:6060", nil)
            }()
        }

        func CPUProfile(filename string) func() {
            f, _ := os.Create(filename)
            pprof.StartCPUProfile(f)
            return func() {
                pprof.StopCPUProfile()
                f.Close()
            }
        }

        func MemProfile(filename string) {
            f, _ := os.Create(filename)
            defer f.Close()
            runtime.GC()
            pprof.WriteHeapProfile(f)
        }
        ```

    2. 트레이스와 메트릭
        ```go
        import (
            "go.opentelemetry.io/otel"
            "go.opentelemetry.io/otel/trace"
        )

        func TracedFunction(ctx context.Context) error {
            ctx, span := otel.Tracer("my-service").Start(ctx, "TracedFunction")
            defer span.End()

            // 작업 수행
            result, err := doWork(ctx)
            if err != nil {
                span.RecordError(err)
                return err
            }

            span.SetAttributes(attribute.String("result", result))
            return nil
        }
        ```

7. 배포와 운영
    1. 크로스 컴파일
        ```bash
        # Linux용 빌드
        GOOS=linux GOARCH=amd64 go build -o myapp-linux

        # Windows용 빌드
        GOOS=windows GOARCH=amd64 go build -o myapp.exe

        # MacOS용 빌드
        GOOS=darwin GOARCH=amd64 go build -o myapp-mac
        ```

    2. Docker 통합
        ```dockerfile
        # 빌드 스테이지
        FROM golang:1.20-alpine AS builder

        WORKDIR /app
        COPY go.* ./
        RUN go mod download

        COPY . .
        RUN CGO_ENABLED=0 GOOS=linux go build -o /app/server

        # 실행 스테이지
        FROM alpine:latest

        COPY --from=builder /app/server /server
        EXPOSE 8080
        ENTRYPOINT ["/server"]
        ```

    3. Kubernetes 배포
        ```yaml
        apiVersion: apps/v1
        kind: Deployment
        metadata:
        name: myapp
        spec:
        replicas: 3
        selector:
            matchLabels:
            app: myapp
        template:
            metadata:
            labels:
                app: myapp
            spec:
            containers:
            - name: myapp
                image: myapp:latest
                ports:
                - containerPort: 8080
        ```

8. 유용한 개발 도구와 라이브러리
    1. CLI 도구 개발 (cobra)
        ```go
        import "github.com/spf13/cobra"

        func NewRootCmd() *cobra.Command {
            cmd := &cobra.Command{
                Use:   "myapp",
                Short: "My application description",
                Run: func(cmd *cobra.Command, args []string) {
                    // 기본 명령어 실행
                },
            }

            // 하위 명령어 추가
            cmd.AddCommand(NewServeCmd())
            return cmd
        }
        ```

    2. gRPC 서비스
        ```protobuf
        // service.proto
        service MyService {
            rpc DoSomething(Request) returns (Response);
        }
        ```

        ```go
        // 서버 구현
        type server struct {
            pb.UnimplementedMyServiceServer
        }

        func (s *server) DoSomething(ctx context.Context, req *pb.Request) (*pb.Response, error) {
            // 구현
            return &pb.Response{}, nil
        }
        ```

    3. 테스트 도구
        ```go
        // testify 사용
        func TestWithAssertions(t *testing.T) {
            assert := assert.New(t)
            
            result := SomeFunction()
            assert.NotNil(result)
            assert.Equal("expected", result.Value)
        }

        // mockgen으로 생성된 목 사용
        func TestWithMocks(t *testing.T) {
            ctrl := gomock.NewController(t)
            defer ctrl.Finish()

            mockService := mock_service.NewMockService(ctrl)
            mockService.EXPECT().
                DoSomething(gomock.Any()).
                Return("result", nil)
        }
        ```

9. Best Practices
    1. 코드 구조화
        - 패키지는 단일 책임 원칙 준수
        - 의존성 주입 활용
        - 인터페이스는 사용하는 쪽에 정의

    2. 성능 최적화
        - 프로파일링 기반 최적화
        - 메모리 할당 최소화
        - 적절한 고루틴 수 유지

    3. 운영 관점
        - 체계적인 로깅과 모니터링
        - graceful shutdown 구현
        - 헬스체크 엔드포인트 제공

10. 주의사항
    1. CGO 사용
        - 크로스 컴파일 제약 고려
        - 성능 오버헤드 인지
        - 플랫폼 종속성 주의

    2. 고급 기능 활용
        - 제네릭은 필요한 경우에만 사용
        - unsafe 패키지 사용 최소화
        - 복잡한 동시성 패턴 주의