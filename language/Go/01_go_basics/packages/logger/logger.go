package logger

import (
	"fmt"
	"io"
	"os"
	"sync"
)

// Logger는 사용자 정의 로깅 기능을 제공하는 구조체입니다.
// K8s 스타일: 로깅 상태와 설정을 캡슐화하여 모듈화.
type Logger struct {
	appName string     // 애플리케이션 식별자.
	output  io.Writer  // 로그 출력 대상 (예: os.Stdout).
	mu      sync.Mutex // 동시성 안전성을 위한 뮤텍스.
}

// NewLogger는 새로운 Logger 인스턴스를 생성합니다.
// appName: 로그에 포함될 애플리케이션 이름.
// output: 로그 출력 대상 (기본값: os.Stdout).
// K8s 스타일: 생성자 함수로 초기화 캡슐화, 기본값 제공.
func NewLogger(appName string, output io.Writer) *Logger {
	if output == nil {
		output = os.Stdout // 기본 출력으로 표준 출력 사용.
	}
	return &Logger{
		appName: appName,
		output:  output,
	}
}

// Log는 기본 로그 메시지를 출력합니다.
// K8s 스타일: 간단한 로깅 메서드로 최소 기능 제공.
func (l *Logger) Log(message string) {
	l.mu.Lock()
	defer l.mu.Unlock() // 동시성 안전성 보장.
	// 로그 형식: [appName] message
	fmt.Fprintf(l.output, "[%s] %s\n", l.appName, message)
}

// Info는 정보 레벨 로그 메시지를 출력합니다.
// K8s 스타일: 로그 레벨을 명시하여 메시지 구분.
func (l *Logger) Info(message string) {
	l.mu.Lock()
	defer l.mu.Unlock()
	// 로그 형식: [appName INFO] message
	fmt.Fprintf(l.output, "[%s INFO] %s\n", l.appName, message)
}

// Error는 에러 레벨 로그 메시지를 출력하며 에러를 포함합니다.
// K8s 스타일: 에러와 함께 메시지를 구조화.
func (l *Logger) Error(message string, err error) {
	l.mu.Lock()
	defer l.mu.Unlock()
	// 로그 형식: [appName ERROR] message (error)
	if err != nil {
		fmt.Fprintf(l.output, "[%s ERROR] %s (%v)\n", l.appName, message, err)
	} else {
		fmt.Fprintf(l.output, "[%s ERROR] %s\n", l.appName, message)
	}
}

// WithContext는 컨텍스트 데이터를 포함한 새로운 Logger 인스턴스를 반환합니다.
// K8s 스타일: 메서드 체이닝 지원으로 유연성 제공.
func (l *Logger) WithContext(context map[string]interface{}) *Logger {
	l.mu.Lock()
	defer l.mu.Unlock()
	// 기존 Logger의 복사본 생성.
	newLogger := &Logger{
		appName: l.appName,
		output:  l.output,
	}
	// 컨텍스트 데이터를 메시지에 포함하도록 출력 재정의.
	newLogger.output = &contextWriter{
		writer:  l.output,
		context: context,
	}
	return newLogger
}

// contextWriter는 컨텍스트 데이터를 로그에 포함시키는 io.Writer 래퍼입니다.
// K8s 스타일: 내부 구조체로 로깅 로직 확장.
type contextWriter struct {
	writer  io.Writer
	context map[string]interface{}
}

// Write는 컨텍스트 데이터를 로그 메시지에 추가하여 출력합니다.
// K8s 스타일: io.Writer 인터페이스 구현으로 표준화.
func (cw *contextWriter) Write(p []byte) (n int, err error) {
	// 컨텍스트 데이터를 문자열로 변환.
	contextStr := " {"
	for k, v := range cw.context {
		contextStr += fmt.Sprintf("%s: %v, ", k, v)
	}
	if len(cw.context) > 0 {
		contextStr = contextStr[:len(contextStr)-2] // 마지막 ", " 제거.
	}
	contextStr += "}"
	// 원본 메시지에 컨텍스트 추가.
	fullMessage := fmt.Sprintf("%s%s", string(p[:len(p)-1]), contextStr) // 개행 제거 후 추가.
	return fmt.Fprintf(cw.writer, "%s\n", fullMessage)
}
