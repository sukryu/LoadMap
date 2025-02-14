/**
 * main.c
 *
 * 고도화된 Hybrid Pattern Matching 구현 예제
 * - 패턴의 길이와 데이터 특성에 따라 서로 다른 문자열 검색 알고리즘(브루트 포스, Boyer-Moore)을 선택하여 최적의 성능을 달성합니다.
 * - 짧은 패턴은 간단한 브루트 포스 알고리즘을, 긴 패턴은 Boyer-Moore 알고리즘(불일치 문자 규칙 기반)을 사용합니다.
 * - 검색 결과는 동적 배열로 반환되며, 호출자가 사용 후 free()로 메모리 해제해야 합니다.
 *
 * 사용 예:
 *   int matchCount = 0;
 *   int *matches = hybrid_pattern_search("This is a simple example", "example", &matchCount);
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
#include <limits.h>

#define PATTERN_THRESHOLD 10  // 패턴 길이가 이 값 미만이면 브루트 포스 사용

/* 
 * 브루트 포스 탐색 함수
 * - 텍스트 내에서 패턴과 일치하는 모든 시작 인덱스를 동적 배열로 반환합니다.
 */
int* brute_force_search(const char *text, const char *pattern, int *matchCount) {
    int n = (int)strlen(text);
    int m = (int)strlen(pattern);
    int capacity = 10;
    int count = 0;
    int *result = (int*)malloc(capacity * sizeof(int));
    if (!result) {
        fprintf(stderr, "메모리 할당 실패 (brute_force_search)\n");
        *matchCount = -1;
        return NULL;
    }
    
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && text[i+j] == pattern[j])
            j++;
        if (j == m) {
            if (count == capacity) {
                capacity *= 2;
                int *temp = (int*)realloc(result, capacity * sizeof(int));
                if (!temp) {
                    fprintf(stderr, "결과 배열 재할당 실패 (brute_force_search)\n");
                    free(result);
                    *matchCount = -1;
                    return NULL;
                }
                result = temp;
            }
            result[count++] = i;
        }
    }
    
    *matchCount = count;
    return result;
}

/*
 * Boyer-Moore 탐색 함수 (불일치 문자 규칙만 사용)
 * - 패턴의 각 문자에 대한 마지막 등장 위치를 이용하여 건너뛰기 간격을 결정합니다.
 * - 텍스트 내에서 패턴과 일치하는 모든 시작 인덱스를 동적 배열로 반환합니다.
 */
int* bm_search(const char *text, const char *pattern, int *matchCount) {
    int n = (int)strlen(text);
    int m = (int)strlen(pattern);
    int capacity = 10;
    int count = 0;
    int *result = (int*)malloc(capacity * sizeof(int));
    if (!result) {
        fprintf(stderr, "메모리 할당 실패 (bm_search)\n");
        *matchCount = -1;
        return NULL;
    }
    
    // Build Bad Character Table
    int badChar[256];
    for (int i = 0; i < 256; i++)
        badChar[i] = -1;
    for (int i = 0; i < m; i++)
        badChar[(unsigned char)pattern[i]] = i;
    
    int s = 0;  // shift of the pattern with respect to text
    while (s <= n - m) {
        int j = m - 1;
        // Compare pattern from rightmost character
        while (j >= 0 && pattern[j] == text[s + j])
            j--;
        if (j < 0) {
            // Pattern found at shift s
            if (count == capacity) {
                capacity *= 2;
                int *temp = (int*)realloc(result, capacity * sizeof(int));
                if (!temp) {
                    fprintf(stderr, "결과 배열 재할당 실패 (bm_search)\n");
                    free(result);
                    *matchCount = -1;
                    return NULL;
                }
                result = temp;
            }
            result[count++] = s;
            // Shift pattern so that next character in text aligns with last occurrence in pattern.
            // If no such occurrence, shift by m+1.
            s += (s + m < n) ? m - badChar[(unsigned char)text[s + m]] : 1;
        } else {
            int shift = j - badChar[(unsigned char)text[s + j]];
            s += (shift > 0) ? shift : 1;
        }
    }
    
    *matchCount = count;
    return result;
}

/*
 * Hybrid Pattern Matching 함수
 * - 패턴 길이가 PATTERN_THRESHOLD 미만이면 브루트 포스 탐색을,
 *   그렇지 않으면 Boyer-Moore 탐색을 사용합니다.
 */
int* hybrid_pattern_search(const char *text, const char *pattern, int *matchCount) {
    if (!text || !pattern || !matchCount) {
        fprintf(stderr, "입력 인자에 NULL이 전달되었습니다.\n");
        return NULL;
    }
    
    int m = (int)strlen(pattern);
    // 선택 기준: 패턴 길이가 작으면 단순 브루트 포스, 그렇지 않으면 Boyer-Moore 사용
    if (m < PATTERN_THRESHOLD) {
        return brute_force_search(text, pattern, matchCount);
    } else {
        return bm_search(text, pattern, matchCount);
    }
}

/* main 함수: Hybrid Pattern Matching 알고리즘 데모 */
int main(void) {
    const char *text = "This is a simple example to demonstrate hybrid pattern matching.";
    const char *pattern = "pattern";
    int matchCount = 0;
    
    int *matches = hybrid_pattern_search(text, pattern, &matchCount);
    if (!matches && matchCount <= 0) {
        printf("패턴을 찾을 수 없습니다.\n");
    } else if (matchCount > 0) {
        printf("텍스트 \"%s\"에서 패턴 \"%s\"의 매칭 위치:\n", text, pattern);
        for (int i = 0; i < matchCount; i++) {
            printf("인덱스 %d\n", matches[i]);
        }
        free(matches);
    } else {
        printf("검색 중 오류가 발생했습니다.\n");
    }
    
    return 0;
}