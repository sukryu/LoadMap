# Libevent 라이브러리 사용 가이드

Libevent는 고성능 네트워크 애플리케이션을 개발하기 위해 비동기 이벤트 기반 네트워크 통신을 제공하는 C 라이브러리입니다. 비동기 I/O, 타이머, 시그널 처리를 지원하며, 효율적인 비차단 소켓 통신을 구현하는 데 유용합니다.

---

## 1. 주요 특징

1. **비동기 이벤트 처리**: 소켓, 파일 디스크립터, 타이머 등 다양한 이벤트를 비동기적으로 처리.
2. **이식성**: 다양한 운영 체제에서 작동 (Linux, macOS, Windows).
3. **고성능**: 대규모 연결 처리를 위한 효율적인 이벤트 루프 제공.
4. **TLS 지원**: OpenSSL과의 통합을 통해 보안 통신 지원.

---

## 2. 설치

### 2.1 설치
**Ubuntu/Linux:**
```bash
sudo apt-get update
sudo apt-get install libevent-dev
```

**macOS:**
```bash
brew install libevent
```

**Windows:**
- Libevent 공식 GitHub 저장소(https://github.com/libevent/libevent)에서 소스 코드 다운로드 후 빌드.

---

## 3. 주요 구성 요소

### 3.1 이벤트 루프
Libevent는 이벤트 루프를 기반으로 작동하며, 이벤트를 대기하고 처리하는 핵심 역할을 수행합니다.

### 3.2 이벤트 타입
1. **I/O 이벤트**: 소켓 또는 파일 디스크립터에서 읽기/쓰기 가능 여부.
2. **타이머 이벤트**: 일정 시간 간격으로 실행.
3. **신호 이벤트**: 특정 시스템 신호 처리.

---

## 4. 주요 함수

### 4.1 기본 초기화와 종료

#### `event_base_new`
- **설명**: 이벤트 루프를 생성합니다.
- **형식**: `struct event_base *event_base_new(void);`

#### `event_base_free`
- **설명**: 이벤트 루프를 해제합니다.
- **형식**: `void event_base_free(struct event_base *base);`

**예제:**
```c
#include <event2/event.h>
#include <stdio.h>

int main() {
    struct event_base *base = event_base_new();
    if (!base) {
        fprintf(stderr, "이벤트 루프를 생성할 수 없습니다.\n");
        return 1;
    }

    printf("이벤트 루프 생성 성공\n");
    event_base_free(base);
    return 0;
}
```

**출력:**
```
이벤트 루프 생성 성공
```

---

### 4.2 I/O 이벤트 처리

#### `event_new`
- **설명**: 새로운 이벤트를 생성합니다.
- **형식**: `struct event *event_new(struct event_base *base, evutil_socket_t fd, short events, event_callback_fn cb, void *arg);`

#### `event_add`
- **설명**: 이벤트를 이벤트 루프에 추가합니다.
- **형식**: `int event_add(struct event *ev, const struct timeval *timeout);`

#### `event_del`
- **설명**: 이벤트를 이벤트 루프에서 제거합니다.
- **형식**: `int event_del(struct event *ev);`

**예제:**
```c
#include <event2/event.h>
#include <stdio.h>
#include <unistd.h>

void read_callback(evutil_socket_t fd, short events, void *arg) {
    char buffer[1024];
    int len = read(fd, buffer, sizeof(buffer) - 1);
    if (len > 0) {
        buffer[len] = '\0';
        printf("읽은 데이터: %s\n", buffer);
    }
}

int main() {
    struct event_base *base = event_base_new();
    struct event *ev = event_new(base, STDIN_FILENO, EV_READ | EV_PERSIST, read_callback, NULL);

    event_add(ev, NULL);
    event_base_dispatch(base);

    event_free(ev);
    event_base_free(base);
    return 0;
}
```

**설명:**
- 표준 입력(STDIN)을 비동기적으로 읽습니다.
- 사용자가 데이터를 입력하면 `read_callback`이 호출됩니다.

**출력 (입력 예시: Hello):**
```
읽은 데이터: Hello
```

---

### 4.3 타이머 이벤트 처리

#### `event_add`와 타이머
`event_add`에서 타이머를 설정하여 일정 시간 후 이벤트를 트리거할 수 있습니다.

**예제:**
```c
#include <event2/event.h>
#include <stdio.h>

void timeout_callback(evutil_socket_t fd, short events, void *arg) {
    printf("타이머 이벤트 발생\n");
}

int main() {
    struct event_base *base = event_base_new();
    struct timeval timeout = {2, 0};  // 2초 대기

    struct event *timeout_event = event_new(base, -1, EV_TIMEOUT, timeout_callback, NULL);
    event_add(timeout_event, &timeout);

    event_base_dispatch(base);

    event_free(timeout_event);
    event_base_free(base);
    return 0;
}
```

**출력 (2초 후):**
```
타이머 이벤트 발생
```

---

### 4.4 신호 이벤트 처리

#### `evsignal_new`
- **설명**: 신호 이벤트를 생성합니다.
- **형식**: `struct event *evsignal_new(struct event_base *base, int signum, event_callback_fn cb, void *arg);`

**예제:**
```c
#include <event2/event.h>
#include <signal.h>
#include <stdio.h>

void signal_callback(evutil_socket_t sig, short events, void *arg) {
    printf("SIGINT 신호(%d) 수신\n", (int)sig);
    struct event_base *base = (struct event_base *)arg;
    event_base_loopbreak(base);
}

int main() {
    struct event_base *base = event_base_new();
    struct event *signal_event = evsignal_new(base, SIGINT, signal_callback, base);

    event_add(signal_event, NULL);
    printf("Ctrl+C를 눌러 종료하세요\n");

    event_base_dispatch(base);

    event_free(signal_event);
    event_base_free(base);
    return 0;
}
```

**출력:**
```
Ctrl+C를 눌러 종료하세요
SIGINT 신호(2) 수신
```

---

## 5. 사용 시 주의사항

1. **메모리 관리**: 모든 `event`와 `event_base`는 사용 후 반드시 해제해야 메모리 누수를 방지할 수 있습니다.
2. **스레드 안전성**: Libevent는 멀티스레드 환경에서 사용할 수 있지만, 스레드 간 데이터 공유는 주의해야 합니다.
3. **이식성 확인**: 특정 플랫폼에서는 일부 기능이 제한될 수 있으므로, 크로스 플랫폼 개발 시 주의하세요.

---

Libevent는 대규모 네트워크 애플리케이션 개발에 필수적인 도구입니다. 위의 예제와 기능을 참고하여 효율적인 비동기 이벤트 기반 프로그램을 작성해보세요.

