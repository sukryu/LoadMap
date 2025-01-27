# <assert.h>: 조건 검증 라이브러리

`<assert.h>`는 프로그램의 실행 중 특정 조건을 검증하고, 조건이 만족되지 않을 경우 디버깅 정보를 제공하는 데 사용되는 표준 라이브러리입니다. 주로 디버깅 및 테스트 단계에서 코드의 논리적 오류를 식별하기 위해 사용됩니다.

---

## 1. 주요 함수

### `assert`: 조건 검증

#### 개요
`assert`는 조건이 참인지 확인합니다. 조건이 거짓일 경우, 프로그램 실행을 중단하고 오류 메시지를 출력합니다. 

#### 사용법
```c
#include <assert.h>
#include <stdio.h>

int main() {
    int x = 5;
    assert(x > 0);  // 조건이 참이므로 아무런 동작도 하지 않음

    x = -1;
    assert(x > 0);  // 조건이 거짓이므로 프로그램 종료

    printf("이 메시지는 출력되지 않습니다.\n");
    return 0;
}
```

#### 출력 예제 (조건 실패 시):
```
Assertion failed: x > 0, file program.c, line 9
```

#### 특징
1. 조건이 거짓일 경우:
   - **오류 메시지** 출력.
   - 실행 중단.
2. 조건이 참일 경우:
   - 아무 작업도 수행하지 않음.

---

## 2. `NDEBUG` 매크로

### 개요
`assert`는 디버깅 목적으로 사용되며, 프로그램을 배포할 때는 비활성화하는 것이 일반적입니다. `NDEBUG` 매크로를 정의하면 모든 `assert` 호출이 무시됩니다.

#### 사용법
```c
#include <assert.h>
#include <stdio.h>

#define NDEBUG  // assert 비활성화

int main() {
    int x = -1;
    assert(x > 0);  // 무시됨

    printf("프로그램이 종료되지 않았습니다.\n");
    return 0;
}
```

#### 출력 (NDEBUG 활성화 시):
```
프로그램이 종료되지 않았습니다.
```

---

## 3. `assert`와 디버깅

### 디버깅 시 사용 사례

#### 배열 인덱스 유효성 검사
```c
#include <assert.h>
#include <stdio.h>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int index = 7;

    assert(index >= 0 && index < 5);  // 인덱스가 범위를 벗어나면 프로그램 종료
    printf("배열 값: %d\n", arr[index]);

    return 0;
}
```

#### 함수 입력값 확인
```c
#include <assert.h>
#include <stdio.h>

double divide(int a, int b) {
    assert(b != 0);  // 분모가 0인지 확인
    return (double)a / b;
}

int main() {
    printf("결과: %.2f\n", divide(10, 2));

    // 다음 호출은 assert 실패로 종료됨
    printf("결과: %.2f\n", divide(10, 0));

    return 0;
}
```

---

## 4. 실습 예제

### 입력 값 검증 프로그램
**코드:**
```c
#include <assert.h>
#include <stdio.h>

int get_positive_number() {
    int num;
    printf("양수를 입력하세요: ");
    scanf("%d", &num);

    assert(num > 0);  // 입력값이 양수인지 확인
    return num;
}

int main() {
    int value = get_positive_number();
    printf("입력된 값: %d\n", value);
    return 0;
}
```

**출력 (양수 입력):**
```
양수를 입력하세요: 5
입력된 값: 5
```

**출력 (양수 미입력):**
```
양수를 입력하세요: -3
Assertion failed: num > 0, file program.c, line 9
```

---

## 5. `assert` 사용 시 주의사항
1. **런타임 영향**: `assert`는 디버깅 도구로만 사용해야 하며, 배포용 코드에서는 비활성화 (`NDEBUG` 정의)하는 것이 권장됩니다.
2. **조건식 단순화**: 복잡한 조건식을 피하고 읽기 쉽게 작성하세요.
3. **안전하지 않은 코드 제거**: 실패 시 프로그램이 강제로 종료되므로 중요한 로직에 사용하지 않는 것이 좋습니다.

---

`<assert.h>`는 코드의 논리적 오류를 사전에 발견하고, 디버깅을 용이하게 하는 강력한 도구입니다. 이를 올바르게 사용하면 코드의 안정성과 유지보수성을 높일 수 있습니다.