# I/O & Filesystem in Go 📂

이 디렉토리는 Go 언어를 사용하여 파일 입출력 및 파일 시스템 작업을 수행하는 방법을 다룹니다.  
여기서는 파일 생성, 읽기, 쓰기, 디렉토리 관리와 같은 기본 I/O 작업부터, 버퍼링을 통한 성능 향상 및 에러 핸들링에 관한 모범 사례를 실무에 적용할 수 있도록 학습합니다.

---

## What You'll Learn 🎯

- **파일 입출력 기본**:  
  - Go의 `os`, `io`, `ioutil` 패키지를 사용하여 파일 생성, 읽기, 쓰기 작업 수행
- **버퍼링 I/O**:  
  - `bufio`를 사용해 버퍼링된 입출력으로 대용량 데이터 처리 성능 향상
- **디렉토리 및 파일 시스템 관리**:  
  - 디렉토리 생성, 탐색, 파일 및 디렉토리 메타데이터 처리
- **에러 핸들링 및 리소스 관리**:  
  - `defer`를 활용해 파일 핸들러를 안전하게 닫고, 에러 발생 시 적절히 대응하는 방법

---

## 디렉토리 구조 📁

```plaintext
01-go-basics/
└── io-filesystem/
    ├── main.go        # 기본 I/O 예제 코드
    ├── examples/      # 추가 실습 예제 및 패턴 코드
    └── README.md      # 이 문서
```

- **main.go**: 파일 입출력 및 디렉토리 작업의 기본 예제를 포함합니다.
- **examples/**: 다양한 I/O 작업 예제 및 고급 활용 패턴을 실습할 수 있는 코드들이 모여 있습니다.

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
- 실행 결과를 통해 파일 입출력 작업이 어떻게 이루어지는지 확인하세요.

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

---

## Next Steps

- 기본 I/O 작업에 익숙해진 후, **동시 I/O** 및 **네트워크 I/O**와 같은 고급 주제로 확장해보세요.
- 실무 프로젝트에 I/O 및 파일 시스템 작업을 통합하여, 로그 관리, 설정 파일 처리, 데이터 파이프라인 구축 등 다양한 응용 사례를 구현해 보세요.

Happy File I/O Coding! 📂✨