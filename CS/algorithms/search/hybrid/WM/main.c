/**
 * main.c
 *
 * 고도화된 Wu-Manber 알고리즘 구현 예제
 * - 다중 패턴 검색을 위해 Boyer–Moore의 불일치 휴리스틱과 해시 기반 블록 처리 기법을 결합합니다.
 * - 여러 패턴(문자열) 배열과 텍스트를 입력받아, 모든 매칭 위치와 해당 패턴 ID를 동적 배열로 반환합니다.
 * - 이 구현은 실무 환경에서 사용할 수 있도록 전처리, 동적 메모리 관리, 에러 처리 등을 포함하여 견고하게 작성되었습니다.
 *
 * 사용 예:
 *   const char *patterns[] = {"pattern", "search", "example"};
 *   int patternCount = 3;
 *   int matchCount = 0;
 *   Occurrence *matches = wu_manber_search(patterns, patternCount, 
 *                           "this is an example pattern for search. another example is provided.", &matchCount);
 *   if (matches) {
 *       for (int i = 0; i < matchCount; i++) {
 *           printf("패턴 ID %d 발견, 시작 인덱스 %d\n", matches[i].patternId, matches[i].start);
 *       }
 *       free(matches);
 *   }
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define BLOCK_SIZE 2
#define SHIFT_SIZE 65536  // 256^2

/* Occurrence 구조체: 매칭 결과 저장 */
typedef struct {
    int patternId; // 매칭된 패턴의 인덱스
    int start;     // 텍스트 내 매칭 시작 인덱스 (0 기반)
} Occurrence;

/* CandidateList 구조체: 특정 블록 해시 값에 대응하는 패턴 인덱스 목록 */
typedef struct {
    int *indices;  // 동적 배열 (패턴 인덱스)
    int count;     // 현재 저장된 개수
    int capacity;  // 배열의 현재 용량
} CandidateList;

/* Utility: BLOCK_SIZE 길이의 블록에 대한 해시 계산 */
static int block_hash(const char *s) {
    // s는 최소 BLOCK_SIZE 문자 이상이어야 함
    return (((unsigned char)s[0]) << 8) | ((unsigned char)s[1]);
}

/* Preprocessing 함수
   - patterns: 패턴 문자열 배열
   - patternCount: 패턴 개수
   - minLen: 출력, 패턴 집합 중 최소 길이
   - shiftTable: SHIFT_SIZE 크기의 배열에 불일치 이동 값 저장
   - hashTable: SHIFT_SIZE 크기의 CandidateList 배열에 패턴 인덱스 저장 (마지막 BLOCK_SIZE 문자 기준)
   - prefixes: patternCount 크기의 배열, 각 패턴의 첫 BLOCK_SIZE 문자에 대한 해시 값
*/
static void preprocess_patterns(const char **patterns, int patternCount,
                                int *minLen, int *shiftTable,
                                CandidateList *hashTable, int *prefixes) {
    int i, j;
    *minLen = INT_MAX;
    // 초기화: 최소 길이 계산
    for (i = 0; i < patternCount; i++) {
        int len = (int)strlen(patterns[i]);
        if (len < *minLen) {
            *minLen = len;
        }
    }
    if (*minLen < BLOCK_SIZE) {
        fprintf(stderr, "모든 패턴은 최소 %d 길이 이상이어야 합니다.\n", BLOCK_SIZE);
        exit(EXIT_FAILURE);
    }
    int defaultShift = *minLen - BLOCK_SIZE + 1;
    for (i = 0; i < SHIFT_SIZE; i++) {
        shiftTable[i] = defaultShift;
    }
    // 초기화: hashTable의 각 후보 리스트
    for (i = 0; i < SHIFT_SIZE; i++) {
        hashTable[i].indices = NULL;
        hashTable[i].count = 0;
        hashTable[i].capacity = 0;
    }
    // 각 패턴에 대해 SHIFT 테이블 업데이트, HASH 테이블 및 prefixes 계산
    for (i = 0; i < patternCount; i++) {
        int len = (int)strlen(patterns[i]);
        // prefixes: 패턴의 첫 BLOCK_SIZE 문자 해시 계산
        prefixes[i] = block_hash(patterns[i]);
        // SHIFT 테이블: 패턴의 각 가능한 블록(길이 BLOCK_SIZE)에 대해 이동 값 업데이트
        for (j = 0; j <= len - BLOCK_SIZE; j++) {
            int hashVal = block_hash(patterns[i] + j);
            int shiftCandidate = len - j - BLOCK_SIZE;
            if (shiftCandidate < shiftTable[hashVal]) {
                shiftTable[hashVal] = shiftCandidate;
            }
        }
        // HASH 테이블: 패턴의 마지막 BLOCK_SIZE 문자 블록을 기준으로 후보 추가
        int endBlockHash = block_hash(patterns[i] + (len - BLOCK_SIZE));
        CandidateList *clist = &hashTable[endBlockHash];
        if (clist->count == clist->capacity) {
            int newCapacity = (clist->capacity == 0) ? 2 : clist->capacity * 2;
            int *newIndices = (int *)realloc(clist->indices, newCapacity * sizeof(int));
            if (!newIndices) {
                fprintf(stderr, "메모리 재할당 실패 (hashTable candidate list)\n");
                exit(EXIT_FAILURE);
            }
            clist->indices = newIndices;
            clist->capacity = newCapacity;
        }
        clist->indices[clist->count++] = i;
    }
}

/* Free hashTable의 CandidateList */
static void free_hash_table(CandidateList *hashTable) {
    for (int i = 0; i < SHIFT_SIZE; i++) {
        if (hashTable[i].indices) {
            free(hashTable[i].indices);
        }
    }
}

/*
 * wu_manber_search
 *
 * 다중 패턴 검색을 위한 Wu-Manber 알고리즘 구현
 * - patterns: 패턴 문자열 배열
 * - patternCount: 패턴 개수
 * - text: 검색할 텍스트 문자열
 * - matchCount: 출력, 매칭 결과 개수 (0 이상)
 *
 * 반환: Occurrence 배열 (동적 할당), 각 요소에 매칭된 패턴 ID와 텍스트 내 시작 인덱스 저장
 *       호출자가 free()로 메모리 해제해야 함.
 */
Occurrence* wu_manber_search(const char **patterns, int patternCount,
                             const char *text, int *matchCount) {
    if (!patterns || !text || !matchCount) {
        fprintf(stderr, "입력 인자에 NULL이 전달되었습니다.\n");
        return NULL;
    }
    int n = (int)strlen(text);
    int minLen, i;
    int *shiftTable = (int *)malloc(SHIFT_SIZE * sizeof(int));
    if (!shiftTable) {
        fprintf(stderr, "메모리 할당 실패 (shiftTable)\n");
        exit(EXIT_FAILURE);
    }
    CandidateList *hashTable = (CandidateList *)calloc(SHIFT_SIZE, sizeof(CandidateList));
    if (!hashTable) {
        fprintf(stderr, "메모리 할당 실패 (hashTable)\n");
        free(shiftTable);
        exit(EXIT_FAILURE);
    }
    int *prefixes = (int *)malloc(patternCount * sizeof(int));
    if (!prefixes) {
        fprintf(stderr, "메모리 할당 실패 (prefixes)\n");
        free(shiftTable);
        free(hashTable);
        exit(EXIT_FAILURE);
    }
    
    // 전처리: 최소 패턴 길이, SHIFT 테이블, HASH 테이블, PREFIX 계산
    preprocess_patterns(patterns, patternCount, &minLen, shiftTable, hashTable, prefixes);
    
    // 결과 배열 초기화
    int occCapacity = 10;
    int occCount = 0;
    Occurrence *occurrences = (Occurrence *)malloc(occCapacity * sizeof(Occurrence));
    if (!occurrences) {
        fprintf(stderr, "메모리 할당 실패 (occurrences)\n");
        free(shiftTable);
        free_hash_table(hashTable);
        free(hashTable);
        free(prefixes);
        exit(EXIT_FAILURE);
    }
    
    // 검색: 텍스트를 BLOCK_SIZE 단위로 스캔하며 후보 패턴 검증
    int s = minLen - BLOCK_SIZE; // 초기 스캔 위치: 최소 패턴의 끝 블록 정렬
    while (s <= n - minLen) {
        int hashVal = block_hash(text + s);
        int shift = shiftTable[hashVal];
        if (shift > 0) {
            s += shift;
        } else {
            // shift == 0: 후보 패턴이 있을 수 있음.
            CandidateList clist = hashTable[hashVal];
            for (i = 0; i < clist.count; i++) {
                int patId = clist.indices[i];
                int patLen = (int)strlen(patterns[patId]);
                // 추정되는 매칭 시작 위치: s - (patLen - BLOCK_SIZE)
                int pos = s - (patLen - BLOCK_SIZE);
                if (pos < 0 || pos + patLen > n)
                    continue;
                // 후보 패턴과 텍스트의 해당 위치 비교
                if (strncmp(text + pos, patterns[patId], patLen) == 0) {
                    if (occCount == occCapacity) {
                        occCapacity *= 2;
                        Occurrence *temp = (Occurrence *)realloc(occurrences, occCapacity * sizeof(Occurrence));
                        if (!temp) {
                            fprintf(stderr, "결과 배열 재할당 실패 (occurrences)\n");
                            free(occurrences);
                            free(shiftTable);
                            free_hash_table(hashTable);
                            free(hashTable);
                            free(prefixes);
                            exit(EXIT_FAILURE);
                        }
                        occurrences = temp;
                    }
                    occurrences[occCount].patternId = patId;
                    occurrences[occCount].start = pos;
                    occCount++;
                }
            }
            s++;
        }
    }
    
    // Cleanup
    free(shiftTable);
    free_hash_table(hashTable);
    free(hashTable);
    free(prefixes);
    
    *matchCount = occCount;
    return occurrences;
}

/* main 함수: Wu-Manber 알고리즘 데모 */
int main(void) {
    const char *patterns[] = {"pattern", "search", "example"};
    int patternCount = sizeof(patterns) / sizeof(patterns[0]);
    const char *text = "this is an example pattern for search. another example is provided.";
    
    int matchCount = 0;
    Occurrence *matches = wu_manber_search(patterns, patternCount, text, &matchCount);
    if (matches == NULL || matchCount <= 0) {
        printf("패턴을 찾을 수 없습니다.\n");
    } else {
        printf("텍스트 \"%s\"에서 매칭 결과:\n", text);
        for (int i = 0; i < matchCount; i++) {
            printf("패턴 ID %d 발견, 시작 인덱스 %d\n", matches[i].patternId, matches[i].start);
        }
        free(matches);
    }
    
    return 0;
}