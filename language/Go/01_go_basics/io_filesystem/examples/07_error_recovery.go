/*
이 예제는 I/O 작업 중 발생할 수 있는 오류 상황에 대한 복구 전략을 구현합니다.
주요 기능:
1. 파일 백업: 작업 전 원본 파일을 백업하여, 오류 발생 시 원본을 복원합니다.
2. 체크포인트 생성: 긴 작업 중간에 체크포인트 파일을 생성하여, 작업 재시작에 활용합니다.
3. 트랜잭션 로그: 작업 단계를 기록하여, 오류 발생 시 로그를 기반으로 복구를 시도합니다.
4. 오류 복구: I/O 작업 오류 시 백업 복원 및 로그를 통한 복구를 수행합니다.

각 함수는 실제 업무에서 파일 I/O 작업의 안정성을 높이기 위한 모범 사례와 함께, 상세한 주석을 통해 동작 원리를 설명합니다.
*/

package examples

import (
	"fmt"
	"io"
	"io/ioutil"
	"os"
	"path/filepath"
	"time"
)

// ----------------------------
// 파일 백업 및 복원
// ----------------------------

// BackupFile은 srcPath의 파일을 dstPath로 복사하여 백업을 생성합니다.
func BackupFile(srcPath, backupPath string) error {
	// 원본 파일 열기
	srcFile, err := os.Open(srcPath)
	if err != nil {
		return fmt.Errorf("백업: 원본 파일 열기 실패 (%s): %w", srcPath, err)
	}
	defer srcFile.Close()

	// 백업 파일 생성 (덮어쓰기)
	backupFile, err := os.Create(backupPath)
	if err != nil {
		return fmt.Errorf("백업: 백업 파일 생성 실패 (%s): %w", backupPath, err)
	}
	defer backupFile.Close()

	// 데이터 복사
	if _, err := io.Copy(backupFile, srcFile); err != nil {
		return fmt.Errorf("백업: 데이터 복사 실패: %w", err)
	}

	fmt.Printf("백업 파일 생성 완료: %s -> %s\n", srcPath, backupPath)
	return nil
}

// RestoreBackup는 백업 파일을 원본 위치로 복원합니다.
func RestoreBackup(backupPath, srcPath string) error {
	// 백업 파일 열기
	backupFile, err := os.Open(backupPath)
	if err != nil {
		return fmt.Errorf("복원: 백업 파일 열기 실패 (%s): %w", backupPath, err)
	}
	defer backupFile.Close()

	// 원본 파일 생성 (덮어쓰기)
	srcFile, err := os.Create(srcPath)
	if err != nil {
		return fmt.Errorf("복원: 원본 파일 생성 실패 (%s): %w", srcPath, err)
	}
	defer srcFile.Close()

	// 데이터 복사
	if _, err := io.Copy(srcFile, backupFile); err != nil {
		return fmt.Errorf("복원: 데이터 복사 실패: %w", err)
	}

	fmt.Printf("복원 완료: 백업 파일 %s가 원본 파일 %s로 복원되었습니다.\n", backupPath, srcPath)
	return nil
}

// ----------------------------
// 체크포인트 및 트랜잭션 로그
// ----------------------------

// WriteCheckpoint는 현재 진행 상황을 checkpoint 파일로 기록합니다.
func WriteCheckpoint(checkpointPath string, data string) error {
	err := ioutil.WriteFile(checkpointPath, []byte(data), 0644)
	if err != nil {
		return fmt.Errorf("체크포인트 쓰기 실패 (%s): %w", checkpointPath, err)
	}
	fmt.Printf("체크포인트 저장: %s\n", checkpointPath)
	return nil
}

// ReadCheckpoint는 checkpoint 파일을 읽어 내용을 반환합니다.
func ReadCheckpoint(checkpointPath string) (string, error) {
	data, err := ioutil.ReadFile(checkpointPath)
	if err != nil {
		return "", fmt.Errorf("체크포인트 읽기 실패 (%s): %w", checkpointPath, err)
	}
	return string(data), nil
}

// AppendTransactionLog는 트랜잭션 로그 파일에 새로운 로그를 추가합니다.
func AppendTransactionLog(logPath string, logEntry string) error {
	// 파일을 append 모드로 열기 (없으면 생성)
	file, err := os.OpenFile(logPath, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		return fmt.Errorf("트랜잭션 로그 열기 실패 (%s): %w", logPath, err)
	}
	defer file.Close()

	entry := fmt.Sprintf("%s: %s\n", time.Now().Format(time.RFC3339), logEntry)
	if _, err := file.WriteString(entry); err != nil {
		return fmt.Errorf("트랜잭션 로그 쓰기 실패: %w", err)
	}
	return nil
}

// ----------------------------
// 오류 복구 작업 시뮬레이션
// ----------------------------

// SimulateFileOperation은 파일 작업 중 일부러 오류를 발생시키고, 오류 복구 절차를 수행하는 예제 함수입니다.
func SimulateFileOperation(srcPath, backupPath, checkpointPath, logPath string) {
	fmt.Println("==== 오류 복구 데모 시작 ====")

	// 1. 원본 파일 백업
	if err := BackupFile(srcPath, backupPath); err != nil {
		fmt.Printf("백업 실패: %v\n", err)
		return
	}
	AppendTransactionLog(logPath, "백업 파일 생성")

	// 2. 체크포인트 생성: 현재 작업 상태 기록
	checkpointData := "Step 1 완료: 백업 생성됨"
	if err := WriteCheckpoint(checkpointPath, checkpointData); err != nil {
		fmt.Printf("체크포인트 기록 실패: %v\n", err)
		return
	}
	AppendTransactionLog(logPath, "체크포인트 기록됨")

	// 3. 파일 작업 시뮬레이션: 원본 파일에 데이터 추가
	err := appendDataToFile(srcPath, "\n추가 데이터: 작업 중 오류 발생 시뮬레이션")
	if err != nil {
		AppendTransactionLog(logPath, fmt.Sprintf("파일 작업 실패: %v", err))
		// 오류 발생 시 백업 복원
		fmt.Println("오류 발생: 백업 파일로 복원 시도...")
		if errRestore := RestoreBackup(backupPath, srcPath); errRestore != nil {
			fmt.Printf("복원 실패: %v\n", errRestore)
		} else {
			AppendTransactionLog(logPath, "파일 복원 완료")
		}
	} else {
		AppendTransactionLog(logPath, "파일 작업 성공")
	}

	// 4. 최종 체크포인트 업데이트 (정상 완료 시)
	finalCheckpoint := "Step 2 완료: 파일 작업 성공"
	if err := WriteCheckpoint(checkpointPath, finalCheckpoint); err != nil {
		fmt.Printf("최종 체크포인트 기록 실패: %v\n", err)
	} else {
		AppendTransactionLog(logPath, "최종 체크포인트 기록됨")
	}

	fmt.Println("==== 오류 복구 데모 종료 ====")
}

// appendDataToFile는 주어진 파일에 데이터를 추가하는 함수입니다.
// 고의로 오류를 발생시킬 수 있도록 조건을 넣어 시뮬레이션할 수 있습니다.
func appendDataToFile(filePath, data string) error {
	// 파일을 append 모드로 열기
	file, err := os.OpenFile(filePath, os.O_APPEND|os.O_WRONLY, 0644)
	if err != nil {
		return fmt.Errorf("파일 열기 실패: %w", err)
	}
	defer file.Close()

	// 고의로 오류 시뮬레이션: 파일 크기가 특정 크기 이상이면 오류 발생
	info, err := file.Stat()
	if err != nil {
		return fmt.Errorf("파일 상태 확인 실패: %w", err)
	}
	if info.Size() > 1024*1024 { // 예: 1MB 이상이면 오류 발생
		return fmt.Errorf("파일 크기 제한 초과: %d 바이트", info.Size())
	}

	// 데이터 추가
	if _, err := file.WriteString(data); err != nil {
		return fmt.Errorf("데이터 추가 실패: %w", err)
	}
	return nil
}

// ----------------------------
// ErrorRecoveryDemo: 전체 오류 복구 데모
// ----------------------------

// ErrorRecoveryDemo는 파일 시스템 작업 중 오류 복구 전략을 종합적으로 데모합니다.
func ErrorRecoveryDemo() {
	// 데모를 위한 기본 경로 설정 (data 디렉토리 존재 보장)
	baseDir := "./data/error_recovery"
	os.MkdirAll(baseDir, 0755)

	srcFile := filepath.Join(baseDir, "original.txt")
	backupFile := filepath.Join(baseDir, "backup.txt")
	checkpointFile := filepath.Join(baseDir, "checkpoint.txt")
	logFile := filepath.Join(baseDir, "transaction.log")

	// 원본 파일 생성: 초기 데이터 기록
	initialContent := "원본 파일 초기 내용\n"
	if err := os.WriteFile(srcFile, []byte(initialContent), 0644); err != nil {
		fmt.Printf("원본 파일 생성 실패: %v\n", err)
		return
	}
	fmt.Printf("원본 파일 생성됨: %s\n", srcFile)

	// 오류 복구 데모 실행: 파일 작업 도중 고의로 오류를 발생시키고 복구를 시도합니다.
	SimulateFileOperation(srcFile, backupFile, checkpointFile, logFile)

	// 최종 원본 파일 내용 확인
	finalData, err := os.ReadFile(srcFile)
	if err != nil {
		fmt.Printf("최종 파일 읽기 실패: %v\n", err)
		return
	}
	fmt.Println("최종 원본 파일 내용:")
	fmt.Println(string(finalData))
}
