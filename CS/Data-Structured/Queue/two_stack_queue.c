/*
 * main.c
 *
 * Two-Stack Queue를 구현한 예제입니다.
 * 이 구현체는 두 개의 배열 기반 스택(Stack)을 사용하여 큐(Queue)의 동작(enqueue, dequeue, peek, isEmpty)을 구현합니다.
 *
 * 기본 아이디어:
 * - enqueue 연산은 stack_in에 요소를 push합니다.
 * - dequeue 연산은 먼저 stack_out이 비어 있는지 확인한 후, 비어 있다면 stack_in의 모든 요소를 pop하여 stack_out에 push합니다.
 *   그 후, stack_out에서 요소를 pop하여 반환합니다.
 *
 * 이 코드는 초보자부터 실무자까지 이해할 수 있도록 자세한 주석과 함께 작성되었습니다.
 */

#include <stdio.h>
#include <stdlib.h>

#define STACK_CAPACITY 10  // 각 스택의 최대 용량

// 배열 기반 스택 구조체 정의
typedef struct {
    int *data;      // 스택 데이터를 저장할 배열
    int top;        // 스택의 현재 탑 인덱스 (-1이면 스택이 비어 있음)
    int capacity;   // 스택의 최대 용량
} Stack;

// 스택 생성 함수
Stack* createStack(int capacity) {
    Stack *s = (Stack*) malloc(sizeof(Stack));
    if (s == NULL) {
        fprintf(stderr, "Stack 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    s->capacity = capacity;
    s->top = -1;
    s->data = (int*) malloc(sizeof(int) * capacity);
    if (s->data == NULL) {
        fprintf(stderr, "Stack 데이터 배열 메모리 할당 실패!\n");
        free(s);
        exit(EXIT_FAILURE);
    }
    return s;
}

// 스택이 비어있는지 확인
int isEmptyStack(Stack *s) {
    return (s->top == -1);
}

// 스택이 가득 찼는지 확인
int isFullStack(Stack *s) {
    return (s->top == s->capacity - 1);
}

// 스택에 값 삽입 (Push)
void pushStack(Stack *s, int value) {
    if (isFullStack(s)) {
        fprintf(stderr, "Stack 오버플로우! %d을(를) 삽입할 수 없습니다.\n", value);
        return;
    }
    s->data[++(s->top)] = value;
}

// 스택에서 값 삭제 (Pop)
int popStack(Stack *s) {
    if (isEmptyStack(s)) {
        fprintf(stderr, "Stack 언더플로우! 삭제할 값이 없습니다.\n");
        return -1;  // 오류 코드
    }
    return s->data[(s->top)--];
}

// 스택의 탑 값 확인 (Peek)
int peekStack(Stack *s) {
    if (isEmptyStack(s)) {
        fprintf(stderr, "Stack이 비어 있습니다. 피크할 값이 없습니다.\n");
        return -1;
    }
    return s->data[s->top];
}

// 스택에 저장된 요소 수 반환
int sizeStack(Stack *s) {
    return s->top + 1;
}

// 스택 메모리 해제
void freeStack(Stack *s) {
    free(s->data);
    free(s);
}

// Two-Stack Queue 구조체 정의
typedef struct {
    Stack *stack_in;   // 요소 삽입 전용 스택
    Stack *stack_out;  // 요소 삭제 전용 스택
    int capacity;      // 큐의 최대 용량 (전체 요소 수)
} TwoStackQueue;

// 두 스택을 사용하는 큐 생성 함수
TwoStackQueue* createTwoStackQueue(int capacity) {
    TwoStackQueue *q = (TwoStackQueue*) malloc(sizeof(TwoStackQueue));
    if (q == NULL) {
        fprintf(stderr, "TwoStackQueue 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    q->capacity = capacity;
    // 각 스택은 최대 capacity 만큼의 요소를 저장할 수 있도록 생성
    q->stack_in = createStack(capacity);
    q->stack_out = createStack(capacity);
    return q;
}

// 두 스택에 저장된 총 요소 수 반환
int totalSize(TwoStackQueue *q) {
    return sizeStack(q->stack_in) + sizeStack(q->stack_out);
}

// 큐가 비어있는지 확인
int isEmptyQueue(TwoStackQueue *q) {
    return (totalSize(q) == 0);
}

// 큐가 가득 찼는지 확인
int isFullQueue(TwoStackQueue *q) {
    return (totalSize(q) == q->capacity);
}

/*
 * enqueue 함수:
 * 큐에 값을 삽입합니다.
 * stack_in에 요소를 push하여 구현하며, 전체 큐의 용량을 초과하지 않도록 합니다.
 */
void enqueue(TwoStackQueue *q, int value) {
    if (isFullQueue(q)) {
        fprintf(stderr, "TwoStackQueue 오버플로우! %d을(를) 삽입할 수 없습니다.\n", value);
        return;
    }
    pushStack(q->stack_in, value);
    printf("Enqueued: %d\n", value);
}

/*
 * dequeue 함수:
 * 큐에서 값을 삭제하고 반환합니다.
 * stack_out이 비어 있을 경우, stack_in의 모든 요소를 pop하여 stack_out에 push한 후, stack_out에서 pop합니다.
 */
int dequeue(TwoStackQueue *q) {
    if (isEmptyQueue(q)) {
        fprintf(stderr, "TwoStackQueue 언더플로우! 삭제할 값이 없습니다.\n");
        return -1;
    }
    if (isEmptyStack(q->stack_out)) {
        // stack_in의 모든 요소를 stack_out으로 이동
        while (!isEmptyStack(q->stack_in)) {
            int temp = popStack(q->stack_in);
            pushStack(q->stack_out, temp);
        }
    }
    int value = popStack(q->stack_out);
    printf("Dequeued: %d\n", value);
    return value;
}

/*
 * peek 함수:
 * 큐의 front에 있는 값을 확인하여 반환합니다.
 * stack_out이 비어 있다면, stack_in의 모든 요소를 stack_out으로 이동한 후에 peek합니다.
 */
int peek(TwoStackQueue *q) {
    if (isEmptyQueue(q)) {
        fprintf(stderr, "TwoStackQueue가 비어 있습니다. 피크할 값이 없습니다.\n");
        return -1;
    }
    if (isEmptyStack(q->stack_out)) {
        while (!isEmptyStack(q->stack_in)) {
            int temp = popStack(q->stack_in);
            pushStack(q->stack_out, temp);
        }
    }
    return peekStack(q->stack_out);
}

/*
 * freeTwoStackQueue 함수:
 * Two-Stack Queue에 할당된 모든 메모리를 해제합니다.
 */
void freeTwoStackQueue(TwoStackQueue *q) {
    freeStack(q->stack_in);
    freeStack(q->stack_out);
    free(q);
}

/*
 * 메인 함수:
 * Two-Stack Queue의 동작을 시연합니다.
 */
int main(void) {
    // 큐의 최대 용량을 10으로 설정
    TwoStackQueue *queue = createTwoStackQueue(10);
    
    printf("=== Two-Stack Queue 데모 ===\n\n");

    // Enqueue 연산: 값 삽입
    enqueue(queue, 100);
    enqueue(queue, 200);
    enqueue(queue, 300);
    enqueue(queue, 400);
    enqueue(queue, 500);

    // Peek 연산: 큐의 front 값 확인
    int frontValue = peek(queue);
    if (frontValue != -1) {
        printf("Front value: %d\n", frontValue);
    }

    // Dequeue 연산: 값 삭제
    dequeue(queue);
    dequeue(queue);

    // 추가 Enqueue 연산
    enqueue(queue, 600);
    enqueue(queue, 700);

    // 연속적인 Dequeue 연산
    while (!isEmptyQueue(queue)) {
        dequeue(queue);
    }

    // 언더플로우 상태에서 Dequeue 시도
    dequeue(queue);

    // 메모리 해제
    freeTwoStackQueue(queue);

    return 0;
}
