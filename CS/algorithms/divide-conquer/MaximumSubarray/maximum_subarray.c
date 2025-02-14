/**
 * maximum_subarray.c
 *
 * 고도화된 Maximum Subarray Problem 구현 예제 (Kadane's Algorithm)
 * - 이 파일은 주어진 정수 배열에서 연속된 부분 배열 중 합계가 최대인 부분 배열을 찾기 위한
 *   Kadane's 알고리즘을 구현합니다.
 * - Kadane's 알고리즘은 선형 시간(O(n))에 문제를 해결할 수 있으며, 실무에서 주식 가격 분석,
 *   신호 처리, 데이터 분석 등 다양한 분야에 응용될 수 있습니다.
 *
 * 주요 아이디어:
 *   1. 배열을 한 번 순회하면서 현재까지의 최대 합(currentMax)을 갱신합니다.
 *   2. 현재 원소 자체가 현재 원소와 이전의 합을 더한 값보다 크면, 새로운 부분 배열의 시작점으로 결정합니다.
 *   3. 전체 최대 합(maxSoFar)과 현재 최대 합(currentMax)을 비교하여 최종 결과를 업데이트합니다.
 *   4. 추가적으로, 최대 부분 배열의 시작 인덱스와 종료 인덱스를 함께 추적하여, 최적 부분 배열의 위치도 제공합니다.
 *
 * 컴파일 예시: gcc -Wall -O2 maximum_subarray.c -o maximum_subarray
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 구조체: 최대 부분 배열의 결과를 저장합니다.
typedef struct {
    int maxSum;      // 최대 부분 배열의 합
    int startIndex;  // 최대 부분 배열의 시작 인덱스
    int endIndex;    // 최대 부분 배열의 종료 인덱스
} Result;

/**
 * kadane - Kadane's 알고리즘을 사용하여 최대 부분 배열을 찾습니다.
 * @arr: 정수 배열
 * @n: 배열의 크기
 *
 * 반환값: 최대 부분 배열의 합과 시작/종료 인덱스를 포함한 Result 구조체
 *
 * 동작 원리:
 *   - currentMax: 현재 부분 배열의 합
 *   - maxSoFar: 지금까지 발견한 최대 부분 배열의 합
 *   - tempStart: 현재 부분 배열의 잠재적 시작 인덱스
 *   - 최종적으로, maxSoFar, start, end를 Result에 저장하여 반환합니다.
 */
Result kadane(int arr[], int n) {
    Result res;
    
    // 초기값 설정: 배열의 첫 원소로 초기화
    int maxSoFar = arr[0];
    int currentMax = arr[0];
    int start = 0;
    int tempStart = 0;
    int end = 0;
    
    // 배열의 두 번째 원소부터 순회
    for (int i = 1; i < n; i++) {
        // 만약 현재 원소 자체가 현재 부분 배열의 합 + 현재 원소보다 크다면,
        // 새로운 부분 배열을 시작
        if (arr[i] > currentMax + arr[i]) {
            currentMax = arr[i];
            tempStart = i;
        } else {
            // 그렇지 않으면, 현재 부분 배열에 원소를 추가
            currentMax += arr[i];
        }
        
        // 현재 부분 배열의 합이 지금까지의 최대 합보다 크다면 업데이트
        if (currentMax > maxSoFar) {
            maxSoFar = currentMax;
            start = tempStart;
            end = i;
        }
    }
    
    res.maxSum = maxSoFar;
    res.startIndex = start;
    res.endIndex = end;
    return res;
}

/**
 * main - Maximum Subarray Problem 데모
 *
 * 이 함수는 예제 배열을 입력받아 Kadane's 알고리즘을 통해 최대 부분 배열의 합과
 * 해당 부분 배열의 인덱스 및 원소들을 출력합니다.
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
        fprintf(stderr, "메모리 할당 실패.\n");
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
    
    Result result = kadane(arr, n);
    printf("\n최대 부분 배열의 합: %d\n", result.maxSum);
    printf("최대 부분 배열의 인덱스 범위: [%d, %d]\n", result.startIndex, result.endIndex);
    printf("최대 부분 배열 원소들: ");
    for (int i = result.startIndex; i <= result.endIndex; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    free(arr);
    return 0;
}