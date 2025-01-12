# 고급 네트워크(Advanced) 디렉토리

이 디렉토리는 실무에서 네트워크를 다루는 엔지니어, 혹은 기본 프로토콜 지식을 이미 습득한 분들을 위해 마련되었습니다.
VPC 설계, 로드밸런서, 트러블슈팅, 클라우드 네트워킹, 애플리케이션 레벨 프로토콜, 보안/성능 최적화 등 폭넓은 고급 주제를 다룹니다.

## 디렉토리 구성 (Files Overview)

이 곳에는 현재 다음과 같은 문서들이 있습니다:

1. `network-basics.md`
    - 이미 `basic/` 디렉토리에서 다룬 프로토콜 개념을 실무 시나리오에 맞춰 간단히 재정리
    - TCP vs UDP, HTTP/HTTPS, DNS, 등 주요 포인트를 빠르게 훑어보고 싶을 때 참고

2. `network-design.md`
    - 네트워크 인프라 설계 원칙: VPC, 서브넷팅, NAT 게이트웨이, 방화벽(보안 그룹/NACL)
    - 로드밸런싱(L4/L7) 구성, DNS 설계, 이중화/고가용성(HA) 전략 등

3. `troubleshooting.md`
    - 패킷 분석(tcpdump, Wireshark), 네트워크 모니터링(MTR, iperf3), QoS/Traffic Shaping
    - 실제 장애 시나리오(연결 안 됨, 지연 증가, DNS 오작동 등)를 단계별로 해결

4. `cloud-networking.md`
    - AWS/GCP/Azure에서의 VPC, 네트워크 보안, 하이브리드 클라우드(VPN, Direct Connect)
    - 컨테이너 환경(Kubernetes CNI, Service Mesh) 및 마이크로서비스 네트워킹

5. `app-level-networking.md`
    - RESTful API, gRPC, WebSocket, GraphQL 등 애플리케이션 레벨 프로토콜/아키텍처
    - MSA(마이크로서비스) 통신 구조, API Gateway, 메시 브로커, 서버리스 연계

6. `security-performance.md`
    - TLS/SSL, 인증서 관리, DDoS 방어, WAF, CDN 활용
    - 로드 테스트, 캐싱, 로드밸런서 최적화, 고트래픽 서비스 설계

7. `appendix.md`
    - 용어 사전, FAQ, 추가 참고 링크, 권장 도구 목록
    - 전체 문서에서 자주 언급되는 용어/설정 예시를 한곳에 정리

## 학습 및 활용 방법 (How to Use)

1. 특정 주제만 빠르게
    - 예: “로드밸런서 구성 방법”을 알고 싶다면` network-design.md` → L4 vs L7 로드밸런싱 섹션을 찾아보세요.
    - “TCP 캡처로 문제 디버깅?” → `troubleshooting.md`의 tcpdump·Wireshark 활용 파트를 참고.

2. 순차적으로 심화 학습
    - “네트워크 전반적인 아키텍처 설계를 공부하고 싶다”면 `network-design.md`부터,
    - 이어서 “보안·성능 최적화” → “클라우드 네트워킹” → “애플리케이션 레벨” 순으로 보면 체계적으로 파악할 수 있습니다.

3. 실무 시나리오 기반
    - 각 문서에는 “실제 설정 예시(Nginx, HAProxy, AWS 등)”나 “트러블슈팅 시나리오”가 포함되어 있습니다.
    - 바로 적용할 수 있는 코드 스니펫 및 명령어 예시가 많으니, 복붙해 테스트하거나 사내 문서에 참고해도 좋습니다.

## 대상 독자 (Who Is This For?)

* 인프라/시스템 엔지니어: VPC 설계, 방화벽 정책, 로드밸런서, 모니터링 등
* 클라우드/DevOps 엔지니어: AWS/GCP/Azure 네트워킹, CI/CD, 쿠버네티스 CNI, 서비스 메시
* 백엔드 개발자: REST/gRPC/WebSocket/GraphQL, 고트래픽 서비스, API 게이트웨이, 보안과 성능 최적화
* 네트워크 문제를 직접 해결해야 하는 분: tcpdump, Wireshark 분석, QoS/Traffic Shaping, CDN/WAF 설정

## 추천 학습 경로 (Suggested Reading Path)

1. 네트워크 설계(`network-design.md`) → VPC, 서브넷, 로드밸런싱, DNS, 방화벽 구조 이해
2. 트러블슈팅(`troubleshooting.md`) → 패킷 분석, 모니터링, 장애 해결 프로세스
3. 클라우드 네트워킹(`cloud-networking.md`) → AWS/GCP/Azure VPC, 하이브리드 클라우드, K8s CNI
4. 애플리케이션 레벨(`app-level-networking.md`) → REST, gRPC, WebSocket, MSA 디자인
5. 보안·성능(`security-performance.md`) → TLS/SSL, DDoS, WAF, CDN, 성능 테스트

(원하는 주제부터 골라 읽어도 무방합니다.)