/**
 * main.c
 *
 * 고도화된 Aho-Corasick 알고리즘 구현 예제
 * - 여러 패턴을 동시에 검색할 수 있는 트라이 기반 자동자(automaton)를 구축합니다.
 * - 각 패턴을 트라이에 삽입하고, 실패 링크(failure link)와 출력 리스트(output list)를 구축하여,
 *   텍스트를 한 번만 스캔하면서 모든 패턴의 매칭 결과를 찾습니다.
 * - 검색 결과는 Occurrence 구조체 배열로 반환되며, 각 Occurrence는 패턴 ID와 텍스트 내 시작 인덱스를 포함합니다.
 * - 이 구현체는 실무에서도 사용할 수 있도록 메모리 관리 및 동적 배열 확장을 포함하여 견고하게 작성되었습니다.
 *
 * 사용 예:
 *   // 패턴 목록
 *   const char *patterns[] = {"he", "she", "his", "hers"};
 *   int patternCount = 4;
 *
 *   // 트라이(automaton) 구축
 *   TrieNode *root = createTrieNode();
 *   for (int i = 0; i < patternCount; i++) {
 *       insertPattern(root, patterns[i], i);
 *   }
 *   buildFailureLinks(root);
 *
 *   // 텍스트 검색
 *   const char *text = "ahishers";
 *   int occCount = 0;
 *   Occurrence *occurrences = ac_search(root, text, &occCount);
 *   if (occurrences) {
 *       for (int i = 0; i < occCount; i++) {
 *           printf("패턴 ID %d 발견, 시작 인덱스 %d\n", occurrences[i].patternId, occurrences[i].start);
 *       }
 *       free(occurrences);
 *   }
 *
 *   // 트라이 메모리 해제
 *   freeTrie(root);
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 256

/* 구조체 정의 */

// 각 패턴의 정보를 저장 (패턴 ID와 패턴 길이)
typedef struct {
    int patternId;
    int patternLength;
} PatternInfo;

// Trie 노드 구조체
typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE]; // 각 문자에 대한 자식 노드
    struct TrieNode *failure;                 // 실패 링크
    PatternInfo *output;                      // 이 노드에서 끝나는 패턴들의 정보 (동적 배열)
    int outputCount;                          // 출력 배열에 저장된 패턴 개수
    int outputCapacity;                       // 출력 배열의 현재 용량
} TrieNode;

// 검색 결과를 저장하는 구조체
typedef struct {
    int patternId; // 매칭된 패턴의 ID
    int start;     // 텍스트에서 패턴이 시작하는 인덱스 (0 기반)
} Occurrence;

/* Trie 노드 관련 함수 */

// 새로운 Trie 노드를 생성하고 초기화합니다.
TrieNode* createTrieNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    if (!node) {
        fprintf(stderr, "메모리 할당 실패: TrieNode\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    node->failure = NULL;
    node->output = NULL;
    node->outputCount = 0;
    node->outputCapacity = 0;
    return node;
}

// 출력 배열에 새로운 패턴 정보를 추가합니다.
void addOutput(TrieNode *node, int patternId, int patternLength) {
    if (node->outputCount == node->outputCapacity) {
        int newCapacity = (node->outputCapacity == 0) ? 2 : node->outputCapacity * 2;
        PatternInfo *newOutput = (PatternInfo *)realloc(node->output, newCapacity * sizeof(PatternInfo));
        if (!newOutput) {
            fprintf(stderr, "메모리 재할당 실패: addOutput\n");
            exit(EXIT_FAILURE);
        }
        node->output = newOutput;
        node->outputCapacity = newCapacity;
    }
    node->output[node->outputCount].patternId = patternId;
    node->output[node->outputCount].patternLength = patternLength;
    node->outputCount++;
}

// 패턴을 트라이에 삽입합니다.
void insertPattern(TrieNode *root, const char *pattern, int patternId) {
    TrieNode *node = root;
    for (int i = 0; pattern[i] != '\0'; i++) {
        unsigned char c = (unsigned char)pattern[i];
        if (node->children[c] == NULL) {
            node->children[c] = createTrieNode();
        }
        node = node->children[c];
    }
    int len = (int)strlen(pattern);
    addOutput(node, patternId, len);
}

/* 실패 링크 구축 함수 */

// A simple queue implementation for BFS.
typedef struct {
    TrieNode **data;
    int head;
    int tail;
    int capacity;
} Queue;

// Initialize a new queue.
Queue* createQueue(int capacity) {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    if (!queue) {
        fprintf(stderr, "메모리 할당 실패: Queue\n");
        exit(EXIT_FAILURE);
    }
    queue->data = (TrieNode**)malloc(capacity * sizeof(TrieNode*));
    if (!queue->data) {
        fprintf(stderr, "메모리 할당 실패: Queue data\n");
        exit(EXIT_FAILURE);
    }
    queue->head = 0;
    queue->tail = 0;
    queue->capacity = capacity;
    return queue;
}

// Enqueue an element.
void enqueue(Queue *queue, TrieNode *node) {
    if (queue->tail >= queue->capacity) {
        queue->capacity *= 2;
        TrieNode **newData = (TrieNode**)realloc(queue->data, queue->capacity * sizeof(TrieNode*));
        if (!newData) {
            fprintf(stderr, "메모리 재할당 실패: enqueue\n");
            exit(EXIT_FAILURE);
        }
        queue->data = newData;
    }
    queue->data[queue->tail++] = node;
}

// Dequeue an element.
TrieNode* dequeue(Queue *queue) {
    if (queue->head < queue->tail) {
        return queue->data[queue->head++];
    }
    return NULL;
}

// Check if the queue is empty.
int isQueueEmpty(Queue *queue) {
    return queue->head >= queue->tail;
}

// Free the queue.
void freeQueue(Queue *queue) {
    free(queue->data);
    free(queue);
}

// Build failure links for the Aho-Corasick automaton.
void buildFailureLinks(TrieNode *root) {
    root->failure = root;
    Queue *queue = createQueue(100);
    
    // 초기: 루트의 자식들의 실패 링크는 루트로 설정
    for (int c = 0; c < ALPHABET_SIZE; c++) {
        if (root->children[c]) {
            root->children[c]->failure = root;
            enqueue(queue, root->children[c]);
        }
    }
    
    // BFS로 트라이 순회
    while (!isQueueEmpty(queue)) {
        TrieNode *current = dequeue(queue);
        for (int c = 0; c < ALPHABET_SIZE; c++) {
            TrieNode *child = current->children[c];
            if (child) {
                TrieNode *fail = current->failure;
                // 실패 링크를 따라 이동하며, 해당 문자를 가진 노드를 찾음
                while (fail != root && fail->children[c] == NULL) {
                    fail = fail->failure;
                }
                if (fail->children[c]) {
                    child->failure = fail->children[c];
                } else {
                    child->failure = root;
                }
                // 실패 링크를 통해 출력 목록 병합
                for (int i = 0; i < child->failure->outputCount; i++) {
                    PatternInfo info = child->failure->output[i];
                    addOutput(child, info.patternId, info.patternLength);
                }
                enqueue(queue, child);
            }
        }
    }
    freeQueue(queue);
}

/* Aho-Corasick 검색 함수 */

// 검색 결과를 저장하는 Occurrence 구조체는 위에 정의됨:
// typedef struct {
//     int patternId;
//     int start;
// } Occurrence;

// Aho-Corasick 알고리즘을 사용하여 텍스트에서 패턴 매칭 결과를 찾습니다.
// patternId와 패턴 길이는 트라이 생성 시 삽입한 값에 기반합니다.
Occurrence* ac_search(TrieNode *root, const char *text, int *occurrenceCount) {
    int textLen = (int)strlen(text);
    int capacity = 10;
    int count = 0;
    Occurrence *occurrences = (Occurrence*)malloc(capacity * sizeof(Occurrence));
    if (!occurrences) {
        fprintf(stderr, "메모리 할당 실패: occurrences\n");
        exit(EXIT_FAILURE);
    }
    
    TrieNode *node = root;
    for (int i = 0; i < textLen; i++) {
        unsigned char c = (unsigned char)text[i];
        // 상태 전이: 해당 문자가 없는 경우 실패 링크를 따라 이동
        while (node != root && node->children[c] == NULL) {
            node = node->failure;
        }
        if (node->children[c])
            node = node->children[c];
        // 출력 목록이 있다면, 매칭된 모든 패턴에 대해 결과 기록
        if (node->outputCount > 0) {
            for (int j = 0; j < node->outputCount; j++) {
                int patLen = node->output[j].patternLength;
                int startIndex = i - patLen + 1;
                if (startIndex >= 0) {
                    if (count == capacity) {
                        capacity *= 2;
                        Occurrence *temp = (Occurrence*)realloc(occurrences, capacity * sizeof(Occurrence));
                        if (!temp) {
                            fprintf(stderr, "메모리 재할당 실패: occurrences\n");
                            free(occurrences);
                            exit(EXIT_FAILURE);
                        }
                        occurrences = temp;
                    }
                    occurrences[count].patternId = node->output[j].patternId;
                    occurrences[count].start = startIndex;
                    count++;
                }
            }
        }
    }
    *occurrenceCount = count;
    return occurrences;
}

/* 메모리 해제 함수 */

// 트라이의 메모리를 재귀적으로 해제합니다.
void freeTrie(TrieNode *node) {
    if (node == NULL)
        return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        // 자식 노드가 존재하면 재귀적으로 해제
        if (node->children[i]) {
            freeTrie(node->children[i]);
        }
    }
    if (node->output)
        free(node->output);
    free(node);
}

/* main 함수: Aho-Corasick 알고리즘 데모 */
int main(void) {
    // 패턴 목록 (실제 응용에서는 동적 입력을 사용할 수 있음)
    const char *patterns[] = {"he", "she", "his", "hers"};
    int patternCount = sizeof(patterns) / sizeof(patterns[0]);
    
    // 트라이(automaton) 구축
    TrieNode *root = createTrieNode();
    for (int i = 0; i < patternCount; i++) {
        insertPattern(root, patterns[i], i);
    }
    buildFailureLinks(root);
    
    // 검색할 텍스트
    const char *text = "ahishers";
    int occCount = 0;
    Occurrence *occurrences = ac_search(root, text, &occCount);
    
    if (occurrences) {
        printf("텍스트 \"%s\"에서 패턴 매칭 결과:\n", text);
        for (int i = 0; i < occCount; i++) {
            printf("패턴 ID %d 발견, 시작 인덱스 %d\n", occurrences[i].patternId, occurrences[i].start);
        }
        free(occurrences);
    } else {
        printf("매칭된 패턴이 없습니다.\n");
    }
    
    freeTrie(root);
    return 0;
}