/**
 * time.c
 *
 * 최적화된 하이브리드 정렬(TimSort) 구현 예제
 * - 배열의 요소를 오름차순으로 정렬합니다.
 * - 작은 구간은 삽입 정렬로 정렬하고, 이후 병합 정렬 방식으로 구간을 합칩니다.
 * - 최소 구간 길이(MIN_RUN)는 데이터 특성에 따라 조정할 수 있습니다.
 *
 * 참고: 이 구현은 Python의 TimSort 알고리즘의 기본 아이디어를 단순화하여 구현한 예제입니다.
 */

#include <stdio.h>
#include <stdlib.h>

#define MIN_RUN 32

// 삽입 정렬 함수: arr[left..right] 구간을 오름차순 정렬
void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// 병합 함수: arr[l..m]와 arr[m+1..r] 두 개의 정렬된 구간을 병합
void merge(int arr[], int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    int *leftArr = (int *)malloc(len1 * sizeof(int));
    int *rightArr = (int *)malloc(len2 * sizeof(int));

    for (int i = 0; i < len1; i++) {
        leftArr[i] = arr[l + i];
    }
    for (int j = 0; j < len2; j++) {
        rightArr[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
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

// TimSort 함수: 배열 전체를 정렬
void timSort(int arr[], int n) {
    // 1단계: MIN_RUN 크기의 작은 구간들에 대해 삽입 정렬 수행
    for (int i = 0; i < n; i += MIN_RUN) {
        int right = i + MIN_RUN - 1;
        if (right >= n)
            right = n - 1;
        insertionSort(arr, i, right);
    }

    // 2단계: 정렬된 구간들을 병합하여 전체 정렬을 완성
    for (int size = MIN_RUN; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            if (mid >= n - 1)
                continue;
            int right = (left + 2 * size - 1 < n) ? left + 2 * size - 1 : n - 1;
            merge(arr, left, mid, right);
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

// main 함수: TimSort 데모
int main(void) {
    int arr[] = {5, 21, 7, 23, 19, 10, 15, 3, 8, 12, 2, 18};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("원본 배열:\n");
    printArray(arr, n);

    timSort(arr, n);

    printf("정렬된 배열:\n");
    printArray(arr, n);

    return 0;
}