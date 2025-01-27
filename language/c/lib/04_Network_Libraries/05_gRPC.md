# gRPC 라이브러리 사용 가이드

gRPC는 Google에서 개발한 고성능 원격 프로시저 호출(Remote Procedure Call) 프레임워크로, 네트워크 분산 시스템 간 통신을 위한 강력한 도구입니다. Protocol Buffers(ProtoBuf)를 사용하여 데이터 직렬화를 처리하며, 다양한 언어에서 사용 가능합니다.

---

## 1. 주요 특징

1. **멀티플랫폼 지원**: 다양한 언어(C++, Python, Java 등)에서 사용 가능.
2. **고성능**: HTTP/2 기반 비동기 통신 지원.
3. **프로토콜 버퍼**: 데이터 직렬화 및 역직렬화에 ProtoBuf 사용.
4. **양방향 스트리밍**: 클라이언트와 서버 간 실시간 스트리밍 지원.
5. **보안**: TLS 암호화를 통한 안전한 통신 지원.

---

## 2. 설치

### 2.1 gRPC와 Protocol Buffers 설치

**Ubuntu/Linux:**
```bash
sudo apt-get install build-essential autoconf libtool pkg-config
sudo apt-get install libssl-dev

# Clone the gRPC repository
git clone --recurse-submodules -b v1.56.0 https://github.com/grpc/grpc
cd grpc

# Build gRPC and Protocol Buffers
mkdir -p cmake/build
cd cmake/build
cmake ../..
make -j
sudo make install
```

**macOS:**
```bash
brew install grpc
```

**Windows:**
- gRPC 공식 GitHub 저장소(https://github.com/grpc/grpc)에서 소스 코드 다운로드 후 빌드.

---

## 3. 주요 구성 요소

### 3.1 Protocol Buffers (ProtoBuf)
- gRPC의 기본 직렬화 포맷.
- `.proto` 파일을 작성하여 서비스 및 메시지를 정의.

**예제:**
```proto
syntax = "proto3";

service Greeter {
  rpc SayHello (HelloRequest) returns (HelloReply);
}

message HelloRequest {
  string name = 1;
}

message HelloReply {
  string message = 1;
}
```

### 3.2 gRPC Core
- gRPC 서버와 클라이언트를 구현하기 위한 핵심 라이브러리.

---

## 4. 주요 사용법

### 4.1 gRPC 코드 생성

#### 1. `.proto` 파일 컴파일
**명령어:**
```bash
protoc -I=. --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` greeter.proto
protoc -I=. --cpp_out=. greeter.proto
```
- `--grpc_out`: gRPC 코드 생성.
- `--cpp_out`: Protocol Buffers 코드 생성.

---

### 4.2 서버 구현

**서버 코드:**
```cpp
#include <grpcpp/grpcpp.h>
#include "greeter.grpc.pb.h"

class GreeterServiceImpl final : public Greeter::Service {
    grpc::Status SayHello(grpc::ServerContext* context, const HelloRequest* request, HelloReply* reply) override {
        std::string name = request->name();
        reply->set_message("Hello, " + name);
        return grpc::Status::OK;
    }
};

int main() {
    std::string server_address("0.0.0.0:50051");
    GreeterServiceImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
    return 0;
}
```

---

### 4.3 클라이언트 구현

**클라이언트 코드:**
```cpp
#include <grpcpp/grpcpp.h>
#include "greeter.grpc.pb.h"

int main() {
    auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    std::unique_ptr<Greeter::Stub> stub = Greeter::NewStub(channel);

    HelloRequest request;
    request.set_name("World");

    HelloReply reply;
    grpc::ClientContext context;

    grpc::Status status = stub->SayHello(&context, request, &reply);

    if (status.ok()) {
        std::cout << "서버 응답: " << reply.message() << std::endl;
    } else {
        std::cerr << "gRPC 오류: " << status.error_message() << std::endl;
    }

    return 0;
}
```

**출력:**
```
서버 응답: Hello, World
```

---

### 4.4 양방향 스트리밍

**서버 코드:**
```cpp
grpc::Status StreamChat(grpc::ServerContext* context, grpc::ServerReaderWriter<ChatMessage, ChatMessage>* stream) override {
    ChatMessage message;
    while (stream->Read(&message)) {
        std::cout << "클라이언트 메시지: " << message.text() << std::endl;
        ChatMessage reply;
        reply.set_text("Echo: " + message.text());
        stream->Write(reply);
    }
    return grpc::Status::OK;
}
```

**클라이언트 코드:**
```cpp
auto stream = stub->StreamChat(&context);
ChatMessage message;
message.set_text("Hello, Server!");
stream->Write(message);
stream->Read(&reply);
std::cout << "서버 응답: " << reply.text() << std::endl;
```

---

## 5. 사용 시 주의사항

1. **에러 처리**: 모든 gRPC 호출은 `grpc::Status`를 반환하므로, 이를 확인하여 오류를 처리해야 합니다.
2. **보안 설정**: 배포 환경에서는 `InsecureServerCredentials` 대신 TLS를 사용하는 것이 필수입니다.
3. **리소스 관리**: 서버 및 클라이언트 객체는 사용 후 반드시 정리해야 합니다.

---

gRPC는 분산 시스템 간 통신을 단순화하고, 고성능 및 확장성을 제공합니다. 위의 예제와 기능을 활용하여 효율적인 네트워크 애플리케이션을 설계해보세요.

