/*
 * main.c
 *
 * 이 파일은 이진 검색 트리(Binary Search Tree, BST)를 활용한 예제입니다.
 *
 * 주요 연산:
 * - 삽입 (Insertion): BST의 성질에 따라 새로운 노드를 트리에 삽입합니다.
 * - 탐색 (Search): 재귀적으로 BST를 탐색하여 특정 키를 가진 노드를 찾습니다.
 * - 삭제 (Deletion): 특정 키를 가진 노드를 삭제하고 트리의 구조를 재정비합니다.
 * - 순회 (Traversal): 중위, 전위, 후위 순회 방식을 통해 트리의 모든 노드를 방문합니다.
 *
 * 각 함수에는 초보자도 이해할 수 있도록 상세한 주석이 포함되어 있습니다.
 */

#include <stdio.h>
#include <stdlib.h>

// BST 노드 구조체 정의
typedef struct Node {
    int data;              // 노드가 저장하는 데이터
    struct Node *left;     // 왼쪽 자식 노드 포인터
    struct Node *right;    // 오른쪽 자식 노드 포인터
} Node;

/*
 * createNode 함수:
 * 주어진 데이터를 저장하는 새 BST 노드를 생성합니다.
 * 매개변수: data - 노드에 저장할 정수 값
 * 반환값: 새로 생성된 노드의 포인터
 */
Node* createNode(int data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

/*
 * insert 함수:
 * BST의 성질을 이용하여 새 데이터를 적절한 위치에 삽입합니다.
 * 매개변수: root - 현재 트리의 루트, data - 삽입할 데이터
 * 반환값: 업데이트된 트리의 루트 포인터
 */
Node* insert(Node* root, int data) {
    if (root == NULL)
        return createNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else  // data가 root->data보다 크거나 같은 경우 오른쪽 서브트리에 삽입
        root->right = insert(root->right, data);
    return root;
}

/*
 * inOrder 함수:
 * 중위 순회(In-order) 방식으로 트리를 방문합니다.
 * 방문 순서: 왼쪽 서브트리 → 현재 노드 → 오른쪽 서브트리
 * 중위 순회는 BST의 경우 오름차순으로 정렬된 결과를 출력합니다.
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
 * 전위 순회(Pre-order) 방식으로 트리를 방문합니다.
 * 방문 순서: 현재 노드 → 왼쪽 서브트리 → 오른쪽 서브트리
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
 * 후위 순회(Post-order) 방식으로 트리를 방문합니다.
 * 방문 순서: 왼쪽 서브트리 → 오른쪽 서브트리 → 현재 노드
 */
void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

/*
 * search 함수:
 * BST에서 주어진 키를 가진 노드를 재귀적으로 탐색합니다.
 * 매개변수: root - 현재 노드, key - 찾을 값
 * 반환값: 찾은 노드의 포인터 (없으면 NULL 반환)
 */
Node* search(Node* root, int key) {
    if (root == NULL || root->data == key)
        return root;
    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

/*
 * minValueNode 함수:
 * 주어진 서브트리에서 가장 작은 값을 가진 노드를 찾습니다.
 * 주로 삭제 연산 시 오른쪽 서브트리의 중위 후계자를 찾는 데 사용됩니다.
 */
Node* minValueNode(Node* root) {
    Node* current = root;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

/*
 * deleteNode 함수:
 * BST에서 특정 키를 가진 노드를 삭제하고, 트리의 구조를 재정비합니다.
 * 삭제 시 세 가지 경우를 고려합니다:
 * 1. 삭제할 노드가 리프인 경우: 단순 삭제
 * 2. 한 개의 자식만 있는 경우: 자식을 부모와 직접 연결
 * 3. 두 개의 자식을 가진 경우: 오른쪽 서브트리의 최소 노드(중위 후계자)를 찾아 대체 후 삭제
 */
Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;
    
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // 삭제할 노드 발견
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // 두 자식을 가진 경우: 오른쪽 서브트리의 최소 노드를 찾음
        Node* temp = minValueNode(root->right);
        root->data = temp->data;  // 후계자 값으로 대체
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

/*
 * freeTree 함수:
 * BST의 모든 노드를 재귀적으로 방문하여 메모리를 해제합니다.
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
 * BST의 생성, 탐색, 순회, 삭제 연산을 시연합니다.
 */
int main(void) {
    Node *root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);
    
    printf("=== 이진 검색 트리 (Binary Search Tree) 데모 ===\n\n");
    
    // BST에 노드 삽입
    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
        printf("삽입: %d\n", values[i]);
    }
    printf("\n");
    
    // 트리 순회: 중위, 전위, 후위 순회
    printf("중위 순회 (In-order, 오름차순): ");
    inOrder(root);
    printf("\n");
    
    printf("전위 순회 (Pre-order): ");
    preOrder(root);
    printf("\n");
    
    printf("후위 순회 (Post-order): ");
    postOrder(root);
    printf("\n\n");
    
    // 탐색 연산: 값 40을 가진 노드 검색
    int key = 40;
    Node *found = search(root, key);
    if (found != NULL)
        printf("탐색: %d 노드를 찾았습니다.\n", key);
    else
        printf("탐색: %d 노드를 찾지 못했습니다.\n", key);
    printf("\n");
    
    // 삭제 연산: 값 30인 노드 삭제
    int deleteKey = 30;
    printf("삭제: %d 노드를 삭제합니다.\n", deleteKey);
    root = deleteNode(root, deleteKey);
    
    printf("중위 순회 (삭제 후, 오름차순): ");
    inOrder(root);
    printf("\n\n");
    
    // BST 메모리 해제
    freeTree(root);
    printf("BST 메모리 해제 완료.\n");
    
    return 0;
}
