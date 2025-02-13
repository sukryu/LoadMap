/*
 * main.c
 *
 * 이 파일은 최대 힙(Max Heap)과 최소 힙(Min Heap)을 구분하여 구현한 예제입니다.
 * 각 힙은 PQNode 구조체를 사용하여 (data, priority) 쌍으로 관리되며,
 * 최대 힙은 부모 노드의 우선순위가 자식 노드보다 크거나 같고, 
 * 최소 힙은 부모 노드의 우선순위가 자식 노드보다 작거나 같도록 유지합니다.
 *
 * 주요 연산:
 * [Max Heap]
 *  - insertMax: 새로운 요소 삽입 후 maxHeapifyUp으로 힙 성질 복구
 *  - peekMax: 최대 우선순위 요소 확인 (루트 노드)
 *  - extractMax: 루트 노드를 삭제 후 maxHeapifyDown으로 힙 성질 복구
 *
 * [Min Heap]
 *  - insertMin: 새로운 요소 삽입 후 minHeapifyUp으로 힙 성질 복구
 *  - peekMin: 최소 우선순위 요소 확인 (루트 노드)
 *  - extractMin: 루트 노드를 삭제 후 minHeapifyDown으로 힙 성질 복구
 *
 * 이 코드는 초보자부터 실무자까지 이해할 수 있도록 상세한 주석과 함께 작성되었습니다.
 */

#include <stdio.h>
#include <stdlib.h>

#define HEAP_CAPACITY 10  // 두 힙의 최대 용량

// PQNode: 힙의 각 요소를 나타내며, data와 priority를 포함합니다.
typedef struct {
    int data;       // 실제 데이터 (예: 작업 ID 등)
    int priority;   // 우선순위 값 (높을수록 높은 우선순위 for Max Heap, 낮을수록 높은 우선순위 for Min Heap)
} PQNode;

/* =======================
   최대 힙 (Max Heap)
   ======================= */

// MaxHeap 구조체: 최대 힙을 배열 기반으로 구현
typedef struct {
    int size;       // 현재 요소 개수
    int capacity;   // 최대 용량
    PQNode *nodes;  // 동적 배열로 저장되는 PQNode들
} MaxHeap;

// 두 노드를 교환하는 함수
void swapNodes(PQNode *a, PQNode *b) {
    PQNode temp = *a;
    *a = *b;
    *b = temp;
}

// 최대 힙 생성 함수
MaxHeap* createMaxHeap(int capacity) {
    MaxHeap *heap = (MaxHeap*) malloc(sizeof(MaxHeap));
    if (!heap) {
        fprintf(stderr, "MaxHeap 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    heap->size = 0;
    heap->capacity = capacity;
    heap->nodes = (PQNode*) malloc(capacity * sizeof(PQNode));
    if (!heap->nodes) {
        fprintf(stderr, "MaxHeap 노드 배열 메모리 할당 실패!\n");
        free(heap);
        exit(EXIT_FAILURE);
    }
    return heap;
}

// maxHeapifyUp: 삽입 후 새 노드의 위치를 재조정하여 최대 힙 성질 유지
void maxHeapifyUp(MaxHeap *heap, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && heap->nodes[index].priority > heap->nodes[parent].priority) {
        swapNodes(&heap->nodes[index], &heap->nodes[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

// maxHeapifyDown: 루트 삭제 후 힙 성질을 복구하기 위해 하향 조정
void maxHeapifyDown(MaxHeap *heap, int index) {
    int largest = index;
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        if (left < heap->size && heap->nodes[left].priority > heap->nodes[largest].priority) {
            largest = left;
        }
        if (right < heap->size && heap->nodes[right].priority > heap->nodes[largest].priority) {
            largest = right;
        }
        if (largest != index) {
            swapNodes(&heap->nodes[index], &heap->nodes[largest]);
            index = largest;
        } else {
            break;
        }
    }
}

// insertMax: 최대 힙에 (data, priority) 쌍을 삽입
void insertMax(MaxHeap *heap, int data, int priority) {
    if (heap->size == heap->capacity) {
        fprintf(stderr, "MaxHeap 오버플로우! (%d, %d) 삽입 실패.\n", data, priority);
        return;
    }
    PQNode node;
    node.data = data;
    node.priority = priority;
    heap->nodes[heap->size] = node;
    maxHeapifyUp(heap, heap->size);
    heap->size++;
    printf("MaxHeap에 삽입: (data: %d, priority: %d)\n", data, priority);
}

// peekMax: 최대 힙의 루트 노드를 반환 (삭제 없이)
PQNode peekMax(MaxHeap *heap) {
    if (heap->size == 0) {
        fprintf(stderr, "MaxHeap이 비어 있습니다. 피크할 값이 없습니다.\n");
        PQNode errorNode = {-1, -1};
        return errorNode;
    }
    return heap->nodes[0];
}

// extractMax: 최대 힙의 루트 노드를 삭제 후 반환
PQNode extractMax(MaxHeap *heap) {
    if (heap->size == 0) {
        fprintf(stderr, "MaxHeap이 비어 있습니다. 삭제할 요소가 없습니다.\n");
        PQNode errorNode = {-1, -1};
        return errorNode;
    }
    PQNode maxNode = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    maxHeapifyDown(heap, 0);
    printf("MaxHeap에서 추출: (data: %d, priority: %d)\n", maxNode.data, maxNode.priority);
    return maxNode;
}

// printMaxHeap: 최대 힙의 현재 상태를 출력
void printMaxHeap(MaxHeap *heap) {
    printf("MaxHeap: ");
    for (int i = 0; i < heap->size; i++) {
        printf("(data: %d, priority: %d) ", heap->nodes[i].data, heap->nodes[i].priority);
    }
    printf("\n");
}

// freeMaxHeap: 최대 힙에 할당된 메모리 해제
void freeMaxHeap(MaxHeap *heap) {
    free(heap->nodes);
    free(heap);
}

/* =======================
   최소 힙 (Min Heap)
   ======================= */

// MinHeap 구조체: 최소 힙을 배열 기반으로 구현
typedef struct {
    int size;       // 현재 요소 개수
    int capacity;   // 최대 용량
    PQNode *nodes;  // 동적 배열로 저장되는 PQNode들
} MinHeap;

// 최소 힙 생성 함수
MinHeap* createMinHeap(int capacity) {
    MinHeap *heap = (MinHeap*) malloc(sizeof(MinHeap));
    if (!heap) {
        fprintf(stderr, "MinHeap 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    heap->size = 0;
    heap->capacity = capacity;
    heap->nodes = (PQNode*) malloc(capacity * sizeof(PQNode));
    if (!heap->nodes) {
        fprintf(stderr, "MinHeap 노드 배열 메모리 할당 실패!\n");
        free(heap);
        exit(EXIT_FAILURE);
    }
    return heap;
}

// minHeapifyUp: 삽입 후 새 노드의 위치를 재조정하여 최소 힙 성질 유지
void minHeapifyUp(MinHeap *heap, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && heap->nodes[index].priority < heap->nodes[parent].priority) {
        swapNodes(&heap->nodes[index], &heap->nodes[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

// minHeapifyDown: 루트 삭제 후 최소 힙 성질을 복구하기 위해 하향 조정
void minHeapifyDown(MinHeap *heap, int index) {
    int smallest = index;
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        if (left < heap->size && heap->nodes[left].priority < heap->nodes[smallest].priority) {
            smallest = left;
        }
        if (right < heap->size && heap->nodes[right].priority < heap->nodes[smallest].priority) {
            smallest = right;
        }
        if (smallest != index) {
            swapNodes(&heap->nodes[index], &heap->nodes[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

// insertMin: 최소 힙에 (data, priority) 쌍을 삽입
void insertMin(MinHeap *heap, int data, int priority) {
    if (heap->size == heap->capacity) {
        fprintf(stderr, "MinHeap 오버플로우! (%d, %d) 삽입 실패.\n", data, priority);
        return;
    }
    PQNode node;
    node.data = data;
    node.priority = priority;
    heap->nodes[heap->size] = node;
    minHeapifyUp(heap, heap->size);
    heap->size++;
    printf("MinHeap에 삽입: (data: %d, priority: %d)\n", data, priority);
}

// peekMin: 최소 힙의 루트 노드를 반환 (삭제 없이)
PQNode peekMin(MinHeap *heap) {
    if (heap->size == 0) {
        fprintf(stderr, "MinHeap이 비어 있습니다. 피크할 값이 없습니다.\n");
        PQNode errorNode = {-1, -1};
        return errorNode;
    }
    return heap->nodes[0];
}

// extractMin: 최소 힙의 루트 노드를 삭제 후 반환
PQNode extractMin(MinHeap *heap) {
    if (heap->size == 0) {
        fprintf(stderr, "MinHeap이 비어 있습니다. 삭제할 요소가 없습니다.\n");
        PQNode errorNode = {-1, -1};
        return errorNode;
    }
    PQNode minNode = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    minHeapifyDown(heap, 0);
    printf("MinHeap에서 추출: (data: %d, priority: %d)\n", minNode.data, minNode.priority);
    return minNode;
}

// printMinHeap: 최소 힙의 현재 상태를 출력
void printMinHeap(MinHeap *heap) {
    printf("MinHeap: ");
    for (int i = 0; i < heap->size; i++) {
        printf("(data: %d, priority: %d) ", heap->nodes[i].data, heap->nodes[i].priority);
    }
    printf("\n");
}

// freeMinHeap: 최소 힙에 할당된 메모리 해제
void freeMinHeap(MinHeap *heap) {
    free(heap->nodes);
    free(heap);
}

/* =======================
   메인 함수: 데모 실행
   ======================= */
int main(void) {
    // 최대 힙 데모
    printf("=== Max Heap Demo ===\n");
    MaxHeap *maxHeap = createMaxHeap(HEAP_CAPACITY);
    insertMax(maxHeap, 10, 2);
    insertMax(maxHeap, 20, 5);
    insertMax(maxHeap, 30, 1);
    insertMax(maxHeap, 40, 3);
    insertMax(maxHeap, 50, 4);
    printMaxHeap(maxHeap);

    PQNode maxPeek = peekMax(maxHeap);
    printf("MaxHeap Peek: (data: %d, priority: %d)\n", maxPeek.data, maxPeek.priority);

    extractMax(maxHeap);
    printMaxHeap(maxHeap);
    freeMaxHeap(maxHeap);

    printf("\n");

    // 최소 힙 데모
    printf("=== Min Heap Demo ===\n");
    MinHeap *minHeap = createMinHeap(HEAP_CAPACITY);
    insertMin(minHeap, 10, 2);
    insertMin(minHeap, 20, 5);
    insertMin(minHeap, 30, 1);
    insertMin(minHeap, 40, 3);
    insertMin(minHeap, 50, 4);
    printMinHeap(minHeap);

    PQNode minPeek = peekMin(minHeap);
    printf("MinHeap Peek: (data: %d, priority: %d)\n", minPeek.data, minPeek.priority);

    extractMin(minHeap);
    printMinHeap(minHeap);
    freeMinHeap(minHeap);

    return 0;
}