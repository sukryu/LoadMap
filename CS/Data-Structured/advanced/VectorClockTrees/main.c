/*
 * Vector Clock Tree Demo
 *
 * 이 예제는 분산 시스템에서 이벤트의 인과 관계를 추적하기 위해
 * 벡터 시계(Vector Clock)를 트리 구조와 결합한 Vector Clock Tree의
 * 고도화된 구현 예제입니다.
 *
 * 각 노드(VCTreeNode)는 이벤트 ID, 이벤트 데이터를 저장하고,
 * 고정 크기의 벡터 시계(배열)를 포함합니다.  
 * 이 트리 구조는 단순한 이진 탐색 트리(BST)로 구현되며,
 * 이벤트의 순서와 인과 관계를 판단하기 위해 벡터 시계를 비교하는 기능을 포함합니다.
 *
 * 주요 기능:
 *  - create_vc_tree_node(): 새로운 이벤트 노드를 생성합니다.
 *  - insert_vc_tree_node(): 이벤트 ID를 기준으로 트리에 노드를 삽입합니다.
 *  - search_vc_tree(): 이벤트 ID로 노드를 검색합니다.
 *  - compare_vector_clock(): 두 벡터 시계의 인과 관계를 비교합니다.
 *  - print_inorder(): 중위 순회 방식으로 트리의 내용을 출력합니다.
 *  - free_vc_tree(): 트리의 모든 노드에 할당된 메모리를 해제합니다.
 *
 * 이 구현은 단순화를 위해 균형 트리 대신 기본 이진 탐색 트리로 작성되었으며,
 * 실무에서는 AVL, 레드-블랙 트리와 같은 균형 트리 구조 또는 다른 고성능 인덱스 구조와 결합하여 사용될 수 있습니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PROCESSES 4  // 벡터 시계의 크기 (분산 시스템 참여자 수)

// Enum: 벡터 시계 비교 결과
typedef enum {
    VC_LESS,      // a happened before b
    VC_GREATER,   // a happened after b
    VC_EQUAL,     // a and b are equal
    VC_CONCURRENT // a and b are concurrent (동시 발생)
} VCComparison;

// 벡터 시계 구조체 (고정 크기 배열)
typedef struct {
    int clock[MAX_PROCESSES];
} VectorClock;

// Vector Clock Tree 노드 구조체
typedef struct VCTreeNode {
    int event_id;                // 노드 키 (이벤트 ID)
    char *data;                  // 이벤트 데이터 (동적 문자열)
    VectorClock vclock;          // 벡터 시계
    struct VCTreeNode *left;     // 왼쪽 자식
    struct VCTreeNode *right;    // 오른쪽 자식
} VCTreeNode;

/* 벡터 시계 출력 함수 */
void print_vector_clock(const VectorClock *vc) {
    printf("[");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("%d", vc->clock[i]);
        if (i < MAX_PROCESSES - 1)
            printf(", ");
    }
    printf("]");
}

/* 두 벡터 시계를 비교하는 함수
   반환값:
     VC_LESS:  a <= b and a != b (즉, a happened before b)
     VC_GREATER: a >= b and a != b (즉, a happened after b)
     VC_EQUAL: a == b
     VC_CONCURRENT: 서로 인과 관계를 결정할 수 없음 (동시 발생)
*/
VCComparison compare_vector_clock(const VectorClock *a, const VectorClock *b) {
    bool a_le_b = true;
    bool a_ge_b = true;
    bool equal = true;
    
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (a->clock[i] < b->clock[i]) {
            a_ge_b = false;
            equal = false;
        } else if (a->clock[i] > b->clock[i]) {
            a_le_b = false;
            equal = false;
        }
    }
    if (equal)
        return VC_EQUAL;
    else if (a_le_b)
        return VC_LESS;
    else if (a_ge_b)
        return VC_GREATER;
    else
        return VC_CONCURRENT;
}

/* VCTreeNode 생성: event_id, 데이터, 벡터 시계 배열(크기 MAX_PROCESSES)를 인자로 받음 */
VCTreeNode* create_vc_tree_node(int event_id, const char *data, int clock_array[MAX_PROCESSES]) {
    VCTreeNode *node = (VCTreeNode*)malloc(sizeof(VCTreeNode));
    if (!node) {
        fprintf(stderr, "메모리 할당 실패 (VCTreeNode)\n");
        exit(EXIT_FAILURE);
    }
    node->event_id = event_id;
    node->data = strdup(data);
    if (!node->data) {
        fprintf(stderr, "메모리 할당 실패 (data)\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MAX_PROCESSES; i++) {
        node->vclock.clock[i] = clock_array[i];
    }
    node->left = node->right = NULL;
    return node;
}

/* 이진 탐색 트리(BST) 삽입: event_id를 기준으로 트리에 노드 삽입 */
VCTreeNode* insert_vc_tree_node(VCTreeNode *root, VCTreeNode *node) {
    if (root == NULL)
        return node;
    if (node->event_id < root->event_id)
        root->left = insert_vc_tree_node(root->left, node);
    else if (node->event_id > root->event_id)
        root->right = insert_vc_tree_node(root->right, node);
    else {
        // 동일 event_id가 존재하면, 데이터를 업데이트하고 벡터 시계 갱신
        free(root->data);
        root->data = strdup(node->data);
        for (int i = 0; i < MAX_PROCESSES; i++) {
            root->vclock.clock[i] = node->vclock.clock[i];
        }
        free(node->data);
        free(node);
    }
    return root;
}

/* event_id로 트리에서 노드 검색 */
VCTreeNode* search_vc_tree(VCTreeNode *root, int event_id) {
    if (root == NULL)
        return NULL;
    if (event_id == root->event_id)
        return root;
    else if (event_id < root->event_id)
        return search_vc_tree(root->left, event_id);
    else
        return search_vc_tree(root->right, event_id);
}

/* 중위 순회로 트리 출력: 각 노드의 event_id와 데이터, 벡터 시계 출력 */
void print_inorder(VCTreeNode *root) {
    if (root == NULL)
        return;
    print_inorder(root->left);
    printf("Event ID: %d, Data: %s, Vector Clock: ", root->event_id, root->data);
    print_vector_clock(&root->vclock);
    printf("\n");
    print_inorder(root->right);
}

/* 트리의 모든 노드 메모리 해제 */
void free_vc_tree(VCTreeNode *root) {
    if (root == NULL)
        return;
    free_vc_tree(root->left);
    free_vc_tree(root->right);
    free(root->data);
    free(root);
}

/* main 함수: 데모 시뮬레이션 */
int main(void) {
    VCTreeNode *root = NULL;
    
    // 예제 벡터 시계 배열 (4 프로세스, 인덱스별 카운트)
    int vc1[MAX_PROCESSES] = {1, 0, 0, 0};
    int vc2[MAX_PROCESSES] = {1, 1, 0, 0};
    int vc3[MAX_PROCESSES] = {2, 1, 0, 0};
    int vc4[MAX_PROCESSES] = {2, 2, 0, 0};
    int vc5[MAX_PROCESSES] = {2, 2, 1, 0};
    
    // 이벤트 노드 생성: (event_id, 데이터, 벡터 시계)
    VCTreeNode *node1 = create_vc_tree_node(1, "Event 1", vc1);
    VCTreeNode *node2 = create_vc_tree_node(2, "Event 2", vc2);
    VCTreeNode *node3 = create_vc_tree_node(3, "Event 3", vc3);
    VCTreeNode *node4 = create_vc_tree_node(4, "Event 4", vc4);
    VCTreeNode *node5 = create_vc_tree_node(5, "Event 5", vc5);
    
    // 트리에 노드 삽입 (event_id를 기준으로 BST 삽입)
    root = insert_vc_tree_node(root, node3);
    root = insert_vc_tree_node(root, node1);
    root = insert_vc_tree_node(root, node4);
    root = insert_vc_tree_node(root, node2);
    root = insert_vc_tree_node(root, node5);
    
    printf("=== Vector Clock Tree In-Order Traversal ===\n");
    print_inorder(root);
    
    // 검색 데모: event_id 3 검색
    int search_id = 3;
    VCTreeNode *found_node = search_vc_tree(root, search_id);
    if (found_node) {
        printf("\nSearch: Found event with ID %d\n", search_id);
        printf("Data: %s, Vector Clock: ", found_node->data);
        print_vector_clock(&found_node->vclock);
        printf("\n");
    } else {
        printf("\nSearch: Event with ID %d not found\n", search_id);
    }
    
    // 벡터 시계 비교 데모: event 2와 event 4의 벡터 시계 비교
    VCTreeNode *n2 = search_vc_tree(root, 2);
    VCTreeNode *n4 = search_vc_tree(root, 4);
    if (n2 && n4) {
        VCComparison cmp = compare_vector_clock(&n2->vclock, &n4->vclock);
        printf("\nVector Clock Comparison between Event 2 and Event 4:\n");
        printf("Event 2: ");
        print_vector_clock(&n2->vclock);
        printf("\nEvent 4: ");
        print_vector_clock(&n4->vclock);
        printf("\nResult: ");
        switch (cmp) {
            case VC_LESS:
                printf("Event 2 happened before Event 4\n");
                break;
            case VC_GREATER:
                printf("Event 2 happened after Event 4\n");
                break;
            case VC_EQUAL:
                printf("Event 2 and Event 4 are identical\n");
                break;
            case VC_CONCURRENT:
                printf("Event 2 and Event 4 are concurrent\n");
                break;
        }
    }
    
    // 메모리 해제
    free_vc_tree(root);
    
    return 0;
}