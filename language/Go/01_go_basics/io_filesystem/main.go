package main

import (
	"bufio"
	"fmt"
	"io/ioutil"
	"os"
	"path/filepath"
	"sync"
	"time"
)

// =============================================================
// Chapter 1: 기본 파일 작업
// Go에서 파일을 생성하고 읽고 쓰는 기본적인 작업을 다룹니다.
// =============================================================

// FileManager는 파일 작업을 관리하는 구조체입니다.
type FileManager struct {
	basePath string
	mu       sync.Mutex
}

// NewFileManager는 새로운 파일 관리자를 생성합니다.
func NewFileManager(basePath string) (*FileManager, error) {
	// 기본 디렉토리가 없으면 생성
	if err := os.MkdirAll(basePath, 0755); err != nil {
		return nil, fmt.Errorf("디렉토리 생성 실패: %w", err)
	}

	return &FileManager{
		basePath: basePath,
	}, nil
}

// WriteFile은 파일에 데이터를 씁니다.
func (fm *FileManager) WriteFile(filename string, data []byte) error {
	fm.mu.Lock()
	defer fm.mu.Unlock()

	fullPath := filepath.Join(fm.basePath, filename)
	return ioutil.WriteFile(fullPath, data, 0644)
}

// ReadFile은 파일의 내용을 읽습니다.
func (fm *FileManager) ReadFile(filename string) ([]byte, error) {
	fullPath := filepath.Join(fm.basePath, filename)
	return ioutil.ReadFile(fullPath)
}

// =============================================================
// Chapter 2: 버퍼 I/O
// 대용량 파일을 효율적으로 처리하기 위한 버퍼 I/O 작업을 다룹니다.
// =============================================================

// BufferedFileWriter는 버퍼를 사용하는 파일 쓰기를 구현합니다.
type BufferedFileWriter struct {
	file   *os.File
	writer *bufio.Writer
}

// NewBufferedFileWriter는 새로운 버퍼 파일 쓰기 객체를 생성합니다.
func NewBufferedFileWriter(filename string) (*BufferedFileWriter, error) {
	file, err := os.Create(filename)
	if err != nil {
		return nil, err
	}

	return &BufferedFileWriter{
		file:   file,
		writer: bufio.NewWriter(file),
	}, nil
}

// Write는 버퍼를 통해 데이터를 씁니다.
func (bw *BufferedFileWriter) Write(data []byte) error {
	_, err := bw.writer.Write(data)
	return err
}

// Close는 버퍼를 플러시하고 파일을 닫습니다.
func (bw *BufferedFileWriter) Close() error {
	if err := bw.writer.Flush(); err != nil {
		return err
	}
	return bw.file.Close()
}

// =============================================================
// Chapter 3: 디렉토리 작업
// 디렉토리 생성, 순회, 파일 검색 등의 작업을 다룹니다.
// =============================================================

// DirectoryScanner는 디렉토리를 스캔하고 파일을 찾는 기능을 제공합니다.
type DirectoryScanner struct {
	root      string
	filters   []FileFilter
	recursive bool
}

// FileFilter는 파일 필터링 함수 타입입니다.
type FileFilter func(os.FileInfo) bool

// NewDirectoryScanner는 새로운 디렉토리 스캐너를 생성합니다.
func NewDirectoryScanner(root string, recursive bool) *DirectoryScanner {
	return &DirectoryScanner{
		root:      root,
		recursive: recursive,
		filters:   make([]FileFilter, 0),
	}
}

// AddFilter는 파일 필터를 추가합니다.
func (ds *DirectoryScanner) AddFilter(filter FileFilter) {
	ds.filters = append(ds.filters, filter)
}

// Scan은 디렉토리를 스캔하고 조건에 맞는 파일 목록을 반환합니다.
func (ds *DirectoryScanner) Scan() ([]string, error) {
	var files []string

	walkFn := func(path string, info os.FileInfo, err error) error {
		if err != nil {
			return err
		}

		// 디렉토리이고 재귀 검색이 아닌 경우 건너뛰기
		if info.IsDir() {
			if !ds.recursive && path != ds.root {
				return filepath.SkipDir
			}
			return nil
		}

		// 모든 필터 적용
		for _, filter := range ds.filters {
			if !filter(info) {
				return nil
			}
		}

		files = append(files, path)
		return nil
	}

	if err := filepath.Walk(ds.root, walkFn); err != nil {
		return nil, err
	}

	return files, nil
}

// =============================================================
// Chapter 4: 파일 모니터링
// 파일 변경 사항을 모니터링하고 이벤트를 처리합니다.
// =============================================================

// FileEvent는 파일 시스템 이벤트를 나타냅니다.
type FileEvent struct {
	Path      string
	Operation string
	Time      time.Time
}

// FileWatcher는 파일 변경 사항을 감시합니다.
type FileWatcher struct {
	path    string
	events  chan FileEvent
	done    chan struct{}
	files   map[string]time.Time
	mu      sync.RWMutex
	watches []string
}

// NewFileWatcher는 새로운 파일 감시자를 생성합니다.
func NewFileWatcher(path string) *FileWatcher {
	return &FileWatcher{
		path:    path,
		events:  make(chan FileEvent, 100),
		done:    make(chan struct{}),
		files:   make(map[string]time.Time),
		watches: make([]string, 0),
	}
}

// Start는 파일 감시를 시작합니다.
func (fw *FileWatcher) Start() {
	go fw.watch()
}

// Stop은 파일 감시를 중지합니다.
func (fw *FileWatcher) Stop() {
	close(fw.done)
}

// watch는 주기적으로 파일 변경 사항을 확인합니다.
func (fw *FileWatcher) watch() {
	ticker := time.NewTicker(time.Second)
	defer ticker.Stop()

	for {
		select {
		case <-fw.done:
			return
		case <-ticker.C:
			fw.checkChanges()
		}
	}
}

// checkChanges는 파일 변경 사항을 확인하고 이벤트를 발생시킵니다.
func (fw *FileWatcher) checkChanges() {
	fw.mu.Lock()
	defer fw.mu.Unlock()

	for _, path := range fw.watches {
		info, err := os.Stat(path)
		if err != nil {
			// 파일이 삭제된 경우
			if os.IsNotExist(err) {
				if _, exists := fw.files[path]; exists {
					fw.events <- FileEvent{
						Path:      path,
						Operation: "deleted",
						Time:      time.Now(),
					}
					delete(fw.files, path)
				}
			}
			continue
		}

		modTime := info.ModTime()
		lastModTime, exists := fw.files[path]
		if !exists {
			// 새로운 파일
			fw.events <- FileEvent{
				Path:      path,
				Operation: "created",
				Time:      time.Now(),
			}
		} else if modTime.After(lastModTime) {
			// 파일 수정
			fw.events <- FileEvent{
				Path:      path,
				Operation: "modified",
				Time:      time.Now(),
			}
		}

		fw.files[path] = modTime
	}
}

// AddWatch는 감시할 파일을 추가합니다.
func (fw *FileWatcher) AddWatch(path string) {
	fw.mu.Lock()
	defer fw.mu.Unlock()

	fw.watches = append(fw.watches, path)
	if info, err := os.Stat(path); err == nil {
		fw.files[path] = info.ModTime()
	}
}

// =============================================================
// Chapter 5: 파일 처리 파이프라인
// 파일을 읽고 처리하는 파이프라인을 구현합니다.
// =============================================================

// FilePipeline은 파일 처리 파이프라인을 구현합니다.
type FilePipeline struct {
	input  chan string
	output chan []byte
	done   chan struct{}
	wg     sync.WaitGroup
}

// NewFilePipeline은 새로운 파일 처리 파이프라인을 생성합니다.
func NewFilePipeline() *FilePipeline {
	return &FilePipeline{
		input:  make(chan string),
		output: make(chan []byte),
		done:   make(chan struct{}),
	}
}

// Process는 파일을 처리하는 파이프라인을 시작합니다.
func (fp *FilePipeline) Process(workers int) {
	// 워커 생성
	for i := 0; i < workers; i++ {
		fp.wg.Add(1)
		go fp.worker()
	}

	// 완료 대기
	go func() {
		fp.wg.Wait()
		close(fp.output)
	}()
}

// worker는 파일을 읽고 처리합니다.
func (fp *FilePipeline) worker() {
	defer fp.wg.Done()

	for path := range fp.input {
		select {
		case <-fp.done:
			return
		default:
			data, err := ioutil.ReadFile(path)
			if err != nil {
				fmt.Printf("파일 읽기 오류: %v\n", err)
				continue
			}

			// 처리된 데이터 전송
			fp.output <- data
		}
	}
}

func main() {
	// 파일 관리자 생성
	fm, err := NewFileManager("./data")
	if err != nil {
		fmt.Printf("파일 관리자 생성 실패: %v\n", err)
		return
	}

	// 파일 쓰기 예제
	data := []byte("Hello, File I/O!")
	if err := fm.WriteFile("test.txt", data); err != nil {
		fmt.Printf("파일 쓰기 실패: %v\n", err)
		return
	}

	// 버퍼 파일 쓰기 예제
	bw, err := NewBufferedFileWriter("large_file.txt")
	if err != nil {
		fmt.Printf("버퍼 파일 쓰기 객체 생성 실패: %v\n", err)
		return
	}
	defer bw.Close()

	// 디렉토리 스캔 예제
	scanner := NewDirectoryScanner("./data", true)
	scanner.AddFilter(func(info os.FileInfo) bool {
		return !info.IsDir() // 파일만 선택
	})

	files, err := scanner.Scan()
	if err != nil {
		fmt.Printf("디렉토리 스캔 실패: %v\n", err)
		return
	}
	fmt.Printf("%s", files)

	// 파일 감시 예제
	watcher := NewFileWatcher("./data")
	watcher.Start()
	defer watcher.Stop()

	// 파일 처리 파이프라인 예제
	pipeline := NewFilePipeline()
	pipeline.Process(4)

	// 이벤트 처리
	go func() {
		for event := range watcher.events {
			fmt.Printf("파일 이벤트: %+v\n", event)
		}
	}()

	// 테스트를 위한 대기
	time.Sleep(time.Second * 5)
}
