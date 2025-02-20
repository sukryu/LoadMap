# Go SQL Database Integration 📊

이 디렉토리는 Go에서 SQL 데이터베이스와 상호작용하는 방법에 대해 다룹니다.  
Go의 `database/sql` 패키지와 다양한 SQL 드라이버(PostgreSQL, MySQL, SQLite 등)를 활용하여, 데이터베이스 연결, 쿼리 실행, 트랜잭션 관리 및 커넥션 풀링 등 실무에 바로 적용할 수 있는 기법을 학습할 수 있습니다.

---

## What You'll Learn 🎯

- **기본 연결 및 쿼리 실행**:  
  - `database/sql` 패키지를 사용하여 데이터베이스에 연결하고, 쿼리를 실행하는 방법을 익힙니다.
  
- **Prepared Statement 및 트랜잭션 관리**:  
  - SQL 인젝션 방지와 데이터 일관성을 위한 Prepared Statement 및 트랜잭션 처리 기법을 학습합니다.
  
- **커넥션 풀링**:  
  - 데이터베이스 연결 수를 관리하여, 효율적인 리소스 사용과 성능 최적화를 달성하는 방법을 이해합니다.
  
- **드라이버 활용**:  
  - PostgreSQL, MySQL, SQLite 등 주요 SQL 드라이버를 이용한 실습 예제를 통해, 각 데이터베이스의 특성을 파악합니다.

---

## Directory Structure 📁

```plaintext
go-sql/
├── main.go                           # 기본 데이터베이스 연동 예제
└── examples/
    ├── 01_connection_pooling.go      # 연결 풀 관리
    ├── 02_prepared_statements.go     # 준비된 구문 활용
    ├── 03_transactions.go            # 트랜잭션 처리
    ├── 04_batch_operations.go        # 배치 작업 처리
    ├── 05_query_builder.go           # 동적 쿼리 생성
    ├── 06_error_handling.go          # 에러 처리 전략
    ├── 07_migration_patterns.go      # 마이그레이션 관리
    ├── 08_query_monitoring.go        # 쿼리 모니터링
    ├── 09_context_usage.go           # 컨텍스트 활용
    └── 10_replication_handling.go    # 복제 처리
```

- **main.go**: 기본적인 데이터베이스 연결과 쿼리 실행을 보여주는 샘플 코드가 포함되어 있습니다.
- **examples/**: 다양한 실습 예제와 고급 기능(트랜잭션 관리, Prepared Statement 활용, 커넥션 풀링 등)을 다룹니다.

---

## Getting Started 🚀

### 1. Prerequisites
- Go 최신 버전 설치: [Download Go](https://go.dev/dl/)
- 사용하려는 SQL 데이터베이스(PostgreSQL, MySQL, SQLite 등)가 설치되어 있거나, Docker 컨테이너를 통해 실행 중인지 확인하세요.

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/04-go-sql
```

### 3. 예제 코드 실행
```bash
go run main.go
```
- 실행 결과를 통해 데이터베이스 연결 및 쿼리 결과를 확인해 보세요.

---

## Example Code Snippet 📄

아래는 PostgreSQL을 사용한 간단한 데이터베이스 연결 예제입니다:

```go
package main

import (
    "database/sql"
    "fmt"
    "log"

    _ "github.com/lib/pq" // PostgreSQL 드라이버
)

func main() {
    // PostgreSQL 연결 문자열 (환경에 맞게 수정)
    connStr := "user=youruser password=yourpassword dbname=yourdb sslmode=disable"
    db, err := sql.Open("postgres", connStr)
    if err != nil {
        log.Fatalf("데이터베이스 연결 실패: %v", err)
    }
    defer db.Close()

    // 데이터베이스 연결 확인
    err = db.Ping()
    if err != nil {
        log.Fatalf("데이터베이스 핑 실패: %v", err)
    }
    fmt.Println("데이터베이스 연결 성공!")

    // 간단한 쿼리 실행: 현재 시간 조회
    var now string
    err = db.QueryRow("SELECT NOW()").Scan(&now)
    if err != nil {
        log.Fatalf("쿼리 실행 실패: %v", err)
    }
    fmt.Println("현재 시간:", now)
}
```

이 예제는 PostgreSQL 데이터베이스에 연결하여 현재 시간을 조회하는 기본적인 작업을 수행합니다.

---

## Best Practices & Tips 💡

- **자원 관리**:  
  - 데이터베이스 연결 후 `defer db.Close()`를 사용하여 리소스를 반드시 반환하세요.
  
- **Prepared Statements**:  
  - 보안과 성능 개선을 위해 SQL 쿼리는 Prepared Statement로 실행하여, SQL 인젝션 공격을 방지하세요.
  
- **트랜잭션 처리**:  
  - 데이터 일관성을 위해 여러 쿼리를 하나의 트랜잭션 내에서 처리하고, 에러 발생 시 적절히 롤백하세요.
  
- **커넥션 풀링**:  
  - `db.SetMaxOpenConns()`, `db.SetMaxIdleConns()` 등의 설정을 통해 데이터베이스 커넥션을 효율적으로 관리하세요.
  
- **에러 핸들링**:  
  - 각 단계에서 발생할 수 있는 에러를 꼼꼼하게 처리하여, 문제 발생 시 빠른 대응이 가능하도록 합니다.

---

## Next Steps

- **다양한 SQL 드라이버 학습**:  
  - PostgreSQL 외에도 MySQL, SQLite 등의 드라이버 사용법을 비교하며 학습하세요.
  
- **ORM 활용**:  
  - GORM이나 Ent와 같은 ORM 라이브러리를 사용해, SQL 작성 없이 데이터베이스 연동을 추상화하는 방법을 익혀보세요.
  
- **고급 트랜잭션 관리**:  
  - 복잡한 트랜잭션 처리 및 쿼리 최적화 기법을 학습하고, 실무 예제를 통해 적용해 보세요.

---

## References 📚

- [Go database/sql Package Documentation](https://pkg.go.dev/database/sql)
- [PostgreSQL Go Driver (lib/pq)](https://github.com/lib/pq)
- [MySQL Go Driver (go-sql-driver/mysql)](https://github.com/go-sql-driver/mysql)
- [GORM Documentation](https://gorm.io/)

---

Go에서 SQL 데이터베이스와 상호작용하는 것은 데이터 중심 애플리케이션의 핵심입니다.  
이 자료를 통해 효율적이고 안정적인 데이터 처리를 구현하고, 실무에 바로 적용해 보세요! Happy SQL Coding! 🚀