# 트러블 슈팅 & 모니터링

1. 패킷 분석 기법
    1. tcpdump 활용
        1. 기본 사용법
            ```bash
            # 특정 인터페이스의 모든 트래픽 캡처
            tcpdump -i eth0

            # 특정 호스트와의 통신만 캡처
            tcpdump host 192.168.1.100

            # 특정 포트의 트래픽만 캡처
            tcpdump port 80

            # HTTP 트래픽 상세 분석
            tcpdump -A -s0 'tcp port 80'
            ```

        2. 고급 필터링
            ```bash
            # TCP SYN 패킷만 캡처
            tcpdump 'tcp[tcpflags] & (tcp-syn) != 0'

            # TCP RST 패킷 확인
            tcpdump 'tcp[tcpflags] & (tcp-rst) != 0'

            # ICMP 오류 메시지 캡처
            tcpdump 'icmp[icmptype] != 8 and icmp[icmptype] != 0'
            ```

    2. Wireshark 분석
        1. 캡처 필터
            ```plaintext
            ip.addr == 192.168.1.100 and tcp.port == 80
            http.request.method == "POST"
            tcp.flags.syn == 1
            ```

        2. 주요 분석 포인트
            - TCP 핸드셰이크 과정
            - 재전송 패턴
            - TCP 윈도우 크기 변화
            - HTTP 요청/응답 시간

2. 네트워크 성능 분석
    1. 대역폭 측정
        1. iperf3 활용
            ```bash
            # 서버 측
            iperf3 -s

            # 클라이언트 측
            iperf3 -c server_ip -t 30 -P 4
            ```

        2. 측정 지표
            - 처리량(Throughput)
            - 지연 시간(Latency)
            - 패킷 손실률(Packet Loss)
            - 지터 (Jitter)

    2. 네트워크 지연 분석
        1. ping 상세 분석
            ```bash
            # 상세 통계와 함께 ping
            ping -c 100 -i 0.2 target_host | tee ping_log.txt

            # 결과 분석
            awk '/time=/ {sum+=$7} END {print "Average = ", sum/NR}' ping_log.txt
            ```

        2. MTR (My TraceRoute) 활용
            ```bash
            # 상세 경로 분석
            mtr -r -c 100 target_host

            # 결과 해석
            - Loss%: 각 홉에서의 패킷 손실률
            - Snt: 전송된 패킷 수
            - Last: 마지막 RTT
            - Avg: 평균 RTT
            - Best: 최소 RTT
            - Wrst: 최대 RTT
            - StDev: 표준 편차
            ```

3. 시스템 레벨 모니터링
    1. 네트워크 소켓 상태
        1. netstat 분석
            ```bash
            # 연결 상태 확인
            netstat -tunapee

            # TIME_WAIT 상태 분석
            netstat -nat | grep TIME_WAIT | wc -l

            # ESTABLISHED 연결 수
            netstat -nat | grep ESTABLISHED | wc -l
            ```

        2. ss 명령어 활용
            ```bash
            # 상세 소켓 정보
            ss -tip

            # 수신 버퍼 크기 확인
            ss -tim

            # 혼잡 윈도우 크기 확인
            ss -timi
            ```

    2. 시스템 리소스 모니터링
        1. sar 활용
            ```bash
            # 네트워크 인터페이스 통계
            sar -n DEV 1

            # TCP 통계
            sar -n TCP 1

            # 네트워크 에러
            sar -n EDEV 1
            ```

        2. nload 모니터링
            ```bash
            # 실시간 대역폭 모니터링
            nload eth0
            ```

4. 로그 분석 및 트러블 슈팅
    1. 시스템 로그 분석
        1. 주요 로그 파일
            ```plaintext
            /var/log/messages
            /var/log/syslog
            /var/log/dmesg
            ```

        2. 로그 분석 도구
            ```bash
            # 실시간 로그 모니터링
            tail -f /var/log/syslog | grep --line-buffered "NetworkManager"

            # 특정 시간대 로그 추출
            awk '/Jun 15 10:0/{p=1}p' /var/log/syslog
            ```

    2. 네트워크 문제 패턴 분석
        1. 연결 문제
            ```plaintext
            - TCP 재전송 증가
            - 비정상적인 RST 패킷
            - 높은 latency
            ```

        2. 성능 문제
            ```plaintext
            - 버퍼 오버플로우
            - NIC 드롭
            - TCP 윈도우 크기 제한
            ```

5. QoS 및 트래픽 제어
    1. Traffic Shaping
        1. tc 명령어 활용
            ```bash
            # HTB를 사용한 대역폭 제한
            tc qdisc add dev eth0 root handle 1: htb default 12
            tc class add dev eth0 parent 1: classid 1:1 htb rate 100mbit ceil 100mbit
            tc class add dev eth0 parent 1:1 classid 1:12 htb rate 60mbit ceil 100mbit
            ```

        2. iptables 마킹
            ```bash
            # 특정 트래픽 마킹
            iptables -A PREROUTING -t mangle -p tcp --dport 80 -j MARK --set-mark 1
            ```

    2. Rate Limiting
        1. nginx rate limiting
            ```nginx
            http {
                limit_req_zone $binary_remote_addr zone=one:10m rate=10r/s;
                
                server {
                    location /api/ {
                        limit_req zone=one burst=20 nodelay;
                    }
                }
            }
            ```

        2. HAProxy rate limiting
            ```haproxy
            frontend web
                stick-table type ip size 100k store http_req_rate(10s)
                tcp-request content track-sc0 src
                tcp-request content reject if { src_http_req_rate gt 100 }
            ```

6. 트러블슈팅 시나리오
    1. 시나리오1: 높은 지연시간
        1. 증상
            - 애플리케이션 응답 지연
            - 간헐적 타임아웃

        2. 분석 단계
            ```bash
            # 1. 경로 분석
            mtr target_host

            # 2. TCP 연결 상태
            netstat -ant | grep ESTABLISHED

            # 3. 패킷 캡처
            tcpdump -i eth0 -w capture.pcap host target_host
            ```

        3. 해결 방안
            - 네트워크 경로 최적화
            - TCP 튜닝
            - 로드밸런서 설정 조정

    2. 시나리오2: 간헐적 연결 끊김
        1. 증상
            - TCP 연결 리셋
            - 애플리케이션 에러

        2. 분석 단계
            ```bash
            # 1. TCP 재전송 확인
            netstat -s | grep retransmitted

            # 2. 네트워크 인터페이스 에러
            ifconfig eth0 | grep errors

            # 3. 시스템 로그 확인
            dmesg | grep eth0
            ```

        3. 해결 방안
            - NIC 설정 최적화
            - TCP keepalive 조정
            - MTU 크기 조정

7. Key Takeaways
    1. 문제 해결 접근법
        - 체계적인 분석 방법론
        - 적절한 도구 활용
        - 로그와 메트릭 중요성

    2. 성능 최적화
        - 병목 구간 식별
        - 시스템 튜닝
        - 지속적 모니터링

    3. 예방적 관리
        - 모니터링 시스템 구축
        - 알림 임계치 설정
        - 정기적인 성능 검토