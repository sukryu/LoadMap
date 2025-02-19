/*
이 예제는 디렉토리 트리 조작에 관한 고급 기능들을 상세하게 구현합니다.
주요 기능:
1. 재귀적 디렉토리 순회 및 트리 시각화:
   - 지정한 루트 디렉토리의 모든 파일 및 하위 디렉토리를 탐색하고,
     계층 구조를 텍스트 트리 형태로 출력합니다.
2. 디렉토리 동기화:
   - 소스 디렉토리와 대상 디렉토리를 비교하여, 소스에만 존재하는 파일들을 대상 디렉토리로 복사합니다.
3. 변경 감지:
   - 주기적으로 디렉토리의 파일 변경 사항(생성, 수정, 삭제)을 확인하여,
     변경 이벤트를 콘솔에 출력합니다.
각 기능은 실제 업무에서 디렉토리 관리, 백업, 동기화, 변경 감시 등에 유용하게 사용할 수 있습니다.
*/

package examples

import (
	"fmt"
	"io"
	"io/fs"
	"os"
	"path/filepath"
	"sync"
	"time"
)

// ----------------------------
// 1. 재귀적 디렉토리 순회 및 트리 시각화
// ----------------------------

// DirTree는 디렉토리 트리 구조를 표현하는 노드입니다.
type DirTree struct {
	Name     string
	IsDir    bool
	Children []*DirTree
}

// buildDirTree는 주어진 경로부터 재귀적으로 디렉토리 트리를 생성합니다.
func buildDirTree(root string) (*DirTree, error) {
	info, err := os.Stat(root)
	if err != nil {
		return nil, err
	}

	node := &DirTree{
		Name:  info.Name(),
		IsDir: info.IsDir(),
	}

	if info.IsDir() {
		entries, err := os.ReadDir(root)
		if err != nil {
			return nil, err
		}

		for _, entry := range entries {
			childPath := filepath.Join(root, entry.Name())
			childTree, err := buildDirTree(childPath)
			if err != nil {
				// 에러 발생 시 해당 항목은 건너뜁니다.
				continue
			}
			node.Children = append(node.Children, childTree)
		}
	}

	return node, nil
}

// printDirTree는 DirTree 구조체를 텍스트 트리 형식으로 출력합니다.
func printDirTree(node *DirTree, prefix string) {
	fmt.Println(prefix + node.Name)
	if node.IsDir {
		for i, child := range node.Children {
			var newPrefix string
			if i == len(node.Children)-1 {
				fmt.Print(prefix + "└── ")
				newPrefix = prefix + "    "
			} else {
				fmt.Print(prefix + "├── ")
				newPrefix = prefix + "│   "
			}
			printDirTree(child, newPrefix)
		}
	}
}

// DirectoryTreeDemo는 주어진 루트 디렉토리의 트리 구조를 생성하고 출력합니다.
func DirectoryTreeDemo(root string) {
	fmt.Printf("==== 디렉토리 트리 시각화: %s ====\n", root)
	tree, err := buildDirTree(root)
	if err != nil {
		fmt.Printf("디렉토리 트리 생성 실패: %v\n", err)
		return
	}
	printDirTree(tree, "")
	fmt.Println("==== 디렉토리 트리 시각화 종료 ====")
}

// ----------------------------
// 2. 디렉토리 동기화
// ----------------------------

// syncFile copies a single file from src to dst.
func syncFile(src, dst string) error {
	// 원본 파일 열기
	srcFile, err := os.Open(src)
	if err != nil {
		return fmt.Errorf("원본 파일 열기 실패 (%s): %w", src, err)
	}
	defer srcFile.Close()

	// 대상 디렉토리 생성
	dstDir := filepath.Dir(dst)
	if err := os.MkdirAll(dstDir, 0755); err != nil {
		return fmt.Errorf("대상 디렉토리 생성 실패 (%s): %w", dstDir, err)
	}

	// 대상 파일 생성
	dstFile, err := os.Create(dst)
	if err != nil {
		return fmt.Errorf("대상 파일 생성 실패 (%s): %w", dst, err)
	}
	defer dstFile.Close()

	// 데이터 복사
	_, err = io.Copy(dstFile, srcFile)
	if err != nil {
		return fmt.Errorf("파일 복사 오류 (%s -> %s): %w", src, dst, err)
	}
	return nil
}

// SyncDirectories는 srcDir에 존재하지만 dstDir에 없는 파일들을 동기화합니다.
func SyncDirectories(srcDir, dstDir string) error {
	var errors []error

	err := filepath.Walk(srcDir, func(path string, info fs.FileInfo, err error) error {
		if err != nil {
			return err
		}

		// 소스 디렉토리 기준의 상대 경로 계산
		relPath, err := filepath.Rel(srcDir, path)
		if err != nil {
			return err
		}
		dstPath := filepath.Join(dstDir, relPath)

		if info.IsDir() {
			// 대상 디렉토리 생성 (없으면)
			if err := os.MkdirAll(dstPath, 0755); err != nil {
				errors = append(errors, fmt.Errorf("디렉토리 생성 실패 (%s): %w", dstPath, err))
			}
		} else {
			// 파일인 경우, 대상 파일이 없으면 복사
			if _, err := os.Stat(dstPath); os.IsNotExist(err) {
				fmt.Printf("동기화: %s -> %s\n", path, dstPath)
				if err := syncFile(path, dstPath); err != nil {
					errors = append(errors, err)
				}
			}
		}
		return nil
	})

	if err != nil {
		return err
	}

	if len(errors) > 0 {
		// 에러들을 하나의 에러로 집계하여 반환
		return fmt.Errorf("동기화 중 발생한 오류: %v", errors)
	}

	fmt.Println("디렉토리 동기화 완료!")
	return nil
}

// ----------------------------
// 3. 디렉토리 변경 감지
// ----------------------------

// DirChangeEvent는 디렉토리 내 파일의 변경 이벤트를 나타냅니다.
type DirChangeEvent struct {
	Path      string
	Operation string // "created", "modified", "deleted"
	Time      time.Time
}

// DirectoryWatcher는 지정한 디렉토리의 변경 사항을 모니터링합니다.
type DirectoryWatcher struct {
	root     string
	interval time.Duration
	// 파일의 최종 수정 시간을 저장하는 맵
	fileModTimes map[string]time.Time
	// 이벤트 채널을 통해 변경 이벤트를 전달합니다.
	events chan DirChangeEvent
	done   chan struct{}
	mu     sync.RWMutex
}

// NewDirectoryWatcher는 새로운 디렉토리 감시자를 생성합니다.
func NewDirectoryWatcher(root string, interval time.Duration) *DirectoryWatcher {
	return &DirectoryWatcher{
		root:         root,
		interval:     interval,
		fileModTimes: make(map[string]time.Time),
		events:       make(chan DirChangeEvent, 100),
		done:         make(chan struct{}),
	}
}

// StartMonitoring은 디렉토리 변경 감시를 시작합니다.
func (dw *DirectoryWatcher) StartMonitoring() {
	go func() {
		ticker := time.NewTicker(dw.interval)
		defer ticker.Stop()

		for {
			select {
			case <-dw.done:
				return
			case <-ticker.C:
				dw.scanChanges()
			}
		}
	}()
}

// StopMonitoring은 감시를 중지합니다.
func (dw *DirectoryWatcher) StopMonitoring() {
	close(dw.done)
	close(dw.events)
}

// scanChanges는 디렉토리를 순회하며 변경 사항을 감지합니다.
func (dw *DirectoryWatcher) scanChanges() {
	dw.mu.Lock()
	defer dw.mu.Unlock()

	filepath.Walk(dw.root, func(path string, info fs.FileInfo, err error) error {
		if err != nil {
			return nil // 오류 발생 시 해당 항목 건너뛰기
		}
		// 디렉토리는 건너뜁니다.
		if info.IsDir() {
			return nil
		}
		lastMod, exists := dw.fileModTimes[path]
		if !exists {
			// 새로운 파일 생성 이벤트
			dw.fileModTimes[path] = info.ModTime()
			dw.events <- DirChangeEvent{
				Path:      path,
				Operation: "created",
				Time:      time.Now(),
			}
		} else if info.ModTime().After(lastMod) {
			// 수정 이벤트
			dw.fileModTimes[path] = info.ModTime()
			dw.events <- DirChangeEvent{
				Path:      path,
				Operation: "modified",
				Time:      time.Now(),
			}
		}
		return nil
	})

	// 삭제된 파일 감지: 현재 맵에 있지만 실제로는 존재하지 않는 파일 제거
	for path, modTime := range dw.fileModTimes {
		if _, err := os.Stat(path); os.IsNotExist(err) {
			delete(dw.fileModTimes, path)
			dw.events <- DirChangeEvent{
				Path:      path,
				Operation: "deleted",
				Time:      time.Now(),
			}
		} else if err != nil {
			// 다른 오류는 무시
			_ = modTime
		}
	}
}

// DirectoryChangeDemo는 디렉토리 변경 감지 기능을 데모합니다.
func DirectoryChangeDemo(root string, duration time.Duration) {
	fmt.Printf("==== 디렉토리 변경 감지 데모 시작: %s ====\n", root)
	watcher := NewDirectoryWatcher(root, 2*time.Second)
	watcher.StartMonitoring()

	// 변경 이벤트를 처리하는 고루틴
	go func() {
		for event := range watcher.events {
			fmt.Printf("변경 이벤트 - 경로: %s, 작업: %s, 시간: %s\n", event.Path, event.Operation, event.Time.Format(time.RFC3339))
		}
	}()

	// 데모 실행 시간 동안 대기
	time.Sleep(duration)
	watcher.StopMonitoring()
	fmt.Println("==== 디렉토리 변경 감지 데모 종료 ====")
}

// ----------------------------
// DirectoryTreeDemo와 SyncDemo, ChangeDetectionDemo 통합 데모
// ----------------------------

// DirectoryTreeAndSyncDemo는 디렉토리 트리 시각화와 동기화 기능을 데모합니다.
func DirectoryTreeAndSyncDemo(srcDir, dstDir string) {
	fmt.Println("==== 디렉토리 트리 및 동기화 데모 시작 ====")
	fmt.Println("\n[디렉토리 트리 시각화 - 소스 디렉토리]")
	DirectoryTreeDemo(srcDir)

	// 동기화 실행
	if err := SyncDirectories(srcDir, dstDir); err != nil {
		fmt.Printf("디렉토리 동기화 중 오류 발생: %v\n", err)
	} else {
		fmt.Println("디렉토리 동기화 성공!")
		fmt.Println("\n[디렉토리 트리 시각화 - 대상 디렉토리]")
		DirectoryTreeDemo(dstDir)
	}
	fmt.Println("==== 디렉토리 트리 및 동기화 데모 종료 ====")
}

// DirectoryTreeDemo, SyncDirectories, DirectoryChangeDemo를 포함한 최종 데모 함수
func DirectoryTreeOperationsDemo() {
	// 데모를 위한 기본 디렉토리 설정
	srcDir := "./data/dir_demo_src"
	dstDir := "./data/dir_demo_dst"

	// 소스 디렉토리 및 일부 파일 생성 (데모용)
	os.MkdirAll(srcDir, 0755)
	os.MkdirAll(dstDir, 0755)
	// 예제 파일 생성
	os.WriteFile(filepath.Join(srcDir, "file1.txt"), []byte("파일1 내용\n"), 0644)
	os.WriteFile(filepath.Join(srcDir, "file2.txt"), []byte("파일2 내용\n"), 0644)
	os.MkdirAll(filepath.Join(srcDir, "subdir"), 0755)
	os.WriteFile(filepath.Join(srcDir, "subdir", "file3.txt"), []byte("파일3 내용 (서브디렉토리)\n"), 0644)

	// 디렉토리 트리 시각화 및 동기화 데모
	DirectoryTreeAndSyncDemo(srcDir, dstDir)

	// 디렉토리 변경 감지 데모: 15초 동안 감시
	DirectoryChangeDemo(srcDir, 15*time.Second)
}
