# 06. Go 동시성 프로그래밍 (Goroutines and Channels)

## 1. 동시성과 병렬성

### 동시성이란?
- 여러 작업이 **논리적으로 동시에 실행되는 것**을 의미합니다.
- 단일 코어에서도 스케줄링을 통해 여러 작업이 번갈아 가며 실행될 수 있습니다.

### 병렬성이란?
- 여러 작업이 **물리적으로 동시에 실행되는 것**을 의미합니다.
- 멀티코어 프로세서에서 여러 작업이 실제로 동시에 실행됩니다.

Go는 동시성을 지원하며, 고루틴과 채널을 활용하여 간결하고 효율적인 동시성 프로그래밍이 가능합니다.

---

## 2. 고루틴 (Goroutines)

### 고루틴이란?
- Go에서 제공하는 **경량 스레드**입니다.
- `go` 키워드를 사용하여 함수를 병렬로 실행할 수 있습니다.
- 운영체제 스레드보다 가볍고, 수천 개 이상의 고루틴을 실행할 수 있습니다.

### 기본적인 고루틴 사용법
```go
package main
import (
    "fmt"
    "time"
)

func sayHello() {
    fmt.Println("Hello, Goroutine!")
}

func main() {
    go sayHello()
    time.Sleep(time.Second) // 고루틴이 실행될 시간을 확보
}
```

> `go sayHello()`를 사용하면 `sayHello` 함수가 새로운 고루틴에서 실행됩니다.
> `time.Sleep(time.Second)`는 고루틴이 실행될 시간을 확보하기 위해 사용됩니다.

### 익명 함수를 활용한 고루틴 실행
```go
package main
import (
    "fmt"
    "time"
)

func main() {
    go func() {
        fmt.Println("Hello from anonymous Goroutine!")
    }()
    time.Sleep(time.Second)
}
```

---

## 3. 채널 (Channels)

### 채널이란?
- 고루틴 간의 **데이터 교환을 위한 통신 수단**입니다.
- `make(chan 타입)`을 사용하여 생성할 수 있습니다.
- `chan <-` 연산자를 사용하여 데이터를 전송하고, `<- chan`을 사용하여 데이터를 수신합니다.

### 기본적인 채널 사용법
```go
package main
import "fmt"

func main() {
    ch := make(chan string)
    go func() {
        ch <- "Hello, Channel!" // 채널에 데이터 전송
    }()
    msg := <-ch // 채널에서 데이터 수신
    fmt.Println(msg)
}
```

> `ch <- "Hello, Channel!"`으로 데이터를 채널에 보내고, `<-ch`를 통해 데이터를 수신합니다.

### 채널의 버퍼링
- 기본적으로 채널은 **언버퍼드(Buffered)** 상태이며, 송신과 수신이 동기적으로 일어납니다.
- 버퍼 크기를 지정하면 비동기적인 송신이 가능해집니다.

```go
package main
import "fmt"

func main() {
    ch := make(chan int, 2) // 버퍼 크기 2
    ch <- 1
    ch <- 2
    fmt.Println(<-ch)
    fmt.Println(<-ch)
}
```

> 버퍼 크기 `2`를 지정하여 두 개의 데이터를 비동기적으로 보낼 수 있습니다.

---

## 4. Select 문을 활용한 다중 채널 처리

### Select 문이란?
- 여러 개의 채널을 감시하여, **데이터가 준비된 채널을 먼저 실행**하는 기능을 합니다.

#### 예제: 여러 채널에서 데이터 수신하기
```go
package main
import (
    "fmt"
    "time"
)

func main() {
    ch1 := make(chan string)
    ch2 := make(chan string)

    go func() {
        time.Sleep(2 * time.Second)
        ch1 <- "Channel 1 Data"
    }()

    go func() {
        time.Sleep(1 * time.Second)
        ch2 <- "Channel 2 Data"
    }()

    select {
    case msg1 := <-ch1:
        fmt.Println("Received:", msg1)
    case msg2 := <-ch2:
        fmt.Println("Received:", msg2)
    }
}
```

> `select` 문을 사용하면 먼저 준비된 채널의 데이터를 수신합니다.

---

## 5. 뮤텍스(Mutex)와 동기화

### 경쟁 상태(Race Condition)
- 두 개 이상의 고루틴이 동시에 공유된 자원을 수정하려고 할 때 발생하는 문제입니다.
- 해결하지 않으면 **데이터 불일치, 충돌, 예측 불가능한 동작**이 발생할 수 있습니다.

### `sync.Mutex`를 활용한 동기화
```go
package main
import (
    "fmt"
    "sync"
)

var (
    count int
    mu    sync.Mutex
)

func increment(wg *sync.WaitGroup) {
    mu.Lock()
    count++
    mu.Unlock()
    wg.Done()
}

func main() {
    var wg sync.WaitGroup
    for i := 0; i < 10; i++ {
        wg.Add(1)
        go increment(&wg)
    }
    wg.Wait()
    fmt.Println("Final count:", count)
}
```

> `sync.Mutex`를 사용하여 **하나의 고루틴만 공유 자원(count)을 수정하도록 보장**합니다.

---

## 6. `sync.WaitGroup`을 활용한 고루틴 종료 대기

### `sync.WaitGroup`이란?
- 여러 개의 고루틴이 완료될 때까지 대기할 수 있도록 도와주는 동기화 도구입니다.

```go
package main
import (
    "fmt"
    "sync"
)

func worker(id int, wg *sync.WaitGroup) {
    defer wg.Done()
    fmt.Printf("Worker %d started\n", id)
}

func main() {
    var wg sync.WaitGroup
    for i := 1; i <= 3; i++ {
        wg.Add(1)
        go worker(i, &wg)
    }
    wg.Wait()
    fmt.Println("All workers completed")
}
```

> `wg.Add(1)`, `wg.Done()`, `wg.Wait()`을 사용하여 고루틴 종료를 기다릴 수 있습니다.

---

Go의 동시성 프로그래밍은 고루틴과 채널을 이용하여 효율적으로 처리할 수 있습니다. 다음으로 Go의 구조체와 메서드(Structs and Methods)에 대해 알아보겠습니다.

