# Gin Framework

1. Gin이란?
    - Gin은 Go 언어로 작성된 HTTP 웹 프레임워크로, 다음과 같은 특징을 가집니다:

    1. 핵심 특징:
        - 고성능: Martini와 유사한 API를 제공하면서도 40배 더 빠른 성능
        - 경량화: 필수적인 기능만 포함한 미니멀한 프레임워크
        - 미들웨어 지원: 유연한 미들웨어 시스템으로 기능 확장 용이
        - JSON 검증: 자동화된 JSON 검증 및 바인딩
        - 라우팅: 고성능 httprouter 기반의 라우팅
        - 에러 관리: 편리한 에러 관리 시스템

    2. 주요 장점:
        1. 빠른 개발 속도
            - 직관적인 API
            - 풍부한 미들웨어 생태계
            - 간단한 설정

        2. 높은 성능
            - Zero allocation router
            - 메모리 사용 최적화
            - 빠른 응답 시간

        3. 안정성
            - 내장된 복구(recovery) 시스템
            - 광범위한 테스트 커버리지
            - 검증된 프로덕션 환경

2. 기본 아키텍처
    1. 핵심 컴포넌트
        ```go
        // 기본 Gin 엔진
        r := gin.Default()  // Logger와 Recovery 미들웨어 포함
        // 또는
        r := gin.New()      // 미들웨어 없는 깨끗한 엔진
        ```

    2. 주요 인터페이스
        ```go
        // Context 인터페이스 - 요청 처리의 핵심
        type Context interface {
            // HTTP 요청/응답 관련
            Request() *http.Request
            Writer() ResponseWriter
            
            // 파라미터 접근
            Param(key string) string
            Query(key string) string
            PostForm(key string) string
            
            // 응답 메서드
            JSON(code int, obj interface{})
            XML(code int, obj interface{})
            String(code int, format string, values ...interface{})
            
            // 미들웨어 관련
            Next()
            Abort()
        }
        ```

3. Hello World 예제
    ```go
    package main

    import "github.com/gin-gonic/gin"

    func main() {
        // Gin 엔진 생성
        r := gin.Default()
        
        // 라우트 설정
        r.GET("/", func(c *gin.Context) {
            c.JSON(200, gin.H{
                "message": "Hello Gin Framework!",
            })
        })
        
        // 서버 시작
        r.Run(":8080")
    }
    ```

4. 기본 기능 요약
    1. 라우팅
        ```go
        // 기본 HTTP 메서드 지원
        r.GET("/path", handlerFunc)
        r.POST("/path", handlerFunc)
        r.PUT("/path", handlerFunc)
        r.DELETE("/path", handlerFunc)

        // 그룹 라우팅
        v1 := r.Group("/api/v1")
        {
            v1.GET("/users", getUsers)
            v1.POST("/users", createUser)
        }
        ```

    2. 미들웨어
        ```go
        // 글로벌 미들웨어
        r.Use(gin.Logger())
        r.Use(gin.Recovery())

        // 특정 라우트 미들웨어
        r.GET("/admin", authRequired(), adminHandler)
        ```

    3. 데이터 바인딩
        ```go
        type User struct {
            Name string `json:"name" binding:"required"`
            Age  int    `json:"age" binding:"required,gte=0"`
        }

        r.POST("/user", func(c *gin.Context) {
            var user User
            if err := c.ShouldBindJSON(&user); err != nil {
                c.JSON(400, gin.H{"error": err.Error()})
                return
            }
            // 처리 로직
        })
        ```

5. 설치 및 시작하기
    1. 요구사항
        - Go 1.18 이상
        - Go modules 활성화

    2. 설치 과정
        ```bash
        # 1. 새 프로젝트 디렉토리 생성
        mkdir my-gin-app
        cd my-gin-app

        # 2. Go 모듈 초기화
        go mod init my-gin-app

        # 3. Gin 설치
        go get -u github.com/gin-gonic/gin

        # 4. 의존성 정리
        go mod tidy
        ```

6. 개발 도구 통합
    1. IDE 설정 (VS Code)
        1. Go 확장 설치
        2. 코드 포맷팅 설정
        3. 디버깅 설정

        ```json
        // settings.json
        {
            "go.formatTool": "goimports",
            "go.lintTool": "golangci-lint",
            "editor.formatOnSave": true
        }
        ```

    2. 개발 서버 실행
        ```bash
        # 라이브 리로드 with air
        go install github.com/cosmtrek/air@latest
        air
        ```

7. 주의사항 및 모범 사례
    1. 주의사항
        1. 프로덕션 환경에서는 `gin.SetMode(gin.ReleaseMode)` 설정
        2. panic 방지를 위해 Recovery 미들웨어 사용
        3. 적절한 에러 처리 구현

    2. 모범 사례
        1. 구조화된 프로젝트 레이아웃 사용
        2. 환경 변수로 설정 관리
        3. 적절한 로깅 레벨 설정

## Gin 프로젝트 설정

1. 프로젝트 구조 설정
    * 표준 프로젝트 레이아웃
    ```plaintext
    myapp/
    ├── cmd/                    # main 애플리케이션
    │   └── server/
    │       └── main.go        # 진입점
    ├── internal/              # 비공개 애플리케이션 코드
    │   ├── auth/             # 인증 관련
    │   │   ├── middleware.go
    │   │   └── jwt.go
    │   ├── handlers/         # HTTP 핸들러
    │   │   ├── user.go
    │   │   └── product.go
    │   ├── models/          # 데이터 모델
    │   │   ├── user.go
    │   │   └── product.go
    │   └── repository/      # 데이터 접근 계층
    │       ├── user.go
    │       └── product.go
    ├── pkg/                  # 공개 라이브러리 코드
    │   ├── logger/
    │   └── utils/
    ├── configs/             # 설정 파일
    │   ├── config.yaml
    │   └── config.go
    ├── migrations/          # 데이터베이스 마이그레이션
    ├── scripts/            # 빌드/배포 스크립트
    ├── test/              # 추가 외부 테스트
    ├── .env               # 환경 변수
    ├── .gitignore
    ├── Dockerfile
    ├── docker-compose.yml
    ├── go.mod
    └── README.md
    ```

2. 기본 설정 파일
    1. main.go
        ```go
        package main

        import (
            "log"
            
            "github.com/gin-gonic/gin"
            "github.com/yourusername/myapp/internal/handlers"
            "github.com/yourusername/myapp/configs"
        )

        func main() {
            // 설정 로드
            config, err := configs.LoadConfig()
            if err != nil {
                log.Fatal("설정을 불러올 수 없습니다:", err)
            }

            // Gin 엔진 설정
            r := gin.Default()
            
            // 라우터 설정
            setupRoutes(r)
            
            // 서버 시작
            r.Run(config.Server.Address)
        }

        func setupRoutes(r *gin.Engine) {
            // 헬스 체크
            r.GET("/health", handlers.HealthCheck)
            
            // API 버전 그룹
            v1 := r.Group("/api/v1")
            {
                // 사용자 라우트
                v1.GET("/users", handlers.GetUsers)
                v1.POST("/users", handlers.CreateUser)
                
                // 제품 라우트
                v1.GET("/products", handlers.GetProducts)
                v1.POST("/products", handlers.CreateProduct)
            }
        }
        ```

    2. config.yaml
        ```yaml
        server:
            address: ":8080"
            mode: "debug"  # debug or release

        database:
            driver: "postgres"
            host: "localhost"
            port: 5432
            name: "myapp"
            user: "postgres"
            password: "secret"

        redis:
            address: "localhost:6379"
            password: ""
            db: 0

        jwt:
            secret: "your-secret-key"
            expiration: 24h
        ```

    3. configs/config.go
        ```go
        package configs

        import (
            "github.com/spf13/viper"
        )

        type Config struct {
            Server   ServerConfig
            Database DatabaseConfig
            Redis    RedisConfig
            JWT      JWTConfig
        }

        type ServerConfig struct {
            Address string
            Mode    string
        }

        type DatabaseConfig struct {
            Driver   string
            Host     string
            Port     int
            Name     string
            User     string
            Password string
        }

        type RedisConfig struct {
            Address  string
            Password string
            DB       int
        }

        type JWTConfig struct {
            Secret     string
            Expiration string
        }

        func LoadConfig() (*Config, error) {
            viper.SetConfigName("config")
            viper.SetConfigType("yaml")
            viper.AddConfigPath("./configs")
            
            // 환경 변수 오버라이드 설정
            viper.AutomaticEnv()
            
            if err := viper.ReadInConfig(); err != nil {
                return nil, err
            }
            
            var config Config
            if err := viper.Unmarshal(&config); err != nil {
                return nil, err
            }
            
            return &config, nil
        }
        ```

3. 데이터베이스 설정
    * internal/repository/db.go
        ```go
        package repository

        import (
            "fmt"
            "github.com/yourusername/myapp/configs"
            "gorm.io/gorm"
            "gorm.io/driver/postgres"
        )

        func NewDatabase(config *configs.DatabaseConfig) (*gorm.DB, error) {
            dsn := fmt.Sprintf("host=%s user=%s password=%s dbname=%s port=%d",
                config.Host,
                config.User,
                config.Password,
                config.Name,
                config.Port,
            )
            
            db, err := gorm.Open(postgres.Open(dsn), &gorm.Config{})
            if err != nil {
                return nil, err
            }
            
            return db, nil
        }
        ```

4. 미들웨어 설정
    * internal/auth/middleware.go
        ```go
        package auth

        import (
            "github.com/gin-gonic/gin"
        )

        func AuthMiddleware() gin.HandlerFunc {
            return func(c *gin.Context) {
                token := c.GetHeader("Authorization")
                if token == "" {
                    c.JSON(401, gin.H{"error": "인증이 필요합니다"})
                    c.Abort()
                    return
                }
                
                // JWT 토큰 검증
                claims, err := ValidateToken(token)
                if err != nil {
                    c.JSON(401, gin.H{"error": "유효하지 않은 토큰입니다"})
                    c.Abort()
                    return
                }
                
                // 사용자 정보를 컨텍스트에 저장
                c.Set("user", claims)
                c.Next()
            }
        }
        ```

5. 로깅 설정
    * pkg/logger/logger.go
        ```go
        package logger

        import (
            "go.uber.org/zap"
            "go.uber.org/zap/zapcore"
        )

        var log *zap.Logger

        func Init(environment string) {
            var config zap.Config
            
            if environment == "production" {
                config = zap.NewProductionConfig()
            } else {
                config = zap.NewDevelopmentConfig()
            }
            
            var err error
            log, err = config.Build()
            if err != nil {
                panic(err)
            }
        }

        func Info(msg string, fields ...zap.Field) {
            log.Info(msg, fields...)
        }

        func Error(msg string, fields ...zap.Field) {
            log.Error(msg, fields...)
        }
        ```

6. 개발 도구 설정
    1. .air.toml(라이브 리로드)
        ```toml
        root = "."
        tmp_dir = "tmp"

        [build]
        cmd = "go build -o ./tmp/main ./cmd/server"
        bin = "./tmp/main"
        delay = 1000
        exclude_dir = ["assets", "tmp", "vendor"]
        include_ext = ["go", "tpl", "tmpl", "html"]
        kill_delay = "0s"
        log = "build-errors.log"
        send_interrupt = false
        stop_on_error = true

        [color]
        app = ""
        build = "yellow"
        main = "magenta"
        runner = "green"
        watcher = "cyan"

        [log]
        time = false

        [misc]
        clean_on_exit = false
        ```

    2. .gitignore
        ```gitignore
        # 바이너리 파일
        /tmp
        *.exe
        *.exe~
        *.dll
        *.so
        *.dylib

        # 테스트 바이너리
        *.test

        # 커버리지 파일
        *.out

        # 의존성 디렉토리
        /vendor/

        # IDE 설정
        .idea/
        .vscode/

        # 환경 변수
        .env

        # 로그 파일
        *.log

        # 빌드 디렉토리
        /build/
        /bin/
        ```

7. 모듈 의존성 관리
    * go.mod
        ```go
        module github.com/yourusername/myapp

        go 1.19

        require (
            github.com/gin-gonic/gin v1.9.1
            github.com/spf13/viper v1.16.0
            github.com/golang-jwt/jwt/v5 v5.0.0
            go.uber.org/zap v1.24.0
            gorm.io/gorm v1.25.1
            gorm.io/driver/postgres v1.5.2
        )
        ```

8. Docker 설정
    1. Dockerfile
        ```dockerfile
        # 빌드 스테이지
        FROM golang:1.19-alpine AS builder

        WORKDIR /app

        # 의존성 다운로드
        COPY go.mod go.sum ./
        RUN go mod download

        # 소스 코드 복사 및 빌드
        COPY . .
        RUN CGO_ENABLED=0 GOOS=linux go build -o main ./cmd/server

        # 실행 스테이지
        FROM alpine:latest

        WORKDIR /app

        # 빌드된 바이너리 복사
        COPY --from=builder /app/main .
        COPY --from=builder /app/configs configs/

        # 환경 변수 설정
        ENV GIN_MODE=release

        EXPOSE 8080

        CMD ["./main"]
        ```

    2. docker-compose.yml
        ```yaml
        version: '3.8'

        services:
            app:
                build: .
                ports:
                - "8080:8080"
                depends_on:
                - db
                - redis
                environment:
                - DB_HOST=db
                - REDIS_HOST=redis
                volumes:
                - .:/app

            db:
                image: postgres:13
                environment:
                - POSTGRES_USER=postgres
                - POSTGRES_PASSWORD=secret
                - POSTGRES_DB=myapp
                volumes:
                - postgres_data:/var/lib/postgresql/data

            redis:
                image: redis:6
                volumes:
                - redis_data:/data

        volumes:
        postgres_data:
        redis_data:
        ```

9. 시작하기
    1. 프로젝트 실행
        ```bash
        # 개발 모드
        go run ./cmd/server

        # 또는 air로 실행 (라이브 리로드)
        air

        # Docker로 실행
        docker-compose up -d
        ```

    2. 테스트
        ```bash
        # 전체 테스트 실행
        go test ./...

        # 커버리지 리포트 생성
        go test -coverprofile=coverage.out ./...
        go tool cover -html=coverage.out
        ```