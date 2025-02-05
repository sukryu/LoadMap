# Docker 고급 네트워크 구성 가이드

> **목표:**  
> - 복잡한 네트워크 토폴로지 구성 방법을 이해한다.
> - 고가용성과 확장성을 위한 네트워크 설정을 학습한다.
> - 보안과 성능 최적화 전략을 습득한다.
> - 실제 운영 환경에서의 네트워크 관리 기법을 익힌다.

---

## 1. 고급 네트워크 토폴로지 설계

고급 네트워크 토폴로지는 마이크로서비스 아키텍처와 같은 복잡한 시스템에서 필수적입니다. 각 서비스의 특성과 요구사항에 맞는 네트워크 구성이 중요합니다.

### 1.1 다중 네트워크 계층 구성

운영 환경에서의 다중 네트워크 계층 예시:

```yaml
version: "3.8"

services:
  reverse-proxy:
    image: traefik:v2.5
    networks:
      - public
      - internal
    ports:
      - "80:80"
      - "443:443"
    volumes:
      - /var/run/docker.sock:/var/run/docker.sock
    command:
      - "--providers.docker=true"
      - "--entrypoints.web.address=:80"
      - "--entrypoints.websecure.address=:443"

  api-gateway:
    image: api-gateway
    networks:
      - internal
      - services
    deploy:
      replicas: 3
      update_config:
        parallelism: 1
        delay: 10s

  auth-service:
    image: auth-service
    networks:
      - services
      - database
    secrets:
      - db_password
      - jwt_secret

  database:
    image: postgres:13
    networks:
      - database
    volumes:
      - db_data:/var/lib/postgresql/data

networks:
  public:
    driver: overlay
    attachable: true
  internal:
    driver: overlay
    internal: true
  services:
    driver: overlay
    internal: true
  database:
    driver: overlay
    internal: true
    driver_opts:
      encrypted: "true"

secrets:
  db_password:
    external: true
  jwt_secret:
    external: true

volumes:
  db_data:
```

## 2. 고가용성 네트워크 구성

### 2.1 로드 밸런싱과 서비스 디스커버리

Traefik을 활용한 동적 로드 밸런싱 구성:

```yaml
services:
  traefik:
    image: traefik:v2.5
    command:
      - "--api.insecure=true"
      - "--providers.docker=true"
      - "--providers.docker.swarmMode=true"
      - "--entrypoints.web.address=:80"
    ports:
      - "80:80"
      - "8080:8080"
    volumes:
      - /var/run/docker.sock:/var/run/docker.sock
    deploy:
      placement:
        constraints:
          - node.role == manager

  web:
    image: nginx
    deploy:
      replicas: 3
      labels:
        - "traefik.enable=true"
        - "traefik.http.routers.web.rule=Host(`example.com`)"
```

### 2.2 장애 복구 설정

자동 장애 복구를 위한 네트워크 구성:

```yaml
services:
  app:
    deploy:
      replicas: 3
      restart_policy:
        condition: on-failure
        delay: 5s
        max_attempts: 3
        window: 120s
      update_config:
        parallelism: 1
        delay: 10s
        order: start-first
```

## 3. 네트워크 보안 강화

### 3.1 네트워크 암호화

Overlay 네트워크에서의 데이터 암호화 설정:

```yaml
networks:
  secure-network:
    driver: overlay
    driver_opts:
      encrypted: "true"
    attachable: true
    internal: true
    ipam:
      driver: default
      config:
        - subnet: "10.0.0.0/24"
          ip_range: "10.0.0.0/25"
          gateway: "10.0.0.1"
```

### 3.2 네트워크 격리 및 접근 제어

세분화된 네트워크 접근 제어 설정:

```yaml
services:
  frontend:
    networks:
      frontend:
        aliases:
          - web-ui
    security_opt:
      - no-new-privileges:true
    cap_drop:
      - ALL
    cap_add:
      - NET_BIND_SERVICE

networks:
  frontend:
    driver: overlay
    internal: true
    attachable: false
    driver_opts:
      com.docker.network.driver.mtu: "1450"
```

## 4. 성능 최적화

### 4.1 MTU 최적화

네트워크 성능 향상을 위한 MTU 설정:

```yaml
networks:
  performance-network:
    driver: overlay
    driver_opts:
      com.docker.network.driver.mtu: "9000"
    ipam:
      driver: default
      config:
        - subnet: "192.168.0.0/16"
```

### 4.2 네트워크 큐 및 버퍼 튜닝

시스템 레벨 네트워크 최적화:

```bash
# 네트워크 버퍼 크기 조정
sysctl -w net.core.rmem_max=26214400
sysctl -w net.core.wmem_max=26214400

# 네트워크 큐 길이 조정
sysctl -w net.core.netdev_max_backlog=2000
```

## 5. 모니터링 및 트러블슈팅

### 5.1 네트워크 모니터링 설정

Prometheus와 Grafana를 활용한 모니터링 구성:

```yaml
services:
  prometheus:
    image: prom/prometheus
    volumes:
      - ./prometheus.yml:/etc/prometheus/prometheus.yml
    networks:
      - monitoring

  grafana:
    image: grafana/grafana
    depends_on:
      - prometheus
    networks:
      - monitoring
    environment:
      - GF_SECURITY_ADMIN_PASSWORD=secret

networks:
  monitoring:
    driver: overlay
    internal: true
```

### 5.2 네트워크 디버깅 도구

문제 해결을 위한 고급 디버깅 도구 설정:

```yaml
services:
  debug-tools:
    image: nicolaka/netshoot
    networks:
      - target-network
    cap_add:
      - NET_ADMIN
      - SYS_ADMIN
    command: sleep infinity
```

## 6. 대규모 배포 전략

### 6.1 네트워크 스케일링

대규모 서비스를 위한 네트워크 구성:

```yaml
services:
  api:
    deploy:
      mode: replicated
      replicas: 10
      placement:
        constraints:
          - node.role == worker
        preferences:
          - spread: node.labels.zone
      resources:
        limits:
          cpus: '0.50'
          memory: 512M
      restart_policy:
        condition: any
        delay: 5s
        window: 120s
```

### 6.2 서비스 메시 구성

Istio를 활용한 서비스 메시 구성:

```yaml
services:
  istiod:
    image: istio/pilot:1.9.0
    networks:
      - mesh-network
    ports:
      - "15010:15010"
      - "15012:15012"

  app:
    networks:
      - mesh-network
    deploy:
      labels:
        sidecar.istio.io/inject: "true"
```

---

## 참고 자료

- [Docker Swarm 네트워킹](https://docs.docker.com/engine/swarm/networking/)
- [Traefik 공식 문서](https://doc.traefik.io/traefik/)
- [Docker 네트워크 성능 최적화](https://docs.docker.com/config/containers/container-networking/)

---

## 마무리

고급 네트워크 구성은 현대적인 컨테이너 기반 애플리케이션의 성공적인 운영을 위한 핵심 요소입니다. 이 문서에서 다룬 고가용성 설정, 보안 강화, 성능 최적화 전략을 적절히 조합하여 견고하고 효율적인 네트워크 인프라를 구축할 수 있습니다.