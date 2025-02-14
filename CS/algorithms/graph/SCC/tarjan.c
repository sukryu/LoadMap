/**
 * tarjan.c
 *
 * 고도화된 Tarjan 알고리즘 구현 예제
 * - 이 파일은 방향 그래프에서 강하게 연결된 성분(SCC; Strongly Connected Components)을 찾기 위해
 *   Tarjan의 알고리즘을 구현한 예제입니다.
 * - Tarjan 알고리즘은 DFS(깊이 우선 탐색)를 한 번 수행하면서 각 정점의 발견 순서와 low-link 값을 기록합니다.
 * - 재귀 호출과 스택을 활용하여, low-link 값이 자기 자신과 동일한 정점을 만났을 때
 *   해당 정점부터 스택에 있는 정점들을 하나의 SCC로 그룹화합니다.
 *
 * 주요 단계:
 *   1. 각 정점에 대해 discovery time과 low-link 값을 초기화합니다.
 *   2. DFS를 수행하면서, 각 정점을 스택에 푸시하고 방문 상태를 기록합니다.
 *   3. 재귀 호출 후, 인접 정점의 low-link 값을 통해 현재 정점의 low 값을 업데이트합니다.
 *   4. 만약 정점 v의 low[v]가 discovery time과 같다면, 스택에서 v가 나올 때까지 팝하여 하나의 SCC를 구성합니다.
 *
 * 컴파일 예시: gcc -Wall -O2 tarjan.c -o tarjan
 */

#include <stdio.h>
#include <stdlib.h>

#define UNVISITED -1

/*---------------- Data Structures ----------------*/

// Node 구조체: 인접 리스트에서 한 정점을 나타냄
typedef struct Node {
    int dest;              // 인접한 정점 번호
    struct Node* next;     // 다음 인접 노드 포인터
} Node;

// Graph 구조체: 방향 그래프를 인접 리스트로 표현
typedef struct Graph {
    int V;         // 정점의 수
    Node** array;  // 각 정점의 인접 리스트 배열
} Graph;

/*---------------- Graph Utility Functions ----------------*/

/**
 * createGraph - V개의 정점을 가진 그래프를 생성하고 초기화합니다.
 * @V: 그래프의 정점 수
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
    graph->array = (Node**)malloc(V * sizeof(Node*));
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
 * addDirectedEdge - 방향 그래프에서 src에서 dest로의 에지를 추가합니다.
 * @graph: 그래프 포인터
 * @src: 출발 정점 번호
 * @dest: 도착 정점 번호
 *
 * 이 함수는 src의 인접 리스트에 dest를 추가합니다.
 */
void addDirectedEdge(Graph* graph, int src, int dest) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "메모리 할당 실패 (addDirectedEdge)\n");
        exit(EXIT_FAILURE);
    }
    node->dest = dest;
    node->next = graph->array[src];
    graph->array[src] = node;
}

/**
 * freeGraph - 그래프에 할당된 모든 메모리를 해제합니다.
 * @graph: 그래프 포인터
 */
void freeGraph(Graph* graph) {
    if (graph) {
        for (int i = 0; i < graph->V; i++) {
            Node* temp = graph->array[i];
            while (temp != NULL) {
                Node* next = temp->next;
                free(temp);
                temp = next;
            }
        }
        free(graph->array);
        free(graph);
    }
}

/*---------------- Tarjan's Algorithm Variables ----------------*/

// Global variables used for Tarjan's algorithm
int timeCounter;   // 글로벌 시간 카운터 (발견 순서를 기록)
int *disc;         // 각 정점의 발견 시간 (discovery time)
int *low;          // 각 정점의 low-link 값 (최소 발견 시간)
int *stackMember;  // 스택에 있는지 여부를 표시하는 배열 (0: 없음, 1: 있음)
int *sccStack;     // DFS 동안 사용되는 스택 (정점 번호 저장)
int sccStackTop;   // 스택의 현재 top index

/*---------------- Tarjan's Algorithm Function ----------------*/

/**
 * tarjanDFS - Tarjan 알고리즘을 이용한 DFS 함수
 * @graph: 그래프 포인터
 * @u: 현재 방문 중인 정점 번호
 *
 * 이 함수는 DFS를 수행하면서 각 정점의 발견 시간과 low-link 값을 계산하고,
 * 스택을 사용하여 SCC를 식별합니다.
 */
void tarjanDFS(Graph* graph, int u) {
    // 초기 설정: 정점 u의 발견 시간과 low-link 값을 설정
    disc[u] = low[u] = ++timeCounter;
    sccStack[sccStackTop++] = u;  // u를 스택에 푸시
    stackMember[u] = 1;

    // u의 인접 리스트 순회
    Node* temp = graph->array[u];
    while (temp != NULL) {
        int v = temp->dest;
        if (disc[v] == UNVISITED) {
            // v가 아직 방문되지 않았다면, 재귀적으로 방문
            tarjanDFS(graph, v);
            // v의 low-link 값을 u의 low-link에 반영
            if (low[v] < low[u])
                low[u] = low[v];
        }
        // v가 스택에 있다면, 그것은 u와 같은 SCC에 속함
        else if (stackMember[v] == 1 && disc[v] < low[u]) {
            low[u] = disc[v];
        }
        temp = temp->next;
    }

    // 만약 u가 SCC의 루트라면, 스택에서 pop하여 하나의 SCC를 구성
    if (low[u] == disc[u]) {
        printf("SCC: ");
        int w;
        do {
            w = sccStack[--sccStackTop];
            stackMember[w] = 0;
            printf("%d ", w);
        } while (w != u);
        printf("\n");
    }
}

/**
 * tarjanSCC - Tarjan 알고리즘을 이용하여 강하게 연결된 성분(SCC)을 찾습니다.
 * @graph: 그래프 포인터
 *
 * 이 함수는 모든 정점에 대해 Tarjan DFS를 수행하여 SCC를 출력합니다.
 */
void tarjanSCC(Graph* graph) {
    int V = graph->V;
    
    // 동적 배열 초기화: disc, low, stackMember, sccStack
    disc = (int*)malloc(V * sizeof(int));
    low = (int*)malloc(V * sizeof(int));
    stackMember = (int*)malloc(V * sizeof(int));
    sccStack = (int*)malloc(V * sizeof(int));
    if (!disc || !low || !stackMember || !sccStack) {
        fprintf(stderr, "메모리 할당 실패 (tarjanSCC 초기화)\n");
        exit(EXIT_FAILURE);
    }

    // 모든 정점을 UNVISITED로 초기화
    for (int i = 0; i < V; i++) {
        disc[i] = UNVISITED;
        low[i] = UNVISITED;
        stackMember[i] = 0;
    }
    timeCounter = 0;
    sccStackTop = 0;

    // 모든 정점에 대해 DFS를 수행하여 SCC를 찾음
    for (int i = 0; i < V; i++) {
        if (disc[i] == UNVISITED)
            tarjanDFS(graph, i);
    }

    // 동적 할당된 메모리 해제
    free(disc);
    free(low);
    free(stackMember);
    free(sccStack);
}

/*---------------- main 함수 (데모) ----------------*/

/**
 * main - Tarjan 알고리즘 데모
 *
 * 이 함수는 예제 그래프를 생성하고, 에지를 추가한 후,
 * Tarjan 알고리즘을 통해 강하게 연결된 성분(SCC)을 식별하여 출력합니다.
 */
int main(void) {
    /*
     * 예제 그래프:
     * 정점 수: 8
     * 에지:
     * 0 -> 1, 0 -> 3
     * 1 -> 2
     * 2 -> 0, 2 -> 4
     * 3 -> 5
     * 4 -> 5, 4 -> 7
     * 5 -> 6
     * 6 -> 4, 6 -> 7
     * 7 -> 7 (자기 자신으로의 에지)
     */
    int V = 8;
    Graph* graph = createGraph(V);

    addDirectedEdge(graph, 0, 1);
    addDirectedEdge(graph, 0, 3);
    addDirectedEdge(graph, 1, 2);
    addDirectedEdge(graph, 2, 0);
    addDirectedEdge(graph, 2, 4);
    addDirectedEdge(graph, 3, 5);
    addDirectedEdge(graph, 4, 5);
    addDirectedEdge(graph, 4, 7);
    addDirectedEdge(graph, 5, 6);
    addDirectedEdge(graph, 6, 4);
    addDirectedEdge(graph, 6, 7);
    addDirectedEdge(graph, 7, 7);

    printf("Tarjan's SCC 알고리즘 결과:\n");
    tarjanSCC(graph);

    freeGraph(graph);
    return 0;
}
