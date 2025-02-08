# 20. Go 동시성 프로그래밍 (Concurrency)

## 1. `sync` 패키지

### 1.1 Mutex
```go
type Counter struct {
    mu    sync.Mutex
    count int
}

func (c *Counter) Increment() {
    c.mu.Lock()
    defer c.mu.Unlock()
    c.count++
}
```

### 1.2 RWMutex
```go
type Cache struct {
    mu    sync.RWMutex
    items map[string]string
}

func (c *Cache) Get(key string) (string, bool) {
    c.mu.RLock()
    defer c.mu.RUnlock()
    item, exists := c.items[key]
    return item, exists
}
```

### 1.3 WaitGroup
```go
func ProcessItems(items []int) {
    var wg sync.WaitGroup
    for _, item := range items {
        wg.Add(1)
        go func(item int) {
            defer wg.Done()
            processItem(item)
        }(item)
    }
    wg.Wait()
}
```

### 1.4 Once
```go
var instance *Singleton
var once sync.Once

func GetInstance() *Singleton {
    once.Do(func() {
        instance = &Singleton{data: "initialized"}
    })
    return instance
}
```

### 1.5 Cond
```go
type Queue struct {
    cond *sync.Cond
    data []interface{}
}

func (q *Queue) Put(item interface{}) {
    q.cond.L.Lock()
    defer q.cond.L.Unlock()
    q.data = append(q.data, item)
    q.cond.Signal()
}
```

---

## 2. `sync/atomic` 패키지

### 2.1 기본 원자성 연산
```go
type AtomicCounter struct {
    count int64
}

func (c *AtomicCounter) Increment() {
    atomic.AddInt64(&c.count, 1)
}
```

### 2.2 CompareAndSwap
```go
type AtomicFlag struct {
    flag int32
}

func (f *AtomicFlag) Set() bool {
    return atomic.CompareAndSwapInt32(&f.flag, 0, 1)
}
```

---

## 3. `context` 패키지

### 3.1 타임아웃 컨텍스트
```go
func worker(ctx context.Context) {
    for {
        select {
        case <-ctx.Done():
            return
        default:
            time.Sleep(time.Second)
        }
    }
}
```

### 3.2 값 전달
```go
func ProcessRequest(ctx context.Context) {
    user := ctx.Value("user").(string)
    fmt.Printf("Processing user: %s\n", user)
}
```

---

## 4. `runtime` 패키지

### 4.1 고루틴 관리
```go
func monitorGoroutines() {
    go func() {
        for range time.Tick(time.Second) {
            fmt.Printf("Active goroutines: %d\n", runtime.NumGoroutine())
        }
    }()
}
```

---

## 5. 실용적인 패턴

### 5.1 작업자 풀
```go
type WorkerPool struct {
    workers int
    tasks   chan func()
}

func (p *WorkerPool) Start() {
    for i := 0; i < p.workers; i++ {
        go func() {
            for task := range p.tasks {
                task()
            }
        }()
    }
}
```

### 5.2 세마포어 패턴
```go
type Semaphore struct {
    sem chan struct{}
}

func (s *Semaphore) Acquire() {
    s.sem <- struct{}{}
}
```

---

## 6. 동시성 패턴

### 6.1 파이프라인 패턴
```go
func generator(nums ...int) <-chan int {
    out := make(chan int)
    go func() {
        defer close(out)
        for _, n := range nums {
            out <- n
        }
    }()
    return out
}
```

### 6.2 Fan-out, Fan-in 패턴
```go
func fanOut(ch <-chan int, n int) []<-chan int {
    channels := make([]<-chan int, n)
    for i := 0; i < n; i++ {
        channels[i] = processChannel(ch)
    }
    return channels
}
```

---

## 7. Best Practices

### 7.1 동시성 관리
- 적절한 수의 고루틴 사용
- 컨텍스트를 통한 취소 처리

### 7.2 에러 처리
- 고루틴 내 에러 수집
- 우아한 종료

### 7.3 성능 최적화
- 적절한 버퍼 크기
- 컨텍스트 타임아웃 설정

---

## 8. 주의사항
- 데드락 방지
- 고루틴 누수 관리
- 공유 메모리 접근 동기화
- 채널 닫기 규칙 준수

---

Go의 동시성 프로그래밍을 활용하면 효율적인 병렬 처리를 구현할 수 있습니다! 🚀

