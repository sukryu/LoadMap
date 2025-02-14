/**
 * lis.c
 *
 * 고도화된 최장 증가 부분 수열 (Longest Increasing Subsequence, LIS) 구현 예제
 * - 이 파일은 주어진 배열에서 순서를 유지하면서 증가하는 부분 수열 중 길이가 가장 긴 
 *   부분 수열(LIS)을 O(n log n) 시간 복잡도로 찾는 알고리즘을 구현합니다.
 * - 이 구현은 동적 메모리 관리, 에러 처리 및 최적화된 이진 검색 기법을 사용하여, 
 *   실무에서도 바로 활용할 수 있도록 작성되었습니다.
 *
 * 알고리즘 개요:
 *   1. 배열의 각 원소에 대해, 현재까지의 증가 부분 수열의 끝 원소들을 저장하는 tailIndices 배열을 유지합니다.
 *   2. 각 원소에 대해 이진 검색(lower_bound)을 통해 tailIndices에서 교체할 위치를 찾거나, 
 *      새로운 길이의 수열로 확장합니다.
 *   3. 동시에, 각 원소의 이전 인덱스를 기록하는 prev 배열을 사용하여 최종적으로 실제 LIS를 재구성합니다.
 *
 * 컴파일 예시: gcc -Wall -O2 lis.c -o lis
 */

#include <stdio.h>
#include <stdlib.h>

// Function to perform binary search on tailIndices array
// It returns the leftmost position in tailIndices such that arr[tailIndices[pos]] >= key.
int lowerBound(int arr[], int tailIndices[], int size, int key) {
    int low = 0, high = size - 1;
    int mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (arr[tailIndices[mid]] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low;
}

/**
 * lis - 최장 증가 부분 수열(LIS)을 계산하고, 그 길이와 실제 수열을 재구성합니다.
 * @arr: 입력 배열
 * @n: 배열의 크기
 * @lisLength: 최장 증가 부분 수열의 길이를 출력하는 포인터
 *
 * 반환값: 동적 할당된 LIS 배열 (오름차순 순서로 출력).
 *         호출자가 free()로 메모리 해제해야 합니다.
 */
int* lis(int arr[], int n, int *lisLength) {
    if (n <= 0) {
        *lisLength = 0;
        return NULL;
    }

    // tailIndices[i]는 길이가 (i+1)인 증가 부분 수열의 마지막 원소의 인덱스를 저장
    int *tailIndices = (int*)malloc(n * sizeof(int));
    // prev[i]는 arr[i]가 포함된 증가 부분 수열에서 바로 이전 원소의 인덱스를 저장 (재구성에 사용)
    int *prev = (int*)malloc(n * sizeof(int));
    if (!tailIndices || !prev) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }

    // 초기화: 첫 원소로 시작
    tailIndices[0] = 0;
    prev[0] = -1;
    int length = 1; // 현재까지의 LIS 길이

    // Loop over the array to build tailIndices and prev arrays
    for (int i = 1; i < n; i++) {
        // If current element is greater than the last element of current LIS, extend the sequence
        if (arr[i] > arr[tailIndices[length - 1]]) {
            prev[i] = tailIndices[length - 1];
            tailIndices[length++] = i;
        } else {
            // Find the position to replace in tailIndices using binary search
            int pos = lowerBound(arr, tailIndices, length, arr[i]);
            tailIndices[pos] = i;
            // Update prev pointer if pos is not the first element
            prev[i] = (pos > 0) ? tailIndices[pos - 1] : -1;
        }
    }

    *lisLength = length;

    // Reconstruct the LIS sequence from tailIndices and prev arrays
    int *sequence = (int*)malloc(length * sizeof(int));
    if (!sequence) {
        fprintf(stderr, "메모리 할당 실패 (sequence)\n");
        free(tailIndices);
        free(prev);
        exit(EXIT_FAILURE);
    }
    int index = tailIndices[length - 1];
    for (int i = length - 1; i >= 0; i--) {
        sequence[i] = arr[index];
        index = prev[index];
    }

    // Cleanup temporary arrays
    free(tailIndices);
    free(prev);

    return sequence;
}

/**
 * main - 최장 증가 부분 수열 (LIS) 데모
 *
 * 이 함수는 예제 배열을 입력받아, 최장 증가 부분 수열의 길이와 실제 수열을 계산 및 출력합니다.
 */
int main(void) {
    int n;
    printf("배열의 크기 n을 입력하세요: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "유효한 n 값을 입력하세요.\n");
        return EXIT_FAILURE;
    }

    int *arr = (int*)malloc(n * sizeof(int));
    if (!arr) {
        fprintf(stderr, "메모리 할당 실패 (arr)\n");
        return EXIT_FAILURE;
    }

    printf("배열의 원소들을 입력하세요 (정수들):\n");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "유효한 정수를 입력하세요.\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }

    int lisLen;
    int *sequence = lis(arr, n, &lisLen);
    if (!sequence) {
        printf("최장 증가 부분 수열을 찾을 수 없습니다.\n");
    } else {
        printf("최장 증가 부분 수열의 길이: %d\n", lisLen);
        printf("최장 증가 부분 수열: ");
        for (int i = 0; i < lisLen; i++) {
            printf("%d ", sequence[i]);
        }
        printf("\n");
        free(sequence);
    }

    free(arr);
    return 0;
}