/**
 * binary-advanced.c
 *
 * 이진 검색 심화 구현 예제
 * - 정렬된 배열에 중복된 값이 존재할 경우,
 *   target 값의 첫 번째 발생 위치와 마지막 발생 위치를 찾는 기능을 추가합니다.
 * - 두 가지 함수(binarySearchFirst, binarySearchLast)를 통해 각각 첫 번째와 마지막 인덱스를 반환합니다.
 */

#include <stdio.h>

// 첫 번째 발생 위치를 찾는 이진 검색 함수
int binarySearchFirst(int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;
    int result = -1;  // target이 발견되지 않을 경우 -1을 반환

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid;    // target 발견
            // 더 왼쪽에도 target이 있을 수 있으므로 검색 범위를 왼쪽으로 줄임
            right = mid - 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else { // arr[mid] > target
            right = mid - 1;
        }
    }
    return result;
}

// 마지막 발생 위치를 찾는 이진 검색 함수
int binarySearchLast(int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;
    int result = -1;  // target이 발견되지 않을 경우 -1을 반환

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid;    // target 발견
            // 더 오른쪽에도 target이 있을 수 있으므로 검색 범위를 오른쪽으로 확장
            left = mid + 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else { // arr[mid] > target
            right = mid - 1;
        }
    }
    return result;
}

// main 함수: 이진 검색 심화 데모
int main(void) {
    // 중복된 값이 포함된 정렬된 배열
    int arr[] = {1, 3, 3, 3, 5, 7, 9, 9, 11, 13};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 3;
    
    int firstIndex = binarySearchFirst(arr, n, target);
    int lastIndex = binarySearchLast(arr, n, target);
    
    if (firstIndex != -1) {
        printf("값 %d의 첫 번째 발생 위치: 인덱스 %d\n", target, firstIndex);
        printf("값 %d의 마지막 발생 위치: 인덱스 %d\n", target, lastIndex);
    } else {
        printf("값 %d를 배열에서 찾을 수 없습니다.\n", target);
    }
    
    return 0;
}