# 최장 공통 부분 수열 (Longest Common Subsequence, LCS)

## 개요
최장 공통 부분 수열 문제는 두 개의 시퀀스(문자열, 배열 등)에서 공통으로 나타나는 부분 수열 중에서 길이가 가장 긴 것을 찾는 문제입니다.  
LCS는 생물정보학(예: DNA, 단백질 서열 비교), 텍스트 비교, 버전 관리 시스템 등 다양한 분야에서 활용되는 중요한 문제입니다.

## 문제 설명
- **입력:**  
  두 개의 시퀀스 X와 Y (예: 문자열 X와 Y)
- **목표:**  
  X와 Y에 공통으로 나타나는 부분 수열 중에서 길이가 가장 긴 수열을 찾습니다.
- **예시:**  
  - X = "ABCBDAB", Y = "BDCABC"  
    최장 공통 부분 수열(LCS)은 "BCAB" 또는 "BDAB" 등이 될 수 있으며, 길이는 4입니다.

## 알고리즘의 핵심 아이디어
- **동적 계획법 (Dynamic Programming):**  
  LCS 문제는 두 시퀀스의 접두사를 이용해 최적 부분 구조(Optimal Substructure)를 가지며,  
  중복되는 하위 문제들이 존재하므로 동적 계획법을 적용하여 효율적으로 해결할 수 있습니다.
  
- **DP 점화식:**  
  정의: `dp[i][j]`는 X의 처음 i개 원소와 Y의 처음 j개 원소를 고려했을 때의 LCS 길이  
  점화식:  
  ```
  if (X[i-1] == Y[j-1])
      dp[i][j] = dp[i-1][j-1] + 1;
  else
      dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
  ```
  - 초기 조건: `dp[0][j] = 0`와 `dp[i][0] = 0` (빈 시퀀스의 LCS는 항상 0)

## 시간 및 공간 복잡도
- **시간 복잡도:** O(m * n)  
  (m과 n은 각각 시퀀스 X와 Y의 길이)
- **공간 복잡도:** O(m * n)  
  (메모리 사용량은 DP 테이블의 크기에 비례하지만, 공간 최적화를 통해 O(min(m, n))로 줄일 수 있음)

## 응용 분야
- **문자열 비교:**  
  파일 차이점(다른 점)을 찾거나 버전 관리를 위한 텍스트 비교 도구에서 활용
- **생물정보학:**  
  DNA, RNA, 단백질 서열의 유사성 분석 및 계통수 추정
- **데이터 마이닝:**  
  시계열 데이터나 기타 시퀀스 데이터의 유사도 측정

## 참고 자료
- [Wikipedia - Longest common subsequence](https://en.wikipedia.org/wiki/Longest_common_subsequence)
- [GeeksforGeeks - Longest Common Subsequence](https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/)
- 관련 알고리즘 서적 및 학술 자료