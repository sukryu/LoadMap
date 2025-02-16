/*
 * main.c
 *
 * 이 파일은 코딩 테스트에서 특수 문자열 패턴 문제를 해결하기 위한 예제 함수들을 포함합니다.
 *
 * 주요 기능:
 * 1. 와일드카드 매칭 (Wildcard Matching):
 *    - 패턴에 '?'와 '*'를 포함하여, 주어진 문자열이 패턴과 일치하는지 판별합니다.
 *    - DP(Dynamic Programming)를 사용하여 O(m*n) 시간 복잡도로 문제를 해결합니다.
 *
 * 2. 정규 표현식 매칭 (Regular Expression Matching):
 *    - 패턴에 '.'와 '*'를 포함하여, 주어진 문자열이 정규 표현식 규칙에 맞는지 판별합니다.
 *    - DP를 사용하여 O(m*n) 시간 복잡도로 문제를 해결합니다.
 *
 * 3. KMP 알고리즘을 이용한 부분 문자열 검색:
 *    - KMP 알고리즘으로 텍스트 내에서 패턴이 처음 등장하는 위치를 효율적으로 찾습니다.
 *    - 전처리 단계에서 LPS 배열(부분 일치 테이블)을 계산하여 O(n + m) 시간 복잡도로 동작합니다.
 *
 * 각 함수는 상세한 주석과 함께 구현되어 있어, 코드만 보더라도 알고리즘의 동작 원리 및 시간/공간 복잡도를 쉽게 이해할 수 있습니다.
 *
 * 참고: 이 파일에는 main 함수는 포함되어 있지 않으므로, 별도의 테스트 코드나 main 함수를 작성하여
 *       이 함수들을 호출하고 검증할 수 있습니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 함수: isWildcardMatch
 * -----------------------
 * 설명:
 *   와일드카드 패턴 매칭 문제를 DP를 통해 해결합니다.
 *   패턴 p는 '?' (임의의 한 문자)와 '*' (0개 이상의 문자)를 포함할 수 있습니다.
 *
 * 매개변수:
 *   - s: 입력 문자열 (null 종료)
 *   - p: 패턴 문자열 (null 종료)
 *
 * 반환값:
 *   문자열 s가 패턴 p와 매칭되면 1, 그렇지 않으면 0을 반환합니다.
 *
 * 시간 복잡도: O(m*n), m = strlen(s), n = strlen(p)
 * 공간 복잡도: O(m*n)
 */
int isWildcardMatch(const char *s, const char *p) {
    int m = strlen(s);
    int n = strlen(p);

    // dp[i][j]를 1차원 배열로 표현, 크기는 (m+1) x (n+1)
    // dp[i*(n+1) + j]는 s[0..i-1]와 p[0..j-1]가 매칭되는지 여부를 저장
    int *dp = (int*)malloc((m + 1) * (n + 1) * sizeof(int));
    if (!dp) return 0;  // 메모리 할당 실패 시 0 반환

    // 모든 셀을 0으로 초기화
    for (int i = 0; i < (m + 1) * (n + 1); i++) {
        dp[i] = 0;
    }

    // 빈 문자열과 빈 패턴은 매칭됨
    dp[0 * (n + 1) + 0] = 1;

    // 패턴이 '*'인 경우 빈 문자열과도 매칭될 수 있으므로, 첫 번째 행을 미리 초기화
    for (int j = 1; j <= n; j++) {
        if (p[j - 1] == '*')
            dp[0 * (n + 1) + j] = dp[0 * (n + 1) + (j - 1)];
        else
            dp[0 * (n + 1) + j] = 0;
    }

    // DP 테이블 채우기
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '*') {
                // '*'는 빈 문자열에 해당하거나, 현재 문자를 포함할 수 있음:
                // 1. '*'가 빈 문자열과 매칭 (dp[i][j-1])
                // 2. '*'가 s[i-1]을 매칭 (dp[i-1][j])
                dp[i * (n + 1) + j] = dp[i * (n + 1) + (j - 1)] || dp[(i - 1) * (n + 1) + j];
            } else if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
                // '?' 또는 현재 문자가 일치하는 경우, 이전 상태의 매칭 결과를 그대로 사용
                dp[i * (n + 1) + j] = dp[(i - 1) * (n + 1) + (j - 1)];
            } else {
                // 문자가 일치하지 않는 경우
                dp[i * (n + 1) + j] = 0;
            }
        }
    }

    int result = dp[m * (n + 1) + n];
    free(dp);
    return result;
}

/*
 * 함수: isRegexMatch
 * --------------------
 * 설명:
 *   정규 표현식 매칭 문제를 DP를 통해 해결합니다.
 *   패턴 p는 '.' (임의의 한 문자)와 '*' (바로 앞 문자가 0번 이상 반복됨)를 포함할 수 있습니다.
 *
 * 매개변수:
 *   - s: 입력 문자열 (null 종료)
 *   - p: 정규 표현식 패턴 (null 종료)
 *
 * 반환값:
 *   문자열 s가 패턴 p와 매칭되면 1, 그렇지 않으면 0을 반환합니다.
 *
 * 시간 복잡도: O(m*n), m = strlen(s), n = strlen(p)
 * 공간 복잡도: O(m*n)
 */
int isRegexMatch(const char *s, const char *p) {
    int m = strlen(s);
    int n = strlen(p);

    // dp[i][j]는 s[0..i-1]와 p[0..j-1]가 매칭되는지 여부를 저장하는 2차원 배열을 1차원으로 표현
    int *dp = (int*)malloc((m + 1) * (n + 1) * sizeof(int));
    if (!dp) return 0;  // 메모리 할당 실패 시 0 반환

    // 모든 셀을 0으로 초기화
    for (int i = 0; i < (m + 1) * (n + 1); i++) {
        dp[i] = 0;
    }

    // 빈 문자열과 빈 패턴은 매칭됨
    dp[0 * (n + 1) + 0] = 1;

    // 패턴에서 '*'는 바로 앞의 문자와 결합되어 빈 문자열과도 매칭될 수 있으므로, 초기화
    for (int j = 1; j <= n; j++) {
        if (p[j - 1] == '*' && j >= 2)
            dp[0 * (n + 1) + j] = dp[0 * (n + 1) + (j - 2)];
    }

    // DP 테이블 채우기
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '*') {
                // '*'는 두 가지 경우를 고려:
                // 1. '*'를 0회 사용: dp[i][j-2]
                // 2. '*'를 1회 이상 사용: p[j-2]가 s[i-1]와 일치하거나 '.'인 경우, dp[i-1][j]
                dp[i * (n + 1) + j] = dp[i * (n + 1) + (j - 2)] ||
                                      ((p[j - 2] == s[i - 1] || p[j - 2] == '.') && dp[(i - 1) * (n + 1) + j]);
            } else if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                // 문자가 일치하거나 '.'인 경우, 이전 상태의 결과를 그대로 사용
                dp[i * (n + 1) + j] = dp[(i - 1) * (n + 1) + (j - 1)];
            } else {
                dp[i * (n + 1) + j] = 0;
            }
        }
    }

    int result = dp[m * (n + 1) + n];
    free(dp);
    return result;
}

/*
 * 함수: computeLPS
 * -------------------
 * 설명:
 *   KMP 알고리즘에서 사용되는 LPS(Longest Prefix Suffix) 배열을 계산합니다.
 *   LPS 배열은 패턴 내에서 각 위치까지의 부분 문자열에 대해, 
 *   접두사와 접미사가 일치하는 최대 길이를 저장합니다.
 *
 * 매개변수:
 *   - pattern: 검색할 패턴 문자열 (null 종료)
 *   - m: 패턴의 길이
 *
 * 반환값:
 *   동적 할당된 LPS 배열의 포인터 (caller가 free()를 통해 메모리 해제 필요)
 *
 * 시간 복잡도: O(m)
 * 공간 복잡도: O(m)
 */
int *computeLPS(const char *pattern, int m) {
    int *lps = (int*)malloc(m * sizeof(int));
    if (!lps) return NULL;  // 메모리 할당 실패 시 NULL 반환

    // lps[0]은 항상 0
    lps[0] = 0;
    int len = 0;  // 이전 최대 접두사-접미사 길이
    int i = 1;
    
    // 패턴 전체를 순회하면서 LPS 배열 계산
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            // 현재 문자가 일치하면, 길이를 증가시키고 lps[i]에 저장
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                // 이전에 저장된 lps 값을 이용하여 len 값을 재조정
                len = lps[len - 1];
            } else {
                // 일치하지 않고 len이 0이면 lps[i]는 0
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

/*
 * 함수: kmpSearch
 * ------------------
 * 설명:
 *   KMP 알고리즘을 사용하여 텍스트(text) 내에서 패턴(pattern)이 처음 등장하는 위치를 찾습니다.
 *   패턴이 발견되면 해당 인덱스를 반환하며, 발견되지 않으면 -1을 반환합니다.
 *
 * 매개변수:
 *   - text: 검색 대상 텍스트 문자열 (null 종료)
 *   - pattern: 검색할 패턴 문자열 (null 종료)
 *
 * 반환값:
 *   패턴이 처음 등장하는 인덱스 (0 기반) 또는 패턴이 없으면 -1
 *
 * 시간 복잡도: O(n + m), n = strlen(text), m = strlen(pattern)
 * 공간 복잡도: O(m) (LPS 배열)
 */
int kmpSearch(const char *text, const char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    
    // 빈 패턴은 항상 0번 인덱스에서 매칭됨
    if (m == 0) return 0;
    
    // LPS 배열 계산
    int *lps = computeLPS(pattern, m);
    if (!lps) return -1;  // 메모리 할당 실패 시 -1 반환

    int i = 0; // text의 인덱스
    int j = 0; // pattern의 인덱스

    // 텍스트 전체를 순회하며 패턴 매칭 시도
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }
        if (j == m) {
            // 패턴 전체가 매칭된 경우, 시작 인덱스는 i - j
            free(lps);
            return i - j;
        } else if (i < n && text[i] != pattern[j]) {
            // 불일치가 발생한 경우, 이전 LPS 값을 활용하여 j 조정
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    free(lps);
    return -1;  // 패턴이 텍스트 내에 없음
}

/*
 * End of main.c
 *
 * 이 파일은 특수 문자열 패턴 문제를 해결하기 위한 예제 함수들을 포함합니다.
 *
 * 포함된 기능:
 * - isWildcardMatch: 와일드카드 ('?'와 '*')를 포함한 패턴 매칭 (DP 기반)
 * - isRegexMatch: 정규 표현식 ('.'와 '*') 매칭 (DP 기반)
 * - computeLPS 및 kmpSearch: KMP 알고리즘을 이용한 부분 문자열 검색
 *
 * 각 함수는 상세한 주석과 함께 구현되어 있어, 코드만 보더라도 알고리즘의 동작 원리와
 * 시간/공간 복잡도를 쉽게 이해할 수 있도록 작성되었습니다.
 *
 * 참고: 이 파일에는 main 함수가 포함되어 있지 않으므로, 별도의 테스트 코드나 main 함수를 작성하여
 *        이 함수들을 호출하고 검증할 수 있습니다.
 */
