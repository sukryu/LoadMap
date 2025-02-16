/*
 * main.c
 *
 * 이 파일은 코딩 테스트에서 정렬된 배열의 최적화를 활용하여 다양한 문제를 해결하기 위한 예제 함수들을 포함합니다.
 * 정렬된 배열의 특성을 활용하면 이진 탐색, 두 포인터 기법, 중복 제거, 병합 등 여러 최적화 기법을 적용할 수 있습니다.
 * 각 함수는 시간 및 공간 복잡도를 고려하여 최적의 답을 제시하며, 매우 상세한 주석을 포함하고 있어 코드만 보더라도
 * 알고리즘의 동작 원리와 구현 방법을 쉽게 이해할 수 있습니다.
 *
 * 포함된 함수 목록:
 * 1. binarySearch:
 *      - 정렬된 배열에서 target 값을 찾기 위한 일반적인 이진 탐색 함수.
 * 2. lowerBound:
 *      - 정렬된 배열에서 target 이상의 첫 번째 원소의 인덱스를 찾습니다.
 * 3. findFirstOccurrence:
 *      - 정렬된 배열에서 target 값의 첫 번째(최소) 인덱스를 찾습니다.
 * 4. findLastOccurrence:
 *      - 정렬된 배열에서 target 값의 마지막(최대) 인덱스를 찾습니다.
 * 5. removeDuplicatesInPlace:
 *      - 정렬된 배열에서 중복된 원소를 in-place 방식으로 제거하여 유일한 원소들만 남기고, 새로운 길이를 반환합니다.
 * 6. mergeSortedArrays:
 *      - 두 개의 정렬된 배열을 하나의 정렬된 배열로 병합합니다.
 * 7. findPairWithSum:
 *      - 정렬된 배열에서 두 수의 합이 주어진 target과 일치하는 쌍을 두 포인터 기법으로 찾습니다.
 *
 * 참고: 이 파일에는 main 함수는 포함되어 있지 않습니다.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 함수: binarySearch
 * --------------------------------
 * 설명:
 *   정렬된 배열 arr에서 target 값을 찾기 위한 이진 탐색 알고리즘입니다.
 *   배열이 정렬되어 있다는 특성을 활용하여 탐색 범위를 절반씩 줄여나감으로써
 *   O(log n)의 시간 복잡도로 target의 존재 여부 및 인덱스를 반환합니다.
 *
 * 매개변수:
 *   - arr: 정렬된 정수 배열 (오름차순)
 *   - n: 배열의 원소 개수
 *   - target: 찾고자 하는 정수 값
 *
 * 반환값:
 *   target이 존재하면 해당 인덱스를 반환하고, 그렇지 않으면 -1을 반환합니다.
 *
 * 시간 복잡도: O(log n)
 * 공간 복잡도: O(1)
 */
int binarySearch(int* arr, int n, int target) {
    int left = 0;
    int right = n - 1;
    
    while (left <= right) {
        // 중간 인덱스를 계산 (오버플로우 방지를 위해 left + (right - left) / 2 사용)
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid; // target 발견
        }
        else if (arr[mid] < target) {
            left = mid + 1; // target이 오른쪽에 있음
        }
        else {
            right = mid - 1; // target이 왼쪽에 있음
        }
    }
    
    return -1; // target이 배열 내에 없음
}

/*
 * 함수: lowerBound
 * --------------------------------
 * 설명:
 *   정렬된 배열 arr에서 target 이상의 첫 번째 원소의 인덱스를 찾습니다.
 *   만약 모든 원소가 target보다 작다면, 배열의 길이(n)를 반환합니다.
 *
 * 매개변수:
 *   - arr: 정렬된 정수 배열 (오름차순)
 *   - n: 배열의 원소 개수
 *   - target: 기준 값
 *
 * 반환값:
 *   arr[i] >= target인 가장 작은 인덱스 i를 반환합니다.
 *
 * 시간 복잡도: O(log n)
 * 공간 복잡도: O(1)
 */
int lowerBound(int* arr, int n, int target) {
    int left = 0;
    int right = n;  // right는 n으로 초기화하여 target 이상의 원소가 없는 경우 n을 반환
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

/*
 * 함수: findFirstOccurrence
 * --------------------------------
 * 설명:
 *   정렬된 배열 arr에서 target 값이 처음으로 등장하는 인덱스를 찾습니다.
 *   이 함수는 이진 탐색을 변형하여 target의 첫 번째(최소) 인덱스를 반환합니다.
 *
 * 매개변수:
 *   - arr: 정렬된 정수 배열 (오름차순)
 *   - n: 배열의 원소 개수
 *   - target: 찾고자 하는 정수 값
 *
 * 반환값:
 *   target의 첫 번째 발생 위치의 인덱스를 반환하며, 존재하지 않을 경우 -1을 반환합니다.
 *
 * 시간 복잡도: O(log n)
 * 공간 복잡도: O(1)
 */
int findFirstOccurrence(int* arr, int n, int target) {
    int index = -1;
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            index = mid;      // 현재 위치를 기록하고,
            right = mid - 1;  // 왼쪽 부분에서 더 작은 인덱스가 있는지 탐색
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return index;
}

/*
 * 함수: findLastOccurrence
 * --------------------------------
 * 설명:
 *   정렬된 배열 arr에서 target 값이 마지막으로 등장하는 인덱스를 찾습니다.
 *   이 함수는 이진 탐색을 변형하여 target의 마지막(최대) 인덱스를 반환합니다.
 *
 * 매개변수:
 *   - arr: 정렬된 정수 배열 (오름차순)
 *   - n: 배열의 원소 개수
 *   - target: 찾고자 하는 정수 값
 *
 * 반환값:
 *   target의 마지막 발생 위치의 인덱스를 반환하며, 존재하지 않을 경우 -1을 반환합니다.
 *
 * 시간 복잡도: O(log n)
 * 공간 복잡도: O(1)
 */
int findLastOccurrence(int* arr, int n, int target) {
    int index = -1;
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            index = mid;     // 현재 위치를 기록하고,
            left = mid + 1;  // 오른쪽 부분에서 더 큰 인덱스가 있는지 탐색
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return index;
}

/*
 * 함수: removeDuplicatesInPlace
 * --------------------------------
 * 설명:
 *   정렬된 배열 arr에서 중복된 원소를 in-place 방식으로 제거합니다.
 *   배열 내에서 각 원소는 한 번씩만 남게 되며, 유일한 원소들의 새 길이를 반환합니다.
 *
 * 매개변수:
 *   - arr: 정렬된 정수 배열 (중복이 있을 수 있음)
 *   - n: 배열의 원소 개수
 *
 * 반환값:
 *   중복 제거 후 배열의 새로운 길이를 반환합니다.
 *
 * 시간 복잡도: O(n)
 * 공간 복잡도: O(1)
 */
int removeDuplicatesInPlace(int* arr, int n) {
    if (n == 0) return 0;
    
    int j = 0;  // 느린 포인터: 유일한 원소가 저장될 인덱스
    for (int i = 1; i < n; i++) {
        // 현재 원소가 이전에 기록된 원소와 다르면, 중복이 아님
        if (arr[i] != arr[j]) {
            j++;           // 다음 위치로 이동 후,
            arr[j] = arr[i]; // 유일한 원소를 복사
        }
    }
    return j + 1;  // 유일한 원소의 수 (인덱스는 0부터 시작하므로 +1)
}

/*
 * 함수: mergeSortedArrays
 * --------------------------------
 * 설명:
 *   두 개의 정렬된 배열 arr1과 arr2를 하나의 정렬된 배열로 병합합니다.
 *   동적 메모리를 할당하여 결과 배열을 생성하며, caller가 메모리 해제를 책임집니다.
 *
 * 매개변수:
 *   - arr1: 첫 번째 정렬된 배열
 *   - n: arr1의 원소 개수
 *   - arr2: 두 번째 정렬된 배열
 *   - m: arr2의 원소 개수
 *
 * 반환값:
 *   병합된 정렬 배열의 포인터 (동적 할당된 메모리).
 *
 * 시간 복잡도: O(n + m)
 * 공간 복잡도: O(n + m)
 */
int* mergeSortedArrays(int* arr1, int n, int* arr2, int m) {
    // 병합된 배열의 총 길이는 n + m
    int* merged = (int*)malloc((n + m) * sizeof(int));
    if (merged == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }
    
    int i = 0, j = 0, k = 0;
    
    // 두 배열을 동시에 순회하며, 작은 원소부터 결과 배열에 삽입
    while (i < n && j < m) {
        if (arr1[i] <= arr2[j]) {
            merged[k++] = arr1[i++];
        } else {
            merged[k++] = arr2[j++];
        }
    }
    
    // 남은 원소들을 결과 배열에 복사
    while (i < n) {
        merged[k++] = arr1[i++];
    }
    while (j < m) {
        merged[k++] = arr2[j++];
    }
    
    return merged;
}

/*
 * 함수: findPairWithSum
 * --------------------------------
 * 설명:
 *   정렬된 배열 arr에서 두 수의 합이 target과 일치하는 원소 쌍을 찾습니다.
 *   두 포인터(left와 right)를 사용하여 배열의 양 끝에서 시작해 조건에 맞는 쌍을 탐색합니다.
 *
 * 매개변수:
 *   - arr: 정렬된 정수 배열
 *   - n: 배열의 원소 개수
 *   - target: 찾고자 하는 합
 *   - num1: 결과로 반환할 첫 번째 원소의 주소
 *   - num2: 결과로 반환할 두 번째 원소의 주소
 *
 * 반환값:
 *   조건을 만족하는 쌍이 있으면 1을 반환하고, 그렇지 않으면 0을 반환합니다.
 *
 * 시간 복잡도: O(n)
 * 공간 복잡도: O(1)
 */
int findPairWithSum(int* arr, int n, int target, int* num1, int* num2) {
    int left = 0;
    int right = n - 1;
    
    // 두 포인터가 서로 교차할 때까지 탐색
    while (left < right) {
        int sum = arr[left] + arr[right];
        
        if (sum == target) {
            *num1 = arr[left];
            *num2 = arr[right];
            return 1; // 쌍 발견
        }
        else if (sum < target) {
            left++;  // 합이 작으면 왼쪽 포인터 이동하여 값을 증가
        }
        else {
            right--; // 합이 크면 오른쪽 포인터 이동하여 값을 감소
        }
    }
    
    return 0; // 조건을 만족하는 쌍을 찾지 못함
}

/*
 * End of main.c
 *
 * 이 파일은 정렬된 배열에서의 최적화 기법을 활용하여 여러 문제 유형을 해결하는 예제 함수들을 포함합니다.
 * 각 함수는 상세한 주석과 함께 구현되어 있어, 코드만 보더라도 알고리즘의 동작 원리 및 시간/공간 복잡도를 쉽게 이해할 수 있습니다.
 *
 * 참고: 이 파일에는 main 함수는 포함되어 있지 않으므로,
 * 별도의 테스트 코드나 main 함수를 작성하여 이 함수들을 호출하고 검증할 수 있습니다.
 */
