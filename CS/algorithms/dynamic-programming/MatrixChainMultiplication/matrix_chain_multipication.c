/**
 * matrix_chain_multiplication.c
 *
 * 고도화된 행렬 체인 곱셈 (Matrix Chain Multiplication) 구현 예제
 * - 이 파일은 주어진 행렬 체인 (각 행렬의 크기는 p[i-1] x p[i]로 주어짐)에 대해,
 *   동적 계획법(Dynamic Programming)을 사용하여 전체 행렬 곱셈에 필요한 최소 스칼라 곱셈 연산 수를 계산하고,
 *   최적의 괄호 배치를 재구성합니다.
 *
 * 알고리즘 개요:
 *   1. dp[i][j]는 행렬 Aᵢ부터 Aⱼ까지 곱셈에 필요한 최소 연산 수를 저장합니다.
 *   2. s[i][j]는 dp[i][j]가 최적이 되도록 하는 분할 지점(k)을 기록합니다.
 *   3. 점화식:
 *          dp[i][j] = min { dp[i][k] + dp[k+1][j] + p[i-1]*p[k]*p[j] } for i ≤ k < j
 *      기저 조건: dp[i][i] = 0 (단일 행렬에는 곱셈 연산이 필요하지 않음)
 *   4. 최종적으로 dp[1][n] (또는 0-based index에서는 dp[0][n-1])가 최소 비용이며,
 *      s[][] 배열을 통해 최적 괄호 배치를 재구성합니다.
 *
 * 컴파일 예시: gcc -Wall -O2 matrix_chain_multiplication.c -o matrix_chain_multiplication
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

// Function prototypes
int** allocateIntMatrix(int rows, int cols);
void freeIntMatrix(int **matrix, int rows);
void printOptimalParens(int **s, int i, int j);
int matrixChainOrder(int p[], int n, int ***sOut);

/**
 * allocateIntMatrix - rows x cols 크기의 정수 행렬을 동적 할당합니다.
 * @rows: 행의 수
 * @cols: 열의 수
 *
 * 반환값: 동적 할당된 2차원 정수 배열 포인터.
 */
int** allocateIntMatrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (!matrix) {
        fprintf(stderr, "메모리 할당 실패 (allocateIntMatrix)\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (!matrix[i]) {
            fprintf(stderr, "메모리 할당 실패 (allocateIntMatrix, row %d)\n", i);
            for (int j = 0; j < i; j++)
                free(matrix[j]);
            free(matrix);
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

/**
 * freeIntMatrix - 동적 할당된 정수 행렬의 메모리를 해제합니다.
 * @matrix: 해제할 행렬 포인터
 * @rows: 행의 수
 */
void freeIntMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

/**
 * matrixChainOrder - 동적 계획법을 사용하여 행렬 체인 곱셈의 최소 비용을 계산합니다.
 * @p: 행렬 크기를 나타내는 배열 (길이 = n+1; Aᵢ는 p[i-1] x p[i])
 * @n: 행렬의 개수
 * @sOut: 최적 분할 인덱스를 기록한 2차원 배열 포인터 (출력 인자)
 *
 * 반환값: 최소 곱셈 연산 수
 *
 * 이 함수는 dp 테이블과 s 테이블을 계산합니다.
 */
int matrixChainOrder(int p[], int n, int ***sOut) {
    int i, j, k, L;
    // dp[i][j] = 최소 곱셈 연산 수, i에서 j까지의 곱셈 결과에 대한 비용
    int **dp = allocateIntMatrix(n, n);
    // s[i][j] = dp[i][j]의 최적 분할 인덱스
    int **s = allocateIntMatrix(n, n);
    
    // 기저 조건: 단일 행렬에는 곱셈 연산이 필요 없음.
    for (i = 0; i < n; i++)
        dp[i][i] = 0;
    
    // L은 chain의 길이 (2부터 n까지)
    for (L = 2; L <= n; L++) {
        for (i = 0; i <= n - L; i++) {
            j = i + L - 1;
            dp[i][j] = INT_MAX;
            // 가능한 분할 지점 k
            for (k = i; k < j; k++) {
                int q = dp[i][k] + dp[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (q < dp[i][j]) {
                    dp[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    
    // 결과로 s 테이블을 출력 인자로 전달
    *sOut = s;
    int result = dp[0][n - 1];
    
    // dp 테이블은 더 이상 필요 없으므로 해제 (s는 반환)
    freeIntMatrix(dp, n);
    
    return result;
}

/**
 * printOptimalParens - 재귀적으로 최적 괄호 배치를 출력합니다.
 * @s: 최적 분할 인덱스가 저장된 2차원 배열
 * @i: 시작 인덱스
 * @j: 종료 인덱스
 *
 * 이 함수는 재귀적으로 s[i][j]를 사용하여 Aᵢ...Aⱼ의 곱셈 순서를 최적화하는 괄호 배치를 출력합니다.
 */
void printOptimalParens(int **s, int i, int j) {
    if (i == j) {
        printf("A%d", i + 1);
        return;
    }
    printf("(");
    printOptimalParens(s, i, s[i][j]);
    printf(" x ");
    printOptimalParens(s, s[i][j] + 1, j);
    printf(")");
}

/**
 * main - 행렬 체인 곱셈 데모
 *
 * 이 함수는 예제 행렬 체인을 정의하고, 최적 곱셈 비용과 최적 괄호 배치를 출력합니다.
 */
int main(void) {
    int n;
    printf("행렬의 개수 n을 입력하세요: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "유효한 n을 입력하세요.\n");
        return EXIT_FAILURE;
    }
    
    // 행렬 크기를 나타내는 배열 p (길이 = n+1)
    int *p = (int*)malloc((n + 1) * sizeof(int));
    if (!p) {
        fprintf(stderr, "메모리 할당 실패 (p 배열)\n");
        return EXIT_FAILURE;
    }
    
    printf("n+1개의 행렬 크기(예: p0 p1 ... p_n)를 입력하세요:\n");
    for (int i = 0; i <= n; i++) {
        if (scanf("%d", &p[i]) != 1) {
            fprintf(stderr, "유효한 정수를 입력하세요.\n");
            free(p);
            return EXIT_FAILURE;
        }
    }
    
    int **s;
    int minCost = matrixChainOrder(p, n, &s);
    
    printf("\n최소 곱셈 연산 수: %d\n", minCost);
    printf("최적 괄호 배치: ");
    printOptimalParens(s, 0, n - 1);
    printf("\n");
    
    freeIntMatrix(s, n);
    free(p);
    return 0;
}
