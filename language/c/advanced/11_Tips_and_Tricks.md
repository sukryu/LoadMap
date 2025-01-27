# 11. C Programming Tips and Tricks

## 1. 코드 최적화 트릭

### 레지스터 키워드 활용 (deprecated but educational)
`register` 키워드는 변수의 값을 CPU 레지스터에 저장하도록 요청하여 접근 속도를 높입니다. 현대 컴파일러에서는 효과가 제한적이지만 학습 목적으로 알아두면 좋습니다.

#### 예제
```c
#include <stdio.h>

int main() {
    register int counter;
    for (counter = 0; counter < 10; counter++) {
        printf("%d\n", counter);
    }
    return 0;
}
```

### 매크로와 인라인 함수의 균형 잡기
- **매크로**는 컴파일 타임에 코드가 확장되어 빠르지만 디버깅이 어렵습니다.
- **인라인 함수**는 매크로와 유사한 성능을 제공하며 디버깅에 유리합니다.

#### 매크로와 인라인 비교
```c
#define SQUARE(x) ((x) * (x))  // 매크로

inline int square(int x) {  // 인라인 함수
    return x * x;
}

int main() {
    printf("매크로 결과: %d\n", SQUARE(5));
    printf("인라인 함수 결과: %d\n", square(5));
    return 0;
}
```

### 루프 언롤링 (Loop Unrolling)
루프의 반복 횟수를 줄이기 위해 여러 반복을 한 번에 처리하여 성능을 향상시킬 수 있습니다.

#### 예제
```c
void processArray(int *arr, int size) {
    for (int i = 0; i < size; i += 4) {
        arr[i] = arr[i] * 2;
        arr[i + 1] = arr[i + 1] * 2;
        arr[i + 2] = arr[i + 2] * 2;
        arr[i + 3] = arr[i + 3] * 2;
    }
}
```

---

## 2. 디버깅 및 로깅 트릭

### 조건부 로깅
컴파일 타임에 디버그 코드를 포함하거나 제거할 수 있습니다.

#### 예제
```c
#include <stdio.h>

#define DEBUG 1

#if DEBUG
    #define LOG(msg) printf("DEBUG: %s\n", msg)
#else
    #define LOG(msg)
#endif

int main() {
    LOG("디버깅 모드 활성화");
    printf("프로그램 실행\n");
    return 0;
}
```

### GDB를 활용한 동적 디버깅
1. 중단점 설정:
   ```bash
   gdb program
   (gdb) break main
   ```
2. 메모리 값 확인:
   ```bash
   (gdb) print variable
   ```

---

## 3. 메모리 최적화 기법

### 메모리 정렬과 패딩 제거
구조체 내부의 데이터 정렬을 최적화하여 메모리 사용량을 줄일 수 있습니다.

#### 예제
```c
#include <stdio.h>
#include <stddef.h>

struct Unoptimized {
    char a;
    int b;
    char c;
};

struct Optimized {
    int b;
    char a;
    char c;
};

int main() {
    printf("비최적화 구조체 크기: %zu\n", sizeof(struct Unoptimized));
    printf("최적화 구조체 크기: %zu\n", sizeof(struct Optimized));
    return 0;
}
```

### 메모리 풀 활용
메모리 단편화를 줄이고, 반복적인 메모리 할당/해제를 방지합니다.

#### 예제
```c
#define POOL_SIZE 1024
static char memory_pool[POOL_SIZE];
static size_t pool_index = 0;

void* allocate(size_t size) {
    if (pool_index + size > POOL_SIZE) {
        return NULL;
    }
    void* ptr = &memory_pool[pool_index];
    pool_index += size;
    return ptr;
}

void reset_pool() {
    pool_index = 0;
}
```

---

## 4. 하드웨어와 가까운 최적화

### 비트 연산 활용
비트 연산은 조건문과 산술 연산을 대체하여 성능을 높이는 데 사용됩니다.

#### 예제: 홀수/짝수 판별
```c
#include <stdio.h>

int main() {
    int num = 5;
    if (num & 1) {
        printf("홀수\n");
    } else {
        printf("짝수\n");
    }
    return 0;
}
```

### 데이터 캐싱
데이터를 캐시 메모리에 적합하게 배치하면 성능을 극대화할 수 있습니다.

#### 예제
```c
void processMatrix(int matrix[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] *= 2;
        }
    }
}
```

---

## 5. 코드 가독성과 유지보수 향상

### 매직 넘버(Magic Number) 제거
매직 넘버 대신 상수와 매크로를 사용하여 의미를 명확히 합니다.

#### 예제
```c
#define MAX_BUFFER_SIZE 256

char buffer[MAX_BUFFER_SIZE];
```

### 함수 포인터 활용
동적으로 함수 호출을 변경할 수 있습니다.

#### 예제
```c
#include <stdio.h>

void sayHello() {
    printf("Hello\n");
}

void sayGoodbye() {
    printf("Goodbye\n");
}

int main() {
    void (*funcPtr)();
    funcPtr = sayHello;
    funcPtr();

    funcPtr = sayGoodbye;
    funcPtr();
    return 0;
}
```

---

C 언어는 성능 최적화와 하드웨어 접근에서 강력한 도구이지만, 개발자는 생산성을 높이기 위해 다양한 트릭과 기술을 활용해야 합니다. 위의 팁과 트릭을 실무에 적용하여 효율적인 코드를 작성해보세요.

