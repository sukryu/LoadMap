/*
 * main.c
 *
 * 이 파일은 코딩 테스트에서 중복 원소 처리 이론을 활용하여 다양한 문제 유형을 해결하기 위한 예제 함수들을 포함합니다.
 * 아래에 제공된 함수들은 정렬된 배열에서의 중복 제거, 정렬되지 않은 배열에서 중복 존재 여부 검사,
 * 그리고 정렬되지 않은 배열에서 유일한 원소와 그 빈도를 추출하는 예제를 포함합니다.
 *
 * 각 함수는 시간 및 공간 복잡도를 고려하여 최적의 답을 제시하며, 주석을 매우 상세하게 달아서
 * 코드만 보더라도 각 알고리즘의 동작 원리와 구현 방법을 쉽게 이해할 수 있도록 작성되었습니다.
 *
 * 포함된 함수 목록:
 * 1. removeDuplicatesInPlaceSorted:
 *      - 정렬된 배열에서 in-place 방식으로 중복 원소를 제거하고, 유일한 원소의 개수를 반환합니다.
 *
 * 2. containsDuplicateUnsorted:
 *      - 정렬되지 않은 배열에 중복 원소가 존재하는지 검사합니다.
 *      - 내부적으로 qsort를 사용하여 배열을 정렬한 후 인접 원소를 비교합니다.
 *
 * 3. uniqueElementsAndFrequencies:
 *      - 정렬되지 않은 배열에서 유일한 원소들을 추출하고, 각 원소의 빈도수를 계산합니다.
 *      - 동적 할당을 통해 유일한 원소 배열과 빈도수 배열을 생성하며, caller에서 메모리 해제를 책임집니다.
 *
 * 참고: 이 파일에는 main 함수는 포함되어 있지 않으므로, 별도의 테스트 코드나 main 함수를 작성하여
 * 이 함수들을 호출 및 검증할 수 있습니다.
 */

#include <stdio.h>
#include <stdlib.h>

/* 비교 함수: qsort에서 사용될 두 정수의 비교 함수
 * 매개변수:
 *   - a, b: 비교할 두 정수에 대한 포인터 (const void*)
 * 반환값:
 *   두 정수의 차이에 따른 값 (음수, 0, 양수)
 */
int compareInt(const void *a, const void *b) {
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;
    return (int_a - int_b);
}

/*
 * 함수: removeDuplicatesInPlaceSorted
 * --------------------------------
 * 설명:
 *   정렬된 배열 arr에서 중복된 원소들을 in-place 방식으로 제거합니다.
 *   중복된 원소는 연속해서 나타나므로, 두 포인터(느린 포인터와 빠른 포인터)를 사용하여
 *   유일한 원소들을 배열의 앞부분에 재배치합니다.
 *
 * 매개변수:
 *   - arr: 정렬된 정수 배열 (오름차순)
 *   - n: 배열의 원소 개수
 *
 * 반환값:
 *   중복 제거 후 유일한 원소의 개수를 반환합니다.
 *
 * 시간 복잡도: O(n)
 * 공간 복잡도: O(1)
 */
int removeDuplicatesInPlaceSorted(int* arr, int n) {
    if (n == 0) return 0;  // 빈 배열 처리

    int slow = 0;  // 느린 포인터: 유일한 원소의 마지막 인덱스를 가리킴
    for (int fast = 1; fast < n; fast++) {
        // 빠른 포인터가 가리키는 값이 현재 유일 원소와 다르면,
        // 느린 포인터를 증가시키고 해당 값을 복사하여 유일 원소를 확장
        if (arr[fast] != arr[slow]) {
            slow++;
            arr[slow] = arr[fast];
        }
    }
    // 유일 원소의 개수는 slow 인덱스 + 1
    return slow + 1;
}

/*
 * 함수: containsDuplicateUnsorted
 * --------------------------------
 * 설명:
 *   정렬되지 않은 배열 arr에서 중복된 원소가 존재하는지 검사합니다.
 *   이 함수는 원본 배열을 수정하지 않도록 복사본을 만들어 qsort를 통해 정렬한 후,
 *   인접 원소를 비교하여 중복 여부를 확인합니다.
 *
 * 매개변수:
 *   - arr: 정렬되지 않은 정수 배열
 *   - n: 배열의 원소 개수
 *
 * 반환값:
 *   중복 원소가 존재하면 1을, 그렇지 않으면 0을 반환합니다.
 *
 * 시간 복잡도: O(n log n) (qsort에 의한 정렬 비용)
 * 공간 복잡도: O(n) (배열 복사본에 사용되는 추가 메모리)
 */
int containsDuplicateUnsorted(int* arr, int n) {
    if (n <= 1) return 0;  // 원소가 0개 또는 1개이면 중복 없음

    // 배열 복사본을 생성하여 원본을 변경하지 않음
    int* copy = (int*)malloc(n * sizeof(int));
    if (copy == NULL) {
        // 메모리 할당 실패 시, 안전하게 중복 없음으로 판단 (또는 에러 처리)
        return 0;
    }
    for (int i = 0; i < n; i++) {
        copy[i] = arr[i];
    }
    
    // qsort를 이용하여 배열 복사본 정렬
    qsort(copy, n, sizeof(int), compareInt);
    
    // 정렬된 배열에서 인접 원소 비교: 중복이 있다면 인접 원소가 동일함
    int duplicateFound = 0;
    for (int i = 1; i < n; i++) {
        if (copy[i] == copy[i - 1]) {
            duplicateFound = 1;
            break;
        }
    }
    
    free(copy);  // 동적 할당된 복사본 메모리 해제
    return duplicateFound;
}

/*
 * 함수: uniqueElementsAndFrequencies
 * --------------------------------
 * 설명:
 *   정렬되지 않은 배열 arr에서 유일한 원소들과 각 원소의 빈도수를 추출합니다.
 *   이 함수는 배열 복사본을 생성한 후 qsort를 이용하여 정렬하고,
 *   순차적으로 순회하며 유일 원소와 그 빈도를 계산합니다.
 *
 * 매개변수:
 *   - arr: 정렬되지 않은 정수 배열
 *   - n: 배열의 원소 개수
 *   - unique: 출력 매개변수, 동적 할당된 유일 원소 배열의 주소를 저장 (caller가 free)
 *   - frequencies: 출력 매개변수, 각 유일 원소의 빈도수를 저장하는 배열의 주소 (caller가 free)
 *   - uniqueCount: 출력 매개변수, 유일 원소의 개수를 저장하는 정수의 주소
 *
 * 반환값:
 *   없음. 결과는 출력 매개변수를 통해 반환됩니다.
 *
 * 시간 복잡도: O(n log n) (qsort 정렬 비용 포함)
 * 공간 복잡도: O(n) (배열 복사본과 출력 배열에 대한 추가 메모리)
 */
void uniqueElementsAndFrequencies(int* arr, int n, int** unique, int** frequencies, int* uniqueCount) {
    if (n == 0) {
        *unique = NULL;
        *frequencies = NULL;
        *uniqueCount = 0;
        return;
    }
    
    // 배열 복사본 생성 (원본 배열은 수정하지 않음)
    int* copy = (int*)malloc(n * sizeof(int));
    if (copy == NULL) return;  // 메모리 할당 실패 시, 반환 (추가 에러 처리는 caller에서)
    for (int i = 0; i < n; i++) {
        copy[i] = arr[i];
    }
    
    // 배열 복사본을 qsort로 정렬
    qsort(copy, n, sizeof(int), compareInt);
    
    // 최대 유일 원소 개수는 n (모든 원소가 다를 경우)
    int* tempUnique = (int*)malloc(n * sizeof(int));
    int* tempFreq = (int*)malloc(n * sizeof(int));
    if (tempUnique == NULL || tempFreq == NULL) {
        free(copy);
        free(tempUnique);
        free(tempFreq);
        return;
    }
    
    int count = 1;           // 현재 원소의 빈도 수 (최소 1)
    int uniqueIndex = 0;     // 유일 원소 배열의 인덱스
    // copy[0]은 첫 번째 유일 원소
    tempUnique[uniqueIndex] = copy[0];
    
    // 정렬된 배열 복사본을 순회하며 유일 원소와 빈도 수 계산
    for (int i = 1; i < n; i++) {
        if (copy[i] == copy[i - 1]) {
            // 현재 원소가 이전 원소와 같다면 빈도 증가
            count++;
        } else {
            // 다른 원소가 나오면, 이전 원소의 빈도 기록 및 새로운 유일 원소 등록
            tempFreq[uniqueIndex] = count;
            uniqueIndex++;
            tempUnique[uniqueIndex] = copy[i];
            count = 1;  // 새 원소의 빈도 초기화
        }
    }
    // 마지막 원소에 대한 빈도 기록
    tempFreq[uniqueIndex] = count;
    uniqueIndex++;  // 유일 원소의 총 개수
    
    // 결과를 출력 매개변수를 통해 반환
    *unique = tempUnique;
    *frequencies = tempFreq;
    *uniqueCount = uniqueIndex;
    
    free(copy);  // 임시 복사본 메모리 해제
}

/*
 * End of main.c
 *
 * 이 파일은 코딩 테스트에서 중복 원소 처리 기법을 활용하여 여러 문제 유형을 해결하기 위한
 * 예제 함수들을 포함합니다.
 *
 * - removeDuplicatesInPlaceSorted: 정렬된 배열에서 in-place로 중복 제거 (O(n) 시간, O(1) 공간)
 * - containsDuplicateUnsorted: 정렬되지 않은 배열에서 중복 존재 여부 검사 (O(n log n) 시간, O(n) 공간)
 * - uniqueElementsAndFrequencies: 정렬되지 않은 배열에서 유일 원소 및 빈도수 추출 (O(n log n) 시간, O(n) 공간)
 *
 * 각 함수는 상세한 주석과 함께 구현되어 있어, 코드만 보더라도 알고리즘의 동작 원리 및 시간/공간 복잡도를 쉽게 이해할 수 있습니다.
 *
 * 참고: 이 파일에는 main 함수는 포함되어 있지 않으므로, 별도의 테스트 코드나 main 함수를 작성하여
 * 이 함수들을 호출하고 검증할 수 있습니다.
 */
