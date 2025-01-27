# 08. Real-World Applications

## 1. 운영 체제 개발

### C 언어와 운영 체제
C 언어는 운영 체제 개발에 최적화된 언어로, 하드웨어와 가까운 수준에서 작업할 수 있으면서도 고수준 언어의 기능을 제공합니다. 대표적인 운영 체제로는 **UNIX**와 **Linux**가 있습니다.

#### 특징
- **저수준 접근**: 메모리와 하드웨어 자원을 직접 관리.
- **이식성**: 다양한 아키텍처에서 동작 가능한 코드 작성.

#### 간단한 시스템 호출 예제
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    char buffer[] = "Hello, Kernel!\n";
    write(STDOUT_FILENO, buffer, sizeof(buffer));  // 시스템 호출로 출력
    return 0;
}
```

---

## 2. 임베디드 시스템

### 임베디드 시스템이란?
임베디드 시스템은 특정 기능을 수행하기 위해 설계된 컴퓨터 시스템입니다. C 언어는 임베디드 시스템에서 널리 사용됩니다.

#### 장점
- 메모리와 CPU 자원을 효율적으로 사용.
- 하드웨어 레지스터와 직접 통신 가능.

#### GPIO 제어 예제
```c
#include <stdint.h>

#define GPIO_BASE 0x40020C00
#define GPIO_MODER (*(volatile uint32_t *)(GPIO_BASE))
#define GPIO_ODR (*(volatile uint32_t *)(GPIO_BASE + 0x14))

int main() {
    GPIO_MODER |= (1 << 10);  // 핀 5를 출력 모드로 설정
    GPIO_ODR |= (1 << 5);     // 핀 5 HIGH 설정
    return 0;
}
```

---

## 3. 네트워킹과 소켓 프로그래밍

### 소켓 프로그래밍이란?
소켓 프로그래밍은 네트워크 상에서 데이터 교환을 가능하게 하는 기술입니다. C 언어는 TCP/IP 프로토콜 기반의 소켓 프로그래밍을 지원합니다.

#### 간단한 서버 예제
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    int client_fd = accept(server_fd, NULL, NULL);
    char *message = "Hello, Client!\n";
    send(client_fd, message, strlen(message), 0);

    close(client_fd);
    close(server_fd);
    return 0;
}
```

---

## 4. 데이터베이스와 시스템 관리

### 데이터 파일 처리
C 언어를 사용하면 텍스트와 바이너리 데이터를 효과적으로 처리할 수 있습니다. 이를 통해 간단한 데이터베이스 시스템을 구축할 수 있습니다.

#### 레코드 저장 예제
```c
#include <stdio.h>
#include <string.h>

struct Record {
    int id;
    char name[50];
};

int main() {
    FILE *file = fopen("records.dat", "wb");

    struct Record rec1 = {1, "Alice"};
    struct Record rec2 = {2, "Bob"};

    fwrite(&rec1, sizeof(struct Record), 1, file);
    fwrite(&rec2, sizeof(struct Record), 1, file);

    fclose(file);
    return 0;
}
```

---

## 5. 고성능 컴퓨팅과 과학 계산

### 행렬 연산 예제
고성능 컴퓨팅 환경에서 행렬 연산은 매우 중요한 작업입니다. C는 효율적인 메모리 관리와 연산 성능을 제공합니다.

#### 행렬 곱셈
```c
#include <stdio.h>
#define N 3

void multiplyMatrices(int mat1[N][N], int mat2[N][N], int result[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

int main() {
    int mat1[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int mat2[N][N] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    int result[N][N];

    multiplyMatrices(mat1, mat2, result);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    return 0;
}
```

---

## 6. 게임 개발

### 게임 루프 구현
C 언어는 경량 게임 엔진이나 시뮬레이션에 적합합니다.

#### 간단한 텍스트 기반 게임 루프
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int number, guess;
    srand(time(0));
    number = rand() % 100 + 1;  // 1에서 100 사이의 난수 생성

    printf("숫자를 맞춰보세요 (1-100):\n");

    do {
        printf("추측: ");
        scanf("%d", &guess);
        if (guess > number) {
            printf("너무 높습니다!\n");
        } else if (guess < number) {
            printf("너무 낮습니다!\n");
        } else {
            printf("정답입니다!\n");
        }
    } while (guess != number);

    return 0;
}
```

---

## 7. 간단한 프로젝트: 파일 암호화 도구

### 프로그램 설명
사용자로부터 입력받은 텍스트 파일을 간단히 암호화/복호화하는 프로그램입니다.

#### 프로그램
```c
#include <stdio.h>
#include <stdlib.h>

void encryptDecrypt(char *input, char *output, char key) {
    FILE *inFile = fopen(input, "r");
    FILE *outFile = fopen(output, "w");

    if (inFile == NULL || outFile == NULL) {
        printf("파일을 열 수 없습니다.\n");
        exit(1);
    }

    char ch;
    while ((ch = fgetc(inFile)) != EOF) {
        fputc(ch ^ key, outFile);  // XOR 연산으로 암호화/복호화
    }

    fclose(inFile);
    fclose(outFile);
}

int main() {
    char input[100], output[100];
    char key;

    printf("입력 파일 이름: ");
    scanf("%s", input);
    printf("출력 파일 이름: ");
    scanf("%s", output);
    printf("암호화 키 (한 문자): ");
    scanf(" %c", &key);

    encryptDecrypt(input, output, key);
    printf("작업이 완료되었습니다!\n");

    return 0;
}
```

---

C 언어는 다양한 분야에서 실용적인 응용을 위한 강력한 도구입니다. 이를 활용하면 운영 체제, 네트워킹, 임베디드 시스템, 게임 개발 등에서 혁신적인 솔루션을 구현할 수 있습니다.

