/*
 * main.cpp
 *
 * 이 파일은 "팰린드롬(회문)" 관련 문제들을 모아서,
 * 여러 유형별로 함수를 작성하고 상세 주석을 제공하는 예시 코드입니다.
 *
 * 포함된 함수 목록:
 *
 * 1) isPalindrome
 *    - 주어진 문자열이 팰린드롬인지(앞뒤가 같은지) 판별
 *
 * 2) longestPalindromeExpand
 *    - "가장 긴 팰린드롬 부분 문자열(Longest Palindromic Substring)" 문제를
 *      중심 확장(Expand Around Center) 기법으로 해결 (O(n^2) 시간)
 *
 * 3) longestPalindromeDP
 *    - 가장 긴 팰린드롬 부분 문자열을 동적 계획법(DP)으로 해결 (O(n^2) 시간, O(n^2) 공간)
 *
 * 4) longestPalindromeManacher
 *    - 가장 긴 팰린드롬 부분 문자열을 Manacher 알고리즘으로 해결 (O(n) 시간)
 *
 * 5) countPalindromicSubstrings
 *    - 문자열 내에 존재하는 모든 팰린드롬 부분 문자열의 총 개수를
 *      중심 확장 기법으로 세는 예시 (O(n^2) 시간)
 *
 * 주의:
 *  - 본 파일은 함수들을 예시로 작성하였으며, 실제로 동작을 확인하려면
 *    별도의 main 함수를 작성하여 이 함수를 호출해야 합니다.
 *  - 각 함수는 학습 및 참고 목적의 예제 수준으로 구현되었습니다.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*
 * 함수: isPalindrome
 * ------------------
 * 설명:
 *   주어진 문자열 s가 팰린드롬(회문)인지 판별합니다.
 *   앞에서 읽으나 뒤에서 읽으나 동일하면 팰린드롬입니다.
 *
 * 매개변수:
 *   - s: 검사할 문자열
 *
 * 반환값:
 *   - true: s가 팰린드롬이면
 *   - false: 그렇지 않으면
 *
 * 시간 복잡도: O(n)
 * 공간 복잡도: O(1)
 */
bool isPalindrome(const string &s) {
    int left = 0;
    int right = static_cast<int>(s.size()) - 1;
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

/*
 * 함수: longestPalindromeExpand
 * --------------------------------
 * 설명:
 *   "가장 긴 팰린드롬 부분 문자열(Longest Palindromic Substring)"을
 *   중심 확장(Expand Around Center) 기법을 사용해 찾는 함수입니다.
 *
 * 매개변수:
 *   - s: 탐색할 문자열
 *
 * 반환값:
 *   s 내 존재하는 가장 긴 팰린드롬 부분 문자열 (여러 개일 경우, 그 중 하나)
 *
 * 시간 복잡도: O(n^2)
 *   - 각 인덱스를 중심으로 왼쪽/오른쪽으로 최대 O(n) 확장
 * 공간 복잡도: O(1) (추가 배열 사용 없음)
 *
 * 알고리즘 개요:
 *   1) 각 인덱스 i를 "홀수 길이 팰린드롬"의 중심이라 가정하고 확장
 *   2) 각 인덱스 i, i+1 사이를 "짝수 길이 팰린드롬"의 중심이라 가정하고 확장
 *   3) 확장 과정에서 가장 긴 팰린드롬 구간을 기록
 */
string longestPalindromeExpand(const string &s) {
    if (s.empty()) return "";

    int start = 0, maxLen = 1; // 최소 길이가 1 이상

    auto expandAroundCenter = [&](int left, int right) {
        while (left >= 0 && right < static_cast<int>(s.size()) &&
               s[left] == s[right]) {
            left--;
            right++;
        }
        // 팰린드롬이 깨진 직전 범위: (left+1, right-1)
        int length = right - left - 1;
        if (length > maxLen) {
            maxLen = length;
            start = left + 1;
        }
    };

    for (int i = 0; i < (int)s.size(); i++) {
        // 홀수 길이 (문자 i를 중심)
        expandAroundCenter(i, i);
        // 짝수 길이 (문자 i, i+1 사이를 중심)
        expandAroundCenter(i, i + 1);
    }

    return s.substr(start, maxLen);
}

/*
 * 함수: longestPalindromeDP
 * ---------------------------
 * 설명:
 *   "가장 긴 팰린드롬 부분 문자열"을 동적 계획법(DP)으로 해결하는 방법입니다.
 *
 * 매개변수:
 *   - s: 탐색할 문자열
 *
 * 반환값:
 *   s 내 존재하는 가장 긴 팰린드롬 부분 문자열 (복수 존재 시 그 중 하나)
 *
 * 시간 복잡도: O(n^2)
 * 공간 복잡도: O(n^2)
 *
 * 알고리즘 개요 (DP 정의):
 *   - dp[i][j] = s의 i번째 문자부터 j번째 문자까지 부분 문자열이
 *                팰린드롬인지 여부(true/false).
 *   - 점화식:
 *     1) 길이 1은 무조건 팰린드롬
 *     2) 길이 2는 두 문자가 같으면 팰린드롬
 *     3) 길이가 3 이상일 때,
 *        s[i] == s[j] && dp[i+1][j-1] == true → dp[i][j] = true
 */
string longestPalindromeDP(const string &s) {
    int n = static_cast<int>(s.size());
    if (n < 2) return s;

    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int maxLen = 1;
    int start = 0;

    // 길이 1 → 모두 팰린드롬
    for (int i = 0; i < n; i++) {
        dp[i][i] = true;
    }

    // 길이 2 처리
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            if (maxLen < 2) {
                maxLen = 2;
                start = i;
            }
        }
    }

    // 길이 3 이상
    for (int length = 3; length <= n; length++) {
        // 시작 인덱스 i
        for (int i = 0; i + length - 1 < n; i++) {
            int j = i + length - 1; // 끝 인덱스
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                if (length > maxLen) {
                    maxLen = length;
                    start = i;
                }
            }
        }
    }

    return s.substr(start, maxLen);
}

/*
 * 함수: longestPalindromeManacher
 * ---------------------------------
 * 설명:
 *   "가장 긴 팰린드롬 부분 문자열" 문제를 Manacher 알고리즘을 통해 O(n)에 해결합니다.
 *
 * 매개변수:
 *   - s: 탐색할 문자열
 *
 * 반환값:
 *   s 내 존재하는 가장 긴 팰린드롬 부분 문자열
 *
 * 시간 복잡도: O(n)
 * 공간 복잡도: O(n) (전처리 문자열과 보조 배열)
 *
 * 알고리즘 개요:
 *   1) 문자열 전처리(문자 사이에 '#' 삽입 등)를 통해 홀/짝수 구분 없이 처리
 *   2) 각 인덱스에서의 '팰린드롬 반경'을 p 배열에 저장
 *   3) 현재 오른쪽 경계를 유지하면서, i의 대칭 위치(mirror) 정보를 활용해 p[i] 초기화
 *   4) i에서 추가로 확장하며 p[i] 갱신 → right, center 업데이트
 *   5) 최대 반경을 가진 center 찾기 후, 원본 문자열로 역매핑하여 결과 반환
 */
string longestPalindromeManacher(const string &s) {
    if (s.empty()) return "";

    // 전처리: ^# + 각 문자 + # + $ 형태
    // 예) "abba" -> "^#a#b#b#a#$"
    string t = "^#";
    for (char c : s) {
        t.push_back(c);
        t.push_back('#');
    }
    t.push_back('$');

    int n = (int)t.size();
    vector<int> p(n, 0); // p[i] : i를 중심으로 한 팰린드롬 반경
    int center = 0, right = 0;
    int maxLen = 0, maxCenter = 0;

    for (int i = 1; i < n - 1; i++) {
        int mirror = 2 * center - i;
        if (i < right) {
            p[i] = min(right - i, p[mirror]);
        }
        // i에서 좌우 확장
        while (t[i + (p[i] + 1)] == t[i - (p[i] + 1)]) {
            p[i]++;
        }
        // 더 오른쪽에 도달했다면 center, right 갱신
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
        // 최대 반경 갱신
        if (p[i] > maxLen) {
            maxLen = p[i];
            maxCenter = i;
        }
    }

    // p[maxCenter] = maxLen
    // t에서 인덱스 (maxCenter - maxLen) ~ (maxCenter + maxLen)
    // '#' 제외, '^','$' 제외 → 원본 문자열 부분 문자열 복원
    int startInT = maxCenter - maxLen;
    int endInT = maxCenter + maxLen;

    // 복원
    string result;
    result.reserve(maxLen); // 대략적으로 reserve
    for (int i = startInT; i <= endInT; i++) {
        char c = t[i];
        // '#' '^' '$'는 스킵
        if (c != '#' && c != '^' && c != '$') {
            result.push_back(c);
        }
    }
    return result;
}

/*
 * 함수: countPalindromicSubstrings
 * ---------------------------------
 * 설명:
 *   문자열 내 존재하는 "팰린드롬 부분 문자열"의 총 개수를 세는 함수입니다.
 *   (예: "aaa" → "a", "a", "a", "aa", "aa", "aaa" 총 6개)
 *
 * 매개변수:
 *   - s: 탐색할 문자열
 *
 * 반환값:
 *   팰린드롬 부분 문자열의 총 개수(중복 포함)
 *
 * 시간 복잡도: O(n^2)
 * 공간 복잡도: O(1)
 *
 * 알고리즘 개요 (중심 확장):
 *   - 각 인덱스 i를 기준으로, 홀수/짝수 팰린드롬을 확장하며 세어 줌
 *   - 확장하면서 발견되는 모든 팰린드롬마다 count++
 */
int countPalindromicSubstrings(const string &s) {
    int n = (int)s.size();
    if (n == 0) return 0;

    int count = 0;

    // 확장 함수
    auto expandCount = [&](int left, int right) {
        while (left >= 0 && right < n && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
    };

    // 모든 중심에 대해 확장
    for (int i = 0; i < n; i++) {
        // 홀수 길이 팰린드롬
        expandCount(i, i);
        // 짝수 길이 팰린드롬
        expandCount(i, i + 1);
    }

    return count;
}

/*
 * 주의:
 *   - 위 함수들은 예시로 작성된 것이며, 대규모 데이터나 특정 극단상황에서는
 *     추가 최적화가 필요할 수 있습니다.
 *   - 별도의 main 함수를 작성하여 원하는 함수를 호출하고 테스트하세요.
 *
 * 예시 (임시 main 함수):
 *
 *   int main() {
 *       string s = "babad";
 *
 *       // 1) 단일 문자열 팰린드롬 판별
 *       cout << (isPalindrome(s) ? "Palindrome" : "Not palindrome") << endl;
 *
 *       // 2) 가장 긴 팰린드롬 (중심 확장)
 *       cout << "Longest Expand: " << longestPalindromeExpand(s) << endl;
 *
 *       // 3) 가장 긴 팰린드롬 (DP)
 *       cout << "Longest DP: " << longestPalindromeDP(s) << endl;
 *
 *       // 4) 가장 긴 팰린드롬 (Manacher)
 *       cout << "Longest Manacher: " << longestPalindromeManacher(s) << endl;
 *
 *       // 5) 팰린드롬 부분 문자열 총 개수
 *       cout << "Count of Palindromic Substrings: "
 *            << countPalindromicSubstrings(s) << endl;
 *
 *       return 0;
 *   }
 *
 * End of palindromes.cpp
 */
