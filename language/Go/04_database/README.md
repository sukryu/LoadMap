# 04 Database & Caching in Go 📊

이 디렉토리는 **Go**를 사용하여 데이터베이스와 캐싱을 효과적으로 다루는 방법을 학습할 수 있도록 구성되었습니다.  
여기에서는 관계형 데이터베이스와 NoSQL 데이터베이스에 접근하는 방법, ORM 라이브러리(GORM, Ent 등)의 활용, 그리고 쿼리 최적화 기법과 캐싱 전략을 Go 환경에 맞춰 다룹니다.

---

## 디렉토리 구조 📁

```plaintext
04-database/
├── README.md                  # 이 가이드 문서
├── go-sql/                    # Go를 이용한 SQL 데이터베이스 활용 예제 (PostgreSQL, MySQL, SQLite 등)
├── nosql-go/                  # Go를 이용한 NoSQL 데이터베이스 활용 (MongoDB, Redis 등)
└── query-optimization/         # Go 환경에서의 SQL 쿼리 최적화 기법 및 모범 사례
```

- **go-sql/**:  
  - Go의 표준 라이브러리 `database/sql`과 인기 ORM 라이브러리(GORM, Ent 등)를 활용하여 관계형 데이터베이스와 상호작용하는 방법을 학습합니다.
  
- **nosql-go/**:  
  - Go 언어로 MongoDB, Redis 등 NoSQL 데이터베이스에 접속하고 데이터를 처리하는 예제와 패턴을 다룹니다.
  
- **query-optimization/**:  
  - SQL 쿼리 작성, 인덱스 설계, 연결 풀링 및 트랜잭션 관리 등 데이터베이스 성능 최적화 기법을 Go 환경에서 적용하는 방법을 정리합니다.

---

## 학습 목표 🎯

- **Go에서의 SQL 활용**:  
  - `database/sql` 패키지와 GORM 등을 통해 관계형 데이터베이스와 연동하는 방법 이해  
  - Prepared Statement, 트랜잭션 관리, 커넥션 풀링 등 핵심 기법 습득

- **NoSQL 활용**:  
  - Go 클라이언트를 사용해 MongoDB, Redis와 같은 NoSQL 데이터베이스와 상호작용하는 방법 익히기  
  - 캐싱 전략과 데이터 모델링 기법 적용

- **쿼리 최적화**:  
  - 효율적인 SQL 쿼리 작성법, 인덱스 활용, 실행 계획 분석 등 데이터베이스 성능 최적화 기법 이해

---

## 시작하기 🚀

### 1. 필수 도구 설치
- Go 최신 버전 설치: [Download Go](https://go.dev/dl/)
- 데이터베이스 설치 또는 Docker 컨테이너 활용 (예: PostgreSQL, MySQL, MongoDB, Redis)
- Git 클라이언트 설치

### 2. 프로젝트 클론하기
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/04-database
```

### 3. 예제 실행
#### a. SQL 데이터베이스 예제 (go-sql)
```bash
cd go-sql
go run main.go
```

#### b. NoSQL 데이터베이스 예제 (nosql-go)
```bash
cd ../nosql-go
go run main.go
```

#### c. 쿼리 최적화 실습
- `query-optimization` 폴더 내의 문서를 참고하여 인덱스 설계, 준비된 쿼리, 트랜잭션 및 커넥션 풀링 기법을 실습해 보세요.

---

## Best Practices & Tips 💡

- **커넥션 풀링**: `database/sql`은 기본적으로 커넥션 풀링을 제공하므로, 적절한 설정으로 데이터베이스 연결 효율을 극대화하세요.
- **Prepared Statements**: SQL 인젝션 방지와 성능 향상을 위해 반드시 Prepared Statement를 사용하세요.
- **ORM 활용**: GORM 또는 Ent와 같은 ORM을 사용해 코드의 가독성을 높이고, 복잡한 SQL 쿼리를 추상화하세요.
- **에러 처리**: 데이터베이스 작업 시 발생하는 에러를 꼼꼼하게 처리하여, 문제 발생 시 빠른 대응이 가능하도록 합니다.
- **캐싱 전략**: Redis와 같은 캐싱 시스템을 활용하여, 자주 조회되는 데이터를 빠르게 처리하세요.

---

## 참고 자료 📚

- [Go database/sql Package Documentation](https://pkg.go.dev/database/sql)
- [GORM 공식 문서](https://gorm.io/)
- [MongoDB Go Driver Documentation](https://www.mongodb.com/docs/drivers/go/current/)
- [Redis Go Client (go-redis)](https://github.com/go-redis/redis)
- [SQL Tuning Guide](https://www.sqltuning.com/)

---

데이터베이스와 캐싱은 백엔드 시스템의 핵심입니다.  
Go에서 효율적으로 데이터베이스와 상호작용하는 방법을 익혀, 고성능 애플리케이션을 구축해 보세요! Happy Coding! 🎉