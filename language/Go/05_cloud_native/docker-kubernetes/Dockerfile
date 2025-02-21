######################
# 빌드 스테이지
######################
FROM golang:1.21-alpine AS builder

# 필요한 빌드 도구 설치
RUN apk add --no-cache git make

# 작업 디렉토리 설정
WORKDIR /app

# 먼저 의존성 파일만 복사하여 레이어 캐싱 활용
COPY go.mod go.sum ./
RUN go mod download && go mod verify

# 소스 코드 복사
COPY . .

# 빌드 (정적 바이너리로 컴파일)
# CGO_ENABLED=0: C 바인딩 비활성화 (순수 Go 코드로 컴파일)
# -ldflags="-s -w": 디버그 정보 제거로 바이너리 크기 축소
# -trimpath: 빌드 경로 정보 제거로 재현 가능한 빌드 생성
RUN CGO_ENABLED=0 GOOS=linux GOARCH=amd64 go build \
    -ldflags="-s -w -X main.version=$(git describe --tags --always --dirty) -X main.buildTime=$(date +%FT%T%z)" \
    -trimpath \
    -o /go/bin/app \
    ./cmd/api

######################
# 실행 스테이지
######################
FROM alpine:3.18

# 보안 스캐닝을 위한 비 루트 사용자 생성
RUN addgroup -S appgroup && adduser -S appuser -G appgroup

# 기본 timezone 설정
RUN apk --no-cache add tzdata
ENV TZ=Asia/Seoul

# 인증서 설치 (HTTPS 요청 등에 필요)
RUN apk --no-cache add ca-certificates

# 앱 디렉토리 생성 및 권한 설정
WORKDIR /app
RUN chown -R appuser:appgroup /app

# 설정 파일 및 필요한 리소스 복사
COPY --from=builder /go/bin/app /app/
COPY configs /app/configs
COPY static /app/static

# 비 루트 사용자로 전환
USER appuser

# 애플리케이션 포트 노출
EXPOSE 8080

# 헬스체크 설정 (Kubernetes 등에서 활용)
HEALTHCHECK --interval=30s --timeout=3s --start-period=5s --retries=3 \
  CMD wget -qO- http://localhost:8080/health || exit 1

# 환경 변수 설정
ENV APP_ENV=production \
    LOG_LEVEL=info

# 컨테이너 시작 시 실행할 명령어
ENTRYPOINT ["/app/app"]
CMD ["--config", "/app/configs/config.production.yaml"]