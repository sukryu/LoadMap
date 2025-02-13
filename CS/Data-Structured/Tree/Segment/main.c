/*
 * main.c
 *
 * 이 파일은 세그먼트 트리(Segment Tree)를 활용한 고도화된 예제입니다.
 * 세그먼트 트리는 주어진 배열에 대해 구간 합, 구간 최소/최댓값 등 다양한 구간 질의를 
 * 효율적으로 처리할 수 있도록 도와주는 자료구조입니다.
 *
 * 이 구현에서는 포인터 기반의 트리 구조를 사용하며, 
 * "lazy propagation" 기법을 도입하여 구간 업데이트(range update) 연산을 최적화합니다.
 *
 * 주요 기능:
 * - buildSegmentTree: 배열을 기반으로 세그먼트 트리 구축 (O(n))
 * - queryRange: 주어진 구간 [l, r]에 대한 합을 O(log n)에 계산
 * - updateRange: 구간 [l, r]에 일정 값을 더하는 업데이트를 lazy propagation을 통해 O(log n)에 수행
 * - freeTree: 트리에 할당된 메모리를 재귀적으로 해제
 *
 * 이 코드는 B+ Tree의 복잡한 구현 사례처럼 세그먼트 트리의 다양한 케이스(완전한 lazy propagation, 
 * 부분 겹침, 전체 겹침 등)를 모두 처리하도록 고도화되어 있습니다.
 *
 * 참고: 실무에서 사용하기 위해서는 추가적인 에러 처리, 동적 메모리 최적화, 입력 검증 등이 필요합니다.
 */

#include <stdio.h>
#include <stdlib.h>

// 세그먼트 트리 노드 구조체 정의
typedef struct SegmentTreeNode {
    int start;                      // 구간 시작 인덱스
    int end;                        // 구간 종료 인덱스
    int sum;                        // 해당 구간의 합
    int lazy;                       // lazy propagation 값 (구간 업데이트가 지연된 누적 값)
    struct SegmentTreeNode *left;   // 왼쪽 자식 노드 (구간: [start, mid])
    struct SegmentTreeNode *right;  // 오른쪽 자식 노드 (구간: [mid+1, end])
} SegmentTreeNode;

/*
 * buildSegmentTree 함수:
 * 주어진 배열(arr)와 구간 [start, end]에 대해 세그먼트 트리를 재귀적으로 구축합니다.
 * 리프 노드에서는 단일 원소의 값을, 내부 노드에서는 자식 노드들의 합을 저장합니다.
 */
SegmentTreeNode* buildSegmentTree(int arr[], int start, int end) {
    SegmentTreeNode *node = (SegmentTreeNode*) malloc(sizeof(SegmentTreeNode));
    if (node == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    node->start = start;
    node->end = end;
    node->lazy = 0;  // 초기 lazy 값은 0
    node->left = node->right = NULL;
    
    // 리프 노드인 경우, 배열의 단일 값 저장
    if (start == end) {
        node->sum = arr[start];
    } else {
        // 내부 노드: 구간을 반으로 분할하여 자식 노드 생성
        int mid = (start + end) / 2;
        node->left = buildSegmentTree(arr, start, mid);
        node->right = buildSegmentTree(arr, mid + 1, end);
        // 현재 노드의 합은 좌우 자식 노드의 합
        node->sum = node->left->sum + node->right->sum;
    }
    return node;
}

/*
 * propagate 함수:
 * 현재 노드에 지연되어 있는(lazy) 업데이트 값을 자식 노드로 전파하고, 
 * 현재 노드의 값을 올바르게 갱신합니다.
 */
void propagate(SegmentTreeNode *node) {
    if (node->lazy != 0) {
        // 현재 노드 구간의 길이 계산
        int len = node->end - node->start + 1;
        // lazy 값 적용: 현재 노드의 sum 업데이트
        node->sum += node->lazy * len;
        
        // 만약 현재 노드가 리프가 아니라면 자식 노드에 lazy 값 전달
        if (node->start != node->end) {
            node->left->lazy += node->lazy;
            node->right->lazy += node->lazy;
        }
        // 현재 노드의 lazy 값 초기화
        node->lazy = 0;
    }
}

/*
 * updateRange 함수:
 * 세그먼트 트리에서 구간 [l, r]에 대해 val을 더하는 업데이트를 수행합니다.
 * lazy propagation을 이용하여 부분 겹침(overlap) 케이스도 효율적으로 처리합니다.
 */
void updateRange(SegmentTreeNode *node, int l, int r, int val) {
    if (node == NULL)
        return;
    
    // 현재 노드에 지연된 업데이트를 먼저 처리
    propagate(node);
    
    // 현재 노드 구간이 업데이트 범위와 전혀 겹치지 않는 경우
    if (node->end < l || node->start > r)
        return;
    
    // 현재 노드 구간이 업데이트 범위를 완전히 포함하는 경우
    if (node->start >= l && node->end <= r) {
        node->lazy += val;
        propagate(node);
        return;
    }
    
    // 구간이 부분적으로 겹치는 경우, 자식 노드에 대해 재귀적 업데이트 수행
    updateRange(node->left, l, r, val);
    updateRange(node->right, l, r, val);
    // 자식 노드 업데이트 후 현재 노드의 합 재계산
    node->sum = node->left->sum + node->right->sum;
}

/*
 * queryRange 함수:
 * 세그먼트 트리에서 구간 [l, r]의 합을 계산하여 반환합니다.
 * lazy propagation을 통해 지연 업데이트된 값들도 반영합니다.
 */
int queryRange(SegmentTreeNode *node, int l, int r) {
    if (node == NULL)
        return 0;
    
    // 현재 노드에 지연된 업데이트가 있으면 먼저 적용
    propagate(node);
    
    // 현재 노드 구간과 질의 범위가 전혀 겹치지 않으면 0 반환
    if (node->end < l || node->start > r)
        return 0;
    
    // 현재 노드 구간이 질의 범위를 완전히 포함하면 현재 노드의 sum 반환
    if (node->start >= l && node->end <= r)
        return node->sum;
    
    // 부분 겹침인 경우, 좌우 자식 노드에 대해 질의 수행
    int leftSum = queryRange(node->left, l, r);
    int rightSum = queryRange(node->right, l, r);
    return leftSum + rightSum;
}

/*
 * freeSegmentTree 함수:
 * 세그먼트 트리에 할당된 메모리를 재귀적으로 해제합니다.
 */
void freeSegmentTree(SegmentTreeNode *node) {
    if (node == NULL)
        return;
    freeSegmentTree(node->left);
    freeSegmentTree(node->right);
    free(node);
}

/*
 * printSegmentTree 함수:
 * 세그먼트 트리의 현재 상태를 레벨 순회 방식으로 출력합니다.
 * (디버깅 및 구조 확인 용도)
 */
void printSegmentTree(SegmentTreeNode *root) {
    if (root == NULL) {
        printf("세그먼트 트리가 비어 있습니다.\n");
        return;
    }
    // 간단한 큐 배열을 사용 (최대 노드 수 100 가정)
    SegmentTreeNode *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    
    printf("세그먼트 트리 레벨 순회:\n");
    while (front < rear) {
        int count = rear - front;
        while (count > 0) {
            SegmentTreeNode *node = queue[front++];
            printf("[[%d, %d]: sum=%d] ", node->start, node->end, node->sum);
            if (node->left != NULL)
                queue[rear++] = node->left;
            if (node->right != NULL)
                queue[rear++] = node->right;
            count--;
        }
        printf("\n");
    }
}

/*
 * main 함수:
 * 예제 배열에 대해 세그먼트 트리를 구축하고, 구간 질의 및 업데이트 연산을 수행하는 시연 프로그램입니다.
 */
int main(void) {
    // 예제 배열 (인덱스 0부터 n-1까지)
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    // 세그먼트 트리 구축
    SegmentTreeNode *root = buildSegmentTree(arr, 0, n - 1);
    printf("원본 배열: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n세그먼트 트리 구축 완료.\n");
    
    // 레벨 순회로 트리 구조 출력 (디버깅용)
    printSegmentTree(root);
    printf("\n");
    
    // 구간 질의 예제: 인덱스 1부터 3까지의 합 (3 + 5 + 7 = 15)
    int q1 = queryRange(root, 1, 3);
    printf("구간 [1, 3]의 합: %d\n", q1);
    
    // 구간 업데이트 예제: 인덱스 1부터 3까지에 10을 더함
    printf("\n구간 [1, 3]에 10을 더합니다.\n");
    updateRange(root, 1, 3, 10);
    
    // 업데이트 후 구간 질의: 인덱스 1부터 3까지의 합
    int q2 = queryRange(root, 1, 3);
    printf("업데이트 후 구간 [1, 3]의 합: %d\n", q2);
    
    // 전체 배열 구간 질의
    int q3 = queryRange(root, 0, n - 1);
    printf("전체 배열 구간 [0, %d]의 합: %d\n", n - 1, q3);
    
    // 레벨 순회로 업데이트 후 트리 구조 출력
    printf("\n업데이트 후 세그먼트 트리 상태:\n");
    printSegmentTree(root);
    
    // 메모리 해제
    freeSegmentTree(root);
    printf("\n세그먼트 트리 메모리 해제 완료.\n");
    
    return 0;
}