package main

import (
	"context"
	"fmt"
	"io"
	"net/http"
	"strings"
	"sync"
	"time"
)

func crawlURLs(urls []string, maxConcurrency int, timeout time.Duration) (map[string]string, map[string]error) {
	results := make(map[string]string)
	errors := make(map[string]error)
	var mu sync.Mutex // 맵 동기화를 위한 뮤텍스
	var wg sync.WaitGroup
	sem := make(chan struct{}, maxConcurrency) // 동시성 제한용 세마포어

	// 타임아웃 설정
	ctx, cancel := context.WithTimeout(context.Background(), timeout)
	defer cancel()

	for _, url := range urls {
		wg.Add(1)
		sem <- struct{}{} // 세마포어 획득 (최대 maxConcurrency까지)

		go func(url string) {
			defer wg.Done()
			defer func() { <-sem }() // 세마포어 해제

			// HTTP 요청 (타임아웃 고려)
			req, err := http.NewRequestWithContext(ctx, "GET", url, nil)
			if err != nil {
				mu.Lock()
				errors[url] = err
				mu.Unlock()
				return
			}
			res, err := http.DefaultClient.Do(req)
			if err != nil {
				mu.Lock()
				errors[url] = err
				mu.Unlock()
				return
			}
			defer res.Body.Close()

			// 본문 읽기
			bodyBytes, err := io.ReadAll(res.Body)
			if err != nil {
				mu.Lock()
				errors[url] = err
				mu.Unlock()
				return
			}
			body := string(bodyBytes)

			// 제목 추출
			startTag := "<title>"
			endTag := "</title>"
			startIndex := strings.Index(body, startTag)
			if startIndex == -1 {
				mu.Lock()
				errors[url] = fmt.Errorf("no <title> tag found")
				mu.Unlock()
				return
			}
			startIndex += len(startTag)
			endIndex := strings.Index(body[startIndex:], endTag)
			if endIndex == -1 {
				mu.Lock()
				errors[url] = fmt.Errorf("no </title> tag found")
				mu.Unlock()
				return
			}

			title := strings.TrimSpace(body[startIndex : startIndex+endIndex])
			mu.Lock()
			results[url] = title
			mu.Unlock()
		}(url)
	}

	wg.Wait() // 모든 goroutine 완료 대기
	return results, errors
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
