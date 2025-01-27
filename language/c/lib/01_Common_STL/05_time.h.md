# <time.h>: 시간 및 날짜 처리 라이브러리

`<time.h>`는 C 언어에서 시간과 날짜를 처리하기 위한 표준 라이브러리입니다. 시스템 시간을 얻거나, 날짜를 계산하거나, 프로그램의 실행 시간을 측정하는 데 사용할 수 있습니다.

---

## 1. 주요 함수

### 1.1 시간 가져오기

#### `time`: 현재 시간 가져오기
`time` 함수는 현재 시간을 초 단위로 반환하며, 1970년 1월 1일 00:00:00 UTC를 기준으로 한 **에포크 시간**을 제공합니다.

**사용법:**
```c
#include <time.h>
#include <stdio.h>

int main() {
    time_t current_time;
    current_time = time(NULL);

    printf("현재 시간(초): %ld\n", current_time);
    return 0;
}
```

**출력:**
```
현재 시간(초): 1672531200
```

---

### 1.2 시간 변환

#### `ctime`: 시간을 문자열로 변환
`ctime` 함수는 `time_t` 형식의 시간을 사람이 읽을 수 있는 문자열로 변환합니다.

**사용법:**
```c
#include <time.h>
#include <stdio.h>

int main() {
    time_t current_time = time(NULL);
    printf("현재 시간: %s", ctime(&current_time));
    return 0;
}
```

**출력:**
```
현재 시간: Sun Jan  1 00:00:00 2023
```

#### `localtime`: 지역 시간 구조체로 변환
`localtime` 함수는 `time_t` 형식을 `struct tm` 구조체로 변환합니다. 이 구조체는 연도, 월, 일, 시, 분, 초 등의 세부 정보를 포함합니다.

**사용법:**
```c
#include <time.h>
#include <stdio.h>

int main() {
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);

    printf("현재 시간: %d-%02d-%02d %02d:%02d:%02d\n",
           local_time->tm_year + 1900,
           local_time->tm_mon + 1,
           local_time->tm_mday,
           local_time->tm_hour,
           local_time->tm_min,
           local_time->tm_sec);

    return 0;
}
```

**출력:**
```
현재 시간: 2023-01-01 00:00:00
```

#### `gmtime`: UTC 시간 구조체로 변환
`gmtime` 함수는 `time_t` 형식을 UTC 시간 기준의 `struct tm` 구조체로 변환합니다.

---

### 1.3 시간 포맷팅

#### `strftime`: 시간 형식 지정 출력
`strftime` 함수는 `struct tm` 구조체를 형식화된 문자열로 출력합니다.

**사용법:**
```c
#include <time.h>
#include <stdio.h>

int main() {
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local_time);

    printf("형식화된 시간: %s\n", buffer);
    return 0;
}
```

**출력:**
```
형식화된 시간: 2023-01-01 00:00:00
```

---

### 1.4 시간 차이 계산

#### `difftime`: 시간 차이 계산
`difftime` 함수는 두 `time_t` 값의 차이를 초 단위로 반환합니다.

**사용법:**
```c
#include <time.h>
#include <stdio.h>

int main() {
    time_t start_time = time(NULL);

    // 5초 대기
    sleep(5);

    time_t end_time = time(NULL);
    double elapsed = difftime(end_time, start_time);

    printf("경과 시간: %.2f초\n", elapsed);
    return 0;
}
```

---

### 1.5 타이머

#### `clock`: CPU 시간 측정
`clock` 함수는 프로그램 실행 시간(프로세스가 CPU를 사용한 시간)을 클록 틱 단위로 반환합니다.

**사용법:**
```c
#include <time.h>
#include <stdio.h>

int main() {
    clock_t start = clock();

    // 작업 수행
    for (volatile int i = 0; i < 100000000; i++);

    clock_t end = clock();
    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("CPU 시간: %.2f초\n", cpu_time);
    return 0;
}
```

---

## 2. 실습 예제

### 간단한 디지털 시계 구현
**코드:**
```c
#include <time.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    while (1) {
        time_t current_time = time(NULL);
        struct tm *local_time = localtime(&current_time);

        printf("\r%02d:%02d:%02d", local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
        fflush(stdout);
        sleep(1);
    }
    return 0;
}
```

**출력:**
```
실행 중: 14:23:45 (1초마다 갱신)
```

---

`<time.h>`는 시간 및 날짜 처리에 유용한 기능을 제공합니다. 이 라이브러리를 활용하면 프로그램의 시간 기반 로직 구현이 쉬워집니다. 위의 예제와 함께 다양한 시간 관련 작업에 적용해 보세요.

