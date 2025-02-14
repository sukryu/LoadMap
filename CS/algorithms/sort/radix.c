/**
 * radix.c
 *
 * 최적화된 기수 정렬 (Radix Sort) 구현 예제
 * - 배열의 요소를 오름차순으로 정렬합니다.
 * - 각 자릿수별로 안정적인 계수 정렬(Counting Sort)을 활용하여 전체 정렬을 수행합니다.
 */

#include <stdio.h>
#include <stdlib.h>

// 배열에서 최대 값을 찾아 반환하는 함수
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

// exp는 10^i (i번째 자릿수)를 의미하며, 해당 자릿수를 기준으로 배열을 정렬합니다.
void countSort(int arr[], int n, int exp) {
    int *output = (int *)malloc(n * sizeof(int));
    int count[10] = {0};

    // 각 자릿수의 발생 빈도 계산
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // count 배열을 누적 합으로 변환하여 실제 위치 계산
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // 안정적인 정렬을 위해 뒤에서부터 순회하면서 출력 배열 구성
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // 정렬된 결과를 원본 배열에 복사
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(output);
}

// 기수 정렬 함수: 배열의 모든 자릿수에 대해 계수 정렬을 수행합니다.
void radixSort(int arr[], int n) {
    // 배열의 최대값을 구하여, 정렬할 자릿수 범위를 결정합니다.
    int max = getMax(arr, n);

    // 1의 자리부터 시작해 자릿수가 있을 때까지 계수 정렬 수행
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(arr, n, exp);
    }
}

// 배열의 요소를 출력하는 유틸리티 함수
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
         printf("%d ", arr[i]);
    }
    printf("\n");
}

// main 함수: 기수 정렬 데모
int main(void) {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    radixSort(arr, n);

    printf("Sorted array:\n");
    printArray(arr, n);

    return 0;
}