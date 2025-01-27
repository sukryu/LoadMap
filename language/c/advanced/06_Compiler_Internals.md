# 06. Compiler Internals

## 1. 컴파일러의 동작 원리

### 컴파일의 단계
컴파일러는 소스 코드를 실행 가능한 기계어 코드로 변환하는 도구로, 다음과 같은 주요 단계를 거칩니다:

1. **전처리 (Preprocessing)**
   - 전처리기 지시문(`#include`, `#define`) 처리.
   - 주석 제거, 매크로 확장, 조건부 컴파일 수행.

2. **컴파일 (Compilation)**
   - 전처리된 코드를 어셈블리 코드로 변환.
   - 구문 분석, 의미 분석, 코드 생성 포함.

3. **어셈블리 (Assembly)**
   - 어셈블리 코드를 기계어로 변환하여 객체 파일 생성.

4. **링킹 (Linking)**
   - 여러 객체 파일과 라이브러리를 결합하여 실행 가능한 바이너리 파일 생성.

#### 단계별 결과
| 단계          | 출력 파일           |
|---------------|---------------------|
| 전처리        | `.i` 파일           |
| 컴파일        | `.s` 파일           |
| 어셈블리      | `.o` 파일           |
| 링킹          | 실행 파일 (e.g., `a.out`) |

---

## 2. 전처리기

### 주요 전처리기 지시문
| 지시문       | 설명                                   |
|--------------|--------------------------------------|
| `#include`   | 헤더 파일 포함                         |
| `#define`    | 매크로 정의                            |
| `#ifdef`     | 조건부 컴파일 시작                      |
| `#ifndef`    | 조건부 컴파일 (미정의 상태 검사)         |
| `#pragma`    | 컴파일러에 특정 명령 전달               |

#### 매크로와 조건부 컴파일 예제
```c
#include <stdio.h>
#define DEBUG

int main() {
#ifdef DEBUG
    printf("디버그 모드 활성화\n");
#endif
    printf("프로그램 실행\n");
    return 0;
}
```

---

## 3. 구문 분석 (Parsing)

### 구문 분석이란?
구문 분석은 소스 코드를 구문 트리(Syntax Tree)로 변환하는 과정입니다. 이 과정은 다음 두 단계로 나뉩니다:

1. **어휘 분석 (Lexical Analysis)**: 소스 코드를 토큰(token)으로 분리.
2. **구문 분석 (Syntax Analysis)**: 토큰을 사용해 구문 트리를 생성.

#### 구문 트리 예시
코드: `int x = 10 + 5;`
```
Assignment
├── Variable: x
├── Operator: =
└── Expression
    ├── Constant: 10
    ├── Operator: +
    └── Constant: 5
```

---

## 4. 코드 최적화 패스

### 코드 최적화란?
코드 최적화는 실행 속도를 높이거나 메모리 사용량을 줄이기 위해 코드의 효율성을 개선하는 과정입니다. 컴파일러는 여러 최적화 패스를 통해 이를 수행합니다.

#### 주요 최적화 기법
1. **Dead Code Elimination**: 사용되지 않는 코드 제거.
2. **Constant Folding**: 상수 연산을 컴파일 시간에 계산.
3. **Loop Unrolling**: 루프 반복을 줄여 분기(branch) 비용 감소.
4. **Inlining**: 함수 호출을 코드로 직접 삽입.

#### 예제: 상수 폴딩
```c
// 입력 코드
int x = 10 * 5;

// 최적화된 코드
int x = 50;
```

---

## 5. 어셈블리 코드 분석

### C 코드와 어셈블리 코드의 관계
컴파일러는 C 코드에서 어셈블리 코드를 생성하여 CPU가 이해할 수 있는 명령어로 변환합니다.

#### 예제: 어셈블리 코드 생성
```c
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    printf("%d\n", add(5, 3));
    return 0;
}
}
```
컴파일 명령:
```bash
gcc -S -o program.s program.c
```
출력된 어셈블리 코드 (일부):
```
_add:
    movl    %edi, -4(%rsp)
    movl    %esi, -8(%rsp)
    movl    -4(%rsp), %eax
    addl    -8(%rsp), %eax
    ret
```

---

## 6. 커스텀 컴파일러 플래그 작성

### GCC 플래그 사용
GCC는 다양한 컴파일러 플래그를 제공하여 컴파일 과정을 사용자화할 수 있습니다.

#### 주요 플래그
| 플래그           | 설명                                   |
|------------------|--------------------------------------|
| `-Wall`          | 모든 경고를 활성화.                   |
| `-O1`, `-O2`, `-O3` | 최적화 레벨 설정.                     |
| `-g`             | 디버깅 정보 포함.                     |
| `-S`             | 어셈블리 코드 생성.                   |

#### 예제: 최적화와 디버깅 활성화
```bash
gcc -O2 -g -o program program.c
```

---

## 7. 실습: 간단한 인터프리터 제작

### 목표
간단한 수식 계산 인터프리터를 작성하여 컴파일러의 일부 기능을 이해합니다.

#### 코드
```c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int evaluate(const char* expression) {
    int result = 0;
    int sign = 1;

    for (const char* ptr = expression; *ptr != '\0'; ptr++) {
        if (isdigit(*ptr)) {
            result += sign * (*ptr - '0');
        } else if (*ptr == '+') {
            sign = 1;
        } else if (*ptr == '-') {
            sign = -1;
        }
    }

    return result;
}

int main() {
    char expression[100];
    printf("수식을 입력하세요 (예: 1+2-3): ");
    scanf("%s", expression);

    int result = evaluate(expression);
    printf("결과: %d\n", result);
    return 0;
}
```

### 설명
1. 입력된 수식을 문자 단위로 분석.
2. 숫자와 연산자를 파싱하여 결과 계산.
3. 단순한 구문 분석 및 계산 동작 이해.

---

컴파일러의 내부 동작을 이해하면 프로그램의 성능 최적화와 디버깅 능력을 향상시킬 수 있습니다. 이 장에서는 컴파일러의 주요 구성 요소와 원리를 학습했습니다.

