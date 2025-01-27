# <string.h>: 문자열 처리 라이브러리

`<string.h>`는 C 언어에서 문자열 및 메모리 관련 작업을 수행하는 표준 라이브러리입니다. 문자열 복사, 비교, 검색, 길이 계산, 메모리 조작 등 다양한 기능을 제공합니다.

---

## 1. 주요 함수

### 1.1 문자열 복사와 연결

#### `strcpy`: 문자열 복사
`strcpy`는 소스 문자열을 대상 배열로 복사합니다. 대상 배열은 소스 문자열보다 커야 하며, NULL 종료를 포함합니다.

**사용법:**
```c
#include <string.h>
#include <stdio.h>

int main() {
    char src[] = "Hello, World!";
    char dest[50];

    strcpy(dest, src);
    printf("복사된 문자열: %s\n", dest);
    return 0;
}
```

#### `strncpy`: 안전한 문자열 복사
`strncpy`는 최대 `n` 바이트를 복사하며, 대상 배열이 충분히 크지 않더라도 오버플로우를 방지합니다.

**사용법:**
```c
strncpy(dest, src, sizeof(dest) - 1);
dest[sizeof(dest) - 1] = '\0';
```

#### `strcat`: 문자열 연결
`strcat`은 대상 문자열의 끝에 소스 문자열을 연결합니다.

**사용법:**
```c
char dest[50] = "Hello, ";
char src[] = "World!";
strcat(dest, src);
```

#### `strncat`: 안전한 문자열 연결
`strncat`은 최대 `n` 바이트만 연결하여 오버플로우를 방지합니다.

---

### 1.2 문자열 비교

#### `strcmp`: 문자열 비교
`strcmp`는 두 문자열을 비교하여 같으면 0, 다르면 음수 또는 양수를 반환합니다.

**사용법:**
```c
#include <string.h>
#include <stdio.h>

int main() {
    char str1[] = "Hello";
    char str2[] = "World";

    if (strcmp(str1, str2) == 0) {
        printf("문자열이 같습니다.\n");
    } else {
        printf("문자열이 다릅니다.\n");
    }
    return 0;
}
```

#### `strncmp`: 문자열의 일부 비교
`strncmp`는 두 문자열의 처음 `n` 바이트만 비교합니다.

**사용법:**
```c
if (strncmp(str1, str2, 3) == 0) {
    printf("처음 3문자가 같습니다.\n");
}
```

---

### 1.3 문자열 검색

#### `strchr`: 특정 문자 찾기
`strchr`은 문자열에서 지정한 문자가 처음으로 나타나는 위치를 반환합니다.

**사용법:**
```c
char *result = strchr("Hello, World!", 'W');
if (result) {
    printf("문자 'W'의 위치: %ld\n", result - "Hello, World!");
}
```

#### `strstr`: 부분 문자열 찾기
`strstr`은 문자열에서 특정 부분 문자열이 처음 나타나는 위치를 반환합니다.

**사용법:**
```c
char *result = strstr("Hello, World!", "World");
if (result) {
    printf("부분 문자열 위치: %ld\n", result - "Hello, World!");
}
```

---

### 1.4 문자열 길이

#### `strlen`: 문자열 길이 계산
`strlen`은 NULL 종료 문자를 제외한 문자열의 길이를 반환합니다.

**사용법:**
```c
#include <string.h>
#include <stdio.h>

int main() {
    char str[] = "Hello, World!";
    printf("문자열 길이: %zu\n", strlen(str));
    return 0;
}
```

---

### 1.5 메모리 조작 함수

#### `memcpy`: 메모리 복사
`memcpy`는 소스 메모리 블록에서 대상 메모리 블록으로 데이터를 복사합니다.

**사용법:**
```c
#include <string.h>
#include <stdio.h>

int main() {
    char src[] = "Data";
    char dest[10];

    memcpy(dest, src, strlen(src) + 1);
    printf("복사된 데이터: %s\n", dest);
    return 0;
}
```

#### `memset`: 메모리 초기화
`memset`은 메모리 블록을 특정 값으로 채웁니다.

**사용법:**
```c
char buffer[50];
memset(buffer, 0, sizeof(buffer));
```

---

## 2. 실습 예제

### 문자열 뒤집기 프로그램
**코드:**
```c
#include <stdio.h>
#include <string.h>

void reverseString(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }
}

int main() {
    char str[] = "Hello, World!";
    printf("원래 문자열: %s\n", str);

    reverseString(str);
    printf("뒤집힌 문자열: %s\n", str);

    return 0;
}
```

**출력:**
```
원래 문자열: Hello, World!
뒤집힌 문자열: !dlroW ,olleH
```

---

`<string.h>`는 문자열과 메모리 처리를 위한 필수적인 함수들을 제공합니다. 이 장에서 다룬 내용을 활용하여 문자열 관련 작업을 효율적으로 처리하세요.

