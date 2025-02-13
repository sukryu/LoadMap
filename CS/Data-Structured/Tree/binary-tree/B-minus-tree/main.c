/*
 * main.c
 *
 * 이 파일은 B-Tree의 주요 연산(삽입, 삭제, 검색, 순회)을 시연하는 예제입니다.
 * B-Tree는 노드 하나가 여러 키와 자식 포인터를 가지며, 
 * 삽입 시 노드가 가득 차면 분할(splitting)하고, 삭제 시 노드가 최소 키 개수 미만이 되면 
 * 재분배(redistribution) 또는 병합(merging)을 통해 균형을 유지합니다.
 *
 * 이 구현은 최소 차수(T)를 기반으로 합니다.
 * 각 노드는 최소 T-1개의 키, 최대 2*T-1개의 키를 가집니다.
 *
 * 이 코드는 B+ Tree의 구현 방식과 유사한 스타일로 작성되었으며,
 * 복잡한 경우(노드 분할, 재분배, 병합 등)를 모두 처리합니다.
 *
 * 참고: 실무에서 사용하기 위해서는 추가적인 에러 처리와 메모리 관리 최적화가 필요합니다.
 */

#include <stdio.h>
#include <stdlib.h>

#define T 2  // 최소 차수; 각 노드는 최소 T-1, 최대 2*T-1 키를 가짐

// B-Tree 노드 구조체 정의
typedef struct BTreeNode {
    int n;                    // 현재 저장된 키의 개수
    int *keys;                // 키 배열
    struct BTreeNode **C;     // 자식 포인터 배열 (자식의 개수 = n+1)
    int leaf;                 // 리프 노드 여부 (1이면 리프, 0이면 내부 노드)
} BTreeNode;

// 함수 선언
BTreeNode* createNode(int leaf);
void traverse(BTreeNode* root);
BTreeNode* search(BTreeNode* root, int key);
void insert(BTreeNode** root, int key);
void splitChild(BTreeNode* x, int i, BTreeNode* y);
void insertNonFull(BTreeNode* x, int key);
void removeKey(BTreeNode** root, int key);
void removeFromLeaf(BTreeNode* node, int idx);
void removeFromNonLeaf(BTreeNode* node, int idx);
int getPred(BTreeNode* node, int idx);
int getSucc(BTreeNode* node, int idx);
void fill(BTreeNode* node, int idx);
void borrowFromPrev(BTreeNode* node, int idx);
void borrowFromNext(BTreeNode* node, int idx);
void mergeNodes(BTreeNode* node, int idx);
void printLevelOrder(BTreeNode* root);
void freeTree(BTreeNode* root);

// B-Tree 노드 생성
BTreeNode* createNode(int leaf) {
    BTreeNode* node = (BTreeNode*) malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->keys = (int*) malloc(sizeof(int) * (2*T - 1));
    node->C = (BTreeNode**) malloc(sizeof(BTreeNode*) * (2*T));
    node->n = 0;
    return node;
}

// B-Tree 전체 순회 (중위 순회)
void traverse(BTreeNode* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->n; i++) {
            if (!root->leaf)
                traverse(root->C[i]);
            printf("%d ", root->keys[i]);
        }
        if (!root->leaf)
            traverse(root->C[i]);
    }
}

// B-Tree에서 키 검색
BTreeNode* search(BTreeNode* root, int key) {
    int i = 0;
    while (i < root->n && key > root->keys[i])
        i++;
    if (i < root->n && root->keys[i] == key)
        return root;
    if (root->leaf)
        return NULL;
    return search(root->C[i], key);
}

// Splits the child y of node x at index i.
void splitChild(BTreeNode* x, int i, BTreeNode* y) {
    // y는 full node. z는 y의 새로운 분할 노드.
    BTreeNode* z = createNode(y->leaf);
    z->n = T - 1;
    // y의 마지막 T-1 키를 z로 복사
    for (int j = 0; j < T - 1; j++)
        z->keys[j] = y->keys[j + T];
    // 만약 y가 내부 노드라면, 자식 포인터도 이동
    if (!y->leaf) {
        for (int j = 0; j < T; j++)
            z->C[j] = y->C[j + T];
    }
    y->n = T - 1;
    // x의 자식 포인터 공간을 늘려 z를 삽입
    for (int j = x->n; j >= i+1; j--)
        x->C[j+1] = x->C[j];
    x->C[i+1] = z;
    // x의 키를 이동시켜 y의 중간 키를 삽입
    for (int j = x->n - 1; j >= i; j--)
        x->keys[j+1] = x->keys[j];
    x->keys[i] = y->keys[T - 1];
    x->n = x->n + 1;
}

// 삽입할 노드가 비포화 상태일 때 키 삽입
void insertNonFull(BTreeNode* x, int key) {
    int i = x->n - 1;
    if (x->leaf) {
        // 리프 노드이면, 키를 적절한 위치에 삽입하며 키들을 오른쪽으로 이동
        while (i >= 0 && x->keys[i] > key) {
            x->keys[i+1] = x->keys[i];
            i--;
        }
        x->keys[i+1] = key;
        x->n = x->n + 1;
    } else {
        // 내부 노드이면, 적절한 자식을 찾음
        while (i >= 0 && x->keys[i] > key)
            i--;
        i++;
        if (x->C[i]->n == 2*T - 1) {
            splitChild(x, i, x->C[i]);
            if (x->keys[i] < key)
                i++;
        }
        insertNonFull(x->C[i], key);
    }
}

// B-Tree 삽입 (루트를 업데이트 할 수 있음)
void insert(BTreeNode** root, int key) {
    BTreeNode* r = *root;
    if (r->n == 2*T - 1) {
        // 루트가 가득 찬 경우, 트리 높이를 증가시킴.
        BTreeNode* s = createNode(0);
        s->C[0] = r;
        splitChild(s, 0, r);
        int i = 0;
        if (s->keys[0] < key)
            i++;
        insertNonFull(s->C[i], key);
        *root = s;
    } else {
        insertNonFull(r, key);
    }
}

// A utility function to find the index of the first key greater than or equal to key
int findKey(BTreeNode* node, int key) {
    int idx = 0;
    while (idx < node->n && node->keys[idx] < key)
        ++idx;
    return idx;
}

// Remove a key from the B-Tree rooted with node
void removeKey(BTreeNode** root, int key) {
    if (*root == NULL) return;
    BTreeNode* node = *root;
    int idx = findKey(node, key);
    
    // If the key to be removed is present in this node
    if (idx < node->n && node->keys[idx] == key) {
        if (node->leaf)
            removeFromLeaf(node, idx);
        else
            removeFromNonLeaf(node, idx);
    } else {
        // If this node is a leaf node, then the key is not present in tree
        if (node->leaf) {
            printf("The key %d is not present in the tree\n", key);
            return;
        }
        // The key to be removed is present in the sub-tree rooted with this node
        int flag = ( (idx == node->n) ? 1 : 0 );
        if (node->C[idx]->n < T)
            fill(node, idx);
        if (flag && idx > node->n)
            removeKey(&(node->C[idx-1]), key);
        else
            removeKey(&(node->C[idx]), key);
    }
    
    // If the root node has 0 keys, change root
    if (node->n == 0) {
        BTreeNode* tmp = node;
        if (node->leaf)
            *root = NULL;
        else
            *root = node->C[0];
        free(tmp->keys);
        free(tmp->C);
        free(tmp);
    }
}

// Remove key from a leaf node
void removeFromLeaf(BTreeNode* node, int idx) {
    for (int i = idx+1; i < node->n; ++i)
        node->keys[i-1] = node->keys[i];
    node->n--;
}

// Remove key from an internal node
void removeFromNonLeaf(BTreeNode* node, int idx) {
    int key = node->keys[idx];
    // If the child that precedes key has at least T keys
    if (node->C[idx]->n >= T) {
        int pred = getPred(node, idx);
        node->keys[idx] = pred;
        removeKey(&(node->C[idx]), pred);
    }
    // If the child that succeeds key has at least T keys
    else if (node->C[idx+1]->n >= T) {
        int succ = getSucc(node, idx);
        node->keys[idx] = succ;
        removeKey(&(node->C[idx+1]), succ);
    }
    // If both children have less than T keys, merge key and child at idx+1 into child at idx
    else {
        mergeNodes(node, idx);
        removeKey(&(node->C[idx]), key);
    }
}

// Get predecessor of key at index idx in node
int getPred(BTreeNode* node, int idx) {
    BTreeNode* cur = node->C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];
    return cur->keys[cur->n - 1];
}

// Get successor of key at index idx in node
int getSucc(BTreeNode* node, int idx) {
    BTreeNode* cur = node->C[idx+1];
    while (!cur->leaf)
        cur = cur->C[0];
    return cur->keys[0];
}

// Fill child node at index idx which has less than T-1 keys
void fill(BTreeNode* node, int idx) {
    if (idx != 0 && node->C[idx-1]->n >= T)
        borrowFromPrev(node, idx);
    else if (idx != node->n && node->C[idx+1]->n >= T)
        borrowFromNext(node, idx);
    else {
        if (idx != node->n)
            mergeNodes(node, idx);
        else
            mergeNodes(node, idx-1);
    }
}

// Borrow a key from node->C[idx-1] and insert it into node->C[idx]
void borrowFromPrev(BTreeNode* node, int idx) {
    BTreeNode* child = node->C[idx];
    BTreeNode* sibling = node->C[idx-1];
    // Shift child keys to right
    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i+1] = child->keys[i];
    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->C[i+1] = child->C[i];
    }
    child->keys[0] = node->keys[idx-1];
    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];
    node->keys[idx-1] = sibling->keys[sibling->n - 1];
    child->n += 1;
    sibling->n -= 1;
}

// Borrow a key from node->C[idx+1] and insert it into node->C[idx]
void borrowFromNext(BTreeNode* node, int idx) {
    BTreeNode* child = node->C[idx];
    BTreeNode* sibling = node->C[idx+1];
    child->keys[child->n] = node->keys[idx];
    if (!child->leaf)
        child->C[child->n+1] = sibling->C[0];
    node->keys[idx] = sibling->keys[0];
    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i-1] = sibling->keys[i];
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i-1] = sibling->C[i];
    }
    child->n += 1;
    sibling->n -= 1;
}

// Merge node->C[idx] and node->C[idx+1] with a key from node
void mergeNodes(BTreeNode* node, int idx) {
    BTreeNode* child = node->C[idx];
    BTreeNode* sibling = node->C[idx+1];
    child->keys[child->n] = node->keys[idx];
    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + child->n + 1] = sibling->keys[i];
    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + child->n + 1] = sibling->C[i];
    }
    child->n += sibling->n + 1;
    for (int i = idx+1; i < node->n; ++i)
        node->keys[i-1] = node->keys[i];
    for (int i = idx+2; i <= node->n; ++i)
        node->C[i-1] = node->C[i];
    node->n--;
    free(sibling->keys);
    free(sibling->C);
    free(sibling);
}

// Level Order Traversal for B-Tree
void printLevelOrder(BTreeNode* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    BTreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        int count = rear - front;
        while (count > 0) {
            BTreeNode* node = queue[front++];
            printf("[");
            for (int i = 0; i < node->n; i++) {
                printf("%d ", node->keys[i]);
            }
            printf("] ");
            if (!node->leaf) {
                for (int i = 0; i <= node->n; i++) {
                    if (node->C[i])
                        queue[rear++] = node->C[i];
                }
            }
            count--;
        }
        printf("\n");
    }
}

// Free B-Tree memory recursively
void freeTree(BTreeNode* root) {
    if (root != NULL) {
        if (!root->leaf) {
            for (int i = 0; i <= root->n; i++) {
                freeTree(root->C[i]);
            }
        }
        free(root->keys);
        free(root->C);
        free(root);
    }
}

/* Main function demonstrating B-Tree operations */
int main(void) {
    BTreeNode *root = createNode(1); // Initially, root is a leaf.
    printf("=== B-Tree Demo ===\n\n");
    
    // Insertion Test
    int keys_to_insert[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys_to_insert) / sizeof(keys_to_insert[0]);
    for (int i = 0; i < n; i++) {
        insert(&root, keys_to_insert[i]);
        printf("Inserted key %d\n", keys_to_insert[i]);
    }
    
    printf("\nB-Tree Level Order Traversal after insertion:\n");
    printLevelOrder(root);
    
    // Search Test
    int search_key = 12;
    BTreeNode* found = search(root, search_key);
    if (found)
        printf("\nSearch: Key %d found in the tree.\n", search_key);
    else
        printf("\nSearch: Key %d not found in the tree.\n", search_key);
    
    // Deletion Test
    int keys_to_delete[] = {6, 7, 10};
    int m = sizeof(keys_to_delete) / sizeof(keys_to_delete[0]);
    for (int i = 0; i < m; i++) {
        printf("\nDeleting key %d\n", keys_to_delete[i]);
        removeKey(&root, keys_to_delete[i]);
        printLevelOrder(root);
    }
    
    printf("\nFinal B-Tree Level Order Traversal:\n");
    printLevelOrder(root);
    
    // Free memory
    freeTree(root);
    
    return 0;
}