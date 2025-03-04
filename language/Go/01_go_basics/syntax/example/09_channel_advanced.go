package examples

import (
	"fmt"
	"sync"
	"time"
)

// ChannelManager는 채널 작업을 관리하는 구조체입니다.
// K8s 스타일: 관련 로직을 구조체로 묶어 모듈화하고 재사용성을 높임.
type ChannelManager struct {
	wg *sync.WaitGroup // 동기화를 위한 WaitGroup.
}

// NewChannelManager는 새로운 ChannelManager 인스턴스를 생성합니다.
// K8s 스타일: 생성자 함수는 'New'를 접두사로 사용하며, 초기화 로직을 캡슐화.
func NewChannelManager() *ChannelManager {
	return &ChannelManager{
		wg: &sync.WaitGroup{},
	}
}

// DemonstrateChannelClosing은 채널 닫기(close)와 안전한 수신 방법을 보여줍니다.
// K8s 스타일: 메서드는 단일 책임을 가지며, 동작과 주의 사항을 주석으로 상세히 설명.
func (cm *ChannelManager) DemonstrateChannelClosing(numMessages int) {
	// 메시지 전송을 위한 채널 생성.
	// 버퍼 크기를 지정해 생산자와 소비자의 속도 차이를 완화.
	msgChan := make(chan string, numMessages)

	// 생산자 고루틴: 메시지를 채널에 전송 후 닫음.
	cm.wg.Add(1)
	go func() {
		defer cm.wg.Done()
		defer close(msgChan) // 채널 닫기로 수신자에게 EOF 신호 전달.
		// K8s 스타일: 작업 완료 후 리소스 정리 보장.

		for i := 0; i < numMessages; i++ {
			msgChan <- fmt.Sprintf("메시지 %d", i+1)
			// 의도적인 지연으로 비동기 동작 시뮬레이션.
			time.Sleep(100 * time.Millisecond)
		}
		fmt.Println("생산자: 모든 메시지 전송 완료, 채널 닫음")
	}()

	// 소비자 고루틴: 채널에서 메시지를 수신.
	cm.wg.Add(1)
	go func() {
		defer cm.wg.Done()
		// K8s 스타일: 채널 닫기를 감지하기 위해 range 사용.
		for msg := range msgChan {
			fmt.Printf("소비자: 수신 - %s\n", msg)
		}
		fmt.Println("소비자: 채널이 닫혀 더 이상 메시지 없음")
	}()

	// 모든 고루틴이 완료될 때까지 대기.
	cm.wg.Wait()
}

// DemonstrateBroadcast는 채널을 통한 브로드캐스트 패턴을 구현합니다.
// 여러 수신자가 동일한 메시지를 받을 수 있도록 설계.
// K8s 스타일: 동작의 목적과 제한 사항을 주석으로 명시.
func (cm *ChannelManager) DemonstrateBroadcast(numReceivers, numMessages int) {
	// 브로드캐스트용 채널 생성.
	broadcastChan := make(chan string, numMessages)
	// 완료 신호 채널 생성.
	doneChan := make(chan struct{}, numReceivers)

	// 생산자 고루틴: 메시지를 채널에 전송 후 닫음.
	cm.wg.Add(1)
	go func() {
		defer cm.wg.Done()
		defer close(broadcastChan)
		for i := 0; i < numMessages; i++ {
			broadcastChan <- fmt.Sprintf("브로드캐스트 메시지 %d", i+1)
			time.Sleep(200 * time.Millisecond)
		}
		fmt.Println("생산자: 브로드캐스트 완료, 채널 닫음")
	}()

	// 여러 수신자 고루틴: 동일한 채널에서 메시지 수신.
	for i := 0; i < numReceivers; i++ {
		cm.wg.Add(1)
		go func(receiverID int) {
			defer cm.wg.Done()
			defer func() { doneChan <- struct{}{} }() // 완료 신호 전송.
			// K8s 스타일: 고루틴 ID로 작업 추적 가능.
			for msg := range broadcastChan {
				fmt.Printf("수신자 %d: %s\n", receiverID, msg)
			}
			fmt.Printf("수신자 %d: 브로드캐스트 종료\n", receiverID)
		}(i + 1)
	}

	// 모든 수신자가 완료될 때까지 대기.
	go func() {
		for i := 0; i < numReceivers; i++ {
			<-doneChan
		}
		close(doneChan)
	}()

	cm.wg.Wait()
}

// DemonstrateTimeout은 채널 작업에 타임아웃을 적용하는 방법을 보여줍니다.
// K8s 스타일: 타임아웃과 에러 처리를 명확히 구분.
func (cm *ChannelManager) DemonstrateTimeout(timeoutDuration time.Duration) error {
	// 작업 결과를 전달할 채널 생성.
	resultChan := make(chan string, 1)

	// 작업 고루틴: 지연된 작업 시뮬레이션.
	cm.wg.Add(1)
	go func() {
		defer cm.wg.Done()
		// 의도적으로 타임아웃보다 긴 시간 대기.
		time.Sleep(timeoutDuration + 500*time.Millisecond)
		resultChan <- "작업 완료"
	}()

	// K8s 스타일: select를 사용해 타임아웃과 결과 수신을 처리.
	select {
	case result := <-resultChan:
		fmt.Printf("결과: %s\n", result)
		cm.wg.Wait()
		return nil
	case <-time.After(timeoutDuration):
		fmt.Println("타임아웃 발생: 작업이 지정 시간 내 완료되지 않음")
		cm.wg.Wait()
		return fmt.Errorf("작업 타임아웃: %v 초과", timeoutDuration)
	}
}

// ChannelAdvanced demonstrates advanced channel patterns including closing, broadcasting, and timeouts.
// K8s 스타일: 메인 함수는 각 데모를 독립적으로 호출하며, 실행 흐름을 명확히 보여줌.
func ChannelAdvanced() {
	// ChannelManager 인스턴스 생성.
	manager := NewChannelManager()

	// 데모 1: 채널 닫기.
	fmt.Println("=== 채널 닫기 데모 ===")
	manager.DemonstrateChannelClosing(5)

	// 데모 2: 브로드캐스트.
	fmt.Println("\n=== 브로드캐스트 데모 ===")
	manager.DemonstrateBroadcast(3, 4)

	// 데모 3: 타임아웃 처리.
	fmt.Println("\n=== 타임아웃 데모 ===")
	if err := manager.DemonstrateTimeout(1 * time.Second); err != nil {
		fmt.Printf("에러: %v\n", err)
	} else {
		fmt.Println("작업이 타임아웃 없이 완료됨")
	}
}
