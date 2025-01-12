# 네트워크 가이드(Network Guide)

환영합니다!
이 저장소(`network/`)는 컴퓨터 네트워크에 대해 기초부터 고급(실무) 영역까지 폭넓게 학습할 수 있도록 구성된 자료 모음입니다.

## 개요 (Overview)

* 누구를 위한 문서인가?
    - 입문자: 네트워크 용어, IP 주소, TCP/UDP, HTTP 등 기본 개념을 처음 배우고 싶은 분
    - 실무자/고급 사용자: VPC 설계, 로드밸런싱, 트러블슈팅, 보안/성능 최적화 등 실제 서비스 운영에 필요한 내용을 찾는 분

* 어떤 내용을 다루는가?
    - 기본(Basic) 디렉토리에서는 네트워크의 가장 기초가 되는 프로토콜 구조, 동작 원리, 헤더 분석 등을 다룹니다.
    - 고급(Advenced) 디렉토리에서는 클라우드 환경에서의 VPC 설계, 로드밸런서, 서비스 메시, 애플리케이션 레벨 네트워킹, 보안/성능 튜닝, 트러블슈팅 등 심화 내용을 다룹니다.

## 디렉토리 구조 (Directory Structure)
```bash
network/
├── README.md            # (바로 이 문서) 전체 네트워크 문서 안내
├── basic/               # 네트워크 기초 개념 및 프로토콜 상세
│   ├── README.md        # basic 디렉토리 소개
│   ├── 01_osi_and_tcpip.md
│   ├── 02_ip_addressing.md
│   ├── 03_tcp_udp_details.md
│   ├── 04_http_https.md
│   └── ... (추가 가능)
└── advanced/            # 실무/고급 주제
    ├── README.md        # advanced 디렉토리 소개
    ├── network-basics.md
    ├── network-design.md
    ├── troubleshooting.md
    ├── cloud-networking.md
    ├── app-level-networking.md
    ├── security-performance.md
    └── appendix.md
```

1. `basic/`
    - 네트워크를 처음 접하는 분들을 위한 기초 지식 정리
    - OSI 모델, TCP/IP 4계층, IP/서브넷, TCP/UDP 내부 동작, HTTP/HTTPS 프로토콜, DNS rlch emd
    - 매우 상세하고 친절한 설명, 그림 예시, 패킷 캡처 등을 포함

2. `advanced/`
    - 실제 서비스를 운영하거나 심도 있는 네트워크 지식을 쌓고자 하는 분들을 위한 고급 주제
    - VPC 설계, 로드밸런싱, 방화벽·보안 그룹, 트러블슈팅(tcpdump·Wireshark·QoS), 클라우드 네트워킹(AWS/GCP/Azure), 애플리케이션 레벨(REST/gRPC/WebSocket/GraphQL), 보안·성능 최적화(TLS, CDN, DDoS 방어, 모니터링) 등

## 사용 가이드 (How to Use)

1. 네트워크 입문자
    - `basic/README.md`부터 차례대로 읽어보세요.
    - `01_osi_and_tcpip.md → 02_ip_addressing.md → 03_tcp_udp_details.md → 04_http_https.md` 순으로 학습하면 흐름을 잡기가 쉽습니다.

2. 중급/고급 실무자
    - 이미 IP/TCP/HTTP 등 기초 지식이 있다면, `advanced/`폴더로 이동해 필요한 주제부터 찾아보세요.
    - 예: VPC 설계가 궁금하다면 `network-design.md`, 모니터링과 트러블슈팅이 궁금하다면 `troubleshooting.md`.

3. 전체적으로 빠르게 훑고 싶은 경우
    - `advanced/network-basics.md` 문서를 먼저 보시면, 주요 프로토콜과 실무 개념들을 대략적으로 정리해둔 내용이 있습니다.

## 추천 학습 순서 (Recommanded Learning Path)

1. 기본(Basic) 폴더 → OSI & TCP/IP, IP 주소, TCP/UDP, HTTP/HTTPS

2. 고급(Advanced) 폴더 → 네트워크 인프라 설계(VPC, 로드밸런싱, 방화벽), 트러블슈팅(tcpdump, QoS), 클라우드 네트워킹, 애플리케이션 레벨(REST/gRPC), 보안/성능 최적화

**Tip: 초심자라도 `advanced/` 문서를 가볍게 스캔해 두면, 전체 그림을 파악하는 데 도움이 됩니다.**