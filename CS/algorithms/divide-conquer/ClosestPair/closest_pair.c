/**
 * closest_pair.c
 *
 * 고도화된 Closest Pair of Points 알고리즘 구현 예제
 * - 이 파일은 평면 상의 점들 중에서 서로 가장 가까운 두 점의 거리를 분할 정복 기법을 통해 O(n log n) 시간 복잡도로 계산합니다.
 * - 기본 아이디어는 점들을 x좌표 기준으로 정렬한 후, 재귀적으로 문제를 분할하고, 분할 경계 근처의 점들에 대해
 *   y좌표 기준으로 정렬하여 추가 비교를 수행하는 것입니다.
 * - 이 구현체는 동적 메모리 관리, 에러 처리 및 상세한 주석을 포함하여 실무 환경에서도 바로 사용할 수 있도록 작성되었습니다.
 *
 * 컴파일 예시: gcc -Wall -O2 closest_pair.c -o closest_pair -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

// Point 구조체: 평면 상의 점 (x, y)
typedef struct {
    double x;
    double y;
} Point;

// Comparator: x 좌표 기준 오름차순 정렬
int compareX(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    if (p1->x < p2->x) return -1;
    else if (p1->x > p2->x) return 1;
    else return 0;
}

// Comparator: y 좌표 기준 오름차순 정렬
int compareY(const void* a, const void* b) {
    Point* p1 = *(Point**)a;
    Point* p2 = *(Point**)b;
    if (p1->y < p2->y) return -1;
    else if (p1->y > p2->y) return 1;
    else return 0;
}

// Function: Euclidean distance between two points
double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
                (p1.y - p2.y)*(p1.y - p2.y));
}

// Brute force method for small number of points (n <= 3)
double bruteForce(Point points[], int n) {
    double minDist = DBL_MAX;
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++) {
            double d = distance(points[i], points[j]);
            if (d < minDist)
                minDist = d;
        }
    return minDist;
}

/**
 * stripClosest - Find the smallest distance among points in the strip.
 * @strip: 배열 of pointers to points that lie within d of the midline.
 * @size: the number of points in the strip.
 * @d: current minimum distance.
 *
 * 반환값: 최소 거리 in the strip (possibly smaller than d).
 * 이 함수는 strip 내의 점들을 y 좌표 기준으로 정렬한 후, 
 * 각 점에 대해 최대 6개 이하의 인접 점만을 검사합니다.
 */
double stripClosest(Point* strip[], int size, double d) {
    qsort(strip, size, sizeof(Point*), compareY);
    double minDist = d;
    
    // 각 점마다 최대 6개 이내의 다음 점들과 비교 (이론상 최대 7개 비교)
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && (strip[j]->y - strip[i]->y) < minDist; j++) {
            double distIJ = distance(*strip[i], *strip[j]);
            if (distIJ < minDist)
                minDist = distIJ;
        }
    }
    return minDist;
}

/**
 * closestUtil - 재귀적으로 Closest Pair distance를 계산하는 함수.
 * @points: 정렬된 점 배열 (by x-coordinate).
 * @n: 배열의 크기.
 *
 * 반환값: 점들 사이의 최소 거리를 반환합니다.
 */
double closestUtil(Point points[], int n) {
    // 기저 사례: 점이 3개 이하이면 brute force 사용.
    if (n <= 3)
        return bruteForce(points, n);
    
    int mid = n / 2;
    Point midPoint = points[mid];
    
    // 재귀적으로 왼쪽과 오른쪽 부분의 최소 거리를 계산
    double dl = closestUtil(points, mid);
    double dr = closestUtil(points + mid, n - mid);
    double d = (dl < dr) ? dl : dr;
    
    // 분할 경계에 가까운 점들을 strip 배열에 저장 (x 좌표 차이가 d보다 작음)
    Point** strip = (Point**)malloc(n * sizeof(Point*));
    if (!strip) {
        fprintf(stderr, "메모리 할당 실패 (closestUtil: strip)\n");
        exit(EXIT_FAILURE);
    }
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(points[i].x - midPoint.x) < d) {
            strip[j] = &points[i];
            j++;
        }
    }
    
    // strip 영역에서의 최소 거리 계산
    double stripMin = stripClosest(strip, j, d);
    free(strip);
    
    return (d < stripMin) ? d : stripMin;
}

/**
 * closestPair - 점들 사이의 최소 거리를 계산하는 메인 함수.
 * @points: 평면상의 점들을 담은 배열.
 * @n: 점의 개수.
 *
 * 반환값: 두 점 사이의 최소 거리.
 *
 * 이 함수는 먼저 점들을 x 좌표 기준으로 정렬한 후, 재귀적으로 Closest Pair 문제를 해결합니다.
 */
double closestPair(Point points[], int n) {
    qsort(points, n, sizeof(Point), compareX);
    return closestUtil(points, n);
}

/**
 * main - Closest Pair of Points 알고리즘 데모
 *
 * 이 함수는 예제 점 배열을 생성하고, 가장 가까운 두 점 사이의 거리를 계산하여 출력합니다.
 */
int main(void) {
    // 예제: 평면상의 10개의 점
    Point points[] = {
        {2.1, 3.2}, {12.3, 30.7}, {40.1, 50.5}, {5.0, 1.2},
        {12.0, 10.3}, {3.5, 4.8}, {20.0, 20.0}, {25.5, 30.0},
        {18.0, 18.0}, {7.0, 8.0}
    };
    int n = sizeof(points) / sizeof(points[0]);
    
    double minDist = closestPair(points, n);
    printf("가장 가까운 두 점 사이의 최소 거리: %.4f\n", minDist);
    
    return 0;
}