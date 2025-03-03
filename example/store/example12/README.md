# 문제: "동시 파일 다운로더"
## 설명
당신은 여러 파일을 인터넷에서 동시에 다운로드하고, 로컬 디스크에 저장하는 프로그램을 Go로 작성해야 합니다. 이 다운로더는 파일 URL 목록을 받아 병렬로 다운로드하며, 진행 상황을 추적하고 결과를 보고합니다. 동시성 제어와 에러 처리를 연습해 보세요.

## 요구사항
1. **입력**: 파일 URL 목록(예: `[]string{"https://example.com/file1.txt", ...}`).
2. **동작**:
   - 각 파일을 goroutine으로 동시에 다운로드.
   - 최대 동시 다운로드 수를 제한(예: 4개).
   - `sync.WaitGroup`으로 모든 다운로드 완료 대기.
   - 다운로드한 파일을 로컬에 저장(파일명은 URL의 마지막 부분 사용, 예: `file1.txt`).
   - `sync.Mutex`로 결과 맵 동기화.
3. **출력**:
   - 성공한 파일: `map[string]string` (URL → 로컬 파일 경로).
   - 실패한 파일: `map[string]error` (URL → 에러 메시지).
4. **추가 요구사항**:
   - 진행률을 표시(예: "Downloaded 3/10 files").
   - 타임아웃 15초 적용(`context` 사용).

## 목표
- Goroutine, 채널, 뮤텍스, WaitGroup을 조합한 동시성 처리.
- 파일 I/O와 네트워크 요청 통합.
- 진행 상황 모니터링과 에러 관리.

---

## 예시 입력
```go
urls := []string{
    "https://golang.org/doc/gopher/frontpage.png",
    "https://example.com/index.html",
    "https://github.com/favicon.ico",
    "https://invalid-url/file.txt",
}
```

## 기대 출력
```
Progress: Downloaded 1/4 files
Progress: Downloaded 2/4 files
Progress: Downloaded 3/4 files
Progress: Downloaded 3/4 files

Results:
https://golang.org/doc/gopher/frontpage.png: ./frontpage.png
https://example.com/index.html: ./index.html
https://github.com/favicon.ico: ./favicon.ico

Errors:
https://invalid-url/file.txt: Get "https://invalid-url/file.txt": dial tcp: lookup invalid-url: no such host
```

---

## 힌트
1. **동시성**:
   - `sync.WaitGroup`으로 모든 goroutine 완료 감지.
   - 세마포어 패턴(`chan struct{}`)으로 최대 동시성 제한.
2. **파일 저장**:
   - `os.Create`로 파일 생성, `io.Copy`로 HTTP 응답 본문을 파일에 쓰기.
   - URL에서 파일명 추출은 `path.Base` 사용 가능.
3. **진행률**:
   - 다운로드 완료 시마다 카운터 증가, `sync.Mutex`로 보호.
4. **타임아웃**:
   - `context.WithTimeout`으로 전체 작업 제한.

---

## 참고 코드 구조
```go
package main

import (
    "context"
    "fmt"
    "io"
    "net/http"
    "os"
    "path"
    "sync"
    "time"
)

func downloadFiles(urls []string, maxConcurrency int, timeout time.Duration) (map[string]string, map[string]error) {
    // 여기에 구현
}

func main() {
    urls := []string{
        "https://golang.org/doc/gopher/frontpage.png",
        "https://example.com/index.html",
        "https://github.com/favicon.ico",
        "https://invalid-url/file.txt",
    }
    results, errors := downloadFiles(urls, 4, 15*time.Second)

    fmt.Println("\nResults:")
    for url, file := range results {
        fmt.Printf("%s: %s\n", url, file)
    }
    fmt.Println("\nErrors:")
    for url, err := range errors {
        fmt.Printf("%s: %v\n", url, err)
    }
}
```

---

## 난이도 조정
- **기본**: 동시성 없이 순차 다운로드 구현 후 goroutine 추가.
- **고급**: 진행률을 실시간으로 업데이트(별도 goroutine 사용), 다운로드 속도 측정 추가.