/*
 * main.c
 *
 * 이 파일은 AVL 트리(자기 균형 이진 검색 트리)를 활용한 예제입니다.
 *
 * 주요 연산:
 * - 삽입 (Insertion): BST 규칙에 따라 노드를 삽입한 후, 균형 인수(Balance Factor)를 계산하여
 *   LL, RR, LR, RL 회전을 통해 트리의 균형을 유지합니다.
 *
 * - 삭제 (Deletion): 노드를 삭제한 후, 균형 인수를 재계산하여 필요한 경우 회전 연산을 수행합니다.
 *
 * - 순회 (Traversal): 중위, 전위, 후위 순회 방식을 통해 트리의 모든 노드를 방문합니다.
 *
 * 각 함수에는 초보자도 이해할 수 있도록 상세한 주석이 포함되어 있습니다.
 */

#include <stdio.h>
#include <stdlib.h>

// AVL 트리 노드 구조체 정의
typedef struct Node {
    int data;              // 노드가 저장하는 데이터
    struct Node *left;     // 왼쪽 자식 노드 포인터
    struct Node *right;    // 오른쪽 자식 노드 포인터
    int height;            // 노드의 높이
} Node;

// 최대값을 구하는 함수
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 노드의 높이를 반환하는 함수 (NULL이면 0)
int height(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

/*
 * createNode 함수:
 * 주어진 데이터를 저장하는 새 AVL 노드를 생성하고 초기화합니다.
 */
Node* createNode(int data) {
    Node *node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1;  // 새 노드의 높이는 1
    return node;
}

/*
 * rightRotate 함수:
 * LL 불균형을 해결하기 위해 우측 회전을 수행합니다.
 */
Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    
    // 회전 수행
    x->right = y;
    y->left = T2;
    
    // 높이 업데이트
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    
    // 새로운 루트 반환
    return x;
}

/*
 * leftRotate 함수:
 * RR 불균형을 해결하기 위해 좌측 회전을 수행합니다.
 */
Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    
    // 회전 수행
    y->left = x;
    x->right = T2;
    
    // 높이 업데이트
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    
    // 새로운 루트 반환
    return y;
}

/*
 * getBalance 함수:
 * 주어진 노드의 균형 인수(Balance Factor)를 계산합니다.
 */
int getBalance(Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

/*
 * insert 함수:
 * AVL 트리에 새 데이터를 삽입합니다.
 * BST 방식으로 삽입한 후, 균형 인수를 확인하여 필요한 회전 연산을 수행합니다.
 */
Node* insert(Node* node, int data) {
    // 기본 BST 삽입
    if (node == NULL)
        return createNode(data);
    
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else  // 중복된 값은 허용하지 않음
        return node;
    
    // 노드의 높이 업데이트
    node->height = 1 + max(height(node->left), height(node->right));
    
    // 균형 인수 계산
    int balance = getBalance(node);
    
    // 불균형 상태인 경우 4가지 경우로 나누어 회전 수행
    
    // Left Left Case (LL)
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);
    
    // Right Right Case (RR)
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);
    
    // Left Right Case (LR)
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Left Case (RL)
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    // 변경된 루트 반환
    return node;
}

/*
 * minValueNode 함수:
 * 주어진 서브트리에서 가장 작은 값을 가진 노드를 반환합니다.
 * 주로 삭제 연산 시 오른쪽 서브트리의 중위 후계자를 찾기 위해 사용됩니다.
 */
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

/*
 * deleteNode 함수:
 * AVL 트리에서 특정 데이터를 가진 노드를 삭제한 후 균형을 회복합니다.
 */
Node* deleteNode(Node* root, int data) {
    // 기본 BST 삭제 수행
    if (root == NULL)
        return root;
    
    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        // 삭제할 노드 발견
        if ((root->left == NULL) || (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right;
            
            // 자식이 없는 경우
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                // 자식이 하나인 경우, 자식 노드로 대체
                *root = *temp;
            }
            free(temp);
        } else {
            // 두 자식을 가진 경우: 오른쪽 서브트리의 최소 노드를 찾아 대체
            Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    
    // 트리에 노드가 하나도 없는 경우
    if (root == NULL)
        return root;
    
    // 높이 업데이트
    root->height = 1 + max(height(root->left), height(root->right));
    
    // 균형 인수 계산
    int balance = getBalance(root);
    
    // 불균형 상태인 경우 4가지 경우에 대해 회전 수행
    
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

/*
 * inOrder 함수:
 * 중위 순회(In-order) 방식으로 AVL 트리를 방문하며, 오름차순으로 데이터를 출력합니다.
 */
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

/*
 * preOrder 함수:
 * 전위 순회(Pre-order) 방식으로 AVL 트리를 방문합니다.
 */
void preOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

/*
 * postOrder 함수:
 * 후위 순회(Post-order) 방식으로 AVL 트리를 방문합니다.
 */
void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

/*
 * freeTree 함수:
 * 재귀적으로 AVL 트리의 모든 노드를 방문하여 메모리를 해제합니다.
 */
void freeTree(Node* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

/*
 * main 함수:
 * AVL 트리의 생성, 삽입, 삭제, 순회 연산을 시연합니다.
 */
int main(void) {
    Node *root = NULL;
    printf("=== AVL Tree Demo ===\n\n");
    
    // 삽입 연산: 데이터 배열을 AVL 트리에 삽입
    int values[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
        printf("Inserted %d\n", values[i]);
    }
    printf("\n");
    
    // 순회 연산
    printf("In-order Traversal: ");
    inOrder(root);
    printf("\n");
    
    printf("Pre-order Traversal: ");
    preOrder(root);
    printf("\n");
    
    printf("Post-order Traversal: ");
    postOrder(root);
    printf("\n\n");
    
    // 삭제 연산: 값 40 삭제
    int deleteVal = 40;
    printf("Deleting %d\n", deleteVal);
    root = deleteNode(root, deleteVal);
    
    printf("In-order Traversal after deletion: ");
    inOrder(root);
    printf("\n");
    
    // 트리 메모리 해제
    freeTree(root);
    printf("\nAVL Tree memory freed.\n");
    
    return 0;
}
