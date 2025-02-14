/**
 * main.c
 *
 * 고도화된 KMP (Knuth-Morris-Pratt) 문자열 검색 알고리즘 구현 예제
 *
 * 이 구현은 실무에서 사용할 수 있도록 robust하게 작성되었습니다.
 * - 입력 문자열(text)와 패턴(pattern)을 받아, 패턴이 나타나는 모든 시작 인덱스를 동적 배열로 반환합니다.
 * - 부분 일치 테이블(LPS: Longest Prefix Suffix)을 미리 계산하여 불필요한 비교를 줄입니다.
 * - 결과 배열은 동적으로 할당되며, 호출자가 사용 후 free()로 메모리 해제해야 합니다.
 *
 * 사용 예:
 *   int matchCount = 0;
 *   int *matches = kmp_search("ABABDABACDABABCABAB", "ABABCABAB", &matchCount);
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

/**
 * computeLPS
 *
 * 주어진 패턴에 대해 부분 일치 테이블(LPS 배열)을 계산합니다.
 *
 * @param pattern 검색할 패턴 문자열
 * @param m       패턴의 길이
 * @param lps     미리 할당된 정수 배열 (크기 m) - 결과로 LPS 값들이 채워집니다.
 */
static void computeLPS(const char *pattern, int m, int *lps) {
    int len = 0; // 이전 최대 접두사 길이
    lps[0] = 0;  // 첫 번째 문자는 항상 0
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                // 이전 접두사 길이를 참조하여 len 값을 업데이트
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

/**
 * kmp_search
 *
 * KMP 알고리즘을 사용하여 텍스트 내에서 패턴이 등장하는 모든 시작 인덱스를 찾습니다.
 *
 * @param text       검색할 텍스트 문자열
 * @param pattern    검색할 패턴 문자열
 * @param matchCount 출력: 검색 결과로 발견된 패턴의 개수를 저장 (0 이상)
 *
 * @return 동적 할당된 정수 배열 포인터 (각 요소는 패턴의 시작 인덱스),
 *         매치가 없거나 오류 발생 시 NULL을 반환합니다.
 *         반환된 배열은 호출자가 free()로 메모리 해제해야 합니다.
 */
int *kmp_search(const char *text, const char *pattern, int *matchCount) {
    // 입력 유효성 검사
    if (text == NULL || pattern == NULL || matchCount == NULL) {
        fprintf(stderr, "입력 인자에 NULL이 전달되었습니다.\n");
        return NULL;
    }

    int n = (int)strlen(text);
    int m = (int)strlen(pattern);

    // 패턴이 빈 문자열이면 검색할 수 없음
    if (m == 0) {
        *matchCount = 0;
        return NULL;
    }

    // LPS 배열 동적 할당 및 계산
    int *lps = (int *)malloc(sizeof(int) * m);
    if (lps == NULL) {
        fprintf(stderr, "LPS 배열 할당 실패\n");
        *matchCount = -1;
        return NULL;
    }
    computeLPS(pattern, m, lps);

    // 결과 배열 초기 할당 (동적 크기 조정)
    int capacity = 10;
    int *result = (int *)malloc(sizeof(int) * capacity);
    if (result == NULL) {
        fprintf(stderr, "결과 배열 할당 실패\n");
        free(lps);
        *matchCount = -1;
        return NULL;
    }

    int count = 0;  // 매치 횟수
    int i = 0;      // text 인덱스
    int j = 0;      // pattern 인덱스

    // 텍스트를 순회하며 패턴 검색
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            // 패턴이 발견된 경우, 시작 인덱스는 (i - j)
            if (count == capacity) {
                capacity *= 2;
                int *temp = (int *)realloc(result, sizeof(int) * capacity);
                if (temp == NULL) {
                    fprintf(stderr, "결과 배열 재할당 실패\n");
                    free(result);
                    free(lps);
                    *matchCount = -1;
                    return NULL;
                }
                result = temp;
            }
            result[count++] = i - j;
            // 다음 검색을 위해 j를 업데이트
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    free(lps);
    *matchCount = count;
    return result;
}

// main 함수: 고도화된 KMP 알고리즘 데모
int main(void) {
    const char *text = "ABABDABACDABABCABAB";
    const char *pattern = "ABABCABAB";
    int matchCount = 0;
    
    int *matches = kmp_search(text, pattern, &matchCount);
    if (matches == NULL && matchCount <= 0) {
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