# 분할 정복 알고리즘

분할 정복 알고리즘은 복잡한 문제를 여러 개의 더 작은 문제로 분할하여 각각 해결한 후, 그 결과를 결합함으로써 전체 문제의 해답을 도출하는 알고리즘 설계 기법입니다.  
이 방식은 재귀적 성격을 띠며, 많은 문제(정렬, 곱셈, 신호 처리, 기하 문제 등)를 효율적으로 해결할 수 있게 해줍니다.

---

## 목차 📝
1. [개요](#개요)
2. [정렬 알고리즘](#정렬-알고리즘)
   - [Merge Sort](../sort/merge.c)
   - [Quick Sort](../sort/quick.c)
3. [수치 계산 및 곱셈 알고리즘](#수치-계산-및-곱셈-알고리즘)
   - [Karatsuba Multiplication](karatsuba.md)
   - [Strassen's Matrix Multiplication](strassen.md)
4. [신호 처리 및 FFT](#신호-처리-및-fft)
   - [Fast Fourier Transform (FFT)](fft.md)
5. [Closest Pair 문제](#closest-pair-문제)
   - [Closest Pair of Points](closest_pair.md)
6. [기타 분할 정복 알고리즘](#기타-분할-정복-알고리즘)
   - [Divide and Conquer Optimization](dnc_optimization.md)
   - [Selection Algorithm](select.md)
   - [Maximum Subarray Problem](max_subarray.md)

---

## 개요
분할 정복 알고리즘은 문제를 다음과 같이 세 단계로 처리합니다:

1. **분할(Divide):**  
   - 원래 문제를 여러 개의 하위 문제로 분할합니다.
   - 하위 문제들은 원래 문제와 동일한 형태를 갖지만, 크기는 작습니다.

2. **정복(Conquer):**  
   - 분할된 하위 문제들을 재귀적으로 해결합니다.
   - 하위 문제가 충분히 작으면, 직접 해결(예: 기본 연산)합니다.

3. **결합(Combine):**  
   - 하위 문제들의 해답을 결합하여 원래 문제의 해답을 도출합니다.

이러한 접근 방식은 문제의 구조에 따라 시간 복잡도를 크게 개선할 수 있으며, 
많은 경우 재귀적 호출을 통해 자연스럽게 구현할 수 있습니다.

---

## 정렬 알고리즘
- **Merge Sort:**  
  분할 정복 알고리즘의 대표적인 예로, 배열을 절반으로 분할한 후 각각 정렬하고, 다시 합병(merge)하여 전체 정렬을 수행합니다.  
  [Merge Sort](../sort/merge.c)

- **Quick Sort:**  
  배열에서 피벗을 선택한 후, 피벗을 기준으로 배열을 두 부분으로 분할하고, 각 부분을 재귀적으로 정렬하는 방식입니다.  
  [Quick Sort](../sort/quick.c)

---

## 수치 계산 및 곱셈 알고리즘
- **Karatsuba Multiplication:**  
  큰 수의 곱셈을 분할 정복 방식으로 처리하여 전통적인 O(n²) 곱셈보다 빠른 O(n^log2 3) 시간 복잡도를 달성합니다.  
  [Karatsuba Multiplication](./Multiplication/README.md)

- **Strassen's Matrix Multiplication:**  
  행렬 곱셈을 분할 정복 기법을 사용해 전통적인 O(n³)보다 빠른 성능을 제공하는 알고리즘입니다.  
  [Strassen's Matrix Multiplication](./Multiplication/README.md)

---

## 신호 처리 및 FFT
- **Fast Fourier Transform (FFT):**  
  시간 영역의 신호를 주파수 영역으로 변환하는 알고리즘으로, 분할 정복을 통해 O(n log n)의 효율성을 달성합니다.  
  [Fast Fourier Transform (FFT)](./FFT/README.md)

---

## Closest Pair 문제
- **Closest Pair of Points:**  
  평면 상의 점들 중 두 점 사이의 최단 거리를 찾는 문제를 분할 정복을 사용해 효율적으로 해결하는 알고리즘입니다.  
  [Closest Pair of Points](./ClosestPair/README.md)

---

## 기타 분할 정복 알고리즘
추가적으로 분할 정복 기법은 다음과 같은 문제들에도 응용할 수 있습니다:

- **Divide and Conquer Optimization:**  
  동적 계획법(DP) 문제의 최적화 과정에서 분할 정복을 활용해 계산 복잡도를 줄이는 기법입니다.  
  [Divide and Conquer Optimization](./Optimization/README.md)

- **Selection Algorithm:**  
  예를 들어, QuickSelect 알고리즘은 분할 정복을 사용하여 배열에서 k번째 작은 원소를 효율적으로 찾습니다.  
  [Selection Algorithm](./Selection/README.md)

- **Maximum Subarray Problem:**  
  배열에서 연속된 부분 배열의 합이 최대가 되는 부분을 찾는 문제를 분할 정복으로 해결하는 알고리즘입니다.  
  [Maximum Subarray Problem](./MaximumSubarray/README.md)

---

분할 정복 알고리즘은 문제를 효과적으로 분할하고, 각각의 하위 문제를 독립적으로 해결한 후 결합함으로써,  
복잡한 문제에 대한 효율적인 솔루션을 제공합니다.  
각 링크를 통해 상세한 이론과 구현체 예시를 확인하고, 다양한 실무 문제에 응용해 보세요!