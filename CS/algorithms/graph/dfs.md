# 깊이 우선 탐색 (DFS: Depth First Search)

* 개념
    * DFS는 그래프(또는 트리)의 한 노드에서 출발하여, 인접한 노드를 우선 깊이(depth) 방향으로 탐색해 나가는 방법입니다.
    * 방문할 수 있는 노드가 더 이상 없을 때(또는 목표를 찾았을 때) 역으로 돌아가(backtrack) 다른 경로를 탐색하는 식으로 진행합니다.
    * 스택(혹은 재귀 호출 스택)을 사용하여 구현하는 것이 일반적입니다.
    * 그래프 탐색, 트리 순회, 백트래킹 문제 등 다양한 문제에서 사용됩니다.

* 동작 원리
    1. 시작 노드를 방문하고 스택(또는 재귀 호출 스택)에 넣습니다.
    2. 스택(또는 현재 재귀 호출의)최상단 노드와 인접한 노드 중 아직 방문하지 않은 노드가 있으면, 그 노드를 방문하고 스택에 푸시(push)합니다.
    3. 인접한 노드가 모두 방문된 경우, 스택에서 해당 노드를 팝(pop)하여 되돌아갑니다.
    4. 스택이 빌 때까지(혹은 더 이상 방문할 노드가 없을 때까지) 2 ~ 3 과정을 반복합니다.

    **트리의 DFS는 동일한 로직이나, 그래프는 사이클이 있을 수 있으므로 이미 방문한 노드를 다시 방문하지 않도록 방문 배열(visited)을 관리해야 합니다.**

* 기본 구현
    ```python
    def dfs_recursive(graph, start, visited=None):
        """재귀 함수를 사용한 DFS"""
        if visited is None:
            visited = set()
        visited.add(start)

        # 현재 노드 처리 (예: print)
        print(start, end=' ')

        for neighbor in graph[start]:
            if neighbor not in visited:
                dfs_recursive(graph, neighbor, visited)

    def dfs_iterative(graph, start):
        """스택을 사용한 반복문 기반 DFS"""
        visited = set()
        stack = [start]

        while stack:
            node = stack.pop()
            if node not in visited:
                visited.add(node)
                print(node, end=' ')
                # 스택의 특성상 뒤에 넣은 노드부터 먼저 탐색되므로,
                # 인접 노드를 역순으로 넣어야 정해진 순서대로 탐색 가능
                for neighbor in reversed(graph[node]):
                    if neighbor not in visited:
                        stack.append(neighbor)
    ```

    * `graph`는 일반적으로 인접 리스트 형태를 가정합니다.
    - 예:
        ```python
        graph = {
            'A': ['B', 'C'],
            'B': ['A', 'D', 'E'],
            'C': ['A', 'F'],
            ...
        }
        ```
    * `visited`는 이미 방문한 노드를 저장하는 자료구조(집합, 리스트, boolean 배열 등).

* 최적화된 C++ 구현
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    void dfs_iterative(const vector<vector<int>>& graph, int start) {
        vector<bool> visited(graph.size(), false);
        stack<int> st;
        st.push(start);

        while (!st.empty()) {
            int node = st.top();
            st.pop();

            if (!visited[node]) {
                visited[node] = true;
                cout << node << " ";

                // 인접 노드를 역순으로 스택에 넣어야
                // 오름차순으로 탐색 (그래프 구성에 따라 다름)
                // 예: 그래프가 작은 번호부터 방문하고 싶으면 역순으로 푸시
                for (auto it = graph[node].rbegin(); it != graph[node].rend(); ++it) {
                    if (!visited[*it]) {
                        st.push(*it);
                    }
                }
            }
        }
    }

    int main() {
        // 예시 그래프 (인접 리스트)
        vector<vector<int>> graph = {
            {1, 2},     // 0번 노드는 1, 2와 연결
            {0, 3, 4},  // 1번 노드는 0, 3, 4와 연결
            {0, 5},     // 2번 노드는 0, 5와 연결
            {1},        // 3번 노드는 1과 연결
            {1},        // 4번 노드는 1과 연결
            {2}         // 5번 노드는 2와 연결
        };

        dfs_iterative(graph, 0);
        return 0;
    }
    ```
    * 노드를 인접 벡터에서 역순으로 탐색하는 이유: 스택은 LIFO(후입선출)이므로, "작은 노드부터 방문하겠다." 같은 순서를 보장하려면 역순 푸시가 필요할 수 있습니다.
    * 만약 "큰 노드부터 방문"하고 싶다면 정방향 순서로 스택에 넣으면 됩니다.

* 시간 복잡도
    * 그래프 G에 대해, 정점(Vertex) 수를 V, 간선(Edge) 수를 E라고 할 때:
        * DFS의 시간 복잡도는 O(V + E) 입니다.
            - 모든 정점을 최소 한 번씩 방문하고, 각 간선을 최대 두 번(양방향 그래프의 경우) 확인하기 때문.
    
    * 트리(간선이 V - 1개)에서는 **O(V)**와 같습니다.

* 공간 복잡도
    * O(V): 방문 배열(visited) 및 재귀/스택이 최대 V 깊이로 쌓일 수 있음.
    * 인접 리스트는 **O(V + E)**를 저장하는 데 필요.

* 장단점
    1. 장점
        - 구현이 간단(특히 재귀)
        - 메모리 사용량이 적은 편(인접 리스트 사용 시)
        - 백트래킹, 조합 탐색 등과 자연스럽게 연계 가능

    2. 단점
        - 재귀 사용 시, 재귀 스택이 깊어지는 문제(스택 오버플로우)가 발생할 수 있음
        - 사이클이 있는 그래프에서, 방문 배열을 잘못 다루면 무한 루프
        - BFS에 비해, 최단 경로(edge 가중치가 없을 때)를 바로 구하기는 어렵다

* 최적화 전략
    1. 인접 리스트 사용
        - 행렬(Adjacency Matrix)보다 리스트(Adjacency List)를 사용하면, **희소 그래프(sparse graph)**에서 메모리를 효율적으로 쓸 수 있고, 탐색 비용도 줄어듭니다.

    2. 재귀 대신 스택 사용
        - 재귀 깊이가 큰 경우(수만 ~ 수십만 노드)에는 반복문 + 스택으로 구현하여 스택 오버플로우 위험을 줄입니다.

    3. 정점 방문 순서 제어
        - 문제에 따라 "작은 정점 번호부터 방문" 혹은 "특정 우선순위 순서로 방문"이 필요할 때, 인접 리스트를 정렬하고 DFS를 수행하면 됩니다.

    4. 방문 시간/나가는 시간 기록 (DFS Tree)
        - 그래프 알고리즘(사이클 판별, 위상 정렬, 트리 에지/역방향 에지 구분 등)을 위해 DFS 시작/종료 시간을 기록하기도 합니다.

* 활용 예시
    1. 사이클 탐지 (Cycle Detection)
        - 무방향 그래프에서 "이미 방문한 노드가 현재 탐색 경로(재귀 스택)에 있다면" 사이클.
        - 방향 그래프에서는 "백 엣지(back edge)"가 존재하면 사이클.

    2. 위상 정렬 (Topological Sort)
        - 방향 그래프에서 DAG(사이클 없는 방향 그래프)라면, DFS 종료 시간을 역순으로 나열하면 위상 정렬 순서를 얻을 수 있습니다.

    3. 백트래킹 문제
        - 예: N-Queen, 미로 찾기(maze), 조합 탐색 등.

    4. 트리 순회
        - 이진 트리/일반 트리에서도, DFS(전위, 중위, 후위)를 통해 노드를 순환합니다.

    5. 연결 요소 분리
        - 그래프에서 DFS를 반복 호출하여 연결 요소 개수나 구성 노드를 알 수 있습니다.

* 마무리
    - **깊이 우선 탐색(DFS)**은 그래프 탐색 및 트리 순회에서 가장 기본이 되는 알고리즘 중 하나입니다.
    - 단순해 보이지만, 백트래킹, 사이클 판별, 위상 정렬, 그리고 조합 탐색 등 다양한 문제에 활용되는 "기본 도구"입니다.
    - 큰 그래프를 다룰 때는 재귀 대신 반복문 + 스택을 사용하거나, 인접 리스트를 최적화해야 합니다.
    - BFS에 비해 최단 거리를 찾는 데는 직접적인 이점이 없지만, "모든 경로를 시도"하거나 "깊이 있는 정보"가 필요한 문제에는 DFS가 유리합니다.

```mermaid
graph TB
    A[시작 노드 방문] --> B{인접 노드 중 방문안됨?}
    B -->|Yes| C[그 노드 방문 + 스택/재귀 호출]
    C --> B
    B -->|No| D[스택/재귀 빠져나옴(백트래킹)]
    D --> E{스택 비었나?}
    E -->|No| B
    E -->|Yes| F[탐색 종료]

    style A fill:#f9f,stroke:#333
    style C fill:#bfb,stroke:#333
    style D fill:#bbf,stroke:#333
    style F fill:#fbf,stroke:#333

```