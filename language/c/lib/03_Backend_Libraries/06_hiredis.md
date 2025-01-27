# Hiredis 라이브러리 사용 가이드

Hiredis는 C 언어 기반의 경량화된 Redis 클라이언트 라이브러리입니다. Redis 서버와의 통신을 위해 설계되었으며, 빠르고 간단하게 Redis 데이터를 처리할 수 있습니다.

---

## 1. 주요 특징

1. **경량성**: 빠르고 간단한 API 제공.
2. **Redis 프로토콜 지원**: Redis의 모든 명령어를 처리 가능.
3. **비동기 및 동기 통신**: 동기와 비동기 API를 모두 지원.
4. **이식성**: 다양한 플랫폼에서 작동.

---

## 2. 설치

### 2.1 설치 방법

**Ubuntu/Linux:**
```bash
git clone https://github.com/redis/hiredis.git
cd hiredis
make
sudo make install
```

**macOS:**
```bash
brew install hiredis
```

**Windows:**
- Windows용 빌드를 지원하는 저장소를 참고하거나, WSL에서 설치.

---

## 3. 주요 구성 요소

### 3.1 동기 API
동기식 Redis 명령어 처리를 지원하며, 간단한 작업에 적합합니다.

### 3.2 비동기 API
이벤트 기반 비동기 Redis 처리를 지원하며, 대규모 네트워크 애플리케이션에 적합합니다.

---

## 4. 주요 함수

### 4.1 연결

#### `redisConnect`
- **설명**: Redis 서버에 동기적으로 연결합니다.
- **형식**: `redisContext *redisConnect(const char *ip, int port);`

**예제:**
```c
#include <hiredis/hiredis.h>
#include <stdio.h>

int main() {
    redisContext *c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err) {
        printf("Redis 연결 실패: %s\n", c ? c->errstr : "메모리 부족");
        return 1;
    }

    printf("Redis 연결 성공\n");
    redisFree(c);
    return 0;
}
```

**출력:**
```
Redis 연결 성공
```

---

### 4.2 명령어 실행

#### `redisCommand`
- **설명**: Redis 명령어를 실행하고 결과를 반환합니다.
- **형식**: `void *redisCommand(redisContext *c, const char *format, ...);`

**예제:**
```c
#include <hiredis/hiredis.h>
#include <stdio.h>

int main() {
    redisContext *c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err) {
        printf("Redis 연결 실패: %s\n", c ? c->errstr : "메모리 부족");
        return 1;
    }

    redisReply *reply = redisCommand(c, "SET %s %s", "key", "value");
    printf("SET 명령어 결과: %s\n", reply->str);
    freeReplyObject(reply);

    reply = redisCommand(c, "GET %s", "key");
    printf("GET 명령어 결과: %s\n", reply->str);
    freeReplyObject(reply);

    redisFree(c);
    return 0;
}
```

**출력:**
```
SET 명령어 결과: OK
GET 명령어 결과: value
```

---

### 4.3 비동기 API

#### `redisAsyncConnect`
- **설명**: Redis 서버에 비동기적으로 연결합니다.
- **형식**: `redisAsyncContext *redisAsyncConnect(const char *ip, int port);`

#### `redisAsyncCommand`
- **설명**: 비동기 Redis 명령어를 실행합니다.
- **형식**: `int redisAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void *privdata, const char *format, ...);`

**예제:**
```c
#include <hiredis/async.h>
#include <hiredis/adapters/libevent.h>
#include <event2/event.h>
#include <stdio.h>

void getCallback(redisAsyncContext *c, void *r, void *privdata) {
    redisReply *reply = (redisReply *)r;
    if (reply == NULL) return;
    printf("GET 명령어 결과: %s\n", reply->str);
    redisAsyncDisconnect(c);
}

int main() {
    struct event_base *base = event_base_new();
    redisAsyncContext *c = redisAsyncConnect("127.0.0.1", 6379);
    if (c->err) {
        printf("Redis 연결 실패: %s\n", c->errstr);
        return 1;
    }

    redisLibeventAttach(c, base);
    redisAsyncCommand(c, NULL, NULL, "SET %s %s", "key", "value");
    redisAsyncCommand(c, getCallback, NULL, "GET %s", "key");

    event_base_dispatch(base);
    return 0;
}
```

**출력:**
```
GET 명령어 결과: value
```

---

## 5. 실습 예제

### 간단한 키-값 저장 및 조회 프로그램
**코드:**
```c
#include <hiredis/hiredis.h>
#include <stdio.h>
#include <string.h>

int main() {
    redisContext *c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err) {
        printf("Redis 연결 실패: %s\n", c ? c->errstr : "메모리 부족");
        return 1;
    }

    char key[100], value[100];

    printf("저장할 키: ");
    scanf("%s", key);
    printf("저장할 값: ");
    scanf("%s", value);

    redisReply *reply = redisCommand(c, "SET %s %s", key, value);
    freeReplyObject(reply);

    reply = redisCommand(c, "GET %s", key);
    printf("%s의 값: %s\n", key, reply->str);
    freeReplyObject(reply);

    redisFree(c);
    return 0;
}
```

**출력 (입력 예시):**
```
저장할 키: name
저장할 값: Alice
name의 값: Alice
```

---

## 6. 사용 시 주의사항

1. **메모리 관리**: `redisReply`는 사용 후 반드시 `freeReplyObject`로 해제해야 합니다.
2. **연결 상태 확인**: 연결 실패 여부를 항상 확인하고 적절히 처리하세요.
3. **멀티스레드 환경**: Hiredis는 멀티스레드에서 안전하지 않으므로 스레드마다 별도의 연결을 사용해야 합니다.

---

Hiredis는 경량화된 Redis 클라이언트로, 빠르고 안정적인 데이터 처리를 제공합니다. 위의 예제와 기능을 참고하여 Redis와 효율적으로 통신하는 애플리케이션을 작성해보세요.