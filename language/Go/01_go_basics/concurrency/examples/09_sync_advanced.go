package examples

import (
	"fmt"
	"sync"
	"time"
)

// SyncManager는 고급 sync 패키지 기능을 관리하는 구조체입니다.
// K8s 스타일: 동기화 로직을 모듈화하여 재사용성과 안정성 높임.
type SyncManager struct{}

// NewSyncManager는 새로운 SyncManager 인스턴스를 생성합니다.
// K8s 스타일: 생성자 함수로 초기화 캡슐화.
func NewSyncManager() *SyncManager {
	return &SyncManager{}
}

// DemonstrateSyncOnce는 sync.Once를 사용한 단일 실행 보장을 보여줍니다.
// K8s 스타일: 동작과 사용 사례를 상세히 설명.
func (sm *SyncManager) DemonstrateSyncOnce() {
	var once sync.Once
	var wg sync.WaitGroup
	count := 0

	// 초기화 함수: 한 번만 실행.
	initialize := func() {
		count++
		fmt.Println("초기화 실행: count =", count)
	}

	// 여러 고루틴에서 초기화 시도.
	for i := 0; i < 5; i++ {
		wg.Add(1)
		go func(id int) {
			defer wg.Done()
			once.Do(initialize)
			fmt.Printf("고루틴 %d: 초기화 후 count = %d\n", id, count)
		}(i)
	}

	wg.Wait()
	fmt.Println("결과: 초기화는 단 한 번만 실행됨")
}

// DemonstrateRWMutex는 sync.RWMutex를 사용한 읽기/쓰기 동기화를 보여줍니다.
// K8s 스타일: 메서드별 단일 책임 유지.
func (sm *SyncManager) DemonstrateRWMutex() {
	var rwm sync.RWMutex
	data := 0
	var wg sync.WaitGroup

	// 쓰기 고루틴: 데이터 수정.
	wg.Add(1)
	go func() {
		defer wg.Done()
		rwm.Lock() // 쓰기 잠금.
		defer rwm.Unlock()
		data = 42
		time.Sleep(100 * time.Millisecond) // 작업 시간 시뮬레이션.
		fmt.Println("쓰기: 데이터 업데이트 완료, data =", data)
	}()

	// 여러 읽기 고루틴: 데이터 읽기.
	for i := 0; i < 3; i++ {
		wg.Add(1)
		go func(id int) {
			defer wg.Done()
			rwm.RLock() // 읽기 잠금.
			defer rwm.RUnlock()
			fmt.Printf("읽기 고루틴 %d: data = %d\n", id, data)
		}(i)
	}

	wg.Wait()
}

// DemonstrateSyncMap는 sync.Map을 사용한 동시성 안전 맵을 보여줍니다.
// K8s 스타일: 동작과 제한사항 명시.
func (sm *SyncManager) DemonstrateSyncMap() {
	var smap sync.Map
	var wg sync.WaitGroup

	// 여러 고루틴에서 맵에 데이터 쓰기.
	for i := 0; i < 5; i++ {
		wg.Add(1)
		go func(id int) {
			defer wg.Done()
			key := fmt.Sprintf("key%d", id)
			smap.Store(key, id*10)
			fmt.Printf("고루틴 %d: %s = %d 저장\n", id, key, id*10)
		}(i)
	}

	wg.Wait()

	// 맵 순회 및 읽기.
	smap.Range(func(key, value interface{}) bool {
		fmt.Printf("맵 항목: %v = %v\n", key, value)
		return true // 계속 순회.
	})
}

// DemonstrateSyncCond는 sync.Cond를 사용한 조건부 동기화를 보여줍니다.
// K8s 스타일: 복잡한 동기화 패턴을 명확히 설명.
func (sm *SyncManager) DemonstrateSyncCond() {
	var mu sync.Mutex
	cond := sync.NewCond(&mu)
	ready := false
	var wg sync.WaitGroup

	// 대기 고루틴: 조건 충족 시 실행.
	for i := 0; i < 2; i++ {
		wg.Add(1)
		go func(id int) {
			defer wg.Done()
			mu.Lock()
			for !ready {
				cond.Wait() // 조건 대기.
			}
			fmt.Printf("고루틴 %d: 조건 충족, 실행\n", id)
			mu.Unlock()
		}(i)
	}

	// 신호 전송 고루틴.
	wg.Add(1)
	go func() {
		defer wg.Done()
		time.Sleep(500 * time.Millisecond) // 대기 시뮬레이션.
		mu.Lock()
		ready = true
		cond.Broadcast() // 모든 대기자에게 신호 전송.
		fmt.Println("신호 전송: 조건 활성화")
		mu.Unlock()
	}()

	wg.Wait()
}

// SyncAdvanced demonstrates advanced sync package features.
// K8s 스타일: 메인 함수는 각 데모를 독립적으로 호출.
func SyncAdvanced() {
	manager := NewSyncManager()

	fmt.Println("=== sync.Once 데모 ===")
	manager.DemonstrateSyncOnce()

	fmt.Println("\n=== sync.RWMutex 데모 ===")
	manager.DemonstrateRWMutex()

	fmt.Println("\n=== sync.Map 데모 ===")
	manager.DemonstrateSyncMap()

	fmt.Println("\n=== sync.Cond 데모 ===")
	manager.DemonstrateSyncCond()
}
