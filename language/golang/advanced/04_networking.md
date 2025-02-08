# 18. Go 네트워킹 (Networking)

## 1. `net` 패키지

### 1.1 TCP 서버
```go
func TCPServer() error {
    listener, err := net.Listen("tcp", ":8080")
    if err != nil {
        return err
    }
    defer listener.Close()

    for {
        conn, err := listener.Accept()
        if err != nil {
            log.Printf("연결 수락 실패: %v", err)
            continue
        }
        go handleConnection(conn)
    }
}

func handleConnection(conn net.Conn) {
    defer conn.Close()
    buffer := make([]byte, 1024)
    for {
        n, err := conn.Read(buffer)
        if err != nil {
            return
        }
        conn.Write(buffer[:n]) // 에코 서버
    }
}
```

### 1.2 TCP 클라이언트
```go
func TCPClient() error {
    conn, err := net.Dial("tcp", "localhost:8080")
    if err != nil {
        return err
    }
    defer conn.Close()
    fmt.Fprintf(conn, "Hello, Server!")
    buffer := make([]byte, 1024)
    n, _ := conn.Read(buffer)
    fmt.Printf("서버 응답: %s\n", buffer[:n])
    return nil
}
```

### 1.3 UDP 통신
```go
func UDPServer() error {
    addr, _ := net.ResolveUDPAddr("udp", ":8081")
    conn, _ := net.ListenUDP("udp", addr)
    defer conn.Close()
    buffer := make([]byte, 1024)
    for {
        n, remoteAddr, _ := conn.ReadFromUDP(buffer)
        go conn.WriteToUDP(buffer[:n], remoteAddr)
    }
}

func UDPClient() error {
    conn, _ := net.Dial("udp", "localhost:8081")
    defer conn.Close()
    fmt.Fprintf(conn, "Hello, UDP Server!")
    return nil
}
```

---

## 2. `net/http` 패키지

### 2.1 HTTP 서버
```go
func BasicHTTPServer() {
    http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
        fmt.Fprintf(w, "Hello, HTTP!")
    })
    log.Fatal(http.ListenAndServe(":8080", nil))
}
```

### 2.2 HTTP 클라이언트
```go
func BasicGet() error {
    resp, _ := http.Get("http://example.com")
    defer resp.Body.Close()
    body, _ := io.ReadAll(resp.Body)
    fmt.Printf("응답: %s\n", body)
    return nil
}
```

### 2.3 JSON API 핸들러
```go
func apiHandler(w http.ResponseWriter, r *http.Request) {
    var data struct {
        Name string `json:"name"`
        Age  int    `json:"age"`
    }
    json.NewDecoder(r.Body).Decode(&data)
    json.NewEncoder(w).Encode(map[string]string{"status": "success"})
}
```

---

## 3. 웹소켓 (`gorilla/websocket` 사용)
```go
var upgrader = websocket.Upgrader{
    ReadBufferSize:  1024,
    WriteBufferSize: 1024,
}

func wsHandler(w http.ResponseWriter, r *http.Request) {
    conn, _ := upgrader.Upgrade(w, r, nil)
    defer conn.Close()
    for {
        msgType, msg, _ := conn.ReadMessage()
        conn.WriteMessage(msgType, msg)
    }
}
```

---

## 4. 보안 및 TLS

### 4.1 HTTPS 서버
```go
func HTTPSServer() {
    http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
        fmt.Fprintf(w, "Secure Hello!")
    })
    log.Fatal(http.ListenAndServeTLS(":443", "cert.pem", "key.pem", nil))
}
```

---

## 5. 실용적인 네트워크 예제

### 5.1 로드밸런서
```go
type LoadBalancer struct {
    backends []string
    current  int
    mu       sync.Mutex
}

func (lb *LoadBalancer) NextBackend() string {
    lb.mu.Lock()
    defer lb.mu.Unlock()
    backend := lb.backends[lb.current]
    lb.current = (lb.current + 1) % len(lb.backends)
    return backend
}
```

### 5.2 레이트 리미터
```go
type RateLimiter struct {
    tokens chan struct{}
}

func NewRateLimiter(limit int, interval time.Duration) *RateLimiter {
    rl := &RateLimiter{tokens: make(chan struct{}, limit)}
    go func() {
        ticker := time.NewTicker(interval / time.Duration(limit))
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
```

---

## 6. Best Practices

### 6.1 에러 처리
- **네트워크 작업에서 타임아웃 설정**
- **연결은 확실히 `Close()` 처리**
- **적절한 로깅과 모니터링 활용**

### 6.2 성능 최적화
- **연결 풀링 사용 (`http.Transport`)**
- **Keep-Alive 설정 활용**
- **적절한 버퍼 크기 설정 (`net.Buffers`)**

### 6.3 보안
- **HTTPS 사용 필수 (`TLS 설정`)**
- **CORS 설정 적용**
- **적절한 타임아웃 설정 (`http.Server.Timeout`)**

---

## 7. 주의사항
- **고루틴 누수 방지 (`defer Close() 활용`)**
- **타임아웃 및 재연결 로직 적용**
- **보안 검토 (TLS, CORS, 입력 검증 등)**
- **리소스 관리 (`연결 풀, 버퍼 크기 설정 등`)**

---

Go의 네트워크 기능을 활용하면 효율적이고 확장 가능한 서버 및 클라이언트를 개발할 수 있습니다! 🚀

