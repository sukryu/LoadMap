# I/O & Filesystem in Go 📂

이 디렉토리는 Go 언어를 사용하여 파일 입출력 및 파일 시스템 작업을 수행하는 방법을 다룹니다.  
기본 파일 작업(파일 생성, 읽기, 쓰기, 디렉토리 관리)부터 시작하여, 버퍼링 I/O, 다양한 파일 형식 처리, 고급 파일 조작, 동시 I/O, 디렉토리 트리 및 동기화, 오류 복구, 네트워크 기반 파일 작업 등 실제 업무에 바로 적용할 수 있는 모범 사례를 학습할 수 있습니다.

---

## What You'll Learn 🎯

- **파일 입출력 기본**:  
  - Go의 `os`, `io`, `ioutil` 패키지를 사용하여 파일 생성, 읽기, 쓰기 작업 수행
- **버퍼링 I/O**:  
  - `bufio`를 사용해 버퍼링된 입출력으로 대용량 데이터 처리 성능 향상
- **디렉토리 및 파일 시스템 관리**:  
  - 디렉토리 생성, 순회, 탐색 및 파일 메타데이터 처리
- **고급 파일 조작**:  
  - 파일 잠금, 임시 파일 생성, 파일 권한 관리, 심볼릭 링크 처리 등의 기능 구현
- **스트리밍 I/O**:  
  - io.Reader, io.Writer 인터페이스를 활용한 청크 단위 데이터 처리 및 진행률 모니터링
- **파일 형식 처리**:  
  - CSV, JSON, XML 등 구조화된 데이터 파일의 읽기/쓰기, 파싱, 검증 기능
- **동시 I/O 작업**:  
  - 병렬 파일 처리, 동시 다운로드, 비동기 파일 작업 및 작업 큐 관리
- **디렉토리 트리 조작**:  
  - 재귀적 디렉토리 순회, 트리 구조 시각화, 디렉토리 동기화 및 변경 감지
- **오류 복구 전략**:  
  - 파일 백업, 체크포인트, 트랜잭션 로그 기록 및 복구 메커니즘 구현
- **네트워크 기반 파일 작업**:  
  - HTTP 파일 서버, 파일 다운로드 및 동시 다운로드 등 네트워크 I/O 패턴

---

## 디렉토리 구조 📁

```plaintext
01-go-basics/
└── io-filesystem/
    ├── main.go                # 기본 I/O 예제 코드
    ├── examples/              # 추가 실습 예제 및 패턴 코드
    │   ├── 01_advanced_file_operations.go  # 파일 잠금, 임시 파일 생성, 권한 관리, 심볼릭 링크 처리
    │   ├── 02_streaming_io.go               # 스트리밍 I/O, 청크 단위 데이터 처리 및 진행률 모니터링
    │   ├── 03_compression.go                # gzip, zip 압축 및 해제 작업
    │   ├── 04_concurrent_io.go              # 동시 I/O 작업 및 병렬 파일 처리
    │   ├── 05_file_formats.go               # CSV, JSON, XML 파일 형식 처리
    │   ├── 06_directory_tree.go             # 재귀적 디렉토리 순회, 트리 시각화, 동기화, 변경 감지
    │   ├── 07_error_recovery.go             # I/O 작업 중 오류 복구 전략 (백업, 체크포인트, 트랜잭션 로그)
    │   └── 08_network_io.go                 # HTTP 파일 서버, 파일 다운로드 및 동시 다운로드
    └── README.md              # 이 문서
```

- **main.go**: 파일 입출력 및 디렉토리 작업의 기본 예제를 포함합니다.
- **examples/**: 다양한 고급 I/O 작업 예제 및 패턴 코드를 통해 실무에서 자주 발생하는 시나리오를 학습할 수 있습니다.

---

## Getting Started 🚀

### 1. 필수 도구 설치
- Go 최신 버전: [Download Go](https://go.dev/dl/)

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/01-go-basics/io-filesystem
```

### 3. 예제 코드 실행
```bash
go run main.go
```
- 실행 결과를 통해 파일 입출력 및 디렉토리 작업이 어떻게 이루어지는지 확인하고, 예제들을 직접 실행하며 학습하세요.

---

## Example Code Snippet 📄

아래는 간단한 파일 입출력 예제입니다:
```go
package main

import (
    "bufio"
    "fmt"
    "io/ioutil"
    "os"
)

func main() {
    // 파일에 데이터 쓰기
    content := []byte("Hello, Go I/O and Filesystem!")
    err := ioutil.WriteFile("example.txt", content, 0644)
    if err != nil {
        fmt.Println("Error writing file:", err)
        return
    }
    fmt.Println("File written successfully!")

    // 파일 전체 읽기
    data, err := ioutil.ReadFile("example.txt")
    if err != nil {
        fmt.Println("Error reading file:", err)
        return
    }
    fmt.Println("File content:", string(data))

    // 버퍼를 이용한 라인 단위 읽기
    file, err := os.Open("example.txt")
    if err != nil {
        fmt.Println("Error opening file:", err)
        return
    }
    defer file.Close()

    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        fmt.Println("Line:", scanner.Text())
    }
    if err := scanner.Err(); err != nil {
        fmt.Println("Error scanning file:", err)
    }
}
```

---

## Best Practices & Tips 💡

- **리소스 관리**:  
  - 파일을 열었으면 `defer file.Close()`를 사용해 리소스를 안전하게 반환하세요.
  
- **버퍼링 I/O 활용**:  
  - `bufio` 패키지를 사용하여 대용량 파일 처리 시 I/O 성능을 개선하세요.
  
- **에러 체크**:  
  - 각 I/O 작업 후 발생할 수 있는 에러를 꼼꼼히 체크하여, 문제를 신속하게 해결하세요.
  
- **경로 관리**:  
  - 파일 경로를 다룰 때는 `filepath` 패키지를 사용해 OS에 독립적인 코드를 작성하세요.
  
- **프로파일링**:  
  - I/O 작업이 병목이 될 경우, Go의 프로파일링 도구를 활용해 문제 지점을 찾으세요.
  
- **고급 파일 조작**:  
  - 파일 잠금, 임시 파일 생성, 파일 권한 관리, 심볼릭 링크 처리 등 고급 기능을 적용하여 안정적인 I/O 작업을 구현하세요.
  
- **동시성 및 네트워크 I/O**:  
  - 동시 파일 작업, 병렬 다운로드 및 HTTP 파일 서버를 활용한 네트워크 기반 I/O 작업을 구현하여 확장성을 높이세요.

---

## Next Steps

- 기본 I/O 작업에 익숙해진 후, **동시 I/O**, **네트워크 I/O** 및 **고급 파일 조작** 주제로 확장해보세요.
- 실무 프로젝트에 I/O 및 파일 시스템 작업을 통합하여, 로그 관리, 설정 파일 처리, 데이터 파이프라인 구축 등 다양한 응용 사례를 구현해 보세요.

Happy File I/O Coding! 📂✨