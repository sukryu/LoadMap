/**
 * bubble.c
 *
 * 최적화된 버블 정렬 구현 예제
 * - 배열의 요소를 오름차순으로 정렬합니다.
 * - 내부 반복에서 swap이 발생하지 않으면 조기 종료하여 불필요한 비교를 줄입니다.
 */

#include <stdio.h>
#include <stdbool.h>

// 버블 정렬 함수: arr 배열을 n 크기 기준으로 오름차순 정렬
void bubbleSort(int arr[], int n) {
    bool swapped;
    // 전체 배열에 대해 반복
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        // 마지막 i개의 요소는 이미 정렬되어 있으므로, 그 이전까지 비교
        for (int j = 0; j < n - i - 1; j++) {
            // 현재 요소가 다음 요소보다 크면 교환
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        // 만약 내부 반복에서 한 번도 swap이 발생하지 않았다면, 배열은 이미 정렬된 상태임
        if (!swapped) {
            break;
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

// main 함수: 버블 정렬 데모
int main(void) {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    bubbleSort(arr, n);

    printf("Sorted array:\n");
    printArray(arr, n);

    return 0;
}