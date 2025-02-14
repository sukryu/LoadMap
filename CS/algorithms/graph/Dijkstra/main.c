/**
 * main.c
 *
 * 고도화된 다익스트라 알고리즘(Dijkstra's Algorithm) 구현 예제
 * - 이 파일은 인접 리스트로 표현된 가중치 그래프에서 단일 시작점으로부터 다른 모든 정점까지의 최단 경로를 찾는 구현체입니다.
 * - 우선순위 큐(최소 힙)를 사용하여 효율적으로 정점 선택 및 경로 갱신(relaxation)을 수행합니다.
 * - 실무 환경에서 바로 사용할 수 있도록 동적 메모리 관리, 에러 처리, 그리고 결과 출력 기능을 포함하여 작성되었습니다.
 *
 * 컴파일 예시: gcc -Wall -O2 dijkstra.c -o dijkstra
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*---------------- Data Structures for Graph ----------------*/

// Node structure for the adjacency list
typedef struct AdjListNode {
    int dest;                // Destination vertex
    int weight;              // Edge weight
    struct AdjListNode* next; // Pointer to next node
} AdjListNode;

// Adjacency list for each vertex
typedef struct AdjList {
    AdjListNode* head;       // Pointer to head node of list
} AdjList;

// Graph structure: represents a weighted directed graph
typedef struct Graph {
    int V;                   // Number of vertices
    AdjList* array;          // Array of adjacency lists
} Graph;

/*---------------- Graph Utility Functions ----------------*/

// Create a new adjacency list node
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

// Create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        fprintf(stderr, "메모리 할당 실패 (createGraph)\n");
        exit(EXIT_FAILURE);
    }
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    if (!graph->array) {
        fprintf(stderr, "메모리 할당 실패 (createGraph: array)\n");
        free(graph);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < V; i++) {
        graph->array[i].head = NULL;
    }
    return graph;
}

// Add a directed edge from src to dest with given weight
void addEdge(Graph* graph, int src, int dest, int weight) {
    // Add edge from src to dest
    AdjListNode* node = newAdjListNode(dest, weight);
    node->next = graph->array[src].head;
    graph->array[src].head = node;
}

/*---------------- Min Heap (Priority Queue) Data Structures ----------------*/

// Structure for a min heap node
typedef struct MinHeapNode {
    int v;      // Vertex number
    int dist;   // Distance value (key)
} MinHeapNode;

// Structure for a min heap
typedef struct MinHeap {
    int size;           // Current size of min heap
    int capacity;       // Capacity of min heap
    int* pos;           // Position of vertices in min heap array; pos[v] gives the index of vertex v
    MinHeapNode** array;// Array of pointers to min heap nodes
} MinHeap;

// Create a new min heap node for vertex v with distance dist
MinHeapNode* newMinHeapNode(int v, int dist) {
    MinHeapNode* heapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    if (!heapNode) {
        fprintf(stderr, "메모리 할당 실패 (newMinHeapNode)\n");
        exit(EXIT_FAILURE);
    }
    heapNode->v = v;
    heapNode->dist = dist;
    return heapNode;
}

// Create a min heap with given capacity
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

// Swap two min heap nodes
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Heapify at given index idx in min heap
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        // Update positions
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Check if min heap is empty
int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

// Extract the node with minimum distance value from min heap
MinHeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    MinHeapNode* root = minHeap->array[0];
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Update position of last node
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    minHeap->size--;
    minHeapify(minHeap, 0);

    return root;
}

// Decrease distance value of a given vertex v in min heap
void decreaseKey(MinHeap* minHeap, int v, int dist) {
    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist;

    // Fix the min heap property if violated
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

// Check if a given vertex v is in min heap
int isInMinHeap(MinHeap* minHeap, int v) {
    if (minHeap->pos[v] < minHeap->size)
        return 1;
    return 0;
}

/*---------------- Dijkstra's Algorithm Implementation ----------------*/

/**
 * dijkstra - 다익스트라 알고리즘을 사용하여, 주어진 시작 정점(src)에서 다른 모든 정점까지의 최단 경로 거리를 계산합니다.
 * @graph: 가중치 그래프 (인접 리스트 표현)
 * @src: 시작 정점 번호
 *
 * 반환값: 각 정점까지의 최단 거리를 담은 동적 배열.
 *         (각 배열 요소의 값이 해당 정점까지의 최단 경로 길이이며, 도달 불가능한 경우 INT_MAX)
 *         반환된 배열은 호출자가 free()로 메모리 해제해야 합니다.
 */
int* dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int* dist = (int*)malloc(V * sizeof(int));
    if (!dist) {
        fprintf(stderr, "메모리 할당 실패 (dijkstra: dist)\n");
        exit(EXIT_FAILURE);
    }

    // Create min heap
    MinHeap* minHeap = createMinHeap(V);

    // Initialize min heap with all vertices; set distance for src as 0 and others as INT_MAX
    for (int v = 0; v < V; v++) {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
    // Update src distance to 0
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = V;

    // Main loop of Dijkstra's algorithm
    while (!isEmpty(minHeap)) {
        // Extract vertex with minimum distance value
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
        free(minHeapNode);

        // Traverse all adjacent vertices of u and update distances
        AdjListNode* temp = graph->array[u].head;
        while (temp != NULL) {
            int v = temp->dest;

            // If v is still in min heap and distance through u is less than current distance of v
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&
                temp->weight + dist[u] < dist[v]) {
                dist[v] = temp->weight + dist[u];
                decreaseKey(minHeap, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    // Free min heap resources
    free(minHeap->pos);
    free(minHeap->array);
    free(minHeap);

    return dist;
}

/*---------------- Free Graph ----------------*/

/**
 * freeGraph - 그래프의 모든 메모리를 해제합니다.
 * @graph: 가중치 그래프 포인터
 *
 * 이 함수는 각 정점의 인접 리스트에 할당된 노드와 그래프 구조체 자체의 메모리를 해제합니다.
 */
void freeGraph(Graph* graph) {
    if (graph) {
        for (int i = 0; i < graph->V; i++) {
            AdjListNode* temp = graph->array[i].head;
            while (temp != NULL) {
                AdjListNode* next = temp->next;
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
 * main - 다익스트라 알고리즘 데모
 *
 * 이 함수는 예제 그래프를 생성하고, 여러 방향 에지를 추가한 후,
 * 시작 정점(src)에서부터 모든 정점까지의 최단 경로 거리를 계산하여 출력합니다.
 */
int main(void) {
    int V = 9;
    Graph* graph = createGraph(V);

    // 예제 그래프 에지 추가
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 8, 2);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 7, 8, 7);

    int src = 0;
    int* distances = dijkstra(graph, src);
    if (distances == NULL) {
        fprintf(stderr, "다익스트라 알고리즘 실행 실패\n");
        freeGraph(graph);
        exit(EXIT_FAILURE);
    }

    printf("정점 %d에서 시작하는 최단 경로 거리:\n", src);
    for (int i = 0; i < V; i++) {
        printf("정점 %d: ", i);
        if (distances[i] == INT_MAX)
            printf("도달 불가");
        else
            printf("%d", distances[i]);
        printf("\n");
    }

    free(distances);
    freeGraph(graph);
    return 0;
}