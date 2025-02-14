/**
 * main.c
 *
 * 고도화된 벨만-포드 알고리즘(Bellman-Ford Algorithm) 구현 예제
 * - 이 파일은 간선 리스트로 표현된 가중치 방향 그래프에서 단일 시작점으로부터
 *   다른 모든 정점까지의 최단 경로를 계산하는 벨만-포드 알고리즘을 구현합니다.
 * - 음의 가중치 간선을 포함한 그래프에서도 동작하며, 음의 사이클을 감지할 수 있습니다.
 * - 실무 환경에서 사용할 수 있도록 동적 메모리 관리, 에러 처리 및 결과 검증 기능을 포함하여 작성되었습니다.
 *
 * 컴파일 예시: gcc -Wall -O2 bellman_ford.c -o bellman_ford
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*---------------- Data Structures ----------------*/

// Edge 구조체: 그래프의 간선을 나타냄
typedef struct {
    int src;     // 시작 정점
    int dest;    // 도착 정점
    int weight;  // 간선 가중치
} Edge;

// Graph 구조체: 간선 리스트를 사용하는 가중치 방향 그래프
typedef struct {
    int V;       // 정점의 수
    int E;       // 간선의 수
    Edge* edges; // 간선 배열 (동적 할당)
} Graph;

/*---------------- Graph Utility Functions ----------------*/

/**
 * createGraph - V개의 정점과 E개의 간선을 가진 그래프를 생성합니다.
 * @V: 정점의 수
 * @E: 간선의 수
 *
 * 반환값: 동적 할당된 Graph 포인터
 *         (간선 배열은 호출 전에 적절히 초기화되어야 하며, 사용 후 free()로 해제해야 합니다.)
 */
Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        fprintf(stderr, "메모리 할당 실패 (createGraph)\n");
        exit(EXIT_FAILURE);
    }
    graph->V = V;
    graph->E = E;
    graph->edges = (Edge*)malloc(E * sizeof(Edge));
    if (!graph->edges) {
        fprintf(stderr, "메모리 할당 실패 (graph->edges)\n");
        free(graph);
        exit(EXIT_FAILURE);
    }
    return graph;
}

/*---------------- Bellman-Ford Algorithm ----------------*/

/**
 * bellmanFord - 벨만-포드 알고리즘을 사용하여 시작 정점 src로부터 각 정점까지의 최단 경로를 계산합니다.
 * @graph: 입력 그래프 (간선 리스트로 표현)
 * @src: 시작 정점 번호
 * @dist: 각 정점까지의 최단 거리를 저장할 배열 (크기: graph->V)
 *
 * 반환값: 음의 사이클이 존재하면 -1을, 그렇지 않으면 0을 반환합니다.
 *
 * 이 함수는 모든 정점의 최단 거리를 계산하고, 음의 사이클을 탐지합니다.
 * 도달 불가능한 정점의 거리는 INT_MAX로 유지됩니다.
 */
int bellmanFord(Graph* graph, int src, int* dist) {
    int V = graph->V;
    int E = graph->E;

    // 모든 정점의 거리를 무한대로 초기화, src의 거리는 0으로 설정
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // V-1번 모든 간선을 완화(relaxation)
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edges[j].src;
            int v = graph->edges[j].dest;
            int weight = graph->edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    // 음의 사이클 탐지: 한 번 더 완화 시도가 가능하면 음의 사이클 존재
    for (int j = 0; j < E; j++) {
        int u = graph->edges[j].src;
        int v = graph->edges[j].dest;
        int weight = graph->edges[j].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            return -1; // 음의 사이클 발견
        }
    }
    return 0;
}

/*---------------- main 함수 (데모) ----------------*/

int main(void) {
    /*
     * 예제 그래프:
     * 정점 수: 5, 간선 수: 8
     * 간선 목록:
     *  0 -> 1 (6)
     *  0 -> 2 (7)
     *  1 -> 2 (8)
     *  1 -> 3 (5)
     *  1 -> 4 (-4)
     *  2 -> 3 (-3)
     *  2 -> 4 (9)
     *  3 -> 1 (-2)
     *  4 -> 0 (2)
     *  4 -> 3 (7)
     *
     * (위 목록은 10개의 간선을 가진 그래프로, 음의 가중치 간선이 있으나 음의 사이클은 없습니다.)
     */
    int V = 5;
    int E = 10;
    Graph* graph = createGraph(V, E);

    // 간선 입력 (간선 인덱스 0부터 E-1)
    graph->edges[0] = (Edge){0, 1, 6};
    graph->edges[1] = (Edge){0, 2, 7};
    graph->edges[2] = (Edge){1, 2, 8};
    graph->edges[3] = (Edge){1, 3, 5};
    graph->edges[4] = (Edge){1, 4, -4};
    graph->edges[5] = (Edge){2, 3, -3};
    graph->edges[6] = (Edge){2, 4, 9};
    graph->edges[7] = (Edge){3, 1, -2};
    graph->edges[8] = (Edge){4, 0, 2};
    graph->edges[9] = (Edge){4, 3, 7};

    int src = 0;
    int* dist = (int*)malloc(V * sizeof(int));
    if (!dist) {
        fprintf(stderr, "메모리 할당 실패 (dist 배열)\n");
        free(graph->edges);
        free(graph);
        exit(EXIT_FAILURE);
    }

    int result = bellmanFord(graph, src, dist);
    if (result == -1) {
        printf("그래프에 음의 사이클이 존재합니다. 최단 경로를 계산할 수 없습니다.\n");
    } else {
        printf("정점 %d에서 시작하는 최단 경로 거리:\n", src);
        for (int i = 0; i < V; i++) {
            printf("정점 %d: ", i);
            if (dist[i] == INT_MAX)
                printf("도달 불가");
            else
                printf("%d", dist[i]);
            printf("\n");
        }
    }

    free(dist);
    free(graph->edges);
    free(graph);
    return 0;
}