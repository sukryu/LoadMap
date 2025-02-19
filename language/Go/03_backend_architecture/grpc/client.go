/*
client.go
이 파일은 gRPC 클라이언트를 구현한 예제입니다.
주요 기능:
1. gRPC 서버와의 연결 설정: grpc.Dial을 사용하여 서버에 연결합니다.
2. 클라이언트 인스턴스 생성: 프로토콜 버퍼로 생성된 gRPC 클라이언트 인터페이스를 사용합니다.
3. 컨텍스트 생성: RPC 호출 시 타임아웃을 지정하여 안정성을 높입니다.
4. RPC 호출: SayHello 메서드를 호출하여, 서버로부터 응답을 받습니다.
5. 응답 처리: 서버의 응답 메시지를 출력합니다.

실제 운영 환경에서는 TLS 인증을 적용하여 보안을 강화하는 것이 좋습니다.
*/

package main

import (
	"context"
	"fmt"
	"log"
	"time"

	// 프로토콜 버퍼로 생성된 코드를 가져옵니다.
	// 실제 프로젝트 경로에 맞게 수정해야 합니다.
	pb "grpc/proto-impl"

	"google.golang.org/grpc"
)

func client_main() {
	// 1. gRPC 서버 연결 설정
	// grpc.WithInsecure() 옵션은 TLS 없이 연결하도록 설정합니다.
	// 실무에서는 반드시 TLS를 적용하여 보안을 강화해야 합니다.
	conn, err := grpc.Dial("localhost:50051", grpc.WithInsecure(), grpc.WithBlock())
	if err != nil {
		log.Fatalf("서버 연결 실패: %v", err)
	}
	// 연결 종료 시, conn.Close()를 호출하여 리소스를 해제합니다.
	defer conn.Close()

	// 2. gRPC 클라이언트 인스턴스 생성
	// pb.NewYourServiceClient 함수는 proto에서 정의된 인터페이스를 구현한 클라이언트를 생성합니다.
	client := pb.NewYourServiceClient(conn)

	// 3. RPC 호출을 위한 컨텍스트 생성
	// context.WithTimeout을 사용하여, 1초의 타임아웃을 지정합니다.
	ctx, cancel := context.WithTimeout(context.Background(), time.Second)
	defer cancel() // 함수 종료 시 컨텍스트 취소

	// 4. RPC 요청 메시지 생성
	// HelloRequest 메시지는 클라이언트의 이름을 전달하는 역할을 합니다.
	req := &pb.HelloRequest{
		Name: "Gopher",
	}

	// 5. 서버에 RPC 호출 (SayHello 메서드)
	// 서버는 HelloRequest 메시지를 받고, HelloResponse 메시지를 반환합니다.
	res, err := client.SayHello(ctx, req)
	if err != nil {
		log.Fatalf("RPC 호출 실패: %v", err)
	}

	// 6. 서버 응답 출력
	fmt.Printf("서버 응답: %s\n", res.GetMessage())
}
