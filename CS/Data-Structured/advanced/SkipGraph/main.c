/*
 * Skip Graph Demo
 *
 * 이 예제는 실무에서 바로 사용할 수 있도록 고도화한 Skip Graph의 구현 예제입니다.
 * Skip Graph는 분산 환경에서 효율적인 검색 및 범위 쿼리를 지원하는 확률적 자가 조직화 데이터 구조입니다.
 *
 * 본 구현은 단일 프로세스 내에서 Skip Graph의 핵심 기능(삽입, 검색, 삭제 및 레벨별 출력)을 
 * 시뮬레이션하는 간단한 인메모리 Skip Graph입니다.
 *
 * 주요 기능:
 *  - skip_graph_insert(): 새로운 노드를 확률적 레벨 결정(random level)을 통해 Skip Graph에 삽입합니다.
 *  - skip_graph_search(): 다중 레벨 포인터를 활용하여 키를 빠르게 탐색합니다.
 *  - skip_graph_delete(): 키에 해당하는 노드를 제거하고, 각 레벨의 링크를 재조정합니다.
 *  - skip_graph_print(): 각 레벨의 연결 리스트를 출력하여 전체 Skip Graph 구조를 확인합니다.
 *
 * 주의: Skip Graph는 분산 시스템에서 동적으로 노드가 참여 및 탈퇴하는 환경에 적합한 구조입니다.
 * 본 예제는 단일 프로세스 내에서 Skip List와 유사한 방식으로 구현하였으며,
 * 실무 환경에서는 네트워크 통신, 동시성 제어 및 복잡한 멤버십 벡터 관리가 추가되어야 합니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

#define MAX_LEVEL 16       // Skip Graph의 최대 레벨 (노드마다 가질 수 있는 레벨 수)
#define P 0.5              // 레벨 결정 확률

// Skip Graph 노드 구조체
typedef struct SkipGraphNode {
    int key;
    int value;
    int level;                        // 이 노드가 가진 레벨 수
    struct SkipGraphNode **next;      // 각 레벨별 오른쪽 링크 (다음 노드)
    struct SkipGraphNode **prev;      // 각 레벨별 왼쪽 링크 (이전 노드)
} SkipGraphNode;

// Skip Graph 구조체: 헤드와 테일 sentinel 노드를 포함
typedef struct SkipGraph {
    int max_level;
    float p;
    SkipGraphNode *head;  // 최소값(-∞) sentinel
    SkipGraphNode *tail;  // 최대값(+∞) sentinel
} SkipGraph;

/* 난수 기반 레벨 결정 함수 */
int random_level() {
    int lvl = 1;
    while (((float)rand() / RAND_MAX) < P && lvl < MAX_LEVEL)
        lvl++;
    return lvl;
}

/* 새 Skip Graph 노드 생성 */
SkipGraphNode* create_node(int key, int value, int level) {
    SkipGraphNode *node = (SkipGraphNode*) malloc(sizeof(SkipGraphNode));
    if (!node) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->value = value;
    node->level = level;
    node->next = (SkipGraphNode**) malloc(sizeof(SkipGraphNode*) * level);
    node->prev = (SkipGraphNode**) malloc(sizeof(SkipGraphNode*) * level);
    if (!node->next || !node->prev) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < level; i++) {
        node->next[i] = NULL;
        node->prev[i] = NULL;
    }
    return node;
}

/* Skip Graph 초기화: 헤드와 테일 sentinel 생성 */
SkipGraph* create_skip_graph() {
    SkipGraph *graph = (SkipGraph*) malloc(sizeof(SkipGraph));
    if (!graph) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    graph->max_level = MAX_LEVEL;
    graph->p = P;
    // 헤드: -∞, 테일: +∞
    graph->head = create_node(INT_MIN, 0, MAX_LEVEL);
    graph->tail = create_node(INT_MAX, 0, MAX_LEVEL);
    for (int i = 0; i < MAX_LEVEL; i++) {
        graph->head->next[i] = graph->tail;
        graph->tail->prev[i] = graph->head;
    }
    return graph;
}

/* Skip Graph 삽입 함수 */
void skip_graph_insert(SkipGraph *graph, int key, int value) {
    SkipGraphNode *update[MAX_LEVEL];
    SkipGraphNode *x = graph->head;
    
    // 각 레벨에서 update 배열에 삽입 위치의 직전 노드를 저장
    for (int i = MAX_LEVEL - 1; i >= 0; i--) {
        while (x->next[i] != graph->tail && x->next[i]->key < key)
            x = x->next[i];
        update[i] = x;
    }
    
    x = x->next[0];
    // 키가 이미 존재하면 값 업데이트
    if (x != graph->tail && x->key == key) {
        x->value = value;
        return;
    }
    
    int lvl = random_level();
    SkipGraphNode *new_node = create_node(key, value, lvl);
    
    // 각 레벨에서 new_node 삽입
    for (int i = 0; i < lvl; i++) {
        new_node->next[i] = update[i]->next[i];
        new_node->prev[i] = update[i];
        update[i]->next[i]->prev[i] = new_node;
        update[i]->next[i] = new_node;
    }
}

/* Skip Graph 검색 함수 */
bool skip_graph_search(SkipGraph *graph, int key, int *value) {
    SkipGraphNode *x = graph->head;
    for (int i = MAX_LEVEL - 1; i >= 0; i--) {
        while (x->next[i] != graph->tail && x->next[i]->key < key)
            x = x->next[i];
    }
    x = x->next[0];
    if (x != graph->tail && x->key == key) {
        *value = x->value;
        return true;
    }
    return false;
}

/* Skip Graph 삭제 함수 */
void skip_graph_delete(SkipGraph *graph, int key) {
    SkipGraphNode *update[MAX_LEVEL];
    SkipGraphNode *x = graph->head;
    for (int i = MAX_LEVEL - 1; i >= 0; i--) {
        while (x->next[i] != graph->tail && x->next[i]->key < key)
            x = x->next[i];
        update[i] = x;
    }
    x = x->next[0];
    if (x == graph->tail || x->key != key) {
        printf("Key %d not found for deletion.\n", key);
        return;
    }
    for (int i = 0; i < x->level; i++) {
        update[i]->next[i] = x->next[i];
        x->next[i]->prev[i] = update[i];
    }
    free(x->next);
    free(x->prev);
    free(x);
}

/* Skip Graph 레벨 순회 출력 함수 */
void skip_graph_print(SkipGraph *graph) {
    printf("Skip Graph Levels:\n");
    for (int i = MAX_LEVEL - 1; i >= 0; i--) {
        SkipGraphNode *x = graph->head->next[i];
        printf("Level %d: ", i);
        while (x != graph->tail) {
            printf("(%d:%d) ", x->key, x->value);
            x = x->next[i];
        }
        printf("\n");
    }
}

/* 전체 Skip Graph 메모리 해제 */
void free_skip_graph(SkipGraph *graph) {
    // 순차적 탐색: 레벨 0에서 모든 노드 해제 (헤드와 테일 제외)
    SkipGraphNode *x = graph->head->next[0];
    while (x != graph->tail) {
        SkipGraphNode *temp = x;
        x = x->next[0];
        free(temp->next);
        free(temp->prev);
        free(temp);
    }
    free(graph->head->next);
    free(graph->head->prev);
    free(graph->head);
    free(graph->tail->next);
    free(graph->tail->prev);
    free(graph->tail);
    free(graph);
}

/* --- main 함수 --- */
int main(void) {
    // 난수 초기화
    srand((unsigned int)time(NULL));
    
    SkipGraph *graph = create_skip_graph();
    
    printf("=== Skip Graph Demo ===\n\n");
    
    // 삽입 테스트
    int keys_to_insert[] = {10, 20, 5, 6, 12, 30, 7, 17, 25, 15, 27, 35, 3};
    int n = sizeof(keys_to_insert) / sizeof(keys_to_insert[0]);
    for (int i = 0; i < n; i++) {
        skip_graph_insert(graph, keys_to_insert[i], keys_to_insert[i] * 10);
        printf("Inserted key %d with value %d\n", keys_to_insert[i], keys_to_insert[i] * 10);
    }
    
    printf("\nSkip Graph Levels after insertions:\n");
    skip_graph_print(graph);
    
    // 검색 테스트
    int search_key = 12;
    int value;
    if (skip_graph_search(graph, search_key, &value))
        printf("\nSearch: Key %d found with value %d\n", search_key, value);
    else
        printf("\nSearch: Key %d not found\n", search_key);
    
    // 삭제 테스트
    int keys_to_delete[] = {6, 7, 10};
    int m = sizeof(keys_to_delete) / sizeof(keys_to_delete[0]);
    for (int i = 0; i < m; i++) {
        printf("\nDeleting key %d\n", keys_to_delete[i]);
        skip_graph_delete(graph, keys_to_delete[i]);
        skip_graph_print(graph);
    }
    
    // 최종 트리 출력
    printf("\nFinal Skip Graph Levels:\n");
    skip_graph_print(graph);
    
    // 메모리 해제
    free_skip_graph(graph);
    
    return 0;
}