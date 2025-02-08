# 23. Go 에러 처리와 로깅, 디버깅

## 1. `errors` 패키지

### 1.1 기본 에러 생성과 처리
```go
err := errors.New("something went wrong")
err := fmt.Errorf("failed to read file %s", name)
err := fmt.Errorf("failed to process: %w", originalErr)
if err != nil {
    return fmt.Errorf("operation failed: %v", err)
}
```

### 1.2 커스텀 에러 타입
```go
type ValidationError struct {
    Field   string
    Message string
}
func (e *ValidationError) Error() string {
    return fmt.Sprintf("validation failed on %s: %s", e.Field, e.Message)
}
```

### 1.3 에러 체인
```go
type QueryError struct {
    Query string
    Err   error
}
func (e *QueryError) Error() string {
    return fmt.Sprintf("query error for %q: %v", e.Query, e.Err)
}
```

---

## 2. `log` 패키지

### 2.1 기본 로깅
```go
log.Println("Starting application...")
log.Printf("Processing item: %v", item)
```

### 2.2 커스텀 로거
```go
func initLogger() *log.Logger {
    f, err := os.OpenFile("app.log", os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
    if err != nil {
        log.Fatal(err)
    }
    return log.New(f, "APP: ", log.Ldate|log.Ltime|log.Lshortfile)
}
```

---

## 3. `runtime/pprof`

### 3.1 CPU 프로파일링
```go
func CPUProfile() {
    f, err := os.Create("cpu.pprof")
    if err != nil {
        log.Fatal(err)
    }
    defer f.Close()
    pprof.StartCPUProfile(f)
    defer pprof.StopCPUProfile()
}
```

### 3.2 메모리 프로파일링
```go
func MemoryProfile() {
    f, err := os.Create("memory.pprof")
    if err != nil {
        log.Fatal(err)
    }
    defer f.Close()
    runtime.GC()
    pprof.WriteHeapProfile(f)
}
```

---

## 4. 실용적인 에러 처리 패턴

### 4.1 에러 핸들러
```go
type ErrorHandler struct {
    handlers map[error]func(error) error
}
func (eh *ErrorHandler) Handle(err error) error {
    for e, handler := range eh.handlers {
        if errors.Is(err, e) {
            return handler(err)
        }
    }
    return err
}
```

### 4.2 재시도 메커니즘
```go
func Retry(attempts int, sleep time.Duration, f func() error) error {
    var err error
    for i := 0; i < attempts; i++ {
        err = f()
        if err == nil {
            return nil
        }
        time.Sleep(sleep * time.Duration(i+1))
    }
    return fmt.Errorf("after %d attempts, last error: %v", attempts, err)
}
```

---

## 5. 디버깅 도구

### 5.1 런타임 디버깅
```go
func dumpGoroutines() {
    buf := make([]byte, 1<<20)
    buf = buf[:runtime.Stack(buf, true)]
    fmt.Printf("=== goroutine dump:\n%s\n", buf)
}
```

### 5.2 트레이스 도구
```go
func Trace() func() {
    start := time.Now()
    return func() {
        fmt.Printf("exit: %s (%s)\n", functionName(1), time.Since(start))
    }
}
```

---

## 6. Best Practices

### 6.1 에러 처리
- 의미 있는 에러 메시지 작성
- 에러 컨텍스트 포함
- 에러 타입 계층 구조 설계

### 6.2 로깅
- 로그 레벨 적절히 사용
- 구조화된 로깅 활용
- 로그 순환(rotation) 구현

### 6.3 디버깅
- 프로파일링 도구 활용
- 디버그 로그 추가
- 테스트 커버리지 확인

---

## 7. 주의사항
- 에러 무시하지 않기
- 에러 메시지에 민감한 정보 포함 금지
- panic/recover 적절히 사용
- 로그 레벨 적절히 선택
- 디스크 공간 관리

---

Go의 에러 처리, 로깅, 디버깅 기능을 활용하여 신뢰성 높은 애플리케이션을 개발할 수 있습니다! 🚀

