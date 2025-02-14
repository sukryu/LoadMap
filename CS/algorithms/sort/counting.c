/**
 * counting.c
 *
 * 최적화된 계수 정렬 (Counting Sort) 구현 예제
 * - 배열의 요소를 오름차순으로 정렬합니다.
 * - 배열 내 요소들의 범위를 기반으로 각 요소의 등장 빈도를 계산하여 정렬합니다.
 * - 안정적인 정렬을 위해 입력 배열의 순서를 보존합니다.
 */

#include <stdio.h>
#include <stdlib.h>

// 배열의 최소값과 최대값을 찾는 함수
void findMinMax(int arr[], int n, int *min, int *max) {
    *min = arr[0];
    *max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min) {
            *min = arr[i];
        }
        if (arr[i] > *max) {
            *max = arr[i];
        }
    }
}

// 계수 정렬 함수: arr 배열을 n 크기 기준으로 오름차순 정렬
void countingSort(int arr[], int n) {
    int min, max;
    findMinMax(arr, n, &min, &max);
    
    int range = max - min + 1; // 배열 내 값의 범위
    int *count = (int *)calloc(range, sizeof(int)); // count 배열 초기화
    if (count == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    
    // 각 요소의 발생 빈도를 count 배열에 기록
    for (int i = 0; i < n; i++) {
        count[arr[i] - min]++;
    }
    
    // count 배열을 누적 합으로 변환 (안정적인 정렬을 위해)
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }
    
    // 결과를 저장할 임시 배열 생성
    int *output = (int *)malloc(n * sizeof(int));
    if (output == NULL) {
        free(count);
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    
    // 원래 배열의 요소를 역순으로 탐색하여 안정적으로 정렬된 위치에 배치
    for (int i = n - 1; i >= 0; i--) {
        int index = arr[i] - min;
        output[count[index] - 1] = arr[i];
        count[index]--;
    }
    
    // 정렬된 결과를 원본 배열에 복사
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    
    // 동적 할당한 메모리 해제
    free(count);
    free(output);
}

// 배열의 요소를 출력하는 함수
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
         printf("%d ", arr[i]);
    }
    printf("\n");
}

// main 함수: 계수 정렬 데모
int main(void) {
    int arr[] = {4, 2, -3, 6, 1, 0, -1, 3, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    countingSort(arr, n);

    printf("Sorted array:\n");
    printArray(arr, n);

    return 0;
}