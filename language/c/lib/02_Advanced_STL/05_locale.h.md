# <locale.h>: 지역화 설정 라이브러리

`<locale.h>`는 C 언어에서 지역화(localization)와 관련된 작업을 처리하는 표준 라이브러리입니다. 이 라이브러리는 숫자, 날짜, 시간, 문자열 등 문화권별로 다른 표현 형식을 관리하고 설정하는 데 사용됩니다.

---

## 1. 주요 내용

### 1.1 지역화 개념
- 지역화(Localization)는 특정 지역이나 문화권의 형식에 맞게 데이터를 표현하는 과정을 의미합니다.
- C 언어에서는 지역화 설정을 통해 숫자 형식, 화폐 단위, 날짜와 시간 형식을 조정할 수 있습니다.

#### 주요 지역화 카테고리
| 카테고리      | 설명                              |
|---------------|-----------------------------------|
| `LC_ALL`      | 모든 카테고리에 대한 설정 변경     |
| `LC_NUMERIC`  | 숫자 형식                         |
| `LC_TIME`     | 날짜와 시간 형식                  |
| `LC_MONETARY` | 화폐 단위                         |
| `LC_COLLATE`  | 문자열 정렬 순서                  |
| `LC_CTYPE`    | 문자 분류와 대소문자 변환 규칙     |
| `LC_MESSAGES` | 메시지 출력 형식                  |

---

### 1.2 주요 함수

#### `setlocale`: 지역화 설정
- **정의**: 현재 지역화 설정을 변경하거나 확인합니다.
- **형식**: `char *setlocale(int category, const char *locale);`

| 매개변수      | 설명                                               |
|---------------|----------------------------------------------------|
| `category`    | 변경할 지역화 카테고리 (`LC_ALL`, `LC_TIME` 등).   |
| `locale`      | 지역 코드 문자열 (예: `"en_US.UTF-8"`, `"ko_KR"`).|

**사용법:**
```c
#include <locale.h>
#include <stdio.h>

int main() {
    printf("기본 지역화: %s\n", setlocale(LC_ALL, NULL));

    setlocale(LC_ALL, "en_US.UTF-8");
    printf("변경된 지역화: %s\n", setlocale(LC_ALL, NULL));

    return 0;
}
```

**출력:**
```
기본 지역화: C
변경된 지역화: en_US.UTF-8
```

---

#### `localeconv`: 지역화 정보 가져오기
- **정의**: 현재 지역화 설정에 따른 숫자 및 화폐 형식을 반환합니다.
- **형식**: `struct lconv *localeconv(void);`

| 반환 값 | 설명                                    |
|---------|-----------------------------------------|
| `lconv` | 숫자와 화폐 형식 정보를 담은 구조체 포인터 |

#### `struct lconv` 멤버
| 멤버                | 설명                              |
|---------------------|-----------------------------------|
| `decimal_point`     | 소수점 기호                      |
| `thousands_sep`     | 천 단위 구분 기호                |
| `currency_symbol`   | 화폐 기호                        |
| `positive_sign`     | 양수 기호                        |
| `negative_sign`     | 음수 기호                        |

**사용법:**
```c
#include <locale.h>
#include <stdio.h>

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");

    struct lconv *locale_info = localeconv();
    printf("소수점 기호: %s\n", locale_info->decimal_point);
    printf("천 단위 구분 기호: %s\n", locale_info->thousands_sep);
    printf("화폐 기호: %s\n", locale_info->currency_symbol);

    return 0;
}
```

**출력:**
```
소수점 기호: .
천 단위 구분 기호: ,
화폐 기호: $
```

---

## 2. 실습 예제

### 숫자 형식 출력
**코드:**
```c
#include <locale.h>
#include <stdio.h>

int main() {
    setlocale(LC_NUMERIC, "fr_FR.UTF-8");  // 프랑스 지역 설정

    printf("숫자 형식: %'.2f\n", 1234567.89);  // 천 단위 구분
    return 0;
}
```

**출력:**
```
숫자 형식: 1 234 567,89
```

---

### 날짜 및 시간 출력
**코드:**
```c
#include <locale.h>
#include <stdio.h>
#include <time.h>

int main() {
    setlocale(LC_TIME, "ko_KR.UTF-8");  // 한국 지역 설정

    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);

    char buffer[100];
    strftime(buffer, sizeof(buffer), "%A, %d %B %Y", local_time);

    printf("현재 날짜: %s\n", buffer);
    return 0;
}
```

**출력:**
```
현재 날짜: 일요일, 01 1월 2023
```

---

### 화폐 정보 출력
**코드:**
```c
#include <locale.h>
#include <stdio.h>

int main() {
    setlocale(LC_MONETARY, "en_US.UTF-8");

    struct lconv *locale_info = localeconv();
    printf("화폐 기호: %s\n", locale_info->currency_symbol);
    printf("양수 기호: %s\n", locale_info->positive_sign);
    printf("음수 기호: %s\n", locale_info->negative_sign);

    return 0;
}
```

**출력:**
```
화폐 기호: $
양수 기호:
음수 기호: -
```

---

## 3. 사용 시 주의사항

1. **지역화 코드 확인**: 각 운영 체제에서 사용 가능한 지역화 코드는 다를 수 있습니다. 적합한 코드를 확인 후 사용하세요.
2. **표준 출력 설정**: UTF-8과 같은 지역화 문자열을 제대로 표시하려면 터미널 또는 IDE의 인코딩 설정을 조정해야 합니다.
3. **프로그램 호환성**: 지역화 설정은 프로그램 실행 중 전역적으로 영향을 미치므로 다중 스레드 환경에서는 주의해야 합니다.

---

`<locale.h>`는 지역화 작업에서 필수적인 도구를 제공하여 문화권에 맞는 데이터 형식을 처리할 수 있도록 돕습니다. 이를 통해 국제화(i18n) 요구 사항을 만족하는 프로그램을 작성할 수 있습니다.

