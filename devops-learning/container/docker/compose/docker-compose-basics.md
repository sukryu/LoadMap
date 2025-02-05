# Docker Compose 기본 개념 및 활용 가이드

> **목표:**  
> - Docker Compose의 핵심 개념과 작동 방식을 이해한다.
> - docker-compose.yml 파일의 구조와 작성 방법을 습득한다.
> - 멀티 컨테이너 애플리케이션 구성 방법을 익힌다.
> - 실제 프로젝트에서의 활용 방법을 학습한다.

---

## 1. Docker Compose 개요

### 1.1 Docker Compose란?

Docker Compose는 여러 개의 Docker 컨테이너를 정의하고 관리하기 위한 도구입니다. 복잡한 애플리케이션을 구성하는 여러 컨테이너들을 하나의 파일로 정의하고, 단일 명령으로 모든 컨테이너를 실행할 수 있게 해줍니다.

예를 들어, 웹 애플리케이션을 구축할 때 웹 서버, 데이터베이스, 캐시 서버 등 여러 서비스가 필요합니다. Docker Compose를 사용하면 이러한 서비스들을 하나의 설정 파일로 관리하고, 동시에 실행할 수 있습니다.

### 1.2 주요 특징

Docker Compose는 다음과 같은 주요 특징을 제공합니다:

1. 단일 호스트에서 여러 격리된 환경 실행
2. 컨테이너 생성 시 볼륨 데이터 보존
3. 변경된 컨테이너만 재생성하는 캐싱 기능
4. 환경 변수 및 구성 옵션 관리
5. 컨테이너 간 의존성 관리

---

## 2. docker-compose.yml 파일 구조

### 2.1 기본 구조

docker-compose.yml 파일은 YAML 형식으로 작성되며, 다음과 같은 기본 구조를 가집니다:

```yaml
version: "3.8"

services:
  웹서비스_이름:
    설정...
  
  데이터베이스_이름:
    설정...

volumes:
  볼륨_설정...

networks:
  네트워크_설정...
```

### 2.2 주요 구성 요소

각 서비스 정의에는 다음과 같은 주요 설정들이 포함될 수 있습니다:

```yaml
version: "3.8"

services:
  web:
    image: nginx:latest           # 사용할 이미지
    build: ./web                 # Dockerfile 위치
    ports:
      - "80:80"                  # 포트 매핑
    volumes:
      - ./web:/usr/share/nginx/html  # 볼륨 마운트
    environment:                 # 환경 변수 설정
      - NODE_ENV=production
    depends_on:                  # 의존성 설정
      - db
    networks:                    # 네트워크 설정
      - backend

  db:
    image: mysql:5.7
    volumes:
      - db_data:/var/lib/mysql
    environment:
      - MYSQL_ROOT_PASSWORD=somewordpress
      - MYSQL_DATABASE=wordpress

volumes:
  db_data:

networks:
  backend:
```

---

## 3. Docker Compose 주요 명령어

### 3.1 기본 명령어

Docker Compose의 주요 명령어는 다음과 같습니다:

```bash
# 서비스 시작
docker-compose up

# 백그라운드에서 서비스 시작
docker-compose up -d

# 서비스 중지
docker-compose down

# 서비스 상태 확인
docker-compose ps

# 서비스 로그 확인
docker-compose logs

# 특정 서비스의 로그 확인
docker-compose logs web
```

### 3.2 고급 명령어

```bash
# 설정 파일 검증
docker-compose config

# 특정 서비스만 재시작
docker-compose restart web

# 서비스 빌드
docker-compose build

# 특정 서비스의 컨테이너에 명령어 실행
docker-compose exec web bash
```

---

## 4. 실전 활용 예제

### 4.1 웹 애플리케이션 구성 예제

다음은 Node.js 웹 애플리케이션과 MongoDB를 연동하는 예제입니다:

```yaml
version: "3.8"

services:
  web:
    build: .
    ports:
      - "3000:3000"
    environment:
      - MONGODB_URI=mongodb://db:27017/myapp
    depends_on:
      - db
    volumes:
      - .:/usr/src/app
      - /usr/src/app/node_modules
    command: npm start

  db:
    image: mongo:latest
    volumes:
      - mongodb_data:/data/db

volumes:
  mongodb_data:
```

### 4.2 개발 환경과 운영 환경 분리

개발 환경과 운영 환경의 설정을 분리하여 관리할 수 있습니다:

```yaml
# docker-compose.override.yml (개발 환경)
version: "3.8"

services:
  web:
    build:
      context: .
      dockerfile: Dockerfile.dev
    volumes:
      - .:/usr/src/app
    environment:
      - NODE_ENV=development

# docker-compose.prod.yml (운영 환경)
version: "3.8"

services:
  web:
    build:
      context: .
      dockerfile: Dockerfile.prod
    environment:
      - NODE_ENV=production
```

---

## 5. 모범 사례와 주의사항

### 5.1 모범 사례

1. 버전 관리: 명시적인 버전 태그 사용
2. 환경 변수: .env 파일 활용
3. 볼륨 관리: 명확한 볼륨 정책 수립
4. 네트워크 설계: 적절한 네트워크 분리

### 5.2 주의사항

1. 보안: 민감한 정보는 환경 변수로 관리
2. 리소스 관리: 적절한 리소스 제한 설정
3. 의존성 관리: 서비스 간 의존성 명확히 정의
4. 로깅: 적절한 로깅 전략 수립

---

## 6. 확장 및 스케일링

### 6.1 서비스 스케일링

```bash
# 웹 서비스를 3개의 인스턴스로 확장
docker-compose up -d --scale web=3
```

### 6.2 로드 밸런싱

```yaml
version: "3.8"

services:
  web:
    image: nginx
    deploy:
      replicas: 3
      resources:
        limits:
          cpus: '0.5'
          memory: 512M
    ports:
      - "80:80"
```

---

## 참고 자료

- [Docker Compose 공식 문서](https://docs.docker.com/compose/)
- [Docker Compose 파일 레퍼런스](https://docs.docker.com/compose/compose-file/)
- [Docker Compose 명령어 레퍼런스](https://docs.docker.com/compose/reference/)

---

## 마무리

Docker Compose는 복잡한 애플리케이션 환경을 효율적으로 관리할 수 있게 해주는 강력한 도구입니다. 이 문서에서 다룬 기본 개념과 사용법을 바탕으로, 실제 프로젝트에서 Docker Compose를 활용하여 개발 및 운영 환경을 구성할 수 있습니다. 특히 여러 서비스를 포함하는 마이크로서비스 아키텍처에서 그 진가를 발휘합니다.