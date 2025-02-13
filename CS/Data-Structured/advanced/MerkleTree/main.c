/*
 * Merkle Tree Demo
 *
 * 이 예제는 OpenSSL의 SHA-256 해시 함수를 활용하여 Merkle Tree를 
 * 구성, 검증, 업데이트하는 고도화된 구현 예제입니다.
 *
 * Merkle Tree는 각 리프 노드에 데이터 블록의 해시값을 저장하고,  
 * 내부 노드는 자식 노드들의 해시값을 결합(문자열 연결 후 해시 계산)하여 생성됩니다.
 * 최종적으로 루트 노드의 해시값은 전체 데이터 집합의 무결성을 대표합니다.
 *
 * 주요 기능:
 *  - compute_sha256(): 주어진 데이터의 SHA-256 해시값(16진수 문자열)을 계산합니다.
 *  - hash_concat(): 두 해시값을 연결하여 새로운 해시값을 생성합니다.
 *  - build_merkle_tree(): 데이터 배열로부터 Merkle Tree를 재귀적으로 구성합니다.
 *  - print_merkle_tree(): 레벨 순회 방식으로 Merkle Tree의 노드 해시값들을 출력합니다.
 *  - update_merkle_tree(): 특정 데이터 블록을 업데이트하고, 트리를 재구성합니다.
 *
 * 이 구현은 OpenSSL 라이브러리를 사용하므로, 컴파일 시 -lssl -lcrypto 옵션을 추가해야 합니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// SHA-256 해시 계산 함수: 입력 데이터를 해시하고, 64자리 16진수 문자열로 반환
char* compute_sha256(const char *data, size_t len) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)data, len, hash);
    char *hex_str = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (!hex_str) {
        fprintf(stderr, "메모리 할당 실패 (compute_sha256)\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_str + (i * 2), "%02x", hash[i]);
    }
    hex_str[SHA256_DIGEST_LENGTH * 2] = '\0';
    return hex_str;
}

// 두 해시 문자열을 연결하여 SHA-256 해시를 계산 (내부 노드 해시 계산)
char* hash_concat(const char *left, const char *right) {
    size_t len_left = strlen(left);
    size_t len_right = strlen(right);
    size_t total_len = len_left + len_right;
    char *combined = malloc(total_len + 1);
    if (!combined) {
        fprintf(stderr, "메모리 할당 실패 (hash_concat)\n");
        exit(EXIT_FAILURE);
    }
    strcpy(combined, left);
    strcat(combined, right);
    char *result = compute_sha256(combined, total_len);
    free(combined);
    return result;
}

// Merkle Tree 노드 구조체
typedef struct MerkleNode {
    char *hash;                // 노드의 해시값 (16진수 문자열)
    struct MerkleNode *left;   // 왼쪽 자식 (NULL이면 리프 노드)
    struct MerkleNode *right;  // 오른쪽 자식 (NULL이면 리프 노드)
    char *data;                // 리프 노드일 경우, 원본 데이터 (내부 노드에서는 NULL)
} MerkleNode;

// 리프 노드 생성: 데이터의 해시를 계산
MerkleNode* create_leaf(const char *data) {
    MerkleNode *node = malloc(sizeof(MerkleNode));
    if (!node) {
        fprintf(stderr, "메모리 할당 실패 (create_leaf)\n");
        exit(EXIT_FAILURE);
    }
    node->data = strdup(data);
    node->left = node->right = NULL;
    node->hash = compute_sha256(data, strlen(data));
    return node;
}

// 내부 노드 생성: 왼쪽, 오른쪽 자식의 해시값을 결합하여 해시 계산
MerkleNode* create_internal(MerkleNode *left, MerkleNode *right) {
    MerkleNode *node = malloc(sizeof(MerkleNode));
    if (!node) {
        fprintf(stderr, "메모리 할당 실패 (create_internal)\n");
        exit(EXIT_FAILURE);
    }
    node->left = left;
    node->right = right;
    node->data = NULL;
    node->hash = hash_concat(left->hash, right->hash);
    return node;
}

// Merkle Tree 재귀적 구성: 데이터 배열과 개수를 받아 Merkle Tree의 루트 노드를 반환
MerkleNode* build_merkle_tree(char **data_array, int n) {
    if (n == 0) return NULL;
    // 리프 노드 배열 생성
    int num_leaves = n;
    MerkleNode **nodes = malloc(sizeof(MerkleNode*) * num_leaves);
    if (!nodes) {
        fprintf(stderr, "메모리 할당 실패 (build_merkle_tree)\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        nodes[i] = create_leaf(data_array[i]);
    }
    // 짝수 개수 맞추기: 홀수인 경우 마지막 노드를 복제
    if (num_leaves % 2 == 1) {
        nodes = realloc(nodes, sizeof(MerkleNode*) * (num_leaves + 1));
        if (!nodes) {
            fprintf(stderr, "메모리 재할당 실패 (build_merkle_tree)\n");
            exit(EXIT_FAILURE);
        }
        nodes[num_leaves] = create_leaf(data_array[n - 1]);
        num_leaves++;
    }
    
    // 상위 레벨 노드 생성 (반복)
    while (num_leaves > 1) {
        int new_count = num_leaves / 2;
        MerkleNode **parent_nodes = malloc(sizeof(MerkleNode*) * new_count);
        if (!parent_nodes) {
            fprintf(stderr, "메모리 할당 실패 (parent_nodes)\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < new_count; i++) {
            MerkleNode *left = nodes[i * 2];
            MerkleNode *right = nodes[i * 2 + 1];
            parent_nodes[i] = create_internal(left, right);
        }
        free(nodes);
        nodes = parent_nodes;
        num_leaves = new_count;
        // 홀수 개수가 발생하면, 복제하여 짝수로 만듦
        if (num_leaves > 1 && (num_leaves % 2 == 1)) {
            nodes = realloc(nodes, sizeof(MerkleNode*) * (num_leaves + 1));
            if (!nodes) {
                fprintf(stderr, "메모리 재할당 실패 (build_merkle_tree 홀수 보정)\n");
                exit(EXIT_FAILURE);
            }
            nodes[num_leaves] = create_internal(nodes[num_leaves - 1], nodes[num_leaves - 1]);
            num_leaves++;
        }
    }
    MerkleNode *root = nodes[0];
    free(nodes);
    return root;
}

// Merkle Tree 레벨 순회 출력
void print_merkle_tree(MerkleNode *root) {
    if (!root) return;
    MerkleNode **queue = malloc(sizeof(MerkleNode*) * 1024);
    if (!queue) {
        fprintf(stderr, "메모리 할당 실패 (print_merkle_tree)\n");
        exit(EXIT_FAILURE);
    }
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        int level_count = rear - front;
        while (level_count > 0) {
            MerkleNode *node = queue[front++];
            printf("[%s] ", node->hash);
            if (node->left) queue[rear++] = node->left;
            if (node->right) queue[rear++] = node->right;
            level_count--;
        }
        printf("\n");
    }
    free(queue);
}

// Merkle Tree 전체 메모리 해제 (재귀적)
void free_merkle_tree(MerkleNode *node) {
    if (!node) return;
    free_merkle_tree(node->left);
    free_merkle_tree(node->right);
    if (node->hash) free(node->hash);
    if (node->data) free(node->data);
    free(node);
}

// Merkle Tree 업데이트: 데이터 배열에서 특정 인덱스의 데이터를 변경하고, 트리를 재구성
MerkleNode* update_merkle_tree(MerkleNode *root, char **data_array, int n, int index, const char *new_data) {
    if (index < 0 || index >= n) {
        fprintf(stderr, "업데이트 인덱스 오류\n");
        return root;
    }
    free(data_array[index]);
    data_array[index] = strdup(new_data);
    free_merkle_tree(root);
    return build_merkle_tree(data_array, n);
}

int main(void) {
    // 예제 데이터: 각 데이터 블록을 문자열로 표현
    int num_data = 5;
    char **data_array = malloc(sizeof(char*) * num_data);
    if (!data_array) {
        fprintf(stderr, "메모리 할당 실패 (main data_array)\n");
        exit(EXIT_FAILURE);
    }
    data_array[0] = strdup("Block 1: Transaction A");
    data_array[1] = strdup("Block 2: Transaction B");
    data_array[2] = strdup("Block 3: Transaction C");
    data_array[3] = strdup("Block 4: Transaction D");
    data_array[4] = strdup("Block 5: Transaction E");
    
    // Merkle Tree 구축
    MerkleNode *root = build_merkle_tree(data_array, num_data);
    printf("Initial Merkle Tree Root Hash:\n%s\n\n", root->hash);
    
    printf("Merkle Tree Level Order Traversal:\n");
    print_merkle_tree(root);
    
    // 검증: 간단히, 동일한 데이터 배열로 다시 트리를 구축하여 루트 해시 비교
    MerkleNode *rebuild_root = build_merkle_tree(data_array, num_data);
    if (strcmp(root->hash, rebuild_root->hash) == 0)
        printf("\n검증 성공: 루트 해시가 일치합니다.\n");
    else
        printf("\n검증 실패: 루트 해시가 일치하지 않습니다.\n");
    free_merkle_tree(rebuild_root);
    
    // 데이터 업데이트: 인덱스 2의 데이터를 변경하고 트리 재구성
    printf("\nUpdating Block 3...\n");
    root = update_merkle_tree(root, data_array, num_data, 2, "Block 3: UPDATED Transaction C");
    printf("Updated Merkle Tree Root Hash:\n%s\n\n", root->hash);
    print_merkle_tree(root);
    
    // 정리: Merkle Tree 및 데이터 배열 메모리 해제
    free_merkle_tree(root);
    for (int i = 0; i < num_data; i++) {
        free(data_array[i]);
    }
    free(data_array);
    
    return 0;
}