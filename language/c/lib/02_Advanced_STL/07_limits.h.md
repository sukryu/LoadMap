# <limits.h>: 데이터 타입 한계 라이브러리

`<limits.h>`는 C 언어에서 정수형 데이터 타입의 한계를 정의하는 표준 라이브러리입니다. 이를 통해 각 데이터 타입의 최소값과 최대값을 확인할 수 있습니다. 이 라이브러리는 플랫폼 독립적인 코드를 작성하는 데 유용합니다.

---

## 1. 주요 상수

### 1.1 정수 데이터 타입 한계

#### `char` 타입
| 매크로          | 설명                       |
|-----------------|--------------------------|
| `CHAR_BIT`      | `char`의 비트 수           |
| `CHAR_MIN`      | 부호 있는 `char`의 최소값  |
| `CHAR_MAX`      | 부호 있는 `char`의 최대값  |
| `SCHAR_MIN`     | 부호 있는 `signed char` 최소값 |
| `SCHAR_MAX`     | 부호 있는 `signed char` 최대값 |
| `UCHAR_MAX`     | 부호 없는 `unsigned char` 최대값 |

**사용법:**
```c
#include <limits.h>
#include <stdio.h>

int main() {
    printf("CHAR_BIT: %d\n", CHAR_BIT);
    printf("CHAR_MIN: %d\n", CHAR_MIN);
    printf("CHAR_MAX: %d\n", CHAR_MAX);
    return 0;
}
```

**출력:**
```
CHAR_BIT: 8
CHAR_MIN: -128
CHAR_MAX: 127
```

#### `short`, `int`, `long` 타입
| 매크로          | 설명                                |
|-----------------|-----------------------------------|
| `SHRT_MIN`      | `short`의 최소값                  |
| `SHRT_MAX`      | `short`의 최대값                  |
| `USHRT_MAX`     | 부호 없는 `unsigned short` 최대값  |
| `INT_MIN`       | `int`의 최소값                    |
| `INT_MAX`       | `int`의 최대값                    |
| `UINT_MAX`      | 부호 없는 `unsigned int` 최대값    |
| `LONG_MIN`      | `long`의 최소값                   |
| `LONG_MAX`      | `long`의 최대값                   |
| `ULONG_MAX`     | 부호 없는 `unsigned long` 최대값   |

**사용법:**
```c
#include <limits.h>
#include <stdio.h>

int main() {
    printf("INT_MIN: %d\n", INT_MIN);
    printf("INT_MAX: %d\n", INT_MAX);
    printf("UINT_MAX: %u\n", UINT_MAX);
    return 0;
}
```

**출력:**
```
INT_MIN: -2147483648
INT_MAX: 2147483647
UINT_MAX: 4294967295
```

#### `long long` 타입 (C99 이상 지원)
| 매크로            | 설명                                 |
|-------------------|------------------------------------|
| `LLONG_MIN`       | `long long`의 최소값               |
| `LLONG_MAX`       | `long long`의 최대값               |
| `ULLONG_MAX`      | 부호 없는 `unsigned long long` 최대값 |

**사용법:**
```c
#include <limits.h>
#include <stdio.h>

int main() {
    printf("LLONG_MIN: %lld\n", LLONG_MIN);
    printf("LLONG_MAX: %lld\n", LLONG_MAX);
    printf("ULLONG_MAX: %llu\n", ULLONG_MAX);
    return 0;
}
```

**출력:**
```
LLONG_MIN: -9223372036854775808
LLONG_MAX: 9223372036854775807
ULLONG_MAX: 18446744073709551615
```

---

### 1.2 기타 상수

#### 멀티바이트 문자 관련
| 매크로          | 설명                             |
|-----------------|--------------------------------|
| `MB_LEN_MAX`    | 멀티바이트 문자 하나의 최대 바이트 수 |

**사용법:**
```c
#include <limits.h>
#include <stdio.h>

int main() {
    printf("MB_LEN_MAX: %d\n", MB_LEN_MAX);
    return 0;
}
```

**출력:**
```
MB_LEN_MAX: 16
```

---

## 2. 실습 예제

### 정수 데이터 타입의 한계 출력
**코드:**
```c
#include <limits.h>
#include <stdio.h>

int main() {
    printf("char: %d to %d\n", CHAR_MIN, CHAR_MAX);
    printf("short: %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("int: %d to %d\n", INT_MIN, INT_MAX);
    printf("long: %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("long long: %lld to %lld\n", LLONG_MIN, LLONG_MAX);

    return 0;
}
```

**출력:**
```
char: -128 to 127
short: -32768 to 32767
int: -2147483648 to 2147483647
long: -9223372036854775808 to 9223372036854775807
long long: -9223372036854775808 to 9223372036854775807
```

---

### 배열 크기 설정 시 사용
**코드:**
```c
#include <limits.h>
#include <stdio.h>

#define MAX_ARRAY_SIZE UINT_MAX

int main() {
    printf("최대 배열 크기: %u\n", MAX_ARRAY_SIZE);
    return 0;
}
```

**출력:**
```
최대 배열 크기: 4294967295
```

---

## 3. 사용 시 주의사항

1. **플랫폼 의존성**: 상수 값은 플랫폼과 컴파일러에 따라 달라질 수 있으므로 항상 `<limits.h>`를 사용하여 값을 참조하세요.
2. **데이터 오버플로우 방지**: 최대값(`MAX`)과 최소값(`MIN`)을 사용하여 연산 중 오버플로우를 방지할 수 있습니다.
3. **표준 준수**: C99 이상의 표준에서는 추가적으로 `long long` 타입이 지원됩니다.

---

`<limits.h>`는 데이터 타입의 한계를 명확히 정의하여 코드의 안정성과 이식성을 높이는 데 필수적인 라이브러리입니다. 이를 잘 활용하여 시스템 간 호환성을 유지하세요.