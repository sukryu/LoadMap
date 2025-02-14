/**
 * strassen.c
 *
 * 고도화된 Strassen 행렬 곱셈 알고리즘 구현 예제
 * - 이 파일은 Strassen 알고리즘을 사용하여 두 개의 정방행렬의 곱을 계산합니다.
 * - Strassen 알고리즘은 분할 정복 기법을 사용하여 전통적인 O(n³) 행렬 곱셈보다 빠른 O(n^log₂7) ≈ O(n^2.807)의 시간 복잡도를 달성합니다.
 * - 본 구현은 동적 메모리 관리, 에러 처리 및 재귀적 분할을 포함하여 실무 환경에서 바로 활용할 수 있도록 작성되었습니다.
 *
 * 주의: 이 구현은 입력 행렬의 크기가 2의 거듭제곱이라고 가정합니다.
 *
 * 컴파일 예시: gcc -Wall -O2 strassen.c -o strassen
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*---------------- Utility Functions for Matrix Allocation ----------------*/

/**
 * allocateMatrix - n x n 크기의 정수 행렬을 동적 할당합니다.
 * @n: 행렬의 크기 (정방행렬)
 *
 * 반환값: 동적 할당된 2차원 정수 배열의 포인터.
 */
int** allocateMatrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    if (!matrix) {
        fprintf(stderr, "행렬 할당 실패 (allocateMatrix)\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)calloc(n, sizeof(int));
        if (!matrix[i]) {
            fprintf(stderr, "행렬 할당 실패 (allocateMatrix row %d)\n", i);
            for (int j = 0; j < i; j++)
                free(matrix[j]);
            free(matrix);
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

/**
 * freeMatrix - 동적 할당된 행렬의 메모리를 해제합니다.
 * @matrix: 해제할 행렬 포인터
 * @n: 행렬의 크기 (행의 수)
 */
void freeMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

/*---------------- Matrix Operations ----------------*/

/**
 * addMatrix - 두 n x n 행렬 A와 B의 합을 계산합니다.
 * @A, @B: 입력 행렬 포인터
 * @n: 행렬의 크기
 *
 * 반환값: 결과 행렬 (A+B), 동적 할당된 행렬 (호출자가 freeMatrix()로 해제)
 */
int** addMatrix(int **A, int **B, int n) {
    int **C = allocateMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

/**
 * subMatrix - 두 n x n 행렬 A와 B의 차이를 계산합니다.
 * @A, @B: 입력 행렬 포인터
 * @n: 행렬의 크기
 *
 * 반환값: 결과 행렬 (A-B), 동적 할당된 행렬 (호출자가 freeMatrix()로 해제)
 */
int** subMatrix(int **A, int **B, int n) {
    int **C = allocateMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

/*---------------- Strassen Algorithm ----------------*/

/**
 * strassenMultiply - Strassen 알고리즘을 이용하여 두 n x n 행렬 A와 B의 곱을 계산합니다.
 * @A, @B: 입력 행렬 포인터
 * @n: 행렬의 크기 (2의 거듭제곱)
 *
 * 반환값: 결과 행렬 (A*B), 동적 할당된 행렬 (호출자가 freeMatrix()로 해제)
 *
 * 기본 케이스: n == 1이면, 단순 곱셈을 수행합니다.
 * 재귀적 분할: 행렬을 네 개의 서브 행렬로 분할한 후, 7개의 재귀 호출을 통해 부분 곱셈을 계산합니다.
 */
int** strassenMultiply(int **A, int **B, int n) {
    int i, j;
    // 기본 케이스: 행렬 크기가 1이면 직접 곱셈
    if (n == 1) {
        int **C = allocateMatrix(1);
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int newSize = n / 2;
    // Allocate submatrices
    int **A11 = allocateMatrix(newSize);
    int **A12 = allocateMatrix(newSize);
    int **A21 = allocateMatrix(newSize);
    int **A22 = allocateMatrix(newSize);
    int **B11 = allocateMatrix(newSize);
    int **B12 = allocateMatrix(newSize);
    int **B21 = allocateMatrix(newSize);
    int **B22 = allocateMatrix(newSize);

    // Divide A and B into 4 submatrices each
    for (i = 0; i < newSize; i++) {
        for (j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Compute 7 products using Strassen's formulas:
    // M1 = (A11 + A22) * (B11 + B22)
    int **A11A22 = addMatrix(A11, A22, newSize);
    int **B11B22 = addMatrix(B11, B22, newSize);
    int **M1 = strassenMultiply(A11A22, B11B22, newSize);
    freeMatrix(A11A22, newSize);
    freeMatrix(B11B22, newSize);

    // M2 = (A21 + A22) * B11
    int **A21A22 = addMatrix(A21, A22, newSize);
    int **M2 = strassenMultiply(A21A22, B11, newSize);
    freeMatrix(A21A22, newSize);

    // M3 = A11 * (B12 - B22)
    int **B12B22 = subMatrix(B12, B22, newSize);
    int **M3 = strassenMultiply(A11, B12B22, newSize);
    freeMatrix(B12B22, newSize);

    // M4 = A22 * (B21 - B11)
    int **B21B11 = subMatrix(B21, B11, newSize);
    int **M4 = strassenMultiply(A22, B21B11, newSize);
    freeMatrix(B21B11, newSize);

    // M5 = (A11 + A12) * B22
    int **A11A12 = addMatrix(A11, A12, newSize);
    int **M5 = strassenMultiply(A11A12, B22, newSize);
    freeMatrix(A11A12, newSize);

    // M6 = (A21 - A11) * (B11 + B12)
    int **A21A11 = subMatrix(A21, A11, newSize);
    int **B11B12 = addMatrix(B11, B12, newSize);
    int **M6 = strassenMultiply(A21A11, B11B12, newSize);
    freeMatrix(A21A11, newSize);
    freeMatrix(B11B12, newSize);

    // M7 = (A12 - A22) * (B21 + B22)
    int **A12A22 = subMatrix(A12, A22, newSize);
    int **B21B22 = addMatrix(B21, B22, newSize);
    int **M7 = strassenMultiply(A12A22, B21B22, newSize);
    freeMatrix(A12A22, newSize);
    freeMatrix(B21B22, newSize);

    // Combine the 7 products to form the result submatrices:
    // C11 = M1 + M4 - M5 + M7
    int **M1_M4 = addMatrix(M1, M4, newSize);
    int **M1_M4_M5 = subMatrix(M1_M4, M5, newSize);
    int **C11 = addMatrix(M1_M4_M5, M7, newSize);
    freeMatrix(M1_M4, newSize);
    freeMatrix(M1_M4_M5, newSize);

    // C12 = M3 + M5
    int **C12 = addMatrix(M3, M5, newSize);

    // C21 = M2 + M4
    int **C21 = addMatrix(M2, M4, newSize);

    // C22 = M1 - M2 + M3 + M6
    int **M1_M3 = addMatrix(M1, M3, newSize);
    int **M1_M3_M6 = addMatrix(M1_M3, M6, newSize);
    int **C22 = subMatrix(M1_M3_M6, M2, newSize);
    freeMatrix(M1_M3, newSize);
    freeMatrix(M1_M3_M6, newSize);

    // Allocate result matrix C (n x n)
    int **C = allocateMatrix(n);
    // Combine submatrices C11, C12, C21, C22 into C
    for (i = 0; i < newSize; i++) {
        for (j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    // Free all allocated submatrices
    freeMatrix(A11, newSize);
    freeMatrix(A12, newSize);
    freeMatrix(A21, newSize);
    freeMatrix(A22, newSize);
    freeMatrix(B11, newSize);
    freeMatrix(B12, newSize);
    freeMatrix(B21, newSize);
    freeMatrix(B22, newSize);
    freeMatrix(M1, newSize);
    freeMatrix(M2, newSize);
    freeMatrix(M3, newSize);
    freeMatrix(M4, newSize);
    freeMatrix(M5, newSize);
    freeMatrix(M6, newSize);
    freeMatrix(M7, newSize);
    freeMatrix(C11, newSize);
    freeMatrix(C12, newSize);
    freeMatrix(C21, newSize);
    freeMatrix(C22, newSize);

    return C;
}

/*---------------- Utility Function: Print Matrix ----------------*/

/**
 * printMatrix - n x n 크기의 행렬을 출력합니다.
 * @matrix: 출력할 행렬 포인터
 * @n: 행렬의 크기
 */
void printMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

/*---------------- main 함수 (데모) ----------------*/
int main(void) {
    int n = 4;  // n must be a power of 2 for this implementation
    int **A = allocateMatrix(n);
    int **B = allocateMatrix(n);

    // 예제 행렬 A
    // 1 2 3 4
    // 5 6 7 8
    // 9 10 11 12
    // 13 14 15 16
    int count = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = count++;
        }
    }

    // 예제 행렬 B (동일한 값으로 설정)
    count = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = count++;
        }
    }

    printf("행렬 A:\n");
    printMatrix(A, n);
    printf("\n행렬 B:\n");
    printMatrix(B, n);

    int **C = strassenMultiply(A, B, n);
    printf("\nStrassen 행렬 곱셈 결과 (A x B):\n");
    printMatrix(C, n);

    // 동적 할당된 행렬 해제
    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}
