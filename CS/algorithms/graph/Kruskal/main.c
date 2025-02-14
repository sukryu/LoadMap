/**
 * main.c
 *
 * 고도화된 크루스칼 알고리즘(Kruskal's Algorithm) 구현 예제
 * - 이 파일은 간선 리스트로 표현된 가중치 방향/무방향 그래프에서 최소 신장 트리(MST)를 찾는 크루스칼 알고리즘을 구현합니다.
 * - 그래프의 모든 간선을 가중치 순으로 정렬한 후, Union-Find (Disjoint Set) 자료구조를 사용하여 사이클을 방지하면서
 *   간선을 선택하여 MST를 구성합니다.
 * - 실무 환경에서 사용할 수 있도록 동적 메모리 관리, 에러 처리 및 Union-Find 최적화(경로 압축, 랭크)를 포함하여 작성되었습니다.
 *
 * 컴파일 예시: gcc -Wall -O2 kruskal.c -o kruskal
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*---------------- Data Structures ----------------*/

// Edge 구조체: 그래프의 간선을 나타냄
typedef struct Edge {
    int src;      // 시작 정점
    int dest;     // 도착 정점
    int weight;   // 간선의 가중치
} Edge;

// Graph 구조체: 간선 리스트를 사용하는 가중치 그래프
typedef struct Graph {
    int V;      // 정점의 수
    int E;      // 간선의 수
    Edge* edges;  // 간선 배열 (동적 할당)
} Graph;

/*---------------- Graph Utility Functions ----------------*/

/**
 * createGraph - V개의 정점과 E개의 간선을 가진 그래프를 생성합니다.
 * @V: 정점의 수
 * @E: 간선의 수
 *
 * 반환값: 동적 할당된 Graph 포인터.
 *         (간선 배열은 사용 후 free()로 해제해야 합니다.)
 */
Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    if (!graph) {
        fprintf(stderr, "메모리 할당 실패 (createGraph)\n");
        exit(EXIT_FAILURE);
    }
    graph->V = V;
    graph->E = E;
    graph->edges = (Edge*) malloc(E * sizeof(Edge));
    if (!graph->edges) {
        fprintf(stderr, "메모리 할당 실패 (graph->edges)\n");
        free(graph);
        exit(EXIT_FAILURE);
    }
    return graph;
}

/*---------------- Union-Find (Disjoint Set) Structures ----------------*/

// Subset 구조체: 각 정점에 대한 부모와 랭크 정보를 저장
typedef struct Subset {
    int parent;
    int rank;
} Subset;

/**
 * find - 경로 압축을 사용하여, 주어진 정점 i가 속한 집합의 대표(parent)를 반환합니다.
 * @subsets: Subset 배열
 * @i: 정점 번호
 *
 * 반환값: 집합의 대표 번호
 */
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

/**
 * unionSets - 두 집합을 랭크 기반으로 합칩니다.
 * @subsets: Subset 배열
 * @x: 집합 x의 대표 정점 번호
 * @y: 집합 y의 대표 정점 번호
 */
void unionSets(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (xroot == yroot)
        return;
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

/*---------------- Edge Sorting ----------------*/

/**
 * compareEdges - qsort를 위한 비교 함수
 * @a, @b: 비교할 Edge 포인터
 *
 * 반환값: 간선의 가중치 차이를 반환하여 오름차순 정렬을 수행합니다.
 */
int compareEdges(const void* a, const void* b) {
    Edge* edgeA = (Edge*) a;
    Edge* edgeB = (Edge*) b;
    return edgeA->weight - edgeB->weight;
}

/*---------------- Kruskal's Algorithm ----------------*/

/**
 * kruskalMST - 크루스칼 알고리즘을 사용하여 최소 신장 트리(MST)를 구성합니다.
 * @graph: 입력 그래프 (간선 리스트 형태)
 * @mstEdgeCount: MST에 포함된 간선 수를 출력 (정점 수 - 1 이어야 함)
 * @totalWeight: MST의 총 가중치를 출력
 *
 * 반환값: MST를 구성하는 Edge 배열 (동적 할당).
 *         만약 MST 구성이 불가능하면 NULL을 반환합니다.
 *         반환된 배열은 호출자가 free()로 메모리 해제해야 합니다.
 */
Edge* kruskalMST(Graph* graph, int* mstEdgeCount, int* totalWeight) {
    int V = graph->V;
    int E = graph->E;
    
    // 결과 배열: MST 간선들 (최대 V-1 간선)
    Edge* result = (Edge*) malloc((V - 1) * sizeof(Edge));
    if (!result) {
        fprintf(stderr, "메모리 할당 실패 (kruskalMST: result)\n");
        exit(EXIT_FAILURE);
    }
    
    // 간선들을 가중치 오름차순으로 정렬
    qsort(graph->edges, E, sizeof(Edge), compareEdges);
    
    // Union-Find를 위한 집합 초기화
    Subset* subsets = (Subset*) malloc(V * sizeof(Subset));
    if (!subsets) {
        fprintf(stderr, "메모리 할당 실패 (kruskalMST: subsets)\n");
        free(result);
        exit(EXIT_FAILURE);
    }
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    
    int e = 0; // MST에 포함된 간선 수
    int i = 0; // 간선 배열 인덱스
    *totalWeight = 0;
    
    // 간선 배열에서 순차적으로 간선을 선택
    while (e < V - 1 && i < E) {
        Edge next_edge = graph->edges[i++];
        
        // 사이클 형성을 피하기 위해, 선택된 간선의 두 정점의 집합을 확인
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
        
        // 두 정점이 서로 다른 집합에 있다면, 간선을 MST에 추가하고 집합을 합칩니다.
        if (x != y) {
            result[e++] = next_edge;
            *totalWeight += next_edge.weight;
            unionSets(subsets, x, y);
        }
    }
    
    // MST 구성 여부 확인: MST에 포함된 간선 수가 V-1이어야 합니다.
    if (e != V - 1) {
        fprintf(stderr, "MST를 구성할 수 없습니다. 그래프가 연결되어 있지 않습니다.\n");
        free(result);
        result = NULL;
    }
    
    *mstEdgeCount = e;
    free(subsets);
    return result;
}

/*---------------- Free Graph ----------------*/

/**
 * freeGraph - 그래프에 할당된 모든 메모리를 해제합니다.
 * @graph: 입력 그래프 포인터
 */
void freeGraph(Graph* graph) {
    if (graph) {
        if (graph->edges)
            free(graph->edges);
        free(graph);
    }
}

/*---------------- main 함수 (데모) ----------------*/
/**
 * main - 크루스칼 알고리즘 데모
 *
 * 이 함수는 예제 그래프를 생성하고, 간선 목록을 초기화한 후,
 * 크루스칼 알고리즘을 통해 최소 신장 트리를 구성하여 MST 간선과 총 가중치를 출력합니다.
 */
int main(void) {
    // 예제 그래프: 정점 수 4, 간선 수 5
    int V = 4, E = 5;
    Graph* graph = createGraph(V, E);
    
    // 간선 목록 초기화
    graph->edges[0] = (Edge){0, 1, 10};
    graph->edges[1] = (Edge){0, 2, 6};
    graph->edges[2] = (Edge){0, 3, 5};
    graph->edges[3] = (Edge){1, 3, 15};
    graph->edges[4] = (Edge){2, 3, 4};
    
    int mstEdgeCount = 0;
    int totalWeight = 0;
    Edge* mst = kruskalMST(graph, &mstEdgeCount, &totalWeight);
    
    if (mst == NULL) {
        printf("MST를 구성할 수 없습니다. 그래프가 연결되어 있지 않습니다.\n");
    } else {
        printf("MST 간선 수: %d\n", mstEdgeCount);
        printf("MST 총 가중치: %d\n", totalWeight);
        printf("MST 간선 목록:\n");
        for (int i = 0; i < mstEdgeCount; i++) {
            printf("간선 %d: %d -- %d (가중치 %d)\n", i, mst[i].src, mst[i].dest, mst[i].weight);
        }
        free(mst);
    }
    
    freeGraph(graph);
    return 0;
}
