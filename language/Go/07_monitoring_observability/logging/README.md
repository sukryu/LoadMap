# Logging in Go: Structured Logging & Best Practices 📝

이 디렉토리는 Go 애플리케이션에서 **로깅**을 효과적으로 구현하고 관리하는 방법을 다룹니다.  
구조화된 로깅을 통해 애플리케이션의 상태를 명확하게 기록하고, 문제 발생 시 빠르게 디버깅할 수 있으며, 모니터링 및 추적 시스템과 연계하여 운영 효율성을 높일 수 있습니다.

---

## What You'll Learn 🎯

- **로깅의 중요성**:  
  - 로그의 역할과 생산 환경에서의 중요성 이해
  - 디버깅, 모니터링, 감사(Compliance)에 기여하는 로깅

- **구조화된 로깅**:  
  - 단순 텍스트 로그보다 키-값 쌍으로 구성된 로그의 장점
  - 컨텍스트 정보와 메타데이터를 추가하여 로그를 풍부하게 만드는 방법

- **Go의 인기 로깅 라이브러리**:  
  - Uber의 [Zap](https://pkg.go.dev/go.uber.org/zap)와 [Logrus](https://github.com/sirupsen/logrus) 등 주요 라이브러리 사용법
  - 각 라이브러리의 특징 및 선택 기준

- **Best Practices**:  
  - 적절한 로깅 레벨 설정 (DEBUG, INFO, WARN, ERROR, FATAL)
  - 로그 출력 포맷, 파일 출력, stdout/stderr 사용 등의 운영 환경에 맞는 로깅 전략

---

## Directory Structure 📁

```plaintext
07-logging/
├── main.go         # 구조화된 로깅 예제 코드 (예: Zap을 활용한 샘플)
├── examples/       # 고급 로깅 기능 및 다양한 사용 사례 예제
└── README.md       # 이 문서
```

- **main.go**: 기본 로깅 설정과 예제 코드가 포함되어 있어, Go 애플리케이션에서 구조화된 로깅을 실습할 수 있습니다.
- **examples/**: 다양한 시나리오(예: HTTP 요청 로깅, 에러 로깅, 분산 환경 로깅 등)에 대한 추가 예제 코드들이 포함되어 있습니다.

---

## Getting Started 🚀

### 1. 필수 도구 설치
- Go 최신 버전: [Download Go](https://go.dev/dl/)
- 로깅 라이브러리 설치 (예: Zap)
  ```bash
  go get -u go.uber.org/zap
  ```

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/07-logging
```

### 3. 예제 코드 실행
```bash
go run main.go
```
- 실행 결과를 확인하며, 구조화된 로깅 메시지가 어떻게 출력되는지 살펴보세요.

---

## Example Code Snippet 📄

아래는 Zap 라이브러리를 활용한 간단한 구조화된 로깅 예제입니다:

```go
package main

import (
    "go.uber.org/zap"
)

func main() {
    // Production 모드의 로거 생성 (높은 성능과 구조화된 로그 제공)
    logger, err := zap.NewProduction()
    if err != nil {
        panic(err)
    }
    defer logger.Sync() // 버퍼에 남은 로그를 플러시

    // Sugar 로거를 사용하여 간편한 로그 기록
    sugar := logger.Sugar()

    // 구조화된 로그 예제
    sugar.Infow("Starting application",
        "version", "1.0.0",
        "port", 8080,
    )

    // 포맷된 로그 예제
    sugar.Infof("Listening on port %d", 8080)
}
```

이 예제는 Zap를 통해 생성된 로거를 사용하여, 키-값 쌍으로 구성된 구조화된 로그 메시지를 기록하는 방법을 보여줍니다.

---

## Best Practices & Tips 💡

- **적절한 로깅 레벨 사용**:  
  - DEBUG, INFO, WARN, ERROR, FATAL 등의 로깅 레벨을 상황에 맞게 사용하여, 필요 시 로그 필터링을 쉽게 합니다.
  
- **구조화된 로깅**:  
  - 로그 메시지에 키-값 쌍으로 메타데이터를 추가하여, 나중에 로그 분석이나 모니터링 도구와 연동 시 유용하게 활용하세요.
  
- **환경에 따른 출력 설정**:  
  - 컨테이너 환경에서는 stdout/stderr로 로그를 출력하고, 중앙 집중식 로깅 시스템(예: ELK Stack, Prometheus, Grafana)과 연계하세요.
  
- **에러 로깅**:  
  - 에러 발생 시 스택 트레이스와 추가 컨텍스트 정보를 포함하여, 문제 분석을 용이하게 하세요.
  
- **성능 고려**:  
  - 로깅이 애플리케이션 성능에 미치는 영향을 최소화하기 위해, 비동기 로깅 또는 배치 로깅 기법을 고려하세요.

---

## Next Steps

- **고급 로깅**:  
  - HTTP 요청/응답 로깅, 분산 로깅(예: OpenTelemetry와 연계) 등의 고급 기능을 추가로 실습해 보세요.
- **로그 분석**:  
  - 수집된 로그 데이터를 ELK Stack, Grafana Loki, Splunk 등과 연계하여, 실시간 로그 모니터링 및 분석을 경험해 보세요.
- **로깅 미들웨어 구현**:  
  - Gin, Fiber 등의 웹 프레임워크와 통합하여, 자동화된 HTTP 요청 로깅 미들웨어를 구현해 보세요.

---

## References 📚

- [Zap Documentation](https://pkg.go.dev/go.uber.org/zap)
- [Logrus Documentation](https://github.com/sirupsen/logrus)
- [Effective Go - Logging](https://golang.org/doc/effective_go.html)
- [Centralized Logging Patterns](https://www.elastic.co/guide/en/logstash/current/centralized-logging.html)

---

구조화된 로깅은 안정적인 운영과 빠른 문제 해결을 위한 필수 도구입니다.  
이 자료를 통해 Go 애플리케이션에 효과적으로 로깅을 적용하고, 실무에서 로그 데이터를 활용하여 시스템 상태를 모니터링해 보세요! Happy Logging! 🎉