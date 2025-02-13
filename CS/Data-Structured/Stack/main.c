/*
 * main.c
 *
 * 스택(Stack) 자료구조를 배열 기반(Stack using Array)과 연결리스트 기반(Stack using Linked List)으로 각각 구현하고,
 * 각 구현 방식의 주요 연산(Push, Pop, Peek)을 시연하는 예제입니다.
 *
 * 이 코드는 초보자부터 실무자까지 이해할 수 있도록 상세한 주석과 함께 작성되었습니다.
 */

#include <stdio.h>
#include <stdlib.h>

/* ===========================================================
 * 배열 기반 스택 (Array-based Stack) 구현
 * ===========================================================
 */

// 최대 스택 용량 정의
#define ARRAY_STACK_CAPACITY 10

// 배열 기반 스택 구조체
typedef struct {
    int *data;      // 스택 데이터를 저장할 동적 배열
    int top;        // 현재 탑의 인덱스 (-1이면 스택이 비어 있음)
    int capacity;   // 스택의 최대 용량
} ArrayStack;

// 배열 기반 스택 생성: 주어진 용량으로 스택을 초기화
ArrayStack* createArrayStack(int capacity) {
    ArrayStack *stack = (ArrayStack*) malloc(sizeof(ArrayStack));
    if (stack == NULL) {
        fprintf(stderr, "ArrayStack 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    stack->capacity = capacity;
    stack->top = -1;
    stack->data = (int*) malloc(sizeof(int) * capacity);
    if (stack->data == NULL) {
        fprintf(stderr, "ArrayStack 데이터 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    return stack;
}

// 배열 기반 스택이 비어있는지 확인
int isEmptyArrayStack(ArrayStack *stack) {
    return (stack->top == -1);
}

// 배열 기반 스택에 값 삽입 (Push)
void pushArrayStack(ArrayStack *stack, int value) {
    if (stack->top == stack->capacity - 1) {
        fprintf(stderr, "ArrayStack 오버플로우! %d을(를) 삽입할 수 없습니다.\n", value);
        return;
    }
    stack->data[++stack->top] = value;
    printf("ArrayStack: %d 삽입\n", value);
}

// 배열 기반 스택에서 값 삭제 (Pop)
int popArrayStack(ArrayStack *stack) {
    if (isEmptyArrayStack(stack)) {
        fprintf(stderr, "ArrayStack 언더플로우! 삭제할 값이 없습니다.\n");
        return -1;  // 오류 코드
    }
    int value = stack->data[stack->top--];
    printf("ArrayStack: %d 삭제\n", value);
    return value;
}

// 배열 기반 스택의 탑 값 확인 (Peek)
int peekArrayStack(ArrayStack *stack) {
    if (isEmptyArrayStack(stack)) {
        fprintf(stderr, "ArrayStack이 비어 있습니다. 피크할 값이 없습니다.\n");
        return -1;
    }
    return stack->data[stack->top];
}

// 배열 기반 스택 메모리 해제
void freeArrayStack(ArrayStack *stack) {
    free(stack->data);
    free(stack);
}

/* ===========================================================
 * 연결리스트 기반 스택 (Linked List-based Stack) 구현
 * ===========================================================
 */

// 연결리스트 스택 노드 구조체
typedef struct StackNode {
    int data;               // 노드에 저장된 데이터
    struct StackNode *next; // 다음 노드를 가리키는 포인터
} StackNode;

// 연결리스트 기반 스택에 값 삽입 (Push)
// 새 노드를 생성하고 스택의 맨 앞(탑)으로 연결합니다.
StackNode* pushLinkedListStack(StackNode *top, int value) {
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode == NULL) {
        fprintf(stderr, "LinkedList Stack 노드 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->next = top;
    printf("LinkedListStack: %d 삽입\n", value);
    return newNode;  // 새로운 노드가 스택의 탑이 됨
}

// 연결리스트 기반 스택에서 값 삭제 (Pop)
// 스택의 탑 노드를 삭제하고, 그 다음 노드를 새로운 탑으로 지정합니다.
StackNode* popLinkedListStack(StackNode **top) {
    if (*top == NULL) {
        fprintf(stderr, "LinkedListStack 언더플로우! 삭제할 값이 없습니다.\n");
        return NULL;
    }
    StackNode *temp = *top;
    int value = temp->data;
    *top = temp->next;
    printf("LinkedListStack: %d 삭제\n", value);
    free(temp);
    return *top;
}

// 연결리스트 기반 스택의 탑 값 확인 (Peek)
int peekLinkedListStack(StackNode *top) {
    if (top == NULL) {
        fprintf(stderr, "LinkedListStack이 비어 있습니다. 피크할 값이 없습니다.\n");
        return -1;
    }
    return top->data;
}

// 연결리스트 기반 스택이 비어있는지 확인
int isEmptyLinkedListStack(StackNode *top) {
    return (top == NULL);
}

// 연결리스트 기반 스택의 모든 노드 메모리 해제
void freeLinkedListStack(StackNode *top) {
    while (top != NULL) {
        StackNode *temp = top;
        top = top->next;
        free(temp);
    }
}

/* ===========================================================
 * 메인 함수: 두 가지 스택 구현 방식 시연
 * ===========================================================
 */
int main(void) {
    /* ----------------------------
     * 1. 배열 기반 스택 데모
     * ----------------------------
     */
    printf("=== 배열 기반 스택 데모 ===\n");
    ArrayStack *arrayStack = createArrayStack(ARRAY_STACK_CAPACITY);

    // 값 삽입 (Push)
    pushArrayStack(arrayStack, 10);
    pushArrayStack(arrayStack, 20);
    pushArrayStack(arrayStack, 30);

    // 탑 값 확인 (Peek)
    int topValue = peekArrayStack(arrayStack);
    printf("ArrayStack 탑의 값: %d\n", topValue);

    // 값 삭제 (Pop)
    popArrayStack(arrayStack);
    popArrayStack(arrayStack);
    
    // 재확인
    topValue = peekArrayStack(arrayStack);
    printf("ArrayStack 팝 후 탑의 값: %d\n", topValue);

    // 배열 기반 스택 메모리 해제
    freeArrayStack(arrayStack);

    printf("\n");

    /* ----------------------------
     * 2. 연결리스트 기반 스택 데모
     * ----------------------------
     */
    printf("=== 연결리스트 기반 스택 데모 ===\n");
    StackNode *linkedStack = NULL;  // 초기 스택은 빈 상태

    // 값 삽입 (Push)
    linkedStack = pushLinkedListStack(linkedStack, 100);
    linkedStack = pushLinkedListStack(linkedStack, 200);
    linkedStack = pushLinkedListStack(linkedStack, 300);

    // 탑 값 확인 (Peek)
    int topNodeValue = peekLinkedListStack(linkedStack);
    printf("LinkedListStack 탑의 값: %d\n", topNodeValue);

    // 값 삭제 (Pop)
    popLinkedListStack(&linkedStack);
    popLinkedListStack(&linkedStack);

    // 재확인
    topNodeValue = peekLinkedListStack(linkedStack);
    printf("LinkedListStack 팝 후 탑의 값: %d\n", topNodeValue);

    // 연결리스트 기반 스택 메모리 해제
    freeLinkedListStack(linkedStack);

    return 0;
}