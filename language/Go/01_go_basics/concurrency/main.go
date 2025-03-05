package main

import (
	"context"
	"fmt"
	"sync"
	"time"
)

// =============================================================
// Chapter 1: 기본 고루틴과 채널
// Go의 동시성 프로그래밍의 기초를 다룹니다.
// =============================================================

func basicGoroutineExample() {
	// 간단한 고루틴 실행.
	// K8s 스타일: 동작 목적을 명확히 주석으로 설명.
	go func() {
		fmt.Println("고루틴에서 실행됨")
	}()

	// 메인 고루틴이 너무 빨리 종료되지 않도록 대기.
	time.Sleep(time.Millisecond * 100)
}

func basicChannelExample() {
	// 버퍼가 없는 채널 생성.
	// K8s 스타일: 채널 용량과 목적을 명시.
	ch := make(chan string)

	// 고루틴에서 채널로 데이터 전송.
	go func() {
		ch <- "Hello from goroutine!"
	}()

	// 채널에서 데이터 수신.
	message := <-ch
	fmt.Println("받은 메시지:", message)
}

// ChannelCloser는 채널 닫기와 에러 전파를 관리하는 구조체입니다.
// K8s 스타일: 관련 로직을 구조체로 묶어 모듈화.
type ChannelCloser struct {
	wg *sync.WaitGroup
}

// NewChannelCloser는 새로운 ChannelCloser 인스턴스를 생성합니다.
// K8s 스타일: 생성자 함수로 초기화 캡슐화.
func NewChannelCloser() *ChannelCloser {
	return &ChannelCloser{
		wg: &sync.WaitGroup{},
	}
}

// CloseChannelExample은 채널 닫기(close)와 안전한 수신을 보여줍니다.
// K8s 스타일: 동작과 주의사항을 상세히 설명.
func (cc *ChannelCloser) CloseChannelExample(numMessages int) {
	// 메시지 전송을 위한 버퍼 채널 생성.
	// K8s 스타일: 버퍼 크기로 성능 최적화.
	msgChan := make(chan string, numMessages)

	// 생산자 고루틴: 메시지 전송 후 채널 닫기.
	cc.wg.Add(1)
	go func() {
		defer cc.wg.Done()
		defer close(msgChan) // 채널 닫기로 수신자에게 EOF 신호 전달.
		// K8s 스타일: 리소스 정리 보장.
		for i := 0; i < numMessages; i++ {
			msgChan <- fmt.Sprintf("메시지 %d", i+1)
			time.Sleep(100 * time.Millisecond)
		}
		fmt.Println("생산자: 모든 메시지 전송 완료, 채널 닫음")
	}()

	// 소비자 고루틴: 채널에서 메시지 수신.
	cc.wg.Add(1)
	go func() {
		defer cc.wg.Done()
		for msg := range msgChan { // 채널 닫기 감지.
			fmt.Printf("소비자: 수신 - %s\n", msg)
		}
		fmt.Println("소비자: 채널 닫힘 확인")
	}()

	cc.wg.Wait()
}

// ErrorPropagationExample은 채널을 통한 에러 전파를 보여줍니다.
// K8s 스타일: 에러 처리를 명확히 구분.
func (cc *ChannelCloser) ErrorPropagationExample() error {
	// 결과와 에러를 전달할 채널 생성.
	type Result struct {
		Value int
		Err   error
	}
	resultChan := make(chan Result, 1)

	// 작업 고루틴: 에러 발생 시뮬레이션.
	cc.wg.Add(1)
	go func() {
		defer cc.wg.Done()
		defer close(resultChan) // 작업 완료 후 채널 닫기.
		// K8s 스타일: 작업 상태와 에러를 함께 전달.
		time.Sleep(500 * time.Millisecond)
		resultChan <- Result{
			Value: 0,
			Err:   fmt.Errorf("작업 실패: 의도적 에러 발생"),
		}
	}()

	// 결과 처리.
	result := <-resultChan
	if result.Err != nil {
		fmt.Printf("에러 수신: %v\n", result.Err)
		return result.Err
	}
	fmt.Printf("성공: 값 %d\n", result.Value)
	return nil
}

// =============================================================
// Chapter 2: 버퍼 채널과 채널 방향
// 채널의 고급 기능과 방향성을 설명합니다.
// =============================================================

func bufferedChannelExample() {
	// 버퍼가 있는 채널 생성 (크기: 2).
	// K8s 스타일: 버퍼 크기와 동작을 설명.
	bufCh := make(chan int, 2)

	// 채널이 가득 차지 않았으므로 블로킹되지 않음.
	bufCh <- 1
	bufCh <- 2

	// 채널에서 데이터 읽기.
	fmt.Println("첫 번째 값:", <-bufCh)
	fmt.Println("두 번째 값:", <-bufCh)
}

// Send는 데이터를 보내기만 하는 채널을 매개변수로 받습니다.
// K8s 스타일: 채널 방향을 명확히 구분.
func send(ch chan<- int) {
	for i := 0; i < 3; i++ {
		ch <- i
	}
	close(ch) // 작업 완료 후 채널 닫기.
}

// Receive는 데이터를 받기만 하는 채널을 매개변수로 받습니다.
func receive(ch <-chan int) {
	for num := range ch {
		fmt.Println("받은 숫자:", num)
	}
}

// =============================================================
// Chapter 3: select 문과 타임아웃 처리
// 여러 채널을 동시에 처리하는 방법을 설명합니다.
// =============================================================

func selectExample() {
	ch1 := make(chan string)
	ch2 := make(chan string)

	// 첫 번째 고루틴.
	go func() {
		time.Sleep(time.Second)
		ch1 <- "채널 1의 메시지"
	}()

	// 두 번째 고루틴.
	go func() {
		time.Sleep(time.Second * 2)
		ch2 <- "채널 2의 메시지"
	}()

	// select를 사용한 다중 채널 처리.
	for i := 0; i < 2; i++ {
		select {
		case msg1 := <-ch1:
			fmt.Println(msg1)
		case msg2 := <-ch2:
			fmt.Println(msg2)
		case <-time.After(3 * time.Second):
			fmt.Println("타임아웃!")
			return
		}
	}
}

// =============================================================
// Chapter 4: WaitGroup을 사용한 동기화
// 여러 고루틴의 완료를 기다리는 방법을 설명합니다.
// =============================================================

func waitGroupExample() {
	var wg sync.WaitGroup

	// 3개의 고루틴 실행.
	for i := 0; i < 3; i++ {
		wg.Add(1) // 카운터 증가.
		go func(id int) {
			defer wg.Done() // 작업 완료 시 카운터 감소.
			time.Sleep(time.Second)
			fmt.Printf("고루틴 %d 완료\n", id)
		}(i)
	}

	wg.Wait() // 모든 고루틴이 완료될 때까지 대기.
	fmt.Println("모든 고루틴 작업 완료")
}

// =============================================================
// Chapter 5: Mutex를 사용한 상태 관리
// 공유 자원에 대한 안전한 접근 방법을 설명합니다.
// =============================================================

type Counter struct {
	mu    sync.Mutex
	value int
}

func (c *Counter) Increment() {
	c.mu.Lock()
	defer c.mu.Unlock()
	c.value++
}

func (c *Counter) Value() int {
	c.mu.Lock()
	defer c.mu.Unlock()
	return c.value
}

func mutexExample() {
	counter := &Counter{}
	var wg sync.WaitGroup

	// 여러 고루틴에서 동시에 카운터 증가.
	for i := 0; i < 1000; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			counter.Increment()
		}()
	}

	wg.Wait()
	fmt.Printf("최종 카운터 값: %d\n", counter.Value())
}

// =============================================================
// Chapter 6: Context를 사용한 작업 취소
// 컨텍스트를 통한 고루틴 제어 방법을 설명합니다.
// =============================================================

func longRunningTask(ctx context.Context) error {
	select {
	case <-time.After(5 * time.Second):
		return nil
	case <-ctx.Done():
		return ctx.Err()
	}
}

func contextExample() {
	// 2초 후에 취소되는 컨텍스트 생성.
	ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)
	defer cancel()

	// 작업 실행.
	err := longRunningTask(ctx)
	if err != nil {
		fmt.Printf("작업 중단: %v\n", err)
		return
	}
	fmt.Println("작업 완료!")
}

func main() {
	// ChannelCloser 인스턴스 생성.
	closer := NewChannelCloser()

	fmt.Println("=== Chapter 1: 기본 고루틴과 채널 ===")
	basicGoroutineExample()
	basicChannelExample()
	closer.CloseChannelExample(3)
	if err := closer.ErrorPropagationExample(); err != nil {
		fmt.Printf("에러 전파 예제 실패: %v\n", err)
	}

	fmt.Println("\n=== Chapter 2: 버퍼 채널과 채널 방향 ===")
	bufferedChannelExample()
	ch := make(chan int)
	go send(ch)
	receive(ch)

	fmt.Println("\n=== Chapter 3: select 문과 타임아웃 처리 ===")
	selectExample()

	fmt.Println("\n=== Chapter 4: WaitGroup을 사용한 동기화 ===")
	waitGroupExample()

	fmt.Println("\n=== Chapter 5: Mutex를 사용한 상태 관리 ===")
	mutexExample()

	fmt.Println("\n=== Chapter 6: Context를 사용한 작업 취소 ===")
	contextExample()
}
