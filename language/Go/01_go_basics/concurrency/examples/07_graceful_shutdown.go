/*
이 예제는 Go에서 우아한 종료(Graceful Shutdown) 패턴을 구현한 포괄적인 예시를 제공합니다. 이 패턴은 서비스가 안전하게 종료되도록 보장하면서, 진행 중인 작업을 완료하고 리소스를 정리하는 과정을 관리합니다.
구현의 핵심 컴포넌트들은 다음과 같은 기능을 제공합니다:
Service 인터페이스는 장기 실행 서비스의 기본 동작을 정의합니다. 각 서비스는 시작, 종료, 상태 확인 기능을 제공해야 합니다.
AppServer 구조체는 전체 애플리케이션 서버를 구현하며, 다음과 같은 주요 기능을 포함합니다:

서비스 수명 주기 관리
활성 연결 추적
상태 모니터링
메트릭 수집

이 구현은 다음과 같은 우아한 종료 단계를 포함합니다:

새로운 연결 수락 중단
진행 중인 연결이 완료될 때까지 대기
서비스의 순차적 종료
리소스 정리 및 정상 종료 확인

이 패턴의 주요 이점은 다음과 같습니다:

데이터 무결성 보장: 진행 중인 작업이 안전하게 완료됩니다.
리소스 관리: 모든 리소스가 적절히 정리됩니다.
상태 모니터링: 종료 과정의 각 단계를 추적할 수 있습니다.
유연한 타임아웃: 컨텍스트를 통해 종료 시간을 제어할 수 있습니다.

이 구현은 실제 프로덕션 환경에서 사용할 수 있도록 설계되었으며, 필요에 따라 추가 기능을 확장할 수 있습니다. 예를 들어, 종료 순서의 우선순위 지정, 상세한 상태 보고, 또는 분산 시스템에서의 조정된 종료 등을 구현할 수 있습니다.
*/

package examples

import (
	"context"
	"errors"
	"fmt"
	"log"
	"sync"
	"sync/atomic"
	"time"
)

// Service represents a long-running service that needs graceful shutdown
// 우아한 종료가 필요한 장기 실행 서비스를 나타내는 인터페이스입니다.
type Service interface {
	Start() error
	Stop(context.Context) error
	Status() ServiceStatus
}

// ServiceStatus represents the current status of a service
// 서비스의 현재 상태를 나타내는 열거형입니다.
type ServiceStatus int

const (
	StatusStopped ServiceStatus = iota
	StatusStarting
	StatusRunning
	StatusStopping
)

// String provides a string representation of service status
func (s ServiceStatus) String() string {
	switch s {
	case StatusStopped:
		return "Stopped"
	case StatusStarting:
		return "Starting"
	case StatusRunning:
		return "Running"
	case StatusStopping:
		return "Stopping"
	default:
		return "Unknown"
	}
}

// AppServer implements a sample application server with graceful shutdown
// 우아한 종료를 지원하는 애플리케이션 서버를 구현합니다.
type AppServer struct {
	services []Service
	// 서버 상태 관리
	status atomic.Value // ServiceStatus
	// 활성 연결 추적
	activeConnections sync.WaitGroup
	// 종료 알림 채널
	shutdown chan struct{}
	// 메트릭 수집
	metrics struct {
		sync.Mutex
		startTime        time.Time
		totalConnections int64
		totalErrors      int64
	}
}

// NewAppServer creates a new application server instance
// 새로운 애플리케이션 서버 인스턴스를 생성합니다.
func NewAppServer(services []Service) *AppServer {
	server := &AppServer{
		services: services,
		shutdown: make(chan struct{}),
	}
	server.status.Store(StatusStopped)
	return server
}

// Start initializes and starts all services
// 모든 서비스를 초기화하고 시작합니다.
func (s *AppServer) Start() error {
	if s.Status() != StatusStopped {
		return errors.New("server is already running or in transition")
	}

	s.status.Store(StatusStarting)
	s.metrics.startTime = time.Now()

	// 각 서비스 시작
	for _, service := range s.services {
		if err := service.Start(); err != nil {
			s.status.Store(StatusStopped)
			return fmt.Errorf("failed to start service: %w", err)
		}
	}

	s.status.Store(StatusRunning)
	log.Println("Server started successfully")
	return nil
}

// Shutdown initiates a graceful shutdown of the server
// 서버의 우아한 종료를 시작합니다.
func (s *AppServer) Shutdown(ctx context.Context) error {
	if s.Status() != StatusRunning {
		return errors.New("server is not running")
	}

	s.status.Store(StatusStopping)
	log.Println("Initiating graceful shutdown...")

	// 새로운 연결 거부 시작
	close(s.shutdown)

	// 진행 중인 연결이 완료될 때까지 대기
	done := make(chan struct{})
	go func() {
		s.activeConnections.Wait()
		close(done)
	}()

	// 서비스 종료 시작
	for i := len(s.services) - 1; i >= 0; i-- {
		service := s.services[i]
		if err := service.Stop(ctx); err != nil {
			log.Printf("Error stopping service: %v", err)
			s.incrementErrors()
		}
	}

	// 진행 중인 작업 완료 대기
	select {
	case <-ctx.Done():
		return fmt.Errorf("shutdown timed out: %w", ctx.Err())
	case <-done:
		s.status.Store(StatusStopped)
		log.Println("Server shutdown completed successfully")
		return nil
	}
}

// HandleConnection simulates handling a new connection
// 새로운 연결 처리를 시뮬레이션합니다.
func (s *AppServer) HandleConnection(ctx context.Context) error {
	// 서버가 종료 중인지 확인
	select {
	case <-s.shutdown:
		return errors.New("server is shutting down")
	default:
	}

	// 활성 연결 추적 시작
	s.activeConnections.Add(1)
	s.incrementConnections()
	defer s.activeConnections.Done()

	// 연결 처리 시뮬레이션
	select {
	case <-ctx.Done():
		s.incrementErrors()
		return ctx.Err()
	case <-time.After(time.Second):
		return nil
	}
}

// Status returns the current server status
// 현재 서버 상태를 반환합니다.
func (s *AppServer) Status() ServiceStatus {
	return s.status.Load().(ServiceStatus)
}

// GetMetrics returns server metrics
// 서버 메트릭을 반환합니다.
func (s *AppServer) GetMetrics() map[string]interface{} {
	s.metrics.Lock()
	defer s.metrics.Unlock()

	uptime := time.Since(s.metrics.startTime)
	return map[string]interface{}{
		"status":             s.Status().String(),
		"uptime_seconds":     uptime.Seconds(),
		"total_connections":  s.metrics.totalConnections,
		"total_errors":       s.metrics.totalErrors,
		"active_connections": s.getActiveConnectionCount(),
	}
}

// 메트릭 업데이트 헬퍼 함수들
func (s *AppServer) incrementConnections() {
	s.metrics.Lock()
	s.metrics.totalConnections++
	s.metrics.Unlock()
}

func (s *AppServer) incrementErrors() {
	s.metrics.Lock()
	s.metrics.totalErrors++
	s.metrics.Unlock()
}

func (s *AppServer) getActiveConnectionCount() int {
	// WaitGroup의 카운터 값을 직접 가져올 수는 없으므로,
	// atomic 연산을 통해 추적된 값을 반환
	return int(atomic.LoadInt64(&s.metrics.totalConnections) -
		atomic.LoadInt64(&s.metrics.totalErrors))
}

// GracefulShutdownExample demonstrates the usage of graceful shutdown pattern
func GracefulShutdownExample() {
	// 테스트 서비스 생성
	services := []Service{
		// 실제 서비스 구현체들이 여기에 들어갈 수 있습니다
	}

	// 서버 인스턴스 생성
	server := NewAppServer(services)

	// 서버 시작
	if err := server.Start(); err != nil {
		log.Fatalf("Failed to start server: %v", err)
	}

	// 연결 처리 시뮬레이션
	for i := 0; i < 5; i++ {
		go func(id int) {
			ctx := context.Background()
			if err := server.HandleConnection(ctx); err != nil {
				log.Printf("Connection %d error: %v", id, err)
			}
		}(i)
	}

	// 잠시 대기 후 종료 시작
	time.Sleep(2 * time.Second)

	// 종료 컨텍스트 생성 (10초 타임아웃)
	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	// 우아한 종료 시작
	if err := server.Shutdown(ctx); err != nil {
		log.Printf("Shutdown error: %v", err)
	}

	// 최종 메트릭 출력
	metrics := server.GetMetrics()
	log.Printf("\nFinal Server Metrics:")
	log.Printf("Status: %s", metrics["status"])
	log.Printf("Total Connections: %d", metrics["total_connections"])
	log.Printf("Total Errors: %d", metrics["total_errors"])
	log.Printf("Uptime: %.2f seconds", metrics["uptime_seconds"])
}
