/*
 * main.c
 *
 * 이 파일은 펜윅 트리(Fenwick Tree, Binary Indexed Tree)를 활용한 예제입니다.
 * 펜윅 트리는 배열의 누적 합(prefix sum)과 단일 원소 업데이트를 효율적으로 처리하는 자료구조로,
 * 각 연산이 O(log n) 시간 내에 처리됩니다.
 *
 * 주요 기능:
 * - buildFenwickTree: 주어진 배열을 기반으로 펜윅 트리를 구성합니다.
 * - updateFenwickTree: 배열의 특정 인덱스 값을 변경하고, 관련 누적합 정보를 O(log n) 시간에 갱신합니다.
 * - queryFenwickTree: 1부터 주어진 인덱스까지의 누적합을 O(log n) 시간에 계산합니다.
 * - printFenwickTree: 내부 BIT 배열을 출력하여 구조를 확인할 수 있습니다.
 * - freeFenwickTree: 펜윅 트리에 할당된 메모리를 해제합니다.
 *
 * 이 구현은 세그먼트 트리의 구현 방식과 유사한 스타일로, 복잡한 구간 질의와 업데이트를 단순화한 형태로 작성되었습니다.
 *
 * 참고: 실제 실무 환경에서는 에러 처리, 동적 크기 조정 등 추가적인 최적화가 필요할 수 있습니다.
 */

#include <stdio.h>
#include <stdlib.h>

// 펜윅 트리 구조체 정의 (1-indexed 배열 사용)
typedef struct {
    int *tree;  // BIT 배열: 인덱스 1부터 n까지 사용
    int n;      // 원본 배열의 크기
} FenwickTree;

/*
 * createFenwickTree 함수:
 * 주어진 크기(n)를 기반으로 펜윅 트리 구조체를 생성하고, BIT 배열을 0으로 초기화합니다.
 */
FenwickTree* createFenwickTree(int n) {
    FenwickTree *ft = (FenwickTree*) malloc(sizeof(FenwickTree));
    if (ft == NULL) {
        fprintf(stderr, "FenwickTree 구조체 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    ft->n = n;
    // BIT 배열은 1-indexed 이므로 크기는 n+1로 할당
    ft->tree = (int*) calloc(n + 1, sizeof(int));
    if (ft->tree == NULL) {
        fprintf(stderr, "BIT 배열 메모리 할당 실패!\n");
        free(ft);
        exit(EXIT_FAILURE);
    }
    return ft;
}

/*
 * updateFenwickTree 함수:
 * 펜윅 트리의 BIT 배열에서 index 위치부터 끝까지, 
 * val 값을 더하는 업데이트를 수행합니다.
 * 이 함수는 단일 원소 업데이트를 O(log n) 시간에 처리합니다.
 */
void updateFenwickTree(FenwickTree *ft, int index, int val) {
    // index는 1부터 시작해야 함
    while (index <= ft->n) {
        ft->tree[index] += val;
        // index의 마지막 1 비트만큼 증가
        index += index & (-index);
    }
}

/*
 * queryFenwickTree 함수:
 * 펜윅 트리를 이용해 1부터 index까지의 누적합(prefix sum)을 계산하여 반환합니다.
 * 이 함수는 O(log n) 시간에 누적합을 계산합니다.
 */
int queryFenwickTree(FenwickTree *ft, int index) {
    int sum = 0;
    while (index > 0) {
        sum += ft->tree[index];
        // index의 마지막 1 비트를 제거
        index -= index & (-index);
    }
    return sum;
}

/*
 * buildFenwickTree 함수:
 * 주어진 배열(arr) (0-indexed)을 기반으로 펜윅 트리를 구축합니다.
 * BIT 배열은 초기에는 0으로 초기화한 후, updateFenwickTree를 반복 호출하여 구성됩니다.
 */
FenwickTree* buildFenwickTree(int arr[], int n) {
    FenwickTree *ft = createFenwickTree(n);
    // 배열 arr의 각 원소를 BIT에 반영 (인덱스는 1부터 시작)
    for (int i = 0; i < n; i++) {
        updateFenwickTree(ft, i + 1, arr[i]);
    }
    return ft;
}

/*
 * printFenwickTree 함수:
 * BIT 배열의 내부 상태를 출력하여 펜윅 트리의 구조를 디버깅할 수 있도록 합니다.
 */
void printFenwickTree(FenwickTree *ft) {
    printf("Fenwick Tree (BIT 배열) 상태:\n");
    for (int i = 1; i <= ft->n; i++) {
        printf("Index %d: %d\n", i, ft->tree[i]);
    }
}

/*
 * freeFenwickTree 함수:
 * 펜윅 트리에 할당된 메모리를 해제합니다.
 */
void freeFenwickTree(FenwickTree *ft) {
    if (ft) {
        free(ft->tree);
        free(ft);
    }
}

/*
 * main 함수:
 * 예제 배열을 기반으로 펜윅 트리를 구축하고, 누적합 질의 및 업데이트 연산을 수행하는 예제입니다.
 */
int main(void) {
    // 예제 배열 (0-indexed)
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("원본 배열: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    // 펜윅 트리 구축
    FenwickTree *ft = buildFenwickTree(arr, n);
    printf("펜윅 트리 구축 완료.\n");
    printFenwickTree(ft);
    printf("\n");

    // 누적합 질의: 예를 들어, 인덱스 1부터 4까지의 합 계산 (인덱스 1~4 -> BIT query at index 4)
    int query_index = 4;
    int prefixSum = queryFenwickTree(ft, query_index);
    printf("누적합 질의 (1부터 %d까지): %d\n", query_index, prefixSum);

    // 단일 원소 업데이트: 예를 들어, 원본 배열의 인덱스 3(값 7)에 5를 더함
    int update_index = 3;  // 0-indexed, BIT index는 update_index+1
    int update_val = 5;
    printf("\n업데이트: 인덱스 %d의 값에 %d를 더합니다.\n", update_index, update_val);
    updateFenwickTree(ft, update_index + 1, update_val);

    // 업데이트 후, 다시 누적합 질의
    prefixSum = queryFenwickTree(ft, query_index);
    printf("업데이트 후 누적합 질의 (1부터 %d까지): %d\n", query_index, prefixSum);

    // 전체 배열의 누적합 질의
    int totalSum = queryFenwickTree(ft, n);
    printf("전체 배열의 누적합: %d\n\n", totalSum);

    // BIT 배열 상태 출력
    printFenwickTree(ft);

    // 메모리 해제
    freeFenwickTree(ft);
    printf("\n펜윅 트리 메모리 해제 완료.\n");

    return 0;
}