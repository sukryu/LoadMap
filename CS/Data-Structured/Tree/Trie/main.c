/*
 * main.c
 *
 * 이 파일은 트라이(Trie) 자료구조의 고도화된 구현 예제입니다.
 * 트라이는 문자열 데이터를 저장하고 검색하는 데 최적화된 트리 기반 자료구조로,
 * 각 노드는 한 문자를 나타내며, 문자열의 접두사를 공유하는 단어들을 효율적으로 저장할 수 있습니다.
 *
 * 주요 기능:
 * - createTrieNode: 새로운 트라이 노드를 생성합니다.
 * - insertTrie: 주어진 문자열을 트라이에 삽입합니다.
 * - searchTrie: 트라이에서 주어진 문자열의 존재 여부를 검색합니다.
 * - deleteTrie: 트라이에서 특정 문자열을 삭제하며, 불필요한 노드들을 회수합니다.
 * - printTrieWords: 트라이에 저장된 모든 단어를 재귀적으로 출력합니다.
 * - freeTrie: 트라이의 모든 노드에 할당된 메모리를 재귀적으로 해제합니다.
 *
 * 이 구현은 B+ Tree의 고도화된 구현과 유사한 스타일로, 다양한 케이스(문자 삽입, 검색, 삭제 후
 * 불필요한 노드 제거 등)를 모두 처리하도록 작성되었습니다.
 *
 * 참고: 실제 실무 환경에서는 에러 처리, 동적 알파벳 크기 지원, 추가 최적화 등이 필요할 수 있습니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26  // 영어 소문자 a~z

// 트라이 노드 구조체 정의
typedef struct TrieNode {
    bool isEnd;                       // 해당 노드가 단어의 끝인지 여부
    struct TrieNode *children[ALPHABET_SIZE]; // 각 알파벳에 대응하는 자식 포인터
} TrieNode;

/*
 * createTrieNode 함수:
 * 새로운 트라이 노드를 생성하고, 모든 자식 포인터를 NULL로 초기화합니다.
 */
TrieNode* createTrieNode() {
    TrieNode *node = (TrieNode*) malloc(sizeof(TrieNode));
    if (node == NULL) {
        fprintf(stderr, "TrieNode 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    node->isEnd = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

/*
 * insertTrie 함수:
 * 주어진 단어를 트라이에 삽입합니다.
 * 각 문자를 순차적으로 따라가며, 노드가 없으면 새로 생성합니다.
 * 단어의 마지막 문자 노드에 isEnd를 true로 설정합니다.
 */
void insertTrie(TrieNode *root, const char *word) {
    TrieNode *current = root;
    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        int index = word[i] - 'a';
        if (index < 0 || index >= ALPHABET_SIZE) {
            fprintf(stderr, "잘못된 문자 '%c' 발견됨. 영어 소문자만 지원합니다.\n", word[i]);
            return;
        }
        if (current->children[index] == NULL) {
            current->children[index] = createTrieNode();
        }
        current = current->children[index];
    }
    current->isEnd = true;
}

/*
 * searchTrie 함수:
 * 트라이에서 주어진 단어의 존재 여부를 검색합니다.
 * 단어의 각 문자를 따라가며, 경로가 모두 존재하고 마지막 노드의 isEnd가 true이면 단어가 존재합니다.
 * 존재하면 true, 아니면 false를 반환합니다.
 */
bool searchTrie(TrieNode *root, const char *word) {
    TrieNode *current = root;
    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL)
            return false;
        current = current->children[index];
    }
    return current->isEnd;
}

/*
 * deleteTrieHelper 함수:
 * 재귀적으로 트라이에서 단어를 삭제합니다.
 * depth가 문자열 길이와 같으면, 단어의 끝 노드를 처리하고,
 * 이후 불필요한 노드를 회수할 수 있으면 true를 반환합니다.
 */
bool deleteTrieHelper(TrieNode *node, const char *word, int depth) {
    if (node == NULL)
        return false;

    // 기저 사례: 단어의 끝에 도달한 경우
    if (depth == strlen(word)) {
        // 단어가 존재하는 경우 isEnd를 false로 변경
        if (node->isEnd)
            node->isEnd = false;
        // 노드가 자식이 없으면 이 노드를 삭제할 수 있음
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i] != NULL)
                return false;
        }
        return true;
    }

    int index = word[depth] - 'a';
    if (deleteTrieHelper(node->children[index], word, depth + 1)) {
        // 자식 노드를 삭제 가능한 경우, free하고 NULL로 설정
        free(node->children[index]);
        node->children[index] = NULL;

        // 현재 노드가 단어의 끝이 아니고 다른 자식도 없으면 삭제 가능
        if (!node->isEnd) {
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (node->children[i] != NULL)
                    return false;
            }
            return true;
        }
    }
    return false;
}

/*
 * deleteTrie 함수:
 * 트라이에서 주어진 단어를 삭제합니다.
 * 반환값: 단어가 성공적으로 삭제되었으면 true, 아니면 false.
 */
bool deleteTrie(TrieNode **root, const char *word) {
    if (searchTrie(*root, word) == false) {
        printf("단어 \"%s\"는 트라이에 존재하지 않습니다.\n", word);
        return false;
    }
    bool shouldDelete = deleteTrieHelper(*root, word, 0);
    // 루트 노드 자체는 삭제하지 않음
    return true;
}

/*
 * printTrieWords 함수:
 * 트라이에 저장된 모든 단어들을 재귀적으로 출력합니다.
 * buffer는 단어를 임시로 저장할 배열이며, depth는 현재 깊이(버퍼 인덱스)입니다.
 */
void printTrieWords(TrieNode *node, char *buffer, int depth) {
    if (node == NULL)
        return;
    if (node->isEnd) {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            buffer[depth] = 'a' + i;
            printTrieWords(node->children[i], buffer, depth + 1);
        }
    }
}

/*
 * freeTrie 함수:
 * 트라이의 모든 노드를 재귀적으로 방문하여 메모리를 해제합니다.
 */
void freeTrie(TrieNode *node) {
    if (node == NULL)
        return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL)
            freeTrie(node->children[i]);
    }
    free(node);
}

/*
 * main 함수:
 * 트라이의 삽입, 검색, 삭제, 모든 단어 출력 등의 연산을 시연합니다.
 */
int main(void) {
    TrieNode *root = createTrieNode();
    char buffer[100];

    // 단어 삽입 테스트
    insertTrie(root, "hello");
    insertTrie(root, "hell");
    insertTrie(root, "heaven");
    insertTrie(root, "goodbye");
    insertTrie(root, "helium");

    printf("트라이에 삽입된 단어들:\n");
    printTrieWords(root, buffer, 0);
    printf("\n");

    // 검색 테스트
    const char *wordsToSearch[] = {"hello", "heaven", "good", "hellish", "helium"};
    int searchCount = sizeof(wordsToSearch) / sizeof(wordsToSearch[0]);
    for (int i = 0; i < searchCount; i++) {
        if (searchTrie(root, wordsToSearch[i]))
            printf("단어 \"%s\"를 찾았습니다.\n", wordsToSearch[i]);
        else
            printf("단어 \"%s\"는 트라이에 존재하지 않습니다.\n", wordsToSearch[i]);
    }
    printf("\n");

    // 삭제 테스트
    const char *wordToDelete = "hell";
    printf("단어 \"%s\"를 삭제합니다.\n", wordToDelete);
    if (deleteTrie(&root, wordToDelete))
        printf("단어 \"%s\"가 성공적으로 삭제되었습니다.\n", wordToDelete);
    else
        printf("단어 \"%s\" 삭제에 실패했습니다.\n", wordToDelete);
    printf("\n트라이에 남은 단어들:\n");
    printTrieWords(root, buffer, 0);
    
    // 추가 삭제 테스트 (존재하지 않는 단어)
    wordToDelete = "good";
    printf("\n단어 \"%s\"를 삭제 시도합니다.\n", wordToDelete);
    if (!deleteTrie(&root, wordToDelete))
        printf("단어 \"%s\" 삭제에 실패했습니다. (존재하지 않음)\n", wordToDelete);
    
    // 메모리 해제
    freeTrie(root);
    printf("\n트라이 메모리 해제 완료.\n");

    return 0;
}