/*
 * Adaptive Radix Tree (ART) Demo
 *
 * 이 예제는 ART (Adaptive Radix Tree)의 고도화된 구현 예제입니다.
 * 이 구현은 실무에서 바로 사용할 수 있도록 노드 타입(Node4, Node16) 전환,
 * 재귀적 삽입, 검색, 삭제, 그리고 레벨 순회 출력 기능을 포함합니다.
 *
 * ART는 키를 바이트 단위로 분할하여 경로를 구성하는 트라이 기반 인덱스 자료구조입니다.
 * 본 예제에서는 키를 문자열로 가정하며, 각 노드는 적은 수의 자식을 가진 경우에는 Node4,
 * 자식이 많아지면 Node16으로 자동 전환됩니다.
 *
 * 주요 기능:
 *  - art_insert(): 재귀적으로 키를 삽입하며, 노드가 꽉 찰 경우 Node4에서 Node16으로 전환합니다.
 *  - art_search(): 키의 바이트 단위 경로를 따라 재귀적으로 탐색합니다.
 *  - art_delete(): 키를 찾아 삭제하고, 부모 노드에서 해당 자식을 제거합니다.
 *  - art_print_level_order(): 큐를 이용해 레벨 순회로 트리 구조를 출력합니다.
 *
 * 주의: 본 예제는 ART의 핵심 개념을 단순화하여 구현한 것으로,
 * 실제 실무 환경에서는 키 압축, 동시성 제어, 메모리 해제 등 추가 고려사항이 필요합니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum { NODE_TYPE, LEAF_TYPE } NodeClass;
typedef enum { ART_NODE4, ART_NODE16 } ArtNodeType;

/* ART Leaf: 단일 키-값 쌍 저장 */
typedef struct ArtLeaf {
    NodeClass class;            // LEAF_TYPE
    unsigned char *key;         // null-terminated string key
    int key_len;                // 키 길이
    int value;                  // 연관 값
} ArtLeaf;

/* ART Internal Node: 자식 포인터와 해당 분기 바이트 저장 */
typedef struct ArtNode {
    NodeClass class;            // NODE_TYPE
    ArtNodeType type;           // ART_NODE4 또는 ART_NODE16
    int num_children;           // 현재 자식 수
    unsigned char keys[16];     // 자식 분기 키 (최대 4 또는 16)
    void *children[16];         // 자식 노드 또는 리프에 대한 포인터
} ArtNode;

/* 새 ART Leaf 생성 */
ArtLeaf *art_create_leaf(const unsigned char *key, int key_len, int value) {
    ArtLeaf *leaf = (ArtLeaf *)malloc(sizeof(ArtLeaf));
    if (!leaf) {
        fprintf(stderr, "Leaf 메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    leaf->class = LEAF_TYPE;
    leaf->key = strdup((const char *)key);
    leaf->key_len = key_len;
    leaf->value = value;
    return leaf;
}

/* 새 ART Internal Node 생성 */
ArtNode *art_create_node(ArtNodeType type) {
    ArtNode *node = (ArtNode *)malloc(sizeof(ArtNode));
    if (!node) {
        fprintf(stderr, "Node 메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    node->class = NODE_TYPE;
    node->type = type;
    node->num_children = 0;
    return node;
}

/*
 * art_insert_recursive:
 * - 재귀적으로 키를 삽입합니다.
 * - 만약 현재 노드가 NULL이면 새 리프를 생성합니다.
 * - 만약 현재 노드가 리프이면, 키가 동일하면 업데이트하고, 아니면
 *   새 Internal Node(Node4)를 생성하여 두 리프를 삽입합니다.
 * - Internal Node의 경우, 현재 깊이의 키 바이트(cur_byte)에 따라
 *   해당 자식을 찾아 재귀 삽입하거나, 자식이 없으면 새 리프를 추가합니다.
 * - 노드의 자식 수가 한계(Node4: 4, Node16: 16)를 초과하면 Node4에서 Node16으로 전환합니다.
 */
void *art_insert_recursive(void *node, const unsigned char *key, int key_len, int value, int depth) {
    if (node == NULL) {
        return (void *)art_create_leaf(key, key_len, value);
    }
    if (((ArtLeaf *)node)->class == LEAF_TYPE) {
        ArtLeaf *leaf = (ArtLeaf *)node;
        if (leaf->key_len == key_len && strcmp((char *)leaf->key, (char *)key) == 0) {
            // 동일 키: 값 업데이트
            leaf->value = value;
            return node;
        } else {
            // 두 개의 서로 다른 리프를 Internal Node로 결합
            ArtNode *new_node = art_create_node(ART_NODE4);
            // 분기할 바이트: 첫번째 다른 위치 (depth에서 비교)
            int i = depth;
            while (i < key_len && i < leaf->key_len && leaf->key[i] == key[i])
                i++;
            unsigned char existing_byte = (i < leaf->key_len) ? leaf->key[i] : 0;
            unsigned char new_byte = (i < key_len) ? key[i] : 0;
            new_node->keys[0] = existing_byte;
            new_node->children[0] = leaf;
            new_node->keys[1] = new_byte;
            new_node->children[1] = art_create_leaf(key, key_len, value);
            new_node->num_children = 2;
            return new_node;
        }
    } else { // Internal node
        ArtNode *art_node = (ArtNode *)node;
        if (depth >= key_len) {
            // 키가 끝났다면, 삽입 위치 결정이 애매하므로 새 리프를 삽입
            ArtLeaf *leaf = art_create_leaf(key, key_len, value);
            if (art_node->num_children < ((art_node->type == ART_NODE4) ? 4 : 16)) {
                art_node->keys[art_node->num_children] = 0;
                art_node->children[art_node->num_children] = leaf;
                art_node->num_children++;
            }
            return art_node;
        }
        unsigned char cur_byte = key[depth];
        int i;
        for (i = 0; i < art_node->num_children; i++) {
            if (art_node->keys[i] == cur_byte) {
                art_node->children[i] = art_insert_recursive(art_node->children[i], key, key_len, value, depth + 1);
                return art_node;
            }
        }
        // 해당 바이트에 대한 자식이 없으므로, 새 리프 삽입
        ArtLeaf *new_leaf = art_create_leaf(key, key_len, value);
        if (art_node->num_children < ((art_node->type == ART_NODE4) ? 4 : 16)) {
            art_node->keys[art_node->num_children] = cur_byte;
            art_node->children[art_node->num_children] = new_leaf;
            art_node->num_children++;
        } else {
            // Node4가 가득 찬 경우, 업그레이드: Node4 -> Node16
            if (art_node->type == ART_NODE4) {
                ArtNode *new_node = art_create_node(ART_NODE16);
                for (i = 0; i < art_node->num_children; i++) {
                    new_node->keys[i] = art_node->keys[i];
                    new_node->children[i] = art_node->children[i];
                }
                new_node->num_children = art_node->num_children;
                free(art_node);
                art_node = new_node;
                art_node->keys[art_node->num_children] = cur_byte;
                art_node->children[art_node->num_children] = new_leaf;
                art_node->num_children++;
            } else {
                // 이미 Node16가 가득 찼다면 (완전한 구현에서는 Node48로 업그레이드)
                // 여기서는 단순히 마지막 자식을 대체합니다.
                art_node->keys[art_node->num_children - 1] = cur_byte;
                art_node->children[art_node->num_children - 1] = new_leaf;
            }
        }
        return art_node;
    }
}

/* ART 삽입 래퍼: depth 0부터 시작 */
void art_insert(void **root, const unsigned char *key, int value) {
    int key_len = strlen((const char *)key);
    *root = art_insert_recursive(*root, key, key_len, value, 0);
}

/*
 * art_search_recursive:
 * - 재귀적으로 키를 탐색하며, 리프 노드를 찾으면 값을 반환합니다.
 */
int art_search_recursive(void *node, const unsigned char *key, int key_len, int depth, bool *found) {
    if (node == NULL) {
        *found = false;
        return -1;
    }
    if (((ArtLeaf *)node)->class == LEAF_TYPE) {
        ArtLeaf *leaf = (ArtLeaf *)node;
        if (leaf->key_len == key_len && strcmp((char *)leaf->key, (char *)key) == 0) {
            *found = true;
            return leaf->value;
        }
        *found = false;
        return -1;
    } else {
        ArtNode *art_node = (ArtNode *)node;
        if (depth >= key_len) {
            *found = false;
            return -1;
        }
        unsigned char cur_byte = key[depth];
        int i;
        for (i = 0; i < art_node->num_children; i++) {
            if (art_node->keys[i] == cur_byte) {
                return art_search_recursive(art_node->children[i], key, key_len, depth + 1, found);
            }
        }
        *found = false;
        return -1;
    }
}

/* ART 검색 래퍼 */
int art_search(void *root, const unsigned char *key, bool *found) {
    int key_len = strlen((const char *)key);
    return art_search_recursive(root, key, key_len, 0, found);
}

/*
 * art_delete_recursive:
 * - 재귀적으로 키를 탐색하여 삭제하고, 해당 노드를 NULL로 반환합니다.
 * - Internal Node의 경우, 자식 배열에서 삭제된 항목을 제거하고, 자식 수를 감소시킵니다.
 */
void *art_delete_recursive(void *node, const unsigned char *key, int key_len, int depth, bool *deleted) {
    if (node == NULL) {
        *deleted = false;
        return NULL;
    }
    if (((ArtLeaf *)node)->class == LEAF_TYPE) {
        ArtLeaf *leaf = (ArtLeaf *)node;
        if (leaf->key_len == key_len && strcmp((char *)leaf->key, (char *)key) == 0) {
            *deleted = true;
            free(leaf->key);
            free(leaf);
            return NULL;
        }
        *deleted = false;
        return node;
    } else {
        ArtNode *art_node = (ArtNode *)node;
        if (depth >= key_len) {
            *deleted = false;
            return node;
        }
        unsigned char cur_byte = key[depth];
        int i;
        for (i = 0; i < art_node->num_children; i++) {
            if (art_node->keys[i] == cur_byte) {
                art_node->children[i] = art_delete_recursive(art_node->children[i], key, key_len, depth + 1, deleted);
                if (*deleted) {
                    // 자식 배열에서 삭제된 항목 제거
                    for (int j = i; j < art_node->num_children - 1; j++) {
                        art_node->keys[j] = art_node->keys[j + 1];
                        art_node->children[j] = art_node->children[j + 1];
                    }
                    art_node->num_children--;
                }
                break;
            }
        }
        if (art_node->num_children == 0) {
            free(art_node);
            return NULL;
        }
        return art_node;
    }
}

/* ART 삭제 래퍼 */
void art_delete(void **root, const unsigned char *key) {
    int key_len = strlen((const char *)key);
    bool deleted = false;
    *root = art_delete_recursive(*root, key, key_len, 0, &deleted);
    if (deleted)
        printf("Deleted key: %s\n", key);
    else
        printf("Key not found for deletion: %s\n", key);
}

/*
 * art_print_level_order:
 * - 큐를 이용하여 ART의 모든 노드를 레벨 순회로 출력합니다.
 * - 리프 노드는 [Leaf: key, value]로, Internal Node는 [Node (Type) keys: ...]로 출력합니다.
 */
void art_print_level_order(void *root) {
    if (root == NULL) {
        printf("ART is empty.\n");
        return;
    }
    void **queue = malloc(sizeof(void *) * 1024);
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        int level_count = rear - front;
        while (level_count--) {
            void *node = queue[front++];
            if (((ArtLeaf *)node)->class == LEAF_TYPE) {
                ArtLeaf *leaf = (ArtLeaf *)node;
                printf("[Leaf: %s, value: %d] ", leaf->key, leaf->value);
            } else {
                ArtNode *art_node = (ArtNode *)node;
                printf("[Node (%s) keys: ", art_node->type == ART_NODE4 ? "Node4" : "Node16");
                for (int i = 0; i < art_node->num_children; i++) {
                    printf("%02x ", art_node->keys[i]);
                }
                printf("] ");
                for (int i = 0; i < art_node->num_children; i++) {
                    queue[rear++] = art_node->children[i];
                }
            }
        }
        printf("\n");
    }
    free(queue);
}

/* --- main 함수 --- */
int main(void) {
    void *root = NULL;
    
    printf("=== Adaptive Radix Tree (ART) Demo ===\n\n");
    
    // 삽입 테스트: 문자열 키와 정수 값을 사용
    art_insert(&root, (unsigned char *)"apple", 100);
    art_insert(&root, (unsigned char *)"banana", 200);
    art_insert(&root, (unsigned char *)"cherry", 300);
    art_insert(&root, (unsigned char *)"date", 400);
    art_insert(&root, (unsigned char *)"elderberry", 500);
    art_insert(&root, (unsigned char *)"fig", 600);
    art_insert(&root, (unsigned char *)"grape", 700);
    
    printf("\nART Level Order Traversal after insertions:\n");
    art_print_level_order(root);
    
    // 검색 테스트
    bool found = false;
    int val = art_search(root, (unsigned char *)"cherry", &found);
    if (found)
        printf("\nSearch: key \"cherry\" found with value %d\n", val);
    else
        printf("\nSearch: key \"cherry\" not found\n");
    
    val = art_search(root, (unsigned char *)"kiwi", &found);
    if (found)
        printf("Search: key \"kiwi\" found with value %d\n", val);
    else
        printf("Search: key \"kiwi\" not found\n");
    
    // 삭제 테스트
    art_delete(&root, (unsigned char *)"banana");
    art_delete(&root, (unsigned char *)"date");
    
    printf("\nART Level Order Traversal after deletions:\n");
    art_print_level_order(root);
    
    // 메모리 해제는 전체 트리 해제 함수가 필요하나, 본 예제에서는 생략합니다.
    
    return 0;
}
