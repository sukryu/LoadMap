/*
이 예제는 Go 프로그램에서 발생할 수 있는 다양한 메모리 누수 패턴과
이를 해결하는 방법을 설명합니다. 메모리 누수는 장기 실행 애플리케이션에서
특히 문제가 될 수 있으며, 조기 발견과 예방이 중요합니다.

주요 내용:
1. 고루틴 누수 패턴과 해결책
2. 채널 관련 메모리 누수
3. 슬라이스와 맵의 메모리 누수
4. 타이머/티커 관련 누수

실행 방법:
go run memory_leaks.go
*/

package examples

import (
	"context"
	"fmt"
	"runtime"
	"sync"
	"time"
)

// =============================================================
// Chapter 1: 고루틴 누수
// 고루틴이 적절히 종료되지 않아 발생하는 메모리 누수를 다룹니다.
// =============================================================

// LeakyGoroutineExample은 고루틴 누수가 발생하는 예를 보여줍니다.
type LeakyGoroutineExample struct {
	done    chan struct{}
	cleanup chan struct{}
	wg      sync.WaitGroup
}

// NewLeakyGoroutineExample은 새로운 고루틴 누수 예제를 생성합니다.
func NewLeakyGoroutineExample() *LeakyGoroutineExample {
	return &LeakyGoroutineExample{
		done:    make(chan struct{}),
		cleanup: make(chan struct{}),
	}
}

// leakyWorker는 누수가 발생할 수 있는 고루틴을 시작합니다.
func (l *LeakyGoroutineExample) leakyWorker() {
	// 이 고루틴은 done 채널이 닫히지 않으면 영원히 실행됩니다
	for {
		select {
		case <-l.done:
			return
		default:
			time.Sleep(time.Second)
		}
	}
}

// fixedWorker는 컨텍스트를 사용하여 적절히 종료되는 고루틴입니다.
func (l *LeakyGoroutineExample) fixedWorker(ctx context.Context) {
	defer l.wg.Done()

	for {
		select {
		case <-ctx.Done():
			return
		case <-time.After(time.Second):
			// 작업 수행
		}
	}
}

// =============================================================
// Chapter 2: 채널 관련 메모리 누수
// 채널 사용 시 발생할 수 있는 메모리 누수를 설명합니다.
// =============================================================

// ChannelLeakExample은 채널 관련 메모리 누수를 시뮬레이션합니다.
type ChannelLeakExample struct {
	dataChan chan []byte
	quitChan chan struct{}
}

// NewChannelLeakExample은 새로운 채널 누수 예제를 생성합니다.
func NewChannelLeakExample() *ChannelLeakExample {
	return &ChannelLeakExample{
		dataChan: make(chan []byte),
		quitChan: make(chan struct{}),
	}
}

// leakyDataProcessor는 채널 누수가 발생할 수 있는 처리를 시뮬레이션합니다.
func (c *ChannelLeakExample) leakyDataProcessor() {
	for {
		data := make([]byte, 1024*1024) // 1MB
		select {
		case c.dataChan <- data: // 채널이 가득 차면 블록됨
		default:
			// 데이터를 처리할 수 없는 경우 메모리 누수 발생
		}
	}
}

// fixedDataProcessor는 적절한 채널 처리를 보여줍니다.
func (c *ChannelLeakExample) fixedDataProcessor(ctx context.Context) {
	for {
		select {
		case <-ctx.Done():
			return
		case data := <-c.dataChan:
			// 데이터 처리
			_ = data
		}
	}
}

// =============================================================
// Chapter 3: 슬라이스와 맵의 메모리 누수
// 슬라이스와 맵 사용 시 발생하는 메모리 누수를 다룹니다.
// =============================================================

// SliceLeakExample은 슬라이스 관련 메모리 누수를 시뮬레이션합니다.
type SliceLeakExample struct {
	largeData [][]byte
	cache     map[string][]byte
	mu        sync.RWMutex
}

// NewSliceLeakExample은 새로운 슬라이스 누수 예제를 생성합니다.
func NewSliceLeakExample() *SliceLeakExample {
	return &SliceLeakExample{
		largeData: make([][]byte, 0),
		cache:     make(map[string][]byte),
	}
}

// leakySliceOperation은 슬라이스 누수가 발생하는 작업을 보여줍니다.
func (s *SliceLeakExample) leakySliceOperation() {
	original := make([]byte, 1024*1024*100) // 100MB
	// 잘못된 슬라이싱 - 전체 배열이 메모리에 유지됨
	s.largeData = append(s.largeData, original[10:20])
}

// fixedSliceOperation은 올바른 슬라이스 처리를 보여줍니다.
func (s *SliceLeakExample) fixedSliceOperation() {
	original := make([]byte, 1024*1024*100)
	// 필요한 부분만 복사
	needed := make([]byte, 10)
	copy(needed, original[10:20])
	s.largeData = append(s.largeData, needed)
}

// =============================================================
// Chapter 4: 타이머와 티커 누수
// 타이머와 티커 사용 시 발생하는 메모리 누수를 설명합니다.
// =============================================================

// TimerLeakExample은 타이머 관련 메모리 누수를 시뮬레이션합니다.
type TimerLeakExample struct {
	timers []*time.Timer
	mu     sync.Mutex
}

// NewTimerLeakExample은 새로운 타이머 누수 예제를 생성합니다.
func NewTimerLeakExample() *TimerLeakExample {
	return &TimerLeakExample{
		timers: make([]*time.Timer, 0),
	}
}

// leakyTimerOperation은 타이머 누수가 발생하는 작업을 보여줍니다.
func (t *TimerLeakExample) leakyTimerOperation() {
	// 타이머 생성 후 정리하지 않음
	timer := time.NewTimer(time.Hour)
	t.mu.Lock()
	t.timers = append(t.timers, timer)
	t.mu.Unlock()
}

// fixedTimerOperation은 올바른 타이머 처리를 보여줍니다.
func (t *TimerLeakExample) fixedTimerOperation() {
	timer := time.NewTimer(time.Hour)
	t.mu.Lock()
	t.timers = append(t.timers, timer)
	t.mu.Unlock()

	go func() {
		<-timer.C
		t.mu.Lock()
		timer.Stop()
		// 타이머 제거
		for i, tm := range t.timers {
			if tm == timer {
				t.timers = append(t.timers[:i], t.timers[i+1:]...)
				break
			}
		}
		t.mu.Unlock()
	}()
}

// =============================================================
// Chapter 5: 메모리 누수 감지와 디버깅
// 메모리 누수를 감지하고 디버깅하는 도구와 기법을 설명합니다.
// =============================================================

// MemoryLeakDetector는 메모리 사용량을 모니터링합니다.
type MemoryLeakDetector struct {
	snapshots []runtime.MemStats
	interval  time.Duration
}

// NewMemoryLeakDetector는 새로운 메모리 누수 감지기를 생성합니다.
func NewMemoryLeakDetector(interval time.Duration) *MemoryLeakDetector {
	return &MemoryLeakDetector{
		snapshots: make([]runtime.MemStats, 0),
		interval:  interval,
	}
}

// StartMonitoring은 메모리 사용량 모니터링을 시작합니다.
func (m *MemoryLeakDetector) StartMonitoring(ctx context.Context) {
	ticker := time.NewTicker(m.interval)
	defer ticker.Stop()

	for {
		select {
		case <-ctx.Done():
			return
		case <-ticker.C:
			var stats runtime.MemStats
			runtime.ReadMemStats(&stats)
			m.snapshots = append(m.snapshots, stats)
			m.analyzeMemoryUsage()
		}
	}
}

// analyzeMemoryUsage는 메모리 사용량 패턴을 분석합니다.
func (m *MemoryLeakDetector) analyzeMemoryUsage() {
	if len(m.snapshots) < 2 {
		return
	}

	latest := m.snapshots[len(m.snapshots)-1]
	previous := m.snapshots[len(m.snapshots)-2]

	// 메모리 증가율 계산
	increase := float64(latest.HeapAlloc-previous.HeapAlloc) / float64(previous.HeapAlloc) * 100

	if increase > 10 { // 10% 이상 증가
		fmt.Printf("경고: 메모리 사용량이 %.2f%% 증가했습니다.\n", increase)
		fmt.Printf("현재 힙 크기: %d MB\n", latest.HeapAlloc/1024/1024)
	}
}

// RunMemoryLeakDemo demonstrates various memory leak scenarios
func RunMemoryLeakDemo() {
	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	// 메모리 누수 감지기 시작
	detector := NewMemoryLeakDetector(time.Second)
	go detector.StartMonitoring(ctx)

	// 다양한 메모리 누수 시나리오 실행
	leakyGoroutine := NewLeakyGoroutineExample()
	channelLeak := NewChannelLeakExample()
	sliceLeak := NewSliceLeakExample()
	timerLeak := NewTimerLeakExample()

	// 의도적으로 메모리 누수 발생
	for i := 0; i < 5; i++ {
		go leakyGoroutine.leakyWorker()
		go channelLeak.leakyDataProcessor()
		sliceLeak.leakySliceOperation()
		timerLeak.leakyTimerOperation()
		time.Sleep(time.Second)
	}

	// 수정된 버전 실행
	for i := 0; i < 5; i++ {
		go leakyGoroutine.fixedWorker(ctx)
		go channelLeak.fixedDataProcessor(ctx)
		sliceLeak.fixedSliceOperation()
		timerLeak.fixedTimerOperation()
		time.Sleep(time.Second)
	}

	// 결과 대기
	<-ctx.Done()
}

/*
메모리 누수 방지 가이드라인:

1. 고루틴 관리
   - context 사용하여 취소 가능하게 구현
   - WaitGroup으로 완료 대기
   - 고루틴 수 모니터링

2. 채널 처리
   - 버퍼 크기 적절히 설정
   - select로 타임아웃 처리
   - 채널 명시적 닫기

3. 슬라이스/맵 관리
   - 큰 배열의 부분 참조 시 복사
   - 주기적인 맵 클리닝
   - 적절한 초기 용량 설정

4. 타이머/티커 관리
   - 사용 후 반드시 Stop() 호출
   - 전역 타이머 풀 사용 고려
   - 주기적인 정리 루틴 구현

메모리 누수 디버깅:

1. 프로파일링 도구
   - pprof 사용
   - go tool trace 활용
   - 주기적인 메모리 덤프 분석

2. 모니터링
   - 메모리 사용량 추적
   - 고루틴 수 모니터링
   - GC 통계 분석

3. 디버깅 전략
   - 점진적 메모리 증가 패턴 확인
   - 메모리 할당 지점 식별
   - 참조 체인 분석
*/
