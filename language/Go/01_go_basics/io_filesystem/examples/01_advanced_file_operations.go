/*
이 예제는 기본 파일 작업을 넘어서는 고급 파일 조작 기능들을 보여줍니다.
주요 기능:
1. 파일 잠금 (File Locking)
   - 파일에 대한 독점적 접근을 위해 잠금을 구현합니다.
   - syscall.Flock을 사용하여 Unix 환경에서 파일 잠금을 수행합니다.
2. 임시 파일 생성 (Temporary File Creation)
   - os.CreateTemp를 사용하여 임시 파일을 생성하고, 데이터를 기록 후 삭제하는 예제를 포함합니다.
3. 파일 권한 관리 (File Permission Management)
   - 파일의 권한을 읽고 변경하는 방법을 보여줍니다.
4. 심볼릭 링크 처리 (Symbolic Link Handling)
   - 심볼릭 링크 생성, 읽기, 삭제 등의 작업을 수행합니다.

각 기능은 상세한 주석과 함께 단계별로 구현되어 있어, 실제 업무에서 자주 발생하는 시나리오에 대한 모범 사례를 학습할 수 있습니다.
*/

package examples

import (
	"fmt"
	"io/ioutil"
	"os"
	"syscall"
	"time"
)

// ----------------------------
// 파일 잠금 (File Locking)
// ----------------------------

// LockFile는 지정한 파일에 대해 독점적 잠금을 수행합니다.
// 이 함수는 Unix 시스템에서 syscall.Flock을 사용하여 파일 잠금을 구현합니다.
func LockFile(f *os.File) error {
	// LOCK_EX: 배타적 잠금, LOCK_NB: 논블로킹 모드 (잠금에 실패하면 에러 반환)
	err := syscall.Flock(int(f.Fd()), syscall.LOCK_EX|syscall.LOCK_NB)
	if err != nil {
		return fmt.Errorf("파일 잠금 실패: %w", err)
	}
	return nil
}

// UnlockFile는 파일의 잠금을 해제합니다.
func UnlockFile(f *os.File) error {
	err := syscall.Flock(int(f.Fd()), syscall.LOCK_UN)
	if err != nil {
		return fmt.Errorf("파일 잠금 해제 실패: %w", err)
	}
	return nil
}

// DemonstrateFileLocking은 파일 잠금 및 해제 동작을 예제로 보여줍니다.
func DemonstrateFileLocking(filePath string) {
	fmt.Println("== 파일 잠금 예제 ==")
	// 파일 열기 (없으면 생성)
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_RDWR, 0644)
	if err != nil {
		fmt.Printf("파일 열기 실패: %v\n", err)
		return
	}
	defer file.Close()

	// 파일 잠금 시도
	if err := LockFile(file); err != nil {
		fmt.Printf("파일 잠금 실패: %v\n", err)
		return
	}
	fmt.Println("파일 잠금 성공!")

	// 파일에 데이터 기록 (잠금이 걸린 상태에서 안전하게 작업)
	_, err = file.WriteString("고급 파일 잠금 예제 데이터\n")
	if err != nil {
		fmt.Printf("파일 쓰기 실패: %v\n", err)
	}

	// 잠시 대기 (다른 프로세스가 접근할 수 없음을 시뮬레이션)
	time.Sleep(2 * time.Second)

	// 파일 잠금 해제
	if err := UnlockFile(file); err != nil {
		fmt.Printf("파일 잠금 해제 실패: %v\n", err)
		return
	}
	fmt.Println("파일 잠금 해제 성공!")
}

// ----------------------------
// 임시 파일 생성 (Temporary File Creation)
// ----------------------------

// DemonstrateTempFileCreation은 임시 파일 생성, 데이터 기록, 읽기 및 삭제 작업을 보여줍니다.
func DemonstrateTempFileCreation() {
	fmt.Println("\n== 임시 파일 생성 예제 ==")
	// os.TempDir()를 사용해 시스템 임시 디렉토리 경로를 얻습니다.
	tempDir := os.TempDir()
	// 임시 파일 생성 (패턴: "advfile_*.txt")
	tempFile, err := os.CreateTemp(tempDir, "advfile_*.txt")
	if err != nil {
		fmt.Printf("임시 파일 생성 실패: %v\n", err)
		return
	}
	// 생성된 임시 파일 경로 출력
	fmt.Printf("임시 파일 생성됨: %s\n", tempFile.Name())

	// 임시 파일에 데이터 기록
	content := "임시 파일에 저장된 고급 파일 작업 예제 데이터\n"
	if _, err := tempFile.WriteString(content); err != nil {
		fmt.Printf("임시 파일 쓰기 실패: %v\n", err)
		tempFile.Close()
		return
	}

	// 파일 닫기
	tempFile.Close()

	// 임시 파일 읽기
	data, err := ioutil.ReadFile(tempFile.Name())
	if err != nil {
		fmt.Printf("임시 파일 읽기 실패: %v\n", err)
		return
	}
	fmt.Printf("임시 파일 내용:\n%s", string(data))

	// 임시 파일 삭제
	if err := os.Remove(tempFile.Name()); err != nil {
		fmt.Printf("임시 파일 삭제 실패: %v\n", err)
		return
	}
	fmt.Println("임시 파일 삭제 성공!")
}

// ----------------------------
// 파일 권한 관리 (File Permission Management)
// ----------------------------

// DemonstrateFilePermissionManagement은 파일 권한 읽기 및 변경 작업을 예제로 보여줍니다.
func DemonstrateFilePermissionManagement(filePath string) {
	fmt.Println("\n== 파일 권한 관리 예제 ==")
	// 파일 생성 (없으면 생성)
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_RDWR, 0644)
	if err != nil {
		fmt.Printf("파일 열기 실패: %v\n", err)
		return
	}
	file.Close()

	// 파일 권한 확인
	info, err := os.Stat(filePath)
	if err != nil {
		fmt.Printf("파일 정보 확인 실패: %v\n", err)
		return
	}
	fmt.Printf("기본 파일 권한: %o\n", info.Mode().Perm())

	// 파일 권한 변경 (예: 0640으로 변경)
	if err := os.Chmod(filePath, 0640); err != nil {
		fmt.Printf("파일 권한 변경 실패: %v\n", err)
		return
	}
	fmt.Println("파일 권한 변경 성공!")

	// 변경된 파일 권한 확인
	info, err = os.Stat(filePath)
	if err != nil {
		fmt.Printf("파일 정보 재확인 실패: %v\n", err)
		return
	}
	fmt.Printf("변경된 파일 권한: %o\n", info.Mode().Perm())
}

// ----------------------------
// 심볼릭 링크 처리 (Symbolic Link Handling)
// ----------------------------

// DemonstrateSymlinkHandling은 심볼릭 링크 생성, 읽기, 삭제를 수행합니다.
func DemonstrateSymlinkHandling(targetPath, linkPath string) {
	fmt.Println("\n== 심볼릭 링크 처리 예제 ==")
	// 우선, 대상 파일이 존재하는지 확인하고 없으면 생성
	if _, err := os.Stat(targetPath); os.IsNotExist(err) {
		err = ioutil.WriteFile(targetPath, []byte("심볼릭 링크 대상 파일 내용\n"), 0644)
		if err != nil {
			fmt.Printf("대상 파일 생성 실패: %v\n", err)
			return
		}
	}

	// 심볼릭 링크 생성
	err := os.Symlink(targetPath, linkPath)
	if err != nil {
		fmt.Printf("심볼릭 링크 생성 실패: %v\n", err)
		return
	}
	fmt.Printf("심볼릭 링크 생성됨: %s -> %s\n", linkPath, targetPath)

	// 심볼릭 링크 대상 읽기
	resolvedPath, err := os.Readlink(linkPath)
	if err != nil {
		fmt.Printf("심볼릭 링크 읽기 실패: %v\n", err)
		return
	}
	fmt.Printf("심볼릭 링크가 가리키는 대상: %s\n", resolvedPath)

	// 심볼릭 링크 삭제
	if err := os.Remove(linkPath); err != nil {
		fmt.Printf("심볼릭 링크 삭제 실패: %v\n", err)
		return
	}
	fmt.Println("심볼릭 링크 삭제 성공!")
}

// ----------------------------
// AdvancedFileOperationsExample: 전체 고급 파일 작업 예제
// ----------------------------

// AdvancedFileOperationsExample은 위의 모든 고급 파일 조작 기능들을 통합적으로 실행합니다.
func AdvancedFileOperationsExample() {
	fmt.Println("==== 고급 파일 조작 예제 시작 ====")

	// 1. 파일 잠금 데모
	lockFilePath := "./data/advanced_lock.txt"
	// 파일 잠금 예제를 위해 파일 관리자 사용 (data 디렉토리는 사전에 생성되어야 함)
	// 만약 "./data" 디렉토리가 없으면 os.MkdirAll로 생성할 수 있습니다.
	os.MkdirAll("./data", 0755)
	DemonstrateFileLocking(lockFilePath)

	// 2. 임시 파일 생성 데모
	DemonstrateTempFileCreation()

	// 3. 파일 권한 관리 데모
	permFilePath := "./data/advanced_perm.txt"
	// 파일이 존재하지 않으면 생성
	ioutil.WriteFile(permFilePath, []byte("파일 권한 관리 예제 데이터\n"), 0644)
	DemonstrateFilePermissionManagement(permFilePath)

	// 4. 심볼릭 링크 처리 데모
	targetPath := "./data/advanced_target.txt"
	linkPath := "./data/advanced_symlink.txt"
	// 대상 파일 생성 (없으면)
	if _, err := os.Stat(targetPath); os.IsNotExist(err) {
		ioutil.WriteFile(targetPath, []byte("심볼릭 링크 대상 파일 내용\n"), 0644)
	}
	DemonstrateSymlinkHandling(targetPath, linkPath)

	fmt.Println("==== 고급 파일 조작 예제 종료 ====")
}
