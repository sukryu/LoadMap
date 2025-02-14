/**
 * main.c
 *
 * 고도화된 A* (A-Star) 알고리즘 구현 예제
 * - 이 파일은 2차원 그리드에서 시작점으로부터 목표점까지 최적(최단) 경로를 찾기 위한 A* 알고리즘을 구현합니다.
 * - A* 알고리즘은 실제 비용(g-cost)과 휴리스틱 비용(h-cost)의 합(f-cost)을 기준으로
 *   우선순위 큐(최소 힙)를 사용해 경로를 탐색하며, 최적의 경로를 효율적으로 찾습니다.
 * - 이 구현체는 실무 환경에서 바로 사용할 수 있도록 동적 메모리 관리, 에러 처리 및 상세한 주석을 포함하여 작성되었습니다.
 *
 * 컴파일 예시: gcc -Wall -O2 main.c -o astar -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

// 그리드 크기 설정
#define ROWS 5
#define COLS 5

// 장애물로 사용할 값
#define OBSTACLE 1

// 이동 비용 (상하좌우 이동 비용: 1)
#define MOVE_COST 1

// 구조체: 그리드 상의 각 셀(Node)을 나타냄
typedef struct Node {
    int x, y;            // 셀의 좌표
    int f, g, h;         // f = g + h: f-cost, g: 실제 비용, h: 휴리스틱 비용
    int parentX, parentY; // 경로 재구성을 위한 부모 셀 좌표
    int open;            // 열린 목록에 있는지 여부 (0: 없음, 1: 있음)
    int closed;          // 닫힌 목록에 있는지 여부 (0: 없음, 1: 있음)
} Node;

// 구조체: 최소 힙(우선순위 큐)을 위한 배열, 노드 포인터들을 저장
typedef struct MinHeap {
    Node** data;         // 동적 배열, 노드 포인터들 저장
    int size;            // 현재 노드 수
    int capacity;        // 최대 용량
} MinHeap;

/*---------------- Utility Functions ----------------*/

/**
 * heuristic - 두 노드 사이의 맨해튼 거리 계산 (휴리스틱 함수)
 * @a: 시작 노드
 * @b: 목표 노드
 *
 * 반환값: 두 노드 간의 맨해튼 거리
 */
int heuristic(Node* a, Node* b) {
    return abs(a->x - b->x) + abs(a->y - b->y);
}

/**
 * createNode - 그리드 상의 노드를 초기화합니다.
 * @x: 노드의 x 좌표
 * @y: 노드의 y 좌표
 *
 * 반환값: 동적 할당된 Node 포인터 (초기 비용 값은 INT_MAX, open/closed 플래그 0)
 */
Node* createNode(int x, int y) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "메모리 할당 실패 (createNode)\n");
        exit(EXIT_FAILURE);
    }
    node->x = x;
    node->y = y;
    node->f = node->g = node->h = INT_MAX;
    node->parentX = node->parentY = -1;
    node->open = 0;
    node->closed = 0;
    return node;
}

/**
 * createMinHeap - 주어진 용량의 최소 힙을 생성합니다.
 * @capacity: 최소 힙의 초기 용량
 *
 * 반환값: 동적 할당된 MinHeap 포인터
 */
MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) {
        fprintf(stderr, "메모리 할당 실패 (createMinHeap)\n");
        exit(EXIT_FAILURE);
    }
    heap->data = (Node**)malloc(capacity * sizeof(Node*));
    if (!heap->data) {
        fprintf(stderr, "메모리 할당 실패 (createMinHeap: data)\n");
        free(heap);
        exit(EXIT_FAILURE);
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

/**
 * swapNodes - 두 노드 포인터를 교환합니다.
 */
void swapNodes(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * minHeapify - 인덱스 idx에서 최소 힙 속성을 유지하도록 힙을 재구성합니다.
 * @heap: 최소 힙 포인터
 * @idx: 현재 인덱스
 */
void minHeapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < heap->size && heap->data[left]->f < heap->data[smallest]->f)
        smallest = left;
    if (right < heap->size && heap->data[right]->f < heap->data[smallest]->f)
        smallest = right;
    if (smallest != idx) {
        swapNodes(&heap->data[smallest], &heap->data[idx]);
        minHeapify(heap, smallest);
    }
}

/**
 * insertMinHeap - 최소 힙에 노드를 삽입합니다.
 * @heap: 최소 힙 포인터
 * @node: 삽입할 Node 포인터
 */
void insertMinHeap(MinHeap* heap, Node* node) {
    // 동적 재할당: 힙이 가득 찼으면 용량을 2배로 확장
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        Node** newData = (Node**)realloc(heap->data, heap->capacity * sizeof(Node*));
        if (!newData) {
            fprintf(stderr, "메모리 재할당 실패 (insertMinHeap)\n");
            exit(EXIT_FAILURE);
        }
        heap->data = newData;
    }
    // 삽입: 새 노드를 배열 끝에 추가하고, 위로 올리며 최소 힙 속성 복원
    int i = heap->size++;
    heap->data[i] = node;
    while (i && heap->data[i]->f < heap->data[(i - 1) / 2]->f) {
        swapNodes(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    node->open = 1;
}

/**
 * extractMin - 최소 힙에서 가장 f-cost가 낮은 노드를 추출합니다.
 * @heap: 최소 힙 포인터
 *
 * 반환값: 추출된 Node 포인터, 힙이 비어있으면 NULL 반환.
 */
Node* extractMin(MinHeap* heap) {
    if (heap->size == 0)
        return NULL;
    Node* root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    minHeapify(heap, 0);
    root->open = 0;
    return root;
}

/**
 * freeMinHeap - 최소 힙에 할당된 메모리를 해제합니다.
 * @heap: 최소 힙 포인터
 */
void freeMinHeap(MinHeap* heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

/*---------------- A* Algorithm Implementation ----------------*/

/**
 * isValid - 주어진 좌표 (x, y)가 그리드 범위 내에 있는지 확인합니다.
 * @x: x 좌표
 * @y: y 좌표
 *
 * 반환값: 유효하면 1, 아니면 0.
 */
int isValid(int x, int y) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS);
}

/**
 * isUnBlocked - (x, y) 셀이 장애물이 아닌지 확인합니다.
 * @grid: 그리드 2차원 배열 (0: 자유, 1: 장애물)
 * @x: x 좌표
 * @y: y 좌표
 *
 * 반환값: 자유면 1, 장애물이면 0.
 */
int isUnBlocked(int grid[ROWS][COLS], int x, int y) {
    return (grid[x][y] == 0);
}

/**
 * isDestination - (x, y)가 목표 셀인지 확인합니다.
 * @x: 현재 x 좌표
 * @y: 현재 y 좌표
 * @destX: 목표 x 좌표
 * @destY: 목표 y 좌표
 *
 * 반환값: 목표면 1, 아니면 0.
 */
int isDestination(int x, int y, int destX, int destY) {
    return (x == destX && y == destY);
}

/**
 * calculateHValue - 현재 셀에서 목표 셀까지의 휴리스틱 비용(맨해튼 거리)을 계산합니다.
 * @x: 현재 x 좌표
 * @y: 현재 y 좌표
 * @destX: 목표 x 좌표
 * @destY: 목표 y 좌표
 *
 * 반환값: 맨해튼 거리
 */
int calculateHValue(int x, int y, int destX, int destY) {
    return abs(x - destX) + abs(y - destY);
}

/**
 * tracePath - 목표 셀에서 시작 셀까지 부모 정보를 따라 경로를 추적하여 출력합니다.
 * @cellDetails: 각 셀의 정보가 저장된 2차원 배열 (Node 구조체 배열)
 * @destX: 목표 x 좌표
 * @destY: 목표 y 좌표
 */
void tracePath(Node* cellDetails[ROWS][COLS], int destX, int destY) {
    printf("경로: ");
    int row = destX, col = destY;
    // 경로를 역순으로 추적하기 위해 임시 배열 사용 (최대 ROWS*COLS 길이)
    int pathSize = ROWS * COLS;
    int (*path)[2] = malloc(pathSize * sizeof(*path));
    if (!path) {
        fprintf(stderr, "메모리 할당 실패 (tracePath)\n");
        exit(EXIT_FAILURE);
    }
    int index = 0;
    
    while (!(cellDetails[row][col]->parentX == row && cellDetails[row][col]->parentY == col)) {
        path[index][0] = row;
        path[index][1] = col;
        index++;
        int tempRow = cellDetails[row][col]->parentX;
        int tempCol = cellDetails[row][col]->parentY;
        row = tempRow;
        col = tempCol;
    }
    // 시작 셀
    path[index][0] = row;
    path[index][1] = col;
    index++;
    
    // 경로를 역순으로 출력
    for (int i = index - 1; i >= 0; i--) {
        printf("(%d, %d) ", path[i][0], path[i][1]);
    }
    printf("\n");
    free(path);
}

/**
 * aStarSearch - A* 알고리즘을 사용하여 그리드에서 시작 셀에서 목표 셀까지 최적 경로를 찾습니다.
 * @grid: 2차원 그리드 배열 (0: 자유, 1: 장애물)
 * @startX: 시작 x 좌표
 * @startY: 시작 y 좌표
 * @destX: 목표 x 좌표
 * @destY: 목표 y 좌표
 *
 * 이 함수는 우선순위 큐(최소 힙)를 사용하여 열린 목록을 관리하고,
 * 각 셀에 대해 실제 비용(g), 휴리스틱 비용(h), 총 비용(f = g + h)를 계산합니다.
 * 목표 셀에 도달하면 경로를 추적하여 출력합니다.
 */
void aStarSearch(int grid[ROWS][COLS], int startX, int startY, int destX, int destY) {
    // 만약 시작 또는 목표 셀이 장애물이면 경로 탐색 불가
    if (!isUnBlocked(grid, startX, startY) || !isUnBlocked(grid, destX, destY)) {
        printf("시작 혹은 목표 셀이 장애물입니다.\n");
        return;
    }
    
    // 만약 시작 셀이 목표 셀이면 바로 종료
    if (isDestination(startX, startY, destX, destY)) {
        printf("시작 셀이 이미 목표 셀입니다.\n");
        return;
    }
    
    // 2차원 배열로 각 셀의 정보를 저장 (Node 포인터)
    Node* cellDetails[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cellDetails[i][j] = createNode(i, j);
            // 초기에는 자기 자신을 부모로 설정 (경로 추적을 위한 초기값)
            cellDetails[i][j]->parentX = i;
            cellDetails[i][j]->parentY = j;
        }
    }
    
    // 시작 셀 초기화
    cellDetails[startX][startY]->g = 0;
    cellDetails[startX][startY]->h = calculateHValue(startX, startY, destX, destY);
    cellDetails[startX][startY]->f = cellDetails[startX][startY]->g + cellDetails[startX][startY]->h;
    
    // 최소 힙(우선순위 큐) 초기화
    MinHeap* openList = createMinHeap(ROWS * COLS);
    insertMinHeap(openList, cellDetails[startX][startY]);
    
    // 방향 벡터 (상, 하, 좌, 우)
    int dirX[4] = {-1, 1, 0, 0};
    int dirY[4] = {0, 0, -1, 1};
    
    int foundDest = 0;
    
    // A* 알고리즘 메인 루프
    while (openList->size > 0) {
        // 열린 목록에서 f-cost가 가장 낮은 셀 추출
        Node* current = extractMin(openList);
        int x = current->x;
        int y = current->y;
        current->closed = 1;
        
        // 목표 셀에 도달하면 경로 추적 후 종료
        if (isDestination(x, y, destX, destY)) {
            foundDest = 1;
            tracePath(cellDetails, destX, destY);
            break;
        }
        
        // 인접 셀(상하좌우) 검사
        for (int i = 0; i < 4; i++) {
            int newX = x + dirX[i];
            int newY = y + dirY[i];
            // 유효한 좌표이고 장애물이 아니며 아직 닫힌 셀이 아닌 경우
            if (isValid(newX, newY) && isUnBlocked(grid, newX, newY) && !cellDetails[newX][newY]->closed) {
                int newG = current->g + MOVE_COST;
                int newH = calculateHValue(newX, newY, destX, destY);
                int newF = newG + newH;
                // 만약 새 경로가 더 좋은 경로이면 업데이트
                if (cellDetails[newX][newY]->f == INT_MAX || cellDetails[newX][newY]->f > newF) {
                    cellDetails[newX][newY]->g = newG;
                    cellDetails[newX][newY]->h = newH;
                    cellDetails[newX][newY]->f = newF;
                    cellDetails[newX][newY]->parentX = x;
                    cellDetails[newX][newY]->parentY = y;
                    // 열린 목록에 아직 추가되지 않았다면 추가
                    if (!cellDetails[newX][newY]->open)
                        insertMinHeap(openList, cellDetails[newX][newY]);
                }
            }
        }
    }
    
    if (!foundDest)
        printf("목표 셀에 도달할 수 있는 경로가 없습니다.\n");
    
    // 동적 할당된 메모리 해제: 열린 목록은 freeMinHeap()로, 각 셀은 별도로 해제
    freeMinHeap(openList);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            free(cellDetails[i][j]);
        }
    }
}

/*---------------- main 함수 (데모) ----------------*/
/**
 * main - A* 알고리즘 데모
 *
 * 이 함수는 5x5 그리드에서 시작점과 목표점을 지정하고,
 * A* 알고리즘을 통해 최적 경로를 찾은 후, 경로를 출력합니다.
 * 그리드에서 0은 자유 공간, 1은 장애물을 나타냅니다.
 */
int main(void) {
    // 예제 그리드 (5x5)
    // 0: 자유, 1: 장애물
    int grid[ROWS][COLS] = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    
    int startX = 0, startY = 0;
    int destX = 4, destY = 4;
    
    printf("A* 알고리즘 경로 탐색 데모:\n");
    aStarSearch(grid, startX, startY, destX, destY);
    
    return 0;
}
