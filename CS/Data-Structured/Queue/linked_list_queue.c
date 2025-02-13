/*
 * main.c
 *
 * 연결리스트 기반 큐(Linked List-based Queue)를 구현하고 다양한 연산(enqueue, dequeue, peek, isEmpty)
 * 을 시연하는 예제입니다.
 *
 * 이 구현은 동적 메모리 할당을 통해 큐의 크기를 제한 없이 관리할 수 있으며,
 * 초보자부터 실무자까지 이해할 수 있도록 상세한 주석과 함께 작성되었습니다.
 */

#include <stdio.h>
#include <stdlib.h>

// 노드 구조체: 각 노드는 데이터를 저장하고 다음 노드를 가리키는 포인터를 포함합니다.
typedef struct Node {
    int data;           // 저장할 데이터
    struct Node *next;  // 다음 노드에 대한 포인터
} Node;

// 연결리스트 기반 큐 구조체: 프론트(Front)와 리어(Rear) 포인터를 포함합니다.
typedef struct {
    Node *front;        // 큐의 앞부분 (삭제가 이루어지는 위치)
    Node *rear;         // 큐의 뒷부분 (삽입이 이루어지는 위치)
} LinkedQueue;

/*
 * createQueue 함수:
 * 빈 연결리스트 기반 큐를 생성하고 초기화합니다.
 */
LinkedQueue* createQueue() {
    LinkedQueue *queue = (LinkedQueue*) malloc(sizeof(LinkedQueue));
    if (queue == NULL) {
        fprintf(stderr, "큐 구조체 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

/*
 * isEmptyQueue 함수:
 * 큐가 비어있는지 확인합니다.
 * 반환값: 큐가 비어있으면 1(true), 그렇지 않으면 0(false)
 */
int isEmptyQueue(LinkedQueue *queue) {
    return (queue->front == NULL);
}

/*
 * enqueue 함수:
 * 큐의 rear에 새 노드를 삽입합니다.
 */
void enqueue(LinkedQueue *queue, int value) {
    // 새 노드 생성
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "새 노드 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->next = NULL;

    // 큐가 비어있는 경우, 프론트와 리어 모두 새 노드를 가리킵니다.
    if (isEmptyQueue(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        // 큐가 비어있지 않은 경우, 리어의 next에 새 노드를 연결하고 리어를 갱신합니다.
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    printf("Enqueued: %d\n", value);
}

/*
 * dequeue 함수:
 * 큐의 front에서 노드를 삭제하고, 해당 노드의 데이터를 반환합니다.
 * 만약 큐가 비어있다면, 에러 메시지를 출력하고 -1을 반환합니다.
 */
int dequeue(LinkedQueue *queue) {
    if (isEmptyQueue(queue)) {
        fprintf(stderr, "큐 언더플로우! 삭제할 값이 없습니다.\n");
        return -1;
    }
    Node *temp = queue->front;
    int value = temp->data;
    queue->front = temp->next;
    
    // 큐에서 마지막 노드를 삭제한 경우, 리어도 NULL로 설정합니다.
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    printf("Dequeued: %d\n", value);
    return value;
}

/*
 * peek 함수:
 * 큐의 front에 있는 값을 반환합니다.
 * 만약 큐가 비어있다면, 에러 메시지를 출력하고 -1을 반환합니다.
 */
int peek(LinkedQueue *queue) {
    if (isEmptyQueue(queue)) {
        fprintf(stderr, "큐가 비어 있습니다. 피크할 값이 없습니다.\n");
        return -1;
    }
    return queue->front->data;
}

/*
 * printQueue 함수:
 * 큐의 현재 상태를 순서대로 출력합니다.
 */
void printQueue(LinkedQueue *queue) {
    if (isEmptyQueue(queue)) {
        printf("Queue: 비어 있음\n");
        return;
    }
    printf("Queue: ");
    Node *current = queue->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

/*
 * freeQueue 함수:
 * 큐에 할당된 모든 메모리를 해제합니다.
 */
void freeQueue(LinkedQueue *queue) {
    Node *current = queue->front;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(queue);
}

/*
 * 메인 함수:
 * 연결리스트 기반 큐의 동작을 시연합니다.
 */
int main(void) {
    // 빈 큐 생성
    LinkedQueue *queue = createQueue();
    
    printf("=== 연결리스트 기반 큐 데모 ===\n\n");

    // Enqueue 연산: 값 삽입
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    printQueue(queue);

    // Peek 연산: 큐의 front 값 확인
    int frontValue = peek(queue);
    if (frontValue != -1) {
        printf("Front value: %d\n", frontValue);
    }

    // Dequeue 연산: 값 삭제
    dequeue(queue);
    printQueue(queue);

    // 추가 Enqueue 연산
    enqueue(queue, 40);
    enqueue(queue, 50);
    printQueue(queue);

    // 모든 요소를 Dequeue하여 큐를 비움
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
