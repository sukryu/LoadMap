# 누적 합 기법 이론 정리

누적 합(Cumulative Sum) 기법은 배열이나 2차원 행렬과 같은 데이터 구조에서 부분 합(구간 합)을 효율적으로 계산하기 위한 방법입니다. 이 문서에서는 누적 합 기법의 기본 개념, 동작 원리, 다양한 응용 사례 및 주의사항을 초보자도 쉽게 이해할 수 있도록 아주 자세하게 설명합니다.

---

## 1. 누적 합 기법이란?

- **기본 개념:**  
  누적 합 기법은 주어진 배열의 각 원소까지의 합을 미리 계산하여, 이후 특정 구간의 합을 빠르게 구할 수 있도록 하는 알고리즘입니다.  
  예를 들어, 배열 A가 주어졌을 때, prefix 배열 P를 정의하여 P[i] = A[0]부터 A[i]까지의 합으로 계산합니다.

- **목적:**  
  구간 합을 매번 반복 계산하지 않고, 미리 계산된 누적 합을 이용하여 O(1) 시간에 구간 합을 조회할 수 있습니다.

---

## 2. 누적 합 기법의 기본 원리

1. **누적 합 배열의 구성:**  
   - 원본 배열 `A`의 길이를 `n`이라 할 때, 누적 합 배열 `P`는 `n+1` 길이(또는 n 길이)로 생성합니다.
   - 일반적으로 `P[0]`을 0으로 초기화하고, 그 다음부터 `P[i] = P[i-1] + A[i-1]` (1-indexed 기준)으로 계산합니다.
   - 이를 통해 배열의 구간 합, 예를 들어 `A[l]`부터 `A[r]`까지의 합은 `P[r+1] - P[l]`로 구할 수 있습니다.

2. **구간 합 계산:**  
   - 구간 합을 계산할 때, 전체 합을 다시 계산하지 않고 두 값의 차이만으로 O(1)에 계산 가능하므로, 반복되는 구간 합 문제에서 매우 유용합니다.

3. **2차원 누적 합:**  
   - 2차원 배열(행렬)의 경우, 각 위치 (i, j)까지의 누적 합을 계산해두면 특정 영역의 합을 빠르게 계산할 수 있습니다.
   - 2차원 누적 합 배열 `P[i][j]`는 보통 `P[i][j] = P[i-1][j] + P[i][j-1] - P[i-1][j-1] + A[i][j]` 와 같이 정의합니다.

---

## 3. 누적 합 기법의 주요 응용 문제 유형

- **구간 합 문제:**  
  예를 들어, 배열 내 특정 범위의 합을 여러 번 계산해야 하는 문제에서 누적 합 배열을 사용하면 효율적으로 처리할 수 있습니다.
  
- **부분 배열/부분 행렬의 최적화 문제:**  
  주어진 조건에 맞는 구간의 합이나 평균 등을 빠르게 구하여, 최적의 결과를 도출하는 문제에 활용됩니다.
  
- **데이터 분석 및 통계 계산:**  
  실시간 데이터 분석에서 누적 합을 이용해 구간별 합계나 평균값을 신속하게 계산할 수 있습니다.

- **DP(동적 계획법)와의 결합:**  
  누적 합 기법은 특정 문제의 상태 전이를 빠르게 계산할 때 보조 도구로 활용되기도 합니다.

---

## 4. 시간 및 공간 복잡도

- **시간 복잡도:**  
  - 누적 합 배열을 구성하는 데 O(n) 시간이 소요됩니다.
  - 이후 각 구간의 합을 조회할 때는 O(1) 시간이 소요됩니다.
  
- **공간 복잡도:**  
  - 원본 배열과 동일한 크기의 추가 배열(Prefix Sum 배열)이 필요하므로 O(n)의 추가 공간이 필요합니다.
  - 2차원 배열의 경우, O(n*m)의 공간 복잡도가 발생합니다.

---

## 5. 누적 합 기법 사용 시 주의사항

- **인덱스 관리:**  
  - 배열의 인덱스가 0부터 시작하는지, 1부터 시작하는지에 따라 누적 합 배열을 구성하는 방식이 달라집니다.
  - 구간 합 계산 시, 시작 및 끝 인덱스를 올바르게 처리해야 합니다.

- **경계 조건 처리:**  
  - 빈 배열이나 특정 범위가 배열의 끝을 초과하는 경우를 반드시 고려해야 합니다.
  - 2차원 누적 합의 경우, 행 또는 열이 0인 경계를 특별히 처리해야 합니다.

- **정수 오버플로우:**  
  - 누적 합의 값이 매우 커질 경우, 정수 오버플로우에 주의해야 합니다.
  - 필요한 경우, 자료형을 적절하게 선택하거나 오버플로우를 방지하는 방법을 고려합니다.

- **데이터 업데이트 문제:**  
  - 배열의 값이 동적으로 변하는 경우, 누적 합 기법은 재계산이 필요하므로 세그먼트 트리나 펜윅 트리와 같은 자료구조를 고려할 수 있습니다.

---

## 6. 예제 코드 (의사코드)

### 6.1 1차원 누적 합 예제

```
function buildPrefixSum(A):
    n = length(A)
    // P[0]을 0으로 초기화하여, 구간 합 계산 시 편리하게 사용
    P = new array of size (n + 1)
    P[0] = 0
    for i from 1 to n:
        P[i] = P[i-1] + A[i-1]
    return P

// 구간 [l, r]의 합은 P[r+1] - P[l]로 계산
function rangeSum(P, l, r):
    return P[r+1] - P[l]
```

### 6.2 2차원 누적 합 예제

```
function build2DPrefixSum(A):
    rows = number of rows in A
    cols = number of columns in A
    // P 배열은 A와 동일한 크기 +1 행과 +1 열을 포함하여 경계를 쉽게 처리
    P = new 2D array of size (rows+1) x (cols+1)
    for i from 1 to rows:
        for j from 1 to cols:
            P[i][j] = P[i-1][j] + P[i][j-1] - P[i-1][j-1] + A[i-1][j-1]
    return P

// 구간 (r1, c1)부터 (r2, c2)의 합은 다음과 같이 계산
function rangeSum2D(P, r1, c1, r2, c2):
    return P[r2+1][c2+1] - P[r1][c2+1] - P[r2+1][c1] + P[r1][c1]
```

---

## 7. 결론

누적 합 기법은 배열이나 행렬의 구간 합을 효율적으로 계산할 수 있게 해주는 매우 강력한 도구입니다.  
- **장점:**  
  한 번 누적 합 배열을 구성하면 이후 구간 합 계산이 O(1)에 가능해, 반복되는 합 계산 문제에서 큰 성능 향상을 기대할 수 있습니다.
- **적용 문제:**  
  구간 합, 부분 배열/행렬 문제, 동적 계획법 등 다양한 문제에 적용 가능하며, 특히 대량의 데이터에서 빠른 연산이 필요할 때 유용합니다.
- **주의사항:**  
  인덱스 관리, 경계 조건, 오버플로우, 동적 업데이트 문제 등을 꼼꼼히 체크하여 올바른 구현을 보장해야 합니다.

이 문서를 통해 누적 합 기법의 기본 원리와 구현 방법을 충분히 이해하고, 실제 코딩 테스트나 문제 해결에 효과적으로 활용하시길 바랍니다.