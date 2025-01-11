# Docker란 무엇인가?

* Docker는 현대 애플리케이션을 컨테이너화하여 개발, 배포, 실행할 수 있게 해주는 플랫폼입니다. 주요 특징은 다음과 같습니다:
    1. 컨테이너 기반 가상화 기술
        - 기존 VM과 달리 호스트 OS의 커널을 공유하여 사용
        - 각 컨테이너는 독립된 실행 환경을 가지지만, 호스트의 자원을 효율적으로 활용

    2. VM vs Docker 컨테이너 비교
        - VM: 각각의 VM마다 완전한 OS를 포함하므로 무겁고 시작 시간이 오래 걸림
        - Docker: 호스트 OS 커널을 공유하므로 가볍고 빠르게 시작 가능

    3. Docker의 주요 장점
        1. 경량화: 컨테이너는 필요한 라이브러리와 바이너리만 포함
        2. 빠른 배포: 이미지 기반으로 빠른 배포와 롤백 가능
        3. 높은 이식성: "내 컴퓨터에서는 작동했는데..." 문제 해결

* Docker 아키텍처
    * Docker는 다음과 같은 주요 컴포넌트로 구성됩니다:
        1. Docker Deamon(dockerd)
            -  호스트에서 실행되는 백그라운드 프로세스
            - 이미지, 컨테이너, 네트워크, 볼륨 등을 관리
            - REST API를 통해 Docker 클라이언트와 통신

        2. Docker Client (docker CLI)
            -  사용자가 Docker와 상호작용하는 주요 인터페이스
            - docker build, docker run 등의 명령어 제공
            - Docker daemon과 통신하여 작업 수행

    * 핵심 개념
        1. 이미지(Image)
            - 애플리케이션과 그 실행에 필요한 모든 것을 포함한 패키지
            - 읽기 전용 템플릿

        2. 컨테이너(Container)
            - 이미지의 실행 가능한 인스턴스
            - 독립된 실행 환경 제공

        3. 레지스트리(Registry)
            - 이미지를 저장하고 배포하는 저장소
            - Docker Hub가 대표적인 공개 레지스트리

* 설치 및 환경 설정
    * 운영체제별 설치 방법
        1. Windows
            - Docker Desktop for Windows 설치
            - WSL2 지원으로 리눅스 컨테이너 실행 가능

        2. macOS
            - Docker Desktop for Mac 설치
            - Intel 및 Apple Silicon 지원

        3. Linux
            - Docker Engine (Community Edition) 직접 설치
            - 패키지 매니저를 통한 설치 (apt, yum 등)

    * 시스템 요구사항
        - CPU: 64비트 프로세서
        - RAM: 최소 4GB (권장 8GB 이상)
        - 디스크: 설치용 최소 20GB 여유 공간
        - 운영체제: Windows10 이상, macOS 10.14 이상, 지원되는 Linux 배포판

# Docker 이미지 (Image)

1. 이미지 구조와 개념
    1. 레이어 시스템
        - Docker 이미지는 여러 읽기 전용 레이어의 스택으로 구성
        - 각 레이어는 이전 레이어의 변경사항을 포함
        - Dockerfile의 각 명령어가 새로운 레이어 생성

    2. Union File System
        - 여러 레이러를 하나의 통합된 파일시스템으로 제공
        - Copy-On-Write (CoW)방식 사용
            - 기존 이미지 레이어는 읽기 전용으로 유지
            - 변경이 필요한 경우 새로운 레이어에 복사 후 수정

    3. 이미지 상속과 태그
        - 기반 이미지(Base Image)를 시작점으로 사용
            - 예: `FROM ubuntu:20.04`
        - 태그를 통한 버전 관리
            - latest: 최신 버전
            - 특정 버전: 18.04, 20.04 등

2. 도커 이미지 생성
    1. Dockerfile 주요 명령어
        ```dockerfile
        # 기본 이미지 지정
        FROM ubuntu:20.04

        # 작업 디렉토리 설정
        WORKDIR /app

        # 파일 복사
        COPY . /app/

        # 명령어 실행
        RUN apt-get update && apt-get install -y python3

        # 환경변수 설정
        ENV PORT=8080

        # 포트 노출
        EXPOSE 8080

        # 시작 명령어
        CMD ["python3", "app.py"]
        ```

    2. 이미지 빌드 명령어
        ```bash
        # 기본 빌드
        docker build -t myapp:1.0 .

        # 캐시 없이 빌드
        docker build --no-cache -t myapp:1.0 .
        ```

3. 이미지 최적화
    1. 레이어 최소화 전략
        1. RUN 명령어 체인
            ```dockerfile
            RUN apt-get update && \
            apt-get install -y python3 && \
            rm -rf /var/lib/apt/lists/*
            ```

        2. .dockerignore 활용
            ```plaintext
            node_modules
            npm-debug.log
            .git
            ```

    2. Multi-stage Build 예시
        ```dockerfile
        # 빌드 스테이지
        FROM node:14 AS builder
        WORKDIR /app
        COPY package*.json ./
        RUN npm install
        COPY . .
        RUN npm run build

        # 실행 스테이지
        FROM nginx:alpine
        COPY --from=builder /app/build /usr/share/nginx/html
        ```

4. 이미지 레지스트리
    1. 레지스트리 작업
        ```bash
        # 이미지 푸시
        docker push username/myapp:1.0

        # 이미지 풀
        docker pull username/myapp:1.0

        # 이미지 태그 변경
        docker tag myapp:1.0 username/myapp:1.0
        ```

    2. Private Registry 구성
        - 보안이 필요한 이미지를 위한 사설 저장소
        - 지원 시스템:
            - Harbor
            - Docker Registry
            - AWS ECR
            - Azure Container Registry

# Docker 컨테이너 (Container)

1. 컨테이너 실행과 관리
    1. 기본 실행 명령어
        ```bash
        # 기본 실행
        docker run nginx

        # 백그라운드 실행 (-d)
        docker run -d nginx

        # 이름 지정 (--name)
        docker run --name my-nginx nginx

        # 포트 매핑 (-p)
        docker run -p 8080:80 nginx

        # 환경변수 설정 (-e)
        docker run -e DB_HOST=localhost nginx

        # 볼륨 마운트 (-v)
        docker run -v /host/path:/container/path nginx
        ```

2. 컨테이너 라이프사이클
    1. 기본 관리 명령어
        ```bash
        # 실행 중인 컨테이너 목록
        docker ps

        # 모든 컨테이너 목록 (중지된 것 포함)
        docker ps -a

        # 컨테이너 중지
        docker stop my-nginx

        # 컨테이너 시작
        docker start my-nginx

        # 컨테이너 재시작
        docker restart my-nginx

        # 컨테이너 삭제
        docker rm my-nginx
        ```

    2. 컨테이너 로그 및 디버깅
        ```bash
        # 로그 확인
        docker logs my-nginx

        # 실시간 로그 확인
        docker logs -f my-nginx

        # 컨테이너 내부 접속
        docker exec -it my-nginx bash

        # 프로세스 상태 확인
        docker top my-nginx
        ```

3. 네트워크와 포트 매핑
    1. 네트워크 드라이버 종류
        1. bridge: 기본 네트워크 드라이버
        2. host: 호스트의 네트워크를 직접 사용
        3. none: 네트워크 비활성화
        4. overlay: 여러 Docker 데몬간 통신 (Swarm)

    2. 네트워크 관리
        ```bash
        # 네트워크 생성
        docker network create my-network

        # 네트워크 연결
        docker network connect my-network my-nginx

        # 네트워크 목록
        docker network ls
        ```

4. 스토리지 볼륨
    1. 볼륨 타입
        1. 볼륨 (Volume)
            - Docker가 관리하는 영구 저장소
            - 컨테이너 삭제 후에도 데이터 유지
            ```bash
            docker volume create my-vol
            docker run -v my-vol:/app nginx
            ```

        2. 바인드 마운트 (Bind Mount)
            - 호스트의 특정 경로를 컨테이너에 마운트
            ```bash
            docker run -v /host/path:/container/path nginx
            ```

        3. tmpfs
            - 메모리에만 존재하는 임시 저장소

5. 컨테이너 모니터링
    1. 리소스 사용량 모니터링
        ```bash
        # 실시간 리소스 사용량
        docker stats

        # 특정 컨테이너 상태
        docker stats my-nginx
        ```

    2. 헬스체크 설정
        ```dockerfile
        # Dockerfile에서 헬스체크 설정
        HEALTHCHECK --interval=30s --timeout=3s \
            CMD curl -f http://localhost/ || exit 1
        ```

    3. 이벤트 모니터링
        ```bash
        # 도커 이벤트 실시간 확인
        docker events

        # 필터링된 이벤트 확인
        docker events --filter 'container=my-nginx'
        ```

# Docker Compose

1. Docker Compose 개념과 기본 구조
    1. Docker Compose란?
        - 다중 컨테이너 애플리케이션을 정의하고 실행하는 도구
        - YAML 파일을 통해 서비스, 네트워크, 볼륨을 선언적으로 정의
        - 개발 환경, 테스트 서버 구성에 적합

    2. 기본 docker-compose.yml 예시
        ```yaml
        version: "3.8"
        services:
            web:
                image: nginx:alpine
                ports:
                    - "80:80"
                volumes:
                    - ./html:/usr/share/nginx/html
                depends_on:
                    - api

            api:
                build: ./api
                environment:
                    - DB_HOST=db
                    - DB_PASSWORD=secret
                depends_on:
                    - db

            db:
                image: postgres:13
                volumes:
                    - postgres_data:/var/lib/postgresql/data
                environment:
                    - POSTGRES_PASSWORD=secret

        volumes:
        postgres_data:
        ```

2. 주요 명령어
    1. 기본 작업
        ```bash
        # 서비스 시작
        docker compose up

        # 백그라운드 실행
        docker compose up -d

        # 서비스 중지
        docker compose down

        # 서비스 상태 확인
        docker compose ps

        # 로그 확인
        docker compose logs
        ```

3. 환경 분리
    1. 개발/운영 환경 분리
        1. 기본 설정(docker-compose.yml)
        2. 개발 환경 설정(docker-compose.override.yml)
        3. 운영 환경 설정(docker-compose.prod.yml)

    2. 환경 분리 예시
        ```yaml
        # docker-compose.yml (기본)
        version: "3.8"
        services:
            web:
                image: nginx:alpine

        # docker-compose.override.yml (개발)
        services:
            web:
                volumes:
                - ./src:/app
                environment:
                - DEBUG=1

        # docker-compose.prod.yml (운영)
        services:
            web:
                restart: always
                environment:
                - DEBUG=0
        ```

4. Compose 베스트 프랙티스
    1. 환경변수 관리
        ```bash
        # .env 파일
        DB_PASSWORD=secret
        POSTGRES_VERSION=13
        ```

    2. 서비스 의존성 관리
        ```yaml
        services:
        api:
            depends_on:
            db:
                condition: service_healthy
            redis:
                condition: service_started
        ```

    3. 스케일링
        ```bash
        # 웹 서비스 3개 인스턴스로 확장
        docker compose up --scale web=3
        ```

    4. 네트워크 설정
        ```yaml
        services:
        web:
            networks:
            - frontend
        api:
            networks:
            - frontend
            - backend
        db:
            networks:
            - backend

        networks:
            frontend:
            backend:
                internal: true  # 외부 접근 차단
        ```

    5. 볼륨 관리
        ```yaml
        services:
        db:
            volumes:
            - db_data:/var/lib/postgresql/data
            - ./init.sql:/docker-entrypoint-initdb.d/init.sql

        volumes:
            db_data:
                driver: local
                driver_opts:
                type: none
                device: /data/postgresql
                o: bind
        ```

# Docker 운영 및 배포

1. 환경별 배포 전략
    1. CI/CD 파이프라인 구성
        ```yaml
        # GitLab CI 예시
        stages:
            - build
            - test
            - deploy

        build:
            stage: build
            script:
                - docker build -t myapp:${CI_COMMIT_SHA} .
                - docker push myapp:${CI_COMMIT_SHA}

        test:
            stage: test
            script:
                - docker pull myapp:${CI_COMMIT_SHA}
                - docker run myapp:${CI_COMMIT_SHA} npm test

        deploy:
            stage: deploy
            script:
                - docker tag myapp:${CI_COMMIT_SHA} myapp:latest
                - docker push myapp:latest
        ```

    2. 태그 전략
        1. 환경별 태그:
            - myapp:dev - 개발환경
            - myapp:staging - 스테이징 환경
            - myapp:prod - 운영 환경

        2. 버전 태그:
            - myapp:1.0.0 - 정식 릴리스
            - myapp:1.0.1 - 패치 버전

    2. 배포 전략
        1. Rolling Update
            - 점진적으로 새 버전 배포
            - 다운타임 없이 업데이트 가능
            ```bash
            docker service update --image myapp:2.0 --update-delay 10s myapp
            ```

        2. Blue-Green 배포
            - 두 환경을 번갈아 가며 배포
            - 빠른 롤백 가능
            ```bash
            # Blue 환경 배포
            docker stack deploy -c docker-compose.blue.yml myapp

            # Green 환경으로 전환
            docker stack deploy -c docker-compose.green.yml myapp
            ```

2. 모니터링과 로깅
    1. 로그 수집 구성
        ```yaml
        services:
        app:
            logging:
                driver: "json-file"
                options:
                    max-size: "10m"
                    max-file: "3"
        ```

    2. EFK 스택 구성
        ```yaml
        version: "3.8"
        services:
            fluentd:
                image: fluent/fluentd
                volumes:
                - ./fluentd/conf:/fluentd/etc
                ports:
                - "24224:24224"

            elasticsearch:
                image: elasticsearch:7.9.3
                environment:
                - discovery.type=single-node

            kibana:
                image: kibana:7.9.3
                ports:
                - "5601:5601"
        ```

3. 보안 설정
    1. 컨테이너 보안 강화
        ```dockerfile
        # Dockerfile 보안 설정
        FROM alpine:3.14
        RUN adduser -D appuser
        USER appuser
        ```

    2. 리소스 제한
        ```bash
        # 메모리 제한
        docker run --memory="512m" myapp

        # CPU 제한
        docker run --cpus="1.5" myapp
        ```

    3. 네트워크 보안
        ```yaml
        services:
            webapp:
                networks:
                - frontend
            database:
                networks:
                - backend
                internal: true  # 외부 접근 차단

        networks:
            frontend:
                driver: bridge
            backend:
                driver: bridge
                internal: true
        ```

4. Docker Swarm vs Kubernetes
    1. Docker Swarm
        - Docker 내장 오케스트레이션
        - 간단한 설정과 관리
        ```bash
        # Swarm 초기화
        docker swarm init

        # 서비스 배포
        docker service create --name myapp --replicas 3 myapp:latest
        ```

    2. Kubernetes
        - 더 강력한 오케스트레이션 기능
        - 복잡한 배포 시나리오 지원
        ```yaml
        # Kubernetes 배포 예시
        apiVersion: apps/v1
        kind: Deployment
        metadata:
            name: myapp
        spec:
            replicas: 3
            selector:
                matchLabels:
                app: myapp
            template:
                metadata:
                labels:
                    app: myapp
                spec:
                containers:
                - name: myapp
                    image: myapp:latest
        ```

# Multi-stage Builds

1. 개념과 목적
    - Multi-stage Build의 장점
        - 최종 이미지 크기 최소화
        - 빌드 의존성과 런타임 의존성 분리
        - 보안 향상: 빌드 도구와 소스 코드가 최종 이미지에 포함되지 않음

2. 예시 시나리오
    1. Go 애플리케이션 빌드
        ```dockerfile
        # 빌드 스테이지
        FROM golang:1.19 AS builder
        WORKDIR /app
        COPY go.* ./
        RUN go mod download
        COPY . .
        RUN CGO_ENABLED=0 GOOS=linux go build -o /go/bin/app

        # 최종 스테이지
        FROM alpine:3.14
        COPY --from=builder /go/bin/app /usr/local/bin/app
        EXPOSE 8080
        CMD ["app"]
        ```

    2. Node.js + React 프로젝트
        ```dockerfile
        # 빌드 스테이지
        FROM node:16 AS builder
        WORKDIR /app
        COPY package*.json ./
        RUN npm install
        COPY . .
        RUN npm run build

        # 운영 스테이지
        FROM nginx:alpine
        COPY --from=builder /app/build /usr/share/nginx/html
        EXPOSE 80
        CMD ["nginx", "-g", "daemon off;"]
        ```

    3. Java Spring Boot 애플리케이션
        ```dockerfile
        # 빌드 스테이지
        FROM maven:3.8-openjdk-11 AS builder
        WORKDIR /app
        COPY pom.xml .
        COPY src ./src
        RUN mvn clean package -DskipTests

        # 런타임 스테이지
        FROM openjdk:11-jre-slim
        COPY --from=builder /app/target/*.jar app.jar
        EXPOSE 8080
        CMD ["java", "-jar", "app.jar"]
        ```

3. 고급 기능 활용
    1. 조건부 빌드 스테이지
        ```dockerfile
        # 개발 빌드
        FROM node:16 AS development
        WORKDIR /app
        COPY package*.json ./
        RUN npm install
        COPY . .
        CMD ["npm", "run", "dev"]

        # 프로덕션 빌드
        FROM node:16 AS builder
        WORKDIR /app
        COPY package*.json ./
        RUN npm install --production
        COPY . .
        RUN npm run build

        # 프로덕션 실행
        FROM nginx:alpine AS production
        COPY --from=builder /app/dist /usr/share/nginx/html
        ```

    2. 캐시 활용 최적화
        ```dockerfile
        # 의존성 설치 스테이지
        FROM node:16 AS deps
        WORKDIR /app
        COPY package*.json ./
        RUN npm install

        # 빌드 스테이지
        FROM node:16 AS builder
        WORKDIR /app
        COPY --from=deps /app/node_modules ./node_modules
        COPY . .
        RUN npm run build

        # 실행 스테이지
        FROM nginx:alpine
        COPY --from=builder /app/dist /usr/share/nginx/html
        ```

3. 디버깅과 테스트
    * 중간 스테이지 빌드
        ```bash
        # 특정 스테이지까지만 빌드
        docker build --target builder -t myapp:builder .

        # 디버깅을 위한 중간 스테이지 진입
        docker run -it myapp:builder sh
        ```

# Docker 베스트 프렉티스

1. 이미지 최적화 전략
    1. 기본 이미지 선택
        ```dockerfile
        # 👎 나쁜 예: 큰 기본 이미지
        FROM ubuntu:latest

        # 👍 좋은 예: 경량 이미지 사용
        FROM alpine:latest
        # 또는
        FROM gcr.io/distroless/java11-debian11
        ```

    2. 레이어 최소화
        ```dockerfile
        # 👎 나쁜 예: 각 명령어마다 새 레이어 생성
        RUN apt-get update
        RUN apt-get install -y python3
        RUN apt-get install -y nginx

        # 👍 좋은 예: 명령어 체이닝
        RUN apt-get update && \
            apt-get install -y \
            python3 \
            nginx && \
            rm -rf /var/lib/apt/lists/*
        ```

2. 캐시 활용 최적화
    1. 의존성 관리
        ```dockerfile
        # 👍 좋은 예: 자주 변경되지 않는 레이어를 먼저 복사
        COPY package.json package-lock.json ./
        RUN npm install
        COPY . .
        ```

    2. .dockerignore 활용
        ```plaintext
        node_modules
        .git
        .env
        *.log
        test
        docs
        ```

3. CI/CD 통합 베스트 프렉티스
    1. 버전 관리
        ```bash
        # 이미지 태그 전략
        docker build -t myapp:${GIT_COMMIT_SHA} .
        docker tag myapp:${GIT_COMMIT_SHA} myapp:latest
        ```

    2. 자동화된 테스트
        ```yaml
        # GitLab CI 예시
        test:
            stage: test
            script:
                - docker build -t myapp:test .
                - docker run myapp:test npm run test
                - docker run -e CI=true myapp:test npm run lint
        ```

4. 운영 보안 강화
    1. 컨테이너 권한 제한
        ```dockerfile
        # 비루트 사용자 생성 및 전환
        RUN addgroup -S appgroup && adduser -S appuser -G appgroup
        USER appuser

        # 읽기 전용 루트 파일시스템 사용
        docker run --read-only myapp
        ```

    2. 리소스 제한 설정
        ```yaml
        services:
            api:
                deploy:
                    resources:
                        limits:
                        cpus: '0.50'
                        memory: 512M
                        reservations:
                        cpus: '0.25'
                        memory: 256M
        ```

5. 로깅과 모니터링
    1. 효율적인 로깅 구성
        ```yaml
        services:
            app:
                logging:
                    driver: "json-file"
                    options:
                        max-size: "10m"
                        max-file: "3"
                        labels: "production_status"
                        env: "os,customer"
        ```

    2. 헬스체크 구현
        ```dockerfile
        HEALTHCHECK --interval=30s --timeout=3s \
            CMD curl -f http://localhost/health || exit 1
        ```

6. 개발 생산성 향상
    1. 개발 환경 구성
        ```yaml
        version: "3.8"
        services:
            dev:
                build:
                context: .
                target: development
                volumes:
                - .:/app
                - /app/node_modules
                environment:
                - NODE_ENV=development
                ports:
                - "3000:3000"
        ```

    2. 디버깅 용이성
        ```bash
        # 디버그 모드로 실행
        docker run --rm -it \
            -v $(pwd):/app \
            -p 9229:9229 \
            myapp npm run debug
        ```

# 고급 주제와 확장 기능

1. Docker Networking 고급
    1. MACVLAN
        - MACVLAN은 Docker 컨테이너에 물리적 네트워크 인터페이스의 MAC 주소를 직접 할당하는 네트워크 드라이버입니다.

        * 작동 방식
            1. 각 컨테이너가 고유한 MAC 주소를 가짐
            2. 물리 네트워크에 직접 연결된 것처럼 동작
            3. 호스트의 네트워크 인터페이스를 통해 트래픽 전달

        * 사용 시나리오
            ```bash
            # MACVLAN 네트워크 생성 예시
            docker network create -d macvlan \
                --subnet=192.168.1.0/24 \
                --gateway=192.168.1.1 \
                -o parent=eth0 \
                -o macvlan_mode=bridge \
                macvlan_network

            # 컨테이너에 MACVLAN 네트워크 연결
            docker run --network=macvlan_network \
                --ip=192.168.1.10 \
                nginx
            ```

        * 장점:
            - 네트워크 성능 향상
            - 물리 네트워크와 직접 통신
            - 네트워크 격리성 우수

        * 단점
            - 호스트와 컨테이너 간 통신 제한
            - 네트워크 카드가 MACVLAN을 지원해야 함
            - 물리 네트워크 설정 변경 필요

    2. IPVLAN
        - IPVLAN은 하나의 MAC 주소를 공유하면서 여러 IP 주소를 사용하는 네트워크 드라이버입니다.

        1. 두 가지 모드
            1. L2 모드
                ```bash
                # IPVLAN L2 모드 네트워크 생성
                docker network create -d ipvlan \
                    --subnet=192.168.1.0/24 \
                    --gateway=192.168.1.1 \
                    -o parent=eth0 \
                    -o ipvlan_mode=l2 \
                    ipvlan_l2_network
                ```

            2. L3 모드
                ```bash
                # IPVLAN L3 모드 네트워크 생성
                docker network create -d ipvlan \
                    --subnet=192.168.1.0/24 \
                    -o parent=eth0 \
                    -o ipvlan_mode=l3 \
                    ipvlan_l3_network
                ```

            3. 구성 예시
                ```bash
                # 기본 IPVLAN 네트워크 설정
                docker network create -d ipvlan \
                    --subnet=192.168.1.0/24 \
                    --gateway=192.168.1.1 \
                    -o parent=eth0 \
                    ipvlan_network

                # 서브넷이 다른 두 번째 IPVLAN 네트워크
                docker network create -d ipvlan \
                    --subnet=192.168.2.0/24 \
                    --gateway=192.168.2.1 \
                    -o parent=eth0 \
                    ipvlan_network2
                ```

    3. MACVLAN vs IPVLAN
        1. MAC 주소 관리
            - MACVLAN: 각 컨테이너가 고유 MAC 주소
            - IPVLAN: 모든 컨테이너가 부모 인터페이스의 MAC 주소 공유

        2. 네트워크 격리
            - MACVLAN: L2 레벨에서 완전한 격리
            - IPVLAN: L3 레벨에서 격리 가능

        3. 성능
            - MACVLAN: 약간 더 높은 오버헤드
            - IPVLAN: 더 낮은 오버헤드, MAC 주소 관리 불필요

    4. 사용 사례
        1. MACVLAN
            - 완전한 네트워크 격리 필요
            - 레거시 네트워크 통합
            ```bash
            # 레거시 네트워크 통합 예시
            docker network create -d macvlan \
                --subnet=10.0.0.0/24 \
                --gateway=10.0.0.1 \
                -o parent=eth0 \
                -o macvlan_mode=bridge \
                legacy_network
            ```

        2. IPVLAN
            - 대규모 컨테이너 배포
            - MAC 주소 제한이 있는 환경
            ```bash
            # 대규모 배포 예시
            docker network create -d ipvlan \
                --subnet=10.0.0.0/16 \
                -o parent=eth0 \
                -o ipvlan_mode=l3 \
                large_scale_network
            ```

2. Docker BuildKit 상세 설명
    1. BuildKit이란?
        - BuildKit은 Docker의 차세대 이미지 빌드 엔진으로, 기존 빌드 엔진보다 더 빠르고 효율적인 빌드를 제공합니다.

    2. 주요 기능
        1. 병렬 빌드 처리
        2. 증분 빌드
        3. 더 나은 캐시 관리
        4. 더 나은 보안성

    3. 활성화 방법
        ```bash
        # 방법 1: 환경변수 설정
        export DOCKER_BUILDKIT=1

        # 방법 2: daemon.json 설정
        echo '{
            "features": {
                "buildkit": true
            }
        }' > /etc/docker/daemon.json
        ```

    4. 고급 기능 활용
        1. 병렬 처리
            ```dockerfile
            # 여러 플랫폼 동시 빌드
            FROM --platform=$BUILDPLATFORM golang:1.19 AS build
            ARG TARGETOS
            ARG TARGETARCH

            WORKDIR /src
            COPY go.mod go.sum .
            RUN go mod download

            COPY . .
            RUN --mount=type=cache,target=/root/.cache/go-build \
                CGO_ENABLED=0 GOOS=$TARGETOS GOARCH=$TARGETARCH \
                go build -o /bin/app
            ```

        2. 비밀 관리
            ```dockerfile
            # 비밀 파일 마운트
            RUN --mount=type=secret,id=aws,target=/root/.aws/credentials \
                aws s3 cp s3://mybucket/file.txt .

            # 비밀 사용 예시
            docker build --secret id=aws,src=~/.aws/credentials .
            ```

        3. SSH 마운트
            ```dockerfile
            # SSH 키를 이용한 private 저장소 접근
            RUN --mount=type=ssh ssh-keyscan github.com >> /known_hosts
            RUN --mount=type=ssh git clone git@github.com:private/repo.git
            ```

3. 컨테이너 오케스트레이션 상세 비교
    1. Docker Swarm
        1. 아키텍처
            1. Manager Node
                - 클러스터 상태 관리
                - 서비스 스케줄링
                - Raft 합의 알고리즘 사용

            2. Worker Node
                - 실제 컨테이너 실행
                - Manager의 명령 수행

        2. 주요 기능
            ```bash
            # Swarm 초기화
            docker swarm init --advertise-addr <MANAGER-IP>

            # 노드 추가
            docker swarm join --token <TOKEN> <MANAGER-IP>:2377

            # 서비스 배포
            docker service create \
                --name web \
                --replicas 3 \
                --update-delay 10s \
                --update-parallelism 1 \
                --update-order start-first \
                nginx:latest

            # 서비스 스케일링
            docker service scale web=5

            # 롤링 업데이트
            docker service update \
                --image nginx:new \
                --update-parallelism 2 \
                --update-delay 20s \
                web
            ```

    2. Kubernetes vs Swarm 상세 비교
        1. Kubernetes 특징
            1. 구성 요소
                ```yaml
                # Pod 예시
                apiVersion: v1
                kind: Pod
                metadata:
                    name: nginx
                spec:
                    containers:
                    - name: nginx
                        image: nginx:latest
                        resources:
                        limits:
                            memory: "128Mi"
                            cpu: "500m"
                        ports:
                        - containerPort: 80
                ```

            2. 서비스 디스커버리
                ```yaml
                # Service 예시
                apiVersion: v1
                kind: Service
                metadata:
                    name: nginx-service
                spec:
                    selector:
                        app: nginx
                    ports:
                    - port: 80
                        targetPort: 80
                    type: LoadBalancer
                ```

        2. Swarm 특징
            ```yaml
            # docker-compose.yml
            version: "3.8"
            services:
            web:
                image: nginx
                deploy:
                replicas: 3
                update_config:
                    parallelism: 1
                    delay: 10s
                restart_policy:
                    condition: on-failure
                ports:
                - "80:80"
            ```

# Docker 확장 가이드 개요 (Introduction)

1. 이 가이드의 목적
    - 이 확장 가이드는 Docker의 기본적인 개념과 사용법을 넘어서, 실제 엔터프라이즈 환경에서 마주치는 고급 시나리오와 문제 해결 방법을 다룹니다. 특히 다음과 같은 상황에서 유용한 정보를 제공합니다:
        - Docker Desktop과 Docker Engine의 차이점으로 인한 성능 이슈
        - 컨테이너 보안과 DevSecOps 구현
        - GPU 및 특수 하드웨어를 활용하는 컨테이너 워크로드
        - 클라우드 네이티브 환경에서의 Docker 활용

2. 대상 독자
    - 이 가이드는 다음과 같은 독자를 대상으로 합니다:
        - Docker의 기본 개념을 이해하고 있는 개발자
        - 엔터프라이즈 환경에서 Docker를 운영하는 DevOps 엔지니어
        - 컨테이너 기반의 AI/ML 인프라를 구축하려는 ML 엔지니어
        - 컨테이너 보안을 강화하려는 보안 담당자

3. 주요 다루는 문제/시나리오
    1. 개발 환경 최적화
        ```plaintext
        문제: Windows/macOS에서 Docker Desktop 사용 시 발생하는 성능 저하
        해결: WSL2 최적화, 리소스 제한 조정, 볼륨 마운트 최적화
        ```

    2. 보안 강화
        ```plaintext
        문제: 컨테이너 이미지 취약점, 민감정보 노출 위험
        해결: 자동화된 취약점 스캔, 안전한 시크릿 관리, 런타임 보안 정책
        ```

    3. 특수 워크로드
        ```plaintext
        문제: GPU 활용, 하드웨어 직접 접근이 필요한 상황
        해결: NVIDIA Container Toolkit, 디바이스 패스스루, 리소스 모니터링
        ```

4. 가이드 구성
    1. 각 챕터 구성
        - 개념 설명과 배경
        - 구체적인 설정 방법과 예시 코드
        - 실제 적용 시나리오와 팁
        - 주의사항과 문제해결 가이드

    2.  실습 환경 준비
        ```bash
        # 필요한 도구 설치
        ## Linux 환경
        apt-get update && apt-get install -y \
            docker.io \
            nvidia-container-toolkit \
            trivy

        ## macOS 환경
        brew install --cask docker
        brew install trivy

        ## Windows 환경
        choco install docker-desktop
        choco install trivy
        ```

5. 시작하기 전에
    - 이 가이드를 최대한 활용하기 위해 다음 사항을 확인해주세요:
        1. Docker 기본 개념 이해
            - 컨테이너와 이미지의 개념
            - Docker CLI 기본 명령어
            - Docker Compose 사용법
        
        2. 준비된 환경
            ```plaintext
            - Docker Engine 24.0 이상 또는 Docker Desktop 최신 버전
            - 최소 8GB RAM
            - (선택) NVIDIA GPU + 드라이버 설치
            ```

        3. 알아두면 좋은 도구
            ```plaintext
            - Visual Studio Code + Docker 확장
            - Portainer (Docker 관리 UI)
            - ctop (컨테이너 모니터링)
            ```

## Docker 환경별 차이점과 특징

1. Docker Desktop vs Docker Engine 아키텍처
    1. Docker Desktop 아키텍처
        ```plaintext
        Windows/macOS에서의 구조:
        Host OS → (Hypervisor) → Linux VM → Docker Engine → Containers
        ```

        * 주요 컴포넌트
            1. WSL2 (Windows)
                ```powershell
                # WSL2 메모리 제한 설정
                wsl --shutdown
                notepad "$env:USERPROFILE/.wslconfig"

                # .wslconfig 예시
                [wsl2]
                memory=6GB
                processors=4
                swap=2GB
                ```

            2. HyperKit (macOS)
                ```bash
                # Docker Desktop 리소스 설정
                # ~/Library/Group Containers/group.com.docker/settings.json
                {
                    "cpus": 4,
                    "memoryMiB": 6144,
                    "diskSizeMiB": 61035
                }
                ```

    2. Linux Docker Engine 아키텍처
        ```plaintext
        Host OS → Docker Engine → Containers (네이티브 성능)
        ```

        * 설정 최적화
            ```bash
            # /etc/docker/daemon.json
            {
                "storage-driver": "overlay2",
                "log-driver": "json-file",
                "log-opts": {
                    "max-size": "10m",
                    "max-file": "3"
                },
                "default-ulimits": {
                    "nofile": {
                    "Name": "nofile",
                    "Hard": 64000,
                    "Soft": 64000
                    }
                }
            }
            ```

2. 환경별 주요 차이점
    1. 볼륨 마운트 성능
        1. Docker Desktop
            ```yaml
            # docker-compose.yml 최적화 예시
            services:
                app:
                    volumes:
                    - .:/app:delegated  # 성능 향상을 위한 캐시 위임
            ```

        2. Linux Native
            ```yaml
            services:
                app:
                    volumes:
                    - .:/app  # 직접 마운트로 최고 성능
            ```

    2. 네트워크 차이점
        ```bash
        # Docker Desktop의 포트 포워딩
        localhost:8080 → VM → Container

        # Linux의 직접 네트워킹
        localhost:8080 → Container
        ```

3. 디버깅 및 문제 해결
    1. Docker Desktop 문제 해결
        ```bash
        # 로그 확인
        ## Windows
        %APPDATA%\Docker Desktop\log.txt

        ## macOS
        ~/Library/Containers/com.docker.docker/Data/log/vm.log

        # WSL2 재시작
        wsl --shutdown
        wsl --start
        ```

    2. Linux Engine 문제 해결
        ```bash
        # 시스템 로그 확인
        journalctl -u docker.service

        # Docker 데몬 상태 확인
        systemctl status docker

        # 디버그 모드 활성화
        dockerd --debug
        ```

4. 개발 워크플로우 통합
    1. VS Code 통합
        ```json
        // .devcontainer/devcontainer.json
        {
            "name": "Development",
            "dockerFile": "Dockerfile",
            "settings": {
                "terminal.integrated.shell.linux": "/bin/bash"
            },
            "extensions": [
                "ms-azuretools.vscode-docker"
            ],
            "mounts": [
                "source=${localWorkspaceFolder},target=/workspace,type=bind"
            ]
        }
        ```

    2. 성능 모니터링
        ```bash
        # 컨테이너 리소스 사용량
        docker stats

        # 상세 메트릭 수집 (Prometheus 포맷)
        docker run -d \
            --name cadvisor \
            --volume=/:/rootfs:ro \
            --volume=/var/run:/var/run:ro \
            --volume=/sys:/sys:ro \
            --volume=/var/lib/docker/:/var/lib/docker:ro \
            --publish=8080:8080 \
            gcr.io/cadvisor/cadvisor:latest
        ```

5. Key Takeaways
    1. Docker Desktop은 VM을 통해 동작하므로 성능 오버헤드가 있음
    2. Linux에서는 네이티브 성능을 얻을 수 있으나 세부 설정이 필요
    3. 환경에 따른 최적화 전략을 적절히 선택해야 함

## Container Security & DevSecOps

1. 이미지 취약점 관리
    1. Trivy를 이용한 이미지 스캐닝
        ```bash
        # 기본 스캔
        trivy image nginx:latest

        # 심각도 필터링
        trivy image --severity HIGH,CRITICAL nginx:latest

        # JSON 출력 (CI/CD 통합용)
        trivy image -f json -o results.json nginx:latest
        ```

    2. CI/CD 파이프라인 통합
        ```yaml
        # GitHub Actions 예시
        name: Container Security Scan
        on: [push]

        jobs:
            security_scan:
                runs-on: ubuntu-latest
                steps:
                - uses: actions/checkout@v2
                
                - name: Build image
                    run: docker build -t myapp:${{ github.sha }} .
                
                - name: Run Trivy vulnerability scanner
                    uses: aquasecurity/trivy-action@master
                    with:
                    image-ref: myapp:${{ github.sha }}
                    format: 'table'
                    exit-code: '1'
                    ignore-unfixed: true
                    severity: 'CRITICAL,HIGH'
        ```

2. 민감정보 관리
    1. Docker Secrets
        ```bash
        # 시크릿 생성
        echo "my_secret_password" | docker secret create db_password -

        # 서비스에서 시크릿 사용
        docker service create \
            --name db \
            --secret db_password \
            --secret source=db_password,target=/run/secrets/password \
            mysql:8.0
        ```

    2. HashiCorp Vault 통합
        ```yaml
        # docker-compose.yml
        services:
        app:
            image: myapp
            environment:
            - VAULT_ADDR=http://vault:8200
            volumes:
            - type: bind
                source: ./vault-agent.hcl
                target: /vault/config/agent.hcl
        ```
        ```hcl
        # vault-agent.hcl
        auto_auth {
            method "approle" {
                config = {
                role_id_file_path = "/vault/config/role-id"
                secret_id_file_path = "/vault/config/secret-id"
                }
            }
        }
        ```

3. 런타임 보안 강화
    1. 보안 옵션 설정
        ```yaml
        # docker-compose.yml with security options
        services:
            webapp:
                image: myapp
                security_opt:
                - no-new-privileges:true
                - seccomp:custom-seccomp.json
                read_only: true
                tmpfs:
                - /tmp
                - /var/run
                cap_drop:
                - ALL
                cap_add:
                - NET_BIND_SERVICE
        ```

    2. AppArmor 프로필 적용
        ```bash
        # AppArmor 프로필 로드
        apparmor_parser -r -W custom-profile

        # 컨테이너에 프로필 적용
        docker run --security-opt apparmor=custom-profile nginx
        ```

    3. Falco를 이용한 런타임 모니터링
        ```yaml
        # falco.yaml
        rules:
            - rule: Terminal shell in container
                desc: A shell was spawned by a container
                condition: container.id != host and proc.name = bash
                output: Shell in container (user=%user.name container=%container.name)
                priority: WARNING
        ```

4. 컨테이너 보안 베스트 프랙티스
    1. 이미지 생성 시 
        ```dockerfile
        # 보안 강화 Dockerfile
        FROM alpine:3.14

        # 시스템 업데이트 및 취약점 패치
        RUN apk update && apk upgrade

        # 전용 사용자 생성
        RUN adduser -D appuser

        # 필요한 디렉토리 권한 설정
        WORKDIR /app
        COPY --chown=appuser:appuser . .

        # 비root 사용자로 전환
        USER appuser

        # 실행 명령
        CMD ["./app"]
        ```

    2. 컨테이너 실행 시
        ```bash
        # 리소스 제한
        docker run -d \
            --cpus=".5" \
            --memory="512m" \
            --pids-limit=100 \
            --security-opt="no-new-privileges:true" \
            nginx
        ```

5. Key Takeaways
    1. 이미지 취약점 스캔은 CI/CD 파이프라인의 필수 요소
    2. 민감정보는 반드시 외부 시크릿 관리 도구를 통해 관리
    3. 런타임 보안은 여러 계층(컨테이너, 호스트, 네트워크)에서 구현 필요

## 특수 워크로드 컨테이너화

1. GPU 워크로드 구성
    1. NVIDIA Container Toolkit 설정
        ```bash
        # NVIDIA Container Toolkit 설치
        distribution=$(. /etc/os-release;echo $ID$VERSION_ID) \
            && curl -s -L https://nvidia.github.io/libnvidia-container/gpgkey | sudo apt-key add - \
            && curl -s -L https://nvidia.github.io/libnvidia-container/$distribution/libnvidia-container.list | \
            sudo tee /etc/apt/sources.list.d/nvidia-container-toolkit.list

        sudo apt-get update && sudo apt-get install -y nvidia-container-toolkit
        ```

    2. Docker 설정
        ```json
        // /etc/docker/daemon.json
        {
            "default-runtime": "nvidia",
            "runtimes": {
                "nvidia": {
                    "path": "nvidia-container-runtime",
                    "runtimeArgs": []
                }
            }
        }
        ```

    3. GPU 활용 예시
        ```dockerfile
        # GPU 기반 딥러닝 환경
        FROM nvidia/cuda:11.6.2-base-ubuntu20.04

        RUN apt-get update && apt-get install -y \
            python3 \
            python3-pip \
            && rm -rf /var/lib/apt/lists/*

        RUN pip3 install torch torchvision torchaudio

        WORKDIR /app
        COPY . .

        CMD ["python3", "train.py"]
        ```
        ```yaml
        # docker-compose.yml
        version: "3.8"
        services:
            ml-training:
                build: .
                deploy:
                resources:
                    reservations:
                    devices:
                        - driver: nvidia
                        count: 1
                        capabilities: [gpu]
        ```

2. 특수 하드웨어 액세스
    1. USB 디바이스 연결
        ```bash
        # USB 디바이스 목록 확인
        lsusb

        # 특정 USB 디바이스 마운트
        docker run --device=/dev/ttyUSB0:/dev/ttyUSB0 \
            -v /dev/bus/usb:/dev/bus/usb \
            --privileged \
            my-iot-app
        ```

    2. 네트워크 카드 직접 접근
        ```yaml
        # docker-compose.yml
        services:
            network-app:
                image: network-tools
                network_mode: host
                cap_add:
                - NET_ADMIN
                - NET_RAW
                devices:
                - /dev/net/tun:/dev/net/tun
        ```

3. 특수 워크로드 모니터링
    1. GPU 모니터링
        ```bash
        # NVIDIA-SMI 통합
        docker run --gpus all \
            -v /usr/bin/nvidia-smi:/usr/bin/nvidia-smi \
            my-gpu-app nvidia-smi
        ```

    2. Prometheus + Grafana 설정
        ```yaml
        # docker-compose.monitoring.yml
        services:
            prometheus:
                image: prom/prometheus
                volumes:
                - ./prometheus.yml:/etc/prometheus/prometheus.yml
                ports:
                - "9090:9090"

            grafana:
                image: grafana/grafana
                ports:
                - "3000:3000"
                environment:
                - GF_SECURITY_ADMIN_PASSWORD=secret
                volumes:
                - grafana-data:/var/lib/grafana

            dcgm-exporter:
                image: nvidia/dcgm-exporter
                runtime: nvidia
                ports:
                - "9400:9400"

        volumes:
            grafana-data:
        ```
        ```yaml
        # prometheus.yml
        global:
            scrape_interval: 15s

        scrape_configs:
            - job_name: 'gpu_metrics'
                static_configs:
                - targets: ['dcgm-exporter:9400']
        ```

    3. 리소스 사용량 알림 설정
        ```yaml
        # alertmanager.yml
        route:
            group_by: ['instance']
            group_wait: 30s
            group_interval: 5m
            repeat_interval: 1h
            receiver: 'slack'

        receivers:
            - name: 'slack'
                slack_configs:
                - api_url: 'https://hooks.slack.com/services/T00000000/B00000000/XXXXXXXXXXXXXXXXXXXXXXXX'
                    channel: '#monitoring'
        ```

4. Key Takeaways
    1. GPU 워크로드는 NVIDIA Container Toolkit 설정이 필수
    2. 특수 하드웨어 접근 시 보안 고려사항 확인 필요
    3. 모니터링은 Prometheus + Grafana + DCGM-Exporter 조합이 표준

## 대체 컨테이너 런타임

1. OCI호환 런타임 소개
    1. Podman 아키텍처
        ```bash
        # Podman 설치
        # Ubuntu/Debian
        sudo apt-get install -y podman

        # RHEL/CentOS
        sudo dnf install -y podman

        # 기본 사용법
        podman run nginx  # Docker와 유사한 명령어
        podman pod create # Pod 생성 (K8s 스타일)
        ```

    2. Podman vs Docker 비교
        ```bash
        # Docker
        docker run -d nginx

        # Podman (루트리스 컨테이너)
        podman run --userns=keep-id -d nginx

        # 시스템 서비스 없이 실행
        podman run --network=host nginx
        ```

2. containerd 상세
    1. containerd 설정
        ```yaml
        # /etc/containerd/config.toml
        version = 2
        [plugins]
            [plugins."io.containerd.grpc.v1.cri"]
                [plugins."io.containerd.grpc.v1.cri".containerd]
                default_runtime_name = "runc"
                [plugins."io.containerd.grpc.v1.cri".containerd.runtimes.runc]
                    runtime_type = "io.containerd.runc.v2"
        ```

    2. nerdctl 사용
        ```bash
        # nerdctl 설치
        wget https://github.com/containerd/nerdctl/releases/download/v0.22.2/nerdctl-0.22.2-linux-amd64.tar.gz
        sudo tar Cxzvf /usr/local/bin nerdctl-0.22.2-linux-amd64.tar.gz

        # 컨테이너 관리
        nerdctl run -d nginx
        nerdctl compose up
        ```

3. CRI-O 설정
    1. 기본 설정
        ```bash
        # CRI-O 설치
        OS=xUbuntu_20.04
        VERSION=1.23

        echo "deb https://download.opensuse.org/repositories/devel:/kubic:/libcontainers:/stable/$OS/ /"| sudo tee /etc/apt/sources.list.d/devel:kubic:libcontainers:stable.list
        curl -L https://download.opensuse.org/repositories/devel:/kubic:/libcontainers:/stable/$OS/Release.key | sudo apt-key add -
        sudo apt-get update
        sudo apt-get install cri-o cri-o-runc
        ```

    2. CRI-O 설정 파일
        ```toml
        # /etc/crio/crio.conf
        [crio]
        root = "/var/lib/containers/storage"
        runroot = "/var/run/containers/storage"
        storage_driver = "overlay"

        [crio.runtime]
        default_runtime = "runc"
        ```

4. 마이그레이션 전략
    1. Docker -> Podman
        ```bash
        # 1. 이미지 마이그레이션
        docker save myapp > myapp.tar
        podman load < myapp.tar

        # 2. 컨테이너 설정 변환
        # docker-compose.yml을 podman-compose.yml로 변환
        podman-compose up

        # 3. 시스템 서비스 마이그레이션
        podman generate systemd --name myapp > /etc/systemd/system/myapp.service
        systemctl enable --now myapp
        ```

    2. Docker -> containerd
        ```bash
        # 1. Docker 중지
        systemctl stop docker

        # 2. containerd 설정
        cat > /etc/containerd/config.toml <<EOF
        version = 2
        [plugins."io.containerd.grpc.v1.cri"]
        sandbox_image = "k8s.gcr.io/pause:3.6"
        EOF

        # 3. 서비스 시작
        systemctl restart containerd
        ```

5. Key Takeaways
    1. 각 런타임은 고유한 장단점 보유
        - Podman: 데몬리스, 루트리스 실행
        - containerd: 쿠버네티스 통합
        - CRI-O: 쿠버네티스 최적화

    2. 마이그레이션은 단계적으로 진행
        - 이미지 -> 컨테이너 -> 설정 -> 서비스 순

    3. 호환성 고려 필수
        - OCI 표준 준수 확인
        - 기존 도구/스크립트 검증

## 엔터프라이즈 확장 기능

1. 고가용성 구성
    1. Docker Swarm HA 설정
        ```bash
        # 매니저 노드 초기화
        docker swarm init --advertise-addr <MANAGER-IP>

        # 매니저 노드 추가 (3개 이상 권장)
        docker swarm join-token manager
        docker swarm join \
        --token <MANAGER-TOKEN> \
        --advertise-addr <MANAGER2-IP> \
        <MANAGER1-IP>:2377

        # 상태 확인
        docker node ls
        ```

    2. 백업 및 복구 전략
        ```bash
        # Swarm 상태 백업
        tar zcf backup.tar.gz \
        /var/lib/docker/swarm \
        /var/lib/docker/network \
        /var/lib/docker/volumes

        # 자동 백업 스크립트
        cat > /etc/cron.daily/docker-backup <<EOF
        #!/bin/bash
        BACKUP_DIR="/backup/docker"
        DATE=$(date +%Y%m%d)
        mkdir -p $BACKUP_DIR
        tar zcf $BACKUP_DIR/docker-$DATE.tar.gz \
        /var/lib/docker/swarm \
        /var/lib/docker/network \
        /var/lib/docker/volumes
        find $BACKUP_DIR -type f -mtime +7 -delete
        EOF
        ```

    3. 장애 복구 자동화
        ```yaml
        # docker-compose.yml with failover
        version: "3.8"
        services:
            webapp:
                image: nginx
                deploy:
                replicas: 3
                placement:
                    constraints:
                    - node.role == worker
                restart_policy:
                    condition: any
                    delay: 5s
                    max_attempts: 3
                    window: 120s
                update_config:
                    parallelism: 1
                    delay: 10s
                    order: start-first
        ```

2. 고급 모니터링 구성
    1. Prometheus 상세 설정
        ```yaml
        # prometheus.yml
        global:
            scrape_interval: 15s
            evaluation_interval: 15s

        rule_files:
        - "alert.rules"

        alerting:
            alertmanagers:
                - static_configs:
                    - targets: ['alertmanager:9093']

        scrape_configs:
            - job_name: 'docker'
                static_configs:
                - targets: ['localhost:9323']

            - job_name: 'node-exporter'
                static_configs:
                - targets: ['node-exporter:9100']

            - job_name: 'cadvisor'
                static_configs:
                - targets: ['cadvisor:8080']
        ```

    2. 로그 수집 및 분석
        ```yaml
        # EFK 스택 구성
        services:
            elasticsearch:
                image: docker.elastic.co/elasticsearch/elasticsearch:7.9.3
                environment:
                - node.name=elasticsearch
                - discovery.type=single-node
                - "ES_JAVA_OPTS=-Xms512m -Xmx512m"
                volumes:
                - elasticsearch_data:/usr/share/elasticsearch/data

            fluent-bit:
                image: fluent/fluent-bit
                volumes:
                - ./fluent-bit.conf:/fluent-bit/etc/fluent-bit.conf
                - /var/lib/docker/containers:/var/lib/docker/containers:ro

            kibana:
                image: docker.elastic.co/kibana/kibana:7.9.3
                environment:
                - ELASTICSEARCH_HOSTS=http://elasticsearch:9200
                ports:
                - "5601:5601"
        ```

3. 성능 최적화
    1. 스토리지 최적화
        ```json
        // /etc/docker/daemon.json
        {
            "storage-driver": "overlay2",
            "storage-opts": [
                "overlay2.override_kernel_check=true"
            ],
            "data-root": "/data/docker",
            "log-driver": "json-file",
            "log-opts": {
                "max-size": "10m",
                "max-file": "3"
            }
        }
        ```

    2. 네트워크 성능 향상
        ```bash
        # MTU 최적화
        docker network create \
            --driver=overlay \
            --opt com.docker.network.driver.mtu=9000 \
            my_network

        # TCP 튜닝
        cat >> /etc/sysctl.conf <<EOF
        net.ipv4.tcp_tw_reuse=1
        net.ipv4.ip_local_port_range=1024 65000
        net.core.somaxconn=65535
        EOF
        sysctl -p
        ```

4. Key Takeaways
    1. HA 구성은 최소 3개의 매니저 노드 필요
    2. 자동화된 백업/복구 전략 필수
    3. 모니터링은 멀티 레이어(인프라, 컨테이너, 애플리케이션)로 구성

## 클라우드 네이티브 통합

1. 클라우드 서비스 연동
    1. AWS ECS 통합
        ```yaml
        # task-definition.json
        {
            "family": "webapp",
            "containerDefinitions": [
                {
                "name": "web",
                "image": "nginx:latest",
                "memory": 512,
                "cpu": 256,
                "portMappings": [
                    {
                    "containerPort": 80,
                    "hostPort": 80,
                    "protocol": "tcp"
                    }
                ],
                "logConfiguration": {
                    "logDriver": "awslogs",
                    "options": {
                    "awslogs-group": "/ecs/webapp",
                    "awslogs-region": "us-east-1"
                    }
                }
                }
            ]
        }
        ```

    2. Azure Container Instances
        ```bash
        # Azure CLI를 통한 컨테이너 배포
        az container create \
            --resource-group myResourceGroup \
            --name myapp \
            --image myregistry.azurecr.io/myapp:latest \
            --dns-name-label myapp \
            --ports 80 \
            --cpu 1 \
            --memory 1.5

        # 컨테이너 그룹 설정
        az container create \
            --resource-group myResourceGroup \
            --name myapp-group \
            --file container-group.yaml
        ```

    3. GCP Clound Run
        ```yaml
        # service.yaml
        apiVersion: serving.knative.dev/v1
        kind: Service
        metadata:
            name: myapp
        spec:
            template:
                spec:
                containers:
                    - image: gcr.io/myproject/myapp:latest
                    resources:
                        limits:
                        memory: "256Mi"
                        cpu: "1000m"
                    ports:
                        - containerPort: 8080
        ```

2. 서비스메시 통합
    1. Istio 설정
        ```yaml
        # application.yaml
        apiVersion: networking.istio.io/v1alpha3
        kind: VirtualService
        metadata:
            name: myapp-routes
        spec:
            hosts:
                - myapp.example.com
            gateways:
                - myapp-gateway
            http:
                - match:
                    - uri:
                        prefix: /api
                route:
                    - destination:
                        host: myapp-service
                        subset: v1
                    weight: 90
                    - destination:
                        host: myapp-service
                        subset: v2
                    weight: 10
        ```

    2. 트래픽 관리
        ```yaml
        # destination-rule.yaml
        apiVersion: networking.istio.io/v1alpha3
        kind: DestinationRule
        metadata:
            name: myapp
        spec:
            host: myapp-service
            trafficPolicy:
                loadBalancer:
                simple: ROUND_ROBIN
                connectionPool:
                tcp:
                    maxConnections: 100
                http:
                    http1MaxPendingRequests: 1
                    maxRequestsPerConnection: 10
            subsets:
                - name: v1
                labels:
                    version: v1
                - name: v2
                labels:
                    version: v2
        ```

3. 멀티클라우드 전략
    1. Docker Context 활용
        ```bash
        # AWS Context 생성
        docker context create ecs myapp-ecs
        docker context use myapp-ecs

        # Azure Context 생성
        docker context create aci myapp-aci
        docker context use myapp-aci

        # Context 전환을 통한 배포
        docker compose up  # 현재 Context에 배포
        ```

    2. 멀티클라우드 로드밸런싱
        ```yaml
        # global-lb.yaml
        apiVersion: v1
        kind: Service
        metadata:
            name: global-lb
            annotations:
                service.beta.kubernetes.io/aws-load-balancer-type: nlb
                service.beta.kubernetes.io/azure-load-balancer-internal: "true"
        spec:
            type: LoadBalancer
            ports:
                - port: 80
                targetPort: 8080
            selector:
                app: myapp
        ```

4. Key Takeaways
    1. 클라우드 제공자별 특화 기능 활용이 중요
    2. 서비스메시를 통한 트래픽 제어는 마이크로서비스의 필수 요소
    3. 멀티클라우드 전략은 복잡성과 이점을 잘 저울질해야 함

## 컨테이너 네트워크 고급 구성

1. SDN(Software-Defined Networking) 통합
    1. Calico 네트워크 정책
        ```yaml
        # calico-policy.yaml
        apiVersion: projectcalico.org/v3
        kind: NetworkPolicy
        metadata:
            name: restrict-traffic
        spec:
            selector: app == 'frontend'
            types:
                - Ingress
                - Egress
            ingress:
                - action: Allow
                protocol: TCP
                source:
                    selector: role == 'external-lb'
                destination:
                    ports:
                    - 80
                    - 443
        ```

    2. Cilium과 eBPE 설정
        ```bash
        # Cilium 설치
        helm repo add cilium https://helm.cilium.io/
        helm install cilium cilium/cilium \
            --namespace kube-system \
            --set ebpf.enabled=true
        ```
        ```yaml
        # cilium-network-policy.yaml
        apiVersion: "cilium.io/v2"
        kind: CiliumNetworkPolicy
        metadata:
            name: "secure-frontend"
        spec:
            endpointSelector:
                matchLabels:
                app: frontend
            ingress:
                - fromEndpoints:
                    - matchLabels:
                        app: api-gateway
                toPorts:
                    - ports:
                    - port: "80"
                        protocol: TCP
        ```

2. 서비스 디스커버리
    1. Consul 통합
        ```yaml
        # docker-compose.consul.yml
        version: '3.8'
        services:
            consul-server:
                image: hashicorp/consul:latest
                command: agent -server -bootstrap-expect=1
                volumes:
                - consul-data:/consul/data
                ports:
                - "8500:8500"
                - "8600:8600/udp"

            app:
                image: myapp
                environment:
                - CONSUL_HTTP_ADDR=consul-server:8500
                depends_on:
                - consul-server

        volumes:
            consul-data:
        ```
        ```hcl
        # consul-config.hcl
        service {
            name = "myapp"
            port = 8080
            
            check {
                id = "myapp-health"
                http = "http://localhost:8080/health"
                interval = "10s"
                timeout = "1s"
            }

            connect {
                sidecar_service {}
            }
        }
        ```

    2. DNS 기반 서비스 디스커버리
        ```yaml
        # CoreDNS 설정
        .:53 {
            errors
            health
            kubernetes cluster.local in-addr.arpa ip6.arpa {
                pods insecure
                fallthrough in-addr.arpa ip6.arpa
            }
            forward . /etc/resolv.conf
            cache 30
            loop
            reload
            loadbalance
        }
        ```

    3. 동적 프록시 구성
        ```yaml
        # traefik.yaml
        providers:
            docker:
                endpoint: "unix:///var/run/docker.sock"
                exposedByDefault: false
                network: web

        entryPoints:
            web:
                address: ":80"
            websecure:
                address: ":443"

        certificatesResolvers:
            myresolver:
                acme:
                email: admin@example.com
                storage: acme.json
                httpChallenge:
                    entryPoint: web
        ```