/*
 * main.c
 *
 * 우선순위 큐(Priority Queue)를 이진 힙(Max Heap)을 기반으로 구현한 예제입니다.
 * 각 요소는 data와 priority를 갖으며, priority가 높은 요소가 먼저 반환됩니다.
 *
 * 주요 연산:
 * - insert: 새 요소 삽입 후 heapifyUp을 통해 힙 성질 유지
 * - peek: 최대 우선순위 요소 확인 (삭제 없이)
 * - extractMax: 최대 우선순위 요소 삭제 후 heapifyDown을 통해 힙 성질 유지
 *
 * 이 코드는 초보자부터 실무자까지 이해할 수 있도록 상세한 주석과 함께 작성되었습니다.
 */

#include <stdio.h>
#include <stdlib.h>

#define PQ_CAPACITY 10  // 우선순위 큐의 최대 용량

// 우선순위 큐의 노드 구조체 (각 요소는 data와 priority를 가짐)
typedef struct {
    int data;       // 저장할 데이터 (예: 작업 ID 등)
    int priority;   // 우선순위 값 (숫자가 클수록 높은 우선순위)
} PQNode;

// 우선순위 큐 구조체 (Max Heap 기반)
typedef struct {
    int size;       // 현재 저장된 요소 개수
    int capacity;   // 최대 용량
    PQNode *nodes;  // 동적 배열로 관리되는 힙
} PriorityQueue;

// 우선순위 큐 생성: 주어진 용량으로 초기화
PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue *pq = (PriorityQueue*) malloc(sizeof(PriorityQueue));
    if (!pq) {
        fprintf(stderr, "우선순위 큐 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    pq->size = 0;
    pq->capacity = capacity;
    pq->nodes = (PQNode*) malloc(capacity * sizeof(PQNode));
    if (!pq->nodes) {
        fprintf(stderr, "우선순위 큐 노드 배열 메모리 할당 실패!\n");
        free(pq);
        exit(EXIT_FAILURE);
    }
    return pq;
}

// 두 노드의 값을 교환하는 함수
void swap(PQNode *a, PQNode *b) {
    PQNode temp = *a;
    *a = *b;
    *b = temp;
}

// heapifyUp 함수: 새로 삽입된 노드의 위치를 재조정하여 최대 힙 성질 유지
void heapifyUp(PriorityQueue *pq, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && pq->nodes[index].priority > pq->nodes[parent].priority) {
        swap(&pq->nodes[index], &pq->nodes[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

// heapifyDown 함수: 루트 노드 교체 후 힙 성질을 복구
void heapifyDown(PriorityQueue *pq, int index) {
    int largest = index;
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        if (left < pq->size && pq->nodes[left].priority > pq->nodes[largest].priority) {
            largest = left;
        }
        if (right < pq->size && pq->nodes[right].priority > pq->nodes[largest].priority) {
            largest = right;
        }
        if (largest != index) {
            swap(&pq->nodes[index], &pq->nodes[largest]);
            index = largest;
        } else {
            break;
        }
    }
}

// insert 함수: (data, priority) 쌍을 우선순위 큐에 삽입합니다.
void insert(PriorityQueue *pq, int data, int priority) {
    if (pq->size == pq->capacity) {
        fprintf(stderr, "우선순위 큐 오버플로우! (%d, %d) 삽입 실패.\n", data, priority);
        return;
    }
    PQNode node;
    node.data = data;
    node.priority = priority;
    pq->nodes[pq->size] = node;
    heapifyUp(pq, pq->size);
    pq->size++;
    printf("Inserted: (data: %d, priority: %d)\n", data, priority);
}

// peek 함수: 최대 우선순위 요소를 반환 (삭제 없이)
PQNode peek(PriorityQueue *pq) {
    if (pq->size == 0) {
        fprintf(stderr, "우선순위 큐가 비어 있습니다. 피크할 값이 없습니다.\n");
        PQNode errorNode = {-1, -1};
        return errorNode;
    }
    return pq->nodes[0];
}

// extractMax 함수: 최대 우선순위 요소를 삭제 후 반환
PQNode extractMax(PriorityQueue *pq) {
    if (pq->size == 0) {
        fprintf(stderr, "우선순위 큐가 비어 있습니다. 삭제할 요소가 없습니다.\n");
        PQNode errorNode = {-1, -1};
        return errorNode;
    }
    PQNode maxNode = pq->nodes[0];
    pq->nodes[0] = pq->nodes[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
    printf("Extracted: (data: %d, priority: %d)\n", maxNode.data, maxNode.priority);
    return maxNode;
}

// printPriorityQueue 함수: 현재 우선순위 큐의 상태를 출력
void printPriorityQueue(PriorityQueue *pq) {
    printf("Priority Queue: ");
    for (int i = 0; i < pq->size; i++) {
        printf("(data: %d, priority: %d) ", pq->nodes[i].data, pq->nodes[i].priority);
    }
    printf("\n");
}

// freePriorityQueue 함수: 우선순위 큐에 할당된 메모리를 해제
void freePriorityQueue(PriorityQueue *pq) {
    free(pq->nodes);
    free(pq);
}

// 메인 함수: 우선순위 큐의 동작을 시연합니다.
int main(void) {
    // 용량 10의 우선순위 큐 생성
    PriorityQueue *pq = createPriorityQueue(PQ_CAPACITY);
    
    printf("=== Priority Queue (Max Heap) Demo ===\n\n");
    
    // 요소 삽입: 각 요소는 (data, priority) 쌍으로 추가
    insert(pq, 10, 2);   // data: 10, priority: 2
    insert(pq, 20, 5);   // data: 20, priority: 5
    insert(pq, 30, 1);   // data: 30, priority: 1
    insert(pq, 40, 3);   // data: 40, priority: 3
    insert(pq, 50, 4);   // data: 50, priority: 4
    
    // 현재 우선순위 큐 상태 출력
    printPriorityQueue(pq);
    
    // Peek 연산: 최대 우선순위 요소 확인
    PQNode top = peek(pq);
    printf("Peek: (data: %d, priority: %d)\n", top.data, top.priority);
    
    // ExtractMax 연산: 최대 우선순위 요소 삭제
    extractMax(pq);
    printPriorityQueue(pq);
    
    // 추가 요소 삽입
    insert(pq, 60, 6);
    insert(pq, 70, 3);
    printPriorityQueue(pq);
    
    // 우선순위 큐가 빌 때까지 반복적으로 extractMax 연산 수행
    while (pq->size > 0) {
        extractMax(pq);
        printPriorityQueue(pq);
    }
    
    // 메모리 해제
    freePriorityQueue(pq);
    
    return 0;
}