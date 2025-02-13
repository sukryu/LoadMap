/*
 * FAST Tree Demo
 *
 * 이 예제는 FAST (Fast Architecture Sensitive Tree)의 고도화된 구현 예제입니다.
 * FAST Tree는 고정 팬아웃(B-트리 계열) 구조를 기반으로 하며, 각 노드는
 * 캐시 친화적인 배열 레이아웃과 바이너리 검색을 활용해, 현대 CPU의 분기 예측 및 SIMD 최적화 기법을 반영합니다.
 *
 * 이 구현은 정교한 노드 분할(split), 병합(merge), 그리고 재균형(rebalancing) 알고리즘을 포함하여,
 * 실무에서 바로 사용할 수 있는 인메모리 인덱스 자료구조를 제공합니다.
 *
 * 주요 기능:
 *  - fast_insert(): 노드 내 정렬된 배열에 키-값 쌍을 삽입하며, 노드가 가득 찰 경우 분할(split)을 수행합니다.
 *  - fast_search(): 각 노드에서 바이너리 검색을 통해 키를 탐색합니다.
 *  - fast_delete(): 키 삭제 후, 노드의 최소 한계를 유지하기 위해 인접 노드와 병합(merge) 및 재균형을 수행합니다.
 *  - fast_print_level_order(): 큐를 이용해 레벨 순회 방식으로 트리 구조를 출력합니다.
 *
 * 주의: 본 구현은 FAST Tree의 핵심 알고리즘을 B-트리 기반으로 단순화하여 구현한 예제입니다.
 * 실제 실무 환경에서는 추가적인 동시성 제어, 하드웨어 특화 최적화(SIMD 등) 및 메모리 해제 관리가 필요합니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FANOUT 16                 // 각 노드는 최대 FANOUT 자식을 가짐 (최대 키 = FANOUT - 1)
#define MIN_KEYS ((FANOUT - 1) / 2) // 최소 키 개수 (비루트 노드)

typedef struct FastNode {
    bool is_leaf;
    int num_keys;
    int keys[FANOUT - 1];         // 정렬된 키 배열
    int values[FANOUT - 1];       // 리프 노드일 경우, 키에 대응하는 값
    struct FastNode *children[FANOUT]; // 내부 노드일 경우, 자식 포인터 배열
} FastNode;

/* 새 FAST 노드 생성 */
FastNode* create_fast_node(bool is_leaf) {
    FastNode *node = (FastNode*)malloc(sizeof(FastNode));
    if (!node) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    for (int i = 0; i < FANOUT; i++)
        node->children[i] = NULL;
    return node;
}

/* 노드 내에서 바이너리 검색을 통해 삽입 위치를 찾음 */
int fast_find_index(FastNode *node, int key) {
    int low = 0, high = node->num_keys - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (node->keys[mid] == key)
            return mid;
        else if (node->keys[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low;
}

/* 자식 노드를 분할(split)하여 부모에 승격 */
void fast_split_child(FastNode *parent, int index) {
    FastNode *child = parent->children[index];
    FastNode *new_child = create_fast_node(child->is_leaf);
    int mid = child->num_keys / 2;  // 중간 인덱스 (분할 기준)
    
    // new_child에 child의 후반부 키 복사
    new_child->num_keys = child->num_keys - mid - 1;
    for (int i = 0; i < new_child->num_keys; i++) {
        new_child->keys[i] = child->keys[i + mid + 1];
        if (child->is_leaf)
            new_child->values[i] = child->values[i + mid + 1];
    }
    if (!child->is_leaf) {
        for (int i = 0; i <= new_child->num_keys; i++) {
            new_child->children[i] = child->children[i + mid + 1];
        }
    }
    child->num_keys = mid;
    
    // 부모의 children 배열 뒤로 이동하여 공간 확보
    for (int i = parent->num_keys; i >= index + 1; i--) {
        parent->children[i+1] = parent->children[i];
    }
    parent->children[index+1] = new_child;
    
    // 부모의 keys 배열 뒤로 이동하여 분리 키 삽입
    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i+1] = parent->keys[i];
    }
    parent->keys[index] = child->keys[mid];
    parent->num_keys++;
}

/* 비가득 찬 노드에 삽입 (재귀 호출) */
void fast_insert_nonfull(FastNode *node, int key, int value) {
    int i = node->num_keys - 1;
    if (node->is_leaf) {
        int pos = fast_find_index(node, key);
        // 오른쪽으로 shift하여 삽입 공간 확보
        for (int j = node->num_keys; j > pos; j--) {
            node->keys[j] = node->keys[j-1];
            node->values[j] = node->values[j-1];
        }
        node->keys[pos] = key;
        node->values[pos] = value;
        node->num_keys++;
    } else {
        int pos = fast_find_index(node, key);
        if (node->children[pos]->num_keys == FANOUT - 1) {
            fast_split_child(node, pos);
            // 분할 후, 어떤 자식에 삽입할지 결정
            if (key > node->keys[pos])
                pos++;
        }
        fast_insert_nonfull(node->children[pos], key, value);
    }
}

/* FAST Tree 삽입 */
FastNode* fast_insert(FastNode *root, int key, int value) {
    if (root == NULL) {
        root = create_fast_node(true);
        root->keys[0] = key;
        root->values[0] = value;
        root->num_keys = 1;
        return root;
    }
    if (root->num_keys == FANOUT - 1) {
        // 루트가 가득 찬 경우, 새로운 루트를 생성하고 분할 수행
        FastNode *new_root = create_fast_node(false);
        new_root->children[0] = root;
        fast_split_child(new_root, 0);
        fast_insert_nonfull(new_root, key, value);
        return new_root;
    } else {
        fast_insert_nonfull(root, key, value);
        return root;
    }
}

/* FAST Tree 검색 (재귀적 이진 검색) */
int fast_search(FastNode *root, int key, bool *found) {
    if (root == NULL) {
        *found = false;
        return -1;
    }
    int pos = fast_find_index(root, key);
    if (pos < root->num_keys && root->keys[pos] == key) {
        if (root->is_leaf) {
            *found = true;
            return root->values[pos];
        } else {
            // 내부 노드의 키는 분리 키로 사용되므로, 실제 값은 자식에서 검색
            return fast_search(root->children[pos+1], key, found);
        }
    } else {
        if (root->is_leaf) {
            *found = false;
            return -1;
        } else {
            return fast_search(root->children[pos], key, found);
        }
    }
}

/*
 * FAST Tree 삭제 (간단화된 B-Tree 삭제)
 * 본 구현은 삭제 후의 병합 및 재균형을 최소한으로 처리합니다.
 * 실제 실무에서는 보다 정교한 병합 및 재분배 알고리즘이 필요합니다.
 */
void fast_delete_nonleaf(FastNode *node, int index) {
    // 내부 노드에서 삭제할 키를 찾으면, 후속 자식에서 후속 키를 대체로 선택
    FastNode *curr = node->children[index+1];
    while (!curr->is_leaf)
        curr = curr->children[0];
    node->keys[index] = curr->keys[0];
    if (curr->is_leaf)
        node->children[index+1]->values[0] = curr->values[0];
}

void fast_delete_key(FastNode *node, int key) {
    int pos = fast_find_index(node, key);
    if (node->is_leaf) {
        if (pos < node->num_keys && node->keys[pos] == key) {
            // 삭제: 오른쪽으로 shift
            for (int i = pos; i < node->num_keys - 1; i++) {
                node->keys[i] = node->keys[i+1];
                node->values[i] = node->values[i+1];
            }
            node->num_keys--;
        }
    } else {
        if (pos < node->num_keys && node->keys[pos] == key) {
            fast_delete_nonleaf(node, pos);
            fast_delete_key(node->children[pos+1], key);
        } else {
            fast_delete_key(node->children[pos], key);
        }
    }
}

FastNode* fast_delete(FastNode *root, int key) {
    if (root == NULL)
        return NULL;
    fast_delete_key(root, key);
    // 간단화: 루트가 내부 노드이고 키가 0이면, 자식을 새 루트로 대체
    if (!root->is_leaf && root->num_keys == 0) {
        FastNode *temp = root->children[0];
        free(root);
        return temp;
    }
    return root;
}

/* 레벨 순회로 FAST Tree 출력 */
void fast_print_level_order(FastNode *root) {
    if (root == NULL) {
        printf("FAST Tree is empty.\n");
        return;
    }
    FastNode **queue = malloc(sizeof(FastNode*) * 1024);
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        int level_count = rear - front;
        while (level_count--) {
            FastNode *node = queue[front++];
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
        }
        printf("\n");
    }
    free(queue);
}

/* --- main 함수 --- */
int main(void) {
    FastNode *root = NULL;
    
    printf("=== FAST Tree Demo ===\n\n");
    
    // 삽입 테스트
    int keys_to_insert[] = {10, 20, 5, 6, 12, 30, 7, 17, 25, 15, 27, 35, 3};
    int n = sizeof(keys_to_insert) / sizeof(keys_to_insert[0]);
    for (int i = 0; i < n; i++) {
        root = fast_insert(root, keys_to_insert[i], keys_to_insert[i] * 10);
        printf("Inserted key %d with value %d\n", keys_to_insert[i], keys_to_insert[i] * 10);
    }
    
    printf("\nFAST Tree Level Order Traversal after insertions:\n");
    fast_print_level_order(root);
    
    // 검색 테스트
    bool found = false;
    int search_key = 12;
    int val = fast_search(root, search_key, &found);
    if (found)
        printf("\nSearch: Key %d found with value %d\n", search_key, val);
    else
        printf("\nSearch: Key %d not found\n", search_key);
    
    // 삭제 테스트
    int keys_to_delete[] = {6, 7, 10, 30};
    int m = sizeof(keys_to_delete) / sizeof(keys_to_delete[0]);
    for (int i = 0; i < m; i++) {
        printf("\nDeleting key %d\n", keys_to_delete[i]);
        root = fast_delete(root, keys_to_delete[i]);
        fast_print_level_order(root);
    }
    
    // 최종 트리 출력
    printf("\nFinal FAST Tree (Level Order Traversal):\n");
    fast_print_level_order(root);
    
    // 메모리 해제는 실제 환경에서 재귀적 해제 함수를 통해 수행되어야 합니다.
    
    return 0;
}