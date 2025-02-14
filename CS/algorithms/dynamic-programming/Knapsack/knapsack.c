/**
 * knapsack.c
 *
 * 고도화된 0/1 배낭 문제 (Knapsack Problem) 구현 예제
 * - 이 파일은 주어진 n개의 아이템(각 아이템은 무게와 가치가 있음)과 배낭의 최대 용량 W가 주어졌을 때,
 *   배낭에 넣을 수 있는 아이템들의 조합 중 총 무게가 W 이하가 되도록 하면서 총 가치가 최대가 되는 해를 찾는 0/1 배낭 문제를
 *   동적 계획법(Dynamic Programming)을 사용하여 해결합니다.
 *
 * 주요 아이디어:
 *   - dp[i][j]를 "첫 i개의 아이템을 고려했을 때, 배낭 용량이 j일 때의 최대 가치"로 정의합니다.
 *   - 점화식: 
 *         dp[i][j] = dp[i-1][j] (아이템 i를 선택하지 않는 경우)
 *         dp[i][j] = max(dp[i-1][j], dp[i-1][j - w[i]] + v[i]) (아이템 i를 선택하는 경우, j >= w[i])
 *
 * 시간 복잡도: O(n * W)
 * 공간 복잡도: O(W) (공간 최적화를 적용한 경우)
 *
 * 컴파일 예시: gcc -Wall -O2 knapsack.c -o knapsack
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to compute maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

/**
 * knapsack - 0/1 배낭 문제를 동적 계획법을 사용하여 해결합니다.
 * @W: 배낭의 최대 용량
 * @wt: 아이템들의 무게 배열 (크기 n)
 * @val: 아이템들의 가치 배열 (크기 n)
 * @n: 아이템의 수
 *
 * 반환값: 배낭 문제의 최적해, 즉 선택된 아이템들의 최대 총 가치
 *
 * 이 구현은 공간 최적화를 위해 1차원 dp 배열을 사용합니다.
 */
int knapsack(int W, int wt[], int val[], int n) {
    // dp[j]는 현재 고려한 아이템들로 배낭 용량 j에서 얻을 수 있는 최대 가치
    int *dp = (int*)calloc(W + 1, sizeof(int));
    if (!dp) {
        fprintf(stderr, "메모리 할당 실패 (dp 배열)\n");
        exit(EXIT_FAILURE);
    }
    
    // 각 아이템에 대해 배낭 용량을 역순으로 업데이트합니다.
    for (int i = 0; i < n; i++) {
        // 무게가 W부터 wt[i]까지 역순으로 순회
        for (int j = W; j >= wt[i]; j--) {
            dp[j] = max(dp[j], dp[j - wt[i]] + val[i]);
        }
    }
    
    int result = dp[W];
    free(dp);
    return result;
}

/**
 * main - 0/1 배낭 문제 데모
 *
 * 이 함수는 예제 아이템과 배낭 용량을 입력받아, knapsack 함수를 통해
 * 최적의 가치와 선택된 아이템들의 정보를 출력합니다.
 */
int main(void) {
    int n, W;
    
    printf("배낭 문제 데모\n");
    printf("아이템의 개수 n을 입력하세요: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "유효한 n 값을 입력하세요.\n");
        return EXIT_FAILURE;
    }
    
    printf("배낭의 최대 용량 W를 입력하세요: ");
    if (scanf("%d", &W) != 1 || W < 0) {
        fprintf(stderr, "유효한 W 값을 입력하세요.\n");
        return EXIT_FAILURE;
    }
    
    int *wt = (int*)malloc(n * sizeof(int));
    int *val = (int*)malloc(n * sizeof(int));
    if (!wt || !val) {
        fprintf(stderr, "메모리 할당 실패 (wt 또는 val 배열)\n");
        free(wt);
        free(val);
        return EXIT_FAILURE;
    }
    
    printf("각 아이템의 무게와 가치를 입력하세요 (예: 무게 가치):\n");
    for (int i = 0; i < n; i++) {
        if (scanf("%d %d", &wt[i], &val[i]) != 2) {
            fprintf(stderr, "유효한 무게와 가치를 입력하세요.\n");
            free(wt);
            free(val);
            return EXIT_FAILURE;
        }
    }
    
    int maxValue = knapsack(W, wt, val, n);
    printf("최적의 총 가치: %d\n", maxValue);
    
    free(wt);
    free(val);
    return 0;
}
