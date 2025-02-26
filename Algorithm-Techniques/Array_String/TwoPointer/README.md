# 투 포인터 기법 이론 정리

투 포인터(two pointers) 기법은 배열이나 문자열과 같은 선형 자료구조에서 두 개의 인덱스를 이용하여 문제를 효율적으로 해결하는 알고리즘 기법입니다. 이 문서에서는 투 포인터 기법의 기본 원리, 다양한 응용 방법, 주의사항, 그리고 어떤 문제 유형에 효과적인지 자세하게 설명합니다.

---

## 1. 투 포인터 기법이란?

- **기본 아이디어:**  
  투 포인터 기법은 두 개의 포인터(인덱스)를 사용하여 배열 또는 문자열의 시작과 끝 또는 두 개의 위치에서 동시에 탐색하는 방식입니다. 이를 통해 이중 반복문을 단일 반복문이나 선형 시간 복잡도로 대체할 수 있습니다.

- **주요 활용 분야:**  
  - **슬라이딩 윈도우:** 연속된 구간의 합, 길이, 조건 만족 여부를 판별할 때 사용
  - **두 배열의 병합:** 정렬된 배열 두 개를 병합하는 문제
  - **특정 조건을 만족하는 부분 배열/부분 문자열 탐색:** 예를 들어, 특정 합을 만족하는 연속 구간 찾기 등

---

## 2. 투 포인터 기법의 기본 원리

- **포인터 설정:**  
  일반적으로 `left`와 `right` 두 개의 포인터를 배열의 시작점이나 끝점에 위치시킵니다.
  
- **포인터 이동:**  
  조건에 따라 한쪽 혹은 양쪽 포인터를 이동시킵니다. 예를 들어,  
  - **슬라이딩 윈도우:** 구간의 합이 조건을 만족하지 않으면 `right` 포인터를 증가시키고, 조건을 초과하면 `left` 포인터를 증가시킵니다.
  - **두 배열 병합:** 각 배열의 포인터를 비교하여 더 작은 값을 결과 배열에 삽입하고 해당 포인터를 이동합니다.

- **종료 조건:**  
  포인터가 배열의 끝에 도달하거나, 원하는 조건을 만족하면 탐색을 종료합니다.

---

## 3. 투 포인터 기법의 응용

### 3.1 슬라이딩 윈도우 (Sliding Window)
- **문제 예시:**  
  - 길이가 `K`인 부분 배열의 최대/최소 합 찾기
  - 두 포인터를 사용하여 조건(예: 합, 길이 등)을 만족하는 가장 긴 또는 짧은 연속 구간 찾기

- **핵심 포인트:**  
  구간에 포함되는 원소의 추가/제거 시 빠르게 조건을 업데이트할 수 있도록 상태를 관리하는 것이 중요합니다.

### 3.2 두 배열/리스트 병합
- **문제 예시:**  
  - 정렬된 두 배열을 병합하여 하나의 정렬된 배열 만들기
  - 두 배열에서 공통 요소 찾기

- **핵심 포인트:**  
  두 배열 각각의 포인터를 사용하여, 두 값 중 더 작은 값을 결과에 추가하며 포인터를 한 칸씩 이동시킵니다.

### 3.3 특정 조건의 부분 배열/문자열 찾기
- **문제 예시:**  
  - 특정 합을 가지는 연속된 부분 배열 찾기
  - 주어진 문자열에서 특정 패턴을 만족하는 부분 문자열 찾기

- **핵심 포인트:**  
  조건에 따라 포인터의 이동 방향과 업데이트 방식을 결정하고, 조건 충족 여부를 효율적으로 검사해야 합니다.

---

## 4. 투 포인터 기법 사용 시 주의사항

- **인덱스 범위 관리:**  
  포인터가 배열 범위를 벗어나지 않도록 항상 조건문으로 체크합니다.

- **포인터 이동 조건:**  
  무한 루프에 빠지지 않도록 포인터가 적절하게 이동되고 있는지 확인해야 합니다. 특히, 어떤 조건에서 두 포인터가 같은 값을 가리키거나 교차할 때 종료 조건을 명확히 해야 합니다.

- **초기값 설정:**  
  문제에 따라 포인터의 초기 위치가 달라질 수 있으므로, 문제의 특성을 고려하여 적절한 시작 위치를 정해야 합니다.

- **상태 업데이트:**  
  슬라이딩 윈도우와 같이 상태(예: 현재 구간의 합, 길이 등)를 유지하는 문제에서는 포인터 이동 시 상태를 정확하게 업데이트하는 것이 중요합니다.

- **경계 조건:**  
  배열의 첫 번째 원소와 마지막 원소를 처리할 때, 경계 조건을 꼼꼼히 체크하여 에러를 방지합니다.

---

## 5. 어떤 문제 유형에 사용하면 좋을까?

- **연속된 구간의 합/평균 문제:**  
  예를 들어, 주어진 배열에서 합이 특정 값 이상인 가장 짧은 부분 배열 찾기

- **정렬된 배열에서의 특정 쌍 찾기:**  
  두 수의 합이 특정 값에 가까운 경우 찾기, 또는 두 배열에서 공통 요소 찾기

- **문자열 처리 문제:**  
  연속된 부분 문자열에서 특정 조건(예: 중복 없는 최대 길이) 찾기

- **최적 구간 문제:**  
  예를 들어, 구간 내에서 최대/최소값을 찾거나 특정 조건을 만족하는 가장 긴/짧은 구간을 찾는 문제

---

## 6. 결론

투 포인터 기법은 문제의 조건을 잘 파악하고 포인터의 이동 및 상태 관리를 올바르게 수행하면 시간 복잡도를 크게 줄일 수 있는 강력한 도구입니다.  
초보자라면 먼저 단순한 슬라이딩 윈도우 문제부터 시작하여 점차 복잡한 문제로 나아가는 것이 좋으며, 각 문제에서 포인터 이동 로직과 종료 조건을 명확히 이해하는 것이 중요합니다.

투 포인터 기법을 충분히 익히면 다양한 문제 상황에서 효율적인 해결책을 설계할 수 있으므로, 다양한 문제를 풀어보며 경험을 쌓아보시길 권장합니다.
