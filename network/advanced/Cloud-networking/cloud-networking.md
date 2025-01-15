# 클라우드 환경에서의 네트워크

1. 클라우드 네트워크 기초
    1. 클라우드 네트워크의 특징
        1. 가상화 기반 네트워크
            - 소프트웨어 정의 네트워킹 (SDN)
            - 동적 리소스 할당
            - 탄력적 확장/축소

        2. 멀티 테넌시
            - 리소스 격리
            - 보안 경계 설정
            - 네트워크 격리

        3. 글로벌 인프라
            - 리전 간 연결
            - 엣지 로케이션
            - 글로벌 로드밸런싱

2. VPC (Virtual Private Cloud) 심화
    1. VPC 디자인 패턴
        1. 기본 패턴
            ```plaintext
            VPC (10.0.0.0/16)
            ├── Public Subnet (10.0.1.0/24)
            │   ├── NAT Gateway
            │   ├── Bastion Host
            │   └── Load Balancer
            ├── Private App Subnet (10.0.2.0/24)
            │   └── Application Servers
            └── Private DB Subnet (10.0.3.0/24)
                └── Database Servers
            ```

        2. 멀티 AZ 패턴
            ```plaintext
            VPC (10.0.0.0/16)
            ├── AZ-1
            │   ├── Public Subnet (10.0.1.0/24)
            │   ├── Private App Subnet (10.0.2.0/24)
            │   └── Private DB Subnet (10.0.3.0/24)
            └── AZ-2
                ├── Public Subnet (10.0.4.0/24)
                ├── Private App Subnet (10.0.5.0/24)
                └── Private DB Subnet (10.0.6.0/24)
            ```

    2. VPC 엔드포인트
        1. 인터페이스 엔드포인트
            ```hcl
            # Terraform 예시
            resource "aws_vpc_endpoint" "s3" {
                vpc_id       = aws_vpc.main.id
                service_name = "com.amazonaws.region.s3"
                
                private_dns_enabled = true
                security_group_ids = [aws_security_group.endpoint.id]
                subnet_ids         = aws_subnet.private[*].id
            }
            ```

        2. 게이트웨이 엔드포인트
            ```hcl
            resource "aws_vpc_endpoint" "dynamodb" {
                vpc_id       = aws_vpc.main.id
                service_name = "com.amazonaws.region.dynamodb"
                
                route_table_ids = [aws_route_table.private.id]
            }
            ```

3. 클라우드 로드밸런싱
    1. Application Load Balancer (L7)
        1. 구성 예시
            ```yaml
            apiVersion: v1
            kind: Service
            metadata:
                name: web-service
            spec:
                type: LoadBalancer
                ports:
                - port: 80
                    targetPort: 8080
                selector:
                    app: web
            ```

        2. 주요 기능
            - 경로 기반 라우팅
            - 호스트 기반 라우팅
            - SSL/TLS 종단
            - WebSocket 지원

    2. Network Load Balancer (L4)
        1. 구성 예시
            ```hcl
            resource "aws_lb" "nlb" {
                name               = "network-lb"
                internal           = false
                load_balancer_type = "network"
                subnets           = aws_subnet.public[*].id
                
                enable_cross_zone_load_balancing = true
            }
            ```

        2. 특징
            - 고성능 TCP/UDP 처리
            - 정적 IP 지원
            - 낮은 지연시간

4. 클라우드 네트워크 보안
    1. 보안 그룹 설계
        1. 계층별 보안 그룹
            ```plaintext
            # Web Tier
            Inbound:
                - HTTP (80) from 0.0.0.0/0
                - HTTPS (443) from 0.0.0.0/0

            # App Tier
            Inbound:
                - Custom TCP (8080) from Web Tier
                - Custom TCP (9000) from Monitoring

            # DB Tier
            Inbound:
                - MySQL (3306) from App Tier
                - PostgreSQL (5432) from App Tier
            ```

        2. 보안 그룹 연계
            ```hcl
            resource "aws_security_group_rule" "app_to_db" {
                type                     = "ingress"
                from_port               = 3306
                to_port                 = 3306
                protocol                = "tcp"
                source_security_group_id = aws_security_group.app.id
                security_group_id       = aws_security_group.db.id
            }
            ```

    2. WAF (Web Application Firewall)
        1. 규칙 설정
            ```yaml
            Rules:
            - Name: "Block SQL Injection"
                Priority: 1
                Action: BLOCK
                Conditions:
                - SQLi patterns
            
            - Name: "Rate Limit by IP"
                Priority: 2
                Action: BLOCK
                RateLimit: 2000/5m
            ```

        2. 지리적 제한
            ```json
            {
                "GeoMatch": {
                    "CountryCodes": ["US", "CA", "GB"],
                    "Action": "ALLOW",
                    "DefaultAction": "BLOCK"
                }
            }
            ```

5. 서비스메시 아키텍처
    1. Istio 구성
        1. 기본 설정
            ```yaml
            apiVersion: networking.istio.io/v1alpha3
            kind: VirtualService
            metadata:
                name: reviews-route
            spec:
                hosts:
                - reviews
                http:
                - route:
                    - destination:
                        host: reviews
                        subset: v1
                    weight: 75
                    - destination:
                        host: reviews
                        subset: v2
                    weight: 25
            ```

        2. 트래픽 관리
            ```yaml
            apiVersion: networking.istio.io/v1alpha3
            kind: DestinationRule
            metadata:
                name: reviews-destination
            spec:
                host: reviews
                trafficPolicy:
                    loadBalancer:
                    simple: ROUND_ROBIN
                subsets:
                - name: v1
                    labels:
                    version: v1
                - name: v2
                    labels:
                    version: v2
            ```

    2. 서비스 디스커버리
        1. DNS 기반
            ```yaml
            apiVersion: v1
            kind: Service
            metadata:
                name: web-service
            spec:
                selector:
                    app: web
                ports:
                - protocol: TCP
                    port: 80
                    targetPort: 8080
                type: ClusterIP
            ```

        2. 서비스 레지스트리
            ```yaml
            apiVersion: networking.istio.io/v1alpha3
            kind: ServiceEntry
            metadata:
                name: external-service
            spec:
                hosts:
                - api.external.com
                ports:
                - number: 443
                    name: https
                    protocol: HTTPS
                resolution: DNS
            ```

6. 클라우드 네트워크 모니터링
    1. 메트릭 수집
        1. CloudWatch 메트릭
            ```plaintext
            # 주요 모니터링 지표
            - VPC Flow Logs
            - ELB Request Count
            - NAT Gateway Bandwidth
            - VPN Tunnel Status
            ```

        2. 커스텀 메트릭
            ```python
            import boto3

            cloudwatch = boto3.client('cloudwatch')

            def publish_metric():
                cloudwatch.put_metric_data(
                    Namespace='Custom/Network',
                    MetricData=[{
                        'MetricName': 'ConnectionCount',
                        'Value': connection_count,
                        'Unit': 'Count'
                    }]
                )
            ```

    2. 알림 설정
        1. 임계값 기반 알림
            ```yaml
            Alarms:
            HighLatency:
                Metric: Latency
                Threshold: 1000ms
                Period: 5m
                Action: SNS
            
            ErrorRate:
                Metric: 5xxError
                Threshold: 5%
                Period: 5m
                Action: SNS
            ```

        2. 이상 탐지
            ```json
            {
                "AnomalyDetection": {
                    "MetricName": "RequestCount",
                    "Threshold": 2,
                    "EvaluationPeriods": 3,
                    "DatapointsToAlarm": 2
                }
            }
            ```

7. Key Takeaways
    1. 클라우드 네트워크 설계
        - 가용성과 확장성 고려
        - 적절한 서브넷 구성
        - 보안 계층화

    2. 성능 최적화
        - 적절한 로드밸런서 선택
        - 엔드포인트 최적화
        - 트래픽 모니터링

    3. 보안 관리
        - 다층적 보안 구성
        - 접근 제어 정책
        - 지속적인 모니터링