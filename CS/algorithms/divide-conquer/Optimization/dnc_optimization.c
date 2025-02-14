/**
 * dnc_optimization.c
 *
 * 고도화된 Divide and Conquer Optimization 구현 예제
 * - 이 파일은 분할 정복 최적화 기법을 사용하여, 동적 계획법(DP)의
 *   상태 전이 점화식의 계산 시간을 줄이는 예제를 구현합니다.
 *
 * 문제 예시:
 *   주어진 배열 arr의 각 원소는 0 이상의 정수이며, 
 *   dp[i] = min{ dp[j] + cost(j, i) } (0 ≤ j < i) 를 계산합니다.
 *
 * 여기서 cost(j, i)는 누적 합의 차이의 제곱으로 정의됩니다.
 *   cost(j, i) = (prefix[i] - prefix[j])^2,
 *   단, prefix[0] = 0, prefix[i] = arr[0] + ... + arr[i-1].
 *
 * 이 점화식은 특정 모노토닉 성질(예: quadrangle inequality)을 만족할 경우,
 * Divide and Conquer Optimization을 적용하여 O(n log n) 또는 O(n)에 근접한 시간 복잡도로 계산할 수 있습니다.
 *
 * 구현 구조:
 *   - 배열 arr와 그 누적 합(prefix)을 미리 계산합니다.
 *   - dp[0] = 0, 그리고 dp[i] (1 ≤ i ≤ n) 를 재귀적으로 Divide and Conquer 방식으로 계산합니다.
 *   - 함수 compute(l, r, optL, optR)는 dp 값들을 계산하며,
 *     각 dp[mid]에 대해 최적의 전이 인덱스 k를 [optL, optR] 범위 내에서 탐색합니다.
 *
 * 컴파일 예시: gcc -Wall -O2 dnc_optimization.c -o dnc_optimization
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define INF LLONG_MAX

typedef long long ll;

// Global arrays for DP and prefix sums
ll *dp;       // dp[i] = 최적의 비용 (0 ≤ i ≤ n)
ll *prefix;   // prefix[i] = arr[0] + arr[1] + ... + arr[i-1]

// Cost function: cost(j, i) = (prefix[i] - prefix[j])^2
// Assumes 0 <= j < i.
ll cost(int j, int i) {
    ll diff = prefix[i] - prefix[j];
    return diff * diff;
}

/**
 * computeDP - Divide and Conquer Optimization을 사용하여 dp[l..r]를 계산합니다.
 * @l: dp 배열의 시작 인덱스 (l >= 1)
 * @r: dp 배열의 끝 인덱스 (r <= n)
 * @optL: 최적 전이 인덱스의 최소 범위
 * @optR: 최적 전이 인덱스의 최대 범위 (dp[i] = min{ dp[k] + cost(k, i) }에서 k 범위)
 *
 * 이 함수는 dp[mid]에 대해 최적의 전이 인덱스(opt)를 찾고,
 * 재귀적으로 왼쪽과 오른쪽 부분 문제를 해결합니다.
 */
void computeDP(int l, int r, int optL, int optR) {
    if (l > r) return;

    int mid = (l + r) / 2;
    int bestK = optL;
    dp[mid] = INF;
    // k는 dp[mid] = min_{optL <= k < mid} { dp[k] + cost(k, mid) }를 만족해야 함.
    // 최적의 k는 모노토닉성을 가지므로, [optL, min(mid, optR)] 범위 내에서만 검사하면 됩니다.
    int end = (mid < optR ? mid : optR);
    for (int k = optL; k <= end; k++) {
        ll current = dp[k] + cost(k, mid);
        if (current < dp[mid]) {
            dp[mid] = current;
            bestK = k;
        }
    }
    // 재귀 호출: 왼쪽 구간 [l, mid-1]에서 최적 전이 인덱스 범위는 [optL, bestK]
    computeDP(l, mid - 1, optL, bestK);
    // 재귀 호출: 오른쪽 구간 [mid+1, r]에서 최적 전이 인덱스 범위는 [bestK, optR]
    computeDP(mid + 1, r, bestK, optR);
}

int main(void) {
    int n;
    // 예제 입력: 배열의 크기와 배열 원소들
    printf("배열의 크기 n을 입력하세요: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "유효한 n을 입력하세요.\n");
        return EXIT_FAILURE;
    }
    int *arr = (int*)malloc(n * sizeof(int));
    if (!arr) {
        fprintf(stderr, "메모리 할당 실패 (arr)\n");
        return EXIT_FAILURE;
    }
    printf("배열의 원소들을 입력하세요 (0 이상의 정수):\n");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "유효한 정수를 입력하세요.\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }
    
    // n+1개의 dp와 prefix 배열 할당 (dp[0]부터 dp[n])
    dp = (ll*)malloc((n + 1) * sizeof(ll));
    prefix = (ll*)malloc((n + 1) * sizeof(ll));
    if (!dp || !prefix) {
        fprintf(stderr, "메모리 할당 실패 (dp 또는 prefix)\n");
        free(arr);
        exit(EXIT_FAILURE);
    }
    
    // 누적 합(prefix) 계산: prefix[0] = 0, prefix[i] = sum(arr[0..i-1])
    prefix[0] = 0;
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + arr[i - 1];
    }
    
    // DP 초기화: dp[0] = 0, 나머지는 INF
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
    }
    
    // Divide and Conquer Optimization 적용:
    // Compute dp[1..n] with optimal transition indices in [0, n-1]
    computeDP(1, n, 0, n - 1);
    
    printf("최소 비용: %lld\n", dp[n]);
    
    // Cleanup
    free(arr);
    free(dp);
    free(prefix);
    
    return 0;
}