/*
 * ISAM Demo
 *
 * 이 예제는 ISAM(Indexed Sequential Access Method)의 기본 동작을 시뮬레이션합니다.
 * ISAM은 정적 인덱스를 기반으로, 데이터 파일(순차 파일)과 인덱스 파일을 결합하여
 * 빠른 검색과 효율적인 순차 접근을 제공하는 저장 방식입니다.
 *
 * 이 데모에서는 두 개의 영역으로 ISAM을 모사합니다:
 *  1. Primary Area: 정렬되어 저장되는 주요 데이터 영역 (최대 MAX_PRIMARY 건)
 *  2. Overflow Area: 삽입 시 Primary Area에 즉시 반영되지 않은 레코드들을 임시 저장하는 영역 (최대 MAX_OVERFLOW 건)
 *
 * 주요 연산:
 *  - 검색 (Search): Primary Area에서 이진 검색 후, Overflow Area에서 선형 검색
 *  - 삽입 (Insertion): 키가 존재하면 업데이트, 없으면 Overflow Area에 저장; Overflow가 가득 찰 경우 재구성(Reorganization) 수행
 *  - 삭제 (Deletion): 해당 레코드를 삭제 표시 (valid 플래그 false)
 *  - 재구성 (Reorganization): Primary와 Overflow의 유효 레코드를 병합, 정렬 후 재분배
 *
 * 주의: 이 코드는 교육용 예제이며, 실제 ISAM 시스템에서는 더 복잡한 인덱스 관리 및 동기화가 필요합니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PRIMARY 10
#define MAX_OVERFLOW 5

typedef struct {
    int key;
    int value;
    bool valid;  // true: 유효, false: 삭제된 레코드
} Record;

// 전역 배열과 카운트 변수
Record primary[MAX_PRIMARY];
int primaryCount = 0;

Record overflow[MAX_OVERFLOW];
int overflowCount = 0;

/* 비교 함수: qsort용, key 기준 오름차순 정렬 */
int compareRecords(const void *a, const void *b) {
    Record *r1 = (Record *)a;
    Record *r2 = (Record *)b;
    return r1->key - r2->key;
}

/* Primary Area에서 이진 검색 수행.
 * 찾으면 해당 인덱스를, 없으면 -1을 반환.
 * 단, 삭제된 레코드(valid == false)는 무시합니다.
 */
int binarySearchPrimary(int key) {
    int left = 0, right = primaryCount - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (primary[mid].key == key) {
            if (primary[mid].valid)
                return mid;
            else
                return -1;
        } else if (primary[mid].key < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

/* Overflow Area에서 선형 검색 수행 */
int linearSearchOverflow(int key) {
    for (int i = 0; i < overflowCount; i++) {
        if (overflow[i].key == key && overflow[i].valid)
            return i;
    }
    return -1;
}

/* ISAM 검색:
 * Primary Area에서 이진 검색 후, 없으면 Overflow Area에서 선형 검색
 */
bool searchISAM(int key, int *value) {
    int idx = binarySearchPrimary(key);
    if (idx != -1) {
        *value = primary[idx].value;
        return true;
    }
    idx = linearSearchOverflow(key);
    if (idx != -1) {
        *value = overflow[idx].value;
        return true;
    }
    return false;
}

/* 재구성(Reorganization):
 * Primary와 Overflow의 유효 레코드를 병합한 후, 정렬하여
 * Primary Area와 Overflow Area를 다시 분배합니다.
 */
void reorganizeISAM() {
    int total = 0;
    int capacity = primaryCount + overflowCount;
    Record *temp = malloc(sizeof(Record) * capacity);
    if (!temp) {
        fprintf(stderr, "재구성 메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    // Primary Area에서 유효 레코드 복사
    for (int i = 0; i < primaryCount; i++) {
        if (primary[i].valid) {
            temp[total++] = primary[i];
        }
    }
    // Overflow Area에서 유효 레코드 복사
    for (int i = 0; i < overflowCount; i++) {
        if (overflow[i].valid) {
            temp[total++] = overflow[i];
        }
    }
    // 전체를 key 기준으로 정렬
    qsort(temp, total, sizeof(Record), compareRecords);
    
    // 새롭게 재분배: Primary Area는 최대 MAX_PRIMARY 건, 나머지는 Overflow에 저장
    if (total > MAX_PRIMARY) {
        primaryCount = MAX_PRIMARY;
        for (int i = 0; i < MAX_PRIMARY; i++) {
            primary[i] = temp[i];
        }
        overflowCount = total - MAX_PRIMARY;
        for (int i = 0; i < overflowCount; i++) {
            overflow[i] = temp[MAX_PRIMARY + i];
        }
    } else {
        primaryCount = total;
        for (int i = 0; i < total; i++) {
            primary[i] = temp[i];
        }
        overflowCount = 0;
    }
    free(temp);
    printf("재구성 완료. Primary: %d 건, Overflow: %d 건\n", primaryCount, overflowCount);
}

/* ISAM 삽입:
 * 이미 존재하면 업데이트, 없으면 Overflow Area에 삽입.
 * Overflow Area가 가득 차면 재구성을 수행합니다.
 */
void insertISAM(int key, int value) {
    // 존재 여부 확인 (Primary와 Overflow)
    int idx = binarySearchPrimary(key);
    if (idx != -1) {
        primary[idx].value = value;
        printf("Key %d 업데이트 (Primary Area).\n", key);
        return;
    }
    idx = linearSearchOverflow(key);
    if (idx != -1) {
        overflow[idx].value = value;
        printf("Key %d 업데이트 (Overflow Area).\n", key);
        return;
    }
    // 새 레코드 삽입: Overflow Area에 추가
    if (overflowCount < MAX_OVERFLOW) {
        overflow[overflowCount].key = key;
        overflow[overflowCount].value = value;
        overflow[overflowCount].valid = true;
        overflowCount++;
        printf("Key %d 삽입 (Overflow Area).\n", key);
    } else {
        printf("Overflow Area 가득 참. 재구성 수행...\n");
        reorganizeISAM();
        // 재구성 후에도 Primary에 빈 공간이 없으면 Overflow에 삽입
        if (overflowCount < MAX_OVERFLOW) {
            overflow[overflowCount].key = key;
            overflow[overflowCount].value = value;
            overflow[overflowCount].valid = true;
            overflowCount++;
            printf("재구성 후 Key %d 삽입 (Overflow Area).\n", key);
        } else if (primaryCount < MAX_PRIMARY) {
            // 드물게 Primary에 여유가 있으면 여기에 삽입
            primary[primaryCount].key = key;
            primary[primaryCount].value = value;
            primary[primaryCount].valid = true;
            primaryCount++;
            printf("재구성 후 Key %d 삽입 (Primary Area).\n", key);
        } else {
            printf("재구성 후에도 Key %d 삽입 불가.\n", key);
        }
    }
}

/* ISAM 삭제:
 * Primary 또는 Overflow Area에서 해당 레코드를 찾아 삭제 표시(valid = false)
 */
void deleteISAM(int key) {
    int idx = binarySearchPrimary(key);
    if (idx != -1) {
        primary[idx].valid = false;
        printf("Key %d 삭제 (Primary Area).\n", key);
        return;
    }
    idx = linearSearchOverflow(key);
    if (idx != -1) {
        overflow[idx].valid = false;
        printf("Key %d 삭제 (Overflow Area).\n", key);
        return;
    }
    printf("Key %d 삭제 실패: 존재하지 않음.\n", key);
}

/* ISAM 구조 출력: Primary Area와 Overflow Area의 내용을 표시 */
void printISAM() {
    printf("\n=== ISAM 구조 ===\n");
    printf("Primary Area (정렬됨):\n");
    for (int i = 0; i < primaryCount; i++) {
        if (primary[i].valid)
            printf("[Key: %d, Value: %d] ", primary[i].key, primary[i].value);
        else
            printf("[Key: %d, DELETED] ", primary[i].key);
    }
    printf("\nOverflow Area:\n");
    for (int i = 0; i < overflowCount; i++) {
        if (overflow[i].valid)
            printf("[Key: %d, Value: %d] ", overflow[i].key, overflow[i].value);
        else
            printf("[Key: %d, DELETED] ", overflow[i].key);
    }
    printf("\n");
}

/* --- main 함수 --- */
int main(void) {
    primaryCount = 0;
    overflowCount = 0;
    
    printf("=== ISAM Demo ===\n\n");
    
    // 삽입 테스트
    insertISAM(10, 100);
    insertISAM(20, 200);
    insertISAM(5, 50);
    insertISAM(15, 150);
    insertISAM(25, 250);
    // 현재 Primary Area는 비어있을 수 있으므로 대부분 레코드가 Overflow에 저장됨
    printISAM();
    
    // 검색 테스트
    int value;
    if (searchISAM(15, &value))
        printf("\n검색: Key 15의 값은 %d 입니다.\n", value);
    else
        printf("\n검색: Key 15를 찾을 수 없습니다.\n");
    
    if (searchISAM(30, &value))
        printf("검색: Key 30의 값은 %d 입니다.\n", value);
    else
        printf("검색: Key 30을 찾을 수 없습니다.\n");
    
    // Overflow Area 가득 차도록 추가 삽입 (재구성 트리거)
    insertISAM(30, 300);
    insertISAM(12, 120);
    insertISAM(18, 180);
    printISAM();
    
    // 삭제 테스트
    deleteISAM(15);
    deleteISAM(5);
    printISAM();
    
    // 삭제 후 추가 삽입
    insertISAM(8, 80);
    printISAM();
    
    return 0;
}