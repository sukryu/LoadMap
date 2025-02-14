/**
 * edit_distance.c
 *
 * 고도화된 편집 거리 (Edit Distance) 알고리즘 구현 예제
 * - 이 파일은 두 문자열 X와 Y 사이의 최소 편집 연산(삽입, 삭제, 대체) 횟수를 
 *   동적 계획법(Dynamic Programming)을 사용하여 계산합니다.
 * - DP 테이블 dp[i][j]는 문자열 X의 처음 i문자와 Y의 처음 j문자를 일치시키기 위해 필요한 최소 편집 연산의 수를 저장합니다.
 * - 점화식:
 *      if (X[i-1] == Y[j-1])
 *          dp[i][j] = dp[i-1][j-1];
 *      else
 *          dp[i][j] = 1 + min(dp[i-1][j],    // 삭제
 *                             dp[i][j-1],    // 삽입
 *                             dp[i-1][j-1]); // 대체
 *
 * - 이 구현은 입력 문자열들을 표준 입력에서 받아 편집 거리를 계산한 후 결과를 출력합니다.
 *
 * 컴파일 예시: gcc -Wall -O2 edit_distance.c -o edit_distance
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Utility macro: minimum of three values
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

// Function: Compute the edit distance between two strings X and Y.
int editDistance(const char *X, const char *Y) {
    int m = strlen(X);
    int n = strlen(Y);
    
    // Allocate DP table: dimensions (m+1) x (n+1)
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (!dp) {
        fprintf(stderr, "메모리 할당 실패 (dp table)\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        if (!dp[i]) {
            fprintf(stderr, "메모리 할당 실패 (dp[%d])\n", i);
            for (int k = 0; k < i; k++)
                free(dp[k]);
            free(dp);
            exit(EXIT_FAILURE);
        }
    }
    
    // 초기 조건: dp[0][j] = j, dp[i][0] = i
    for (int i = 0; i <= m; i++)
        dp[i][0] = i;
    for (int j = 0; j <= n; j++)
        dp[0][j] = j;
    
    // Build the DP table bottom-up.
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + MIN3(dp[i - 1][j],    // 삭제
                                    dp[i][j - 1],    // 삽입
                                    dp[i - 1][j - 1] // 대체
                                    );
        }
    }
    
    int result = dp[m][n];
    
    // Free DP table
    for (int i = 0; i <= m; i++)
        free(dp[i]);
    free(dp);
    
    return result;
}

/**
 * main - 편집 거리(Edit Distance) 알고리즘 데모
 *
 * 이 함수는 사용자로부터 두 문자열을 입력받아, 
 * 두 문자열 간의 최소 편집 거리(삽입, 삭제, 대체 연산의 최소 횟수)를 계산한 후 결과를 출력합니다.
 */
int main(void) {
    // 최대 입력 길이를 제한합니다.
    char X[1001], Y[1001];
    
    printf("첫 번째 문자열을 입력하세요: ");
    if (scanf("%1000s", X) != 1) {
        fprintf(stderr, "문자열 입력 실패.\n");
        return EXIT_FAILURE;
    }
    
    printf("두 번째 문자열을 입력하세요: ");
    if (scanf("%1000s", Y) != 1) {
        fprintf(stderr, "문자열 입력 실패.\n");
        return EXIT_FAILURE;
    }
    
    int distance = editDistance(X, Y);
    printf("\n문자열 \"%s\"와 \"%s\" 사이의 편집 거리: %d\n", X, Y, distance);
    
    return 0;
}