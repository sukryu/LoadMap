# 배열과 문자열 문제 해결 가이드 📊

> 배열과 문자열은 알고리즘 문제 해결의 기초가 되는 핵심 자료구조입니다. 이 가이드에서는 이러한 자료구조를 활용한 다양한 문제 해결 전략과 최적화 방법을 체계적으로 설명합니다.

## 목차
1. [기본 접근 방법](#기본-접근-방법)
2. [주요 문제 해결 기법](#주요-문제-해결-기법)
3. [배열 특성별 문제 해결 전략](#배열-특성별-문제-해결-전략)
4. [문자열 처리 심화](#문자열-처리-심화)
5. [다차원 배열 활용](#다차원-배열-활용)
6. [최적화 전략](#최적화-전략)

## 기본 접근 방법

문제를 효과적으로 해결하기 위해서는 먼저 입력 데이터의 특성을 정확히 파악해야 합니다. 다음의 핵심 질문들을 통해 적절한 접근 방법을 선택할 수 있습니다.

### 입력 데이터 분석
배열이나 문자열 문제를 마주했을 때, 가장 먼저 다음 사항들을 확인해야 합니다:

입력 데이터의 크기와 범위를 파악합니다. 이는 시간 복잡도와 공간 복잡도의 제약을 결정하는 중요한 요소입니다.

데이터의 정렬 상태를 확인합니다. 정렬된 데이터는 이진 탐색과 같은 효율적인 알고리즘을 적용할 수 있습니다.

중복 원소의 존재 여부를 확인합니다. 중복 처리는 문제 해결 방식에 큰 영향을 미칩니다.

메모리 제약 조건을 확인합니다. 추가 공간 사용이 제한적인 경우, 인플레이스(in-place) 알고리즘을 고려해야 합니다.

## 주요 문제 해결 기법

### 투 포인터 기법

배열이나 문자열을 순회할 때 두 개의 포인터를 전략적으로 이동시키는 방법입니다. 다음과 같은 상황에서 특히 효과적입니다:

연속된 구간의 합을 구하는 문제에서는 시작점과 끝점을 관리하며 구간을 확장하거나 축소합니다.

정렬된 배열에서 두 수의 합을 찾는 문제는 양 끝에서 시작하여 중앙으로 이동하는 방식으로 해결합니다.

중복 원소를 제거하거나 특정 조건을 만족하는 부분 배열을 찾는 경우에도 효과적으로 적용할 수 있습니다.
[투 포인터 기법 바로가기](./TwoPointer/README.md)

### 슬라이딩 윈도우

고정 크기 또는 가변 크기의 윈도우를 이동시키며 문제를 해결하는 기법입니다. 다음과 같은 경우에 활용됩니다:

연속된 K개 원소의 최대/최소값을 찾는 문제에서 효율적으로 사용됩니다.

문자열에서 특정 조건을 만족하는 최소 길이의 부분 문자열을 찾는 경우에 적용됩니다.

윈도우 내 원소들의 특성을 유지하면서 효율적으로 업데이트하는 것이 핵심입니다.
[슬라이딩 윈도우 바로가기](./SlidingWindow/README.md)

### 누적 합 기법

구간의 합을 빠르게 계산하기 위한 전처리 방법입니다. 다음과 같은 특징이 있습니다:

한 번의 전처리로 이후의 모든 구간 합 질의를 O(1) 시간에 처리할 수 있습니다.

2차원 배열에서도 적용 가능하며, 직사각형 영역의 합을 효율적으로 계산할 수 있습니다.
[누적합 기법 바로가기](./CumulativeSum/README.md)

## 배열 특성별 문제 해결 전략

### 정렬된 배열에서의 최적화

정렬된 배열에서는 다음과 같은 최적화 기법을 적용할 수 있습니다:

이진 탐색을 활용한 효율적인 검색이 가능합니다.

병합 정렬의 아이디어를 활용하여 두 정렬된 배열의 처리를 최적화할 수 있습니다.

정렬 상태를 유지하면서 삽입/삭제를 수행하는 효율적인 방법을 사용할 수 있습니다.
[정렬된 배열에서의 최적화 바로가기](./SortedArrayOptimization/README.md)

### 중복 원소 처리

중복 원소가 존재하는 경우의 특별한 처리 방법입니다:

해시 테이블을 활용하여 빈도수를 효율적으로 관리합니다.

정렬을 활용하여 중복 원소를 그룹화하고 처리합니다.

투 포인터 기법을 활용하여 중복 제거를 수행합니다.
[중복 원소 처리 바로가기](./DuplicateProcess/README.md)

## 문자열 처리 심화

### 패턴 매칭 알고리즘

문자열 검색을 위한 다양한 알고리즘을 상황에 맞게 선택합니다:

KMP 알고리즘은 긴 문자열에서 패턴을 찾는 데 효율적입니다.

라빈-카프 알고리즘은 여러 패턴을 동시에 검색할 때 유용합니다.

보이어-무어 알고리즘은 실제 텍스트 처리에서 높은 성능을 보입니다.
[패턴 매칭 알고리즘 바로 가기](../../CS/algorithms/search/README.md)

### 특수 문자열 패턴

자주 등장하는 특수한 문자열 패턴들의 처리 방법입니다:

회문(Palindrome) 검사는 투 포인터 방식으로 효율적으로 수행할 수 있습니다.

아나그램 검사는 문자 빈도수 배열이나 해시 테이블을 활용합니다.

접두사/접미사 관련 문제는 트라이(Trie) 자료구조를 고려합니다.
[특수 문자열 패턴 바로가기](./StringPattern/README.md)

## 다차원 배열 활용

### 2차원 배열 처리

2차원 이상의 배열을 다루는 효과적인 방법입니다:

행렬의 효율적인 순회 방법을 이해하고 적용합니다.

대각선 방향의 처리를 위한 인덱스 계산 기법을 활용합니다.

경계 조건 처리를 위한 패딩(padding) 기법을 적용합니다.
[2차원 배열 처리 바로가기](./2DArrayProcess/README.md)

### 다차원 누적합

2차원 이상의 배열에서 구간 합을 계산하는 방법입니다:

2D 누적합 배열을 구축하여 직사각형 영역의 합을 O(1)에 계산합니다.

업데이트가 빈번한 경우 펜윅 트리(Fenwick Tree)를 고려합니다.
[다차원 누적합 바로가기](./MultidimensionalPrefixSum/README.md)

## 최적화 전략

### 공간 복잡도 최적화

메모리 사용을 최소화하기 위한 전략입니다:

입력 배열을 직접 수정하여 추가 공간 사용을 줄입니다.

비트 연산을 활용하여 공간 효율적인 상태 표현을 구현합니다.

불필요한 임시 배열을 제거하고 변수로 대체합니다.
[공간 복잡도 최적화 바로가기](./SpaceComplexityOptimization/README.md)

### 시간 복잡도 최적화

실행 시간을 개선하기 위한 전략입니다:

해시 테이블을 활용하여 검색 시간을 O(1)로 단축합니다.

정렬을 통해 문제를 단순화하고 효율적인 알고리즘을 적용합니다.

전처리를 통해 반복적인 계산을 제거합니다.
[시간 복잡도 최적화 바로가기](./TimeComplexityOptimization/README.md)

---

이러한 다양한 기법들을 상황에 맞게 조합하여 사용하면, 대부분의 배열과 문자열 관련 문제를 효율적으로 해결할 수 있습니다. 각 기법의 장단점을 이해하고, 문제의 특성에 따라 적절한 방법을 선택하는 것이 중요합니다.