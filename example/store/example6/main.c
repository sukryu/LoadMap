#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* head = NULL;

// 오름차순 순서를 유지하며 새로운 노드를 삽입
void add(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    
    // 리스트가 비어있거나 새 노드가 헤드보다 작을 경우
    if (head == NULL || data <= head->data) {
        newNode->next = head;
        head = newNode;
        return;
    }
    
    // 삽입 위치 찾기
    Node* current = head;
    while (current->next != NULL && current->next->data < data) {
        current = current->next;
    }
    
    // 노드 연결
    newNode->next = current->next;
    current->next = newNode;
}

// 값 탐색
int search(int target) {
    Node* current = head;
    while (current != NULL) {
        if (current->data == target) {
            return 1;  // 찾음
        }
        current = current->next;
    }
    return 0;  // 못찾음
}

// 메모리 해제
void freeList() {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}

int main() {
    int N, Q, value;
    
    // N개의 정수 입력 받기
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &value);
        add(value);
    }
    
    // Q개의 탐색 쿼리 처리
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        scanf("%d", &value);
        printf("%s\n", search(value) ? "YES" : "NO");
    }
    
    // 메모리 해제
    freeList();
    return 0;
}