# 03. Network Programming

## 1. 네트워크 프로그래밍 기초

### 네트워크 프로그래밍이란?
네트워크 프로그래밍은 컴퓨터 네트워크를 통해 데이터를 교환하거나 서비스를 제공하는 프로그램을 작성하는 기술입니다. C 언어는 TCP/IP 프로토콜과 같은 저수준 네트워크 작업에 적합하며, 효율적인 네트워크 애플리케이션 개발을 지원합니다.

### 주요 개념
1. **소켓 (Socket)**: 네트워크 통신의 끝점을 나타냅니다.
2. **프로토콜**: 데이터 교환을 정의하는 규칙 (예: TCP, UDP).
3. **IP 주소와 포트 번호**: 네트워크 상에서 장치와 서비스를 식별합니다.

---

## 2. 소켓 프로그래밍

### 소켓 생성과 설정

#### 주요 함수
| 함수              | 설명                                   |
|-------------------|--------------------------------------|
| `socket()`        | 소켓 생성.                           |
| `bind()`          | 소켓에 IP 주소와 포트 번호 할당.      |
| `listen()`        | 클라이언트 연결 요청 대기.            |
| `accept()`        | 클라이언트 연결 요청 수락.            |
| `connect()`       | 서버에 연결 요청.                    |
| `send()`          | 데이터를 송신.                        |
| `recv()`          | 데이터를 수신.                        |
| `close()`         | 소켓 닫기.                           |

#### 소켓 생성 예제
```c
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);  // TCP 소켓 생성
    if (server_fd == -1) {
        perror("소켓 생성 실패");
        return 1;
    }
    printf("소켓 생성 성공\n");
    return 0;
}
```

---

### TCP 서버-클라이언트 통신

#### TCP 서버 예제
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("소켓 생성 실패");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("바인딩 실패");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("리스닝 실패");
        exit(EXIT_FAILURE);
    }

    printf("서버 대기 중...\n");
    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd < 0) {
        perror("클라이언트 연결 실패");
        exit(EXIT_FAILURE);
    }

    read(client_fd, buffer, BUFFER_SIZE);
    printf("클라이언트로부터 받은 메시지: %s\n", buffer);

    char* response = "Hello, Client!";
    send(client_fd, response, strlen(response), 0);

    close(client_fd);
    close(server_fd);
    return 0;
}
```

#### TCP 클라이언트 예제
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE] = {0};

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("소켓 생성 실패");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("IP 주소 변환 실패");
        exit(EXIT_FAILURE);
    }

    if (connect(client_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("서버 연결 실패");
        exit(EXIT_FAILURE);
    }

    char* message = "Hello, Server!";
    send(client_fd, message, strlen(message), 0);

    read(client_fd, buffer, BUFFER_SIZE);
    printf("서버로부터 받은 메시지: %s\n", buffer);

    close(client_fd);
    return 0;
}
```

---

## 3. 비동기 소켓 프로그래밍

### `select()`를 활용한 다중 클라이언트 처리
`select()` 함수는 여러 소켓을 동시에 모니터링하며, 읽기/쓰기 가능 여부를 확인합니다.

#### 예제: 다중 클라이언트 처리
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket, client_sockets[MAX_CLIENTS], max_sd, sd;
    struct sockaddr_in address;
    fd_set readfds;
    char buffer[BUFFER_SIZE];

    for (int i = 0; i < MAX_CLIENTS; i++) {
        client_sockets[i] = 0;
    }

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    printf("서버 대기 중...\n");

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        max_sd = server_fd;

        for (int i = 0; i < MAX_CLIENTS; i++) {
            sd = client_sockets[i];
            if (sd > 0) FD_SET(sd, &readfds);
            if (sd > max_sd) max_sd = sd;
        }

        select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if (FD_ISSET(server_fd, &readfds)) {
            new_socket = accept(server_fd, NULL, NULL);
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_sockets[i] == 0) {
                    client_sockets[i] = new_socket;
                    break;
                }
            }
        }

        for (int i = 0; i < MAX_CLIENTS; i++) {
            sd = client_sockets[i];
            if (FD_ISSET(sd, &readfds)) {
                int valread = read(sd, buffer, BUFFER_SIZE);
                if (valread == 0) {
                    close(sd);
                    client_sockets[i] = 0;
                } else {
                    buffer[valread] = '\0';
                    printf("클라이언트 메시지: %s\n", buffer);
                    send(sd, "메시지 수신 완료", strlen("메시지 수신 완료"), 0);
                }
            }
        }
    }

    return 0;
}
```

---

## 4. SSL/TLS를 활용한 보안 통신

### OpenSSL을 이용한 SSL/TLS 통합
- 클라이언트와 서버 간 데이터를 암호화하여 보안을 강화.

#### OpenSSL 초기화
```c
#include <openssl/ssl.h>
#include <openssl/err.h>

SSL_CTX* initializeSSL() {
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    return SSL_CTX_new(TLS_server_method());
}
```

---

네트워크 프로그래밍은 현대 애플리케이션의 핵심 기술로, TCP/UDP 통신, 보안 통신, 비동기 처리와 같은 주제를 학습하면 안정적이고 확장 가능한 네트워크 서비스를 구축할 수 있습니다.

