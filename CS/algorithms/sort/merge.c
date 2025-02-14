/**
 * merge.c
 *
 * 최적화된 병합 정렬 구현 예제
 * - 배열의 요소를 오름차순으로 정렬합니다.
 * - 재귀적 분할 및 합병을 통해 안정적인 O(n log n) 성능을 보장합니다.
 */

#include <stdio.h>
#include <stdlib.h>

// 병합 정렬 함수 프로토타입 선언
void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);
void printArray(int arr[], int n);

// 병합 정렬: 배열을 재귀적으로 분할하고 합병하여 정렬
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // 중간 인덱스 계산 (오버플로우 방지)
        int mid = left + (right - left) / 2;
        // 왼쪽 부분 배열 정렬
        mergeSort(arr, left, mid);
        // 오른쪽 부분 배열 정렬
        mergeSort(arr, mid + 1, right);
        // 정렬된 두 부분 배열을 합병
        merge(arr, left, mid, right);
    }
}

// 두 정렬된 서브 배열을 합병하여 하나의 정렬된 배열로 만듭니다.
void merge(int arr[], int left, int mid, int right) {
    // 좌측과 우측 배열의 크기 계산
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // 임시 배열 동적 할당
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));
    
    // 임시 배열에 데이터 복사
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
    
    // 두 배열을 병합
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    
    // 남은 요소 복사
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
    
    // 할당한 임시 배열 해제
    free(L);
    free(R);
}

// 배열의 요소를 출력하는 함수
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// main 함수: 병합 정렬 데모
int main(void) {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array:\n");
    printArray(arr, n);
    
    mergeSort(arr, 0, n - 1);
    
    printf("Sorted array:\n");
    printArray(arr, n);
    
    return 0;
}