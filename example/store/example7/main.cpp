#include <iostream>
#include <vector>
#include <string>

struct Node {
    int value;              // 노드의 값
    int parent;             // 부모 노드 번호
    int depth;              // 루트로부터의 깊이
    int subtree_size;       // 서브트리 크기
    std::vector<int> adj;   // 인접 노드 리스트

    Node(int v = 0) : value(v), parent(-1), depth(0), subtree_size(1) {}
};

class Tree {
private:
    std::vector<SegmentTree> chain_trees;  // 각 체인별 세그먼트 트리
    std::vector<int> chain_head; // 각 체인의 시작 노드
    std::vector<int> chain_number; // 각 노드가 속한 체인 넘버
    std::vector<int> chain_pos; // 각 노드의 체인 내에서의 위치
    std::vector<Node> nodes;
    int chain_count; // 총 체인의 개수
    int chain_pos_count; // 체인 내 위치 카운터
    int n; // 노드의 개수

    // DFS로 트리 정보 계산
    int dfs(int curr, int parent, int depth) {
        nodes[curr].parent = parent;
        nodes[curr].depth = depth;

        int subtree_size = 1;
        for (int next : nodes[curr].adj) {
            if (next != parent) {
                subtree_size += dfs(next, curr, depth + 1);
            }
        }
        nodes[curr].subtree_size = subtree_size;
        return subtree_size;
    }

    // Heavy child를 찾는 함수
    int find_heavy_child(int node) {
        int heacy_child = -1;
        int max_subtree = 0;

        for (int child : nodes[node].adj) {
            if (child != nodes[node].parent) {
                if (nodes[child].subtree_size > max_subtree) {
                    max_subtree = nodes[child].subtree_size;
                    heacy_child = child;
                }
            }
        }
        return heacy_child;
    }

    // HLD 분해 수행
    void decompose(int curr, int parent, int chain_no) {
        if (chain_head[chain_no] == -1) {
            chain_head[chain_no] = curr; // 새로운 체인의 시작
        }

        chain_number[curr] = chain_no;
        chain_pos[curr] = chain_pos_count++;

        // Heavy child를 찾아서 같은 체인에 포함
        int heavy_child = find_heavy_child(curr);
        if (heavy_child != -1) {
            decompose(heavy_child, curr, chain_no);
        }

        // 나머지 자식들은 새로운 체인으로 처리
        for (int child : nodes[curr].adj) {
            if (child != parent && child != heavy_child) {
                decompose(child, curr, ++chain_count);
            }
        }
    }

    // 체인 내에서의 쿼리 처리
    SegmentInfo query_chain(int chain_no, int chain_from, int chain_to) {
        return chain_trees[chain_no].query(
            std::min(chain_from, chain_to),
            std::max(chain_from, chain_to)
        );
    }

    // 두 노드 사이의 경로 쿼리 처리
    SegmentInfo query_path(int u, int v) {
        std::vector<SegmentInfo> path_segments;

        while (chain_number[u] != chain_number[v]) {
            // 더 깊은 체인의 노드를 선택
            if (nodes[chain_head[chain_number[u]]].depth < nodes[chain_head[chain_number[v]]].depth) {
                std::swap(u, v);
            }

            int u_chain = chain_number[u];
            int u_head = chain_head[u_chain];

            // 현재 체인에서의 구간 쿼리
            path_segments.push_back(
                query_chain(u_chain, chain_pos[u_head], chain_pos[u])
            );

            // 체인의 헤더의 부모로 이동
            u = nodes[u_head].parent;
        }

        // 같은 체인에 있는 두 노드 처리
        if (chain_pos[u] != chain_pos[v]) {
            path_segments.push_back(
                query_chain(chain_number[u], chain_pos[u], chain_pos[v])
            );
        }

        // 모든 구간 정보 병합
        SegmentInfo result = path_segments[0];
        for (size_t i = 1; i < path_segments.size(); i++) {
            result = merge(result, path_segments[i]);
        }

        return result;
    }

public:
    Tree(int size, const std::vector<int>& values) : n(size) {
        nodes.reserve(size + 1); // 1-based indexing
        nodes.push_back(Node()); // dummy node for 1-based indexing
        for (int i = 0; i < size; i++) {
            nodes.push_back(Node(values[i]));
        }
    }

    // 간선 추가
    void addEdge(int u, int v) {
        nodes[u].adj.push_back(v);
        nodes[v].adj.push_back(u);
    }

    // 트리 정보 초기화 (루트를 1로 가정)
    void initialize() {
        // 기존의 트리 정보 초기화
        dfs(1, -1, 0);

        // HLD 초기화
        initialize_hld();

        // 각 체인별 세그먼트 트리 초기화
        chain_trees.resize(chain_count + 1);
        std::vector<std::vector<int>> chain_values(chain_count + 1);

        // 각 체인별로 노드 값들을 수집
        for (int i = 1; i < nodes.size(); i++) {
            int chain = chain_number[i];
            if (chain != -1) {
                while (chain_values[chain].size() <= chain_pos[i]) {
                    chain_values[chain].push_back(0);
                }
                chain_values[chain][chain_pos[i]] = nodes[i].value;
            }
        }

        // 각 체인별 세그먼트 트리 생성
        for (int i = 0; i < chain_count; i++) {
            if (!chain_values[i].empty()) {
                chain_trees[i] = SegmentTree(chain_values[i]);
            }
        }
    }

    // 노드 값 업데이트
    void update_node(int node, int new_value) {
        nodes[node].value = new_value;
        int chain = chain_number[node];
        int pos = chain_pos[node];
        chain_trees[chain].update(pos, new_value);
    }

    // 경로 최대 부분합 처리
    long long query_max_path_sum(int u, int v) {
        return query_path(u, v).maxsum;
    }

    // HLD 초기화
    void initialize_hld() {
        int n = nodes.size();
        chain_head.assign(n,  -1);
        chain_number.assign(n, -1);
        chain_pos.assign(n, -1);
        chain_count = 0;
        chain_pos_count = 0;

        // 루트 (1번 노드)부터 시작하여 HLD 수행
        decompose(1, -1, 0);
    }

    // 두 노드의 최소 공통 조상(LCA)을 찾는 함수
    int find_lca(int u, int v) {
        while(chain_number[u] != chain_number[v]) {
            if(nodes[chain_head[chain_number[u]]].depth < nodes[chain_head[chain_number[v]]].depth) {
                std::swap(u, v);
            }
            u = nodes[chain_head[chain_number[u]]].parent;
        }
        return nodes[u].depth < nodes[v].depth ? u : v;
    }

    // HLD 관련 정보 접근자
    int get_chain_number(int node) const { return chain_number[node]; }
    int get_chain_pos(int node) const { return chain_pos[node]; }
    int get_chain_head(int chain) const { return chain_head[chain]; }

    // 노드의 값 반환
    int getValue(int node) const {
        return nodes[node].value;
    }

    // 노드의 값 설정
    void setValue(int node, int value) {
        nodes[node].value = value;
    }

    // 부모 노드 반환
    int getParent(int node) const {
        return nodes[node].parent;
    }

    // 노드의 깊이 반환
    int getDepth(int node) const {
        return nodes[node].depth;
    }

    // 서브트리 크기 반환
    int getSubtreeSize(int node) const {
        return nodes[node].subtree_size;
    }

    // 인접 노드 리스트 반환
    const std::vector<int>& getAdjacent(int node) const {
        return nodes[node].adj;
    }
};

// 구간 정보를 저장하는 구조체
struct SegmentInfo {
    long long total; // 구간의 총합
    long long prefix; // 최대 접두사 합
    long long suffix; // 최대 접미사 합
    long long maxsum; // 구간 내 최대 부분합

    SegmentInfo() : total(0), prefix(0), suffix(0), maxsum(0) {}

    // 단일 값으로 초기화하는 생성자
    SegmentInfo(long long val) {
        total = val;
        prefix = std::max(0LL, val);
        suffix = std::max(0LL, val);
        maxsum = std::max(0LL, val);
    }
};

// 두 구간 정보를 병합하는 함수
SegmentInfo merge(const SegmentInfo& left, const SegmentInfo& right) {
    SegmentInfo result;
    result.total = left.total + right.total;
    result.prefix = std::max(left.prefix, left.total + right.prefix);
    result.suffix = std::max(right.suffix, right.total + left.suffix);
    result.maxsum = std::max({left.maxsum, right.maxsum, left.suffix + right.prefix});
    return result;
}

class SegmentTree {
private:
    std::vector<SegmentInfo> tree;
    int n; // 리프 노드의 개수

    void build(const std::vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = SegmentInfo(arr[start]);
            return;
        }

        int mid = (start + end) / 2;
        build(arr, node * 2, start, mid);
        build(arr, node * 2 + 1, mid + 1, end);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = SegmentInfo(val);
            return;
        }

        int mid = (start + end) / 2;
        if (idx <= mid)
            update(node * 2, start, mid, idx, val);
        else
            update(node * 2 + 1, mid + 1, end, idx, val);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    SegmentInfo query(int node, int start, int end, int left, int right) {
        if (right < start || end < left) {
            return SegmentInfo();
        }

        if (left <= start && end <= right) {
            return tree[node];
        }

        int mid = (start + end) / 2;
        return merge(
            query(node * 2, start, mid, left, right),
            query(node * 2 + 1, mid + 1, end, left, right)
        );
    }

public:
    SegmentTree(const std::vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }

    // 특정 위치의 값을 업데이트
    void update(int idx, int val) {
        update(1, 0, n - 1, idx, val);
    }

    // 구간 [left, right]의 정보를 조회
    SegmentInfo query(int left, int right) {
        return query(1, 0, n - 1, left, right);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // 입력: 노드의 개수
    int N;
    std::cin >> N;

    // 입력: 각 노드의 초기 값
    std::vector<int> values(N);
    for (int i = 0; i < N; i++) {
        std::cin >> values[i];
    }

    // 트리 객체 생성
    Tree tree(N, values);

    // 입력: 간선 정보
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        tree.addEdge(u, v);
    }

    // 트리 초기화(DFS, HLD, 세그먼트 트리 구성)
    tree.initialize();

    // 입력: 쿼리의 개수
    int Q;
    std::cin >> Q;

    // 쿼리 처리
    while(Q--) {
        std::string query_type;
        std::cin >> query_type;

        if (query_type == "U") {
            // 업데이트 쿼리
            int node, new_value;
            std::cin >> node >> new_value;
            tree.update_node(node, new_value);
        }
        else { // query_type = "Q"
            // 경로 쿼리
            int u, v;
            std::cin >> u >> v;
            long long result = tree.query_max_path_sum(u, v);
            std::cout << result << '\n';

        }
    }
    return 0;
}