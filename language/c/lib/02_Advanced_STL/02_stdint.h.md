# <stdint.h>: 고정 크기 정수 라이브러리

`<stdint.h>`는 C 언어에서 고정 크기 정수형과 관련된 타입 및 매크로를 제공하는 표준 헤더 파일입니다. 이를 통해 정수 크기와 서명을 명확하게 지정할 수 있으며, 플랫폼 간 코드의 이식성을 보장합니다.

---

## 1. 주요 내용

### 1.1 고정 크기 정수 타입

#### 정수 타입 표
| 데이터 타입     | 설명                            | 크기 (비트) |
|-----------------|--------------------------------|------------|
| `int8_t`        | 부호 있는 8비트 정수           | 8          |
| `uint8_t`       | 부호 없는 8비트 정수           | 8          |
| `int16_t`       | 부호 있는 16비트 정수          | 16         |
| `uint16_t`      | 부호 없는 16비트 정수          | 16         |
| `int32_t`       | 부호 있는 32비트 정수          | 32         |
| `uint32_t`      | 부호 없는 32비트 정수          | 32         |
| `int64_t`       | 부호 있는 64비트 정수          | 64         |
| `uint64_t`      | 부호 없는 64비트 정수          | 64         |

#### 사용법
```c
#include <stdint.h>
#include <stdio.h>

int main() {
    int32_t signed_int = -100;
    uint32_t unsigned_int = 100;

    printf("부호 있는 32비트 정수: %d\n", signed_int);
    printf("부호 없는 32비트 정수: %u\n", unsigned_int);

    return 0;
}
```

**출력:**
```
부호 있는 32비트 정수: -100
부호 없는 32비트 정수: 100
```

---

### 1.2 최소 및 최대 크기 정수 타입

#### 최소 크기 정수
- **정의**: 최소한 지정된 비트 크기를 가지는 정수 타입.
- 예: `int_least8_t`, `uint_least16_t`.

#### 최대 크기 정수
- **정의**: 지정된 비트 크기에서 가장 효율적인 정수 타입.
- 예: `int_fast8_t`, `uint_fast16_t`.

**사용법:**
```c
#include <stdint.h>
#include <stdio.h>

int main() {
    int_least8_t least = 127;  // 최소 8비트
    int_fast16_t fast = 32000; // 가장 빠른 16비트

    printf("최소 8비트 정수: %d\n", least);
    printf("빠른 16비트 정수: %d\n", fast);

    return 0;
}
```

**출력:**
```
최소 8비트 정수: 127
빠른 16비트 정수: 32000
```

---

### 1.3 최대 값과 최소 값 상수

#### 주요 상수
| 상수              | 설명                          |
|-------------------|-------------------------------|
| `INT8_MIN`        | 부호 있는 8비트 최소값        |
| `INT8_MAX`        | 부호 있는 8비트 최대값        |
| `UINT8_MAX`       | 부호 없는 8비트 최대값        |
| `INT16_MIN`       | 부호 있는 16비트 최소값       |
| `INT16_MAX`       | 부호 있는 16비트 최대값       |
| `UINT16_MAX`      | 부호 없는 16비트 최대값       |
| `INT32_MIN`       | 부호 있는 32비트 최소값       |
| `INT32_MAX`       | 부호 있는 32비트 최대값       |
| `UINT32_MAX`      | 부호 없는 32비트 최대값       |

#### 사용법
```c
#include <stdint.h>
#include <stdio.h>

int main() {
    printf("부호 있는 8비트 최소값: %d\n", INT8_MIN);
    printf("부호 있는 8비트 최대값: %d\n", INT8_MAX);
    printf("부호 없는 8비트 최대값: %u\n", UINT8_MAX);

    return 0;
}
```

**출력:**
```
부호 있는 8비트 최소값: -128
부호 있는 8비트 최대값: 127
부호 없는 8비트 최대값: 255
```

---

### 1.4 포인터 크기 정수 타입

#### `intptr_t`와 `uintptr_t`
- **정의**: 포인터를 저장할 수 있는 정수 타입.
- **용도**: 포인터와 정수 간 변환을 안전하게 수행.

**사용법:**
```c
#include <stdint.h>
#include <stdio.h>

int main() {
    int a = 42;
    intptr_t ptr_value = (intptr_t)&a;  // 포인터를 정수로 변환

    printf("포인터 주소 값: %p\n", (void *)ptr_value);

    return 0;
}
```

**출력:**
```
포인터 주소 값: 0x7ffddc123456
```

---

## 2. 실습 예제

### 고정 크기 정수로 배열 처리
**코드:**
```c
#include <stdint.h>
#include <stdio.h>

int main() {
    int32_t numbers[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);

    for (size_t i = 0; i < size; i++) {
        printf("numbers[%zu]: %d\n", i, numbers[i]);
    }

    return 0;
}
```

**출력:**
```
numbers[0]: 1
numbers[1]: 2
numbers[2]: 3
numbers[3]: 4
numbers[4]: 5
```

---

### 포인터와 정수 변환
**코드:**
```c
#include <stdint.h>
#include <stdio.h>

int main() {
    int value = 10;
    int *ptr = &value;

    uintptr_t int_ptr = (uintptr_t)ptr;  // 포인터를 정수로 변환
    int *new_ptr = (int *)int_ptr;      // 정수를 다시 포인터로 변환

    printf("원래 값: %d\n", *new_ptr);

    return 0;
}
```

**출력:**
```
원래 값: 10
```

---

`<stdint.h>`는 고정 크기 정수와 플랫폼 독립적인 정수 타입을 제공하여 코드의 이식성과 명확성을 높이는 데 필수적입니다. 이를 잘 활용하면 다양한 시스템에서 안정적이고 유지보수 가능한 코드를 작성할 수 있습니다.

