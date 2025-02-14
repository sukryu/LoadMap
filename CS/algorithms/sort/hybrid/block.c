/**
 * block.c
 *
 * 최적화된 블록 정렬 (Block Sort) 구현 예제
 * - 배열의 요소를 오름차순으로 정렬합니다.
 * - 데이터를 고정 크기의 블록으로 분할한 후, 각 블록을 삽입 정렬로 정렬합니다.
 * - 정렬된 블록들을 반복적인 병합 과정을 통해 전체 정렬을 완성합니다.
 *
 * 참고: 이 구현은 블록 기반 정렬의 간단한 형태로, 데이터가 균일하게 분포되어 있을 때
 *       캐시 최적화와 지역성을 활용하여 성능을 향상시킬 수 있습니다.
 */

#include <stdio.h>
#include <stdlib.h>

// 작은 구간에 대해 삽입 정렬을 수행하는 함수
void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 두 정렬된 구간을 병합하는 함수: arr[left..mid]와 arr[mid+1..right]를 병합
void merge(int arr[], int left, int mid, int right) {
    int len1 = mid - left + 1;
    int len2 = right - mid;
    
    int *leftArr = (int *)malloc(len1 * sizeof(int));
    int *rightArr = (int *)malloc(len2 * sizeof(int));
    
    for (int i = 0; i < len1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < len2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }
    
    int i = 0, j = 0, k = left;
    while (i < len1 && j < len2) {
        if (leftArr[i] <= rightArr[j])
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
    }
    while (i < len1) {
        arr[k++] = leftArr[i++];
    }
    while (j < len2) {
        arr[k++] = rightArr[j++];
    }
    
    free(leftArr);
    free(rightArr);
}

// 블록 정렬 함수: 배열을 블록 단위로 정렬 후 병합하여 전체 정렬을 수행
void blockSort(int arr[], int n) {
    // 블록 크기 정의 (예: 32)
    int blockSize = 32;
    
    // 1단계: 각 블록별로 삽입 정렬 수행
    for (int i = 0; i < n; i += blockSize) {
        int right = (i + blockSize - 1 < n) ? i + blockSize - 1 : n - 1;
        insertionSort(arr, i, right);
    }
    
    // 2단계: 정렬된 블록들을 반복적으로 병합하여 전체 정렬 완성
    for (int size = blockSize; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            if (mid >= n - 1)
                continue;
            int right = (left + 2 * size - 1 < n) ? left + 2 * size - 1 : n - 1;
            merge(arr, left, mid, right);
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

// main 함수: 블록 정렬 데모
int main(void) {
    int arr[] = {42, 23, 4, 16, 8, 15, 9, 55, 0, 34, 12, 3, 28, 17, 6, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("원본 배열:\n");
    printArray(arr, n);

    blockSort(arr, n);

    printf("정렬된 배열:\n");
    printArray(arr, n);

    return 0;
}