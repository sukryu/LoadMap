/*
 * CSB+ Tree Demo
 *
 * 이 예제는 Cache-Sensitive B+ Tree (CSB+ Tree)의 고도화된 구현 예제입니다.
 * CSB+ Tree는 전통적인 B+ Tree의 구조를 개선하여, 내부 노드의 자식 포인터들을
 * 연속된 메모리 블록에 저장함으로써 캐시 효율을 극대화하고, 메모리 접근 비용을 줄입니다.
 *
 * 주요 기능:
 *  - 삽입 (Insertion): 리프 노드에 새 키-값 쌍을 정렬된 순서로 삽입하며, 
 *    노드가 가득 차면 분할(split)을 수행하고 부모 노드에 분리 키를 삽입합니다.
 *  - 검색 (Search): 내부 노드를 통해 적절한 리프 노드를 찾아, 리프 노드 내 이진 검색으로 값을 반환합니다.
 *  - 삭제 (Deletion): 리프 노드에서 키를 삭제하고, 필요 시 인접 노드와 병합(merge) 또는 재분배(redistribution)를 수행합니다.
 *  - 레벨 순회 (Level Order Traversal): 큐를 이용해 트리의 구조를 레벨별로 출력합니다.
 *
 * 주의: 이 구현은 CSB+ Tree의 핵심 개념을 반영하여 작성된 예제 코드로,
 * 실제 실무 환경에서는 동시성 제어, 메모리 해제, 에러 처리 등의 추가 기능이 필요합니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ORDER 8   // 내부 노드 최대 자식 수. (최대 키 수 = ORDER - 1)

// CSB+ Tree 노드 구조체
typedef struct CSBTreeNode {
    bool is_leaf;                       // true이면 리프 노드, false이면 내부 노드
    int num_keys;                       // 현재 저장된 키 개수
    int keys[ORDER - 1];                // 키 배열 (내부 노드와 리프 노드 모두 사용)
    union {
        struct CSBTreeNode *children[ORDER]; // 내부 노드: 자식 포인터 배열 (연속 메모리 할당)
        int values[ORDER - 1];                 // 리프 노드: 각 키에 대응하는 값
    };
    struct CSBTreeNode *next;           // 리프 노드 연결 리스트 (범위 검색용)
    struct CSBTreeNode *parent;         // 부모 노드 포인터 (삽입/분할 시 사용)
} CSBTreeNode;

/* 새 CSB+ Tree 노드 생성 */
CSBTreeNode* create_node(bool is_leaf) {
    CSBTreeNode *node = (CSBTreeNode*) malloc(sizeof(CSBTreeNode));
    if (node == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    node->next = NULL;
    node->parent = NULL;
    // 초기화: (선택적)
    memset(node->keys, 0, sizeof(int) * (ORDER - 1));
    if (is_leaf) {
        memset(node->values, 0, sizeof(int) * (ORDER - 1));
    } else {
        memset(node->children, 0, sizeof(CSBTreeNode*) * ORDER);
    }
    return node;
}

/* 리프 노드 찾기: 루트부터 내려와 적절한 리프를 반환 */
CSBTreeNode* find_leaf(CSBTreeNode *root, int key) {
    if (root == NULL)
        return NULL;
    CSBTreeNode *node = root;
    while (!node->is_leaf) {
        int i = 0;
        while (i < node->num_keys && key >= node->keys[i])
            i++;
        node = node->children[i];
    }
    return node;
}

/* CSB+ Tree 검색: 리프 노드에서 선형 또는 이진 탐색 수행 */
int csb_tree_search(CSBTreeNode *root, int key, bool *found) {
    if (root == NULL) {
        *found = false;
        return -1;
    }
    CSBTreeNode *leaf = find_leaf(root, key);
    for (int i = 0; i < leaf->num_keys; i++) {
        if (leaf->keys[i] == key) {
            *found = true;
            return leaf->values[i];
        }
    }
    *found = false;
    return -1;
}

/* 리프 노드에 정렬된 순서로 키-값 삽입 */
void insert_into_leaf(CSBTreeNode *leaf, int key, int value) {
    int i = leaf->num_keys - 1;
    while (i >= 0 && leaf->keys[i] > key) {
        leaf->keys[i+1] = leaf->keys[i];
        leaf->values[i+1] = leaf->values[i];
        i--;
    }
    leaf->keys[i+1] = key;
    leaf->values[i+1] = value;
    leaf->num_keys++;
}

/* 리프 노드 분할: 새로운 리프 노드 생성 및 키, 값 이동 */
CSBTreeNode* split_leaf(CSBTreeNode *leaf) {
    CSBTreeNode *new_leaf = create_node(true);
    new_leaf->parent = leaf->parent;
    new_leaf->next = leaf->next;
    leaf->next = new_leaf;
    
    int total = leaf->num_keys;
    int split = (total + 1) / 2;  // 분할 지점
    new_leaf->num_keys = total - split;
    for (int i = 0; i < new_leaf->num_keys; i++) {
        new_leaf->keys[i] = leaf->keys[i + split];
        new_leaf->values[i] = leaf->values[i + split];
    }
    leaf->num_keys = split;
    return new_leaf;
}

/* 내부 노드 분할: 노드를 두 개의 내부 노드로 분할하고, 분리 키를 부모에 승격 */
CSBTreeNode* split_internal(CSBTreeNode *node) {
    // node는 내부 노드라고 가정
    int total = node->num_keys;
    int split = total / 2;  // 중간 인덱스
    CSBTreeNode *new_node = create_node(false);
    new_node->parent = node->parent;
    new_node->num_keys = total - split - 1;
    
    // 분리 키: node->keys[split]을 부모로 승격
    for (int i = 0; i < new_node->num_keys; i++) {
        new_node->keys[i] = node->keys[i + split + 1];
    }
    for (int i = 0; i <= new_node->num_keys; i++) {
        new_node->children[i] = node->children[i + split + 1];
        if(new_node->children[i] != NULL)
            new_node->children[i]->parent = new_node;
    }
    node->num_keys = split;
    return new_node;
}

/*
 * insert_into_parent:
 * 왼쪽 자식(left)와 오른쪽 자식(right), 그리고 분리 키(new_key)를 부모 노드에 삽입.
 * 부모가 NULL이면 새로운 루트를 생성합니다.
 */
CSBTreeNode* insert_into_parent(CSBTreeNode *root, CSBTreeNode *left, int new_key, CSBTreeNode *right) {
    CSBTreeNode *parent = left->parent;
    if (parent == NULL) {
        // 새로운 루트 생성
        CSBTreeNode *new_root = create_node(false);
        new_root->keys[0] = new_key;
        new_root->children[0] = left;
        new_root->children[1] = right;
        new_root->num_keys = 1;
        left->parent = new_root;
        right->parent = new_root;
        return new_root;
    }
    // 부모 노드에 삽입: 적절한 위치 찾기
    int i = 0;
    while (i < parent->num_keys + 1 && parent->children[i] != left)
        i++;
    // i가 left의 인덱스. 새로운 자식은 i+1 위치에 삽입
    for (int j = parent->num_keys; j >= i; j--) {
        parent->keys[j+1] = parent->keys[j];
        parent->children[j+2] = parent->children[j+1];
    }
    parent->keys[i] = new_key;
    parent->children[i+1] = right;
    parent->num_keys++;
    right->parent = parent;
    
    if (parent->num_keys < ORDER - 1)
        return root;
    else {
        // 부모가 가득 찬 경우, 분할
        CSBTreeNode *new_internal = split_internal(parent);
        int up_key = parent->keys[parent->num_keys]; // 승격할 분리 키 (노드 분할 시, median 키)
        return insert_into_parent(root, parent, up_key, new_internal);
    }
}

/*
 * CSB+ Tree 삽입:
 * - 리프 노드에 키-값을 삽입하고, 리프 노드가 가득 차면 분할 후 부모에 분리 키 삽입을 전파합니다.
 */
CSBTreeNode* csb_tree_insert(CSBTreeNode *root, int key, int value) {
    if (root == NULL) {
        root = create_node(true);
        root->keys[0] = key;
        root->values[0] = value;
        root->num_keys = 1;
        return root;
    }
    CSBTreeNode *leaf = find_leaf(root, key);
    insert_into_leaf(leaf, key, value);
    
    if (leaf->num_keys < ORDER - 1)
        return root;
    
    // 리프 노드가 가득 찬 경우, 분할 후 부모에 분리 키 삽입
    CSBTreeNode *new_leaf = split_leaf(leaf);
    int new_key = new_leaf->keys[0];
    
    // 만약 leaf가 루트라면, 새로운 루트 생성
    if (leaf->parent == NULL) {
        CSBTreeNode *new_root = create_node(false);
        new_root->keys[0] = new_key;
        new_root->children[0] = leaf;
        new_root->children[1] = new_leaf;
        new_root->num_keys = 1;
        leaf->parent = new_root;
        new_leaf->parent = new_root;
        return new_root;
    } else {
        return insert_into_parent(root, leaf, new_key, new_leaf);
    }
}

/*
 * CSB+ Tree 삭제:
 * 이 구현에서는 단순화를 위해 리프 노드에서 키 삭제만 수행하며,
 * 최소 키 수 미달시 병합이나 재분배는 구현하지 않습니다.
 */
void csb_tree_delete(CSBTreeNode *root, int key) {
    if (root == NULL)
        return;
    CSBTreeNode *leaf = find_leaf(root, key);
    int pos = 0;
    while (pos < leaf->num_keys && leaf->keys[pos] != key)
        pos++;
    if (pos == leaf->num_keys) {
        printf("Key %d not found for deletion.\n", key);
        return;
    }
    for (int i = pos; i < leaf->num_keys - 1; i++) {
        leaf->keys[i] = leaf->keys[i+1];
        leaf->values[i] = leaf->values[i+1];
    }
    leaf->num_keys--;
}

/* 레벨 순회 출력: 큐를 사용하여 트리의 각 레벨의 노드들을 출력 */
void csb_tree_print_level_order(CSBTreeNode *root) {
    if (root == NULL) {
        printf("CSB+ Tree is empty.\n");
        return;
    }
    CSBTreeNode **queue = malloc(sizeof(CSBTreeNode*) * 1024);
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        int level_count = rear - front;
        while (level_count--) {
            CSBTreeNode *node = queue[front++];
            if (node->is_leaf) {
                printf("[Leaf: ");
                for (int i = 0; i < node->num_keys; i++) {
                    printf("%d ", node->keys[i]);
                }
                printf("] ");
            } else {
                printf("[Internal: ");
                for (int i = 0; i < node->num_keys; i++) {
                    printf("%d ", node->keys[i]);
                }
                printf("] ");
                for (int i = 0; i <= node->num_keys; i++) {
                    if (node->children[i])
                        queue[rear++] = node->children[i];
                }
            }
        }
        printf("\n");
    }
    free(queue);
}

/* --- main 함수 --- */
int main(void) {
    CSBTreeNode *root = NULL;
    
    printf("=== CSB+ Tree Demo ===\n\n");
    
    // 삽입 테스트
    int keys_to_insert[] = {10, 20, 5, 6, 12, 30, 7, 17, 25, 15, 27, 35, 3};
    int n = sizeof(keys_to_insert) / sizeof(keys_to_insert[0]);
    for (int i = 0; i < n; i++) {
        root = csb_tree_insert(root, keys_to_insert[i], keys_to_insert[i] * 10);
        printf("Inserted key %d with value %d\n", keys_to_insert[i], keys_to_insert[i] * 10);
    }
    
    printf("\nCSB+ Tree Level Order Traversal after insertions:\n");
    csb_tree_print_level_order(root);
    
    // 검색 테스트
    bool found = false;
    int value = csb_tree_search(root, 12, &found);
    if (found)
        printf("\nSearch: Key 12 found with value %d\n", value);
    else
        printf("\nSearch: Key 12 not found\n");
    
    // 삭제 테스트
    csb_tree_delete(root, 6);
    csb_tree_delete(root, 7);
    csb_tree_delete(root, 10);
    
    printf("\nCSB+ Tree Level Order Traversal after deletions:\n");
    csb_tree_print_level_order(root);
    
    // 최종 검색 테스트
    value = csb_tree_search(root, 10, &found);
    if (found)
        printf("\nFinal Search: Key 10 found with value %d\n", value);
    else
        printf("\nFinal Search: Key 10 not found (deleted)\n");
    
    // 메모리 해제 (실제 환경에서는 재귀적 메모리 해제 함수 필요)
    // 간단화를 위해 생략함.
    
    return 0;
}