# libcurl 라이브러리 사용 가이드

libcurl은 데이터 전송을 위해 설계된 멀티 프로토콜 지원 C 라이브러리입니다. HTTP, HTTPS, FTP, SMTP, IMAP 등 다양한 프로토콜을 지원하며, RESTful API 호출 및 파일 다운로드 등의 작업에 유용합니다.

---

## 1. 주요 특징

1. **멀티 프로토콜 지원**: HTTP, HTTPS, FTP, SCP 등 다양한 프로토콜 제공.
2. **동기 및 비동기 지원**: 블로킹과 논블로킹 방식 모두 지원.
3. **TLS/SSL 통합**: HTTPS 및 보안 프로토콜 지원(OpenSSL, GnuTLS 등과 호환).
4. **사용자 정의 요청**: 헤더, 쿠키, 인증 등 사용자 정의 HTTP 요청 가능.
5. **멀티스레드 안전성**: 여러 스레드에서 안전하게 사용할 수 있음.

---

## 2. 설치

### 2.1 설치 방법
**Ubuntu/Linux:**
```bash
sudo apt-get update
sudo apt-get install libcurl4-openssl-dev
```

**macOS:**
```bash
brew install curl
```

**Windows:**
- libcurl 공식 웹사이트(https://curl.se/libcurl/)에서 바이너리 다운로드 후 설치.

---

## 3. 주요 함수

### 3.1 초기화와 종료

#### `curl_global_init`
- **설명**: libcurl을 초기화합니다.
- **형식**: `CURLcode curl_global_init(long flags);`

#### `curl_global_cleanup`
- **설명**: libcurl에서 사용된 리소스를 해제합니다.
- **형식**: `void curl_global_cleanup(void);`

**예제:**
```c
#include <curl/curl.h>
#include <stdio.h>

int main() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    printf("libcurl 초기화 완료\n");
    curl_global_cleanup();
    return 0;
}
```

**출력:**
```
libcurl 초기화 완료
```

---

### 3.2 HTTP GET 요청

#### `curl_easy_init`
- **설명**: CURL 핸들을 생성합니다.
- **형식**: `CURL *curl_easy_init(void);`

#### `curl_easy_setopt`
- **설명**: CURL 옵션을 설정합니다.
- **형식**: `CURLcode curl_easy_setopt(CURL *handle, CURLoption option, parameter);`

#### `curl_easy_perform`
- **설명**: 요청을 실행합니다.
- **형식**: `CURLcode curl_easy_perform(CURL *handle);`

#### `curl_easy_cleanup`
- **설명**: CURL 핸들을 해제합니다.
- **형식**: `void curl_easy_cleanup(CURL *handle);`

**예제:**
```c
#include <curl/curl.h>
#include <stdio.h>

int main() {
    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.example.com");
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() 실패: %s\n", curl_easy_strerror(res));
        } else {
            printf("HTTP GET 요청 성공\n");
        }

        curl_easy_cleanup(curl);
    }
    return 0;
}
```

**출력:**
```
HTTP GET 요청 성공
```

---

### 3.3 HTTP POST 요청

#### POST 데이터 전송
**예제:**
```c
#include <curl/curl.h>
#include <stdio.h>

int main() {
    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.example.com/api");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "key1=value1&key2=value2");

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() 실패: %s\n", curl_easy_strerror(res));
        } else {
            printf("HTTP POST 요청 성공\n");
        }

        curl_easy_cleanup(curl);
    }
    return 0;
}
```

**출력:**
```
HTTP POST 요청 성공
```

---

### 3.4 데이터 콜백 처리

#### 사용자 정의 콜백 함수
libcurl은 수신 데이터를 처리하기 위해 콜백을 설정할 수 있습니다.

**예제:**
```c
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total_size = size * nmemb;
    strncat(userp, contents, total_size);
    return total_size;
}

int main() {
    CURL *curl = curl_easy_init();
    if (curl) {
        char response[1024] = {0};

        curl_easy_setopt(curl, CURLOPT_URL, "https://www.example.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            printf("응답 데이터: %s\n", response);
        } else {
            fprintf(stderr, "curl_easy_perform() 실패: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }
    return 0;
}
```

**출력:**
```
응답 데이터: <!doctype html>...
```

---

## 4. 실습 예제

### 파일 다운로드 프로그램
**코드:**
```c
#include <curl/curl.h>
#include <stdio.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}

int main() {
    CURL *curl = curl_easy_init();
    if (curl) {
        FILE *fp = fopen("downloaded_file.txt", "wb");
        if (!fp) {
            fprintf(stderr, "파일을 열 수 없습니다.\n");
            return 1;
        }

        curl_easy_setopt(curl, CURLOPT_URL, "https://www.example.com/file.txt");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            printf("파일 다운로드 성공\n");
        } else {
            fprintf(stderr, "curl_easy_perform() 실패: %s\n", curl_easy_strerror(res));
        }

        fclose(fp);
        curl_easy_cleanup(curl);
    }
    return 0;
}
```

**출력:**
```
파일 다운로드 성공
```

---

## 5. 사용 시 주의사항

1. **SSL/TLS 설정**: HTTPS를 사용할 경우 SSL/TLS 관련 옵션을 설정하세요.
   ```c
   curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
   curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
   ```
2. **메모리 관리**: `curl_easy_cleanup`와 같은 정리 함수 호출을 잊지 마세요.
3. **에러 처리**: `curl_easy_perform` 호출 후 반환값을 항상 확인하세요.

---

libcurl은 다양한 프로토콜을 지원하는 강력한 데이터 전송 라이브러리입니다. 위의 예제와 기능을 참고하여 효율적인 네트워크 애플리케이션을 작성해보세요.

