# 크루스칼 (Kruskal) 알고리즘

* 개념
    * **크루스칼(Kruskal)**은 그래프의 모든 정점을 연결하는 **최소 비용(가중치)의 신장 트리(Spanning Tree)**를 찾는 알고리즘입니다.
    * 선(Edge)을 오름차순(가중치가 작은 순)으로 정렬한 뒤, 사이클을 형성하지 않는 간선을 하나씩 선택(Union-Find 자료구조 사용)해 나가는 방식입니다.
    * 결과적으로 선택된 간선들이 신장 트리(Spanning Tree)를 형성하게 되며, 가중치 합이 최소가 됩니다.

* 동작 원리
    1. 간선 목록을 가중치에 따라 오름차순으로 정렬한다.
    2. Union-Find(Disjoint Set) 자료구조를 초기화하여, 모든 정점을 각각 서로 다른 집합으로 둔다.
    3. 정렬된 간선들을 하나씩 순회하며, 해당 간선의 양 끝 정점이 현재 같은 집합인지(이미 연결되어 있는지) 확인한다.
        - 만약 서로 다른 집합이면, 이 간선을 선택하고(Union), 두 집합을 합친다.
        - 같은 집합이면, 이 간선을 선택하면 사이클이 생기므로 선택하지 않는다(Skip).

    4. 모든 정점이 하나의 집합(즉, 연결)이 될 때까지(또는 간선 수가 V-1개가 될 때까지) 계속한다.
    5. 선택된 간선들의 집합이 최소 신장 트리를 이룬다.

* 기본 구현
    ```python
    class UnionFind:
        def __init__(self, n):
            self.parent = list(range(n))
            self.rank = [0] * n  # union by rank 최적화
        
        def find(self, x):
            if self.parent[x] != x:
                self.parent[x] = self.find(self.parent[x])  # path compression
            return self.parent[x]
        
        def union(self, a, b):
            rootA = self.find(a)
            rootB = self.find(b)
            if rootA != rootB:
                # union by rank
                if self.rank[rootA] < self.rank[rootB]:
                    self.parent[rootA] = rootB
                elif self.rank[rootA] > self.rank[rootB]:
                    self.parent[rootB] = rootA
                else:
                    self.parent[rootB] = rootA
                    self.rank[rootA] += 1
                return True
            return False

    def kruskal(edges, V):
        """
        edges: [(w, u, v), ... ]  # (가중치, 시작정점, 끝정점)
        V: 정점 개수
        """
        # 1. 간선 정렬 (가중치 오름차순)
        edges.sort(key=lambda x: x[0])
        
        uf = UnionFind(V)
        mst_weight = 0
        mst_edges = []
        
        # 2. 간선을 순서대로 확인
        for w, u, v in edges:
            # 3. 사이클 체크 (Union-Find)
            if uf.union(u, v):
                # 사이클이 형성되지 않는다면, MST에 포함
                mst_weight += w
                mst_edges.append((u, v, w))
                
                # 4. 모든 정점이 연결되었는지 확인(옵션)
                # 보통은 mst_edges가 (V-1)개가 되면 종료
                if len(mst_edges) == V-1:
                    break
        
        return mst_weight, mst_edges

    # 예시
    # 정점: 0, 1, 2, 3, 4
    # 간선: (가중치, u, v) 형식
    example_edges = [
        (1, 0, 1),
        (2, 0, 2),
        (5, 1, 2),
        (6, 2, 3),
        (4, 1, 3),
        (3, 1, 4),
        (7, 3, 4)
    ]
    V = 5
    mst_w, mst_e = kruskal(example_edges, V)
    print("MST Weight:", mst_w)
    print("MST Edges:", mst_e)
    ```

    - **Union-Find(Disjoint Set)**를 사용하여 사이클을 효율적으로 감지합니다.
        - `find(x)`: 어떤 원소 x가 속한 집합의 대표자(루트)를 찾는다.
        - `union(a, b)`: 두 원소가 속한 집합을 합침. (같은 집합이면 합치지 않음)
    - 간선을 `w`(가중치) 기준으로 오름차순 정렬 후, 최소 가중치부터 차례대로 MST에 포함 여부를 결정합니다.

* 최적화된 C++ 스타일 (Union-Find)
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    struct Edge {
        int u, v;
        long long w;
    };

    struct UnionFind {
        vector<int> parent, rank;
        UnionFind(int n) : parent(n), rank(n, 0) {
            for (int i = 0; i < n; i++) parent[i] = i;
        }
        int find(int x) {
            if (parent[x] != x) 
                parent[x] = find(parent[x]);
            return parent[x];
        }
        bool unite(int a, int b) {
            int ra = find(a), rb = find(b);
            if (ra == rb) return false;
            if (rank[ra] < rank[rb]) parent[ra] = rb;
            else if (rank[ra] > rank[rb]) parent[rb] = ra;
            else {
                parent[rb] = ra;
                rank[ra]++;
            }
            return true;
        }
    };

    int main(){
        ios::sync_with_stdio(false); cin.tie(nullptr);
        int V = 5;  // 정점 수
        vector<Edge> edges = {
            {0, 1, 1}, {0, 2, 2}, {1, 2, 5},
            {1, 3, 4}, {1, 4, 3}, {2, 3, 6},
            {3, 4, 7}
        };
        
        // 1. 간선 정렬
        sort(edges.begin(), edges.end(), [](auto &a, auto &b){
            return a.w < b.w;
        });
        
        UnionFind uf(V);
        long long mst_weight = 0;
        vector<Edge> mst_edges;
        
        // 2. 간선을 순서대로 확인
        for(auto &edge : edges){
            if(uf.unite(edge.u, edge.v)){
                // MST에 포함
                mst_weight += edge.w;
                mst_edges.push_back(edge);
                if((int)mst_edges.size() == V-1) break;
            }
        }
        
        cout << "MST Weight: " << mst_weight << "\n";
        for(auto &e : mst_edges){
            cout << e.u << "-" << e.v << " (" << e.w << ")\n";
        }
        
        return 0;
    }
    ```
    - **간선 구조체(Edge)**에 `(u, v, w)` 정보를 담고, `sort`로 `w` 기준 오름차순 정렬.
    - Union-Find로 사이클 여부를 판단, 간선을 채택(unite).
    - MST의 총 가중치와 선택된 간선 목록을 얻음.

* 시간 복잡도
    * 간선이 E, 정점이 V개일 때
        1. 간선을 정렬: O(E log E)
        2. Union-Find 작업: 각 간선마다 `union` 및 `find`를 수행
            - `find` 연산이 α(V) (inverse Ackermann 함수, 사실상 매우 작음)
            - 결과적으로 O(E log E + Eα(V) ) ≈ O(E log E).

    * 실제로는 Union-Find + 정렬이므로, 크루스칼 전체 시간 복잡도는 O(E log E).
    * 프림(Prim) 알고리즘은 **O(E log V)**로 표현되는 게 일반적이지만, 희소/조밀 그래프 상황이나 구현 방식에 따라 성능 차이가 날 수 있습니다.

* 장단점
    1. 장점
        - 간선 위주로 접근:
            - 희소 그래프(E가 V에 비해 작을 때)일수록 간선 정렬 비용이 상대적으로 작아 유리.
        
        - Union-Find 자료구조만 있으면 구현이 간단하고 직관적("최소 가중치 간선부터 하나씩 채택").
        - **부분 그래프(MST)**를 만드는 과정이 단계별로 명확함(사이클 검사)

    2. 단점
        - 간선을 우선 정렬해야 하므로, E가 큰 **조밀 그래프(dense)**에서는 정렬 비용이 커질 수 있음(E ≈ V^2).
        - Union-Find 구조를 모르면 구현이 어려울 수 있음(사이클 판별을 다른 방식으로 해도 되지만, 비효율적).

* 활용 예시
    1. 전기 회로(전력망) 구성
        - 비용이 가장 적게 드는 방식으로 모든 노드(도시/건물 등)을 연결.

    2. 통신 케이블 연결
        - 네트워크 선(간선) 비용이 최소가 되도록, 모든 지점을 하나로 연결.

    3. 그래프 전체를 연결하는 최소 리소스 사용
        - MST의 전형적인 활용: 어떤 구조에서 "연결"이 핵심이고, 비용이 최소가 되어야 할 때.

* 사이클 체크와 Union-Find
    - 사이클이란, 그래프에서 어떤 경로를 통해 한 노드로 다시 돌아올 수 있음을 의미.
    - `Kruskal`에서는 "새 간선을 추가했을 때, 그 두 노드가 이미 같은 집합(connected component)에 속해 있으면 사이클"이라고 판단.
    - **Union-Find(Disjoint Set)**를 이용하면, 각 노드가 속한 **루트(대표자)**를 효율적으로 구해, 사이클 생성을 빠르게 판별 가능.

* 마무리
    * 크루스칼(Kruskal) 알고리즘은 가중치가 있는 그래프에서 **최소 신장 트리(MST)**를 구하는 대표적 방법 중 하나입니다.
    * 간선을 가중치 순으로 정렬한 뒤, Union-Find로 사이클을 검출하면서 최소 가중치 간선부터 차례로 채택합니다.
    * 시간 복잡도는 O(E log E), 일반적으로 희소 그래프에서 매우 효율적입니다.
    * 프림(Prim) 알고리즘과 함께 MST의 양대 산맥으로, 상황에 따라 구현 편의와 성능을 고려하여 선택됩니다.

```mermaid
flowchart LR
    A[모든 간선 가중치 오름차순 정렬] --> B[초기 모든 정점: 서로 다른 집합]
    B --> C[간선 하나씩 순회 (가중치 작은 것부터)]
    C --> D{두 정점이 다른 집합?}
    D -->|Yes| E[Union: MST에 간선 채택]
    D -->|No| F[사이클 -> 간선 스킵]
    E --> G[간선 선택 개수=V-1이 되면 종료]
    F --> C

    style A fill:#f9f,stroke:#333
    style B fill:#bbf,stroke:#333
    style C fill:#bfb,stroke:#333
    style D fill:#fbf,stroke:#333
    style E fill:#dfd,stroke:#333
    style F fill:#ffd,stroke:#333
    style G fill:#fff,stroke:#333

```