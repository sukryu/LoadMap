# 보안/성능 측면에서의 네트워크

1. TLS/SSL 보안
    1. 인증서 관리
        1. 인증서 생성
            ```bash
            # 개인키 생성
            openssl genrsa -out private.key 2048

            # CSR 생성
            openssl req -new -key private.key -out cert.csr

            # 자체 서명 인증서 생성
            openssl x509 -req -days 365 -in cert.csr -signkey private.key -out cert.crt
            ```

        2. Let`s Encrypt 활용
            ```bash
            # Certbot 설치 및 인증서 발급
            apt-get install certbot
            certbot certonly --standalone -d example.com

            # 자동 갱신 설정
            certbot renew --dry-run
            ```

    2. HTTPS 설정
        1. Nginx HTTPS 설정
            ```nginx
            server {
                listen 443 ssl;
                server_name example.com;

                ssl_certificate /etc/letsencrypt/live/example.com/fullchain.pem;
                ssl_certificate_key /etc/letsencrypt/live/example.com/privkey.pem;

                # 최신 보안 설정
                ssl_protocols TLSv1.2 TLSv1.3;
                ssl_ciphers ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256;
                ssl_prefer_server_ciphers on;
                ssl_session_cache shared:SSL:10m;
                ssl_session_timeout 10m;

                # HSTS 설정
                add_header Strict-Transport-Security "max-age=31536000" always;
            }
            ```

        2. Apache HTTPS 설정
            ```apache
            <VirtualHost *:443>
                ServerName example.com
                SSLEngine on
                SSLCertificateFile /etc/letsencrypt/live/example.com/cert.pem
                SSLCertificateKeyFile /etc/letsencrypt/live/example.com/privkey.pem
                SSLCertificateChainFile /etc/letsencrypt/live/example.com/chain.pem

                # 보안 헤더 설정
                Header always set Strict-Transport-Security "max-age=31536000"
                Header always set X-Frame-Options "SAMEORIGIN"
                Header always set X-Content-Type-Options "nosniff"
            </VirtualHost>
            ```

2. DDoS 방어
    1. 인프라 레벨 방어
        1. AWS Shield 설정
            ```json
            {
                "ShieldProtection": {
                    "Name": "WebProtection",
                    "ResourceArn": "arn:aws:elasticloadbalancing:region:account-id:loadbalancer/app/my-lb/1234567890",
                    "Protection": {
                    "AutoRenew": true,
                    "ProactiveEngagement": true
                    }
                }
            }
            ```

        2. Cloudflare 설정
            ```yaml
            # Cloudflare 방화벽 규칙
            firewall_rules:
                - description: "Block suspicious IPs"
                    expression: >
                    (ip.geoip.country in {"CN" "RU"}) and
                    (http.request.uri.path contains "/wp-login.php")
                    action: block

                - description: "Rate limit API"
                    expression: >
                    (http.request.uri.path contains "/api/") and
                    (rate_limit("api", 100))
                    action: challenge
            ```

    2. 애플리케이션 레벨 방어
        1. Rate Limiting 구현
            ```python
            from flask import Flask, request
            from flask_limiter import Limiter
            from flask_limiter.util import get_remote_address

            app = Flask(__name__)
            limiter = Limiter(
                app,
                key_func=get_remote_address,
                default_limits=["200 per day", "50 per hour"]
            )

            @app.route("/api/resource")
            @limiter.limit("1 per second")
            def api_resource():
                return {"status": "success"}
            ```

        2. WAF 규칙 설정
            ```nginx
            # ModSecurity 규칙
            SecRule REQUEST_HEADERS:User-Agent "@contains bad_bot" \
                "phase:1,deny,status:403,msg:'Bad Bot Detected'"

            SecRule REQUEST_URI "@rx (?i)\.\./" \
                "phase:1,deny,status:403,msg:'Directory Traversal Attack'"
            ```

3. 네트워크 성능 최적화
    1. CDN 구성
        1. AWS CloudFront 설정
            ```json
            {
                "Distribution": {
                    "DistributionConfig": {
                    "Origins": {
                        "Items": [{
                        "DomainName": "origin.example.com",
                        "Id": "myOrigin",
                        "CustomOriginConfig": {
                            "HTTPPort": 80,
                            "HTTPSPort": 443,
                            "OriginProtocolPolicy": "https-only"
                        }
                        }]
                    },
                    "DefaultCacheBehavior": {
                        "TargetOriginId": "myOrigin",
                        "ViewerProtocolPolicy": "redirect-to-https",
                        "MinTTL": 0,
                        "DefaultTTL": 86400,
                        "MaxTTL": 31536000,
                        "Compress": true
                    }
                    }
                }
            }
            ```

        2. 캐시 최적화
            ```nginx
            # Nginx 캐시 설정
            proxy_cache_path /path/to/cache levels=1:2 keys_zone=my_cache:10m max_size=10g inactive=60m use_temp_path=off;

            server {
                location / {
                    proxy_cache my_cache;
                    proxy_cache_use_stale error timeout http_500 http_502 http_503 http_504;
                    proxy_cache_valid 200 60m;
                    proxy_cache_valid 404 1m;
                }
            }
            ```

    2. 로드밸런서 최적화
        1. HAProxy 설정
            ```haproxy
            global
                maxconn 50000
                ssl-default-bind-ciphers ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256
                ssl-default-bind-options no-sslv3 no-tlsv10 no-tlsv11

            frontend http-in
                bind *:80
                bind *:443 ssl crt /etc/ssl/private/cert.pem
                mode http
                option httplog
                option forwardfor
                
                # ACL for path-based routing
                acl is_api path_beg /api
                use_backend api-servers if is_api
                default_backend web-servers

            backend web-servers
                mode http
                balance roundrobin
                option httpchk HEAD /health HTTP/1.1
                server web1 10.0.0.1:8080 check
                server web2 10.0.0.2:8080 check
            ```

        2. Nginx 로드 밸런서
            ```nginx
            upstream backend {
                least_conn;  # 최소 연결 수 기반 밸런싱
                server backend1.example.com:8080 max_fails=3 fail_timeout=30s;
                server backend2.example.com:8080 max_fails=3 fail_timeout=30s;
                keepalive 32;  # keepalive 연결 유지
            }

            server {
                listen 80;
                location / {
                    proxy_pass http://backend;
                    proxy_http_version 1.1;
                    proxy_set_header Connection "";
                    proxy_next_upstream error timeout invalid_header http_500;
                }
            }
            ```

4. 네트워크 모니터링
    1. 성능 모니터링
        1. Prometheus 설정
            ```yaml
            global:
            scrape_interval: 15s
            evaluation_interval: 15s

            scrape_configs:
                - job_name: 'nginx'
                    static_configs:
                    - targets: ['localhost:9113']

                - job_name: 'node'
                    static_configs:
                    - targets: ['localhost:9100']
            ```

        2. Grafana 대시보드
            ```json
            {
                "panels": [
                    {
                    "title": "Request Latency",
                    "type": "graph",
                    "datasource": "Prometheus",
                    "targets": [
                        {
                        "expr": "rate(http_request_duration_seconds_sum[5m])",
                        "legendFormat": "{{method}} {{path}}"
                        }
                    ]
                    },
                    {
                    "title": "Error Rate",
                    "type": "graph",
                    "targets": [
                        {
                        "expr": "rate(http_requests_total{status=~\"5..\"}[5m])",
                        "legendFormat": "{{status}}"
                        }
                    ]
                    }
                ]
            }
            ```

    2. 보안 모니터링
        1. ELK Stack 설정
            ```yaml
            # Filebeat 설정
            filebeat.inputs:
                - type: log
                enabled: true
                paths:
                    - /var/log/nginx/access.log
                fields:
                    type: nginx-access

            output.elasticsearch:
                hosts: ["localhost:9200"]
                index: "nginx-access-%{+yyyy.MM.dd}"
            ```

        2. 알림 설정
            ```yaml
            # Alertmanager 설정
            global:
                resolve_timeout: 5m

            route:
                group_by: ['alertname']
                group_wait: 10s
                group_interval: 10s
                repeat_interval: 1h
                receiver: 'team-emails'

            receivers:
                - name: 'team-emails'
                email_configs:
                - to: 'team@example.com'
                    from: 'alertmanager@example.com'
                    smarthost: 'smtp.example.com:587'
            ```

5. 성능 테스트
    1. 부하 테스트
        1. Apache Benchmark
            ```bash
            # 동시 100 연결로 1000 요청 테스트
            ab -n 1000 -c 100 https://example.com/

            # Keep-Alive 테스트
            ab -n 1000 -c 100 -k https://example.com/
            ```

        2. k6 테스트 스크립트
            ```javascript
            import http from 'k6/http';
            import { check, sleep } from 'k6';

            export let options = {
                stages: [
                    { duration: '2m', target: 100 },  // 점진적 사용자 증가
                    { duration: '5m', target: 100 },  // 부하 유지
                    { duration: '2m', target: 0 },    // 점진적 감소
                ],
            };

            export default function() {
                let res = http.get('https://example.com');
                check(res, {
                    'is status 200': (r) => r.status === 200,
                    'transaction time OK': (r) => r.timings.duration < 200
                });
                sleep(1);
            }
            ```

6. Key Takeaways
    1. 보안 최적화
        - TLS/SSL 인증서 관리 자동화
        - 다층적 DDoS 방어 전략
        - WAF 규칙 최적화

    2. 성능 최적화
        - CDN 활용으로 지연시간 감소
        - 적절한 캐싱 전략
        - 로드 밸런싱 구성

    3. 모니터링과 테스트
        - 실시간 성능 모니터링
        - 보안 이벤트 추적
        - 장기적인 부하 테스트