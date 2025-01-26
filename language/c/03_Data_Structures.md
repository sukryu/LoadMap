# C 언어 Data Structures

## 배열 (Arrays)

### 1. 배열의 개념
배열은 동일한 데이터 타입의 연속된 메모리 공간에 데이터를 저장하는 자료구조입니다.

#### 배열 선언과 초기화
```c
int numbers[5];  // 크기가 5인 정수 배열 선언
int values[] = {1, 2, 3, 4, 5};  // 초기화와 함께 선언
```

#### 배열 접근
```c
int numbers[5] = {10, 20, 30, 40, 50};
printf("첫 번째 값: %d\n", numbers[0]);
numbers[2] = 35;  // 배열의 세 번째 값을 변경
```

### 2. 다차원 배열
C 언어는 다차원 배열을 지원합니다.

#### 2차원 배열 선언과 초기화
```c
int matrix[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
```

#### 2차원 배열 접근
```c
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        printf("%d ", matrix[i][j]);
    }
    printf("\n");
}
```

### 3. 배열과 함수
배열을 함수에 전달할 때는 포인터를 사용합니다.

#### 배열 전달
```c
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    printArray(numbers, 5);
    return 0;
}
```

---

## 문자열 (Strings)

### 1. 문자열의 개념
C 언어에서 문자열은 널 종료 문자(`\0`)로 끝나는 문자 배열입니다.

#### 문자열 선언과 초기화
```c
char str1[] = "Hello";  // 자동으로 널 문자 추가
char str2[6] = {'H', 'e', 'l', 'l', 'o', '\0'};  // 명시적 널 문자
```

#### 문자열 출력
```c
char greeting[] = "Hello, World!";
printf("%s\n", greeting);
```

### 2. 문자열 함수
C 언어는 `<string.h>`를 통해 다양한 문자열 처리를 지원합니다.

#### 주요 함수
- `strlen()`: 문자열 길이 반환
- `strcpy()`: 문자열 복사
- `strcat()`: 문자열 연결
- `strcmp()`: 문자열 비교

#### 사용 예
```c
#include <stdio.h>
#include <string.h>

int main() {
    char str1[20] = "Hello";
    char str2[] = "World";

    printf("Length: %lu\n", strlen(str1));
    strcat(str1, " ");
    strcat(str1, str2);
    printf("Concatenated: %s\n", str1);

    return 0;
}
```

### 3. 문자열 입력
```c
char name[50];
printf("Enter your name: ");
scanf("%s", name);
printf("Hello, %s!\n", name);
```

---

## 포인터 (Pointers)

### 1. 포인터의 개념
포인터는 메모리 주소를 저장하는 변수입니다. 이를 통해 메모리를 직접 다룰 수 있습니다.

#### 포인터 선언과 사용
```c
int num = 10;
int *ptr = &num;  // num의 주소를 ptr에 저장
printf("num의 값: %d\n", *ptr);  // 역참조를 통해 값에 접근
```

### 2. 포인터와 배열
배열 이름은 배열의 첫 번째 요소를 가리키는 포인터로 사용됩니다.

#### 배열과 포인터
```c
int arr[] = {10, 20, 30};
int *ptr = arr;
printf("%d\n", *ptr);  // 10
printf("%d\n", *(ptr + 1));  // 20
```

### 3. 다중 포인터
포인터의 포인터를 사용할 수 있습니다.
```c
int num = 10;
int *ptr = &num;
int **pptr = &ptr;
printf("num: %d\n", **pptr);
```

---

## 구조체 (Structures)

### 1. 구조체의 개념
구조체는 서로 다른 데이터 타입을 그룹화하여 하나의 단위로 묶는 사용자 정의 데이터 타입입니다.

#### 구조체 선언과 사용
```c
struct Person {
    char name[50];
    int age;
    float height;
};

int main() {
    struct Person person = {"John", 30, 175.5};
    printf("Name: %s, Age: %d, Height: %.1f\n", person.name, person.age, person.height);
    return 0;
}
```

### 2. 구조체 배열
```c
struct Person people[2] = {
    {"Alice", 25, 160.0},
    {"Bob", 28, 170.5}
};

for (int i = 0; i < 2; i++) {
    printf("%s: %d years old\n", people[i].name, people[i].age);
}
```

### 3. 구조체 포인터
```c
struct Person person = {"Jane", 22, 165.0};
struct Person *ptr = &person;
printf("Name: %s\n", ptr->name);
```

---

## 공용체 (Unions)

### 1. 공용체의 개념
공용체는 모든 멤버가 동일한 메모리 공간을 공유하는 데이터 타입입니다.

#### 공용체 선언과 사용
```c
union Data {
    int i;
    float f;
    char str[20];
};

int main() {
    union Data data;
data.i = 10;
printf("Integer: %d\n", data.i);
data.f = 3.14;
printf("Float: %.2f\n", data.f);
return 0;
}
```

---

## 열거형 (Enumerations)

### 1. 열거형의 개념
열거형은 관련된 상수들의 집합을 정의하는 데 사용됩니다.

#### 열거형 선언과 사용
```c
enum Days {SUN, MON, TUE, WED, THU, FRI, SAT};

enum Days today = WED;
printf("Today is day %d\n", today);
```

---

C 언어의 주요 데이터 구조를 소개했습니다. 이러한 구조는 효율적이고 안전한 데이터 관리를 가능하게 합니다.

