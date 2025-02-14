/**
 * linear.c
 *
 * 순차 탐색(Linear Search) 구현 예제
 * - 배열의 첫 번째 요소부터 끝까지 순차적으로 검사하여, 원하는 값을 찾습니다.
 * - 찾으면 해당 인덱스를 반환하며, 찾지 못하면 -1을 반환합니다.
 */

#include <stdio.h>

// 순차 탐색 함수: 배열 arr에서 n개의 요소 중 target 값을 찾습니다.
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;  // target 값을 발견하면 해당 인덱스를 반환
        }
    }
    return -1;  // target 값이 없으면 -1 반환
}

// main 함수: 순차 탐색 데모
int main(void) {
    int arr[] = {3, 5, 7, 9, 11, 13};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 9;
    
    int index = linearSearch(arr, n, target);
    
    if (index != -1) {
        printf("값 %d를 인덱스 %d에서 찾았습니다.\n", target, index);
    } else {
        printf("값 %d를 찾을 수 없습니다.\n", target);
    }
    
    return 0;
}