# 13. Go 동시성 패턴과 실제 사례 (Concurrency Patterns and Examples)

## 1. 동시성 패턴이란?
Go는 **고루틴(Goroutines)**과 **채널(Channels)**을 활용하여 동시성을 구현합니다. Go에서는 다양한 동시성 패턴을 적용할 수 있으며, 이를 통해 **성능 최적화와 안정적인 데이터 처리**를 보장할 수 있습니다.

---

## 2. 기본적인 고루틴 패턴

### 2.1 고루틴을 활용한 비동기 실행
```go
package main
import (
    "fmt"
    "time"
)

func sayHello() {
    fmt.Println("Hello from Goroutine!")
}

func main() {
    go sayHello() // 고루틴 실행
    time.Sleep(time.Second) // 메인 함수가 종료되지 않도록 대기
}
```

> `go` 키워드를 사용하여 함수를 비동기로 실행할 수 있습니다.

---

## 3. 채널을 활용한 동시성 패턴

### 3.1 기본 채널 패턴
```go
package main
import "fmt"

func sendMessage(ch chan string) {
    ch <- "Hello, Channel!"
}

func main() {
    ch := make(chan string)
    go sendMessage(ch)
    message := <-ch // 채널에서 데이터 수신
    fmt.Println(message)
}
```

> 채널을 사용하면 **고루틴 간 안전한 데이터 전달**이 가능합니다.

---

### 3.2 버퍼링된 채널을 활용한 비동기 처리
```go
package main
import "fmt"

func main() {
    ch := make(chan int, 3) // 버퍼 크기 3
    ch <- 1
    ch <- 2
    ch <- 3
    fmt.Println(<-ch)
    fmt.Println(<-ch)
    fmt.Println(<-ch)
}
```

> **버퍼링된 채널**을 사용하면 고루틴이 블로킹되지 않고 데이터를 전송할 수 있습니다.

---

## 4. 워커 풀(Worker Pool) 패턴

### 4.1 워커 풀을 활용한 작업 분배
```go
package main
import (
    "fmt"
    "sync"
    "time"
)

func worker(id int, jobs <-chan int, results chan<- int, wg *sync.WaitGroup) {
    defer wg.Done()
    for job := range jobs {
        fmt.Printf("Worker %d processing job %d\n", id, job)
        time.Sleep(time.Second) // 작업 수행 시뮬레이션
        results <- job * 2
    }
}

func main() {
    var wg sync.WaitGroup
    jobs := make(chan int, 5)
    results := make(chan int, 5)

    // 3명의 워커 실행
    for i := 1; i <= 3; i++ {
        wg.Add(1)
        go worker(i, jobs, results, &wg)
    }

    // 작업 전송
    for j := 1; j <= 5; j++ {
        jobs <- j
    }
    close(jobs)

    wg.Wait()
    close(results)
    
    // 결과 출력
    for result := range results {
        fmt.Println("Result:", result)
    }
}
```

> **워커 풀 패턴**은 다수의 작업을 여러 개의 고루틴으로 분산 실행하는 데 효과적입니다.

---

## 5. Fan-out, Fan-in 패턴

### 5.1 Fan-out: 여러 고루틴이 데이터를 동시에 처리
```go
package main
import (
    "fmt"
    "sync"
)

func worker(id int, jobs <-chan int, wg *sync.WaitGroup) {
    defer wg.Done()
    for job := range jobs {
        fmt.Printf("Worker %d processing job %d\n", id, job)
    }
}

func main() {
    jobs := make(chan int, 10)
    var wg sync.WaitGroup
    
    // 여러 개의 워커 실행 (Fan-out)
    for i := 1; i <= 3; i++ {
        wg.Add(1)
        go worker(i, jobs, &wg)
    }

    // 작업 추가
    for j := 1; j <= 5; j++ {
        jobs <- j
    }
    close(jobs)
    wg.Wait()
}
```

> **Fan-out** 패턴은 여러 개의 고루틴이 동시에 작업을 처리하도록 만듭니다.

---

### 5.2 Fan-in: 여러 채널의 데이터를 단일 채널로 모으기
```go
package main
import (
    "fmt"
)

func mergeChannels(channels ...<-chan int) <-chan int {
    merged := make(chan int)
    go func() {
        for _, ch := range channels {
            for value := range ch {
                merged <- value
            }
        }
        close(merged)
    }()
    return merged
}

func sendNumbers(ch chan int, start, end int) {
    for i := start; i <= end; i++ {
        ch <- i
    }
    close(ch)
}

func main() {
    ch1 := make(chan int)
    ch2 := make(chan int)
    go sendNumbers(ch1, 1, 5)
    go sendNumbers(ch2, 6, 10)

    merged := mergeChannels(ch1, ch2)
    for value := range merged {
        fmt.Println(value)
    }
}
```

> **Fan-in** 패턴은 여러 개의 고루틴에서 전달되는 데이터를 하나의 채널로 합칩니다.

---

## 6. Context를 활용한 고루틴 관리

Go의 `context` 패키지는 **고루틴을 취소하거나 제한 시간을 설정할 때 유용**합니다.

### 6.1 `context.WithTimeout`을 활용한 실행 제한
```go
package main
import (
    "context"
    "fmt"
    "time"
)

func worker(ctx context.Context) {
    for {
        select {
        case <-ctx.Done():
            fmt.Println("Worker shutting down")
            return
        default:
            fmt.Println("Working...")
            time.Sleep(500 * time.Millisecond)
        }
    }
}

func main() {
    ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)
    defer cancel()
    
    go worker(ctx)
    time.Sleep(3 * time.Second) // 3초 후 종료 확인
}
```

> `context.WithTimeout`을 사용하면 일정 시간이 지나면 자동으로 고루틴을 종료할 수 있습니다.

---

## 7. 결론
- **고루틴과 채널을 활용하여 다양한 동시성 패턴을 구현할 수 있음.**
- **워커 풀, Fan-out/Fan-in, Context 활용 등의 패턴을 적용하면 더 안정적인 동시성 처리가 가능함.**
- **Go의 동시성 모델을 잘 활용하면 성능과 효율성이 극대화됨.**

이제 다음으로 **최신 기능과 고급 활용(Advanced Go Features)**을 다루겠습니다!

