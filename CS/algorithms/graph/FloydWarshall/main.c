/**
 * main.c
 *
 * 고도화된 플로이드-워셜 알고리즘(Floyd-Warshall Algorithm) 구현 예제
 * - 이 파일은 인접 행렬로 표현된 가중치 방향 그래프에서 모든 쌍의 최단 경로를 계산하는 구현체입니다.
 * - 동적 메모리 할당, 에러 처리, 그리고 경로 계산 시 음의 가중치를 안전하게 처리하는 기능을 포함하여 실무 환경에서 바로 사용할 수 있도록 작성되었습니다.
 *
 * 컴파일 예시: gcc -Wall -O2 floyd_warshall.c -o floyd_warshall
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX  // 무한대 값; 단, INF와의 덧셈 시 오버플로우 주의

/**
 * allocateMatrix - V x V 크기의 2차원 정수 행렬을 동적 할당합니다.
 * @V: 행렬의 차원(정점의 수)
 *
 * 반환값: 동적 할당된 2차원 정수 배열의 포인터.
 *         메모리 할당에 실패하면 프로그램을 종료합니다.
 */
int** allocateMatrix(int V) {
    int **matrix = (int **)malloc(V * sizeof(int *));
    if (matrix == NULL) {
        fprintf(stderr, "행렬 메모리 할당 실패 (allocateMatrix)\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < V; i++) {
        matrix[i] = (int *)malloc(V * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "행렬 메모리 할당 실패 (allocateMatrix row %d)\n", i);
            // Free already allocated rows
            for (int j = 0; j < i; j++)
                free(matrix[j]);
            free(matrix);
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

/**
 * freeMatrix - 동적 할당된 2차원 행렬의 메모리를 해제합니다.
 * @matrix: 해제할 행렬 포인터
 * @V: 행렬의 차원(행의 수)
 */
void freeMatrix(int **matrix, int V) {
    for (int i = 0; i < V; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

/**
 * floydWarshall - 플로이드-워셜 알고리즘을 이용하여 모든 쌍의 최단 경로를 계산합니다.
 * @graph: 원본 그래프의 가중치 인접 행렬 (V x V 크기)
 * @V: 정점의 수
 *
 * 반환값: 동적 할당된 최단 경로 행렬 (V x V 크기)
 *         도달 불가능한 경로는 INF로 표시됩니다.
 *         호출자가 결과 행렬을 freeMatrix()로 메모리 해제해야 합니다.
 */
int** floydWarshall(int **graph, int V) {
    // allocate the distance matrix and initialize it with graph values
    int **dist = allocateMatrix(V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Compute all-pairs shortest paths
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            // Skip if there's no path from i to k
            if (dist[i][k] == INF)
                continue;
            for (int j = 0; j < V; j++) {
                // If both subpaths exist and the new path is shorter, update
                if (dist[k][j] != INF && dist[i][k] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    return dist;
}

/**
 * printMatrix - 행렬을 출력하는 유틸리티 함수
 * @matrix: 출력할 2차원 정수 행렬
 * @V: 행렬의 크기 (V x V)
 */
void printMatrix(int **matrix, int V) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (matrix[i][j] == INF)
                printf("%7s ", "INF");
            else
                printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

/**
 * main - 플로이드-워셜 알고리즘 데모
 *
 * 이 함수는 예제 그래프를 생성하고, 플로이드-워셜 알고리즘을 통해 모든 쌍의 최단 경로를 계산한 후,
 * 결과 행렬을 출력합니다.
 */
int main(void) {
    // 예제 그래프: 4개의 정점을 가진 그래프
    // 인접 행렬 표현; INF는 연결이 없음을 의미
    int V = 4;
    int **graph = allocateMatrix(V);

    // 그래프 초기화
    // 예제 값:
    //    0   5   INF 10
    //  INF   0   3   INF
    //  INF INF   0    1
    //  INF INF INF   0
    graph[0][0] = 0;    graph[0][1] = 5;    graph[0][2] = INF;  graph[0][3] = 10;
    graph[1][0] = INF;  graph[1][1] = 0;    graph[1][2] = 3;    graph[1][3] = INF;
    graph[2][0] = INF;  graph[2][1] = INF;  graph[2][2] = 0;    graph[2][3] = 1;
    graph[3][0] = INF;  graph[3][1] = INF;  graph[3][2] = INF;  graph[3][3] = 0;

    printf("원본 그래프의 인접 행렬:\n");
    printMatrix(graph, V);
    printf("\n");

    // 플로이드-워셜 알고리즘 실행
    int **dist = floydWarshall(graph, V);
    if (dist == NULL) {
        fprintf(stderr, "플로이드-워셜 알고리즘 실행 실패\n");
        freeMatrix(graph, V);
        exit(EXIT_FAILURE);
    }

    printf("모든 쌍의 최단 경로 (Floyd-Warshall 결과):\n");
    printMatrix(dist, V);

    // 동적 할당된 메모리 해제
    freeMatrix(graph, V);
    freeMatrix(dist, V);
    return 0;
}