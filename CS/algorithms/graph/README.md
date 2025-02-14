# 그래프 알고리즘

그래프 알고리즘은 노드(정점)와 간선으로 구성된 그래프 구조에서 데이터 탐색, 경로 최적화, 순회, 연결성 분석 등 다양한 문제를 해결하기 위한 핵심 기법입니다.  
이 문서는 기본적인 탐색, 최단 경로, 최소 신장 트리와 더불어 강하게 연결된 성분, 네트워크 플로우, A* 알고리즘, 이분 매칭 등 고급 그래프 알고리즘까지 폭넓게 다루며, 각 알고리즘의 이론 및 구현체 예시로 연결된 링크를 제공합니다.

---

## 기본 그래프 탐색
- **깊이 우선 탐색 (DFS):**  
  재귀 또는 스택을 사용해 그래프를 깊게 탐색합니다.  
  [DFS](dfs.c)
  
- **너비 우선 탐색 (BFS):**  
  큐를 이용해 그래프를 레벨별로 탐색합니다.  
  [BFS](bfs.c)
  
- **사이클 탐지:**  
  그래프 내 순환(사이클)이 존재하는지 판별합니다.  
  [Cycle Detect](cycle_detect.c)
  
- **위상 정렬 (Topological Sort):**  
  방향 그래프(DAG)에서 노드 간 선후 관계를 고려하여 정렬합니다.  
  [Topological Sort](topological_sort.c)

---

## 최단 경로 알고리즘 (기초)
- **다익스트라 (Dijkstra):**  
  음의 가중치가 없는 그래프에서 단일 시작점 최단 경로를 계산합니다.  
  [Dijkstra](./Dijkstra/README.md)
  
- **벨만-포드 (Bellman-Ford):**  
  음의 가중치가 있는 그래프에서도 단일 시작점 최단 경로를 구하며, 음의 사이클을 탐지할 수 있습니다.  
  [Bellman-Ford](./BellmanFord/README.md)
  
- **플로이드-워셜 (Floyd-Warshall):**  
  모든 쌍의 노드 간 최단 경로를 동적 계획법으로 계산합니다.  
  [Floyd-Warshall](./FloydWarshall/README.md)

---

## 최소 신장 트리 (기초)
- **크루스칼 (Kruskal):**  
  간선들을 가중치 순으로 선택하여 사이클 없이 최소 신장 트리를 구성합니다.  
  [Kruskal](./Kruskal/README.md)
  
- **프림 (Prim):**  
  하나의 노드에서 시작해 인접 노드 중 최소 가중치 간선을 선택하면서 최소 신장 트리를 구성합니다.  
  [Prim](./Prim/README.md)

---

## 강하게 연결된 성분 (SCC)
- **SCC (Strongly Connected Components):**  
  방향 그래프에서 서로 도달 가능한 노드들의 집합(강하게 연결된 컴포넌트)을 찾습니다.  
  Kosaraju 또는 Tarjan 알고리즘을 통해 구현됩니다.
  [SCC](./SCC/README.md)

---

## 네트워크 플로우
- **네트워크 플로우:**  
  그래프에서 최대 유량 문제를 해결하는 알고리즘입니다.  
  대표적으로 Ford-Fulkerson, Edmonds-Karp, 그리고 Dinic 알고리즘이 있습니다.  
  [Network Flow](./NetworkFlow/README.md)

---

## A* 알고리즘 (A-star)
- **A* 알고리즘:**  
  휴리스틱을 사용해 최단 경로를 효율적으로 탐색하는 알고리즘으로, 주로 지도 기반 경로 탐색이나 게임 AI에서 활용됩니다.  
  [A*](./AStar/README.md)

---

## 이분 매칭 (Bipartite Matching)
- **이분 매칭:**  
  이분 그래프에서 최대 매칭을 찾는 알고리즘으로, 대표적으로 Hopcroft-Karp 알고리즘이 사용됩니다.  
  할당 문제나 스케줄링 문제에 자주 활용됩니다.  
  [Bipartite Matching](./BipartiteMatching/README.md)

---

그래프 알고리즘은 네트워크 설계, 데이터 분석, 최적화 문제 해결, 일정 계획 등 다양한 분야에서 핵심적인 역할을 수행합니다.  
각 링크를 통해 상세한 이론과 구현체 예시를 확인하고, 실무 문제 해결에 응용해 보세요!
