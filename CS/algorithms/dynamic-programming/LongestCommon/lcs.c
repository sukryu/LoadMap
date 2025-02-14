/**
 * lcs.c
 *
 * 고도화된 최장 공통 부분 수열 (Longest Common Subsequence, LCS) 구현 예제
 * - 이 파일은 두 문자열 간의 최장 공통 부분 수열을 동적 계획법(DP)을 통해 계산하고,
 *   재구성을 통해 실제 LCS 문자열을 출력하는 구현체입니다.
 * - DP 테이블(dp[i][j])은 문자열 X의 처음 i개와 Y의 처음 j개를 고려했을 때의 LCS 길이를 저장합니다.
 * - 점화식:
 *       if (X[i-1] == Y[j-1])
 *           dp[i][j] = dp[i-1][j-1] + 1;
 *       else
 *           dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
 *
 * 컴파일 예시: gcc -Wall -O2 lcs.c -o lcs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Utility macro to get maximum of two values
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * lcsLength - 동적 계획법을 사용하여 두 문자열 X와 Y의 최장 공통 부분 수열 길이를 계산하고,
 *             DP 테이블을 반환합니다.
 * @X: 첫 번째 문자열
 * @Y: 두 번째 문자열
 * @m: 첫 번째 문자열의 길이
 * @n: 두 번째 문자열의 길이
 *
 * 반환값: DP 테이블(2차원 배열)을 반환합니다.
 *         (반환된 배열은 호출자가 free()로 해제해야 하며, 각 행도 개별적으로 해제)
 */
int** lcsLength(const char *X, const char *Y, int m, int n) {
    int i, j;
    
    // Allocate DP table of size (m+1) x (n+1)
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (!dp) {
        fprintf(stderr, "메모리 할당 실패 (dp 테이블)\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i <= m; i++) {
        dp[i] = (int *)calloc(n + 1, sizeof(int));
        if (!dp[i]) {
            fprintf(stderr, "메모리 할당 실패 (dp[%d])\n", i);
            for (j = 0; j < i; j++)
                free(dp[j]);
            free(dp);
            exit(EXIT_FAILURE);
        }
    }
    
    // Build the dp table bottom-up
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = MAX(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    
    return dp;
}

/**
 * printLCS - 재귀적으로 DP 테이블을 따라 최장 공통 부분 수열(LCS)을 출력합니다.
 * @dp: 계산된 DP 테이블
 * @X: 첫 번째 문자열
 * @Y: 두 번째 문자열
 * @m: 첫 번째 문자열의 길이
 * @n: 두 번째 문자열의 길이
 *
 * 반환값: 동적 할당된 LCS 문자열. (호출자가 free()로 해제해야 함)
 */
char* printLCS(int **dp, const char *X, const char *Y, int m, int n) {
    // 길이: dp[m][n]
    int lcsLen = dp[m][n];
    char *lcs = (char *)malloc((lcsLen + 1) * sizeof(char));
    if (!lcs) {
        fprintf(stderr, "메모리 할당 실패 (lcs 문자열)\n");
        exit(EXIT_FAILURE);
    }
    lcs[lcsLen] = '\0';  // Null-terminate the string

    int i = m, j = n;
    int index = lcsLen - 1;
    
    // Backtrack from dp[m][n] to reconstruct LCS
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }
    return lcs;
}

/**
 * lcs - 주어진 두 문자열의 최장 공통 부분 수열(LCS)를 계산하여 반환합니다.
 * @X: 첫 번째 문자열
 * @Y: 두 번째 문자열
 *
 * 반환값: 동적 할당된 LCS 문자열 (호출자가 free()로 해제해야 함)
 */
char* lcs(const char *X, const char *Y) {
    int m = strlen(X);
    int n = strlen(Y);
    
    // Compute the DP table for LCS
    int **dp = lcsLength(X, Y, m, n);
    
    // Reconstruct the LCS from the DP table
    char *lcsStr = printLCS(dp, X, Y, m, n);
    
    // Free DP table
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return lcsStr;
}

/**
 * main - 최장 공통 부분 수열(LCS) 데모
 *
 * 이 함수는 두 문자열을 예제로 사용하여 LCS를 계산하고, 결과를 출력합니다.
 */
int main(void) {
    const char *X = "ABCBDAB";
    const char *Y = "BDCABC";
    
    char *result = lcs(X, Y);
    printf("문자열 X: %s\n", X);
    printf("문자열 Y: %s\n", Y);
    printf("최장 공통 부분 수열(LCS): %s\n", result);
    
    free(result);
    return 0;
}