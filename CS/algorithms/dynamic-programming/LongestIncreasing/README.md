# 최장 증가 부분 수열 (Longest Increasing Subsequence, LIS)

## 개요
최장 증가 부분 수열 문제는 주어진 수열에서, 원소들의 순서를 유지하면서 증가하는 부분 수열 중 가장 긴 것을 찾는 문제입니다.  
이 문제는 동적 계획법(Dynamic Programming) 및 기타 최적화 기법을 통해 효율적으로 해결할 수 있으며, 다양한 분야(예: 데이터 분석, 주식 시장 분석, 생물정보학 등)에서 응용됩니다.

## 문제 설명
- **입력:**  
  하나의 수열 A = [a₁, a₂, ..., aₙ] (일반적으로 정수 배열)
  
- **목표:**  
  A의 원소들의 순서를 유지하면서, 증가하는(각 원소가 이전 원소보다 큰) 부분 수열 중에서 길이가 가장 긴 것을 찾습니다.
  
- **예시:**  
  - 입력: A = [10, 22, 9, 33, 21, 50, 41, 60]  
    최장 증가 부분 수열(LIS)은 [10, 22, 33, 50, 60]로, 길이는 5입니다.

## 알고리즘의 핵심 아이디어
- **동적 계획법 (DP) 접근법:**  
  각 위치 i에 대해, A[i]를 마지막 원소로 하는 증가 부분 수열의 최대 길이를 dp[i]라고 정의합니다.
  점화식은 다음과 같이 구성할 수 있습니다:
  ```
  dp[i] = 1 + max { dp[j] } for all j < i such that A[j] < A[i],
  ```
  만약 그런 j가 없다면, dp[i] = 1입니다.
  
- **이진 검색을 이용한 최적화:**  
  O(n log n) 시간 복잡도를 달성하기 위해, 현재까지 찾은 증가 부분 수열의 마지막 원소들을 저장하는 배열을 유지하며,
  새로운 원소를 적절한 위치에 삽입(또는 대체)하는 방식으로 문제를 해결하는 기법도 존재합니다.

## 시간 및 공간 복잡도
- **동적 계획법 (DP) 방식:**  
  - 시간 복잡도: O(n²)
  - 공간 복잡도: O(n)
  
- **이진 검색 최적화 방식:**  
  - 시간 복잡도: O(n log n)
  - 공간 복잡도: O(n)

## 응용 분야
- **데이터 분석:**  
  시간에 따른 데이터의 추세를 분석하거나, 변화 추이를 파악하는 데 활용됩니다.
- **주식 시장 분석:**  
  주식 가격 데이터에서 최장 상승 구간(증가 추세)을 분석하는 데 사용됩니다.
- **생물정보학:**  
  유전자 서열 등에서 증가하는 패턴이나 특정 패턴을 찾는 문제에 응용될 수 있습니다.

## 참고 자료
- [Wikipedia - Longest Increasing Subsequence](https://en.wikipedia.org/wiki/Longest_increasing_subsequence)
- [GeeksforGeeks - Longest Increasing Subsequence](https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/)
- 관련 알고리즘 서적 및 학술 자료