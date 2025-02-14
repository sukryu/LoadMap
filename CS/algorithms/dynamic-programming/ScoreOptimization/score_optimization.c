/**
 * score_optimization.c
 *
 * 고도화된 스코어 최적화 예제: 그리드 경로 최적화 문제
 * - 이 파일은 m x n 그리드에서 좌측 상단에서 우측 하단까지 이동할 때,
 *   각 셀에 배정된 점수의 합이 최대가 되는 경로의 총 점수를 계산하는 예제입니다.
 * - 이동은 오직 오른쪽 또는 아래쪽으로만 가능합니다.
 * - 동적 계획법(Dynamic Programming)을 사용하여 O(m*n) 시간 복잡도로 최적 경로 점수를 구합니다.
 *
 * 주요 기능:
 *   1. 그리드 입력 및 동적 메모리 할당
 *   2. dp 테이블을 사용하여 각 셀까지 도달할 수 있는 최대 점수를 계산
 *   3. 최종적으로 우측 하단 셀의 최대 점수를 출력
 *
 * 컴파일 예시: gcc -Wall -O2 score_optimization.c -o score_optimization
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function prototypes
int** allocateIntMatrix(int rows, int cols);
void freeIntMatrix(int **matrix, int rows);
int maxPathScore(int **grid, int m, int n);
void printMatrix(int **matrix, int rows, int cols);

/**
 * allocateIntMatrix - rows x cols 크기의 정수 행렬을 동적 할당합니다.
 * @rows: 행의 수
 * @cols: 열의 수
 *
 * 반환값: 동적 할당된 2차원 정수 배열의 포인터
 */
int** allocateIntMatrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (!matrix) {
        fprintf(stderr, "행렬 메모리 할당 실패 (allocateIntMatrix)\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (!matrix[i]) {
            fprintf(stderr, "행렬 메모리 할당 실패 (allocateIntMatrix, row %d)\n", i);
            for (int j = 0; j < i; j++)
                free(matrix[j]);
            free(matrix);
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

/**
 * freeIntMatrix - 동적 할당된 2차원 정수 행렬의 메모리를 해제합니다.
 * @matrix: 해제할 행렬 포인터
 * @rows: 행의 수
 */
void freeIntMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);
}

/**
 * maxPathScore - 주어진 그리드에서 좌측 상단에서 우측 하단까지 이동할 때의 최대 경로 점수를 계산합니다.
 * @grid: m x n 그리드 (각 셀에 정수 점수가 배정됨)
 * @m: 행의 수
 * @n: 열의 수
 *
 * 반환값: 최적 경로를 통해 얻을 수 있는 최대 점수
 *
 * 동작 원리:
 *   - dp[i][j]는 (i, j) 셀까지 도달할 때의 최대 점수를 저장합니다.
 *   - 초기 조건: dp[0][0] = grid[0][0]
 *   - 점화식:
 *         dp[i][j] = grid[i][j] + max( dp[i-1][j], dp[i][j-1] )
 *     단, 경계 조건에 주의합니다.
 */
int maxPathScore(int **grid, int m, int n) {
    // Allocate DP table of size m x n
    int **dp = allocateIntMatrix(m, n);

    // 초기 조건: 시작 셀
    dp[0][0] = grid[0][0];

    // 첫 행: 오른쪽으로만 이동 가능
    for (int j = 1; j < n; j++) {
        dp[0][j] = dp[0][j-1] + grid[0][j];
    }
    
    // 첫 열: 아래쪽으로만 이동 가능
    for (int i = 1; i < m; i++) {
        dp[i][0] = dp[i-1][0] + grid[i][0];
    }
    
    // 내부 셀: 왼쪽 또는 위쪽에서 도착하는 경우 중 큰 값을 선택
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            int maxPrev = (dp[i-1][j] > dp[i][j-1]) ? dp[i-1][j] : dp[i][j-1];
            dp[i][j] = grid[i][j] + maxPrev;
        }
    }
    
    int result = dp[m-1][n-1];
    
    // (옵션) 결과 DP 테이블 출력 (디버깅용)
    // printMatrix(dp, m, n);
    
    freeIntMatrix(dp, m);
    return result;
}

/**
 * printMatrix - 2차원 정수 행렬을 출력하는 유틸리티 함수
 * @matrix: 출력할 행렬 포인터
 * @rows: 행의 수
 * @cols: 열의 수
 */
void printMatrix(int **matrix, int rows, int cols) {
    printf("DP 테이블:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%5d ", matrix[i][j]);
        }
        printf("\n");
    }
}

/**
 * main - Grid Path Score Optimization 데모
 *
 * 이 함수는 사용자로부터 m x n 그리드의 크기와 각 셀의 점수를 입력받아,
 * 좌측 상단에서 우측 하단까지의 최대 경로 점수를 계산하고 출력합니다.
 */
int main(void) {
    int m, n;
    printf("그리드의 행 수 m과 열 수 n을 입력하세요: ");
    if (scanf("%d %d", &m, &n) != 2 || m <= 0 || n <= 0) {
        fprintf(stderr, "유효한 m과 n을 입력하세요.\n");
        return EXIT_FAILURE;
    }
    
    int **grid = allocateIntMatrix(m, n);
    printf("각 셀의 점수를 입력하세요 (총 %d개):\n", m * n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &grid[i][j]) != 1) {
                fprintf(stderr, "유효한 정수를 입력하세요.\n");
                freeIntMatrix(grid, m);
                return EXIT_FAILURE;
            }
        }
    }
    
    int result = maxPathScore(grid, m, n);
    printf("\n최적 경로 점수 (좌측 상단 -> 우측 하단): %d\n", result);
    
    freeIntMatrix(grid, m);
    return 0;
}
