# Concurrency in Go 🚀

Go 언어의 강력한 동시성 기능을 체계적으로 학습할 수 있도록 구성된 교육 자료입니다. 고루틴과 채널을 활용한 기본적인 동시성 프로그래밍부터 복잡한 동시성 패턴의 구현까지, 실전에서 활용 가능한 지식을 제공합니다.

## Learning Objectives 🎯

이 학습을 통해 다음과 같은 동시성 프로그래밍 역량을 획득하게 됩니다:

### 기본 동시성 메커니즘
- 고루틴의 생성과 관리
- 채널을 통한 고루틴 간 통신
- select 문을 사용한 다중 채널 처리
- 동기화 도구(WaitGroup, Mutex, Once 등) 활용

### 고급 동시성 패턴
- 워커 풀 패턴을 통한 작업 분배
- 파이프라인 구축을 통한 데이터 처리
- Fan-out/Fan-in 패턴을 활용한 병렬 처리
- 발행-구독 패턴 구현

### 실무 응용
- 동시성 관련 버그 예방과 디버깅
- 성능 최적화와 모니터링
- 실제 서비스에서의 동시성 패턴 적용

## Directory Structure 📁

```plaintext
concurrency/
├── main.go                      # 핵심 동시성 개념 예제
├── examples/
│   ├── 01_worker_pool.go       # 워커 풀 패턴 구현
│   ├── 02_pipeline.go          # 파이프라인 패턴
│   ├── 03_pub_sub.go           # 발행-구독 패턴
│   ├── 04_rate_limiter.go      # 속도 제한 구현
│   ├── 05_fan_out_fan_in.go    # Fan-out/Fan-in 패턴
│   ├── 06_semaphore.go         # 세마포어 패턴
│   ├── 07_graceful_shutdown.go # 우아한 종료 처리
│   └── 08_error_handling.go    # 동시성 에러 처리
└── README.md                    # 이 문서
```

### Examples Directory Contents

examples 디렉토리의 각 파일은 특정 동시성 패턴이나 문제 해결 방법을 다룹니다:

1. **Worker Pool (01_worker_pool.go)**
   - 작업 큐와 워커 풀 구현
   - 작업 분배 및 결과 수집
   - 자원 사용 최적화

2. **Pipeline (02_pipeline.go)**
   - 데이터 처리 파이프라인 구축
   - 스트림 처리와 병렬화
   - 단계별 처리 최적화

3. **Pub/Sub (03_pub_sub.go)**
   - 이벤트 기반 아키텍처 구현
   - 토픽 기반 메시지 라우팅
   - 구독자 관리

4. **Rate Limiter (04_rate_limiter.go)**
   - 요청 제한 구현
   - 버스트 처리
   - 공정한 자원 분배

5. **Fan-out/Fan-in (05_fan_out_fan_in.go)**
   - 작업 병렬 처리
   - 결과 수집 및 집계
   - 부하 분산

6. **Semaphore (06_semaphore.go)**
   - 리소스 접근 제어
   - 동시성 제한
   - 임계 영역 관리

7. **Graceful Shutdown (07_graceful_shutdown.go)**
   - 안전한 종료 처리
   - 리소스 정리
   - 진행 중인 작업 완료

8. **Error Handling (08_error_handling.go)**
   - 동시성 환경의 에러 처리
   - 에러 전파 및 복구
   - 장애 격리

## Getting Started 🚀

### Prerequisites
- Go 1.21 이상
- 기본적인 Go 문법 이해
- IDE (VS Code + Go 확장 권장)

### Installation & Setup
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/01-go-basics/concurrency
```

### Running Examples
```bash
# 기본 동시성 예제 실행
go run main.go

# 특정 패턴 예제 실행
go run examples/01_worker_pool.go
```

## Performance Optimization 🔧

동시성 코드의 성능 최적화를 위한 도구와 기법:

### Profiling
- `go tool pprof`를 사용한 프로파일링
- 고루틴 누수 탐지
- 경쟁 상태 분석

### Monitoring
- 실행 중인 고루틴 수 모니터링
- 메모리 사용량 추적
- 채널 버퍼 상태 확인

## Best Practices 💡

동시성 프로그래밍의 모범 사례:

1. 적절한 수의 고루틴 유지
2. 채널 크기의 신중한 설정
3. 데드락 방지를 위한 채널 관리
4. 공유 자원에 대한 적절한 동기화
5. 컨텍스트를 통한 취소 처리

## Next Steps 🎯

1. 각 예제를 순서대로 학습하고 실습
2. 예제 코드를 수정하여 다양한 시나리오 테스트
3. 실제 프로젝트에 동시성 패턴 적용
4. 성능 측정 및 최적화 실습

## Additional Resources 📚

- [Go Concurrency Patterns](https://talks.golang.org/2012/concurrency.slide)
- [Go Blog: Share Memory By Communicating](https://golang.org/doc/codewalk/sharemem)
- [Debugging Concurrency in Go](https://golang.org/doc/diagnostics.html)

Happy Concurrent Programming! 🚀