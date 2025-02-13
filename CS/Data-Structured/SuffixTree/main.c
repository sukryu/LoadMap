/*
 * main.c
 *
 * 이 파일은 접미사 트리(Suffix Tree)의 고도화된 Naive 구현 예제입니다.
 * (주의: 효율적인 접미사 트리 알고리즘(예: Ukkonen의 알고리즘)은 구현이 매우 복잡하지만,
 *  본 예제는 교육용으로 모든 접미사를 나이브하게 삽입하는 방식을 사용합니다.)
 *
 * 주요 기능:
 * - buildSuffixTree: 입력 문자열의 모든 접미사를 트리에 삽입하여 접미사 트리를 구축합니다.
 * - printSuffixTree: 접미사 트리의 각 노드(에지)의 레이블과, 리프 노드인 경우 접미사 시작 인덱스를 출력합니다.
 * - freeSuffixTree: 접미사 트리에 할당된 모든 메모리를 재귀적으로 해제합니다.
 *
 * 이 구현은 B+ Tree의 고도화된 구현 스타일을 참고하여,  
 * 에러 처리 및 메모리 관리를 신경 쓴 단순 Naive 접미사 트리 구현입니다.
 *
 * 예제 문자열에는 고유의 종결 문자 '$'를 추가하여 접미사의 유일성을 보장합니다.
 *
 * 참고: 실제 실무에서는 Ukkonen의 알고리즘 등 더 효율적인 알고리즘을 사용해야 합니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26  // 가정: 입력 문자열은 영어 소문자만 사용

// 접미사 트리 노드 구조체
typedef struct SuffixTreeNode {
    int start;                  // 부모와 연결된 에지의 시작 인덱스 (문자열 내)
    int end;                    // 에지의 종료 인덱스 (문자열 내; 양쪽 모두 포함)
    int suffixIndex;            // 리프 노드인 경우, 해당 접미사의 시작 인덱스; 내부 노드는 -1
    struct SuffixTreeNode *children[ALPHABET_SIZE]; // 각 알파벳에 대한 자식 포인터 (없으면 NULL)
} SuffixTreeNode;

// 노드 생성: start, end 값을 초기화하며, suffixIndex는 -1로 설정 (내부 노드)
SuffixTreeNode* createNode(int start, int end) {
    SuffixTreeNode *node = (SuffixTreeNode*) malloc(sizeof(SuffixTreeNode));
    if (!node) {
        fprintf(stderr, "createNode: 메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    node->start = start;
    node->end = end;
    node->suffixIndex = -1;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

/*
 * insertSuffix 함수:
 * 주어진 문자열 text의 접미사 (pos에서 시작하는)를
 * 접미사 트리 rooted at 'root'에 삽입하는 나이브 알고리즘입니다.
 *
 * 동작:
 * - 현재 노드에서, text[pos]를 시작으로 하는 에지(자식)가 있으면,
 *   해당 에지와 접미사 간의 최대 공통 접두사를 찾습니다.
 * - 에지와 접미사가 부분적으로 일치하면, 에지를 분할(split)하고 새로운 노드를 삽입합니다.
 * - 해당 에지가 완전히 일치하면, 접미사 트리에서 더 깊은 자식으로 내려갑니다.
 */
void insertSuffix(SuffixTreeNode *root, const char *text, int pos) {
    int n = strlen(text);
    SuffixTreeNode *current = root;
    int i = pos;
    while (i < n) {
        int index = text[i] - 'a';
        if (index < 0 || index >= ALPHABET_SIZE) {
            fprintf(stderr, "insertSuffix: 잘못된 문자 '%c' 발견\n", text[i]);
            return;
        }
        if (current->children[index] == NULL) {
            // 해당 에지가 없으면, 새 리프 노드 생성 후 삽입
            SuffixTreeNode *leaf = createNode(i, n - 1);
            leaf->suffixIndex = pos;
            current->children[index] = leaf;
            return;
        }
        // 에지가 존재하면, 해당 자식 노드로 이동하며 최대 공통 접두사 길이를 계산
        SuffixTreeNode *child = current->children[index];
        int j = child->start;
        while (i < n && j <= child->end && text[i] == text[j]) {
            i++;
            j++;
        }
        if (j <= child->end) {
            // 분할 필요: 에지의 일부만 일치하는 경우
            SuffixTreeNode *split = createNode(child->start, j - 1);
            // 새로 분할된 노드의 자식: 기존 에지(자식)
            int childIndex = text[j] - 'a';
            split->children[childIndex] = child;
            child->start = j;
            // 새 리프 노드: 나머지 접미사 부분
            int newIndex = text[i] - 'a';
            SuffixTreeNode *leaf = createNode(i, n - 1);
            leaf->suffixIndex = pos;
            split->children[newIndex] = leaf;
            // 현재 노드의 자식을 split 노드로 교체
            current->children[index] = split;
            return;
        }
        // 에지의 전체가 일치한 경우, current를 자식으로 갱신하고 계속 진행
        current = child;
    }
    // 접미사가 완전히 일치하는 경우(이미 트리에 존재할 경우)
    current->suffixIndex = pos;
}

/*
 * buildSuffixTree 함수:
 * 입력 문자열 text의 모든 접미사를 접미사 트리에 삽입하여 트리를 구축합니다.
 */
SuffixTreeNode* buildSuffixTree(const char *text) {
    int n = strlen(text);
    // 루트 노드 생성: 루트 노드는 에지 레이블이 없으므로 start, end를 -1로 설정
    SuffixTreeNode *root = createNode(-1, -1);
    for (int i = 0; i < n; i++) {
        insertSuffix(root, text, i);
    }
    return root;
}

/*
 * printSuffixTree 함수:
 * 접미사 트리의 각 노드를 재귀적으로 출력합니다.
 * level 파라미터는 들여쓰기를 위한 깊이를 나타냅니다.
 */
void printSuffixTree(SuffixTreeNode *node, const char *text, int level) {
    if (node == NULL)
        return;
    if (node->start != -1) { // 루트는 에지 레이블이 없음
        printf("%*s", level * 2, "");  // 들여쓰기
        printf("Edge [%d, %d]: ", node->start, node->end);
        for (int i = node->start; i <= node->end; i++) {
            putchar(text[i]);
        }
        if (node->suffixIndex != -1) {
            printf(" (Leaf, suffixIndex=%d)", node->suffixIndex);
        }
        printf("\n");
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            printSuffixTree(node->children[i], text, level + 1);
        }
    }
}

/*
 * freeSuffixTree 함수:
 * 접미사 트리의 모든 노드를 재귀적으로 해제합니다.
 */
void freeSuffixTree(SuffixTreeNode *node) {
    if (node == NULL)
        return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            freeSuffixTree(node->children[i]);
        }
    }
    free(node);
}

/*
 * main 함수:
 * 예제 문자열에 대해 접미사 트리를 구축, 출력 및 메모리 해제를 시연합니다.
 */
int main(void) {
    // 예제 문자열: 고유 종결 문자 '$'를 추가하여 모든 접미사의 유일성을 보장합니다.
    const char *text = "banana$";
    printf("원본 문자열: %s\n\n", text);
    
    // 접미사 트리 구축
    SuffixTreeNode *root = buildSuffixTree(text);
    
    // 접미사 트리 출력
    printf("구축된 접미사 트리:\n");
    printSuffixTree(root, text, 0);
    
    // 메모리 해제
    freeSuffixTree(root);
    printf("\n접미사 트리 메모리 해제 완료.\n");
    
    return 0;
}
