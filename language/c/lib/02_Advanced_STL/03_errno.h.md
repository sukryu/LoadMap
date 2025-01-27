# <errno.h>: 오류 코드 처리 라이브러리

`<errno.h>`는 C 언어에서 함수 호출 중 발생한 오류를 처리하기 위한 표준 라이브러리입니다. 이 헤더 파일은 오류 상태를 나타내는 전역 변수와 관련된 매크로를 제공합니다.

---

## 1. 주요 내용

### 1.1 `errno` 변수

#### 개요
- **정의**: `errno`는 전역 변수로, 함수 호출에서 발생한 오류를 나타냅니다.
- **초기화**: 오류가 발생하기 전 `errno`는 0으로 설정되어 있어야 합니다.
- **용도**: 시스템 호출 및 라이브러리 함수의 오류를 확인.

#### 사용법
```c
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main() {
    FILE *file = fopen("nonexistent.txt", "r");
    if (file == NULL) {
        printf("파일 열기 실패: %s\n", strerror(errno));
    }
    return 0;
}
```

**출력:**
```
파일 열기 실패: No such file or directory
```

---

### 1.2 주요 매크로

#### 오류 코드 매크로
| 매크로         | 설명                                      |
|----------------|-----------------------------------------|
| `EACCES`       | 접근 권한 없음                          |
| `EEXIST`       | 파일이 이미 존재함                      |
| `EINVAL`       | 잘못된 인자                            |
| `EIO`          | 입출력 오류                             |
| `ENOMEM`       | 메모리 부족                             |
| `ENOENT`       | 파일 또는 디렉터리가 존재하지 않음       |
| `EPERM`        | 작업에 대한 권한 없음                   |

#### 사용법
```c
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main() {
    FILE *file = fopen("readonly.txt", "w");
    if (file == NULL) {
        if (errno == EACCES) {
            printf("접근 권한이 없습니다.\n");
        } else {
            printf("오류 발생: %s\n", strerror(errno));
        }
    }
    return 0;
}
```

**출력:**
```
접근 권한이 없습니다.
```

---

### 1.3 `strerror` 함수

#### 개요
- **정의**: 오류 코드를 사람이 읽을 수 있는 문자열로 변환합니다.
- **반환값**: 오류 메시지 문자열.

#### 사용법
```c
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main() {
    printf("ENOMEM: %s\n", strerror(ENOMEM));
    printf("EIO: %s\n", strerror(EIO));
    return 0;
}
```

**출력:**
```
ENOMEM: Cannot allocate memory
EIO: Input/output error
```

---

### 1.4 `perror` 함수

#### 개요
- **정의**: `errno` 변수에 저장된 오류 메시지를 출력합니다.
- **형식**: `perror(const char *message)`.
- **용도**: 사용자 정의 메시지와 함께 오류 메시지를 출력.

#### 사용법
```c
#include <errno.h>
#include <stdio.h>

int main() {
    FILE *file = fopen("nonexistent.txt", "r");
    if (file == NULL) {
        perror("파일 열기 실패");
    }
    return 0;
}
```

**출력:**
```
파일 열기 실패: No such file or directory
```

---

## 2. 실습 예제

### 파일 열기 오류 처리
**코드:**
```c
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main() {
    FILE *file = fopen("data.txt", "r");

    if (file == NULL) {
        printf("오류 코드: %d\n", errno);
        printf("오류 메시지: %s\n", strerror(errno));
        return 1;
    }

    fclose(file);
    return 0;
}
```

**출력 (파일이 없는 경우):**
```
오류 코드: 2
오류 메시지: No such file or directory
```

---

### 메모리 할당 오류 처리
**코드:**
```c
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t size = (size_t)-1;  // 매우 큰 크기 요청
    void *ptr = malloc(size);

    if (ptr == NULL) {
        perror("메모리 할당 실패");
    }

    return 0;
}
```

**출력:**
```
메모리 할당 실패: Cannot allocate memory
```

---

## 3. 사용 시 주의사항

1. **초기화**: `errno`는 함수 호출 전에 0으로 초기화해야 정확한 오류를 확인할 수 있습니다.
   ```c
   errno = 0;
   ```

2. **스레드 안전성**: `errno`는 스레드마다 독립적으로 관리되므로 멀티스레드 환경에서도 안전하게 사용할 수 있습니다.

3. **사용 제한**: 모든 함수가 `errno`를 설정하지는 않습니다. 사용 전 함수 문서를 확인하세요.

---

`<errno.h>`는 오류 처리를 단순화하고 프로그램의 안정성을 높이는 데 필수적인 라이브러리입니다. 이를 활용하여 오류 발생 시 적절한 메시지를 제공하고, 프로그램의 디버깅 및 유지보수를 효율적으로 수행할 수 있습니다.