# Load Balancing in Go: Strategies & Implementations ⚖️

이 디렉토리는 Go 애플리케이션의 성능 및 가용성을 향상시키기 위한 **로드 밸런싱** 전략과 구현 방법을 다룹니다.  
여기서는 Nginx, HAProxy, Envoy와 같은 로드 밸런서와, Go 내에서 로드 밸런싱 로직을 구현하거나, 클라우드 네이티브 환경에서 트래픽 분산을 최적화하는 전략을 학습할 수 있습니다.

---

## What You'll Learn 🎯

- **로드 밸런싱 기본 개념**:  
  - 로드 밸런싱의 필요성과 목표, 주요 알고리즘(라운드 로빈, 최소 연결, 가중치 기반 등)의 이해

- **외부 로드 밸런서 활용**:  
  - Nginx, HAProxy, Envoy 등을 사용하여 Go 애플리케이션에 트래픽을 분산시키는 방법  
  - 클러스터 환경에서의 로드 밸런싱 구성 및 설정

- **내부 로드 밸런싱 구현**:  
  - Go 내에서 로드 밸런싱 로직(예: 클라이언트 요청을 여러 인스턴스로 분배)을 직접 구현하는 방법
  - 마이크로서비스 환경에서 각 서비스 인스턴스 간의 부하 분산 전략

- **실무 Best Practices**:  
  - 트래픽 라우팅, 헬스체크, 자동 복구 및 롤백 전략
  - 모니터링 및 성능 최적화를 위한 설정과 도구 활용

---

## Directory Structure 📁

```plaintext
10-performance-optimization/
└── load-balancing/
    ├── main.go          # Go 내에서 간단한 로드 밸런싱 로직 예제 (예: 요청 분배)
    ├── nginx/           # Nginx를 활용한 로드 밸런싱 설정 예제 및 구성 파일
    ├── haproxy/         # HAProxy를 활용한 로드 밸런싱 설정 예제
    ├── envoy/           # Envoy를 활용한 로드 밸런싱 및 API 게이트웨이 예제
    └── README.md        # 이 문서
```

- **main.go**:  
  - Go 애플리케이션 내에서 간단한 로드 밸런싱 알고리즘을 구현하는 예제 코드를 포함합니다.
- **nginx/**, **haproxy/**, **envoy/**:  
  - 각 로드 밸런서의 설정 파일과 구성 예제를 제공하여, 외부 로드 밸런서를 통한 트래픽 분산을 학습할 수 있습니다.

---

## Getting Started 🚀

### 1. Prerequisites
- Go 최신 버전 설치: [Download Go](https://go.dev/dl/)
- Docker 또는 로컬 환경에서 Nginx, HAProxy, Envoy 등을 실행할 수 있는 환경 구성
- 기본 네트워킹 및 클러스터 관리에 대한 이해

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/10-performance-optimization/load-balancing
```

### 3. 예제 코드 실행 (내부 로드 밸런싱)
- **Go 내 로드 밸런싱 예제 실행**
  ```bash
  go run main.go
  ```
- 예제 코드에서는 여러 서버 인스턴스에 요청을 라운드 로빈 방식으로 분배하는 간단한 로직을 시연합니다.

### 4. 외부 로드 밸런서 구성
- **Nginx 예제**:  
  - `nginx/` 디렉토리 내의 설정 파일을 참고하여, 로컬 또는 클라우드에서 Nginx를 설정하고 테스트하세요.
- **HAProxy 예제**:  
  - `haproxy/` 디렉토리 내의 설정 파일을 활용해 HAProxy를 구성하고, 트래픽 분산을 확인해 보세요.
- **Envoy 예제**:  
  - `envoy/` 디렉토리의 예제 파일로 Envoy 설정을 학습하고, API 게이트웨이 및 로드 밸런싱 기능을 실습하세요.

---

## Example Code Snippet 📄

아래는 Go 내에서 라운드 로빈 방식으로 요청을 분배하는 간단한 로드 밸런서 예제입니다:

```go
package main

import (
    "fmt"
    "log"
    "net/http"
    "net/http/httputil"
    "net/url"
    "sync/atomic"
)

var (
    // 백엔드 서버 목록 (예시)
    backends = []string{
        "http://localhost:8081",
        "http://localhost:8082",
        "http://localhost:8083",
    }
    // 요청을 분배하기 위한 인덱스
    counter uint64
)

// getNextBackend은 라운드 로빈 방식으로 다음 백엔드 URL을 선택합니다.
func getNextBackend() string {
    idx := atomic.AddUint64(&counter, 1)
    return backends[idx % uint64(len(backends))]
}

// loadBalancerHandler는 요청을 선택된 백엔드로 프록시합니다.
func loadBalancerHandler(w http.ResponseWriter, r *http.Request) {
    targetURL, err := url.Parse(getNextBackend())
    if err != nil {
        log.Printf("URL 파싱 에러: %v", err)
        http.Error(w, "Internal Server Error", http.StatusInternalServerError)
        return
    }
    proxy := httputil.NewSingleHostReverseProxy(targetURL)
    proxy.ServeHTTP(w, r)
}

func main() {
    // 로드 밸런서 HTTP 서버 시작
    http.HandleFunc("/", loadBalancerHandler)
    fmt.Println("Load Balancer is running on :8080")
    log.Fatal(http.ListenAndServe(":8080", nil))
}
```

이 예제는 3개의 백엔드 서버로 요청을 라운드 로빈 방식으로 분배하는 간단한 로드 밸런서를 구현합니다.

---

## Best Practices & Tips 💡

- **헬스체크**:  
  - 로드 밸런서에 연결된 각 백엔드 서버의 상태를 주기적으로 확인하여, 장애 발생 시 자동으로 제외하는 기능을 구현하세요.
  
- **가중치 기반 분배**:  
  - 서버의 성능이나 부하에 따라 가중치를 부여하여 트래픽을 분배하는 알고리즘을 고려하세요.
  
- **연결 유지**:  
  - 지속적인 연결 유지를 위한 Keep-Alive 설정과 타임아웃을 적절히 조정하여, 네트워크 효율을 높이세요.
  
- **모니터링 및 로깅**:  
  - 로드 밸런서의 트래픽 패턴과 각 서버의 상태를 모니터링하고, 로그를 분석하여 시스템 성능을 최적화하세요.
  
- **보안**:  
  - SSL/TLS를 활용하여 백엔드와의 통신 보안을 강화하고, 인증서 관리 정책을 적용하세요.
  
- **자동 스케일링과 통합**:  
  - 클라우드 환경에서는 자동 스케일링과 연계하여, 트래픽 급증 시 동적으로 인스턴스를 추가하도록 설정하세요.

---

## Next Steps

- **고급 로드 밸런싱 알고리즘**:  
  - 가중치 기반, 최소 연결, 지능형 트래픽 분배 등의 고급 알고리즘을 학습하고 구현해 보세요.
- **외부 로드 밸런서 실습**:  
  - Nginx, HAProxy, Envoy와 같은 외부 로드 밸런서의 설정 파일을 분석하고, 실제 클러스터에 적용해 보세요.
- **통합 모니터링**:  
  - Prometheus와 Grafana 등을 활용하여, 로드 밸런서의 성능을 모니터링하고, 실시간 알림 체계를 구축해 보세요.

---

## References 📚

- [Nginx Load Balancing Documentation](https://docs.nginx.com/nginx/admin-guide/load-balancing/)
- [HAProxy Documentation](https://www.haproxy.org/documentation/)
- [Envoy Proxy Documentation](https://www.envoyproxy.io/docs)
- [Kubernetes Service Load Balancing](https://kubernetes.io/docs/concepts/services-networking/service/)
- [Go Reverse Proxy Example](https://golang.org/pkg/net/http/httputil/#NewSingleHostReverseProxy)

---

로드 밸런싱은 애플리케이션의 가용성과 확장성을 보장하는 중요한 요소입니다.  
이 자료를 통해 다양한 로드 밸런싱 전략을 이해하고, Go 애플리케이션에 효과적으로 적용하여 안정적인 서비스를 운영해 보세요! Happy Load Balancing! ⚖️🚀