# Docker 네트워크 개요 및 설정 가이드

> **목표:**  
> - Docker 네트워크의 기본 개념과 아키텍처를 이해한다.
> - 다양한 네트워크 드라이버의 특징과 사용 사례를 파악한다.
> - 컨테이너 간 네트워크 구성 방법을 습득한다.
> - 네트워크 보안 설정과 문제 해결 방법을 익힌다.

---

## 1. Docker 네트워크 기본 개념

Docker 네트워크는 컨테이너 간의 통신을 가능하게 하는 핵심 기능입니다. 각 컨테이너는 독립적인 네트워크 네임스페이스를 가지며, Docker는 이들을 연결하여 안전하고 효율적인 통신을 제공합니다.

### 1.1 네트워크 구성요소

Docker 네트워크는 다음과 같은 주요 구성요소로 이루어져 있습니다:

1. 네트워크 드라이버: 네트워크의 동작 방식을 결정하는 핵심 요소
2. 네트워크 인터페이스: 컨테이너와 호스트 시스템을 연결하는 가상 인터페이스
3. DNS 서버: 컨테이너 간 이름 해결을 담당하는 내장 DNS
4. IP 주소 관리 (IPAM): 컨테이너에 IP 주소를 할당하고 관리

---

## 2. Docker 네트워크 드라이버

Docker는 다양한 사용 사례에 맞춰 여러 종류의 네트워크 드라이버를 제공합니다.

### 2.1 Bridge 네트워크

기본적인 네트워크 드라이버로, 동일한 Docker 호스트 내의 컨테이너 간 통신에 사용됩니다.

```bash
# 브릿지 네트워크 생성
docker network create --driver bridge my-bridge-network

# 컨테이너를 네트워크에 연결
docker run -d --network my-bridge-network --name container1 nginx
```

### 2.2 Host 네트워크

컨테이너가 호스트의 네트워크 스택을 직접 사용합니다.

```bash
# 호스트 네트워크 사용
docker run -d --network host --name container2 nginx
```

### 2.3 Overlay 네트워크

여러 Docker 데몬 간의 통신을 가능하게 하는 네트워크입니다.

```bash
# 오버레이 네트워크 생성
docker network create --driver overlay \
  --attachable \
  --subnet=10.0.0.0/24 \
  my-overlay-network
```

### 2.4 Macvlan 네트워크

컨테이너에 물리적 네트워크 인터페이스처럼 보이는 MAC 주소를 할당합니다.

```bash
# Macvlan 네트워크 생성
docker network create --driver macvlan \
  --subnet=192.168.1.0/24 \
  --gateway=192.168.1.1 \
  -o parent=eth0 \
  my-macvlan-network
```

---

## 3. 네트워크 설정 및 관리

### 3.1 기본 네트워크 명령어

네트워크 관리를 위한 주요 명령어들입니다:

```bash
# 네트워크 목록 확인
docker network ls

# 네트워크 상세 정보 확인
docker network inspect my-network

# 컨테이너를 네트워크에 연결
docker network connect my-network container1

# 컨테이너의 네트워크 연결 해제
docker network disconnect my-network container1
```

### 3.2 고급 네트워크 설정

Docker Compose를 사용한 복잡한 네트워크 구성:

```yaml
version: "3.8"

services:
  web:
    image: nginx
    networks:
      frontend:
        ipv4_address: 172.20.0.2
      backend:
  
  api:
    image: api-server
    networks:
      backend:
        ipv4_address: 172.21.0.2

networks:
  frontend:
    driver: bridge
    ipam:
      config:
        - subnet: 172.20.0.0/16
  
  backend:
    driver: bridge
    ipam:
      config:
        - subnet: 172.21.0.0/16
```

---

## 4. 네트워크 보안 설정

### 4.1 네트워크 격리

컨테이너와 네트워크의 보안을 강화하는 설정:

```yaml
services:
  web:
    networks:
      frontend:
        aliases:
          - web-service
    security_opt:
      - no-new-privileges:true

networks:
  frontend:
    driver: bridge
    internal: true  # 외부 접근 차단
```

### 4.2 포트 관리

포트 노출 및 매핑 설정:

```yaml
services:
  web:
    ports:
      - "8080:80"  # 외부:내부 포트
    expose:
      - "80"  # 내부 포트만 노출
```

---

## 5. 네트워크 문제 해결

### 5.1 연결 테스트

네트워크 연결 문제를 진단하는 방법:

```bash
# 컨테이너 간 연결 테스트
docker exec container1 ping container2

# 네트워크 정보 확인
docker exec container1 ip addr show

# DNS 확인
docker exec container1 nslookup container2
```

### 5.2 일반적인 문제 해결

네트워크 관련 일반적인 문제들의 해결 방법:

1. DNS 문제 해결:
```bash
# DNS 설정 확인
docker exec container1 cat /etc/resolv.conf
```

2. 네트워크 성능 모니터링:
```bash
# 네트워크 통계 확인
docker stats container1
```

---

## 6. 실전 네트워크 구성 예제

### 6.1 마이크로서비스 아키텍처

여러 서비스를 포함하는 마이크로서비스 네트워크 구성:

```yaml
version: "3.8"

services:
  frontend:
    image: frontend-app
    networks:
      - frontend

  api-gateway:
    image: api-gateway
    networks:
      - frontend
      - backend

  auth-service:
    image: auth-service
    networks:
      - backend
      - db

  db:
    image: postgres
    networks:
      - db

networks:
  frontend:
    driver: bridge
  backend:
    driver: bridge
    internal: true
  db:
    driver: bridge
    internal: true
```

### 6.2 로드 밸런싱 설정

Nginx를 사용한 로드 밸런싱 구성:

```yaml
services:
  nginx:
    image: nginx
    ports:
      - "80:80"
    networks:
      - frontend
    volumes:
      - ./nginx.conf:/etc/nginx/nginx.conf

  app1:
    image: web-app
    networks:
      - frontend

  app2:
    image: web-app
    networks:
      - frontend
```

---

## 7. 모니터링 및 관리

### 7.1 네트워크 모니터링

네트워크 상태와 성능을 모니터링하는 방법:

```bash
# 네트워크 사용량 모니터링
docker stats $(docker ps -q)

# 특정 컨테이너의 네트워크 연결 확인
docker exec container1 netstat -tulpn
```

### 7.2 로깅 설정

네트워크 관련 로그 수집 및 분석:

```yaml
services:
  web:
    logging:
      driver: "json-file"
      options:
        max-size: "10m"
        max-file: "3"
```

---

## 참고 자료

- [Docker 네트워킹 공식 문서](https://docs.docker.com/network/)
- [Docker Compose 네트워킹](https://docs.docker.com/compose/networking/)
- [Docker 네트워크 드라이버](https://docs.docker.com/network/drivers/)

---

## 마무리

Docker 네트워크는 컨테이너화된 애플리케이션의 핵심 구성 요소입니다. 적절한 네트워크 설계와 구성은 애플리케이션의 성능, 보안, 확장성에 직접적인 영향을 미칩니다. 이 문서에서 다룬 내용을 바탕으로 실제 환경에서 효율적이고 안전한 네트워크 구성을 구현할 수 있습니다.