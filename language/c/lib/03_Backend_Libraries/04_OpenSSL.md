# OpenSSL 라이브러리 사용 가이드

OpenSSL은 암호화와 보안 통신을 위한 오픈 소스 라이브러리로, SSL/TLS 프로토콜과 다양한 암호화 알고리즘을 지원합니다. 네트워크 애플리케이션에서 데이터 보호와 인증 작업을 수행하는 데 필수적인 도구입니다.

---

## 1. 주요 특징

1. **SSL/TLS 지원**: HTTPS 통신을 포함한 보안 프로토콜 구현.
2. **암호화 알고리즘**: AES, RSA, SHA, HMAC 등 다양한 암호화 알고리즘 제공.
3. **키 관리**: 비대칭 키 생성 및 관리.
4. **디지털 인증서**: X.509 인증서 처리.

---

## 2. 설치

### 2.1 설치 방법
**Ubuntu/Linux:**
```bash
sudo apt-get update
sudo apt-get install libssl-dev openssl
```

**macOS:**
```bash
brew install openssl
```

**Windows:**
- OpenSSL 공식 웹사이트(https://www.openssl.org/)에서 바이너리 다운로드 후 설치.

---

## 3. 주요 구성 요소

### 3.1 SSL/TLS
OpenSSL은 서버와 클라이언트 간 안전한 데이터 전송을 보장하는 SSL/TLS 프로토콜을 제공합니다.

### 3.2 암호화 알고리즘
- **대칭 키 암호화**: AES, DES 등.
- **비대칭 키 암호화**: RSA, DSA 등.
- **해시 함수**: SHA-256, MD5 등.

### 3.3 디지털 인증서
X.509 인증서를 생성하고 관리하며, 공개 키 인프라(PKI) 작업을 지원합니다.

---

## 4. 주요 함수

### 4.1 초기화

#### `SSL_library_init`
- **설명**: OpenSSL 라이브러리를 초기화합니다.
- **형식**: `int SSL_library_init(void);`

#### `SSL_load_error_strings`
- **설명**: 오류 메시지를 읽기 위한 문자열을 로드합니다.
- **형식**: `void SSL_load_error_strings(void);`

**예제:**
```c
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <stdio.h>

int main() {
    SSL_library_init();
    SSL_load_error_strings();

    printf("OpenSSL 초기화 완료\n");
    return 0;
}
```

**출력:**
```
OpenSSL 초기화 완료
```

---

### 4.2 SSL 컨텍스트 생성

#### `SSL_CTX_new`
- **설명**: SSL 컨텍스트를 생성합니다.
- **형식**: `SSL_CTX *SSL_CTX_new(const SSL_METHOD *method);`

#### `SSL_CTX_free`
- **설명**: SSL 컨텍스트를 해제합니다.
- **형식**: `void SSL_CTX_free(SSL_CTX *ctx);`

**예제:**
```c
#include <openssl/ssl.h>
#include <stdio.h>

int main() {
    SSL_library_init();

    SSL_CTX *ctx = SSL_CTX_new(SSLv23_client_method());
    if (!ctx) {
        printf("SSL 컨텍스트 생성 실패\n");
        return 1;
    }

    printf("SSL 컨텍스트 생성 성공\n");
    SSL_CTX_free(ctx);
    return 0;
}
```

**출력:**
```
SSL 컨텍스트 생성 성공
```

---

### 4.3 암호화 및 복호화

#### AES 암호화
OpenSSL의 AES 암호화 API를 사용하여 데이터를 암호화할 수 있습니다.

**예제:**
```c
#include <openssl/aes.h>
#include <stdio.h>
#include <string.h>

int main() {
    unsigned char key[16] = "0123456789abcdef";
    unsigned char plaintext[16] = "Hello, OpenSSL!";
    unsigned char ciphertext[16];
    unsigned char decryptedtext[16];

    AES_KEY enc_key, dec_key;

    AES_set_encrypt_key(key, 128, &enc_key);
    AES_encrypt(plaintext, ciphertext, &enc_key);

    AES_set_decrypt_key(key, 128, &dec_key);
    AES_decrypt(ciphertext, decryptedtext, &dec_key);

    printf("원문: %s\n", plaintext);
    printf("암호문: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n복호문: %s\n", decryptedtext);

    return 0;
}
```

**출력:**
```
원문: Hello, OpenSSL!
암호문: [16진수 출력]
복호문: Hello, OpenSSL!
```

---

### 4.4 디지털 인증서 생성
OpenSSL 명령줄 도구를 사용해 인증서를 생성할 수 있습니다.

**명령어:**
```bash
openssl req -new -x509 -days 365 -keyout key.pem -out cert.pem
```

**설명:**
- `-new`: 새로운 인증서 요청 생성.
- `-x509`: X.509 인증서 생성.
- `-days 365`: 유효 기간 설정.
- `-keyout`: 개인 키 파일 저장 경로.
- `-out`: 인증서 파일 저장 경로.

---

## 5. SSL/TLS 서버와 클라이언트 예제

### 서버
```c
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <stdio.h>
#include <netinet/in.h>

int main() {
    SSL_library_init();
    SSL_CTX *ctx = SSL_CTX_new(SSLv23_server_method());

    SSL_CTX_use_certificate_file(ctx, "cert.pem", SSL_FILETYPE_PEM);
    SSL_CTX_use_PrivateKey_file(ctx, "key.pem", SSL_FILETYPE_PEM);

    int server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4433);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server, (struct sockaddr*)&addr, sizeof(addr));
    listen(server, 5);

    int client = accept(server, NULL, NULL);
    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, client);

    SSL_accept(ssl);
    printf("SSL 연결 성공\n");

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(client);
    close(server);
    SSL_CTX_free(ctx);

    return 0;
}
```

### 클라이언트
```c
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <stdio.h>
#include <netdb.h>

int main() {
    SSL_library_init();
    SSL_CTX *ctx = SSL_CTX_new(SSLv23_client_method());

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct hostent *host = gethostbyname("localhost");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4433);
    addr.sin_addr.s_addr = *(long*)(host->h_addr);

    connect(sock, (struct sockaddr*)&addr, sizeof(addr));

    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);

    SSL_connect(ssl);
    printf("SSL 연결 성공\n");

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(sock);
    SSL_CTX_free(ctx);

    return 0;
}
```

---

## 6. 사용 시 주의사항

1. **SSL/TLS 설정**: 최신 보안 프로토콜(TLS 1.2 이상)을 사용해야 합니다.
2. **인증서 관리**: 신뢰할 수 있는 인증서를 사용하여 보안을 강화하세요.
3. **에러 처리**: `SSL_get_error`를 사용해 SSL 함수 호출 실패 시 적절히 처리해야 합니다.

---

OpenSSL은 보안 통신과 암호화를 구현하는 강력한 도구입니다. 위의 예제와 기능을 참고하여 안전한 네트워크 애플리케이션을 작성해보세요.

