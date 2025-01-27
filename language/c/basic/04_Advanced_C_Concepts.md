# 04. Advanced C Concepts

## 1. 포인터 (Pointers)

### 포인터란?
포인터는 메모리 주소를 저장하는 변수입니다. 이는 변수나 데이터의 위치를 참조할 수 있도록 도와줍니다.

#### 포인터 선언과 사용
```c
int num = 10;
int *ptr = &num;  // num의 주소를 ptr에 저장

printf("num의 값: %d\n", *ptr);  // 역참조로 값 출력
```

#### 주요 연산자
- **주소 연산자 (`&`)**: 변수의 메모리 주소를 반환.
- **역참조 연산자 (`*`)**: 포인터가 가리키는 값에 접근.

### 포인터와 배열
- 배열의 이름은 첫 번째 요소의 주소를 나타냅니다.

```c
int arr[5] = {1, 2, 3, 4, 5};
int *ptr = arr;

printf("첫 번째 요소: %d\n", *ptr);
printf("두 번째 요소: %d\n", *(ptr + 1));
```

### 다중 포인터
- 포인터를 가리키는 포인터입니다.

```c
int num = 10;
int *ptr = &num;
int **dptr = &ptr;

printf("num의 값: %d\n", **dptr);  // 10 출력
```

---

## 2. 동적 메모리 할당

### 동적 메모리 할당이란?
실행 중에 메모리를 동적으로 할당하여 유연하게 사용할 수 있는 기능입니다.

#### 주요 함수
| 함수        | 설명                                           |
|-------------|------------------------------------------------|
| `malloc`    | 지정한 크기만큼 메모리 블록을 할당합니다.         |
| `calloc`    | 초기화된 메모리 블록을 할당합니다.              |
| `realloc`   | 기존 메모리 블록의 크기를 변경합니다.           |
| `free`      | 동적으로 할당된 메모리를 해제합니다.            |

#### 예제: `malloc`과 `free`
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = (int *)malloc(5 * sizeof(int));  // 정수형 배열 5개 동적 할당

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
- 동적 메모리를 할당한 후 반드시 `free`를 호출하여 해제해야 합니다.

```c
int *ptr = (int *)malloc(sizeof(int));
*ptr = 42;
free(ptr);  // 메모리 해제
ptr = NULL;  // 댕글링 포인터 방지
```

---

## 3. 함수와 함수 포인터

### 함수 포인터란?
함수의 주소를 저장하여 동적으로 함수를 호출할 수 있는 포인터입니다.

#### 함수 포인터 선언과 사용
```c
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    int (*operation)(int, int) = add;  // 함수 포인터 선언

    printf("결과: %d\n", operation(3, 5));  // 함수 호출
    return 0;
}
```

#### 함수 포인터 배열
```c
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }

int (*operations[])(int, int) = {add, subtract};

printf("덧셈 결과: %d\n", operations[0](3, 5));
printf("뺄셈 결과: %d\n", operations[1](3, 5));
```

### 함수 포인터의 활용
- 콜백 함수 구현.
- 동적으로 함수 실행 경로를 결정.

---

## 4. 전처리기 (Preprocessor)

### 전처리기란?
C 컴파일러가 소스 코드를 컴파일하기 전에 수행하는 명령어 집합입니다.

#### 주요 전처리기 지시문
| 지시문       | 설명                               |
|--------------|------------------------------------|
| `#include`   | 헤더 파일 포함                     |
| `#define`    | 매크로 정의                        |
| `#ifdef`     | 조건부 컴파일 시작                  |
| `#ifndef`    | 조건부 컴파일 (미정의 상태 검사)     |
| `#pragma`    | 컴파일러에 특정 명령 전달          |

#### 매크로 정의
```c
#define PI 3.14159
#define MAX(a, b) ((a) > (b) ? (a) : (b))

printf("원주율: %.2f\n", PI);
printf("최대값: %d\n", MAX(10, 20));
```

#### 조건부 컴파일
```c
#ifdef DEBUG
    printf("디버그 모드\n");
#else
    printf("릴리스 모드\n");
#endif
```

---

## 5. 재귀 함수 (Recursive Functions)

### 재귀 함수란?
재귀 함수는 자기 자신을 호출하여 반복 작업을 수행하는 함수입니다.

#### 기본 구조
```c
int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;  // 기저 조건
    }
    return n * factorial(n - 1);  // 재귀 호출
}

int main() {
    printf("5! = %d\n", factorial(5));
    return 0;
}
```

#### 꼬리 재귀 (Tail Recursion)
컴파일러가 최적화할 수 있는 재귀 호출 방식입니다.

```c
int factorial_tail(int n, int acc) {
    if (n == 0) {
        return acc;
    }
    return factorial_tail(n - 1, n * acc);
}

int main() {
    printf("5! = %d\n", factorial_tail(5, 1));
    return 0;
}
```

---

## 6. 간단한 예제: 동적 함수 호출

### 프로그램
```c
#include <stdio.h>

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }

void executeOperation(int (*operation)(int, int), int x, int y) {
    printf("결과: %d\n", operation(x, y));
}

int main() {
    executeOperation(add, 10, 5);
    executeOperation(subtract, 10, 5);
    return 0;
}
```

### 프로그램 설명
1. 함수 포인터를 통해 동적으로 함수를 호출.
2. `executeOperation`은 함수 포인터를 인자로 받아 다양한 연산 수행.

---

이 장에서는 포인터, 동적 메모리 할당, 함수 포인터, 전처리기, 그리고 재귀 함수와 같은 고급 C 개념을 다뤘습니다. 이러한 개념은 복잡한 프로그램 개발에서 필수적인 도구입니다.

