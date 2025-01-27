# 04. Embedded Programming

## 1. 임베디드 시스템 개요

### 임베디드 시스템이란?
임베디드 시스템은 특정 작업을 수행하기 위해 설계된 컴퓨터 시스템입니다. 이는 하드웨어와 소프트웨어가 밀접하게 통합되어 있으며, 일반적으로 실시간 처리를 요구합니다.

### 주요 특징
1. **제한된 자원**: 메모리, CPU, 저장공간이 제한적.
2. **실시간 처리**: 특정 작업을 정해진 시간 안에 완료해야 함.
3. **전용 설계**: 특정 기능 수행에 최적화.

### 임베디드 시스템의 예
- 마이크로컨트롤러 기반 시스템 (Arduino, STM32)
- 가전제품 (전자레인지, 세탁기)
- 자동차 시스템 (ABS, 엔진 제어)

---

## 2. 하드웨어와의 통신

### GPIO (General Purpose Input/Output)
GPIO는 임베디드 시스템에서 외부 장치와 상호작용하기 위한 기본적인 인터페이스입니다.

#### GPIO 기본 예제
```c
#include <stdint.h>

#define GPIO_BASE 0x40020C00
#define GPIO_MODER (*(volatile uint32_t *)(GPIO_BASE))
#define GPIO_ODR (*(volatile uint32_t *)(GPIO_BASE + 0x14))

int main() {
    GPIO_MODER |= (1 << 10);  // 핀 5를 출력 모드로 설정
    GPIO_ODR |= (1 << 5);     // 핀 5를 HIGH로 설정

    while (1) {
        GPIO_ODR ^= (1 << 5); // 핀 5 토글
        for (volatile int i = 0; i < 100000; i++);  // 간단한 지연
    }

    return 0;
}
```

### UART (Universal Asynchronous Receiver/Transmitter)
UART는 직렬 통신을 위한 프로토콜로, 데이터를 비동기 방식으로 전송합니다.

#### UART 송수신 예제
```c
#include <stdio.h>

void UART_Init() {
    // UART 초기화 코드 작성
    printf("UART 초기화 완료\n");
}

void UART_Send(char *data) {
    // 데이터 송신 코드 작성
    printf("송신: %s\n", data);
}

int main() {
    UART_Init();
    UART_Send("Hello, UART!");
    return 0;
}
```

### I2C와 SPI
- **I2C**: 다중 슬레이브 장치를 제어하는 직렬 버스 프로토콜.
- **SPI**: 고속 직렬 데이터 전송을 지원하는 프로토콜.

#### I2C 데이터 전송 예제
```c
void I2C_Send(uint8_t address, uint8_t data) {
    // I2C 데이터 전송 구현
    printf("I2C 송신 - 주소: 0x%X, 데이터: 0x%X\n", address, data);
}

int main() {
    I2C_Send(0x50, 0xA5);
    return 0;
}
```

---

## 3. 메모리 제한 환경에서의 효율적 코딩

### 동적 메모리 할당 지양
임베디드 시스템에서는 동적 메모리 할당 (`malloc`, `free`)을 지양하고 정적 메모리 할당을 권장합니다. 이는 메모리 누수와 단편화를 방지하기 위함입니다.

#### 정적 메모리 예제
```c
#include <stdio.h>

#define BUFFER_SIZE 256
char buffer[BUFFER_SIZE];

int main() {
    snprintf(buffer, BUFFER_SIZE, "임베디드 시스템에서 정적 메모리 사용\n");
    printf("%s", buffer);
    return 0;
}
```

### 메모리 풀이용
동적 메모리를 효율적으로 사용하기 위해 메모리 풀(memory pool)을 구현합니다.

#### 메모리 풀 예제
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POOL_SIZE 1024
static char memory_pool[POOL_SIZE];
static size_t pool_index = 0;

void* allocate(size_t size) {
    if (pool_index + size > POOL_SIZE) {
        return NULL; // 메모리 부족
    }
    void* ptr = &memory_pool[pool_index];
    pool_index += size;
    return ptr;
}

void reset_pool() {
    pool_index = 0; // 메모리 풀 재설정
}

int main() {
    char* data = (char*)allocate(100);
    if (data) {
        strcpy(data, "Memory Pool Test");
        printf("%s\n", data);
    } else {
        printf("메모리 부족\n");
    }
    reset_pool();
    return 0;
}
```

---

## 4. 실시간 운영 체제 (RTOS)

### RTOS란?
실시간 운영 체제(Real-Time Operating System)는 임베디드 시스템에서 다중 작업을 관리하며, 특정 작업을 정해진 시간 안에 완료하도록 보장합니다.

### 주요 개념
1. **태스크(Task)**: RTOS에서 실행되는 개별 작업.
2. **스케줄러(Scheduler)**: 태스크의 실행 순서를 관리.
3. **세마포어와 뮤텍스**: 동기화 메커니즘 제공.

#### RTOS 예제 (FreeRTOS)
```c
#include "FreeRTOS.h"
#include "task.h"

void Task1(void *pvParameters) {
    while (1) {
        printf("Task 1 실행\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // 1초 대기
    }
}

void Task2(void *pvParameters) {
    while (1) {
        printf("Task 2 실행\n");
        vTaskDelay(500 / portTICK_PERIOD_MS);  // 0.5초 대기
    }
}

int main() {
    xTaskCreate(Task1, "Task 1", 1000, NULL, 1, NULL);
    xTaskCreate(Task2, "Task 2", 1000, NULL, 1, NULL);

    vTaskStartScheduler();  // 스케줄러 시작
    return 0;
}
```

---

## 5. 저전력 설계와 최적화

### 저전력 모드
임베디드 시스템은 배터리 수명을 늘리기 위해 저전력 모드를 활용합니다.

#### 저전력 모드 활성화 예제
```c
void enterLowPowerMode() {
    // 저전력 모드 진입 코드
    printf("저전력 모드 활성화\n");
}

int main() {
    enterLowPowerMode();
    return 0;
}
```

### 인터럽트 기반 설계
불필요한 폴링을 줄이고 인터럽트를 활용해 효율성을 극대화합니다.

#### 인터럽트 예제
```c
#include <stdio.h>

void interruptHandler() {
    printf("인터럽트 발생!\n");
}

int main() {
    // 인터럽트 설정 코드 작성
    printf("대기 중...\n");
    interruptHandler();
    return 0;
}
```

---

## 6. 실습: LED 점멸 프로그램

### 목표
GPIO를 사용하여 LED를 주기적으로 점멸시킵니다.

#### 프로그램
```c
#include <stdint.h>
#include <stdio.h>

#define GPIO_BASE 0x40020C00
#define GPIO_MODER (*(volatile uint32_t *)(GPIO_BASE))
#define GPIO_ODR (*(volatile uint32_t *)(GPIO_BASE + 0x14))

void delay(int count) {
    for (volatile int i = 0; i < count; i++);
}

int main() {
    GPIO_MODER |= (1 << 10);  // GPIO 핀 설정

    while (1) {
        GPIO_ODR ^= (1 << 5); // LED 토글
        delay(1000000);
    }

    return 0;
}
```

---

임베디드 프로그래밍은 하드웨어와 밀접하게 통합된 시스템을 설계하는 기술입니다. GPIO, UART, RTOS 등 다양한 도구와 기술을 활용하여 고성능, 저전력, 안정적인 시스템을 구축할 수 있습니다.

