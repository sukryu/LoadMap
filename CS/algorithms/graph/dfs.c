/**
 * dfs.c
 *
 * 고도화된 깊이 우선 탐색(DFS) 알고리즘 구현 예제
 * - 이 파일은 인접 리스트로 표현된 그래프에서 깊이 우선 탐색(DFS)을 수행하는 구현체입니다.
 * - DFS 함수는 주어진 시작 정점으로부터 방문할 수 있는 모든 정점을 방문하며,
 *   재귀적 호출을 통해 그래프를 탐색합니다.
 * - 실무 환경에서 바로 사용할 수 있도록 동적 메모리 관리, 에러 처리 및 그래프 메모리 해제 기능을 포함하여 작성되었습니다.
 *
 * 컴파일 예시: gcc -Wall -O2 dfs.c -o dfs
 */

#include <stdio.h>
#include <stdlib.h>

// Node 구조체: 인접 리스트의 노드를 나타냄
typedef struct Node {
    int dest;              // 인접한 정점 번호
    struct Node* next;     // 다음 인접 노드 포인터
} Node;

// Graph 구조체: 그래프를 인접 리스트로 표현
typedef struct Graph {
    int V;               // 그래프의 정점 수
    Node** array;        // 각 정점의 인접 리스트 배열
} Graph;

/**
 * newNode - 새로운 노드를 생성하여 반환합니다.
 * @dest: 노드가 가리킬 인접 정점 번호
 *
 * 반환값: 동적 할당된 새로운 Node 포인터
 */
Node* newNode(int dest) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "메모리 할당 실패 (newNode)\n");
        exit(EXIT_FAILURE);
    }
    node->dest = dest;
    node->next = NULL;
    return node;
}

/**
 * createGraph - V개의 정점을 가진 그래프를 생성하고 초기화합니다.
 * @V: 그래프의 정점 수
 *
 * 반환값: 동적 할당된 Graph 포인터
 */
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        fprintf(stderr, "메모리 할당 실패 (createGraph)\n");
        exit(EXIT_FAILURE);
    }
    graph->V = V;
    graph->array = (Node**)malloc(V * sizeof(Node*));
    if (graph->array == NULL) {
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
 *
 * 이 함수는 src와 dest 간의 연결을 두 방향(양방향)으로 추가합니다.
 */
void addEdge(Graph* graph, int src, int dest) {
    // src -> dest 에지 추가
    Node* node = newNode(dest);
    node->next = graph->array[src];
    graph->array[src] = node;

    // dest -> src 에지 추가 (무방향 그래프)
    node = newNode(src);
    node->next = graph->array[dest];
    graph->array[dest] = node;
}

/**
 * DFSUtil - 재귀적 깊이 우선 탐색 함수
 * @graph: 그래프 포인터
 * @v: 현재 방문할 정점 번호
 * @visited: 정점 방문 여부를 저장한 배열
 *
 * 이 함수는 정점 v를 방문하고, v의 인접 정점 중 아직 방문하지 않은 정점들에 대해 재귀적으로 DFS를 수행합니다.
 */
void DFSUtil(Graph* graph, int v, int* visited) {
    // 정점 v 방문 처리 및 출력
    visited[v] = 1;
    printf("%d ", v);

    // v의 인접 리스트 순회
    Node* crawler = graph->array[v];
    while (crawler != NULL) {
        int adj = crawler->dest;
        if (!visited[adj])
            DFSUtil(graph, adj, visited);
        crawler = crawler->next;
    }
}

/**
 * DFS - 주어진 시작 정점으로부터 DFS 탐색을 수행합니다.
 * @graph: 그래프 포인터
 * @start: 시작 정점 번호
 *
 * 이 함수는 내부적으로 방문 배열을 초기화한 후, DFSUtil 함수를 호출하여
 * 모든 도달 가능한 정점을 탐색하고, 탐색 결과를 출력합니다.
 */
void DFS(Graph* graph, int start) {
    int* visited = (int*)calloc(graph->V, sizeof(int));
    if (visited == NULL) {
        fprintf(stderr, "메모리 할당 실패 (DFS: visited)\n");
        exit(EXIT_FAILURE);
    }

    printf("DFS 시작 정점 %d: ", start);
    DFSUtil(graph, start, visited);
    printf("\n");

    free(visited);
}

/**
 * freeGraph - 그래프의 모든 메모리를 해제합니다.
 * @graph: 그래프 포인터
 *
 * 이 함수는 그래프의 각 정점에 할당된 인접 리스트 노드와, 그래프 구조체 자체의 메모리를 해제합니다.
 */
void freeGraph(Graph* graph) {
    if (graph) {
        for (int i = 0; i < graph->V; i++) {
            Node* crawler = graph->array[i];
            while (crawler != NULL) {
                Node* temp = crawler;
                crawler = crawler->next;
                free(temp);
            }
        }
        free(graph->array);
        free(graph);
    }
}

/**
 * main - DFS 알고리즘 데모
 *
 * 이 함수는 6개의 정점을 가진 예제 그래프를 생성하고, 무방향 에지를 추가한 후,
 * 시작 정점 0에서부터 DFS 탐색을 수행하여 결과를 출력합니다.
 */
int main(void) {
    int V = 6;
    Graph* graph = createGraph(V);
    
    // 예제 에지 추가 (무방향 그래프)
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);
    
    // DFS 탐색 실행: 시작 정점 0
    DFS(graph, 0);
    
    // 그래프 메모리 해제
    freeGraph(graph);
    
    return 0;
}
