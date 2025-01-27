  # <stdlib.h>: 표준 유틸리티 라이브러리

`<stdlib.h>`는 C 언어의 표준 유틸리티 함수들을 제공하는 헤더 파일로, 동적 메모리 관리, 수학 연산, 프로세스 제어, 난수 생성 등의 다양한 기능을 포함합니다.

---

## 1. 주요 함수

### 1.1 동적 메모리 관리

#### `malloc`: 메모리 블록 할당
`malloc`은 지정된 크기의 메모리를 동적으로 할당하며, 할당된 메모리의 포인터를 반환합니다.

**사용법:**
```c
#include <stdlib.h>
#include <stdio.h>

int main() {
    int *arr = (int *)malloc(5 * sizeof(int));
    if (arr == NULL) {
        perror("메모리 할당 실패");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        arr[i] = i + 1;
    }

    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);  // 메모리 해제
    return 0;
}
```

#### `calloc`: 초기화된 메모리 블록 할당
`calloc`은 지정된 개수와 크기의 메모리를 할당하며, 0으로 초기화된 메모리 블록을 반환합니다.

**사용법:**
```c
int *arr = (int *)calloc(5, sizeof(int));
```

#### `realloc`: 메모리 블록 크기 조정
`realloc`은 기존 메모리 블록의 크기를 조정하거나 새로운 메모리를 할당합니다.

**사용법:**
```c
arr = (int *)realloc(arr, 10 * sizeof(int));
```

#### `free`: 동적 메모리 해제
`free`는 동적으로 할당된 메모리를 해제하여 메모리 누수를 방지합니다.

**사용법:**
```c
free(arr);
```

---

### 1.2 난수 생성

#### `rand`: 난수 생성
`rand`는 0에서 `RAND_MAX` 사이의 난수를 반환합니다.

**사용법:**
```c
#include <stdlib.h>
#include <stdio.h>

int main() {
    for (int i = 0; i < 5; i++) {
        printf("%d\n", rand());
    }
    return 0;
}
```

#### `srand`: 난수 시드 설정
`srand`를 사용하여 `rand`의 초기 값을 설정할 수 있습니다. 이를 통해 동일한 난수 시퀀스를 재현하거나 다른 난수 시퀀스를 생성할 수 있습니다.

**사용법:**
```c
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    printf("랜덤 값: %d\n", rand());
    return 0;
}
```

---

### 1.3 수학 및 변환 함수

#### `abs`: 정수 절댓값 반환
**사용법:**
```c
#include <stdlib.h>
#include <stdio.h>

int main() {
    int value = -10;
    printf("절댓값: %d\n", abs(value));
    return 0;
}
```

#### `atoi`: 문자열을 정수로 변환
**사용법:**
```c
#include <stdlib.h>
#include <stdio.h>

int main() {
    char str[] = "12345";
    int num = atoi(str);
    printf("정수 값: %d\n", num);
    return 0;
}
```

#### `atof`: 문자열을 실수로 변환
**사용법:**
```c
char str[] = "3.14";
double num = atof(str);
```

#### `strtol`와 `strtod`: 문자열을 숫자로 변환
`strtol`은 문자열을 정수로, `strtod`는 문자열을 실수로 변환합니다. 변환 실패를 확인하기 위해 더 안전하게 사용할 수 있습니다.

**사용법:**
```c
#include <stdlib.h>
#include <stdio.h>

int main() {
    char str[] = "123abc";
    char *endptr;
    long num = strtol(str, &endptr, 10);
    printf("변환된 숫자: %ld\n", num);
    printf("남은 문자열: %s\n", endptr);
    return 0;
}
```

---

### 1.4 프로세스 제어

#### `exit`: 프로그램 종료
`exit`는 프로그램을 즉시 종료하며, 종료 상태 코드를 반환합니다.

**사용법:**
```c
#include <stdlib.h>

int main() {
    exit(0);  // 성공적으로 종료
}
```

#### `system`: 쉘 명령 실행
`system`은 운영 체제 명령을 실행할 때 사용됩니다.

**사용법:**
```c
#include <stdlib.h>

int main() {
    system("ls");  // UNIX/Linux에서 디렉토리 내용 출력
    return 0;
}
```

---

## 2. 실습 예제

### 동적 메모리를 활용한 배열 확장
**코드:**
```c
#include <stdlib.h>
#include <stdio.h>

int main() {
    int *arr = (int *)malloc(5 * sizeof(int));
    if (arr == NULL) {
        perror("메모리 할당 실패");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        arr[i] = i + 1;
    }

    printf("확장 전 배열: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    arr = (int *)realloc(arr, 10 * sizeof(int));
    if (arr == NULL) {
        perror("메모리 재할당 실패");
        return 1;
    }

    for (int i = 5; i < 10; i++) {
        arr[i] = i + 1;
    }

    printf("확장 후 배열: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}
```

**출력:**
```
확장 전 배열: 1 2 3 4 5
확장 후 배열: 1 2 3 4 5 6 7 8 9 10
```

---

`<stdlib.h>`는 동적 메모리 관리와 난수 생성, 문자열 변환 등 C 언어에서 필수적인 유틸리티 함수를 제공합니다. 이를 숙지하면 다양한 프로그램에서 효율적으로 작업할 수 있습니다.

