/**
 * psort.c
 *
 * 최적화된 PSort 구현 예제
 * - 배열의 요소를 오름차순으로 정렬합니다.
 * - 본 예제에서는 병렬 병합 정렬(parallel merge sort)을 활용하여,
 *   여러 코어를 활용한 병렬 정렬을 구현합니다.
 *
 * 참고: 이 구현은 OpenMP를 사용하여 병렬 태스크를 생성합니다.
 *       컴파일 시 -fopenmp 옵션을 사용해야 합니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define THRESHOLD 32  // 배열 구간의 크기가 THRESHOLD 이하이면 삽입 정렬을 사용

// 삽입 정렬: arr[left..right] 구간을 오름차순으로 정렬
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

// 두 정렬된 구간을 병합하는 함수: arr[left..mid]와 arr[mid+1..right] 병합
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int *leftArr = (int *)malloc(n1 * sizeof(int));
    int *rightArr = (int *)malloc(n2 * sizeof(int));
    
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j])
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
    }
    while (i < n1) {
        arr[k++] = leftArr[i++];
    }
    while (j < n2) {
        arr[k++] = rightArr[j++];
    }
    
    free(leftArr);
    free(rightArr);
}

// 병렬 병합 정렬 함수: arr[left..right] 구간을 정렬
void parallelMergeSort(int arr[], int left, int right) {
    if (right - left + 1 <= THRESHOLD) {
        insertionSort(arr, left, right);
        return;
    }
    
    int mid = left + (right - left) / 2;
    
    // 병렬 태스크 생성: 두 부분을 동시에 정렬
    #pragma omp task shared(arr) if (right - left > THRESHOLD)
    {
        parallelMergeSort(arr, left, mid);
    }
    #pragma omp task shared(arr) if (right - left > THRESHOLD)
    {
        parallelMergeSort(arr, mid + 1, right);
    }
    #pragma omp taskwait
    merge(arr, left, mid, right);
}

// PSort 인터페이스 함수: 전체 배열을 정렬
void pSort(int arr[], int n) {
    #pragma omp parallel
    {
        #pragma omp single
        {
            parallelMergeSort(arr, 0, n - 1);
        }
    }
}

// 배열의 요소를 출력하는 유틸리티 함수
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
         printf("%d ", arr[i]);
    }
    printf("\n");
}

// main 함수: PSort 데모
int main(void) {
    int arr[] = {45, 23, 53, 12, 87, 34, 9, 76, 41, 3, 68, 29, 100, 56};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("원본 배열:\n");
    printArray(arr, n);

    pSort(arr, n);

    printf("정렬된 배열:\n");
    printArray(arr, n);

    return 0;
}