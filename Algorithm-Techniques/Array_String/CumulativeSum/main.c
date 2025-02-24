/*
 * main.c
 *
 * 이 파일은 코딩 테스트에서 누적 합 기법(Cumulative Sum)을 활용하여 다양한 문제를 해결하기 위한 예제 함수들을 포함합니다.
 * 각 함수는 누적 합 기법을 적용한 최적의 해결책을 제시하며, 시간 및 공간 복잡도를 고려하여 구현되었습니다.
 * 아래 함수들은 매우 상세한 주석을 포함하고 있어, 코드만 보더라도 각 알고리즘의 동작 원리와 구현 방법을 쉽게 이해할 수 있습니다.
 *
 * 포함된 함수 목록:
 * 1. buildPrefixSum:
 *      - 문제: 1차원 정수 배열의 누적 합(Prefix Sum) 배열 생성
 *      - 기법: 단순 반복을 통한 누적 합 계산
 * 2. rangeSum:
 *      - 문제: 누적 합 배열을 이용하여 원본 배열의 특정 구간의 합을 O(1)에 계산
 * 3. build2DPrefixSum:
 *      - 문제: 2차원 정수 배열(행렬)의 누적 합 배열 생성
 *      - 기법: 2차원 누적 합 계산 (포함, 보정 처리)
 * 4. rangeSum2D:
 *      - 문제: 2차원 누적 합 배열을 이용하여 특정 서브 매트릭스의 합을 O(1)에 계산
 *
 * 주의: 이 파일에는 main 함수는 포함되어 있지 않습니다.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 함수: buildPrefixSum
 * --------------------------------
 * 설명:
 *   주어진 1차원 정수 배열 'arr'의 누적 합(Prefix Sum) 배열을 생성합니다.
 *   누적 합 배열은 원본 배열의 각 원소까지의 합을 미리 계산하여, 이후 구간 합을 O(1) 시간에 조회할 수 있도록 합니다.
 *
 * 매개변수:
 *   - arr: 원본 정수 배열
 *   - n: 원본 배열의 길이
 *
 * 반환값:
 *   동적 할당된 누적 합 배열의 포인터. 배열의 길이는 n+1이며, P[0] = 0으로 초기화됩니다.
 *   (구간 합 계산 시, 배열 A의 [l, r] 구간의 합은 P[r+1] - P[l]로 계산)
 *
 * 시간 복잡도: O(n) (누적 합 배열 구성)
 * 공간 복잡도: O(n) (누적 합 배열에 추가 공간 사용)
 */
int* buildPrefixSum(int* arr, int n) {
    // 누적 합 배열의 크기는 n+1 (P[0]은 0)
    int* prefix = (int*)malloc((n + 1) * sizeof(int));
    if (prefix == NULL) {
        // 메모리 할당 실패시 NULL 반환
        return NULL;
    }
    
    // 초기값 설정: P[0] = 0
    prefix[0] = 0;
    
    // i = 1부터 n까지 누적 합 계산: prefix[i] = prefix[i-1] + arr[i-1]
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + arr[i - 1];
    }
    
    return prefix;
}

/*
 * 함수: rangeSum
 * --------------------------------
 * 설명:
 *   누적 합 배열을 이용하여 원본 배열의 구간 합을 O(1) 시간에 계산합니다.
 *   주어진 구간 [l, r] (0-indexed)의 합은 prefix[r+1] - prefix[l]로 계산됩니다.
 *
 * 매개변수:
 *   - prefix: 누적 합 배열 (buildPrefixSum 함수를 통해 생성됨)
 *   - l: 구간의 시작 인덱스 (0-indexed)
 *   - r: 구간의 종료 인덱스 (0-indexed)
 *
 * 반환값:
 *   구간 [l, r]의 합 (정수 값)
 *
 * 주의:
 *   l과 r의 값이 원본 배열의 범위를 벗어나지 않는지 호출 전에 반드시 확인해야 합니다.
 *
 * 시간 복잡도: O(1)
 * 공간 복잡도: O(1)
 */
int rangeSum(int* prefix, int l, int r) {
    return prefix[r + 1] - prefix[l];
}

/*
 * 함수: build2DPrefixSum
 * --------------------------------
 * 설명:
 *   주어진 2차원 정수 배열(행렬) 'matrix'의 누적 합 배열을 생성합니다.
 *   2차원 누적 합 배열은 각 위치 (i, j)까지의 합을 미리 계산하여,
 *   이후 특정 영역의 합을 O(1) 시간에 계산할 수 있도록 합니다.
 *
 * 매개변수:
 *   - matrix: 2차원 정수 배열 (행렬), 각 행은 int 배열로 구성됨
 *   - rows: 행렬의 행 수
 *   - cols: 행렬의 열 수
 *
 * 반환값:
 *   동적 할당된 2차원 누적 합 배열의 포인터.
 *   누적 합 배열 P의 크기는 (rows+1) x (cols+1)이며,
 *   P[i][j]는 matrix[0..i-1][0..j-1]의 합을 나타냅니다.
 *
 * 시간 복잡도: O(rows * cols)
 * 공간 복잡도: O(rows * cols)
 *
 * 주의:
 *   동적 할당된 2차원 배열의 메모리 해제는 호출 측에서 적절히 수행해야 합니다.
 */
int** build2DPrefixSum(int** matrix, int rows, int cols) {
    // (rows+1) x (cols+1) 크기의 2차원 배열 할당
    int** prefix = (int**)malloc((rows + 1) * sizeof(int*));
    if (prefix == NULL) {
        // 메모리 할당 실패 시, 바로 NULL 반환
        return NULL;
    }

    // 2차원 할당 루프
    for (int i = 0; i <= rows; i++) {
        prefix[i] = (int*)malloc((cols + 1) * sizeof(int));
        if (prefix[i] == NULL) {
            // ========== 수정된 부분 시작 ==========
            // 지금까지 할당된 i개 분량 해제
            for (int k = 0; k < i; k++) {
                free(prefix[k]);
            }
            // prefix 자체도 해제
            free(prefix);
            // NULL 반환
            return NULL;
            // ========== 수정된 부분 끝 ==========
        }
    }

    // 첫 행과 첫 열을 0으로 초기화
    for (int i = 0; i <= rows; i++) {
        prefix[i][0] = 0;
    }
    for (int j = 0; j <= cols; j++) {
        prefix[0][j] = 0;
    }

    // 실제 누적 합 계산
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            prefix[i][j] = prefix[i-1][j]
                         + prefix[i][j-1]
                         - prefix[i-1][j-1]
                         + matrix[i-1][j-1];
        }
    }
    return prefix;  // 성공적으로 할당, 계산 완료
}

/*
 * 함수: rangeSum2D
 * --------------------------------
 * 설명:
 *   2차원 누적 합 배열을 이용하여 주어진 2차원 배열의 특정 영역(서브 매트릭스)의 합을 O(1) 시간에 계산합니다.
 *   영역의 좌상단 좌표 (r1, c1)와 우하단 좌표 (r2, c2) (0-indexed)를 입력받아, 해당 영역의 합을 반환합니다.
 *
 * 매개변수:
 *   - prefix: 2차원 누적 합 배열 (build2DPrefixSum 함수를 통해 생성됨)
 *   - r1: 영역의 시작 행 (0-indexed)
 *   - c1: 영역의 시작 열 (0-indexed)
 *   - r2: 영역의 종료 행 (0-indexed)
 *   - c2: 영역의 종료 열 (0-indexed)
 *
 * 반환값:
 *   영역 (r1, c1)부터 (r2, c2)까지의 합 (정수 값)
 *
 * 구간 합 계산 공식:
 *   sum = P[r2+1][c2+1] - P[r1][c2+1] - P[r2+1][c1] + P[r1][c1]
 *
 * 시간 복잡도: O(1)
 * 공간 복잡도: O(1)
 */
int rangeSum2D(int** prefix, int r1, int c1, int r2, int c2) {
    return prefix[r2 + 1][c2 + 1] - prefix[r1][c2 + 1]
         - prefix[r2 + 1][c1] + prefix[r1][c1];
}

/*
 * End of main.c
 *
 * 이 파일은 코딩 테스트에서 누적 합 기법을 활용하여 다양한 문제를 해결하기 위한 예제 함수들을 포함합니다.
 * 각 함수는 상세한 주석과 함께 구현되어 있어, 코드만 보더라도 누적 합 기법의 동작 원리 및 시간/공간 복잡도를 쉽게 이해할 수 있도록 작성되었습니다.
 *
 * 참고: main 함수는 포함되어 있지 않으므로, 별도의 테스트 코드나 main 함수를 작성하여
 * 이 함수들을 호출 및 검증할 수 있습니다.
 */
