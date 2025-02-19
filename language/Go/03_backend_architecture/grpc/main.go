/*
main.go
이 파일은 gRPC 서버의 진입점입니다.
주요 기능:
1. TCP 리스너를 생성하여 지정된 포트(예: 50051)에서 클라이언트 연결을 대기합니다.
2. grpc.NewServer()를 사용하여 gRPC 서버 인스턴스를 생성하고, 서비스 핸들러를 등록합니다.
3. graceful shutdown을 위해 OS 신호를 감지하여, 서버를 정상적으로 종료할 수 있도록 합니다.
4. 서버 실행 중 발생하는 오류를 로깅하고, 적절히 종료합니다.

실제 운영 환경에서는 TLS 설정, 로깅 및 모니터링 등을 추가하여 보안을 강화하고 안정성을 높일 수 있습니다.
*/

package main

import (
	"context"
	"log"
	"net"
	"os"
	"os/signal"
	"syscall"

	// proto 파일에서 생성된 gRPC 코드를 가져옵니다.
	// 실제 프로젝트 경로에 맞게 수정하세요.
	pb "grpc/proto-impl"

	"google.golang.org/grpc"
)

// server 구조체는 YourService 인터페이스를 구현합니다.
// UnimplementedYourServiceServer를 임베딩하여, 향후 서비스 확장이 용이하도록 합니다.
type server struct {
	pb.UnimplementedYourServiceServer
}

// SayHello 메서드는 YourService 인터페이스의 Unary RPC 메서드를 구현합니다.
// 클라이언트의 인사 요청(HelloRequest)을 받아, 인사 메시지(HelloResponse)를 반환합니다.
func (s *server) SayHello(ctx context.Context, req *pb.HelloRequest) (*pb.HelloResponse, error) {
	log.Printf("Received SayHello request for: %s", req.GetName())
	// 간단한 응답 메시지 생성
	respMessage := "Hello, " + req.GetName() + "!"
	return &pb.HelloResponse{Message: respMessage}, nil
}

func server_main() {
	// 1. TCP 리스너 생성: 포트 50051에서 클라이언트 요청 수신
	lis, err := net.Listen("tcp", ":50051")
	if err != nil {
		log.Fatalf("포트 50051에서 리스너 생성 실패: %v", err)
	}

	// 2. gRPC 서버 인스턴스 생성
	grpcServer := grpc.NewServer()
	// 3. 서비스 등록: proto 파일로 생성된 인터페이스에 따라 서비스 핸들러 등록
	pb.RegisterYourServiceServer(grpcServer, &server{})
	log.Println("gRPC 서버가 포트 50051에서 실행 중입니다...")

	// 4. graceful shutdown(우아한 종료) 설정
	// OS 신호(예: SIGINT, SIGTERM)를 감지하여 서버를 정상 종료합니다.
	go func() {
		// 채널을 생성하여 OS 신호를 수신합니다.
		sigChan := make(chan os.Signal, 1)
		signal.Notify(sigChan, os.Interrupt, syscall.SIGTERM)
		// 신호가 수신되면, 서버 종료를 시작합니다.
		sig := <-sigChan
		log.Printf("종료 신호(%v) 수신: gRPC 서버를 우아하게 종료합니다.", sig)
		grpcServer.GracefulStop()
		lis.Close()
	}()

	// 5. 서버 실행: 리스너를 사용하여 클라이언트 요청을 처리합니다.
	if err := grpcServer.Serve(lis); err != nil {
		log.Fatalf("gRPC 서버 실행 실패: %v", err)
	}
}
