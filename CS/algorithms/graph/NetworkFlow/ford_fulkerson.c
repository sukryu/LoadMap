/**
 * ford_fulkerson.c
 *
 * 고도화된 Ford-Fulkerson 알고리즘 구현 예제
 * - 이 파일은 2차원 인접 행렬로 표현된 가중치 방향 그래프에서 최대 유량(Maximum Flow)을 계산하는 Ford-Fulkerson 알고리즘을 구현합니다.
 * - 알고리즘은 DFS(깊이 우선 탐색)를 사용하여 소스(Source)에서 싱크(Sink)까지의 증가 경로(augmenting path)를 찾고,
 *   해당 경로를 따라 유량을 보냅니다.
 * - 반복적으로 증가 경로를 찾지 못할 때까지 과정을 수행하며, 이때의 총 유량이 최대 유량이 됩니다.
 *
 * 주요 단계:
 *  1. 원본 그래프의 복사본을 잔여 그래프(residual graph)로 초기화합니다.
 *  2. DFS를 통해 소스에서 싱크까지의 증가 경로를 찾습니다.
 *  3. 경로 상의 최소 잔여 용량(병목 용량)을 찾아 유량을 증가시키고, 잔여 그래프를 업데이트합니다.
 *  4. 더 이상 증가 경로를 찾을 수 없을 때까지 반복합니다.
 *
 * 컴파일 예시: gcc -Wall -O2 ford_fulkerson.c -o ford_fulkerson
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

/**
 * dfs - 잔여 그래프에서 소스에서 싱크까지 경로를 찾기 위한 DFS 함수.
 * @rGraph: 잔여 그래프 (2차원 배열: rGraph[u][v]는 u에서 v로 남은 용량)
 * @V: 그래프의 정점 수
 * @s: 소스 정점 번호
 * @t: 싱크 정점 번호
 * @parent: 증가 경로를 저장할 배열. parent[v]는 v의 부모 정점.
 *
 * 반환값: 증가 경로가 존재하면 1, 아니면 0.
 *
 * 이 함수는 DFS를 사용하여 잔여 그래프에서 소스(s)부터 싱크(t)까지 도달 가능한 경로가 있는지 확인하며,
 * 경로가 존재하면 parent[] 배열에 경로 정보를 저장합니다.
 */
int dfs(int **rGraph, int V, int s, int t, int parent[]) {
    // visited 배열 초기화 (동적 메모리 사용, 꼭 free 필요)
    int *visited = (int *)calloc(V, sizeof(int));
    if (!visited) {
        fprintf(stderr, "메모리 할당 실패 (dfs: visited)\n");
        exit(EXIT_FAILURE);
    }
    
    // 스택 구현: 동적 배열 사용 (여기서는 간단한 배열을 사용)
    int *stack = (int *)malloc(V * sizeof(int));
    if (!stack) {
        fprintf(stderr, "메모리 할당 실패 (dfs: stack)\n");
        free(visited);
        exit(EXIT_FAILURE);
    }
    int top = -1;
    
    // 시작 정점 s를 스택에 push
    stack[++top] = s;
    visited[s] = 1;
    parent[s] = -1;
    
    while (top >= 0) {
        int u = stack[top--];
        // 만약 싱크에 도달했다면 DFS 종료
        if (u == t) {
            free(visited);
            free(stack);
            return 1;
        }
        // 인접 정점을 탐색: 모든 v에 대해 잔여 용량이 양수이면 push
        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                stack[++top] = v;
                parent[v] = u;
                visited[v] = 1;
            }
        }
    }
    
    free(visited);
    free(stack);
    return 0; // 증가 경로 없음
}

/**
 * fordFulkerson - Ford-Fulkerson 알고리즘을 사용하여 소스에서 싱크까지의 최대 유량을 계산합니다.
 * @graph: 원본 그래프 (2차원 인접 행렬, graph[u][v]는 u에서 v로의 용량)
 * @V: 그래프의 정점 수
 * @s: 소스 정점 번호
 * @t: 싱크 정점 번호
 *
 * 반환값: 최대 유량 (정수)
 *
 * 이 함수는 잔여 그래프를 업데이트하면서 DFS를 이용해 증가 경로를 반복적으로 찾습니다.
 * 각 경로에서 병목 용량(최소 잔여 용량)을 구해 전체 유량에 더하고,
 * 경로를 통해 잔여 용량을 갱신합니다.
 */
int fordFulkerson(int **graph, int V, int s, int t) {
    int u, v;
    
    // 잔여 그래프 초기화: 원본 그래프의 복사본을 사용합니다.
    int **rGraph = (int **)malloc(V * sizeof(int *));
    if (!rGraph) {
        fprintf(stderr, "메모리 할당 실패 (fordFulkerson: rGraph)\n");
        exit(EXIT_FAILURE);
    }
    for (u = 0; u < V; u++) {
        rGraph[u] = (int *)malloc(V * sizeof(int));
        if (!rGraph[u]) {
            fprintf(stderr, "메모리 할당 실패 (fordFulkerson: rGraph[%d])\n", u);
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
        fprintf(stderr, "메모리 할당 실패 (fordFulkerson: parent)\n");
        exit(EXIT_FAILURE);
    }
    
    int maxFlow = 0;
    
    // 반복: DFS를 통해 증가 경로가 존재하는 동안
    while (dfs(rGraph, V, s, t, parent)) {
        // 경로 상의 최소 잔여 용량을 찾습니다.
        int pathFlow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            if (rGraph[u][v] < pathFlow)
                pathFlow = rGraph[u][v];
        }
        
        // 경로를 따라 유량 업데이트: 잔여 용량 감소, 역방향 간선의 잔여 용량 증가
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }
        
        // 최대 유량에 경로 유량 추가
        maxFlow += pathFlow;
    }
    
    // 동적 할당된 메모리 해제
    for (u = 0; u < V; u++)
        free(rGraph[u]);
    free(rGraph);
    free(parent);
    
    return maxFlow;
}

/**
 * main - Ford-Fulkerson 알고리즘 데모
 *
 * 이 함수는 예제 그래프를 생성하고, 최대 유량을 계산하여 결과를 출력합니다.
 */
int main(void) {
    /*
     * 예제 그래프:
     * 정점 수: 6
     * 인접 행렬 표현:
     *     0   16   13    0    0    0
     *     0    0    10   12    0    0
     *     0    4     0    0    14   0
     *     0    0     9    0     0    20
     *     0    0     0    7     0    4
     *     0    0     0    0     0    0
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
    
    // 그래프 초기화
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
    
    int maxFlow = fordFulkerson(graph, V, s, t);
    printf("최대 유량: %d\n", maxFlow);
    
    // 동적 할당된 그래프 메모리 해제
    for (int i = 0; i < V; i++)
        free(graph[i]);
    free(graph);
    
    return 0;
}
