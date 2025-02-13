/*
 * B* Tree Demo
 *
 * 이 예제는 B* Tree 자료구조의 기본 동작을 시뮬레이션합니다.
 * B* Tree는 B-Tree의 변형으로, 노드의 최소 채움률(일반적으로 2/3 이상)을 유지하기 위해
 * 인접 노드와의 키 재분배 및 병합(merge) 과정을 활용합니다.
 *
 * 주요 기능:
 *  - 삽입 (Insertion): 리프 노드에 키-값 쌍을 정렬된 상태로 삽입하며,
 *    노드가 오버플로우될 경우 인접 형제 노드와 재분배하거나 분할(split)합니다.
 *  - 검색 (Search): 리프 노드에서 선형 탐색을 통해 키를 검색합니다.
 *  - 삭제 (Deletion): 리프 노드에서 키를 삭제한 후, 최소 채움률 미달 시 형제 노드와의 병합 또는 재분배를 수행합니다.
 *  - 순회 (Traversal): 레벨 순회(level order)를 통해 트리의 전체 구조를 출력합니다.
 *
 * 주의: 본 코드는 교육용 예제로, B* Tree의 핵심 아이디어(재분배, 분할, 병합)를 단순화하여 구현하였습니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDER 4
#define MAX_KEYS (ORDER - 1)
// 최소 채움률: B* Tree에서는 일반적으로 ceil(2*ORDER/3)-1. (ORDER=4: ceil(8/3)-1 = 3-1 = 2)
#define MIN_KEYS 2

typedef struct BStarTreeNode {
    int is_leaf;                   // 1이면 리프, 0이면 내부 노드
    int num_keys;                  // 현재 저장된 키 개수
    int keys[MAX_KEYS];            // 키 배열
    int values[MAX_KEYS];          // 리프 노드에 저장되는 값 (내부 노드는 미사용)
    struct BStarTreeNode *children[ORDER]; // 자식 포인터 (내부 노드용)
    struct BStarTreeNode *parent;  // 부모 포인터
} BStarTreeNode;

/* 함수 선언 */
BStarTreeNode* create_node(int is_leaf);
BStarTreeNode* find_leaf(BStarTreeNode *root, int key);
void insert_into_leaf(BStarTreeNode *leaf, int key, int value);
void handle_overflow(BStarTreeNode **root, BStarTreeNode *node);
void insert(BStarTreeNode **root, int key, int value);
int bstar_tree_search(BStarTreeNode *root, int key, bool *found);
void delete_key(BStarTreeNode **root, int key);
void handle_underflow(BStarTreeNode **root, BStarTreeNode *node);
void print_level_order(BStarTreeNode *root);

/* 노드 생성 */
BStarTreeNode* create_node(int is_leaf) {
    BStarTreeNode *node = (BStarTreeNode*) malloc(sizeof(BStarTreeNode));
    if (node == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    node->parent = NULL;
    for (int i = 0; i < ORDER; i++) {
        node->children[i] = NULL;
    }
    return node;
}

/* 키에 따라 적절한 리프 노드를 탐색 */
BStarTreeNode* find_leaf(BStarTreeNode *root, int key) {
    if (root == NULL)
        return NULL;
    BStarTreeNode *node = root;
    while (!node->is_leaf) {
        int i = 0;
        while (i < node->num_keys && key >= node->keys[i])
            i++;
        node = node->children[i];
    }
    return node;
}

/* 리프 노드에 정렬된 순서로 키-값 삽입 */
void insert_into_leaf(BStarTreeNode *leaf, int key, int value) {
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

/*
 * 노드 오버플로우 처리 (재분배 또는 분할)
 * B* Tree에서는 오버플로우된 노드와 인접 형제 노드 간의 키 재분배를 우선 시도합니다.
 * 만약 재분배가 불가능하면 노드를 분할하여 부모 노드에 승격합니다.
 */
void handle_overflow(BStarTreeNode **root, BStarTreeNode *node) {
    if (node->num_keys <= MAX_KEYS)
        return; // 오버플로우 아님

    BStarTreeNode *parent = node->parent;
    BStarTreeNode *left_sibling = NULL;
    BStarTreeNode *right_sibling = NULL;
    int index_in_parent = 0;

    if (parent != NULL) {
        // 부모의 children 배열에서 node의 인덱스 찾기
        for (int i = 0; i <= parent->num_keys; i++) {
            if (parent->children[i] == node) {
                index_in_parent = i;
                break;
            }
        }
        if (index_in_parent > 0)
            left_sibling = parent->children[index_in_parent - 1];
        if (index_in_parent < parent->num_keys)
            right_sibling = parent->children[index_in_parent + 1];
    }

    // 왼쪽 형제와 재분배 시도
    if (left_sibling && left_sibling->num_keys < MAX_KEYS) {
        int total_keys = left_sibling->num_keys + node->num_keys;
        int *temp_keys = (int*)malloc(sizeof(int) * total_keys);
        int *temp_values = NULL;
        if (node->is_leaf)
            temp_values = (int*)malloc(sizeof(int) * total_keys);

        // 왼쪽 형제의 키 복사
        for (int i = 0; i < left_sibling->num_keys; i++) {
            temp_keys[i] = left_sibling->keys[i];
            if (left_sibling->is_leaf)
                temp_values[i] = left_sibling->values[i];
        }
        // 현재 노드의 키 복사
        for (int i = 0; i < node->num_keys; i++) {
            temp_keys[left_sibling->num_keys + i] = node->keys[i];
            if (node->is_leaf)
                temp_values[left_sibling->num_keys + i] = node->values[i];
        }
        // 균등하게 재분배: 왼쪽 형제에 앞쪽, 현재 노드에 나머지 할당
        int split = total_keys / 2;
        left_sibling->num_keys = split;
        for (int i = 0; i < split; i++) {
            left_sibling->keys[i] = temp_keys[i];
            if (left_sibling->is_leaf)
                left_sibling->values[i] = temp_values[i];
        }
        node->num_keys = total_keys - split;
        for (int i = 0; i < node->num_keys; i++) {
            node->keys[i] = temp_keys[split + i];
            if (node->is_leaf)
                node->values[i] = temp_values[split + i];
        }
        // 부모의 구분 키 업데이트 (왼쪽 형제의 마지막 키가 구분 키)
        parent->keys[index_in_parent - 1] = node->keys[0];
        free(temp_keys);
        if (temp_values)
            free(temp_values);
        return;
    }

    // 오른쪽 형제와 재분배 시도
    if (right_sibling && right_sibling->num_keys < MAX_KEYS) {
        int total_keys = node->num_keys + right_sibling->num_keys;
        int *temp_keys = (int*)malloc(sizeof(int) * total_keys);
        int *temp_values = NULL;
        if (node->is_leaf)
            temp_values = (int*)malloc(sizeof(int) * total_keys);
        // 현재 노드의 키 복사
        for (int i = 0; i < node->num_keys; i++) {
            temp_keys[i] = node->keys[i];
            if (node->is_leaf)
                temp_values[i] = node->values[i];
        }
        // 오른쪽 형제의 키 복사
        for (int i = 0; i < right_sibling->num_keys; i++) {
            temp_keys[node->num_keys + i] = right_sibling->keys[i];
            if (node->is_leaf)
                temp_values[node->num_keys + i] = right_sibling->values[i];
        }
        int split = total_keys / 2;
        node->num_keys = split;
        for (int i = 0; i < split; i++) {
            node->keys[i] = temp_keys[i];
            if (node->is_leaf)
                node->values[i] = temp_values[i];
        }
        right_sibling->num_keys = total_keys - split;
        for (int i = 0; i < right_sibling->num_keys; i++) {
            right_sibling->keys[i] = temp_keys[split + i];
            if (node->is_leaf)
                right_sibling->values[i] = temp_values[split + i];
        }
        // 부모의 구분 키 업데이트 (오른쪽 형제의 첫 번째 키)
        parent->keys[index_in_parent] = right_sibling->keys[0];
        free(temp_keys);
        if (temp_values)
            free(temp_values);
        return;
    }

    // 재분배가 불가능한 경우, 노드 분할 수행
    int total_keys = node->num_keys; // 이미 새 키가 삽입된 상태
    int split = total_keys / 2;
    BStarTreeNode *new_node = create_node(node->is_leaf);
    new_node->parent = parent;
    new_node->num_keys = total_keys - split;
    for (int i = 0; i < new_node->num_keys; i++) {
        new_node->keys[i] = node->keys[split + i];
        if (node->is_leaf)
            new_node->values[i] = node->values[split + i];
    }
    node->num_keys = split;

    // 내부 노드의 경우, 자식 포인터 재조정
    if (!node->is_leaf) {
        for (int i = 0; i <= new_node->num_keys; i++) {
            new_node->children[i] = node->children[split + i];
            if (new_node->children[i])
                new_node->children[i]->parent = new_node;
        }
    }

    // 부모가 없는 경우, 새로운 루트 생성
    if (parent == NULL) {
        BStarTreeNode *new_root = create_node(0);
        new_root->keys[0] = new_node->keys[0]; // 구분 키
        new_root->children[0] = node;
        new_root->children[1] = new_node;
        new_root->num_keys = 1;
        node->parent = new_root;
        new_node->parent = new_root;
        *root = new_root;
    } else {
        // 부모의 children 배열에 new_node 삽입 (node 뒤에)
        int i;
        for (i = parent->num_keys; i > index_in_parent; i--) {
            parent->keys[i] = parent->keys[i-1];
            parent->children[i+1] = parent->children[i];
        }
        parent->keys[index_in_parent] = new_node->keys[0];
        parent->children[index_in_parent+1] = new_node;
        parent->num_keys++;
        // 부모에 대해 재귀적으로 오버플로우 처리
        handle_overflow(root, parent);
    }
}

/* B* Tree 삽입 인터페이스 */
void insert(BStarTreeNode **root, int key, int value) {
    if (*root == NULL) {
        BStarTreeNode *leaf = create_node(1);
        leaf->keys[0] = key;
        leaf->values[0] = value;
        leaf->num_keys = 1;
        *root = leaf;
        return;
    }
    BStarTreeNode *leaf = find_leaf(*root, key);
    insert_into_leaf(leaf, key, value);
    if (leaf->num_keys > MAX_KEYS)
        handle_overflow(root, leaf);
}

/* B* Tree 검색: 리프 노드에서 선형 탐색 */
int bstar_tree_search(BStarTreeNode *root, int key, bool *found) {
    if (root == NULL) {
        *found = false;
        return -1;
    }
    BStarTreeNode *leaf = find_leaf(root, key);
    for (int i = 0; i < leaf->num_keys; i++) {
        if (leaf->keys[i] == key) {
            *found = true;
            return leaf->values[i];
        }
    }
    *found = false;
    return -1;
}

/*
 * 노드 언더플로우 처리: 삭제 후 노드의 키 개수가 최소 채움 이하가 되면,
 * 인접 형제 노드와의 재분배 또는 병합을 수행합니다.
 */
void handle_underflow(BStarTreeNode **root, BStarTreeNode *node) {
    if (node->parent == NULL)
        return; // 루트 노드인 경우
    if (node->num_keys >= MIN_KEYS)
        return;
    
    BStarTreeNode *parent = node->parent;
    int index_in_parent = 0;
    for (int i = 0; i <= parent->num_keys; i++) {
        if (parent->children[i] == node) {
            index_in_parent = i;
            break;
        }
    }
    BStarTreeNode *left_sibling = (index_in_parent > 0) ? parent->children[index_in_parent - 1] : NULL;
    BStarTreeNode *right_sibling = (index_in_parent < parent->num_keys) ? parent->children[index_in_parent + 1] : NULL;
    
    // 왼쪽 형제에서 빌리기
    if (left_sibling && left_sibling->num_keys > MIN_KEYS) {
        // 왼쪽 형제의 마지막 키를 빌려와서 현재 노드 앞에 삽입
        for (int i = node->num_keys; i > 0; i--) {
            node->keys[i] = node->keys[i-1];
            if (node->is_leaf)
                node->values[i] = node->values[i-1];
        }
        node->keys[0] = left_sibling->keys[left_sibling->num_keys - 1];
        if (node->is_leaf)
            node->values[0] = left_sibling->values[left_sibling->num_keys - 1];
        left_sibling->num_keys--;
        node->num_keys++;
        parent->keys[index_in_parent - 1] = node->keys[0];
        return;
    }
    // 오른쪽 형제에서 빌리기
    if (right_sibling && right_sibling->num_keys > MIN_KEYS) {
        node->keys[node->num_keys] = right_sibling->keys[0];
        if (node->is_leaf)
            node->values[node->num_keys] = right_sibling->values[0];
        node->num_keys++;
        for (int i = 0; i < right_sibling->num_keys - 1; i++) {
            right_sibling->keys[i] = right_sibling->keys[i+1];
            if (right_sibling->is_leaf)
                right_sibling->values[i] = right_sibling->values[i+1];
        }
        right_sibling->num_keys--;
        parent->keys[index_in_parent] = right_sibling->keys[0];
        return;
    }
    // 재분배가 불가능하면 병합 수행
    if (left_sibling) {
        // 왼쪽 형제와 병합: node의 키를 왼쪽 형제로 복사
        for (int i = 0; i < node->num_keys; i++) {
            left_sibling->keys[left_sibling->num_keys + i] = node->keys[i];
            if (node->is_leaf)
                left_sibling->values[left_sibling->num_keys + i] = node->values[i];
        }
        left_sibling->num_keys += node->num_keys;
        // 부모에서 node 제거
        for (int i = index_in_parent; i < parent->num_keys; i++) {
            parent->keys[i-1] = parent->keys[i];
            parent->children[i] = parent->children[i+1];
        }
        parent->num_keys--;
        free(node);
    } else if (right_sibling) {
        // 오른쪽 형제와 병합: 오른쪽 형제의 키를 node에 복사
        for (int i = 0; i < right_sibling->num_keys; i++) {
            node->keys[node->num_keys + i] = right_sibling->keys[i];
            if (node->is_leaf)
                node->values[node->num_keys + i] = right_sibling->values[i];
        }
        node->num_keys += right_sibling->num_keys;
        for (int i = index_in_parent + 1; i < parent->num_keys; i++) {
            parent->keys[i-1] = parent->keys[i];
            parent->children[i] = parent->children[i+1];
        }
        parent->num_keys--;
        free(right_sibling);
    }
    // 재귀적으로 부모의 언더플로우 처리
    handle_underflow(root, parent);
    // 만약 부모가 비게 되면, 현재 노드가 새 루트가 됨
    if (parent->num_keys == 0) {
        *root = node;
        node->parent = NULL;
        free(parent);
    }
}

/* B* Tree에서 키 삭제 */
void delete_key(BStarTreeNode **root, int key) {
    if (*root == NULL)
        return;
    BStarTreeNode *leaf = find_leaf(*root, key);
    int pos = -1;
    for (int i = 0; i < leaf->num_keys; i++) {
        if (leaf->keys[i] == key) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        printf("Key %d not found.\n", key);
        return;
    }
    // 키 삭제 후 오른쪽으로 shift
    for (int i = pos; i < leaf->num_keys - 1; i++) {
        leaf->keys[i] = leaf->keys[i+1];
        if (leaf->is_leaf)
            leaf->values[i] = leaf->values[i+1];
    }
    leaf->num_keys--;
    // 루트가 아니면서 최소 채움 이하이면 언더플로우 처리
    if (leaf->parent != NULL && leaf->num_keys < MIN_KEYS)
        handle_underflow(root, leaf);
    // 만약 루트가 비게 되면 트리 비움
    if (leaf->parent == NULL && leaf->num_keys == 0) {
        free(leaf);
        *root = NULL;
    }
}

/* 레벨 순회: 각 레벨별로 노드의 키들을 출력 */
void print_level_order(BStarTreeNode *root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    BStarTreeNode **queue = malloc(sizeof(BStarTreeNode*) * 100);
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        int level_count = rear - front;
        while (level_count > 0) {
            BStarTreeNode *node = queue[front++];
            printf("[");
            for (int i = 0; i < node->num_keys; i++) {
                printf("%d ", node->keys[i]);
            }
            printf("] ");
            if (!node->is_leaf) {
                for (int i = 0; i <= node->num_keys; i++) {
                    if (node->children[i])
                        queue[rear++] = node->children[i];
                }
            }
            level_count--;
        }
        printf("\n");
    }
    free(queue);
}

/* --- main 함수 --- */
int main(void) {
    BStarTreeNode *root = NULL;
    
    printf("=== B* Tree Demo ===\n\n");
    
    // 삽입 테스트
    int keys_to_insert[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys_to_insert) / sizeof(keys_to_insert[0]);
    for (int i = 0; i < n; i++) {
        insert(&root, keys_to_insert[i], keys_to_insert[i] * 10);
        printf("Inserted key %d with value %d\n", keys_to_insert[i], keys_to_insert[i]*10);
    }
    
    printf("\nLevel Order Traversal after insertion:\n");
    print_level_order(root);
    
    // 검색 테스트
    bool found;
    int search_key = 12;
    int val = bstar_tree_search(root, search_key, &found);
    if (found)
        printf("\nSearch: Key %d found with value %d\n", search_key, val);
    else
        printf("\nSearch: Key %d not found\n", search_key);
    
    // 삭제 테스트
    int keys_to_delete[] = {6, 7, 10};
    int m = sizeof(keys_to_delete) / sizeof(keys_to_delete[0]);
    for (int i = 0; i < m; i++) {
        printf("\nDeleting key %d\n", keys_to_delete[i]);
        delete_key(&root, keys_to_delete[i]);
        print_level_order(root);
    }
    
    // 최종 트리 출력
    printf("\nFinal B* Tree (Level Order Traversal):\n");
    print_level_order(root);
    
    // 메모리 해제 (간단히, 재귀적 해제 생략)
    
    return 0;
}
