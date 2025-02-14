/**
 * main.c
 *
 * 고도화된 프림 알고리즘(Prim's Algorithm) 구현 예제
 * - 이 파일은 가중치 무방향 그래프를 인접 리스트로 표현하고,
 *   최소 신장 트리(MST)를 프림 알고리즘을 통해 구성하는 구현체입니다.
 * - 우선순위 큐(최소 힙)를 사용하여 MST에 아직 포함되지 않은 정점들 중 최소 간선 가중치로 연결되는 정점을 효율적으로 선택합니다.
 * - 각 정점에 대한 최소 간선 가중치와 부모 정보를 기록하여 MST를 구성하며,
 *   최종적으로 MST의 간선 정보와 총 가중치를 출력합니다.
 *
 * 컴파일 예시: gcc -Wall -O2 prim.c -o prim
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

/*---------------- Data Structures for Graph ----------------*/

// 인접 리스트의 노드 구조체: 정점 u에서 정점 v로 가는 간선을 나타냄
typedef struct AdjListNode {
    int dest;                  // 도착 정점 번호
    int weight;                // 간선 가중치
    struct AdjListNode *next;  // 다음 노드 포인터
} AdjListNode;

// 그래프 구조체: V개의 정점을 가지며, 각 정점은 인접 리스트(AdjListNode*)로 표현
typedef struct Graph {
    int V;                  // 정점의 수
    AdjListNode **array;    // 각 정점의 인접 리스트 배열
} Graph;

/**
 * newAdjListNode - 새로운 인접 리스트 노드를 생성합니다.
 * @dest: 도착 정점 번호
 * @weight: 간선 가중치
 *
 * 반환값: 동적 할당된 AdjListNode 포인터
 */
AdjListNode* newAdjListNode(int dest, int weight) {
    AdjListNode* node = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (!node) {
        fprintf(stderr, "메모리 할당 실패 (newAdjListNode)\n");
        exit(EXIT_FAILURE);
    }
    node->dest = dest;
    node->weight = weight;
    node->next = NULL;
    return node;
}

/**
 * createGraph - V개의 정점을 가진 그래프를 생성하고 초기화합니다.
 * @V: 정점의 수
 *
 * 반환값: 동적 할당된 Graph 포인터
 */
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        fprintf(stderr, "메모리 할당 실패 (createGraph)\n");
        exit(EXIT_FAILURE);
    }
    graph->V = V;
    graph->array = (AdjListNode**)malloc(V * sizeof(AdjListNode*));
    if (!graph->array) {
        fprintf(stderr, "메모리 할당 실패 (createGraph: array)\n");
        free(graph);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < V; i++)
        graph->array[i] = NULL;
    return graph;
}

/**
 * addEdge - 무방향 그래프에서 src와 dest 사이의 에지를 추가합니다.
 * @graph: 그래프 포인터
 * @src: 출발 정점 번호
 * @dest: 도착 정점 번호
 * @weight: 간선 가중치
 *
 * 이 함수는 src->dest 및 dest->src 에지를 모두 추가합니다.
 */
void addEdge(Graph* graph, int src, int dest, int weight) {
    // src -> dest
    AdjListNode* node = newAdjListNode(dest, weight);
    node->next = graph->array[src];
    graph->array[src] = node;

    // dest -> src (무방향 그래프)
    node = newAdjListNode(src, weight);
    node->next = graph->array[dest];
    graph->array[dest] = node;
}

/*---------------- Min Heap (Priority Queue) for Prim's Algorithm ----------------*/

// 최소 힙 노드 구조체: 정점 번호와 현재 키(최소 간선 가중치)를 저장
typedef struct MinHeapNode {
    int v;    // 정점 번호
    int key;  // 정점까지의 현재 최소 가중치
} MinHeapNode;

// 최소 힙 구조체
typedef struct MinHeap {
    int size;           // 현재 힙에 저장된 노드 수
    int capacity;       // 힙의 최대 용량
    int *pos;           // 정점의 위치 배열: pos[v]는 힙 배열 내에서 정점 v의 인덱스
    MinHeapNode **array; // 최소 힙 노드 포인터 배열
} MinHeap;

/**
 * newMinHeapNode - 새로운 최소 힙 노드를 생성합니다.
 * @v: 정점 번호
 * @key: 정점까지의 키(최소 가중치)
 *
 * 반환값: 동적 할당된 MinHeapNode 포인터
 */
MinHeapNode* newMinHeapNode(int v, int key) {
    MinHeapNode* heapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    if (!heapNode) {
        fprintf(stderr, "메모리 할당 실패 (newMinHeapNode)\n");
        exit(EXIT_FAILURE);
    }
    heapNode->v = v;
    heapNode->key = key;
    return heapNode;
}

/**
 * createMinHeap - 주어진 용량의 최소 힙을 생성합니다.
 * @capacity: 최소 힙의 최대 용량
 *
 * 반환값: 동적 할당된 MinHeap 포인터
 */
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!minHeap) {
        fprintf(stderr, "메모리 할당 실패 (createMinHeap)\n");
        exit(EXIT_FAILURE);
    }
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    if (!minHeap->pos) {
        fprintf(stderr, "메모리 할당 실패 (createMinHeap: pos)\n");
        free(minHeap);
        exit(EXIT_FAILURE);
    }
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    if (!minHeap->array) {
        fprintf(stderr, "메모리 할당 실패 (createMinHeap: array)\n");
        free(minHeap->pos);
        free(minHeap);
        exit(EXIT_FAILURE);
    }
    return minHeap;
}

/**
 * swapMinHeapNode - 두 최소 힙 노드 포인터를 교환합니다.
 */
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

/**
 * minHeapify - 인덱스 idx에서 최소 힙 속성을 유지하도록 힙을 재구성합니다.
 * @minHeap: 최소 힙 포인터
 * @idx: 힙 배열 내에서의 현재 인덱스
 */
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->key < minHeap->array[smallest]->key)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->key < minHeap->array[smallest]->key)
        smallest = right;

    if (smallest != idx) {
        // Update positions
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

/**
 * isEmpty - 최소 힙이 비어있는지 검사합니다.
 * @minHeap: 최소 힙 포인터
 *
 * 반환값: 최소 힙의 크기가 0이면 1, 아니면 0
 */
int isEmpty(MinHeap* minHeap) {
    return (minHeap->size == 0);
}

/**
 * extractMin - 최소 힙에서 최소 키 값을 가진 노드를 추출합니다.
 * @minHeap: 최소 힙 포인터
 *
 * 반환값: 추출된 최소 힙 노드 포인터
 */
MinHeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    MinHeapNode* root = minHeap->array[0];
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Update positions
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    minHeap->size--;
    minHeapify(minHeap, 0);

    return root;
}

/**
 * decreaseKey - 주어진 정점 v의 키 값을 새 값으로 감소시키고, 힙 속성을 복원합니다.
 * @minHeap: 최소 힙 포인터
 * @v: 정점 번호
 * @key: 새 키 값
 */
void decreaseKey(MinHeap* minHeap, int v, int key) {
    int i = minHeap->pos[v];
    minHeap->array[i]->key = key;
    while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key) {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

/**
 * isInMinHeap - 정점 v가 최소 힙에 있는지 검사합니다.
 * @minHeap: 최소 힙 포인터
 * @v: 정점 번호
 *
 * 반환값: 정점 v가 최소 힙에 있으면 1, 그렇지 않으면 0
 */
int isInMinHeap(MinHeap* minHeap, int v) {
    if (minHeap->pos[v] < minHeap->size)
        return 1;
    return 0;
}

/*---------------- Prim's Algorithm Implementation ----------------*/

/**
 * primMST - 프림 알고리즘을 사용하여 최소 신장 트리(MST)를 구성합니다.
 * @graph: 가중치 무방향 그래프 (인접 리스트 표현)
 *
 * 이 함수는 각 정점의 최소 간선 가중치와 부모 정보를 기록하여 MST를 구성하고,
 * MST에 포함된 간선 정보를 출력하며 총 가중치를 계산합니다.
 *
 * 주의: 기존 DFS/BFS에서와 달리, 그래프 구조체의 인접 리스트는 단순히 각 정점의 첫 번째 인접 노드를 가리키는 포인터입니다.
 *       따라서 인접 리스트의 순회를 위해서는 "graph->array[u]"를 사용해야 하며, ".head"와 같이 접근하지 않습니다.
 */
void primMST(Graph* graph) {
    int V = graph->V;
    int *parent = (int*) malloc(V * sizeof(int));  // MST 구성 결과: 각 정점의 부모
    int *key = (int*) malloc(V * sizeof(int));       // 각 정점까지의 최소 가중치
    int *inMST = (int*) calloc(V, sizeof(int));       // MST에 포함된 정점 여부

    if (!parent || !key || !inMST) {
        fprintf(stderr, "메모리 할당 실패 (primMST: parent/key/inMST)\n");
        exit(EXIT_FAILURE);
    }

    // 최소 힙 생성
    MinHeap *minHeap = createMinHeap(V);

    // 초기화: 모든 정점의 키를 INF, 부모를 -1로 설정; 시작 정점 0의 키는 0
    for (int v = 0; v < V; v++) {
        parent[v] = -1;
        key[v] = INF;
        minHeap->array[v] = newMinHeapNode(v, key[v]);
        minHeap->pos[v] = v;
    }
    key[0] = 0;
    decreaseKey(minHeap, 0, key[0]);
    minHeap->size = V;

    // 프림 알고리즘 실행: 최소 힙이 빌 때까지 반복
    while (!isEmpty(minHeap)) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
        free(minHeapNode);
        inMST[u] = 1;

        // u의 모든 인접 정점을 검사하며, 아직 MST에 포함되지 않았고,
        // u를 통해 접근하는 것이 더 낮은 가중치를 제공하는 경우 업데이트
        AdjListNode *temp = graph->array[u]; // 수정된 부분: graph->array[u]는 바로 인접 리스트의 첫 노드를 가리킵니다.
        while (temp != NULL) {
            int v = temp->dest;
            if (!inMST[v] && temp->weight < key[v]) {
                key[v] = temp->weight;
                parent[v] = u;
                decreaseKey(minHeap, v, key[v]);
            }
            temp = temp->next;
        }
    }

    // MST 결과 출력
    int totalWeight = 0;
    printf("MST 간선 및 가중치:\n");
    for (int i = 1; i < V; i++) {
        if (parent[i] != -1) {
            printf("%d - %d (가중치 %d)\n", parent[i], i, key[i]);
            totalWeight += key[i];
        }
    }
    printf("MST 총 가중치: %d\n", totalWeight);

    // 동적 메모리 해제
    free(parent);
    free(key);
    free(inMST);
    free(minHeap->pos);
    // free remaining nodes in the heap array
    // (이미 최소 힙이 소진되어 있으므로, minHeap->size is 0)
    free(minHeap->array);
    free(minHeap);
}

/*---------------- Free Graph ----------------*/

/**
 * freeGraph - 그래프에 할당된 모든 메모리를 해제합니다.
 * @graph: 가중치 무방향 그래프 포인터
 *
 * 이 함수는 각 정점의 인접 리스트 노드와, 그래프 구조체 자체의 메모리를 해제합니다.
 */
void freeGraph(Graph* graph) {
    if (graph) {
        for (int i = 0; i < graph->V; i++) {
            AdjListNode *temp = graph->array[i];
            while (temp != NULL) {
                AdjListNode *next = temp->next;
                free(temp);
                temp = next;
            }
        }
        free(graph->array);
        free(graph);
    }
}

/*---------------- main 함수 (데모) ----------------*/

/**
 * main - 프림 알고리즘 데모
 *
 * 이 함수는 예제 그래프를 생성하고, 에지를 추가한 후,
 * 프림 알고리즘을 통해 최소 신장 트리를 구성하여 결과를 출력합니다.
 */
int main(void) {
    int V = 5;
    Graph* graph = createGraph(V);

    // 예제 에지 추가 (무방향 그래프)
    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 3, 6);
    addEdge(graph, 1, 2, 3);
    addEdge(graph, 1, 3, 8);
    addEdge(graph, 1, 4, 5);
    addEdge(graph, 2, 4, 7);
    addEdge(graph, 3, 4, 9);

    primMST(graph);

    freeGraph(graph);
    return 0;
}
