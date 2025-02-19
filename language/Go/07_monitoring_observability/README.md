# 07 Monitoring & Observability 🚦

이 디렉토리는 클라우드 네이티브 환경에서 **모니터링**과 **관찰성(Observability)**을 실무에 어떻게 적용할 수 있는지를 다룹니다.  
서비스 운영, 성능 최적화, 장애 대응을 위해 필수적인 로깅, 분산 트레이싱, 메트릭 수집 등의 전략과 도구 사용법을 살펴봅니다.

---

## 디렉토리 구조 📁

```plaintext
07-monitoring-observability/
├── logging/         # 구조화된 로깅 시스템과 중앙집중식 로그 관리
├── tracing/         # 분산 트레이싱 (OpenTelemetry, Jaeger 등) 및 추적 전략
└── metrics/         # Prometheus, Grafana를 활용한 시스템 메트릭 수집 및 시각화
```

- **logging/**:  
  - 서비스 간 통합 로그 수집 및 분석
  - ELK 스택, Fluentd, Go 기반 로깅 라이브러리(logrus, zap 등) 활용 예제

- **tracing/**:  
  - 분산 시스템에서 요청의 흐름을 추적하는 방법
  - OpenTelemetry, Jaeger 등을 활용한 트레이싱 설정 및 코드 예제

- **metrics/**:  
  - 시스템과 애플리케이션의 성능 메트릭 수집 및 시각화
  - Prometheus로 데이터 스크랩, Grafana로 대시보드 구성하는 방법

---

## 실무 활용 목표 🎯

- **효과적인 로깅 구현**:  
  - 모든 서비스에서 일관된 구조의 로그를 남겨 문제 발생 시 빠르게 원인 분석
  - 중앙 로그 시스템(예: ELK, Fluentd)과 연계하여 로그를 실시간으로 모니터링

- **분산 트레이싱 도입**:  
  - 마이크로서비스 아키텍처에서 각 서비스 간의 요청 추적을 통해 병목 현상 및 장애 원인 파악
  - OpenTelemetry와 Jaeger를 통해 엔드투엔드 트레이싱을 구현

- **메트릭 수집 및 시각화**:  
  - Prometheus로 애플리케이션 및 인프라 메트릭을 수집하고, Grafana 대시보드를 통해 실시간 모니터링
  - 자동화된 알림 시스템을 구축해 이상 징후 발생 시 즉각 대응

---

## 실무 적용 사례 🚀

1. **통합 로깅 시스템 구축**  
   - 여러 서비스에서 발생하는 로그를 중앙 로그 서버로 전송하여, Kibana 등을 통해 분석
   - 로그를 기반으로 에러 패턴 및 사용자 행동 분석

2. **분산 트레이싱 도입**  
   - 마이크로서비스 간 호출에서 트레이스 ID를 전달하여, 전체 요청의 흐름과 지연을 파악
   - Jaeger를 통해 서비스 간 호출 지연, 병목 현상, 오류 경로를 시각화

3. **메트릭 기반 모니터링 및 알림**  
   - Prometheus를 이용해 CPU, 메모리, 네트워크 등 시스템 메트릭을 수집
   - Grafana 대시보드를 통해 실시간 모니터링하고, 임계치 초과 시 알림을 설정하여 빠른 대응

---

## 실무 적용 방법 및 팁 💡

### 1. 로깅
- **구조화된 로깅**: logrus, zap 같은 라이브러리를 사용해 JSON 형식의 로그를 남기세요.
- **중앙집중식 로그 수집**: Fluentd, Logstash와 함께 ELK 스택을 사용하면 여러 서비스의 로그를 한 곳에서 관리할 수 있습니다.
- **로그 레벨 관리**: Info, Warn, Error 등 적절한 로그 레벨을 설정하여 로그의 중요도를 구분하세요.

### 2. 분산 트레이싱
- **트레이스 컨텍스트 전파**: 각 서비스 호출 시 trace ID, span ID를 전달하여 전체 요청 흐름을 추적합니다.
- **도구 설정**: OpenTelemetry SDK를 애플리케이션에 적용하고, Jaeger 백엔드를 설정하여 추적 데이터를 시각화하세요.
- **샘플링 전략**: 트레이싱 데이터의 양을 제어하기 위해 적절한 샘플링 기법을 적용합니다.

### 3. 메트릭 수집 및 모니터링
- **Prometheus 설정**: 애플리케이션에서 메트릭 엔드포인트를 노출하고, Prometheus가 이를 스크랩할 수 있도록 구성하세요.
- **Grafana 대시보드 구성**: 수집된 메트릭 데이터를 기반으로 시각화 대시보드를 구축하여, 시스템 상태를 실시간 모니터링합니다.
- **알림 설정**: Prometheus나 Grafana에서 임계치 기반의 알림을 설정해, 시스템 이상 징후를 조기에 탐지하세요.

---

## 시작하기 🚀

### 1. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/07-monitoring-observability
```

### 2. 예제 실행
#### a. 로깅 예제
```bash
cd logging
go run main.go
```
- 로그 파일이나 콘솔에 출력되는 구조화된 로그를 확인해보세요.

#### b. 트레이싱 예제
```bash
cd ../tracing
go run main.go
```
- Jaeger UI를 통해 트레이스 데이터를 확인하며, 서비스 호출 흐름을 분석합니다.

#### c. 메트릭 예제
```bash
cd ../metrics
go run main.go
```
- Prometheus에 노출되는 메트릭 데이터를 확인하고, Grafana 대시보드를 구성하여 모니터링 환경을 구축해 보세요.

---

## 참고 자료 📚

- [Prometheus Documentation](https://prometheus.io/docs/)
- [Grafana Documentation](https://grafana.com/docs/)
- [Jaeger Documentation](https://www.jaegertracing.io/docs/)
- [OpenTelemetry Documentation](https://opentelemetry.io/docs/)
- [Go Logging Libraries (logrus, zap)](https://github.com/sirupsen/logrus), (https://github.com/uber-go/zap)

---

모니터링 및 관찰성은 서비스 안정성과 성능 개선에 필수적입니다.  
실무 환경에서 발생할 수 있는 문제를 신속하게 파악하고 대응할 수 있도록, 이 자료를 기반으로 모니터링 시스템을 구축해 보세요! Happy Monitoring! 🚀