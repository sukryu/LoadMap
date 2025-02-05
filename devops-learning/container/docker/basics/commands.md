# Docker 주요 명령어 가이드

> **목표:**  
> - Docker의 기본 명령어와 사용법을 이해한다.
> - 명령어의 다양한 옵션과 활용 방법을 습득한다.
> - 실제 사용 사례를 통해 명령어 활용법을 익힌다.
> - 명령어 사용 시 주의사항과 모범 사례를 파악한다.

---

## 1. 기본 명령어 구조

Docker 명령어는 다음과 같은 기본 구조를 가집니다:
```bash
docker [명령어] [옵션] [대상]
```

예를 들어, nginx 이미지를 실행할 때는 다음과 같이 사용합니다:
```bash
docker run -d -p 80:80 nginx
```

여기서:
- `run`: 컨테이너 실행 명령어
- `-d`: 백그라운드 실행 옵션
- `-p 80:80`: 포트 매핑 옵션
- `nginx`: 실행할 이미지 이름

---

## 2. 이미지 관련 명령어

### 2.1 이미지 검색
```bash
# Docker Hub에서 이미지 검색
docker search nginx

# 결과 제한
docker search --limit 5 nginx

# 공식 이미지만 검색
docker search --filter "is-official=true" nginx
```

### 2.2 이미지 다운로드
```bash
# 최신 버전 다운로드
docker pull nginx

# 특정 버전 다운로드
docker pull nginx:1.21

# 다중 플랫폼 이미지 다운로드
docker pull --platform linux/amd64 nginx
```

### 2.3 이미지 관리
```bash
# 이미지 목록 확인
docker images
docker image ls

# 이미지 상세 정보 확인
docker image inspect nginx

# 이미지 삭제
docker rmi nginx
docker image rm nginx

# 사용하지 않는 이미지 정리
docker image prune
```

---

## 3. 컨테이너 관련 명령어

### 3.1 컨테이너 생성 및 실행
```bash
# 기본 실행
docker run nginx

# 백그라운드 실행 및 포트 매핑
docker run -d -p 80:80 --name my-nginx nginx

# 환경 변수 설정
docker run -e MYSQL_ROOT_PASSWORD=mysecret mysql

# 볼륨 마운트
docker run -v /host/path:/container/path nginx

# 리소스 제한 설정
docker run --memory="512m" --cpus="1.0" nginx
```

### 3.2 컨테이너 관리
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

# 실행 중인 컨테이너 강제 삭제
docker rm -f my-nginx
```

### 3.3 컨테이너 상호작용
```bash
# 컨테이너 내부 셸 접속
docker exec -it my-nginx /bin/bash

# 로그 확인
docker logs my-nginx

# 실시간 로그 확인
docker logs -f my-nginx

# 컨테이너 리소스 사용량 확인
docker stats my-nginx
```

---

## 4. 네트워크 관련 명령어

### 4.1 네트워크 생성 및 관리
```bash
# 네트워크 생성
docker network create my-network

# 네트워크 목록 확인
docker network ls

# 네트워크 상세 정보
docker network inspect my-network

# 네트워크 삭제
docker network rm my-network
```

### 4.2 컨테이너 네트워크 연결
```bash
# 컨테이너를 네트워크에 연결
docker network connect my-network my-nginx

# 컨테이너의 네트워크 연결 해제
docker network disconnect my-network my-nginx
```

---

## 5. 볼륨 관련 명령어

### 5.1 볼륨 생성 및 관리
```bash
# 볼륨 생성
docker volume create my-volume

# 볼륨 목록 확인
docker volume ls

# 볼륨 상세 정보
docker volume inspect my-volume

# 볼륨 삭제
docker volume rm my-volume

# 사용하지 않는 볼륨 정리
docker volume prune
```

### 5.2 볼륨 사용
```bash
# 볼륨을 사용하여 컨테이너 실행
docker run -v my-volume:/var/lib/mysql mysql

# 호스트 디렉토리 마운트
docker run -v $(pwd):/usr/share/nginx/html nginx
```

---

## 6. 시스템 및 관리 명령어

### 6.1 시스템 정보
```bash
# Docker 버전 확인
docker version

# 상세 시스템 정보
docker info

# 디스크 사용량 확인
docker system df

# 실시간 이벤트 모니터링
docker events
```

### 6.2 시스템 정리
```bash
# 미사용 리소스 정리
docker system prune

# 볼륨 포함하여 정리
docker system prune -a --volumes
```

---

## 7. 명령어 사용 시 주의사항

### 7.1 보안 관련
- 컨테이너 실행 시 권한 설정 주의
- 민감한 환경 변수는 파일로 관리
- 네트워크 포트 노출 시 보안 고려

### 7.2 리소스 관리
- 컨테이너에 적절한 리소스 제한 설정
- 불필요한 이미지와 컨테이너 주기적 정리
- 로그 크기 제한 설정

---

## 8. 실전 활용 예제

### 8.1 웹 서버 배포
```bash
# Nginx 웹 서버 실행
docker run -d \
  --name my-nginx \
  -p 80:80 \
  -v $(pwd)/html:/usr/share/nginx/html \
  --restart unless-stopped \
  nginx
```

### 8.2 데이터베이스 서버 배포
```bash
# MySQL 데이터베이스 실행
docker run -d \
  --name my-mysql \
  -e MYSQL_ROOT_PASSWORD=mysecret \
  -e MYSQL_DATABASE=myapp \
  -v mysql-data:/var/lib/mysql \
  --restart always \
  mysql:5.7
```

---

## 참고 자료

- [Docker 명령어 공식 문서](https://docs.docker.com/engine/reference/commandline/cli/)
- [Docker 명령어 치트 시트](https://docs.docker.com/get-started/docker_cheatsheet.pdf)
- [Docker 컨테이너 가이드](https://docs.docker.com/engine/reference/run/)

---

## 마무리

이 문서에서 다룬 Docker 명령어들은 컨테이너 기반 개발과 운영에 필수적인 도구입니다. 각 명령어의 기본 사용법부터 고급 옵션까지 익히고, 실제 환경에서 활용해보면서 숙달하는 것이 중요합니다. 명령어를 조합하여 사용하면 더욱 효율적인 Docker 환경 관리가 가능합니다.