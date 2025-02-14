/**
 * dinic.c
 *
 * 고도화된 Dinic 알고리즘 구현 예제
 * - 이 파일은 인접 리스트로 표현된 가중치 방향 그래프에서 소스(Source)에서 싱크(Sink)까지의 최대 유량(Maximum Flow)을 계산하는 Dinic 알고리즘을 구현합니다.
 * - Dinic 알고리즘은 다음 단계로 동작합니다:
 *     1. BFS를 사용하여 레벨 그래프(Level Graph)를 구성합니다.
 *     2. DFS를 이용하여 Blocking Flow를 찾습니다.
 *     3. 레벨 그래프가 더 이상 확장될 수 없을 때까지 이 과정을 반복하며, 총 유량을 증가시킵니다.
 * - 이 구현체는 동적 메모리 관리, 에러 처리 및 상세한 주석을 포함하여 실무 환경에서 바로 사용할 수 있도록 작성되었습니다.
 *
 * 컴파일 예시: gcc -Wall -O2 dinic.c -o dinic
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define INITIAL_CAPACITY 4
#define INF INT_MAX

/*---------------- Data Structures ----------------*/

// Edge 구조체: 각 간선의 도착 정점, 용량, 현재 흐름, 그리고 역 간선 인덱스를 저장합니다.
typedef struct Edge {
    int to;     // 간선이 연결하는 도착 정점
    int cap;    // 간선의 용량
    int flow;   // 현재 간선을 통해 흐른 유량
    int rev;    // 도착 정점의 인접 리스트에서 역 간선(잔여 간선)의 인덱스
} Edge;

// AdjList 구조체: 각 정점의 인접 간선들을 동적 배열로 저장합니다.
typedef struct AdjList {
    Edge* edges;   // 동적 할당된 Edge 배열
    int count;     // 현재 저장된 간선 수
    int capacity;  // 할당된 용량
} AdjList;

// Graph 구조체: 그래프는 정점 수와 각 정점의 인접 리스트 배열로 표현됩니다.
typedef struct Graph {
    int V;         // 정점의 수
    AdjList* adj;  // 각 정점의 인접 리스트 배열 (크기 V)
} Graph;

/*---------------- Graph Utility Functions ----------------*/

/**
 * createGraph - 정점 수 V를 가진 그래프를 생성하고 초기화합니다.
 * @V: 그래프의 정점 수
 *
 * 반환값: 동적 할당된 Graph 포인터.
 */
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        fprintf(stderr, "메모리 할당 실패 (createGraph)\n");
        exit(EXIT_FAILURE);
    }
    graph->V = V;
    graph->adj = (AdjList*)malloc(V * sizeof(AdjList));
    if (!graph->adj) {
        fprintf(stderr, "메모리 할당 실패 (graph->adj)\n");
        free(graph);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < V; i++) {
        graph->adj[i].count = 0;
        graph->adj[i].capacity = INITIAL_CAPACITY;
        graph->adj[i].edges = (Edge*)malloc(INITIAL_CAPACITY * sizeof(Edge));
        if (!graph->adj[i].edges) {
            fprintf(stderr, "메모리 할당 실패 (graph->adj[%d].edges)\n", i);
            // Free previously allocated memory
            for (int j = 0; j < i; j++) {
                free(graph->adj[j].edges);
            }
            free(graph->adj);
            free(graph);
            exit(EXIT_FAILURE);
        }
    }
    return graph;
}

/**
 * addEdge - 그래프에 간선을 추가합니다.
 * @graph: 그래프 포인터
 * @u: 시작 정점 번호
 * @v: 도착 정점 번호
 * @cap: 간선의 용량
 *
 * 이 함수는 u에서 v로의 간선을 추가하고, 역 간선은 v에서 u로 추가합니다.
 * 역 간선은 초기 용량 0과 흐름 0을 가집니다.
 */
void addEdge(Graph* graph, int u, int v, int cap) {
    // Forward edge: u -> v
    AdjList *listU = &graph->adj[u];
    if (listU->count == listU->capacity) {
        listU->capacity *= 2;
        Edge* newEdges = (Edge*)realloc(listU->edges, listU->capacity * sizeof(Edge));
        if (!newEdges) {
            fprintf(stderr, "메모리 재할당 실패 (addEdge, forward)\n");
            exit(EXIT_FAILURE);
        }
        listU->edges = newEdges;
    }
    listU->edges[listU->count].to = v;
    listU->edges[listU->count].cap = cap;
    listU->edges[listU->count].flow = 0;
    // Temporary, reverse index to be set later
    int forwardIndex = listU->count;
    listU->count++;

    // Reverse edge: v -> u with 0 capacity
    AdjList *listV = &graph->adj[v];
    if (listV->count == listV->capacity) {
        listV->capacity *= 2;
        Edge* newEdges = (Edge*)realloc(listV->edges, listV->capacity * sizeof(Edge));
        if (!newEdges) {
            fprintf(stderr, "메모리 재할당 실패 (addEdge, reverse)\n");
            exit(EXIT_FAILURE);
        }
        listV->edges = newEdges;
    }
    listV->edges[listV->count].to = u;
    listV->edges[listV->count].cap = 0; // 역간선 용량은 0
    listV->edges[listV->count].flow = 0;
    int reverseIndex = listV->count;
    listV->count++;

    // Set the reverse indices for both edges
    graph->adj[u].edges[forwardIndex].rev = reverseIndex;
    graph->adj[v].edges[reverseIndex].rev = forwardIndex;
}

/**
 * freeGraph - 그래프에 할당된 모든 메모리를 해제합니다.
 * @graph: 그래프 포인터
 */
void freeGraph(Graph* graph) {
    if (graph) {
        for (int i = 0; i < graph->V; i++) {
            free(graph->adj[i].edges);
        }
        free(graph->adj);
        free(graph);
    }
}

/*---------------- Dinic Algorithm Variables ----------------*/

// level 배열: 레벨 그래프에서 각 정점의 레벨을 저장합니다.
int *level;

/*---------------- Dinic's Algorithm Functions ----------------*/

/**
 * dinicBFS - BFS를 사용하여 레벨 그래프를 구성합니다.
 * @graph: 입력 그래프 포인터
 * @s: 소스 정점 번호
 * @t: 싱크 정점 번호
 *
 * 반환값: 싱크(t)가 레벨 그래프에서 도달 가능하면 1, 아니면 0.
 *
 * 이 함수는 소스에서 시작하여 각 정점의 레벨을 계산하고, 
 * 싱크가 도달 가능한지 확인합니다.
 */
int dinicBFS(Graph* graph, int s, int t) {
    int V = graph->V;
    // Allocate and initialize level array
    for (int i = 0; i < V; i++)
        level[i] = -1;
    level[s] = 0;

    // BFS queue
    int *queue = (int*)malloc(V * sizeof(int));
    if (!queue) {
        fprintf(stderr, "메모리 할당 실패 (dinicBFS: queue)\n");
        exit(EXIT_FAILURE);
    }
    int front = 0, rear = 0;
    queue[rear++] = s;

    while (front < rear) {
        int u = queue[front++];
        for (int i = 0; i < graph->adj[u].count; i++) {
            Edge edge = graph->adj[u].edges[i];
            // If vertex not visited and residual capacity > 0
            if (level[edge.to] < 0 && edge.flow < edge.cap) {
                level[edge.to] = level[u] + 1;
                queue[rear++] = edge.to;
            }
        }
    }
    free(queue);
    return (level[t] >= 0);
}

/**
 * dinicDFS - DFS를 사용하여 Blocking Flow를 찾는 함수.
 * @graph: 입력 그래프 포인터
 * @u: 현재 정점
 * @t: 싱크 정점 번호
 * @flow: 현재까지 흐를 수 있는 유량
 * @start: 각 정점의 인접 리스트에서 다음 탐색할 간선의 인덱스를 추적하는 배열
 *
 * 반환값: 현재 경로를 통해 추가로 흘려보낼 수 있는 유량.
 *
 * 이 함수는 레벨 그래프 상에서 DFS를 수행하며, Blocking Flow를 찾고 잔여 용량을 업데이트합니다.
 */
int dinicDFS(Graph* graph, int u, int t, int flow, int *start) {
    if (u == t)
        return flow;
    
    for ( ; start[u] < graph->adj[u].count; start[u]++) {
        Edge *edge = &graph->adj[u].edges[start[u]];
        if (level[edge->to] == level[u] + 1 && edge->flow < edge->cap) {
            int curr_flow = (flow < (edge->cap - edge->flow)) ? flow : (edge->cap - edge->flow);
            int temp_flow = dinicDFS(graph, edge->to, t, curr_flow, start);
            
            if (temp_flow > 0) {
                // Update flows: add flow to current edge and subtract from reverse edge
                edge->flow += temp_flow;
                graph->adj[edge->to].edges[edge->rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }
    return 0;
}

/**
 * dinicMaxFlow - Dinic 알고리즘을 사용하여 최대 유량을 계산합니다.
 * @graph: 입력 그래프 포인터
 * @s: 소스 정점 번호
 * @t: 싱크 정점 번호
 *
 * 반환값: 계산된 최대 유량 (정수)
 *
 * 이 함수는 BFS를 통해 레벨 그래프를 구성하고, DFS를 통해 Blocking Flow를 찾는 과정을 반복합니다.
 * 더 이상 증가 경로가 존재하지 않을 때까지 최대 유량을 누적하여 반환합니다.
 */
int dinicMaxFlow(Graph* graph, int s, int t) {
    if (!graph || s < 0 || t < 0 || s >= graph->V || t >= graph->V) {
        fprintf(stderr, "잘못된 인자 (dinicMaxFlow)\n");
        exit(EXIT_FAILURE);
    }
    
    int totalFlow = 0;
    // Allocate level array (global)
    level = (int*)malloc(graph->V * sizeof(int));
    if (!level) {
        fprintf(stderr, "메모리 할당 실패 (dinicMaxFlow: level)\n");
        exit(EXIT_FAILURE);
    }
    
    // 반복: BFS를 통해 레벨 그래프 구성, DFS로 Blocking Flow 찾기
    while (dinicBFS(graph, s, t)) {
        // start 배열: 각 정점의 인접 리스트에서 DFS를 위한 시작 인덱스 초기화
        int *start = (int*)calloc(graph->V, sizeof(int));
        if (!start) {
            fprintf(stderr, "메모리 할당 실패 (dinicMaxFlow: start)\n");
            free(level);
            exit(EXIT_FAILURE);
        }
        while (1) {
            int flow = dinicDFS(graph, s, t, INF, start);
            if (flow <= 0)
                break;
            totalFlow += flow;
        }
        free(start);
    }
    
    free(level);
    return totalFlow;
}

/*---------------- main 함수 (데모) ----------------*/
/**
 * main - Dinic 알고리즘 데모
 *
 * 이 함수는 예제 그래프를 생성하고, 소스에서 싱크까지의 최대 유량을 계산한 후 결과를 출력합니다.
 */
int main(void) {
    /*
     * 예제 그래프:
     * 정점 수: 6
     * 인접 리스트 표현:
     * 정점 0: (0 -> 1, cap=16), (0 -> 2, cap=13)
     * 정점 1: (1 -> 3, cap=12)
     * 정점 2: (2 -> 1, cap=4), (2 -> 4, cap=14)
     * 정점 3: (3 -> 2, cap=9), (3 -> 5, cap=20)
     * 정점 4: (4 -> 3, cap=7), (4 -> 5, cap=4)
     * 정점 5: -
     *
     * 이 예제는 소스(0)에서 싱크(5)까지의 최대 유량을 계산합니다.
     */
    int V = 6;
    Graph* graph = createGraph(V);
    
    // 간선 추가: addEdge(graph, u, v, capacity)
    addEdge(graph, 0, 1, 16);
    addEdge(graph, 0, 2, 13);
    addEdge(graph, 1, 3, 12);
    addEdge(graph, 2, 1, 4);
    addEdge(graph, 2, 4, 14);
    addEdge(graph, 3, 2, 9);
    addEdge(graph, 3, 5, 20);
    addEdge(graph, 4, 3, 7);
    addEdge(graph, 4, 5, 4);
    
    int s = 0, t = 5;
    int maxFlow = dinicMaxFlow(graph, s, t);
    printf("최대 유량 (Dinic): %d\n", maxFlow);
    
    freeGraph(graph);
    return 0;
}