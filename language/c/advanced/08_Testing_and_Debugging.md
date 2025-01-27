# 08. Testing and Debugging

## 1. 테스트와 디버깅의 중요성

테스트와 디버깅은 소프트웨어 개발의 필수 단계로, 코드의 안정성과 품질을 보장하는 데 중요한 역할을 합니다.

### 테스트의 목적
1. **버그 식별**: 코드에 숨겨진 결함 발견.
2. **요구 사항 충족**: 프로그램이 설계대로 동작하는지 확인.
3. **코드 유지 보수**: 변경된 코드가 기존 기능에 영향을 미치지 않도록 보장.

### 디버깅의 목적
1. **문제 해결**: 런타임 오류와 논리적 결함 수정.
2. **성능 개선**: 병목 지점 탐지 및 최적화.
3. **코드 이해**: 복잡한 코드의 동작 방식 파악.

---

## 2. 테스트 주도 개발 (Test-Driven Development, TDD)

### TDD란?
TDD는 코드를 작성하기 전에 테스트 케이스를 먼저 설계하고, 테스트를 기반으로 코드를 구현하는 개발 방식입니다.

#### TDD 주기
1. **테스트 작성**: 실패할 테스트 케이스 설계.
2. **코드 작성**: 테스트를 통과하기 위한 최소한의 코드 작성.
3. **리팩토링**: 코드를 정리하며 최적화.

### C 언어에서 TDD 도구
1. **CUnit**: 단위 테스트 프레임워크.
2. **Unity**: 임베디드 시스템용 경량 테스트 도구.

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

## 3. 디버깅 기법

### 기본 디버깅 도구
1. **GDB (GNU Debugger)**: C/C++ 프로그램 디버깅 도구.
2. **Valgrind**: 메모리 누수 및 오류 탐지.
3. **printf 디버깅**: 출력문을 삽입해 코드 흐름 파악.

#### GDB 사용법
1. 컴파일 시 디버깅 정보 포함:
   ```bash
   gcc -g -o program program.c
   ```
2. GDB 실행:
   ```bash
   gdb program
   ```
3. 주요 명령어:
   - `break <line_number>`: 중단점 설정.
   - `run`: 프로그램 실행.
   - `next`: 다음 명령 실행.
   - `print <variable>`: 변수 값 출력.
   - `backtrace`: 호출 스택 확인.

#### 예제: GDB로 디버깅
```c
#include <stdio.h>

int main() {
    int x = 10;
    int y = 0;
    printf("Result: %d\n", x / y);  // 런타임 오류
    return 0;
}
```
```bash
gcc -g -o program program.c
gdb program
(gdb) run
(gdb) backtrace
(gdb) print x
```

---

## 4. 메모리 디버깅

### 메모리 누수 탐지
**Valgrind**는 메모리 관련 문제를 탐지하는 데 유용한 도구입니다.

#### Valgrind 사용
1. 프로그램 실행:
   ```bash
   valgrind --leak-check=full ./program
   ```
2. 결과 분석:
   - `definitely lost`: 명백한 메모리 누수.
   - `indirectly lost`: 참조가 끊긴 메모리 누수.

#### 메모리 누수 예제
```c
#include <stdlib.h>

void leakyFunction() {
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 42;
    // free(ptr);  // 메모리 누수 발생
}

int main() {
    leakyFunction();
    return 0;
}
```

---

## 5. 성능 테스트

### 성능 병목점 분석
1. **gprof**: 프로그램의 실행 시간을 분석.
2. **perf**: Linux에서 성능 데이터를 수집.

#### gprof 사용법
1. 컴파일:
   ```bash
   gcc -pg -o program program.c
   ```
2. 실행:
   ```bash
   ./program
   ```
3. 프로파일링 결과 출력:
   ```bash
   gprof program gmon.out > analysis.txt
   ```

#### 프로파일링 결과 예제
```
Flat profile:
  %   cumulative   self              self     total
 time   seconds   seconds    calls   s/call   s/call  name
  90.00      0.90     0.90    10000     0.00     0.00  compute
  10.00      1.00     0.10    10000     0.00     0.00  process
```

---

## 6. 코드 커버리지 분석

### gcov 도구
**gcov**는 코드 커버리지를 분석하는 도구로, 테스트가 얼마나 많은 코드를 실행했는지 확인할 수 있습니다.

#### gcov 사용법
1. 컴파일 시 커버리지 활성화:
   ```bash
   gcc -fprofile-arcs -ftest-coverage -o program program.c
   ```
2. 실행:
   ```bash
   ./program
   ```
3. 커버리지 출력:
   ```bash
   gcov program.c
   ```

#### 결과 파일 분석
```text
File 'program.c'
Lines executed:80.00% of 10
Creating 'program.c.gcov'
```

---

## 7. 실습: 디버깅과 테스트 적용

### 문제
다음 코드에서 메모리 누수와 논리적 오류를 디버깅하고 수정하세요:
```c
#include <stdio.h>
#include <stdlib.h>

int* createArray(int size) {
    int *arr = malloc(size * sizeof(int));
    for (int i = 0; i <= size; i++) {  // 경계 초과 오류
        arr[i] = i;
    }
    return arr;
}

int main() {
    int *array = createArray(5);
    for (int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}
```

### 수정된 코드
```c
#include <stdio.h>
#include <stdlib.h>

int* createArray(int size) {
    int *arr = malloc(size * sizeof(int));
    if (arr == NULL) {
        perror("메모리 할당 실패");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {  // 경계 초과 수정
        arr[i] = i;
    }
    return arr;
}

int main() {
    int *array = createArray(5);
    for (int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    free(array);  // 메모리 해제
    return 0;
}
```

---

테스트와 디버깅은 안정적이고 효율적인 소프트웨어 개발을 위한 핵심입니다. 위에서 소개된 도구와 기법을 활용하여 코드를 검증하고 문제를 해결하세요.

