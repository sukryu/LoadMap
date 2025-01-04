# 분산 시스템 & 대규모 트래픽 대응

1. 시스템 디자인
    - 고가용성(HA), 스케일 아웃(수평 확장) 구조, 로드 밸런싱 레벨별(L4, L7) 설계
    - Cache(레디스, 멤캐시드), CDN, 메시지 큐(Kafka, RabbitMQ, SQS) 활용
    - 마이크로서비스 아키텍처에서 API 게이트웨이, 서비스 간 통신(gRPC, REST), 서킷 브레이커, 리트라이, 백오프 등

2. 이벤트 기반 비동기 아키텍처
    - 메시지 브로커(Kafka, RabbitMQ, NATS) 개념, Publish/Subscibe, 스트리밍
    - CQRS, 이벤트 소싱(Event Sourcing) 등 고급 패턴

3. Observability(가시성)
    - 로그 수집/분석(ELK Stack, Loki, Cloud Logging), 메트릭(Prometheus), 트레이싱(Zipkin, Jaeger)
    - 장애 상황에서 근본 원인(Root Cause) 찾아내기 -> 대규모 분산 서비스 진단 기법법