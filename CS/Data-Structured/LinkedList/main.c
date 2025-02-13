/*
 * main.c
 *
 * 연결리스트(Linked List)를 직접 구현하고 다양한 연산(삽입, 삭제, 탐색)을 시연하는 예제입니다.
 * 이 코드는 초보자도 이해할 수 있도록 자세한 주석과 함께 작성되었으며, 실무에서 직접 활용할 수 있는 수준의 구현을 목표로 합니다.
 *
 * 연결리스트는 C 언어에서 기본 제공되지 않으므로, 개발자가 직접 노드(Node) 구조체와 관련 함수들을 구현해야 합니다.
 */

#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의: 각 노드는 데이터를 저장하고 다음 노드를 가리키는 포인터를 가짐.
typedef struct Node {
    int data;              // 저장할 데이터 (여기서는 정수를 예로 사용)
    struct Node* next;     // 다음 노드의 주소
} Node;

/*
 * 새로운 노드를 생성하는 함수.
 * 매개변수: data - 노드에 저장할 데이터
 * 반환값: 동적으로 생성된 노드의 포인터.
 */
Node* createNode(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(new_node == NULL) {
        fprintf(stderr, "메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

/*
 * 헤드(리스트의 시작)에 새 노드를 삽입하는 함수.
 * 매개변수: head - 연결리스트의 포인터의 주소, data - 삽입할 데이터.
 * 결과: 새로운 노드가 리스트의 맨 앞에 추가됩니다.
 */
void insertAtHead(Node** head, int data) {
    Node* new_node = createNode(data);
    new_node->next = *head;
    *head = new_node;
}

/*
 * 리스트의 끝(꼬리)에 새 노드를 삽입하는 함수.
 * 매개변수: head - 연결리스트의 포인터의 주소, data - 삽입할 데이터.
 * 결과: 새로운 노드가 리스트의 맨 끝에 추가됩니다.
 */
void insertAtTail(Node** head, int data) {
    Node* new_node = createNode(data);
    if(*head == NULL) {
        *head = new_node;
        return;
    }
    Node* temp = *head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

/*
 * 특정 노드 뒤에 새로운 노드를 삽입하는 함수.
 * 매개변수: prev_node - 삽입할 위치의 바로 앞 노드, data - 삽입할 데이터.
 * 결과: prev_node 뒤에 새로운 노드가 추가됩니다.
 */
void insertAfter(Node* prev_node, int data) {
    if(prev_node == NULL) {
        printf("이전 노드는 NULL일 수 없습니다.\n");
        return;
    }
    Node* new_node = createNode(data);
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

/*
 * 리스트에서 첫 번째로 등장하는 특정 값을 가진 노드를 삭제하는 함수.
 * 매개변수: head - 연결리스트의 포인터의 주소, key - 삭제할 데이터 값.
 */
void deleteNode(Node** head, int key) {
    Node* temp = *head;
    Node* prev = NULL;
    
    // 만약 헤드 노드가 삭제할 값일 경우
    if(temp != NULL && temp->data == key) {
        *head = temp->next; // 헤드를 다음 노드로 변경
        free(temp);
        return;
    }
    
    // 삭제할 노드를 찾을 때까지 순회
    while(temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
    
    // 삭제할 값이 리스트에 없는 경우
    if(temp == NULL) {
        printf("값 %d을(를) 찾을 수 없습니다.\n", key);
        return;
    }
    
    // 노드를 리스트에서 분리하고 메모리 해제
    prev->next = temp->next;
    free(temp);
}

/*
 * 리스트에서 특정 값을 가진 노드를 탐색하는 함수.
 * 매개변수: head - 연결리스트의 시작 포인터, key - 찾을 데이터 값.
 * 반환값: 찾은 노드의 포인터를 반환하며, 없으면 NULL을 반환.
 */
Node* search(Node* head, int key) {
    Node* current = head;
    while(current != NULL) {
        if(current->data == key) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/*
 * 연결리스트의 모든 요소를 출력하는 함수.
 * 매개변수: head - 연결리스트의 시작 포인터.
 */
void printList(Node* head) {
    Node* current = head;
    printf("연결리스트: ");
    while(current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

/*
 * 연결리스트에 할당된 메모리를 모두 해제하는 함수.
 * 매개변수: head - 연결리스트의 시작 포인터.
 */
void freeList(Node* head) {
    Node* current = head;
    Node* next_node;
    while(current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

int main(void) {
    Node* head = NULL;  // 빈 연결리스트 초기화

    // 1. 헤드 삽입 예제
    printf("=== 헤드 삽입 예제 ===\n");
    insertAtHead(&head, 10);
    insertAtHead(&head, 20);
    insertAtHead(&head, 30);
    printList(head);

    // 2. 꼬리 삽입 예제
    printf("\n=== 꼬리 삽입 예제 ===\n");
    insertAtTail(&head, 40);
    insertAtTail(&head, 50);
    printList(head);

    // 3. 특정 노드 뒤에 삽입 예제
    printf("\n=== 특정 노드 뒤 삽입 예제 (두 번째 노드 뒤에 25 삽입) ===\n");
    if(head != NULL && head->next != NULL) {
        insertAfter(head->next, 25);
    }
    printList(head);

    // 4. 노드 삭제 예제: 값이 20인 노드 삭제
    printf("\n=== 노드 삭제 예제 (값 20 삭제) ===\n");
    deleteNode(&head, 20);
    printList(head);

    // 5. 노드 탐색 예제: 값이 40인 노드 검색
    printf("\n=== 노드 탐색 예제 (값 40 탐색) ===\n");
    int search_key = 40;
    Node* found = search(head, search_key);
    if(found != NULL) {
        printf("값 %d을(를) 가진 노드를 찾았습니다.\n", search_key);
    } else {
        printf("값 %d을(를) 가진 노드를 찾지 못했습니다.\n", search_key);
    }

    // 6. 연결리스트의 모든 노드 메모리 해제
    freeList(head);

    return 0;
}