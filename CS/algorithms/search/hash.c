/**
 * hash.c
 *
 * 해시 탐색(Hash Search) 구현 예제
 * - 해시 테이블을 사용하여 키-값 쌍을 저장하고 검색합니다.
 * - 충돌 해결은 체이닝(Linked List)을 사용합니다.
 * - 해시 함수는 간단하게 모듈러 연산을 사용합니다.
 */

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10  // 해시 테이블의 크기

// 해시 노드 구조체: 키와 값, 그리고 다음 노드를 가리키는 포인터
typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

// 해시 테이블: TABLE_SIZE 크기의 노드 포인터 배열
Node* hashTable[TABLE_SIZE];

// 간단한 해시 함수: 키를 TABLE_SIZE로 나눈 나머지를 인덱스로 사용
int hash(int key) {
    return key % TABLE_SIZE;
}

// 해시 테이블에 (key, value) 쌍을 삽입하는 함수 (체이닝 방식)
void insert(int key, int value) {
    int index = hash(key);
    
    // 새 노드 생성
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->value = value;
    
    // 새 노드를 해당 인덱스의 체인 앞에 삽입
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// 해시 테이블에서 key에 해당하는 노드를 검색하는 함수
Node* search(int key) {
    int index = hash(key);
    Node* current = hashTable[index];
    
    // 해당 체인을 순회하면서 key 비교
    while (current != NULL) {
        if (current->key == key)
            return current;  // key를 찾으면 해당 노드 반환
        current = current->next;
    }
    return NULL;  // key를 찾지 못한 경우 NULL 반환
}

// 메모리 해제를 위한 함수: 해시 테이블의 모든 노드 해제
void freeHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

// main 함수: 해시 탐색 데모
int main(void) {
    // 해시 테이블 초기화: 모든 인덱스를 NULL로 설정
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
    
    // 예제 데이터를 삽입 (충돌 발생 가능)
    insert(1, 100);
    insert(11, 200);  // 1과 11은 동일한 인덱스(1)로 매핑됨 (11 % 10 == 1)
    insert(21, 300);  // 21도 동일한 인덱스(1)
    insert(5, 500);
    insert(15, 600);  // 15 % 10 == 5
    
    // 키 11에 대한 검색
    int target = 11;
    Node* result = search(target);
    
    if (result != NULL) {
        printf("키 %d에 대한 값: %d\n", result->key, result->value);
    } else {
        printf("키 %d를 찾을 수 없습니다.\n", target);
    }
    
    // 키 15에 대한 검색
    target = 15;
    result = search(target);
    if (result != NULL) {
        printf("키 %d에 대한 값: %d\n", result->key, result->value);
    } else {
        printf("키 %d를 찾을 수 없습니다.\n", target);
    }
    
    // 해시 테이블 메모리 해제
    freeHashTable();
    
    return 0;
}