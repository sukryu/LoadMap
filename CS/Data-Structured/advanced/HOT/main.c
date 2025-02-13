/*
 * HOT Trie Demo
 *
 * 이 예제는 HOT(Height-Optimized Trie) 자료구조의 기본 동작을 시뮬레이션합니다.
 * HOT Trie는 키를 다중 비트(여기서는 4비트 단위)로 분할하여 트리의 높이를 최소화하고,
 * 검색, 삽입, 삭제 연산을 빠르게 수행할 수 있도록 설계된 트라이 구조입니다.
 *
 * 주요 기능:
 *  - 삽입 (Insertion): 32비트 정수 키를 4비트씩 분할하여, 
 *    경로를 따라 노드를 생성하고 리프 노드에서 키와 연관된 값을 저장합니다.
 *  - 검색 (Search): 키의 4비트 청크를 사용하여 루트부터 리프까지 탐색한 후,
 *    해당 키의 값을 반환합니다.
 *  - 삭제 (Deletion): 키에 해당하는 리프 노드의 종료 표시를 해제하여 삭제를 처리합니다.
 *  - 레벨 순회 (Level Order Traversal): 큐를 이용하여 트리의 모든 노드를 레벨별로 출력합니다.
 *
 * 주의: 이 예제는 HOT Trie의 기본 개념을 단순화하여 구현한 것으로,
 * 실제 HOT Trie는 경로 압축 및 다양한 최적화 기법을 포함할 수 있습니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BRANCH 16                   // 각 노드는 4비트(0~15)의 분기를 가짐
#define BITS_PER_LEVEL 4            // 한 레벨당 4비트씩 처리
#define MAX_LEVELS (32 / BITS_PER_LEVEL)  // 32비트 키를 처리하기 위한 최대 레벨 (8)

typedef struct HOTNode {
    bool is_end;                    // 이 노드가 키의 끝이면 true, 아니면 false
    int value;                      // 키에 연관된 값 (리프 노드에서만 의미 있음)
    struct HOTNode *children[BRANCH];  // 0~15까지의 자식 포인터
} HOTNode;

/* 새 HOT Trie 노드 생성 */
HOTNode* hot_create_node() {
    HOTNode *node = (HOTNode*) malloc(sizeof(HOTNode));
    if (!node) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    node->is_end = false;
    node->value = 0;
    for (int i = 0; i < BRANCH; i++) {
        node->children[i] = NULL;
    }
    return node;
}

/* HOT Trie 삽입:
 * 주어진 32비트 정수 key를 4비트 청크로 분할하여 경로를 따라 노드를 생성하고,
 * 리프 노드에서 is_end를 true로 설정한 후 value를 저장합니다.
 */
void hot_insert(HOTNode **root, int key, int value) {
    if (*root == NULL) {
        *root = hot_create_node();
    }
    HOTNode *node = *root;
    for (int level = 0; level < MAX_LEVELS; level++) {
        int shift = BITS_PER_LEVEL * (MAX_LEVELS - level - 1);
        int index = (key >> shift) & 0xF;  // 해당 레벨의 4비트 추출
        if (node->children[index] == NULL) {
            node->children[index] = hot_create_node();
        }
        node = node->children[index];
    }
    node->is_end = true;
    node->value = value;
}

/* HOT Trie 검색:
 * key를 4비트씩 분할하여 리프 노드까지 탐색한 후,
 * 해당 노드가 종료 노드(is_end == true)면 value를 반환합니다.
 */
int hot_search(HOTNode *root, int key, bool *found) {
    if (root == NULL) {
        *found = false;
        return -1;
    }
    HOTNode *node = root;
    for (int level = 0; level < MAX_LEVELS; level++) {
        int shift = BITS_PER_LEVEL * (MAX_LEVELS - level - 1);
        int index = (key >> shift) & 0xF;
        if (node->children[index] == NULL) {
            *found = false;
            return -1;
        }
        node = node->children[index];
    }
    if (node->is_end) {
        *found = true;
        return node->value;
    } else {
        *found = false;
        return -1;
    }
}

/* HOT Trie 삭제:
 * key에 해당하는 리프 노드의 is_end를 false로 설정하여 삭제합니다.
 */
void hot_delete(HOTNode *root, int key) {
    if (root == NULL)
        return;
    HOTNode *node = root;
    for (int level = 0; level < MAX_LEVELS; level++) {
        int shift = BITS_PER_LEVEL * (MAX_LEVELS - level - 1);
        int index = (key >> shift) & 0xF;
        if (node->children[index] == NULL) {
            return;  // key 존재하지 않음
        }
        node = node->children[index];
    }
    if (node->is_end) {
        node->is_end = false;
        printf("Deleted key %d\n", key);
    }
}

/* 레벨 순회 출력:
 * 큐를 사용하여 HOT Trie의 모든 노드를 레벨별로 출력합니다.
 * 각 노드는 종료 노드이면 "[T:value]"로, 아니면 "[ ]"로 표시합니다.
 */
void hot_print_level_order(HOTNode *root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    HOTNode **queue = malloc(sizeof(HOTNode*) * 1024);
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        int level_count = rear - front;
        while (level_count > 0) {
            HOTNode *node = queue[front++];
            if (node->is_end)
                printf("[T:%d] ", node->value);
            else
                printf("[ ] ");
            for (int i = 0; i < BRANCH; i++) {
                if (node->children[i] != NULL) {
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
    HOTNode *root = NULL;
    
    printf("=== HOT Trie Demo ===\n\n");
    
    // 삽입 테스트
    int keys_to_insert[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys_to_insert) / sizeof(keys_to_insert[0]);
    for (int i = 0; i < n; i++) {
        hot_insert(&root, keys_to_insert[i], keys_to_insert[i] * 10);
        printf("Inserted key %d with value %d\n", keys_to_insert[i], keys_to_insert[i] * 10);
    }
    
    printf("\nLevel Order Traversal after insertions:\n");
    hot_print_level_order(root);
    
    // 검색 테스트
    bool found = false;
    int search_key = 12;
    int val = hot_search(root, search_key, &found);
    if (found)
        printf("\nSearch: Key %d found with value %d\n", search_key, val);
    else
        printf("\nSearch: Key %d not found\n", search_key);
    
    // 삭제 테스트
    int keys_to_delete[] = {6, 7, 10};
    int m = sizeof(keys_to_delete) / sizeof(keys_to_delete[0]);
    for (int i = 0; i < m; i++) {
        printf("\nDeleting key %d\n", keys_to_delete[i]);
        hot_delete(root, keys_to_delete[i]);
        hot_print_level_order(root);
    }
    
    // 최종 트리 출력
    printf("\nFinal HOT Trie (Level Order Traversal):\n");
    hot_print_level_order(root);
    
    // 메모리 해제는 재귀적 노드 해제 함수를 추가하여 처리할 수 있습니다.
    
    return 0;
}