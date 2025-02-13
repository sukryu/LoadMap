/*
 * main.c
 *
 * 이 파일은 유니온 파인드(Union-Find, Disjoint Set) 자료구조의 고도화된 구현 예제입니다.
 * 유니온 파인드는 여러 원소들이 속한 집합들을 효율적으로 관리하며, 두 원소가 같은 집합에 속하는지
 * 빠르게 판별할 수 있는 자료구조입니다.
 *
 * 이 구현은 경로 압축(Path Compression)과 랭크 기반 합치기(Union by Rank)를 포함하여,
 * 실무에서 사용될 수 있을 만큼 최적화되어 있습니다.
 *
 * 주요 기능:
 * - createDisjointSet: 주어진 원소 개수(n)로 초기 유니온 파인드 자료구조를 생성합니다.
 * - find: 주어진 원소의 대표(루트)를 경로 압축 기법을 통해 찾습니다.
 * - unionSet: 두 원소의 집합을 랭크 기반 합치기로 하나의 집합으로 합칩니다.
 * - printSets: 현재 각 원소의 대표를 출력하여, 집합의 상태를 확인합니다.
 * - freeDisjointSet: 할당된 메모리를 해제합니다.
 *
 * 이 구현은 B+ Tree의 고도화된 구현 스타일을 참고하여, 복잡한 최적화 기법을 모두 적용하였으며,
 * 에러 처리 및 메모리 관리에도 신경 썼습니다.
 *
 * 참고: 실제 환경에서는 동적 크기 조정, 스레드 안전성 등의 추가적인 최적화가 필요할 수 있습니다.
 */

#include <stdio.h>
#include <stdlib.h>

// 유니온 파인드 자료구조 정의 (Disjoint Set)
typedef struct DisjointSet {
    int n;          // 총 원소 개수
    int *parent;    // parent[i]는 원소 i의 부모를 가리킵니다.
    int *rank;      // rank[i]는 원소 i가 루트인 트리의 높이(예상)를 나타냅니다.
} DisjointSet;

/*
 * createDisjointSet 함수:
 * 주어진 n(원소 개수)에 대해 유니온 파인드 자료구조를 생성하고 초기화합니다.
 * 초기에는 모든 원소가 자신을 부모로 가지며, rank는 0으로 설정됩니다.
 */
DisjointSet* createDisjointSet(int n) {
    DisjointSet *ds = (DisjointSet*) malloc(sizeof(DisjointSet));
    if (!ds) {
        fprintf(stderr, "DisjointSet 구조체 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    ds->n = n;
    ds->parent = (int*) malloc(n * sizeof(int));
    ds->rank = (int*) malloc(n * sizeof(int));
    if (!ds->parent || !ds->rank) {
        fprintf(stderr, "DisjointSet 내부 배열 메모리 할당 실패!\n");
        free(ds->parent);
        free(ds->rank);
        free(ds);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        ds->parent[i] = i;   // 초기에는 각 원소가 자신의 집합을 대표함.
        ds->rank[i] = 0;     // 초기 트리 높이는 0
    }
    return ds;
}

/*
 * find 함수:
 * 경로 압축(Path Compression) 기법을 사용하여, 원소 x의 대표(루트)를 찾습니다.
 * 재귀적으로 호출하여, x가 직접 루트를 가리키도록 함으로써 이후의 find 연산을 최적화합니다.
 */
int find(DisjointSet *ds, int x) {
    if (ds->parent[x] != x)
        ds->parent[x] = find(ds, ds->parent[x]);
    return ds->parent[x];
}

/*
 * unionSet 함수:
 * 랭크 기반 합치기(Union by Rank)를 사용하여, 원소 x와 y가 속한 집합을 합칩니다.
 * 두 집합의 루트 중 랭크가 낮은 쪽을 높은 쪽에 연결하여 트리의 높이가 최소화되도록 합니다.
 */
void unionSet(DisjointSet *ds, int x, int y) {
    int rootX = find(ds, x);
    int rootY = find(ds, y);
    
    if (rootX == rootY)
        return; // 이미 같은 집합에 속함
    
    // 루트의 랭크를 비교하여 낮은 랭크의 트리를 높은 트리에 연결합니다.
    if (ds->rank[rootX] < ds->rank[rootY]) {
        ds->parent[rootX] = rootY;
    } else if (ds->rank[rootX] > ds->rank[rootY]) {
        ds->parent[rootY] = rootX;
    } else {
        ds->parent[rootY] = rootX;
        ds->rank[rootX]++;
    }
}

/*
 * printSets 함수:
 * 각 원소의 대표(루트)를 출력하여 현재 집합의 상태를 확인합니다.
 */
void printSets(DisjointSet *ds) {
    printf("각 원소의 대표(루트) 출력:\n");
    for (int i = 0; i < ds->n; i++) {
        printf("원소 %d -> 대표: %d\n", i, find(ds, i));
    }
}

/*
 * freeDisjointSet 함수:
 * 유니온 파인드 자료구조에 할당된 메모리를 해제합니다.
 */
void freeDisjointSet(DisjointSet *ds) {
    if (ds) {
        free(ds->parent);
        free(ds->rank);
        free(ds);
    }
}

/*
 * main 함수:
 * 유니온 파인드 자료구조의 주요 연산(생성, union, find, 상태 출력)을 시연합니다.
 */
int main(void) {
    int n = 10; // 0부터 9까지의 10개 원소
    DisjointSet *ds = createDisjointSet(n);
    
    printf("유니온 파인드 자료구조 초기 상태:\n");
    printSets(ds);
    printf("\n");

    // 집합 합치기 연산 수행
    // 예시: 0과 1을 합치고, 1과 2를 합친 후, 3과 4, 4와 5, 그리고 5와 6을 합칩니다.
    unionSet(ds, 0, 1);
    unionSet(ds, 1, 2);
    unionSet(ds, 3, 4);
    unionSet(ds, 4, 5);
    unionSet(ds, 5, 6);
    // 7과 8, 8과 9도 합칩니다.
    unionSet(ds, 7, 8);
    unionSet(ds, 8, 9);

    // 추가 합치기: 2와 4를 합쳐, 두 집합을 연결합니다.
    unionSet(ds, 2, 4);

    printf("합치기 연산 후 각 원소의 대표 출력:\n");
    printSets(ds);
    printf("\n");

    // 연결 여부 확인: 몇몇 원소가 같은 집합에 속하는지 확인
    int pairs[][2] = { {0, 6}, {0, 7}, {3, 6}, {7, 9} };
    int numPairs = sizeof(pairs) / (2 * sizeof(int));
    for (int i = 0; i < numPairs; i++) {
        int a = pairs[i][0];
        int b = pairs[i][1];
        if (find(ds, a) == find(ds, b))
            printf("원소 %d와 %d는 같은 집합에 속합니다.\n", a, b);
        else
            printf("원소 %d와 %d는 다른 집합에 속합니다.\n", a, b);
    }
    
    // 메모리 해제
    freeDisjointSet(ds);
    printf("\n유니온 파인드 자료구조 메모리 해제 완료.\n");

    return 0;
}
