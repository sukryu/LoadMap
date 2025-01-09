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

## Gin 라우팅 시스템

1. 기본 라우팅
    * HTTP 메서드 라우팅
        ```go
        func main() {
            r := gin.Default()

            // 기본 HTTP 메서드
            r.GET("/users", getUsers)
            r.POST("/users", createUser)
            r.PUT("/users/:id", updateUser)
            r.DELETE("/users/:id", deleteUser)
            
            // 추가 HTTP 메서드
            r.HEAD("/users", getUsersHead)
            r.OPTIONS("/users", getUsersOptions)
            r.PATCH("/users/:id", partialUpdateUser)
            
            // 모든 HTTP 메서드 처리
            r.Any("/ping", func(c *gin.Context) {
                c.String(200, "pong")
            })

            r.Run(":8080")
        }

        func getUsers(c *gin.Context) {
            c.JSON(200, gin.H{
                "message": "Get users",
            })
        }

        func createUser(c *gin.Context) {
            var user User
            if err := c.ShouldBindJSON(&user); err != nil {
                c.JSON(400, gin.H{"error": err.Error()})
                return
            }
            c.JSON(201, user)
        }
        ```

2. URL 파라미터
    1. 경로 파라미터
        ```go
        // Single parameter
        r.GET("/users/:id", func(c *gin.Context) {
            id := c.Param("id")
            c.JSON(200, gin.H{"id": id})
        })

        // Multiple parameters
        r.GET("/users/:userID/posts/:postID", func(c *gin.Context) {
            userID := c.Param("userID")
            postID := c.Param("postID")
            c.JSON(200, gin.H{
                "userID": userID,
                "postID": postID,
            })
        })

        // Wildcard parameter
        r.GET("/files/*filepath", func(c *gin.Context) {
            filepath := c.Param("filepath") // /files/images/avatar.jpg -> /images/avatar.jpg
            c.JSON(200, gin.H{"filepath": filepath})
        })
        ```

    2. 쿼리 파라미터
        ```go
        r.GET("/search", func(c *gin.Context) {
            // 필수 쿼리 파라미터
            query := c.Query("q")
            
            // 선택적 쿼리 파라미터 (기본값 지정)
            page := c.DefaultQuery("page", "1")
            limit := c.DefaultQuery("limit", "10")
            
            // 쿼리 파라미터 존재 여부 확인
            if sort, exists := c.GetQuery("sort"); exists {
                // sort 파라미터가 있는 경우
                c.JSON(200, gin.H{
                    "query": query,
                    "page": page,
                    "limit": limit,
                    "sort": sort,
                })
            } else {
                c.JSON(200, gin.H{
                    "query": query,
                    "page": page,
                    "limit": limit,
                })
            }
        })
        ```

3. 라우트 그룹핑
    1. 기본 그룹핑
        ```go
        func setupRouter() *gin.Engine {
            r := gin.Default()

            // API v1 그룹
            v1 := r.Group("/api/v1")
            {
                v1.GET("/users", getAllUsers)
                v1.POST("/users", createUser)
                
                // 중첩 그룹
                auth := v1.Group("/auth")
                {
                    auth.POST("/login", login)
                    auth.POST("/register", register)
                }
            }

            // API v2 그룹
            v2 := r.Group("/api/v2")
            {
                v2.GET("/users", getAllUsersV2)
                v2.POST("/users", createUserV2)
            }

            return r
        }
        ```

    2. 미들웨어와 함께 사용
        ```go
        func setupAuthenticatedRoutes(r *gin.Engine) {
            // 인증이 필요한 그룹
            authorized := r.Group("/admin")
            authorized.Use(AuthRequired())
            {
                authorized.GET("/users", adminGetUsers)
                authorized.POST("/users", adminCreateUser)
                
                // 추가 권한이 필요한 서브그룹
                superAdmin := authorized.Group("/super")
                superAdmin.Use(SuperAdminRequired())
                {
                    superAdmin.GET("/stats", getAdminStats)
                    superAdmin.POST("/settings", updateSettings)
                }
            }
        }

        func AuthRequired() gin.HandlerFunc {
            return func(c *gin.Context) {
                token := c.GetHeader("Authorization")
                if token == "" {
                    c.AbortWithStatusJSON(401, gin.H{"error": "Unauthorized"})
                    return
                }
                // 토큰 검증 로직...
                c.Next()
            }
        }
        ```

4. 고급 라우팅 기능
    1. 커스텀 HTTP 메서드
        ```go
        func customHTTPMethod() {
            r := gin.Default()
            
            r.Handle("PROPFIND", "/files", func(c *gin.Context) {
                c.JSON(200, gin.H{
                    "method": "PROPFIND",
                    "status": "success",
                })
            })
        }
        ```

    2. 다중 핸들러
        ```go
        func logging() gin.HandlerFunc {
            return func(c *gin.Context) {
                t := time.Now()
                c.Next()
                latency := time.Since(t)
                log.Printf("Latency: %v", latency)
            }
        }

        func authenticate() gin.HandlerFunc {
            return func(c *gin.Context) {
                // 인증 로직
                c.Next()
            }
        }

        // 다중 핸들러 등록
        r.GET("/protected",
            logging(),
            authenticate(),
            func(c *gin.Context) {
                c.JSON(200, gin.H{"message": "success"})
            },
        )
        ```

5. 라우터 확장
    1. 커스텀 라우터
        ```go
        type CustomRouter struct {
            *gin.Engine
            routes map[string][]string
        }

        func NewCustomRouter() *CustomRouter {
            return &CustomRouter{
                Engine: gin.Default(),
                routes: make(map[string][]string),
            }
        }

        func (r *CustomRouter) RegisterRoute(method, path string) {
            if _, exists := r.routes[method]; !exists {
                r.routes[method] = make([]string, 0)
            }
            r.routes[method] = append(r.routes[method], path)
        }

        // 라우트 목록 출력
        func (r *CustomRouter) PrintRoutes() {
            for method, paths := range r.routes {
                for _, path := range paths {
                    log.Printf("%s %s", method, path)
                }
            }
        }
        ```

    2. NoRoute 핸들러
        ```go
        r.NoRoute(func(c *gin.Context) {
            c.JSON(404, gin.H{
                "code": "PAGE_NOT_FOUND",
                "message": "Page not found",
            })
        })
        ```

6. 라우트 유효성 검사
    1. 파라미터 검증
        ```go
        func validateID() gin.HandlerFunc {
            return func(c *gin.Context) {
                id := c.Param("id")
                if _, err := strconv.Atoi(id); err != nil {
                    c.AbortWithStatusJSON(400, gin.H{
                        "error": "Invalid ID format",
                    })
                    return
                }
                c.Next()
            }
        }

        r.GET("/users/:id", validateID(), getUser)
        ```

    2. 요청 바디 검증
        ```go
        type CreateUserRequest struct {
            Username string `json:"username" binding:"required,min=3,max=30"`
            Email    string `json:"email" binding:"required,email"`
            Age      int    `json:"age" binding:"required,gte=0,lte=150"`
        }

        func createUser(c *gin.Context) {
            var req CreateUserRequest
            if err := c.ShouldBindJSON(&req); err != nil {
                c.JSON(400, gin.H{"error": err.Error()})
                return
            }
            
            // 추가 커스텀 검증
            if !isValidUsername(req.Username) {
                c.JSON(400, gin.H{"error": "Invalid username format"})
                return
            }
            
            // 처리 로직...
        }
        ```

7. 성능 최적화
    1. 라우터 캐싱
        ```go
        type RouterCache struct {
            cache    map[string]gin.HandlerFunc
            mutex    sync.RWMutex
            lifetime time.Duration
        }

        func NewRouterCache(lifetime time.Duration) *RouterCache {
            return &RouterCache{
                cache:    make(map[string]gin.HandlerFunc),
                lifetime: lifetime,
            }
        }

        func (rc *RouterCache) Get(key string) (gin.HandlerFunc, bool) {
            rc.mutex.RLock()
            defer rc.mutex.RUnlock()
            handler, exists := rc.cache[key]
            return handler, exists
        }

        func (rc *RouterCache) Set(key string, handler gin.HandlerFunc) {
            rc.mutex.Lock()
            defer rc.mutex.Unlock()
            rc.cache[key] = handler
            
            // 캐시 만료 설정
            time.AfterFunc(rc.lifetime, func() {
                rc.mutex.Lock()
                delete(rc.cache, key)
                rc.mutex.Unlock()
            })
        }
        ```

    2. 라우트 프로파일링
        ```go
        func routeProfiler() gin.HandlerFunc {
            return func(c *gin.Context) {
                start := time.Now()
                path := c.Request.URL.Path
                
                c.Next()
                
                latency := time.Since(start)
                status := c.Writer.Status()
                
                log.Printf("[PROFILE] %s %s %d %v", 
                    c.Request.Method, 
                    path, 
                    status, 
                    latency,
                )
            }
        }
        ```

8. 모범 사례
    1. 라우트 조직화
        ```go
        // routes/routes.go
        func SetupRoutes(r *gin.Engine) {
            // 공통 미들웨어
            r.Use(gin.Logger())
            r.Use(gin.Recovery())
            
            // API 그룹
            api := r.Group("/api")
            {
                // 버전별 라우트
                setupV1Routes(api.Group("/v1"))
                setupV2Routes(api.Group("/v2"))
            }
            
            // 웹 라우트
            setupWebRoutes(r.Group(""))
            
            // Admin 라우트
            setupAdminRoutes(r.Group("/admin"))
        }

        // routes/v1.go
        func setupV1Routes(r *gin.RouterGroup) {
            // User 관련 라우트
            users := r.Group("/users")
            {
                users.GET("", handlers.GetUsers)
                users.POST("", handlers.CreateUser)
                users.GET("/:id", handlers.GetUser)
                users.PUT("/:id", handlers.UpdateUser)
                users.DELETE("/:id", handlers.DeleteUser)
            }
            
            // Product 관련 라우트
            products := r.Group("/products")
            {
                products.GET("", handlers.GetProducts)
                // ...
            }
        }
        ```
    
    2. 에러처리
        ```go
        func errorHandler(c *gin.Context, err error) {
            switch e := err.(type) {
            case *customErrors.ValidationError:
                c.JSON(400, gin.H{
                    "error": e.Error(),
                    "fields": e.Fields,
                })
            case *customErrors.AuthError:
                c.JSON(401, gin.H{"error": e.Error()})
            default:
                c.JSON(500, gin.H{"error": "Internal Server Error"})
            }
        }
        ```

## 미들웨어 아키텍처

1. 미들웨어 기본 구조
    1. 기본 미들웨어 템플릿
        ```go
        func BasicMiddleware() gin.HandlerFunc {
            // 미들웨어 초기화
            return func(c *gin.Context) {
                // 요청 처리 전
                beforeRequest(c)

                // 다음 핸들러 호출
                c.Next()

                // 요청 처리 후
                afterRequest(c)
            }
        }

        func beforeRequest(c *gin.Context) {
            // 전처리 로직
            startTime := time.Now()
            c.Set("startTime", startTime)
        }

        func afterRequest(c *gin.Context) {
            // 후처리 로직
            startTime, _ := c.Get("startTime")
            endTime := time.Now()
            latency := endTime.Sub(startTime.(time.Time))
            log.Printf("Latency: %v", latency)
        }
        ```

    2. 미들웨어 적용 방법
        ```go
        func main() {
            r := gin.New() // 미들웨어가 없는 엔진

            // 글로벌 미들웨어
            r.Use(gin.Logger())
            r.Use(gin.Recovery())
            r.Use(BasicMiddleware())

            // 그룹 미들웨어
            authorized := r.Group("/admin")
            authorized.Use(AuthMiddleware())

            // 특정 라우트 미들웨어
            r.GET("/special", SpecialMiddleware(), handleSpecial)
        }
        ```

2. 인증 미들웨어
    1. JWT 인증
        ```go
        func JWTMiddleware() gin.HandlerFunc {
            return func(c *gin.Context) {
                token := c.GetHeader("Authorization")
                if token == "" {
                    c.AbortWithStatusJSON(401, gin.H{
                        "error": "No token provided",
                    })
                    return
                }

                // Bearer 토큰 처리
                tokenString := strings.Replace(token, "Bearer ", "", 1)
                
                // JWT 검증
                claims, err := validateToken(tokenString)
                if err != nil {
                    c.AbortWithStatusJSON(401, gin.H{
                        "error": "Invalid token",
                    })
                    return
                }

                // 사용자 정보를 컨텍스트에 저장
                c.Set("userID", claims.UserID)
                c.Set("userRole", claims.Role)

                c.Next()
            }
        }

        func validateToken(tokenString string) (*Claims, error) {
            claims := &Claims{}
            token, err := jwt.ParseWithClaims(
                tokenString,
                claims,
                func(token *jwt.Token) (interface{}, error) {
                    return []byte(os.Getenv("JWT_SECRET")), nil
                },
            )

            if err != nil || !token.Valid {
                return nil, err
            }

            return claims, nil
        }
        ```

    2. RBAC(Role-Based Access Control)
        ```go
        func RBACMiddleware(requiredRole string) gin.HandlerFunc {
            return func(c *gin.Context) {
                userRole, exists := c.Get("userRole")
                if !exists {
                    c.AbortWithStatusJSON(401, gin.H{
                        "error": "No role information",
                    })
                    return
                }

                if !hasPermission(userRole.(string), requiredRole) {
                    c.AbortWithStatusJSON(403, gin.H{
                        "error": "Insufficient permissions",
                    })
                    return
                }

                c.Next()
            }
        }

        func hasPermission(userRole, requiredRole string) bool {
            roleHierarchy := map[string]int{
                "admin":    3,
                "manager": 2,
                "user":    1,
            }

            return roleHierarchy[userRole] >= roleHierarchy[requiredRole]
        }
        ```

3. 로깅 미들웨어
    1. 구조화된 로깅
        ```go
        func StructuredLogger() gin.HandlerFunc {
            return func(c *gin.Context) {
                start := time.Now()
                path := c.Request.URL.Path
                raw := c.Request.URL.RawQuery

                // 요청 처리
                c.Next()

                // 로그 필드 준비
                param := gin.LogFormatterParams{
                    Request: c.Request,
                    Keys:    c.Keys,
                    TimeStamp: time.Now(),
                    Latency: time.Since(start),
                    ClientIP: c.ClientIP(),
                    Method: c.Request.Method,
                    StatusCode: c.Writer.Status(),
                    Path: path,
                    ErrorMessage: c.Errors.ByType(gin.ErrorTypePrivate).String(),
                }

                if raw != "" {
                    path = path + "?" + raw
                }

                // JSON 형식으로 로그 출력
                log.Printf(`{
                    "timestamp": "%s",
                    "latency": "%s",
                    "clientIP": "%s",
                    "method": "%s",
                    "path": "%s",
                    "statusCode": %d,
                    "error": "%s"
                }`,
                    param.TimeStamp.Format(time.RFC3339),
                    param.Latency,
                    param.ClientIP,
                    param.Method,
                    path,
                    param.StatusCode,
                    param.ErrorMessage,
                )
            }
        }
        ```

4. CORS 미들웨어
    1. CORS 설정
        ```go
        func CORSMiddleware() gin.HandlerFunc {
            return func(c *gin.Context) {
                c.Writer.Header().Set("Access-Control-Allow-Origin", "*")
                c.Writer.Header().Set("Access-Control-Allow-Credentials", "true")
                c.Writer.Header().Set("Access-Control-Allow-Headers", "Content-Type, Content-Length, Accept-Encoding, X-CSRF-Token, Authorization, accept, origin, Cache-Control, X-Requested-With")
                c.Writer.Header().Set("Access-Control-Allow-Methods", "POST, OPTIONS, GET, PUT, DELETE")

                if c.Request.Method == "OPTIONS" {
                    c.AbortWithStatus(204)
                    return
                }

                c.Next()
            }
        }

        // 커스텀 CORS 설정
        func CustomCORS(allowedOrigins []string) gin.HandlerFunc {
            return func(c *gin.Context) {
                origin := c.Request.Header.Get("Origin")
                
                // 허용된 오리진 확인
                for _, allowedOrigin := range allowedOrigins {
                    if origin == allowedOrigin {
                        c.Writer.Header().Set("Access-Control-Allow-Origin", origin)
                        break
                    }
                }
                
                // 나머지 CORS 설정...
                c.Next()
            }
        }
        ```

5. 캐시 미들웨어
    1. 응답 캐싱
        ```go
        func CacheMiddleware(duration time.Duration) gin.HandlerFunc {
            cache := make(map[string]cacheEntry)
            mutex := &sync.RWMutex{}

            type cacheEntry struct {
                data       interface{}
                expiration time.Time
            }

            return func(c *gin.Context) {
                key := c.Request.URL.String()
                
                // 캐시 확인
                mutex.RLock()
                if entry, exists := cache[key]; exists && time.Now().Before(entry.expiration) {
                    mutex.RUnlock()
                    c.JSON(200, entry.data)
                    c.Abort()
                    return
                }
                mutex.RUnlock()

                // 응답 캡처를 위한 writer 래핑
                writer := &responseWriter{ResponseWriter: c.Writer}
                c.Writer = writer

                c.Next()

                // 캐시 저장
                if c.Writer.Status() == 200 {
                    mutex.Lock()
                    cache[key] = cacheEntry{
                        data:       writer.body,
                        expiration: time.Now().Add(duration),
                    }
                    mutex.Unlock()
                }
            }
        }

        type responseWriter struct {
            gin.ResponseWriter
            body interface{}
        }

        func (w *responseWriter) Write(b []byte) (int, error) {
            var data interface{}
            json.Unmarshal(b, &data)
            w.body = data
            return w.ResponseWriter.Write(b)
        }
        ```

6. 레이트 리미트 미들웨어
    1. 토큰 버킷 알고리즘
        ```go
        func RateLimiter(rate int, burst int) gin.HandlerFunc {
            limiter := rate.NewLimiter(rate.Limit(rate), burst)
            
            return func(c *gin.Context) {
                if !limiter.Allow() {
                    c.AbortWithStatusJSON(429, gin.H{
                        "error": "Too many requests",
                    })
                    return
                }
                c.Next()
            }
        }

        // IP 기반 레이트 리미팅
        func IPRateLimiter(rate int, burst int) gin.HandlerFunc {
            limiters := make(map[string]*rate.Limiter)
            mutex := &sync.RWMutex{}

            return func(c *gin.Context) {
                ip := c.ClientIP()
                
                mutex.Lock()
                limiter, exists := limiters[ip]
                if !exists {
                    limiter = rate.NewLimiter(rate.Limit(rate), burst)
                    limiters[ip] = limiter
                }
                mutex.Unlock()

                if !limiter.Allow() {
                    c.AbortWithStatusJSON(429, gin.H{
                        "error": "Too many requests",
                    })
                    return
                }
                
                c.Next()
            }
        }
        ```

7. 복구 및 에러 처리 미들웨어
    1. 패닉 복구
        ```go
        func RecoveryMiddleware() gin.HandlerFunc {
            return func(c *gin.Context) {
                defer func() {
                    if err := recover(); err != nil {
                        // 스택 트레이스 수집
                        stack := debug.Stack()
                        
                        // 에러 로깅
                        log.Printf("panic recovered: %v\n%s", err, stack)
                        
                        // 클라이언트에 응답
                        c.AbortWithStatusJSON(500, gin.H{
                            "error": "Internal Server Error",
                        })
                    }
                }()
                
                c.Next()
            }
        }
        ```

    2. 에러 핸들링
        ```go
        func ErrorHandler() gin.HandlerFunc {
            return func(c *gin.Context) {
                c.Next()

                // 에러 수집
                if len(c.Errors) > 0 {
                    for _, err := range c.Errors {
                        switch e := err.Err.(type) {
                        case *customErrors.ValidationError:
                            c.JSON(400, gin.H{
                                "error": e.Error(),
                                "details": e.Details,
                            })
                        case *customErrors.AuthError:
                            c.JSON(401, gin.H{
                                "error": e.Error(),
                            })
                        default:
                            c.JSON(500, gin.H{
                                "error": "Internal Server Error",
                            })
                        }
                    }
                }
            }
        }
        ```

8. 모니터링 미들웨어
    1. 프로메테우스 메트릭
        ```go
        func PrometheusMiddleware() gin.HandlerFunc {
            httpRequestsTotal := prometheus.NewCounterVec(
                prometheus.CounterOpts{
                    Name: "http_requests_total",
                    Help: "Total number of HTTP requests",
                },
                []string{"method", "path", "status"},
            )
            
            httpRequestDuration := prometheus.NewHistogramVec(
                prometheus.HistogramOpts{
                    Name: "http_request_duration_seconds",
                    Help: "HTTP request duration in seconds",
                },
                []string{"method", "path"},
            )

            prometheus.MustRegister(httpRequestsTotal)
            prometheus.MustRegister(httpRequestDuration)

            return func(c *gin.Context) {
                start := time.Now()

                c.Next()

                duration := time.Since(start).Seconds()
                
                httpRequestsTotal.WithLabelValues(
                    c.Request.Method,
                    c.Request.URL.Path,
                    strconv.Itoa(c.Writer.Status()),
                ).Inc()

                httpRequestDuration.WithLabelValues(
                    c.Request.Method,
                    c.Request.URL.Path,
                ).Observe(duration)
            }
        }
        ```

9. Best Practices
    1. 미들웨어 체인 구성
        ```go
        func SetupMiddlewares(r *gin.Engine) {
            // 전역 미들웨어
            r.Use(
                RecoveryMiddleware(),
                StructuredLogger(),
                CORSMiddleware(),
            )

            // API 그룹
            api := r.Group("/api")
            api.Use(
                RateLimiter(100, 10),
                PrometheusMiddleware(),
            )

            // 인증된 라우트
            authorized := api.Group("/")
            authorized.Use(
                JWTMiddleware(),
                RBACMiddleware("user"),
            )
        }
        ```

    2. 미들웨어 순서 최적화
        ```go
        func OptimizeMiddlewareOrder(r *gin.Engine) {
            // 1. 복구 (가장 먼저)
            r.Use(RecoveryMiddleware())
            
            // 2. 로깅
            r.Use(StructuredLogger())
            
            // 3. 보안
            r.Use(
                CORSMiddleware(),
                SecurityHeaders(),
            )
            
            // 4. 성능
            r.Use(
                GzipMiddleware(),
                CacheMiddleware(5 * time.Minute),
            )
            
            // 5. 인증/인가 (라우트별로 적용)
            auth := r.Group("/auth")
            auth.Use(
                JWTMiddleware(),
                RBACMiddleware("user"),
            )
            
            // 6. 비즈니스 로직 미들웨어
            auth.Use(
                ValidationMiddleware(),
                TransactionMiddleware(),
            )
        }
        ```

## 데이터 처리

1. 요청 바인딩
    1. JSON 바인딩
        ```go
        type User struct {
            ID        uint      `json:"id"`
            Username  string    `json:"username" binding:"required,min=3,max=30"`
            Email     string    `json:"email" binding:"required,email"`
            Age       int       `json:"age" binding:"required,gte=0,lte=130"`
            CreatedAt time.Time `json:"created_at"`
        }

        func createUser(c *gin.Context) {
            var user User
            if err := c.ShouldBindJSON(&user); err != nil {
                c.JSON(400, gin.H{
                    "error": err.Error(),
                })
                return
            }

            // 데이터베이스 저장 로직...
            c.JSON(201, user)
        }
        ```

    2. Form 데이터 바인딩
        ```go
        type LoginForm struct {
            Username string `form:"username" binding:"required"`
            Password string `form:"password" binding:"required"`
            Remember bool   `form:"remember"`
        }

        func login(c *gin.Context) {
            var form LoginForm
            if err := c.ShouldBind(&form); err != nil {
                c.JSON(400, gin.H{"error": err.Error()})
                return
            }
            
            // 로그인 처리...
        }
        ```

    3. Query 파라미터 바인딩
        ```go
        type SearchParams struct {
            Query  string `form:"q" binding:"required"`
            Page   int    `form:"page,default=1" binding:"gte=1"`
            Limit  int    `form:"limit,default=10" binding:"gte=1,lte=100"`
            Sort   string `form:"sort" binding:"oneof=asc desc"`
        }

        func search(c *gin.Context) {
            var params SearchParams
            if err := c.ShouldBindQuery(&params); err != nil {
                c.JSON(400, gin.H{"error": err.Error()})
                return
            }
            
            // 검색 로직...
        }
        ```

2. 파일 업로드
    1. 단일 파일 업로드
        ```go
        func uploadFile(c *gin.Context) {
            file, err := c.FormFile("file")
            if err != nil {
                c.JSON(400, gin.H{"error": "No file uploaded"})
                return
            }

            // 파일 확장자 검증
            if !isAllowedFileType(file.Filename) {
                c.JSON(400, gin.H{"error": "Invalid file type"})
                return
            }

            // 파일 크기 검증
            if file.Size > 10<<20 { // 10MB
                c.JSON(400, gin.H{"error": "File too large"})
                return
            }

            // 저장할 경로 생성
            dst := filepath.Join("uploads", file.Filename)
            if err := c.SaveUploadedFile(file, dst); err != nil {
                c.JSON(500, gin.H{"error": "Failed to save file"})
                return
            }

            c.JSON(200, gin.H{
                "message": "File uploaded successfully",
                "filename": file.Filename,
            })
        }

        func isAllowedFileType(filename string) bool {
            allowedTypes := map[string]bool{
                ".jpg":  true,
                ".jpeg": true,
                ".png":  true,
                ".pdf":  true,
            }
            ext := strings.ToLower(filepath.Ext(filename))
            return allowedTypes[ext]
        }
        ```

    2. 다중 파일 업로드
        ```go
        func uploadMultipleFiles(c *gin.Context) {
            form, err := c.MultipartForm()
            if err != nil {
                c.JSON(400, gin.H{"error": err.Error()})
                return
            }

            files := form.File["files"]
            results := make([]UploadResult, 0)

            for _, file := range files {
                result := UploadResult{
                    Filename: file.Filename,
                    Size:    file.Size,
                }

                if err := c.SaveUploadedFile(file, "uploads/"+file.Filename); err != nil {
                    result.Error = err.Error()
                } else {
                    result.Success = true
                }

                results = append(results, result)
            }

            c.JSON(200, gin.H{
                "message": "Files processed",
                "results": results,
            })
        }

        type UploadResult struct {
            Filename string `json:"filename"`
            Size     int64  `json:"size"`
            Success  bool   `json:"success"`
            Error    string `json:"error,omitempty"`
        }
        ```

3. 데이터 검증
    1. 커스텀 검증기
        ```go
        type Registration struct {
            Username string `json:"username" binding:"required,username"`
            Password string `json:"password" binding:"required,min=8,password"`
        }

        func setupValidators() {
            if v, ok := binding.Validator.Engine().(*validator.Validate); ok {
                // 사용자명 검증
                v.RegisterValidation("username", func(fl validator.FieldLevel) bool {
                    username := fl.Field().String()
                    // 영문자, 숫자, 언더스코어만 허용
                    match, _ := regexp.MatchString("^[a-zA-Z0-9_]+$", username)
                    return match
                })

                // 비밀번호 검증
                v.RegisterValidation("password", func(fl validator.FieldLevel) bool {
                    password := fl.Field().String()
                    // 최소 8자, 대문자, 소문자, 숫자, 특수문자 포함
                    hasUpper := regexp.MustCompile(`[A-Z]`).MatchString(password)
                    hasLower := regexp.MustCompile(`[a-z]`).MatchString(password)
                    hasNumber := regexp.MustCompile(`[0-9]`).MatchString(password)
                    hasSpecial := regexp.MustCompile(`[!@#$%^&*]`).MatchString(password)
                    return hasUpper && hasLower && hasNumber && hasSpecial
                })
            }
        }
        ```

    2. 구조체 레벨 검증
        ```go
        type TimeRange struct {
            StartTime time.Time `json:"start_time" binding:"required"`
            EndTime   time.Time `json:"end_time" binding:"required,gtfield=StartTime"`
        }

        func (tr TimeRange) Validate() error {
            if tr.EndTime.Sub(tr.StartTime) > 24*time.Hour {
                return errors.New("time range cannot exceed 24 hours")
            }
            return nil
        }
        ```

4. 응답 포맷팅
    1. JSON 응답
        ```go
        type TimeRange struct {
            StartTime time.Time `json:"start_time" binding:"required"`
            EndTime   time.Time `json:"end_time" binding:"required,gtfield=StartTime"`
        }

        func (tr TimeRange) Validate() error {
            if tr.EndTime.Sub(tr.StartTime) > 24*time.Hour {
                return errors.New("time range cannot exceed 24 hours")
            }
            return nil
        }
        ```

    2. XML 응답
        ```go
        type XMLResponse struct {
            XMLName xml.Name    `xml:"response"`
            Success bool        `xml:"success"`
            Data    interface{} `xml:"data,omitempty"`
            Error   string      `xml:"error,omitempty"`
        }

        func SendXMLResponse(c *gin.Context, success bool, data interface{}, err string) {
            response := XMLResponse{
                Success: success,
                Data:    data,
                Error:   err,
            }
            c.XML(200, response)
        }
        ```

    3. 페이지네이션 응답
        ```go
        type PaginatedResponse struct {
            Items      interface{} `json:"items"`
            Total      int64      `json:"total"`
            Page       int        `json:"page"`
            PerPage    int        `json:"per_page"`
            TotalPages int        `json:"total_pages"`
            HasMore    bool       `json:"has_more"`
        }

        func SendPaginatedResponse(c *gin.Context, items interface{}, total int64, page, perPage int) {
            totalPages := int(math.Ceil(float64(total) / float64(perPage)))
            hasMore := page < totalPages

            response := PaginatedResponse{
                Items:      items,
                Total:      total,
                Page:       page,
                PerPage:    perPage,
                TotalPages: totalPages,
                HasMore:    hasMore,
            }

            c.JSON(200, response)
        }
        ```

5. 에러 처리
    1. 에러 타입 정의
        ```go
        type AppError struct {
            Type    string `json:"type"`
            Message string `json:"message"`
            Details string `json:"details,omitempty"`
        }

        func (e *AppError) Error() string {
            return e.Message
        }

        var (
            ErrNotFound     = &AppError{Type: "NOT_FOUND", Message: "Resource not found"}
            ErrUnauthorized = &AppError{Type: "UNAUTHORIZED", Message: "Unauthorized access"}
            ErrValidation   = &AppError{Type: "VALIDATION", Message: "Validation failed"}
        )
        ```

    2. 에러 핸들러
        ```go
        func ErrorHandler(c *gin.Context, err error) {
            switch e := err.(type) {
            case *AppError:
                c.JSON(getStatusCode(e.Type), e)
            case validator.ValidationErrors:
                errors := processValidationErrors(e)
                c.JSON(400, gin.H{
                    "type":    "VALIDATION",
                    "message": "Validation failed",
                    "errors":  errors,
                })
            default:
                c.JSON(500, gin.H{
                    "type":    "INTERNAL_ERROR",
                    "message": "Internal server error",
                })
            }
        }

        func getStatusCode(errorType string) int {
            switch errorType {
            case "NOT_FOUND":
                return 404
            case "UNAUTHORIZED":
                return 401
            case "VALIDATION":
                return 400
            default:
                return 500
            }
        }

        func processValidationErrors(err validator.ValidationErrors) []map[string]string {
            var errors []map[string]string
            for _, e := range err {
                errors = append(errors, map[string]string{
                    "field":   e.Field(),
                    "message": getValidationMessage(e),
                })
            }
            return errors
        }
        ```

6. 데이터 변환
    1. DTO 변환
        ```go
        type UserDTO struct {
            ID        uint      `json:"id"`
            Username  string    `json:"username"`
            Email     string    `json:"email"`
            CreatedAt time.Time `json:"created_at"`
        }

        func (u *User) ToDTO() UserDTO {
            return UserDTO{
                ID:        u.ID,
                Username:  u.Username,
                Email:     u.Email,
                CreatedAt: u.CreatedAt,
            }
        }

        func ToUserDTOs(users []User) []UserDTO {
            dtos := make([]UserDTO, len(users))
            for i, user := range users {
                dtos[i] = user.ToDTO()
            }
            return dtos
        }
        ```

    2. 데이터 마스킹
        ```go
        func maskEmail(email string) string {
            parts := strings.Split(email, "@")
            if len(parts) != 2 {
                return email
            }

            username := parts[0]
            domain := parts[1]

            if len(username) <= 3 {
                return username[:1] + strings.Repeat("*", len(username)-1) + "@" + domain
            }

            return username[:2] + strings.Repeat("*", len(username)-3) + 
                username[len(username)-1:] + "@" + domain
        }

        func (u *UserDTO) MaskSensitiveData() {
            u.Email = maskEmail(u.Email)
        }
        ```

7. 데이터 캐싱
    1. 인메모리 캐시
        ```go
        type Cache struct {
            data  map[string]cacheItem
            mutex sync.RWMutex
        }

        type cacheItem struct {
            value      interface{}
            expiration time.Time
        }

        func NewCache() *Cache {
            cache := &Cache{
                data: make(map[string]cacheItem),
            }
            go cache.cleanup()
            return cache
        }

        func (c *Cache) Set(key string, value interface{}, duration time.Duration) {
            c.mutex.Lock()
            defer c.mutex.Unlock()

            c.data[key] = cacheItem{
                value:      value,
                expiration: time.Now().Add(duration),
            }
        }

        func (c *Cache) Get(key string) (interface{}, bool) {
            c.mutex.RLock()
            defer c.mutex.RUnlock()

            item, exists := c.data[key]
            if !exists {
                return nil, false
            }

            if time.Now().After(item.expiration) {
                delete(c.data, key)
                return nil, false
            }

            return item.value, true
        }

        func (c *Cache) cleanup() {
            ticker := time.NewTicker(time.Minute)
            for range ticker.C {
                c.mutex.Lock()
                for key, item := range c.data {
                    if time.Now().After(item.expiration) {
                        delete(c.data, key)
                    }
                }
                c.mutex.Unlock()
            }
        }
        ```

8. Best Practices
    1. 데이터 검증 체크리스트
        1. 입력 데이터 타입 확인
        2. 필수 필드 검증
        3. 데이터 형식 검증(이메일, 전화번호 등)
        4. 데이터 길이/범위 검증
        5. 비즈니스 규칙 검증
        6. XSS, SQL 인젝션 방지

    2. 성능 최적화 팁
        1. 적절한 인덱싱
        2. 캐싱 전략 수립
        3. 배치 처리 활용
        4. 데이터 페이지네이션

## GORM 통합

1. GORM 설정
    1. 기본 설정
        ```go
        // configs/database.go
        package configs

        import (
            "fmt"
            "log"
            "os"
            "time"

            "gorm.io/driver/postgres"
            "gorm.io/gorm"
            "gorm.io/gorm/logger"
        )

        func SetupDatabase() (*gorm.DB, error) {
            dsn := fmt.Sprintf(
                "host=%s user=%s password=%s dbname=%s port=%s sslmode=disable TimeZone=Asia/Seoul",
                os.Getenv("DB_HOST"),
                os.Getenv("DB_USER"),
                os.Getenv("DB_PASSWORD"),
                os.Getenv("DB_NAME"),
                os.Getenv("DB_PORT"),
            )

            // GORM 로거 설정
            gormLogger := logger.New(
                log.New(os.Stdout, "\r\n", log.LstdFlags),
                logger.Config{
                    SlowThreshold:             time.Second,
                    LogLevel:                  logger.Info,
                    IgnoreRecordNotFoundError: true,
                    Colorful:                  true,
                },
            )

            // 데이터베이스 연결
            db, err := gorm.Open(postgres.Open(dsn), &gorm.Config{
                Logger: gormLogger,
                NowFunc: func() time.Time {
                    return time.Now().UTC()
                },
            })
            if err != nil {
                return nil, err
            }

            // 커넥션 풀 설정
            sqlDB, err := db.DB()
            if err != nil {
                return nil, err
            }

            sqlDB.SetMaxIdleConns(10)
            sqlDB.SetMaxOpenConns(100)
            sqlDB.SetConnMaxLifetime(time.Hour)

            return db, nil
        }
        ```

    2. 모델 정의
        ```go
        // internal/models/user.go
        package models

        import (
            "time"
            "gorm.io/gorm"
        )

        type User struct {
            ID        uint           `gorm:"primarykey"`
            Username  string         `gorm:"type:varchar(100);unique;not null"`
            Email     string         `gorm:"type:varchar(100);unique;not null"`
            Password  string         `gorm:"type:varchar(255);not null"`
            Role      string         `gorm:"type:varchar(20);default:'user'"`
            Active    bool           `gorm:"default:true"`
            CreatedAt time.Time
            UpdatedAt time.Time
            DeletedAt gorm.DeletedAt `gorm:"index"`
        }

        // 비밀번호 해싱 훅
        func (u *User) BeforeCreate(tx *gorm.DB) error {
            hashedPassword, err := bcrypt.GenerateFromPassword([]byte(u.Password), bcrypt.DefaultCost)
            if err != nil {
                return err
            }
            u.Password = string(hashedPassword)
            return nil
        }

        // internal/models/post.go
        type Post struct {
            ID        uint           `gorm:"primarykey"`
            Title     string         `gorm:"type:varchar(200);not null"`
            Content   string         `gorm:"type:text"`
            UserID    uint          
            User      User           `gorm:"foreignKey:UserID"`
            Tags      []Tag          `gorm:"many2many:post_tags;"`
            CreatedAt time.Time
            UpdatedAt time.Time
            DeletedAt gorm.DeletedAt `gorm:"index"`
        }

        type Tag struct {
            ID    uint   `gorm:"primarykey"`
            Name  string `gorm:"type:varchar(50);unique;not null"`
            Posts []Post `gorm:"many2many:post_tags;"`
        }
        ```

2. Repository 패턴
    1. 기본 Repository 인터페이스
        ```go
        // internal/repository/repository.go
        package repository

        type Repository interface {
            Create(interface{}) error
            Update(interface{}) error
            Delete(interface{}) error
            FindByID(id uint, dest interface{}) error
            FindOne(condition interface{}, dest interface{}) error
            Find(dest interface{}, conds ...interface{}) error
        }

        // 기본 구현
        type BaseRepository struct {
            db *gorm.DB
        }

        func NewBaseRepository(db *gorm.DB) *BaseRepository {
            return &BaseRepository{db: db}
        }

        func (r *BaseRepository) Create(value interface{}) error {
            return r.db.Create(value).Error
        }

        func (r *BaseRepository) Update(value interface{}) error {
            return r.db.Save(value).Error
        }

        func (r *BaseRepository) Delete(value interface{}) error {
            return r.db.Delete(value).Error
        }

        func (r *BaseRepository) FindByID(id uint, dest interface{}) error {
            return r.db.First(dest, id).Error
        }

        func (r *BaseRepository) FindOne(condition interface{}, dest interface{}) error {
            return r.db.Where(condition).First(dest).Error
        }

        func (r *BaseRepository) Find(dest interface{}, conds ...interface{}) error {
            return r.db.Find(dest, conds...).Error
        }
        ```

    2. 사용자 Repository
        ```go
        // internal/repository/user_repository.go
        type UserRepository struct {
            *BaseRepository
        }

        func NewUserRepository(db *gorm.DB) *UserRepository {
            return &UserRepository{NewBaseRepository(db)}
        }

        func (r *UserRepository) FindByEmail(email string) (*models.User, error) {
            var user models.User
            err := r.db.Where("email = ?", email).First(&user).Error
            if err != nil {
                return nil, err
            }
            return &user, nil
        }

        func (r *UserRepository) FindByUsername(username string) (*models.User, error) {
            var user models.User
            err := r.db.Where("username = ?", username).First(&user).Error
            if err != nil {
                return nil, err
            }
            return &user, nil
        }

        func (r *UserRepository) FindActiveUsers(page, pageSize int) ([]models.User, int64, error) {
            var users []models.User
            var total int64

            query := r.db.Model(&models.User{}).Where("active = ?", true)
            
            err := query.Count(&total).Error
            if err != nil {
                return nil, 0, err
            }

            err = query.Offset((page - 1) * pageSize).
                Limit(pageSize).
                Find(&users).Error
            
            return users, total, err
        }
        ```

3. 트랜잭션 처리
    1. 트랜잭션 미들웨어
        ```go
        func TransactionMiddleware(db *gorm.DB) gin.HandlerFunc {
            return func(c *gin.Context) {
                tx := db.Begin()
                c.Set("tx", tx)
                
                defer func() {
                    if r := recover(); r != nil {
                        tx.Rollback()
                        panic(r)
                    }
                }()

                c.Next()

                if len(c.Errors) > 0 {
                    tx.Rollback()
                } else {
                    tx.Commit()
                }
            }
        }
        ```

    2. 트랜잭션 사용 예시
        ```go
        func CreateUserWithProfile(c *gin.Context) {
            tx := c.MustGet("tx").(*gorm.DB)
            
            var user models.User
            if err := c.ShouldBindJSON(&user); err != nil {
                c.JSON(400, gin.H{"error": err.Error()})
                return
            }

            if err := tx.Create(&user).Error; err != nil {
                c.JSON(500, gin.H{"error": "Failed to create user"})
                return
            }

            profile := models.Profile{
                UserID: user.ID,
                // 프로필 데이터...
            }

            if err := tx.Create(&profile).Error; err != nil {
                c.JSON(500, gin.H{"error": "Failed to create profile"})
                return
            }

            c.JSON(201, gin.H{"message": "User created successfully"})
        }
        ```

4. 관계 처리
    1. Eager Loading
        ```go
        func (r *PostRepository) GetPostWithRelations(id uint) (*models.Post, error) {
            var post models.Post
            err := r.db.Preload("User").
                Preload("Tags").
                Preload("Comments").
                First(&post, id).Error
            return &post, err
        }

        func (r *PostRepository) GetUserPosts(userID uint) ([]models.Post, error) {
            var posts []models.Post
            err := r.db.Preload("Tags").
                Where("user_id = ?", userID).
                Find(&posts).Error
            return posts, err
        }
        ```

    2. Lazy Loading
        ```go
        func (r *PostRepository) GetPostComments(post *models.Post) error {
            return r.db.Model(post).Association("Comments").Find(&post.Comments)
        }
        ```

5. 쿼리 최적화
    1. 인덱스 설정
        ```go
        type Post struct {
            ID        uint      `gorm:"primarykey"`
            Title     string    `gorm:"type:varchar(200);index:idx_title"`
            UserID    uint      `gorm:"index"`
            CreatedAt time.Time `gorm:"index"`
        }
        ```

    2. 복합 인덱스
        ```go
        func (p *Post) TableName() string {
            return "posts"
        }

        func (p *Post) AfterMigrate(tx *gorm.DB) error {
            return tx.Exec(`
                CREATE INDEX idx_posts_user_created 
                ON posts(user_id, created_at DESC)
            `).Error
        }
        ```

    3. 쿼리 최적화
        ```go
        func (r *PostRepository) GetUserFeed(userID uint, page, pageSize int) ([]models.Post, error) {
            var posts []models.Post
            
            err := r.db.Select("id, title, created_at"). // 필요한 필드만 선택
                Where("user_id = ?", userID).
                Order("created_at DESC").
                Limit(pageSize).
                Offset((page - 1) * pageSize).
                Find(&posts).Error
                
            return posts, err
        }
        ```

6. 마이그레이션
    1. Auto Migration
        ```go
        func AutoMigrate(db *gorm.DB) error {
            return db.AutoMigrate(
                &models.User{},
                &models.Profile{},
                &models.Post{},
                &models.Comment{},
                &models.Tag{},
            )
        }
        ```

    2. 수동 마이그레이션
        ```go
        // migrations/20240109_add_user_status.go
        func Migrate(db *gorm.DB) error {
            return db.Transaction(func(tx *gorm.DB) error {
                // 새 컬럼 추가
                if err := tx.Exec(`
                    ALTER TABLE users 
                    ADD COLUMN status varchar(20) NOT NULL DEFAULT 'active'
                `).Error; err != nil {
                    return err
                }

                // 인덱스 추가
                if err := tx.Exec(`
                    CREATE INDEX idx_users_status ON users(status)
                `).Error; err != nil {
                    return err
                }

                return nil
            })
        }
        ```

7. 성능 모니터링
    1. 쿼리 로깅
        ```go
        func setupQueryLogger(db *gorm.DB) {
            db.Callback().Query().Before("gorm:query").Register("custom_query_logger", func(db *gorm.DB) {
                startTime := time.Now()
                db.Statement.Settings.Store("startTime", startTime)
            })

            db.Callback().Query().After("gorm:query").Register("custom_query_logger", func(db *gorm.DB) {
                if v, ok := db.Statement.Settings.Load("startTime"); ok {
                    startTime := v.(time.Time)
                    duration := time.Since(startTime)
                    
                    // 느린 쿼리 로깅
                    if duration > time.Millisecond*100 {
                        log.Printf("Slow Query (%v): %v\n", duration, db.Statement.SQL.String())
                    }
                }
            })
        }
        ```

    2. 메트릭 수집
        ```go
        type DBStats struct {
            OpenConnections int
            InUse          int
            Idle           int
            WaitCount      int64
            WaitDuration   time.Duration
            MaxIdleClosed  int64
            MaxLifetimeClosed int64
        }

        func CollectDBStats(db *gorm.DB) *DBStats {
            sqlDB, err := db.DB()
            if err != nil {
                return nil
            }

            stats := sqlDB.Stats()
            return &DBStats{
                OpenConnections: stats.OpenConnections,
                InUse:          stats.InUse,
                Idle:           stats.Idle,
                WaitCount:      stats.WaitCount,
                WaitDuration:   stats.WaitDuration,
                MaxIdleClosed:  stats.MaxIdleClosed,
                MaxLifetimeClosed: stats.MaxLifetimeClosed,
            }
        }
        ```

8. 테스트
    1. 테스트 데이터베이스 설정
        ```go
        func SetupTestDB() (*gorm.DB, error) {
            // 테스트 데이터베이스 연결 설정
            dsn := "host=localhost user=test password=test dbname=test_db port=5432 sslmode=disable"
            db, err := gorm.Open(postgres.Open(dsn), &gorm.Config{})
            if err != nil {
                return nil, err
            }

            // 테이블 초기화
            err = db.Migrator().DropTable(&models.User{}, &models.Post{})
            if err != nil {
                return nil, err
            }

            err = db.AutoMigrate(&models.User{}, &models.Post{})
            if err != nil {
                return nil, err
            }

            return db, nil
        }
        ```

    2. Repository 테스트
        ```go
        func TestUserRepository_Create(t *testing.T) {
            db, err := SetupTestDB()
            if err != nil {
                t.Fatal(err)
            }

            repo := NewUserRepository(db)

            testCases := []struct {
                name    string
                user    models.User
                wantErr bool
            }{
                {
                    name: "유효한 사용자 생성",
                    user: models.User{
                        Username: "testuser",
                        Email:    "test@example.com",
                        Password: "password123",
                    },
                    wantErr: false,
                },
                {
                    name: "중복된 사용자 생성",
                    user: models.User{
                        Username: "testuser",  // 이미 생성된 사용자와 동일
                        Email:    "test@example.com",
                        Password: "password123", 
                    },
                    wantErr: true,
                },
                {
                    name: "빈 이메일로 사용자 생성",
                    user: models.User{
                        Username: "newuser",
                        Email:    "",
                        Password: "password123",
                    },
                    wantErr: true,
                },
            }

            for _, tc := range testCases {
                t.Run(tc.name, func(t *testing.T) {
                    err := repo.Create(&tc.user)
                    if (err != nil) != tc.wantErr {
                        t.Errorf("Create() error = %v, wantErr %v", err, tc.wantErr)
                    }

                    if !tc.wantErr {
                        // 생성된 사용자 확인
                        var found models.User
                        err = db.Where("username = ?", tc.user.Username).First(&found).Error
                        if err != nil {
                            t.Errorf("Failed to find created user: %v", err)
                        }

                        if found.Username != tc.user.Username {
                            t.Errorf("Created user username = %v, want %v", found.Username, tc.user.Username)
                        }

                        if found.Email != tc.user.Email {
                            t.Errorf("Created user email = %v, want %v", found.Email, tc.user.Email)
                        }
                    }
                })
            }
        }

        // 조회 테스트 추가
        func TestUserRepository_FindByUsername(t *testing.T) {
            db, err := SetupTestDB()
            if err != nil {
                t.Fatal(err)
            }

            repo := NewUserRepository(db)

            // 테스트 데이터 생성
            testUser := &models.User{
                Username: "testuser",
                Email:    "test@example.com",
                Password: "password123",
            }
            if err := repo.Create(testUser); err != nil {
                t.Fatal(err)
            }

            testCases := []struct {
                name     string
                username string
                wantErr  bool
            }{
                {
                    name:     "존재하는 사용자 찾기",
                    username: "testuser",
                    wantErr:  false,
                },
                {
                    name:     "존재하지 않는 사용자 찾기",
                    username: "nonexistent",
                    wantErr:  true,
                },
            }

            for _, tc := range testCases {
                t.Run(tc.name, func(t *testing.T) {
                    user, err := repo.FindByUsername(tc.username)
                    if (err != nil) != tc.wantErr {
                        t.Errorf("FindByUsername() error = %v, wantErr %v", err, tc.wantErr)
                        return
                    }

                    if !tc.wantErr {
                        if user.Username != tc.username {
                            t.Errorf("FindByUsername() got = %v, want %v", user.Username, tc.username)
                        }
                    }
                })
            }
        }

        // 업데이트 테스트 추가
        func TestUserRepository_Update(t *testing.T) {
            db, err := SetupTestDB()
            if err != nil {
                t.Fatal(err)
            }

            repo := NewUserRepository(db)

            // 테스트 사용자 생성
            user := &models.User{
                Username: "testuser",
                Email:    "test@example.com",
                Password: "password123",
            }
            if err := repo.Create(user); err != nil {
                t.Fatal(err)
            }

            // 업데이트 테스트
            user.Email = "updated@example.com"
            if err := repo.Update(user); err != nil {
                t.Errorf("Update() error = %v", err)
            }

            // 업데이트 확인
            updated, err := repo.FindByUsername("testuser")
            if err != nil {
                t.Errorf("Failed to find updated user: %v", err)
            }

            if updated.Email != "updated@example.com" {
                t.Errorf("Update() got = %v, want %v", updated.Email, "updated@example.com")
            }
        }
        ```

## 캐싱 전략

1. Redis 설정
    1. Redis 연결 설정
        ```go
        // pkg/cache/redis.go
        package cache

        import (
            "context"
            "encoding/json"
            "time"

            "github.com/redis/go-redis/v9"
        )

        type RedisCache struct {
            client *redis.Client
            ctx    context.Context
        }

        func NewRedisCache(addr, password string, db int) *RedisCache {
            client := redis.NewClient(&redis.Options{
                Addr:         addr,
                Password:     password,
                DB:           db,
                PoolSize:     10,
                MinIdleConns: 5,
                MaxRetries:   3,
            })

            return &RedisCache{
                client: client,
                ctx:    context.Background(),
            }
        }

        // 기본 CRUD 메서드
        func (c *RedisCache) Set(key string, value interface{}, expiration time.Duration) error {
            data, err := json.Marshal(value)
            if err != nil {
                return err
            }
            return c.client.Set(c.ctx, key, data, expiration).Err()
        }

        func (c *RedisCache) Get(key string, dest interface{}) error {
            data, err := c.client.Get(c.ctx, key).Bytes()
            if err != nil {
                return err
            }
            return json.Unmarshal(data, dest)
        }

        func (c *RedisCache) Delete(key string) error {
            return c.client.Del(c.ctx, key).Err()
        }

        func (c *RedisCache) Exists(key string) bool {
            return c.client.Exists(c.ctx, key).Val() > 0
        }
        ```

    2. 캐시 키 생성기
        ```go
        // pkg/cache/key_generator.go
        type KeyGenerator struct {
            prefix string
        }

        func NewKeyGenerator(prefix string) *KeyGenerator {
            return &KeyGenerator{prefix: prefix}
        }

        func (kg *KeyGenerator) Generate(parts ...string) string {
            key := kg.prefix
            for _, part := range parts {
                key += ":" + part
            }
            return key
        }

        func (kg *KeyGenerator) UserKey(userID string) string {
            return kg.Generate("user", userID)
        }

        func (kg *KeyGenerator) PostKey(postID string) string {
            return kg.Generate("post", postID)
        }

        func (kg *KeyGenerator) ListKey(resource string, page string) string {
            return kg.Generate(resource, "list", page)
        }
        ```

2. 캐시 미들웨어
    1. 응답 캐싱 미들웨어
        ```go
        // internal/middleware/cache.go
        func CacheMiddleware(cache *cache.RedisCache, duration time.Duration) gin.HandlerFunc {
            return func(c *gin.Context) {
                // 캐시 키 생성
                key := generateCacheKey(c.Request)

                // 캐시된 응답 확인
                var cachedResponse []byte
                err := cache.Get(key, &cachedResponse)
                if err == nil {
                    c.Data(http.StatusOK, "application/json", cachedResponse)
                    c.Abort()
                    return
                }

                // 응답 캡처를 위한 responseWriter 래핑
                writer := &responseWriter{ResponseWriter: c.Writer}
                c.Writer = writer

                c.Next()

                // 성공적인 응답만 캐시
                if c.Writer.Status() == http.StatusOK {
                    cache.Set(key, writer.body, duration)
                }
            }
        }

        func generateCacheKey(r *http.Request) string {
            // URL과 쿼리 파라미터를 포함한 캐시 키 생성
            key := r.URL.Path
            if r.URL.RawQuery != "" {
                key += "?" + r.URL.RawQuery
            }
            return key
        }

        type responseWriter struct {
            gin.ResponseWriter
            body []byte
        }

        func (w *responseWriter) Write(b []byte) (int, error) {
            w.body = b
            return w.ResponseWriter.Write(b)
        }
        ```

    2. 사용자별 캐싱 미들웨어
        ```go
        func UserCacheMiddleware(cache *cache.RedisCache, duration time.Duration) gin.HandlerFunc {
            return func(c *gin.Context) {
                // 사용자 ID 추출
                userID := c.GetString("userID")
                if userID == "" {
                    c.Next()
                    return
                }

                // 사용자별 캐시 키 생성
                key := fmt.Sprintf("user:%s:%s", userID, c.Request.URL.Path)
                
                // 캐시 확인 및 처리
                var response interface{}
                err := cache.Get(key, &response)
                if err == nil {
                    c.JSON(http.StatusOK, response)
                    c.Abort()
                    return
                }

                c.Next()

                // 성공 응답 캐싱
                if c.Writer.Status() == http.StatusOK {
                    var responseData interface{}
                    if err := json.Unmarshal([]byte(c.Writer.Body()), &responseData); err == nil {
                        cache.Set(key, responseData, duration)
                    }
                }
            }
        }
        ```

3. 고급 캐싱 전략
    1. 계층형 캐싱
        ```go
        type CacheLayer interface {
            Get(key string, dest interface{}) error
            Set(key string, value interface{}, expiration time.Duration) error
            Delete(key string) error
        }

        type LayeredCache struct {
            l1    CacheLayer // 메모리 캐시 (빠름)
            l2    CacheLayer // Redis 캐시 (느림)
            stats *CacheStats
        }

        func NewLayeredCache(l1, l2 CacheLayer) *LayeredCache {
            return &LayeredCache{
                l1: l1,
                l2: l2,
                stats: &CacheStats{},
            }
        }

        func (c *LayeredCache) Get(key string, dest interface{}) error {
            // L1 캐시 확인
            err := c.l1.Get(key, dest)
            if err == nil {
                c.stats.L1Hits++
                return nil
            }
            c.stats.L1Misses++

            // L2 캐시 확인
            err = c.l2.Get(key, dest)
            if err == nil {
                c.stats.L2Hits++
                // L1 캐시 업데이트
                c.l1.Set(key, dest, time.Minute*5)
                return nil
            }
            c.stats.L2Misses++

            return err
        }
        ```

    2. 패턴 기반 캐시 무효화
        ```go
        type CacheInvalidator struct {
            cache  *RedisCache
            client *redis.Client
        }

        func (ci *CacheInvalidator) InvalidateByPattern(pattern string) error {
            ctx := context.Background()
            iter := ci.client.Scan(ctx, 0, pattern, 0).Iterator()
            
            var keys []string
            for iter.Next(ctx) {
                keys = append(keys, iter.Val())
            }
            
            if len(keys) > 0 {
                return ci.client.Del(ctx, keys...).Err()
            }
            
            return nil
        }

        func (ci *CacheInvalidator) InvalidateUserData(userID string) error {
            pattern := fmt.Sprintf("user:%s:*", userID)
            return ci.InvalidateByPattern(pattern)
        }

        func (ci *CacheInvalidator) InvalidateResource(resource string) error {
            pattern := fmt.Sprintf("%s:*", resource)
            return ci.InvalidateByPattern(pattern)
        }
        ```

    3. 캐시 프리페칭
        ```go
        type CachePrefetcher struct {
            cache    *RedisCache
            repo     *repository.Repository
            interval time.Duration
        }

        func (cp *CachePrefetcher) StartPrefetching() {
            go func() {
                ticker := time.NewTicker(cp.interval)
                defer ticker.Stop()

                for range ticker.C {
                    cp.prefetchPopularContent()
                }
            }()
        }

        func (cp *CachePrefetcher) prefetchPopularContent() {
            // 인기 콘텐츠 조회
            posts, err := cp.repo.GetPopularPosts()
            if err != nil {
                log.Printf("Failed to prefetch popular posts: %v", err)
                return
            }

            // 캐시 업데이트
            for _, post := range posts {
                key := fmt.Sprintf("post:%d", post.ID)
                cp.cache.Set(key, post, time.Hour)
            }
        }
        ```

4. 분산 캐싱
    1. Redis cluster 설정
        ```go
        type ClusterCache struct {
            client *redis.ClusterClient
            ctx    context.Context
        }

        func NewClusterCache(addrs []string) *ClusterCache {
            client := redis.NewClusterClient(&redis.ClusterOptions{
                Addrs:        addrs,
                MaxRedirects: 3,
                PoolSize:     10,
                RouteByLatency: true,
            })

            return &ClusterCache{
                client: client,
                ctx:    context.Background(),
            }
        }
        ```

    2. 일관성 있는 해싱
        ```go
        type ConsistentHashCache struct {
            hashRing *hashring.HashRing
            caches   map[string]*RedisCache
        }

        func NewConsistentHashCache(nodes []string) *ConsistentHashCache {
            ring := hashring.New(nodes)
            caches := make(map[string]*RedisCache)
            
            for _, node := range nodes {
                caches[node] = NewRedisCache(node, "", 0)
            }
            
            return &ConsistentHashCache{
                hashRing: ring,
                caches:   caches,
            }
        }

        func (c *ConsistentHashCache) Get(key string) (interface{}, error) {
            node, _ := c.hashRing.GetNode(key)
            cache := c.caches[node]
            return cache.Get(key)
        }
        ```

5. 캐시 모니터링
    1. 캐시 통계
        ```go
        type CacheStats struct {
            Hits      uint64
            Misses    uint64
            Evictions uint64
            mu        sync.RWMutex
        }

        func (cs *CacheStats) RecordHit() {
            cs.mu.Lock()
            cs.Hits++
            cs.mu.Unlock()
        }

        func (cs *CacheStats) RecordMiss() {
            cs.mu.Lock()
            cs.Misses++
            cs.mu.Unlock()
        }

        func (cs *CacheStats) GetHitRate() float64 {
            cs.mu.RLock()
            defer cs.mu.RUnlock()
            
            total := cs.Hits + cs.Misses
            if total == 0 {
                return 0
            }
            return float64(cs.Hits) / float64(total)
        }
        ```

    2. Prometheus 메트릭스
        ```go
        type CacheMetrics struct {
            hits      prometheus.Counter
            misses    prometheus.Counter
            latency   prometheus.Histogram
        }

        func NewCacheMetrics() *CacheMetrics {
            return &CacheMetrics{
                hits: prometheus.NewCounter(prometheus.CounterOpts{
                    Name: "cache_hits_total",
                    Help: "Total number of cache hits",
                }),
                misses: prometheus.NewCounter(prometheus.CounterOpts{
                    Name: "cache_misses_total",
                    Help: "Total number of cache misses",
                }),
                latency: prometheus.NewHistogram(prometheus.HistogramOpts{
                    Name:    "cache_operation_duration_seconds",
                    Help:    "Time spent on cache operations",
                    Buckets: prometheus.DefBuckets,
                }),
            }
        }
        ```

6. Best Practices
    1. 캐시 키 설계
        ```go
        // 좋은 예시
        user:123:profile     // 사용자 프로필
        post:456:comments    // 게시글 댓글
        list:posts:page:1    // 페이지네이션된 목록

        // 나쁜 예시
        123                 // 컨텍스트 없음
        user_profile_123    // 구분자 일관성 없음
        ```

    2. TTL 전략
        ```go
        const (
            ShortTTL  = 5 * time.Minute  // 자주 변경되는 데이터
            MediumTTL = 1 * time.Hour    // 일반적인 데이터
            LongTTL   = 24 * time.Hour   // 거의 변경되지 않는 데이터
        )

        func getTTL(resourceType string) time.Duration {
            switch resourceType {
            case "user_profile":
                return MediumTTL
            case "post_content":
                return LongTTL
            case "comments":
                return ShortTTL
            default:
                return MediumTTL
            }
        }
        ```

    3. 캐싱 갱신 전략
        ```go
        // Write-Through 캐시
        func (s *Service) UpdateUser(user *models.User) error {
            // DB 업데이트
            if err := s.repo.Update(user); err != nil {
                return err
            }
            
            // 캐시 업데이트
            key := fmt.Sprintf("user:%d", user.ID)
            return s.cache.Set(key, user, MediumTTL)
        }

        // Write-Behind 캐시
        type WriteBuffer struct {
            buffer chan WriteOperation
            db     *gorm.DB
        }

        func (wb *WriteBuffer) Start() {
            go func() {
                for op := range wb.buffer {
                    wb.db.Create(op.Data)
                }
            }()
        }
        ```

## 인증/인가 (Authentication/Authorization)

1. JWT 인증
    1. JWT 설정
        ```go
        // pkg/auth/jwt.go
        package auth

        import (
            "time"

            "github.com/golang-jwt/jwt/v5"
        )

        type JWTConfig struct {
            SecretKey     string
            TokenDuration time.Duration
        }

        type JWTClaims struct {
            UserID   uint   `json:"user_id"`
            Username string `json:"username"`
            Role     string `json:"role"`
            jwt.RegisteredClaims
        }

        type JWTService struct {
            config JWTConfig
        }

        func NewJWTService(config JWTConfig) *JWTService {
            return &JWTService{
                config: config,
            }
        }

        // 토큰 생성
        func (s *JWTService) GenerateToken(userID uint, username, role string) (string, error) {
            claims := JWTClaims{
                UserID:   userID,
                Username: username,
                Role:     role,
                RegisteredClaims: jwt.RegisteredClaims{
                    ExpiresAt: jwt.NewNumericDate(time.Now().Add(s.config.TokenDuration)),
                    IssuedAt:  jwt.NewNumericDate(time.Now()),
                    NotBefore: jwt.NewNumericDate(time.Now()),
                },
            }

            token := jwt.NewWithClaims(jwt.SigningMethodHS256, claims)
            return token.SignedString([]byte(s.config.SecretKey))
        }

        // 토큰 검증
        func (s *JWTService) ValidateToken(tokenString string) (*JWTClaims, error) {
            token, err := jwt.ParseWithClaims(tokenString, &JWTClaims{}, func(token *jwt.Token) (interface{}, error) {
                return []byte(s.config.SecretKey), nil
            })

            if err != nil {
                return nil, err
            }

            if claims, ok := token.Claims.(*JWTClaims); ok && token.Valid {
                return claims, nil
            }

            return nil, jwt.ErrSignatureInvalid
        }
        ```

    2. 인증 미들웨어
        ```go
        // internal/middleware/auth.go
        func JWTAuthMiddleware(jwtService *auth.JWTService) gin.HandlerFunc {
            return func(c *gin.Context) {
                token := extractToken(c)
                if token == "" {
                    c.AbortWithStatusJSON(http.StatusUnauthorized, gin.H{
                        "error": "No authorization token provided",
                    })
                    return
                }

                claims, err := jwtService.ValidateToken(token)
                if err != nil {
                    c.AbortWithStatusJSON(http.StatusUnauthorized, gin.H{
                        "error": "Invalid token",
                    })
                    return
                }

                // 사용자 정보를 컨텍스트에 저장
                c.Set("userID", claims.UserID)
                c.Set("username", claims.Username)
                c.Set("userRole", claims.Role)

                c.Next()
            }
        }

        func extractToken(c *gin.Context) string {
            bearerToken := c.GetHeader("Authorization")
            if len(bearerToken) > 7 && strings.ToUpper(bearerToken[0:7]) == "BEARER " {
                return bearerToken[7:]
            }
            return ""
        }
        ```

2. RBAC(Role-Based Access Control)
    1. 역할 정의
        ```go
        // internal/models/role.go
        type Role struct {
            ID          uint   `gorm:"primarykey"`
            Name        string `gorm:"type:varchar(50);unique;not null"`
            Permissions []Permission `gorm:"many2many:role_permissions;"`
        }

        type Permission struct {
            ID          uint   `gorm:"primarykey"`
            Resource    string `gorm:"type:varchar(100);not null"`
            Action      string `gorm:"type:varchar(50);not null"`  // create, read, update, delete
        }

        // 역할 상수
        const (
            RoleAdmin     = "admin"
            RoleManager   = "manager"
            RoleUser      = "user"
        )
        ```

    2. RBAC 미들웨어
        ```go
        // internal/middleware/rbac.go
        type RBACService struct {
            permissions map[string]map[string][]string  // role -> resource -> actions
        }

        func NewRBACService() *RBACService {
            return &RBACService{
                permissions: map[string]map[string][]string{
                    RoleAdmin: {
                        "users":    {"create", "read", "update", "delete"},
                        "posts":    {"create", "read", "update", "delete"},
                        "comments": {"create", "read", "update", "delete"},
                    },
                    RoleManager: {
                        "users":    {"read"},
                        "posts":    {"create", "read", "update"},
                        "comments": {"read", "delete"},
                    },
                    RoleUser: {
                        "posts":    {"read"},
                        "comments": {"create", "read"},
                    },
                },
            }
        }

        func (rbac *RBACService) CheckPermission(role, resource, action string) bool {
            if resourcePerms, ok := rbac.permissions[role]; ok {
                if actions, ok := resourcePerms[resource]; ok {
                    for _, a := range actions {
                        if a == action {
                            return true
                        }
                    }
                }
            }
            return false
        }

        func RBACMiddleware(rbac *RBACService) gin.HandlerFunc {
            return func(c *gin.Context) {
                role := c.GetString("userRole")
                if role == "" {
                    c.AbortWithStatusJSON(http.StatusUnauthorized, gin.H{
                        "error": "Role not found",
                    })
                    return
                }

                resource := getResourceFromPath(c.Request.URL.Path)
                action := getActionFromMethod(c.Request.Method)

                if !rbac.CheckPermission(role, resource, action) {
                    c.AbortWithStatusJSON(http.StatusForbidden, gin.H{
                        "error": "Insufficient permissions",
                    })
                    return
                }

                c.Next()
            }
        }

        func getResourceFromPath(path string) string {
            // /api/v1/users -> users
            parts := strings.Split(path, "/")
            if len(parts) >= 3 {
                return parts[3]
            }
            return ""
        }

        func getActionFromMethod(method string) string {
            switch method {
            case "GET":
                return "read"
            case "POST":
                return "create"
            case "PUT", "PATCH":
                return "update"
            case "DELETE":
                return "delete"
            default:
                return ""
            }
        }
        ```

3. 인증 세션 관리
    1. Redis 세션 저장소
        ```go
        // pkg/session/redis_store.go
        type SessionStore struct {
            client *redis.Client
        }

        type Session struct {
            ID        string    `json:"id"`
            UserID    uint      `json:"user_id"`
            UserRole  string    `json:"user_role"`
            CreatedAt time.Time `json:"created_at"`
            ExpiresAt time.Time `json:"expires_at"`
        }

        func (store *SessionStore) CreateSession(userID uint, role string, duration time.Duration) (*Session, error) {
            session := &Session{
                ID:        uuid.New().String(),
                UserID:    userID,
                UserRole:  role,
                CreatedAt: time.Now(),
                ExpiresAt: time.Now().Add(duration),
            }

            data, err := json.Marshal(session)
            if err != nil {
                return nil, err
            }

            err = store.client.Set(context.Background(), 
                fmt.Sprintf("session:%s", session.ID), 
                data, 
                duration).Err()
            if err != nil {
                return nil, err
            }

            return session, nil
        }

        func (store *SessionStore) GetSession(sessionID string) (*Session, error) {
            data, err := store.client.Get(context.Background(), 
                fmt.Sprintf("session:%s", sessionID)).Bytes()
            if err != nil {
                return nil, err
            }

            var session Session
            if err := json.Unmarshal(data, &session); err != nil {
                return nil, err
            }

            return &session, nil
        }
        ```

    2. 세션 미들웨어
        ```go
        // internal/middleware/session.go
        func SessionMiddleware(store *session.SessionStore) gin.HandlerFunc {
            return func(c *gin.Context) {
                sessionID, err := c.Cookie("session_id")
                if err != nil {
                    c.AbortWithStatusJSON(http.StatusUnauthorized, gin.H{
                        "error": "No session found",
                    })
                    return
                }

                session, err := store.GetSession(sessionID)
                if err != nil {
                    c.AbortWithStatusJSON(http.StatusUnauthorized, gin.H{
                        "error": "Invalid session",
                    })
                    return
                }

                if time.Now().After(session.ExpiresAt) {
                    store.DeleteSession(sessionID)
                    c.AbortWithStatusJSON(http.StatusUnauthorized, gin.H{
                        "error": "Session expired",
                    })
                    return
                }

                c.Set("userID", session.UserID)
                c.Set("userRole", session.UserRole)

                c.Next()
            }
        }
        ```

4. OAuth2 통합
    1. OAuth2 설정
        ```go
        // pkg/auth/oauth2.go
        type OAuth2Config struct {
            Provider     string
            ClientID     string
            ClientSecret string
            RedirectURL  string
            Scopes       []string
        }

        type OAuth2Service struct {
            configs map[string]*oauth2.Config
        }

        func NewOAuth2Service(configs []OAuth2Config) *OAuth2Service {
            service := &OAuth2Service{
                configs: make(map[string]*oauth2.Config),
            }

            for _, config := range configs {
                service.configs[config.Provider] = &oauth2.Config{
                    ClientID:     config.ClientID,
                    ClientSecret: config.ClientSecret,
                    RedirectURL:  config.RedirectURL,
                    Scopes:      config.Scopes,
                    Endpoint:     getOAuth2Endpoint(config.Provider),
                }
            }

            return service
        }

        func getOAuth2Endpoint(provider string) oauth2.Endpoint {
            switch provider {
            case "google":
                return google.Endpoint
            case "github":
                return github.Endpoint
            default:
                return oauth2.Endpoint{}
            }
        }
        ```

    2. OAuth 핸들러
        ```go
        // internal/handlers/oauth2.go
        func (h *OAuth2Handler) HandleOAuth2Login(c *gin.Context) {
            provider := c.Param("provider")
            config, exists := h.service.configs[provider]
            if !exists {
                c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid provider"})
                return
            }

            state := generateRandomState()
            c.SetCookie("oauth_state", state, 3600, "/", "", false, true)

            url := config.AuthCodeURL(state)
            c.Redirect(http.StatusTemporaryRedirect, url)
        }

        func (h *OAuth2Handler) HandleOAuth2Callback(c *gin.Context) {
            provider := c.Param("provider")
            config, exists := h.service.configs[provider]
            if !exists {
                c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid provider"})
                return
            }

            state, _ := c.Cookie("oauth_state")
            if state != c.Query("state") {
                c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid state"})
                return
            }

            code := c.Query("code")
            token, err := config.Exchange(context.Background(), code)
            if err != nil {
                c.JSON(http.StatusBadRequest, gin.H{"error": "Failed to exchange token"})
                return
            }

            userInfo, err := h.getUserInfo(provider, token.AccessToken)
            if err != nil {
                c.JSON(http.StatusInternalServerError, gin.H{"error": "Failed to get user info"})
                return
            }

            // 사용자 정보 처리 및 세션 생성
            user, err := h.userService.FindOrCreateOAuthUser(userInfo)
            if err != nil {
                c.JSON(http.StatusInternalServerError, gin.H{"error": "Failed to process user"})
                return
            }

            // JWT 토큰 생성
            token, err = h.jwtService.GenerateToken(user.ID, user.Email, user.Role)
            if err != nil {
                c.JSON(http.StatusInternalServerError, gin.H{"error": "Failed to generate token"})
                return
            }

            c.JSON(http.StatusOK, gin.H{
                "token": token,
                "user":  user,
            })
        }
        ```

5. 보안 강화
    1. 비밀번호 해싱
        ```go
        // pkg/auth/password.go
        type PasswordService struct {
            pepper string
            cost   int
        }

        func NewPasswordService(pepper string, cost int) *PasswordService {
            return &PasswordService{
                pepper: pepper,
                cost:   cost,
            }
        }

        func (s *PasswordService) HashPassword(password string) (string, error) {
            // 페퍼 추가
            peppered := password + s.pepper

            // bcrypt 해싱
            hash, err := bcrypt.GenerateFromPassword([]byte(peppered), s.cost)
            if err != nil {
                return "", err
            }

            return string(hash), nil
        }

        func (s *PasswordService) CheckPassword(password, hash string) bool {
            peppered := password + s.pepper
            err := bcrypt.CompareHashAndPassword([]byte(hash), []byte(peppered))
            return err == nil
        }
        ```

    2. 레이트 리미팅
        ```go
        // internal/middleware/ratelimit.go
        func RateLimitMiddleware(store *redis.Client) gin.HandlerFunc {
            return func(c *gin.Context) {
                key := fmt.Sprintf("ratelimit:%s", c.ClientIP())
                
                count, err := store.Incr(context.Background(), key).Result()
                if err != nil {
                    c.Next()
                    return
                }
                
                // 첫 요청이면 만료 시간 설정
                if count == 1 {
                    store.Expire(context.Background(), key, time.Hour)
                }
                
                // 시간당 최대 요청 수 체크 (예: 100회)
                if count > 100 {
                    c.AbortWithStatusJSON(http.StatusTooManyRequests, gin.H{
                        "error": "Rate limit exceeded",
                    })
                    return
                }
                
                c.Next()
            }
        }

        // 보안 헤더 미들웨어 추가
        func SecurityHeadersMiddleware() gin.HandlerFunc {
            return func(c *gin.Context) {
                // XSS 방지
                c.Header("X-XSS-Protection", "1; mode=block")
                // 콘텐츠 보안 정책
                c.Header("Content-Security-Policy", "default-src 'self'")
                // 클릭재킹 방지
                c.Header("X-Frame-Options", "DENY")
                // MIME 스니핑 방지
                c.Header("X-Content-Type-Options", "nosniff")
                // HSTS
                c.Header("Strict-Transport-Security", "max-age=31536000; includeSubDomains")
                
                c.Next()
            }
        }

        // SQL 인젝션 방지 미들웨어
        func SQLInjectionPreventionMiddleware() gin.HandlerFunc {
            return func(c *gin.Context) {
                // SQL 인젝션 패턴 체크
                params := c.Request.URL.Query()
                for _, values := range params {
                    for _, v := range values {
                        if containsSQLInjection(v) {
                            c.AbortWithStatusJSON(http.StatusBadRequest, gin.H{
                                "error": "Invalid input detected",
                            })
                            return
                        }
                    }
                }
                
                c.Next()
            }
        }

        func containsSQLInjection(input string) bool {
            // SQL 인젝션 패턴 체크
            patterns := []string{
                "SELECT", "INSERT", "UPDATE", "DELETE", "DROP",
                "UNION", "OR 1=1", "OR '1'='1",
                "--", ";--", ";", "/*", "*/",
            }
            
            input = strings.ToUpper(input)
            for _, pattern := range patterns {
                if strings.Contains(input, pattern) {
                    return true
                }
            }
            
            return false
        }
        ```

## 보안 강화

1. CORS (Cross-Origin Resource Sharing)
    1. CORS 설정
        ```go
        // internal/middleware/cors.go
        func CORSMiddleware() gin.HandlerFunc {
            return func(c *gin.Context) {
                c.Writer.Header().Set("Access-Control-Allow-Origin", "*")
                c.Writer.Header().Set("Access-Control-Max-Age", "86400")
                c.Writer.Header().Set("Access-Control-Allow-Methods", "POST, GET, PUT, DELETE, UPDATE, OPTIONS")
                c.Writer.Header().Set("Access-Control-Allow-Headers", "Content-Type, Content-Length, Accept-Encoding, X-CSRF-Token, Authorization")
                c.Writer.Header().Set("Access-Control-Expose-Headers", "Content-Length")
                c.Writer.Header().Set("Access-Control-Allow-Credentials", "true")

                if c.Request.Method == "OPTIONS" {
                    c.AbortWithStatus(204)
                    return
                }

                c.Next()
            }
        }

        // 커스텀 CORS 설정
        type CORSConfig struct {
            AllowOrigins     []string
            AllowMethods     []string
            AllowHeaders     []string
            ExposeHeaders    []string
            AllowCredentials bool
            MaxAge          time.Duration
        }

        func CustomCORSMiddleware(config CORSConfig) gin.HandlerFunc {
            return func(c *gin.Context) {
                origin := c.Request.Header.Get("Origin")
                
                // Origin 검증
                if isAllowedOrigin(origin, config.AllowOrigins) {
                    c.Writer.Header().Set("Access-Control-Allow-Origin", origin)
                }
                
                // 다른 CORS 헤더 설정
                if len(config.AllowMethods) > 0 {
                    c.Writer.Header().Set("Access-Control-Allow-Methods", 
                        strings.Join(config.AllowMethods, ", "))
                }
                
                if len(config.AllowHeaders) > 0 {
                    c.Writer.Header().Set("Access-Control-Allow-Headers", 
                        strings.Join(config.AllowHeaders, ", "))
                }
                
                if len(config.ExposeHeaders) > 0 {
                    c.Writer.Header().Set("Access-Control-Expose-Headers", 
                        strings.Join(config.ExposeHeaders, ", "))
                }
                
                if config.AllowCredentials {
                    c.Writer.Header().Set("Access-Control-Allow-Credentials", "true")
                }
                
                if config.MaxAge > 0 {
                    c.Writer.Header().Set("Access-Control-Max-Age", 
                        fmt.Sprintf("%.0f", config.MaxAge.Seconds()))
                }

                if c.Request.Method == "OPTIONS" {
                    c.AbortWithStatus(204)
                    return
                }

                c.Next()
            }
        }
        ```

2. XSS (Cross-Site Scripting) 방지
    1. HTML 이스케이프
        ```go
        // pkg/security/xss.go
        type XSSProtection struct {
            // 허용된 HTML 태그와 속성
            allowedTags       map[string]bool
            allowedAttributes map[string]bool
        }

        func NewXSSProtection() *XSSProtection {
            return &XSSProtection{
                allowedTags: map[string]bool{
                    "p": true, "br": true, "b": true, "i": true,
                    "strong": true, "em": true, "u": true,
                },
                allowedAttributes: map[string]bool{
                    "href": true, "title": true,
                },
            }
        }

        func (x *XSSProtection) SanitizeHTML(input string) string {
            p := bluemonday.NewPolicy()
            
            // 허용된 태그 설정
            for tag := range x.allowedTags {
                p.AllowElements(tag)
            }
            
            // 허용된 속성 설정
            for attr := range x.allowedAttributes {
                p.AllowAttrs(attr).OnElements("a")
            }
            
            return p.Sanitize(input)
        }

        // XSS 미들웨어
        func XSSMiddleware() gin.HandlerFunc {
            xss := NewXSSProtection()
            
            return func(c *gin.Context) {
                // request body가 있는 경우에만 처리
                if c.Request.Method == "POST" || c.Request.Method == "PUT" {
                    body, err := c.GetRawData()
                    if err != nil {
                        c.AbortWithError(http.StatusBadRequest, err)
                        return
                    }

                    // JSON 데이터 처리
                    var data map[string]interface{}
                    if err := json.Unmarshal(body, &data); err == nil {
                        sanitizeMap(data, xss)
                        
                        // 처리된 데이터를 다시 request body에 설정
                        newBody, _ := json.Marshal(data)
                        c.Request.Body = ioutil.NopCloser(bytes.NewBuffer(newBody))
                    }
                }
                
                c.Next()
            }
        }

        func sanitizeMap(data map[string]interface{}, xss *XSSProtection) {
            for k, v := range data {
                switch v := v.(type) {
                case string:
                    data[k] = xss.SanitizeHTML(v)
                case map[string]interface{}:
                    sanitizeMap(v, xss)
                case []interface{}:
                    for i, item := range v {
                        if str, ok := item.(string); ok {
                            v[i] = xss.SanitizeHTML(str)
                        }
                    }
                }
            }
        }
        ```

3. CSRF (Cross-Site Request Forgery) 방지
    1. CSRF 토큰 생성 및 검증
        ```go
        // pkg/security/csrf.go
        type CSRFProtection struct {
            secret []byte
            store  *redis.Client
        }

        func NewCSRFProtection(secret string, store *redis.Client) *CSRFProtection {
            return &CSRFProtection{
                secret: []byte(secret),
                store:  store,
            }
        }

        func (c *CSRFProtection) GenerateToken(userID string) (string, error) {
            // 토큰 생성
            token := make([]byte, 32)
            if _, err := rand.Read(token); err != nil {
                return "", err
            }
            
            tokenStr := base64.StdEncoding.EncodeToString(token)
            
            // Redis에 토큰 저장
            err := c.store.Set(context.Background(),
                fmt.Sprintf("csrf:%s", userID),
                tokenStr,
                24*time.Hour).Err()
            
            return tokenStr, err
        }

        func (c *CSRFProtection) ValidateToken(userID, token string) bool {
            storedToken, err := c.store.Get(context.Background(),
                fmt.Sprintf("csrf:%s", userID)).Result()
            if err != nil {
                return false
            }
            
            return subtle.ConstantTimeCompare([]byte(token), []byte(storedToken)) == 1
        }

        // CSRF 미들웨어
        func CSRFMiddleware(protection *CSRFProtection) gin.HandlerFunc {
            return func(c *gin.Context) {
                // GET 요청은 건너뜀
                if c.Request.Method == "GET" {
                    c.Next()
                    return
                }
                
                // 토큰 검증
                token := c.GetHeader("X-CSRF-Token")
                userID := c.GetString("userID")  // 인증 미들웨어에서 설정된 값
                
                if !protection.ValidateToken(userID, token) {
                    c.AbortWithStatusJSON(http.StatusForbidden, gin.H{
                        "error": "CSRF token validation failed",
                    })
                    return
                }
                
                c.Next()
            }
        }
        ```

4. 보안 헤더 설정
    1. 보안 헤더 미들웨어
        ```go
        // internal/middleware/security.go
        func SecurityHeadersMiddleware() gin.HandlerFunc {
            return func(c *gin.Context) {
                // XSS 방지
                c.Header("X-XSS-Protection", "1; mode=block")
                
                // 콘텐츠 보안 정책
                csp := []string{
                    "default-src 'self'",
                    "script-src 'self' 'unsafe-inline' 'unsafe-eval'",
                    "style-src 'self' 'unsafe-inline'",
                    "img-src 'self' data: https:",
                    "font-src 'self'",
                    "connect-src 'self'",
                }
                c.Header("Content-Security-Policy", strings.Join(csp, "; "))
                
                // 클릭재킹 방지
                c.Header("X-Frame-Options", "SAMEORIGIN")
                
                // MIME 스니핑 방지
                c.Header("X-Content-Type-Options", "nosniff")
                
                // HSTS (HTTPS 강제)
                c.Header("Strict-Transport-Security", "max-age=31536000; includeSubDomains")
                
                // Referrer Policy
                c.Header("Referrer-Policy", "strict-origin-when-cross-origin")
                
                // Feature Policy
                features := []string{
                    "camera 'none'",
                    "microphone 'none'",
                    "geolocation 'self'",
                    "payment 'self'",
                }
                c.Header("Feature-Policy", strings.Join(features, "; "))
                
                c.Next()
            }
        }
        ```

5. 입력 검증 및 이스케이프
    1. 입력 검증 유틸리티
        ```go
        // pkg/security/validation.go
        type Validator struct {
            // 정규식 패턴
            patterns map[string]*regexp.Regexp
        }

        func NewValidator() *Validator {
            return &Validator{
                patterns: map[string]*regexp.Regexp{
                    "email":    regexp.MustCompile(`^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$`),
                    "username": regexp.MustCompile(`^[a-zA-Z0-9_-]{3,20}$`),
                    "password": regexp.MustCompile(`^(?=.*[A-Za-z])(?=.*\d)(?=.*[@$!%*#?&])[A-Za-z\d@$!%*#?&]{8,}$`),
                    "url":      regexp.MustCompile(`^https?:\/\/.+`),
                },
            }
        }

        func (v *Validator) ValidateEmail(email string) bool {
            return v.patterns["email"].MatchString(email)
        }

        func (v *Validator) ValidateUsername(username string) bool {
            return v.patterns["username"].MatchString(username)
        }

        func (v *Validator) ValidatePassword(password string) bool {
            return v.patterns["password"].MatchString(password)
        }

        func (v *Validator) ValidateURL(url string) bool {
            return v.patterns["url"].MatchString(url)
        }

        // SQL 인젝션 방지
        func (v *Validator) EscapeSQL(input string) string {
            // 위험한 문자 이스케이프
            replacer := strings.NewReplacer(
                "'", "''",
                "\\", "\\\\",
                "\x00", "\\0",
                "\n", "\\n",
                "\r", "\\r",
                "\"", "\\\"",
                "\x1a", "\\Z",
            )
            
            return replacer.Replace(input)
        }
        ```

6. 파일 업로드 보안
    1. 안전한 파일 업로드 처리
        ```go
        // internal/handlers/upload.go
        type FileUploadConfig struct {
            MaxSize      int64
            AllowedTypes map[string]bool
            UploadDir    string
        }

        func NewFileUploadHandler(config FileUploadConfig) *FileUploadHandler {
            return &FileUploadHandler{
                config: config,
            }
        }

        func (h *FileUploadHandler) ValidateAndSaveFile(file *multipart.FileHeader) error {
            // 파일 크기 검증
            if file.Size > h.config.MaxSize {
                return errors.New("file size exceeds limit")
            }
            
            // 파일 타입 검증
            contentType, err := h.getFileContentType(file)
            if err != nil {
                return err
            }
            
            if !h.config.AllowedTypes[contentType] {
                return errors.New("file type not allowed")
            }
            
            // 안전한 파일명 생성
            filename := h.generateSafeFilename(file.Filename)
            
            // 파일 저장
            dst := filepath.Join(h.config.UploadDir, filename)
            return h.saveFile(file, dst)
        }

        func (h *FileUploadHandler) getFileContentType(file *multipart.FileHeader) (string, error) {
            f, err := file.Open()
            if err != nil {
                return "", err
            }
            defer f.Close()
            
            // 파일 시작 부분만 읽어서 MIME 타입 확인
            buffer := make([]byte, 512)
            _, err = f.Read(buffer)
            if err != nil {
                return "", err
            }
            
            return http.DetectContentType(buffer), nil
        }

        func (h *FileUploadHandler) generateSafeFilename(original string) string {
            // 확장자 추출
            ext := filepath.Ext(original)
            
            // UUID로 새 파일명 생성
            return fmt.Sprintf("%s%s", uuid.New().String(), ext)
        }

        func (h *FileUploadHandler) saveFile(file *multipart.FileHeader, dst string) error {
            src, err := file.Open()
            if err != nil {
                return err
            }
            defer src.Close()
            
            out, err := os.Create(dst)
            if err != nil {
                return err
            }
            defer out.Close()
            
            _, err = io.Copy(out, src)
            return err
        }
        ```

7. 로깅 및 모니터링
    ```go
    // pkg/security/logging.go
    type SecurityLogger struct {
        logger *zap.Logger
    }

    func NewSecurityLogger() (*SecurityLogger, error) {
        config := zap.NewProductionConfig()
        config.OutputPaths = []string{
            "security.log",
            "stdout",
        }
        
        logger, err := config.Build()
        if err != nil {
            return nil, err
        }
        
        return &SecurityLogger{
            logger: logger,
        }, nil
    }

    // 보안 이벤트 로깅
    func (l *SecurityLogger) LogSecurityEvent(eventType string, details map[string]interface{}) {
        l.logger.Info("security_event",
            zap.String("type", eventType),
            zap.Any("details", details),
            zap.String("timestamp", time.Now().UTC().Format(time.RFC3339)),
        )
    }

    // 인증 실패 로깅
    func (l *SecurityLogger) LogAuthFailure(username string, ip string, reason string) {
        l.logger.Warn("auth_failure",
            zap.String("username", username),
            zap.String("ip", ip),
            zap.String("reason", reason),
            zap.String("timestamp", time.Now().UTC().Format(time.RFC3339)),
        )
    }

    // 의심스러운 활동 로깅
    func (l *SecurityLogger) LogSuspiciousActivity(activity string, context map[string]interface{}) {
        l.logger.Warn("suspicious_activity",
            zap.String("activity", activity),
            zap.Any("context", context),
            zap.String("timestamp", time.Now().UTC().Format(time.RFC3339)),
        )
    }

    // 보안 감사 미들웨어
    func SecurityAuditMiddleware(logger *SecurityLogger) gin.HandlerFunc {
        return func(c *gin.Context) {
            start := time.Now()
            path := c.Request.URL.Path
            raw := c.Request.URL.RawQuery
            
            c.Next()
            
            // 보안 관련 엔드포인트나 에러 상태 코드에 대해서만 로깅
            if isSecurityEndpoint(path) || c.Writer.Status() >= 400 {
                logger.LogSecurityEvent("http_request", map[string]interface{}{
                    "path":         path,
                    "method":       c.Request.Method,
                    "status_code": c.Writer.Status(),
                    "client_ip":    c.ClientIP(),
                    "duration":     time.Since(start),
                    "query":        raw,
                    "user_agent":   c.Request.UserAgent(),
                })
            }
        }
    }

    func isSecurityEndpoint(path string) bool {
        securityPaths := []string{
            "/login",
            "/register",
            "/admin",
            "/api/auth",
            "/api/users",
        }
        
        for _, p := range securityPaths {
            if strings.HasPrefix(path, p) {
                return true
            }
        }
        return false
    }
    ```

8. 보안 모니터링
    1. 보안 메트릭스 수집
        ```go
        // pkg/security/metrics.go
        type SecurityMetrics struct {
            authFailures    prometheus.Counter
            loginAttempts   prometheus.Counter
            blockedRequests prometheus.Counter
            rateLimits     prometheus.Counter
            suspiciousIPs   *prometheus.CounterVec
        }

        func NewSecurityMetrics() *SecurityMetrics {
            metrics := &SecurityMetrics{
                authFailures: prometheus.NewCounter(prometheus.CounterOpts{
                    Name: "auth_failures_total",
                    Help: "Total number of authentication failures",
                }),
                loginAttempts: prometheus.NewCounter(prometheus.CounterOpts{
                    Name: "login_attempts_total",
                    Help: "Total number of login attempts",
                }),
                blockedRequests: prometheus.NewCounter(prometheus.CounterOpts{
                    Name: "blocked_requests_total",
                    Help: "Total number of blocked requests",
                }),
                rateLimits: prometheus.NewCounter(prometheus.CounterOpts{
                    Name: "rate_limits_total",
                    Help: "Total number of rate limit hits",
                }),
                suspiciousIPs: prometheus.NewCounterVec(
                    prometheus.CounterOpts{
                        Name: "suspicious_ip_requests_total",
                        Help: "Total number of suspicious requests per IP",
                    },
                    []string{"ip"},
                ),
            }

            // Prometheus에 메트릭스 등록
            prometheus.MustRegister(
                metrics.authFailures,
                metrics.loginAttempts,
                metrics.blockedRequests,
                metrics.rateLimits,
                metrics.suspiciousIPs,
            )

            return metrics
        }

        // 보안 메트릭스 미들웨어
        func SecurityMetricsMiddleware(metrics *SecurityMetrics) gin.HandlerFunc {
            return func(c *gin.Context) {
                // 로그인 시도 기록
                if c.Request.URL.Path == "/login" {
                    metrics.loginAttempts.Inc()
                }

                c.Next()

                // 요청 결과에 따른 메트릭스 수집
                if c.Writer.Status() == http.StatusUnauthorized {
                    metrics.authFailures.Inc()
                }
                if c.Writer.Status() == http.StatusTooManyRequests {
                    metrics.rateLimits.Inc()
                }
                if c.Writer.Status() == http.StatusForbidden {
                    metrics.blockedRequests.Inc()
                }
            }
        }
        ```

    2. 실시간 보안 알림
        ```go
        // pkg/security/alerts.go
        type SecurityAlerts struct {
            alertChan chan Alert
            notifiers []Notifier
        }

        type Alert struct {
            Level     string
            Message   string
            Details   map[string]interface{}
            Timestamp time.Time
        }

        type Notifier interface {
            Notify(Alert) error
        }

        // Slack 노티파이어 구현
        type SlackNotifier struct {
            webhookURL string
            client     *http.Client
        }

        func (n *SlackNotifier) Notify(alert Alert) error {
            payload := map[string]interface{}{
                "text": fmt.Sprintf("[%s] %s", alert.Level, alert.Message),
                "attachments": []map[string]interface{}{
                    {
                        "fields": formatAlertDetails(alert.Details),
                        "ts":     alert.Timestamp.Unix(),
                    },
                },
            }

            jsonData, err := json.Marshal(payload)
            if err != nil {
                return err
            }

            resp, err := n.client.Post(n.webhookURL, "application/json", bytes.NewBuffer(jsonData))
            if err != nil {
                return err
            }
            defer resp.Body.Close()

            return nil
        }

        // 이메일 노티파이어 구현
        type EmailNotifier struct {
            smtpConfig SMTPConfig
        }

        func (n *EmailNotifier) Notify(alert Alert) error {
            subject := fmt.Sprintf("[Security Alert] %s", alert.Message)
            body := formatAlertEmail(alert)

            return sendEmail(n.smtpConfig, subject, body)
        }
        ```

9. 보안 정책 적용
    1. 보안 정책 설정
        ```go
        // pkg/security/policy.go
        type SecurityPolicy struct {
            PasswordPolicy        PasswordPolicy
            SessionPolicy        SessionPolicy
            RateLimitPolicy     RateLimitPolicy
            FileUploadPolicy    FileUploadPolicy
        }

        type PasswordPolicy struct {
            MinLength           int
            RequireUppercase    bool
            RequireLowercase    bool
            RequireNumbers      bool
            RequireSpecialChars bool
            MaxAge             time.Duration
            PreventReuse       int
        }

        type SessionPolicy struct {
            Timeout            time.Duration
            MaxConcurrent      int
            RequireMFA        bool
            RefreshTokenTTL   time.Duration
        }

        type RateLimitPolicy struct {
            RequestsPerMinute  int
            BurstSize         int
            BlockDuration     time.Duration
        }

        type FileUploadPolicy struct {
            MaxFileSize       int64
            AllowedTypes      []string
            ScanForMalware   bool
            RequireEncryption bool
        }

        // 정책 검사기
        type PolicyChecker struct {
            policy SecurityPolicy
        }

        func (pc *PolicyChecker) ValidatePassword(password string) error {
            if len(password) < pc.policy.PasswordPolicy.MinLength {
                return errors.New("password too short")
            }
            
            if pc.policy.PasswordPolicy.RequireUppercase {
                if !regexp.MustCompile(`[A-Z]`).MatchString(password) {
                    return errors.New("password must contain uppercase letter")
                }
            }
            
            // 추가 검증...
            return nil
        }
        ```

    2. 정책 적용 미들웨어
        ```go
        func SecurityPolicyMiddleware(policy SecurityPolicy) gin.HandlerFunc {
            return func(c *gin.Context) {
                // 파일 업로드 정책 적용
                if isFileUpload(c.Request) {
                    if err := enforceFileUploadPolicy(c, policy.FileUploadPolicy); err != nil {
                        c.AbortWithStatusJSON(http.StatusBadRequest, gin.H{"error": err.Error()})
                        return
                    }
                }

                // 세션 정책 적용
                if err := enforceSessionPolicy(c, policy.SessionPolicy); err != nil {
                    c.AbortWithStatusJSON(http.StatusUnauthorized, gin.H{"error": err.Error()})
                    return
                }

                c.Next()
            }
        }

        func enforceFileUploadPolicy(c *gin.Context, policy FileUploadPolicy) error {
            file, err := c.FormFile("file")
            if err != nil {
                return err
            }

            if file.Size > policy.MaxFileSize {
                return errors.New("file size exceeds limit")
            }

            if !isAllowedFileType(file.Filename, policy.AllowedTypes) {
                return errors.New("file type not allowed")
            }

            if policy.ScanForMalware {
                if err := scanFileForMalware(file); err != nil {
                    return err
                }
            }

            return nil
        }
        ```

10. 보안 감사 및 리포팅
    1. 보안 감사 로그
        ```go
        // pkg/security/audit.go
        type AuditLog struct {
            ID           string                 `json:"id"`
            Timestamp    time.Time             `json:"timestamp"`
            Event        string                `json:"event"`
            UserID       string                `json:"user_id"`
            Action       string                `json:"action"`
            ResourceType string                `json:"resource_type"`
            ResourceID   string                `json:"resource_id"`
            Status       string                `json:"status"`
            Details      map[string]interface{} `json:"details"`
        }

        type AuditLogger struct {
            store  AuditStore
            logger *zap.Logger
        }

        func (a *AuditLogger) LogEvent(event AuditLog) error {
            // 감사 로그 저장
            if err := a.store.SaveAuditLog(event); err != nil {
                a.logger.Error("Failed to save audit log",
                    zap.Error(err),
                    zap.Any("event", event),
                )
                return err
            }

            // 중요 이벤트 알림
            if isSignificantEvent(event) {
                a.notifySecurityTeam(event)
            }

            return nil
        }
        ```

    2. 보안 보고서 생성
        ```go
        // pkg/security/reporting.go
        type SecurityReport struct {
            Period          time.Duration
            StartTime       time.Time
            EndTime         time.Time
            AuthStats       AuthenticationStats
            AccessStats     AccessStats
            IncidentStats   IncidentStats
            Recommendations []string
        }

        type AuthenticationStats struct {
            TotalAttempts    int
            FailedAttempts   int
            SuccessRate      float64
            UniqueFails      map[string]int
            MFAUsage         float64
        }

        func GenerateSecurityReport(period time.Duration) (*SecurityReport, error) {
            endTime := time.Now()
            startTime := endTime.Add(-period)

            report := &SecurityReport{
                Period:    period,
                StartTime: startTime,
                EndTime:   endTime,
            }

            // 통계 수집
            if err := report.collectAuthStats(); err != nil {
                return nil, err
            }

            if err := report.collectAccessStats(); err != nil {
                return nil, err
            }

            if err := report.collectIncidentStats(); err != nil {
                return nil, err
            }

            // 보안 권장사항 생성
            report.generateRecommendations()

            return report, nil
        }
        ```

## API 문서화

1. Swagger/OpenAPI 설정
    1. 기본 Swagger 설정
        ```go
        // docs/swagger.go
        package docs

        import (
            "github.com/swaggo/swag"
        )

        // @title My API
        // @version 1.0
        // @description This is a sample server for using swagger with Gin framework.
        // @termsOfService http://swagger.io/terms/

        // @contact.name API Support
        // @contact.url http://www.swagger.io/support
        // @contact.email support@swagger.io

        // @license.name Apache 2.0
        // @license.url http://www.apache.org/licenses/LICENSE-2.0.html

        // @host localhost:8080
        // @BasePath /api/v1
        // @schemes http https
        func SwaggerInfo() {
        }
        ```

    2. Swagger 라우터 설정
        ```go
        // internal/router/swagger.go
        import (
            "github.com/gin-gonic/gin"
            swaggerFiles "github.com/swaggo/files"
            ginSwagger "github.com/swaggo/gin-swagger"
            "myapp/docs"
        )

        func SetupSwagger(r *gin.Engine) {
            // 프로그래매틱하게 swagger 정보 설정
            docs.SwaggerInfo.Title = "My API"
            docs.SwaggerInfo.Description = "API Documentation"
            docs.SwaggerInfo.Version = "1.0"
            docs.SwaggerInfo.Host = "localhost:8080"
            docs.SwaggerInfo.BasePath = "/api/v1"
            docs.SwaggerInfo.Schemes = []string{"http", "https"}

            // Swagger 엔드포인트 설정
            r.GET("/swagger/*any", ginSwagger.WrapHandler(swaggerFiles.Handler))
        }
        ```

2. API 엔드포인터 문서화
    1. 사용자 관련 API
        ```go
        // internal/handlers/user_handler.go

        // @Summary Get user by ID
        // @Description Get user information by user ID
        // @Tags users
        // @Accept json
        // @Produce json
        // @Param id path int true "User ID"
        // @Success 200 {object} models.User
        // @Failure 400 {object} ErrorResponse
        // @Failure 404 {object} ErrorResponse
        // @Router /users/{id} [get]
        func (h *UserHandler) GetUser(c *gin.Context) {
            // 구현...
        }

        // @Summary Create new user
        // @Description Create a new user with the provided information
        // @Tags users
        // @Accept json
        // @Produce json
        // @Param user body CreateUserRequest true "User information"
        // @Success 201 {object} models.User
        // @Failure 400 {object} ErrorResponse
        // @Router /users [post]
        func (h *UserHandler) CreateUser(c *gin.Context) {
            // 구현...
        }

        // 요청/응답 모델 정의
        type CreateUserRequest struct {
            Username string `json:"username" binding:"required" example:"johndoe"`
            Email    string `json:"email" binding:"required,email" example:"john@example.com"`
            Password string `json:"password" binding:"required" example:"secretpass123"`
        }

        type ErrorResponse struct {
            Code    int    `json:"code" example:"400"`
            Message string `json:"message" example:"Bad Request"`
        }
        ```

    2. 인증 관련 API
        ```go
        // internal/handlers/auth_handler.go

        // @Summary User login
        // @Description Login with username and password
        // @Tags auth
        // @Accept json
        // @Produce json
        // @Param credentials body LoginRequest true "Login credentials"
        // @Success 200 {object} LoginResponse
        // @Failure 401 {object} ErrorResponse
        // @Router /auth/login [post]
        func (h *AuthHandler) Login(c *gin.Context) {
            // 구현...
        }

        // @Summary Refresh token
        // @Description Refresh access token using refresh token
        // @Tags auth
        // @Accept json
        // @Produce json
        // @Security ApiKeyAuth
        // @Param refresh_token body RefreshTokenRequest true "Refresh token"
        // @Success 200 {object} TokenResponse
        // @Failure 401 {object} ErrorResponse
        // @Router /auth/refresh [post]
        func (h *AuthHandler) RefreshToken(c *gin.Context) {
            // 구현...
        }
        ```

3. 보안 스키마 설정
    1. API 보안 설정
        ```go
        // docs/security.go

        // @SecurityDefinitions.apikey ApiKeyAuth
        // @in header
        // @name Authorization

        // @SecurityDefinitions.oauth2.password OAuth2Password
        // @tokenUrl /auth/token
        // @scope.write Grants write access
        // @scope.admin Grants admin access

        // 보안이 필요한 엔드포인트 예시
        // @Summary Get protected resource
        // @Security ApiKeyAuth
        // @Security OAuth2Password
        // @Tags protected
        // @Accept json
        // @Produce json
        // @Success 200 {object} ProtectedResponse
        // @Failure 401 {object} ErrorResponse
        // @Router /protected [get]
        func getProtectedResource(c *gin.Context) {
            // 구현...
        }
        ```

4. 모델 문서화
    1. 데이터 모델 정의
        ```go
        // internal/models/user.go

        // swagger:model User
        type User struct {
            // 사용자 ID
            // required: true
            // example: 1
            ID uint `json:"id"`

            // 사용자 이름
            // required: true
            // min length: 3
            // max length: 50
            // example: johndoe
            Username string `json:"username"`

            // 이메일 주소
            // required: true
            // format: email
            // example: john@example.com
            Email string `json:"email"`

            // 생성 시간
            // required: true
            // format: date-time
            // example: 2024-01-09T15:04:05Z
            CreatedAt time.Time `json:"created_at"`
        }

        // swagger:model Post
        type Post struct {
            // 게시글 ID
            // required: true
            // example: 1
            ID uint `json:"id"`

            // 제목
            // required: true
            // min length: 1
            // max length: 200
            // example: My First Post
            Title string `json:"title"`

            // 내용
            // required: true
            // example: This is the content of my first post.
            Content string `json:"content"`

            // 작성자 ID
            // required: true
            // example: 1
            UserID uint `json:"user_id"`

            // 작성 시간
            // required: true
            // format: date-time
            CreatedAt time.Time `json:"created_at"`
        }
        ```

5. API 버저닝 문서화
    1. 버전별 API 문서
        ```go
        // docs/v1/api.go

        // @title My API V1
        // @version 1.0
        // @description API version 1
        // @BasePath /api/v1

        // docs/v2/api.go

        // @title My API V2
        // @version 2.0
        // @description API version 2 with new features
        // @BasePath /api/v2

        // 버전별 라우터 설정
        func SetupVersionedSwagger(r *gin.Engine) {
            // V1 문서
            r.GET("/docs/v1/*any", ginSwagger.WrapHandler(swaggerFiles.Handler,
                ginSwagger.URL("/swagger/v1/doc.json"),
            ))

            // V2 문서
            r.GET("/docs/v2/*any", ginSwagger.WrapHandler(swaggerFiles.Handler,
                ginSwagger.URL("/swagger/v2/doc.json"),
            ))
        }
        ```

6. 예제 및 테스트 데이터
    1. API 예제 포함
        ```go
        // @Summary Create new post
        // @Description Create a new blog post
        // @Tags posts
        // @Accept json
        // @Produce json
        // @Param post body CreatePostRequest true "Post information"
        // @Success 201 {object} PostResponse
        // @Failure 400 {object} ErrorResponse
        // @Example {json} Request-Example:
        //     {
        //         "title": "My First Post",
        //         "content": "This is the content of my first post",
        //         "tags": ["tech", "golang"]
        //     }
        // @Example {json} Success-Response:
        //     {
        //         "id": 1,
        //         "title": "My First Post",
        //         "content": "This is the content of my first post",
        //         "author": {
        //             "id": 1,
        //             "username": "johndoe"
        //         },
        //         "created_at": "2024-01-09T15:04:05Z"
        //     }
        // @Router /posts [post]
        ```

7. 문서 생성 자동화
    1. 문서 생성 스크립트
        ```bash
        #!/bin/bash
        # scripts/generate_docs.sh

        # Swagger 문서 생성
        swag init -g cmd/server/main.go --output docs

        # 버전별 문서 생성
        swag init -g internal/router/v1/router.go --output docs/v1
        swag init -g internal/router/v2/router.go --output docs/v2

        # HTML 문서 생성
        spectacle --target-dir docs/html docs/swagger.json
        ```

    2. CI/CD 파이프라인 통합
        ```yaml
        # .github/workflows/docs.yml
        name: Generate API Documentation

        on:
        push:
            branches: [main]
            paths:
            - 'internal/**/*.go'
            - 'cmd/**/*.go'
            - 'docs/**/*'

        jobs:
        generate-docs:
            runs-on: ubuntu-latest
            steps:
            - uses: actions/checkout@v2
            
            - name: Set up Go
                uses: actions/setup-go@v2
                with:
                go-version: ^1.19
                
            - name: Install swag
                run: go install github.com/swaggo/swag/cmd/swag@latest
                
            - name: Generate Swagger docs
                run: ./scripts/generate_docs.sh
                
            - name: Deploy to Github Pages
                uses: peaceiris/actions-gh-pages@v3
                with:
                github_token: ${{ secrets.GITHUB_TOKEN }}
                publish_dir: ./docs/html
        ```

8. 문서 커스터마이징
    1. 커스텀 템플릿
        ```go
        // docs/custom/template.go
        var customTemplate = template.Must(template.New("swagger_info").Parse(`{
            "swagger": "2.0",
            "info": {
                "title": "{{.Title}}",
                "description": "{{.Description}}",
                "version": "{{.Version}}",
                "contact": {
                    "name": "{{.ContactName}}",
                    "email": "{{.ContactEmail}}"
                },
                "license": {
                    "name": "{{.LicenseName}}",
                    "url": "{{.LicenseURL}}"
                }
            },
            "host": "{{.Host}}",
            "basePath": "{{.BasePath}}",
            "schemes": {{.Schemes}},
            "securityDefinitions": {
                "ApiKeyAuth": {
                    "type": "apiKey",
                    "name": "Authorization",
                    "in": "header"
                }
            }
        }`))

        func init() {
            swag.Register(swag.Name, &swag.Spec{
                InfoInstanceName: "swagger_info",
                SwaggerTemplate: customTemplate,
            })
        }
        ```

    2. 커스텀 UI 설정
        ```go
        // internal/router/swagger_ui.go
        func SetupCustomSwaggerUI(r *gin.Engine) {
            config := &ginSwagger.Config{
                URL: "http://localhost:8080/swagger/doc.json",
                DeepLinking: true,
                DocExpansion: "none",
                Layout: "BaseLayout",
                ValidatorUrl: "",
                PersistAuthorization: true,
                Plugins: []string{
                    "TopBarPlugin",
                    "SidebarPlugin",
                },
                Presets: []string{
                    "apis",
                    "modals",
                },
            }

            r.GET("/api-docs/*any", ginSwagger.CustomWrapHandler(config, swaggerFiles.Handler))
        }
        ```

## 테스트

1. 단위 테스트
    1. 핸들러 테스트
        ```go
        // internal/handlers/user_handler_test.go
        package handlers

        import (
            "bytes"
            "encoding/json"
            "net/http"
            "net/http/httptest"
            "testing"

            "github.com/gin-gonic/gin"
            "github.com/stretchr/testify/assert"
            "github.com/stretchr/testify/mock"
        )

        type MockUserService struct {
            mock.Mock
        }

        func (m *MockUserService) GetUser(id uint) (*models.User, error) {
            args := m.Called(id)
            if args.Get(0) == nil {
                return nil, args.Error(1)
            }
            return args.Get(0).(*models.User), args.Error(1)
        }

        func TestGetUser(t *testing.T) {
            // 테스트 케이스 정의
            tests := []struct {
                name       string
                userID     string
                mockUser   *models.User
                mockError  error
                wantStatus int
                wantUser   *models.User
            }{
                {
                    name:   "유효한 사용자 ID",
                    userID: "1",
                    mockUser: &models.User{
                        ID:       1,
                        Username: "testuser",
                        Email:    "test@example.com",
                    },
                    mockError:  nil,
                    wantStatus: http.StatusOK,
                    wantUser: &models.User{
                        ID:       1,
                        Username: "testuser",
                        Email:    "test@example.com",
                    },
                },
                {
                    name:       "존재하지 않는 사용자",
                    userID:     "999",
                    mockUser:   nil,
                    mockError:  errors.New("user not found"),
                    wantStatus: http.StatusNotFound,
                    wantUser:   nil,
                },
            }

            for _, tt := range tests {
                t.Run(tt.name, func(t *testing.T) {
                    // Mock 서비스 설정
                    mockService := new(MockUserService)
                    mockService.On("GetUser", uint(1)).Return(tt.mockUser, tt.mockError)

                    // 핸들러 및 라우터 설정
                    gin.SetMode(gin.TestMode)
                    router := gin.New()
                    handler := NewUserHandler(mockService)
                    router.GET("/users/:id", handler.GetUser)

                    // 테스트 요청 생성
                    req := httptest.NewRequest("GET", "/users/"+tt.userID, nil)
                    resp := httptest.NewRecorder()

                    // 요청 처리
                    router.ServeHTTP(resp, req)

                    // 응답 검증
                    assert.Equal(t, tt.wantStatus, resp.Code)

                    if tt.wantUser != nil {
                        var gotUser models.User
                        err := json.Unmarshal(resp.Body.Bytes(), &gotUser)
                        assert.NoError(t, err)
                        assert.Equal(t, tt.wantUser, &gotUser)
                    }
                })
            }
        }
        ```

    2. 서비스 테스트
        ```go
        // internal/services/user_service_test.go
        package services

        import (
            "testing"
            "github.com/stretchr/testify/assert"
            "github.com/stretchr/testify/mock"
        )

        type MockUserRepository struct {
            mock.Mock
        }

        func (m *MockUserRepository) FindByID(id uint) (*models.User, error) {
            args := m.Called(id)
            return args.Get(0).(*models.User), args.Error(1)
        }

        func TestUserService_GetUserByID(t *testing.T) {
            // Mock 리포지토리 설정
            mockRepo := new(MockUserRepository)
            service := NewUserService(mockRepo)

            // 테스트 데이터 설정
            user := &models.User{
                ID:       1,
                Username: "testuser",
                Email:    "test@example.com",
            }

            // Mock 동작 정의
            mockRepo.On("FindByID", uint(1)).Return(user, nil)

            // 테스트 실행
            result, err := service.GetUserByID(1)

            // 결과 검증
            assert.NoError(t, err)
            assert.Equal(t, user, result)
            mockRepo.AssertExpectations(t)
        }

        func TestUserService_CreateUser(t *testing.T) {
            mockRepo := new(MockUserRepository)
            service := NewUserService(mockRepo)

            input := &CreateUserInput{
                Username: "newuser",
                Email:    "new@example.com",
                Password: "password123",
            }

            mockRepo.On("Create", mock.AnythingOfType("*models.User")).Return(nil)

            result, err := service.CreateUser(input)

            assert.NoError(t, err)
            assert.NotNil(t, result)
            assert.Equal(t, input.Username, result.Username)
            assert.Equal(t, input.Email, result.Email)
        }
        ```

2. 통합 테스트
    1. 데이터베이스 통합 테스트
        ```go
        // tests/integration/db_test.go
        package integration

        import (
            "testing"
            "github.com/stretchr/testify/suite"
            "gorm.io/gorm"
        )

        type DBTestSuite struct {
            suite.Suite
            db *gorm.DB
        }

        func (s *DBTestSuite) SetupSuite() {
            // 테스트 데이터베이스 연결 설정
            db, err := setupTestDB()
            s.Require().NoError(err)
            s.db = db
        }

        func (s *DBTestSuite) TearDownSuite() {
            // 테스트 데이터베이스 정리
            sql, err := s.db.DB()
            s.Require().NoError(err)
            sql.Close()
        }

        func (s *DBTestSuite) SetupTest() {
            // 각 테스트 전에 테이블 초기화
            s.db.Migrator().DropTable(&models.User{}, &models.Post{})
            s.db.AutoMigrate(&models.User{}, &models.Post{})
        }

        func TestDBSuite(t *testing.T) {
            suite.Run(t, new(DBTestSuite))
        }

        func (s *DBTestSuite) TestCreateUser() {
            user := &models.User{
                Username: "testuser",
                Email:    "test@example.com",
            }

            result := s.db.Create(user)
            s.Require().NoError(result.Error)
            s.NotZero(user.ID)

            // 생성된 사용자 조회
            var found models.User
            result = s.db.First(&found, user.ID)
            s.Require().NoError(result.Error)
            s.Equal(user.Username, found.Username)
        }
        ```

    2. API 통합 테스트
        ```go
        // tests/integration/api_test.go
        package integration

        import (
            "encoding/json"
            "net/http"
            "net/http/httptest"
            "testing"

            "github.com/stretchr/testify/suite"
        )

        type APITestSuite struct {
            suite.Suite
            app    *gin.Engine
            server *httptest.Server
            client *http.Client
        }

        func (s *APITestSuite) SetupSuite() {
            // API 서버 설정
            s.app = setupTestServer()
            s.server = httptest.NewServer(s.app)
            s.client = s.server.Client()
        }

        func (s *APITestSuite) TearDownSuite() {
            s.server.Close()
        }

        func TestAPISuite(t *testing.T) {
            suite.Run(t, new(APITestSuite))
        }

        func (s *APITestSuite) TestUserAPI() {
            // 사용자 생성 테스트
            createUser := map[string]interface{}{
                "username": "testuser",
                "email":    "test@example.com",
                "password": "password123",
            }

            resp, err := s.makeRequest("POST", "/api/users", createUser)
            s.Require().NoError(err)
            s.Equal(http.StatusCreated, resp.StatusCode)

            var user models.User
            s.Require().NoError(json.NewDecoder(resp.Body).Decode(&user))
            s.NotZero(user.ID)
            s.Equal(createUser["username"], user.Username)

            // 사용자 조회 테스트
            resp, err = s.makeRequest("GET", "/api/users/"+strconv.Itoa(int(user.ID)), nil)
            s.Require().NoError(err)
            s.Equal(http.StatusOK, resp.StatusCode)
        }

        func (s *APITestSuite) makeRequest(method, path string, body interface{}) (*http.Response, error) {
            var reqBody io.Reader
            if body != nil {
                jsonBody, err := json.Marshal(body)
                s.Require().NoError(err)
                reqBody = bytes.NewBuffer(jsonBody)
            }

            req, err := http.NewRequest(method, s.server.URL+path, reqBody)
            s.Require().NoError(err)

            if body != nil {
                req.Header.Set("Content-Type", "application/json")
            }

            return s.client.Do(req)
        }
        ```

3. 성능 테스트
    1. 벤치마크 테스트
        ```go
        // tests/benchmark/handlers_test.go
        package benchmark

        import (
            "net/http"
            "net/http/httptest"
            "testing"
        )

        func BenchmarkGetUser(b *testing.B) {
            // 벤치마크 설정
            router := setupRouter()
            w := httptest.NewRecorder()
            req, _ := http.NewRequest("GET", "/api/users/1", nil)

            // 벤치마크 실행
            b.ResetTimer()
            for i := 0; i < b.N; i++ {
                router.ServeHTTP(w, req)
            }
        }

        func BenchmarkUserList(b *testing.B) {
            router := setupRouter()
            
            b.Run("10_users", func(b *testing.B) {
                benchmarkUserList(b, router, 10)
            })
            
            b.Run("100_users", func(b *testing.B) {
                benchmarkUserList(b, router, 100)
            })
            
            b.Run("1000_users", func(b *testing.B) {
                benchmarkUserList(b, router, 1000)
            })
        }

        func benchmarkUserList(b *testing.B, router *gin.Engine, count int) {
            // 테스트 데이터 준비
            setupTestData(count)
            
            w := httptest.NewRecorder()
            req, _ := http.NewRequest("GET", "/api/users", nil)
            
            b.ResetTimer()
            for i := 0; i < b.N; i++ {
                router.ServeHTTP(w, req)
            }
        }
        ```

    2. 부하 테스트
        ```go
        // tests/load/api_test.go
        package load

        import (
            "fmt"
            "net/http"
            "sync"
            "testing"
            "time"
        )

        func TestConcurrentUsers(t *testing.T) {
            if testing.Short() {
                t.Skip("스킵: 부하 테스트")
            }

            tests := []struct {
                name         string
                concurrency  int
                requests    int
                expectedAvg time.Duration
            }{
                {
                    name:        "10_concurrent_users",
                    concurrency: 10,
                    requests:    100,
                    expectedAvg: 100 * time.Millisecond,
                },
                {
                    name:        "50_concurrent_users",
                    concurrency: 50,
                    requests:    100,
                    expectedAvg: 200 * time.Millisecond,
                },
            }

            for _, tt := range tests {
                t.Run(tt.name, func(t *testing.T) {
                    results := make(chan time.Duration, tt.concurrency*tt.requests)
                    var wg sync.WaitGroup

                    // 동시 요청 실행
                    for i := 0; i < tt.concurrency; i++ {
                        wg.Add(1)
                        go func() {
                            defer wg.Done()
                            for j := 0; j < tt.requests; j++ {
                                start := time.Now()
                                resp, err := http.Get("http://localhost:8080/api/users")
                                if err != nil {
                                    t.Error(err)
                                    return
                                }
                                resp.Body.Close()
                                results <- time.Since(start)
                            }
                        }()
                    }

                    wg.Wait()
                    close(results)

                    // 결과 분석
                    var total time.Duration
                    var count int
                    for dur := range results {
                        total += dur
                        count++
                    }

                    avg := total / time.Duration(count)
                    if avg > tt.expectedAvg {
                        t.Errorf("평균 응답 시간이 너무 김: got %v, want < %v", avg, tt.expectedAvg)
                    }
                })
            }
        }
        ```

4. 모의 객체
    1. 서비스 모의 객체
        ```go
        // internal/mocks/user_service_mock.go
        package mocks

        type MockUserService struct {
        mock.Mock
        }

        func (m *MockUserService) GetUser(id uint) (*models.User, error) {
        args := m.Called(id)
        if args.Get(0) == nil {
            return nil, args.Error(1)
        }
        return args.Get(0).(*models.User), args.Error(1)
        }

        func (m *MockUserService) CreateUser(input *CreateUserInput) (*models.User, error) {
        args := m.Called(input)
        if args.Get(0) == nil {
            return nil, args.Error(1)
        }
        return args.Get(0).(*models.User), args.Error(1)
        }

        // 저장소 모의 객체
        type MockUserRepository struct {
        mock.Mock
        }

        func (m *MockUserRepository) FindByID(id uint) (*models.User, error) {
        args := m.Called(id)
        if args.Get(0) == nil {
            return nil, args.Error(1)
        }
        return args.Get(0).(*models.User), args.Error(1)
        }

        func (m *MockUserRepository) Create(user *models.User) error {
        args := m.Called(user)
        return args.Error(0)
        }

        func (m *MockUserRepository) Update(user *models.User) error {
        args := m.Called(user)
        return args.Error(0)
        }

        func (m *MockUserRepository) Delete(id uint) error {
        args := m.Called(id)
        return args.Error(0)
        }

        // 캐시 모의 객체
        type MockCache struct {
        mock.Mock
        }

        func (m *MockCache) Get(key string) (interface{}, error) {
        args := m.Called(key)
        return args.Get(0), args.Error(1)
        }

        func (m *MockCache) Set(key string, value interface{}, expiration time.Duration) error {
        args := m.Called(key, value, expiration)
        return args.Error(0)
        }

        func (m *MockCache) Delete(key string) error {
        args := m.Called(key)
        return args.Error(0)
        }

        // 외부 서비스 모의 객체
        type MockExternalService struct {
        mock.Mock
        }

        func (m *MockExternalService) Request(method, url string, body interface{}) (*http.Response, error) {
        args := m.Called(method, url, body)
        return args.Get(0).(*http.Response), args.Error(1)
        }
        ```

5. 테스트 헬퍼 및 유틸리티
    ```go
    // tests/helpers/test_helpers.go
    package helpers

    import (
        "encoding/json"
        "net/http"
        "net/http/httptest"
        "testing"
    )

    // HTTP 테스트 헬퍼
    func ExecuteRequest(r http.Handler, req *http.Request) *httptest.ResponseRecorder {
        rr := httptest.NewRecorder()
        r.ServeHTTP(rr, req)
        return rr
    }

    // JSON 응답 검증 헬퍼
    func CheckResponseCode(t *testing.T, expected, actual int) {
        if expected != actual {
            t.Errorf("Expected response code %d. Got %d\n", expected, actual)
        }
    }

    // JSON 변환 헬퍼
    func ParseResponse(response *httptest.ResponseRecorder) (map[string]interface{}, error) {
        var parsed map[string]interface{}
        err := json.NewDecoder(response.Body).Decode(&parsed)
        return parsed, err
    }

    // 데이터베이스 테스트 헬퍼
    type TestDB struct {
        DB *gorm.DB
    }

    func NewTestDB() (*TestDB, error) {
        db, err := setupTestDatabase()
        if err != nil {
            return nil, err
        }
        return &TestDB{DB: db}, nil
    }

    func (tdb *TestDB) Clear() error {
        tables := []interface{}{&models.User{}, &models.Post{}}
        for _, table := range tables {
            err := tdb.DB.Where("1 = 1").Delete(table).Error
            if err != nil {
                return err
            }
        }
        return nil
    }

    // 인증 테스트 헬퍼
    func GenerateTestToken(userID uint) string {
        claims := jwt.MapClaims{
            "user_id": userID,
            "exp":     time.Now().Add(time.Hour * 24).Unix(),
        }
        token := jwt.NewWithClaims(jwt.SigningMethodHS256, claims)
        tokenString, _ := token.SignedString([]byte("test_secret"))
        return tokenString
    }
    ```

6. 테스트 커버리지 분석
    ```go
    // scripts/coverage.go
    package main

    import (
        "encoding/json"
        "fmt"
        "os/exec"
    )

    type Coverage struct {
        Packages []PackageCoverage `json:"packages"`
        Total    float64           `json:"total"`
    }

    type PackageCoverage struct {
        Name     string  `json:"name"`
        Coverage float64 `json:"coverage"`
    }

    func main() {
        // 테스트 실행 및 커버리지 생성
        cmd := exec.Command("go", "test", "./...", "-coverprofile=coverage.out")
        if err := cmd.Run(); err != nil {
            fmt.Printf("테스트 실행 실패: %v\n", err)
            return
        }

        // HTML 보고서 생성
        cmd = exec.Command("go", "tool", "cover", "-html=coverage.out", "-o", "coverage.html")
        if err := cmd.Run(); err != nil {
            fmt.Printf("HTML 보고서 생성 실패: %v\n", err)
            return
        }

        // 커버리지 분석
        analyzeCoverage("coverage.out")
    }

    func analyzeCoverage(filename string) {
        cmd := exec.Command("go", "tool", "cover", "-func=coverage.out")
        output, err := cmd.Output()
        if err != nil {
            fmt.Printf("커버리지 분석 실패: %v\n", err)
            return
        }
        fmt.Printf("Coverage Analysis:\n%s\n", string(output))
    }
    ```

7. CI/CD 통합
    ```yaml
    # .github/workflows/test.yml
    name: Tests

    on: [push, pull_request]

    jobs:
    test:
        runs-on: ubuntu-latest
        
        steps:
        - uses: actions/checkout@v2

        - name: Set up Go
        uses: actions/setup-go@v2
        with:
            go-version: ^1.19

        - name: Install dependencies
        run: go mod download

        - name: Run tests with coverage
        run: |
            go test ./... -coverprofile=coverage.out -covermode=atomic
            go tool cover -func=coverage.out

        - name: Upload coverage report
        uses: codecov/codecov-action@v2
        with:
            file: ./coverage.out
            flags: unittests
    ```

8. 테스트 시나리오 자동화
    1. 테스트 시나리오 정의
        ```go
        // tests/scenarios/user_scenarios_test.go
        package scenarios

        import (
            "testing"
            "github.com/stretchr/testify/suite"
        )

        type UserScenarioSuite struct {
            suite.Suite
            app *gin.Engine
        }

        func (s *UserScenarioSuite) SetupSuite() {
            s.app = setupTestApp()
        }

        func (s *UserScenarioSuite) TestUserLifecycle() {
            // 1. 사용자 등록
            user := s.createUser()
            s.NotEmpty(user.ID)

            // 2. 로그인
            token := s.loginUser(user)
            s.NotEmpty(token)

            // 3. 프로필 업데이트
            s.updateUserProfile(user.ID, token)

            // 4. 게시물 작성
            post := s.createPost(user.ID, token)
            s.NotEmpty(post.ID)

            // 5. 게시물 조회
            s.verifyPost(post.ID)

            // 6. 사용자 삭제
            s.deleteUser(user.ID, token)
        }

        func (s *UserScenarioSuite) createUser() *models.User {
            payload := map[string]interface{}{
                "username": "testuser",
                "email":    "test@example.com",
                "password": "password123",
            }

            response := s.makeRequest("POST", "/api/users", payload, "")
            s.Equal(http.StatusCreated, response.Code)

            var user models.User
            s.Require().NoError(json.NewDecoder(response.Body).Decode(&user))
            return &user
        }

        func (s *UserScenarioSuite) loginUser(user *models.User) string {
            payload := map[string]interface{}{
                "email":    user.Email,
                "password": "password123",
            }

            response := s.makeRequest("POST", "/api/auth/login", payload, "")
            s.Equal(http.StatusOK, response.Code)

            var result map[string]string
            s.Require().NoError(json.NewDecoder(response.Body).Decode(&result))
            return result["token"]
        }

        func (s *UserScenarioSuite) updateUserProfile(userID uint, token string) {
            payload := map[string]interface{}{
                "bio": "Updated bio",
            }

            response := s.makeRequest("PUT", fmt.Sprintf("/api/users/%d/profile", userID), payload, token)
            s.Equal(http.StatusOK, response.Code)
        }

        func (s *UserScenarioSuite) createPost(userID uint, token string) *models.Post {
            payload := map[string]interface{}{
                "title":   "Test Post",
                "content": "This is a test post",
            }

            response := s.makeRequest("POST", "/api/posts", payload, token)
            s.Equal(http.StatusCreated, response.Code)

            var post models.Post
            s.Require().NoError(json.NewDecoder(response.Body).Decode(&post))
            return &post
        }

        func (s *UserScenarioSuite) verifyPost(postID uint) {
            response := s.makeRequest("GET", fmt.Sprintf("/api/posts/%d", postID), nil, "")
            s.Equal(http.StatusOK, response.Code)

            var post models.Post
            s.Require().NoError(json.NewDecoder(response.Body).Decode(&post))
            s.Equal(postID, post.ID)
        }

        func (s *UserScenarioSuite) deleteUser(userID uint, token string) {
            response := s.makeRequest("DELETE", fmt.Sprintf("/api/users/%d", userID), nil, token)
            s.Equal(http.StatusOK, response.Code)
        }

        func (s *UserScenarioSuite) makeRequest(method, path string, body interface{}, token string) *httptest.ResponseRecorder {
            var reqBody io.Reader
            if body != nil {
                jsonBody, err := json.Marshal(body)
                s.Require().NoError(err)
                reqBody = bytes.NewBuffer(jsonBody)
            }

            req := httptest.NewRequest(method, path, reqBody)
            if token != "" {
                req.Header.Set("Authorization", "Bearer "+token)
            }
            if body != nil {
                req.Header.Set("Content-Type", "application/json")
            }

            w := httptest.NewRecorder()
            s.app.ServeHTTP(w, req)
            return w
        }
        ```

9. 테스트 문서화
    1. 테스트 문서 자동 생성
        ```go
        // tests/docs/test_docs.go
        package docs

        import (
            "fmt"
            "go/ast"
            "go/parser"
            "go/token"
            "os"
            "path/filepath"
            "strings"
        )

        type TestDoc struct {
            Package     string
            TestName    string
            Description string
            Cases       []TestCase
        }

        type TestCase struct {
            Name        string
            Description string
            Setup       string
            Assertions  []string
        }

        func GenerateTestDocs(dir string) ([]TestDoc, error) {
            var docs []TestDoc
            err := filepath.Walk(dir, func(path string, info os.FileInfo, err error) error {
                if err != nil {
                    return err
                }

                if !strings.HasSuffix(info.Name(), "_test.go") {
                    return nil
                }

                doc, err := parseTestFile(path)
                if err != nil {
                    return err
                }
                docs = append(docs, doc)
                return nil
            })

            return docs, err
        }

        func parseTestFile(filePath string) (TestDoc, error) {
            fset := token.NewFileSet()
            node, err := parser.ParseFile(fset, filePath, nil, parser.ParseComments)
            if err != nil {
                return TestDoc{}, err
            }

            doc := TestDoc{
                Package: node.Name.Name,
            }

            ast.Inspect(node, func(n ast.Node) bool {
                fn, ok := n.(*ast.FuncDecl)
                if !ok || !strings.HasPrefix(fn.Name.Name, "Test") {
                    return true
                }

                testCase := parseTestCase(fn)
                doc.Cases = append(doc.Cases, testCase)
                return true
            })

            return doc, nil
        }

        func parseTestCase(fn *ast.FuncDecl) TestCase {
            testCase := TestCase{
                Name: fn.Name.Name,
            }

            if fn.Doc != nil {
                testCase.Description = fn.Doc.Text()
            }

            return testCase
        }
        ```

## 모니터링과 로깅

1. 로깅 설정
    1. Zap Logger 설정
        ```go
        // pkg/logger/zap.go
        package logger

        import (
            "os"
            "time"

            "go.uber.org/zap"
            "go.uber.org/zap/zapcore"
        )

        type Logger struct {
            *zap.Logger
        }

        func NewLogger(env string) (*Logger, error) {
            var config zap.Config

            if env == "production" {
                config = zap.NewProductionConfig()
                config.EncoderConfig.TimeKey = "timestamp"
                config.EncoderConfig.EncodeTime = zapcore.ISO8601TimeEncoder
            } else {
                config = zap.NewDevelopmentConfig()
                config.EncoderConfig.EncodeLevel = zapcore.CapitalColorLevelEncoder
            }

            // 로그 파일 설정
            logFile, err := os.OpenFile(
                "app.log",
                os.O_APPEND|os.O_CREATE|os.O_WRONLY,
                0644,
            )
            if err != nil {
                return nil, err
            }

            // 콘솔과 파일 모두에 로깅
            core := zapcore.NewTee(
                zapcore.NewCore(
                    zapcore.NewJSONEncoder(config.EncoderConfig),
                    zapcore.AddSync(logFile),
                    config.Level,
                ),
                zapcore.NewCore(
                    zapcore.NewConsoleEncoder(config.EncoderConfig),
                    zapcore.AddSync(os.Stdout),
                    config.Level,
                ),
            )

            logger := zap.New(core, zap.AddCaller(), zap.AddStacktrace(zap.ErrorLevel))

            return &Logger{logger}, nil
        }

        // 로깅 미들웨어
        func LoggerMiddleware(logger *Logger) gin.HandlerFunc {
            return func(c *gin.Context) {
                start := time.Now()
                path := c.Request.URL.Path
                query := c.Request.URL.RawQuery

                c.Next()

                logger.Info("request completed",
                    zap.String("path", path),
                    zap.String("query", query),
                    zap.String("ip", c.ClientIP()),
                    zap.String("method", c.Request.Method),
                    zap.Int("status", c.Writer.Status()),
                    zap.Duration("latency", time.Since(start)),
                    zap.Int("size", c.Writer.Size()),
                    zap.String("user-agent", c.Request.UserAgent()),
                )
            }
        }
        ```

    2. 로그 로테이션
        ```go
        // pkg/logger/rotation.go
        package logger

        import (
            "github.com/natefinch/lumberjack"
            "go.uber.org/zap/zapcore"
        )

        func getLogWriter() zapcore.WriteSyncer {
            lumberJackLogger := &lumberjack.Logger{
                Filename:   "app.log",
                MaxSize:    10,    // 메가바이트
                MaxBackups: 5,     // 유지할 이전 로그 파일 수
                MaxAge:    30,     // 일
                Compress:  true,   // 로그 파일 압축
            }
            return zapcore.AddSync(lumberJackLogger)
        }

        func getEncoder() zapcore.Encoder {
            encoderConfig := zap.NewProductionEncoderConfig()
            encoderConfig.TimeKey = "timestamp"
            encoderConfig.EncodeTime = zapcore.ISO8601TimeEncoder
            encoderConfig.StacktraceKey = ""
            return zapcore.NewJSONEncoder(encoderConfig)
        }
        ```

2. 프로메테우스 메트릭스
    1. 메트릭스 설정
        ```go
        // pkg/metrics/prometheus.go
        package metrics

        import (
            "github.com/prometheus/client_golang/prometheus"
            "github.com/prometheus/client_golang/prometheus/promauto"
        )

        var (
            RequestsTotal = promauto.NewCounterVec(
                prometheus.CounterOpts{
                    Name: "http_requests_total",
                    Help: "Total number of HTTP requests",
                },
                []string{"method", "path", "status"},
            )

            RequestDuration = promauto.NewHistogramVec(
                prometheus.HistogramOpts{
                    Name:    "http_request_duration_seconds",
                    Help:    "HTTP request latencies in seconds",
                    Buckets: prometheus.DefBuckets,
                },
                []string{"method", "path"},
            )

            ResponseSize = promauto.NewHistogramVec(
                prometheus.HistogramOpts{
                    Name:    "http_response_size_bytes",
                    Help:    "HTTP response sizes in bytes",
                    Buckets: prometheus.ExponentialBuckets(100, 10, 8),
                },
                []string{"method", "path"},
            )

            ActiveRequests = promauto.NewGauge(prometheus.GaugeOpts{
                Name: "http_active_requests",
                Help: "Number of active HTTP requests",
            })

            DatabaseConnections = promauto.NewGauge(prometheus.GaugeOpts{
                Name: "database_connections",
                Help: "Number of active database connections",
            })
        )

        // 메트릭스 미들웨어
        func MetricsMiddleware() gin.HandlerFunc {
            return func(c *gin.Context) {
                start := time.Now()
                path := c.FullPath()
                
                ActiveRequests.Inc()
                defer ActiveRequests.Dec()

                c.Next()

                status := strconv.Itoa(c.Writer.Status())
                duration := time.Since(start).Seconds()

                RequestsTotal.WithLabelValues(c.Request.Method, path, status).Inc()
                RequestDuration.WithLabelValues(c.Request.Method, path).Observe(duration)
                ResponseSize.WithLabelValues(c.Request.Method, path).Observe(float64(c.Writer.Size()))
            }
        }
        ```

3. Grafana 대시보드
    1. 대시보드 설정
        ```json
        {
            "annotations": {
                "list": []
            },
            "editable": true,
            "gnetId": null,
            "graphTooltip": 0,
            "id": 1,
            "links": [],
            "panels": [
                {
                "alert": {
                    "conditions": [
                    {
                        "evaluator": {
                        "params": [
                            5
                        ],
                        "type": "gt"
                        },
                        "operator": {
                        "type": "and"
                        },
                        "query": {
                        "params": [
                            "A",
                            "5m",
                            "now"
                        ]
                        },
                        "reducer": {
                        "params": [],
                        "type": "avg"
                        },
                        "type": "query"
                    }
                    ],
                    "executionErrorState": "alerting",
                    "frequency": "60s",
                    "handler": 1,
                    "name": "Request Rate",
                    "noDataState": "no_data",
                    "notifications": []
                },
                "aliasColors": {},
                "bars": false,
                "dashLength": 10,
                "dashes": false,
                "datasource": "Prometheus",
                "fill": 1,
                "gridPos": {
                    "h": 9,
                    "w": 12,
                    "x": 0,
                    "y": 0
                },
                "id": 2,
                "legend": {
                    "avg": false,
                    "current": false,
                    "max": false,
                    "min": false,
                    "show": true,
                    "total": false,
                    "values": false
                },
                "lines": true,
                "linewidth": 1,
                "nullPointMode": "null",
                "percentage": false,
                "pointradius": 2,
                "points": false,
                "renderer": "flot",
                "seriesOverrides": [],
                "spaceLength": 10,
                "stack": false,
                "steppedLine": false,
                "targets": [
                    {
                    "expr": "rate(http_requests_total[5m])",
                    "refId": "A"
                    }
                ],
                "thresholds": [],
                "timeFrom": null,
                "timeRegions": [],
                "timeShift": null,
                "title": "Request Rate",
                "tooltip": {
                    "shared": true,
                    "sort": 0,
                    "value_type": "individual"
                },
                "type": "graph",
                "xaxis": {
                    "buckets": null,
                    "mode": "time",
                    "name": null,
                    "show": true,
                    "values": []
                },
                "yaxes": [
                    {
                    "format": "short",
                    "label": null,
                    "logBase": 1,
                    "max": null,
                    "min": null,
                    "show": true
                    },
                    {
                    "format": "short",
                    "label": null,
                    "logBase": 1,
                    "max": null,
                    "min": null,
                    "show": true
                    }
                ],
                "yaxis": {
                    "align": false,
                    "alignLevel": null
                }
                }
            ],
            "schemaVersion": 22,
            "style": "dark",
            "tags": [],
            "templating": {
                "list": []
            },
            "time": {
                "from": "now-6h",
                "to": "now"
            },
            "timepicker": {},
            "timezone": "",
            "title": "API Monitoring",
            "uid": "api_monitoring",
            "version": 1
        }
        ```

4. 트레이싱
    1. Jaeger 트레이싱 설정
        ```go
        // pkg/tracing/jaeger.go
        package tracing

        import (
            "io"
            "github.com/opentracing/opentracing-go"
            "github.com/uber/jaeger-client-go"
            "github.com/uber/jaeger-client-go/config"
        )

        func InitTracer(serviceName string) (opentracing.Tracer, io.Closer) {
            cfg := &config.Configuration{
                ServiceName: serviceName,
                Sampler: &config.SamplerConfig{
                    Type:  jaeger.SamplerTypeConst,
                    Param: 1,
                },
                Reporter: &config.ReporterConfig{
                    LogSpans: true,
                },
            }
            tracer, closer, err := cfg.NewTracer(config.Logger(jaeger.StdLogger))
            if err != nil {
                panic(err)
            }
            return tracer, closer
        }

        // 트레이싱 미들웨어
        func TracingMiddleware(tracer opentracing.Tracer) gin.HandlerFunc {
            return func(c *gin.Context) {
                spCtx, _ := tracer.Extract(
                    opentracing.HTTPHeaders,
                    opentracing.HTTPHeadersCarrier(c.Request.Header),
                )

                sp := tracer.StartSpan(
                    c.Request.URL.Path,
                    opentracing.ChildOf(spCtx),
                )
                defer sp.Finish()

                // 컨텍스트에 span 추가
                c.Set("span", sp)

                c.Next()

                // span에 응답 정보 추가
                sp.SetTag("http.status_code", c.Writer.Status())
                sp.SetTag("http.method", c.Request.Method)
                sp.SetTag("http.url", c.Request.URL.Path)
            }
        }
        ```

5. 알림 설정
    1. 알림 관리자
        ```go
        // pkg/alerts/manager.go
        package alerts

        import (
            "bytes"
            "encoding/json"
            "net/http"
        )

        type AlertManager struct {
            slackWebhook  string
            emailConfig   EmailConfig
            alertChannels []AlertChannel
        }

        type AlertChannel interface {
            Send(alert Alert) error
        }

        type Alert struct {
            Level     string                 `json:"level"`
            Message   string                 `json:"message"`
            Details   map[string]interface{} `json:"details"`
            Timestamp string                 `json:"timestamp"`
        }

        func NewAlertManager(slackWebhook string, emailConfig EmailConfig) *AlertManager {
            return &AlertManager{
                slackWebhook:  slackWebhook,
                emailConfig:   emailConfig,
                alertChannels: make([]AlertChannel, 0),
            }
        }

        func (am *AlertManager) AddChannel(channel AlertChannel) {
            am.alertChannels = append(am.alertChannels, channel)
        }

        // Slack 알림
        type SlackAlert struct {
            webhook string
        }

        func (sa *SlackAlert) Send(alert Alert) error {
            payload := map[string]interface{}{
                "text": fmt.Sprintf("[%s] %s", alert.Level, alert.Message),
                "attachments": []map[string]interface{}{
                    {
                        "fields": formatAlertDetails(alert.Details),
                        "color":  getAlertColor(alert.Level),
                    },
                },
            }

            jsonData, err := json.Marshal(payload)
            if err != nil {
                return err
            }

            resp, err := http.Post(sa.webhook, "application/json", bytes.NewBuffer(jsonData))
            if err != nil {
                return err
            }
            defer resp.Body.Close()

            return nil
        }

        // 이메일 알림
        type EmailAlert struct {
            config EmailConfig
        }

        func (ea *EmailAlert) Send(alert Alert) error {
            subject := fmt.Sprintf("[%s] Alert: %s", alert.Level, alert.Message)
            body := formatEmailBody(alert)
            
            return sendEmail(ea.config, subject, body)
        }

        func formatEmailBody(alert Alert) string {
            var buf bytes.Buffer
            buf.WriteString(fmt.Sprintf("Alert Level: %s\n", alert.Level))
            buf.WriteString(fmt.Sprintf("Message: %s\n", alert.Message))
            buf.WriteString("\nDetails:\n")
            
            for k, v := range alert.Details {
                buf.WriteString(fmt.Sprintf("%s: %v\n", k, v))
            }
            
            return buf.String()
        }
        ```

6. 헬스체크
    1. 헬스체크 엔드포인트
        ```go
        // internal/handlers/health.go
        package handlers

        type HealthChecker interface {
            Check() error
            Name() string
        }

        type HealthService struct {
            checkers []HealthChecker
        }

        func NewHealthService(checkers ...HealthChecker) *HealthService {
            return &HealthService{checkers: checkers}
        }

        func (h *HealthService) CheckHealth(c *gin.Context) {
            details := make(map[string]interface{})
            status := "healthy"

            for _, checker := range h.checkers {
                if err := checker.Check(); err != nil {
                    details[checker.Name()] = map[string]string{
                        "status":  "unhealthy",
                        "message": err.Error(),
                    }
                    status = "unhealthy"
                } else {
                    details[checker.Name()] = map[string]string{
                        "status": "healthy",
                    }
                }
            }

            health := HealthCheck{
                Status:  status,
                Details: details,
            }

            c.JSON(http.StatusOK, health)
        }

        // 데이터베이스 헬스체커
        type DBHealthChecker struct {
            db *gorm.DB
        }

        func (d *DBHealthChecker) Name() string {
            return "database"
        }

        func (d *DBHealthChecker) Check() error {
            sqlDB, err := d.db.DB()
            if err != nil {
                return err
            }
            return sqlDB.Ping()
        }

        // Redis 헬스체커
        type RedisHealthChecker struct {
            client *redis.Client
        }

        func (r *RedisHealthChecker) Name() string {
            return "redis"
        }

        func (r *RedisHealthChecker) Check() error {
            return r.client.Ping(context.Background()).Err()
        }

        // 외부 서비스 헬스체커
        type ServiceHealthChecker struct {
            name string
            url  string
        }

        func (s *ServiceHealthChecker) Name() string {
            return s.name
        }

        func (s *ServiceHealthChecker) Check() error {
            resp, err := http.Get(s.url)
            if err != nil {
                return err
            }
            defer resp.Body.Close()

            if resp.StatusCode != http.StatusOK {
                return fmt.Errorf("service returned status: %d", resp.StatusCode)
            }
            return nil
        }
        ```

7. 메트릭스 수집기
    ```go
    // pkg/metrics/collector.go
    package metrics

    type MetricsCollector struct {
        metrics map[string]prometheus.Collector
    }

    func NewMetricsCollector() *MetricsCollector {
        return &MetricsCollector{
            metrics: make(map[string]prometheus.Collector),
        }
    }

    // 시스템 메트릭스
    func (mc *MetricsCollector) RegisterSystemMetrics() {
        mc.metrics["memory_usage"] = prometheus.NewGauge(prometheus.GaugeOpts{
            Name: "system_memory_usage_bytes",
            Help: "Current memory usage in bytes",
        })

        mc.metrics["cpu_usage"] = prometheus.NewGauge(prometheus.GaugeOpts{
            Name: "system_cpu_usage_percent",
            Help: "Current CPU usage in percentage",
        })

        mc.metrics["goroutines"] = prometheus.NewGauge(prometheus.GaugeOpts{
            Name: "system_goroutines_count",
            Help: "Number of running goroutines",
        })

        // 모든 메트릭스 등록
        for _, metric := range mc.metrics {
            prometheus.MustRegister(metric)
        }
    }

    // 비즈니스 메트릭스
    func (mc *MetricsCollector) RegisterBusinessMetrics() {
        mc.metrics["active_users"] = prometheus.NewGauge(prometheus.GaugeOpts{
            Name: "business_active_users",
            Help: "Number of active users",
        })

        mc.metrics["daily_transactions"] = prometheus.NewCounter(prometheus.CounterOpts{
            Name: "business_daily_transactions_total",
            Help: "Total number of daily transactions",
        })

        mc.metrics["order_value"] = prometheus.NewHistogram(prometheus.HistogramOpts{
            Name:    "business_order_value_dollars",
            Help:    "Distribution of order values",
            Buckets: []float64{10, 50, 100, 500, 1000, 5000},
        })

        // 모든 메트릭스 등록
        for _, metric := range mc.metrics {
            prometheus.MustRegister(metric)
        }
    }

    // 메트릭스 업데이트
    func (mc *MetricsCollector) UpdateMetrics() {
        go func() {
            for {
                // 시스템 메트릭스 업데이트
                mc.updateSystemMetrics()
                // 비즈니스 메트릭스 업데이트
                mc.updateBusinessMetrics()
                
                time.Sleep(time.Second * 15)
            }
        }()
    }

    func (mc *MetricsCollector) updateSystemMetrics() {
        // 메모리 사용량 업데이트
        var mem runtime.MemStats
        runtime.ReadMemStats(&mem)
        mc.metrics["memory_usage"].(prometheus.Gauge).Set(float64(mem.Alloc))

        // 고루틴 수 업데이트
        mc.metrics["goroutines"].(prometheus.Gauge).Set(float64(runtime.NumGoroutine()))

        // CPU 사용량 업데이트 (예시)
        // 실제 구현에서는 OS 특정 방식으로 CPU 사용량을 얻어야 함
    }

    func (mc *MetricsCollector) updateBusinessMetrics() {
        // 비즈니스 메트릭스 업데이트 로직 구현
        // 실제 구현에서는 데이터베이스나 캐시에서 데이터를 조회해야 함
    }
    ```

8. 로깅 및 모니터링 통합
    1. 통합 모니터링 설정
        ```go
        // pkg/monitoring/setup.go
        package monitoring

        import (
            "context"
            "time"
        )

        type MonitoringService struct {
            logger     *Logger
            metrics    *MetricsCollector
            tracer     *Tracer
            alerts     *AlertManager
            health     *HealthService
            ctx        context.Context
            cancelFunc context.CancelFunc
        }

        func NewMonitoringService(config MonitoringConfig) (*MonitoringService, error) {
            ctx, cancel := context.WithCancel(context.Background())
            
            service := &MonitoringService{
                ctx:        ctx,
                cancelFunc: cancel,
            }
            
            // 로거 초기화
            logger, err := NewLogger(config.LogConfig)
            if err != nil {
                return nil, err
            }
            service.logger = logger
            
            // 메트릭스 초기화
            service.metrics = NewMetricsCollector()
            service.metrics.RegisterSystemMetrics()
            service.metrics.RegisterBusinessMetrics()
            
            // 트레이서 초기화
            tracer, err := NewTracer(config.TracingConfig)
            if err != nil {
                return nil, err
            }
            service.tracer = tracer
            
            // 알림 관리자 초기화
            service.alerts = NewAlertManager(config.AlertConfig)
            
            // 헬스 체크 초기화
            service.health = NewHealthService(config.HealthCheckers...)
            
            return service, nil
        }

        // 통합 미들웨어
        func (ms *MonitoringService) Middleware() gin.HandlerFunc {
            return func(c *gin.Context) {
                start := time.Now()
                path := c.Request.URL.Path
                
                // 트레이싱 시작
                span := ms.tracer.StartSpan(path)
                defer span.Finish()
                
                // 컨텍스트에 span 추가
                c.Set("span", span)
                
                // 메트릭스 수집 시작
                ms.metrics.RequestStarted(path)
                
                // 다음 핸들러 실행
                c.Next()
                
                // 요청 완료 후 메트릭스 업데이트
                duration := time.Since(start)
                status := c.Writer.Status()
                
                ms.metrics.RequestCompleted(path, status, duration)
                
                // 로깅
                ms.logger.Info("request completed",
                    "path", path,
                    "method", c.Request.Method,
                    "status", status,
                    "duration", duration,
                    "ip", c.ClientIP(),
                )
                
                // 에러 발생 시 알림
                if status >= 500 {
                    ms.alerts.Send(Alert{
                        Level:   "error",
                        Message: "Server error occurred",
                        Details: map[string]interface{}{
                            "path":   path,
                            "status": status,
                            "error":  c.Errors.String(),
                        },
                    })
                }
            }
        }

        // 지표 수집 주기 설정
        func (ms *MonitoringService) StartMetricsCollection() {
            go func() {
                ticker := time.NewTicker(15 * time.Second)
                defer ticker.Stop()
                
                for {
                    select {
                    case <-ticker.C:
                        ms.metrics.UpdateSystemMetrics()
                        ms.metrics.UpdateBusinessMetrics()
                    case <-ms.ctx.Done():
                        return
                    }
                }
            }()
        }

        // 정리
        func (ms *MonitoringService) Cleanup() {
            ms.cancelFunc()
            ms.tracer.Close()
            ms.logger.Sync()
        }
        ```

    2. 설정 구조체
        ```go
        // pkg/monitoring/config.go
        type MonitoringConfig struct {
            LogConfig     LogConfig
            TracingConfig TracingConfig
            AlertConfig   AlertConfig
            HealthCheckers []HealthChecker
            MetricsConfig MetricsConfig
        }

        type LogConfig struct {
            Level      string
            OutputPath string
            Encoding   string
        }

        type TracingConfig struct {
            ServiceName  string
            AgentHost    string
            AgentPort    string
            SampleRate   float64
        }

        type AlertConfig struct {
            SlackWebhook   string
            EmailSettings  EmailSettings
            AlertLevels    map[string]AlertLevel
        }

        type MetricsConfig struct {
            PrometheusPort     int
            CollectionInterval time.Duration
            CustomMetrics      []MetricDefinition
        }

        type MetricDefinition struct {
            Name       string
            Help       string
            Type       string
            Labels     []string
        }
        ```

    3. Docker Compose 통합 설정
        ```yml
        # docker-compose.monitoring.yml
        version: '3.8'

        services:
        prometheus:
            image: prom/prometheus:latest
            volumes:
            - ./prometheus.yml:/etc/prometheus/prometheus.yml
            ports:
            - "9090:9090"
            networks:
            - monitoring

        grafana:
            image: grafana/grafana:latest
            depends_on:
            - prometheus
            ports:
            - "3000:3000"
            volumes:
            - grafana_data:/var/lib/grafana
            - ./grafana/provisioning:/etc/grafana/provisioning
            networks:
            - monitoring

        jaeger:
            image: jaegertracing/all-in-one:latest
            ports:
            - "5775:5775/udp"
            - "6831:6831/udp"
            - "6832:6832/udp"
            - "5778:5778"
            - "16686:16686"
            - "14250:14250"
            - "14268:14268"
            - "14269:14269"
            networks:
            - monitoring

        alertmanager:
            image: prom/alertmanager:latest
            ports:
            - "9093:9093"
            volumes:
            - ./alertmanager.yml:/etc/alertmanager/alertmanager.yml
            networks:
            - monitoring

        networks:
            monitoring:
                driver: bridge

        volumes:
            grafana_data:
        ```

    4. Prometheus 설정
        ```yml
        # prometheus.yml
        global:
            scrape_interval: 15s
            evaluation_interval: 15s

        alerting:
            alertmanagers:
                - static_configs:
                    - targets:
                        - alertmanager:9093

        rule_files:
        - 'rules/*.yml'

        scrape_configs:
        - job_name: 'app'
            static_configs:
            - targets: ['app:8080']

        - job_name: 'prometheus'
            static_configs:
            - targets: ['localhost:9090']
        ```

## 배포

1. Docker 설정
    1. Dockerfile
        ```dockerfile
        # Build stage
        FROM golang:1.19-alpine AS builder

        WORKDIR /app

        # 의존성 다운로드
        COPY go.mod go.sum ./
        RUN go mod download

        # 소스 코드 복사 및 빌드
        COPY . .
        RUN CGO_ENABLED=0 GOOS=linux go build -a -installsuffix cgo -o main ./cmd/server

        # Final stage
        FROM alpine:latest

        # 필요한 CA certificates 설치
        RUN apk --no-cache add ca-certificates

        WORKDIR /root/

        # 빌드된 바이너리 복사
        COPY --from=builder /app/main .
        COPY --from=builder /app/configs ./configs

        # 환경 변수 설정
        ENV GIN_MODE=release
        ENV PORT=8080

        # 포트 노출
        EXPOSE ${PORT}

        # 애플리케이션 실행
        CMD ["./main"]
        ```

    2. Docker Compose
        ```yaml
        # docker-compose.yml
        version: '3.8'

        services:
            app:
                build: 
                context: .
                dockerfile: Dockerfile
                ports:
                - "${PORT}:8080"
                environment:
                - DB_HOST=postgres
                - DB_USER=${DB_USER}
                - DB_PASSWORD=${DB_PASSWORD}
                - DB_NAME=${DB_NAME}
                - REDIS_HOST=redis
                - REDIS_PASSWORD=${REDIS_PASSWORD}
                depends_on:
                - postgres
                - redis
                networks:
                - app-network
                volumes:
                - app-data:/data
                healthcheck:
                test: ["CMD", "curl", "-f", "http://localhost:8080/health"]
                interval: 30s
                timeout: 10s
                retries: 3

            postgres:
                image: postgres:13-alpine
                environment:
                - POSTGRES_USER=${DB_USER}
                - POSTGRES_PASSWORD=${DB_PASSWORD}
                - POSTGRES_DB=${DB_NAME}
                volumes:
                - postgres-data:/var/lib/postgresql/data
                networks:
                - app-network
                healthcheck:
                test: ["CMD-SHELL", "pg_isready -U ${DB_USER}"]
                interval: 10s
                timeout: 5s
                retries: 5

            redis:
                image: redis:6-alpine
                command: redis-server --requirepass ${REDIS_PASSWORD}
                volumes:
                - redis-data:/data
                networks:
                - app-network
                healthcheck:
                test: ["CMD", "redis-cli", "ping"]
                interval: 10s
                timeout: 5s
                retries: 5

        volumes:
            app-data:
            postgres-data:
            redis-data:

        networks:
            app-network:
                driver: bridge
        ```

2. Kubernetes 배포
    1. Deployment 설정
        ```yaml
        # k8s/deployment.yaml
        apiVersion: apps/v1
        kind: Deployment
        metadata:
            name: myapp
            labels:
                app: myapp
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
                ports:
                - containerPort: 8080
                env:
                - name: DB_HOST
                valueFrom:
                    configMapKeyRef:
                    name: myapp-config
                    key: db_host
                - name: DB_USER
                valueFrom:
                    secretKeyRef:
                    name: myapp-secrets
                    key: db_user
                - name: DB_PASSWORD
                valueFrom:
                    secretKeyRef:
                    name: myapp-secrets
                    key: db_password
                resources:
                requests:
                    cpu: "100m"
                    memory: "128Mi"
                limits:
                    cpu: "500m"
                    memory: "512Mi"
                readinessProbe:
                httpGet:
                    path: /health
                    port: 8080
                initialDelaySeconds: 5
                periodSeconds: 10
                livenessProbe:
                httpGet:
                    path: /health
                    port: 8080
                initialDelaySeconds: 15
                periodSeconds: 20
        ```

    2. Sevice 설정
        ```yaml
        # k8s/service.yaml
        apiVersion: v1
        kind: Service
        metadata:
            name: myapp-service
        spec:
            selector:
                app: myapp
            ports:
                - protocol: TCP
                port: 80
                targetPort: 8080
            type: LoadBalancer
        ```

    3. ConfigMap과 Secret
        ```yaml
        # k8s/configmap.yaml
        apiVersion: v1
        kind: ConfigMap
        metadata:
            name: myapp-config
        data:
            db_host: "postgres-service"
            redis_host: "redis-service"
            app_env: "production"

        ---
        # k8s/secret.yaml
        apiVersion: v1
        kind: Secret
        metadata:
            name: myapp-secrets
        type: Opaque
        data:
            db_user: BASE64_ENCODED_USER
            db_password: BASE64_ENCODED_PASSWORD
            redis_password: BASE64_ENCODED_REDIS_PASSWORD
        ```

    4. Ingress 설정
        ```yaml
        # k8s/ingress.yaml
        apiVersion: networking.k8s.io/v1
        kind: Ingress
        metadata:
            name: myapp-ingress
            annotations:
                kubernetes.io/ingress.class: "nginx"
                cert-manager.io/cluster-issuer: "letsencrypt-prod"
        spec:
            tls:
            - hosts:
                - myapp.example.com
                secretName: myapp-tls
            rules:
            - host: myapp.example.com
                http:
                paths:
                - path: /
                    pathType: Prefix
                    backend:
                    service:
                        name: myapp-service
                        port:
                        number: 80
        ```

3. CI/CD 파이프라인
    1. Github Actions
        ```yaml
        # .github/workflows/ci.yml
        name: CI/CD Pipeline

        on:
        push:
            branches: [main]
        pull_request:
            branches: [main]

        jobs:
        test:
            runs-on: ubuntu-latest
            steps:
            - uses: actions/checkout@v2

            - name: Set up Go
            uses: actions/setup-go@v2
            with:
                go-version: ^1.19

            - name: Run tests
            run: |
                go test -v ./...
                go test -coverprofile=coverage.out ./...

            - name: Upload coverage report
            uses: codecov/codecov-action@v2
            with:
                file: ./coverage.out

        build:
            needs: test
            runs-on: ubuntu-latest
            if: github.ref == 'refs/heads/main'
            steps:
            - uses: actions/checkout@v2

            - name: Login to Docker Hub
            uses: docker/login-action@v1
            with:
                username: ${{ secrets.DOCKER_HUB_USERNAME }}
                password: ${{ secrets.DOCKER_HUB_ACCESS_TOKEN }}

            - name: Build and push Docker image
            uses: docker/build-push-action@v2
            with:
                push: true
                tags: user/myapp:latest,user/myapp:${{ github.sha }}

        deploy:
            needs: build
            runs-on: ubuntu-latest
            if: github.ref == 'refs/heads/main'
            steps:
            - uses: actions/checkout@v2
            
            - name: Install kubectl
            uses: azure/setup-kubectl@v1
            
            - name: Set Kubernetes context
            uses: azure/k8s-set-context@v1
            with:
                kubeconfig: ${{ secrets.KUBE_CONFIG_DATA }}
            
            - name: Deploy to Kubernetes
            run: |
                kubectl apply -f k8s/
                kubectl rollout restart deployment myapp
        ```

4. 스케일링 설정
    * HorizontalPodAutoscaler
        ```yaml
        # k8s/hpa.yaml
        apiVersion: autoscaling/v2
        kind: HorizontalPodAutoscaler
        metadata:
            name: myapp-hpa
        spec:
            scaleTargetRef:
                apiVersion: apps/v1
                kind: Deployment
                name: myapp
            minReplicas: 3
            maxReplicas: 10
            metrics:
            - type: Resource
                resource:
                name: cpu
                target:
                    type: Utilization
                    averageUtilization: 70
            - type: Resource
                resource:
                name: memory
                target:
                    type: Utilization
                    averageUtilization: 80
        behavior:
            scaleUp:
            stabilizationWindowSeconds: 60
            policies:
            - type: Percent
                value: 100
                periodSeconds: 15
            scaleDown:
            stabilizationWindowSeconds: 300
            policies:
            - type: Percent
                value: 100
                periodSeconds: 15
        ```

    2. PodDisruptionBudget
        ```yaml
        # k8s/pdb.yaml
        apiVersion: policy/v1
        kind: PodDisruptionBudget
        metadata:
            name: myapp-pdb
        spec:
            minAvailable: 2
            selector:
                matchLabels:
                app: myapp
        ```

5. 배포 스크립트
    1. 배포 자동화 스크립트
        ```bash
        #!/bin/bash
        # scripts/deploy.sh

        # 환경 변수 로드
        set -a
        source .env
        set +a

        # 버전 태그 생성
        VERSION=$(date +%Y%m%d-%H%M%S)
        echo "Deploying version: $VERSION"

        # Docker 이미지 빌드 및 푸시
        docker build -t $DOCKER_REGISTRY/$APP_NAME:$VERSION .
        docker push $DOCKER_REGISTRY/$APP_NAME:$VERSION

        # Kubernetes 설정 업데이트
        kubectl set image deployment/$APP_NAME $APP_NAME=$DOCKER_REGISTRY/$APP_NAME:$VERSION

        # 배포 상태 확인
        kubectl rollout status deployment/$APP_NAME

        # 이전 버전으로 롤백 함수
        rollback() {
            echo "Rolling back to previous version..."
            kubectl rollout undo deployment/$APP_NAME
            exit 1
        }

        # 헬스체크
        sleep 30
        if ! curl -s http://$APP_HOST/health | grep -q "ok"; then
            echo "Health check failed. Rolling back..."
            rollback
        fi

        echo "Deployment successful!"
        ```

    2. 백업 스크립트
        ```bash
        #!/bin/bash
        # scripts/backup.sh

        # 환경 변수 로드
        source .env

        # 백업 디렉토리 생성
        BACKUP_DIR="backups/$(date +%Y%m%d)"
        mkdir -p $BACKUP_DIR

        # 데이터베이스 백업
        pg_dump -h $DB_HOST -U $DB_USER -d $DB_NAME > $BACKUP_DIR/database.sql

        # 설정 파일 백업
        cp configs/* $BACKUP_DIR/

        # 백업 압축
        tar -czf $BACKUP_DIR.tar.gz $BACKUP_DIR

        # S3에 업로드
        aws s3 cp $BACKUP_DIR.tar.gz s3://$BACKUP_BUCKET/

        # 오래된 백업 정리
        find backups/ -type f -name "*.tar.gz" -mtime +30 -exec rm {} \;
        ```

6. 모니터링 및 알람 설정
    1. Prometheus Rules
        ```yaml
        # k8s/prometheus-rules.yaml
        apiVersion: monitoring.coreos.com/v1
        kind: PrometheusRule
        metadata:
            name: myapp-alert-rules
            labels:
                app: myapp
        spec:
            groups:
            - name: myapp.rules
                rules:
                - alert: HighErrorRate
                expr: |
                    rate(http_requests_total{status=~"5.."}[5m])
                    /
                    rate(http_requests_total[5m])
                    > 0.1
                for: 5m
                labels:
                    severity: critical
                annotations:
                    summary: High HTTP error rate
                    description: Error rate is above 10% for 5 minutes

                - alert: HighLatency
                expr: |
                    histogram_quantile(0.95,
                    rate(http_request_duration_seconds_bucket[5m]))
                    > 2
                for: 5m
                labels:
                    severity: warning
                annotations:
                    summary: High latency
                    description: 95th percentile latency is above 2 seconds
        ```

    2. AlertManager 설정
        ```yaml
        # k8s/alertmanager-config.yaml
        apiVersion: v1
        kind: Secret
        metadata:
            name: alertmanager-config
        type: Opaque
        stringData:
            alertmanager.yaml: |
                global:
                slack_api_url: 'https://hooks.slack.com/services/T00000000/B00000000/XXXXXXXXXXXXXXXXXXXXXXXX'

                route:
                    group_by: ['alertname']
                    group_wait: 30s
                    group_interval: 5m
                    repeat_interval: 4h
                    receiver: 'slack-notifications'
                    routes:
                    - match:
                        severity: critical
                        receiver: 'slack-critical'

                receivers:
                - name: 'slack-notifications'
                slack_configs:
                    - channel: '#alerts'
                    title: '{{ .GroupLabels.alertname }}'
                    text: "{{ range .Alerts }}{{ .Annotations.description }}\n{{ end }}"

                - name: 'slack-critical'
                    slack_configs:
                    - channel: '#alerts-critical'
                    title: '🚨 {{ .GroupLabels.alertname }}'
                    text: "{{ range .Alerts }}{{ .Annotations.description }}\n{{ end }}"
        ```


