# <stdio.h>: 표준 입출력 라이브러리

`<stdio.h>`는 C 언어에서 표준 입출력 함수를 제공하는 헤더 파일로, 파일 입출력, 화면 출력, 키보드 입력과 같은 작업을 수행하는 데 필수적입니다. 이 라이브러리는 모든 C 프로그램에서 가장 많이 사용됩니다.

---

## 1. 주요 함수

### 1.1 표준 출력 함수

#### `printf`: 서식을 지정하여 출력
`printf`는 데이터를 화면에 출력할 때 사용됩니다.

**사용법:**
```c
#include <stdio.h>

int main() {
    int num = 42;
    float pi = 3.14;
    printf("정수: %d, 실수: %.2f\n", num, pi);
    return 0;
}
```

**출력:**
```
정수: 42, 실수: 3.14
```

**주요 포맷 지정자:**
| 포맷 지정자 | 설명               |
|-------------|--------------------|
| `%d`        | 정수형 출력        |
| `%f`        | 실수형 출력        |
| `%c`        | 문자형 출력        |
| `%s`        | 문자열 출력        |
| `%p`        | 포인터 주소 출력   |

#### `puts`: 문자열 출력
`puts`는 문자열을 출력하고 자동으로 개행(`\n`)합니다.

**사용법:**
```c
#include <stdio.h>

int main() {
    puts("Hello, World!");
    return 0;
}
```

**출력:**
```
Hello, World!
```

---

### 1.2 표준 입력 함수

#### `scanf`: 서식을 지정하여 입력
`scanf`는 사용자로부터 입력을 받을 때 사용됩니다.

**사용법:**
```c
#include <stdio.h>

int main() {
    int age;
    printf("나이를 입력하세요: ");
    scanf("%d", &age);
    printf("입력된 나이: %d\n", age);
    return 0;
}
```

**입력/출력:**
```
나이를 입력하세요: 25
입력된 나이: 25
```

**주의사항:**
- 입력받을 변수의 주소를 지정해야 합니다 (`&`).
- 포맷 지정자가 입력값과 일치하지 않으면 예상치 못한 동작이 발생할 수 있습니다.

#### `gets`: 문자열 입력 (**사용 권장하지 않음**)
`gets`는 개행 문자를 기준으로 문자열을 입력받습니다. 그러나 버퍼 오버플로우 위험이 있어 최신 C 표준에서는 제거되었습니다. 대신 `fgets`를 사용하세요.

---

### 1.3 파일 입출력 함수

#### `fopen`: 파일 열기
`fopen`은 파일을 열고 파일 포인터를 반환합니다.

**사용법:**
```c
FILE *file = fopen("data.txt", "r");
if (file == NULL) {
    printf("파일을 열 수 없습니다.\n");
    return 1;
}
```

**파일 모드:**
| 모드  | 설명                            |
|-------|---------------------------------|
| `r`   | 읽기 모드 (파일이 존재해야 함)  |
| `w`   | 쓰기 모드 (파일이 없으면 생성)  |
| `a`   | 추가 모드                       |
| `r+`  | 읽기/쓰기 모드                  |
| `w+`  | 읽기/쓰기 (파일 내용 초기화)    |
| `a+`  | 읽기/쓰기 (파일 끝에 추가)      |

#### `fclose`: 파일 닫기
`fclose`는 열린 파일을 닫아 시스템 자원을 반환합니다.

```c
fclose(file);
```

#### `fprintf`와 `fscanf`: 파일에 쓰기와 읽기

**`fprintf`: 파일에 서식을 지정하여 쓰기**
```c
FILE *file = fopen("output.txt", "w");
if (file) {
    fprintf(file, "이름: %s, 나이: %d\n", "Alice", 30);
    fclose(file);
}
```

**`fscanf`: 파일에서 서식을 지정하여 읽기**
```c
FILE *file = fopen("input.txt", "r");
if (file) {
    char name[50];
    int age;
    fscanf(file, "%s %d", name, &age);
    printf("이름: %s, 나이: %d\n", name, age);
    fclose(file);
}
```

#### `fgets`와 `fputs`: 문자열 읽기와 쓰기
**`fgets`: 파일에서 문자열 읽기**
```c
char buffer[100];
if (fgets(buffer, sizeof(buffer), file)) {
    printf("읽은 문자열: %s\n", buffer);
}
```

**`fputs`: 파일에 문자열 쓰기**
```c
fputs("Hello, File!\n", file);
```

---

## 2. 실습 예제

### 간단한 텍스트 파일 복사 프로그램
**코드:**
```c
#include <stdio.h>

int main() {
    FILE *source, *dest;
    char buffer[1024];

    source = fopen("source.txt", "r");
    if (source == NULL) {
        perror("원본 파일 열기 실패");
        return 1;
    }

    dest = fopen("dest.txt", "w");
    if (dest == NULL) {
        perror("대상 파일 열기 실패");
        fclose(source);
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), source)) {
        fputs(buffer, dest);
    }

    printf("파일 복사가 완료되었습니다.\n");

    fclose(source);
    fclose(dest);
    return 0;
}
```

**설명:**
1. 원본 파일(`source.txt`)을 읽기 모드로 열기.
2. 대상 파일(`dest.txt`)을 쓰기 모드로 열기.
3. 원본 파일에서 한 줄씩 읽어 대상 파일에 작성.
4. 모든 파일 닫기.

---

`<stdio.h>` 라이브러리는 파일 입출력과 사용자 입력/출력을 처리하는 데 필수적입니다. 이 장에서 다룬 내용을 숙지하면 다양한 프로그램에서 활용할 수 있습니다.

