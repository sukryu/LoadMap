/**
 * bucket.c
 *
 * 최적화된 버킷 정렬 (Bucket Sort) 구현 예제
 * - 배열의 요소를 오름차순으로 정렬합니다.
 * - 입력 데이터의 범위를 기반으로 여러 버킷으로 나누고, 
 *   각 버킷을 개별적으로 정렬한 후 결과를 합칩니다.
 *
 * 참고: 이 구현은 정수 배열에 대해 동작하며, 
 *       데이터 분포가 균등할 때 가장 효과적입니다.
 */

#include <stdio.h>
#include <stdlib.h>

// 버킷 구조체: 동적 배열과 현재 요소 개수, 그리고 용량을 관리합니다.
typedef struct {
    int *data;
    int count;
    int capacity;
} Bucket;

// 버킷 초기화: 초기 용량은 initCap으로 설정합니다.
void initBucket(Bucket *bucket, int initCap) {
    bucket->data = (int *)malloc(initCap * sizeof(int));
    if (bucket->data == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    bucket->count = 0;
    bucket->capacity = initCap;
}

// 버킷에 요소 추가: 용량 부족 시 재할당합니다.
void insertBucket(Bucket *bucket, int value) {
    if (bucket->count == bucket->capacity) {
        bucket->capacity *= 2;
        bucket->data = (int *)realloc(bucket->data, bucket->capacity * sizeof(int));
        if (bucket->data == NULL) {
            fprintf(stderr, "메모리 재할당 실패\n");
            exit(EXIT_FAILURE);
        }
    }
    bucket->data[bucket->count++] = value;
}

// 간단한 삽입 정렬: 버킷 내부의 배열을 오름차순으로 정렬합니다.
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 버킷 정렬 함수: 배열 arr를 n 크기를 기준으로 정렬
void bucketSort(int arr[], int n) {
    if (n <= 0) return;

    // 배열의 최소값과 최대값 찾기
    int min = arr[0], max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) 
            min = arr[i];
        if (arr[i] > max) 
            max = arr[i];
    }
    
    // 만약 모든 값이 동일하면 정렬할 필요 없음
    if (min == max)
        return;
    
    // 입력 배열 크기만큼의 버킷 생성 (최대 n개의 버킷)
    int bucketCount = n;
    Bucket *buckets = (Bucket *)malloc(bucketCount * sizeof(Bucket));
    if (buckets == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    
    // 각 버킷 초기화 (초기 용량은 10)
    for (int i = 0; i < bucketCount; i++) {
        initBucket(&buckets[i], 10);
    }
    
    // 각 요소를 적절한 버킷에 분배
    // 버킷 인덱스: 0 ~ bucketCount-1
    for (int i = 0; i < n; i++) {
        int index = (long long)(arr[i] - min) * (bucketCount - 1) / (max - min);
        insertBucket(&buckets[index], arr[i]);
    }
    
    // 각 버킷 내에서 삽입 정렬 수행
    for (int i = 0; i < bucketCount; i++) {
        if (buckets[i].count > 0) {
            insertionSort(buckets[i].data, buckets[i].count);
        }
    }
    
    // 정렬된 버킷들을 원본 배열에 병합
    int idx = 0;
    for (int i = 0; i < bucketCount; i++) {
        for (int j = 0; j < buckets[i].count; j++) {
            arr[idx++] = buckets[i].data[j];
        }
        free(buckets[i].data); // 각 버킷 동적 메모리 해제
    }
    free(buckets);
}

// 배열의 요소를 출력하는 함수
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
         printf("%d ", arr[i]);
    }
    printf("\n");
}

// main 함수: 버킷 정렬 데모
int main(void) {
    int arr[] = {29, 25, 3, 49, 9, 37, 21, 43};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    bucketSort(arr, n);

    printf("Sorted array:\n");
    printArray(arr, n);

    return 0;
}