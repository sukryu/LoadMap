# Memory Management in Go 🧠

이 디렉토리는 **Go 언어의 메모리 관리**에 대해 학습하고 실무에 적용하는 방법을 다룹니다.  
Go의 메모리 할당, 가비지 컬렉션(GC), escape 분석, 그리고 메모리 최적화 기법을 통해 효율적이고 안정적인 애플리케이션을 구축할 수 있도록 돕습니다.

---

## What You'll Learn 🎯

- **메모리 할당 메커니즘**  
  - 스택과 힙의 차이, escape 분석을 통한 변수 할당 결정 방식
- **가비지 컬렉션(GC)**  
  - Go의 GC 동작 원리, GC 주기 및 튜닝 방법
- **메모리 최적화 기법**  
  - 메모리 누수 방지, 프로파일링 도구(pprof) 활용, 메모리 풀링, 슬라이스 최적화, 캐시 라인 정렬 및 구조체 정렬 최적화
- **실무 적용 사례**  
  - 메모리 사용량 모니터링, GC 튜닝, OOM(Out of Memory) 방지, 적응형 메모리 관리 전략 및 동적 리소스 관리 기법

---

## 디렉토리 구조 📁

```plaintext
01-go-basics/
└── memory-management/
    ├── main.go                  # 메모리 관리 관련 예제 코드
    ├── examples/                # 추가 실습 예제 및 튜닝 팁
    │   ├── 01_memory_profiling.go
    │   ├── 02_escape_analysis.go
    │   ├── 03_memory_pooling.go
    │   ├── 04_slice_opmitization.go
    │   ├── 05_gc_tuning.go
    │   ├── 06_memory_leaks.go
    │   ├── 07_struct_alignment.go
    │   └── 08_memory_bounds.go
    └── README.md                # 이 문서
```

- **main.go**: 기본 메모리 할당, escape 분석, GC 튜닝 등을 실습할 수 있는 예제 코드가 포함되어 있습니다.
- **examples/**: 메모리 프로파일링, escape 분석, 메모리 풀링, 슬라이스 최적화, GC 튜닝, 메모리 누수 방지, 구조체 정렬 최적화, 그리고 메모리 사용 한계 관리 등 다양한 최적화 기법과 문제 해결 사례를 담은 추가 예제들이 있습니다.

---

## Getting Started 🚀

### 1. 필수 도구 설치
- Go 최신 버전: [Download Go](https://go.dev/dl/)
- 메모리 프로파일링을 위해 `go tool pprof` 사용 (Go 내장)

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/01-go-basics/memory-management
```

### 3. 예제 코드 실행
```bash
go run main.go
```
- 실행 결과를 통해 메모리 할당 및 GC 동작을 확인하고, `pprof`를 사용해 프로파일링 데이터를 분석해 보세요.

---

## Example Code Snippet 📄

다음은 간단한 메모리 할당 및 GC 프로파일링 예제입니다:
```go
package main

import (
    "fmt"
    "os"
    "runtime"
    "runtime/pprof"
    "time"
)

func allocateMemory() {
    // 힙 메모리에 대량의 슬라이스 생성 (메모리 할당 예제)
    data := make([]byte, 100*1024*1024) // 100MB
    for i := range data {
        data[i] = byte(i % 256)
    }
    fmt.Println("메모리 할당 완료!")
}

func main() {
    // 메모리 프로파일링 시작
    f, err := os.Create("mem.prof")
    if err != nil {
        fmt.Println("프로파일링 파일 생성 실패:", err)
        return
    }
    defer f.Close()

    // 메모리 할당 함수 실행
    allocateMemory()

    // GC 강제 실행 및 프로파일 저장
    runtime.GC()
    if err := pprof.WriteHeapProfile(f); err != nil {
        fmt.Println("Heap 프로파일 쓰기 실패:", err)
    } else {
        fmt.Println("Heap 프로파일이 mem.prof에 저장되었습니다.")
    }

    // 잠시 대기 후 종료
    time.Sleep(2 * time.Second)
}
```
이 코드는 100MB 크기의 슬라이스를 할당하고, GC를 강제 실행한 후 메모리 프로파일을 저장하는 예제입니다.

---

## Best Practices & Tips 💡

- **Escape 분석 이해**:  
  - 컴파일러가 변수를 스택 또는 힙에 할당하는 기준을 파악하고, 불필요한 힙 할당을 줄이세요.
  
- **가비지 컬렉션 튜닝**:  
  - GC 주기 및 GC 관련 설정(GOGC)을 상황에 맞게 조정하여 성능 최적화를 도모하세요.
  
- **프로파일링**:  
  - `go tool pprof`를 사용해 정기적으로 메모리 사용량과 GC 활동을 모니터링하고, 병목 현상을 찾아 최적화하세요.
  
- **메모리 누수 방지**:  
  - 불필요한 메모리 참조를 해제하고, 사용 후 리소스를 적절히 반환하여 메모리 누수를 방지하세요.
  
- **메모리 풀링 및 슬라이스 최적화**:  
  - 자주 생성되는 객체는 `sync.Pool`을 활용해 재사용하고, 슬라이스 용량 관리 및 복사 기법을 적용하여 불필요한 재할당을 줄이세요.
  
- **구조체 정렬 최적화**:  
  - 구조체 필드의 순서를 조정하여 패딩을 최소화하고, 캐시 효율을 높이세요.

---

## Next Steps

- 기본 메모리 관리 개념을 충분히 이해한 후, **concurrency** 및 **performance optimization** 자료와 연계해 실제 애플리케이션의 메모리 사용 최적화 기법을 학습하세요.
- 더 복잡한 메모리 최적화 기법과 사례 연구를 통해, 실무 환경에서의 메모리 문제 해결 능력을 키워보세요.

Happy Memory Optimizing! 🎉