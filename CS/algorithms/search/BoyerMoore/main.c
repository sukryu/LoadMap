/**
 * main.c
 *
 * 고도화된 보이어-무어 (Boyer-Moore) 문자열 검색 알고리즘 구현 예제
 * - 입력 텍스트(text)에서 패턴(pattern)이 등장하는 모든 시작 인덱스를 동적 배열로 반환합니다.
 * - 불일치 문자 규칙(Bad Character Rule)과 좋은 접미사 규칙(Good Suffix Rule)을 사용하여,
 *   검색 시 불필요한 비교를 크게 줄이고, 빠른 탐색을 수행합니다.
 * - 결과 배열은 동적으로 할당되며, 호출자가 사용 후 free()로 메모리 해제해야 합니다.
 *
 * 사용 예:
 *   int matchCount = 0;
 *   int *matches = boyer_moore_search("HERE IS A SIMPLE EXAMPLE", "EXAMPLE", &matchCount);
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

/**
 * preprocess_bad_character
 *
 * 불일치 문자 규칙(Bad Character Rule)을 위한 테이블을 계산합니다.
 * 각 문자에 대해, 패턴 내에서 해당 문자가 마지막으로 등장하는 인덱스를 기록합니다.
 *
 * @param pattern   검색할 패턴 문자열
 * @param m         패턴의 길이
 * @param badChar   ALPHABET_SIZE 크기의 배열에 결과 저장 (초기값은 -1)
 */
void preprocess_bad_character(const char *pattern, int m, int badChar[ALPHABET_SIZE]) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        badChar[i] = -1;
    for (int i = 0; i < m; i++)
        badChar[(unsigned char)pattern[i]] = i;
}

/**
 * preprocess_strong_suffix
 *
 * 패턴에 대한 강한 접미사(suffix) 배열을 계산합니다.
 * 이 배열은 좋은 접미사 규칙(Good Suffix Rule) 테이블 계산에 사용됩니다.
 *
 * @param pattern   검색할 패턴 문자열
 * @param m         패턴의 길이
 * @param suffix    m 크기의 정수 배열에 결과 저장
 */
void preprocess_strong_suffix(const char *pattern, int m, int *suffix) {
    suffix[m - 1] = m;
    int g = m - 1;
    int f = 0;
    for (int i = m - 2; i >= 0; i--) {
        if (i > g && suffix[i + m - 1 - f] < i - g)
            suffix[i] = suffix[i + m - 1 - f];
        else {
            if (i < g)
                g = i;
            f = i;
            while (g >= 0 && pattern[g] == pattern[g + m - 1 - f])
                g--;
            suffix[i] = f - g;
        }
    }
}

/**
 * preprocess_good_suffix
 *
 * 좋은 접미사 규칙(Good Suffix Rule) 테이블을 계산합니다.
 * 이 테이블은 패턴의 부분 문자열이 일치한 경우, 얼마나 건너뛰어야 하는지를 결정합니다.
 *
 * @param pattern     검색할 패턴 문자열
 * @param m           패턴의 길이
 * @param goodSuffix  m 크기의 정수 배열에 결과 저장
 */
void preprocess_good_suffix(const char *pattern, int m, int *goodSuffix) {
    int *suffix = (int *)malloc(m * sizeof(int));
    if (!suffix) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    preprocess_strong_suffix(pattern, m, suffix);
    for (int i = 0; i < m; i++)
        goodSuffix[i] = m; // 기본적으로 전체 패턴 길이만큼 이동
    int j = 0;
    for (int i = m - 1; i >= 0; i--) {
        if (suffix[i] == i + 1) {
            for (; j < m - 1 - i; j++) {
                if (goodSuffix[j] == m)
                    goodSuffix[j] = m - 1 - i;
            }
        }
    }
    for (int i = 0; i <= m - 2; i++) {
        goodSuffix[m - 1 - suffix[i]] = m - 1 - i;
    }
    free(suffix);
}

/**
 * boyer_moore_search
 *
 * 보이어-무어 알고리즘을 사용하여 텍스트 내에서 패턴이 등장하는 모든 시작 인덱스를 찾습니다.
 *
 * @param text        검색할 텍스트 문자열
 * @param pattern     검색할 패턴 문자열
 * @param matchCount  출력: 검색 결과로 발견된 패턴의 개수를 저장 (0 이상)
 *
 * @return 동적 할당된 정수 배열 포인터 (각 요소는 패턴의 시작 인덱스),
 *         검색 결과가 없거나 오류 발생 시 NULL을 반환합니다.
 *         반환된 배열은 호출자가 free()로 해제해야 합니다.
 */
int *boyer_moore_search(const char *text, const char *pattern, int *matchCount) {
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
    
    int *badChar = (int *)malloc(ALPHABET_SIZE * sizeof(int));
    if (!badChar) {
        fprintf(stderr, "메모리 할당 실패\n");
        *matchCount = -1;
        return NULL;
    }
    preprocess_bad_character(pattern, m, badChar);
    
    int *goodSuffix = (int *)malloc(m * sizeof(int));
    if (!goodSuffix) {
        fprintf(stderr, "메모리 할당 실패\n");
        free(badChar);
        *matchCount = -1;
        return NULL;
    }
    preprocess_good_suffix(pattern, m, goodSuffix);
    
    int capacity = 10;
    int *result = (int *)malloc(capacity * sizeof(int));
    if (!result) {
        fprintf(stderr, "결과 배열 할당 실패\n");
        free(badChar);
        free(goodSuffix);
        *matchCount = -1;
        return NULL;
    }
    
    int count = 0;
    int s = 0; // 텍스트 내에서 패턴의 시작 위치 (shift)
    while (s <= n - m) {
        int j = m - 1;
        // 패턴의 뒤쪽부터 비교하여 일치 여부 확인
        while (j >= 0 && pattern[j] == text[s + j])
            j--;
        if (j < 0) {
            // 패턴 전체가 일치한 경우
            if (count == capacity) {
                capacity *= 2;
                int *temp = (int *)realloc(result, capacity * sizeof(int));
                if (!temp) {
                    fprintf(stderr, "결과 배열 재할당 실패\n");
                    free(result);
                    free(badChar);
                    free(goodSuffix);
                    *matchCount = -1;
                    return NULL;
                }
                result = temp;
            }
            result[count++] = s;
            // goodSuffix[0]는 전체 패턴이 일치한 경우 이동 거리
            s += goodSuffix[0];
        } else {
            int shiftBad = j - badChar[(unsigned char)text[s + j]];
            int shiftGood = goodSuffix[j];
            int shift = (shiftBad > shiftGood) ? shiftBad : shiftGood;
            if (shift < 1)
                shift = 1;
            s += shift;
        }
    }
    
    free(badChar);
    free(goodSuffix);
    *matchCount = count;
    return result;
}

// main 함수: 보이어-무어 알고리즘 데모
int main(void) {
    const char *text = "HERE IS A SIMPLE EXAMPLE";
    const char *pattern = "EXAMPLE";
    int matchCount = 0;
    
    int *matches = boyer_moore_search(text, pattern, &matchCount);
    if (!matches || matchCount <= 0) {
        printf("패턴을 찾을 수 없습니다.\n");
    } else {
        printf("패턴 \"%s\"이(가) 텍스트 내에서 발견된 위치:\n", pattern);
        for (int i = 0; i < matchCount; i++) {
            printf("인덱스 %d\n", matches[i]);
        }
        free(matches);
    }
    
    return 0;
}