package main

import (
	"fmt"
	"os"
	"packages/logger"
	"sync"
	"time"

	"github.com/sirupsen/logrus"
)

// main은 이 프로그램의 진입점(entry point)입니다.
// 이 파일은 Go 모듈 시스템의 사용법과 외부/내부 패키지의 통합을 보여줍니다.
// K8s 스타일: 메인 함수는 프로그램의 전체 흐름을 명확히 드러냄.
func main() {
	// 프로그램 시작 메시지 출력.
	// K8s 스타일: 프로그램 상태를 로깅으로 추적 가능.
	fmt.Println("=== Go Package Management Demo 시작 ===")

	// 1. 외부 패키지(logrus) 사용 예제 호출.
	demonstrateExternalPackage()

	// 2. 사용자 정의 패키지(logger) 사용 예제 호출.
	demonstrateCustomPackage()

	// 프로그램 종료 메시지 출력.
	fmt.Println("\n=== Go Package Management Demo 종료 ===")
}

// demonstrateExternalPackage는 외부 패키지(logrus)를 활용하여 로깅 기능을 보여줍니다.
// K8s 스타일: 외부 의존성 사용 흐름을 명확히 주석으로 설명.
func demonstrateExternalPackage() {
	// logrus 인스턴스 생성 및 설정.
	// K8s 스타일: 초기화는 명시적으로 수행하며, 설정값을 주석으로 설명.
	log := logrus.New()
	log.SetFormatter(&logrus.TextFormatter{ // 텍스트 형식으로 로그 출력.
		FullTimestamp: true, // 타임스탬프 포함.
	})
	log.SetOutput(os.Stdout)       // 표준 출력으로 로그 전송.
	log.SetLevel(logrus.InfoLevel) // 디폴트 로그 레벨: Info 이상만 출력.

	// 다양한 로그 레벨로 메시지 출력.
	// K8s 스타일: 각 동작의 목적과 결과를 명확히 로깅.
	log.Info("외부 패키지(logrus) 데모 시작")
	log.Debug("디버그 메시지: 이건 출력되지 않음 (레벨 낮음)") // Info보다 낮아 출력 X.
	log.Warn("경고 메시지: 주의 필요")
	log.WithFields(logrus.Fields{ // 구조화된 로깅.
		"module": "external",
		"time":   time.Now().Format(time.RFC3339),
	}).Info("구조화된 로그 메시지")

	// 에러 시뮬레이션 및 로그.
	simulatedErr := fmt.Errorf("의도적 에러 발생")
	log.WithError(simulatedErr).Error("에러 로그 출력")

	fmt.Println("외부 패키지(logrus) 데모 완료")
}

// demonstrateCustomPackage는 사용자 정의 패키지(logger)를 활용하여 로깅 기능을 보여줍니다.
// K8s 스타일: 내부 패키지의 사용법과 동작을 상세히 설명.
func demonstrateCustomPackage() {
	// logger 패키지에서 Logger 인스턴스 생성.
	// K8s 스타일: 사용자 정의 패키지의 초기화는 생성자 함수 호출로 수행.
	customLogger := logger.NewLogger("demo-app", os.Stdout)

	// 기본 메시지 로깅.
	// K8s 스타일: 메서드 호출의 목적과 결과를 주석으로 명시.
	customLogger.Log("사용자 정의 패키지(logger) 데모 시작")

	// 다양한 로그 레벨 테스트.
	customLogger.Info("정보 메시지: 작업 진행 중")
	customLogger.Error("에러 메시지: 문제가 발생했습니다", fmt.Errorf("샘플 에러"))

	// 컨텍스트 데이터 포함 로깅.
	// K8s 스타일: 추가 데이터와 함께 로그를 구조화.
	customLogger.WithContext(map[string]interface{}{
		"user_id":   "12345",
		"timestamp": time.Now().Unix(),
	}).Info("컨텍스트가 포함된 로그 메시지")

	// 동시성 테스트: 여러 고루틴에서 로거 사용.
	// K8s 스타일: 동시성 안전성을 테스트하고 결과를 로깅.
	var wg sync.WaitGroup
	for i := 0; i < 3; i++ {
		wg.Add(1)
		go func(id int) {
			defer wg.Done()
			customLogger.Info(fmt.Sprintf("고루틴 %d: 동시성 테스트", id))
		}(i)
	}
	wg.Wait()

	fmt.Println("사용자 정의 패키지(logger) 데모 완료")
}
