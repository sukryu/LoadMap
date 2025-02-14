/**
 * quick.c
 *
 * 최적화된 퀵 정렬 구현 예제
 * - 배열의 요소를 오름차순으로 정렬합니다.
 * - median-of-three 기법을 사용해 피벗을 선택하고, 분할 후 재귀 호출을 수행합니다.
 */

#include <stdio.h>
#include <stdlib.h>

// 두 정수의 값을 교환하는 유틸리티 함수
static inline void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// median-of-three 기법을 사용하여 low, mid, high 값 중 중앙값의 인덱스를 반환합니다.
int medianOfThree(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid])
        swap(&arr[low], &arr[mid]);
    if (arr[low] > arr[high])
        swap(&arr[low], &arr[high]);
    if (arr[mid] > arr[high])
        swap(&arr[mid], &arr[high]);
    // 중앙값이 pivot으로 선택되며, 이후 high 위치와 교환하여 사용합니다.
    return mid;
}

// 배열을 분할하고 피벗의 최종 위치를 반환하는 partition 함수
int partition(int arr[], int low, int high) {
    // median-of-three를 통해 피벗 인덱스 선택 및 high 위치로 이동
    int pivotIndex = medianOfThree(arr, low, high);
    swap(&arr[pivotIndex], &arr[high]);
    int pivot = arr[high];

    int i = low - 1;
    for (int j = low; j < high; j++) {
        // 피벗보다 작은 요소들을 왼쪽으로 이동
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    // 피벗을 올바른 위치로 이동
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// 퀵 정렬 함수: 배열의 low부터 high까지 정렬
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 배열의 요소를 출력하는 함수
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
         printf("%d ", arr[i]);
    }
    printf("\n");
}

// main 함수: 퀵 정렬 데모
int main(void) {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array:\n");
    printArray(arr, n);
    
    quickSort(arr, 0, n - 1);
    
    printf("Sorted array:\n");
    printArray(arr, n);
    
    return 0;
}