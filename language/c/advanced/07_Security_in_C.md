# 07. Security in C

## 1. C 언어와 보안

### C 언어의 보안 취약점
C는 강력하고 유연하지만, 메모리 관리를 직접 다루기 때문에 다음과 같은 보안 취약점이 존재합니다:

1. **버퍼 오버플로우**: 배열이나 버퍼의 경계를 넘어 데이터를 기록하거나 읽을 때 발생.
2. **포인터 오류**: 잘못된 포인터 사용으로 인해 메모리에 예기치 않은 접근.
3. **포맷 문자열 취약점**: 사용자 입력을 포맷 문자열로 직접 사용하는 경우 발생.
4. **메모리 누수**: 동적으로 할당된 메모리를 해제하지 않아 발생.

---

## 2. 버퍼 오버플로우 방지

### 버퍼 오버플로우란?
버퍼 오버플로우는 배열의 크기보다 많은 데이터를 기록하거나 읽으려 할 때 발생합니다. 이는 시스템 충돌, 데이터 유출, 코드 실행 같은 심각한 문제를 초래할 수 있습니다.

#### 취약한 코드 예제
```c
#include <stdio.h>
#include <string.h>

int main() {
    char buffer[10];
    strcpy(buffer, "This is a very long string");  // 버퍼 초과
    printf("%s\n", buffer);
    return 0;
}
```

#### 수정된 코드
```c
#include <stdio.h>
#include <string.h>

int main() {
    char buffer[10];
    strncpy(buffer, "This is a very long string", sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';  // NULL 종료 보장
    printf("%s\n", buffer);
    return 0;
}
```

### 방지 기법
1. **`strncpy` 사용**: 버퍼 크기를 초과하지 않도록 복사.
2. **경계 검사**: 데이터 크기를 항상 확인.
3. **스택 보호**: 컴파일러에서 스택 가드를 활성화.
   ```bash
   gcc -fstack-protector -o program program.c
   ```

---

## 3. 포인터와 메모리 보안

### 포인터 취약점
- **댕글링 포인터**: 해제된 메모리를 참조하는 포인터.
- **NULL 포인터 참조**: 초기화되지 않은 포인터를 사용하는 경우.

#### 예제: 댕글링 포인터
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 42;
    free(ptr);
    // ptr이 댕글링 상태
    *ptr = 0;  // 오류 발생 가능
    return 0;
}
```

#### 수정된 코드
```c
int main() {
    int *ptr = (int *)malloc(sizeof(int));
    if (ptr != NULL) {
        *ptr = 42;
        free(ptr);
        ptr = NULL;  // NULL로 초기화
    }
    return 0;
}
```

### 안전한 포인터 사용
1. 포인터를 NULL로 초기화.
2. 메모리 해제 후 포인터를 NULL로 설정.
3. 정적 분석 도구 활용 (예: Clang Static Analyzer).

---

## 4. 포맷 문자열 취약점

### 포맷 문자열 취약점이란?
사용자 입력을 `printf`와 같은 함수의 포맷 문자열로 사용할 때, 의도하지 않은 메모리 접근이나 코드 실행이 발생할 수 있습니다.

#### 취약한 코드 예제
```c
#include <stdio.h>

int main() {
    char userInput[100];
    gets(userInput);  // 입력값을 직접 읽음
    printf(userInput);  // 사용자 입력을 포맷 문자열로 사용
    return 0;
}
```

#### 수정된 코드
```c
#include <stdio.h>

int main() {
    char userInput[100];
    fgets(userInput, sizeof(userInput), stdin);  // 안전하게 입력받기
    printf("%s", userInput);  // 포맷 문자열 고정
    return 0;
}
```

### 방지 기법
1. **`fgets` 사용**: 입력 데이터를 제한적으로 읽기.
2. **포맷 문자열 고정**: 사용자 입력을 직접 포맷 문자열로 사용하지 않음.

---

## 5. 메모리 보호 기술

### 스택 가드
- 스택 상의 버퍼 오버플로우를 탐지하고 프로그램을 종료.
- 컴파일 시 `-fstack-protector` 플래그 사용.

### ASLR (Address Space Layout Randomization)
- 메모리 주소 공간을 임의화하여 공격자가 메모리 레이아웃을 예측하지 못하게 함.

### NX 비트 (No-eXecute Bit)
- 실행 불가능한 메모리 영역에서 코드 실행을 방지.

#### 활성화
운영 체제와 하드웨어에 따라 기본적으로 활성화되어 있음.

---

## 6. 안전한 C 코딩 관행

### 주요 원칙
1. **초과 데이터 방지**: 입력 데이터 크기를 항상 확인.
2. **정적 분석 도구 사용**: 코드의 잠재적 취약점 탐지.
3. **안전한 함수 사용**: `gets` 대신 `fgets`, `strcpy` 대신 `strncpy` 사용.

#### 안전한 문자열 처리 예제
```c
#include <stdio.h>
#include <string.h>

int main() {
    char dest[10];
    strncpy(dest, "Hello, World!", sizeof(dest) - 1);
    dest[sizeof(dest) - 1] = '\0';
    printf("%s\n", dest);
    return 0;
}
```

---

## 7. 실습: 간단한 취약점 수정

### 문제
다음 코드에서 버퍼 오버플로우와 포맷 문자열 취약점을 수정하세요:
```c
#include <stdio.h>

int main() {
    char buffer[10];
    printf("Enter your name: ");
    gets(buffer);
    printf(buffer);
    return 0;
}
```

### 수정된 코드
```c
#include <stdio.h>

int main() {
    char buffer[10];
    printf("Enter your name: ");
    fgets(buffer, sizeof(buffer), stdin);  // 안전한 입력
    printf("%s", buffer);  // 포맷 문자열 고정
    return 0;
}
```

---

C 언어에서 보안은 매우 중요한 주제입니다. 위의 가이드라인을 따라 안전한 코드를 작성하고, 정적 분석 도구와 메모리 보호 기술을 활용하여 취약점을 방지하세요.

