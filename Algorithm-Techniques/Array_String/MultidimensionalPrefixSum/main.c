/*
 * main.c
 *
 * 이 파일은 코딩 테스트에서 다차원 누적합(Multi-Dimensional Prefix Sum)을 활용하여
 * 다양한 문제 유형을 해결하기 위한 예제 함수들을 포함합니다.
 *
 * 다차원 누적합은 다차원 배열(예: 2차원 행렬, 3차원 배열)에서 특정 영역의 합을 빠르게 계산할 수 있도록
 * 미리 각 위치까지의 합을 구해두는 기법입니다.
 *
 * 포함된 함수 목록:
 * 1. build2DPrefixSum:
 *    - 주어진 2차원 정수 배열(matrix)에 대해 누적합 배열(P)을 생성합니다.
 *    - P[i][j]는 matrix[0..i-1][0..j-1]의 합을 저장합니다.
 *    - 시간 복잡도: O(rows * cols)
 *    - 공간 복잡도: O(rows * cols)
 *
 * 2. query2DSum:
 *    - 2차원 누적합 배열을 이용해 지정된 영역 (r1, c1)부터 (r2, c2)까지의 합을 O(1)에 계산합니다.
 *
 * 3. build3DPrefixSum:
 *    - 주어진 3차원 정수 배열(matrix)에 대해 누적합 배열(P)을 생성합니다.
 *    - P[i][j][k]는 matrix[0..i-1][0..j-1][0..k-1]의 합을 저장합니다.
 *    - 시간 복잡도: O(X * Y * Z)
 *    - 공간 복잡도: O(X * Y * Z)
 *
 * 4. query3DSum:
 *    - 3차원 누적합 배열을 이용해 지정된 직육면체 영역 (x1, y1, z1)부터 (x2, y2, z2)까지의 합을 O(1)에 계산합니다.
 *
 * 참고: 이 파일에는 main 함수는 포함되어 있지 않으므로, 별도의 테스트 코드나 main 함수를 작성하여
 *        각 함수를 호출하고 결과를 검증할 수 있습니다.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 함수: build2DPrefixSum
 * ------------------------
 * 설명:
 *   주어진 2차원 정수 배열(matrix)에 대해 누적합 배열(P)을 생성합니다.
 *   누적합 배열은 P[i][j] = P[i-1][j] + P[i][j-1] - P[i-1][j-1] + matrix[i-1][j-1] (1-indexed 기준)으로 계산됩니다.
 *
 * 매개변수:
 *   - matrix: 원본 2차원 정수 배열 (크기: rows x cols)
 *   - rows: 행의 수
 *   - cols: 열의 수
 *
 * 반환값:
 *   동적 할당된 누적합 배열의 포인터 (int**). 배열의 크기는 (rows+1) x (cols+1)입니다.
 *
 * 시간 복잡도: O(rows * cols)
 * 공간 복잡도: O(rows * cols)
 */
int** build2DPrefixSum(int** matrix, int rows, int cols) {
    int i, j;
    // (rows+1) x (cols+1) 크기의 2차원 배열 할당
    int** prefix = (int**)malloc((rows + 1) * sizeof(int*));
    if (prefix == NULL) return NULL;
    
    for (i = 0; i <= rows; i++) {
        prefix[i] = (int*)malloc((cols + 1) * sizeof(int));
        if (prefix[i] == NULL) {
            for (j = 0; j < i; j++)
                free(prefix[j]);
            free(prefix);
            return NULL;
        }
    }
    
    // 첫 행과 첫 열을 0으로 초기화
    for (i = 0; i <= rows; i++) {
        prefix[i][0] = 0;
    }
    for (j = 0; j <= cols; j++) {
        prefix[0][j] = 0;
    }
    
    // 누적합 배열 채우기
    for (i = 1; i <= rows; i++) {
        for (j = 1; j <= cols; j++) {
            prefix[i][j] = prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1] + matrix[i-1][j-1];
        }
    }
    
    return prefix;
}

/*
 * 함수: query2DSum
 * ------------------
 * 설명:
 *   2차원 누적합 배열(prefix)을 이용하여 지정된 영역 (r1, c1)부터 (r2, c2)까지의 합을 계산합니다.
 *   인덱스 r1, c1, r2, c2는 원본 배열(matrix)의 0-indexed 좌표입니다.
 *   누적합 배열은 1-indexed로 구성되어 있으므로, 영역 합은 다음과 같이 계산됩니다:
 *     영역 합 = P[r2+1][c2+1] - P[r1][c2+1] - P[r2+1][c1] + P[r1][c1]
 *
 * 매개변수:
 *   - prefix: build2DPrefixSum 함수로 생성된 2차원 누적합 배열
 *   - r1, c1: 영역의 시작 좌표 (0-indexed)
 *   - r2, c2: 영역의 종료 좌표 (0-indexed)
 *
 * 반환값:
 *   지정된 영역의 합 (정수)
 *
 * 시간 복잡도: O(1)
 * 공간 복잡도: O(1)
 */
int query2DSum(int** prefix, int r1, int c1, int r2, int c2) {
    return prefix[r2+1][c2+1] - prefix[r1][c2+1] - prefix[r2+1][c1] + prefix[r1][c1];
}

/*
 * 함수: build3DPrefixSum
 * ------------------------
 * 설명:
 *   주어진 3차원 정수 배열(matrix)에 대해 누적합 배열(P)을 생성합니다.
 *   누적합 배열은 P[i][j][k]가 matrix[0..i-1][0..j-1][0..k-1]의 합을 저장하도록 구성됩니다.
 *
 * 매개변수:
 *   - matrix: 원본 3차원 정수 배열 (크기: X x Y x Z)
 *   - X: 1차원 크기 (첫 번째 차원)
 *   - Y: 2차원 크기 (두 번째 차원)
 *   - Z: 3차원 크기 (세 번째 차원)
 *
 * 반환값:
 *   동적 할당된 3차원 누적합 배열의 포인터 (int***). 배열의 크기는 (X+1) x (Y+1) x (Z+1)입니다.
 *
 * 시간 복잡도: O(X * Y * Z)
 * 공간 복잡도: O(X * Y * Z)
 */
int*** build3DPrefixSum(int*** matrix, int X, int Y, int Z) {
    int i, j, k;
    // (X+1) x (Y+1) x (Z+1) 크기의 3차원 배열 할당
    int*** prefix = (int***)malloc((X + 1) * sizeof(int**));
    if (prefix == NULL) return NULL;
    
    for (i = 0; i <= X; i++) {
        prefix[i] = (int**)malloc((Y + 1) * sizeof(int*));
        if (prefix[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(prefix[j]);
            }
            free(prefix);
            return NULL;
        }
        for (j = 0; j <= Y; j++) {
            prefix[i][j] = (int*)malloc((Z + 1) * sizeof(int));
            if (prefix[i][j] == NULL) {
                for (k = 0; k < j; k++) {
                    free(prefix[i][k]);
                }
                free(prefix[i]);
                for (int a = 0; a < i; a++) {
                    for (int b = 0; b <= Y; b++) {
                        free(prefix[a][b]);
                    }
                    free(prefix[a]);
                }
                free(prefix);
                return NULL;
            }
        }
    }
    
    // 첫 면(면에 해당하는 인덱스 0) 초기화: P[0][*][*] = 0, P[*][0][*] = 0, P[*][*][0] = 0
    for (i = 0; i <= X; i++) {
        for (j = 0; j <= Y; j++) {
            prefix[i][j][0] = 0;
        }
    }
    for (i = 0; i <= X; i++) {
        for (k = 0; k <= Z; k++) {
            prefix[i][0][k] = 0;
        }
    }
    for (j = 0; j <= Y; j++) {
        for (k = 0; k <= Z; k++) {
            prefix[0][j][k] = 0;
        }
    }
    
    // 누적합 배열 채우기:
    // 점화식 (1-indexed 기준):
    // P[i][j][k] = P[i-1][j][k] + P[i][j-1][k] + P[i][j][k-1]
    //              - P[i-1][j-1][k] - P[i-1][j][k-1] - P[i][j-1][k-1]
    //              + P[i-1][j-1][k-1] + matrix[i-1][j-1][k-1]
    for (i = 1; i <= X; i++) {
        for (j = 1; j <= Y; j++) {
            for (k = 1; k <= Z; k++) {
                prefix[i][j][k] = prefix[i-1][j][k] + prefix[i][j-1][k] + prefix[i][j][k-1]
                                  - prefix[i-1][j-1][k] - prefix[i-1][j][k-1] - prefix[i][j-1][k-1]
                                  + prefix[i-1][j-1][k-1] + matrix[i-1][j-1][k-1];
            }
        }
    }
    
    return prefix;
}

/*
 * 함수: query3DSum
 * ------------------
 * 설명:
 *   3차원 누적합 배열(prefix)을 이용하여, 지정된 직육면체 영역 (x1, y1, z1)부터 (x2, y2, z2)까지의 합을 계산합니다.
 *   영역의 좌표는 원본 배열(matrix)의 0-indexed 좌표입니다.
 *   누적합 배열은 1-indexed로 구성되어 있으므로, 영역 합은 다음과 같이 계산됩니다:
 *
 *   영역 합 = P[x2+1][y2+1][z2+1]
 *            - P[x1][y2+1][z2+1] - P[x2+1][y1][z2+1] - P[x2+1][y2+1][z1]
 *            + P[x1][y1][z2+1] + P[x1][y2+1][z1] + P[x2+1][y1][z1]
 *            - P[x1][y1][z1]
 *
 * 매개변수:
 *   - prefix: build3DPrefixSum 함수로 생성된 3차원 누적합 배열
 *   - x1, y1, z1: 영역의 시작 좌표 (0-indexed)
 *   - x2, y2, z2: 영역의 종료 좌표 (0-indexed)
 *
 * 반환값:
 *   지정된 직육면체 영역의 합 (정수)
 *
 * 시간 복잡도: O(1)
 * 공간 복잡도: O(1)
 */
int query3DSum(int*** prefix, int x1, int y1, int z1, int x2, int y2, int z2) {
    return prefix[x2+1][y2+1][z2+1]
         - prefix[x1][y2+1][z2+1] - prefix[x2+1][y1][z2+1] - prefix[x2+1][y2+1][z1]
         + prefix[x1][y1][z2+1] + prefix[x1][y2+1][z1] + prefix[x2+1][y1][z1]
         - prefix[x1][y1][z1];
}

/*
 * End of main.c
 *
 * 이 파일은 다차원 누적합 기법을 활용하여 2차원 및 3차원 배열에서 영역 합을
 * 효율적으로 계산하는 예제 함수들을 포함합니다.
 *
 * 각 함수는 상세한 주석과 함께 구현되어 있어, 코드만 보더라도
 * 알고리즘의 동작 원리 및 시간/공간 복잡도를 쉽게 이해할 수 있도록 작성되었습니다.
 *
 * 참고: 이 파일에는 main 함수가 포함되어 있지 않으므로, 별도의 테스트 코드나 main 함수를 작성하여
 *        이 함수들을 호출하고 검증할 수 있습니다.
 */
