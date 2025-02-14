/**
 * lps.c
 *
 * 고도화된 최장 팰린드롬 부분 수열 (Longest Palindromic Subsequence, LPS) 구현 예제
 * - 이 파일은 입력된 문자열에서 최장 팰린드롬 부분 수열의 길이를 계산하고,
 *   동적 계획법(DP)을 사용하여 실제 LPS 문자열을 재구성합니다.
 *
 * 알고리즘 개요:
 *   1. dp[i][j]는 문자열의 부분 문자열 s[i..j]에서의 LPS 길이를 저장합니다.
 *   2. 점화식:
 *         if (i == j)
 *              dp[i][j] = 1;
 *         else if (s[i] == s[j] && i + 1 == j)
 *              dp[i][j] = 2;
 *         else if (s[i] == s[j])
 *              dp[i][j] = dp[i+1][j-1] + 2;
 *         else
 *              dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
 *   3. dp 테이블을 채운 후, 양 끝에서 시작하여 재귀적으로(또는 반복적으로) LPS 문자열을 재구성합니다.
 *
 * 컴파일 예시: gcc -Wall -O2 lps.c -o lps
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Utility macro for maximum of two integers
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * lpsLength - 주어진 문자열 s의 최장 팰린드롬 부분 수열의 길이를 계산하고,
 *             DP 테이블을 채웁니다.
 * @s: 입력 문자열
 * @n: 문자열의 길이
 *
 * 반환값: dp 테이블 (n x n 2차원 배열), 각 dp[i][j]는 s[i..j]의 LPS 길이를 저장.
 *         (반환된 dp 배열은 호출자가 free()로 해제해야 합니다.)
 */
int **lpsLength(const char *s, int n) {
    int **dp = (int **)malloc(n * sizeof(int *));
    if (!dp) {
        fprintf(stderr, "메모리 할당 실패 (dp 테이블)\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        dp[i] = (int *)calloc(n, sizeof(int));
        if (!dp[i]) {
            fprintf(stderr, "메모리 할당 실패 (dp[%d])\n", i);
            for (int k = 0; k < i; k++) free(dp[k]);
            free(dp);
            exit(EXIT_FAILURE);
        }
    }

    // 기저 사례: 한 문자로 구성된 부분 수열은 항상 팰린드롬 (길이 1)
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    // 길이가 2 이상인 부분 문자열에 대해 DP 테이블 채우기
    for (int cl = 2; cl <= n; cl++) { // cl: current length of substring
        for (int i = 0; i <= n - cl; i++) {
            int j = i + cl - 1; // Ending index of substring
            if (s[i] == s[j]) {
                if (cl == 2)
                    dp[i][j] = 2;
                else
                    dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = MAX(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp;
}

/**
 * constructLPS - dp 테이블을 사용하여 입력 문자열 s의 최장 팰린드롬 부분 수열(LPS)을 재구성합니다.
 * @s: 입력 문자열
 * @dp: dp 테이블 (s의 길이 n x n 배열)
 * @n: 입력 문자열의 길이
 *
 * 반환값: 동적 할당된 LPS 문자열 (호출자가 free()로 해제해야 함)
 */
char *constructLPS(const char *s, int **dp, int n) {
    int index = dp[0][n - 1];
    // 최대 LPS 길이 + 1 for null terminator
    char *lps = (char *)malloc((index + 1) * sizeof(char));
    if (!lps) {
        fprintf(stderr, "메모리 할당 실패 (constructLPS)\n");
        exit(EXIT_FAILURE);
    }
    lps[index] = '\0';

    // 재구성: 양쪽에서 시작하여 LPS를 채워나감
    int i = 0, j = n - 1;
    int start = 0, end = index - 1;
    while (i <= j) {
        if (s[i] == s[j]) {
            // 문자 s[i]는 LPS의 양쪽에 포함됨
            lps[start++] = s[i];
            if (i != j) { // Avoid duplicate for middle character in odd length
                lps[end--] = s[j];
            }
            i++;
            j--;
        } else if (dp[i + 1][j] >= dp[i][j - 1]) {
            i++;
        } else {
            j--;
        }
    }
    return lps;
}

/**
 * lpsMain - 최장 팰린드롬 부분 수열(LPS)을 계산하고 출력하는 메인 함수
 * @s: 입력 문자열
 *
 * 반환값: 동적 할당된 LPS 문자열 (호출자가 free()로 해제해야 함)
 */
char *lpsMain(const char *s) {
    int n = strlen(s);
    int **dp = lpsLength(s, n);
    char *lps = constructLPS(s, dp, n);

    // DP 테이블 메모리 해제
    for (int i = 0; i < n; i++)
        free(dp[i]);
    free(dp);

    return lps;
}

/**
 * main - 최장 팰린드롬 부분 수열(LPS) 데모
 *
 * 이 함수는 예제 문자열을 입력받아, 최장 팰린드롬 부분 수열과 그 길이를 출력합니다.
 */
int main(void) {
    char s[1001];
    printf("문자열을 입력하세요 (최대 1000 문자): ");
    if (scanf("%1000s", s) != 1) {
        fprintf(stderr, "문자열 입력 실패.\n");
        return EXIT_FAILURE;
    }

    char *lps = lpsMain(s);
    printf("입력 문자열: %s\n", s);
    printf("최장 팰린드롬 부분 수열 (LPS): %s\n", lps);
    printf("LPS 길이: %lu\n", strlen(lps));

    free(lps);
    return 0;
}
