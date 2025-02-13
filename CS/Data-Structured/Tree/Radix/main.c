/*
 * main.c
 *
 * 이 파일은 Radix Tree (Compressed Trie, Patricia Trie)의 고도화된 구현 예제입니다.
 * Radix Tree는 일반 트라이의 중복된 단일 문자 노드를 압축하여, 
 * 공통 접두사를 공유하는 문자열들을 효율적으로 저장하고 검색할 수 있도록 최적화된 자료구조입니다.
 *
 * 주요 기능:
 * - createTrieNode: 새 Radix 노드를 생성합니다.
 * - insertWord: 문자열을 트라이에 삽입합니다.
 *   → 삽입 시 공통 접두사를 찾아 노드를 분할하고, 필요한 경우 새 노드를 생성합니다.
 * - searchRadix: 트라이에서 문자열의 존재 여부를 검색합니다.
 * - deleteWord: 문자열을 삭제하고, 불필요해진 노드를 회수(merge)합니다.
 * - printRadixWords: 트라이에 저장된 모든 단어들을 재귀적으로 출력합니다.
 * - freeRadixTree: 트라이의 모든 노드를 재귀적으로 해제합니다.
 *
 * 이 구현은 B+ Tree의 고도화된 구현 방식과 유사하게, 복잡한 케이스(노드 분할, 병합, 접두사 압축 등)를 모두 처리하도록 작성되었습니다.
 *
 * 참고: 실무에서는 추가적인 에러 처리, 동적 알파벳 크기 지원, 최적화 등을 고려해야 합니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26  // 영어 소문자 a~z

// Radix Tree (Compressed Trie) 노드 구조체 정의
typedef struct RadixNode {
    char *label;                    // 부모와 연결되는 경로 레이블 (압축된 문자열)
    bool isWord;                    // 이 노드까지의 경로가 유효한 단어인지 여부
    struct RadixNode **children;    // 동적 배열: 자식 노드 포인터들
    int numChildren;                // 현재 자식 노드 수
    int capacity;                   // 자식 배열의 할당 용량
} RadixNode;

// 초기 자식 배열 용량
#define INITIAL_CHILDREN_CAPACITY 4

// 새 Radix 노드를 생성합니다. label이 NULL이면 빈 문자열로 초기화합니다.
RadixNode* createTrieNode(const char *label, bool isWord) {
    RadixNode *node = (RadixNode*) malloc(sizeof(RadixNode));
    if (!node) {
        fprintf(stderr, "메모리 할당 실패 in createTrieNode.\n");
        exit(EXIT_FAILURE);
    }
    if (label)
        node->label = strdup(label);
    else
        node->label = strdup("");
    node->isWord = isWord;
    node->numChildren = 0;
    node->capacity = INITIAL_CHILDREN_CAPACITY;
    node->children = (RadixNode**) malloc(sizeof(RadixNode*) * node->capacity);
    if (!node->children) {
        fprintf(stderr, "메모리 할당 실패 for children in createTrieNode.\n");
        exit(EXIT_FAILURE);
    }
    return node;
}

// Free Radix Tree recursively.
void freeRadixTree(RadixNode *node) {
    if (!node) return;
    for (int i = 0; i < node->numChildren; i++) {
        freeRadixTree(node->children[i]);
    }
    free(node->label);
    free(node->children);
    free(node);
}

// Utility: Find common prefix length between s1 and s2.
int commonPrefixLength(const char *s1, const char *s2) {
    int i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return i;
}

// Utility: Add a child to a Radix node (expand children array if needed).
void addChild(RadixNode *parent, RadixNode *child) {
    if (parent->numChildren >= parent->capacity) {
        parent->capacity *= 2;
        parent->children = (RadixNode**) realloc(parent->children, sizeof(RadixNode*) * parent->capacity);
        if (!parent->children) {
            fprintf(stderr, "Realloc 실패 in addChild.\n");
            exit(EXIT_FAILURE);
        }
    }
    parent->children[parent->numChildren++] = child;
}

// Utility: Remove child at index from parent's children array.
void removeChild(RadixNode *parent, int index) {
    if (index < 0 || index >= parent->numChildren)
        return;
    for (int i = index; i < parent->numChildren - 1; i++) {
        parent->children[i] = parent->children[i+1];
    }
    parent->numChildren--;
}

// Insertion: recursively insert word into the Radix Tree starting from node.
void insertRadix(RadixNode *node, const char *word) {
    int len = strlen(word);
    if (len == 0) {
        node->isWord = true;
        return;
    }
    // Try to find a child with common prefix.
    for (int i = 0; i < node->numChildren; i++) {
        RadixNode *child = node->children[i];
        int commonLen = commonPrefixLength(word, child->label);
        if (commonLen > 0) {
            // Case 1: Partial match where child's label is longer than common prefix.
            if (commonLen < strlen(child->label)) {
                // Split the child node.
                char *childSuffix = strdup(child->label + commonLen);
                RadixNode *splitNode = createTrieNode(childSuffix, child->isWord);
                free(childSuffix);
                // Transfer child's children to splitNode.
                splitNode->children = child->children;
                splitNode->numChildren = child->numChildren;
                splitNode->capacity = child->capacity;
                
                // Update child: its label becomes the common prefix.
                free(child->label);
                child->label = strndup(word, commonLen);
                child->isWord = false;
                // Create new children array for child.
                child->children = (RadixNode**) malloc(sizeof(RadixNode*) * INITIAL_CHILDREN_CAPACITY);
                child->numChildren = 0;
                child->capacity = INITIAL_CHILDREN_CAPACITY;
                addChild(child, splitNode);
                
                // Insert remainder of word as new node.
                const char *wordSuffix = word + commonLen;
                if (strlen(wordSuffix) > 0) {
                    RadixNode *newLeaf = createTrieNode(wordSuffix, true);
                    addChild(child, newLeaf);
                } else {
                    child->isWord = true;
                }
                return;
            }
            // Case 2: Child's label is fully matched.
            else if (commonLen == strlen(child->label)) {
                const char *wordSuffix = word + commonLen;
                insertRadix(child, wordSuffix);
                return;
            }
        }
    }
    // Case 3: No common prefix with any child: create new leaf node.
    RadixNode *newNode = createTrieNode(word, true);
    addChild(node, newNode);
}

// Public API: Insert word into Radix Tree.
void insertWord(RadixNode *root, const char *word) {
    insertRadix(root, word);
}

// Search: returns true if word exists in the Radix Tree.
bool searchRadix(RadixNode *node, const char *word) {
    int len = strlen(word);
    if (len == 0)
        return node->isWord;
    for (int i = 0; i < node->numChildren; i++) {
        RadixNode *child = node->children[i];
        int commonLen = commonPrefixLength(word, child->label);
        if (commonLen > 0) {
            if (commonLen == strlen(child->label))
                return searchRadix(child, word + commonLen);
            else
                return false;
        }
    }
    return false;
}

// Deletion: recursively delete word from Radix Tree.
// Returns true if the current node should be deleted (i.e., no children and not a word).
bool deleteRadixHelper(RadixNode *node, const char *word) {
    int len = strlen(word);
    if (len == 0) {
        // End of word reached: unmark the word flag.
        node->isWord = false;
        // If node has no children, signal that it can be removed.
        return (node->numChildren == 0);
    }
    for (int i = 0; i < node->numChildren; i++) {
        RadixNode *child = node->children[i];
        int commonLen = commonPrefixLength(word, child->label);
        if (commonLen > 0) {
            if (commonLen == strlen(child->label)) {
                bool shouldDeleteChild = deleteRadixHelper(child, word + commonLen);
                if (shouldDeleteChild) {
                    freeRadixTree(child);
                    removeChild(node, i);
                    // After removal, if node is not a word and has exactly one child, merge.
                    if (!node->isWord && node->numChildren == 1) {
                        RadixNode *onlyChild = node->children[0];
                        int newLabelLen = strlen(node->label) + strlen(onlyChild->label) + 1;
                        char *mergedLabel = (char*) malloc(newLabelLen);
                        strcpy(mergedLabel, node->label);
                        strcat(mergedLabel, onlyChild->label);
                        free(node->label);
                        node->label = mergedLabel;
                        
                        // Absorb onlyChild's children.
                        free(node->children);
                        node->children = onlyChild->children;
                        node->numChildren = onlyChild->numChildren;
                        node->capacity = onlyChild->capacity;
                        node->isWord = onlyChild->isWord;
                        free(onlyChild->label);
                        free(onlyChild);
                    }
                    return (node->numChildren == 0 && !node->isWord);
                }
                return false;
            } else {
                return false;
            }
        }
    }
    return false;
}

// Public API: Delete word from Radix Tree. Returns true if deletion successful.
bool deleteWord(RadixNode *root, const char *word) {
    if (!searchRadix(root, word)) {
        printf("단어 \"%s\"가 트라이에 존재하지 않습니다.\n", word);
        return false;
    }
    deleteRadixHelper(root, word);
    return true;
}

// Print all words in the Radix Tree. 
// 'buffer' accumulates the current prefix, and 'depth' is the current length.
void printRadixWords(RadixNode *node, char *buffer, int depth) {
    if (!node) return;
    // Append current node's label to buffer.
    int labelLen = strlen(node->label);
    strncpy(buffer + depth, node->label, labelLen);
    depth += labelLen;
    buffer[depth] = '\0';
    
    if (node->isWord)
        printf("%s\n", buffer);
    
    for (int i = 0; i < node->numChildren; i++) {
        printRadixWords(node->children[i], buffer, depth);
    }
}

// Main function demonstrating Radix Tree operations.
int main(void) {
    // Create the Radix Tree root (with empty label)
    RadixNode *root = createTrieNode("", false);
    
    // Insert words into the Radix Tree.
    insertWord(root, "hello");
    insertWord(root, "hell");
    insertWord(root, "heaven");
    insertWord(root, "goodbye");
    insertWord(root, "helium");
    insertWord(root, "help");
    insertWord(root, "heap");
    
    printf("Radix Tree에 단어를 삽입하였습니다.\n\n");
    
    // Print all words in the Radix Tree.
    char buffer[256] = {0};
    printf("Radix Tree에 저장된 단어들:\n");
    printRadixWords(root, buffer, 0);
    printf("\n");
    
    // Search for words.
    const char *searchWords[] = {"hello", "hell", "heaven", "good", "helium", "help", "heap"};
    int numSearch = sizeof(searchWords) / sizeof(searchWords[0]);
    for (int i = 0; i < numSearch; i++) {
        printf("검색 \"%s\": %s\n", searchWords[i],
               searchRadix(root, searchWords[i]) ? "찾음" : "없음");
    }
    printf("\n");
    
    // Delete a word.
    const char *wordToDelete = "hell";
    printf("단어 \"%s\" 삭제 시도...\n", wordToDelete);
    if (deleteWord(root, wordToDelete))
        printf("단어 \"%s\" 삭제 성공.\n", wordToDelete);
    else
        printf("단어 \"%s\" 삭제 실패.\n", wordToDelete);
    printf("\n");
    
    // Print remaining words.
    printf("삭제 후 남은 단어들:\n");
    printRadixWords(root, buffer, 0);
    printf("\n");
    
    // Free the Radix Tree.
    freeRadixTree(root);
    printf("Radix Tree 메모리 해제 완료.\n");
    
    return 0;
}