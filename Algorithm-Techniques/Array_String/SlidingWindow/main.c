/*
 * main.c
 *
 * 이 파일은 코딩 테스트에서 슬라이딩 윈도우 기법을 활용하여 다양한 문제를 해결하기 위한 예제 함수들을 포함합니다.
 * 각 함수는 슬라이딩 윈도우 기법을 적용한 최적의 해결책을 제시하며, 시간 및 공간 복잡도를 고려하여 구현되었습니다.
 * 아래 함수들은 매우 상세한 주석을 포함하고 있어, 코드만 보더라도 각 알고리즘의 동작 원리와 구현 방법을 쉽게 이해할 수 있습니다.
 *
 * 포함된 함수 목록:
 * 1. maxFixedWindowSum:
 *      - 문제: 길이가 k인 연속된 부분 배열 중 최대 합을 구하는 문제
 *      - 기법: 고정 길이 슬라이딩 윈도우
 * 2. minSubarrayLength:
 *      - 문제: 연속된 부분 배열의 합이 target 이상이 되는 최소 길이를 구하는 문제
 *      - 기법: 가변 길이 슬라이딩 윈도우
 * 3. longestUniqueSubstringLength:
 *      - 문제: 문자열에서 중복 없이 가장 긴 부분 문자열의 길이를 구하는 문제
 *      - 기법: 가변 길이 슬라이딩 윈도우 + 문자 빈도 배열 활용
 *
 * 참고: 이 파일에는 main 함수는 포함되어 있지 않습니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 함수: maxFixedWindowSum
 * --------------------------------
 * 설명:
 *   주어진 정수 배열 'arr'와 배열의 길이 'n', 그리고 고정된 윈도우 크기 'k'가 주어질 때,
 *   길이가 k인 모든 연속 부분 배열의 합 중 최대값을 반환합니다.
 *
 * 방법:
 *   1. 초기 윈도우(첫 k개 원소)의 합을 계산합니다.
 *   2. 슬라이딩 윈도우 기법을 사용하여, 윈도우가 한 칸씩 오른쪽으로 이동할 때마다
 *      이전 윈도우의 첫 번째 원소를 빼고, 새로운 원소를 더하여 합을 업데이트합니다.
 *   3. 매 이동마다 현재 윈도우의 합과 최대 합을 비교하여 최대 값을 갱신합니다.
 *
 * 매개변수:
 *   - arr: 정수 배열 (입력 데이터)
 *   - n: 배열의 원소 개수
 *   - k: 고정된 윈도우의 크기 (연속된 부분 배열의 길이)
 *
 * 반환값:
 *   길이가 k인 연속 부분 배열들의 합 중 최대값을 반환합니다.
 *
 * 시간 복잡도: O(n)
 * 공간 복잡도: O(1)
 */
int maxFixedWindowSum(int* arr, int n, int k) {
    // 만약 윈도우 크기 k가 배열의 길이보다 크면, 올바른 계산을 할 수 없으므로 에러 처리
    if (k > n) return -1;
    
    int currentSum = 0;
    int maxSum = 0;
    
    // 초기 윈도우의 합 계산 (첫 k개의 원소)
    for (int i = 0; i < k; i++) {
        currentSum += arr[i];
    }
    maxSum = currentSum;
    
    // 오른쪽으로 윈도우를 한 칸씩 이동시키며 합을 업데이트
    for (int i = k; i < n; i++) {
        // 윈도우 이동: 이전 윈도우의 첫 원소를 빼고, 새로운 원소를 더함
        currentSum = currentSum - arr[i - k] + arr[i];
        // 최대 합 갱신
        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
    }
    return maxSum;
}

/*
 * 함수: minSubarrayLength
 * --------------------------------
 * 설명:
 *   주어진 정수 배열 'arr'와 배열의 길이 'n', 그리고 목표 합 'target'이 주어질 때,
 *   연속된 부분 배열의 합이 target 이상이 되는 최소 길이를 반환합니다.
 *
 * 방법:
 *   1. 오른쪽 포인터(right)를 이동시키며 현재 윈도우의 합(currentSum)을 증가시킵니다.
 *   2. 현재 합이 target 이상이 되면, 왼쪽 포인터(left)를 이동시켜 윈도우 크기를 축소하면서
 *      조건을 만족하는 최소 길이를 갱신합니다.
 *
 * 매개변수:
 *   - arr: 정수 배열 (양의 정수)
 *   - n: 배열의 길이
 *   - target: 부분 배열의 합이 이 값 이상이어야 함
 *
 * 반환값:
 *   조건을 만족하는 최소 부분 배열의 길이를 반환합니다.
 *   조건을 만족하는 부분 배열이 없으면 0을 반환합니다.
 *
 * 시간 복잡도: O(n)
 * 공간 복잡도: O(1)
 */
int minSubarrayLength(int* arr, int n, int target) {
    int minLength = n + 1; // 가능한 최대 길이보다 큰 값으로 초기화
    int currentSum = 0;    // 현재 윈도우의 합
    int left = 0;          // 윈도우의 시작 인덱스
    
    // 오른쪽 포인터를 0부터 n-1까지 이동
    for (int right = 0; right < n; right++) {
        // 현재 윈도우에 새로운 원소 추가
        currentSum += arr[right];
        
        // 현재 합이 target 이상이면, 윈도우를 축소하며 최소 길이 갱신
        while (currentSum >= target) {
            int currentLength = right - left + 1;
            if (currentLength < minLength) {
                minLength = currentLength;
            }
            // 윈도우에서 가장 왼쪽 원소 제거 후, 왼쪽 포인터 이동
            currentSum -= arr[left];
            left++;
        }
    }
    // 조건을 만족하는 부분 배열이 없으면 0 반환
    return (minLength == n + 1) ? 0 : minLength;
}

/*
 * 함수: longestUniqueSubstringLength
 * --------------------------------
 * 설명:
 *   주어진 문자열 's'에서 중복 없이 구성된 가장 긴 부분 문자열의 길이를 반환합니다.
 *
 * 방법:
 *   1. 두 포인터(left, right)를 사용하여 문자열의 윈도우를 관리합니다.
 *   2. 오른쪽 포인터를 이동시키며, 현재 윈도우 내에 중복 문자가 있는지 확인합니다.
 *   3. 중복이 발생하면, 왼쪽 포인터를 이동시켜 중복 문자를 제거합니다.
 *   4. 매 이동마다 현재 윈도우의 길이를 측정하여 최대 길이를 갱신합니다.
 *
 * 매개변수:
 *   - s: 입력 문자열 (null 종료된 문자열)
 *
 * 반환값:
 *   중복 없는 가장 긴 부분 문자열의 길이를 반환합니다.
 *
 * 시간 복잡도: O(n), n은 문자열의 길이
 * 공간 복잡도: O(1) (상수 크기의 빈도 배열 사용)
 */
int longestUniqueSubstringLength(const char* s) {
    if (s == NULL) return 0; // NULL 입력에 대한 처리
    
    int n = strlen(s);
    int maxLen = 0;  // 최대 부분 문자열 길이 저장 변수
    int left = 0;    // 윈도우의 시작 인덱스
    
    // ASCII 문자에 대한 등장 빈도를 기록하는 배열 (크기 128)
    int freq[128] = {0};
    
    // 오른쪽 포인터를 0부터 n-1까지 이동하면서 윈도우를 확장
    for (int right = 0; right < n; right++) {
        char currentChar = s[right];
        
        // 만약 현재 문자가 윈도우 내에 이미 존재한다면,
        // 중복이 제거될 때까지 왼쪽 포인터를 이동
        while (freq[(int)currentChar] > 0) {
            freq[(int)s[left]]--; // 윈도우에서 제거되는 문자의 빈도 감소
            left++;              // 윈도우의 시작 인덱스 이동
        }
        
        // 현재 문자를 윈도우에 포함시키고 빈도 증가
        freq[(int)currentChar]++;
        
        // 현재 윈도우의 길이 계산 및 최대 길이 갱신
        int currentWindowLength = right - left + 1;
        if (currentWindowLength > maxLen) {
            maxLen = currentWindowLength;
        }
    }
    return maxLen;
}

/*
 * End of main.c
 *
 * 이 파일은 코딩 테스트에서 슬라이딩 윈도우 기법을 활용하여 다양한 문제를 해결하기 위한
 * 예제 함수들을 포함합니다. 각 함수는 상세한 주석과 함께 구현되어 있어, 코드만 보더라도
 * 알고리즘의 동작 원리 및 시간/공간 복잡도를 쉽게 이해할 수 있도록 작성되었습니다.
 *
 * 참고: main 함수는 포함되어 있지 않으므로, 별도의 테스트 코드나 main 함수를 작성하여
 * 이 함수들을 호출 및 검증할 수 있습니다.
 */
