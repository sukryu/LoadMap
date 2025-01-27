# 02. Multithreading and Concurrency

## 1. 멀티스레드 프로그래밍 기초

### 멀티스레드란?
멀티스레드는 하나의 프로세스 내에서 여러 스레드가 동시에 작업을 수행하도록 설계된 프로그래밍 방식입니다. 이를 통해 성능을 향상시키고 자원을 효율적으로 활용할 수 있습니다.

### 스레드의 장점
1. **병렬 처리**: 작업을 분산하여 실행 속도를 높입니다.
2. **자원 공유**: 메모리와 파일 같은 자원을 효율적으로 공유합니다.
3. **응답성 개선**: 사용자 인터페이스와 백그라운드 작업을 분리하여 응답성을 높입니다.

### POSIX 스레드 (pthreads)
POSIX 스레드는 C에서 멀티스레드를 구현하기 위한 표준 라이브러리입니다.

#### 기본 스레드 생성
```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* threadFunction(void* arg) {
    printf("스레드 실행 중: %s\n", (char*)arg);
    return NULL;
}

int main() {
    pthread_t thread;
    char* message = "Hello, Thread!";

    if (pthread_create(&thread, NULL, threadFunction, (void*)message) != 0) {
        perror("스레드 생성 실패");
        exit(1);
    }

    pthread_join(thread, NULL);  // 스레드가 종료될 때까지 대기
    printf("메인 함수 종료\n");
    return 0;
}
```

---

## 2. 동기화 메커니즘

멀티스레드 환경에서는 여러 스레드가 동시에 자원에 접근할 때 발생하는 문제를 해결하기 위해 동기화가 필요합니다.

### 뮤텍스 (Mutex)
뮤텍스는 하나의 스레드만 임계 구역에 접근하도록 보장합니다.

#### 예제: 뮤텍스를 사용한 동기화
```c
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock;
int sharedCounter = 0;

void* increment(void* arg) {
    pthread_mutex_lock(&lock);
    for (int i = 0; i < 100000; i++) {
        sharedCounter++;
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("최종 카운터 값: %d\n", sharedCounter);
    pthread_mutex_destroy(&lock);
    return 0;
}
```

### 세마포어 (Semaphore)
세마포어는 특정 자원의 최대 접근 가능 개수를 제한합니다.

#### 예제: 세마포어 사용
```c
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t semaphore;

void* task(void* arg) {
    sem_wait(&semaphore);  // 세마포어 감소
    printf("스레드 실행: %ld\n", (long)arg);
    sem_post(&semaphore);  // 세마포어 증가
    return NULL;
}

int main() {
    pthread_t threads[5];
    sem_init(&semaphore, 0, 2);  // 동시에 2개 스레드만 실행

    for (long i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, task, (void*)i);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore);
    return 0;
}
```

### 조건 변수 (Condition Variable)
조건 변수는 특정 조건이 충족될 때 스레드가 깨어나도록 동기화합니다.

#### 예제: 조건 변수 사용
```c
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock;
pthread_cond_t cond;
int ready = 0;

void* producer(void* arg) {
    pthread_mutex_lock(&lock);
    ready = 1;
    printf("데이터 생성 완료\n");
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* consumer(void* arg) {
    pthread_mutex_lock(&lock);
    while (ready == 0) {
        pthread_cond_wait(&cond, &lock);
    }
    printf("데이터 소비\n");
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t prod, cons;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&lock);    
    pthread_cond_destroy(&cond);
    return 0;
}
```

---

## 3. 레이스 컨디션과 해결 방법

### 레이스 컨디션이란?
레이스 컨디션은 두 개 이상의 스레드가 동시에 동일한 자원에 접근하며, 예기치 않은 결과를 초래하는 상황을 의미합니다.

### 해결 방법
1. 뮤텍스를 사용하여 임계 구역 보호.
2. 세마포어로 자원 접근 제한.
3. 조건 변수를 활용하여 작업 순서 제어.

---

## 4. 고급 멀티스레딩 기법

### 스레드 풀
스레드 풀은 작업 요청마다 새로운 스레드를 생성하는 대신, 미리 생성된 스레드 풀에서 스레드를 재사용하는 기법입니다.

#### 예제: 간단한 스레드 풀 구현
```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREAD_POOL_SIZE 4

void* worker(void* arg) {
    printf("작업 처리 중: %d\n", *(int*)arg);
    free(arg);
    return NULL;
}

int main() {
    pthread_t threads[THREAD_POOL_SIZE];
    int taskCount = 10;

    for (int i = 0; i < taskCount; i++) {
        int* taskId = malloc(sizeof(int));
        *taskId = i + 1;
        pthread_create(&threads[i % THREAD_POOL_SIZE], NULL, worker, taskId);
        pthread_join(threads[i % THREAD_POOL_SIZE], NULL);
    }

    return 0;
}
```

---

## 5. 실습: 멀티스레드 웹 서버

### 간단한 웹 서버 구현
멀티스레드를 사용해 다중 클라이언트를 처리하는 웹 서버를 구현합니다.

#### 예제
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

void* handleClient(void* arg) {
    int clientSocket = *(int*)arg;
    free(arg);

    char buffer[1024];
    read(clientSocket, buffer, sizeof(buffer) - 1);
    printf("클라이언트 요청: %s\n", buffer);

    char response[] = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!";
    write(clientSocket, response, sizeof(response) - 1);

    close(clientSocket);
    return NULL;
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr = {0};

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);

    printf("서버 시작: 포트 8080\n");

    while (1) {
        int* clientSocket = malloc(sizeof(int));
        *clientSocket = accept(serverSocket, NULL, NULL);

        pthread_t thread;
        pthread_create(&thread, NULL, handleClient, clientSocket);
        pthread_detach(thread);
    }

    close(serverSocket);
    return 0;
}
```

### 설명
1. 서버 소켓 생성 및 바인딩.
2. 클라이언트 연결 수락 후 스레드 생성.
3. 각 스레드에서 클라이언트 요청 처리.

---

멀티스레딩과 동기화는 고성능 애플리케이션의 핵심 기술입니다. 이를 활용하면 다중 작업 환경에서 안정적이고 효율적인 프로그램을 개발할 수 있습니다.

