/**
 * intro.c
 *
 * 최적화된 Introsort 구현 예제
 * - 배열의 요소를 오름차순으로 정렬합니다.
 * - 초기에는 퀵 정렬을 사용하다가, 재귀 깊이가 한계에 도달하면 힙 정렬로 전환합니다.
 * - 작은 구간에 대해서는 삽입 정렬을 적용하여 오버헤드를 줄입니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE_THRESHOLD 16  // 작은 배열 구간에 대한 임계값

// 두 정수의 값을 교환하는 유틸리티 함수
static inline void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

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

// 퀵 정렬에서 사용하는 partition 함수: 피벗을 기준으로 배열을 분할
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// 힙 정렬을 위한 max-heapify 함수: arr 배열에서 인덱스 i를 루트로 하는 서브트리를 힙화 (n은 배열 크기)
void maxHeapify(int arr[], int n, int i, int start) {
    int largest = i;
    int left = 2 * (i - start) + 1 + start;
    int right = 2 * (i - start) + 2 + start;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest, start);
    }
}

// 힙 정렬: arr[start..end] 구간을 힙 정렬로 정렬
void heapSort(int arr[], int start, int end) {
    int n = end + 1;
    // 최대 힙 구축: 내부 노드에서부터 시작
    for (int i = (start + n) / 2 - 1; i >= start; i--) {
        maxHeapify(arr, n, i, start);
    }
    // 힙 정렬: 루트(최대값)를 맨 뒤로 보내고 힙 재구성
    for (int i = end; i > start; i--) {
        swap(&arr[start], &arr[i]);
        maxHeapify(arr, i, start, start);
    }
}

// Introsort의 재귀적 유틸리티 함수
void introsortUtil(int arr[], int start, int end, int depthLimit) {
    int size = end - start + 1;
    if (size < SIZE_THRESHOLD) {
        insertionSort(arr, start, end);
        return;
    }
    if (depthLimit == 0) {
        // 깊이 제한에 도달하면 힙 정렬로 전환
        heapSort(arr, start, end);
        return;
    }
    int pivotIndex = partition(arr, start, end);
    introsortUtil(arr, start, pivotIndex - 1, depthLimit - 1);
    introsortUtil(arr, pivotIndex + 1, end, depthLimit - 1);
}

// Introsort 인터페이스: 배열 arr를 n 크기 기준으로 정렬
void introSort(int arr[], int n) {
    int depthLimit = 2 * (int)log(n);
    introsortUtil(arr, 0, n - 1, depthLimit);
}

// 배열의 요소를 출력하는 유틸리티 함수
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
         printf("%d ", arr[i]);
    }
    printf("\n");
}

// main 함수: Introsort 데모
int main(void) {
    int arr[] = {24, 97, 40, 67, 88, 85, 15, 66, 53, 44, 26, 48, 16};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("원본 배열:\n");
    printArray(arr, n);

    introSort(arr, n);

    printf("정렬된 배열:\n");
    printArray(arr, n);

    return 0;
}