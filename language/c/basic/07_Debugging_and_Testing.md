# 07. Debugging and Testing

## 1. 디버깅 (Debugging)

디버깅은 프로그램에서 발생한 오류를 찾아 수정하는 과정입니다. 이는 소프트웨어 개발의 필수적인 단계로, 효율적인 디버깅은 개발 시간을 줄이고 프로그램의 안정성을 높이는 데 기여합니다.

### 디버깅 도구

#### GDB (GNU Debugger)
GDB는 가장 널리 사용되는 디버깅 도구 중 하나로, 다양한 기능을 제공합니다.

#### 주요 명령어
| 명령어       | 설명                                  |
|--------------|---------------------------------------|
| `gdb program` | 디버깅할 프로그램 실행               |
| `break`      | 특정 위치에 중단점 설정              |
| `run`        | 프로그램 실행                        |
| `next`       | 다음 명령어 실행                     |
| `step`       | 함수 내부로 진입                     |
| `print`      | 변수 값 출력                         |
| `quit`       | 디버깅 종료                          |

#### 예제: GDB 사용
```bash
gcc -g -o program program.c  # 디버깅 정보를 포함하여 컴파일
gdb program                  # 디버깅 시작
```
```gdb
(gdb) break main             # main 함수에 중단점 설정
(gdb) run                    # 프로그램 실행
(gdb) print variable_name    # 변수 값 출력
(gdb) next                   # 다음 명령 실행
```

### 디버깅 팁
1. **코드 주석과 로그 추가**:
   - `printf`로 변수 값을 출력해 문제를 파악.
   ```c
   printf("변수 값: %d\n", var);
   ```
2. **코드 단순화**:
   - 오류를 재현하기 위해 복잡한 코드를 간소화.
3. **중단점 설정**:
   - 특정 지점에서 프로그램 상태를 분석.

---

## 2. 단위 테스트 (Unit Testing)

단위 테스트는 프로그램의 특정 모듈이나 함수가 올바르게 작동하는지 검증하는 과정입니다.

### 단위 테스트의 중요성
- 코드의 품질 보장.
- 버그 조기 발견.
- 리팩토링 시 안정성 확보.

### C 언어에서의 단위 테스트 도구

#### CUnit
CUnit은 C 프로그램의 단위 테스트를 위한 경량 테스트 프레임워크입니다.

#### 기본 사용법
1. **테스트 스위트 생성**:
   - 연관된 테스트 케이스를 모아둔 그룹.
2. **테스트 케이스 작성**:
   - 개별 함수 또는 기능을 테스트.

#### 예제: CUnit 사용
```c
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

// 테스트 대상 함수
int add(int a, int b) {
    return a + b;
}

void test_add() {
    CU_ASSERT(add(2, 3) == 5);
    CU_ASSERT(add(-1, 1) == 0);
}

int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("TestSuite", 0, 0);
    CU_add_test(suite, "test_add", test_add);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
```

---

## 3. 메모리 디버깅

메모리 관련 오류(누수, 잘못된 접근 등)는 프로그램의 안정성을 크게 저하시킬 수 있습니다.

### Valgrind
Valgrind는 메모리 누수 및 잘못된 메모리 접근을 탐지하는 도구입니다.

#### 주요 명령어
```bash
valgrind --leak-check=full ./program
```

#### 예제: Valgrind로 메모리 누수 확인
```c
#include <stdlib.h>

int main() {
    int *arr = (int *)malloc(5 * sizeof(int));
    arr[0] = 10;  // 메모리 할당 후 해제하지 않음
    return 0;
}
```
```bash
valgrind --leak-check=full ./program
```

### 메모리 디버깅 팁
1. **할당된 메모리 해제**:
   - `malloc` 또는 `calloc`으로 할당된 메모리를 `free`로 해제.
2. **댕글링 포인터 방지**:
   - 메모리를 해제한 후 포인터를 `NULL`로 초기화.
3. **정적 분석 도구 사용**:
   - Clang Static Analyzer 등으로 메모리 오류 사전 탐지.

---

## 4. 에러 처리

에러 처리는 프로그램의 안정성을 높이고, 예기치 않은 상황에서의 동작을 정의합니다.

### 반환 값 검사
- 함수의 반환 값을 확인해 에러를 처리합니다.
```c
FILE *file = fopen("data.txt", "r");
if (file == NULL) {
    perror("파일 열기 실패");
    return 1;
}
```

### 에러 코드
- 에러 상황을 나타내는 코드를 정의.
```c
#define SUCCESS 0
#define ERROR_NULL_POINTER -1

int process(int *ptr) {
    if (ptr == NULL) {
        return ERROR_NULL_POINTER;
    }
    // 처리 로직
    return SUCCESS;
}
```

---

## 5. 간단한 예제: 파일 읽기 에러 처리

### 프로그램
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        perror("파일 열기 실패");
        return 1;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}
```

### 프로그램 설명
1. 파일 열기 시 실패 여부를 확인하고 오류 메시지 출력.
2. 파일을 읽으며 내용을 출력.
3. 파일을 닫아 자원을 해제.

---

이 장에서는 디버깅과 테스트의 기본 개념과 방법을 다뤘습니다. 이를 통해 코드의 안정성과 품질을 높이는 방법을 익힐 수 있습니다.

