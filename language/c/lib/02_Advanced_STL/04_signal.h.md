# <signal.h>: 신호 처리 라이브러리

`<signal.h>`는 C 언어에서 신호(Signal)를 처리하기 위한 표준 라이브러리입니다. 신호는 운영 체제가 프로세스에 보내는 비동기적 메시지로, 종료, 인터럽트, 알람 등 다양한 이벤트를 처리할 수 있습니다.

---

## 1. 주요 내용

### 1.1 신호 처리 개념

#### 신호란?
- 신호(Signal)는 운영 체제가 프로세스에 전달하는 이벤트 알림입니다.
- 특정 동작(예: 종료, 중단, 알람)을 트리거하거나 사용자 정의 동작을 수행하도록 설계되었습니다.

#### 주요 신호
| 신호      | 매크로       | 설명                                      |
|-----------|--------------|------------------------------------------|
| `SIGINT`  | 2            | 인터럽트 신호 (Ctrl + C)                 |
| `SIGTERM` | 15           | 종료 요청 신호                          |
| `SIGKILL` | 9            | 강제 종료 신호 (종료 불가)               |
| `SIGHUP`  | 1            | 세션 종료 신호                          |
| `SIGALRM` | 14           | 알람 신호                                |
| `SIGSEGV` | 11           | 잘못된 메모리 접근                      |

---

### 1.2 주요 함수

#### `signal`: 신호 처리기 설정
- **정의**: 신호 발생 시 실행할 핸들러 함수를 설정합니다.
- **형식**: `void (*signal(int sig, void (*handler)(int)))(int);`

**사용법:**
```c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handle_sigint(int sig) {
    printf("SIGINT 신호(%d)가 발생했습니다.\n", sig);
    exit(0);
}

int main() {
    signal(SIGINT, handle_sigint);  // Ctrl + C 핸들러 등록

    while (1) {
        printf("프로그램 실행 중...\n");
        sleep(1);
    }

    return 0;
}
```

**출력 (Ctrl + C 입력):**
```
프로그램 실행 중...
프로그램 실행 중...
SIGINT 신호(2)가 발생했습니다.
```

---

#### `raise`: 신호 전송
- **정의**: 현재 프로세스에 특정 신호를 보냅니다.
- **형식**: `int raise(int sig);`

**사용법:**
```c
#include <signal.h>
#include <stdio.h>

void handle_signal(int sig) {
    printf("신호(%d)가 발생했습니다.\n", sig);
}

int main() {
    signal(SIGTERM, handle_signal);  // SIGTERM 핸들러 등록
    raise(SIGTERM);  // SIGTERM 신호 발생

    return 0;
}
```

**출력:**
```
신호(15)가 발생했습니다.
```

---

#### `kill`: 프로세스에 신호 보내기
- **정의**: 지정된 프로세스 ID에 신호를 보냅니다.
- **형식**: `int kill(pid_t pid, int sig);`

**사용법:**
```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = getpid();
    printf("현재 프로세스 ID: %d\n", pid);

    kill(pid, SIGINT);  // 현재 프로세스에 SIGINT 전송
    return 0;
}
```

**출력:**
```
현재 프로세스 ID: 12345
프로그램 종료 (SIGINT 처리에 따라 다름)
```

---

#### `alarm`: 알람 신호 설정
- **정의**: 지정된 시간 후 `SIGALRM` 신호를 발생시킵니다.
- **형식**: `unsigned int alarm(unsigned int seconds);`

**사용법:**
```c
#include <signal.h>
#include <stdio.h>

void handle_alarm(int sig) {
    printf("알람 신호(%d)가 발생했습니다.\n", sig);
}

int main() {
    signal(SIGALRM, handle_alarm);
    alarm(5);  // 5초 후 SIGALRM 발생

    printf("알람을 설정했습니다.\n");
    pause();  // 신호 대기

    return 0;
}
```

**출력:**
```
알람을 설정했습니다.
알람 신호(14)가 발생했습니다.
```

---

## 2. 실습 예제

### SIGINT와 SIGTERM 처리 프로그램
**코드:**
```c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handle_signal(int sig) {
    if (sig == SIGINT) {
        printf("SIGINT 신호를 처리했습니다. 프로그램을 종료합니다.\n");
        exit(0);
    } else if (sig == SIGTERM) {
        printf("SIGTERM 신호를 처리했습니다.\n");
    }
}

int main() {
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    printf("신호를 기다리는 중... (Ctrl+C 또는 SIGTERM)\n");
    while (1) {
        pause();  // 신호 대기
    }

    return 0;
}
```

**출력 (SIGINT 발생):**
```
신호를 기다리는 중... (Ctrl+C 또는 SIGTERM)
SIGINT 신호를 처리했습니다. 프로그램을 종료합니다.
```

---

## 3. 사용 시 주의사항
1. **비동기적 성격**: 신호는 비동기적으로 발생하며, 핸들러 내에서 제한된 작업만 수행해야 합니다.
2. **중첩 호출 방지**: 신호 핸들러가 실행 중일 때 동일한 신호가 중첩되지 않도록 주의하세요.
3. **중요 작업 보호**: 파일 입출력 및 메모리 작업 중 신호가 발생하면 데이터 손상이 발생할 수 있습니다. 이를 보호하려면 신호 블록을 고려하세요.

---

`<signal.h>`는 프로그램의 제어 흐름을 관리하고 시스템 이벤트를 처리하는 데 매우 유용합니다. 위에서 설명한 함수와 실습 예제를 활용하여 다양한 신호 처리 시나리오를 구현할 수 있습니다.

