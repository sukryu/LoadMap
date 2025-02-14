# 동적 계획법 (Dynamic Programming)

동적 계획법(Dynamic Programming, DP)은 복잡한 문제를 더 작은 부분 문제들로 나누어 해결하고, 이들 결과를 재활용하여 전체 문제의 해답을 도출하는 알고리즘 설계 기법입니다.  
DP는 문제의 하위 문제가 서로 겹치는 경우에 특히 유용하며, 메모이제이션(Memoization)과 테이블화(Tabulation) 기법을 통해 계산 효율성을 크게 향상시킬 수 있습니다.

---

## 목차 📝
1. [개요](#개요)
2. [핵심 개념](#핵심-개념)
3. [알고리즘 설계 전략](#알고리즘-설계-전략)
4. [주요 문제 및 응용 분야](#주요-문제-및-응용-분야)
   - 최적화 문제
   - 경로 및 문자열 처리 문제
   - 게임 및 전략 문제
5. [추가 문제 및 주제](#추가-문제-및-주제)
6. [참고 자료](#참고-자료)

---

## 개요
동적 계획법은 두 가지 핵심 성질을 가진 문제에 적용됩니다:
- **최적 부분 구조 (Optimal Substructure):** 문제의 최적 해가 그 하위 문제들의 최적 해로부터 구성될 수 있음.
- **부분 문제의 중복 (Overlapping Subproblems):** 동일한 하위 문제가 여러 번 반복되어 계산되는 경우, 그 결과를 저장하여 중복 계산을 방지할 수 있음.

---

## 핵심 개념
- **메모이제이션 (Memoization):**  
  재귀 호출 중에 이미 계산된 하위 문제의 결과를 저장해두고, 동일한 문제가 재등장하면 저장된 값을 재사용합니다.
  
- **테이블화 (Tabulation):**  
  가장 작은 문제부터 차례대로 해결하며 결과를 테이블에 저장하고, 이를 바탕으로 전체 문제의 해를 구합니다.

- **상태 정의 및 전이:**  
  문제를 해결하기 위한 상태(state)를 정의하고, 각 상태 간 전이(transition)를 명확히 하는 것이 DP 설계의 핵심입니다.

---

## 알고리즘 설계 전략
동적 계획법은 문제를 두 가지 방식으로 접근할 수 있습니다:

1. **탑다운 방식 (Top-Down) / 메모이제이션:**  
   재귀를 사용하여 문제를 분할하고, 계산된 결과를 캐시에 저장합니다.  
   장점은 코드가 직관적이라는 것이며, 단점은 재귀 깊이가 깊어질 경우 스택 오버플로우의 위험이 있습니다.

2. **바텀업 방식 (Bottom-Up) / 테이블화:**  
   작은 부분 문제부터 차례대로 해결하여, 점차적으로 전체 문제의 해답을 도출합니다.  
   장점은 반복문을 사용하여 스택 오버플로우 문제를 회피할 수 있다는 것이며, 단점은 전체 테이블을 구성해야 하므로 메모리 사용량이 많을 수 있습니다.

---

## 주요 문제 및 응용 분야

### 최적화 문제
- **배낭 문제 (Knapsack Problem):**  
  제한된 자원 내에서 최대의 가치를 얻기 위한 아이템 선택 문제.
  [문제 바로가기](./Knapsack/README.md)

- **최장 공통 부분 수열 (Longest Common Subsequence):**  
  두 문자열 사이에서 공통되는 부분 수열 중 가장 긴 것을 찾는 문제.
  [문제 바로가기](./LongestCommon/README.md)

- **최장 증가 부분 수열 (Longest Increasing Subsequence):**  
  배열에서 증가하는 순서대로 가장 긴 부분 수열을 찾는 문제.
  [문제 바로가기](./LongestIncreasing/README.md)
  
- **최대 부분 배열 문제 (Maximum Subarray Problem):**  
  연속된 부분 배열의 합이 최대가 되는 구간을 찾는 문제 (Kadane's 알고리즘).
  [문제 바로가기](../divide-conquer/MaximumSubarray/README.md)

### 경로 및 문자열 처리 문제
- **편집 거리 (Edit Distance):**  
  두 문자열 간의 최소 편집 거리를 계산하여 유사도를 측정하는 문제.
  [문제 바로가기](./EditDistance/README.md)

- **행렬 체인 곱셈 (Matrix Chain Multiplication):**  
  연속된 행렬들의 곱셈 순서를 최적화하여 계산량을 최소화하는 문제.
  [문제 바로가기](./MatrixChainMultiplication/README.md)

- **최장 팰린드롬 부분 수열 (Longest Palindromic Subsequence):**  
  문자열에서 가장 긴 팰린드롬 부분 수열을 찾는 문제.
  [문제 바로가기](./LongestPalindromicSubsequence/README.md)

### 게임 및 전략 문제
- **게임 이론 및 상태 평가:**  
  여러 게임 및 전략 문제에서 승리 확률이나 최적 전략을 계산하는 데 DP를 활용합니다.
  [문제 바로가기](./Strategy/README.md)

- **스코어 최적화:**  
  일정한 규칙에 따라 점수를 최대화하는 문제 등에서 DP를 적용할 수 있습니다.
  [문제 바로가기](./ScoreOptimization/README.md)

---

## 추가 문제 및 주제
분할 정복과 동적 계획법의 결합 또는 최적화 기법을 통해 더욱 다양한 문제를 해결할 수 있습니다:
- **Divide and Conquer Optimization:**  
  특정 DP 문제에서 전이 인덱스의 단조성을 이용해 시간 복잡도를 개선하는 기법.
- **Knuth Optimization:**  
  특정 유형의 DP 문제에 적용되어 최적 전이 인덱스의 범위를 제한하는 최적화 기법.
- **Bitmask DP:**  
  부분 집합이나 조합 문제를 효율적으로 해결하기 위해 비트마스크를 활용한 DP.
- **DP on Trees:**  
  트리 구조에서 각 노드별 최적 해를 구하는 문제, 예를 들어 트리의 독립 집합 문제.
- **DP with Convex Hull Trick:**  
  함수의 볼록성을 활용하여 DP 전이의 최적화를 수행하는 기법.

---

## 참고 자료
- [Wikipedia - Dynamic Programming](https://en.wikipedia.org/wiki/Dynamic_programming)
- [Topcoder Dynamic Programming Tutorials](https://www.topcoder.com/community/competitive-programming/tutorials/dynamic-programming-from-novice-to-advanced/)
- 관련 알고리즘 서적:
  - "Competitive Programming 3" (Steven Halim & Felix Halim)
  - "Introduction to Algorithms" (Cormen, Leiserson, Rivest, Stein)
