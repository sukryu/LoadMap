# OSI와 TCP/IP 모델 이해

## 1. 들어가기 (Introduction)

오늘날 컴퓨터 네트워크는 매우 복잡하고 다양한 기기·프로토콜이 상호 작용합니다.  
이 복잡성을 해결하기 위해 "계층화" 개념이 등장했으며, 그 대표 모델이 **OSI 7계층**과 **TCP/IP 4계층**입니다.

### 네트워크 계층화의 필요성
- 복잡한 네트워크 통신을 **단순화**하고 **표준화**하기 위한 접근  
- 각 계층별로 독립적으로 발전·유지보수 가능  
- 다양한 벤더/기기 간 **호환성** 보장

### 학습 목표
- OSI 7계층과 TCP/IP 4계층의 **개념과 차이점** 이해  
- 데이터가 각 계층을 거쳐 전송되는 **캡슐화 과정** 파악  
- 실무에서 자주 쓰이는 프로토콜들의 **계층별 분류** 학습

## 2. OSI 7계층 모델

### 2.1 OSI 모델 개념과 탄생 배경
- **1984년 ISO(국제표준화기구)**에서 제정  
- 당시 벤더별로 파편화된 네트워크 기술을 통합하기 위한 표준 프레임워크
- **개방형 시스템** 간의 상호운용성을 높이는 목적

## 계층별 역할(1 ~ 7계층)

1. 물리 계층(Physical Layer)
    - 비트(0, 1) 단위의 데이터를 전기 신호로 변환
    - 전송 매체, 전압, 핀 배치 등 물리적 특성 정의
    - 예: 리피터, 허브, 케이블, 광섬유

2. 데이터링크 계층(Data Link Layer)
    - 노드 간 신뢰성 있는 데이터 전송 보장
    - MAC 주소 기반의 통신
    - 예: 이더넷, 스위치, 브리지

3. 네트워크 계층(Network Layer)
    - 종단 간 패킷 라우팅과 전달
    - 논리적 주소(IP) 사용
    - 예: 라우터, IP, ICMP

4. 전송 계층(Transport Layer)
    - 종단 간 신뢰성 있는 데이터 전송
    - 흐름제어, 오류제어, 분할과 재조립
    - 예: TCP, UDP

5. 세션 계층(Session Layer)
    - 양 끝단의 프로세스 간 통신 세션 관리
    - 연결 설정, 유지, 종료
    - 예: NetBIOS, RPC
    
6. 프레젠테이션 계층(Presentation Layer)
    - 데이터 형식 변환, 압축, 암호화
    - 데이터 인코딩, 디코딩
    - 예: SSL/TLS, JPEG, ASCII

7. 응용 계층(Application Layer)
    - 최종 사용자의 인터페이스 제공
    - 이메일, 파일 전송, 웹 브라우징 등
    - 예: HTTP, FTP, SMTP, DNS

## OSI 모델 다이어그램

<img src="https://www.gklibrarykor.com/wp-content/uploads/2024/10/1_OSI-7%EA%B3%84%EC%B8%B5-%EB%AA%A8%EB%8D%B8.jpg">

# TCP/IP 4계층 모델

## TCP/IP 탄생 배경과 인터넷 역사

1. 역사적 배경
    - 1969년 미국 국방부 DARPA 프로젝트로 시작
    - ARPANET을 통한 초기 인터넷 구축
    - 1983년 TCP/IP가 공식 프로토콜로 채택
    - 현재 인터넷의 실질적 표준 프로토콜

2. 설계 목표
    - 네트워크 쟁애에도 생존 가능한 견고한 아키텍처
    - 다양한 통신 서비스를 수용할 수 있는 유연성
    - 서로 다른 네트워크 간 연결 가능한 개방성

## 4계층 구조

1. 네트워크 접근 계층(Network Access/Link Layer)
    - 물리적 네트워크 매체와의 인터페이스 제공
    - MAC 주소를 이용한 로컬 통신
    - 주요 프로토콜/기술:
        - 이더넷(Ethernet)
        - Wi-Fi(IEEE 802.11)
        - PPP(Point-to-Point Protocol)

2. 인터넷 계층(Internet Layer)
    - 데이터그램 패킷 전달 및 라우팅
    - IP주소 기반 통신
    - 주요 프로토콜:
        - IP(Internet Protocol)
        - ICMP(Internet Control Message Protocol)
        - ARP(Address Resolution Protocol)

3. 전송 계층(Transport Layer)
    - 종단 간 통신 제어
    - 연결/비연결 지향 서비스 제공
    - 주요 프로토콜:
        - TCP(Transmission Control Protocol)
        - UDP(User Datagram Protocol)

4. 애플리케이션 계층(Application Layer)
    - 사용자 레벨의 응용 프로그램 지원
    - 다양한 네트워크 서비스 제공
    - 주요 프로토콜:
        - HTTP/HTTPS(웹)
        - FTP(파일 전송)
        - SMTP/POP3/IMAP(이메일)
        - DNS(도메인 이름 해석)
        - SSH(보안 원격 접속)

## TCP/IP 다이어그램

<img src="https://velog.velcdn.com/images/hey-hey/post/a4828faf-9e85-478b-8271-31897b9fd12c/image.png">

# OSI vs TCP/IP 비교

## 계층별 매핑

1. TCP/IP 애플리케이션 계층 = OSI 5, 6, 7계층
    - OSI의 응용 계층(7)
    - OSI의 프레젠테이션 계층(6)
    - OSI의 세션 계층(5) -> TCP/IP는 이 세 계층의 기능을 하나로 통합

2. TCP/IP 전송 계층 = OSI 전송 계층(4)
    - 완전히 일치하는 계층
    - TCP, UDP 프로토콜이 대표적
    - 종단 간 통신 담당

3. TCP/IP 인터넷 계층 = OSI 네트워크 계층(3)
    - IP 프로토콜 중심
    - 패킷 라우팅과 전달 담당

4. TCP/IP 네트워크 접근 계층 = OSI 1, 2계층
    - OSI의 물리 계층(1)
    - OSI의 데이터링크 계층(2) -> TCP/IP는 이 두 계층을 하나로 통합

## 실무 관점: 실제로 OSI vs TCP/IP 중 어느 것을 주로 쓰나?

1. TCP/IP 모델의 장점
    - 실제 인터넷의 표준 프로토콜
    - 단순하고 구현하기 쉬운 구조
    - 계층이 더 적어 관리가 용이

2. OSI 모델의 가치
    - 교육 및 문제 해결 시 참조 모델로 유용
    - 네트워크 기능을 더 세분화하여 이해 가능
    - 벤더 중립적인 표준 제공

3. 실무에서의 활용
    - 문제 해결 시: OSI 모델 참조
    - 실제 구현 시: TCP/IP 모델 사용
    - 두 모델의 장점을 상호보완적으로 활용

<img src="https://velog.velcdn.com/images/xgro/post/a6003bf5-647d-4f87-b363-98d020306f4a/image.png">

# 데이터 캡슐화 과정(Encapsulation)

## OSI/TCP/IP 관점에서의 Encapsulation

1. 캡슐화 기본 개념
    - 상위 계층에서 하위 계층으로 데이터가 전달될 떄 각 계층의 헤더가 추가되는 과정
    - 각 계층은 자신만의 헤더 정보를 덧붙임
    - 최종적으로 물리 계층에서 비트 스트림으로 변환

2. 계층별 데이터 단위(PDU: Protocol Data Unit)
    - 애플리케이션 계층: 메시지(Message)
    - 전송 계층: 세그먼트(TCP) / 데이터그램(UDP)
    - 인터넷 계층: 패킷(Packet)
    - 네트워크 접근 계층: 프레임(Frame)

3. 디캡슐화(Decapsulation)
    - 수신 측에서 역순으로 진행
    - 각 계층에서 해당 계층의 헤더를 제거
    - 최종적으로 원본 데이터 복원

## 전송 예시: "Hello"메시지가 어떻게 각 계층을 지나는가?

1. 애플리케이션 계층
    - 원본 데이터: "Hello"
    - HTTP 헤더 추가(메시지)

2. 전송 계층
    - TCP 헤더 추가
    - 출발지/목적지 포트 번호
    - 시퀀스 번호, 확인 응답 번호
    - -> TCP 세그먼트 생성

3. 인터넷 계층
    - IP 헤더 추가
    - 출발지/목적지 IP 주소
    - -> IP 패킷 생성

4. 네트워크 접근 계층
    - MAC 헤더와 트레일러 추가
    - 출발지/목적지 MAC 주소
    - -> 이더넷 프레임 생성

<img src="https://www.computernetworkingnotes.com/wp-content/uploads/ccna-study-guide/images/csg25-03-tcp-ip-encapsulation.png">

# 네트워크 계층별 예시 프로토콜

## OSI 7계층별 대표 프로토콜

1. 물리 계층(L1)
    - RS-232, RS-449, X.21
    - IEEE 802.3 (이더넷 물리 규격)
    - 광섬유 규격(SONET/SDH)

2. 데이터링크 계층(L2)
    - 이더넷(Ethernet)
    - PPP(Point-to-Point Protocol)
    - HDLC(High-level Data Link Control)
    - MAC(Media Access Control)

3. 네트워크 계층 (L3)
    - IP(Internet Protocol)
    - ICMP(Internet Control Message Protocol)
    - IGMP(Internet Group Management Protocol)
    - RIP, OSPF(라우팅 프로토콜)

4. 전송 계층 (L4)
    - TCP(Transmission Control Protocol)
    - UDP(User Datagram Protocol)
    - SCTP(Stream Control Transmission Protocol)

5. 세션 게층 (L5)
    - NetBIOS
    - RPC(Remote Procedure Call)
    - PPTP(Point-to-Point Tunneling Protocol)

6. 프레젠테이션 계층 (L6)
    - SSL/TLS
    - JPEG, GIF, MPEG
    - ASCII, EBCDIC

7. 응용 계층 (L7)
    - HTTP/HTTPS(웹)
    - SMTP, POP3, IMAP(이메일)
    - DNS(도메인 이름 시스템)
    - SSH(보안 쉘)
    - Telnet(원격 접속)

## TCP/IP 4계층 대표 프로토콜

1. 네트워크 접근 계층
    - 이더넷(Ethernet)
    - Wi-Fi(IEEE 802.11)
    - PPP
    - ARP(Address Resolution Protocol)

2. 인터넷 계층
    - IPv4/IPv6
    - ICMP
    - IGMP
    - 라우팅 프로토콜(RIP, OSPF, BGP)

3. 전송 계층
    - TCP
    - UDP
    - SCTP

4. 애플리케이션 계층
    - HTTP/HTTPS
    - FTP/SFTP
    - SMTP/POP3/IMAP
    - DNS
    - SSH/Telnet
    - SNMP(네트워크 관리)

| OSI모델 | TCP/IP 모델 | 주요 프로토콜 |
|-----|------|------------|
| 7. 응용 계층 | 4. 응용 계층 | HTTP, FTP, SMTP, SSH, DNS, Telnet, DHCP |
| 6. 응용 계층 | 4. 응용 계층 | ASCII, MPEG, JPEG |
| 5. 응용 계층 | 4. 응용 계층 | SSH, TLS, RPC |
| 4. 응용 계층 | 3. 전송 계층 | TCP, UDP |
| 3. 응용 계층 | 2. 인터넷 계층 | IP. ICMP, ARP, RARP, OSPF, BGP |
| 2. 응용 계층 | 1. 네트워크 인터페이스 계층 | 이더넷(Ethernet), PPP, UART |
| 1. 응용 계층 | 1. 네트워크 인터페이스 계층 | 1000BASE-T, RS-232, RS-485 |

# 요약 (Summary)

1. 네트워크 계층화의 의미
    - 복잡한 네트워크 통신을 논리적으로 분리
    - 각 계층의 독립적 발전과 유지보수 가능
    - 표준화를 통한 상호운용성 확보

2. OSI 7계층 vs TCP/IP 4계층
    - OSI: 이론적/교육적 참조 모델
    - TCP/IP: 실제 인터넷 구현의 표준
    - 두 모델은 상호보완적으로 활용

3. 데이터 캡슐화 프로세스
    - 각 계층별로 헤더 정보 추가
    - 계층별 PDU(Protocol Data Unit) 변화
    - 수신 측에서는 역순으로 디캡슐화

4. 핵심 이해 포인트
    - 각 계층은 독립적 기능 수행
    - 상위 계층은 하위 계층의 구현 세부사항을 몰라도 됨
    - 계층 간 인터페이스만 지키면 내부 구현 변경 가능

# 참고 자료 (References)

1. 표준 문서
    - RFC 1122, 1123 (TCP/IP 아키텍처)
    - ISO/IEC 7498-1 (OSI 모델 표준)

2. 추천 도서
    - "Computer Networks" by Andrew S. Tanenbaum
    - "TCP/IP Illustrated" by W. Richard Stevens
    - "Computer Networking: A Top-Down Approach" by Kurose & Ross

3. 다음 학습 주제 안내
    - IP 주소 체계와 서브네팅 (`02_ip_addressing.md`)
    - TCP/UDP 상세 동작 원리 (`03_tcp_udp_details.md`)
    - HTTP/HTTPS 프로토콜 (`04_http_https.md`)