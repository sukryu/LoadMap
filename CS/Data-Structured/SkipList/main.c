/*
 * main.c
 *
 * 이 파일은 스킵 리스트(Skip List) 자료구조의 고도화된 구현 예제입니다.
 * 스킵 리스트는 확률적(randomized) 자료구조로, 여러 레벨의 연결 리스트를 활용하여 
 * 정렬된 데이터에 대해 빠른 검색, 삽입, 삭제 연산을 평균 O(log n) 시간 내에 수행할 수 있습니다.
 *
 * 이 구현은 B+ Tree의 고도화된 구현 스타일을 참고하여, 
 * 다양한 레벨 관리, 동적 메모리 할당, 에러 처리 및 최적화 기법을 포함합니다.
 *
 * 주요 기능:
 * - createSkipList: 스킵 리스트를 초기화합니다.
 * - insertSkipList: 키를 스킵 리스트에 삽입합니다.
 * - searchSkipList: 키의 존재 여부를 검색합니다.
 * - deleteSkipList: 키를 스킵 리스트에서 삭제합니다.
 * - printSkipList: 각 레벨별로 스킵 리스트의 상태를 출력합니다.
 * - freeSkipList: 스킵 리스트에 할당된 메모리를 재귀적으로 해제합니다.
 *
 * 참고: 실제 환경에서는 추가적인 에러 처리, 동적 크기 조정, 스레드 안전성 등을 고려해야 합니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

// 스킵 리스트 최대 레벨과 레벨 결정 확률(P)
#define MAX_LEVEL 6
#define P 0.5

// 스킵 리스트 노드 구조체 정의
typedef struct SkipListNode {
    int key;
    // forward 배열은 각 레벨에 대한 포인터를 저장 (0부터 level-1까지)
    struct SkipListNode **forward;
} SkipListNode;

// 스킵 리스트 구조체 정의
typedef struct SkipList {
    int level;         // 현재 스킵 리스트의 최고 레벨 (0-based: level 0 ~ level)
    int size;          // 총 원소 수
    SkipListNode *header;  // 헤더 노드 (키는 최소값, 예: INT_MIN)
} SkipList;

/*
 * randomLevel 함수:
 * 확률 P에 따라 새 노드의 레벨을 결정합니다.
 * 기본적으로 레벨 1부터 시작하여, P 확률로 레벨을 1씩 증가시키며,
 * 최대 MAX_LEVEL 까지 설정합니다.
 */
int randomLevel() {
    int lvl = 1;
    while (((double)rand() / RAND_MAX) < P && lvl < MAX_LEVEL)
        lvl++;
    return lvl;
}

/*
 * createNode 함수:
 * 주어진 레벨(level)과 키(key)를 가진 스킵 리스트 노드를 생성합니다.
 * forward 배열의 크기는 level만큼 할당하며, 초기 모든 포인터는 NULL로 설정합니다.
 */
SkipListNode* createNode(int level, int key) {
    SkipListNode* node = (SkipListNode*) malloc(sizeof(SkipListNode));
    if (!node) {
        fprintf(stderr, "createNode: 메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->forward = (SkipListNode**) malloc(sizeof(SkipListNode*) * level);
    if (!node->forward) {
        fprintf(stderr, "createNode: forward 배열 메모리 할당 실패\n");
        free(node);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < level; i++) {
        node->forward[i] = NULL;
    }
    return node;
}

/*
 * createSkipList 함수:
 * 스킵 리스트를 초기화합니다.
 * 헤더 노드는 MAX_LEVEL 길이의 forward 배열을 가지며, 키는 INT_MIN으로 설정합니다.
 */
SkipList* createSkipList() {
    SkipList* list = (SkipList*) malloc(sizeof(SkipList));
    if (!list) {
        fprintf(stderr, "createSkipList: 메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    list->level = 0;
    list->size = 0;
    list->header = createNode(MAX_LEVEL, INT_MIN);
    return list;
}

/*
 * searchSkipList 함수:
 * 스킵 리스트에서 주어진 key를 검색합니다.
 * 헤더 노드부터 시작하여 상위 레벨에서 빠르게 내려오며, 
 * 해당 key가 존재하면 해당 노드의 포인터를 반환하고, 
 * 없으면 NULL을 반환합니다.
 */
SkipListNode* searchSkipList(SkipList* list, int key) {
    SkipListNode* current = list->header;
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->key < key)
            current = current->forward[i];
    }
    current = current->forward[0];
    if (current && current->key == key)
        return current;
    return NULL;
}

/*
 * insertSkipList 함수:
 * 스킵 리스트에 주어진 key를 삽입합니다.
 * 중복된 키는 삽입하지 않습니다.
 * 삽입 시, randomLevel() 함수를 통해 새 노드의 레벨을 결정하고,
 * 각 레벨에서 적절한 위치에 forward 포인터를 업데이트합니다.
 */
void insertSkipList(SkipList* list, int key) {
    SkipListNode* update[MAX_LEVEL];
    SkipListNode* current = list->header;
    
    // 각 레벨별로 삽입 위치를 찾음
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }
    current = current->forward[0];
    
    // 이미 key가 존재하면 삽입하지 않음 (중복 방지)
    if (current && current->key == key)
        return;
    
    int rlevel = randomLevel();
    if (rlevel - 1 > list->level) {
        for (int i = list->level + 1; i < rlevel; i++) {
            update[i] = list->header;
        }
        list->level = rlevel - 1;
    }
    
    // 새 노드 생성 및 삽입
    SkipListNode* newNode = createNode(rlevel, key);
    for (int i = 0; i < rlevel; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
    list->size++;
}

/*
 * deleteSkipList 함수:
 * 스킵 리스트에서 주어진 key를 삭제합니다.
 * 삭제 시, 모든 레벨에서 해당 노드를 제거하고, 
 * 필요에 따라 스킵 리스트의 레벨을 조정합니다.
 * 성공적으로 삭제되면 true, 그렇지 않으면 false를 반환합니다.
 */
bool deleteSkipList(SkipList* list, int key) {
    SkipListNode* update[MAX_LEVEL];
    SkipListNode* current = list->header;
    
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }
    current = current->forward[0];
    
    if (current && current->key == key) {
        for (int i = 0; i <= list->level; i++) {
            if (update[i]->forward[i] != current)
                break;
            update[i]->forward[i] = current->forward[i];
        }
        free(current->forward);
        free(current);
        
        // 레벨 조정: 최고 레벨에서 헤더의 forward가 NULL이면 레벨 감소
        while (list->level > 0 && list->header->forward[list->level] == NULL)
            list->level--;
        list->size--;
        return true;
    }
    return false;
}

/*
 * printSkipList 함수:
 * 스킵 리스트의 각 레벨별로 저장된 key들을 출력합니다.
 */
void printSkipList(SkipList* list) {
    printf("Skip List 구조 (최고 레벨 %d):\n", list->level);
    for (int i = list->level; i >= 0; i--) {
        SkipListNode* node = list->header->forward[i];
        printf("Level %d: ", i);
        while (node) {
            printf("%d ", node->key);
            node = node->forward[i];
        }
        printf("\n");
    }
}

/*
 * freeSkipList 함수:
 * 스킵 리스트에 할당된 모든 메모리를 해제합니다.
 */
void freeSkipList(SkipList* list) {
    SkipListNode* current = list->header;
    while (current) {
        SkipListNode* next = current->forward[0];
        free(current->forward);
        free(current);
        current = next;
    }
    free(list);
}

/*
 * main 함수:
 * 스킵 리스트의 생성, 삽입, 검색, 삭제 및 출력 연산을 시연합니다.
 */
int main(void) {
    // 난수 생성 초기화
    srand((unsigned) time(NULL));
    
    // 스킵 리스트 생성
    SkipList* list = createSkipList();
    
    // 테스트 데이터 삽입
    int keys[] = {3, 6, 7, 9, 12, 19, 17, 26, 21, 25};
    int n = sizeof(keys) / sizeof(keys[0]);
    for (int i = 0; i < n; i++) {
        insertSkipList(list, keys[i]);
        printf("Inserted: %d\n", keys[i]);
    }
    printf("\n");
    
    // 스킵 리스트 구조 출력
    printSkipList(list);
    printf("\n");
    
    // 검색 테스트
    int searchKey = 19;
    SkipListNode* result = searchSkipList(list, searchKey);
    if (result)
        printf("Search: Key %d found.\n", searchKey);
    else
        printf("Search: Key %d not found.\n", searchKey);
    printf("\n");
    
    // 삭제 테스트
    int deleteKey = 7;
    if (deleteSkipList(list, deleteKey))
        printf("Delete: Key %d deleted successfully.\n", deleteKey);
    else
        printf("Delete: Key %d not found.\n", deleteKey);
    printf("\n");
    
    // 스킵 리스트 구조 재출력
    printSkipList(list);
    printf("\n");
    
    // 메모리 해제
    freeSkipList(list);
    printf("Skip List memory freed.\n");
    
    return 0;
}