# Tracing in Go: Distributed Tracing & Observability 🔍

이 디렉토리는 Go 애플리케이션에 분산 트레이싱을 도입하여, 서비스 간의 호출 흐름을 추적하고, 성능 병목 현상과 오류를 효과적으로 진단할 수 있는 방법을 다룹니다.  
OpenTelemetry, Jaeger 등의 도구를 활용해, 애플리케이션의 동작을 투명하게 파악하고, 전체 시스템의 관찰성을 높이는 전략을 학습합니다.

---

## What You'll Learn 🎯

- **분산 트레이싱의 기본 개념**  
  - 스팬(Span), 트레이스(Trace), 컨텍스트 전파 등의 핵심 용어와 원리 이해
- **Go에서의 트레이싱 구현**  
  - OpenTelemetry를 사용하여 애플리케이션에 트레이싱을 추가하는 방법
  - Jaeger와 같은 백엔드에 트레이스 데이터를 전송하는 방법
- **실무 적용 전략**  
  - 트레이싱을 통한 병목 현상 및 오류 진단
  - 로그, 메트릭과 연계한 종합 모니터링 전략
- **성능 고려 사항**  
  - 트레이싱 오버헤드 관리 및 샘플링 전략 적용

---

## Directory Structure 📁

```plaintext
07-monitoring-observability/
└── tracing/
    ├── main.go         # OpenTelemetry를 활용한 기본 트레이싱 예제
    ├── examples/       # 고급 트레이싱 사례 (컨텍스트 전파, 커스텀 스팬 등)
    └── README.md       # 이 문서
```

- **main.go**: Go 애플리케이션에 트레이싱을 설정하고, 간단한 스팬을 생성하는 예제 코드가 포함되어 있습니다.
- **examples/**: 다양한 고급 트레이싱 기법과 사례를 실습할 수 있는 추가 예제들을 제공합니다.

---

## Getting Started 🚀

### 1. Prerequisites
- **Go 최신 버전 설치**: [Download Go](https://go.dev/dl/)
- **Tracing 백엔드 준비**:  
  - Jaeger를 로컬 또는 클라우드에서 실행 (예: Docker, Kubernetes)
- **OpenTelemetry 패키지 설치**:
  ```bash
  go get -u go.opentelemetry.io/otel
  go get -u go.opentelemetry.io/otel/exporters/jaeger
  go get -u go.opentelemetry.io/otel/sdk/trace
  ```

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/07-monitoring-observability/tracing
```

### 3. 예제 코드 실행
```bash
go run main.go
```
- Jaeger UI를 통해 생성된 트레이스를 확인해 보세요.

---

## Example Code Snippet 📄

다음은 OpenTelemetry와 Jaeger를 활용한 간단한 트레이싱 예제입니다:

```go
package main

import (
    "context"
    "fmt"
    "log"
    "time"

    "go.opentelemetry.io/otel"
    "go.opentelemetry.io/otel/exporters/jaeger"
    "go.opentelemetry.io/otel/sdk/resource"
    sdktrace "go.opentelemetry.io/otel/sdk/trace"
    "go.opentelemetry.io/otel/trace"
)

func initTracer() func() {
    // Jaeger Exporter 생성
    exp, err := jaeger.New(jaeger.WithAgentEndpoint(
        jaeger.WithAgentHost("localhost"),
        jaeger.WithAgentPort("6831"),
    ))
    if err != nil {
        log.Fatal(err)
    }

    // Tracer Provider 설정
    tp := sdktrace.NewTracerProvider(
        sdktrace.WithBatcher(exp),
        sdktrace.WithResource(resource.NewWithAttributes(
            "service.name", "go-tracing-example",
        )),
    )
    otel.SetTracerProvider(tp)

    // 종료 시 트레이서 종료 함수 반환
    return func() {
        if err := tp.Shutdown(context.Background()); err != nil {
            log.Fatal(err)
        }
    }
}

func main() {
    shutdown := initTracer()
    defer shutdown()

    tracer := otel.Tracer("go-tracing-example")

    // 루트 스팬 생성
    ctx, span := tracer.Start(context.Background(), "MainOperation")
    defer span.End()

    // 예제 함수 실행
    doWork(ctx, tracer)

    fmt.Println("Tracing complete. Check your Jaeger UI.")
}

func doWork(ctx context.Context, tracer trace.Tracer) {
    ctx, span := tracer.Start(ctx, "DoWork")
    defer span.End()

    // 작업 시뮬레이션
    time.Sleep(2 * time.Second)
    span.AddEvent("Work completed")
}
```

이 예제는 Jaeger에 트레이스를 전송하여, 주요 작업 흐름을 기록하고 모니터링할 수 있게 합니다.

---

## Best Practices & Tips 💡

- **Context Propagation**:  
  - 모든 함수 호출 시 trace context를 전달하여, 트레이스가 여러 서비스에 걸쳐 올바르게 전파되도록 하세요.
  
- **샘플링 전략**:  
  - 트레이싱 오버헤드를 줄이기 위해 적절한 샘플링 비율을 설정하세요.
  
- **커스텀 스팬 추가**:  
  - 중요한 비즈니스 로직이나 외부 API 호출 등에서 커스텀 스팬과 이벤트를 추가하여, 상세한 성능 정보를 기록하세요.
  
- **통합 모니터링**:  
  - 트레이스 로그를 다른 모니터링 도구(예: Prometheus, Grafana)와 연계해, 종합적인 애플리케이션 상태를 파악하세요.
  
- **에러 추적**:  
  - 오류 발생 시, 스팬에 에러 정보를 기록해 빠른 문제 진단이 가능하도록 하세요.

---

## Next Steps

- **고급 트레이싱**:  
  - 여러 서비스 간의 분산 트레이싱, 인터셉터를 통한 자동 트레이싱 추가 등의 고급 기법을 학습해 보세요.
- **서비스 통합**:  
  - 마이크로서비스 아키텍처에 트레이싱을 적용하여, 엔드 투 엔드 호출 흐름을 분석해 보세요.
- **도구 비교**:  
  - Jaeger 외에도 Zipkin, Honeycomb 등 다른 트레이싱 백엔드를 사용해 보고, 각 도구의 장단점을 비교해 보세요.

---

## References 📚

- [OpenTelemetry Documentation](https://opentelemetry.io/docs/)
- [Jaeger Documentation](https://www.jaegertracing.io/docs/)
- [Go OpenTelemetry GitHub](https://github.com/open-telemetry/opentelemetry-go)
- [Distributed Tracing Best Practices](https://medium.com/@kelvinlzx/distributed-tracing-best-practices-2a28f1fef3be)

---

Distributed tracing is essential for understanding and optimizing the performance of modern distributed systems.  
Leverage this guide to instrument your Go applications and gain deep insights into your system's behavior. Happy Tracing! 🔍🚀