# gRPC in Go: High-Performance RPC 🚀

이 디렉토리는 Go 언어를 사용하여 **gRPC** 기반의 고성능 원격 프로시저 호출(RPC)을 구현하는 방법을 다룹니다.  
gRPC와 Protocol Buffers를 통해 서비스 간 통신을 효율적으로 구축하고, 스트리밍 및 양방향 통신 등 실무에서 자주 필요한 기능들을 적용하는 방법을 학습할 수 있습니다.

---

## What You'll Learn 🎯

- **gRPC 기본 개념**:  
  - gRPC의 특징, 장점, 그리고 RESTful API와의 차이점 이해
- **Protocol Buffers 사용법**:  
  - 메시지 및 서비스 정의, .proto 파일 작성 및 컴파일
- **gRPC 서버 및 클라이언트 구현**:  
  - Go에서 gRPC 서버와 클라이언트를 설정하고, 기본 원격 호출을 구현하는 방법
- **스트리밍 RPC**:  
  - 서버 스트리밍, 클라이언트 스트리밍, 그리고 양방향 스트리밍 RPC의 활용
- **실무 적용 및 배포 전략**:  
  - gRPC 서비스의 배포, 보안 (TLS 적용), 그리고 성능 최적화 팁

---

## Directory Structure 📁

```plaintext
03-backend-architecture/
└── grpc/
    ├── main.go            # gRPC 서버의 진입점 예제
    ├── client.go          # gRPC 클라이언트 예제
    ├── proto/             # .proto 파일 및 생성된 코드 (자동 생성)
    ├── examples/          # 추가 실습 예제 및 스트리밍 RPC 예제
    └── README.md          # 이 문서
```

- **main.go**: gRPC 서버를 초기화하고 서비스 핸들러를 등록하는 기본 예제.
- **client.go**: 서버와 통신하는 클라이언트 예제.
- **proto/**: 서비스 인터페이스와 메시지 타입을 정의한 .proto 파일과, 이를 통해 생성된 Go 코드를 포함합니다.
- **examples/**: 다양한 gRPC 기능(스트리밍, 에러 핸들링, 인증 등)을 다루는 추가 예제들.

---

## Getting Started 🚀

### 1. 필수 도구 설치
- Go 최신 버전: [Download Go](https://go.dev/dl/)
- Protocol Buffers 컴파일러 (`protoc`): [Protocol Buffers Releases](https://github.com/protocolbuffers/protobuf/releases)
- gRPC Go 패키지 설치:
  ```bash
  go get -u google.golang.org/grpc
  go get -u google.golang.org/protobuf/cmd/protoc-gen-go
  go get -u google.golang.org/grpc/cmd/protoc-gen-go-grpc
  ```

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/03-backend-architecture/grpc
```

### 3. 프로토콜 파일 컴파일
- proto 디렉토리 내의 .proto 파일을 컴파일하여 Go 코드를 생성합니다:
  ```bash
  protoc --go_out=. --go-grpc_out=. proto/your_service.proto
  ```

### 4. 서버 및 클라이언트 실행
- gRPC 서버 실행:
  ```bash
  go run main.go
  ```
- 다른 터미널에서 클라이언트 실행:
  ```bash
  go run client.go
  ```

---

## Example Code Snippet 📄

### gRPC 서버 (main.go)
```go
package main

import (
    "context"
    "log"
    "net"

    pb "path/to/your/proto"
    "google.golang.org/grpc"
)

type server struct {
    pb.UnimplementedYourServiceServer
}

// 예제: 간단한 RPC 구현
func (s *server) SayHello(ctx context.Context, req *pb.HelloRequest) (*pb.HelloResponse, error) {
    log.Printf("Received: %v", req.GetName())
    return &pb.HelloResponse{Message: "Hello, " + req.GetName() + "!"}, nil
}

func main() {
    lis, err := net.Listen("tcp", ":50051")
    if err != nil {
        log.Fatalf("failed to listen: %v", err)
    }
    s := grpc.NewServer()
    pb.RegisterYourServiceServer(s, &server{})
    log.Println("gRPC 서버가 50051 포트에서 실행 중입니다...")
    if err := s.Serve(lis); err != nil {
        log.Fatalf("failed to serve: %v", err)
    }
}
```

### gRPC 클라이언트 (client.go)
```go
package main

import (
    "context"
    "log"
    "time"

    pb "path/to/your/proto"
    "google.golang.org/grpc"
)

func main() {
    conn, err := grpc.Dial("localhost:50051", grpc.WithInsecure(), grpc.WithBlock())
    if err != nil {
        log.Fatalf("did not connect: %v", err)
    }
    defer conn.Close()
    c := pb.NewYourServiceClient(conn)

    ctx, cancel := context.WithTimeout(context.Background(), time.Second)
    defer cancel()
    r, err := c.SayHello(ctx, &pb.HelloRequest{Name: "Gopher"})
    if err != nil {
        log.Fatalf("could not greet: %v", err)
    }
    log.Printf("Greeting: %s", r.GetMessage())
}
```

이 예제는 기본적인 "Hello" RPC를 구현한 것으로, gRPC 서버와 클라이언트 간의 간단한 통신을 보여줍니다.

---

## Best Practices & Tips 💡

- **보안 적용**:  
  - 프로덕션 환경에서는 `grpc.WithInsecure()` 대신 TLS 인증을 적용하여 보안을 강화하세요.
  
- **스트리밍 활용**:  
  - 서버 스트리밍, 클라이언트 스트리밍, 양방향 스트리밍 등의 RPC를 구현하여, 대용량 데이터 전송 및 실시간 통신을 효과적으로 처리하세요.
  
- **에러 핸들링**:  
  - gRPC의 상태 코드와 에러 메시지를 활용해, 클라이언트와 서버 간의 신뢰할 수 있는 에러 처리를 구현하세요.
  
- **성능 최적화**:  
  - gRPC는 HTTP/2를 기반으로 하므로, 다중화와 헤더 압축의 장점을 최대한 활용하고, 필요 시 프로파일링을 통해 병목 현상을 분석하세요.
  
- **API 계약 관리**:  
  - .proto 파일을 통해 서비스 인터페이스를 명확히 정의하고, 클라이언트와 서버 간의 계약을 일관되게 유지하세요.
```markdown
# gRPC in Go: High-Performance RPC 🚀

이 디렉토리는 Go 언어를 사용하여 **gRPC** 기반의 고성능 원격 프로시저 호출(RPC)을 구현하는 방법을 다룹니다.  
gRPC와 Protocol Buffers를 통해 서비스 간 통신을 효율적으로 구축하고, 스트리밍 및 양방향 통신 등 실무에서 자주 필요한 기능들을 적용하는 방법을 학습할 수 있습니다.

---

## What You'll Learn 🎯

- **gRPC 기본 개념**:  
  - gRPC의 특징, 장점, 그리고 RESTful API와의 차이점 이해
- **Protocol Buffers 사용법**:  
  - 메시지 및 서비스 정의, .proto 파일 작성 및 컴파일
- **gRPC 서버 및 클라이언트 구현**:  
  - Go에서 gRPC 서버와 클라이언트를 설정하고, 기본 원격 호출을 구현하는 방법
- **스트리밍 RPC**:  
  - 서버 스트리밍, 클라이언트 스트리밍, 그리고 양방향 스트리밍 RPC의 활용
- **실무 적용 및 배포 전략**:  
  - gRPC 서비스의 배포, 보안 (TLS 적용), 그리고 성능 최적화 팁

---

## Directory Structure 📁

```plaintext
03-backend-architecture/
└── grpc/
    ├── main.go            # gRPC 서버의 진입점 예제
    ├── client.go          # gRPC 클라이언트 예제
    ├── proto/             # .proto 파일 및 생성된 코드 (자동 생성)
    ├── examples/          # 추가 실습 예제 및 스트리밍 RPC 예제
    └── README.md          # 이 문서
```

- **main.go**: gRPC 서버를 초기화하고 서비스 핸들러를 등록하는 기본 예제.
- **client.go**: 서버와 통신하는 클라이언트 예제.
- **proto/**: 서비스 인터페이스와 메시지 타입을 정의한 .proto 파일과, 이를 통해 생성된 Go 코드를 포함합니다.
- **examples/**: 다양한 gRPC 기능(스트리밍, 에러 핸들링, 인증 등)을 다루는 추가 예제들.

---

## Getting Started 🚀

### 1. 필수 도구 설치
- Go 최신 버전: [Download Go](https://go.dev/dl/)
- Protocol Buffers 컴파일러 (`protoc`): [Protocol Buffers Releases](https://github.com/protocolbuffers/protobuf/releases)
- gRPC Go 패키지 설치:
  ```bash
  go get -u google.golang.org/grpc
  go get -u google.golang.org/protobuf/cmd/protoc-gen-go
  go get -u google.golang.org/grpc/cmd/protoc-gen-go-grpc
  ```

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/03-backend-architecture/grpc
```

### 3. 프로토콜 파일 컴파일
- proto 디렉토리 내의 .proto 파일을 컴파일하여 Go 코드를 생성합니다:
  ```bash
  protoc --go_out=. --go-grpc_out=. proto/your_service.proto
  ```

### 4. 서버 및 클라이언트 실행
- gRPC 서버 실행:
  ```bash
  go run main.go
  ```
- 다른 터미널에서 클라이언트 실행:
  ```bash
  go run client.go
  ```

---

## Example Code Snippet 📄

### gRPC 서버 (main.go)
```go
package main

import (
    "context"
    "log"
    "net"

    pb "path/to/your/proto"
    "google.golang.org/grpc"
)

type server struct {
    pb.UnimplementedYourServiceServer
}

// 예제: 간단한 RPC 구현
func (s *server) SayHello(ctx context.Context, req *pb.HelloRequest) (*pb.HelloResponse, error) {
    log.Printf("Received: %v", req.GetName())
    return &pb.HelloResponse{Message: "Hello, " + req.GetName() + "!"}, nil
}

func main() {
    lis, err := net.Listen("tcp", ":50051")
    if err != nil {
        log.Fatalf("failed to listen: %v", err)
    }
    s := grpc.NewServer()
    pb.RegisterYourServiceServer(s, &server{})
    log.Println("gRPC 서버가 50051 포트에서 실행 중입니다...")
    if err := s.Serve(lis); err != nil {
        log.Fatalf("failed to serve: %v", err)
    }
}
```

### gRPC 클라이언트 (client.go)
```go
package main

import (
    "context"
    "log"
    "time"

    pb "path/to/your/proto"
    "google.golang.org/grpc"
)

func main() {
    conn, err := grpc.Dial("localhost:50051", grpc.WithInsecure(), grpc.WithBlock())
    if err != nil {
        log.Fatalf("did not connect: %v", err)
    }
    defer conn.Close()
    c := pb.NewYourServiceClient(conn)

    ctx, cancel := context.WithTimeout(context.Background(), time.Second)
    defer cancel()
    r, err := c.SayHello(ctx, &pb.HelloRequest{Name: "Gopher"})
    if err != nil {
        log.Fatalf("could not greet: %v", err)
    }
    log.Printf("Greeting: %s", r.GetMessage())
}
```

이 예제는 기본적인 "Hello" RPC를 구현한 것으로, gRPC 서버와 클라이언트 간의 간단한 통신을 보여줍니다.

---

## Best Practices & Tips 💡

- **보안 적용**:  
  - 프로덕션 환경에서는 `grpc.WithInsecure()` 대신 TLS 인증을 적용하여 보안을 강화하세요.
  
- **스트리밍 활용**:  
  - 서버 스트리밍, 클라이언트 스트리밍, 양방향 스트리밍 등의 RPC를 구현하여, 대용량 데이터 전송 및 실시간 통신을 효과적으로 처리하세요.
  
- **에러 핸들링**:  
  - gRPC의 상태 코드와 에러 메시지를 활용해, 클라이언트와 서버 간의 신뢰할 수 있는 에러 처리를 구현하세요.
  
- **성능 최적화**:  
  - gRPC는 HTTP/2를 기반으로 하므로, 다중화와 헤더 압축의 장점을 최대한 활용하고, 필요 시 프로파일링을 통해 병목 현상을 분석하세요.
  
- **API 계약 관리**:  
  - .proto 파일을 통해 서비스 인터페이스를 명확히 정의하고, 클라이언트와 서버 간의 계약을 일관되게 유지하세요.

---

## Next Steps

- **심화 학습**:  
  - 스트리밍 RPC, 인터셉터, 미들웨어, 인증/인가 등 고급 gRPC 기능을 추가로 학습해 보세요.
- **실무 적용**:  
  - gRPC 서비스를 실제 마이크로서비스 아키텍처에 통합하여, 서비스 간 통신을 최적화하고, 운영 자동화를 위한 모니터링 및 로깅을 적용하세요.

---

## 참고 자료 📚

- [gRPC Official Documentation](https://grpc.io/docs/)
- [Protocol Buffers Documentation](https://developers.google.com/protocol-buffers)
- [Go gRPC Tutorial](https://grpc.io/docs/languages/go/basics/)
- [gRPC Interceptors in Go](https://github.com/grpc-ecosystem/go-grpc-middleware)

---

Go에서 gRPC를 활용하면, 높은 성능과 강타입의 인터페이스를 통해 안정적이고 확장 가능한 서비스 간 통신을 구현할 수 있습니다.  
이 자료를 기반으로, 실무에 바로 적용 가능한 gRPC 서비스를 구축해 보세요! Happy gRPC Coding! 🚀
---

## Next Steps

- **심화 학습**:  
  - 스트리밍 RPC, 인터셉터, 미들웨어, 인증/인가 등 고급 gRPC 기능을 추가로 학습해 보세요.
- **실무 적용**:  
  - gRPC 서비스를 실제 마이크로서비스 아키텍처에 통합하여, 서비스 간 통신을 최적화하고, 운영 자동화를 위한 모니터링 및 로깅을 적용하세요.

---

## 참고 자료 📚

- [gRPC Official Documentation](https://grpc.io/docs/)
- [Protocol Buffers Documentation](https://developers.google.com/protocol-buffers)
- [Go gRPC Tutorial](https://grpc.io/docs/languages/go/basics/)
- [gRPC Interceptors in Go](https://github.com/grpc-ecosystem/go-grpc-middleware)

---

Go에서 gRPC를 활용하면, 높은 성능과 강타입의 인터페이스를 통해 안정적이고 확장 가능한 서비스 간 통신을 구현할 수 있습니다.  
이 자료를 기반으로, 실무에 바로 적용 가능한 gRPC 서비스를 구축해 보세요! Happy gRPC Coding! 🚀
```