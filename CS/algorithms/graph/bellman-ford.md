# 벨만-포드 (Bellman-Ford) 알고리즘

* 개념
    * 다익스트라(Dijkstra) 알고리즘이 음수 가중치를 다룰 수 없는 반면, **벨만-포드(Bellman-Ford)**는 음수 간선이 있어도 최단 거리를 구할 수 있습니다.
    * 또한, **음수 사이클(negative cycle)**이 존재하는지까지 판별이 가능하다는 점이 큰 장점입니다.
    * 하지만 시간 복잡도가 **O(V * E)**로, 다익스트라(O(E log V))보다 일반적으로 느립니다.

* 동작 원리
    1. **거리 배열(dist)**을 초기화: 시작 노드는 0, 나머지 노드는 무한(또는 매우 큰 값).
    2. 간선 Relaxation을 V-1번 반복:
        - 모든 간선을 순회하면서, dist[u] + w(u -> v)가 dist[v]보다 작다면 업데이트("릴랙스")합니다.
        - 이를 V-1번 반복하면, 어떤 경로를 거쳐도 길이가 최대 V-1개의 간선을 사용해 최단 거리를 다 반영할 수 있게 됩니다.

    3. 음수 사이클 체크:
        - V-1번 릴랙스 후에도 여전히 갱신될 여지가 있는 간선이 있다면, 그것은 음수 사이클이 존재함을 의미합니다.
        - 즉, V번째 반복에서 거리 값이 갱신된다면, 해당 그래프에는 "무한정으로 거리를 줄이는"사이클이 존재합니다.

* 기본 구현
    ```python
    def bellman_ford(edges, V, start):
        """
        edges: [(u, v, w), ...]  # (출발노드, 도착노드, 가중치)
        V: 노드(정점) 수
        start: 시작 노드 (0 ~ V-1)
        
        return:
        dist: start로부터 각 노드까지의 최단 거리 리스트
        negative_cycle: 음수 사이클 존재 여부
        """
        INF = float('inf')
        dist = [INF] * V
        dist[start] = 0

        # 1. V-1번 반복
        for _ in range(V-1):
            updated = False
            for (u, v, w) in edges:
                if dist[u] != INF and dist[u] + w < dist[v]:
                    dist[v] = dist[u] + w
                    updated = True
            # 더 이상 갱신이 없으면 조기 종료 가능
            if not updated:
                break

        # 2. 음수 사이클 체크
        negative_cycle = False
        for (u, v, w) in edges:
            if dist[u] != INF and dist[u] + w < dist[v]:
                negative_cycle = True
                break

        return dist, negative_cycle

    # 예시
    # 노드 수: 5 (0~4)
    # 간선 리스트 (u, v, w)
    edges = [
        (0, 1, 6),
        (0, 2, 7),
        (1, 2, 8),
        (1, 3, 5),
        (1, 4, -4),
        (2, 3, -3),
        (2, 4, 9),
        (3, 1, -2),
        (4, 0, 2),
        (4, 3, 7)
    ]
    distances, has_negative_cycle = bellman_ford(edges, 5, 0)
    print("Distances:", distances)
    print("Negative Cycle?", has_negative_cycle)
    ```

    - `edges`는 간선 리스트 형태이며, 각 원소가 `(u, v, w)`구조.
    -  V-1번 반복으로 최단 거리를 구하고, 추가 1번 반복해서 더 갱신이 된다면 음수 사이클 존재로 판단.
    - 만약 음수 사이클이 있다면, 실제로 "무한대로 거리 감소가 가능한" 노드들에 대해서는 dist가 올바른 최단 거리가 되지 않습니다.

* 시간 복잡도
    - O(V * E)
        - 매 Iterator(최대 V-1번)마다 모든 간선을 검사.
    - 그래프가 V개의 노드, E개의 간선을 가질 때, E가 대략 O(V^2)가 될 수도 있으므로, 최악의 경우 **O(V^3)**까지 갈 수 있습니다.

* 장단점
    1. 장점
        - 음수 가중치가 있어도 최단 거리 계산 가능
        - 음수 사이클까지도 판별 가능
        - 구현이 상대적으로 단순 (간선 리스트 반복)

    2. 단점
        - 시간 복잡도가 **O(V * E)**로, 다익스트라보다 느림 (음수 간선이 없을 경우에는 다익스트라가 더 효율적)
        - 음수 사이클이 있는 경우, 그 경로에 포함되는 노드들은 실제로 “정의된 최단 거리”가 없으므로, 별도 처리 필요

* 활용 예시
    1. 음수 간선이 있는 그래프의 최단 경로
        - 금융 거래 그래프, 비용이 감소하는 간선(할인, 리베이트) 등이 있을 때

    2. 음수 사이클 검출
        - 화폐 환전(환율 그래프)에서 Arbitrage(차익 거래) 가능성 체크
        - 부정적인 가중치(이익) 경로로 무한 이익을 낼 수 있는지 검사

    3. 학술/연구용
        - Edge relaxation(간선 릴랙스) 과정이 명료하여, 알고리즘 교육이나 증명에 자주 사용

* 음수 사이클 처리
    - 벨만-포드에서 음수 사이클이 탐지되면, 그 사이클에 도달 가능한 노드들의 최단 거리는 "정의 되지 않는" 상태로 봅니다(무한히 감소 가능).
    - 필요하다면 음수 사이클이 위치한 구역(그 사이클과 연결된 노드들)을 찾아서, "이 노드는 유효한 최단 거리를 가지지 않는다"라고 마킹할 수 있습니다.

    ```python
    def detect_negative_cycle_nodes(edges, V, start):
        """음수 사이클에 속하거나, 그 사이클과 연결된 노드를 찾아냄"""
        INF = float('inf')
        dist = [INF] * V
        dist[start] = 0

        # V-1번 릴랙스
        for _ in range(V-1):
            for u,v,w in edges:
                if dist[u] != INF and dist[u] + w < dist[v]:
                    dist[v] = dist[u] + w

        # 음수 사이클에 영향을 받는 노드를 체크
        cycle_nodes = [False] * V
        for _ in range(V-1):
            for u,v,w in edges:
                if dist[u] != INF and dist[u] + w < dist[v]:
                    dist[v] = -INF  # 의미상 -∞로
                    cycle_nodes[v] = True
                    # 연쇄적으로 연결된 노드도 마킹
                    # 혹은 큐 이용 BFS/DFS로 확장 가능

        return cycle_nodes
    ```

* 마무리
    - 벨만-포드(Bellman-Ford) 알고리즘은 음수 가중치가 포함된 단일 시작점 최단 경로(Single-Source Shortest Path) 문제를 해결할 수 있고, 음수 사이클 판별까지도 가능하다는 점이 큰 강점입니다.

    - **O(V * E)**의 시간 복잡도로, 그래프가 크면 성능 상의 부담이 커질 수 있습니다.

    - 실무에서는 음수 가중치가 흔치 않으므로, 주로 특수 상황(음수 간선 존재, 사이클 검사 필요)에서 사용하거나, 학술/연구 등에서 “가장 일반적인 단일 출발 최단 경로 알고리즘”으로 다룹니다.

```mermaid
flowchart LR
    A[시작: dist[start]=0, 나머지=∞] --> B(V-1번 반복)
    B --> C[모든 간선(u->v)을 검사하며 dist[v] 갱신 가능하면 업데이트]
    C --> D[음수 사이클 검사: V번째 반복에서 갱신 발생 여부]
    D --> E[갱신 발생 시 음수 사이클 존재]
    D --> F[갱신 안 되면 최단 거리 확정]

    style A fill:#f9f,stroke:#333
    style B fill:#bbf,stroke:#333
    style C fill:#bfb,stroke:#333
    style D fill:#fbf,stroke:#333

```