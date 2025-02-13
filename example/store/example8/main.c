#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define K_MAX 101
#define N_MAX 200001

// 구간 [start, end]의 합의 제곱을 계산하는 함수
long long get_cost(long long* prefix_sum, int start, int end) {
    long long sum = prefix_sum[end] - prefix_sum[start];
    return sum * sum;
}

// 최적의 분할 지점을 찾는 함수
void find_optimal_split(long long** dp, long long* prefix_sum, int k, int start, int end, int opt_start, int opt_end) {
    if (start > end) return;
    
    int mid = (start + end) >> 1;
    int opt_point = opt_start;
    dp[k][mid] = LLONG_MAX;
    
    // mid 지점에 대한 최적의 분할 지점 찾기
    for (int i = opt_start; i <= opt_end && i < mid; i++) {
        long long cost = dp[k-1][i] + get_cost(prefix_sum, i, mid);
        if (cost < dp[k][mid]) {
            dp[k][mid] = cost;
            opt_point = i;
        }
    }
    
    // 분할 정복으로 나머지 구간 처리
    find_optimal_split(dp, prefix_sum, k, start, mid-1, opt_start, opt_point);
    find_optimal_split(dp, prefix_sum, k, mid+1, end, opt_point, opt_end);
}

int main() {
    int N = 0, K = 0;

    if (scanf("%d %d", &N, &K) != 2) {
        fprintf(stderr, "Error: invalid input");
        exit(0);
    }
    if (N < 1 || N > N_MAX || K < 1 || K > K_MAX) {
        fprintf(stderr, "Error: Out of range");
        exit(0);
    }

    // 입력 배열 할당
    int* arr = (int *)malloc(sizeof(int) * N);
    if (arr == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory");
        exit(0);
    }

    // 누적합 배열 할당
    long long* prefix_sum = (long long *)malloc(sizeof(long long) * (N + 1));
    if (prefix_sum == NULL) {
        free(arr);
        fprintf(stderr, "Error: Failed to allocate memory");
        exit(0);
    }

    // DP 테이블 할당
    long long** dp = (long long **)malloc(sizeof(long long*) * (K + 1));
    if (dp == NULL) {
        free(arr);
        free(prefix_sum);
        fprintf(stderr, "Error: Failed to allocate memory");
        exit(0);
    }
    
    for (int i = 0; i <= K; i++) {
        dp[i] = (long long *)malloc(sizeof(long long) * (N + 1));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            free(arr);
            free(prefix_sum);
            fprintf(stderr, "Error: Failed to allocate memory");
            exit(0);
        }
    }

    // 배열 입력 받기
    for (int i = 0; i < N; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Error: invalid input");
            // 메모리 해제
            for (int j = 0; j <= K; j++) {
                free(dp[j]);
            }
            free(dp);
            free(arr);
            free(prefix_sum);
            exit(0);
        }
    }

    // 누적합 계산
    prefix_sum[0] = 0;
    for (int i = 1; i <= N; i++) {
        prefix_sum[i] = prefix_sum[i-1] + arr[i-1];
    }

    // DP 초기화
    for (int i = 0; i <= N; i++) {
        dp[0][i] = LLONG_MAX;
        dp[1][i] = get_cost(prefix_sum, 0, i);
    }
    dp[0][0] = 0;

    // DP와 분할 최적화
    for (int k = 2; k <= K; k++) {
        find_optimal_split(dp, prefix_sum, k, 0, N, 0, N);
    }

    printf("%lld\n", dp[K][N]);

    // 메모리 해제
    for (int i = 0; i <= K; i++) {
        free(dp[i]);
    }
    free(dp);
    free(arr);
    free(prefix_sum);

    return 0;
}