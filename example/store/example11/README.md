# 문제: "동시성 기반 웹 크롤러"
## 설명
당신은 여러 웹사이트에서 데이터를 수집하는 간단한 웹 크롤러를 Go로 작성해야 합니다. 이 크롤러는 주어진 URL 목록에서 동시에 페이지를 가져오고, 각 페이지의 제목(`<title>` 태그 내용)을 추출해 결과를 출력합니다. 동시성을 활용해 작업 속도를 높이고, Go의 표준 라이브러리와 에러 처리를 연습해 보세요.

## 요구사항
1. **입력**: URL 목록(예: `[]string{"https://golang.org", "https://example.com", ...}`).
2. **동작**:
   - 각 URL을 동시에 크롤링하기 위해 goroutine 사용.
   - 채널을 통해 크롤링 결과를 수집.
   - context 패키지를 사용해 타임아웃(예: 10초) 설정.
   - net/http로 페이지 가져오기, 에러 처리 포함.
3. **출력**: 각 URL과 해당 페이지의 제목을 맵(`map[string]string`)으로 반환.
4. **추가 요구사항**:
   - 크롤링 중 발생하는 에러(예: 연결 실패, 잘못된 URL)는 별도로 기록.
   - 최대 동시 작업 수를 제한(예: 3개 goroutine만 동시에 실행).

## 목표
- Goroutine과 채널을 사용한 동시성 구현.
- 표준 라이브러리(net/http, context 등) 활용.
- 에러 처리 및 리소스 관리 연습.

---

## 예시 입력
```go
urls := []string{
    "https://golang.org",
    "https://example.com",
    "https://github.com",
    "https://invalid-url", // 에러 발생 예시
}
```

## 기대 출력
```
Results:
https://golang.org: The Go Programming Language
https://example.com: Example Domain
https://github.com: GitHub: Let’s build from here · GitHub

Errors:
https://invalid-url: Get "https://invalid-url": dial tcp: lookup invalid-url: no such host
```

---

## 힌트
1. **동시성**: 
   - `sync.WaitGroup`으로 모든 goroutine이 끝날 때까지 대기.
   - 채널로 결과를 수집하거나, 결과 맵을 동기화(`sync.Mutex` 사용).
2. **제한**: 
   - 세마포어 패턴(채널로 동시 작업 수 제어) 사용 가능.
3. **HTML 파싱**: 
   - `strings.Contains`나 간단한 문자열 검색으로 `<title>` 추출(정규식 또는 외부 파서 사용은 선택).
4. **타임아웃**: 
   - `context.WithTimeout`으로 전체 작업에 시간 제한 설정.

---

## 참고 코드 구조
```go
package main

import (
    "context"
    "fmt"
    "net/http"
    "sync"
    "time"
)

func crawlURLs(urls []string, maxConcurrency int, timeout time.Duration) (map[string]string, map[string]error) {
    // 여기에 구현
}

func main() {
    urls := []string{
        "https://golang.org",
        "https://example.com",
        "https://github.com",
        "https://invalid-url",
    }
    results, errors := crawlURLs(urls, 3, 10*time.Second)
    
    fmt.Println("Results:")
    for url, title := range results {
        fmt.Printf("%s: %s\n", url, title)
    }
    fmt.Println("\nErrors:")
    for url, err := range errors {
        fmt.Printf("%s: %v\n", url, err)
    }
}
```

---

## 난이도 조정
- **기본**: 동시성 없이 순차적으로 구현 후 goroutine 추가.
- **고급**: 세마포어로 동시성 제한, context로 타임아웃, HTML 파싱 최적화.