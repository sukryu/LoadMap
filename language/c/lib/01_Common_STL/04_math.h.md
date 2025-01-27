# <math.h>: 수학 함수 라이브러리

`<math.h>`는 C 언어에서 수학 계산을 수행하기 위한 표준 라이브러리입니다. 삼각 함수, 거듭제곱, 로그, 반올림 등 다양한 수학 함수를 제공합니다.

---

## 1. 주요 함수

### 1.1 삼각 함수

#### `sin`, `cos`, `tan`: 삼각 함수
이 함수들은 각각 사인, 코사인, 탄젠트 값을 반환합니다. 입력은 라디안 단위입니다.

**사용법:**
```c
#include <math.h>
#include <stdio.h>

int main() {
    double angle = M_PI / 4;  // 45도
    printf("sin(45도): %.2f\n", sin(angle));
    printf("cos(45도): %.2f\n", cos(angle));
    printf("tan(45도): %.2f\n", tan(angle));
    return 0;
}
```

**출력:**
```
sin(45도): 0.71
cos(45도): 0.71
tan(45도): 1.00
```

#### `asin`, `acos`, `atan`: 역삼각 함수
역삼각 함수는 사인, 코사인, 탄젠트 값으로부터 각도를 반환합니다.

**사용법:**
```c
#include <math.h>
#include <stdio.h>

int main() {
    double value = 0.5;
    printf("asin(0.5): %.2f 라디안\n", asin(value));
    printf("acos(0.5): %.2f 라디안\n", acos(value));
    printf("atan(1.0): %.2f 라디안\n", atan(1.0));
    return 0;
}
```

---

### 1.2 거듭제곱과 제곱근

#### `pow`: 거듭제곱 계산
`pow` 함수는 `x`의 `y` 제곱을 반환합니다.

**사용법:**
```c
#include <math.h>
#include <stdio.h>

int main() {
    printf("2^3: %.2f\n", pow(2, 3));
    return 0;
}
```

#### `sqrt`: 제곱근 계산
`sqrt`는 입력값의 제곱근을 반환합니다.

**사용법:**
```c
printf("sqrt(16): %.2f\n", sqrt(16));
```

---

### 1.3 로그 함수

#### `log`: 자연 로그
`log` 함수는 자연 로그(밑이 e)를 계산합니다.

**사용법:**
```c
#include <math.h>
#include <stdio.h>

int main() {
    printf("ln(10): %.2f\n", log(10));
    return 0;
}
```

#### `log10`: 상용 로그
`log10`은 밑이 10인 로그를 계산합니다.

**사용법:**
```c
printf("log10(100): %.2f\n", log10(100));
```

---

### 1.4 반올림 함수

#### `ceil`: 올림
`ceil`은 입력값을 올림한 가장 작은 정수를 반환합니다.

**사용법:**
```c
#include <math.h>
#include <stdio.h>

int main() {
    printf("ceil(2.3): %.2f\n", ceil(2.3));
    return 0;
}
```

#### `floor`: 내림
`floor`는 입력값을 내림한 가장 큰 정수를 반환합니다.

**사용법:**
```c
printf("floor(2.7): %.2f\n", floor(2.7));
```

#### `round`: 반올림
`round`는 입력값을 반올림한 정수를 반환합니다.

**사용법:**
```c
printf("round(2.5): %.2f\n", round(2.5));
```

---

### 1.5 기타 수학 함수

#### `fabs`: 절댓값
`fabs`는 실수의 절댓값을 반환합니다.

**사용법:**
```c
#include <math.h>
#include <stdio.h>

int main() {
    printf("fabs(-3.14): %.2f\n", fabs(-3.14));
    return 0;
}
```

#### `fmod`: 나머지 계산
`fmod`는 두 실수의 나머지를 반환합니다.

**사용법:**
```c
printf("fmod(5.5, 2): %.2f\n", fmod(5.5, 2));
```

---

## 2. 실습 예제

### 삼각 함수와 거듭제곱을 활용한 계산기
**코드:**
```c
#include <stdio.h>
#include <math.h>

int main() {
    double angle, base, exponent;

    printf("각도를 라디안 단위로 입력하세요: ");
    scanf("%lf", &angle);
    printf("사인: %.2f, 코사인: %.2f, 탄젠트: %.2f\n", sin(angle), cos(angle), tan(angle));

    printf("밑(base)과 지수(exponent)를 입력하세요: ");
    scanf("%lf %lf", &base, &exponent);
    printf("%.2f^%.2f = %.2f\n", base, exponent, pow(base, exponent));

    return 0;
}
```

**출력:**
```
각도를 라디안 단위로 입력하세요: 1.57
사인: 1.00, 코사인: 0.00, 탄젠트: 16331239353195370.00
밑(base)과 지수(exponent)를 입력하세요: 2 3
2.00^3.00 = 8.00
```

---

`<math.h>`는 수학 계산을 수행하는 데 필수적인 라이브러리로, 삼각 함수, 로그, 거듭제곱 등 다양한 기능을 제공합니다. 이를 활용하면 복잡한 계산 작업도 효율적으로 처리할 수 있습니다.

