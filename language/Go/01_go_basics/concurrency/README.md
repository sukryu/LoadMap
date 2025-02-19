# Concurrency in Go 🚀

이 디렉토리는 Go 언어의 **동시성(concurrency)** 기능을 심도 있게 학습할 수 있도록 구성되었습니다.  
Go의 고루틴, 채널, 그리고 동기화 도구들을 활용하여 안전하고 효율적인 동시성 코드를 작성하는 방법을 배우고, 실무에서 병목 현상이나 데이터 경쟁을 방지하는 전략을 익힙니다.

---

## What You'll Learn 🎯

- **고루틴**:  
  - Go의 경량 스레드인 고루틴을 생성하고 관리하는 방법
  - 동시 실행의 개념과 실무 적용 방법

- **채널**:  
  - 고루틴 간 통신을 위한 채널의 사용법
  - 방향성 채널, 버퍼 채널 및 select 문을 통한 멀티 채널 동작

- **동기화 및 동시성 제어**:  
  - `sync` 패키지를 통한 뮤텍스, WaitGroup, Once, Cond 등의 활용
  - 데이터 경쟁(Race Condition) 예방 및 안전한 공유 변수 사용

- **동시성 디자인 패턴**:  
  - 파이프라인, 워커 풀, fan-out/fan-in 등 동시성 프로그래밍 패턴

---

## 디렉토리 구조 📁

```plaintext
01-go-basics/
└── concurrency/
    ├── main.go        # 기본 동시성 예제 코드 (고루틴, 채널, sync 등)
    ├── examples/      # 추가 실습 예제 및 패턴 코드
    └── README.md      # 이 문서
```

- **main.go**: Go의 동시성 기능을 직접 실습할 수 있는 샘플 코드가 포함되어 있습니다.
- **examples/**: 다양한 동시성 패턴 및 도구를 적용한 추가 연습 예제들을 제공합니다.

---

## Getting Started 🚀

### 1. 필수 도구 설치
- Go 최신 버전: [Download Go](https://go.dev/dl/)

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/01-go-basics/concurrency
```

### 3. 예제 코드 실행
```bash
go run main.go
```
- 실행 결과를 확인하면서, 고루틴과 채널의 동작 방식을 직접 체험해 보세요.

---

## Example Code Snippet 📄

아래는 간단한 동시성 예제입니다:
```go
package main

import (
    "fmt"
    "sync"
    "time"
)

func worker(id int, wg *sync.WaitGroup, jobs <-chan int, results chan<- int) {
    defer wg.Done()
    for j := range jobs {
        fmt.Printf("Worker %d processing job %d\n", id, j)
        time.Sleep(time.Millisecond * 100) // 작업 처리 시간 시뮬레이션
        results <- j * 2
    }
}

func main() {
    const numJobs = 10
    jobs := make(chan int, numJobs)
    results := make(chan int, numJobs)
    var wg sync.WaitGroup

    // 3개의 워커 고루틴 실행
    for w := 1; w <= 3; w++ {
        wg.Add(1)
        go worker(w, &wg, jobs, results)
    }

    // 작업 생성
    for j := 1; j <= numJobs; j++ {
        jobs <- j
    }
    close(jobs)

    // 모든 워커가 종료될 때까지 대기
    wg.Wait()
    close(results)

    // 결과 출력
    for res := range results {
        fmt.Println("Result:", res)
    }
}
```
이 예제는 3개의 워커가 채널을 통해 작업을 처리하고, 결과를 반환하는 간단한 동시성 패턴을 보여줍니다.

---

## Best Practices & Tips 💡

- **데이터 경쟁 방지**:  
  - 공유 자원에 접근할 때는 뮤텍스나 기타 동기화 도구를 활용하여 데이터 경쟁을 피하세요.
  
- **채널 활용**:  
  - 채널은 고루틴 간의 안전한 통신을 보장하므로, 데이터를 전달할 때 적극 활용하세요.
  - `select` 문을 사용하여 여러 채널을 동시에 감시하고, 타임아웃 및 기본 동작을 설정하세요.

- **고루틴 관리**:  
  - 너무 많은 고루틴을 생성하면 메모리 사용량이 증가할 수 있으므로, 워커 풀과 같은 패턴으로 고루틴을 효율적으로 관리하세요.
  
- **프로파일링**:  
  - Go의 `go tool pprof`를 사용하여 동시성 코드의 성능을 주기적으로 분석하고 최적화하세요.

---

## Next Steps

- 기본 동시성 기능을 충분히 익힌 후, 더 복잡한 패턴(예: 파이프라인, fan-out/fan-in)을 추가 실습해 보세요.
- 실무 프로젝트에 동시성 패턴을 적용하여, 데이터 경쟁 및 성능 문제를 해결하는 경험을 쌓으세요.

Happy Concurrent Coding! 🎉