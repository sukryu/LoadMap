# 06. Input and Output

## 1. 표준 입출력 (Standard Input and Output)
C 언어에서는 표준 입출력 함수를 통해 사용자와 상호작용할 수 있습니다. 입력과 출력은 `<stdio.h>` 라이브러리를 통해 제공됩니다.

### 표준 출력 (`printf`)
- 데이터를 화면에 출력하는 함수입니다.

#### 기본 사용법
```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

#### 포맷 지정자
| 포맷 지정자 | 설명               |
|-------------|--------------------|
| `%d`        | 정수형 출력        |
| `%f`        | 실수형 출력        |
| `%c`        | 문자형 출력        |
| `%s`        | 문자열 출력        |
| `%p`        | 포인터 주소 출력   |

#### 예제: 포맷 지정자 활용
```c
int num = 42;
float pi = 3.14;
char ch = 'A';
char str[] = "Hello";

printf("정수: %d\n", num);
printf("실수: %.2f\n", pi);
printf("문자: %c\n", ch);
printf("문자열: %s\n", str);
```

### 표준 입력 (`scanf`)
- 데이터를 사용자로부터 입력받는 함수입니다.

#### 기본 사용법
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

#### 주의사항
- 입력받을 변수의 주소를 지정해야 합니다(`&` 사용).
- 입력값의 형식이 포맷 지정자와 맞지 않으면 오류가 발생할 수 있습니다.

---

## 2. 파일 입출력 (File Input and Output)
C 언어에서는 파일 입출력을 통해 데이터를 읽거나 저장할 수 있습니다. 파일 처리는 `<stdio.h>` 라이브러리를 사용합니다.

### 파일 열기 (`fopen`)
- 파일을 열고, 파일 포인터를 반환합니다.

#### 기본 사용법
```c
FILE *file = fopen("data.txt", "r");  // 읽기 모드로 파일 열기
if (file == NULL) {
    printf("파일을 열 수 없습니다.\n");
    return 1;
}
```

#### 파일 모드
| 모드  | 설명                           |
|-------|--------------------------------|
| `r`   | 읽기 모드 (파일이 존재해야 함) |
| `w`   | 쓰기 모드 (파일이 없으면 생성) |
| `a`   | 추가 모드                      |
| `r+`  | 읽기/쓰기 모드                 |
| `w+`  | 읽기/쓰기 (파일 초기화)        |
| `a+`  | 읽기/쓰기 (파일 끝에 추가)     |

### 파일 읽기 (`fgetc`, `fgets`)
- 문자 또는 문자열 단위로 파일을 읽습니다.

#### 예제: 문자 읽기
```c
char ch;
while ((ch = fgetc(file)) != EOF) {
    putchar(ch);
}
```

#### 예제: 문자열 읽기
```c
char buffer[100];
while (fgets(buffer, sizeof(buffer), file) != NULL) {
    printf("%s", buffer);
}
```

### 파일 쓰기 (`fputc`, `fputs`, `fprintf`)
- 파일에 데이터를 저장합니다.

#### 예제: 문자열 쓰기
```c
FILE *file = fopen("output.txt", "w");
fputs("Hello, File!\n", file);
fclose(file);
```

#### 예제: 형식화된 쓰기
```c
FILE *file = fopen("data.txt", "w");
int num = 42;
float pi = 3.14;

fprintf(file, "정수: %d\n실수: %.2f\n", num, pi);
fclose(file);
```

### 파일 닫기 (`fclose`)
- 열려 있는 파일을 닫아 시스템 자원을 반환합니다.

```c
fclose(file);
```

---

## 3. 고급 파일 입출력

### 파일 위치 제어 (`fseek`, `ftell`, `rewind`)
- 파일 내에서 읽기/쓰기 위치를 제어할 수 있습니다.

#### `fseek`
```c
fseek(file, 0, SEEK_END);  // 파일 끝으로 이동
```

#### `ftell`
```c
long position = ftell(file);  // 현재 위치 반환
printf("현재 위치: %ld\n", position);
```

#### `rewind`
```c
rewind(file);  // 파일 위치를 처음으로 초기화
```

### 이진 파일 입출력 (`fread`, `fwrite`)
- 바이너리 데이터를 파일에서 읽거나 파일에 저장합니다.

#### 예제: 구조체 저장
```c
struct Data {
    int id;
    char name[50];
};

struct Data d = {1, "Alice"};
FILE *file = fopen("data.bin", "wb");

fwrite(&d, sizeof(struct Data), 1, file);
fclose(file);
```

#### 예제: 구조체 읽기
```c
struct Data d;
FILE *file = fopen("data.bin", "rb");

fread(&d, sizeof(struct Data), 1, file);
printf("ID: %d, Name: %s\n", d.id, d.name);
fclose(file);
```

---

## 4. 문자열 입출력

### 문자 단위 입출력 (`getchar`, `putchar`)
#### 예제
```c
#include <stdio.h>

int main() {
    char ch;
    printf("문자를 입력하세요: ");
    ch = getchar();
    printf("입력된 문자: ");
    putchar(ch);
    putchar('\n');
    return 0;
}
```

### 문자열 단위 입출력 (`gets`, `puts`)
#### 예제
```c
#include <stdio.h>

int main() {
    char str[100];
    printf("문자열을 입력하세요: ");
    gets(str);  // 문자열 입력
    printf("입력된 문자열: ");
    puts(str);  // 문자열 출력
    return 0;
}
```

> **Note:** `gets`는 보안 문제가 있으므로 최신 표준에서는 사용을 권장하지 않습니다. 대신 `fgets`를 사용하세요.

---

## 5. 간단한 예제: 텍스트 파일 복사

### 프로그램
```c
#include <stdio.h>

int main() {
    FILE *source, *destination;
    char buffer[100];

    source = fopen("source.txt", "r");
    if (source == NULL) {
        printf("원본 파일을 열 수 없습니다.\n");
        return 1;
    }

    destination = fopen("destination.txt", "w");
    if (destination == NULL) {
        printf("대상 파일을 열 수 없습니다.\n");
        fclose(source);
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), source) != NULL) {
        fputs(buffer, destination);
    }

    printf("파일 복사가 완료되었습니다.\n");

    fclose(source);
    fclose(destination);
    return 0;
}
```

### 프로그램 설명
1. 원본 파일(`source.txt`)을 읽기 모드로 엽니다.
2. 대상 파일(`destination.txt`)을 쓰기 모드로 엽니다.
3. 원본 파일의 내용을 한 줄씩 읽어 대상 파일에 복사합니다.
4. 모든 파일을 닫아 자원을 해제합니다.

---

이 장에서는 C 언어의 입력 및 출력 기능, 특히 표준 입출력과 파일 입출력에 대해 다루었습니다. 이를 활용하면 사용자와의 상호작용 및 데이터 관리를 효과적으로 구현할 수 있습니다.

