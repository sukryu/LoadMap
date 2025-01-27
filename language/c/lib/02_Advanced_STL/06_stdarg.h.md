# <stdarg.h>: 가변 인자 처리 라이브러리

`<stdarg.h>`는 가변 인자를 사용하는 함수를 작성하기 위한 표준 라이브러리입니다. 이를 통해 함수가 고정되지 않은 개수의 인자를 처리할 수 있습니다.

---

## 1. 주요 구성 요소

### 1.1 데이터 타입과 매크로

#### 주요 매크로
| 매크로         | 설명                                                   |
|----------------|------------------------------------------------------|
| `va_list`      | 가변 인자를 저장하는 데이터 타입                     |
| `va_start`     | 가변 인자의 처리를 시작                              |
| `va_arg`       | 가변 인자의 값을 가져옴                              |
| `va_end`       | 가변 인자 처리를 종료                                |

---

## 2. 사용법

### 가변 인자를 사용하는 함수 작성

#### 단계별 설명
1. `va_list` 타입의 변수를 선언하여 가변 인자를 관리합니다.
2. `va_start`를 호출하여 가변 인자 처리를 시작합니다.
3. `va_arg`를 사용하여 인자를 순차적으로 가져옵니다.
4. `va_end`를 호출하여 가변 인자 처리를 종료합니다.

#### 예제: 숫자의 합 계산
```c
#include <stdarg.h>
#include <stdio.h>

int sum(int count, ...) {
    va_list args;
    int total = 0;

    va_start(args, count);  // 가변 인자 처리 시작
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);  // 정수형 인자 가져오기
    }
    va_end(args);  // 가변 인자 처리 종료

    return total;
}

int main() {
    printf("합계: %d\n", sum(3, 10, 20, 30));
    printf("합계: %d\n", sum(5, 1, 2, 3, 4, 5));
    return 0;
}
```

**출력:**
```
합계: 60
합계: 15
```

---

### 2.1 다양한 데이터 타입 처리
`va_arg`를 사용할 때 각 인자의 데이터 타입을 명시해야 합니다.

#### 예제: 다양한 데이터 타입 처리
```c
#include <stdarg.h>
#include <stdio.h>

void print_values(const char *format, ...) {
    va_list args;
    va_start(args, format);

    for (const char *ptr = format; *ptr != '\0'; ptr++) {
        if (*ptr == 'd') {
            int i = va_arg(args, int);
            printf("정수: %d\n", i);
        } else if (*ptr == 'f') {
            double d = va_arg(args, double);
            printf("실수: %.2f\n", d);
        } else if (*ptr == 'c') {
            char c = (char)va_arg(args, int);
            printf("문자: %c\n", c);
        }
    }

    va_end(args);
}

int main() {
    print_values("d f c", 42, 3.14, 'A');
    return 0;
}
```

**출력:**
```
정수: 42
실수: 3.14
문자: A
```

---

## 3. 실습 예제

### 평균 계산기
**코드:**
```c
#include <stdarg.h>
#include <stdio.h>

double average(int count, ...) {
    va_list args;
    double sum = 0.0;

    va_start(args, count);
    for (int i = 0; i < count; i++) {
        sum += va_arg(args, double);
    }
    va_end(args);

    return count > 0 ? sum / count : 0;
}

int main() {
    printf("평균: %.2f\n", average(4, 10.0, 20.0, 30.0, 40.0));
    printf("평균: %.2f\n", average(3, 5.5, 6.5, 7.5));
    return 0;
}
```

**출력:**
```
평균: 25.00
평균: 6.50
```

---

### 문자열 출력 함수
**코드:**
```c
#include <stdarg.h>
#include <stdio.h>

void print_strings(int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        const char *str = va_arg(args, const char *);
        printf("문자열 %d: %s\n", i + 1, str);
    }

    va_end(args);
}

int main() {
    print_strings(3, "Hello", "World", "C Language");
    return 0;
}
```

**출력:**
```
문자열 1: Hello
문자열 2: World
문자열 3: C Language
```

---

## 4. 사용 시 주의사항

1. **데이터 타입 일치**: `va_arg`에 지정한 데이터 타입과 실제 인자의 타입이 일치해야 합니다. 잘못된 타입을 지정하면 예기치 않은 동작이 발생할 수 있습니다.
2. **매크로 순서 준수**: `va_start`로 시작하고 `va_end`로 종료해야 합니다.
3. **인자 개수 명시**: 함수의 첫 번째 매개변수로 인자의 개수를 전달하거나, 포맷 문자열 등을 사용해 인자의 개수를 명확히 해야 합니다.

---

`<stdarg.h>`는 가변 개수의 인자를 처리하는 강력한 도구를 제공합니다. 이를 사용하여 유연한 함수를 작성하고 다양한 시나리오에 적용할 수 있습니다.

