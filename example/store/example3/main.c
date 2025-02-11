#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000  // 무한대 값 정의
#define MAX_VERTICES 1001  // 최대 정점 수

// 그래프 모듈
typedef struct Node {
    int vertex; // 도착 정점
    int weight; // 간선의 가중치
    struct Node* next; // 다음 노드를 가리키는 포인터
} Node;

typedef struct {
    int V; // 정점의 개수
    Node** array; // 각 정점의 인접 리스트를 가리키는 포인터 배열
} Graph;

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (Node**)malloc(sizeof(Node*) * (V + 1)); // 1-based indexing

    for (int i = 0; i <= V; i++) {
        graph->array[i] = NULL;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->weight = weight;
    newNode->next = graph->array[src];
    graph->array[src] = newNode;
}

void destroyGraph(Graph* graph) {
    if (graph) {
        for (int i = 0; i <= graph->V; i++) {
            Node* current = graph->array[i];
            while (current) {
                Node* next = current->next;
                free(current);
                current = next;
            }
        }
        free(graph->array);
        free(graph);
    }
}

Graph* readGraphInput() {
    int V, E;
    if (scanf("%d %d", &V, &E) != 2) {
        fprintf(stderr, "Error: Invalid input format for V and E\n");
        return NULL;
    }
    
    if (!validateInput(V, E, 1, 1, 0)) {  // V, E 값 검증
        perror("Invalid input for V or E");
        return NULL;
    }
    
    Graph* graph = createGraph(V);
    
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        if (scanf("%d %d %d", &src, &dest, &weight) != 3) {
            fprintf(stderr, "Error: Invalid input format for edge %d\n", i + 1);
            destroyGraph(graph);
            return NULL;
        }
        if (!validateInput(V, E, src, dest, weight)) {
            perror("Invalid edge input");
            destroyGraph(graph);
            return NULL;
        }
        addEdge(graph, src, dest, weight);
    }
    
    return graph;
}

int validateInput(int V, int E, int src, int dest, int weight) {
    if (V < 1 || V > 1000) return 0;
    if (E < 1 || E > 10000) return 0;
    if (src < 1 || src > V) return 0;
    if (dest < 1 || dest > V) return 0;
    if (weight < 0) return 0;
    return 1;
}

void printGraph(Graph* graph) {
    for (int i = 1; i <= graph->V; i++) {
        Node* current = graph->array[i];
        printf("Vertex %d: ", i);
        while (current) {
            printf("-> %d(w:%d) ", current->vertex, current->weight);
            current = current->next;
        }
        printf("\n");
    }
}

// 그래프 모듈 끝

// 이진 힙 모듈
typedef
struct
{
    int vertex; // 정점 번호
    int distance; // 시작점으로부터의 거리
} element;

typedef
struct
{
    element *heap; // 동적 할당
    int heap_size;
    int capacity;
} HeapType;

HeapType* create(int capacity) 
{
    HeapType* h = (HeapType*)malloc(sizeof(HeapType));
    h->heap = (element*)malloc(sizeof(element) * capacity);
    h->heap_size = 0;
    h->capacity = capacity;
    return h;
}

void init(HeapType* h) 
{
    h->heap_size = 0;
    for(int i = 0; i < h->capacity; i++) {
        h->heap[i].vertex = 0;
        h->heap[i].distance = INF;
    }
}

void resize_heap(HeapType* h) {
    int new_capacity = h->capacity * 2;
    element* new_heap = (element*)realloc(h->heap, sizeof(element) * new_capacity);
    
    if (new_heap == NULL) {
        perror("Failed to resize heap");
        return;
    }
    
    h->heap = new_heap;
    h->capacity = new_capacity;
}

void insert_min_heap(HeapType* h, element item)
{
    if (h->heap_size >= h->capacity - 1) {
        resize_heap(h);
    }
    int i;
    i = ++(h->heap_size);

    // 부모 노드와 비교하면서 거리가 더 작은 경우 위로 이동
    while ((i != 1) && (item.distance < h->heap[i / 2].distance)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

element delete_min_heap(HeapType* h)
{
    if (is_empty(h)) {
        perror("Heap is empty");
        element err = {-1, INF};
        return err;
    }

    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    
    while (child <= h->heap_size) {
        // 두 자식 중 더 작은 거리를 가진 자식을 선택
        if ((child < h->heap_size) && 
            (h->heap[child].distance > h->heap[child + 1].distance)) 
            child++;
            
        // 마지막 노드가 자식 노드보다 작거나 같으면 중단
        if (temp.distance <= h->heap[child].distance) 
            break;

        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

int is_empty(HeapType* h)
{
    return (h->heap_size == 0);
}

void destroy_heap(HeapType* h)
{
    free(h->heap);
    free(h);
}

// 이진 힙 모듈 끝

// 다익스트라 알고리즘 모듈
// Dijkstra 알고리즘 관련 데이터를 관리하는 구조체
typedef struct {
    int* distance;   // 시작 정점으로부터의 최단 거리
    int* visited;    // 정점 방문 여부
    int size;        // 그래프의 정점 수
} DijkstraData;

// Dijkstra 데이터 구조 생성
DijkstraData* createDijkstraData(int V) {
    DijkstraData* data = (DijkstraData*)malloc(sizeof(DijkstraData));
    if (!data) {
        perror("Failed to allocate DijkstraData");
        return NULL;
    }

    data->distance = (int*)malloc(sizeof(int) * (V + 1));
    data->visited = (int*)malloc(sizeof(int) * (V + 1));
    
    if (!data->distance || !data->visited) {
        perror("Failed to allocate arrays");
        free(data->distance);
        free(data->visited);
        free(data);
        return NULL;
    }

    data->size = V;
    
    // 초기화: 모든 거리를 INF로, 방문 상태를 0으로 설정
    for (int i = 0; i <= V; i++) {
        data->distance[i] = INF;
        data->visited[i] = 0;
    }
    
    return data;
}

// Dijkstra 데이터 구조 해제
void destroyDijkstraData(DijkstraData* data) {
    if (data) {
        free(data->distance);
        free(data->visited);
        free(data);
    }
}

// Dijkstra 알고리즘 실행
DijkstraData* dijkstra(Graph* graph, int start) {
    if (!graph || start < 1 || start > graph->V) {
        return NULL;
    }

    // Dijkstra 데이터 구조 생성 및 초기화
    DijkstraData* data = createDijkstraData(graph->V);
    if (!data) return NULL;

    // 시작 정점의 거리를 0으로 초기화
    data->distance[start] = 0;

    // 우선순위 큐 생성
    HeapType* pq = create(graph->V);
    if (!pq) {
        destroyDijkstraData(data);
        return NULL;
    }

    // 시작 정점을 우선순위 큐에 삽입
    element startElement = {start, 0};
    insert_min_heap(pq, startElement);

    // 메인 알고리즘 루프
    while (!is_empty(pq)) {
        element current = delete_min_heap(pq);
        int current_vertex = current.vertex;

        // 이미 처리된 정점은 건너뛰기
        if (data->visited[current_vertex]) continue;
        
        // 현재 정점을 방문 처리
        data->visited[current_vertex] = 1;

        // 현재 정점과 연결된 모든 간선에 대해 최단 거리 갱신
        Node* adjacent = graph->array[current_vertex];
        while (adjacent != NULL) {
            int next = adjacent->vertex;
            int weight = adjacent->weight;

            // 미방문 정점이고 더 짧은 경로를 발견한 경우 거리 갱신
            if (!data->visited[next] && 
                data->distance[current_vertex] != INF && 
                data->distance[current_vertex] + weight < data->distance[next]) {
                
                data->distance[next] = data->distance[current_vertex] + weight;
                element nextElement = {next, data->distance[next]};
                insert_min_heap(pq, nextElement);
            }
            adjacent = adjacent->next;
        }
    }

    // 우선순위 큐 메모리 해제
    destroy_heap(pq);
    return data;
}

// 결과 출력 함수
void printResult(DijkstraData* data) {
    if (!data) return;
    
    for (int i = 1; i <= data->size; i++) {
        if (data->distance[i] == INF)
            printf("INF\n");
        else
            printf("%d\n", data->distance[i]);
    }
}

// 다익스트라 알고리즘 모듈 끝

int main() {
    Graph* graph = readGraphInput();
    if (!graph) return 1;

    int start;
    if (scanf("%d", &start) != 1) {
        destroyGraph(graph);
        return 1;
    }

    DijkstraData* result = dijkstra(graph, start);
    if (result) {
        printResult(result);
        destroyDijkstraData(result);
    }

    destroyGraph(graph);
    return 0;
}