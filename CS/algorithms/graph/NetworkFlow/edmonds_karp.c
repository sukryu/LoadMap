/**
 * edmonds_karp.c
 *
 * 고도화된 Edmonds-Karp 알고리즘 구현 예제
 * - 이 파일은 2차원 인접 행렬로 표현된 가중치 방향 그래프에서 소스(Source)에서 싱크(Sink)까지의 최대 유량(Maximum Flow)을 계산하는 Edmonds-Karp 알고리즘을 구현합니다.
 * - Edmonds-Karp 알고리즘은 Ford-Fulkerson 방법의 한 구현으로, BFS를 사용하여 최단 증가 경로(최소 간선 수 경로)를 찾아, 증가 경로를 통해 유량을 보냅니다.
 * - 알고리즘의 주요 단계는 다음과 같습니다:
 *     1. 원본 그래프의 복사본을 잔여 그래프(residual graph)로 초기화합니다.
 *     2. BFS를 통해 소스에서 싱크까지의 증가 경로를 찾고, 경로가 존재하면 그 경로 상의 최소 잔여 용량(병목 용량)을 결정합니다.
 *     3. 경로에 따라 잔여 용량을 업데이트하고 총 유량을 증가시킵니다.
 *     4. 더 이상 증가 경로를 찾을 수 없을 때까지 반복합니다.
 *
 * 컴파일 예시: gcc -Wall -O2 edmonds_karp.c -o edmonds_karp
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

/**
 * bfs - 잔여 그래프에서 소스에서 싱크까지의 증가 경로를 찾기 위한 BFS 함수.
 * @rGraph: 잔여 그래프 (2차원 배열: rGraph[u][v]는 u에서 v로 남은 용량)
 * @V: 그래프의 정점 수
 * @s: 소스 정점 번호
 * @t: 싱크 정점 번호
 * @parent: 증가 경로를 기록할 배열. parent[v]는 v의 부모 정점.
 *
 * 반환값: 증가 경로가 존재하면 1, 없으면 0.
 *
 * 이 함수는 BFS를 사용하여 잔여 그래프에서 소스(s)부터 싱크(t)까지 도달 가능한 경로가 있는지 확인하며,
 * 경로가 존재하면 parent[] 배열에 경로 정보를 기록합니다.
 */
int bfsEdmondsKarp(int **rGraph, int V, int s, int t, int parent[]) {
    int *visited = (int *)calloc(V, sizeof(int));
    if (!visited) {
        fprintf(stderr, "메모리 할당 실패 (bfsEdmondsKarp: visited)\n");
        exit(EXIT_FAILURE);
    }

    // 큐 구현: 정점을 저장할 배열, 최대 V개의 정점을 저장할 수 있음.
    int *queue = (int *)malloc(V * sizeof(int));
    if (!queue) {
        fprintf(stderr, "메모리 할당 실패 (bfsEdmondsKarp: queue)\n");
        free(visited);
        exit(EXIT_FAILURE);
    }
    int front = 0, rear = 0;

    // 시작 정점을 큐에 삽입
    queue[rear++] = s;
    visited[s] = 1;
    parent[s] = -1;

    while (front < rear) {
        int u = queue[front++];
        // 소스에서 u까지 도달했다고 가정하고, u의 모든 정점을 검사합니다.
        for (int v = 0; v < V; v++) {
            // 아직 방문하지 않았으며, u->v로 남은 용량이 양수이면 v를 방문합니다.
            if (!visited[v] && rGraph[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = 1;
                // 싱크에 도달하면 바로 종료
                if (v == t) {
                    free(visited);
                    free(queue);
                    return 1;
                }
            }
        }
    }
    free(visited);
    free(queue);
    return 0; // 증가 경로 없음
}

/**
 * edmondsKarp - Edmonds-Karp 알고리즘을 사용하여 소스에서 싱크까지의 최대 유량을 계산합니다.
 * @graph: 원본 그래프의 2차원 인접 행렬 (graph[u][v]는 u에서 v로의 용량)
 * @V: 그래프의 정점 수
 * @s: 소스 정점 번호
 * @t: 싱크 정점 번호
 *
 * 반환값: 최대 유량 (정수)
 *
 * 이 함수는 잔여 그래프를 업데이트하면서 BFS를 이용해 증가 경로를 반복적으로 찾고, 
 * 각 경로에서 병목 용량(최소 잔여 용량)을 찾아 전체 유량에 더합니다.
 */
int edmondsKarp(int **graph, int V, int s, int t) {
    int u, v;
    
    // 잔여 그래프 초기화: 원본 그래프의 복사본을 생성
    int **rGraph = (int **)malloc(V * sizeof(int *));
    if (!rGraph) {
        fprintf(stderr, "메모리 할당 실패 (edmondsKarp: rGraph)\n");
        exit(EXIT_FAILURE);
    }
    for (u = 0; u < V; u++) {
        rGraph[u] = (int *)malloc(V * sizeof(int));
        if (!rGraph[u]) {
            fprintf(stderr, "메모리 할당 실패 (edmondsKarp: rGraph[%d])\n", u);
            for (int k = 0; k < u; k++) free(rGraph[k]);
            free(rGraph);
            exit(EXIT_FAILURE);
        }
        for (v = 0; v < V; v++) {
            rGraph[u][v] = graph[u][v];
        }
    }
    
    int *parent = (int *)malloc(V * sizeof(int));
    if (!parent) {
        fprintf(stderr, "메모리 할당 실패 (edmondsKarp: parent)\n");
        exit(EXIT_FAILURE);
    }
    
    int maxFlow = 0;

    // 반복: 증가 경로가 존재하는 동안 BFS를 통해 경로를 찾습니다.
    while (bfsEdmondsKarp(rGraph, V, s, t, parent)) {
        // 경로 상의 최소 잔여 용량(병목 용량)을 계산합니다.
        int pathFlow = INF;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            if (rGraph[u][v] < pathFlow)
                pathFlow = rGraph[u][v];
        }
        
        // 경로를 따라 잔여 용량 업데이트: 
        // - 각 간선의 용량을 감소시키고, 역방향 간선의 용량을 증가시킵니다.
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }
        
        // 전체 유량에 경로 유량을 추가합니다.
        maxFlow += pathFlow;
    }
    
    // 동적 메모리 해제
    for (u = 0; u < V; u++)
        free(rGraph[u]);
    free(rGraph);
    free(parent);
    
    return maxFlow;
}

/**
 * main - Edmonds-Karp 알고리즘 데모
 *
 * 이 함수는 예제 그래프를 생성하고, 소스에서 싱크까지의 최대 유량을 계산하여 출력합니다.
 */
int main(void) {
    /*
     * 예제 그래프:
     * 정점 수: 6
     * 인접 행렬 표현:
     *     0   16   13    0    0    0
     *     0    0   10   12    0    0
     *     0    4    0    0   14    0
     *     0    0    9    0    0   20
     *     0    0    0    7    0    4
     *     0    0    0    0    0    0
     */
    int V = 6;
    int s = 0;
    int t = 5;
    
    // 동적 2차원 배열 할당 (V x V)
    int **graph = (int **)malloc(V * sizeof(int *));
    if (!graph) {
        fprintf(stderr, "메모리 할당 실패 (main: graph)\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < V; i++) {
        graph[i] = (int *)malloc(V * sizeof(int));
        if (!graph[i]) {
            fprintf(stderr, "메모리 할당 실패 (main: graph[%d])\n", i);
            for (int j = 0; j < i; j++) free(graph[j]);
            free(graph);
            exit(EXIT_FAILURE);
        }
    }
    
    // 그래프 초기화 (예제 값)
    int tempGraph[6][6] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = tempGraph[i][j];
    
    int maxFlow = edmondsKarp(graph, V, s, t);
    printf("최대 유량 (Edmonds-Karp): %d\n", maxFlow);
    
    // 동적 할당된 그래프 메모리 해제
    for (int i = 0; i < V; i++)
        free(graph[i]);
    free(graph);
    
    return 0;
}