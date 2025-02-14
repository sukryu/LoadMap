/**
 * hopcroft_karp.c
 *
 * 고도화된 Hopcroft-Karp 알고리즘 구현 예제
 * - 이 파일은 이분 그래프(Bipartite Graph)에서 최대 매칭(Maximum Matching)을 찾기 위한 Hopcroft-Karp 알고리즘을 구현합니다.
 * - 이분 그래프는 두 개의 독립된 정점 집합 U와 V로 구성되며, 모든 간선은 U에서 V로 연결됩니다.
 * - 알고리즘은 BFS를 통해 레벨 그래프를 구성하고, DFS를 통해 증강 경로(augmenting path)를 찾는 과정을 반복하여 최대 매칭을 구합니다.
 *
 * 주요 단계:
 *   1. BFS: U의 각 정점에 대해, 아직 매칭되지 않은 정점은 레벨 0으로 설정하고, BFS를 통해 각 정점의 레벨을 계산합니다.
 *      이때, 매칭되지 않은 정점에 도달하면 'NIL' (매칭 없음) 노드에 도달한 것으로 간주합니다.
 *   2. DFS: BFS 단계에서 계산된 레벨 정보를 이용하여 증강 경로를 찾습니다.
 *   3. 증강 경로가 더 이상 없을 때까지 위 과정을 반복합니다.
 *
 * 반환값: 최대 매칭의 크기와, 각 U와 V 정점의 매칭 정보를 담은 배열
 *
 * 컴파일 예시: gcc -Wall -O2 hopcroft_karp.c -o hopcroft_karp
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 정의: INF와 NIL
#define INF INT_MAX
#define NIL -1

/*---------------- Data Structures ----------------*/

// BipartiteGraph 구조체: U 집합과 V 집합의 정점 수, 그리고 U 집합에서 V 집합으로의 간선 정보를 저장합니다.
typedef struct BipartiteGraph {
    int n1;        // U 집합의 정점 수
    int n2;        // V 집합의 정점 수
    int **adj;     // U 집합의 각 정점에 대한 인접 리스트 배열 (동적 배열, 각 원소는 V 집합의 정점 번호)
    int *adjSize;  // U 집합의 각 정점의 인접 리스트 크기
} BipartiteGraph;

/*---------------- Queue Utility Functions for BFS ----------------*/

// Simple queue implementation for integers
typedef struct Queue {
    int *data;
    int front;
    int rear;
    int capacity;
} Queue;

// Create a new queue with given capacity
Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q) {
        fprintf(stderr, "메모리 할당 실패 (createQueue)\n");
        exit(EXIT_FAILURE);
    }
    q->data = (int*)malloc(capacity * sizeof(int));
    if (!q->data) {
        fprintf(stderr, "메모리 할당 실패 (createQueue data)\n");
        free(q);
        exit(EXIT_FAILURE);
    }
    q->front = 0;
    q->rear = 0;
    q->capacity = capacity;
    return q;
}

// Enqueue an element
void enqueue(Queue* q, int value) {
    if (q->rear == q->capacity) {
        q->capacity *= 2;
        int *newData = (int*)realloc(q->data, q->capacity * sizeof(int));
        if (!newData) {
            fprintf(stderr, "메모리 재할당 실패 (enqueue)\n");
            free(q->data);
            free(q);
            exit(EXIT_FAILURE);
        }
        q->data = newData;
    }
    q->data[q->rear++] = value;
}

// Dequeue an element and return it
int dequeue(Queue* q) {
    if (q->front == q->rear)
        return NIL;
    return q->data[q->front++];
}

// Check if queue is empty
int isQueueEmpty(Queue* q) {
    return (q->front == q->rear);
}

// Free queue memory
void freeQueue(Queue* q) {
    if (q) {
        free(q->data);
        free(q);
    }
}

/*---------------- Hopcroft-Karp Algorithm Functions ----------------*/

/**
 * bfsHK - BFS 단계: 레벨 그래프를 구성합니다.
 * @graph: 이분 그래프 포인터
 * @pairU: U 집합의 매칭 배열 (크기: n1), pairU[u]는 u와 매칭된 V 정점 번호, 매칭되지 않았으면 NIL
 * @pairV: V 집합의 매칭 배열 (크기: n2), pairV[v]는 v와 매칭된 U 정점 번호, 매칭되지 않았으면 NIL
 * @dist: U 집합의 각 정점의 레벨을 저장하는 배열 (크기: n1)
 *
 * 반환값: 매칭 가능 경로가 존재하면 1, 아니면 0.
 *
 * 이 함수는 U 집합의 각 정점을 시작으로, 아직 매칭되지 않은 정점들은 레벨 0으로 설정한 후 BFS를 수행하여,
 * 각 정점의 최단 거리(레벨)를 계산합니다.
 */
int bfsHK(BipartiteGraph* graph, int *pairU, int *pairV, int *dist) {
    int n1 = graph->n1;
    Queue* q = createQueue(n1);
    
    // U 집합의 모든 정점에 대해 초기화: 매칭되지 않은 정점은 레벨 0, 나머지는 INF
    for (int u = 0; u < n1; u++) {
        if (pairU[u] == NIL) {
            dist[u] = 0;
            enqueue(q, u);
        } else {
            dist[u] = INF;
        }
    }
    
    int foundPath = 0;
    // BFS 수행: 큐가 빌 때까지
    while (!isQueueEmpty(q)) {
        int u = dequeue(q);
        // if we have reached an unmatched vertex, we don't go further from here
        if (dist[u] < INF) {
            // For each v in adj[u]
            for (int i = 0; i < graph->adjSize[u]; i++) {
                int v = graph->adj[u][i];
                // If v is unmatched, we have reached NIL (dummy node)
                if (pairV[v] == NIL) {
                    foundPath = 1;
                } else if (dist[pairV[v]] == INF) {
                    // Otherwise, update distance for the U vertex matched with v
                    dist[pairV[v]] = dist[u] + 1;
                    enqueue(q, pairV[v]);
                }
            }
        }
    }
    freeQueue(q);
    return foundPath;
}

/**
 * dfsHK - DFS 단계: BFS로 구성된 레벨 그래프를 따라 증강 경로를 찾습니다.
 * @graph: 이분 그래프 포인터
 * @u: 현재 U 집합의 정점 번호
 * @pairU: U 집합 매칭 배열
 * @pairV: V 집합 매칭 배열
 * @dist: U 집합의 레벨 배열
 *
 * 반환값: 증강 경로가 존재하면 1, 아니면 0.
 *
 * 이 함수는 u에서 시작하여, 증강 경로를 찾으면 매칭 배열을 업데이트합니다.
 */
int dfsHK(BipartiteGraph* graph, int u, int *pairU, int *pairV, int *dist) {
    if (u != NIL) {
        for (int i = 0; i < graph->adjSize[u]; i++) {
            int v = graph->adj[u][i];
            // If v is unmatched or if the next vertex in matching can be further explored
            if (pairV[v] == NIL || (dist[pairV[v]] == dist[u] + 1 && dfsHK(graph, pairV[v], pairU, pairV, dist))) {
                pairV[v] = u;
                pairU[u] = v;
                return 1;
            }
        }
        // If no augmenting path starting from u, set distance to INF to block it
        dist[u] = INF;
        return 0;
    }
    return 1;
}

/**
 * hopcroftKarp - Hopcroft-Karp 알고리즘을 사용하여 이분 그래프의 최대 매칭을 계산합니다.
 * @graph: 이분 그래프 포인터
 *
 * 반환값: 최대 매칭의 크기 (정수)
 *
 * 이 함수는 U와 V 집합의 매칭 정보를 동적 배열 pairU와 pairV에 저장한 후,
 * BFS와 DFS를 반복적으로 수행하여 증강 경로를 찾고, 매칭을 증가시킵니다.
 */
int hopcroftKarp(BipartiteGraph* graph) {
    int n1 = graph->n1;
    int n2 = graph->n2;
    
    // pairU[u]는 u와 매칭된 v, pairV[v]는 v와 매칭된 u (매칭되지 않은 경우 NIL)
    int *pairU = (int*)malloc(n1 * sizeof(int));
    int *pairV = (int*)malloc(n2 * sizeof(int));
    int *dist = (int*)malloc(n1 * sizeof(int));
    if (!pairU || !pairV || !dist) {
        fprintf(stderr, "메모리 할당 실패 (hopcroftKarp)\n");
        exit(EXIT_FAILURE);
    }
    
    for (int u = 0; u < n1; u++)
        pairU[u] = NIL;
    for (int v = 0; v < n2; v++)
        pairV[v] = NIL;
    
    int matching = 0;
    
    // 반복: 증강 경로가 존재하는 동안
    while (bfsHK(graph, pairU, pairV, dist)) {
        for (int u = 0; u < n1; u++) {
            if (pairU[u] == NIL && dfsHK(graph, u, pairU, pairV, dist))
                matching++;
        }
    }
    
    // 해제
    free(pairU);
    free(pairV);
    free(dist);
    
    return matching;
}

/*---------------- Bipartite Graph Utility Functions ----------------*/

/**
 * createBipartiteGraph - 이분 그래프를 생성합니다.
 * @n1: U 집합의 정점 수
 * @n2: V 집합의 정점 수
 *
 * 반환값: 동적 할당된 BipartiteGraph 포인터
 */
BipartiteGraph* createBipartiteGraph(int n1, int n2) {
    BipartiteGraph* graph = (BipartiteGraph*)malloc(sizeof(BipartiteGraph));
    if (!graph) {
        fprintf(stderr, "메모리 할당 실패 (createBipartiteGraph)\n");
        exit(EXIT_FAILURE);
    }
    graph->n1 = n1;
    graph->n2 = n2;
    // U 집합에 대한 인접 리스트 배열 할당
    graph->adj = (int**)malloc(n1 * sizeof(int*));
    graph->adjSize = (int*)malloc(n1 * sizeof(int));
    if (!graph->adj || !graph->adjSize) {
        fprintf(stderr, "메모리 할당 실패 (createBipartiteGraph: adj or adjSize)\n");
        exit(EXIT_FAILURE);
    }
    // 초기에는 각 인접 리스트 크기를 0으로 설정
    for (int i = 0; i < n1; i++) {
        graph->adj[i] = NULL;
        graph->adjSize[i] = 0;
    }
    return graph;
}

/**
 * addBipartiteEdge - 이분 그래프에서 U의 정점 u와 V의 정점 v를 연결하는 간선을 추가합니다.
 * @graph: BipartiteGraph 포인터
 * @u: U 집합의 정점 번호 (0 ≤ u < n1)
 * @v: V 집합의 정점 번호 (0 ≤ v < n2)
 *
 * 이 함수는 동적 배열을 확장하면서, U 집합의 정점 u의 인접 리스트에 v를 추가합니다.
 */
void addBipartiteEdge(BipartiteGraph* graph, int u, int v) {
    // U 집합의 정점 u에 대해, 간선 추가를 위한 동적 배열 확장
    int newSize = graph->adjSize[u] + 1;
    int* newAdj = (int*)realloc(graph->adj[u], newSize * sizeof(int));
    if (!newAdj) {
        fprintf(stderr, "메모리 재할당 실패 (addBipartiteEdge)\n");
        exit(EXIT_FAILURE);
    }
    graph->adj[u] = newAdj;
    graph->adj[u][graph->adjSize[u]] = v; // 간선 추가 (v는 V 집합의 정점)
    graph->adjSize[u] = newSize;
}

/**
 * freeBipartiteGraph - 이분 그래프에 할당된 모든 메모리를 해제합니다.
 * @graph: BipartiteGraph 포인터
 */
void freeBipartiteGraph(BipartiteGraph* graph) {
    if (graph) {
        for (int i = 0; i < graph->n1; i++) {
            free(graph->adj[i]);
        }
        free(graph->adj);
        free(graph->adjSize);
        free(graph);
    }
}

/*---------------- main 함수 (데모) ----------------*/
/**
 * main - Hopcroft-Karp 알고리즘 데모
 *
 * 이 함수는 예제 이분 그래프를 생성하고, U 집합과 V 집합의 정점들 사이에 간선을 추가한 후,
 * Hopcroft-Karp 알고리즘을 사용하여 최대 매칭의 크기를 계산하여 출력합니다.
 */
int main(void) {
    // 예제: U 집합에 4개의 정점, V 집합에 4개의 정점
    BipartiteGraph* graph = createBipartiteGraph(4, 4);
    
    // 간선 추가 예제 (U에서 V로)
    // U0: V0, V1
    addBipartiteEdge(graph, 0, 0);
    addBipartiteEdge(graph, 0, 1);
    // U1: V0, V2
    addBipartiteEdge(graph, 1, 0);
    addBipartiteEdge(graph, 1, 2);
    // U2: V1, V3
    addBipartiteEdge(graph, 2, 1);
    addBipartiteEdge(graph, 2, 3);
    // U3: V2, V3
    addBipartiteEdge(graph, 3, 2);
    addBipartiteEdge(graph, 3, 3);
    
    int maxMatching = hopcroftKarp(graph);
    printf("최대 매칭의 크기: %d\n", maxMatching);
    
    freeBipartiteGraph(graph);
    return 0;
}
