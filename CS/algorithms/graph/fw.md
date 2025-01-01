# 플로이드-워셜 (Floyd-Warshall) 알고리즘

* 개념
    * **플로이드-워셜 (Floyd-Warshall)**은 모든 노드 쌍 (u, v)에 대해 최단 거리를 구하는 알고리즘입니다.
    * 음수 가중치가 있어도 동작하지만, 음수 사이클이 존재하면 해당 사이클에 도달 가능한 경로의 최단 거리는 정의되지 않습니다(무한히 작아질 수 있음).
    * 다익스트라나 벨만-포드는 "단일 시작점(Single Source)" 최단 경로를 구하지만, 플로이드-워셜은 "모든 시작점(Every Source)"에 대해 경로를 구합니다.

* 동작 원리
    1. **거리 행렬(dist)**을 초기화:
        - 노드가 V개일 때, V x V 크기의 2차원 배열 `dist`를 만든 뒤,
        - 자기 자신까지의 거리는 0, 직접 연결된 간선의 거리는 가중치, 연결되지 않은 경우는 ∞(무한대)로 초기 설정.

    2. 모든 노드 k를 중간 경유지로 가정하며,
        - dist[i][j]와 dist[i][k] + dist[k][j]를 비교하여, 더 짧은 거리로 갱신("릴랙스").
        - 즉, 
        ```python
            for i in range(V):
                for i in range(V):
                    for i in range(V):
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
        ```

    3. 이중 반복문에 "중간 노드"를 한 번씩 더 중첩해서 3중 반복문이 되고, 따라서 O(V^3) 시간 복잡도를 갖습니다.

* 기본 구현
    ```python
    def floyd_warshall(graph, V):
        """
        graph: V x V 크기의 2차원 리스트(가중치 인접 행렬)
            graph[i][j] = i->j 가중치 (없으면 float('inf'))
        V: 노드(정점) 수
        return: dist 배열(각 i->j 최단거리), 음수 사이클 여부
        """
        # dist 배열 복사(원본 graph를 훼손하지 않기 위해)
        dist = [row[:] for row in graph]

        # 플로이드-워셜 메인 루프
        for k in range(V):
            for i in range(V):
                for j in range(V):
                    # 중간에 k를 거쳐가는 경로가 더 짧다면 갱신
                    if dist[i][k] + dist[k][j] < dist[i][j]:
                        dist[i][j] = dist[i][k] + dist[k][j]

        # 음수 사이클 체크
        # dist[i][i]가 음수가 되었다면, 해당 i 노드가 포함된 음수 사이클 존재
        negative_cycle = False
        for v in range(V):
            if dist[v][v] < 0:
                negative_cycle = True
                break

        return dist, negative_cycle

    # 예시
    INF = float('inf')
    V = 4
    graph_mat = [
        [0,   5,   INF, 10 ],   # 0->0=0, 0->1=5, 0->2=INF, 0->3=10
        [INF, 0,   3,   INF],   # 1->0=INF, 1->1=0, 1->2=3,   1->3=INF
        [INF, INF, 0,   1  ],   # 2->0=INF, 2->1=INF,2->2=0,   2->3=1
        [INF, INF, INF, 0  ]    # 3->0=INF, 3->1=INF,3->2=INF, 3->3=0
    ]

    dist_result, has_neg_cycle = floyd_warshall(graph_mat, V)

    print("Result Dist Matrix:")
    for row in dist_result:
        print(row)
    print("Negative Cycle?:", has_neg_cycle)
    ```

    - `graph`는 인접 행렬(상호 연결 여부와 가중치), 자기 자신은 0, 연결되지 않은 경우 ∞로 표현.
    - 3중 for문에서 `k`를 중간 노드로 두며, dist[i][k] + dist[k][j]가 더 작다면 `dist[i][j]`를 갱신합니다.
    - 음수 사이클 판별은, 플로이드-워셜을 다 돌린 뒤 `dist[v][v] < 0`인 노드가 있으면, 그 노드는 음수 사이클에 포함된 것으로 간주합니다(0보다 작은 자기 자신으로 가는 비용 -> 무한정 감소 가능).

* 시간 복잡도
    - O(V^3)
        - 모든 쌍(i, j)에 대해, "중간 노드 k"를 하나씩 고려 -> 3중 반복문.

    - V가 큰 그래프(수천 ~ 수만 노드)에는 매우 비효율적, 보통은 수백 ~ 최대 1000 정도 노드까지가 플로이드-워셜의 실용적 한계로 여겨집니다.

* 장단점
    1. 장점
        - 모든 정점 쌍의 최단 경로를 한 번에 구할 수 있음 (All-Pairs Shortest Path)
        - 음수 사중치(단, 음수 사이클은 불가능)도 허용
        - 구현이 단순(3중 for문으로 직관적)
        - 음수 사이클 존재 시, `dist[v][v] < 0`으로 판단 가능

    2. 단점
        - **시간 복잡도 O(V^3)**로 V가 조금만 커져도 계산 비용이 급격히 증가
        - 음수 사이클 존재 시, 해당 사이클에 도달 가능한 노드들의 최단 경로가 정의되지 않으므로, 그 노드들에 대한 처리 추가 필요(단순히 `dist[v][v] < 0` 이외에도, 사이클 영향을 받는 모든 (i, j) 판별).

* 활용 예시
    1. 규모가 작은 그래프(수십 ~ 수백 노드)에서 모든 노드 쌍 최단 거리를 구해야 하는 문제
        - 예: 도시 개수가 몇백 개 정도인 상황에서, 모든 도시 간 최단 경로를 미리 계산해두고 쿼리에 응답.

    2. 동적 프로그래밍(DP) 관점
        - "경로 중간에 k 이하의 노드만 사용할 수 있다고 가정"으로 DP를 확장해 나가는 방식과 동일한 흐름.

    3. 노드 간 거리 테이블이 필요한 경우
        - 예: 네트워크에서 "임의의 두 지점 사이 최단 경로"를 미리 계산
        - 예: 게임에서 "맵 모든 지점 쌍" 간 거리를 precalculation(단, 맵이 매우 크면 비현실적)

* 음수 사이클 처리
    - 플로이드-워셜은 음수 사이클이 있는지 여부를 다음과 같이 확인:
        - 알고리즘 종료 후, `dist[v][v] < 0`인 노드가 있다면, 그 노드가 포함된 음수 사이클이 존재한다고 판단.

    - 해당 노드에 갈 수 있고, 해당 노드에서 올 수 있는 모든 노드 쌍은 "음수 사이클 영향"으로 무한히 작은 거리가 가능하므로, 최단 경로가 정의되지 않습니다.
    - 더 정교하게 처리하고 싶다면, 이렇게 음수 사이클과 연관된 노드들을 찾고 `-∞`로 표기하거나, "경로 없음"으로 표시할 수 있습니다.

* 마무리
    - **플로이드-워셜(Floyd-Warshall)**은 모든 노드 쌍의 최단 거리를 구할 수 있는 대표적인 APSP(All-Pairs Shortest Path) 알고리즘이며, **O(V^3)**라는 높은 시간 복잡도를 가집니다.

    - 음수 간선도 허용하지만, 음수 사이클이 있으면 제대로 된 최단 거리를 정의할 수 없습니다.

    - 그래프의 **노드 수(V)**가 크지 않은 경우에 유용하며, 단일 출발점 최단 경로가 필요한 경우에는 다익스트라(또는 벨만-포드)가 주로 사용됩니다.

```mermaid
flowchart LR
    A[초기 dist[i][j] = graph[i][j]] --> B[k in 0..V-1]
    B --> C[i in 0..V-1]
    C --> D[j in 0..V-1]
    D --> E[dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])]
    E --> B
    B --> F[음수 사이클 체크: dist[v][v] < 0 ?]

    style A fill:#f9f,stroke:#333
    style B fill:#bfb,stroke:#333
    style C fill:#bbf,stroke:#333
    style D fill:#fbf,stroke:#333
    style E fill:#dfd,stroke:#333
    style F fill:#ffd,stroke:#333

```