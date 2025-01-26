# Advanced C Concepts

C 언어의 고급 개념은 프로그램의 성능을 최적화하고, 복잡한 문제를 해결하며, 시스템 수준의 제어를 가능하게 합니다. 이 문서는 초보자들이 고급 개념을 이해하고 활용할 수 있도록 간단한 설명과 실용적인 예제를 제공합니다.

---

## 1. 동적 메모리 관리 (Dynamic Memory Management)

### 동적 메모리란?
동적 메모리는 프로그램 실행 중에 필요에 따라 메모리를 할당하거나 해제하는 방식으로, 런타임에 메모리를 효율적으로 사용할 수 있습니다. C에서는 다음과 같은 함수를 사용하여 동적 메모리를 관리합니다:
- `malloc`: 메모리를 할당합니다.
- `calloc`: 초기화된 메모리를 할당합니다.
- `realloc`: 이미 할당된 메모리의 크기를 변경합니다.
- `free`: 할당된 메모리를 해제합니다.

### 예제: 동적 배열
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr;
    int n;

    printf("배열의 크기를 입력하세요: ");
    scanf("%d", &n);

    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("메모리 할당 실패\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    printf("배열의 내용: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}
```

### 주의사항
1. **메모리 누수 방지**: 사용하지 않는 메모리는 반드시 `free`를 호출하여 해제해야 합니다.
2. **NULL 체크**: 메모리 할당에 실패할 경우 반환값이 `NULL`이므로 이를 항상 확인해야 합니다.

---

## 2. 비트 연산 (Bitwise Operations)

### 비트 연산이란?
비트 연산은 데이터의 개별 비트를 조작하는 연산으로, 성능이 중요한 저수준 프로그래밍에서 유용하게 사용됩니다. 다음과 같은 연산자를 제공합니다:
- `&` (AND): 두 비트가 모두 1일 때 1 반환
- `|` (OR): 두 비트 중 하나가 1이면 1 반환
- `^` (XOR): 두 비트가 다를 때 1 반환
- `~` (NOT): 비트를 반전
- `<<` (왼쪽 시프트): 비트를 왼쪽으로 이동
- `>>` (오른쪽 시프트): 비트를 오른쪽으로 이동

### 예제: 플래그 관리
```c
#include <stdio.h>

#define FLAG_A (1 << 0)  // 0001
#define FLAG_B (1 << 1)  // 0010
#define FLAG_C (1 << 2)  // 0100

int main() {
    unsigned int flags = 0;

    // 플래그 설정
    flags |= FLAG_A;
    flags |= FLAG_B;

    // 플래그 확인
    if (flags & FLAG_A) {
        printf("FLAG_A가 설정됨\n");
    }

    // 플래그 해제
    flags &= ~FLAG_B;

    // 플래그 출력
    printf("현재 플래그: %d\n", flags);

    return 0;
}
```

### 사용 사례
- 네트워크 프로토콜 처리
- 상태 플래그 관리
- 특정 비트의 데이터 조작 (예: 색상 처리, 권한 설정)

---

## 3. 함수 포인터 (Function Pointers)

### 함수 포인터란?
함수 포인터는 함수의 주소를 저장하는 포인터로, 런타임에 함수 호출을 동적으로 선택하거나 전달할 수 있습니다. 이는 플러그인 시스템, 콜백 함수, 이벤트 처리기 등에 유용합니다.

### 예제: 함수 포인터로 동적 함수 호출
```c
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

int main() {
    int (*operation)(int, int);

    operation = add;
    printf("10 + 5 = %d\n", operation(10, 5));

    operation = multiply;
    printf("10 * 5 = %d\n", operation(10, 5));

    return 0;
}
```

### 사용 사례
- 콜백 함수 구현
- 플러그인 기반 아키텍처
- 이벤트 기반 시스템

---

## 4. 전처리기 (Preprocessor)

### 전처리기란?
C 컴파일러가 소스 코드를 컴파일하기 전에 수행하는 작업을 정의합니다. 전처리기는 다음과 같은 작업을 처리합니다:
- 매크로 정의
- 조건부 컴파일
- 파일 포함

### 주요 전처리기 지시문
- `#define`: 매크로 정의
- `#include`: 파일 포함
- `#if`, `#ifdef`, `#ifndef`, `#endif`: 조건부 컴파일
- `#pragma`: 컴파일러 특정 지시

### 예제: 매크로와 조건부 컴파일
```c
#include <stdio.h>

#define DEBUG 1

int main() {
    #ifdef DEBUG
        printf("디버그 모드 활성화\n");
    #else
        printf("디버그 모드 비활성화\n");
    #endif

    return 0;
}
```

### 사용 사례
- 디버그 코드 관리
- 플랫폼별 코드 분리
- 매크로를 통한 간단한 코드 최적화

---

## 5. 재귀 (Recursion)

### 재귀란?
재귀 함수는 자기 자신을 호출하는 함수입니다. 복잡한 문제를 더 작은 문제로 나누어 해결하는 데 유용합니다.

### 예제: 팩토리얼 계산
```c
#include <stdio.h>

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    int num = 5;
    printf("%d! = %d\n", num, factorial(num));
    return 0;
}
```

### 주의사항
1. **기저 조건 필수**: 종료 조건이 없으면 무한 루프에 빠질 수 있습니다.
2. **스택 오버플로우 방지**: 너무 깊은 재귀 호출은 프로그램의 스택 메모리를 초과할 수 있습니다.

---

## 6. 고급 활용

### 콜백 함수
콜백 함수는 다른 함수에 인수로 전달되어 특정 이벤트가 발생할 때 호출됩니다.

#### 예제: 배열 처리
```c
#include <stdio.h>

void processArray(int *arr, int size, void (*callback)(int)) {
    for (int i = 0; i < size; i++) {
        callback(arr[i]);
    }
}

void printElement(int elem) {
    printf("Element: %d\n", elem);
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    processArray(numbers, 5, printElement);
    return 0;
}
```

---

이 문서는 C 언어의 고급 개념을 간단한 설명과 예제를 통해 소개했습니다. 이러한 개념을 연습하면 보다 복잡한 문제를 효율적으로 해결할 수 있습니다. 추가 학습이 필요하면 각 주제에 대해 더 깊이 파고들어 보세요!

