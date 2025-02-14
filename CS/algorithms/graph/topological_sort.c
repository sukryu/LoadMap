/**
 * topological_sort.c
 *
 * 고도화된 위상 정렬(Topological Sort) 알고리즘 구현 예제
 * - 이 파일은 방향 그래프(Directed Acyclic Graph, DAG)에서 위상 정렬을 수행하는 구현체입니다.
 * - Kahn의 알고리즘을 사용하여 각 정점의 진입 차수를 계산한 후, 진입 차수가 0인 정점을 큐에 넣어
 *   순차적으로 정렬된 순서를 도출합니다.
 * - 사이클이 존재하는 경우(즉, DAG가 아닌 경우) 위상 정렬을 수행할 수 없으므로, NULL을 반환합니다.
 * - 실무 환경에서 바로 사용할 수 있도록 동적 메모리 관리, 에러 처리 및 그래프 메모리 해제 기능을 포함하여 작성되었습니다.
 *
 * 컴파일 예시: gcc -Wall -O2 topological_sort.c -o ts
 */

#include <stdio.h>
#include <stdlib.h>

// Node 구조체: 인접 리스트의 노드를 나타냄
typedef struct Node {
    int dest;              // 인접한 정점 번호
    struct Node* next;     // 다음 인접 노드 포인터
} Node;

// Graph 구조체: 방향 그래프를 인접 리스트로 표현
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

/**
 * topologicalSort - Kahn의 알고리즘을 이용하여 위상 정렬을 수행합니다.
 * @graph: 그래프 포인터
 *
 * 반환값: 위상 정렬된 정점 번호를 담은 동적 배열.
 *         만약 그래프에 사이클이 존재하면, NULL을 반환합니다.
 *         (반환된 배열은 호출자가 free()로 메모리 해제해야 합니다.)
 */
int* topologicalSort(Graph* graph) {
    int V = graph->V;
    int* inDegree = (int*)calloc(V, sizeof(int));
    if (inDegree == NULL) {
        fprintf(stderr, "메모리 할당 실패 (inDegree)\n");
        exit(EXIT_FAILURE);
    }
    
    // 모든 정점에 대해 in-degree 계산
    for (int i = 0; i < V; i++) {
        Node* temp = graph->array[i];
        while (temp != NULL) {
            inDegree[temp->dest]++;
            temp = temp->next;
        }
    }
    
    // 큐 구현: 최대 V개의 정점을 저장할 수 있는 배열 사용
    int* queue = (int*)malloc(V * sizeof(int));
    if (queue == NULL) {
        fprintf(stderr, "메모리 할당 실패 (queue)\n");
        free(inDegree);
        exit(EXIT_FAILURE);
    }
    int front = 0, rear = 0;
    
    // in-degree가 0인 정점을 큐에 삽입
    for (int i = 0; i < V; i++) {
        if (inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }
    
    // 위상 정렬 결과를 저장할 배열
    int* topoOrder = (int*)malloc(V * sizeof(int));
    if (topoOrder == NULL) {
        fprintf(stderr, "메모리 할당 실패 (topoOrder)\n");
        free(queue);
        free(inDegree);
        exit(EXIT_FAILURE);
    }
    int count = 0;
    
    // Kahn의 알고리즘 실행: 큐에서 정점을 꺼내고, 해당 정점의 인접 정점들의 in-degree 감소
    while (front < rear) {
        int u = queue[front++];
        topoOrder[count++] = u;
        
        Node* temp = graph->array[u];
        while (temp != NULL) {
            int v = temp->dest;
            inDegree[v]--;
            if (inDegree[v] == 0) {
                queue[rear++] = v;
            }
            temp = temp->next;
        }
    }
    
    free(queue);
    free(inDegree);
    
    // 만약 위상 정렬된 정점의 수가 V보다 작으면, 그래프에 사이클이 존재함
    if (count != V) {
        free(topoOrder);
        return NULL;
    }
    
    return topoOrder;
}

/**
 * freeGraph - 그래프의 모든 메모리를 해제합니다.
 * @graph: 그래프 포인터
 *
 * 이 함수는 그래프의 각 정점에 할당된 인접 리스트 노드와,
 * 그래프 구조체 자체의 메모리를 해제합니다.
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
 * main - 위상 정렬 알고리즘 데모
 *
 * 이 함수는 6개의 정점을 가진 DAG 예제를 생성하고, 방향 에지를 추가한 후,
 * 위상 정렬을 수행하여 정렬된 정점 순서를 출력합니다.
 */
int main(void) {
    int V = 6;
    Graph* graph = createGraph(V);
    
    // DAG 예제 에지 추가
    addDirectedEdge(graph, 5, 2);
    addDirectedEdge(graph, 5, 0);
    addDirectedEdge(graph, 4, 0);
    addDirectedEdge(graph, 4, 1);
    addDirectedEdge(graph, 2, 3);
    addDirectedEdge(graph, 3, 1);
    
    int* topoOrder = topologicalSort(graph);
    if (topoOrder == NULL) {
        printf("그래프에 사이클이 존재하여 위상 정렬을 수행할 수 없습니다.\n");
    } else {
        printf("위상 정렬 결과: ");
        for (int i = 0; i < V; i++) {
            printf("%d ", topoOrder[i]);
        }
        printf("\n");
        free(topoOrder);
    }
    
    freeGraph(graph);
    return 0;
}