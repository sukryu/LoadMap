# Input and Output in C

C 언어에서는 입력과 출력을 처리하기 위해 표준 라이브러리 함수를 제공합니다. 입력/출력은 사용자와 프로그램 간의 상호작용을 가능하게 하며, 파일 작업을 포함한 데이터 처리에도 활용됩니다. 이 문서에서는 C의 입력/출력 개념과 사용법을 초보자도 이해할 수 있도록 설명합니다.

---

## 1. 표준 입력과 출력

C 언어에서는 `stdio.h` 헤더 파일을 통해 표준 입력/출력 함수를 사용할 수 있습니다.

### 1.1 출력: `printf`
`printf` 함수는 데이터를 형식화하여 출력할 때 사용됩니다.

#### 사용법
```c
#include <stdio.h>

int main() {
    int number = 10;
    float pi = 3.14;
    char grade = 'A';

    printf("정수: %d\n", number);
    printf("실수: %.2f\n", pi);
    printf("문자: %c\n", grade);

    return 0;
}
```

#### 주요 형식 지정자
- `%d`: 정수
- `%f`: 부동소수점
- `%c`: 문자
- `%s`: 문자열
- `%p`: 포인터 (메모리 주소)
- `%%`: `%` 문자 출력

### 1.2 입력: `scanf`
`scanf` 함수는 사용자로부터 데이터를 입력받을 때 사용됩니다.

#### 사용법
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
1. 변수의 주소를 전달해야 합니다 (예: `&age`).
2. 입력 형식이 올바르지 않을 경우 예기치 않은 동작이 발생할 수 있습니다.
3. 문자열 입력 시 공백을 포함하려면 `fgets`를 사용하는 것이 좋습니다.

---

## 2. 파일 입출력

파일 입출력은 프로그램이 데이터를 파일에 저장하거나 파일에서 데이터를 읽을 수 있도록 합니다. C 언어는 `fopen`, `fclose`, `fread`, `fwrite` 등의 함수를 제공합니다.

### 2.1 파일 열기: `fopen`
`fopen` 함수는 파일을 열고 파일 포인터를 반환합니다.

#### 파일 모드
- `"r"`: 읽기 전용
- `"w"`: 쓰기 전용 (파일 내용이 삭제됨)
- `"a"`: 추가 모드 (파일 끝에 데이터를 추가)
- `"r+"`: 읽기와 쓰기
- `"w+"`: 읽기와 쓰기 (파일 내용이 삭제됨)

#### 사용법
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("example.txt", "w");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    fprintf(file, "Hello, File!\n");  // 파일에 데이터 쓰기
    fclose(file);  // 파일 닫기

    return 0;
}
```

### 2.2 파일 읽기: `fscanf`와 `fgets`
- `fscanf`: 파일에서 형식화된 데이터를 읽습니다.
- `fgets`: 파일에서 한 줄씩 데이터를 읽습니다.

#### 예제
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("읽은 내용: %s", line);
    }

    fclose(file);
    return 0;
}
```

### 2.3 이진 파일 처리: `fread`와 `fwrite`
이진 파일은 텍스트 파일과 달리 데이터가 이진 형식으로 저장됩니다. `fread`와 `fwrite`를 사용하여 이진 데이터를 읽고 쓸 수 있습니다.

#### 예제
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("data.bin", "wb");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    int numbers[] = {1, 2, 3, 4, 5};
    fwrite(numbers, sizeof(int), 5, file);  // 배열 데이터를 파일에 쓰기
    fclose(file);

    file = fopen("data.bin", "rb");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    int buffer[5];
    fread(buffer, sizeof(int), 5, file);  // 파일에서 데이터 읽기
    for (int i = 0; i < 5; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    fclose(file);
    return 0;
}
```

---

## 3. 고급 입력/출력 기능

### 3.1 `sprintf`와 `sscanf`
- `sprintf`: 데이터를 문자열로 저장
- `sscanf`: 문자열에서 데이터를 읽기

#### 예제
```c
#include <stdio.h>

int main() {
    char buffer[100];
    int num = 42;
    float pi = 3.14;

    sprintf(buffer, "숫자: %d, 원주율: %.2f", num, pi);
    printf("저장된 문자열: %s\n", buffer);

    int extracted_num;
    float extracted_pi;
    sscanf(buffer, "숫자: %d, 원주율: %f", &extracted_num, &extracted_pi);

    printf("추출된 숫자: %d, 추출된 원주율: %.2f\n", extracted_num, extracted_pi);

    return 0;
}
```

### 3.2 에러 처리
- 파일 작업 중 오류를 확인하려면 `ferror`와 `feof`를 사용할 수 있습니다.

#### 예제
```c
if (ferror(file)) {
    printf("파일 읽기 중 오류 발생\n");
}
if (feof(file)) {
    printf("파일 끝에 도달\n");
}
```

---

이 문서는 C 언어의 기본 입력/출력 함수와 파일 작업을 초보자가 이해하기 쉽게 설명했습니다. 이 기능들을 활용하면 프로그램과 사용자, 또는 외부 데이터 간의 상호작용을 효율적으로 처리할 수 있습니다.

