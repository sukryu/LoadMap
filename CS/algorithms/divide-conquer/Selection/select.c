/**
 * selection.c
 *
 * 고도화된 Selection Algorithm 구현 예제 (QuickSelect)
 * - 이 파일은 주어진 배열에서 k번째 작은 원소(k-th smallest element)를 찾기 위한 QuickSelect 알고리즘을 구현합니다.
 * - QuickSelect는 QuickSort와 유사한 분할 정복 방식을 사용하지만, 전체 배열을 정렬하지 않고 원하는 순위의 원소만 선택적으로 찾습니다.
 * - 평균 시간 복잡도는 O(n)이며, 최악의 경우 O(n²) 시간이 소요될 수 있으나, 일반적으로 무작위 피벗 선택을 통해 효율적으로 작동합니다.
 *
 * 주요 단계:
 *   1. Partition: 배열에서 임의의 피벗을 선택하여, 피벗보다 작은 원소는 왼쪽, 큰 원소는 오른쪽으로 분할합니다.
 *   2. 재귀적 선택: 피벗의 최종 위치와 k의 관계를 이용해, 원하는 k번째 원소가 어느 쪽에 있는지 판단하고 재귀 호출합니다.
 *
 * 컴파일 예시: gcc -Wall -O2 selection.c -o selection
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * partition - 배열의 부분 구간을 분할하여 피벗을 올바른 위치에 배치합니다.
 * @arr: 정수 배열
 * @low: 시작 인덱스
 * @high: 끝 인덱스
 *
 * 반환값: 피벗의 최종 인덱스.
 *
 * 이 함수는 배열의 마지막 원소를 피벗으로 선택하고, 피벗보다 작은 원소들을 왼쪽으로,
 * 큰 원소들을 오른쪽으로 이동시킵니다.
 */
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // 피벗을 배열의 마지막 원소로 선택
    int i = low;           // i는 피벗보다 작은 원소의 경계
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            // arr[j]가 피벗보다 작으면 i와 arr[j]를 교환하고 경계를 확장합니다.
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    }
    // 마지막으로 피벗을 올바른 위치(i)로 이동합니다.
    int temp = arr[i];
    arr[i] = arr[high];
    arr[high] = temp;
    
    return i;
}

/**
 * quickSelect - QuickSelect 알고리즘을 이용하여 배열에서 k번째 작은 원소를 찾습니다.
 * @arr: 정수 배열
 * @low: 배열의 시작 인덱스
 * @high: 배열의 끝 인덱스
 * @k: 찾고자 하는 순위 (1-based index; 예: k = 1이면 최소 원소)
 *
 * 반환값: k번째 작은 원소의 값.
 *
 * 이 함수는 partition 함수를 이용하여 배열을 분할하고, 피벗의 위치와 k의 관계에 따라
 * 재귀적으로 원하는 원소를 찾습니다.
 */
int quickSelect(int arr[], int low, int high, int k) {
    // If the array contains only one element, return that element.
    if (low == high)
        return arr[low];

    // Partition the array and get the position of pivot element in sorted array
    int pivotIndex = partition(arr, low, high);

    // Number of elements on the left of pivot including pivot itself
    int count = pivotIndex - low + 1;

    // If pivot is the k-th smallest element, return its value.
    if (count == k)
        return arr[pivotIndex];
    // If k is smaller, recur for the left subarray.
    else if (k < count)
        return quickSelect(arr, low, pivotIndex - 1, k);
    // Else recur for the right subarray adjusting k accordingly.
    else
        return quickSelect(arr, pivotIndex + 1, high, k - count);
}

/**
 * main - QuickSelect 알고리즘 데모
 *
 * 이 함수는 예제 배열을 생성한 후, QuickSelect 알고리즘을 통해
 * k번째 작은 원소를 찾아 출력합니다.
 */
int main(void) {
    int arr[] = {12, 3, 5, 7, 19, 0, 2, 8, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k;
    
    printf("배열: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("찾고자 하는 k번째 작은 원소의 k를 입력하세요 (1 <= k <= %d): ", n);
    if (scanf("%d", &k) != 1 || k < 1 || k > n) {
        fprintf(stderr, "유효한 k 값을 입력하세요.\n");
        return EXIT_FAILURE;
    }
    
    int kthSmallest = quickSelect(arr, 0, n - 1, k);
    printf("배열에서 %d번째 작은 원소: %d\n", k, kthSmallest);
    
    return 0;
}