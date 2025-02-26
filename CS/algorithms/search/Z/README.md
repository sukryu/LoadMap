# Z 알고리즘 (Z Algorithm)

## 개요
Z 알고리즘은 문자열 처리에서 매우 유용한 알고리즘으로, 주어진 문자열의 각 위치에 대해 해당 위치에서 시작하는 접두사와 전체 문자열의 접두사와의 최대 일치 길이(Z 값을)를 효율적으로 계산합니다.  
이 정보를 통해 문자열 내에서 특정 패턴을 빠르게 찾거나, 여러 문자열 간의 공통 접두사(longest common prefix)를 구하는 등 다양한 응용 문제를 해결할 수 있습니다.

## 동작 원리
- **Z 배열 정의:**  
  문자열 S의 길이를 n이라 할 때, Z 배열의 각 원소 Z[i]는 S의 i번째 위치에서 시작하는 부분 문자열이 S의 접두사와 일치하는 최대 길이를 나타냅니다. (단, Z[0]은 보통 n으로 정의되거나 0으로 처리됩니다.)

- **알고리즘 동작:**  
  1. **초기화:**  
     - i = 1부터 시작하여 문자열 전체에 대해 Z 값을 계산합니다.
  2. **Z 박스(Z-box) 유지:**  
     - 현재까지 계산된 Z 값들을 활용하여, [L, R] 구간(현재까지 일치하는 최대 구간)을 유지합니다.
     - i가 이 Z 박스 내부에 있으면, 기존 계산 결과를 재사용하고, 필요에 따라 추가 비교를 수행합니다.
     - i가 Z 박스 외부에 있으면, 처음부터 문자를 비교하여 Z[i]를 새롭게 계산합니다.
  3. **효율성:**  
     - 이 과정을 통해 전체 문자열에 대해 O(n) 시간 내에 Z 배열을 완성할 수 있습니다.

## 알고리즘 특징
- **시간 복잡도:**  
  - 전체 문자열에 대해 한 번의 선형 스캔으로 Z 배열을 계산하므로 O(n)의 시간 복잡도를 가집니다.
- **공간 복잡도:**  
  - Z 배열을 저장하기 위해 O(n)의 추가 공간이 필요합니다.
- **장점:**  
  - 구현이 비교적 간단하며, 패턴 검색, 문자열 매칭, 중복 문자열 탐색 등 다양한 문제에 응용할 수 있습니다.
  - KMP와 유사한 선형 시간 알고리즘이지만, 때에 따라 더 직관적으로 구현할 수 있습니다.
- **응용 사례:**  
  - 패턴 검색: 전체 문자열 S와 패턴 P를 "P$S" 형태로 결합한 후 Z 알고리즘을 적용하면, P가 S 내에 등장하는 모든 위치를 효율적으로 찾을 수 있습니다.
  - 문자열 유사도 계산 및 중복 문자열 찾기

## 참고 자료
- [Wikipedia - Z-algorithm](https://en.wikipedia.org/wiki/Z_algorithm)
- [GeeksforGeeks - Z Algorithm](https://www.geeksforgeeks.org/z-algorithm-linear-time-pattern-searching-algorithm/)
- [Baekjoon Online Judge](https://www.acmicpc.net/)