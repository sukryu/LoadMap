/**
 * bfs.c
 *
 * 고도화된 너비 우선 탐색(BFS) 알고리즘 구현 예제
 * - 이 파일은 인접 리스트로 표현된 그래프에서 너비 우선 탐색(BFS)을 수행하는 구현체입니다.
 * - BFS는 큐를 사용하여 그래프의 각 레벨별로 정점을 방문하며, 
 *   최단 경로 탐색이나 레벨 순회에 유용하게 사용됩니다.
 * - 실무 환경에서 바로 사용할 수 있도록 동적 메모리 관리, 에러 처리, 그래프 메모리 해제 기능을 포함하여 작성되었습니다.
 *
 * 컴파일 예시: gcc -Wall -O2 bfs.c -o bfs
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
 * BFS - 주어진 시작 정점으로부터 너비 우선 탐색(BFS)을 수행합니다.
 * @graph: 그래프 포인터
 * @start: 시작 정점 번호
 *
 * 이 함수는 내부적으로 방문 배열과 큐를 초기화한 후, 
 * 큐를 사용하여 각 레벨별로 정점을 방문하며, 방문 순서를 출력합니다.
 */
void BFS(Graph* graph, int start) {
    int V = graph->V;
    int* visited = (int*)calloc(V, sizeof(int));
    if (visited == NULL) {
        fprintf(stderr, "메모리 할당 실패 (BFS: visited)\n");
        exit(EXIT_FAILURE);
    }

    // 큐 구현: 최대 V개의 정점을 저장할 수 있는 배열 사용
    int* queue = (int*)malloc(V * sizeof(int));
    if (queue == NULL) {
        fprintf(stderr, "메모리 할당 실패 (BFS: queue)\n");
        free(visited);
        exit(EXIT_FAILURE);
    }
    int front = 0, rear = 0;

    // 시작 정점을 큐에 삽입
    visited[start] = 1;
    queue[rear++] = start;

    printf("BFS 시작 정점 %d: ", start);
    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        // current의 인접 리스트 탐색
        Node* temp = graph->array[current];
        while (temp != NULL) {
            int adj = temp->dest;
            if (!visited[adj]) {
                visited[adj] = 1;
                queue[rear++] = adj;
            }
            temp = temp->next;
        }
    }
    printf("\n");

    free(queue);
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

/**
 * main - BFS 알고리즘 데모
 *
 * 이 함수는 6개의 정점을 가진 예제 그래프를 생성하고, 무방향 에지를 추가한 후,
 * 시작 정점 0에서부터 BFS 탐색을 수행하여 결과를 출력합니다.
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

    // BFS 탐색 실행: 시작 정점 0
    BFS(graph, 0);

    // 그래프 메모리 해제
    freeGraph(graph);

    return 0;
}