# ZeroMQ 라이브러리 사용 가이드

ZeroMQ는 고성능 비동기 메시징 라이브러리로, 네트워크 소켓을 추상화하여 간단하면서도 강력한 메시지 큐를 제공합니다. ZeroMQ는 다양한 통신 패턴을 지원하며, 멀티스레드 및 분산 애플리케이션 개발에 적합합니다.

---

## 1. 주요 특징

1. **고성능**: 네트워크 및 멀티스레드 환경에서 빠르고 효율적인 메시징 지원.
2. **유연성**: TCP, IPC, 멀티캐스트 등 다양한 전송 프로토콜 지원.
3. **다양한 통신 패턴**:
   - 요청-응답 (REQ-REP)
   - 게시-구독 (PUB-SUB)
   - 푸시-풀 (PUSH-PULL)
   - 라우터-딜러 (ROUTER-DEALER)
4. **언어 독립성**: C, C++, Python 등 여러 언어에서 사용 가능.
5. **비동기 메시징**: 블로킹과 논블로킹 통신 모두 지원.

---

## 2. 설치

### 2.1 설치 방법

**Ubuntu/Linux:**
```bash
sudo apt-get update
sudo apt-get install libzmq3-dev
```

**macOS:**
```bash
brew install zeromq
```

**Windows:**
- ZeroMQ 공식 웹사이트(https://zeromq.org/)에서 바이너리 다운로드 후 설치.

### 2.2 CMake 프로젝트 설정
```cmake
find_package(ZeroMQ REQUIRED)

add_executable(my_project main.cpp)
target_link_libraries(my_project PRIVATE libzmq)
```

---

## 3. 주요 구성 요소

### 3.1 `zmq_context`
- **설명**: ZeroMQ의 모든 소켓이 공유하는 컨텍스트.
- **역할**: 리소스 관리 및 스레드 간 데이터 공유.

### 3.2 `zmq_socket`
- **설명**: ZeroMQ의 기본 통신 단위로, 다양한 소켓 타입을 생성.

### 3.3 소켓 타입
| 타입       | 설명                                         |
|------------|--------------------------------------------|
| `ZMQ_REQ`  | 요청 소켓 (REQ-REP 패턴의 클라이언트 역할). |
| `ZMQ_REP`  | 응답 소켓 (REQ-REP 패턴의 서버 역할).       |
| `ZMQ_PUB`  | 게시 소켓 (PUB-SUB 패턴에서 게시자).         |
| `ZMQ_SUB`  | 구독 소켓 (PUB-SUB 패턴에서 구독자).         |
| `ZMQ_PUSH` | 데이터 푸시 소켓 (PUSH-PULL 패턴의 송신자). |
| `ZMQ_PULL` | 데이터 풀 소켓 (PUSH-PULL 패턴의 수신자).   |

---

## 4. 주요 사용법

### 4.1 REQ-REP 패턴 (요청-응답)

#### 서버
**코드:**
```c
#include <zmq.h>
#include <stdio.h>
#include <string.h>

int main() {
    void *context = zmq_ctx_new();
    void *responder = zmq_socket(context, ZMQ_REP);
    zmq_bind(responder, "tcp://*:5555");

    while (1) {
        char buffer[256];
        zmq_recv(responder, buffer, 256, 0);
        printf("받은 메시지: %s\n", buffer);
        zmq_send(responder, "World", 5, 0);
    }

    zmq_close(responder);
    zmq_ctx_destroy(context);
    return 0;
}
```

#### 클라이언트
**코드:**
```c
#include <zmq.h>
#include <stdio.h>
#include <string.h>

int main() {
    void *context = zmq_ctx_new();
    void *requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requester, "tcp://localhost:5555");

    zmq_send(requester, "Hello", 5, 0);
    char buffer[256];
    zmq_recv(requester, buffer, 256, 0);
    printf("서버로부터 응답: %s\n", buffer);

    zmq_close(requester);
    zmq_ctx_destroy(context);
    return 0;
}
```

**출력:**
- 서버: `받은 메시지: Hello`
- 클라이언트: `서버로부터 응답: World`

---

### 4.2 PUB-SUB 패턴 (게시-구독)

#### 게시자
**코드:**
```c
#include <zmq.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    void *context = zmq_ctx_new();
    void *publisher = zmq_socket(context, ZMQ_PUB);
    zmq_bind(publisher, "tcp://*:5556");

    while (1) {
        zmq_send(publisher, "Topic1 Hello", 12, 0);
        sleep(1);
    }

    zmq_close(publisher);
    zmq_ctx_destroy(context);
    return 0;
}
```

#### 구독자
**코드:**
```c
#include <zmq.h>
#include <stdio.h>
#include <string.h>

int main() {
    void *context = zmq_ctx_new();
    void *subscriber = zmq_socket(context, ZMQ_SUB);
    zmq_connect(subscriber, "tcp://localhost:5556");
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "Topic1", 6);

    char buffer[256];
    while (1) {
        zmq_recv(subscriber, buffer, 256, 0);
        printf("받은 메시지: %s\n", buffer);
    }

    zmq_close(subscriber);
    zmq_ctx_destroy(context);
    return 0;
}
```

**출력:**
```
받은 메시지: Topic1 Hello
```

---

### 4.3 PUSH-PULL 패턴 (작업 분산)

#### 푸셔 (PUSH)
**코드:**
```c
#include <zmq.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    void *context = zmq_ctx_new();
    void *pusher = zmq_socket(context, ZMQ_PUSH);
    zmq_bind(pusher, "tcp://*:5557");

    for (int i = 0; i < 10; i++) {
        char msg[256];
        sprintf(msg, "작업 #%d", i);
        zmq_send(pusher, msg, strlen(msg), 0);
        sleep(1);
    }

    zmq_close(pusher);
    zmq_ctx_destroy(context);
    return 0;
}
```

#### 풀러 (PULL)
**코드:**
```c
#include <zmq.h>
#include <stdio.h>

int main() {
    void *context = zmq_ctx_new();
    void *puller = zmq_socket(context, ZMQ_PULL);
    zmq_connect(puller, "tcp://localhost:5557");

    char buffer[256];
    while (1) {
        zmq_recv(puller, buffer, 256, 0);
        printf("받은 작업: %s\n", buffer);
    }

    zmq_close(puller);
    zmq_ctx_destroy(context);
    return 0;
}
```

**출력:**
```
받은 작업: 작업 #0
받은 작업: 작업 #1
...
```

---

## 5. 사용 시 주의사항

1. **컨텍스트 관리**: `zmq_ctx_new`로 생성된 컨텍스트는 사용 후 반드시 `zmq_ctx_destroy`로 해제해야 합니다.
2. **소켓 관리**: 모든 소켓은 사용 후 `zmq_close`로 닫아야 합니다.
3. **비동기 처리**: ZeroMQ는 기본적으로 비동기적이므로, 데이터를 수신하지 못할 경우 코드가 블로킹될 수 있습니다. 적절한 타임아웃 설정이 필요합니다.
4. **스레드 안전성**: 각 스레드에서 별도의 소켓을 사용하는 것이 권장됩니다.

---

ZeroMQ는 다양한 통신 패턴과 고성능 메시징을 지원하는 강력한 라이브러리입니다. 위의 예제를 활용하여 네트워크 및 분산 애플리케이션을 설계하고 개발해보세요.

