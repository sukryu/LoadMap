/**
 * selection.c
 *
 * 최적화된 선택 정렬 구현 예제
 * - 배열의 요소를 오름차순으로 정렬합니다.
 * - 각 단계에서 현재 위치 이후의 최소값을 선택하여 교환합니다.
 */

#include <stdio.h>

// 선택 정렬 함수: arr 배열을 n 크기 기준으로 오름차순 정렬
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // i번째 요소를 기준으로 최소값의 인덱스를 찾습니다.
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // 최소값이 현재 i번째 요소와 다르다면 교환합니다.
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

// 배열의 요소를 출력하는 함수
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// main 함수: 선택 정렬 데모
int main(void) {
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    selectionSort(arr, n);

    printf("Sorted array:\n");
    printArray(arr, n);

    return 0;
}
