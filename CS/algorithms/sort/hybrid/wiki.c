/**
 * wiki.c
 *
 * Wiki Sort 구현 예제
 * - Wiki Sort는 안정적인(in-place) 정렬 알고리즘으로, 최소한의 추가 메모리를 사용하여 정렬을 수행합니다.
 * - 이 구현은 Wiki Sort의 기본 아이디어를 단순화한 것으로, 
 *   실제 Wiki Sort는 블록 분할 및 재배열 기법을 통해 추가 메모리 사용을 극소화합니다.
 *
 * 참고: 이 예제는 교육용으로 작성되었으며, 최적화 및 예외 처리는 간략화되어 있습니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define THRESHOLD 16  // 작은 구간에 대해서는 삽입 정렬을 사용

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

// Wiki Merge: 두 정렬된 구간을 작은 버퍼를 사용하여 병합
// 만약 왼쪽 구간의 길이가 bufferSize 이하이면 버퍼에 복사하여 병합하고,
// 그렇지 않으면 전체 왼쪽 구간을 임시 버퍼로 사용합니다.
void wikiMerge(int arr[], int left, int mid, int right, int bufferSize) {
    int leftLen = mid - left + 1;
    if (leftLen <= bufferSize) {
        int *buffer = (int*)malloc(leftLen * sizeof(int));
        if (buffer == NULL) {
            fprintf(stderr, "메모리 할당 실패\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < leftLen; i++) {
            buffer[i] = arr[left + i];
        }
        int i = 0, j = mid + 1, k = left;
        while (i < leftLen && j <= right) {
            if (buffer[i] <= arr[j])
                arr[k++] = buffer[i++];
            else
                arr[k++] = arr[j++];
        }
        while (i < leftLen) {
            arr[k++] = buffer[i++];
        }
        free(buffer);
    } else {
        int *temp = (int*)malloc(leftLen * sizeof(int));
        if (temp == NULL) {
            fprintf(stderr, "메모리 할당 실패\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < leftLen; i++) {
            temp[i] = arr[left + i];
        }
        int i = 0, j = mid + 1, k = left;
        while (i < leftLen && j <= right) {
            if (temp[i] <= arr[j])
                arr[k++] = temp[i++];
            else
                arr[k++] = arr[j++];
        }
        while (i < leftLen) {
            arr[k++] = temp[i++];
        }
        free(temp);
    }
}

// Wiki Sort: 재귀적으로 정렬 수행, 작은 구간은 삽입 정렬로 처리
void wikiSort(int arr[], int left, int right, int bufferSize) {
    if (right - left + 1 <= THRESHOLD) {
        insertionSort(arr, left, right);
        return;
    }
    int mid = left + (right - left) / 2;
    wikiSort(arr, left, mid, bufferSize);
    wikiSort(arr, mid + 1, right, bufferSize);
    wikiMerge(arr, left, mid, right, bufferSize);
}

// Wiki Sort 인터페이스 함수
void wikiSortMain(int arr[], int n) {
    // 버퍼 크기는 보통 sqrt(n) 정도로 설정 (여기서는 단순화를 위해 사용)
    int bufferSize = (int)sqrt(n);
    if (bufferSize < 1)
        bufferSize = 1;
    wikiSort(arr, 0, n - 1, bufferSize);
}

// 배열의 요소를 출력하는 함수
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
         printf("%d ", arr[i]);
    }
    printf("\n");
}

// main 함수: Wiki Sort 데모
int main(void) {
    int arr[] = {37, 23, 0, 17, 12, 72, 31, 46, 100, 88, 54};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("원본 배열:\n");
    printArray(arr, n);

    wikiSortMain(arr, n);

    printf("정렬된 배열:\n");
    printArray(arr, n);

    return 0;
}