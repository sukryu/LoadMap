/**
 * heap.c
 *
 * 최적화된 힙 정렬 구현 예제
 * - 배열의 요소를 오름차순으로 정렬합니다.
 * - 힙 자료구조를 이용하여 정렬을 수행하며, 최악의 경우에도 O(n log n)의 시간 복잡도를 보장합니다.
 */

#include <stdio.h>

// 두 정수의 값을 교환하는 유틸리티 함수
static inline void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 배열 arr에서 인덱스 i를 루트로 하는 서브트리를 힙화합니다. n은 배열의 크기입니다.
void heapify(int arr[], int n, int i) {
    int largest = i;          // 현재 루트를 largest로 설정
    int left = 2 * i + 1;       // 왼쪽 자식
    int right = 2 * i + 2;      // 오른쪽 자식

    // 왼쪽 자식이 존재하고, 현재 largest보다 크다면 largest 업데이트
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // 오른쪽 자식이 존재하고, 현재 largest보다 크다면 largest 업데이트
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // largest가 i와 다르면, 두 요소를 교환 후 재귀적으로 힙화 수행
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// 힙 정렬 함수: 배열 arr를 n 크기를 기준으로 오름차순 정렬합니다.
void heapSort(int arr[], int n) {
    // 1. 최대 힙 구축: 배열의 중간 인덱스부터 시작하여 모든 부모 노드에 대해 힙화 수행
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // 2. 힙에서 최대값(루트)을 하나씩 추출하여 배열의 끝으로 이동시키고, 나머지 배열에 대해 힙화 수행
    for (int i = n - 1; i > 0; i--) {
        // 현재 최대값을 배열 끝으로 이동
        swap(&arr[0], &arr[i]);
        // 힙 크기를 줄이고, 루트부터 다시 힙화
        heapify(arr, i, 0);
    }
}

// 배열의 요소를 출력하는 함수
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
         printf("%d ", arr[i]);
    }
    printf("\n");
}

// main 함수: 힙 정렬 데모
int main(void) {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    heapSort(arr, n);

    printf("Sorted array:\n");
    printArray(arr, n);

    return 0;
}