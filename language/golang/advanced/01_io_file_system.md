# 15. Go 입출력과 파일 시스템 (I/O and File System)

## 1. `fmt` 패키지 (표준 입출력)

### 1.1 기본 출력 함수
```go
fmt.Print("Hello")      // 줄바꿈 없음
fmt.Println("Hello")    // 줄바꿈 포함
fmt.Printf("숫자: %d\n", 42)  // 형식화된 출력
```

### 1.2 형식 지정자
```go
fmt.Printf("%v", value)  // 기본 형식
fmt.Printf("%T", value)  // 타입 정보
fmt.Printf("%f", 3.14)   // 부동소수점
```

### 1.3 입력 함수
```go
var name string
fmt.Scan(&name)
fmt.Scanln(&name)
fmt.Scanf("%s %d", &name, &age)
```

---

## 2. `os` 패키지 (파일 및 프로세스 관리)

### 2.1 파일 조작
```go
file, err := os.Open("input.txt")
defer file.Close()
file, err := os.Create("output.txt")
defer file.Close()
file, err := os.OpenFile("data.txt", os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
```

### 2.2 디렉토리 조작
```go
err := os.Mkdir("newdir", 0755)
os.MkdirAll("path/to/newdir", 0755)
dir, err := os.ReadDir(".")
```

### 2.3 환경 변수 및 프로세스 정보
```go
os.Setenv("MY_VAR", "value")
value := os.Getenv("MY_VAR")
pid := os.Getpid()
dir, err := os.Getwd()
```

---

## 3. `io` 패키지와 버퍼 I/O

### 3.1 `io.Reader`와 `io.Writer`
```go
type Reader interface {
    Read(p []byte) (n int, err error)
}

type Writer interface {
    Write(p []byte) (n int, err error)
}
```

### 3.2 파일 복사 예제
```go
func copyFile(src, dst string) error {
    sourceFile, err := os.Open(src)
    defer sourceFile.Close()
    destFile, err := os.Create(dst)
    defer destFile.Close()
    _, err = io.Copy(destFile, sourceFile)
    return err
}
```

### 3.3 `bufio`를 활용한 입출력 최적화
```go
reader := bufio.NewReader(file)
line, err := reader.ReadString('\n')

scanner := bufio.NewScanner(file)
for scanner.Scan() {
    fmt.Println(scanner.Text())
}

writer := bufio.NewWriter(file)
writer.WriteString("Hello, World!\n")
writer.Flush()
```

---

## 4. `filepath` 패키지 (경로 조작)

### 4.1 경로 결합 및 분할
```go
path := filepath.Join("dir", "subdir", "file.txt")
dir, file := filepath.Split("/path/to/file.txt")
ext := filepath.Ext("file.txt")
absPath, err := filepath.Abs("relative/path")
```

### 4.2 디렉토리 탐색 및 패턴 매칭
```go
err := filepath.Walk(".", func(path string, info os.FileInfo, err error) error {
    fmt.Println("방문:", path)
    return nil
})

matches, err := filepath.Glob("*.txt")
```

---

## 5. 실용적인 예제

### 5.1 파일 유틸리티
```go
func readFileContent(filename string) (string, error) {
    content, err := os.ReadFile(filename)
    return string(content), err
}

func writeFileContent(filename, content string) error {
    return os.WriteFile(filename, []byte(content), 0644)
}

func fileExists(filename string) bool {
    _, err := os.Stat(filename)
    return !os.IsNotExist(err)
}
```

### 5.2 대용량 파일 처리
```go
func processLargeFile(filename string) error {
    file, err := os.Open(filename)
    defer file.Close()
    reader := bufio.NewReader(file)
    buffer := make([]byte, 4096)
    for {
        n, err := reader.Read(buffer)
        if err == io.EOF {
            break
        }
        process(buffer[:n])
    }
    return nil
}
```

---

## 6. Best Practices (모범 사례)

### 6.1 파일 처리
- 항상 `defer file.Close()` 호출
- 큰 파일은 `bufio`를 사용하여 읽기/쓰기
- 에러 처리를 철저히 수행

### 6.2 경로 처리
- `filepath` 패키지를 사용하여 OS 독립적인 코드 작성
- 상대 경로보다 절대 경로를 선호

### 6.3 입출력 최적화
- 적절한 버퍼 크기 선택 (`bufio` 활용)
- `Scanner` 사용 시 커스텀 버퍼 크기 설정 가능

### 6.4 에러 처리
- `os.IsNotExist(err)` 등을 활용하여 특정 에러를 확인
- `defer`를 활용하여 리소스 정리

---

## 7. 주의사항
- **파일 핸들 누수 방지** (`defer file.Close()` 활용)
- **권한 설정 (Permissions) 주의** (`0644`, `0755` 등)
- **크로스 플랫폼 호환성 고려** (`filepath` 패키지 사용)
- **동시성 처리 시 적절한 동기화 필요** (`sync.Mutex` 활용)

---

Go의 파일 시스템과 입출력 처리를 이해하고 활용하면, 더욱 안정적이고 최적화된 애플리케이션을 개발할 수 있습니다! 🚀

