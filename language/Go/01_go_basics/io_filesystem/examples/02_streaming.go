/*
이 예제는 스트리밍 I/O를 통해 대용량 파일 데이터를 효율적으로 처리하는 방법을 보여줍니다.
주요 기능:
1. io.Reader와 io.Writer 인터페이스를 활용하여 데이터를 청크 단위로 읽고 씁니다.
2. 진행률 모니터링: 전체 파일 크기 대비 복사 진행 상황을 주기적으로 출력합니다.
3. 에러 처리: 스트리밍 I/O 작업 중 발생할 수 있는 오류를 적절히 처리합니다.

이 예제는 파일 복사뿐만 아니라, 네트워크 스트리밍과 같이 대용량 데이터를 다루는 다양한 시나리오에 응용할 수 있습니다.
*/

package examples

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"time"
)

// StreamFileCopy는 srcPath의 파일을 dstPath로 청크 단위로 복사하며, 진행률을 모니터링합니다.
// chunkSize: 한 번에 읽어 들일 바이트 수를 지정합니다.
func StreamFileCopy(srcPath, dstPath string, chunkSize int) error {
	// 원본 파일 열기
	srcFile, err := os.Open(srcPath)
	if err != nil {
		return fmt.Errorf("원본 파일 열기 실패: %w", err)
	}
	defer srcFile.Close()

	// 대상 파일 생성 (없으면 새로 생성)
	dstFile, err := os.Create(dstPath)
	if err != nil {
		return fmt.Errorf("대상 파일 생성 실패: %w", err)
	}
	defer dstFile.Close()

	// 원본 파일의 전체 크기를 가져와 진행률 계산에 사용합니다.
	srcInfo, err := srcFile.Stat()
	if err != nil {
		return fmt.Errorf("원본 파일 정보 확인 실패: %w", err)
	}
	totalSize := srcInfo.Size()
	fmt.Printf("파일 복사 시작: 전체 크기 %d 바이트\n", totalSize)

	// 버퍼를 활용한 읽기/쓰기 작업을 위해 bufio 사용
	reader := bufio.NewReader(srcFile)
	writer := bufio.NewWriter(dstFile)
	// writer.Flush()는 작업 종료 전에 반드시 호출해야 합니다.
	defer writer.Flush()

	var totalCopied int64 = 0
	buf := make([]byte, chunkSize)

	// 진행률 모니터링을 위한 고루틴 시작
	progressChan := make(chan struct{})
	go func() {
		ticker := time.NewTicker(time.Second)
		defer ticker.Stop()
		for {
			select {
			case <-ticker.C:
				percent := float64(totalCopied) / float64(totalSize) * 100
				fmt.Printf("복사 진행률: %.2f%% (%d/%d 바이트)\n", percent, totalCopied, totalSize)
			case <-progressChan:
				return
			}
		}
	}()

	// 데이터를 청크 단위로 읽어서 대상 파일에 씁니다.
	for {
		n, err := reader.Read(buf)
		if n > 0 {
			wn, werr := writer.Write(buf[:n])
			if wn < n {
				return fmt.Errorf("데이터 쓰기 불완전: 예상 %d 바이트, 실제 %d 바이트", n, wn)
			}
			if werr != nil {
				return fmt.Errorf("데이터 쓰기 실패: %w", werr)
			}
			totalCopied += int64(n)
		}
		if err != nil {
			if err == io.EOF {
				break
			}
			return fmt.Errorf("데이터 읽기 실패: %w", err)
		}
	}

	// 복사 완료 후 진행률 모니터링 고루틴 종료
	close(progressChan)
	fmt.Printf("파일 복사 완료: 총 %d 바이트 복사됨.\n", totalCopied)
	return nil
}

// StreamingIODemo는 스트리밍 I/O 기능을 데모하는 함수입니다.
// 임시 파일을 생성하여 더미 데이터를 작성한 후, 스트리밍 방식으로 복사하는 예제를 실행합니다.
func StreamingIODemo() {
	fmt.Println("==== 스트리밍 I/O 데모 시작 ====")

	// 데모를 위한 파일 경로 설정 및 data 디렉토리 생성
	srcPath := "./data/streaming_src.txt"
	dstPath := "./data/streaming_dst.txt"
	os.MkdirAll("./data", 0755)

	// 원본 파일 생성: 5MB 크기의 더미 데이터를 작성합니다.
	dummyData := make([]byte, 5*1024*1024)
	for i := range dummyData {
		// 'A'부터 'Z'까지 반복하여 데이터 패턴 생성
		dummyData[i] = byte('A' + (i % 26))
	}
	err := os.WriteFile(srcPath, dummyData, 0644)
	if err != nil {
		fmt.Printf("원본 파일 생성 실패: %v\n", err)
		return
	}
	fmt.Printf("원본 파일 생성됨: %s (크기: %d 바이트)\n", srcPath, len(dummyData))

	// 스트리밍 복사 실행: 청크 크기 64KB 사용
	err = StreamFileCopy(srcPath, dstPath, 64*1024)
	if err != nil {
		fmt.Printf("파일 복사 실패: %v\n", err)
		return
	}

	fmt.Println("==== 스트리밍 I/O 데모 종료 ====")
}
