/*
 * main.c
 *
 * 해시 테이블(Hash Table)을 직접 구현하고 다양한 연산(삽입, 검색, 삭제)을 시연하는 예제입니다.
 * 이 코드는 체이닝(Chaining)을 사용한 충돌 해결 방식을 적용하여, 키-값 쌍을 저장하는 해시 테이블을 구현합니다.
 * 초보자부터 실무자까지 이해할 수 있도록 상세한 주석과 함께 작성되었습니다.
 */

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10  // 해시 테이블의 버킷(bucket) 개수

// 해시 노드 구조체: 각 노드는 키(key), 값(value) 그리고 다음 노드를 가리키는 포인터를 포함합니다.
typedef struct HashNode {
    int key;                // 데이터의 키
    int value;              // 데이터의 값
    struct HashNode *next;  // 체이닝을 위한 다음 노드의 포인터
} HashNode;

// 해시 테이블 구조체: 버킷 배열과 테이블의 크기를 저장합니다.
typedef struct HashTable {
    int size;         // 버킷의 총 개수
    HashNode **table; // 각 버킷은 연결 리스트(체인)의 시작 노드를 가리킴
} HashTable;

// 함수 원형 선언
HashTable* createHashTable(int size);
int hashFunction(HashTable *ht, int key);
void insert(HashTable *ht, int key, int value);
HashNode* search(HashTable *ht, int key);
void deleteKey(HashTable *ht, int key);
void printTable(HashTable *ht);
void freeHashTable(HashTable *ht);

int main(void) {
    // 해시 테이블 생성
    HashTable *ht = createHashTable(TABLE_SIZE);
    
    printf("=== 해시 테이블 초기 상태 ===\n");
    printTable(ht);

    // 1. 요소 삽입 예제
    printf("\n=== 해시 테이블에 요소 삽입 ===\n");
    // 아래 키들은 TABLE_SIZE가 10이므로, 15, 25, 35 모두 5번 버킷에 할당되어 충돌이 발생합니다.
    insert(ht, 15, 150);  // 15 % 10 = 5
    insert(ht, 25, 250);  // 25 % 10 = 5 (충돌 발생)
    insert(ht, 35, 350);  // 35 % 10 = 5 (충돌 발생)
    insert(ht, 7, 70);    // 7 % 10 = 7
    insert(ht, 3, 30);    // 3 % 10 = 3
    printTable(ht);

    // 2. 요소 검색 예제
    printf("\n=== 해시 테이블에서 요소 검색 ===\n");
    int searchKey = 25;
    HashNode *result = search(ht, searchKey);
    if (result) {
        printf("키 %d의 값은 %d 입니다.\n", searchKey, result->value);
    } else {
        printf("키 %d가 해시 테이블에 존재하지 않습니다.\n", searchKey);
    }

    // 3. 요소 삭제 예제
    printf("\n=== 해시 테이블에서 요소 삭제 ===\n");
    deleteKey(ht, 25);
    printTable(ht);

    // 4. 메모리 해제
    freeHashTable(ht);

    return 0;
}

/*
 * createHashTable 함수:
 * 지정된 크기의 해시 테이블을 생성합니다.
 * 각 버킷은 NULL로 초기화됩니다.
 */
HashTable* createHashTable(int size) {
    HashTable *ht = (HashTable*) malloc(sizeof(HashTable));
    if (ht == NULL) {
        fprintf(stderr, "해시 테이블 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    ht->size = size;
    ht->table = (HashNode**) malloc(sizeof(HashNode*) * size);
    if (ht->table == NULL) {
        fprintf(stderr, "버킷 배열 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    // 모든 버킷을 NULL로 초기화
    for (int i = 0; i < size; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

/*
 * hashFunction 함수:
 * 간단한 모듈로 연산을 사용하여 키를 버킷 인덱스로 변환합니다.
 */
int hashFunction(HashTable *ht, int key) {
    return key % ht->size;
}

/*
 * insert 함수:
 * 주어진 키와 값으로 해시 테이블에 새 노드를 삽입합니다.
 * 충돌이 발생하면, 해당 버킷의 연결 리스트의 맨 앞에 삽입하는 체이닝 방식을 사용합니다.
 */
void insert(HashTable *ht, int key, int value) {
    int index = hashFunction(ht, key);
    // 새 노드 생성
    HashNode *newNode = (HashNode*) malloc(sizeof(HashNode));
    if (newNode == NULL) {
        fprintf(stderr, "새 노드 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->value = value;
    // 새 노드를 해당 버킷의 연결 리스트 맨 앞에 삽입
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
}

/*
 * search 함수:
 * 해시 테이블에서 주어진 키를 가진 노드를 탐색합니다.
 * 발견되면 해당 노드의 포인터를 반환하며, 없으면 NULL을 반환합니다.
 */
HashNode* search(HashTable *ht, int key) {
    int index = hashFunction(ht, key);
    HashNode *current = ht->table[index];
    while (current != NULL) {
        if (current->key == key)
            return current;
        current = current->next;
    }
    return NULL;
}

/*
 * deleteKey 함수:
 * 해시 테이블에서 주어진 키를 가진 첫 번째 노드를 삭제합니다.
 */
void deleteKey(HashTable *ht, int key) {
    int index = hashFunction(ht, key);
    HashNode *current = ht->table[index];
    HashNode *prev = NULL;
    while (current != NULL) {
        if (current->key == key) {
            // 삭제할 노드를 찾았으므로 연결 리스트에서 분리
            if (prev == NULL) {
                // 삭제할 노드가 버킷의 첫 번째 노드인 경우
                ht->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("키 %d가 삭제되었습니다.\n", key);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("키 %d를 찾을 수 없습니다.\n", key);
}

/*
 * printTable 함수:
 * 해시 테이블의 모든 버킷과 그 체인(연결 리스트)을 출력합니다.
 */
void printTable(HashTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        printf("버킷 %d: ", i);
        HashNode *current = ht->table[i];
        while (current != NULL) {
            printf("-> [키: %d, 값: %d] ", current->key, current->value);
            current = current->next;
        }
        printf("-> NULL\n");
    }
}

/*
 * freeHashTable 함수:
 * 해시 테이블에 할당된 모든 메모리를 해제합니다.
 */
void freeHashTable(HashTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        HashNode *current = ht->table[i];
        while (current != NULL) {
            HashNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}