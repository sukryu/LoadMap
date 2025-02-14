/**
 * cycle_detect.c
 *
 * 고도화된 사이클 탐지(Cycle Detection) 알고리즘 구현 예제
 * - 이 파일은 방향 그래프(Directed Graph)에서 사이클이 존재하는지 탐지하는 알고리즘을 구현합니다.
 * - DFS(깊이 우선 탐색)를 사용하며, 재귀 호출 시 현재 호출 스택(recursion stack)을 추적하여
 *   사이클이 존재할 경우 이를 감지합니다.
 * - 실무 환경에서 바로 사용할 수 있도록 동적 메모리 관리, 에러 처리 및 그래프 메모리 해제 기능을 포함하여 작성되었습니다.
 *
 * 컴파일 예시: gcc -Wall -O2 cycle_detect.c -o cycle_detect
 */

#include <stdio.h>
#include <stdlib.h>

/*---------------- Data Structures ----------------*/

// Node 구조체: 인접 리스트에서 정점을 나타냄
typedef struct Node {
    int dest;              // 인접한 정점 번호
    struct Node* next;     // 다음 인접 노드 포인터
} Node;

// Graph 구조체: 방향 그래프를 인접 리스트로 표현
typedef struct Graph {
    int V;               // 그래프의 정점 수
    Node** array;        // 각 정점의 인접 리스트 배열
} Graph;

/*---------------- Utility Functions ----------------*/

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
 * createGraph - V개의 정점을 가진 방향 그래프를 생성하고 초기화합니다.
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
 * addDirectedEdge - 방향 그래프에서 src에서 dest로의 에지를 추가합니다.
 * @graph: 그래프 포인터
 * @src: 출발 정점 번호
 * @dest: 도착 정점 번호
 *
 * 이 함수는 단방향 에지를 추가합니다.
 */
void addDirectedEdge(Graph* graph, int src, int dest) {
    Node* node = newNode(dest);
    node->next = graph->array[src];
    graph->array[src] = node;
}

/*---------------- Cycle Detection Functions ----------------*/

/**
 * isCyclicUtil - DFS를 이용하여 사이클을 탐지하는 재귀 함수
 * @graph: 그래프 포인터
 * @v: 현재 탐색 중인 정점 번호
 * @visited: 각 정점의 방문 여부 배열 (0: 미방문, 1: 방문)
 * @recStack: 현재 재귀 호출 스택에 있는 정점 여부 배열 (0: 없음, 1: 있음)
 *
 * 반환값: 정점 v를 포함하는 경로에 사이클이 있으면 1, 없으면 0을 반환합니다.
 */
int isCyclicUtil(Graph* graph, int v, int* visited, int* recStack) {
    // 현재 정점을 방문 처리하고 재귀 스택에 추가
    visited[v] = 1;
    recStack[v] = 1;

    // v의 인접 리스트 순회
    Node* temp = graph->array[v];
    while (temp != NULL) {
        int adj = temp->dest;
        // 인접 정점이 미방문이면 재귀 호출
        if (!visited[adj]) {
            if (isCyclicUtil(graph, adj, visited, recStack))
                return 1;
        }
        // 인접 정점이 재귀 스택에 있으면 사이클 존재
        else if (recStack[adj])
            return 1;
        temp = temp->next;
    }

    // 정점 v를 재귀 스택에서 제거하고 종료
    recStack[v] = 0;
    return 0;
}

/**
 * cycleDetect - 그래프 내 사이클 존재 여부를 검사합니다.
 * @graph: 그래프 포인터
 *
 * 반환값: 그래프에 사이클이 존재하면 1, 그렇지 않으면 0을 반환합니다.
 *
 * 이 함수는 모든 정점을 대상으로 DFS 기반 사이클 탐지를 수행합니다.
 */
int cycleDetect(Graph* graph) {
    int V = graph->V;
    int* visited = (int*)calloc(V, sizeof(int));
    int* recStack = (int*)calloc(V, sizeof(int));
    if (visited == NULL || recStack == NULL) {
        fprintf(stderr, "메모리 할당 실패 (cycleDetect)\n");
        free(visited);
        free(recStack);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (isCyclicUtil(graph, i, visited, recStack)) {
                free(visited);
                free(recStack);
                return 1;
            }
        }
    }
    free(visited);
    free(recStack);
    return 0;
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

/*---------------- main 함수 (데모) ----------------*/
/**
 * main - 사이클 탐지 알고리즘 데모
 *
 * 이 함수는 방향 그래프 예제를 생성하고, 에지를 추가한 후,
 * 사이클이 존재하는지 검사하여 결과를 출력합니다.
 */
int main(void) {
    // 예제: 4개의 정점을 가진 방향 그래프 생성
    int V = 4;
    Graph* graph = createGraph(V);

    // 방향 에지 추가
    // 그래프 예제:
    // 0 -> 1, 0 -> 2
    // 1 -> 2
    // 2 -> 0, 2 -> 3
    // 3 -> 3 (자기 자신으로의 에지: 사이클)
    addDirectedEdge(graph, 0, 1);
    addDirectedEdge(graph, 0, 2);
    addDirectedEdge(graph, 1, 2);
    addDirectedEdge(graph, 2, 0);
    addDirectedEdge(graph, 2, 3);
    addDirectedEdge(graph, 3, 3);

    // 사이클 탐지 실행
    if (cycleDetect(graph))
        printf("그래프에 사이클이 존재합니다.\n");
    else
        printf("그래프에 사이클이 존재하지 않습니다.\n");

    // 그래프 메모리 해제
    freeGraph(graph);

    return 0;
}