# 🦀 Rust 기반 웹 백엔드 개발 (Actix 및 Axum 활용)

## 📌 개요
Rust는 **고성능, 안전성, 동시성**을 보장하는 언어로, **웹 백엔드 개발**에도 적합합니다. 특히, `Actix-web`과 `Axum` 프레임워크를 사용하면 빠르고 안전한 웹 애플리케이션을 구축할 수 있습니다.

이 장에서는 **Rust를 활용한 웹 백엔드 개발**을 다뤄보겠습니다.

---

## 🚀 Actix-web 기본 개념
`Actix-web`은 **고성능 비동기 웹 프레임워크**로, Rust 기반 마이크로서비스 개발에 최적화되어 있습니다.

### 🏷️ Actix 프로젝트 설정
```sh
cargo new actix_server --bin
cd actix_server
cargo add actix-web
```
📌 `cargo add actix-web` → Actix-web 의존성 추가

---

### 🏗️ Actix 웹 서버 예제
```rust
use actix_web::{web, App, HttpResponse, HttpServer, Responder};

async fn hello() -> impl Responder {
    HttpResponse::Ok().body("Hello, Actix!")
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    HttpServer::new(|| {
        App::new().route("/", web::get().to(hello))
    })
    .bind("127.0.0.1:8080")?
    .run()
    .await
}
```
📌 `HttpServer::new()` → 웹 서버 생성

📌 `App::new().route()` → 경로(`/`)에 요청 처리

📌 `#[actix_web::main]` → 비동기 실행

📌 실행 후 `http://127.0.0.1:8080/` 에 접속하면 "Hello, Actix!" 응답

---

## 🔄 Actix에서 JSON API 만들기
Actix에서 JSON API를 만들려면 `serde` 크레이트를 활용합니다.

```rust
use actix_web::{web, App, HttpResponse, HttpServer, Responder};
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize)]
struct User {
    name: String,
    age: u8,
}

async fn get_user() -> impl Responder {
    let user = User {
        name: "Alice".to_string(),
        age: 30,
    };
    HttpResponse::Ok().json(user)
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    HttpServer::new(|| {
        App::new().route("/user", web::get().to(get_user))
    })
    .bind("127.0.0.1:8080")?
    .run()
    .await
}
```
📌 `serde::{Serialize, Deserialize}` → JSON 직렬화/역직렬화 지원

📌 `HttpResponse::Ok().json(user)` → JSON 응답 반환

📌 `/user` 경로에 `GET` 요청 시 JSON 데이터 반환

---

## 🚀 Axum 기본 개념
`Axum`은 **Tokio 기반 비동기 웹 프레임워크**로, Rust 생태계에서 널리 사용됩니다.

### 🏷️ Axum 프로젝트 설정
```sh
cargo new axum_server --bin
cd axum_server
cargo add axum tokio
```
📌 `cargo add axum tokio` → Axum 및 Tokio 런타임 추가

---

### 🏗️ Axum 웹 서버 예제
```rust
use axum::{routing::get, Router};
use std::net::SocketAddr;
use tokio::net::TcpListener;

async fn hello() -> &'static str {
    "Hello, Axum!"
}

#[tokio::main]
async fn main() {
    let app = Router::new().route("/", get(hello));
    let addr = SocketAddr::from(([127, 0, 0, 1], 8080));
    
    axum::Server::bind(&addr)
        .serve(app.into_make_service())
        .await
        .unwrap();
}
```
📌 `Router::new().route("/", get(hello))` → 경로 설정

📌 `axum::Server::bind(&addr).serve(app.into_make_service())` → 서버 실행

📌 실행 후 `http://127.0.0.1:8080/` 접속 시 "Hello, Axum!" 응답

---

## 🔄 Axum에서 JSON API 만들기
```rust
use axum::{routing::get, Json, Router};
use serde::{Deserialize, Serialize};
use std::net::SocketAddr;
use tokio::net::TcpListener;

#[derive(Serialize, Deserialize)]
struct User {
    name: String,
    age: u8,
}

async fn get_user() -> Json<User> {
    let user = User {
        name: "Bob".to_string(),
        age: 25,
    };
    Json(user)
}

#[tokio::main]
async fn main() {
    let app = Router::new().route("/user", get(get_user));
    let addr = SocketAddr::from(([127, 0, 0, 1], 8080));
    
    axum::Server::bind(&addr)
        .serve(app.into_make_service())
        .await
        .unwrap();
}
```
📌 `Json(user)` → Axum에서 JSON 응답을 반환하는 방법

📌 `/user` 경로에서 JSON 데이터 반환

---

## 🏗️ Actix vs Axum 비교

| 항목  | Actix-web | Axum |
|--------|----------|------|
| 실행 방식 | Actor 기반 | Tokio 기반 |
| 성능 | 매우 빠름 | 빠름 |
| 사용성 | 비교적 복잡 | 단순한 API |
| 상태 관리 | Actor 패턴 사용 가능 | `tower::Service` 활용 |
| 추천 용도 | 고성능 API 서버 | 간결한 웹 애플리케이션 |

---

## 🎯 마무리
이 장에서는 **Rust의 웹 백엔드 개발**을 배웠습니다.

- `Actix-web`을 사용하여 **고성능 API 서버 구축**
- `Axum`을 활용하여 **간단하고 빠른 웹 애플리케이션 개발**
- **JSON API 구축 및 경로 설정 방법** 이해
- Actix와 Axum의 **특징 비교 및 활용 사례 분석**

다음 장에서는 **Rust의 마이크로서비스 아키텍처 및 gRPC 통신**을 배워보겠습니다! 🚀
