# POSIX 소켓 API 사용 가이드

POSIX 소켓 API는 네트워크 프로그래밍의 표준 인터페이스로, TCP/IP 및 UDP 프로토콜을 사용하여 데이터를 송수신하는 프로그램을 작성하는 데 사용됩니다. 이 가이드는 소켓 생성, 연결, 데이터 전송, 및 서버/클라이언트 구현을 포함한 POSIX 소켓 프로그래밍의 핵심을 다룹니다.

---

## 1. 주요 함수

### 1.1 소켓 생성과 설정

#### `socket`
- **설명**: 소켓을 생성합니다.
- **형식**: `int socket(int domain, int type, int protocol);`
- **매개변수**:
  - `domain`: 통신 도메인 (예: `AF_INET` IPv4, `AF_INET6` IPv6).
  - `type`: 소켓 타입 (예: `SOCK_STREAM` TCP, `SOCK_DGRAM` UDP).
  - `protocol`: 프로토콜 지정 (보통 0으로 설정하여 기본 프로토콜 사용).

**예제:**
```c
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
    perror("소켓 생성 실패");
    return 1;
}
```

---

### 1.2 주소 바인딩

#### `bind`
- **설명**: 소켓을 특정 IP 주소와 포트 번호에 연결합니다.
- **형식**: `int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`
- **매개변수**:
  - `sockfd`: 소켓 파일 디스크립터.
  - `addr`: 연결할 주소 정보.
  - `addrlen`: 주소 구조체 크기.

**예제:**
```c
struct sockaddr_in serv_addr;
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(8080);

if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("바인딩 실패");
    return 1;
}
```

---

### 1.3 연결 대기 및 수락 (TCP)

#### `listen`
- **설명**: 소켓을 연결 대기 상태로 설정합니다.
- **형식**: `int listen(int sockfd, int backlog);`
- **매개변수**:
  - `sockfd`: 소켓 파일 디스크립터.
  - `backlog`: 대기열 크기.

#### `accept`
- **설명**: 대기 중인 클라이언트 연결을 수락합니다.
- **형식**: `int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);`
- **매개변수**:
  - `sockfd`: 수신 소켓 파일 디스크립터.
  - `addr`: 연결된 클라이언트 주소 정보.
  - `addrlen`: 주소 구조체 크기.

**예제:**
```c
listen(sockfd, 5);
struct sockaddr_in cli_addr;
socklen_t cli_len = sizeof(cli_addr);
int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);
if (newsockfd < 0) {
    perror("연결 수락 실패");
    return 1;
}
```

---

### 1.4 데이터 송수신

#### `send` / `recv`
- **설명**: 데이터 전송과 수신을 수행합니다 (TCP).
- **형식**:
  - `ssize_t send(int sockfd, const void *buf, size_t len, int flags);`
  - `ssize_t recv(int sockfd, void *buf, size_t len, int flags);`

**예제:**
```c
char buffer[1024] = "Hello, Client!";
send(newsockfd, buffer, strlen(buffer), 0);

recv(newsockfd, buffer, sizeof(buffer) - 1, 0);
printf("클라이언트로부터 받은 데이터: %s\n", buffer);
```

#### `sendto` / `recvfrom`
- **설명**: 데이터 전송과 수신을 수행합니다 (UDP).
- **형식**:
  - `ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);`
  - `ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);`

**예제:**
```c
struct sockaddr_in cli_addr;
char buffer[1024] = "Hello, UDP Client!";
sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&cli_addr, sizeof(cli_addr));

recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&cli_addr, &cli_len);
printf("UDP 클라이언트로부터 받은 데이터: %s\n", buffer);
```

---

## 2. TCP 서버/클라이언트 예제

### TCP 서버
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("소켓 생성 실패");
        return 1;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8080);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("바인딩 실패");
        return 1;
    }

    listen(sockfd, 5);

    struct sockaddr_in cli_addr;
    socklen_t cli_len = sizeof(cli_addr);
    int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);

    char buffer[1024];
    recv(newsockfd, buffer, sizeof(buffer) - 1, 0);
    printf("클라이언트로부터 받은 메시지: %s\n", buffer);

    close(newsockfd);
    close(sockfd);
    return 0;
}
```

---

### TCP 클라이언트
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("소켓 생성 실패");
        return 1;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("서버 연결 실패");
        return 1;
    }

    char buffer[1024] = "Hello, Server!";
    send(sockfd, buffer, strlen(buffer), 0);

    close(sockfd);
    return 0;
}
```

---

## 3. 사용 시 주의사항

1. **포트 재사용**: 서버 실행 중 중단되었을 때 `SO_REUSEADDR`를 설정하여 포트 재사용을 허용합니다.
   ```c
   int opt = 1;
   setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
   ```

2. **에러 처리**: 각 함수 호출 결과를 확인하고 적절히 처리해야 합니다.
3. **멀티스레드/비동기**: 대규모 클라이언트 지원이 필요한 경우 멀티스레드 또는 비동기 I/O를 고려하세요.

---

POSIX 소켓 API는 네트워크 프로그래밍의 핵심으로, TCP/UDP 통신 애플리케이션을 작성하는 데 필수적입니다. 위의 예제를 활용하여 네트워크 기반 애플리케이션을 개발해보세요.

