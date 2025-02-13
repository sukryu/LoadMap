/*
 * main.c
 *
 * 배열 기반 큐(Array-based Queue)를 구현하고 다양한 연산(enqueue, dequeue, peek, isEmpty, isFull)
 * 을 시연하는 예제입니다.
 *
 * 이 구현은 원형 큐(Circular Queue)를 사용하여 배열의 고정 크기 내에서 효율적인 공간 활용이 가능하도록 설계되었습니다.
 * 초보자부터 실무자까지 이해할 수 있도록 자세한 주석과 함께 작성되었습니다.
 */

#include <stdio.h>
#include <stdlib.h>

// 배열 기반 큐 구조체 정의
typedef struct {
    int *data;      // 큐 데이터를 저장할 동적 배열
    int front;      // 큐의 앞(front) 인덱스 (삭제 위치)
    int rear;       // 큐의 뒤(rear) 인덱스 (삽입 위치)
    int size;       // 현재 큐에 저장된 요소의 개수
    int capacity;   // 큐의 최대 용량
} ArrayQueue;

/*
 * createQueue 함수:
 * 지정된 용량(capacity)으로 배열 기반 큐를 생성하고 초기화합니다.
 */
ArrayQueue* createQueue(int capacity) {
    ArrayQueue *queue = (ArrayQueue*) malloc(sizeof(ArrayQueue));
    if (queue == NULL) {
        fprintf(stderr, "큐 구조체 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
    queue->data = (int*) malloc(sizeof(int) * capacity);
    if (queue->data == NULL) {
        fprintf(stderr, "큐 데이터 배열 메모리 할당 실패!\n");
        free(queue);
        exit(EXIT_FAILURE);
    }
    return queue;
}

/*
 * isEmptyQueue 함수:
 * 큐가 비어있는지 확인합니다.
 * 반환값: 큐가 비어있으면 1(true), 그렇지 않으면 0(false)
 */
int isEmptyQueue(ArrayQueue *queue) {
    return (queue->size == 0);
}

/*
 * isFullQueue 함수:
 * 큐가 가득 찼는지 확인합니다.
 * 반환값: 큐가 가득 차면 1(true), 그렇지 않으면 0(false)
 */
int isFullQueue(ArrayQueue *queue) {
    return (queue->size == queue->capacity);
}

/*
 * enqueue 함수:
 * 큐의 rear 위치에 값을 삽입합니다.
 * 만약 큐가 가득 차면, 에러 메시지를 출력합니다.
 */
void enqueue(ArrayQueue *queue, int value) {
    if (isFullQueue(queue)) {
        fprintf(stderr, "큐 오버플로우! %d을(를) 삽입할 수 없습니다.\n", value);
        return;
    }
    queue->data[queue->rear] = value;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->size++;
    printf("Enqueued: %d\n", value);
}

/*
 * dequeue 함수:
 * 큐의 front 위치에서 값을 삭제하고 반환합니다.
 * 만약 큐가 비어있으면, 에러 메시지를 출력하고 -1을 반환합니다.
 */
int dequeue(ArrayQueue *queue) {
    if (isEmptyQueue(queue)) {
        fprintf(stderr, "큐 언더플로우! 삭제할 값이 없습니다.\n");
        return -1; // 오류 코드
    }
    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    printf("Dequeued: %d\n", value);
    return value;
}

/*
 * peek 함수:
 * 큐의 front에 있는 값을 반환합니다.
 * 만약 큐가 비어있으면, 에러 메시지를 출력하고 -1을 반환합니다.
 */
int peek(ArrayQueue *queue) {
    if (isEmptyQueue(queue)) {
        fprintf(stderr, "큐가 비어 있습니다. 피크할 값이 없습니다.\n");
        return -1;
    }
    return queue->data[queue->front];
}

/*
 * printQueue 함수:
 * 큐의 현재 상태를 순서대로 출력합니다.
 */
void printQueue(ArrayQueue *queue) {
    printf("Queue: ");
    if (isEmptyQueue(queue)) {
        printf("비어 있음\n");
        return;
    }
    for (int i = 0; i < queue->size; i++) {
        int index = (queue->front + i) % queue->capacity;
        printf("%d ", queue->data[index]);
    }
    printf("\n");
}

/*
 * freeQueue 함수:
 * 큐에 할당된 메모리를 해제합니다.
 */
void freeQueue(ArrayQueue *queue) {
    free(queue->data);
    free(queue);
}

/*
 * 메인 함수:
 * 배열 기반 큐의 동작을 시연합니다.
 */
int main(void) {
    // 용량 5인 큐 생성
    ArrayQueue *queue = createQueue(5);
    
    printf("=== 배열 기반 큐 데모 ===\n\n");

    // Enqueue 연산: 값 삽입
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
    printQueue(queue);

    // Dequeue 연산: 값 삭제
    dequeue(queue);
    printQueue(queue);

    // Peek 연산: 큐의 front 값 확인
    int frontValue = peek(queue);
    if (frontValue != -1) {
        printf("Front value: %d\n", frontValue);
    }
    
    // 추가 Enqueue 연산: 원형 큐 특성을 확인
    enqueue(queue, 50);
    enqueue(queue, 60);  // 큐가 가득 찰 수 있으므로 주의
    printQueue(queue);

    // 가득 찬 경우 enqueue 시도
    enqueue(queue, 70);  // 이 경우 큐 오버플로우 메시지 출력

    // 모든 요소 Dequeue하여 큐를 비움
    while (!isEmptyQueue(queue)) {
        dequeue(queue);
    }
    printQueue(queue);

    // 언더플로우 상태에서 Dequeue 시도
    dequeue(queue);

    // 메모리 해제
    freeQueue(queue);

    return 0;
}
