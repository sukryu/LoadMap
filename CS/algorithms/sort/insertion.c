/**
 * insertion.c
 *
 * 최적화된 삽입 정렬 구현 예제
 * - 배열의 요소를 오름차순으로 정렬합니다.
 * - 각 요소를 적절한 위치에 삽입하여 정렬을 수행합니다.
 */

#include <stdio.h>

// 삽입 정렬 함수: arr 배열을 n 크기 기준으로 오름차순 정렬
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        // key보다 큰 요소들을 한 칸씩 뒤로 이동
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 배열의 요소를 출력하는 함수
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// main 함수: 삽입 정렬 데모
int main(void) {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    insertionSort(arr, n);

    printf("Sorted array:\n");
    printArray(arr, n);

    return 0;
}