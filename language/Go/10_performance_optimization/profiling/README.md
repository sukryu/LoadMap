# Profiling in Go: Performance Analysis & Optimization ⚡️

이 디렉토리는 Go 애플리케이션의 성능을 분석하고 최적화하기 위한 프로파일링 기법을 다룹니다.  
CPU, 메모리, I/O 등 다양한 측면에서 애플리케이션의 병목 지점을 찾아내고, 개선 방법을 적용하여 애플리케이션의 효율성을 높이는 방법을 학습할 수 있습니다.

---

## What You'll Learn 🎯

- **프로파일링 기본 개념**  
  - 프로파일링의 목적, 주요 지표 및 측정 단위 이해
- **Go 프로파일링 도구**  
  - `pprof`, `go tool trace` 등의 내장 도구 사용법
  - CPU, 메모리, goroutine, 블로킹 I/O 프로파일링 기법
- **프로파일링 실행 및 분석**  
  - 프로파일 데이터를 수집하고, 시각화하며, 병목 현상을 파악하는 방법
- **최적화 전략**  
  - 프로파일링 결과를 바탕으로 코드 및 인프라 최적화 방법 적용
- **실무 적용 사례 및 Best Practices**  
  - 지속적인 모니터링과 프로파일링을 통한 성능 개선 및 최적화 전략

---

## Directory Structure 📁

```plaintext
10-performance-optimization/
└── profiling/
    ├── main.go         # 프로파일링 데이터 수집 및 분석 예제 코드
    ├── examples/       # CPU, 메모리, goroutine, I/O 프로파일링 고급 예제
    └── README.md       # 이 문서
```

- **main.go**: 간단한 프로파일링 예제를 통해 CPU 및 메모리 사용량을 측정하는 기본 코드가 포함되어 있습니다.
- **examples/**: 다양한 프로파일링 기법과 분석 도구 사용법을 실습할 수 있는 예제 코드들이 포함되어 있습니다.

---

## Getting Started 🚀

### 1. Prerequisites
- 최신 Go 버전 설치: [Download Go](https://go.dev/dl/)
- 기본 Go 애플리케이션 개발 경험
- `pprof` 및 `go tool trace` 사용 경험이 있으면 더욱 좋습니다

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/10-performance-optimization/profiling
```

### 3. 예제 코드 실행
```bash
go run main.go
```
- 실행 후, 브라우저에서 `http://localhost:6060/debug/pprof/` URL로 접속하여 프로파일링 데이터를 확인할 수 있습니다.

---

## Example Code Snippet 📄

아래는 간단한 CPU 프로파일링 예제입니다:

```go
package main

import (
    "log"
    "os"
    "runtime/pprof"
    "time"
)

func intensiveTask() {
    sum := 0
    for i := 0; i < 1e7; i++ {
        sum += i
    }
}

func main() {
    // CPU 프로파일링 파일 생성
    f, err := os.Create("cpu.prof")
    if err != nil {
        log.Fatal("프로파일 파일 생성 실패: ", err)
    }
    defer f.Close()

    // CPU 프로파일링 시작
    if err := pprof.StartCPUProfile(f); err != nil {
        log.Fatal("CPU 프로파일링 시작 실패: ", err)
    }
    defer pprof.StopCPUProfile()

    // 작업 실행
    for i := 0; i < 10; i++ {
        intensiveTask()
        time.Sleep(100 * time.Millisecond)
    }
    log.Println("CPU 프로파일링 완료! 'cpu.prof' 파일을 확인하세요.")
}
```

이 예제는 CPU 프로파일링을 활성화하여, `intensiveTask` 함수를 반복 실행하면서 성능 데이터를 수집합니다. 생성된 `cpu.prof` 파일은 `go tool pprof`를 통해 분석할 수 있습니다.

---

## Best Practices & Tips 💡

- **정기적인 프로파일링**:  
  - 개발 및 운영 단계에서 정기적으로 프로파일링을 수행하여, 성능 병목 및 리소스 낭비를 사전에 파악하세요.
  
- **적절한 프로파일링 범위 설정**:  
  - CPU, 메모리, goroutine, 블로킹 I/O 등 각 영역별 프로파일링을 별도로 수행해, 문제의 원인을 명확하게 파악하세요.
  
- **프로파일링 도구 활용**:  
  - `go tool pprof` 및 `go tool trace`를 활용하여, 시각화된 그래프와 통계 데이터를 분석하세요.
  
- **성능 최적화 적용**:  
  - 프로파일링 결과를 바탕으로, 코드 최적화, 캐싱, 병렬 처리 개선 등 구체적인 최적화 전략을 수립하세요.
  
- **모니터링과 통합**:  
  - 프로파일링 데이터를 지속적으로 모니터링하고, 성능 개선이 실제 서비스에 미치는 영향을 평가하세요.

---

## Next Steps

- **메모리 및 Goroutine 프로파일링**:  
  - 메모리 누수 및 고루틴 사용량 분석을 위한 추가 예제와 기법을 학습해 보세요.
  
- **실제 서비스 적용**:  
  - 실무 프로젝트에 프로파일링 도구를 통합하여, 운영 중인 서비스의 성능을 지속적으로 모니터링하고 개선하세요.
  
- **자동화**:  
  - CI/CD 파이프라인에 프로파일링 테스트를 추가하여, 성능 회귀를 예방하세요.

---

## References 📚

- [Go Profiling with pprof](https://blog.golang.org/pprof)
- [Go Trace Documentation](https://pkg.go.dev/runtime/trace)
- [Effective Go: Performance](https://golang.org/doc/effective_go.html#performance)
- [Prometheus Go Client](https://github.com/prometheus/client_golang) (추가 모니터링 도구로 활용 가능)

---

효율적인 프로파일링은 애플리케이션 성능 최적화와 안정적인 운영의 핵심입니다.  
이 자료를 통해 Go 애플리케이션의 병목 현상을 파악하고, 구체적인 최적화 전략을 수립해 보세요! Happy Profiling! ⚡️🚀