# 기본적인 네트워크 프로토콜 이해

1. TCP/IP 4계층 모델
    1. 개념 및 원리
        - TCP/IP 4계층 모델은 네트워크 통신의 기본 구조를 이해하는 데 필수적인 개념입니다.

        1. 애플리케이션 계층(L4)
            - HTTP, FTP, SSH, SMTP, DNS등 실제 서비스 프로토콜
            - 사용자와 가장 가까운 계층으로 직접적인 서비스 제공

        2. 전송 계층 (L3)
            - TCP, UDP 프로토콜이 동작
            - 신뢰성 있는 데이터 전송을 담당
            - 포트 번호를 사용한 프로세스 간 통신

        3. 인터넷 계층 (L2)
            - IP 프로토콜이 동작
            - 패킷의 라우팅과 전달을 담당
            - IP 주소를 사용한 호스트 간 통신

        4. 네트워크 접근 계층 (L1)
            - 이더넷, Wi-Fi 등 물리적 네트워크 인터페이스
            - MAC 주소를 사용한 물리적 주소 지정

    2. 주요 개념 상세 설명
        1. IP 주소 체계
            - IPv4: 32비트 주소 체계(예: 192.168.0.1)
            - 서브넷 마스크: 네트워크 부분과 호스트 부분 구분
            - CIDR 표기법: IP주소 범위를 간단히 표현(예: 192.168.0.0/24)

        2. ARP(Address Resolution Protocol)
            - IP 주소를 MAC 주소로 변환하는 프로토콜
            - 같은 네트워크 내에서 통신할 때 필수적
            - ARP 캐시를 통한 성능 최적화

        3. ICMP (Internel Control Message Protocol)
            - 네트워크 상태 및 에러 보고용 프로토콜
            - ping, traceroute 등의 기본이 되는 프로토콜
            - 네트워크 문제 진단에 필수적

2. TCP vs UDP
    1. TCP (Transmission Control Protocol)
        1. 특징:
            - 연결 지향적 프로토콜
            - 신뢰성 있는 데이터 전송
            - 흐름 제어와 혼잡 제어 제공

        2. 3-way Handshake
            - SYN: 클라이언트 -> 서버 (연결 요청)
            - SYN + ACK: 서버 -> 클라이언트 (요청 수락)
            - ACK: 클라이언트 -> 서버 (연결 설정)

        3. 주요 메커니즘
            - 흐름 제어: 수신측의 처리 속도에 맞춰 전송
            - 혼잡 제어: 네트워크 상황에 따른 전송량 조절
            - 오류 제어: 손실된 패킷 재전송

    2. UDP(User Datagram Protocol)
        1. 특징:
            - 비연결형 프로토콜
            - 신뢰성보다 속도 중시
            - 헤더가 단순하여 오버헤드 적음

        2. 활용 사례
            1. DNS 조회
            2. 실시간 스트리밍
            3. 온라인 게임
            4. VoIP 서비스

3. HTTP/HTTPS
    1. HTTP 특징
        - 클라이언트-서버 모델
        - Stateless 프로토콜
        - 요청-응답 방식의 통신

    2. HTTP 버전별 특징
        1. HTTP/1.1
            - 지속 연결(Keep-Alive) 지원
            - 파이프라이닝 도입
            - 호스트 헤더 필수화

        2. HTTP/2
            - 멀티플렉싱 지원
            - 헤더 압축
            - 서버 푸시 기능
            - 바이너리 프로토콜

        3. HTTP/3
            - QUIC 프로토콜 기반
            - UDP 사용으로 연결 설정 시간 단축
            - 향상된 멀티플렉싱

    3. HTTPS 보안
        - TLS/SSL 암호화 적용
        - 인증서를 통한 신원 확인
        - Perfect Forward Secrecy 지원

4. 실습 및 도구 활용
    1. 기본 네트워크 명령어
        ```bash
        # IP 구성 확인
        ifconfig   # Unix/Linux
        ipconfig   # Windows

        # 라우팅 테이블 확인
        route -n   # Unix/Linux
        route print # Windows

        # ARP 테이블 확인
        arp -a

        # DNS 조회
        nslookup example.com
        dig example.com
        ```

    2. 네트워크 연결 테스트
        ```bash
        # ICMP를 이용한 연결성 테스트
        ping 8.8.8.8

        # 경로 추적
        traceroute 8.8.8.8  # Unix/Linux
        tracert 8.8.8.8     # Windows

        # TCP 연결 테스트
        telnet example.com 80
        ```

5. Key Takeaways
    1. 네트워크 계층 이해
        - 각 계층의 역할과 책임이 명확히 구분
        - 문제 발생 시 해당 계층에 집중하여 해결

    2. TCP vs UDP 선택
        - 신뢰성이 중요하다면 TCP
        - 실시간성이 중요하다면 UDP

    3. HTTP/HTTPS 핵심
        - 모던 웹의 기반 프로토콜
        - 버전별 특징을 이해하여 적절히 활용
        - 보안을 위한 HTTPS 필수

6. 문제 해결 시나리오
    1. 시나리오1: 네트워크 연결 문제
        - 증상: 특정 서버 접속 불가
        - 확인 단계:
            1. ping으로 기본 연결성 확인
            2. traceroute로 경로 확인
            3. telnet으로 특정 포트 연결 테스트

    2. 시나리오2: DNS 문제
        - 증상: 도메인 연결 안됨
        - 확인 단계:
            1. nslookup으로 DNS 응답 확인
            2. dig로 상세 DNS 정보 확인
            3. /etc/reslov.conf 설정 확인

    3. 시나리오3: TCP 연결 문제
        - 증상: 애플리케이션 타임아웃
        - 확인 단계:
            1. netstat로 연결 상태 확인
            2. tcpdump로 패킷 흐름 분석
            3. 방화벽 설정 확인