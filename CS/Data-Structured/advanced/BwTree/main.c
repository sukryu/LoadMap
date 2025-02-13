/*
 * Bw Tree Demo
 *
 * 이 예제는 실무에서 바로 사용할 수 있도록 고도화된 Bw Tree의 
 * 단순화된 시뮬레이션 구현 예제입니다.
 *
 * Bw Tree는 락-프리 B-트리 계열 인덱스 구조로, 매핑 테이블과 델타 레코드를
 * 활용하여 동시성을 극대화하고, 업데이트를 비파괴적으로 기록합니다.
 *
 * 본 데모에서는 단일 스레드 환경에서 기본 노드(Base Node)와 델타 레코드 체인을
 * 통해 삽입, 삭제, 업데이트, 검색 및 주기적 병합(consolidation) 기능을 시뮬레이션합니다.
 *
 * 주요 기능:
 *  - bw_tree_insert(): 새 키-값 쌍을 델타 레코드로 기록합니다.
 *  - bw_tree_delete(): 키 삭제 연산을 델타 레코드로 기록합니다.
 *  - bw_tree_update(): 키 업데이트 연산을 델타 레코드로 기록합니다.
 *  - bw_tree_search(): 기본 노드와 델타 레코드 체인을 적용하여 최신 값을 반환합니다.
 *  - consolidate_bw_tree(): 누적된 델타 레코드들을 기본 노드에 병합하여, 
 *       델타 체인을 초기화하고 검색 효율성을 회복합니다.
 *
 * 주의: 이 예제는 단순화를 위한 시뮬레이션 코드이며, 
 * 실제 락-프리 구현 및 동시성 제어, 원자적 연산, 메모리 관리 등은 별도로 구현되어야 합니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INITIAL_BASE_CAPACITY 8
#define DELTA_THRESHOLD 4   // 델타 레코드 누적 임계치에 도달하면 병합(consolidation) 수행

/* 델타 레코드 타입 */
typedef enum {
    DELTA_INSERT,
    DELTA_DELETE,
    DELTA_UPDATE
} DeltaType;

/* 델타 레코드 구조체: 모든 수정 연산을 기록 */
typedef struct DeltaRecord {
    DeltaType type;
    int key;
    int value;  // INSERT/UPDATE시 사용, DELETE시 무시
    struct DeltaRecord *next;
} DeltaRecord;

/* 기본 노드(Base Node) 구조체: 안정적인, 정렬된 키-값 배열 */
typedef struct BaseNode {
    int *keys;
    int *values;
    int count;
    int capacity;
} BaseNode;

/* Bw Tree 구조체: 하나의 기본 노드와 델타 레코드 체인을 관리 */
typedef struct BwTree {
    BaseNode *base;         // 정렬된 기본 노드
    DeltaRecord *delta;     // 델타 레코드 체인 (최신 레코드가 앞쪽에 위치)
} BwTree;

/* 함수 프로토타입 */
BwTree* create_bw_tree();
void free_bw_tree(BwTree *tree);
BaseNode* create_base_node(int capacity);
void free_base_node(BaseNode *base);
void base_node_insert(BaseNode *base, int key, int value);
int base_node_search(BaseNode *base, int key, bool *found);
void base_node_delete(BaseNode *base, int key);
void consolidate_bw_tree(BwTree *tree);
void bw_tree_insert(BwTree *tree, int key, int value);
void bw_tree_delete(BwTree *tree, int key);
void bw_tree_update(BwTree *tree, int key, int value);
bool bw_tree_search(BwTree *tree, int key, int *value);
void bw_tree_print(BwTree *tree);

/* --- Base Node Functions --- */

/* 새 기본 노드 생성 */
BaseNode* create_base_node(int capacity) {
    BaseNode *base = (BaseNode *)malloc(sizeof(BaseNode));
    if (!base) {
        fprintf(stderr, "BaseNode 메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    base->keys = (int *)malloc(sizeof(int) * capacity);
    base->values = (int *)malloc(sizeof(int) * capacity);
    if (!base->keys || !base->values) {
        fprintf(stderr, "BaseNode 배열 메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    base->count = 0;
    base->capacity = capacity;
    return base;
}

/* 기본 노드 메모리 해제 */
void free_base_node(BaseNode *base) {
    if (base) {
        free(base->keys);
        free(base->values);
        free(base);
    }
}

/* 기본 노드에 키-값 삽입 (정렬된 순서 유지) */
void base_node_insert(BaseNode *base, int key, int value) {
    // 이진 탐색으로 삽입 위치 결정 (단순 선형 탐색 사용)
    int i = 0;
    while (i < base->count && base->keys[i] < key) {
        i++;
    }
    // 키 중복이 있으면 업데이트
    if (i < base->count && base->keys[i] == key) {
        base->values[i] = value;
        return;
    }
    // 배열 확장이 필요하면 재할당
    if (base->count == base->capacity) {
        base->capacity *= 2;
        base->keys = (int *)realloc(base->keys, sizeof(int) * base->capacity);
        base->values = (int *)realloc(base->values, sizeof(int) * base->capacity);
        if (!base->keys || !base->values) {
            fprintf(stderr, "BaseNode 재할당 실패\n");
            exit(EXIT_FAILURE);
        }
    }
    // 삽입: 오른쪽으로 shift
    for (int j = base->count; j > i; j--) {
        base->keys[j] = base->keys[j-1];
        base->values[j] = base->values[j-1];
    }
    base->keys[i] = key;
    base->values[i] = value;
    base->count++;
}

/* 기본 노드에서 키 검색 */
int base_node_search(BaseNode *base, int key, bool *found) {
    int low = 0, high = base->count - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (base->keys[mid] == key) {
            *found = true;
            return base->values[mid];
        } else if (base->keys[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    *found = false;
    return -1;
}

/* 기본 노드에서 키 삭제 */
void base_node_delete(BaseNode *base, int key) {
    int i = 0;
    while (i < base->count && base->keys[i] != key) {
        i++;
    }
    if (i == base->count)
        return; // 키 없음
    // Shift left
    for (int j = i; j < base->count - 1; j++) {
        base->keys[j] = base->keys[j+1];
        base->values[j] = base->values[j+1];
    }
    base->count--;
}

/* --- Bw Tree Functions --- */

/* 새 Bw Tree 생성 */
BwTree* create_bw_tree() {
    BwTree *tree = (BwTree *)malloc(sizeof(BwTree));
    if (!tree) {
        fprintf(stderr, "BwTree 메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    tree->base = create_base_node(INITIAL_BASE_CAPACITY);
    tree->delta = NULL; // 델타 레코드 체인은 초기 비어 있음
    return tree;
}

/* Bw Tree 메모리 해제 */
void free_bw_tree(BwTree *tree) {
    if (!tree)
        return;
    // Free 델타 체인
    DeltaRecord *dr = tree->delta;
    while (dr) {
        DeltaRecord *tmp = dr;
        dr = dr->next;
        free(tmp);
    }
    free_base_node(tree->base);
    free(tree);
}

/* 새 델타 레코드 생성 */
DeltaRecord* create_delta_record(DeltaType type, int key, int value) {
    DeltaRecord *dr = (DeltaRecord *)malloc(sizeof(DeltaRecord));
    if (!dr) {
        fprintf(stderr, "DeltaRecord 메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    dr->type = type;
    dr->key = key;
    dr->value = value;
    dr->next = NULL;
    return dr;
}

/* 델타 레코드를 델타 체인 앞에 추가 */
void add_delta_record(BwTree *tree, DeltaRecord *dr) {
    dr->next = tree->delta;
    tree->delta = dr;
}

/* 
 * bw_tree_insert: 델타 레코드로 삽입 연산 기록
 * 실제 삽입은 기본 노드에 직접 반영하지 않고, 델타 체인에 기록합니다.
 * 일정 임계치(DELTA_THRESHOLD) 이상 누적되면 consolidate_bw_tree()를 호출합니다.
 */
void bw_tree_insert(BwTree *tree, int key, int value) {
    DeltaRecord *dr = create_delta_record(DELTA_INSERT, key, value);
    add_delta_record(tree, dr);
    
    // 병합 조건 체크
    int delta_count = 0;
    DeltaRecord *curr = tree->delta;
    while (curr) {
        delta_count++;
        curr = curr->next;
    }
    if (delta_count >= DELTA_THRESHOLD) {
        consolidate_bw_tree(tree);
    }
}

/* bw_tree_delete: 델타 레코드로 삭제 연산 기록 */
void bw_tree_delete(BwTree *tree, int key) {
    DeltaRecord *dr = create_delta_record(DELTA_DELETE, key, 0);
    add_delta_record(tree, dr);
    
    int delta_count = 0;
    DeltaRecord *curr = tree->delta;
    while (curr) {
        delta_count++;
        curr = curr->next;
    }
    if (delta_count >= DELTA_THRESHOLD) {
        consolidate_bw_tree(tree);
    }
}

/* bw_tree_update: 델타 레코드로 업데이트 연산 기록 */
void bw_tree_update(BwTree *tree, int key, int value) {
    DeltaRecord *dr = create_delta_record(DELTA_UPDATE, key, value);
    add_delta_record(tree, dr);
    
    int delta_count = 0;
    DeltaRecord *curr = tree->delta;
    while (curr) {
        delta_count++;
        curr = curr->next;
    }
    if (delta_count >= DELTA_THRESHOLD) {
        consolidate_bw_tree(tree);
    }
}

/*
 * bw_tree_search: 기본 노드와 델타 체인을 순차적으로 적용하여 최신 값을 반환
 * - 기본 노드에서 검색한 결과를 시작으로, 델타 체인(최신이 먼저)을 순회하며
 *   INSERT/UPDATE/DELETE 연산을 반영합니다.
 */
bool bw_tree_search(BwTree *tree, int key, int *value) {
    bool found;
    int base_val = base_node_search(tree->base, key, &found);
    // 초기 값: 기본 노드에 값이 있으면 그 값, 없으면 -1 (없음)
    int result = base_val;
    bool exists = found;
    
    // 델타 체인을 최신순으로 적용 (체인은 최신이 앞쪽에 위치)
    DeltaRecord *curr = tree->delta;
    while (curr) {
        if (curr->key == key) {
            if (curr->type == DELTA_INSERT || curr->type == DELTA_UPDATE) {
                result = curr->value;
                exists = true;
                // 최신 연산이 UPDATE/INSERT이면, 결과를 덮어씀
                break;
            } else if (curr->type == DELTA_DELETE) {
                exists = false;
                break;
            }
        }
        curr = curr->next;
    }
    
    if (exists) {
        *value = result;
        return true;
    }
    return false;
}

/*
 * consolidate_bw_tree: 델타 체인을 기본 노드에 병합(consolidation)
 * - 기본 노드의 데이터를 시작으로, 델타 체인에 기록된 모든 연산을 적용하여
 *   새로운 기본 노드를 재구성합니다.
 * - 병합 후, 델타 체인을 초기화합니다.
 */
void consolidate_bw_tree(BwTree *tree) {
    // 임시 배열로 기존 기본 데이터 복사
    int capacity = tree->base->capacity;
    int *temp_keys = (int *)malloc(sizeof(int) * capacity);
    int *temp_values = (int *)malloc(sizeof(int) * capacity);
    int count = tree->base->count;
    for (int i = 0; i < count; i++) {
        temp_keys[i] = tree->base->keys[i];
        temp_values[i] = tree->base->values[i];
    }
    
    // 적용할 델타 레코드는 최신 순서가 앞쪽에 있으므로, 역순으로 적용하여 올바른 순서를 만듦
    // 먼저 델타 레코드를 배열에 저장
    int delta_count = 0;
    DeltaRecord *curr = tree->delta;
    while (curr) {
        delta_count++;
        curr = curr->next;
    }
    DeltaRecord **deltas = (DeltaRecord **)malloc(sizeof(DeltaRecord *) * delta_count);
    curr = tree->delta;
    for (int i = 0; i < delta_count; i++) {
        deltas[i] = curr;
        curr = curr->next;
    }
    // 역순 적용: 가장 오래된 델타부터 최신까지
    for (int i = delta_count - 1; i >= 0; i--) {
        DeltaRecord *dr = deltas[i];
        bool found;
        int pos = 0;
        // 선형 탐색으로 기존 배열에서 key 위치 찾기
        while (pos < count && temp_keys[pos] < dr->key) pos++;
        
        if (dr->type == DELTA_INSERT) {
            // 중복 체크: 이미 존재하면 업데이트, 아니면 삽입
            if (pos < count && temp_keys[pos] == dr->key) {
                temp_values[pos] = dr->value;
            } else {
                // 배열 확장 필요 시 처리 (단순화를 위해 capacity 고정)
                // 오른쪽 shift 후 삽입
                for (int j = count; j > pos; j--) {
                    temp_keys[j] = temp_keys[j-1];
                    temp_values[j] = temp_values[j-1];
                }
                temp_keys[pos] = dr->key;
                temp_values[pos] = dr->value;
                count++;
            }
        } else if (dr->type == DELTA_UPDATE) {
            if (pos < count && temp_keys[pos] == dr->key) {
                temp_values[pos] = dr->value;
            }
            // 만약 존재하지 않으면, UPDATE를 INSERT로 간주할 수 있음
        } else if (dr->type == DELTA_DELETE) {
            if (pos < count && temp_keys[pos] == dr->key) {
                // 삭제: 오른쪽 shift로 삭제
                for (int j = pos; j < count - 1; j++) {
                    temp_keys[j] = temp_keys[j+1];
                    temp_values[j] = temp_values[j+1];
                }
                count--;
            }
        }
    }
    free(deltas);
    
    // 새로운 기본 노드 생성 및 교체
    BaseNode *new_base = create_base_node(capacity);
    for (int i = 0; i < count; i++) {
        base_node_insert(new_base, temp_keys[i], temp_values[i]);
    }
    free(temp_keys);
    free(temp_values);
    
    // Free 기존 기본 노드 and 델타 체인
    free_base_node(tree->base);
    tree->base = new_base;
    
    // Free 델타 체인
    curr = tree->delta;
    while (curr) {
        DeltaRecord *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    tree->delta = NULL;
    
    printf("Consolidation completed. New base node count: %d\n", tree->base->count);
}

/* bw_tree_print: 기본 노드와 델타 체인 상태 출력 */
void bw_tree_print(BwTree *tree) {
    printf("\n--- Bw Tree State ---\n");
    printf("Base Node (count = %d): ", tree->base->count);
    for (int i = 0; i < tree->base->count; i++) {
        printf("[%d:%d] ", tree->base->keys[i], tree->base->values[i]);
    }
    printf("\nDelta Chain: ");
    DeltaRecord *curr = tree->delta;
    while (curr) {
        if (curr->type == DELTA_INSERT)
            printf("(I %d:%d) -> ", curr->key, curr->value);
        else if (curr->type == DELTA_UPDATE)
            printf("(U %d:%d) -> ", curr->key, curr->value);
        else if (curr->type == DELTA_DELETE)
            printf("(D %d) -> ", curr->key);
        curr = curr->next;
    }
    printf("NULL\n");
}

/* --- main 함수 --- */
int main(void) {
    BwTree *tree = create_bw_tree();
    
    printf("=== Bw Tree Demo ===\n");
    
    // 삽입 테스트
    bw_tree_insert(tree, 50, 500);
    bw_tree_insert(tree, 30, 300);
    bw_tree_insert(tree, 70, 700);
    bw_tree_insert(tree, 20, 200);
    bw_tree_insert(tree, 40, 400);
    bw_tree_insert(tree, 60, 600);
    bw_tree_insert(tree, 80, 800);
    bw_tree_print(tree);
    
    // 검색 테스트
    int val;
    if (bw_tree_search(tree, 40, &val))
        printf("\nSearch: Key 40 found with value %d\n", val);
    else
        printf("\nSearch: Key 40 not found\n");
    
    if (bw_tree_search(tree, 90, &val))
        printf("Search: Key 90 found with value %d\n", val);
    else
        printf("Search: Key 90 not found\n");
    
    // 업데이트 테스트
    bw_tree_update(tree, 70, 750);
    bw_tree_print(tree);
    
    // 삭제 테스트
    bw_tree_delete(tree, 30);
    bw_tree_delete(tree, 60);
    bw_tree_print(tree);
    
    // 강제 consolidation (만약 델타가 누적되었으면 자동 호출되지만, 수동으로도 호출)
    consolidate_bw_tree(tree);
    bw_tree_print(tree);
    
    // 최종 검색 테스트
    if (bw_tree_search(tree, 70, &val))
        printf("\nFinal Search: Key 70 found with value %d\n", val);
    else
        printf("\nFinal Search: Key 70 not found\n");
    
    // 메모리 해제
    free_bw_tree(tree);
    
    return 0;
}