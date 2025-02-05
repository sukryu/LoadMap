# 멀티 컨테이너 애플리케이션 구축 가이드

> **목표:**  
> - 멀티 컨테이너 애플리케이션의 설계 방법을 이해한다.
> - 컨테이너 간 통신과 데이터 공유 방법을 습득한다.
> - 실제 프로젝트 예제를 통해 구축 과정을 학습한다.
> - 운영 환경에서의 관리와 모니터링 방법을 익힌다.

---

## 1. 멀티 컨테이너 애플리케이션 개요

멀티 컨테이너 애플리케이션은 여러 개의 독립적인 컨테이너가 서로 협력하여 하나의 애플리케이션을 구성하는 방식입니다. 이는 마이크로서비스 아키텍처의 기본이 되며, 각 컨테이너가 특정 기능을 담당하여 전체 시스템의 유연성과 확장성을 높입니다.

예를 들어, 웹 애플리케이션은 다음과 같은 컴포넌트들로 구성될 수 있습니다:
- 프론트엔드 서버 (React/Vue/Angular)
- 백엔드 API 서버 (Node.js/Python/Java)
- 데이터베이스 서버 (MySQL/PostgreSQL)
- 캐시 서버 (Redis)
- 웹 서버/프록시 (Nginx)

---

## 2. 애플리케이션 설계 및 구성

### 2.1 프로젝트 구조

전형적인 멀티 컨테이너 프로젝트의 디렉토리 구조는 다음과 같습니다:

```plaintext
my-app/
├── docker-compose.yml
├── frontend/
│   ├── Dockerfile
│   └── src/
├── backend/
│   ├── Dockerfile
│   └── src/
├── nginx/
│   ├── Dockerfile
│   └── nginx.conf
└── .env
```

### 2.2 Docker Compose 설정

실제 운영 환경에서 사용할 수 있는 docker-compose.yml 예제:

```yaml
version: "3.8"

services:
  frontend:
    build: ./frontend
    environment:
      - REACT_APP_API_URL=http://api:3000
    volumes:
      - ./frontend:/app
      - /app/node_modules
    depends_on:
      - backend

  backend:
    build: ./backend
    environment:
      - DATABASE_URL=mysql://db:3306/myapp
      - REDIS_URL=redis://cache:6379
    volumes:
      - ./backend:/app
      - /app/node_modules
    depends_on:
      - db
      - cache

  nginx:
    build: ./nginx
    ports:
      - "80:80"
    depends_on:
      - frontend
      - backend

  db:
    image: mysql:8.0
    volumes:
      - db_data:/var/lib/mysql
    environment:
      - MYSQL_ROOT_PASSWORD=${DB_ROOT_PASSWORD}
      - MYSQL_DATABASE=myapp
    
  cache:
    image: redis:alpine
    volumes:
      - cache_data:/data

volumes:
  db_data:
  cache_data:

networks:
  default:
    driver: bridge
```

---

## 3. 컨테이너 간 통신 설정

### 3.1 네트워크 구성

컨테이너 간 통신을 위한 네트워크 설정은 매우 중요합니다. Docker Compose는 기본적으로 모든 서비스를 위한 기본 네트워크를 생성합니다.

```yaml
networks:
  frontend:
    driver: bridge
  backend:
    driver: bridge

services:
  frontend:
    networks:
      - frontend
  
  backend:
    networks:
      - frontend
      - backend
  
  db:
    networks:
      - backend
```

### 3.2 서비스 디스커버리

Docker Compose는 자동으로 DNS 기반의 서비스 디스커버리를 제공합니다. 각 서비스는 서비스 이름으로 다른 서비스에 접근할 수 있습니다:

```javascript
// backend/src/config.js
module.exports = {
  database: {
    host: 'db',  // 서비스 이름으로 접근
    port: 3306
  },
  redis: {
    host: 'cache',  // 서비스 이름으로 접근
    port: 6379
  }
};
```

---

## 4. 데이터 관리 및 영속성

### 4.1 볼륨 설정

데이터 영속성을 위한 볼륨 구성:

```yaml
services:
  db:
    volumes:
      - db_data:/var/lib/mysql
      - ./init.sql:/docker-entrypoint-initdb.d/init.sql

volumes:
  db_data:
    driver: local
```

### 4.2 환경 변수 관리

환경 변수는 .env 파일을 통해 관리합니다:

```plaintext
# .env
DB_ROOT_PASSWORD=secretpassword
REDIS_PASSWORD=redispassword
API_KEY=myapikey
```

---

## 5. 실전 예제: 풀스택 웹 애플리케이션

### 5.1 프론트엔드 (React)

```dockerfile
# frontend/Dockerfile
FROM node:16-alpine

WORKDIR /app
COPY package*.json ./
RUN npm install
COPY . .

CMD ["npm", "start"]
```

### 5.2 백엔드 (Node.js)

```dockerfile
# backend/Dockerfile
FROM node:16-alpine

WORKDIR /app
COPY package*.json ./
RUN npm install
COPY . .

CMD ["npm", "run", "dev"]
```

### 5.3 Nginx 설정

```nginx
# nginx/nginx.conf
server {
    listen 80;
    
    location / {
        proxy_pass http://frontend:3000;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
    }

    location /api {
        proxy_pass http://backend:3000;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
    }
}
```

---

## 6. 운영 및 모니터링

### 6.1 로깅 설정

각 서비스의 로그를 효율적으로 관리하기 위한 설정:

```yaml
services:
  backend:
    logging:
      driver: "json-file"
      options:
        max-size: "10m"
        max-file: "3"
```

### 6.2 헬스 체크

서비스 상태 모니터링을 위한 헬스 체크 설정:

```yaml
services:
  backend:
    healthcheck:
      test: ["CMD", "curl", "-f", "http://localhost:3000/health"]
      interval: 30s
      timeout: 10s
      retries: 3
```

---

## 7. 배포 및 스케일링

### 7.1 배포 전략

프로덕션 환경을 위한 배포 설정:

```yaml
services:
  backend:
    deploy:
      replicas: 3
      update_config:
        parallelism: 1
        delay: 10s
      restart_policy:
        condition: on-failure
```

### 7.2 성능 최적화

리소스 제한 및 최적화 설정:

```yaml
services:
  backend:
    deploy:
      resources:
        limits:
          cpus: '0.50'
          memory: 512M
        reservations:
          cpus: '0.25'
          memory: 256M
```

---

## 8. 문제 해결 및 디버깅

### 8.1 일반적인 문제 해결

컨테이너 간 통신 문제나 볼륨 마운트 이슈 등 일반적인 문제들의 해결 방법:

1. 네트워크 연결 확인
```bash
docker-compose exec backend ping db
```

2. 볼륨 마운트 확인
```bash
docker-compose exec db ls -la /var/lib/mysql
```

### 8.2 디버깅 도구

개발 및 디버깅을 위한 도구 설정:

```yaml
services:
  backend:
    environment:
      - DEBUG=express:*
    volumes:
      - ./backend:/app
      - /app/node_modules
```

---

## 참고 자료

- [Docker Compose 공식 문서](https://docs.docker.com/compose/)
- [Docker Networking 가이드](https://docs.docker.com/network/)
- [Docker Volume 관리](https://docs.docker.com/storage/volumes/)

---

## 마무리

멀티 컨테이너 애플리케이션의 구축은 현대 애플리케이션 개발에서 필수적인 부분입니다. 각 컨테이너의 역할을 명확히 하고, 적절한 통신 및 데이터 공유 방법을 설정하며, 효율적인 모니터링과 관리 전략을 수립하는 것이 중요합니다. 이 문서에서 다룬 내용을 기반으로 실제 프로젝트에서 멀티 컨테이너 애플리케이션을 성공적으로 구축하고 운영할 수 있습니다.