# 네트워크 기초(Basic) 디렉토리

이 디렉토리는 네트워크를 처음 접하거나 기초 지식을 탄탄히 하고 싶은 분들을 위해 준비되었습니다.
OSI 모델부터 TCP/IP, IP 주소 체계, TCP/UDP 동작, 그리고 HTTP/HTTPS 등 핵심 프로토콜의 기본 원리를 이해하는 데 초점을 맞춥니다.

## 디렉토리 구성 (Files Overview)

현재 `basic/`디렉토리에는 다음과 같은 문서들이 있습니다:

1. `01_osi_and_tcpip.md`
    - OSI 7계층과 TCP/IP 4계층의 개념 비교
    - 각 계층의 역할과 대표 프로토콜 예시
    - 데이터가 어떻게 “캡슐화(encapsulation)” 과정을 통해 전송되는지 이해

2. `02_ip_addressing.md`
    - IP 주소(IPv4) 구조, 서브넷 마스크, CIDR 표기법
    - 게이트웨이, ARP, ICMP 등 IP 계층의 핵심 개념
    - LAN과 WAN에서 IP가 어떻게 라우팅되는지 기본 원리

3. `03_tcp_udp_details.md`
    - TCP의 3-way handshake, 4-way 종료, 시퀀스/ACK 번호, 흐름 제어, 혼잡 제어
    - UDP 헤더 구조, 비연결형 특성, 주요 활용 사례(DNS, 스트리밍 등)
    - 각 프로토콜을 Wireshark/tcpdump로 간단히 살펴보는 예시

4. `04_http_https.md`
    - HTTP/1.1, HTTP/2, HTTP/3(QUIC) 개념 비교
    - 요청/응답 구조, 메서드(GET/POST 등), 상태 코드, 쿠키
    - TLS/SSL 동작 방식, HTTPS 보안, 인증서 개념(서명·체인)

5. `05_dns.md`
    - 

## 학습 순서 (Recommanded Reading Order)

1. OSI & TCP/IP -> 네트워크 계층화 개념을 먼저 이해
2. IP 주소 & ARP/ICMP -> 패킷이 실제로 어떤 경로를 통해 전달되는지 익히기
3. TCP/UDP -> 연결 지향 vs 비연결형 프로토콜의 차이와 내부 동작 구조 파악
4. HTTP/HTTPS -> 웹 통신의 기본 프로토콜 및 보안(암호화) 기초
5. dns

## 문서 특징 (Key Points)

* 기초 지식에 충실: 용어 정의와 배경 지식을 충분히 제공
* 그림/예시/실습 위주: 가능하다면 다이어그램, Wireshark 캡처 샘플을 통해 시각화
* 설계 철학 설명: 단순 암기보다는 "왜 이런 구조로 동작하는가?" 배경을 알 수 있도록 서술
* 초심자 친화적: 복잡한 부분은 추가 자료나 `advenced/` 디렉토리로 연결

## 학습 팁 (Study Tips)

1. 차근차근 따라하기
    - 문서를 읽으며, 실제로 `ping`, `traceroute`, `tcpdump` 등의 명령어를 직접 실행해 보세요.
    - IP 주소, 포트, 프로토콜 필드를 눈으로 확인하면 이해도가 훨씬 높아집니다.

2. Wireshark 실습 권장
    - TCP 3-way handshake나 HTTP 요청/응답을 캡처해보면, 프로토콜 헤더 구조가 명확해집니다.
    - "아, 이 필드가 시퀀스 번호구나!" "여기서 TLS 핸드셰이크가 일어나는구나!" 직접 확인 가능.

3. 추가 질문
    - "왜 ARP가 필요한가?" "TCP 혼잡 제어는 어떻게 작동?" 등 의문이 생기면 스스로 리서치 or Issue/PR로 질문.
    - 문서를 개선하거나 토론하면서 학습 효과를 높일 수 있습니다.

## 앞으로의 확장 (Future Extensions)

* DNS Basics: DNS 동작 원리, 레코드 유형(A, CNAME, MX 등), 재귀/권위DNS 구분
* 이메일 프로토콜: SMTP, POP3, IMAP 동작 구조
* IPv6: IPv6 주소 구조, Neighbor Discovery, IPv6 라우팅 기초
* LAN 스위칭(이더넷, VLAN 등): L2 스위치, MAC 테이블, VLAN 트렁킹 등