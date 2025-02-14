# Divide and Conquer Optimization

## 개요
Divide and Conquer Optimization은 동적 계획법(DP) 문제에서 반복되는 계산을 효율적으로 줄이기 위해 분할 정복 기법을 적용하는 최적화 방법입니다.  
특히, DP의 점화식이 특정 모노토닉 성질(예: 사각 부등식(quadrangle inequality) 또는 단조성(monotonicity))을 만족하는 경우, 이 기법을 통해 일반적으로 O(n²) 또는 그 이상의 시간 복잡도를 O(n log n) 또는 O(n) 수준으로 개선할 수 있습니다.

## 알고리즘의 핵심 아이디어
- **문제 분할:**  
  DP 문제의 상태 전이가 어떤 구간에 대해 최적의 전이가 존재하는지를 분석하여, 상태를 분할 정복 방식으로 해결합니다.

- **최적화 조건:**  
  Divide and Conquer Optimization을 적용하기 위해서는 다음과 같은 조건이 필요합니다:
  - **모노토닉성 (Monotonicity):**  
    최적 결정을 내리는 인덱스가 DP 테이블의 진행 방향에 따라 단조롭게 변해야 합니다.
  - **사각 부등식 (Quadrangle Inequality) 또는 Convexity:**  
    비용 함수나 전이 함수가 볼록(convex)하거나, 특정 사각 부등식을 만족하면 최적화가 가능합니다.

- **분할 정복 전략:**  
  DP의 상태 전이에서 최적 결정(예: 전이 인덱스)을 구간별로 분할하고, 각 구간에서 재귀적으로 최적해를 찾은 후 결합합니다.  
  이때, 각 구간에 대해 가능한 전이 인덱스의 범위를 추정할 수 있으므로, 불필요한 탐색을 줄여 전체 계산량을 감소시킵니다.

## 시간 및 공간 복잡도
- **시간 복잡도:**  
  일반적인 DP의 O(n²) 또는 O(n³) 계산을 Divide and Conquer Optimization을 통해 O(n log n) 또는 O(n)으로 단축할 수 있습니다.  
  실제 복잡도는 문제의 구조와 최적화 조건에 따라 달라집니다.
  
- **공간 복잡도:**  
  추가적으로 분할 정복을 위한 재귀 호출 스택과 보조 배열을 사용하므로, 일반적으로 O(n) 수준의 추가 공간이 필요합니다.

## 적용 사례
- **DP 문제 최적화:**  
  최적화 문제가 많아 계산 비용이 큰 DP 문제(예: 구간 합 최적화, 행렬 곱셈 순서 결정, 편집 거리 등)에서 적용 가능합니다.
  
- **문제 예시:**  
  - "Divide and Conquer Optimization"이 적용된 배낭 문제, 구간 분할 문제 등  
  - Knuth Optimization과 유사한 문제, 두 인덱스 사이의 최적 전이를 계산하는 문제

## 참고 자료
- [Wikipedia - Divide and Conquer Optimization](https://en.wikipedia.org/wiki/Divide_and_conquer_optimization)  
  (용어에 대한 개념과 응용 사례를 참고)
- 관련 알고리즘 서적 및 학술 자료:
  - "Competitive Programming 3" (Steven Halim 등) – DP 최적화 기법 소개
  - "Algorithm Design" (Jon Kleinberg, Éva Tardos) – 분할 정복 기법과 DP 최적화 관련 내용
