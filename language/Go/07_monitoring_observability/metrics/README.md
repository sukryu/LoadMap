# Metrics in Go: Monitoring & Insights 📊

이 디렉토리는 Go 애플리케이션의 성능 및 운영 상태를 모니터링하기 위해 **메트릭 수집**과 **분석**을 구현하는 방법을 다룹니다.  
주로 Prometheus와 Grafana를 활용하여, 애플리케이션, 시스템, 및 인프라 메트릭을 수집하고 시각화하는 전략과 실무 Best Practice를 학습할 수 있습니다.

---

## What You'll Learn 🎯

- **메트릭의 기본 개념**:  
  - 메트릭의 중요성, 수집 대상, 측정 단위와 레이블(label) 개념 이해

- **Prometheus 연동**:  
  - Go 애플리케이션에 Prometheus 클라이언트를 적용하여, 커스텀 메트릭(카운터, 게이지, 히스토그램 등)을 노출하는 방법
  - `/metrics` 엔드포인트를 통해 메트릭 데이터를 수집하는 방법

- **Grafana 시각화**:  
  - Prometheus와 연계하여 Grafana 대시보드를 구성하고, 애플리케이션 성능 및 리소스 사용량을 시각화하는 방법

- **Best Practices**:  
  - 효율적인 메트릭 설계, 레이블 사용 및 모니터링 전략
  - 성능 오버헤드 최소화와 로그, 트레이싱 등 다른 관찰 도구와의 통합 전략

---

## Directory Structure 📁

```plaintext
07-monitoring-observability/
└── metrics/
    ├── main.go         # Prometheus 메트릭 수집 및 HTTP 엔드포인트 예제
    ├── examples/       # 추가 메트릭 예제 및 대시보드 구성 사례
    └── README.md       # 이 문서
```

- **main.go**: Go 애플리케이션 내에서 Prometheus 클라이언트를 사용해 커스텀 메트릭을 수집하고, `/metrics` 엔드포인트를 노출하는 기본 예제가 포함되어 있습니다.
- **examples/**: 다양한 메트릭 수집 패턴과 Grafana 대시보드 설정 사례 등 고급 사용법을 실습할 수 있는 예제 코드들이 포함되어 있습니다.

---

## Getting Started 🚀

### 1. Prerequisites
- **Go 최신 버전**: [Download Go](https://go.dev/dl/)
- **Prometheus**: Prometheus 서버가 설치되어 있거나 Docker, Kubernetes 등으로 실행 중인지 확인하세요.
- **Grafana**: Grafana 설치 및 구성 (로컬 또는 클라우드 환경)

### 2. 라이브러리 설치
```bash
go get -u github.com/prometheus/client_golang/prometheus
go get -u github.com/prometheus/client_golang/prometheus/promhttp
```

### 3. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/07-monitoring-observability/metrics
```

### 4. 예제 코드 실행
```bash
go run main.go
```
- 브라우저에서 `http://localhost:8080/metrics`를 열어, 수집된 메트릭 데이터를 확인하세요.

---

## Example Code Snippet 📄

아래는 Prometheus 클라이언트를 사용하여 간단한 커스텀 메트릭(카운터)을 노출하는 예제입니다:

```go
package main

import (
    "net/http"

    "github.com/prometheus/client_golang/prometheus"
    "github.com/prometheus/client_golang/prometheus/promhttp"
)

var (
    // 사용자 정의 카운터 메트릭
    requestCounter = prometheus.NewCounter(
        prometheus.CounterOpts{
            Name: "myapp_requests_total",
            Help: "Total number of requests processed.",
        },
    )
)

func init() {
    // 메트릭 등록
    prometheus.MustRegister(requestCounter)
}

func handler(w http.ResponseWriter, r *http.Request) {
    // 요청이 들어올 때마다 카운터 증가
    requestCounter.Inc()
    w.Write([]byte("Hello, Metrics!"))
}

func main() {
    http.HandleFunc("/", handler)
    // /metrics 엔드포인트를 통해 Prometheus가 메트릭을 수집할 수 있도록 함
    http.Handle("/metrics", promhttp.Handler())
    http.ListenAndServe(":8080", nil)
}
```

이 예제는 기본 HTTP 서버를 실행하며, 루트 엔드포인트에서 요청 시 커스텀 카운터 메트릭을 증가시키고, `/metrics` 경로에서 Prometheus 메트릭 데이터를 노출합니다.

---

## Best Practices & Tips 💡

- **메트릭 설계**:  
  - 중요한 지표를 식별하고, 불필요한 메트릭 수집은 피하여 성능 오버헤드를 줄이세요.
  
- **레이블 활용**:  
  - 메트릭에 적절한 레이블을 추가하여, 다양한 차원에서 데이터를 필터링하고 분석할 수 있도록 설계하세요.
  
- **샘플링 및 집계**:  
  - 너무 세밀한 데이터는 집계하여 저장 공간과 처리량을 최적화하세요.
  
- **모니터링 통합**:  
  - Prometheus와 Grafana를 연계하여, 실시간 대시보드와 알림 설정을 통해 시스템 상태를 지속적으로 모니터링하세요.
  
- **자동화**:  
  - CI/CD 파이프라인에 메트릭 수집 및 모니터링 설정을 포함하여, 인프라 변경 시에도 모니터링을 자동으로 적용할 수 있도록 하세요.

---

## Next Steps

- **고급 메트릭**:  
  - 히스토그램, 요약(Summary) 등 다른 메트릭 타입을 학습하고, 다양한 사용 사례에 적용해 보세요.
- **대시보드 구축**:  
  - Grafana를 활용하여, Prometheus 메트릭을 시각화하고, 사용자 정의 대시보드를 만들어 보세요.
- **분산 환경 모니터링**:  
  - 마이크로서비스 및 클라우드 환경에서의 메트릭 수집 및 집계를 통해, 전체 시스템의 상태를 종합적으로 모니터링하는 전략을 수립해 보세요.

---

## References 📚

- [Prometheus Client Go Documentation](https://pkg.go.dev/github.com/prometheus/client_golang/prometheus)
- [Prometheus Best Practices](https://prometheus.io/docs/practices/)
- [Grafana Documentation](https://grafana.com/docs/)
- [Effective Go: Best Practices](https://golang.org/doc/effective_go.html)

---

효과적인 메트릭 수집과 모니터링은 애플리케이션의 성능 최적화와 문제 진단에 필수적입니다.  
이 자료를 통해 Go 애플리케이션에서 실시간 데이터를 수집하고, Grafana 대시보드를 통해 운영 상태를 명확하게 파악해 보세요! Happy Metrics Monitoring! 🚀