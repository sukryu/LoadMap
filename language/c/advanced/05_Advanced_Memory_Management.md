# 05. Advanced Memory Management

## 1. 메모리 모델 심화

### C 프로그램의 메모리 구조
C 언어에서 프로그램 실행 중 메모리는 다음과 같이 나뉩니다:

1. **코드 영역 (Text Segment)**: 실행 가능한 코드가 저장되는 영역. 읽기 전용입니다.
2. **데이터 영역 (Data Segment)**:
   - 초기화된 전역 변수와 정적 변수가 저장됩니다.
   - 프로그램 종료 시까지 유지됩니다.
3. **BSS 영역 (BSS Segment)**: 초기화되지 않은 전역 변수와 정적 변수가 저장되는 영역. 시작 시 0으로 초기화됩니다.
4. **힙 (Heap)**: 동적 메모리 할당을 위한 공간으로, 프로그래머가 직접 관리해야 합니다.
5. **스택 (Stack)**: 함수 호출 시 생성되는 지역 변수와 반환 주소가 저장됩니다. LIFO 구조를 따릅니다.

#### 메모리 구조 다이어그램
```
높은 주소
+------------------+
|      스택        |
|        ↓         |
|      힙          |
|        ↑         |
|   BSS 영역       |
|   데이터 영역    |
|   코드 영역      |
+------------------+
낮은 주소
```

---

## 2. 동적 메모리 할당 심화

### 동적 메모리 할당 함수
C 언어에서는 동적 메모리를 할당하고 관리하기 위해 다음 함수를 제공합니다:

| 함수       | 설명                                   |
|------------|--------------------------------------|
| `malloc`   | 지정한 크기의 메모리 블록 할당.         |
| `calloc`   | 초기화된 메모리 블록 할당.              |
| `realloc`  | 기존 메모리 블록 크기 조정.             |
| `free`     | 동적으로 할당된 메모리 해제.            |

#### 예제: 기본 동적 메모리 사용
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = (int *)malloc(5 * sizeof(int));  // 정수형 배열 5개 동적 할당
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

### 메모리 누수 방지
메모리 누수는 동적으로 할당된 메모리를 해제하지 않아 발생합니다. 이를 방지하려면 모든 `malloc` 호출에 대해 반드시 `free`를 호출해야 합니다.

#### 메모리 누수 예제
```c
#include <stdlib.h>

void leakyFunction() {
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 42;  // 메모리를 사용하지만 free를 호출하지 않음
}
```

#### 수정된 코드
```c
void safeFunction() {
    int *ptr = (int *)malloc(sizeof(int));
    if (ptr != NULL) {
        *ptr = 42;
        free(ptr);  // 메모리 해제
    }
}
```

---

## 3. 메모리 풀 (Memory Pool)

### 메모리 풀 개념
메모리 풀은 미리 고정된 크기의 메모리 블록을 할당해 동적 메모리 할당의 오버헤드를 줄이고, 메모리 단편화를 방지합니다.

#### 메모리 풀 구현 예제
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POOL_SIZE 1024
static char memory_pool[POOL_SIZE];
static size_t pool_index = 0;

void* allocate(size_t size) {
    if (pool_index + size > POOL_SIZE) {
        return NULL; // 메모리 부족
    }
    void* ptr = &memory_pool[pool_index];
    pool_index += size;
    return ptr;
}

void reset_pool() {
    pool_index = 0;  // 메모리 풀 초기화
}

int main() {
    char* data = (char*)allocate(100);
    if (data) {
        strcpy(data, "Memory Pool Test");
        printf("%s\n", data);
    } else {
        printf("메모리 부족\n");
    }

    reset_pool();
    return 0;
}
```

---

## 4. 메모리 단편화 문제

### 단편화의 종류
1. **외부 단편화**: 사용 가능한 메모리가 충분하지만, 연속된 블록이 없어서 할당이 불가능한 상태.
2. **내부 단편화**: 할당된 메모리 블록이 요청된 크기보다 클 때 발생하는 낭비.

### 단편화 해결 방법
1. **메모리 풀 사용**: 연속된 메모리 블록을 미리 할당.
2. **메모리 압축**: 사용하지 않는 메모리를 재배치.
3. **적절한 크기의 블록 설계**: 메모리 요구를 예측하여 블록 크기 최적화.

---

## 5. 가상 메모리와 페이지 테이블

### 가상 메모리란?
가상 메모리는 물리 메모리와 독립적으로 동작하며, 각 프로세스가 고유한 메모리 공간을 가지도록 설계되었습니다. 이는 메모리 보호와 프로세스 간의 간섭 방지에 기여합니다.

### 페이지 테이블
- 가상 주소를 물리 주소로 변환하는 데이터 구조.
- 페이지 크기(보통 4KB) 단위로 메모리를 관리.

#### 예제: 가상 메모리 주소 계산
```text
가상 주소: 0x12345
페이지 크기: 4KB (0x1000)
페이지 번호: 0x12
오프셋: 0x345
```

---

## 6. 메모리 디버깅 도구

### Valgrind
Valgrind는 메모리 누수 및 잘못된 메모리 접근을 탐지하는 데 사용되는 도구입니다.

#### 사용 예제
```bash
valgrind --leak-check=full ./program
```

### AddressSanitizer
AddressSanitizer는 런타임에 메모리 문제를 탐지하는 도구입니다.

#### GCC에서 활성화
```bash
gcc -fsanitize=address -o program program.c
./program
```

---

## 7. 실습: 동적 메모리 관리 라이브러리 구현

### 목표
사용자 정의 동적 메모리 관리 함수를 구현합니다.

#### 코드
```c
#include <stdio.h>
#include <stdlib.h>

void* custom_malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    return ptr;
}

void custom_free(void* ptr) {
    if (ptr != NULL) {
        free(ptr);
        printf("메모리 해제 완료\n");
    }
}

int main() {
    int* arr = (int*)custom_malloc(5 * sizeof(int));
    for (int i = 0; i < 5; i++) {
        arr[i] = i + 1;
    }

    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    custom_free(arr);
    return 0;
}
```

---

고급 메모리 관리는 프로그램의 안정성과 성능을 향상시키는 핵심 기술입니다. 메모리 풀, 단편화 해결, 디버깅 도구 등을 활용하여 효율적이고 안정적인 코드를 작성하세요.

