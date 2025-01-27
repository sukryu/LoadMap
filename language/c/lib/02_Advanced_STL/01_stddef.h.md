# <stddef.h>: 표준 정의 헤더 파일

`<stddef.h>`는 C 언어에서 데이터 타입과 상수를 정의하는 데 사용되는 표준 헤더 파일입니다. 이 헤더는 포인터와 메모리 관련 작업, 그리고 데이터 구조 설계에서 필수적인 타입과 상수를 제공합니다.

---

## 1. 주요 내용

### 1.1 데이터 타입 정의

#### `size_t`
- **정의**: 메모리 크기를 나타내는 무부호 정수형 데이터 타입.
- **용도**: 배열 크기, 메모리 크기 등을 나타낼 때 사용됩니다.
- **플랫폼 독립적**: 컴파일러와 플랫폼에 따라 크기가 자동으로 조정됩니다.

**사용법:**
```c
#include <stddef.h>
#include <stdio.h>

int main() {
    size_t array_size = 10;
    printf("배열 크기: %zu\n", array_size);
    return 0;
}
```

**출력:**
```
배열 크기: 10
```

---

#### `ptrdiff_t`
- **정의**: 두 포인터 간의 차이를 나타내는 부호 있는 정수형 데이터 타입.
- **용도**: 같은 배열 내의 두 포인터 간 거리를 계산할 때 사용됩니다.

**사용법:**
```c
#include <stddef.h>
#include <stdio.h>

int main() {
    int array[10];
    int *ptr1 = &array[2];
    int *ptr2 = &array[8];

    ptrdiff_t diff = ptr2 - ptr1;
    printf("포인터 간 거리: %td\n", diff);
    return 0;
}
```

**출력:**
```
포인터 간 거리: 6
```

---

#### `nullptr_t` (C++11부터 지원)
- **정의**: `nullptr`을 위한 타입. C++에서만 사용되며, C에서는 지원되지 않습니다.
- **용도**: `nullptr`을 명확히 표현하기 위한 타입.

**C++ 사용 예:**
```cpp
#include <stddef.h>
#include <iostream>

int main() {
    nullptr_t null_pointer = nullptr;
    if (null_pointer == nullptr) {
        std::cout << "null_pointer는 nullptr입니다." << std::endl;
    }
    return 0;
}
```

---

### 1.2 매크로 정의

#### `NULL`
- **정의**: 포인터의 초기화 값으로 사용되는 매크로.
- **값**: `((void*)0)`로 정의되며, null 포인터를 나타냅니다.

**사용법:**
```c
#include <stddef.h>
#include <stdio.h>

int main() {
    int *ptr = NULL;
    if (ptr == NULL) {
        printf("포인터가 NULL입니다.\n");
    }
    return 0;
}
```

**출력:**
```
포인터가 NULL입니다.
```

---

### 1.3 오프셋 계산 매크로

#### `offsetof`
- **정의**: 구조체 멤버의 오프셋을 바이트 단위로 반환하는 매크로.
- **용도**: 구조체 내부 멤버가 구조체 시작 지점에서 얼마나 떨어져 있는지 계산.

**사용법:**
```c
#include <stddef.h>
#include <stdio.h>

struct Example {
    int id;
    double value;
    char name[20];
};

int main() {
    printf("id의 오프셋: %zu\n", offsetof(struct Example, id));
    printf("value의 오프셋: %zu\n", offsetof(struct Example, value));
    printf("name의 오프셋: %zu\n", offsetof(struct Example, name));
    return 0;
}
```

**출력:**
```
id의 오프셋: 0
value의 오프셋: 4
name의 오프셋: 12
```

---

## 2. 실습 예제

### 포인터 거리 계산 프로그램
**코드:**
```c
#include <stddef.h>
#include <stdio.h>

int main() {
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *start = &array[0];
    int *end = &array[9];

    ptrdiff_t distance = end - start;
    printf("배열의 시작과 끝 사이의 거리: %td\n", distance);

    return 0;
}
```

**출력:**
```
배열의 시작과 끝 사이의 거리: 9
```

---

### 구조체 오프셋을 활용한 메모리 접근
**코드:**
```c
#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct Data {
    int id;
    char name[50];
    double value;
};

int main() {
    struct Data data;
    memset(&data, 0, sizeof(data));

    printf("name의 오프셋: %zu\n", offsetof(struct Data, name));

    strcpy((char *)((char *)&data + offsetof(struct Data, name)), "Example");
    printf("name: %s\n", data.name);

    return 0;
}
```

**출력:**
```
name의 오프셋: 4
name: Example
```

---

`<stddef.h>`는 포인터, 메모리 구조 설계, 데이터 타입 관련 작업에 필수적인 기능을 제공합니다. 이를 잘 활용하면 메모리 효율적 접근과 데이터 처리에 유용한 코드를 작성할 수 있습니다.

