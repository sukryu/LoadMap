/*
 * Chord DHT Demo
 *
 * 이 예제는 Chord 분산 해시 테이블(DHT)의 핵심 프로토콜을 단일 프로세스 내에서 시뮬레이션합니다.
 * 노드들은 0부터 2^M-1 (여기서는 0 ~ 255) 범위의 식별자를 가지며, 원형 링 구조로 연결됩니다.
 * 각 노드는 Finger Table을 유지하여, 로그 시간 내에 키의 소유 노드(즉, successor)를 찾을 수 있습니다.
 *
 * 주요 기능:
 *  - create_node(): 새로운 노드를 생성합니다.
 *  - join(): 새로운 노드를 기존 Chord 링에 추가합니다.
 *  - find_successor(): 주어진 키의 successor를 찾습니다.
 *  - fix_fingers(): 각 노드의 Finger Table을 갱신합니다.
 *  - stabilize(): 안정화 프로토콜을 통해 노드 간 연결을 갱신합니다.
 *  - print_ring(): 링 전체를 순회하며 노드 ID를 출력합니다.
 *
 * 주의: 이 구현은 단일 프로세스 내 시뮬레이션으로, 실제 분산 환경에서는
 * 네트워크 통신, 동시성 제어 및 안정화 알고리즘이 추가적으로 구현되어야 합니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define M 8                     // 식별자 비트 수
#define ID_SPACE (1 << M)       // 식별자 공간: 2^M (256)

// Chord 노드 구조체
typedef struct Node {
    int id;                     // 노드 식별자 (0 ~ 255)
    struct Node *successor;     // 후속 노드 (successor)
    struct Node *predecessor;   // 전임 노드 (predecessor)
    struct Node *finger[M];     // Finger Table: M개의 엔트리
} Node;

// 새로운 노드 생성 (id를 인자로 받음)
Node* create_node(int id) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    n->id = id;
    n->successor = n;      // 초기에는 자기 자신을 가리킴
    n->predecessor = n;
    for (int i = 0; i < M; i++) {
        n->finger[i] = n;
    }
    return n;
}

// 원형 공간에서 a와 b 사이에 x가 있는지 판단 (a < x <= b)
bool in_interval(int x, int a, int b) {
    if (a < b)
        return (x > a && x <= b);
    else  // wrap-around 경우
        return (x > a || x <= b);
}

// 노드 n에서 시작하여, 주어진 키의 successor를 찾음
Node* find_successor(Node *n, int key) {
    if (n == NULL)
        return NULL;
    // 만약 key가 (n->id, n->successor->id] 범위에 있으면, n->successor가 답임
    if (in_interval(key, n->id, n->successor->id))
        return n->successor;
    // 그렇지 않으면, n의 Finger Table에서 가장 가까운 선행 노드 찾기
    for (int i = M - 1; i >= 0; i--) {
        if (n->finger[i] != NULL && in_interval(n->finger[i]->id, n->id, key))
            return find_successor(n->finger[i], key);
    }
    return n->successor;
}

// 새로운 노드를 Chord 링에 참여시키는 함수
void join(Node **ring, Node *new_node) {
    if (*ring == NULL) {
        // 첫 노드인 경우, 자기 자신을 successor 및 predecessor로 설정
        *ring = new_node;
        new_node->successor = new_node;
        new_node->predecessor = new_node;
    } else {
        // 기존 링의 임의 노드(*ring)에서 새 노드의 successor를 찾음
        Node *succ = find_successor(*ring, new_node->id);
        new_node->successor = succ;
        new_node->predecessor = succ->predecessor;
        succ->predecessor->successor = new_node;
        succ->predecessor = new_node;
    }
}

// 각 노드의 Finger Table을 갱신하는 함수
void fix_fingers(Node *n) {
    if (n == NULL) return;
    for (int i = 0; i < M; i++) {
        int start = (n->id + (1 << i)) % ID_SPACE;
        n->finger[i] = find_successor(n, start);
    }
}

// 안정화 프로토콜: 노드 n가 자신의 successor 정보를 확인하고 갱신
void stabilize(Node *n) {
    if (n == NULL) return;
    Node *x = n->successor->predecessor;
    if (x && in_interval(x->id, n->id, n->successor->id))
        n->successor = x;
    n->successor->predecessor = n;
}

// 링 전체의 모든 노드에 대해 안정화와 Finger Table 갱신을 수행
void update_ring(Node *ring) {
    if (ring == NULL) return;
    Node *temp = ring;
    do {
        stabilize(temp);
        fix_fingers(temp);
        temp = temp->successor;
    } while (temp != ring);
}

// 링 구조 전체를 출력하는 함수
void print_ring(Node *start) {
    if (start == NULL) return;
    Node *n = start;
    printf("Chord Ring: ");
    do {
        printf("%d -> ", n->id);
        n = n->successor;
    } while (n != start);
    printf("(back to %d)\n", start->id);
}

// 각 노드의 Finger Table을 출력하는 함수
void print_finger_table(Node *n) {
    if (n == NULL) return;
    printf("Finger Table for Node %d:\n", n->id);
    for (int i = 0; i < M; i++) {
        printf("  Start: %d, Finger[%d]: %d\n", (n->id + (1 << i)) % ID_SPACE, i, n->finger[i]->id);
    }
}

int main(void) {
    Node *ring = NULL;
    
    // 예시 노드 ID 배열 (분산 환경에서는 무작위 분포)
    int node_ids[] = {10, 20, 50, 70, 90, 30, 60, 80};
    int n = sizeof(node_ids) / sizeof(node_ids[0]);
    
    // 각 노드를 생성하여 링에 참여
    for (int i = 0; i < n; i++) {
        Node *node = create_node(node_ids[i]);
        join(&ring, node);
        update_ring(ring);
        printf("Joined node %d\n", node_ids[i]);
    }
    
    // 링 구조 출력
    print_ring(ring);
    
    // 각 노드의 Finger Table 출력
    Node *temp = ring;
    do {
        print_finger_table(temp);
        temp = temp->successor;
    } while (temp != ring);
    
    // Lookup 테스트
    int lookup_keys[] = {5, 15, 35, 65, 95};
    int lookup_count = sizeof(lookup_keys) / sizeof(lookup_keys[0]);
    for (int i = 0; i < lookup_count; i++) {
        int key = lookup_keys[i];
        Node *succ = find_successor(ring, key);
        if (succ)
            printf("Lookup key %d -> successor is node %d\n", key, succ->id);
        else
            printf("Lookup key %d -> not found\n", key);
    }
    
    // 실제 환경에서는 각 노드의 메모리 해제 및 네트워크 종료 절차가 필요합니다.
    // 본 시뮬레이션에서는 메모리 해제를 생략합니다.
    
    return 0;
}