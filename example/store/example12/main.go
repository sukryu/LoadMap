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
	results := make(map[string]string)
	errors := make(map[string]error)
	var mu sync.Mutex
	var wg sync.WaitGroup
	sem := make(chan struct{}, maxConcurrency)

	// 진행률 추적용 변수
	var counter int
	total := len(urls)

	ctx, cancel := context.WithTimeout(context.Background(), timeout)
	defer cancel()

	for _, url := range urls {
		wg.Add(1)
		sem <- struct{}{} // 세마포어 획득

		go func(url string) {
			defer wg.Done()
			defer func() { <-sem }() // 세마포어 해제

			// HTTP 요청
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

			// 파일 생성
			filename := path.Base(url)
			file, err := os.Create(filename)
			if err != nil {
				mu.Lock()
				errors[url] = err
				mu.Unlock()
				return
			}
			defer file.Close()

			// 응답 본문을 파일에 쓰기
			_, err = io.Copy(file, res.Body)
			if err != nil {
				mu.Lock()
				errors[url] = err
				mu.Unlock()
				return
			}

			// 성공 시 결과 기록 및 진행률 업데이트
			mu.Lock()
			results[url] = "./" + filename // 로컬 경로 저장
			counter++
			fmt.Printf("Progress: Downloaded %d/%d files\n", counter, total)
			mu.Unlock()
		}(url)
	}

	wg.Wait() // 모든 다운로드 완료 대기
	return results, errors
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
