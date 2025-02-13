/*
 * Fractal Tree Demo
 *
 * 이 예제는 Fractal Tree 자료구조의 기본 동작을 시뮬레이션합니다.
 * Fractal Tree는 각 내부 노드에 버퍼를 두어 다수의 삽입(및 업데이트, 삭제) 연산을 배치 처리하고,
 * 버퍼가 가득 차면 하위 노드로 플러시하여 디스크 I/O를 최소화하는 구조입니다.
 *
 * 주요 기능:
 *  - 삽입 (Insertion): 각 노드의 버퍼에 연산을 기록한 후, 버퍼가 가득 차면 하위 노드로 플러시합니다.
 *  - 플러시 (Flush): 버퍼에 있는 연산을 해당 노드에 반영하여, 리프 노드에서는 정렬된 상태로 데이터를 저장합니다.
 *  - 노드 분할 (Split): 리프 노드의 키 수가 최대치를 초과하면, 노드를 분할하여 부모에 승격시킵니다.
 *  - 검색 (Search): 전체 버퍼를 플러시한 후, 리프 노드에서 키를 검색합니다.
 *
 * 주의: 이 코드는 Fractal Tree의 기본 개념을 단순화하여 시뮬레이션한 예제입니다.
 * 실제 구현에서는 버퍼 재배치, 내부 노드 분할, 삭제 연산 등 더 복잡한 로직이 필요합니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ORDER 4                // 최대 자식 수 (내부 노드)
#define MAX_KEYS (ORDER - 1)   // 노드당 최대 키 개수 (여기서는 3)
#define BUFFER_CAPACITY 4      // 각 노드의 버퍼 용량

typedef struct {
    int key;
    int value;
} Operation;

typedef struct FTreeNode {
    int is_leaf;                      // 1이면 리프, 0이면 내부 노드
    int num_keys;                     // 현재 저장된 키의 수
    int keys[MAX_KEYS];               // 저장된 키들
    int values[MAX_KEYS];             // 리프 노드일 때 값들
    struct FTreeNode *children[ORDER]; // 내부 노드일 때 자식 포인터들
    int num_buffer;                   // 현재 버퍼에 쌓인 연산 수
    Operation buffer[BUFFER_CAPACITY]; // 버퍼: 배치 삽입 연산 저장
    struct FTreeNode *parent;         // 부모 노드 포인터
} FTreeNode;

/* 함수 선언 */
FTreeNode* create_ftree_node(int is_leaf);
void flush_buffer(FTreeNode *node, FTreeNode **root);
void flush_all(FTreeNode *node, FTreeNode **root);
void split_leaf(FTreeNode **root, FTreeNode *leaf);
void ftree_insert(FTreeNode **root, int key, int value);
int ftree_search(FTreeNode *root, int key, bool *found);
void ftree_print_level_order(FTreeNode *root);

/* 새 Fractal Tree 노드 생성 */
FTreeNode* create_ftree_node(int is_leaf) {
    FTreeNode *node = (FTreeNode*)malloc(sizeof(FTreeNode));
    if (node == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    node->num_buffer = 0;
    node->parent = NULL;
    for (int i = 0; i < ORDER; i++)
        node->children[i] = NULL;
    return node;
}

/*
 * 버퍼 플러시 함수
 * - 리프 노드인 경우: 버퍼에 저장된 각 연산을 리프의 키/값 배열에 정렬 삽입하고,
 *   키 수가 최대치를 초과하면 split_leaf()를 호출하여 노드 분할을 처리합니다.
 * - 내부 노드인 경우: 버퍼의 각 연산을 적절한 자식 노드의 버퍼에 전달합니다.
 */
void flush_buffer(FTreeNode *node, FTreeNode **root) {
    if (node->num_buffer == 0)
        return;
    
    if (node->is_leaf) {
        // 버퍼에 있는 연산을 리프에 적용 (정렬 삽입)
        for (int i = 0; i < node->num_buffer; i++) {
            int op_key = node->buffer[i].key;
            int op_value = node->buffer[i].value;
            // 정렬 삽입: 뒤에서부터 비교하며 이동
            int j = node->num_keys - 1;
            while (j >= 0 && node->keys[j] > op_key) {
                node->keys[j+1] = node->keys[j];
                node->values[j+1] = node->values[j];
                j--;
            }
            node->keys[j+1] = op_key;
            node->values[j+1] = op_value;
            node->num_keys++;
            // 만약 노드의 키 수가 최대치를 초과하면 분할 수행
            if (node->num_keys > MAX_KEYS) {
                split_leaf(root, node);
                // 분할 후, 현재 노드는 변경될 수 있으므로 break
                break;
            }
        }
        // 버퍼 초기화
        node->num_buffer = 0;
    } else {
        // 내부 노드: 각 연산을 자식 노드의 버퍼로 전달
        for (int i = 0; i < node->num_buffer; i++) {
            int op_key = node->buffer[i].key;
            int op_value = node->buffer[i].value;
            // 자식 선택: node->keys를 기준으로 적절한 자식 선택
            int child_index = 0;
            while (child_index < node->num_keys && op_key >= node->keys[child_index])
                child_index++;
            FTreeNode *child = node->children[child_index];
            // 자식의 버퍼에 연산 추가 (버퍼가 가득 차면 재귀적으로 플러시)
            if (child->num_buffer < BUFFER_CAPACITY) {
                child->buffer[child->num_buffer].key = op_key;
                child->buffer[child->num_buffer].value = op_value;
                child->num_buffer++;
            } else {
                flush_buffer(child, root);
                child->buffer[child->num_buffer].key = op_key;
                child->buffer[child->num_buffer].value = op_value;
                child->num_buffer++;
            }
        }
        // 버퍼 초기화
        node->num_buffer = 0;
    }
}

/*
 * 전체 버퍼 플러시: 재귀적으로 모든 노드의 버퍼를 플러시하여
 * 최신 상태의 키/값들이 각 리프에 반영되도록 합니다.
 */
void flush_all(FTreeNode *node, FTreeNode **root) {
    if (node == NULL)
        return;
    flush_buffer(node, root);
    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; i++) {
            flush_all(node->children[i], root);
        }
    }
}

/*
 * 리프 노드 분할
 * - 리프의 키 수가 MAX_KEYS를 초과하면, 리프를 두 개로 분할하여 부모에 승격합니다.
 */
void split_leaf(FTreeNode **root, FTreeNode *leaf) {
    // 새 리프 생성
    FTreeNode *new_leaf = create_ftree_node(1);
    new_leaf->parent = leaf->parent;
    
    int total = leaf->num_keys;
    int split_index = total / 2; // 절반으로 분할
    
    new_leaf->num_keys = total - split_index;
    for (int i = 0; i < new_leaf->num_keys; i++) {
        new_leaf->keys[i] = leaf->keys[split_index + i];
        new_leaf->values[i] = leaf->values[split_index + i];
    }
    leaf->num_keys = split_index;
    
    // 부모가 없는 경우, 새 루트를 생성합니다.
    if (leaf->parent == NULL) {
        FTreeNode *new_root = create_ftree_node(0);
        new_root->keys[0] = new_leaf->keys[0];  // 구분 키
        new_root->children[0] = leaf;
        new_root->children[1] = new_leaf;
        new_root->num_keys = 1;
        leaf->parent = new_root;
        new_leaf->parent = new_root;
        *root = new_root;
    } else {
        // 부모에 new_leaf를 삽입합니다.
        FTreeNode *parent = leaf->parent;
        // 부모의 children 배열에서 leaf의 위치 찾기
        int pos = 0;
        while (pos <= parent->num_keys && parent->children[pos] != leaf)
            pos++;
        // 부모의 children과 keys를 뒤로 이동하여 공간 확보
        for (int i = parent->num_keys; i > pos; i--) {
            parent->children[i+1] = parent->children[i];
            parent->keys[i] = parent->keys[i-1];
        }
        parent->children[pos+1] = new_leaf;
        parent->keys[pos] = new_leaf->keys[0];
        parent->num_keys++;
        // (내부 노드 분할은 이 예제에서 단순화하여 처리합니다.)
    }
}

/*
 * Fractal Tree 삽입
 * - 새로운 삽입 연산을 루트의 버퍼에 추가한 후, 버퍼가 가득 차면 플러시합니다.
 */
void ftree_insert(FTreeNode **root, int key, int value) {
    if (*root == NULL) {
        *root = create_ftree_node(1);
    }
    FTreeNode *node = *root;
    // 루트의 버퍼에 연산 추가
    node->buffer[node->num_buffer].key = key;
    node->buffer[node->num_buffer].value = value;
    node->num_buffer++;
    
    // 버퍼가 가득 차면 플러시
    if (node->num_buffer >= BUFFER_CAPACITY) {
        flush_buffer(node, root);
        // 만약 루트가 리프이고 키 수가 초과되었다면 분할 처리
        if (node->is_leaf && node->num_keys > MAX_KEYS) {
            split_leaf(root, node);
        }
    }
}

/*
 * Fractal Tree 검색
 * - 검색 전에 flush_all()을 호출하여 모든 버퍼를 플러시한 후, 리프 노드에서 이진(또는 선형) 검색합니다.
 */
int ftree_search(FTreeNode *root, int key, bool *found) {
    if (root == NULL) {
        *found = false;
        return -1;
    }
    flush_all(root, &root);
    FTreeNode *node = root;
    while (!node->is_leaf) {
        int i = 0;
        while (i < node->num_keys && key >= node->keys[i])
            i++;
        node = node->children[i];
    }
    // 리프 노드에서 선형 검색
    for (int i = 0; i < node->num_keys; i++) {
        if (node->keys[i] == key) {
            *found = true;
            return node->values[i];
        }
    }
    *found = false;
    return -1;
}

/*
 * 레벨 순회 출력
 * - 큐를 사용하여 각 레벨의 노드 키들을 출력합니다.
 */
void ftree_print_level_order(FTreeNode *root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    FTreeNode **queue = malloc(sizeof(FTreeNode*) * 100);
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        int level_count = rear - front;
        while (level_count > 0) {
            FTreeNode *node = queue[front++];
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
    FTreeNode *root = NULL;
    
    printf("=== Fractal Tree Demo ===\n\n");
    
    // 삽입 테스트
    int keys_to_insert[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys_to_insert) / sizeof(keys_to_insert[0]);
    for (int i = 0; i < n; i++) {
        ftree_insert(&root, keys_to_insert[i], keys_to_insert[i] * 10);
        printf("Inserted key %d with value %d\n", keys_to_insert[i], keys_to_insert[i] * 10);
    }
    
    // 플러시: 모든 버퍼를 최종 반영
    flush_all(root, &root);
    
    printf("\nLevel Order Traversal after insertions:\n");
    ftree_print_level_order(root);
    
    // 검색 테스트
    bool found = false;
    int search_key = 12;
    int val = ftree_search(root, search_key, &found);
    if (found)
        printf("\nSearch: Key %d found with value %d\n", search_key, val);
    else
        printf("\nSearch: Key %d not found\n", search_key);
    
    // 본 예제에서는 삭제 연산은 구현하지 않습니다.
    
    return 0;
}