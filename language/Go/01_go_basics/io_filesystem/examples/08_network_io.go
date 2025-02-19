/*
이 예제는 네트워크 기반 파일 작업을 구현합니다.
주요 기능:
1. HTTP 파일 서버:
   - 지정한 루트 디렉토리의 파일들을 HTTP를 통해 서비스합니다.
   - 사용자는 브라우저나 HTTP 클라이언트를 통해 파일에 접근할 수 있습니다.
2. 파일 다운로드 클라이언트:
   - 원격 HTTP 서버에서 파일을 다운로드하여 로컬 디스크에 저장합니다.
   - 진행률 모니터링과 에러 처리를 포함합니다.
3. 동시 다운로드:
   - 여러 파일을 동시에 다운로드하여 전체 작업 시간을 단축하는 예제를 포함합니다.
이 예제는 실제 업무에서 원격 파일 시스템 연동, 분산 파일 처리, 또는 네트워크 기반 파일 전송에 활용할 수 있는 모범 사례를 제공합니다.
*/

package examples

import (
	"fmt"
	"io"
	"net/http"
	"os"
	"path/filepath"
	"sync"
	"time"
)

// ----------------------------
// 1. HTTP 파일 서버
// ----------------------------

// StartHTTPFileServer는 지정한 디렉토리의 파일들을 HTTP를 통해 서비스하는 파일 서버를 시작합니다.
// rootDir: 서비스할 파일들이 위치한 루트 디렉토리
// port: 서버가 리스닝할 포트 번호 (예: "8080")
func StartHTTPFileServer(rootDir, port string) {
	// http.FileServer는 지정한 디렉토리의 파일들을 서비스하는 핸들러를 반환합니다.
	fileServer := http.FileServer(http.Dir(rootDir))

	// "/" 경로로 들어오는 모든 요청에 대해 fileServer 핸들러를 사용합니다.
	http.Handle("/", fileServer)

	// 서버 시작 로그 출력
	fmt.Printf("HTTP 파일 서버 시작: 루트 디렉토리 %s, 포트 %s\n", rootDir, port)

	// ListenAndServe는 HTTP 서버를 시작합니다.
	if err := http.ListenAndServe(":"+port, nil); err != nil {
		fmt.Printf("HTTP 서버 실행 실패: %v\n", err)
	}
}

// ----------------------------
// 2. 파일 다운로드 클라이언트
// ----------------------------

// DownloadFile는 지정한 URL의 파일을 다운로드하여 dstPath에 저장합니다.
// URL: 다운로드할 파일의 URL
// dstPath: 파일을 저장할 대상 경로
func DownloadFile(url, dstPath string) error {
	// HTTP GET 요청을 통해 파일 데이터 가져오기
	resp, err := http.Get(url)
	if err != nil {
		return fmt.Errorf("HTTP GET 요청 실패: %w", err)
	}
	defer resp.Body.Close()

	// HTTP 응답 상태 코드 확인
	if resp.StatusCode != http.StatusOK {
		return fmt.Errorf("다운로드 실패: HTTP 상태 코드 %d", resp.StatusCode)
	}

	// 대상 디렉토리 생성 (없으면)
	dstDir := filepath.Dir(dstPath)
	if err := os.MkdirAll(dstDir, 0755); err != nil {
		return fmt.Errorf("대상 디렉토리 생성 실패: %w", err)
	}

	// 대상 파일 생성
	outFile, err := os.Create(dstPath)
	if err != nil {
		return fmt.Errorf("파일 생성 실패: %w", err)
	}
	defer outFile.Close()

	// 전체 파일 크기 (진행률 모니터링 용도)
	totalSize := resp.ContentLength
	var downloaded int64 = 0
	buf := make([]byte, 32*1024) // 32KB 버퍼

	// 다운로드 진행: 데이터를 청크 단위로 읽어 대상 파일에 씁니다.
	startTime := time.Now()
	for {
		nr, err := resp.Body.Read(buf)
		if nr > 0 {
			nw, err := outFile.Write(buf[0:nr])
			if err != nil {
				return fmt.Errorf("파일 쓰기 실패: %w", err)
			}
			if nr != nw {
				return fmt.Errorf("쓰기 불완전: 읽은 바이트 %d, 쓴 바이트 %d", nr, nw)
			}
			downloaded += int64(nw)
			// 진행률 출력
			if totalSize > 0 {
				percent := float64(downloaded) / float64(totalSize) * 100
				fmt.Printf("\r다운로드 진행률: %.2f%%", percent)
			} else {
				fmt.Printf("\r다운로드 중: %d 바이트 전송됨", downloaded)
			}
		}
		if err != nil {
			if err == io.EOF {
				break
			}
			return fmt.Errorf("다운로드 중 오류 발생: %w", err)
		}
	}
	duration := time.Since(startTime)
	fmt.Printf("\n다운로드 완료: %s (소요 시간: %v)\n", dstPath, duration)
	return nil
}

// ----------------------------
// 3. 동시 다운로드
// ----------------------------

// ConcurrentDownloader는 여러 URL의 파일을 동시 다운로드하는 함수입니다.
// urls: 다운로드할 파일들의 URL 목록
// dstDir: 파일들을 저장할 대상 디렉토리
// workerCount: 동시에 실행할 다운로드 워커 수
func ConcurrentDownloader(urls []string, dstDir string, workerCount int) []error {
	// 작업 태스크 정의: 각 URL에 대해 저장 경로를 포함하는 구조체
	type DownloadTask struct {
		url     string
		dstPath string
	}

	// 태스크 목록 생성
	var tasks []DownloadTask
	for _, url := range urls {
		// URL에서 파일 이름 추출 (예: 마지막 경로 요소)
		fileName := filepath.Base(url)
		dstPath := filepath.Join(dstDir, fileName)
		tasks = append(tasks, DownloadTask{url: url, dstPath: dstPath})
	}

	taskChan := make(chan DownloadTask, len(tasks))
	resultChan := make(chan error, len(tasks))

	var wg sync.WaitGroup

	// 워커 함수: 태스크 채널에서 다운로드 작업을 수행합니다.
	worker := func(id int) {
		defer wg.Done()
		for task := range taskChan {
			fmt.Printf("워커 %d: %s 다운로드 시작\n", id, task.url)
			err := DownloadFile(task.url, task.dstPath)
			if err != nil {
				resultChan <- fmt.Errorf("워커 %d - %s: %w", id, task.url, err)
			} else {
				resultChan <- nil
			}
		}
	}

	// 워커 시작
	wg.Add(workerCount)
	for i := 0; i < workerCount; i++ {
		go worker(i + 1)
	}

	// 태스크 전송
	for _, task := range tasks {
		taskChan <- task
	}
	close(taskChan)

	// 모든 워커 종료 대기
	wg.Wait()
	close(resultChan)

	// 결과 수집
	var errors []error
	for err := range resultChan {
		if err != nil {
			errors = append(errors, err)
		}
	}
	return errors
}

// NetworkIODemo는 HTTP 파일 서버와 파일 다운로드, 동시 다운로드 기능을 데모합니다.
func NetworkIODemo() {
	fmt.Println("==== 네트워크 I/O 데모 시작 ====")

	// 1. HTTP 파일 서버 데모
	// 데이터 디렉토리 지정 및 간단한 파일 생성
	serverDir := "./data/network_server"
	os.MkdirAll(serverDir, 0755)
	sampleFile := filepath.Join(serverDir, "sample.txt")
	os.WriteFile(sampleFile, []byte("이 파일은 HTTP 파일 서버 데모용입니다.\n네트워크를 통해 접근할 수 있습니다."), 0644)

	// 별도의 고루틴에서 HTTP 파일 서버 실행 (포트 8081)
	go StartHTTPFileServer(serverDir, "8081")
	// 잠시 대기하여 서버가 시작되도록 함
	time.Sleep(2 * time.Second)

	// 2. 파일 다운로드 데모
	// 예시 URL: 로컬에서 실행 중인 파일 서버의 sample.txt 파일 URL
	downloadURL := "http://localhost:8081/sample.txt"
	downloadDest := "./data/network_download/sample_download.txt"
	os.MkdirAll(filepath.Dir(downloadDest), 0755)
	err := DownloadFile(downloadURL, downloadDest)
	if err != nil {
		fmt.Printf("파일 다운로드 실패: %v\n", err)
	} else {
		fmt.Println("파일 다운로드 데모 완료!")
	}

	// 3. 동시 다운로드 데모
	// 여러 파일을 동시에 다운로드합니다.
	// 여기서는 동일한 파일을 여러 번 다운로드하여 데모합니다.
	urls := []string{
		"http://localhost:8081/sample.txt",
		"http://localhost:8081/sample.txt",
		"http://localhost:8081/sample.txt",
	}
	dstDir := "./data/network_download/concurrent"
	os.MkdirAll(dstDir, 0755)
	errors := ConcurrentDownloader(urls, dstDir, 2)
	if len(errors) > 0 {
		fmt.Println("동시 다운로드 중 일부 오류 발생:")
		for _, e := range errors {
			fmt.Printf("- %v\n", e)
		}
	} else {
		fmt.Println("동시 다운로드 데모 완료!")
	}

	fmt.Println("==== 네트워크 I/O 데모 종료 ====")
}
