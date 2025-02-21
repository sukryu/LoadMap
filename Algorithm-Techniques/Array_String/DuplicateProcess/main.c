/*
 * main.c
 *
 * 이 파일은 코딩 테스트에서 중복 원소 처리와 관련된 다양한 문제를 해결하기 위한 예제 함수들을 포함합니다.
 *
 * 포함된 함수 목록:
 * 1. removeDuplicatesInPlaceSorted:
 *      - 정렬된 배열에서 in-place 방식으로 중복 원소를 제거하고, 유일한 원소의 개수를 반환합니다.
 *
 * 2. containsDuplicateUnsorted:
 *      - 정렬되지 않은 배열에서 중복 원소의 존재 여부를 검사합니다.
 *      - 배열 복사 후 qsort로 정렬하여 인접 원소를 비교합니다.
 *
 * 3. uniqueElementsAndFrequencies:
 *      - 정렬되지 않은 배열에서 유일 원소와 각 원소의 빈도수를 추출합니다.
 *
 * 4. singleNumber:
 *      - 모든 원소가 두 번 등장하고 단 한 개의 원소만 한 번 등장할 때, 한 번만 등장하는 숫자를 XOR을 이용해 찾습니다.
 *
 * 5. majorityElement:
 *      - 배열에서 전체 원소의 ⌊n/2⌋를 초과하여 나타나는 다수 원소를 Boyer-Moore Voting Algorithm으로 찾습니다.
 *
 * 6. findDuplicateIndices:
 *      - 정렬되지 않은 배열에서 중복된 원소가 있다면, 해당 원소의 첫 등장 인덱스와 이후 등장 인덱스를 찾아 반환합니다.
 *
 * 참고: 이 파일에는 main 함수는 포함되어 있지 않으므로, 별도의 테스트 코드나 main 함수를 작성하여
 *        각 함수를 호출하고 검증할 수 있습니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 비교 함수: qsort에서 사용될 두 정수의 비교 함수 */
int compareInt(const void *a, const void *b) {
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;
    return (int_a - int_b);
}

/*
 * 함수: removeDuplicatesInPlaceSorted
 * -------------------------------------
 * 정렬된 배열 arr에서 중복된 원소들을 in-place 방식으로 제거합니다.
 * 중복 원소는 연속되어 있으므로, 두 포인터(느린 포인터와 빠른 포인터)를 사용해 유일한 원소들을 배열 앞쪽으로 재배치합니다.
 */
int removeDuplicatesInPlaceSorted(int* arr, int n) {
    if (n == 0) return 0;

    int slow = 0;
    for (int fast = 1; fast < n; fast++) {
        if (arr[fast] != arr[slow]) {
            slow++;
            arr[slow] = arr[fast];
        }
    }
    return slow + 1;
}

/*
 * 함수: containsDuplicateUnsorted
 * ---------------------------------
 * 정렬되지 않은 배열 arr에서 중복 원소가 존재하는지 검사합니다.
 * 원본 배열을 복사한 뒤 qsort를 이용하여 정렬하고, 인접 원소를 비교합니다.
 */
int containsDuplicateUnsorted(int* arr, int n) {
    if (n <= 1) return 0;

    int* copy = (int*)malloc(n * sizeof(int));
    if (copy == NULL) return 0;
    for (int i = 0; i < n; i++) {
        copy[i] = arr[i];
    }

    qsort(copy, n, sizeof(int), compareInt);

    int duplicateFound = 0;
    for (int i = 1; i < n; i++) {
        if (copy[i] == copy[i - 1]) {
            duplicateFound = 1;
            break;
        }
    }
    free(copy);
    return duplicateFound;
}

/*
 * 함수: uniqueElementsAndFrequencies
 * ------------------------------------
 * 정렬되지 않은 배열 arr에서 유일 원소들과 각 원소의 빈도수를 추출합니다.
 * 결과는 출력 매개변수를 통해 반환되며, caller는 할당된 메모리를 free()로 해제해야 합니다.
 */
void uniqueElementsAndFrequencies(int* arr, int n, int** unique, int** frequencies, int* uniqueCount) {
    if (n == 0) {
        *unique = NULL;
        *frequencies = NULL;
        *uniqueCount = 0;
        return;
    }

    int* copy = (int*)malloc(n * sizeof(int));
    if (copy == NULL) return;
    for (int i = 0; i < n; i++) {
        copy[i] = arr[i];
    }
    
    qsort(copy, n, sizeof(int), compareInt);
    
    int* tempUnique = (int*)malloc(n * sizeof(int));
    int* tempFreq = (int*)malloc(n * sizeof(int));
    if (tempUnique == NULL || tempFreq == NULL) {
        free(copy);
        free(tempUnique);
        free(tempFreq);
        return;
    }
    
    int count = 1;
    int uniqueIndex = 0;
    tempUnique[uniqueIndex] = copy[0];
    for (int i = 1; i < n; i++) {
        if (copy[i] == copy[i - 1]) {
            count++;
        } else {
            tempFreq[uniqueIndex] = count;
            uniqueIndex++;
            tempUnique[uniqueIndex] = copy[i];
            count = 1;
        }
    }
    tempFreq[uniqueIndex] = count;
    uniqueIndex++;
    
    *unique = tempUnique;
    *frequencies = tempFreq;
    *uniqueCount = uniqueIndex;
    
    free(copy);
}

/*
 * 함수: singleNumber
 * --------------------
 * 주어진 배열에서 모든 요소가 두 번 등장하고 단 한 요소만 한 번 등장할 때,
 * 한 번만 등장하는 원소를 XOR 연산을 통해 찾아 반환합니다.
 */
int singleNumber(int* nums, int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result ^= nums[i];
    }
    return result;
}

/*
 * 함수: majorityElement
 * -----------------------
 * 배열에서 전체 원소의 ⌊n/2⌋보다 많이 나타나는 다수 원소를 Boyer-Moore Voting Algorithm으로 찾습니다.
 * 문제에서 다수 원소가 반드시 존재한다고 가정합니다.
 */
int majorityElement(int* nums, int n) {
    int candidate = nums[0];
    int count = 1;
    for (int i = 1; i < n; i++) {
        if (count == 0) {
            candidate = nums[i];
            count = 1;
        } else if (nums[i] == candidate) {
            count++;
        } else {
            count--;
        }
    }
    return candidate;
}

/*
 * 함수: findDuplicateIndices
 * ----------------------------
 * 정렬되지 않은 배열에서 중복된 원소가 있다면, 해당 원소의 첫 등장 인덱스와
 * 이후 등장하는 인덱스를 찾아 반환합니다.
 * 이 함수는 해시 테이블을 직접 구현하여 O(n) 시간과 O(n) 추가 공간을 사용합니다.
 *
 * 반환값:
 *   중복이 발견되면 1을, 없으면 0을 반환합니다.
 *
 * 참고:
 *   간단한 해시 테이블 구현을 위해 구조체와 연결 리스트를 사용합니다.
 */
typedef struct Node {
    int key;
    int index;
    struct Node* next;
} Node;

int hashSize = 1000;  // 간단한 해시 테이블 크기

// 간단한 정수 해시 함수
int hashFunc(int key) {
    int hash = key % hashSize;
    if (hash < 0) hash += hashSize;
    return hash;
}

int findDuplicateIndices(int* nums, int n, int* index1, int* index2) {
    Node** hashTable = (Node**)calloc(hashSize, sizeof(Node*));
    if (hashTable == NULL) return 0;

    for (int i = 0; i < n; i++) {
        int key = nums[i];
        int h = hashFunc(key);
        Node* curr = hashTable[h];
        while (curr != NULL) {
            if (curr->key == key) {
                *index1 = curr->index;
                *index2 = i;
                // 메모리 해제
                for (int j = 0; j < hashSize; j++) {
                    Node* node = hashTable[j];
                    while (node) {
                        Node* temp = node;
                        node = node->next;
                        free(temp);
                    }
                }
                free(hashTable);
                return 1;
            }
            curr = curr->next;
        }
        // 새 노드 삽입
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->index = i;
        newNode->next = hashTable[h];
        hashTable[h] = newNode;
    }

    for (int j = 0; j < hashSize; j++) {
        Node* node = hashTable[j];
        while (node) {
            Node* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(hashTable);
    return 0;
}

/*
 * End of main.c
 *
 * 이 파일은 코딩 테스트에서 중복 원소 처리와 관련된 다양한 문제들을 해결하기 위한 예제 함수들을 포함합니다.
 *
 * 포함된 함수들은 다음과 같습니다:
 *   - removeDuplicatesInPlaceSorted: 정렬된 배열에서 in-place 중복 제거 (O(n) 시간, O(1) 공간)
 *   - containsDuplicateUnsorted: 정렬되지 않은 배열에서 중복 여부 검사 (O(n log n) 시간, O(n) 공간)
 *   - uniqueElementsAndFrequencies: 정렬되지 않은 배열에서 유일 원소 및 빈도수 추출 (O(n log n) 시간, O(n) 공간)
 *   - singleNumber: XOR을 이용한 단일 숫자 찾기 (O(n) 시간, O(1) 공간)
 *   - majorityElement: Boyer-Moore Voting Algorithm을 사용한 다수 원소 찾기 (O(n) 시간, O(1) 공간)
 *   - findDuplicateIndices: 해시 테이블을 활용하여 중복 원소의 인덱스 i, j 찾기 (O(n) 시간, O(n) 공간)
 *
 * 각 함수는 상세한 주석을 통해 동작 원리와 시간/공간 복잡도를 설명하고 있으므로,
 * 코드를 통해 해당 기법들에 익숙해질 수 있습니다.
 *
 * 참고: main 함수는 포함되어 있지 않으므로, 별도의 테스트 코드나 main 함수를 작성하여
 *        이 함수들을 호출하고 검증할 수 있습니다.
 */
