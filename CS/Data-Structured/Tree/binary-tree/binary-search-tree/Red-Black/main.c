/*
 * main.c
 *
 * 이 파일은 Red-Black Tree의 주요 연산(삽입, 탐색, 삭제, 순회)을 시연하는 예제입니다.
 * Red-Black Tree는 각 노드에 빨간색(RED) 또는 검은색(BLACK)의 색상을 부여하여 트리의 균형을 유지합니다.
 * 이 예제에서는 NIL 노드(TNULL)를 사용하여 리프(leaf)들을 표현하며, 삽입 및 삭제 후 색상 재조정과 회전 연산을 통해
 * 트리의 속성을 복구합니다.
 *
 * 각 함수에는 초보자도 이해할 수 있도록 상세한 주석을 추가하였습니다.
 */

#include <stdio.h>
#include <stdlib.h>

#define RED   0
#define BLACK 1

// Red-Black Tree 노드 구조체
typedef struct RBNode {
    int data;
    int color;              // RED 또는 BLACK
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;
} RBNode;

// 전역 NIL 노드(TNULL): 모든 리프를 나타내며, 색상은 BLACK
RBNode *TNULL;

// TNULL 초기화 함수: NIL 노드를 생성하고 초기화
void initializeTNULL() {
    TNULL = (RBNode*)malloc(sizeof(RBNode));
    if (TNULL == NULL) {
        fprintf(stderr, "TNULL 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    TNULL->color = BLACK;
    TNULL->left = TNULL->right = TNULL->parent = NULL;
}

// 새로운 Red-Black Tree 노드 생성 함수
RBNode* newRBNode(int data) {
    RBNode *node = (RBNode*)malloc(sizeof(RBNode));
    if (node == NULL) {
        fprintf(stderr, "새 노드 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->color = RED;         // 새 노드는 기본적으로 빨간색
    node->left = node->right = node->parent = TNULL;
    return node;
}

/*
 * 좌측 회전(leftRotate)
 * x를 기준으로 좌측 회전을 수행하여 트리의 균형을 조정합니다.
 */
void leftRotate(RBNode **root, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left != TNULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == TNULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

/*
 * 우측 회전(rightRotate)
 * y를 기준으로 우측 회전을 수행하여 트리의 균형을 조정합니다.
 */
void rightRotate(RBNode **root, RBNode *y) {
    RBNode *x = y->left;
    y->left = x->right;
    if (x->right != TNULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == TNULL)
        *root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;
    x->right = y;
    y->parent = x;
}

/*
 * rbInsertFixup 함수:
 * 새로운 노드 삽입 후, Red-Black Tree의 성질(색상 규칙 등)을 복구하기 위해 호출됩니다.
 */
void rbInsertFixup(RBNode **root, RBNode *k) {
    RBNode *u;
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->left) {
            u = k->parent->parent->right;  // 삼촌 노드
            if (u->color == RED) {
                // Case 1: 삼촌 노드가 빨간색인 경우
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    // Case 2: 삼촌 노드가 검은색이고, k가 오른쪽 자식인 경우
                    k = k->parent;
                    leftRotate(root, k);
                }
                // Case 3: 삼촌 노드가 검은색이고, k가 왼쪽 자식인 경우
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(root, k->parent->parent);
            }
        } else {
            // 대칭적인 경우 (부모가 오른쪽 자식인 경우)
            u = k->parent->parent->left;
            if (u->color == RED) {
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(root, k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(root, k->parent->parent);
            }
        }
        if (*root == k)
            break;
    }
    (*root)->color = BLACK;
}

/*
 * rbInsert 함수:
 * 새로운 데이터를 가진 노드를 Red-Black Tree에 삽입합니다.
 * BST 삽입 후 rbInsertFixup 함수를 호출하여 트리의 성질을 복구합니다.
 */
void rbInsert(RBNode **root, int data) {
    RBNode *node = newRBNode(data);
    RBNode *y = TNULL;
    RBNode *x = *root;
    
    while (x != TNULL) {
        y = x;
        if (node->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    
    node->parent = y;
    if (y == TNULL)
        *root = node;
    else if (node->data < y->data)
        y->left = node;
    else
        y->right = node;
    
    // 만약 노드가 루트라면, 색상을 검은색으로 설정하고 종료
    if (node->parent == TNULL) {
        node->color = BLACK;
        return;
    }
    
    // 조부모가 없는 경우에는 수정이 필요 없음
    if (node->parent->parent == TNULL)
        return;
    
    rbInsertFixup(root, node);
}

/*
 * inorderRBTree 함수:
 * 중위 순회 방식을 통해 Red-Black Tree의 노드를 오름차순으로 출력합니다.
 * 각 노드의 데이터와 색상을 함께 출력합니다.
 */
void inorderRBTree(RBNode *root) {
    if (root != TNULL) {
        inorderRBTree(root->left);
        printf("%d(%s) ", root->data, root->color == RED ? "R" : "B");
        inorderRBTree(root->right);
    }
}

/*
 * rbMinimum 함수:
 * 주어진 서브트리에서 가장 작은 값을 가진 노드를 반환합니다.
 * 삭제 연산에서 후계자(successor)를 찾을 때 사용됩니다.
 */
RBNode* rbMinimum(RBNode *node) {
    while (node->left != TNULL)
        node = node->left;
    return node;
}

/*
 * rbTransplant 함수:
 * 트리에서 한 서브트리를 다른 서브트리로 교체합니다.
 */
void rbTransplant(RBNode **root, RBNode *u, RBNode *v) {
    if (u->parent == TNULL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

/*
 * rbDeleteFixup 함수:
 * 노드 삭제 후 Red-Black Tree의 성질을 복구하기 위해 호출됩니다.
 */
void rbDeleteFixup(RBNode **root, RBNode *x) {
    RBNode *w;
    while (x != *root && x->color == BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            // 대칭적인 경우
            w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

/*
 * rbDelete 함수:
 * Red-Black Tree에서 주어진 데이터를 가진 노드를 삭제하고, 트리의 균형을 복구합니다.
 */
void rbDelete(RBNode **root, int data) {
    RBNode *z = *root;
    RBNode *x, *y;
    // 삭제할 노드를 탐색
    while (z != TNULL) {
        if (z->data == data)
            break;
        else if (data < z->data)
            z = z->left;
        else
            z = z->right;
    }
    if (z == TNULL) {
        printf("Data %d not found in the tree.\n", data);
        return;
    }
    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL) {
        x = z->right;
        rbTransplant(root, z, z->right);
    } else if (z->right == TNULL) {
        x = z->left;
        rbTransplant(root, z, z->left);
    } else {
        y = rbMinimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            rbTransplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (y_original_color == BLACK)
        rbDeleteFixup(root, x);
}

/*
 * rbSearch 함수:
 * Red-Black Tree에서 주어진 데이터를 가진 노드를 재귀적으로 탐색합니다.
 * 찾으면 해당 노드의 포인터를 반환하고, 없으면 TNULL을 반환합니다.
 */
RBNode* rbSearch(RBNode *root, int data) {
    if (root == TNULL || data == root->data)
        return root;
    if (data < root->data)
        return rbSearch(root->left, data);
    else
        return rbSearch(root->right, data);
}

/*
 * inorderRBTree 함수:
 * 중위 순회(In-order)를 통해 트리의 노드를 오름차순으로 출력합니다.
 * 각 노드의 데이터와 색상(R 또는 B)을 함께 출력합니다.
 */
void inorderRBTree(RBNode *root) {
    if (root != TNULL) {
        inorderRBTree(root->left);
        printf("%d(%s) ", root->data, root->color == RED ? "R" : "B");
        inorderRBTree(root->right);
    }
}

/*
 * freeRBTree 함수:
 * Red-Black Tree의 모든 노드를 재귀적으로 방문하며 메모리를 해제합니다.
 */
void freeRBTree(RBNode *root) {
    if (root != TNULL) {
        freeRBTree(root->left);
        freeRBTree(root->right);
        free(root);
    }
}

int main(void) {
    // NIL 노드 초기화
    initializeTNULL();
    
    // Red-Black Tree의 루트 초기화
    RBNode *root = TNULL;
    
    printf("=== Red-Black Tree Demo ===\n\n");
    
    // 삽입 연산
    int values[] = {41, 38, 31, 12, 19, 8};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; i++) {
        rbInsert(&root, values[i]);
        printf("Inserted %d\n", values[i]);
    }
    
    printf("\nIn-order Traversal: ");
    inorderRBTree(root);
    printf("\n\n");
    
    // 탐색 연산
    int key = 19;
    RBNode *found = rbSearch(root, key);
    if (found != TNULL)
        printf("Found node with key %d\n", key);
    else
        printf("Node with key %d not found\n", key);
    
    // 삭제 연산
    int deleteVal = 12;
    printf("\nDeleting %d\n", deleteVal);
    rbDelete(&root, deleteVal);
    
    printf("\nIn-order Traversal after deletion: ");
    inorderRBTree(root);
    printf("\n\n");
    
    // 메모리 해제
    freeRBTree(root);
    free(TNULL);
    printf("Red-Black Tree memory freed.\n");
    
    return 0;
}