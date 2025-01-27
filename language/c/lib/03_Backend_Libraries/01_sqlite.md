# SQLite 라이브러리 사용 가이드

SQLite는 경량의 관계형 데이터베이스로, 서버가 필요 없는 임베디드 데이터베이스 솔루션입니다. C와 함께 자주 사용되며, 간단한 애플리케이션부터 대규모 시스템의 구성 요소까지 폭넓게 활용됩니다.

---

## 1. SQLite 주요 특징

1. **서버리스**: 독립적인 데이터베이스 파일로 동작하며 별도의 서버 프로세스가 필요하지 않습니다.
2. **임베디드**: SQLite는 애플리케이션과 함께 동작하며, 데이터베이스 파일은 로컬 파일 시스템에 저장됩니다.
3. **ACID 지원**: 트랜잭션을 통해 데이터 무결성을 보장합니다.
4. **크로스 플랫폼**: 다양한 운영 체제에서 동일하게 작동합니다.
5. **SQL 표준 준수**: SQL-92의 핵심 기능을 대부분 지원합니다.

---

## 2. 설치 및 초기화

### 2.1 설치
SQLite는 `sqlite3` 라이브러리로 제공되며, 대부분의 시스템에 기본적으로 포함되어 있습니다.

**Ubuntu/Linux:**
```bash
sudo apt-get update
sudo apt-get install sqlite3 libsqlite3-dev
```

**macOS:**
```bash
brew install sqlite
```

**Windows:**
- SQLite 공식 웹사이트(https://www.sqlite.org/)에서 다운로드하여 설치.

### 2.2 초기화
SQLite 데이터베이스 파일은 프로그램 실행 중 생성되며, `sqlite3_open` 함수로 초기화됩니다.

**기본 코드:**
```c
#include <sqlite3.h>
#include <stdio.h>

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("example.db", &db);

    if (rc) {
        printf("데이터베이스 열기 실패: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    printf("데이터베이스 연결 성공\n");
    sqlite3_close(db);
    return 0;
}
```

**출력:**
```
데이터베이스 연결 성공
```

---

## 3. 주요 함수

### 3.1 데이터베이스 열기/닫기

#### `sqlite3_open`
- **설명**: 데이터베이스 연결을 생성합니다.
- **형식**: `int sqlite3_open(const char *filename, sqlite3 **ppDb);`

#### `sqlite3_close`
- **설명**: 데이터베이스 연결을 닫습니다.
- **형식**: `int sqlite3_close(sqlite3 *db);`

---

### 3.2 SQL 실행

#### `sqlite3_exec`
- **설명**: SQL 명령을 실행합니다.
- **형식**: `int sqlite3_exec(sqlite3 *db, const char *sql, sqlite3_callback callback, void *data, char **errmsg);`

**예제:**
```c
#include <sqlite3.h>
#include <stdio.h>

int main() {
    sqlite3 *db;
    char *err_msg = NULL;

    sqlite3_open("example.db", &db);

    const char *sql = "CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY, name TEXT);";

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        printf("SQL 실행 실패: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("테이블 생성 성공\n");
    }

    sqlite3_close(db);
    return 0;
}
```

**출력:**
```
테이블 생성 성공
```

---

### 3.3 SQL 실행 결과 처리

#### `sqlite3_prepare_v2`
- **설명**: SQL 명령을 실행 준비 상태로 변환합니다.
- **형식**: `int sqlite3_prepare_v2(sqlite3 *db, const char *zSql, int nByte, sqlite3_stmt **ppStmt, const char **pzTail);`

#### `sqlite3_step`
- **설명**: SQL 명령을 실행합니다.
- **결과**:
  - `SQLITE_ROW`: 다음 결과 행이 존재함.
  - `SQLITE_DONE`: 명령이 완료됨.

#### `sqlite3_finalize`
- **설명**: SQL 명령 실행이 끝난 후 메모리를 해제합니다.
- **형식**: `int sqlite3_finalize(sqlite3_stmt *pStmt);`

**예제:**
```c
#include <sqlite3.h>
#include <stdio.h>

int main() {
    sqlite3 *db;
    sqlite3_stmt *stmt;

    sqlite3_open("example.db", &db);

    const char *sql = "SELECT id, name FROM users;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char *name = (const char *)sqlite3_column_text(stmt, 1);
        printf("ID: %d, Name: %s\n", id, name);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}
```

**출력 (예시):**
```
ID: 1, Name: Alice
ID: 2, Name: Bob
```

---

## 4. 고급 기능

### 4.1 트랜잭션 관리
SQLite는 트랜잭션을 통해 데이터 무결성을 보장합니다.

**예제:**
```c
sqlite3_exec(db, "BEGIN TRANSACTION;", 0, 0, 0);
sqlite3_exec(db, "INSERT INTO users (name) VALUES ('Charlie');", 0, 0, 0);
sqlite3_exec(db, "COMMIT;", 0, 0, 0);
```

---

### 4.2 에러 처리
SQLite 함수는 실행 결과를 반환하며, 성공 여부를 확인할 수 있습니다.

| 반환 값         | 설명                |
|----------------|-------------------|
| `SQLITE_OK`    | 성공                |
| `SQLITE_ERROR` | SQL 오류 또는 데이터베이스 손상 |
| `SQLITE_BUSY`  | 데이터베이스가 바쁨   |
| `SQLITE_MISUSE`| 함수 호출이 잘못됨   |

**에러 메시지 출력:**
```c
if (rc != SQLITE_OK) {
    printf("오류 발생: %s\n", sqlite3_errmsg(db));
}
```

---

### 4.3 인덱스 생성 및 활용
인덱스를 사용하면 쿼리 성능을 크게 향상시킬 수 있습니다.

**예제:**
```c
const char *create_index = "CREATE INDEX idx_users_name ON users(name);";
sqlite3_exec(db, create_index, 0, 0, &err_msg);
```

---

### 4.4 데이터베이스 백업
SQLite는 데이터베이스를 백업하는 기능을 제공합니다.

**예제:**
```c
sqlite3 *backup_db;
sqlite3_backup *backup = sqlite3_backup_init(backup_db, "main", db, "main");
sqlite3_backup_step(backup, -1);
sqlite3_backup_finish(backup);
```

---

SQLite는 가볍고 강력한 데이터베이스로, 다양한 애플리케이션에서 효율적으로 사용될 수 있습니다. 위의 예제와 기능을 참고하여 SQLite를 프로젝트에 통합해보세요.

