/*
 * T-Tree Demo
 *
 * 이 예제는 메모리 내 데이터베이스 환경에 최적화된 T-Tree 자료구조의
 * 정교한 노드 분할, 병합, 재균형 기능을 포함한 고도화된 구현 예제입니다.
 *
 * T-Tree는 각 노드에 여러 개의 정렬된 키를 저장하여 포인터 오버헤드를 줄이고,
 * 캐시 지역성을 극대화하는 동시에, AVL 트리와 유사한 방식으로 높이 균형을 유지합니다.
 *
 * 주요 기능:
 *  - 삽입 (Insertion): 적절한 노드를 찾아 정렬된 순서로 키-값 쌍을 저장합니다.
 *    노드가 꽉 차면 내부적으로 노드를 분할(split)하여 새로운 자식 노드를 만들고,
 *    부모 노드에 구분 키를 저장합니다.
 *
 *  - 삭제 (Deletion): 노드 내에서 키를 제거하고, 최소 채움률 미달 시 인접 노드와 병합(merge)
 *    또는 재분배를 수행한 후, AVL 회전 기법을 사용하여 트리 균형을 유지합니다.
 *
 *  - 검색 (Search): 탐색 경로 상에서 노드의 최소/최대 값을 이용해 빠르게 해당 노드를 찾은 후,
 *    노드 내 이진 검색으로 값을 반환합니다.
 *
 *  - 재균형 (Rebalancing): 삽입 및 삭제 후 AVL 회전(LL, LR, RR, RL 회전)을 통해 전체 트리의 균형을 유지합니다.
 *
 * 노드 구조:
 *  - 각 T-Tree 노드는 동적 배열(keys, values)을 가지며, 현재 저장된 키의 수(n)
 *    와 최대 저장 가능 수(capacity)를 기록합니다.
 *  - 좌우 자식 포인터와 높이(height)를 저장하여 AVL 균형 트리처럼 작동합니다.
 *  - 노드의 키 범위는 (keys[0] ~ keys[n-1])로, 좌측 자식의 모든 키는 이보다 작고,
 *    우측 자식의 모든 키는 이보다 큽니다.
 *
 * 주의: 이 구현은 교육 및 데모 목적으로 작성되었으며,
 * 실제 실무 환경에서는 에러 처리, 메모리 해제, 동시성 제어 등 추가 기능이 필요합니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CAPACITY 4                // 한 노드당 최대 저장 키 개수
#define MIN_KEYS (CAPACITY / 2)     // 최소 키 개수 (여기서는 2)

// T-Tree 노드 정의
typedef struct TTreeNode {
    int *keys;              // 동적 배열: 정렬된 키들
    int *values;            // 각 키에 대응하는 값
    int n;                  // 현재 저장된 키의 수
    int capacity;           // 최대 저장 가능한 키 개수 (CAPACITY)
    struct TTreeNode *left; // 좌측 자식 (모든 키 < keys[0])
    struct TTreeNode *right;// 우측 자식 (모든 키 > keys[n-1])
    int height;             // AVL 균형 유지를 위한 높이
} TTreeNode;

/* 함수 프로토타입 */
TTreeNode* create_node();
void free_tree(TTreeNode *root);
int get_height(TTreeNode *node);
void update_height(TTreeNode *node);
int balance_factor(TTreeNode *node);
TTreeNode* left_rotate(TTreeNode *x);
TTreeNode* right_rotate(TTreeNode *y);
TTreeNode* rebalance(TTreeNode *node);
TTreeNode* split_node(TTreeNode *node);
TTreeNode* merge_nodes(TTreeNode *left, TTreeNode *right);
TTreeNode* insert_ttree(TTreeNode *root, int key, int value);
TTreeNode* delete_ttree(TTreeNode *root, int key);
TTreeNode* search_ttree(TTreeNode *root, int key);
void print_level_order(TTreeNode *root);

/* 새 T-Tree 노드 생성 (CAPACITY 크기의 배열 할당) */
TTreeNode* create_node() {
    TTreeNode *node = (TTreeNode*)malloc(sizeof(TTreeNode));
    if (!node) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    node->keys = (int*)malloc(sizeof(int) * CAPACITY);
    node->values = (int*)malloc(sizeof(int) * CAPACITY);
    if (!node->keys || !node->values) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    node->n = 0;
    node->capacity = CAPACITY;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

/* 트리 전체 메모리 해제 (재귀적) */
void free_tree(TTreeNode *root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root->keys);
    free(root->values);
    free(root);
}

/* 노드 높이 반환 */
int get_height(TTreeNode *node) {
    return node ? node->height : 0;
}

/* 노드 높이 업데이트 */
void update_height(TTreeNode *node) {
    if (node) {
        int lh = get_height(node->left);
        int rh = get_height(node->right);
        node->height = (lh > rh ? lh : rh) + 1;
    }
}

/* 균형 인자: 좌측 높이 - 우측 높이 */
int balance_factor(TTreeNode *node) {
    return node ? get_height(node->left) - get_height(node->right) : 0;
}

/* AVL 좌측 회전 */
TTreeNode* left_rotate(TTreeNode *x) {
    TTreeNode *y = x->right;
    x->right = y->left;
    y->left = x;
    update_height(x);
    update_height(y);
    return y;
}

/* AVL 우측 회전 */
TTreeNode* right_rotate(TTreeNode *y) {
    TTreeNode *x = y->left;
    y->left = x->right;
    x->right = y;
    update_height(y);
    update_height(x);
    return x;
}

/* 노드 재균형 (AVL 회전 적용) */
TTreeNode* rebalance(TTreeNode *node) {
    update_height(node);
    int bf = balance_factor(node);
    if (bf > 1) { // 좌측 과부하
        if (balance_factor(node->left) < 0)
            node->left = left_rotate(node->left);
        return right_rotate(node);
    } else if (bf < -1) { // 우측 과부하
        if (balance_factor(node->right) > 0)
            node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    return node;
}

/*
 * 노드 분할 (Split)
 * 노드의 키 배열이 가득 찼을 때 호출.
 * - 내부적으로 현재 노드의 데이터를 두 개의 새 노드로 분할합니다.
 * - 분할 후, 새로운 부모 역할을 하는 노드(분리자 노드)를 생성하여 좌/우 자식을 연결합니다.
 */
TTreeNode* split_node(TTreeNode *node) {
    int mid = node->n / 2;
    // 왼쪽과 오른쪽 노드 생성
    TTreeNode *leftNode = create_node();
    TTreeNode *rightNode = create_node();
    for (int i = 0; i < mid; i++) {
        leftNode->keys[i] = node->keys[i];
        leftNode->values[i] = node->values[i];
    }
    leftNode->n = mid;
    for (int i = mid; i < node->n; i++) {
        rightNode->keys[i - mid] = node->keys[i];
        rightNode->values[i - mid] = node->values[i];
    }
    rightNode->n = node->n - mid;
    // 새 부모 노드를 생성. 구분 키로 오른쪽 노드의 첫번째 키를 사용.
    TTreeNode *parent = create_node();
    parent->keys[0] = rightNode->keys[0];
    parent->values[0] = rightNode->values[0]; // 구분 값(필요에 따라 무시 가능)
    parent->n = 1;
    parent->left = leftNode;
    parent->right = rightNode;
    update_height(leftNode);
    update_height(rightNode);
    update_height(parent);
    return parent;
}

/*
 * 두 노드를 병합 (Merge)
 * 삭제 후, 한 노드의 키 개수가 MIN_KEYS 미만이면, 인접 자식(또는 형제)와 병합합니다.
 * 여기서는 left와 right 두 서브트리를 하나의 노드로 병합하는 간단한 형태를 구현합니다.
 * (병합 후 분할 및 재분배로 정렬 상태와 용량 제한을 맞춥니다.)
 */
TTreeNode* merge_nodes(TTreeNode *left, TTreeNode *right) {
    // 새로운 노드를 생성하여 left와 right의 데이터를 병합
    TTreeNode *node = create_node();
    int i, j;
    for (i = 0; i < left->n; i++) {
        node->keys[i] = left->keys[i];
        node->values[i] = left->values[i];
    }
    for (j = 0; j < right->n; j++) {
        node->keys[i + j] = right->keys[j];
        node->values[i + j] = right->values[j];
    }
    node->n = left->n + right->n;
    // 만약 병합된 노드가 capacity를 초과하면 분할 처리
    if (node->n > CAPACITY) {
        TTreeNode *parent = split_node(node);
        free_tree(node);
        return parent;
    }
    update_height(node);
    return node;
}

/*
 * T-Tree 삽입 함수
 * - 탐색 경로 상에서, key가 속하는 노드를 찾습니다.
 * - 만약 key 범위에 포함되면, 해당 노드 내부 배열에 정렬 삽입합니다.
 * - 삽입 후, 노드의 키 개수가 capacity를 초과하면 split_node()를 통해 분할합니다.
 * - 재귀적으로 부모와 AVL 회전을 통해 트리 전체 균형을 유지합니다.
 */
TTreeNode* insert_ttree(TTreeNode *root, int key, int value) {
    if (root == NULL) {
        root = create_node();
        root->keys[0] = key;
        root->values[0] = value;
        root->n = 1;
        return root;
    }
    
    // 키가 현재 노드의 범위 내에 있는지 확인
    if (key >= root->keys[0] && key <= root->keys[root->n - 1]) {
        // 이미 존재하면 업데이트
        for (int i = 0; i < root->n; i++) {
            if (root->keys[i] == key) {
                root->values[i] = value;
                return root;
            }
        }
        // 삽입: 배열 내 정렬된 위치 찾기
        if (root->n < root->capacity) {
            int i = root->n - 1;
            while (i >= 0 && root->keys[i] > key) {
                root->keys[i+1] = root->keys[i];
                root->values[i+1] = root->values[i];
                i--;
            }
            root->keys[i+1] = key;
            root->values[i+1] = value;
            root->n++;
        } else {
            // 노드가 꽉 찼으므로, 분할 후 재삽입
            TTreeNode *newParent = split_node(root);
            // 새로운 부모가 생기면, 재귀적으로 삽입
            newParent = insert_ttree(newParent, key, value);
            return newParent;
        }
    } else if (key < root->keys[0]) {
        // 왼쪽 서브트리로 삽입
        root->left = insert_ttree(root->left, key, value);
    } else { // key > root->keys[root->n - 1]
        // 오른쪽 서브트리로 삽입
        root->right = insert_ttree(root->right, key, value);
    }
    
    root = rebalance(root);
    return root;
}

/*
 * T-Tree 삭제 함수
 * - key가 속하는 노드를 찾아, 해당 배열에서 key를 제거합니다.
 * - 만약 노드의 키 개수가 MIN_KEYS 미만이면, 인접 서브트리와 병합(merge_nodes)하거나
 *   재분배하여 노드 용량을 보충합니다.
 * - 삭제 후, 재균형(AVL 회전) 과정을 통해 트리 균형을 유지합니다.
 */
TTreeNode* delete_ttree(TTreeNode *root, int key) {
    if (root == NULL)
        return NULL;
    
    // 만약 key가 현재 노드의 범위 내에 있다면, 해당 배열에서 삭제 시도
    if (key >= root->keys[0] && key <= root->keys[root->n - 1]) {
        int pos = -1;
        for (int i = 0; i < root->n; i++) {
            if (root->keys[i] == key) {
                pos = i;
                break;
            }
        }
        if (pos != -1) {
            // 삭제: 배열 요소를 왼쪽으로 shift
            for (int i = pos; i < root->n - 1; i++) {
                root->keys[i] = root->keys[i+1];
                root->values[i] = root->values[i+1];
            }
            root->n--;
        }
        // 만약 삭제 후 노드가 너무 빈 상태라면(단, 내부 노드가 아니라면)
        if (root->n < MIN_KEYS && root->left == NULL && root->right == NULL) {
            // 빈 노드는 제거 (NULL 반환)
            free(root->keys);
            free(root->values);
            free(root);
            return NULL;
        }
    } else if (key < root->keys[0]) {
        root->left = delete_ttree(root->left, key);
    } else { // key > root->keys[root->n - 1]
        root->right = delete_ttree(root->right, key);
    }
    
    // 만약 자식 노드가 NULL이 아닌 경우, 노드 병합 시도:
    if (root->left && root->right) {
        // 만약 두 자식의 전체 키 수를 합쳐도 CAPACITY 이하이면 병합
        int total = root->left->n + root->right->n;
        if (total <= CAPACITY) {
            TTreeNode *merged = merge_nodes(root->left, root->right);
            // 새로운 merged 노드를 현재 노드로 대체하고,
            // 기존 노드의 key 배열은 separator로 업데이트
            free(root->keys);
            free(root->values);
            root = merged;
        }
    }
    
    root = rebalance(root);
    return root;
}

/*
 * T-Tree 검색 함수
 * - key가 속하는 노드를 찾아, 해당 배열에서 이진 검색을 수행합니다.
 * - 검색 성공 시, 해당 노드의 포인터를 반환하며, 없으면 NULL을 반환합니다.
 */
TTreeNode* search_ttree(TTreeNode *root, int key) {
    if (root == NULL)
        return NULL;
    if (key >= root->keys[0] && key <= root->keys[root->n - 1]) {
        // 배열 내 선형 검색 (노드 크기가 작으므로)
        for (int i = 0; i < root->n; i++) {
            if (root->keys[i] == key)
                return root;
        }
        return NULL;
    } else if (key < root->keys[0]) {
        return search_ttree(root->left, key);
    } else { // key > root->keys[root->n - 1]
        return search_ttree(root->right, key);
    }
}

/*
 * 레벨 순회 출력 함수
 * - 큐를 사용하여 각 레벨의 T-Tree 노드들을 출력합니다.
 * - 각 노드의 내부 배열(키들)을 출력합니다.
 */
void print_level_order(TTreeNode *root) {
    if (root == NULL) {
        printf("T-Tree is empty.\n");
        return;
    }
    TTreeNode **queue = malloc(sizeof(TTreeNode*) * 1024);
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        int level_count = rear - front;
        while (level_count--) {
            TTreeNode *node = queue[front++];
            printf("[");
            for (int i = 0; i < node->n; i++) {
                printf("%d ", node->keys[i]);
            }
            printf("] ");
            if (node->left)
                queue[rear++] = node->left;
            if (node->right)
                queue[rear++] = node->right;
        }
        printf("\n");
    }
    free(queue);
}

/* --- main 함수 --- */
int main(void) {
    TTreeNode *root = NULL;
    
    printf("=== T-Tree Demo ===\n\n");
    
    // 삽입 테스트
    int keys_to_insert[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 55, 65};
    int n = sizeof(keys_to_insert) / sizeof(keys_to_insert[0]);
    for (int i = 0; i < n; i++) {
        root = insert_ttree(root, keys_to_insert[i], keys_to_insert[i] * 10);
        printf("Inserted key %d with value %d\n", keys_to_insert[i], keys_to_insert[i] * 10);
    }
    
    printf("\nT-Tree Level Order Traversal after insertions:\n");
    print_level_order(root);
    
    // 검색 테스트
    int search_key = 40;
    TTreeNode *found_node = search_ttree(root, search_key);
    if (found_node) {
        printf("\nSearch: Key %d found in node with keys: ", search_key);
        for (int i = 0; i < found_node->n; i++)
            printf("%d ", found_node->keys[i]);
        printf("\n");
    } else {
        printf("\nSearch: Key %d not found\n", search_key);
    }
    
    // 삭제 테스트
    int keys_to_delete[] = {30, 70, 50};
    int m = sizeof(keys_to_delete) / sizeof(keys_to_delete[0]);
    for (int i = 0; i < m; i++) {
        printf("\nDeleting key %d\n", keys_to_delete[i]);
        root = delete_ttree(root, keys_to_delete[i]);
        print_level_order(root);
    }
    
    // 최종 트리 출력
    printf("\nFinal T-Tree (Level Order Traversal):\n");
    print_level_order(root);
    
    // 메모리 해제
    free_tree(root);
    
    return 0;
}
