# C 언어 Basics

## 변수와 데이터 타입

### 1. 변수의 개념
변수는 데이터를 저장하고 참조하는 데 사용되는 이름이 붙은 메모리 공간입니다.
C 언어에서 변수는 특정 데이터 타입을 가지며, 타입에 따라 저장 가능한 데이터 종류와 크기가 결정됩니다.

#### 변수 선언
```c
int age;
float temperature;
char grade;
```

#### 변수 초기화
```c
int count = 0;
float pi = 3.14159;
char initial = 'A';
```

#### 변수 명명 규칙
1. 문자, 숫자, 언더스코어(_)만 사용 가능
2. 첫 글자는 문자나 언더스코어로 시작
3. 대소문자 구분
4. 예약어 사용 불가

### 2. 기본 데이터 타입

#### 정수형
- **int**: 일반적인 정수
- **short**: 작은 정수
- **long**: 큰 정수
- **char**: 문자를 저장하며 작은 정수로도 사용 가능

```c
int a = 10;
short b = 20;
long c = 30L;
char d = 'A';
```

#### 부동소수점형
- **float**: 단밀도 부동소수점
- **double**: 배정밀도 부동소수점
- **long double**: 확장 정밀도 부동소수점

```c
float f = 3.14f;
double d = 3.14159265359;
long double ld = 3.14159265359L;
```

#### 불리언형 (C99 이상)
- **_Bool**: 참(1)과 거짓(0)을 나타내는 타입
- `<stdbool.h>`를 사용하면 `bool`, `true`, `false`를 사용할 수 있습니다.

```c
#include <stdbool.h>
bool is_valid = true;
_Bool is_active = 1;
```

---

## 연산자와 표현식

### 1. 산술 연산자
- `+` (덧셈)
- `-` (뺄셈)
- `*` (곱셈)
- `/` (나눗셈)
- `%` (나머지)

```c
int a = 10, b = 3;
int sum = a + b;    // 13
int diff = a - b;   // 7
int product = a * b; // 30
int quotient = a / b; // 3
int remainder = a % b; // 1
```

### 2. 증감 연산자
- `++`: 1 증가
- `--`: 1 감소

```c
int x = 5;
int y = ++x; // y = 6, x = 6
int z = x--; // z = 6, x = 5
```

### 3. 관계 연산자
- `==`: 같음
- `!=`: 다름
- `<`, `>`, `<=`, `>=`: 대소 비교

### 4. 논리 연산자
- `&&`: 논리 AND
- `||`: 논리 OR
- `!`: 논리 NOT

```c
if (a > 0 && b > 0) {
    printf("a와 b는 모두 양수입니다.\n");
}
```

### 5. 비트 연산자
- `&` (비트 AND)
- `|` (비트 OR)
- `^` (비트 XOR)
- `~` (비트 NOT)
- `<<` (왼쪽 시프트)
- `>>` (오른쪽 시프트)

---

## 제어 구조

### 1. 조건문

#### if문
```c
if (조건) {
    // 조건이 참일 때 실행
}
```

#### if-else문
```c
if (조건) {
    // 조건이 참일 때 실행
} else {
    // 조건이 거짓일 때 실행
}
```

#### switch문
```c
switch (표현식) {
    case 값1:
        // 코드
        break;
    case 값2:
        // 코드
        break;
    default:
        // 기본 코드
}
```

### 2. 반복문

#### for문
```c
for (초기화; 조건; 증감) {
    // 반복할 코드
}
```

#### while문
```c
while (조건) {
    // 반복할 코드
}
```

#### do-while문
```c
do {
    // 최소 한 번은 실행
} while (조건);
```

### 3. 분기문

#### break
```c
for (int i = 0; i < 10; i++) {
    if (i == 5) {
        break;
    }
}
```

#### continue
```c
for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
        continue;
    }
    printf("%d ", i); // 홀수만 출력
}
```

---

## 함수

### 1. 함수 정의
```c
반환타입 함수이름(매개변수) {
    // 함수 본문
    return 반환값;
}
```

#### 예제
```c
int add(int a, int b) {
    return a + b;
}
```

### 2. 함수 호출
```c
int result = add(5, 3);
```

### 3. 반환값과 매개변수
- 반환값이 없는 함수: `void` 사용
```c
void printMessage() {
    printf("Hello, World!\n");
}
```

- 매개변수가 없는 함수
```c
int getRandomNumber() {
    return 42;
}
```

### 4. 재귀 함수
```c
int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}
```

### 5. 가변 인자 함수
```c
#include <stdarg.h>

int sum(int count, ...) {
    va_list args;
    va_start(args, count);

    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }

    va_end(args);
    return total;
}
```

