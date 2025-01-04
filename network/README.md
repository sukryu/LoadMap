# 네트워크

1. 기본적인 네트워크 프로토콜 이해
    1. TCP/IP 4계층 모델
        - 링크(물리), 네트워크(IP), 전송(TCP/UDP), 애플리케이션(HTTP, DNS, FTP 등)
        - IP 주소, 서브넷 마스크, 게이트웨이, 라우팅, ARP, ICMP(ping) 등의 기초 개념

    2. TCP vs UDP
        - 연결 지향(TCP)와 비연결 지향(UDP)의 특징 및 사용 사례
        - TCP 핸드셰이크(3-way handshake), 흐름 제어, 혼잡 제어 개념
        - UDP가 주로 쓰이는 영역(스트리밍, DNS 등)

    3. HTTP/HTTPS
        - HTTP 1.1 vs 2 vs 3(QUIC), Keep-Alice, 헤더, 쿠키, CORS, 상태코드
        - TLS/SSL 원리(핸드셰이크, 인증서, 암호화 채널)

    - **목표: OSI 7계층 전부를 깊이 파지 않아도 좋지만, 실제로 트러블슈팅하거나 서비스를 구성할 때 필요한 수준(주요 프로토콜, 포트, 세션 개념, 라우팅 기본) 이상은 반드시 숙지**

2. 네트워크 설계 & 인프라 구성
    1. 세브넷팅 / VPC 구성
        - 세브넷 마스크 계산, 사설 IP 범위(192.168.x.x, 10.x.x.x 등)
        - 라우팅 테이블, NAT(소스/목적 NAT), 방화벽 기본

    2. DNS
        - 도메인 이름 - IP 주소 변환 원리, Recursive/Authoritative DNS
        - CNAME, A 레코드, MX, TXT, SRV 등 레코드 유형
        - DNS 라우팅(예: 클라우드에서 Route53, Cloud DNS 등)

    3. 로드밸런싱
        - L4(전송 계층) vs L7(애플리케이션 계층) 로드 밸런서 차이
        - 주요 제품(HAProxy, Nginx, AWS ELB, GCP GLB 등) 사용법
        - 세션 스티커(Session Persistence), Health Check, SSL 종료/패스스루

    - **목표: 클라우드(VPC, 서브넷, 게이트웨이, 보안 그룹), 온프레미스(라우터, 스위치, 방화벽) 환경에서 서비스가 어떻게 네트워크 경로를 타고 들어오는지를 이해하고 구성/디버깅 할 수 있을 정도.**

3. 고급 주제(트러블슈팅 & 모니터링)
    1. 패킷 분석
        - `tcpdump`, `Wireshark` 등으로 패킷 캡처하고 분석할 수 있는 능력
        - 예: 특정 요청이 왜 타임아웃되는지, 어떤 패킷이 드롭되는지 확인

    2. 네트워크 지연(Latency), 대역폭(Bandwith), Throughput
        - RTT, BDP(Bandwith Delay Product), CDN/Edge 서버를 통한 지연 감소 방식
        - 로드 테스트, 스트레스 테스트 시 병목 지점 파악(서버 CPU vs 네트워크 I/O vs DB)

    3. QoS, Traffic Shaping
        - 대규모 트래픽 관리, 우선순위 할당, Rate Limiting
        - "백엔드 API의 트래픽 폭주를 어떻게 제어할까?" 같은 시나리오에서 활용

    - **목표: 실무에서 발생하는 네트워크 이슈(IP 충돌, 라우팅 오류, 방화벽/보안 그룹 설정 실수, 패킷 손실, 포트 충돌 등)를 기본적인 명령어와 도구(`ping`, `traceroute`, `tcpdump`, `netstat/lsof`, `ss` 등)로 파악하고 해결할 수 있는 능력.**

4. 클라우드 환경에서의 네트워크
    1. VPC(가상 사설망)와 서브넷
        - AWS VPC, GCP VPC, Azure VIrtual Network 개념
        - IGW(Internet Gateway), NAT Gateway, Peering, PrivateLink 등

    2. 서비스 메시 & 마이크로서비스 네트워킹
        - Istio, Linkerd 등 서비스 메시 -> mTLS, 사이드카 프록시, 라우팅 규칙
        - 쿠버네티스 CNI(Container Network Interface) 플러그인(Calico, Weave, Flannel 등)의 작동 원리

    3. 하이브리드 클라우드, VPN
        - 온프레미스 <-> 클라우드 간 IPSec VPN 터널, Direct Connect/ExpressRoute
        - VPC 간 피어링, Transit Gateway 등 대규모 네트워크 아키텍처

    - **목표: AWS/GCP 등에서 VPC와 서브넷을 올바르게 설계하고, 온프레미스-클라우드 혼합 환경(하이브리드 클라우드)에서 VPN/전용선 설정, 서비스 메시로 마이크로서비스 간 안전한 통신 구조를 구성할 수 있을 정도.**

5. 애플리케이션 레벨 네트워킹
    1. RESTful API, gRPC
        - JSON vs Protocol Buffers, HTTP/2, gRPC 스트리밍, 업/다운스트림 로드 밸런싱
        - gRPC 시큐리티(SSL/TLS), Mutual TLS 인증

    2. WebSocket
        - 장시간 연결(풀 이이벤트), 실시간 통신 구조
        - WebSocket vs SSE(Server Sent Events) vs Polling

    3. GraphQL, GraphQL over HTTP/2
        - GraphQL이 네트워크 트래픽을 어떻게 절약/증가시킬 수 있는지
        - Apollo Federation, Schema Stitching 등 마이크로서비스 구조에서의 GraphQL 접근

    - **목표: 백엔드 엔지니어가 API 설계·통신 구조를 잘 이해해, 성능/보안/실시간성을 고려한 적절한 프로토콜과 구현 방식을 선택할 수 있는 능력.**

6. 보안/성능 측면에서의 네트워크
    1. HTTPS & TLS 심화
        - 인증서 체인, OCSP 스테이플링, HSTS, ALPN(HTTP/2, gRPC)
        - 클라우드에서 SSL termination(로드 밸런서에서 SSL 해제) 후 내부 트래픽은 평문 HTTP로 운영하는 패턴 등

    2. CDN 활용
        - CloudFront, Akamai, Cloudflare 등 CDN으로 정적 리소스 캐싱, 엣지 로직
        - 지리적 위치(Geo routing), DNS 기반 라우팅

    3. DDoS 대응
        - L3/L4 vs L7 공격 방어, Rate Limiting, Connection Reuse
        - AWS Shield, Cloudflare DDoS Protection, GCP Cloud Armor

    - **목표: 고트래픽 환경에서 네트워크 병목을 진단하고, 보안 + 성능을 모두 충족할 수 있도록 TCP/HTTP/HTTPS 레벨 최적화와 CDN, 로드 밸런싱을 적절히 적용할 수 있는 능력.**

    