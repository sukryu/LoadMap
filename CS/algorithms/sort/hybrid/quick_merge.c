/**
 * quick-merge.c
 *
 * 최적화된 Quick Merge Sort 구현 예제
 * - 배열의 요소를 오름차순으로 정렬합니다.
 * - 빠른 분할을 위해 퀵 정렬의 피벗 선택 방식을 사용하고,
 *   분할된 배열을 별도의 임시 배열에 담은 후 병합하여 안정적인 정렬을 수행합니다.
 * - 작은 구간(THRESHOLD 이하)은 삽입 정렬로 처리하여 오버헤드를 줄입니다.
 *
 * 이 구현은 추가 메모리를 사용하지만, 안정성과 성능을 동시에 고려한 하이브리드 정렬 기법의 한 예입니다.
 */

#include <stdio.h>
#include <stdlib.h>

#define THRESHOLD 16

// 삽입 정렬 함수: arr[left..right] 구간을 오름차순 정렬
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

// Quick Merge Sort 함수: 배열 arr를 n 크기를 기준으로 정렬
void quickMergeSort(int arr[], int n) {
    // 작은 구간은 삽입 정렬로 처리
    if (n <= THRESHOLD) {
        insertionSort(arr, 0, n - 1);
        return;
    }
    
    // 피벗 선택: median-of-three 방식 (첫 요소, 중간 요소, 마지막 요소)
    int mid = n / 2;
    int a = arr[0], b = arr[mid], c = arr[n - 1];
    int pivot;
    if ((a <= b && b <= c) || (c <= b && b <= a))
        pivot = b;
    else if ((b <= a && a <= c) || (c <= a && a <= b))
        pivot = a;
    else
        pivot = c;
    
    // 배열을 피벗을 기준으로 세 구간으로 분할: left (< pivot), equal (== pivot), right (> pivot)
    int leftCount = 0, equalCount = 0, rightCount = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < pivot)
            leftCount++;
        else if (arr[i] == pivot)
            equalCount++;
        else
            rightCount++;
    }
    
    // 임시 배열 할당
    int *leftArr = (int *)malloc(leftCount * sizeof(int));
    int *equalArr = (int *)malloc(equalCount * sizeof(int));
    int *rightArr = (int *)malloc(rightCount * sizeof(int));
    if (!leftArr || !equalArr || !rightArr) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    
    // 분할하여 임시 배열에 저장
    int li = 0, ei = 0, ri = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < pivot)
            leftArr[li++] = arr[i];
        else if (arr[i] == pivot)
            equalArr[ei++] = arr[i];
        else
            rightArr[ri++] = arr[i];
    }
    
    // 재귀적으로 왼쪽과 오른쪽 배열을 정렬
    quickMergeSort(leftArr, leftCount);
    quickMergeSort(rightArr, rightCount);
    
    // 병합: 정렬된 왼쪽, 피벗과 동일한 값들, 정렬된 오른쪽을 순서대로 원본 배열에 복사
    int index = 0;
    for (int i = 0; i < leftCount; i++)
        arr[index++] = leftArr[i];
    for (int i = 0; i < equalCount; i++)
        arr[index++] = equalArr[i];
    for (int i = 0; i < rightCount; i++)
        arr[index++] = rightArr[i];
    
    // 임시 배열 해제
    free(leftArr);
    free(equalArr);
    free(rightArr);
}

// 배열의 요소를 출력하는 함수
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
         printf("%d ", arr[i]);
    }
    printf("\n");
}

// main 함수: Quick Merge Sort 데모
int main(void) {
    int arr[] = {34, 7, 23, 32, 5, 62, 32, 12, 9, 45, 28, 19, 41, 50, 3, 17, 29, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("원본 배열:\n");
    printArray(arr, n);

    quickMergeSort(arr, n);

    printf("정렬된 배열:\n");
    printArray(arr, n);

    return 0;
}