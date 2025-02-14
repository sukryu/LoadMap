/**
 * main.c
 *
 * 고도화된 라빈-카프 (Rabin-Karp) 문자열 검색 알고리즘 구현 예제
 * - 입력 텍스트(text)에서 패턴(pattern)이 등장하는 모든 시작 인덱스를 동적 배열로 반환합니다.
 * - 롤링 해시(Rolling Hash) 기법을 사용하여 해시 값을 효율적으로 갱신하며,
 *   해시 값이 일치할 때 실제 문자열 비교를 통해 패턴의 정확한 일치를 확인합니다.
 * - 결과 배열은 동적으로 할당되며, 호출자가 free()로 메모리 해제해야 합니다.
 *
 * 사용 예:
 *   int matchCount = 0;
 *   int *matches = rabinKarpSearch("GEEKS FOR GEEKS", "GEEK", &matchCount);
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

#define BASE 256
#define MOD 1000000007LL

/**
 * rabinKarpSearch
 *
 * 라빈-카프 알고리즘을 사용하여 텍스트 내에서 패턴이 등장하는 모든 시작 인덱스를 찾습니다.
 *
 * @param text       검색할 텍스트 문자열
 * @param pattern    검색할 패턴 문자열
 * @param matchCount 출력: 패턴이 발견된 횟수를 저장 (0 이상)
 *
 * @return 동적 할당된 정수 배열 포인터 (각 요소는 패턴의 시작 인덱스),
 *         검색 결과가 없거나 오류 발생 시 NULL을 반환합니다.
 *         반환된 배열은 호출자가 free()로 해제해야 합니다.
 */
int *rabinKarpSearch(const char *text, const char *pattern, int *matchCount) {
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
    
    // 초기 해시 값 계산을 위한 변수 설정
    long long patternHash = 0;
    long long textHash = 0;
    long long h = 1;  // h = (BASE^(m-1)) % MOD
    
    // h 계산: BASE^(m-1) % MOD
    for (int i = 0; i < m - 1; i++) {
        h = (h * BASE) % MOD;
    }
    
    // 패턴과 텍스트의 첫 m문자에 대한 해시 값 계산
    for (int i = 0; i < m; i++) {
        patternHash = (patternHash * BASE + (unsigned char)pattern[i]) % MOD;
        textHash = (textHash * BASE + (unsigned char)text[i]) % MOD;
    }
    
    // 결과를 저장할 동적 배열 초기 할당
    int capacity = 10;
    int *results = (int *)malloc(sizeof(int) * capacity);
    if (results == NULL) {
        fprintf(stderr, "결과 배열 할당 실패\n");
        *matchCount = -1;
        return NULL;
    }
    
    int count = 0;
    
    // 텍스트에서 패턴 길이 만큼의 모든 부분 문자열에 대해 해시 비교
    for (int i = 0; i <= n - m; i++) {
        // 해시 값이 일치하면 실제 문자열 비교를 수행
        if (patternHash == textHash) {
            int j;
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == m) {
                // 패턴이 일치하면 결과 배열에 인덱스를 저장
                if (count == capacity) {
                    capacity *= 2;
                    int *temp = (int *)realloc(results, sizeof(int) * capacity);
                    if (temp == NULL) {
                        fprintf(stderr, "결과 배열 재할당 실패\n");
                        free(results);
                        *matchCount = -1;
                        return NULL;
                    }
                    results = temp;
                }
                results[count++] = i;
            }
        }
        // 다음 부분 문자열로 이동하면서 해시 값 갱신 (롤링 해시)
        if (i < n - m) {
            // 현재 해시에서 가장 앞의 문자 값을 제거하고 다음 문자를 추가
            textHash = (textHash - ((unsigned char)text[i] * h) % MOD + MOD) % MOD;
            textHash = (textHash * BASE + (unsigned char)text[i + m]) % MOD;
        }
    }
    
    *matchCount = count;
    return results;
}

// main 함수: 라빈-카프 알고리즘 데모
int main(void) {
    const char *text = "GEEKS FOR GEEKS";
    const char *pattern = "GEEK";
    int matchCount = 0;
    
    int *matches = rabinKarpSearch(text, pattern, &matchCount);
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