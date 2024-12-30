# 그래프 사이클(Cycle) 탐지

* 개념
    * 사이클이란, 그래프에서 어느 한 노드에서 출발하여 다른 경로를 통해 다시 해당 노드로 돌아올 수 있는 경로 존재함을 의미합니다.
    * 무방향 그래프와 유방향 그래프는 사이클 존재 여부를 판별하는 방식이 다릅니다.

1. 무방향 그래프에서의 사이클 탐지
    * 동작 원리
        1. **DFS(깊이 우선 탐색)**을 사용하여 탐색을 진행합니다.
        2. 방문하려는 노드가 이미 방문된 노드인데, "현재 탐색 경로(부모 노드와의 관계)로 연결된 노드가 아닌 경우" -> 사이클 존재.
            - 다시 말해, 인접한 노드가 "이전(직계 부모) 노드"가 아니라면, **역방향 간선(back edge)**이 생기므로 사이클이 있다고 판단합니다.

        **BFS로도 사이클을 탐지할 수 있지만, 무방향 그래프에서는 DFS가 더 직관적으로 사용됩니다**

    * 기본 구현
        ```python
        def has_cycle_undirected(graph):
            """무방향 그래프에서 사이클이 있는지 여부 반환"""
            visited = set()

            def dfs(current, parent):
                visited.add(current)
                for neighbor in graph[current]:
                    # 아직 방문하지 않은 노드라면 계속 DFS
                    if neighbor not in visited:
                        if dfs(neighbor, current):
                            return True
                    # 이미 방문했고, 부모가 아닌 노드라면 사이클
                    elif neighbor != parent:
                        return True
                return False

            for node in graph:
                if node not in visited:
                    if dfs(node, None):
                        return True
            
            return False

        # 예시 그래프
        graph_undirected = {
            'A': ['B', 'C'],
            'B': ['A', 'D'],
            'C': ['A'],
            'D': ['B']
            # A - B - D 구조와 A - C 구조 : 사이클 없음
        }
        print(has_cycle_undirected(graph_undirected))  # False
        ```
        - `dfs(current, parent)`에서, `neighbor`가 parent가 아닌데 이미 방문된 노드라면, 사이클이 존재합니다.
        - 부모 노드는 DFS를 진행하면서 한 단계 앞선 노드를 의미합니다(무방향 그래프에서는 간선이 역방향이므로, 바로 직전 노드와의 연결은 "정상적인 방문"으로 간주).

    * 시간 복잡도
        - 그래프 정점 수를 V, 간선 수를 E라 할 때, DFS로 모든 정점을 방문하므로 O(V + E).

    * 최적화 & 주의사항
        1. 인접 리스트 사용: 희소 그래프(sparse)에서 메모리와 시간 절약.
        2. 방문 배열(visited) + 부모 정보(parent) 유지: 무방향 그래프에서 "직전 부모 노드"를 구분하는게 중요합니다.
        3. 연결 그래프가 아닐 수도 있음: 각 연결 요소를 순회하며, 한 번이라도 사이클을 찾으면 `True`.

2. 유방향 그래프에서의 사이클 탐지
    * 동작 원리
        1. DFS를 사용하되, "현재 방문 중인 노드(재귀 스택)"와 "이미 방문을 마친 노드"를 구분해야 합니다.
        2. 재귀 스택(혹은 `in_stack`)에 있는 노드로 다시 방문하려고 하면, 그것은 **역방향 간선(Back Edge)**으로, 사이클이 존재함을 의미합니다.
            - 즉, DFS 과정에서 "아직 탐색이 끝나지 않은 노드"에 다시 진입했다면 사이클이 생긴 것.

    * 색(색깔) 표기법
        - 유방향 그래프에서는 종종 노드를 다음 3가지 상태로 관리합니다.
            1. 0: 아직 방문 전 (unvisited)
            2. 1: 방문 중 (in DFS stack)
            3. 2: 방문 완료 (finished)

        - 이 때, **1(방문 중)**인 노드로 다시 진입하면 사이클 존재.

    * 기본 구현
        ```python
        def has_cycle_directed(graph):
            """유방향 그래프에서 사이클이 있는지 여부 반환"""
            # 0: 미방문, 1: 방문 중, 2: 방문 완료
            state = {node: 0 for node in graph}

            def dfs(node):
                if state[node] == 1:
                    # 현재 방문 중인 노드를 다시 방문 → 사이클
                    return True
                if state[node] == 2:
                    # 이미 방문이 완료된 노드는 안전
                    return False

                # 방문 시작
                state[node] = 1
                for neighbor in graph[node]:
                    if dfs(neighbor):
                        return True

                # 방문 완료
                state[node] = 2
                return False

            for node in graph:
                if state[node] == 0:
                    if dfs(node):
                        return True
            return False

        # 예시 그래프
        graph_directed = {
            'A': ['B'],
            'B': ['C'],
            'C': ['A']  # A -> B -> C -> A 사이클
        }
        print(has_cycle_directed(graph_directed))  # True
        ```
        - `state[node] == 1` 상태로 다시 방문 시, 사이클 존재.
        - 모든 노드가 재귀 스택을 빠져나오면(`state[node] = 2`), 그 노드는 사이클과 무관하다고 볼 수 있음.

    * 시간 복잡도
        - 역시 O(V + E), 모든 정점과 간선을 한 번씩 확인합니다.

    * 최적화 & 주의사항
        1. 색(상태) 배열 대신, "방문 배열 + 재귀 스택 배열" 2개를 따로 써도 됩니다.
            ```python
            visited[node] = True      # 방문 여부
            recStack[node] = True     # 현재 재귀 호출 스택에 있는지 여부
            ```

        2. DAG(Directed Acyclic Graph) 탐지: 유방향 그래프에 사이클이 없다면 DAG입니다. -> 위상 정렬(Topological Sort)이 가능.
        3. 연결 그래프가 아닐 수 있음: 여러 연결 요소에서 사이클을 모두 검사해야 합니다.

* 사이클 탐지의 다른 방법들
    1. Union-Find (Djsjoint Set Union)
        - 무방향 그래프에서 간선을 하나씩 추가하며, "이미 같은 집합(connected component)에 속한 두 정점을 다시 연결하려는 경우" -> 사이클이 발생한다고 판단합니다.
        - 주로 MST(최소 스패닝 트리) 구할 때 유용.

    2. 위상 정렬 (Topological Sort)
        - 유방향 그래프에서 "위상 정렬 시 모든 노드를 방문하지 못하고 중간에 막히면 사이클 존재"라고 판단할 수 있습니다(Kahn 알고리즘).
        - 사이클이 없는 방향 그래프(DAG)만 위상 정렬이 완벽하게 가능합니다.

    3. BFS(Undirected)
        - 무방향 그래프에서도 BFS로 사이클 감지가 가능하지만, DFS + 부모 정보가 좀 더 직관적입니다.
        - BFS로 구현 시, "방문했던 이웃이 부모(직전에 큐에 넣은 노드)가 아닌데 이미 방문되었으면 사이클"로 간주.

* 활용 예시
    1. MST(최소 스패닝 트리) 알고리즘 (Kruskal)
        - 새로운 간선을 추가할 때 Union-Find로 사이클이 생기는지 체크, 생기면 그 간선을 스킵.

    2. 의존성 그래프 (유방향)
        - 예: 소프트웨어 패키지 설치 의존성. 사이클이 있으면 설치 불가.

    3. 위상 정렬
        - 예: "선수 과목" 관계도에 사이클이 있으면 수강 불가능(모순).

    4. 프로세스 스케줄러
        - 유방향 그래프에서 사이클이 있으면 교착 상태(DeadLock)가 발생할 수 있음 -> 사이클 탐지로 데드락 판단.

* 마무리
    * 사이클 탐지는 그래프 문제 전반에서 매우 자주 등장하는 테마입니다.
    * 무방향 그래프는 "DFS 중 부모가 아닌 방문 노드 발견" 혹은 "Union-Find"로 쉽게 체크 가능.
    * 유방향 그래프는 "재귀 스택(방문 중 상태)인 노드 재방문 시 사이클" 또는 "위상 정렬 시 모든 노드를 방문 못하면 사이클"로 판별합니다.
    * MST, 위상 정렬, 의존성 그래프, 데드락 검사 등 실무/이론 모두에서 중요한 알고리즘입니다.

```mermaid
flowchart TB
    A[시작] --> B{무방향 vs 유방향}
    B -->|무방향| C[DFS + (Current, Parent)]
    C --> D[부모 아닌 방문 노드 발견 → 사이클]
    B -->|유방향| E[DFS + 재귀 스택]
    E --> F[Stack인 노드 재진입 → 사이클]
    D --> G[결과: 사이클 O/X]
    F --> G

    style A fill:#f9f,stroke:#333
    style C fill:#bfb,stroke:#333
    style E fill:#bbf,stroke:#333
    style G fill:#fbf,stroke:#333

```