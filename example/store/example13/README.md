# 문제: "실시간 로그 프로세서"
## 설명
당신은 서버에서 생성되는 로그 메시지를 실시간으로 처리하는 프로그램을 Go로 작성해야 합니다. 이 프로그램은 로그 메시지를 생성하는 프로듀서와, 이를 처리해 통계를 계산하는 컨슈머로 구성됩니다. 채널을 활용해 로그를 전달하고, 동시성을 관리하며, 특정 조건에 따라 결과를 출력합니다.

## 요구사항
1. **입력**: 
   - 로그 메시지는 `struct`로 표현되며, 필드는 `Timestamp time.Time`, `Level string` (예: "INFO", "ERROR"), `Message string`.
   - 프로듀서가 1초마다 랜덤 로그 메시지를 생성(최소 10개 이상).
2. **동작**:
   - **프로듀서**: goroutine에서 로그 메시지를 생성해 채널로 전송.
   - **컨슈머**: 별도 goroutine에서 채널을 통해 로그를 받아 처리.
   - 처리 로직: 
     - "ERROR" 레벨 로그의 총 개수 카운트.
     - 최근 5초 내의 로그 메시지만 메모리에 유지(오래된 로그는 버림).
   - 채널은 버퍼 크기 5로 제한.
3. **출력**:
   - 프로그램 종료 시(예: 15초 후):
     - "ERROR" 로그 총 개수.
     - 최근 5초 내 로그 메시지 목록(`Timestamp`, `Level`, `Message` 출력).
4. **추가 요구사항**:
   - `context`로 전체 작업에 타임아웃(15초) 설정.
   - 로그 생성과 처리가 동시에 이루어져야 함.

## 목표
- 채널을 사용한 프로듀서-컨슈머 패턴 구현.
- 실시간 데이터 처리와 시간 기반 필터링 연습.
- 동시성과 타임아웃 관리.

---

## 예시 로그 메시지
```go
type Log struct {
    Timestamp time.Time
    Level     string
    Message   string
}
```

## 기대 출력 (15초 실행 후)
```
Total ERROR logs: 3
Recent logs (last 5 seconds):
2025-03-03 12:00:11 INFO "User logged in"
2025-03-03 12:00:12 ERROR "Database connection failed"
2025-03-03 12:00:13 INFO "Request processed"
```

---

## 힌트
1. **채널**:
   - `chan Log`로 로그 메시지를 전달.
   - 버퍼 크기 5로 설정(`make(chan Log, 5)`).
2. **프로듀서**:
   - `time.Tick`이나 `time.Sleep`으로 1초 간격 로그 생성.
   - 랜덤 레벨 선택(예: `"INFO"`, `"ERROR"`, `"WARN"`)은 `rand` 패키지 사용.
3. **컨슈머**:
   - 슬라이싱으로 최근 5초 로그만 유지(예: `time.Now().Sub(log.Timestamp) < 5*time.Second`).
   - `select`로 채널 수신과 타임아웃 처리 병행.
4. **타임아웃**:
   - `context.WithTimeout`으로 15초 제한.

---

## 참고 코드 구조
```go
package main

import (
    "context"
    "fmt"
    "math/rand"
    "time"
)

type Log struct {
    Timestamp time.Time
    Level     string
    Message   string
}

func processLogs(ctx context.Context, logsChan chan Log) (int, []Log) {
    // 여기에 구현
}

func main() {
    ctx, cancel := context.WithTimeout(context.Background(), 15*time.Second)
    defer cancel()

    logsChan := make(chan Log, 5)
    errorCount, recentLogs := processLogs(ctx, logsChan)

    fmt.Printf("Total ERROR logs: %d\n", errorCount)
    fmt.Println("Recent logs (last 5 seconds):")
    for _, log := range recentLogs {
        fmt.Printf("%s %s %q\n", log.Timestamp.Format("2006-01-02 15:04:05"), log.Level, log.Message)
    }
}
```

---

## 난이도 조정
- **기본**: 프로듀서와 컨슈머를 순차적으로 구현 후 채널 추가.
- **고급**: 로그 레벨별 통계(예: INFO, WARN, ERROR 개수) 추가, 파일에 로그 저장.