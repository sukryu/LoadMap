/*
 * main.c
 *
 * 이 파일은 그래프 자료구조를 인접 리스트(Adjacency List) 방식으로 구현하고,
 * 여러 알고리즘(깊이 우선 탐색(DFS), 너비 우선 탐색(BFS), 그리고 다익스트라(Dijkstra) 최단 경로 알고리즘)을
 * 시연하는 예제입니다.
 *
 * 구현 특징:
 * - 동적 메모리를 활용하여 정점과 간선들을 효율적으로 관리합니다.
 * - 인접 리스트를 사용하여 희소 그래프에서도 메모리 효율적으로 동작합니다.
 * - DFS와 BFS를 통해 그래프 탐색을 시연하며, 다익스트라 알고리즘을 통해 가중치 그래프에서 최단 경로를 구합니다.
 * - 모든 함수는 실무에서도 활용할 수 있도록 에러 처리 및 메모리 관리에 신경 썼습니다.
 *
 * 참고: 실제 환경에서는 입력 검증, 동적 확장, 스레드 안전성 등 추가적인 최적화가 필요할 수 있습니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// --------------------
// 자료구조 정의
// --------------------

// 인접 리스트 노드: 간선의 도착 정점과 가중치, 다음 노드에 대한 포인터
typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode *next;
} AdjListNode;

// 인접 리스트: 각 정점의 인접 노드 목록의 헤드 포인터
typedef struct AdjList {
    AdjListNode *head;
} AdjList;

// 그래프 구조체: 정점 수와 인접 리스트 배열
typedef struct Graph {
    int V;           // 정점의 개수
    AdjList *array;  // 각 정점의 인접 리스트 배열
} Graph;

// --------------------
// 함수 프로토타입
// --------------------
AdjListNode* newAdjListNode(int dest, int weight);
Graph* createGraph(int V);
void addEdge(Graph *graph, int src, int dest, int weight);
void printGraph(Graph *graph);
void BFS(Graph *graph, int start);
void DFSUtil(Graph *graph, int v, bool visited[]);
void DFS(Graph *graph, int start);
void dijkstra(Graph *graph, int src);
void freeGraph(Graph *graph);

// --------------------
// 함수 구현
// --------------------

// 새로운 인접 리스트 노드 생성
AdjListNode* newAdjListNode(int dest, int weight) {
    AdjListNode *newNode = (AdjListNode*) malloc(sizeof(AdjListNode));
    if (!newNode) {
        fprintf(stderr, "메모리 할당 실패 in newAdjListNode.\n");
        exit(EXIT_FAILURE);
    }
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// 그래프 생성: 정점 수 V를 입력 받아 인접 리스트 배열을 초기화합니다.
Graph* createGraph(int V) {
    Graph *graph = (Graph*) malloc(sizeof(Graph));
    if (!graph) {
        fprintf(stderr, "메모리 할당 실패 in createGraph.\n");
        exit(EXIT_FAILURE);
    }
    graph->V = V;
    graph->array = (AdjList*) malloc(V * sizeof(AdjList));
    if (!graph->array) {
        fprintf(stderr, "메모리 할당 실패 for graph->array.\n");
        free(graph);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < V; i++)
        graph->array[i].head = NULL;
    return graph;
}

// 간선 추가: src와 dest 사이의 간선을 weight와 함께 추가 (무향 그래프)
void addEdge(Graph *graph, int src, int dest, int weight) {
    // src -> dest 간선 추가
    AdjListNode *newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    
    // 무향 그래프라면 dest -> src 간선도 추가
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// 그래프 출력: 각 정점의 인접 리스트를 출력합니다.
void printGraph(Graph *graph) {
    for (int v = 0; v < graph->V; v++) {
        AdjListNode *pCrawl = graph->array[v].head;
        printf("정점 %d의 인접 리스트: ", v);
        while (pCrawl) {
            printf("-> (정점: %d, 가중치: %d) ", pCrawl->dest, pCrawl->weight);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

// BFS (너비 우선 탐색): 시작 정점부터 탐색하며 방문 순서를 출력합니다.
void BFS(Graph *graph, int start) {
    bool *visited = (bool*) calloc(graph->V, sizeof(bool));
    if (!visited) {
        fprintf(stderr, "메모리 할당 실패 in BFS.\n");
        exit(EXIT_FAILURE);
    }
    
    int *queue = (int*) malloc(graph->V * sizeof(int));
    if (!queue) {
        fprintf(stderr, "메모리 할당 실패 for BFS queue.\n");
        free(visited);
        exit(EXIT_FAILURE);
    }
    
    int front = 0, rear = 0;
    visited[start] = true;
    queue[rear++] = start;
    
    printf("BFS 탐색 시작 (정점 %d): ", start);
    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);
        
        AdjListNode *adjNode = graph->array[current].head;
        while (adjNode) {
            if (!visited[adjNode->dest]) {
                visited[adjNode->dest] = true;
                queue[rear++] = adjNode->dest;
            }
            adjNode = adjNode->next;
        }
    }
    printf("\n");
    free(queue);
    free(visited);
}

// DFS 재귀 함수: 현재 정점 v에서 시작하여 깊이 우선 탐색을 수행합니다.
void DFSUtil(Graph *graph, int v, bool visited[]) {
    visited[v] = true;
    printf("%d ", v);
    AdjListNode *adjNode = graph->array[v].head;
    while (adjNode) {
        if (!visited[adjNode->dest])
            DFSUtil(graph, adjNode->dest, visited);
        adjNode = adjNode->next;
    }
}

// DFS (깊이 우선 탐색): 시작 정점부터 탐색하며 방문 순서를 출력합니다.
void DFS(Graph *graph, int start) {
    bool *visited = (bool*) calloc(graph->V, sizeof(bool));
    if (!visited) {
        fprintf(stderr, "메모리 할당 실패 in DFS.\n");
        exit(EXIT_FAILURE);
    }
    printf("DFS 탐색 시작 (정점 %d): ", start);
    DFSUtil(graph, start, visited);
    printf("\n");
    free(visited);
}

// 다익스트라 알고리즘: 가중치 그래프에서 src로부터의 최단 거리를 계산합니다.
void dijkstra(Graph *graph, int src) {
    int V = graph->V;
    int *dist = (int*) malloc(V * sizeof(int));
    bool *sptSet = (bool*) calloc(V, sizeof(bool));
    if (!dist || !sptSet) {
        fprintf(stderr, "메모리 할당 실패 in dijkstra.\n");
        exit(EXIT_FAILURE);
    }
    
    // 모든 정점에 대해 초기 거리를 무한대로 설정
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src] = 0;
    
    // 최단 경로 집합에 포함되지 않은 정점 중 최소 거리를 가진 정점을 선택
    for (int count = 0; count < V - 1; count++) {
        int min = INT_MAX, u = -1;
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }
        if(u == -1) break; // 연결된 정점이 없음
        
        sptSet[u] = true;
        
        // u와 인접한 정점들의 거리를 업데이트
        AdjListNode *adjNode = graph->array[u].head;
        while (adjNode) {
            int v = adjNode->dest;
            if (!sptSet[v] && dist[u] != INT_MAX &&
                dist[u] + adjNode->weight < dist[v]) {
                dist[v] = dist[u] + adjNode->weight;
            }
            adjNode = adjNode->next;
        }
    }
    
    // 결과 출력: src로부터 모든 정점까지의 최단 거리
    printf("다익스트라 알고리즘 (출발 정점: %d):\n", src);
    for (int i = 0; i < V; i++) {
        printf("정점 %d까지의 최단 거리: %d\n", i, dist[i] == INT_MAX ? -1 : dist[i]);
    }
    
    free(dist);
    free(sptSet);
}

// 그래프 메모리 해제: 각 인접 리스트 노드와 그래프 구조체를 재귀적으로 해제합니다.
void freeGraph(Graph *graph) {
    if (!graph)
        return;
    for (int v = 0; v < graph->V; v++) {
        AdjListNode *node = graph->array[v].head;
        while (node) {
            AdjListNode *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
}

// --------------------
// main 함수: 데모 실행
// --------------------
int main(void) {
    // 예제: 6개의 정점을 가진 그래프 생성
    int V = 6;
    Graph *graph = createGraph(V);
    
    // 간선 추가 (무향 가중치 그래프)
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 2, 1);
    addEdge(graph, 2, 1, 2);
    addEdge(graph, 1, 3, 1);
    addEdge(graph, 2, 3, 5);
    addEdge(graph, 3, 4, 3);
    addEdge(graph, 4, 5, 1);
    addEdge(graph, 3, 5, 6);
    
    printf("그래프 인접 리스트:\n");
    printGraph(graph);
    printf("\n");
    
    // BFS 데모
    BFS(graph, 0);
    
    // DFS 데모
    DFS(graph, 0);
    
    // 다익스트라 최단 경로 데모 (출발 정점 0)
    dijkstra(graph, 0);
    
    // 그래프 메모리 해제
    freeGraph(graph);
    printf("\n그래프 메모리 해제 완료.\n");
    
    return 0;
}