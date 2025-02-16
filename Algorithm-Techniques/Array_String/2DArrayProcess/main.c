/*
 * main.c
 *
 * 이 파일은 코딩 테스트에서 2차원 배열 처리를 위한 다양한 문제 유형에 대해 최적의 해결책을 제공하는 예제 함수들을 포함합니다.
 * 각 함수는 시간 및 공간 복잡도를 고려하여 구현되었으며, 주석을 매우 상세하게 달아 코드만 보더라도 알고리즘의 동작 원리와 구현 방법을 쉽게 이해할 수 있도록 작성되었습니다.
 *
 * 포함된 함수 목록:
 * 1. build2DPrefixSum:
 *      - 설명: 주어진 2차원 정수 배열(matrix)에 대해 누적 합(Prefix Sum) 배열을 생성합니다.
 *      - 시간 복잡도: O(rows * cols)
 *      - 공간 복잡도: O(rows * cols)
 *
 * 2. query2DSum:
 *      - 설명: 누적 합 배열(prefix)을 이용해 지정한 영역 (r1, c1)부터 (r2, c2)까지의 합을 O(1)에 계산합니다.
 *
 * 3. minPathSum:
 *      - 설명: 2차원 격자(grid)에서 좌측 상단부터 우측 하단까지 이동할 때, 경로상의 숫자 합의 최솟값을 동적 계획법(DP)을 사용하여 계산합니다.
 *      - 시간 복잡도: O(rows * cols)
 *      - 공간 복잡도: O(rows * cols)
 *
 * 4. countIslands:
 *      - 설명: 0과 1로 구성된 2차원 격자(grid)에서 1로 구성된 섬(연결된 영역)의 개수를 DFS(깊이 우선 탐색)를 사용하여 계산합니다.
 *      - 시간 복잡도: O(rows * cols)
 *      - 공간 복잡도: O(rows * cols) (방문 배열)
 *
 * 참고: 이 파일에는 main 함수는 포함되어 있지 않습니다. 별도의 테스트 코드나 main 함수를 작성하여 각 함수를 호출하고 검증할 수 있습니다.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 함수: build2DPrefixSum
 * --------------------------------
 * 설명:
 *   주어진 2차원 정수 배열(matrix)에서 누적 합(Prefix Sum) 배열을 생성합니다.
 *   누적 합 배열은 각 (i, j) 위치에서 원본 배열의 (0,0)부터 (i-1, j-1)까지의 합을 저장합니다.
 *   이를 통해 특정 영역의 합을 O(1)에 계산할 수 있습니다.
 *
 * 매개변수:
 *   - matrix: 원본 2차원 정수 배열 (행렬)
 *   - rows: matrix의 행의 개수
 *   - cols: matrix의 열의 개수
 *
 * 반환값:
 *   동적 할당된 누적 합 배열의 포인터 (int**). 배열의 크기는 (rows+1) x (cols+1)입니다.
 *
 * 시간 복잡도: O(rows * cols)
 * 공간 복잡도: O(rows * cols)
 */
int** build2DPrefixSum(int** matrix, int rows, int cols) {
    // (rows+1) x (cols+1) 크기의 2차원 누적 합 배열 할당
    int** prefix = (int**)malloc((rows + 1) * sizeof(int*));
    if (prefix == NULL) {
        return NULL; // 메모리 할당 실패 처리
    }
    for (int i = 0; i <= rows; i++) {
        prefix[i] = (int*)malloc((cols + 1) * sizeof(int));
        if (prefix[i] == NULL) {
            // 할당 실패 시, 이전에 할당된 메모리 해제
            for (int k = 0; k < i; k++) {
                free(prefix[k]);
            }
            free(prefix);
            return NULL;
        }
    }
    
    // 첫 행과 첫 열을 0으로 초기화 (누적 합 계산의 기초)
    for (int i = 0; i <= rows; i++) {
        prefix[i][0] = 0;
    }
    for (int j = 0; j <= cols; j++) {
        prefix[0][j] = 0;
    }
    
    // 누적 합 배열 계산:
    // prefix[i][j] = prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1] + matrix[i-1][j-1]
    // i와 j는 1부터 rows, cols까지 반복 (matrix 인덱스는 i-1, j-1)
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            prefix[i][j] = prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1] + matrix[i-1][j-1];
        }
    }
    
    return prefix;
}

/*
 * 함수: query2DSum
 * --------------------------------
 * 설명:
 *   누적 합 배열(prefix)을 이용하여, 지정된 영역 (r1, c1)부터 (r2, c2)까지의 합을 O(1) 시간에 계산합니다.
 *   영역의 인덱스는 원본 배열 기준으로 0-indexed이며, prefix 배열은 1-indexed로 구성되어 있습니다.
 *
 * 매개변수:
 *   - prefix: build2DPrefixSum 함수를 통해 생성된 누적 합 배열
 *   - r1: 영역의 시작 행 (0-indexed)
 *   - c1: 영역의 시작 열 (0-indexed)
 *   - r2: 영역의 종료 행 (0-indexed)
 *   - c2: 영역의 종료 열 (0-indexed)
 *
 * 반환값:
 *   지정된 영역의 합 (정수)
 *
 * 계산 공식:
 *   subMatrixSum = prefix[r2+1][c2+1] - prefix[r1][c2+1] - prefix[r2+1][c1] + prefix[r1][c1]
 *
 * 시간 복잡도: O(1)
 * 공간 복잡도: O(1)
 */
int query2DSum(int** prefix, int r1, int c1, int r2, int c2) {
    return prefix[r2+1][c2+1] - prefix[r1][c2+1] - prefix[r2+1][c1] + prefix[r1][c1];
}

/*
 * 함수: minPathSum
 * --------------------------------
 * 설명:
 *   2차원 격자(grid)에서 좌측 상단 (0,0)부터 우측 하단 (rows-1, cols-1)까지 이동하며 경로상의 숫자 합의 최솟값을 계산합니다.
 *   이동은 오른쪽 또는 아래쪽으로만 가능하다고 가정합니다.
 *   동적 계획법(DP)을 사용하여 각 셀까지 도달하는 최소 합을 구합니다.
 *
 * 매개변수:
 *   - grid: 2차원 정수 배열 (격자)
 *   - rows: grid의 행 개수
 *   - cols: grid의 열 개수
 *
 * 반환값:
 *   좌측 상단부터 우측 하단까지 도달하는 최소 경로 합 (정수)
 *
 * 시간 복잡도: O(rows * cols)
 * 공간 복잡도: O(rows * cols)
 */
int minPathSum(int** grid, int rows, int cols) {
    // DP 테이블을 동적 할당: dp[i][j]는 (i,j)까지의 최소 경로 합
    int** dp = (int**)malloc(rows * sizeof(int*));
    if (dp == NULL) return -1; // 메모리 할당 실패 처리
    for (int i = 0; i < rows; i++) {
        dp[i] = (int*)malloc(cols * sizeof(int));
        if (dp[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(dp[k]);
            }
            free(dp);
            return -1;
        }
    }
    
    // 시작점 초기화: dp[0][0]는 grid[0][0]과 동일
    dp[0][0] = grid[0][0];
    
    // 첫 행의 누적 합 계산: 오른쪽으로만 이동 가능
    for (int j = 1; j < cols; j++) {
        dp[0][j] = dp[0][j-1] + grid[0][j];
    }
    
    // 첫 열의 누적 합 계산: 아래로만 이동 가능
    for (int i = 1; i < rows; i++) {
        dp[i][0] = dp[i-1][0] + grid[i][0];
    }
    
    // 나머지 셀에 대해, 위쪽 셀(dp[i-1][j])과 왼쪽 셀(dp[i][j-1]) 중 최소값을 선택하여 grid[i][j]를 더함
    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < cols; j++) {
            int minPrev = (dp[i-1][j] < dp[i][j-1]) ? dp[i-1][j] : dp[i][j-1];
            dp[i][j] = grid[i][j] + minPrev;
        }
    }
    
    int result = dp[rows-1][cols-1]; // 최종 최소 경로 합
    
    // 동적 할당된 dp 배열 해제
    for (int i = 0; i < rows; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

/*
 * 함수: dfsCountIslands
 * --------------------------------
 * 설명:
 *   DFS(깊이 우선 탐색)를 사용하여 2차원 격자(grid)에서 연결된 1의 영역(섬)을 탐색 및 표시합니다.
 *   이 함수는 재귀적으로 동작하며, 방문한 셀은 visited 배열에 표시하여 중복 방문을 방지합니다.
 *
 * 매개변수:
 *   - grid: 2차원 정수 배열 (0과 1로 구성된 격자)
 *   - rows: grid의 행 개수
 *   - cols: grid의 열 개수
 *   - i: 현재 탐색 중인 행 인덱스
 *   - j: 현재 탐색 중인 열 인덱스
 *   - visited: 같은 크기의 2차원 배열로, 이미 방문한 셀을 1로 표시 (방문하지 않은 셀은 0)
 *
 * 반환값:
 *   없음. 재귀 호출을 통해 연결된 영역을 방문 처리합니다.
 */
void dfsCountIslands(int** grid, int rows, int cols, int i, int j, int** visited) {
    // 경계 조건 검사: i, j가 유효한 범위 내에 있는지 확인
    if (i < 0 || i >= rows || j < 0 || j >= cols)
        return;
    
    // 이미 방문했거나, 현재 셀이 0이면 종료 (섬이 아님)
    if (visited[i][j] || grid[i][j] == 0)
        return;
    
    // 현재 셀을 방문 처리
    visited[i][j] = 1;
    
    // 4방향(상, 하, 좌, 우)으로 DFS 재귀 호출
    dfsCountIslands(grid, rows, cols, i - 1, j, visited); // 상
    dfsCountIslands(grid, rows, cols, i + 1, j, visited); // 하
    dfsCountIslands(grid, rows, cols, i, j - 1, visited); // 좌
    dfsCountIslands(grid, rows, cols, i, j + 1, visited); // 우
}

/*
 * 함수: countIslands
 * --------------------------------
 * 설명:
 *   0과 1로 구성된 2차원 격자(grid)에서 섬의 개수를 계산합니다.
 *   섬은 상하좌우로 연결된 1들의 집합으로 정의되며, DFS를 사용하여 연결된 영역을 탐색합니다.
 *
 * 매개변수:
 *   - grid: 2차원 정수 배열 (0과 1로 구성됨)
 *   - rows: grid의 행 개수
 *   - cols: grid의 열 개수
 *
 * 반환값:
 *   격자 내 섬의 개수 (정수)
 *
 * 시간 복잡도: O(rows * cols)
 * 공간 복잡도: O(rows * cols) (visited 배열)
 */
int countIslands(int** grid, int rows, int cols) {
    // 방문 여부를 저장할 2차원 배열을 동적 할당 (visited 배열)
    int** visited = (int**)malloc(rows * sizeof(int*));
    if (visited == NULL) return 0;
    for (int i = 0; i < rows; i++) {
        visited[i] = (int*)calloc(cols, sizeof(int)); // 0으로 초기화
        if (visited[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(visited[k]);
            }
            free(visited);
            return 0;
        }
    }
    
    int islandCount = 0;
    // 격자의 각 셀을 순회하며 아직 방문하지 않은 1을 발견하면 DFS를 수행하고 섬 카운트를 증가
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!visited[i][j] && grid[i][j] == 1) {
                dfsCountIslands(grid, rows, cols, i, j, visited);
                islandCount++;
            }
        }
    }
    
    // 동적 할당된 visited 배열 메모리 해제
    for (int i = 0; i < rows; i++) {
        free(visited[i]);
    }
    free(visited);
    
    return islandCount;
}

/*
 * End of main.c
 *
 * 이 파일은 2차원 배열 처리와 관련된 다양한 문제 유형(누적 합, 동적 계획법, DFS 기반 탐색 등)을 해결하기 위한 예제 함수들을 포함합니다.
 * 각 함수는 상세한 주석과 함께 구현되어 있어, 코드만 보더라도 알고리즘의 동작 원리 및 시간/공간 복잡도를 쉽게 이해할 수 있도록 작성되었습니다.
 *
 * 참고: 이 파일에는 main 함수가 포함되어 있지 않으므로, 별도의 테스트 코드나 main 함수를 작성하여
 *        이 함수들을 호출하고 검증할 수 있습니다.
 */
