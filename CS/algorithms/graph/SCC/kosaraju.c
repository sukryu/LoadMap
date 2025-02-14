/**
 * kosaraju.c
 *
 * 고도화된 Kosaraju 알고리즘 구현 예제
 * - 이 파일은 방향 그래프에서 강하게 연결된 성분(SCC; Strongly Connected Components)을 찾기 위한 Kosaraju 알고리즘을 구현합니다.
 * - Kosaraju 알고리즘은 다음 단계로 구성됩니다:
 *     1. 원본 그래프에서 DFS를 수행하여 각 정점의 종료 시점(finish time)에 따라 정점을 스택에 저장합니다.
 *     2. 그래프의 전치(transpose) 그래프를 생성합니다. (모든 간선 방향을 반대로 바꿈)
 *     3. 전치 그래프에서 스택에 저장된 정점 순서대로 DFS를 수행하면, DFS 트리마다 하나의 SCC가 형성됩니다.
 *
 * - 이 구현체는 동적 메모리 관리, 에러 처리 및 자세한 주석을 포함하여 실무 환경에서도 활용 가능하도록 작성되었습니다.
 *
 * 컴파일 예시: gcc -Wall -O2 kosaraju.c -o kosaraju
 */

#include <stdio.h>
#include <stdlib.h>

#define UNVISITED 0
#define VISITED   1

/*---------------- Data Structures ----------------*/

// Node 구조체: 인접 리스트에서 한 정점을 나타냄
typedef struct Node {
    int dest;              // 인접한 정점 번호
    struct Node* next;     // 다음 인접 노드 포인터
} Node;

// Graph 구조체: 방향 그래프를 인접 리스트로 표현
typedef struct Graph {
    int V;               // 정점의 수
    Node** array;        // 각 정점의 인접 리스트 (배열)
} Graph;

/*---------------- Stack Data Structure ----------------*/

// Stack 구조체: 정수를 저장하는 스택 (정점 번호를 저장)
typedef struct Stack {
    int* data;      // 동적 할당된 정수 배열
    int capacity;   // 스택의 최대 용량
    int top;        // 스택의 현재 최상단 인덱스 (-1이면 빈 스택)
} Stack;

/*---------------- Function Prototypes ----------------*/
Graph* createGraph(int V);
void addEdge(Graph* graph, int src, int dest);
void freeGraph(Graph* graph);

Stack* createStack(int capacity);
void push(Stack* stack, int value);
int pop(Stack* stack);
int isEmpty(Stack* stack);
void freeStack(Stack* stack);

void fillOrder(Graph* graph, int v, int visited[], Stack* stack);
Graph* getTranspose(Graph* graph);
void DFSUtil(Graph* graph, int v, int visited[], int scc[], int* sccCount);

/*---------------- Graph Utility Functions ----------------*/

/**
 * createGraph - 정점 수 V를 가진 그래프를 생성하고 초기화합니다.
 * @V: 정점의 수
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
        fprintf(stderr, "메모리 할당 실패 (graph->array)\n");
        free(graph);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < V; i++) {
        graph->array[i] = NULL;
    }
    return graph;
}

/**
 * addEdge - 방향 그래프에서 src에서 dest로의 에지를 추가합니다.
 * @graph: 그래프 포인터
 * @src: 출발 정점 번호
 * @dest: 도착 정점 번호
 *
 * 이 함수는 src의 인접 리스트에 dest를 추가합니다.
 */
void addEdge(Graph* graph, int src, int dest) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "메모리 할당 실패 (addEdge)\n");
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
            while (temp) {
                Node* next = temp->next;
                free(temp);
                temp = next;
            }
        }
        free(graph->array);
        free(graph);
    }
}

/*---------------- Stack Utility Functions ----------------*/

/**
 * createStack - 주어진 용량을 가지는 스택을 생성합니다.
 * @capacity: 스택의 최대 용량
 * 반환값: 동적 할당된 Stack 포인터
 */
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) {
        fprintf(stderr, "메모리 할당 실패 (createStack)\n");
        exit(EXIT_FAILURE);
    }
    stack->data = (int*)malloc(capacity * sizeof(int));
    if (!stack->data) {
        fprintf(stderr, "메모리 할당 실패 (stack->data)\n");
        free(stack);
        exit(EXIT_FAILURE);
    }
    stack->capacity = capacity;
    stack->top = -1; // 빈 스택
    return stack;
}

/**
 * push - 스택에 정수를 추가합니다.
 * @stack: 스택 포인터
 * @value: 추가할 정수
 */
void push(Stack* stack, int value) {
    // 스택 용량 초과 시 재할당
    if (stack->top == stack->capacity - 1) {
        stack->capacity *= 2;
        int* newData = (int*)realloc(stack->data, stack->capacity * sizeof(int));
        if (!newData) {
            fprintf(stderr, "메모리 재할당 실패 (push)\n");
            free(stack->data);
            free(stack);
            exit(EXIT_FAILURE);
        }
        stack->data = newData;
    }
    stack->data[++stack->top] = value;
}

/**
 * pop - 스택에서 최상위 정수를 제거하고 반환합니다.
 * @stack: 스택 포인터
 * 반환값: 제거된 정수, 스택이 빈 경우 -1을 반환합니다.
 */
int pop(Stack* stack) {
    if (stack->top == -1)
        return -1;
    return stack->data[stack->top--];
}

/**
 * isEmpty - 스택이 비어있는지 검사합니다.
 * @stack: 스택 포인터
 * 반환값: 스택이 비어있으면 1, 그렇지 않으면 0
 */
int isEmpty(Stack* stack) {
    return (stack->top == -1);
}

/**
 * freeStack - 스택에 할당된 메모리를 해제합니다.
 * @stack: 스택 포인터
 */
void freeStack(Stack* stack) {
    if (stack) {
        free(stack->data);
        free(stack);
    }
}

/*---------------- Kosaraju's Algorithm Functions ----------------*/

/**
 * fillOrder - 원본 그래프에서 DFS를 수행하며, 정점의 종료 시각에 따라 스택에 저장합니다.
 * @graph: 그래프 포인터
 * @v: 현재 DFS 탐색 중인 정점 번호
 * @visited: 각 정점의 방문 여부 배열 (0: 미방문, 1: 방문)
 * @stack: 정점의 종료 시각 순서대로 정점을 저장하는 스택
 *
 * 이 함수는 DFS를 수행한 후, 정점 v가 탐색을 마치면 스택에 푸시합니다.
 */
void fillOrder(Graph* graph, int v, int visited[], Stack* stack) {
    visited[v] = VISITED;
    Node* temp = graph->array[v];
    while (temp != NULL) {
        int adj = temp->dest;
        if (!visited[adj])
            fillOrder(graph, adj, visited, stack);
        temp = temp->next;
    }
    push(stack, v);
}

/**
 * getTranspose - 주어진 그래프의 전치(Transpose) 그래프를 생성합니다.
 * @graph: 원본 그래프 포인터
 * 반환값: 동적 할당된 전치 그래프 포인터
 *
 * 전치 그래프는 원래 그래프의 모든 간선 방향을 반대로 뒤집어 구성합니다.
 */
Graph* getTranspose(Graph* graph) {
    Graph* transpose = createGraph(graph->V);
    for (int v = 0; v < graph->V; v++) {
        Node* temp = graph->array[v];
        while (temp != NULL) {
            // 원본 그래프에서 v -> temp->dest 인 간선을
            // 전치 그래프에서는 temp->dest -> v 로 추가합니다.
            addEdge(transpose, temp->dest, v);
            temp = temp->next;
        }
    }
    return transpose;
}

/**
 * DFSUtil - 전치 그래프에서 DFS를 수행하며, 하나의 SCC를 추출합니다.
 * @graph: 전치 그래프 포인터
 * @v: 현재 DFS 탐색 중인 정점 번호
 * @visited: 방문 여부 배열
 * @scc: SCC에 포함된 정점을 저장할 배열
 * @sccCount: 현재 SCC에 저장된 정점 수 (출력 인자)
 *
 * 이 함수는 DFS를 통해 정점 v로부터 도달 가능한 모든 정점을 scc 배열에 저장합니다.
 */
void DFSUtil(Graph* graph, int v, int visited[], int scc[], int* sccCount) {
    visited[v] = VISITED;
    scc[(*sccCount)++] = v;
    Node* temp = graph->array[v];
    while (temp != NULL) {
        int adj = temp->dest;
        if (!visited[adj])
            DFSUtil(graph, adj, visited, scc, sccCount);
        temp = temp->next;
    }
}

/*---------------- Kosaraju's Algorithm Main Function ----------------*/

/**
 * kosarajuSCC - Kosaraju 알고리즘을 이용하여 그래프의 강하게 연결된 성분(SCC)을 찾습니다.
 * @graph: 원본 그래프 포인터
 *
 * 이 함수는 다음 단계로 동작합니다:
 *   1. 원본 그래프에서 DFS를 수행하여 정점의 종료 시각 순서대로 스택에 저장합니다.
 *   2. 전치(Transpose) 그래프를 생성합니다.
 *   3. 전치 그래프에서 스택에서 꺼낸 정점 순서대로 DFS를 수행하여 SCC를 추출합니다.
 *
 * 각 SCC는 실행 중에 출력됩니다.
 */
void kosarajuSCC(Graph* graph) {
    int V = graph->V;
    int* visited = (int*)calloc(V, sizeof(int));
    if (!visited) {
        fprintf(stderr, "메모리 할당 실패 (kosarajuSCC: visited)\n");
        exit(EXIT_FAILURE);
    }

    // 1. 원본 그래프 DFS를 통한 종료 시각 저장
    Stack* stack = createStack(V);
    for (int i = 0; i < V; i++) {
        if (!visited[i])
            fillOrder(graph, i, visited, stack);
    }

    // 2. 그래프의 전치(transpose) 생성
    Graph* transpose = getTranspose(graph);

    // 3. 전치 그래프에서 스택 순서대로 DFS를 수행하여 SCC 추출
    // 초기 방문 배열 재설정
    for (int i = 0; i < V; i++)
        visited[i] = UNVISITED;

    printf("강하게 연결된 성분 (SCC):\n");
    while (!isEmpty(stack)) {
        int v = pop(stack);
        if (!visited[v]) {
            // 하나의 SCC를 저장할 배열 (최대 V개의 정점을 저장할 수 있음)
            int* scc = (int*)malloc(V * sizeof(int));
            if (!scc) {
                fprintf(stderr, "메모리 할당 실패 (kosarajuSCC: scc)\n");
                exit(EXIT_FAILURE);
            }
            int sccCount = 0;
            DFSUtil(transpose, v, visited, scc, &sccCount);
            
            // SCC 출력
            printf("SCC: ");
            for (int i = 0; i < sccCount; i++) {
                printf("%d ", scc[i]);
            }
            printf("\n");
            free(scc);
        }
    }

    free(visited);
    freeStack(stack);
    freeGraph(transpose);
}

/*---------------- main 함수 (데모) ----------------*/

/**
 * main - Kosaraju 알고리즘 데모
 *
 * 이 함수는 예제 그래프를 생성하고, 에지를 추가한 후,
 * Kosaraju 알고리즘을 통해 그래프의 강하게 연결된 성분(SCC)을 찾고 출력합니다.
 */
int main(void) {
    int V = 5;
    Graph* graph = createGraph(V);
    
    /* 예제 그래프 (방향 그래프)
       에지:
         0 -> 2
         2 -> 1
         1 -> 0
         0 -> 3
         3 -> 4
    */
    addEdge(graph, 0, 2);
    addEdge(graph, 2, 1);
    addEdge(graph, 1, 0);
    addEdge(graph, 0, 3);
    addEdge(graph, 3, 4);
    
    kosarajuSCC(graph);
    
    freeGraph(graph);
    return 0;
}
