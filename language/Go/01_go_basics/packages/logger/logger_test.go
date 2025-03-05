package logger

import (
	"bytes"
	"fmt"
	"strings"
	"sync"
	"testing"
)

// TestLogger_Log는 기본 Log 메서드의 동작을 검증합니다.
// K8s 스타일: 단위 테스트로 기능별 동작 확인.
func TestLogger_Log(t *testing.T) {
	// 테스트용 버퍼 출력 생성.
	// K8s 스타일: 테스트 환경을 명확히 설정.
	var buf bytes.Buffer
	log := NewLogger("test-app", &buf)

	// Log 메서드 호출.
	log.Log("기본 로그 메시지")

	// 예상 출력 확인.
	expected := "[test-app] 기본 로그 메시지\n"
	if got := buf.String(); got != expected {
		t.Errorf("Log() 출력 불일치:\n- 기대: %q\n- 실제: %q", expected, got)
	}
}

// TestLogger_Info는 Info 메서드의 동작을 검증합니다.
// K8s 스타일: 로그 레벨별 테스트 분리.
func TestLogger_Info(t *testing.T) {
	var buf bytes.Buffer
	log := NewLogger("test-app", &buf)

	log.Info("정보 메시지")

	expected := "[test-app INFO] 정보 메시지\n"
	if got := buf.String(); got != expected {
		t.Errorf("Info() 출력 불일치:\n- 기대: %q\n- 실제: %q", expected, got)
	}
}

// TestLogger_Error는 Error 메서드의 동작을 검증합니다.
// K8s 스타일: 에러 포함/미포함 케이스 모두 테스트.
func TestLogger_Error(t *testing.T) {
	tests := []struct {
		name     string
		message  string
		err      error
		expected string
	}{
		{
			name:     "WithError",
			message:  "에러 발생",
			err:      fmt.Errorf("샘플 에러"),
			expected: "[test-app ERROR] 에러 발생 (샘플 에러)\n",
		},
		{
			name:     "WithoutError",
			message:  "에러 없음",
			err:      nil,
			expected: "[test-app ERROR] 에러 없음\n",
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			var buf bytes.Buffer
			log := NewLogger("test-app", &buf)

			log.Error(tt.message, tt.err)

			if got := buf.String(); got != tt.expected {
				t.Errorf("Error() 출력 불일치:\n- 기대: %q\n- 실제: %q", tt.expected, got)
			}
		})
	}
}

// TestLogger_WithContext는 컨텍스트 데이터를 포함한 로깅을 검증합니다.
// K8s 스타일: 복잡한 기능 테스트를 테이블 기반으로 수행.
func TestLogger_WithContext(t *testing.T) {
	var buf bytes.Buffer
	log := NewLogger("test-app", &buf)

	// 컨텍스트 포함 Logger 생성.
	contextLog := log.WithContext(map[string]interface{}{
		"user": "alice",
		"time": 12345,
	})
	contextLog.Info("컨텍스트 테스트")

	// 예상 출력 확인: 컨텍스트 데이터가 추가됨.
	expectedPrefix := "[test-app INFO] 컨텍스트 테스트 {"
	if !strings.HasPrefix(buf.String(), expectedPrefix) {
		t.Errorf("WithContext() 출력 불일치:\n- 기대 접두사: %q\n- 실제: %q", expectedPrefix, buf.String())
	}
	if !strings.Contains(buf.String(), "user: alice") || !strings.Contains(buf.String(), "time: 12345") {
		t.Errorf("WithContext() 컨텍스트 누락:\n- 실제: %q", buf.String())
	}
}

// TestLogger_Concurrency는 여러 고루틴에서 Logger의 동시성 안전성을 검증합니다.
// K8s 스타일: 동시성 테스트로 안정성 확인.
func TestLogger_Concurrency(t *testing.T) {
	var buf bytes.Buffer
	log := NewLogger("test-app", &buf)

	// 여러 고루틴에서 로깅 수행.
	var wg sync.WaitGroup
	for i := 0; i < 10; i++ {
		wg.Add(1)
		go func(id int) {
			defer wg.Done()
			log.Info(fmt.Sprintf("고루틴 %d 메시지", id))
		}(i)
	}
	wg.Wait()

	// 출력 줄 수 확인: 10개 메시지가 모두 기록되었는지.
	lines := strings.Split(strings.TrimSpace(buf.String()), "\n")
	if len(lines) != 10 {
		t.Errorf("Concurrency() 출력 줄 수 불일치:\n- 기대: 10\n- 실제: %d", len(lines))
	}

	// 각 줄이 예상 패턴을 따르는지 확인.
	for _, line := range lines {
		if !strings.HasPrefix(line, "[test-app INFO] 고루틴") {
			t.Errorf("Concurrency() 출력 형식 불일치:\n- 실제: %q", line)
		}
	}
}
