# 그래프(Graph) 자료구조

## 1. 기본 개념

### 1.1 정의와 용어
* **그래프(Graph)** 는 정점(Vertex)과 간선(Edge)의 집합으로 이루어진 자료구조
    - G = (V, E) 로 표현
    - V: 정점(Vertex) 집합
    - E: 간선(Edge) 집합 → (u, v) 형태로 두 정점을 연결

* 주요 용어
    1. **차수(Degree)**: 하나의 정점에 연결된 간선의 수
        - 유향 그래프의 경우: 진입 차수(in-degree)와 진출 차수(out-degree)로 구분
    
    2. **경로(Path)**: 한 정점에서 다른 정점으로 가는 정점들의 순서열
        - 단순 경로(Simple Path): 같은 정점을 두 번 방문하지 않는 경로
    
    3. **사이클(Cycle)**: 시작점과 끝점이 같은 경로
    
    4. **연결성(Connectivity)**
        - 무향 그래프에서 두 정점 사이에 경로가 존재하면 '연결됨'
        - 모든 정점 쌍이 연결된 그래프를 '연결 그래프'라 함

### 1.2 그래프의 종류
1. **방향성에 따른 분류**
    - 무향 그래프(Undirected Graph): 간선에 방향이 없음
    - 유향 그래프(Directed Graph): 간선에 방향이 있음

2. **가중치에 따른 분류**
    - 가중치 그래프(Weighted Graph): 간선에 비용/거리 등의 가중치가 있음
    - 비가중치 그래프(Unweighted Graph): 간선의 가중치가 모두 동일

3. **특수한 형태**
    - DAG(Directed Acyclic Graph): 사이클이 없는 유향 그래프
    - 이분 그래프(Bipartite Graph): 정점을 두 그룹으로 나눌 수 있는 그래프
    - 완전 그래프(Complete Graph): 모든 정점 쌍이 간선으로 연결된 그래프

## 2. 그래프 표현 방법

### 2.1 인접 행렬(Adjacency Matrix)
```python
# n x n 행렬로 그래프 표현
class GraphMatrix:
    def __init__(self, n):
        self.n = n
        self.matrix = [[0] * n for _ in range(n)]
    
    def add_edge(self, u, v, w=1):
        self.matrix[u][v] = w
        # 무향 그래프라면: self.matrix[v][u] = w
```

* 특징
    - 장점: 간선 존재 여부 확인이 O(1)
    - 단점: 공간 복잡도 O(V²), 희소 그래프에서 비효율적
    - 모든 정점 쌍의 경로를 찾는 Floyd-Warshall 알고리즘에 적합

### 2.2 인접 리스트(Adjacency List)
```python
class GraphList:
    def __init__(self, n):
        self.n = n
        self.adj = [[] for _ in range(n)]
    
    def add_edge(self, u, v, w=1):
        self.adj[u].append((v, w))
        # 무향 그래프라면: self.adj[v].append((u, w))
```

* 특징
    - 장점: 공간 효율적 O(V+E), 특히 희소 그래프에서 유리
    - 단점: 특정 간선의 존재 여부 확인에 O(degree(v)) 시간 소요
    - DFS/BFS 등 대부분의 그래프 알고리즘에서 선호됨

### 2.3 간선 리스트(Edge List)
```python
class Edge:
    def __init__(self, u, v, w=1):
        self.u = u  # 시작 정점
        self.v = v  # 도착 정점
        self.w = w  # 가중치

class GraphEdgeList:
    def __init__(self, n):
        self.n = n
        self.edges = []
    
    def add_edge(self, u, v, w=1):
        self.edges.append(Edge(u, v, w))
```

* 특징
    - 장점: 간선 기반 알고리즘(Kruskal의 MST 등)에 적합
    - 단점: 정점 간 연결 정보 확인이 어려움
    - 간선 정렬이 필요한 알고리즘에서 주로 사용

## 3. 기본 탐색 알고리즘

### 3.1 깊이 우선 탐색(DFS, Depth-First Search)
```python
def dfs(graph, start, visited=None):
    if visited is None:
        visited = [False] * graph.n
    
    visited[start] = True
    print(start, end=' ')  # 방문 처리
    
    for next_v, _ in graph.adj[start]:
        if not visited[next_v]:
            dfs(graph, next_v, visited)

# 반복적(스택) 구현
def dfs_iterative(graph, start):
    visited = [False] * graph.n
    stack = [start]
    
    while stack:
        v = stack.pop()
        if not visited[v]:
            visited[v] = True
            print(v, end=' ')
            for next_v, _ in reversed(graph.adj[v]):
                if not visited[next_v]:
                    stack.append(next_v)
```

### 3.2 너비 우선 탐색(BFS, Breadth-First Search)
```python
from collections import deque

def bfs(graph, start):
    visited = [False] * graph.n
    queue = deque([start])
    visited[start] = True
    
    while queue:
        v = queue.popleft()
        print(v, end=' ')  # 방문 처리
        
        for next_v, _ in graph.adj[v]:
            if not visited[next_v]:
                visited[next_v] = True
                queue.append(next_v)
```

## 4. 주요 그래프 알고리즘

### 4.1 위상 정렬(Topological Sort)
```python
from collections import deque

def topological_sort(graph):
    # 진입 차수 계산
    in_degree = [0] * graph.n
    for u in range(graph.n):
        for v, _ in graph.adj[u]:
            in_degree[v] += 1
    
    # 진입 차수가 0인 정점을 큐에 삽입
    queue = deque()
    for v in range(graph.n):
        if in_degree[v] == 0:
            queue.append(v)
    
    result = []
    while queue:
        v = queue.popleft()
        result.append(v)
        
        for next_v, _ in graph.adj[v]:
            in_degree[next_v] -= 1
            if in_degree[next_v] == 0:
                queue.append(next_v)
    
    # 사이클이 있다면 위상 정렬 불가능
    return result if len(result) == graph.n else []
```

### 4.2 최단 경로 알고리즘 (Dijkstra)
```python
import heapq

def dijkstra(graph, start):
    dist = [float('inf')] * graph.n
    dist[start] = 0
    pq = [(0, start)]  # (거리, 정점)
    
    while pq:
        d, v = heapq.heappop(pq)
        
        if d > dist[v]:  # 이미 처리된 정점
            continue
        
        for next_v, weight in graph.adj[v]:
            cost = dist[v] + weight
            if cost < dist[next_v]:
                dist[next_v] = cost
                heapq.heappush(pq, (cost, next_v))
    
    return dist
```

### 4.3 최소 신장 트리(MST) - Kruskal 알고리즘
```python
class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n
    
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x, y):
        px, py = self.find(x), self.find(y)
        if px == py:
            return False
        if self.rank[px] < self.rank[py]:
            px, py = py, px
        self.parent[py] = px
        if self.rank[px] == self.rank[py]:
            self.rank[px] += 1
        return True

def kruskal(graph):
    edges = []
    for u in range(graph.n):
        for v, w in graph.adj[u]:
            if u < v:  # 무향 그래프에서 중복 방지
                edges.append((w, u, v))
    
    edges.sort()  # 가중치 기준 정렬
    uf = UnionFind(graph.n)
    mst = []
    
    for w, u, v in edges:
        if uf.union(u, v):
            mst.append((u, v, w))
            if len(mst) == graph.n - 1:
                break
    
    return mst
```

## 5. 실무 활용 사례

### 5.1 소셜 네트워크 분석
- 사용자 관계를 그래프로 모델링
- BFS로 "친구 추천" 구현
- 커뮤니티 탐지에 강연결 요소(SCC) 활용

### 5.2 네비게이션/지도
- 도로망을 가중치 그래프로 표현
- 다익스트라 알고리즘으로 최단 경로 계산
- 실시간 교통 정보를 간선 가중치에 반영

### 5.3 작업 스케줄링
- 작업 간 의존관계를 DAG로 모델링
- 위상 정렬로 실행 순서 결정
- 사이클 탐지로 순환 의존성 체크

## 6. 시간 복잡도 요약

| 알고리즘 | 시간 복잡도 | 공간 복잡도 |
|---------|------------|------------|
| DFS/BFS | O(V + E) | O(V) |
| Dijkstra | O(E log V) | O(V) |
| Kruskal | O(E log E) | O(V) |
| 위상 정렬 | O(V + E) | O(V) |
| Floyd-Warshall | O(V³) | O(V²) |

* V: 정점 수, E: 간선 수

## 7. 그래프 문제 해결 팁

1. 그래프 표현 방법 선택
    - 밀집 그래프 → 인접 행렬
    - 희소 그래프 → 인접 리스트
    - 간선 기반 알고리즘 → 간선 리스트

2. 메모리 사용량 고려
    - 정점 수가 많은 경우 인접 리스트 선호
    - visited 배열은 필수적으로 필요

3. 문제 유형별 접근
    - 최단 경로 → Dijkstra/Floyd-Warshall
    - 사이클 탐지 → DFS/Union-Find
    - 연결성 → BFS/DFS
    - 의존성 관계 → 위상 정렬