# 🦀 Rust의 마이크로서비스 아키텍처 및 gRPC 통신

## 📌 개요
마이크로서비스 아키텍처(MSA)는 **확장성, 유지보수성, 독립 배포 가능성**을 높이는 소프트웨어 설계 방식입니다. Rust에서는 `tonic`을 활용하여 **gRPC 기반 마이크로서비스**를 구축할 수 있습니다.

이 장에서는 **Rust를 사용한 마이크로서비스 아키텍처 구현과 gRPC 통신 방법**을 다뤄보겠습니다.

---

## 🚀 마이크로서비스 아키텍처란?
마이크로서비스 아키텍처(MSA)는 여러 개의 독립적인 서비스로 구성된 아키텍처입니다.

📌 **특징**
✅ 개별 서비스 독립 배포 가능
✅ 확장성이 뛰어나며 수평 확장 가능
✅ 서비스 간 통신이 중요 (HTTP, gRPC, 메시지 큐 등 사용)
✅ 다양한 언어 및 기술 스택 조합 가능

📌 **Rust에서 MSA를 위한 도구**
- `tonic` → gRPC 서버 및 클라이언트 구현
- `tokio` → 비동기 런타임 지원
- `serde` → JSON 직렬화/역직렬화
- `hyper` → HTTP 서비스 구축
- `redis` → 캐싱 및 메시지 큐 활용

---

## 🏗️ `tonic`을 사용한 gRPC 서버 구축

### 🏷️ 프로젝트 설정
```sh
cargo new grpc_server --bin
cd grpc_server
cargo add tonic prost tokio
```
📌 `cargo add tonic prost tokio` → gRPC 및 Protocol Buffers 지원 패키지 추가

---

### 🏷️ Protocol Buffers (`proto/service.proto`)
```proto
syntax = "proto3";

package my_service;

service Greeter {
  rpc SayHello (HelloRequest) returns (HelloResponse);
}

message HelloRequest {
  string name = 1;
}

message HelloResponse {
  string message = 1;
}
```
📌 `service Greeter` → gRPC 서비스 정의

📌 `SayHello(HelloRequest) returns (HelloResponse)` → 요청/응답 메시지 정의

---

### 🏗️ gRPC 서버 구현 (`src/server.rs`)
```rust
use tonic::{transport::Server, Request, Response, Status};
use my_service::greeter_server::{Greeter, GreeterServer};
use my_service::{HelloRequest, HelloResponse};

pub mod my_service {
    tonic::include_proto!("my_service");
}

#[derive(Default)]
pub struct MyGreeter;

#[tonic::async_trait]
impl Greeter for MyGreeter {
    async fn say_hello(
        &self,
        request: Request<HelloRequest>,
    ) -> Result<Response<HelloResponse>, Status> {
        let reply = HelloResponse {
            message: format!("Hello, {}!", request.into_inner().name),
        };
        Ok(Response::new(reply))
    }
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let addr = "127.0.0.1:50051".parse()?;
    let greeter = MyGreeter::default();

    println!("gRPC 서버 실행 중: {}", addr);

    Server::builder()
        .add_service(GreeterServer::new(greeter))
        .serve(addr)
        .await?;
    Ok(())
}
```
📌 `GreeterServer::new(greeter)` → gRPC 서비스 등록

📌 `say_hello()` → 클라이언트 요청을 처리하는 메서드 구현

📌 `Server::builder().serve(addr).await?;` → gRPC 서버 실행

---

## 🔄 gRPC 클라이언트 구현 (`src/client.rs`)
```rust
use tonic::transport::Channel;
use my_service::greeter_client::GreeterClient;
use my_service::HelloRequest;

pub mod my_service {
    tonic::include_proto!("my_service");
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut client = GreeterClient::connect("http://127.0.0.1:50051").await?;

    let request = tonic::Request::new(HelloRequest {
        name: "Rustacean".to_string(),
    });

    let response = client.say_hello(request).await?;
    println!("서버 응답: {:?}", response.into_inner().message);
    
    Ok(())
}
```
📌 `GreeterClient::connect()` → gRPC 서버에 연결

📌 `client.say_hello(request).await?` → 서버에 요청 보내고 응답 받기

---

## 🚀 서비스 확장: Redis 메시지 큐 활용
Microservices 간 **비동기 메시지 큐**를 사용하면 **서비스 간 의존성을 낮출 수 있습니다.**

### 🏗️ Redis를 사용한 메시지 큐 예제 (`src/redis_queue.rs`)
```rust
use redis::{AsyncCommands, Client};
use tokio;

#[tokio::main]
async fn main() -> redis::RedisResult<()> {
    let client = Client::open("redis://127.0.0.1/")?;
    let mut conn = client.get_async_connection().await?;

    conn.set("greeting", "Hello from Rust!").await?;
    let value: String = conn.get("greeting").await?;

    println!("Redis 값: {}", value);
    Ok(())
}
```
📌 `redis::AsyncCommands` → 비동기 Redis 연동 지원

📌 `conn.set("greeting", "Hello from Rust!").await?;` → Redis에 데이터 저장

📌 `conn.get("greeting").await?;` → Redis에서 데이터 조회

---

## 🎯 마무리
이 장에서는 **Rust를 사용한 마이크로서비스 아키텍처 및 gRPC 통신**을 학습했습니다.

- `tonic`을 사용하여 **gRPC 서버 및 클라이언트 구현**
- **Protocol Buffers를 활용한 서비스 정의**
- `redis`를 활용하여 **비동기 메시지 큐 시스템 구축**
- 마이크로서비스 간 **고성능 통신 및 데이터 공유 기법**

다음 장에서는 **Rust의 데이터베이스 연동 및 트랜잭션 관리(PostgreSQL, MySQL, Diesel)** 를 배워보겠습니다! 🚀
