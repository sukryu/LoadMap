# 네트워크 설계 & 인프라 구성

1. 네트워크 설계 기초
    1. 네트워크 설계 원칙
        1. 확장 (Scalability)
            - 향후 성장을 고려한 IP주소 할당
            - 모듈화된 네트워크 구성
            - 유연한 서브넷 구성

        2. 가용성 (Availability)
            - 이중화 구성
            - 장애 복구 계획
            - 백업 경로 확보

        3. 보안성 (Security)
            - 계층적 보안 구조
            - DMZ 구성
            - 접근 제어 정책

        4. 관리 용이성 (Manageability)
            - 명확한 네트워크 문서화
            - 모니터링 체계
            - 표준화된 명명 규칙

2. 서브넷팅 & VPC 설계
    1. 서브넷 설계 기본
        1. CIDR 블록 계획
            ```plaintext
            10.0.0.0/16 (전체 VPC)
            ├── 10.0.0.0/24 (Public Subnet A)
            ├── 10.0.1.0/24 (Public Subnet B)
            ├── 10.0.2.0/24 (Private Subnet A)
            └── 10.0.3.0/24 (Private Subnet B)
            ```

        2. 가용 영역 고려사항
            - 최소 2개 이상의 가용 영역 사용
            - 각 가용 영역에 동일한 구성 배치
            - 자동 장애 복구 고려

    2. VPC 구성 요소
        1. Internet Gateway
            - 인터넷 연결 제공
            - Public 서브넷 연결
            - NAT Gateway 구성

        2. NAT Gateway/Instance
            - Private 서브넷의 외부 접속
            - 고가용성 구성
            - 비용 최적화 고려

        3. Route Tables 
            ```plaintext
            # Public Route Table
            Destination     Target
            10.0.0.0/16    local
            0.0.0.0/0      igw-xxxxx

            # Private Route Table
            Destination     Target
            10.0.0.0/16    local
            0.0.0.0/0      nat-xxxxx
            ```

3. DNS 설계 및 구성
    1. DNS 레코드 설계
        1. A 레코드
            ```plaintext
            www.example.com.    IN A    192.0.2.1
            api.example.com.    IN A    192.0.2.2
            ```

        2. CNAME 레코드
            ```plaintext
            dev.example.com.    IN CNAME   www.example.com.
            stage.example.com.  IN CNAME   www.example.com.
            ```

        3. Route 53 구성(AWS 기준)
            - Weighted Routing
            - Latency-based Routing
            - Geolocation Routing
            - Failover Routing

    2. DNS 보안 및 최적화
        1. DNSSEC 구성
        2. TTL 최적화
        3. DNS 캐싱 전략

4. 로드 밸런서 구성
    1. Layer4 로드 밸런서
        1. TCP/UDP 부하 분산
            ```nginx
            stream {
                upstream backend {
                    server backend1.example.com:12345;
                    server backend2.example.com:12345;
                }
                
                server {
                    listen 12345;
                    proxy_pass backend;
                }
            }
            ```

        2. 세션 지속성 구성
            - Source IP 기반
            - Connection 드레이닝

    2. Layer7 로드 밸런서
        1. HTTP/HTTPS 구성
            ```nginx
            http {
                upstream web_backend {
                    server web1.example.com:8080;
                    server web2.example.com:8080;
                    least_conn;
                }
                
                server {
                    listen 80;
                    server_name example.com;
                    
                    location / {
                        proxy_pass http://web_backend;
                        proxy_set_header Host $host;
                        proxy_set_header X-Real-IP $remote_addr;
                    }
                }
            }
            ```

        2. SSL/TLS 종단
            - 인증서 관리
            - SSL 세션 캐시
            - OCSP Stapling

5. 방화벽 & 보안 그룹
    1. 보안 그룹 설계
        ```plaintext
        # Web Tier Security Group
        Inbound:
        - HTTP (80) from 0.0.0.0/0
        - HTTPS (443) from 0.0.0.0/0
        - SSH (22) from Admin IP

        # App Tier Security Group
        Inbound:
        - Custom TCP (8080) from Web Tier
        - SSH (22) from Bastion Host

        # DB Tier Security Group
        Inbound:
        - MySQL (3306) from App Tier
        - SSH (22) from Bastion Host
        ```

    2. 네트워크 ACL 구성
        ```plaintext
        # Inbound Rules
        Rule # | Type      | Protocol | Port | Source    | Allow/Deny
        100    | HTTP      | TCP      | 80   | 0.0.0.0/0 | ALLOW
        110    | HTTPS     | TCP      | 443  | 0.0.0.0/0 | ALLOW
        120    | Custom TCP| TCP      | 1024-65535 | 0.0.0.0/0 | ALLOW
        * | All Traffic | All      | All  | 0.0.0.0/0 | DENY

        # Outbound Rules
        100    | All Traffic| All      | All  | 0.0.0.0/0 | ALLOW
        * | All Traffic | All      | All  | 0.0.0.0/0 | DENY
        ```

6. 모니터링 구성
    1. 네트워크 모니터링 지표
        1. 기본 지표
            - 대역폭 사용량
            - 패킷 손실률
            - 지연시간
            - 에러율

        2. 고급 지표
            - 연결 상태
            - TCP 재전송률
            - DNS 응답 시간
            - SSL 핸드셰이크 시간

    2. 알림 설정
        ```yaml
        alerts:
        high_latency:
            condition: latency > 100ms
            duration: 5m
            severity: warning
            
        packet_loss:
            condition: packet_loss_rate > 1%
            duration: 1m
            severity: critical
        ```

7. 문제 해결 가이드
    1. 일반적인 문제와 해결방안
        1. 연결성 문제
            - VPC 피어링 상태 확인
            - 라우팅 테이블 검증
            - 보안 그룹/NACL 규칙 검토

        2. 성능 문제
            - 네트워크 대역폭 모니터링
            - 리소스 사용량 확인
            - 로드 밸런서 상태 점검

        3. DNS 문제
            - DNS 레코드 확인
            - Route 53 상태 점검
            - TTL 설정 검토

8. Key Takeaways
    1. 설계 원칙
        - 확장성, 가용성, 보안성을 모두 고려
        - 문서화와 표준화의 중요성

    2. 구성 요소
        - VPC와 서브넷의 적절한 설계
        - 보안 계층화
        - 이중화 구성의 중요성

    3. 운영 관리
        - 모니터링 체계 구축
        - 문제 해결 프로세스 수립
        - 지속적인 최적화