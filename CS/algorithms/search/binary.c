/**
 * binary.c
 *
 * 이진 탐색(Binary Search) 구현 예제
 * - 정렬된 배열을 대상으로 중간값을 기준으로 검색 범위를 절반씩 줄여나가며 원하는 값을 찾습니다.
 * - 찾으면 해당 인덱스를 반환하며, 찾지 못하면 -1을 반환합니다.
 */

#include <stdio.h>

// 이진 탐색 함수: 정렬된 배열 arr에서 n개의 요소 중 target 값을 찾습니다.
int binarySearch(int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;
    
    while (left <= right) {
        // 오버플로우를 방지하기 위한 중간 인덱스 계산
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid; // target 값을 발견하면 해당 인덱스를 반환
        } else if (arr[mid] < target) {
            left = mid + 1; // target이 오른쪽에 있음
        } else {
            right = mid - 1; // target이 왼쪽에 있음
        }
    }
    return -1; // target 값을 찾지 못한 경우
}

// main 함수: 이진 탐색 데모
int main(void) {
    // 정렬된 배열을 사용해야 합니다.
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 14;
    
    int index = binarySearch(arr, n, target);
    
    if (index != -1) {
        printf("값 %d를 인덱스 %d에서 찾았습니다.\n", target, index);
    } else {
        printf("값 %d를 찾을 수 없습니다.\n", target);
    }
    
    return 0;
}