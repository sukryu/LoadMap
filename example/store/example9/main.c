#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define N_MAX 201
#define M_MAX 5000
#define F_MAX 1000000001
#define CAPACITY_COST_MAX 100001

// 간선 구조체
typedef struct Edge {
    int to;             // 도착 정점
    int capacity;       // 용량
    int cost;          // 비용
    int flow;          // 현재 흐르는 유량
    struct Edge* reverse;      // 역방향 간선의 포인터
} Edge;

// 그래프 구조체
typedef struct {
    Edge* edges[N_MAX][N_MAX];  // 간선 정보를 저장하는 2차원 배열
    int edge_count[N_MAX];      // 각 정점에서 나가는 간선의 개수
} Graph;

// SPFA 알고리즘에 사용할 큐 구조체
typedef struct {
    int data[N_MAX * M_MAX];
    int front, rear;
} Queue;

// 그래프 초기화 함수
void init_graph(Graph* g) {
    for (int i = 0; i < N_MAX; i++) {
        g->edge_count[i] = 0;
        for (int j = 0; j < N_MAX; j++) {
            g->edges[i][j] = NULL;
        }
    }
}

// 간선 추가 함수
void add_edge(Graph* g, int from, int to, int capacity, int cost) {
    // 정방향 간선 생성
    Edge* e1 = (Edge*)malloc(sizeof(Edge));
    e1->to = to;
    e1->capacity = capacity;
    e1->cost = cost;
    e1->flow = 0;
    
    // 역방향 간선 생성
    Edge* e2 = (Edge*)malloc(sizeof(Edge));
    e2->to = from;
    e2->capacity = 0;
    e2->cost = -cost;
    e2->flow = 0;
    
    // 역방향 간선 연결
    e1->reverse = e2;
    e2->reverse = e1;
    
    // 그래프에 간선 추가
    g->edges[from][g->edge_count[from]++] = e1;
    g->edges[to][g->edge_count[to]++] = e2;
}

void init_queue(Queue* q) {
    q->front = q->rear = 0;
}

void push(Queue* q, int value) {
    q->data[q->rear++] = value;
}

int pop(Queue* q) {
    return q->data[q->front++];
}

bool is_empty(Queue* q) {
    return q->front == q->rear;
}

// SPFA 알고리즘으로 최소 비용 경로 찾기
bool find_path(Graph* g, int N, int* parent, int* parent_edge, long long* dist) {
    Queue q;
    bool in_queue[N_MAX] = {false};
    Edge* edge_to[N_MAX];

    for (int i = 0; i <= N; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }

    init_queue(&q);
    dist[1] = 0;
    push(&q, 1);
    in_queue[1] = true;

    while (!is_empty(&q)) {
        int curr = pop(&q);
        in_queue[curr] = false;

        for (int i = 0; i < g->edge_count[curr]; i++) {
            Edge* e = g->edges[curr][i];
            int next = e->to;

            if (e->capacity - e->flow > 0 && dist[next] > dist[curr] + e->cost) {
                dist[next] = dist[curr] + e->cost;
                parent[next] = curr;
                parent_edge[next] = i;

                if (!in_queue[next]) {
                    push(&q, next);
                    in_queue[next] = true;
                }
            }
        }
    }

    return dist[N] != INT_MAX;
}

// 최소 비용 최대 유량 알고리즘
long long mcmf(Graph* g, int N, int F) {
    long long total_cost = 0;
    int total_flow = 0;
    int parent[N_MAX], parent_edge[N_MAX];
    long long dist[N_MAX];
    
    while (total_flow < F) {
        if (!find_path(g, N, parent, parent_edge, dist)) {
            return -1;  // F만큼의 유량을 보낼 수 없음
        }
        
        // 현재 경로로 보낼 수 있는 최대 유량 계산
        int flow = F - total_flow;
        int curr = N;
        
        while (curr != 1) {
            int prev = parent[curr];
            Edge* e = g->edges[prev][parent_edge[curr]];
            flow = flow < (e->capacity - e->flow) ? flow : (e->capacity - e->flow);
            curr = prev;
        }
        
        // 유량을 보내고 비용 계산
        curr = N;
        while (curr != 1) {
            int prev = parent[curr];
            Edge* e = g->edges[prev][parent_edge[curr]];
            e->flow += flow;
            e->reverse->flow -= flow;
            total_cost += (long long)flow * e->cost;
            curr = prev;
        }
        
        total_flow += flow;
    }
    
    return total_cost;
}

int main() {
    int N = 0, M = 0, F = 0;
    Graph graph;
    
    if (scanf("%d %d %d", &N, &M, &F) != 3) {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }
    
    if (N < 2 || N > N_MAX || M < 1 || M > M_MAX || F < 1 || F > F_MAX) {
        fprintf(stderr, "Error: out of range\n");
        return 1;
    }
    
    init_graph(&graph);
    
    for (int i = 0; i < M; i++) {
        int u, v, capacity, cost;
        if (scanf("%d %d %d %d", &u, &v, &capacity, &cost) != 4) {
            fprintf(stderr, "Error: invalid input\n");
            return 1;
        }
        
        if (u < 1 || u > N || v < 1 || v > N || u == v ||
            capacity < 1 || capacity >= CAPACITY_COST_MAX ||
            cost < 0 || cost >= CAPACITY_COST_MAX) {
            fprintf(stderr, "Error: out of range\n");
            return 1;
        }
        
        add_edge(&graph, u, v, capacity, cost);
    }
    
    long long result = mcmf(&graph, N, F);
    printf("%lld\n", result);
    
    // 메모리 해제
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < graph.edge_count[i]; j++) {
            free(graph.edges[i][j]);
        }
    }
    
    return 0;
}