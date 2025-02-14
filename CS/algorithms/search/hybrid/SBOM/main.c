/**
 * main.c
 *
 * 고도화된 Set-Backward Oracle Matching (SBOM) 알고리즘 구현 예제
 * - 이 구현은 Boyer-Moore의 불일치 휴리스틱과 Factor Oracle (오토마타 기반) 자료구조를 결합하여
 *   단일 패턴 검색을 수행하는 하이브리드 알고리즘입니다.
 * - 패턴에 대해 Factor Oracle을 구축하고, 이를 활용하여 텍스트 내에서 패턴을 빠르게 검증합니다.
 * - 동시에, Boyer-Moore의 아이디어에 기반한 글로벌 불일치 문자 이동 테이블(global shift table)을 사용하여
 *   불일치 발생 시 효과적으로 검색 위치를 건너뜁니다.
 *
 * 사용 예:
 *   int matchCount = 0;
 *   int *matches = sbom_search("abracadabra", "abra", &matchCount);
 *   if (matches) {
 *       for (int i = 0; i < matchCount; i++) {
 *           printf("패턴 발견 위치: %d\n", matches[i]);
 *       }
 *       free(matches);
 *   }
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 256

/*---------------- Factor Oracle 자료구조 ----------------*/

/*
 * FOState: Factor Oracle의 각 상태를 나타내는 구조체.
 * - transitions: 각 문자에 대한 상태 전이 (-1이면 전이가 없음)
 * - suffix: 실패(또는 suffix) 링크 (오토마타 구축 시 사용)
 */
typedef struct {
    int transitions[ALPHABET_SIZE];
    int suffix;
} FOState;

/*
 * buildFactorOracle
 *
 * 주어진 패턴에 대해 Factor Oracle을 구축합니다.
 * 알고리즘:
 *  - 패턴 길이 m에 대해 m+1개의 상태를 생성합니다.
 *  - 각 상태의 모든 전이를 초기화한 후,
 *    상태 i-1에서 문자 pattern[i-1]에 대한 전이를 상태 i로 추가합니다.
 *  - 이후, 실패 링크를 적절히 설정합니다.
 *
 * 반환: 동적 할당된 FOState 배열 (크기: m+1)
 *         호출자가 free()로 메모리 해제해야 함.
 */
FOState* buildFactorOracle(const char *pattern) {
    int m = (int)strlen(pattern);
    FOState *oracle = (FOState *)malloc((m + 1) * sizeof(FOState));
    if (!oracle) {
        fprintf(stderr, "메모리 할당 실패 (Factor Oracle)\n");
        exit(EXIT_FAILURE);
    }
    // 초기화: 모든 전이 값을 -1, suffix 링크 0 (나중에 설정)
    for (int i = 0; i <= m; i++) {
        for (int c = 0; c < ALPHABET_SIZE; c++) {
            oracle[i].transitions[c] = -1;
        }
        oracle[i].suffix = 0;
    }
    oracle[0].suffix = -1; // 초기 상태의 suffix 링크는 -1

    for (int i = 1; i <= m; i++) {
        unsigned char c = (unsigned char)pattern[i - 1];
        // 직접 전이 추가: 상태 i-1 --c--> 상태 i
        oracle[i - 1].transitions[c] = i;
        // 실패 링크 전파
        int k = oracle[i - 1].suffix;
        while (k != -1 && oracle[k].transitions[c] == -1) {
            oracle[k].transitions[c] = i;
            k = oracle[k].suffix;
        }
        if (k == -1)
            oracle[i].suffix = 0;
        else
            oracle[i].suffix = oracle[k].transitions[c];
    }
    return oracle;
}

/*---------------- 글로벌 불일치 문자 이동 테이블 ----------------*/

/*
 * computeGlobalShift
 *
 * 패턴에 대해 Boyer-Moore 스타일의 불일치 문자 휴리스틱을 적용하여,
 * 각 문자 c에 대해 이동 거리를 globalShift[c]에 계산합니다.
 * - 만약 c가 패턴에 등장하지 않으면, 이동 거리는 (m + 1)로 설정됩니다.
 * - 그렇지 않으면, globalShift[c] = m - lastOccurrence[c] - 1.
 */
void computeGlobalShift(const char *pattern, int globalShift[ALPHABET_SIZE]) {
    int m = (int)strlen(pattern);
    int last[ALPHABET_SIZE];
    for (int c = 0; c < ALPHABET_SIZE; c++) {
        last[c] = -1;
    }
    for (int i = 0; i < m; i++) {
        last[(unsigned char)pattern[i]] = i;
    }
    for (int c = 0; c < ALPHABET_SIZE; c++) {
        if (last[c] == -1)
            globalShift[c] = m + 1;
        else
            globalShift[c] = m - last[c] - 1;
    }
}

/*---------------- SBOM 검색 함수 ----------------*/

/*
 * sbom_search
 *
 * SBOM 알고리즘을 사용하여 텍스트 내에서 패턴이 등장하는 모든 시작 인덱스를 찾습니다.
 * - 먼저, 패턴에 대한 Factor Oracle을 구축하고, 글로벌 불일치 문자 이동 테이블을 계산합니다.
 * - 검색 단계에서는 텍스트의 위치 s에서, Factor Oracle을 이용해 패턴과의 전이 과정을 수행합니다.
 *   만약 전체 패턴에 대해 전이가 성공하면 매칭된 것으로 간주하고, 결과 배열에 s를 기록합니다.
 * - 불일치가 발생하면, 텍스트의 해당 위치 문자에 따른 글로벌 이동 거리를 사용하여 s를 업데이트합니다.
 *
 * 반환: 동적 할당된 정수 배열 (매칭 위치 인덱스들)
 *         매칭된 개수는 matchCount에 저장됨.
 *         호출자가 free()로 결과 배열 메모리 해제 필요.
 */
int* sbom_search(const char *text, const char *pattern, int *matchCount) {
    if (!text || !pattern || !matchCount) {
        fprintf(stderr, "입력 인자에 NULL이 전달되었습니다.\n");
        return NULL;
    }
    int n = (int)strlen(text);
    int m = (int)strlen(pattern);
    if (m == 0) {
        *matchCount = 0;
        return NULL;
    }
    
    // Factor Oracle 구축
    FOState *oracle = buildFactorOracle(pattern);
    // 글로벌 불일치 이동 테이블 계산
    int globalShift[ALPHABET_SIZE];
    computeGlobalShift(pattern, globalShift);
    
    // 결과 배열 초기화
    int capacity = 10;
    int count = 0;
    int *result = (int *)malloc(capacity * sizeof(int));
    if (!result) {
        fprintf(stderr, "결과 배열 할당 실패 (sbom_search)\n");
        free(oracle);
        *matchCount = -1;
        return NULL;
    }
    
    int s = 0;
    while (s <= n - m) {
        int state = 0;
        int i;
        // Factor Oracle을 통해 패턴 전이 검사 (왼쪽부터 순차 비교)
        for (i = 0; i < m; i++) {
            unsigned char c = (unsigned char)text[s + i];
            if (oracle[state].transitions[c] != -1) {
                state = oracle[state].transitions[c];
            } else {
                break;
            }
        }
        if (i == m) {
            // 패턴이 완전히 매칭됨
            if (count == capacity) {
                capacity *= 2;
                int *temp = (int *)realloc(result, capacity * sizeof(int));
                if (!temp) {
                    fprintf(stderr, "결과 배열 재할당 실패 (sbom_search)\n");
                    free(result);
                    free(oracle);
                    *matchCount = -1;
                    return NULL;
                }
                result = temp;
            }
            result[count++] = s;
            // 매칭된 경우, 다음 비교 위치는 s + globalShift[다음 문자] (가능하면)
            if (s + m < n)
                s += globalShift[(unsigned char)text[s + m]];
            else
                s++;
        } else {
            // 불일치 발생: 텍스트의 첫 불일치 문자에 따른 이동
            int shift = globalShift[(unsigned char)text[s + i]];
            s += (shift > 0) ? shift : 1;
        }
    }
    
    free(oracle);
    *matchCount = count;
    return result;
}

/*---------------- main 함수 (데모) ----------------*/

int main(void) {
    const char *text = "abracadabra";
    const char *pattern = "abra";
    int matchCount = 0;
    
    int *matches = sbom_search(text, pattern, &matchCount);
    if (matches == NULL && matchCount == 0) {
        printf("패턴을 찾을 수 없습니다.\n");
    } else if (matchCount > 0) {
        printf("패턴 \"%s\"이(가) 텍스트 \"%s\" 내에서 발견된 위치:\n", pattern, text);
        for (int i = 0; i < matchCount; i++) {
            printf("인덱스 %d\n", matches[i]);
        }
        free(matches);
    } else {
        printf("검색 중 오류가 발생했습니다.\n");
    }
    
    return 0;
}