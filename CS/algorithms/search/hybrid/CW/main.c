/**
 * main.c
 *
 * 고도화된 Commentz-Walter 알고리즘 구현 예제
 * - 이 알고리즘은 Aho–Corasick 트라이와 Boyer–Moore의 불일치 문자 휴리스틱을 결합하여,
 *   다중 패턴 검색에서 텍스트를 한 번만 스캔하면서 효율적으로 매칭을 수행합니다.
 * - 여러 패턴을 트라이에 삽입하고 실패 링크를 구축한 후, 
 *   전체 패턴 집합에 대한 글로벌 불일치 문자 이동 테이블(global shift table)을 계산합니다.
 * - 검색 단계에서는 텍스트의 최소 패턴 길이(minLen)를 기준으로 후방 문자를 확인하고,
 *   불일치 시 global shift 값을 사용하여 건너뛰며, 
 *   잠재적 매칭 위치에서는 트라이를 통한 정확한 매칭을 수행합니다.
 *
 * 사용 예:
 *   const char *patterns[] = {"he", "she", "his", "hers"};
 *   int patternCount = 4;
 *   // 트라이(automaton) 구축
 *   TrieNode *root = createTrieNode();
 *   for (int i = 0; i < patternCount; i++) {
 *       insertPattern(root, patterns[i], i);
 *   }
 *   buildFailureLinks(root);
 *
 *   // Commentz-Walter 검색 수행
 *   int occCount = 0;
 *   Occurrence *occurrences = cw_search(root, patterns, patternCount, "ahishers", &occCount);
 *   if (occurrences) {
 *       for (int i = 0; i < occCount; i++) {
 *           printf("패턴 ID %d 발견, 시작 인덱스 %d\n", occurrences[i].patternId, occurrences[i].start);
 *       }
 *       free(occurrences);
 *   }
 *   freeTrie(root);
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define ALPHABET_SIZE 256

/*---------------- Data Structures ----------------*/

// 각 패턴의 정보를 저장
typedef struct {
    int patternId;
    int patternLength;
} PatternInfo;

// Trie 노드 (Aho–Corasick 기반)
typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    struct TrieNode *failure;
    PatternInfo *output;    // 이 노드에서 끝나는 패턴들
    int outputCount;
    int outputCapacity;
} TrieNode;

// 검색 결과를 저장하는 구조체
typedef struct {
    int patternId; // 매칭된 패턴의 ID
    int start;     // 텍스트에서 패턴이 시작하는 인덱스 (0 기반)
} Occurrence;

/*---------------- Trie 및 Aho-Corasick 관련 함수 ----------------*/

// 새로운 Trie 노드를 생성
TrieNode* createTrieNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
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

// 출력 배열에 패턴 정보를 추가
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

// 트라이에 패턴 삽입
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

// BFS를 이용해 실패 링크를 구축
void buildFailureLinks(TrieNode *root) {
    root->failure = root;
    // 간단한 큐 구현
    TrieNode **queue = (TrieNode **)malloc(100 * sizeof(TrieNode *));
    if (!queue) {
        fprintf(stderr, "메모리 할당 실패: Queue\n");
        exit(EXIT_FAILURE);
    }
    int head = 0, tail = 0, queueCapacity = 100;
    
    // 루트의 자식들은 실패 링크를 루트로 설정
    for (int c = 0; c < ALPHABET_SIZE; c++) {
        if (root->children[c]) {
            root->children[c]->failure = root;
            queue[tail++] = root->children[c];
        }
    }
    
    while (head < tail) {
        TrieNode *current = queue[head++];
        for (int c = 0; c < ALPHABET_SIZE; c++) {
            TrieNode *child = current->children[c];
            if (child) {
                TrieNode *fail = current->failure;
                while (fail != root && fail->children[c] == NULL)
                    fail = fail->failure;
                if (fail->children[c])
                    child->failure = fail->children[c];
                else
                    child->failure = root;
                // 병합: 실패 링크의 출력 목록을 자식에 추가
                for (int i = 0; i < child->failure->outputCount; i++) {
                    PatternInfo info = child->failure->output[i];
                    addOutput(child, info.patternId, info.patternLength);
                }
                // 큐에 자식 추가
                if (tail >= queueCapacity) {
                    queueCapacity *= 2;
                    TrieNode **newQueue = (TrieNode **)realloc(queue, queueCapacity * sizeof(TrieNode *));
                    if (!newQueue) {
                        fprintf(stderr, "메모리 재할당 실패: Queue\n");
                        free(queue);
                        exit(EXIT_FAILURE);
                    }
                    queue = newQueue;
                }
                queue[tail++] = child;
            }
        }
    }
    free(queue);
}

// 트라이 메모리 해제 (재귀적으로)
void freeTrie(TrieNode *node) {
    if (!node)
        return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i])
            freeTrie(node->children[i]);
    }
    if (node->output)
        free(node->output);
    free(node);
}

/*---------------- Global Shift 테이블 계산 (Boyer-Moore 스타일) ----------------*/

/*
 * computeGlobalShift
 *
 * 다중 패턴 집합에 대해, 각 문자에 대한 글로벌 불일치 문자 이동 값을 계산합니다.
 * 각 문자 c에 대해, globalShift[c]는 패턴 중 c가 등장한 위치에 기반하여
 * (pattern_length - last_occurrence_index(c) - 1)의 최솟값을 저장합니다.
 * 만약 c가 어떤 패턴에도 등장하지 않으면, globalShift[c]는 (minPatternLength + 1)로 설정합니다.
 *
 * 또한, *minLen에는 패턴 집합에서 가장 짧은 패턴의 길이가 저장됩니다.
 */
void computeGlobalShift(const char **patterns, int patternCount, int globalShift[ALPHABET_SIZE], int *minLen) {
    *minLen = INT_MAX;
    for (int c = 0; c < ALPHABET_SIZE; c++) {
        globalShift[c] = INT_MAX;
    }
    for (int i = 0; i < patternCount; i++) {
        int len = (int)strlen(patterns[i]);
        if (len < *minLen) *minLen = len;
        // for each character in the pattern, compute candidate shift
        for (int j = 0; j < len; j++) {
            unsigned char c = (unsigned char)patterns[i][j];
            int candidate = len - j - 1;
            if (candidate < globalShift[c])
                globalShift[c] = candidate;
        }
    }
    // For characters not present in any pattern, set shift to minLen + 1
    for (int c = 0; c < ALPHABET_SIZE; c++) {
        if (globalShift[c] == INT_MAX)
            globalShift[c] = *minLen + 1;
    }
}

/*---------------- Commentz-Walter 검색 ----------------*/

/*
 * checkMatchAt
 *
 * 주어진 텍스트의 s 위치에서 Trie(automaton)를 사용하여
 * 패턴들이 시작하는지 확인합니다.
 * 발견된 매칭은 동적 배열 occurrences에 추가됩니다.
 */
void checkMatchAt(TrieNode *root, const char *text, int s, Occurrence **occurrences, int *occCount, int *occCapacity) {
    int n = (int)strlen(text);
    TrieNode *node = root;
    for (int i = s; i < n; i++) {
        unsigned char c = (unsigned char)text[i];
        while (node != root && node->children[c] == NULL)
            node = node->failure;
        if (node->children[c])
            node = node->children[c];
        // Check output: 매칭된 패턴들 중 시작 위치가 s 인 경우 기록
        if (node->outputCount > 0) {
            for (int j = 0; j < node->outputCount; j++) {
                int patLen = node->output[j].patternLength;
                int startIndex = i - patLen + 1;
                if (startIndex == s) {
                    // 동적 배열 확장
                    if (*occCount == *occCapacity) {
                        *occCapacity *= 2;
                        Occurrence *temp = (Occurrence *)realloc(*occurrences, (*occCapacity) * sizeof(Occurrence));
                        if (!temp) {
                            fprintf(stderr, "결과 배열 재할당 실패: checkMatchAt\n");
                            free(*occurrences);
                            exit(EXIT_FAILURE);
                        }
                        *occurrences = temp;
                    }
                    (*occurrences)[*occCount].patternId = node->output[j].patternId;
                    (*occurrences)[*occCount].start = s;
                    (*occCount)++;
                }
            }
        }
    }
}

/*
 * cw_search
 *
 * Commentz-Walter 알고리즘을 사용하여 텍스트 내에서 여러 패턴의 매칭 결과를 찾습니다.
 * - root: Aho–Corasick 트라이 (모든 패턴이 삽입되어 있고 실패 링크가 구축됨)
 * - patterns: 패턴 문자열 배열
 * - patternCount: 패턴의 개수
 * - text: 검색할 텍스트
 * - totalMatches: 출력, 매칭 결과의 개수를 저장
 *
 * 반환: 동적 할당된 Occurrence 배열 (호출자가 free()로 메모리 해제)
 */
Occurrence* cw_search(TrieNode *root, const char **patterns, int patternCount, const char *text, int *totalMatches) {
    int n = (int)strlen(text);
    int globalShift[ALPHABET_SIZE];
    int minLen;
    computeGlobalShift(patterns, patternCount, globalShift, &minLen);
    
    // 동적 배열로 매칭 결과 저장
    int occCapacity = 10;
    int occCount = 0;
    Occurrence *occurrences = (Occurrence *)malloc(occCapacity * sizeof(Occurrence));
    if (!occurrences) {
        fprintf(stderr, "메모리 할당 실패: occurrences (cw_search)\n");
        *totalMatches = -1;
        return NULL;
    }
    
    int s = 0;
    // 텍스트의 최소 패턴 길이만큼만 검사
    while (s <= n - minLen) {
        int j = s + minLen - 1;
        unsigned char c = (unsigned char)text[j];
        int shift = globalShift[c];
        if (shift > 0) {
            s += shift;
        } else {
            // shift == 0인 경우, 잠재적으로 매칭 가능하므로 자세히 확인
            checkMatchAt(root, text, s, &occurrences, &occCount, &occCapacity);
            s++;
        }
    }
    *totalMatches = occCount;
    return occurrences;
}

/*---------------- main 함수 (데모) ----------------*/

int main(void) {
    // 패턴 목록 예제
    const char *patterns[] = {"he", "she", "his", "hers"};
    int patternCount = sizeof(patterns) / sizeof(patterns[0]);
    
    // 트라이(automaton) 구축
    TrieNode *root = createTrieNode();
    for (int i = 0; i < patternCount; i++) {
        insertPattern(root, patterns[i], i);
    }
    buildFailureLinks(root);
    
    // 검색할 텍스트 예제
    const char *text = "ahishers";
    int totalMatches = 0;
    
    Occurrence *matches = cw_search(root, patterns, patternCount, text, &totalMatches);
    if (matches == NULL || totalMatches <= 0) {
        printf("매칭된 패턴이 없습니다.\n");
    } else {
        printf("텍스트 \"%s\"에서 매칭 결과:\n", text);
        for (int i = 0; i < totalMatches; i++) {
            printf("패턴 ID %d 발견, 시작 인덱스 %d\n", matches[i].patternId, matches[i].start);
        }
        free(matches);
    }
    
    freeTrie(root);
    return 0;
}