# <ctype.h>: 문자 처리 라이브러리

`<ctype.h>`는 C 언어에서 문자를 처리하기 위한 표준 라이브러리입니다. 문자가 숫자인지, 알파벳인지, 공백인지 등을 판별하거나 대소문자를 변환하는 데 유용합니다.

---

## 1. 주요 함수

### 1.1 문자 판별 함수

#### `isalpha`: 알파벳 문자인지 확인
`isalpha`는 문자가 알파벳(대문자 또는 소문자)인지 확인합니다.

**사용법:**
```c
#include <ctype.h>
#include <stdio.h>

int main() {
    char c = 'A';
    if (isalpha(c)) {
        printf("%c는 알파벳입니다.\n", c);
    } else {
        printf("%c는 알파벳이 아닙니다.\n", c);
    }
    return 0;
}
```

**출력:**
```
A는 알파벳입니다.
```

#### `isdigit`: 숫자인지 확인
`isdigit`은 문자가 숫자(0~9)인지 확인합니다.

**사용법:**
```c
char c = '5';
if (isdigit(c)) {
    printf("%c는 숫자입니다.\n", c);
}
```

#### `isspace`: 공백인지 확인
`isspace`는 문자가 공백 문자(스페이스, 탭, 개행 등)인지 확인합니다.

**사용법:**
```c
char c = ' ';
if (isspace(c)) {
    printf("공백 문자입니다.\n");
}
```

#### `isalnum`: 알파벳 또는 숫자인지 확인
`isalnum`은 문자가 알파벳 또는 숫자인지 확인합니다.

**사용법:**
```c
char c = 'A';
if (isalnum(c)) {
    printf("%c는 알파벳 또는 숫자입니다.\n", c);
}
```

#### `ispunct`: 구두점인지 확인
`ispunct`는 문자가 구두점(., !, ?)인지 확인합니다.

**사용법:**
```c
char c = '!';
if (ispunct(c)) {
    printf("%c는 구두점입니다.\n", c);
}
```

#### `isprint`: 출력 가능한 문자인지 확인
`isprint`는 문자가 출력 가능한 문자(공백 포함)인지 확인합니다.

**사용법:**
```c
char c = '~';
if (isprint(c)) {
    printf("%c는 출력 가능한 문자입니다.\n", c);
}
```

---

### 1.2 문자 변환 함수

#### `toupper`: 소문자를 대문자로 변환
`toupper`는 소문자를 대문자로 변환합니다. 소문자가 아닌 경우 변경되지 않습니다.

**사용법:**
```c
#include <ctype.h>
#include <stdio.h>

int main() {
    char c = 'a';
    printf("%c를 대문자로 변환: %c\n", c, toupper(c));
    return 0;
}
```

**출력:**
```
a를 대문자로 변환: A
```

#### `tolower`: 대문자를 소문자로 변환
`tolower`는 대문자를 소문자로 변환합니다. 대문자가 아닌 경우 변경되지 않습니다.

**사용법:**
```c
char c = 'A';
printf("%c를 소문자로 변환: %c\n", c, tolower(c));
```

---

## 2. 실습 예제

### 문자열 내 대소문자 변환

**코드:**
```c
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void convertCase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isupper(str[i])) {
            str[i] = tolower(str[i]);
        } else if (islower(str[i])) {
            str[i] = toupper(str[i]);
        }
    }
}

int main() {
    char str[] = "Hello, World!";
    printf("원래 문자열: %s\n", str);

    convertCase(str);
    printf("변환된 문자열: %s\n", str);

    return 0;
}
```

**출력:**
```
원래 문자열: Hello, World!
변환된 문자열: hELLO, wORLD!
```

---

### 사용자 입력 유효성 검사

**코드:**
```c
#include <ctype.h>
#include <stdio.h>

int main() {
    char input[100];
    printf("이름을 입력하세요: ");
    scanf("%s", input);

    for (int i = 0; input[i] != '\0'; i++) {
        if (!isalpha(input[i])) {
            printf("유효하지 않은 문자가 포함되어 있습니다.\n");
            return 1;
        }
    }

    printf("유효한 이름입니다: %s\n", input);
    return 0;
}
```

**출력:**
```
이름을 입력하세요: John123
유효하지 않은 문자가 포함되어 있습니다.
```

---

`<ctype.h>`는 문자의 판별 및 변환 작업에 필수적인 함수들을 제공합니다. 위의 함수를 활용하면 입력 유효성 검사, 문자열 처리 등 다양한 작업을 쉽게 수행할 수 있습니다.

