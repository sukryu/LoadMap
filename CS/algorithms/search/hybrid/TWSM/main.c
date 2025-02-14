/**
 * main.c
 *
 * 고도화된 Two-Way String Matching 알고리즘 구현 예제
 * - 이 알고리즘은 패턴의 "critical factorization" (분할점과 주기 정보를 이용)을
 *   활용하여 텍스트 내에서 패턴을 한 번만 스캔하면서 빠르게 검색합니다.
 * - 전처리 단계에서 패턴의 최대 접미사(maximal suffix)와 주기를 계산한 후,
 *   검색 단계에서 오른쪽(후반부)와 왼쪽(전반부) 비교를 효율적으로 수행합니다.
 *
 * 사용 예:
 *   int matchCount = 0;
 *   int *matches = two_way_search("abracadabra", "abra", &matchCount);
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

/* 
   maximal_suffix: 패턴의 최대 접미사와 그에 해당하는 주기를 계산합니다.
   flag 인자가 1이면 "lexicographically maximum" (>=)를, 0이면 "lexicographically minimum" (<=)을 기준으로 합니다.
   반환값은 계산된 최대 접미사의 시작 인덱스이며, *p에 주기가 저장됩니다.
*/
static int maximal_suffix(const char *s, int m, int flag, int *p) {
    int i = 0, j = 1, k = 0;
    *p = 1;
    while (j + k < m) {
        if (s[i + k] == s[j + k]) {
            k++;
        } else if ((s[i + k] < s[j + k]) == flag) {
            // s[j+k] is "better" than s[i+k] in the chosen order
            j = j + k + 1;
            k = 0;
            *p = j - i;
        } else {
            i = (j > i + k + 1) ? j : i + k + 1;
            j = i + 1;
            k = 0;
            *p = 1;
        }
    }
    return i;
}

/*
   two_way_critical: 패턴의 critical factorization를 계산합니다.
   두 가지 maximal_suffix 계산(하나는 >= 기준, 다른 하나는 <= 기준)을 수행한 후,
   더 큰 시작 인덱스를 critical 분할점(pos)로 선택하고, 해당 주기를 per에 저장합니다.
*/
static void two_way_critical(const char *pattern, int m, int *pos, int *per) {
    int p1, p2;
    int ms1 = maximal_suffix(pattern, m, 1, &p1);
    int ms2 = maximal_suffix(pattern, m, 0, &p2);
    if (ms1 > ms2) {
        *pos = ms1;
        *per = p1;
    } else {
        *pos = ms2;
        *per = p2;
    }
}

/*
   two_way_search: Two-Way String Matching 알고리즘을 사용하여 텍스트 내에서
   패턴이 등장하는 모든 시작 인덱스를 동적 배열로 반환합니다.
   - text: 검색할 텍스트 문자열
   - pattern: 검색할 패턴 문자열
   - matchCount: 매칭된 패턴의 개수를 출력합니다.
   
   반환된 배열은 동적으로 할당되며, 호출자가 사용 후 free()로 해제해야 합니다.
*/
int *two_way_search(const char *text, const char *pattern, int *matchCount) {
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
    
    // 전처리: 패턴의 critical factorization 계산
    int pos, per;
    two_way_critical(pattern, m, &pos, &per);
    
    // 결과 저장을 위한 동적 배열 초기화
    int capacity = 10;
    int *result = (int *)malloc(capacity * sizeof(int));
    if (!result) {
        fprintf(stderr, "결과 배열 할당 실패\n");
        *matchCount = -1;
        return NULL;
    }
    int count = 0;
    
    int i = 0;       // 텍스트 내에서의 현재 검색 시작 인덱스
    int memory = 0;  // 이전 비교에서 왼쪽 부분에서 일치한 문자 수
    while (i <= n - m) {
        // 오른쪽 부분(후반부) 비교: pos와 memory 중 큰 값부터 시작
        int j = (pos > memory) ? pos : memory;
        while (j < m && pattern[j] == text[i + j]) {
            j++;
        }
        if (j < m) {
            // 불일치 발생: 건너뛰기 간격은 (j - memory + 1)
            i += j - memory + 1;
            memory = 0;
        } else {
            // 후반부 모두 일치하면, 왼쪽 부분(전반부) 비교 수행
            int k = pos - 1;
            while (k >= memory && pattern[k] == text[i + k]) {
                k--;
            }
            if (k < memory) {
                // 전체 패턴이 일치함
                if (count == capacity) {
                    capacity *= 2;
                    int *temp = (int *)realloc(result, capacity * sizeof(int));
                    if (!temp) {
                        fprintf(stderr, "결과 배열 재할당 실패\n");
                        free(result);
                        *matchCount = -1;
                        return NULL;
                    }
                    result = temp;
                }
                result[count++] = i;
            }
            // 패턴이 주기(per)만큼 이동
            i += per;
            // 이전 비교에서 오른쪽 부분이 일치했던 문자의 수를 보존
            memory = (m - per > 0) ? m - per : 0;
        }
    }
    
    *matchCount = count;
    return result;
}

/* main 함수: Two-Way String Matching 알고리즘 데모 */
int main(void) {
    const char *text = "abracadabra";
    const char *pattern = "abra";
    int matchCount = 0;
    
    int *matches = two_way_search(text, pattern, &matchCount);
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