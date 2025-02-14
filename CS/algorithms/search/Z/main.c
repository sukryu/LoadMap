/**
 * z_algorithm.c
 *
 * 고도화된 Z 알고리즘 기반 문자열 검색 구현 예제
 * - 주어진 텍스트(text) 내에서 패턴(pattern)이 등장하는 모든 시작 인덱스를 동적 배열로 반환합니다.
 * - Z 알고리즘을 사용하여 "패턴 + '$' + 텍스트" 문자열의 Z 배열을 계산하고,
 *   패턴과 완벽하게 일치하는 부분을 찾아 그 시작 인덱스를 기록합니다.
 * - 결과 배열은 동적으로 할당되며, 호출자가 사용 후 free()로 메모리 해제해야 합니다.
 *
 * 사용 예:
 *   int matchCount = 0;
 *   int *matches = z_search("abracadabra", "abra", &matchCount);
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
 * computeZArray
 *
 * 주어진 문자열 s의 길이 n에 대해 Z 배열을 계산합니다.
 * Z[i]는 s[i..n-1]이 s의 접두사와 일치하는 최대 길이를 의미합니다.
 *
 * @param s  입력 문자열 (NULL 종료)
 * @param n  문자열의 길이
 * @return 동적으로 할당된 Z 배열 포인터 (호출자가 free()로 해제)
 */
int *computeZArray(const char *s, int n) {
    if (s == NULL || n <= 0) return NULL;
    
    int *Z = (int *)malloc(sizeof(int) * n);
    if (Z == NULL) {
        fprintf(stderr, "메모리 할당 실패 (Z 배열)\n");
        return NULL;
    }
    Z[0] = 0; // Z[0]는 보통 0으로 처리합니다.
    
    int L = 0, R = 0;
    for (int i = 1; i < n; i++) {
        if (i > R) {
            L = R = i;
            while (R < n && s[R - L] == s[R])
                R++;
            Z[i] = R - L;
            R--;
        } else {
            int k = i - L;
            if (Z[k] < R - i + 1)
                Z[i] = Z[k];
            else {
                L = i;
                while (R < n && s[R - L] == s[R])
                    R++;
                Z[i] = R - L;
                R--;
            }
        }
    }
    return Z;
}

/**
 * z_search
 *
 * Z 알고리즘을 사용하여 텍스트 내에서 패턴이 등장하는 모든 시작 인덱스를 찾습니다.
 *
 * @param text        검색할 텍스트 문자열
 * @param pattern     검색할 패턴 문자열
 * @param matchCount  출력: 검색 결과로 발견된 패턴의 개수를 저장 (0 이상)
 *
 * @return 동적 할당된 정수 배열 포인터 (각 요소는 텍스트 내에서 패턴의 시작 인덱스),
 *         검색 결과가 없거나 오류 발생 시 NULL을 반환합니다.
 *         반환된 배열은 호출자가 free()로 해제해야 합니다.
 */
int *z_search(const char *text, const char *pattern, int *matchCount) {
    if (text == NULL || pattern == NULL || matchCount == NULL) {
        fprintf(stderr, "입력 인자에 NULL이 전달되었습니다.\n");
        return NULL;
    }
    
    int textLen = (int)strlen(text);
    int patternLen = (int)strlen(pattern);
    if (patternLen == 0) {
        *matchCount = 0;
        return NULL;
    }
    
    // 새 문자열 생성: "패턴 + '$' + 텍스트"
    int concatLen = patternLen + 1 + textLen;
    char *concatStr = (char *)malloc((concatLen + 1) * sizeof(char));
    if (concatStr == NULL) {
        fprintf(stderr, "메모리 할당 실패 (concatStr)\n");
        *matchCount = -1;
        return NULL;
    }
    strcpy(concatStr, pattern);
    concatStr[patternLen] = '$';
    strcpy(concatStr + patternLen + 1, text);
    concatStr[concatLen] = '\0';
    
    // Z 배열 계산
    int *Z = computeZArray(concatStr, concatLen);
    if (Z == NULL) {
        free(concatStr);
        *matchCount = -1;
        return NULL;
    }
    
    // 결과 저장용 동적 배열 (초기 용량 10)
    int capacity = 10;
    int *result = (int *)malloc(capacity * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "메모리 할당 실패 (result 배열)\n");
        free(Z);
        free(concatStr);
        *matchCount = -1;
        return NULL;
    }
    
    int count = 0;
    // 인덱스 patternLen + 1 부터 확인 (패턴과 '$'를 건너뛰고 텍스트 시작)
    for (int i = patternLen + 1; i < concatLen; i++) {
        if (Z[i] == patternLen) {
            int pos = i - patternLen - 1; // 텍스트 내의 시작 인덱스
            if (count == capacity) {
                capacity *= 2;
                int *temp = (int *)realloc(result, capacity * sizeof(int));
                if (temp == NULL) {
                    fprintf(stderr, "결과 배열 재할당 실패\n");
                    free(result);
                    free(Z);
                    free(concatStr);
                    *matchCount = -1;
                    return NULL;
                }
                result = temp;
            }
            result[count++] = pos;
        }
    }
    
    free(Z);
    free(concatStr);
    *matchCount = count;
    return result;
}

// main 함수: Z 알고리즘 데모
int main(void) {
    const char *text = "abracadabra";
    const char *pattern = "abra";
    int matchCount = 0;
    
    int *matches = z_search(text, pattern, &matchCount);
    if (matches == NULL && matchCount <= 0) {
        printf("패턴을 찾을 수 없습니다.\n");
    } else {
        printf("패턴 \"%s\"이(가) 텍스트 \"%s\" 내에서 발견된 위치:\n", pattern, text);
        for (int i = 0; i < matchCount; i++) {
            printf("인덱스 %d\n", matches[i]);
        }
        free(matches);
    }
    
    return 0;
}