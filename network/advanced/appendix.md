# 부록: 용어 정리 및 참고 자료

## A.1 네트워크 용어 사전

### 기본 용어
| 용어 | 설명 | 관련 예시 |
|-----|------|-----------|
| DNS (Domain Name System) | 도메인 이름을 IP 주소로 변환하는 시스템 | example.com → 93.184.216.34 |
| DHCP (Dynamic Host Configuration Protocol) | IP 주소를 자동으로 할당하는 프로토콜 | 새로운 기기 연결 시 자동 IP 할당 |
| NAT (Network Address Translation) | 사설 IP를 공인 IP로 변환하는 기술 | 192.168.1.100 → 203.0.113.1 |
| CIDR (Classless Inter-Domain Routing) | IP 주소 할당 방식 | 192.168.1.0/24 |
| VPN (Virtual Private Network) | 가상 사설망 | Site-to-Site VPN, Client VPN |

### 프로토콜 용어
| 용어 | 설명 | 일반적 용도 |
|-----|------|------------|
| TCP (Transmission Control Protocol) | 연결 지향적 전송 프로토콜 | 웹 브라우징, 이메일 |
| UDP (User Datagram Protocol) | 비연결형 전송 프로토콜 | DNS 쿼리, 스트리밍 |
| HTTP (Hypertext Transfer Protocol) | 웹 통신 프로토콜 | 웹 서비스 |
| HTTPS (HTTP Secure) | 암호화된 HTTP | 보안이 필요한 웹 통신 |
| WebSocket | 양방향 통신 프로토콜 | 실시간 채팅, 게임 |

### 보안 용어
| 용어 | 설명 | 사용 사례 |
|-----|------|-----------|
| SSL/TLS | 보안 계층 프로토콜 | HTTPS 암호화 |
| WAF (Web Application Firewall) | 웹 애플리케이션 방화벽 | SQL 인젝션 방어 |
| DDoS (Distributed Denial of Service) | 분산 서비스 거부 공격 | 대량의 트래픽 공격 |
| HSTS (HTTP Strict Transport Security) | HTTPS 강제 적용 정책 | 보안 연결 강제화 |
| CSP (Content Security Policy) | 콘텐츠 보안 정책 | XSS 공격 방어 |

### 인프라 용어
| 용어 | 설명 | 활용 예시 |
|-----|------|-----------|
| Load Balancer | 부하 분산 장치 | 트래픽 분산 |
| CDN (Content Delivery Network) | 콘텐츠 전송 네트워크 | 정적 콘텐츠 캐싱 |
| Proxy | 중계 서버 | 캐싱, 로드밸런싱 |
| Gateway | 네트워크 간 연결 지점 | 인터넷 접속점 |
| Router | 네트워크 경로 설정 장치 | 패킷 라우팅 |

## A.2 주요 명령어 모음

### 네트워크 진단 명령어
```bash
# 연결성 테스트
ping <host>              # ICMP 연결 테스트
traceroute <host>        # 경로 추적
mtr <host>               # 실시간 경로 분석

# DNS 조회
nslookup <domain>        # DNS 레코드 조회
dig <domain>            # 상세 DNS 정보 조회
host <domain>           # 도메인 정보 조회

# 네트워크 상태
netstat -tuln           # 활성 연결 확인
ss -tuln               # 소켓 상태 확인
iftop                  # 실시간 대역폭 모니터링
```

### 패킷 분석 명령어
```bash
# 패킷 캡처
tcpdump -i eth0        # 기본 패킷 캡처
tcpdump port 80        # 특정 포트 패킷 캡처
tcpdump host 1.2.3.4   # 특정 호스트 패킷 캡처

# 성능 테스트
ab -n 1000 -c 10 <url>  # Apache Benchmark
wrk -t12 -c400 -d30s <url>  # HTTP 벤치마크
```

## A.3 문제 해결 가이드

### 일반적인 문제와 해결 방법

1. 연결 문제
    - 증상: 서비스 접속 불가
    - 확인: ping, traceroute로 연결성 확인
    - 해결: 방화벽 규칙, 라우팅 테이블 확인

2. 성능 문제
    - 증상: 느린 응답 속도
    - 확인: top, htop으로 시스템 부하 확인
    - 해결: 리소스 모니터링, 병목 지점 파악

3. DNS 문제
    - 증상: 도메인 연결 실패
    - 확인: nslookup, dig로 DNS 응답 확인
    - 해결: DNS 서버 설정, 캐시 확인

## A.4 참고 자료

### RFC 문서

1. 네트워크 프로토콜
    - RFC 791: Internet Protocol
    - RFC 793: Transmission Control Protocol
    - RFC 768: User Datagram Protocol
    - RFC 2616: HTTP/1.1
    - RFC 7540: HTTP/2

2. 보안 프로토콜
    - RFC 5246: TLS 1.2
    - RFC 8446: TLS 1.3
    - RFC 6797: HSTS
    - RFC 7518: JSON Web Algorithms

### 기술 문서

1. 클라우드 서비스
    - AWS 네트워킹 가이드: https://docs.aws.amazon.com/vpc/latest/userguide/what-is-amazon-vpc.html
    - GCP 네트워크 설정: https://cloud.google.com/vpc/docs
    - Azure 네트워킹 기본: https://docs.microsoft.com/azure/networking/

2. 웹 서버
    - Nginx 문서: https://nginx.org/en/docs/
    - Apache 문서: https://httpd.apache.org/docs/
    - HAProxy 설정 가이드: http://www.haproxy.org/download/2.4/doc/configuration.txt

3. 모니터링 도구
    - Prometheus 문서: https://prometheus.io/docs/
    - Grafana 대시보드: https://grafana.com/docs/
    - ELK Stack 가이드: https://www.elastic.co/guide/index.html

## A.5 유용한 도구 모음

### 모니터링 도구

1. 시스템 모니터링
    - Prometheus + Grafana
    - Nagios
    - Zabbix
    - Datadog

2. 로그 분석
    - ELK Stack
    - Splunk
    - Graylog
    - Papertrail

### 네트워크 분석 도구

1. 패킷 분석
    - Wireshark
    - tcpdump
    - ngrep
    - Fiddler

2. 성능 테스트
    - Apache Benchmark (ab)
    - JMeter
    - k6
    - wrk

### 보안 도구

1. 취약점 스캐닝
    - Nmap
    - Nikto
    - OWASP ZAP
    - Burp Suite

2. 인증서 관리
    - Let`s Encrypt
    - Certbot
    - OpenSSL
    - mkcert