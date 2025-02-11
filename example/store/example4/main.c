#include <stdio.h>
#include <stdlib.h>

// 입력값 검증을 위한 상수 정의
#define MAX_N 10000
#define MAX_Q 10000

// 세그먼트 트리
long long *tree; // 세그먼트 트리 배열
long long *lazy; // lazy propagation을 위한 배열
int *arr;        // 입력 배열
int n;           // 배열의 크기

// 트리의 크기를 계산하는 함수
int get_tree_size(int n) {
    int size = 1;
    while (size < n) {
        size *= 2;
    }
    return size * 2;
}

// 메모리 할당 및 초기화 함수
void init(int size) {
    int tree_size = get_tree_size(size);

    // 동적 메모리 할당
    tree = (long long*)calloc(tree_size, sizeof(long long));
    lazy = (long long*)calloc(tree_size, sizeof(long long));
    arr = (int*)calloc(size, sizeof(int));

    if (!tree || !lazy || !arr) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
}

void build(int node, int start, int end) {
    if (start == end) {
        // 리프 노드인 경우
        tree[node] = arr[start];
        return;
    }

    int mid = (start + end) / 2;

    // 왼쪽 자식과 오른쪽 자식을 재귀적으로 구축
    build(node * 2, start, mid);
    build(node * 2 + 1, mid + 1, end);

    // 현재 노드의 값은 양쪽 자식 노드의 합
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

long long query(int node, int start, int end, int left, int right) {
    // lazy 값이 있다면 먼저 처리
    if (lazy[node] != 0) {
        tree[node] += lazy[node] * (end - start + 1);
        if (start != end) {  // 리프 노드가 아니면 자식에게 전파
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    // 구간이 전혀 겹치지 않는 경우
    if (right < start || end < left) {
        return 0;
    }

    // 구간이 완전히 포함되는 경우
    if (left <= start && end <= right) {
        return tree[node];
    }

    // 구간이 일부만 겹치는 경우
    int mid = (start + end) / 2;
    long long left_sum = query(node * 2, start, mid, left, right);
    long long right_sum = query(node * 2 + 1, mid + 1, end, left, right);

    return left_sum + right_sum;
}

void update(int node, int start, int end, int left, int right, long long diff) {
    // lazy 값이 있다면 먼저 처리
    if (lazy[node] != 0) {
        tree[node] += lazy[node] * (end - start + 1);
        if (start != end) {  // 리프 노드가 아니면 자식에게 전파
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    // 구간이 전혀 겹치지 않는 경우
    if (right < start || end < left) {
        return;
    }

    // 구간이 완전히 포함되는 경우
    if (left <= start && end <= right) {
        tree[node] += diff * (end - start + 1);
        if (start != end) {  // 리프 노드가 아니면 lazy 업데이트
            lazy[node * 2] += diff;
            lazy[node * 2 + 1] += diff;
        }
        return;
    }

    // 구간이 일부만 겹치는 경우
    int mid = (start + end) / 2;
    update(node * 2, start, mid, left, right, diff);
    update(node * 2 + 1, mid + 1, end, left, right, diff);

    // 자식 노드들의 값을 결합
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

// 메모리 해제 함수
void cleanup() {
    free(tree);
    free(lazy);
    free(arr);
}
// 세그먼트 트리 끝

// 입력값 검증 함수
int validate_input(int n, int q) {
    if (n < 1 || n > MAX_N) {
        fprintf(stderr, "Error: Array size must be between 1 and %d\n", MAX_N);
        return 0;
    }
    if (q < 1 || q > MAX_Q) {
        fprintf(stderr, "Error: Query count must be between 1 and %d\n", MAX_Q);
        return 0;
    }
    return 1;
}

// 범위 검증 함수
int validate_range(int left, int right, int n) {
    if (left < 1 || right > n || left > right) {
        fprintf(stderr, "Error: Invalid range [%d, %d] for array size %d\n", 
                left, right, n);
        return 0;
    }
    return 1;
}

int main() {
    int Q;

    // 배열 크기와 쿼리 개수 입력 및 검증
    if (scanf("%d %d", &n, &Q) != 2) {
        fprintf(stderr, "Error: Failed to read N and Q\b");
        return 1;
    }

    if (!validate_input(n, Q)) {
        return 1;
    }

    // 메모리 초기화
    init(n);

    // 초기 배열 입력 및 검증
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Error: Failed to read array element at index %d\n", i);
            cleanup();
            return 1;
        }
    }

    // 세그먼트 트리 구축
    build(1, 0, n - 1);

    // 쿼리 처리
    for (int i = 0; i < Q; i++) {
        char query_type;
        if (scanf(" %c", &query_type) != 1) {
            fprintf(stderr, "Error: Failed to read query type at query %d\n", i + 1);
            cleanup();
            return 1;
        }

        if (query_type == 'U') {
            int left, right;
            long long value;
            if (scanf("%d %d %lld", &left, &right, &value) != 3) {
                fprintf(stderr, "Error: Failed to read update query parameters at query %d\n", i + 1);
                cleanup();
                return 1;
            }

            if (!validate_range(left, right, n)) {
                cleanup();
                return 1;
            }

            update(1, 0, n - 1, left - 1, right - 1, value);
        }
        else if (query_type == 'Q') {
            int left, right;
            if (scanf("%d %d", &left, &right) != 2) {
                fprintf(stderr, "Error: Failed to read query parameters at query %d\n", i + 1);
                cleanup();
                return 1;
            }

            if (!validate_range(left, right, n)) {
                cleanup();
                return 1;
            }

            long long result = query(1, 0, n - 1, left - 1, right - 1);
            printf("%lld\n", result);
        }
        else {
            fprintf(stderr, "Error: Invalid query type '%c' at query %d\n", query_type, i + 1);
            cleanup();
            return 1;
        }
    }

    cleanup();

    return 0;
}
