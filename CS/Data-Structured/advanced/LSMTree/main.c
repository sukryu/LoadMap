/*
 * LSM Tree Demo
 *
 * 이 예제는 LSM Tree의 기본 동작을 시뮬레이션합니다.
 * 메모테이블(Memtable)에 삽입된 데이터를 일정 임계치(MEMTABLE_THRESHOLD) 이상 모으면,
 * 디스크 기반 SSTable로 플러시하여 저장합니다.
 *
 * 주요 기능:
 *  - 삽입 (Insertion): 메모테이블에 키-값 쌍을 정렬된 상태로 저장.
 *  - 플러시 (Flush): 메모테이블이 가득 차면 SSTable로 데이터를 이동.
 *  - 검색 (Search): 메모테이블 우선, 이후 SSTable들을 순차적으로 검색.
 *  - 삭제 (Deletion): tombstone(삭제 표시)을 메모테이블에 기록하여 삭제 처리.
 *  - 컴팩션 (Compaction): 여러 SSTable을 병합하여 중복 및 삭제된 항목 제거 (시뮬레이션).
 *
 * 주의: 이 코드는 교육 및 데모 목적으로 작성된 간단한 시뮬레이션이며,
 * 실제 LSM Tree 구현에서는 더 복잡한 동기화, 에러 처리, 디스크 I/O 최적화 등이 필요합니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MEMTABLE_THRESHOLD 5    // 메모테이블 플러시 임계치

// 개별 엔트리: key, value, 삭제 여부를 표시하는 tombstone
typedef struct {
    int key;
    int value;
    bool tombstone;  // true이면 삭제된 항목임을 의미
} Entry;

// 메모테이블: 동적 배열로 구현
typedef struct {
    Entry *entries;
    int size;
    int capacity;
} MemTable;

// SSTable: 플러시된 메모테이블 데이터를 저장 (여러 SSTable을 연결 리스트로 관리)
typedef struct SSTableNode {
    Entry *entries;
    int size;
    int capacity;
    struct SSTableNode *next;
} SSTable;

// 함수 선언
void initMemTable(MemTable *mt);
void freeMemTable(MemTable *mt);
void insertMemTable(MemTable *mt, int key, int value, bool tombstone);
void sortMemTable(MemTable *mt);
void printMemTable(MemTable *mt);
SSTable* createSSTable(Entry *entries, int size);
void appendSSTable(SSTable **head, SSTable *node);
void printSSTables(SSTable *head);
void flushMemTable(MemTable *mt, SSTable **sstables);
int searchMemTable(MemTable *mt, int key, bool *found, bool *deleted);
int binarySearch(Entry *arr, int size, int key, bool *found);
int searchLSM(MemTable *mt, SSTable *sstables, int key, bool *found);
void insertLSM(MemTable *mt, SSTable **sstables, int key, int value);
void deleteLSM(MemTable *mt, SSTable **sstables, int key);
void compactSSTables(SSTable **head);

// --- MemTable Functions ---

// 초기 메모테이블 생성: 초기 capacity를 10으로 설정
void initMemTable(MemTable *mt) {
    mt->capacity = 10;
    mt->size = 0;
    mt->entries = (Entry *)malloc(sizeof(Entry) * mt->capacity);
    if (mt->entries == NULL) {
        fprintf(stderr, "메모테이블 메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
}

// 메모테이블 메모리 해제
void freeMemTable(MemTable *mt) {
    free(mt->entries);
    mt->entries = NULL;
    mt->size = 0;
    mt->capacity = 0;
}

// 메모테이블에 새로운 엔트리 삽입 (정렬 상태 유지)
// tombstone이 true이면 삭제 마커로 처리
void insertMemTable(MemTable *mt, int key, int value, bool tombstone) {
    // 메모테이블 확장 필요 시 capacity 증가
    if (mt->size >= mt->capacity) {
        mt->capacity *= 2;
        mt->entries = (Entry *)realloc(mt->entries, sizeof(Entry) * mt->capacity);
        if (mt->entries == NULL) {
            fprintf(stderr, "메모테이블 재할당 실패\n");
            exit(EXIT_FAILURE);
        }
    }
    // 단순히 마지막에 추가 후 정렬 (작은 데이터셋이므로 효율 문제 없음)
    mt->entries[mt->size].key = key;
    mt->entries[mt->size].value = value;
    mt->entries[mt->size].tombstone = tombstone;
    mt->size++;
    sortMemTable(mt);
}

// 간단한 버블 정렬로 메모테이블을 key 기준 오름차순 정렬
void sortMemTable(MemTable *mt) {
    for (int i = 0; i < mt->size - 1; i++) {
        for (int j = 0; j < mt->size - i - 1; j++) {
            if (mt->entries[j].key > mt->entries[j+1].key) {
                Entry temp = mt->entries[j];
                mt->entries[j] = mt->entries[j+1];
                mt->entries[j+1] = temp;
            }
        }
    }
}

// 메모테이블 내용 출력 (key, value, tombstone 여부)
void printMemTable(MemTable *mt) {
    printf("=== MemTable (size: %d) ===\n", mt->size);
    for (int i = 0; i < mt->size; i++) {
        printf("[Key: %d, Value: %d, %s] ", 
               mt->entries[i].key, 
               mt->entries[i].value, 
               mt->entries[i].tombstone ? "TOMBSTONE" : "VALID");
    }
    printf("\n");
}

// --- SSTable Functions ---

// 새로운 SSTable 노드 생성: entries를 복사하여 저장
SSTable* createSSTable(Entry *entries, int size) {
    SSTable *node = (SSTable *)malloc(sizeof(SSTable));
    if (node == NULL) {
        fprintf(stderr, "SSTable 노드 메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    node->capacity = size;
    node->size = size;
    node->entries = (Entry *)malloc(sizeof(Entry) * size);
    if (node->entries == NULL) {
        fprintf(stderr, "SSTable entries 메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    memcpy(node->entries, entries, sizeof(Entry) * size);
    node->next = NULL;
    return node;
}

// SSTable 연결 리스트의 끝에 새로운 노드 추가
void appendSSTable(SSTable **head, SSTable *node) {
    if (*head == NULL) {
        *head = node;
    } else {
        SSTable *curr = *head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = node;
    }
}

// SSTable 연결 리스트 내용 출력
void printSSTables(SSTable *head) {
    printf("=== SSTables ===\n");
    int tableNo = 1;
    while (head != NULL) {
        printf("SSTable %d (size: %d): ", tableNo, head->size);
        for (int i = 0; i < head->size; i++) {
            printf("[Key: %d, Value: %d, %s] ", 
                   head->entries[i].key, 
                   head->entries[i].value, 
                   head->entries[i].tombstone ? "TOMBSTONE" : "VALID");
        }
        printf("\n");
        head = head->next;
        tableNo++;
    }
}

// --- LSM Tree Operations ---

// 플러시: 메모테이블의 내용을 SSTable로 전환 후 메모테이블 초기화
void flushMemTable(MemTable *mt, SSTable **sstables) {
    if (mt->size == 0)
        return;
    // 새로운 SSTable 생성 (메모테이블은 이미 정렬되어 있음)
    SSTable *newSSTable = createSSTable(mt->entries, mt->size);
    appendSSTable(sstables, newSSTable);
    printf("MemTable 플러시: %d개의 항목이 SSTable로 이동되었습니다.\n", mt->size);
    // 메모테이블 초기화 (capacity 유지)
    mt->size = 0;
}

// 이진 검색: 정렬된 배열에서 key를 검색. found 값과 인덱스를 반환
int binarySearch(Entry *arr, int size, int key, bool *found) {
    int low = 0, high = size - 1, mid;
    *found = false;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (arr[mid].key == key) {
            *found = true;
            return mid;
        } else if (arr[mid].key < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return low; // 삽입 위치
}

// 메모테이블에서 key 검색: 삭제된 항목이면 deleted를 true로 설정
int searchMemTable(MemTable *mt, int key, bool *found, bool *deleted) {
    int idx = binarySearch(mt->entries, mt->size, key, found);
    if (*found) {
        if (mt->entries[idx].tombstone) {
            *deleted = true;
            return -1;
        } else {
            *deleted = false;
            return mt->entries[idx].value;
        }
    }
    return -1;
}

// LSM Tree 검색: 먼저 메모테이블, 그 후 최신 SSTable부터 순차적으로 검색
int searchLSM(MemTable *mt, SSTable *sstables, int key, bool *found) {
    bool del = false;
    int value = searchMemTable(mt, key, found, &del);
    if (*found && !del)
        return value;
    // 메모테이블에서 찾았으나 삭제된 경우 혹은 못찾은 경우, SSTable 검색
    SSTable *curr = sstables;
    while (curr != NULL) {
        bool f = false;
        int idx = binarySearch(curr->entries, curr->size, key, &f);
        if (f) {
            if (curr->entries[idx].tombstone) {
                *found = false;
                return -1;
            } else {
                *found = true;
                return curr->entries[idx].value;
            }
        }
        curr = curr->next;
    }
    *found = false;
    return -1;
}

// LSM Tree 삽입: 메모테이블에 삽입 후 임계치 초과 시 플러시
void insertLSM(MemTable *mt, SSTable **sstables, int key, int value) {
    insertMemTable(mt, key, value, false);
    // 임계치를 넘으면 플러시
    if (mt->size >= MEMTABLE_THRESHOLD) {
        flushMemTable(mt, sstables);
    }
}

// LSM Tree 삭제: tombstone을 메모테이블에 삽입하여 삭제 처리
void deleteLSM(MemTable *mt, SSTable **sstables, int key) {
    // 삭제 표시는 tombstone = true, value는 무시
    insertMemTable(mt, key, 0, true);
    if (mt->size >= MEMTABLE_THRESHOLD) {
        flushMemTable(mt, sstables);
    }
    printf("Key %d 삭제 요청 (tombstone 기록됨).\n", key);
}

// 간단한 컴팩션: SSTable들을 모두 병합하여 최신 값 유지
// (실제 구현에서는 각 SSTable의 타임스탬프를 고려하여 최신 데이터를 유지합니다)
void compactSSTables(SSTable **head) {
    if (*head == NULL || (*head)->next == NULL) {
        printf("컴팩션 대상 SSTable이 부족합니다.\n");
        return;
    }
    // 우선 모든 SSTable의 엔트리를 동적 배열에 복사
    int totalEntries = 0;
    SSTable *curr = *head;
    while (curr != NULL) {
        totalEntries += curr->size;
        curr = curr->next;
    }
    Entry *allEntries = (Entry *)malloc(sizeof(Entry) * totalEntries);
    if (allEntries == NULL) {
        fprintf(stderr, "컴팩션을 위한 메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    int pos = 0;
    curr = *head;
    while (curr != NULL) {
        memcpy(allEntries + pos, curr->entries, sizeof(Entry) * curr->size);
        pos += curr->size;
        curr = curr->next;
    }
    // 단순 정렬 (key 기준) - 실제 컴팩션은 더 복잡한 병합 알고리즘을 사용합니다.
    // 버블 정렬 사용 (데모 목적)
    for (int i = 0; i < totalEntries - 1; i++) {
        for (int j = 0; j < totalEntries - i - 1; j++) {
            if (allEntries[j].key > allEntries[j+1].key) {
                Entry temp = allEntries[j];
                allEntries[j] = allEntries[j+1];
                allEntries[j+1] = temp;
            }
        }
    }
    // 중복 키 및 tombstone 처리: 최신 데이터만 남김
    // 여기서는 단순하게 동일 key가 연속되면 마지막 엔트리가 최신이라 가정
    Entry *compacted = (Entry *)malloc(sizeof(Entry) * totalEntries);
    int compactedSize = 0;
    for (int i = 0; i < totalEntries; i++) {
        // 만약 다음 엔트리와 key가 동일하면 건너뛰고 마지막 값만 사용
        if (i < totalEntries - 1 && allEntries[i].key == allEntries[i+1].key)
            continue;
        // tombstone이면 실제 삭제로 간주하여 결과에 포함하지 않음
        if (!allEntries[i].tombstone) {
            compacted[compactedSize++] = allEntries[i];
        }
    }
    free(allEntries);

    // 새로운 SSTable 생성 후 기존 SSTable 리스트 해제
    SSTable *newSSTable = createSSTable(compacted, compactedSize);
    free(compacted);
    // 해제: 기존 SSTable 리스트 해제
    curr = *head;
    while (curr != NULL) {
        SSTable *temp = curr;
        curr = curr->next;
        free(temp->entries);
        free(temp);
    }
    *head = newSSTable;
    printf("컴팩션 완료: SSTable이 병합되었습니다. (새 크기: %d)\n", newSSTable->size);
}

// --- main 함수 ---
int main(void) {
    MemTable memtable;
    SSTable *sstables = NULL;
    initMemTable(&memtable);
    
    printf("=== LSM Tree Demo ===\n\n");
    
    // 삽입 테스트
    int keys_to_insert[] = {15, 10, 20, 5, 12, 25, 18, 30, 7};
    int n = sizeof(keys_to_insert) / sizeof(keys_to_insert[0]);
    for (int i = 0; i < n; i++) {
        insertLSM(&memtable, &sstables, keys_to_insert[i], keys_to_insert[i] * 100);
        printf("Inserted key %d with value %d\n", keys_to_insert[i], keys_to_insert[i]*100);
    }
    
    // 남은 메모테이블 플러시
    flushMemTable(&memtable, &sstables);
    
    printf("\n현재 상태:\n");
    printMemTable(&memtable);
    printSSTables(sstables);
    
    // 검색 테스트
    int search_keys[] = {12, 20, 100};
    int m = sizeof(search_keys) / sizeof(search_keys[0]);
    for (int i = 0; i < m; i++) {
        bool found = false;
        int val = searchLSM(&memtable, sstables, search_keys[i], &found);
        if (found)
            printf("\nSearch: Key %d found with value %d\n", search_keys[i], val);
        else
            printf("\nSearch: Key %d not found\n", search_keys[i]);
    }
    
    // 삭제 테스트
    int keys_to_delete[] = {10, 25};
    int d = sizeof(keys_to_delete) / sizeof(keys_to_delete[0]);
    for (int i = 0; i < d; i++) {
        deleteLSM(&memtable, &sstables, keys_to_delete[i]);
    }
    
    // 플러시 후 삭제 반영
    flushMemTable(&memtable, &sstables);
    
    printf("\n삭제 후 상태:\n");
    printMemTable(&memtable);
    printSSTables(sstables);
    
    // 컴팩션 테스트: SSTable 병합
    compactSSTables(&sstables);
    printSSTables(sstables);
    
    // 최종 검색 테스트 (삭제된 키 확인)
    for (int i = 0; i < d; i++) {
        bool found = false;
        int val = searchLSM(&memtable, sstables, keys_to_delete[i], &found);
        if (found)
            printf("\nAfter compaction: Key %d found with value %d\n", keys_to_delete[i], val);
        else
            printf("\nAfter compaction: Key %d not found (deleted)\n", keys_to_delete[i]);
    }
    
    // 메모리 해제
    freeMemTable(&memtable);
    // SSTable 리스트 해제
    while (sstables != NULL) {
        SSTable *temp = sstables;
        sstables = sstables->next;
        free(temp->entries);
        free(temp);
    }
    
    return 0;
}