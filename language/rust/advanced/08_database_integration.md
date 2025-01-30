# 🦀 Rust의 데이터베이스 연동 및 트랜잭션 관리 (PostgreSQL, MySQL, Diesel)

## 📌 개요
Rust는 강력한 데이터베이스 연동 기능을 제공하며, `Diesel`과 `SQLx` 같은 ORM/쿼리 빌더를 통해 **안전하고 효율적인 데이터베이스 조작**을 할 수 있습니다.

이 장에서는 **Rust에서 PostgreSQL 및 MySQL과 연동하는 방법, 트랜잭션 처리, 효율적인 데이터베이스 사용법**을 다뤄보겠습니다.

---

## 🚀 `Diesel`을 사용한 데이터베이스 연동

### 🏷️ Diesel 프로젝트 설정
```sh
cargo new diesel_project --bin
cd diesel_project
cargo add diesel dotenv
cargo install diesel_cli --no-default-features --features postgres
```
📌 `cargo add diesel dotenv` → Diesel ORM 및 환경 변수 관리 패키지 추가

📌 `cargo install diesel_cli --no-default-features --features postgres` → PostgreSQL 지원 Diesel CLI 설치

📌 MySQL을 사용할 경우 `--features mysql` 옵션 사용

---

### 🏗️ 데이터베이스 초기화 및 마이그레이션 설정
```sh
diesel setup
```
📌 `.env` 파일을 생성하고 데이터베이스 연결 정보를 설정

`.env` 파일 예제:
```
DATABASE_URL=postgres://user:password@localhost/mydatabase
```

마이그레이션 생성:
```sh
diesel migration generate create_users
```
`migrations/` 폴더 내 `up.sql`, `down.sql` 파일이 생성됨.

#### `up.sql` (테이블 생성)
```sql
CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    name VARCHAR NOT NULL,
    email VARCHAR UNIQUE NOT NULL
);
```

#### `down.sql` (테이블 삭제)
```sql
DROP TABLE users;
```
마이그레이션 적용:
```sh
diesel migration run
```

---

## 🔄 Diesel을 활용한 CRUD 연산

### 🏗️ Diesel 모델 및 스키마 설정
```rust
use diesel::prelude::*;

#[derive(Queryable, Insertable)]
#[table_name = "users"]
pub struct User {
    pub id: i32,
    pub name: String,
    pub email: String,
}
```
📌 `#[derive(Queryable, Insertable)]` → Diesel의 ORM 기능을 위한 매크로

📌 `table_name = "users"` → 데이터베이스 테이블 매핑

---

### 🏷️ 데이터 삽입
```rust
use diesel::prelude::*;
use diesel::pg::PgConnection;

fn insert_user(conn: &PgConnection, name: &str, email: &str) {
    use crate::schema::users;
    let new_user = User {
        id: 0,
        name: name.to_string(),
        email: email.to_string(),
    };
    diesel::insert_into(users::table)
        .values(&new_user)
        .execute(conn)
        .expect("사용자 삽입 실패");
}
```
📌 `diesel::insert_into(users::table).values(&new_user).execute(conn)` → 레코드 삽입

---

### 🏷️ 데이터 조회
```rust
fn get_users(conn: &PgConnection) -> Vec<User> {
    use crate::schema::users::dsl::*;
    users.load::<User>(conn).expect("사용자 목록 불러오기 실패")
}
```
📌 `users.load::<User>(conn)` → 모든 사용자 조회

---

### 🏷️ 데이터 업데이트
```rust
fn update_user_email(conn: &PgConnection, user_id: i32, new_email: &str) {
    use crate::schema::users::dsl::*;
    diesel::update(users.filter(id.eq(user_id)))
        .set(email.eq(new_email))
        .execute(conn)
        .expect("이메일 업데이트 실패");
}
```
📌 `diesel::update().set().execute()` → 특정 필드 값 업데이트

---

### 🏷️ 데이터 삭제
```rust
fn delete_user(conn: &PgConnection, user_id: i32) {
    use crate::schema::users::dsl::*;
    diesel::delete(users.filter(id.eq(user_id)))
        .execute(conn)
        .expect("사용자 삭제 실패");
}
```
📌 `diesel::delete(users.filter(id.eq(user_id))).execute(conn)` → 특정 사용자 삭제

---

## 🚀 트랜잭션 관리
Diesel에서 트랜잭션을 사용하여 여러 데이터베이스 연산을 원자적으로 실행할 수 있습니다.

```rust
use diesel::prelude::*;
use diesel::pg::PgConnection;

fn transaction_example(conn: &PgConnection) {
    conn.transaction::<_, diesel::result::Error, _>(|| {
        insert_user(conn, "Alice", "alice@example.com");
        insert_user(conn, "Bob", "bob@example.com");
        Ok(())
    }).expect("트랜잭션 실패");
}
```
📌 `conn.transaction(|| { ... })` → 트랜잭션 내에서 여러 SQL 실행

📌 **중간에 오류가 발생하면 자동으로 롤백**

---

## 🔄 SQLx를 활용한 비동기 데이터베이스 연동
`SQLx`는 비동기 Rust 데이터베이스 드라이버로, Diesel과 달리 **동적 SQL 및 런타임 검사**를 지원합니다.

### 🏗️ SQLx 프로젝트 설정
```sh
cargo add sqlx --features postgres, runtime-tokio-rustls
```
📌 `cargo add sqlx --features postgres` → PostgreSQL 비동기 지원

---

### 🏷️ SQLx를 이용한 비동기 연결
```rust
use sqlx::{PgPool, query};
use tokio;

#[tokio::main]
async fn main() {
    let pool = PgPool::connect("postgres://user:password@localhost/mydatabase").await.unwrap();
    let row: (String,) = query!("SELECT name FROM users WHERE id = $1", 1)
        .fetch_one(&pool)
        .await
        .unwrap();
    println!("사용자 이름: {}", row.0);
}
```
📌 `PgPool::connect()` → 비동기 데이터베이스 연결 풀 생성

📌 `query!("SELECT ...")` → SQL 실행 및 결과 반환

---

## 🎯 마무리
이 장에서는 **Rust의 데이터베이스 연동 및 트랜잭션 관리**를 배웠습니다.

- `Diesel`을 사용한 **ORM 기반 데이터베이스 연동**
- `SQLx`를 활용한 **비동기 SQL 실행**
- **CRUD 연산 및 트랜잭션 처리 방법**
- PostgreSQL 및 MySQL 연동 사례

다음 장에서는 **Rust의 컨테이너화 및 Kubernetes 배포**를 다뤄보겠습니다! 🚀