/*
이 예제는 동시성을 활용한 I/O 작업을 구현합니다.
주요 기능:
1. 파일 복사 작업을 태스크 단위로 정의 (FileTask).
2. 워커 풀 패턴을 사용하여 여러 파일을 병렬로 복사합니다.
3. 각 워커는 io.Copy를 사용해 소스 파일의 데이터를 읽어 대상 파일에 씁니다.
4. 진행률 모니터링 및 에러 처리를 포함하여, 비동기 I/O 작업의 모범 사례를 제시합니다.

실제 업무에서는 대량의 파일 처리, 동시 다운로드, 비동기 파일 작업, 작업 큐 관리 등의 시나리오에 응용할 수 있습니다.
*/

package examples

import (
	"fmt"
	"io"
	"os"
	"path/filepath"
	"sync"
	"time"
)

// FileTask는 하나의 파일 복사 작업을 나타내는 구조체입니다.
// srcPath: 복사할 원본 파일 경로
// dstPath: 복사 결과를 저장할 대상 파일 경로
type FileTask struct {
	srcPath string
	dstPath string
}

// copyFile는 단일 파일 복사 작업을 수행합니다.
// 파일을 열고, 대상 파일을 생성한 후, io.Copy를 사용해 데이터를 스트리밍 방식으로 복사합니다.
// 복사 도중 발생한 에러는 반환됩니다.
func copyFile(task FileTask) error {
	// 원본 파일 열기
	srcFile, err := os.Open(task.srcPath)
	if err != nil {
		return fmt.Errorf("원본 파일 열기 실패 (%s): %w", task.srcPath, err)
	}
	defer srcFile.Close()

	// 대상 디렉토리가 존재하지 않으면 생성
	dstDir := filepath.Dir(task.dstPath)
	if err := os.MkdirAll(dstDir, 0755); err != nil {
		return fmt.Errorf("대상 디렉토리 생성 실패 (%s): %w", dstDir, err)
	}

	// 대상 파일 생성
	dstFile, err := os.Create(task.dstPath)
	if err != nil {
		return fmt.Errorf("대상 파일 생성 실패 (%s): %w", task.dstPath, err)
	}
	defer dstFile.Close()

	// 데이터 스트리밍 복사: 소스에서 대상 파일로 데이터를 전송
	_, err = io.Copy(dstFile, srcFile)
	if err != nil {
		return fmt.Errorf("파일 복사 중 오류 (%s -> %s): %w", task.srcPath, task.dstPath, err)
	}

	// 파일 복사 완료
	return nil
}

// ConcurrentFileCopier는 여러 파일 복사 태스크를 동시 처리하는 워커 풀을 구현합니다.
// tasks: 처리할 FileTask 목록
// workerCount: 동시에 실행할 워커 수
// 반환값: 전체 작업에서 발생한 에러들의 집합 (에러가 없으면 nil)
func ConcurrentFileCopier(tasks []FileTask, workerCount int) []error {
	// 태스크와 결과를 위한 채널 생성
	taskChan := make(chan FileTask, len(tasks))
	resultChan := make(chan error, len(tasks))

	var wg sync.WaitGroup

	// 워커 함수: 태스크 채널에서 FileTask를 수신하여 copyFile 수행 후 결과를 전송
	worker := func(id int) {
		defer wg.Done()
		for task := range taskChan {
			start := time.Now()
			err := copyFile(task)
			duration := time.Since(start)
			if err != nil {
				resultChan <- fmt.Errorf("워커 %d: %v", id, err)
			} else {
				fmt.Printf("워커 %d: %s 복사 완료 (소요 시간: %v)\n", id, filepath.Base(task.srcPath), duration)
				resultChan <- nil
			}
		}
	}

	// 워커 시작
	wg.Add(workerCount)
	for i := 0; i < workerCount; i++ {
		go worker(i + 1)
	}

	// 모든 태스크 전송
	for _, task := range tasks {
		taskChan <- task
	}
	close(taskChan)

	// 워커 종료 대기
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

// ConcurrentIODemo는 동시 파일 작업 데모를 실행합니다.
// 소스 디렉토리의 모든 파일을 대상으로 지정한 대상 디렉토리로 병렬 복사 작업을 수행합니다.
func ConcurrentIODemo() {
	fmt.Println("==== 동시 파일 I/O 데모 시작 ====")

	// 데모를 위한 소스 및 대상 디렉토리 설정
	srcDir := "./data/concurrent_src"
	dstDir := "./data/concurrent_dst"

	// 데모용 파일들이 저장될 디렉토리 생성
	os.MkdirAll(srcDir, 0755)
	os.MkdirAll(dstDir, 0755)

	// 데모용 원본 파일 생성: 5개의 텍스트 파일 생성
	fileCount := 5
	for i := 1; i <= fileCount; i++ {
		filePath := filepath.Join(srcDir, fmt.Sprintf("file_%d.txt", i))
		content := fmt.Sprintf("이것은 파일 %d의 내용입니다. 스트리밍 I/O 데모용 데이터입니다.\n", i)
		if err := os.WriteFile(filePath, []byte(content), 0644); err != nil {
			fmt.Printf("파일 생성 실패 (%s): %v\n", filePath, err)
			return
		}
	}

	// 원본 파일 목록 수집
	var tasks []FileTask
	err := filepath.Walk(srcDir, func(path string, info os.FileInfo, err error) error {
		if err != nil {
			return err
		}
		// 파일인 경우에만 태스크 생성
		if !info.IsDir() {
			relPath, err := filepath.Rel(srcDir, path)
			if err != nil {
				relPath = filepath.Base(path)
			}
			dstPath := filepath.Join(dstDir, relPath)
			tasks = append(tasks, FileTask{
				srcPath: path,
				dstPath: dstPath,
			})
		}
		return nil
	})
	if err != nil {
		fmt.Printf("원본 파일 목록 수집 실패: %v\n", err)
		return
	}

	fmt.Printf("총 %d개의 파일 복사 작업을 시작합니다.\n", len(tasks))

	// 동시 파일 복사: 워커 수를 3으로 설정
	errors := ConcurrentFileCopier(tasks, 3)
	if len(errors) > 0 {
		fmt.Println("일부 파일 복사 중 에러가 발생했습니다:")
		for _, err := range errors {
			fmt.Printf("- %v\n", err)
		}
	} else {
		fmt.Println("모든 파일 복사 작업이 성공적으로 완료되었습니다.")
	}

	fmt.Println("==== 동시 파일 I/O 데모 종료 ====")
}
