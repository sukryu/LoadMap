# 위상 정렬 (Topological Sort)

* 개념
    * **방향 그래프(directed graph)**에서, 어떤 두 노드 u와 v가 **간선 u -> v**로 연결되어 있다면, 정렬 상에서 **u**가 반드시 v 앞에 나와야 합니다.
    * 이렇게 노드 간의 선후관계가 있는 그래프에서, 그 순서를 위배하지 않도록 모든 노드를 일렬로 나열한 것이 "위상 정렬"입니다.
    * **DAG(Directed Acyclic Graph)**일 때만, 즉 사이클이 없을 때만 위상 정렬이 존재합니다.

* 대표 알고리즘
    1. Kahn 알고리즘 (BFS 방식)
        1. 각 노드의 **진입차수(in-degree)**를 계산한다.
            - 진입차수 = 노드에 들어오는 간선의 개수
        
        2. 진입차수가 0인 노드를 큐(Queue)에 넣는다.
        3. 큐에서 노드를 하나 꺼내, 결과 리스트에 추가한다.
        4. 이 노드에서 출발하는 간선들을 모두 제거(간선이 이어진 도착 노드의 진입차수를 1 감소)한다.
        5. 그 과정에서 진입차수가 0이 된 노드를 큐에 넣는다.
        6. 큐가 빌 때까지 3 ~ 5 과정을 반복한다.
        7. 결과 리스트에 모든 노드가 들어갔다면 성공적으로 위상 정렬 완료. 만약 빠진 노드가 있다면, 그래프에 사이클이 존재한다고 판단.

        * 기본 구현
            ```python
            from collections import deque

            def topological_sort_kahn(graph, in_degree):
                """
                graph: {node: [list of adjacent nodes]}
                in_degree: {node: 진입차수 (int)}
                """
                # 진입차수가 0인 노드를 큐에 넣음
                queue = deque([node for node in in_degree if in_degree[node] == 0])
                result = []

                while queue:
                    node = queue.popleft()
                    result.append(node)

                    # node에서 나가는 간선을 제거 (도착 노드들의 진입차수 감소)
                    for adj in graph[node]:
                        in_degree[adj] -= 1
                        if in_degree[adj] == 0:
                            queue.append(adj)

                if len(result) == len(graph):
                    return result  # 모든 노드가 들어갔다면 성공
                else:
                    return []      # 사이클 존재 -> 위상 정렬 불가능

            # 예시 그래프
            graph = {
                'A': ['C'],
                'B': ['C', 'D'],
                'C': ['E'],
                'D': ['F'],
                'E': ['H', 'F'],
                'F': ['G'],
                'G': [],
                'H': []
            }
            in_degree = {
                'A': 0,
                'B': 0,
                'C': 2,  # A->C, B->C
                'D': 1,  # B->D
                'E': 1,  # C->E
                'F': 2,  # D->F, E->F
                'G': 1,  # F->G
                'H': 1   # E->H
            }

            order = topological_sort_kahn(graph, in_degree)
            print(order)  # 예: ['A', 'B', 'C', 'D', 'E', 'F', 'H', 'G']
            ```

            - 시간 복잡도: O(V + E)
                - 모든 노드를 큐에 넣고 빼며, 각 간선을 한 번씩 확인

            - 장점: 사이클이 있는지도 자연스럽게 판별 가능(결과 크기가 V 미만이면 사이클).
            - 단점: `in_degree` 정보를 유지해야 해서, 초기화 단계에서 각 노드의 진입차수를 세는 전처리가 필요.

    2. DFS 기반 위상 정렬
        1. 모든 노드를 방문하지 않은 상태로 시작.
        2. 각 노드에 대해 DFS를 수행한다. (사이클이 있는 경우, 이미 방문 중인 노드를 다시 방문하게 되므로 사이클 판별 가능)
        3. DFS가 종료되는 시점(해당 노드의 모든 인접 노드 탐색이 끝난 시점)에 해당 노드를 스택에 푸시(또는 리스트 앞쪽에 삽입).
        4. 모든 노드에 대한 DFS가 종료된 뒤, 스택을 뒤집으면(또는 리스트를 역순으로 출력)위상 정렬 순서를 얻을 수 있다.

        * 기본 구현
            ```python
            def topological_sort_dfs(graph):
                visited = set()
                temp_stack = []  # DFS 종료 시점을 기록할 스택
                has_cycle = False

                # 0: 미방문, 1: 방문 중, 2: 방문 완료
                state = {node: 0 for node in graph}

                def dfs(node):
                    nonlocal has_cycle
                    if state[node] == 1:
                        # 방문 중인 노드를 또 방문 -> 사이클
                        has_cycle = True
                        return
                    if state[node] == 2:
                        # 이미 방문 완료된 노드는 스킵
                        return

                    state[node] = 1  # 방문 중
                    for adj in graph[node]:
                        if state[adj] != 2:
                            dfs(adj)
                    state[node] = 2  # 방문 완료
                    temp_stack.append(node)

                for node in graph:
                    if state[node] == 0:
                        dfs(node)
                        if has_cycle:
                            return []

                # temp_stack에 DFS 종료 순서로 노드가 쌓임 -> 역순이 위상 정렬
                return temp_stack[::-1]

            # 예시 그래프 (같은 그래프)
            graph_dfs = {
                'A': ['C'],
                'B': ['C', 'D'],
                'C': ['E'],
                'D': ['F'],
                'E': ['H', 'F'],
                'F': ['G'],
                'G': [],
                'H': []
            }
            order_dfs = topological_sort_dfs(graph_dfs)
            print(order_dfs)  # 예: ['B', 'A', 'C', 'E', 'H', 'D', 'F', 'G']
            ```

            - 시간 복잡도: O(V + E)
                - DFS 1회(모든 노드와 간선을 방문)

            - 장점: 별도의 진입차수(in-drgree) 계산 없이, DFS를 통해 바로 순서를 얻을 수 있음.
            - 단점: 사이클 판별 로직(재귀 스택 or 상태 배열) 필수, 재귀 깊이가 커질 수 있어 스택 오버플로우 우려(매우 큰 그래프)

* 사이클과 위상 정렬의 관계
    * 사이클이 있는 방향 그래프에서는 위상 정렬이 불가능합니다.
    * Kahn 알고리즘에서도 사이클이면, 끝까지 진입차수가 0이 되지 않는 노드가 있어서 큐에 못 들어갑니다. 결과 크기가 V 미만이 되어 중단.
    * DFS 방식에서도 **재귀 스택(방문 중)**에 있는 노드를 다시 방문하게 되면 사이클로 판단 -> 빈 리스트(`[]`) 등으로 처리.

* 시간 복잡도
    * 두 방식 모두 O(V + E)
        - Kahn 알고리즘은 진입차수 계산(초기 O(V + E)) + 큐 처리(최대 O(V + E))
        - DFS 알고리즘은 DFS 한 번(노드/간선) + 사이클 판별

* 활용 예시
    1. 선수 과목(Prerequisite) 문제
        - 과목 간 선후 관계를 그래프로 나타낼 때, 위상 정렬 결과대로 과목을 수강해야 함
        - 사이클이 있으면(순환 의존) 수강 불가능

    2. 작업 스케줄링(Tasks Scheduling)
        - 작업 간 의존성이 있는 경우, "모든 의존이 처리된 뒤 작업을 시작" -> 위상 정렬 순서대로 실행
    
    3. 빌드 순서 결정
        - 소프트웨어 모듈 간 종속 관계가 DAG라면, 그 종속 관계를 만족하는 빌드 순서를 정할 수 있음
    
    4. 컴파일러 최적화
        - 표현식 트리에서 부분식 간 순서를 결정하거나, 명령어 최적화 시 의존성을 DAG로 표현하고 의상 정렬 이용

* 마무리
    * **위상 정렬(Topological Sort)**는 **DAG(사이클 없는 방향 그래프)**에서만 가능한 순서 결정 방법입니다.
    * **Kahn 알고리즘(BFS 식)**과 DFS 기반 두 가지 대표 방식이 있으며, 모두 **O(V + E)**로 수행됩니다.
    * 그래프에서 사이클이 있으면 위상 정렬 결과를 얻을 수 없고(빈 리스트로 반환 등), 이를 통해 사이클 존재 여부도 판별할 수 있습니다.
    * 실제 응용에서 "선후 의존"이 중요한 문제들(수강, 태스크, 빌드, 의존성 그래프 등)에 많이 활용됩니다.

```mermaid
flowchart LR
    A[시작] --> B{Kahn or DFS?}
    B -->|Kahn 알고리즘(BFS)| C[진입차수 계산 -> 큐에 0인 노드]
    C --> D[큐에서 노드 꺼내 -> 인접노드 진입차수 감소]
    D -->|진입차수=0이면| C
    D --> E[결과 길이 == V ? => 정렬/사이클 판별]

    B -->|DFS 알고리즘| F[DFS 재귀로 방문]
    F --> G[모든 인접 노드 방문 후 노드를 스택에 push(방문완료 순)]
    G --> H[스택 역순이 위상 정렬]
    style A fill:#f9f,stroke:#333
    style C fill:#bfb,stroke:#333
    style D fill:#bbf,stroke:#333
    style F fill:#fbf,stroke:#333
    style G fill:#bff,stroke:#333
    style H fill:#dfd,stroke:#333

```