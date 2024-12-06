# 정렬 알고리즘.

## 선택 정렬 (Selection Sort)

* 선택 정렬의 개념:
    * 선택 정렬은 해당 위치에 들어갈 값을 선택하여 위치를 교환하는 정렬 알고리즘입니다.
    * 배열에서 가장 작은 값을 찾아 첫 번째 위치와 교환하고, 그 다음으로 작은 값을 찾아 두 번째 위치와 교환하는 과정을 반복합니다.
    * 시간 복잡도는 O(n^2)으로, 비효율적인 정렬 알고리즘 중 하나입니다.

* 동작 과정
    1. 주어진 리스트에서 최솟값을 찾습니다.
    2. 최솟값을 제외한 맨 앞 자리의 값과 교환합니다.
    3. 맨 앞 자리를 제외한 나머지 리스트에서 같은 과정을 반복합니다.
    4. 하나의 원소만 남을 때까지 위 과정을 반복합니다.

    <img src="https://chamdom.blog/435c4529666d4f2c42f744be55e03222/selection-sort.gif">

* 구현:
    ```python
    def selection_sort(arr):
        n = len(arr)
        for i in range(n):
            min_idx = i

            for j in range(i + 1, n):
                if arr[j] < arr[min_idx]:
                    min_idx = j

            arr[i], arr[min_idx] = arr[min_idx], arr[i]

        return arr
    ```

* 시간 복잡도
    * 최선의 경우: O(n^2)
    * 평균의 경우: O(n^2)
    * 최악의 경우: O(n^2)
    * 모든 경우에 대해 동일한 시간 복잡도를 가집니다.

* 공간 복잡도
    * O(1): 주어진 배열 안에서 교환(swap)을 통해 정렬이 수행되므로 추가 메모리가 거의 필요하지 않습니다.

* 장단점
    * 장점
        - 구현이 매우 간단합니다.
        - 정렬을 위한 추가 메모리가 필요하지 않습니다.
        - 교환 횟수가 버블 정렬보다 적어 비교적 효율적입니다.

    * 단점
        - 시간 복잡도가 O(n^2)으로 비효율적입니다.
        - 데이터 양이 많을수록 성능이 급격하게 저하됩니다.
        - 안정 정렬(Stable Sort)이 아닙니다.

* 사용 사례:
    - 작은 규모의 데이터 정렬
    - 메모리 사용이 제한적인 환경
    - 교육용 또는 기초 학습용 알고리즘

* 예제:
    ```python
    # 실제 사용 예시
    numbers = [64, 34, 25, 12, 22, 11, 90]
    sorted_numbers = selection_sort(numbers)
    print(sorted_numbers)  # [11, 12, 22, 25, 34, 64, 90]

    # 단계별 과정을 보여주는 함수
    def selection_sort_with_steps(arr):
        n = len(arr)
        for i in range(n):
            min_idx = i
            for j in range(i + 1, n):
                if arr[j] < arr[min_idx]:
                    min_idx = j
            arr[i], arr[min_idx] = arr[min_idx], arr[i]
            print(f"Step {i + 1}: {arr}")
        return arr

    # 단계별 과정 출력
    numbers = [64, 34, 25, 12, 22, 11, 90]
    selection_sort_with_steps(numbers)
    ```

    - 이렇게 선택 정렬은 간단하지만 비효율적인 정렬 알고리즘입니다. 실제 프로덕션 환경에서는 더 효율적인 정렬 알고리즘 (퀵 정렬, 병합 정렬)을 사용하는 것이 좋습니다.

## 삽입 정렬 (Insertion Sort)

* 삽입 정렬의 개념:
    * 삽입 정렬은 마치 카드 게임에서 카드를 한 장씩 꺼내 적절한 위치에 삽입하는 것처럼 동작하는 정렬 알고리즘입니다.
    * 정렬되지 않은 데이터를 이미 정렬된 부분과 비교하여 적절한 위치에 삽입하는 방식입니다.
    * 배열의 두 번째 요소부터 시작하여, 그 앞의 요소들과 비교하면서 알맞은 위치에 삽입합니다.

* 동작 과정
    1. 두 번째 요소부터 시작합니다.
    2. 현재 요소를 이전의 정렬된 부분과 비교합니다.
    3. 적절한 위치를 찾을 때까지 요소들을 뒤로 이동시킵니다.
    4. 찾은 위치에 현재 요소를 삽입합니다.
    5. 배열의 마지막 요소까지 위 과정을 반복합니다.

    <img src="https://velog.velcdn.com/images/wisdom-one/post/af7786a7-9dad-4a25-aff8-214f3c911a0f/image.gif">

* 구현:
    ```python
    def insertion_sort(arr):
    n = len(arr)
    
    # 두 번째 요소부터 시작
    for i in range(1, n):
        # 현재 삽입할 요소
        key = arr[i]
        # 이전 요소의 인덱스
        j = i - 1
        
        # key보다 큰 요소들을 뒤로 이동
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        
        # 적절한 위치에 key 삽입
        arr[j + 1] = key
    
    return arr
    ```

* 시간 복잡도:
    * 최선의 경우: O(n)
        - 이미 정렬된 배열의 경우
        - 각 요소당 한 번의 비교만 필요

    * 평균의 경우: O(n^2)
    * 최악의 경우: O(n^2)
        - 역순으로 정렬된 배열의 경우
        - 매 단계마다 모든 이전 요소들과 비교 필요

* 공간 복잡도
    - O(1): 주어진 배열 내에서 정렬이 수행되므로 추가 메모리가 거의 필요하지 않습니다.

* 장단점
    * 장점
        - 구현이 간단합니다.
        - 작은 데이터셋에서 효율적입니다.
        - 안정 정렬(Stable Sort)입니다.
        - 대부분 정렬된 배열에서 매우 효율적입니다.
        - 다른 O(n^2)알고리즘보다 일반적으로 더 빠릅니다.
        - 제자리 정렬(In-place-sorting)입니다.

    * 단점
        - 큰 데이터셋에서는 비효율적입니다.
        - 평균과 최악의 경우 시간 복잡도가 O(n^2)입니다.
        - 배열의 크기가 커질수록 성능이 급격히 저하됩니다.

* 사용사례
    - 거의 정렬된 배열의 정렬
    - 작은 크기의 데이터 정렬
    - 온라인 알고리즘이 필요한 경우
        - 데이터가 실시간으로 들어오는 상황
    - 다른 정렬 알고리즘의 부분 루틴으로 사용

* 예제:
    ```python
    # 실제 사용 예시
    numbers = [64, 34, 25, 12, 22, 11, 90]
    sorted_numbers = insertion_sort(numbers)
    print(sorted_numbers)  # [11, 12, 22, 25, 34, 64, 90]

    # 단계별 과정을 보여주는 함수
    def insertion_sort_with_steps(arr):
        n = len(arr)
        print(f"Initial array: {arr}")
        
        for i in range(1, n):
            key = arr[i]
            j = i - 1
            while j >= 0 and arr[j] > key:
                arr[j + 1] = arr[j]
                j -= 1
            arr[j + 1] = key
            print(f"Step {i}: {arr}")
        
        return arr

    # 단계별 과정 출력
    numbers = [64, 34, 25, 12, 22, 11, 90]
    insertion_sort_with_steps(numbers)
    ```

* 최적화 기법
    - 이진 탐색을 활용한 삽입 위치 탐색
        ```python
        def binary_insertion_sort(arr):
            for i in range(1, len(arr)):
                key = arr[i]
                # 이진 탐색으로 삽입 위치 찾기
                left, right = 0, i
                while left < right:
                    mid = (left + right) // 2
                    if arr[mid] > key:
                        right = mid
                    else:
                        left = mid + 1
                        
                # 요소들을 뒤로 이동
                for j in range(i, left, -1):
                    arr[j] = arr[j-1]
                arr[left] = key
            
            return arr
        ```

* 응용
    - 연결 리스트에서의 구현
        ```python
        class Node:
            def __init__(self, data):
                self.data = data
                self.next = None

        class LinkedList:
            def __init__(self):
                self.head = None
            
            def insertion_sort(self):
                if not self.head or not self.head.next:
                    return
                
                sorted_head = None
                current = self.head
                
                while current:
                    next_node = current.next
                    sorted_head = self.sorted_insert(sorted_head, current)
                    current = next_node
                
                self.head = sorted_head

            def sorted_insert(self, sorted_head, new_node):
                if not sorted_head or sorted_head.data >= new_node.data:
                    new_node.next = sorted_head
                    return new_node
                
                current = sorted_head
                while current.next and current.next.data < new_node.data:
                    current = current.next
                    
                new_node.next = current.next
                current.next = new_node
                return sorted_head
        ```

    - 삽입 정렬은 선택 정렬이나 버블 정렬과 같은 O(n^2)알고리즘 중에서 실제로 가장 효율적인 알고리즘으로 평가받고 있으며,
    특히 거의 정렬된 데이터나 작은 데이터셋에서는 퀵 정렬이나 병합 정렬과 같은 고급 정렬 알고리즘보다 더 나은 성능을 보일 수 있습니다.

## 버블 정렬 (Bubble Sort)

* 버블 정렬의 개념:
    * 버블 정렬은 인접한 두 개의 데이터를 비교해가며 정렬하는 방법입니다.
    * 마치 거품이 수면으로 올라오는 것처럼 큰 값들이 배열의 뒤쪽으로 이동하는 모습과 비슷하여 버블 정렬이라고 합니다.
    * 가장 구현하기 쉽지만, 가장 비효율적인 정렬 알고리즘 중 하나입니다.

* 동작 과정
    1. 첫 번째 요소와 두 번째 요소를 비교하여 교환이 필요하면 교환합니다.
    2. 두 번째 요소와 세 번째 요소를 비교하여 교환이 필요하면 교환합니다.
    3. 이런 식으로 끝까지 진행하면 가장 큰 요소가 마지막 위치로 이동합니다.
    4. 위 과정을 배열이 정렬될 때까지 반복합니다.

    <img src="https://blog.kakaocdn.net/dn/PyBkA/btq4yhkVqzx/Fu355VVVDyq5PJ4zVqUnBK/img.gif">

* 구현
    ```python
    def bubble_sort(arr):
        n = len(arr)
        
        # 전체 패스 수행
        for i in range(n):
            # 각 패스에서의 비교
            for j in range(0, n - i - 1):
                # 인접한 요소 비교 및 교환
                if arr[j] > arr[j + 1]:
                    arr[j], arr[j + 1] = arr[j + 1], arr[j]
        
        return arr
    ```

* 최적화된 구현
    ```python
    def optimized_bubble_sort(arr):
        n = len(arr)
        
        for i in range(n):
            # 교환이 발생했는지 추적
            swapped = False
            
            for j in range(0, n - i - 1):
                if arr[j] > arr[j + 1]:
                    arr[j], arr[j + 1] = arr[j + 1], arr[j]
                    swapped = True
            
            # 교환이 없었다면 이미 정렬된 상태
            if not swapped:
                break
        
        return arr
    ```

* 시간 복잡도
    * 최선의 경우: O(n)
        - 이미 정렬된 배열의 경우 (최적화된 버전)
        - `swapped`가 `False`로 남아 루프가 조기 종료됨.

    * 평균의 경우: O(n^2)
    * 최악의 경우: O(n^2)
        - 역순으로 정렬된 배열의 경우

* 공간 복잡도
    - O(1): 추가적인 메모리 공간을 거의 필요로 하지 않습니다.

* 장단점
    * 장점
        - 구현이 매우 간단합니다.
        - 안정 정렬(Stable Sort)입니다.
        - 추가 메모리가 필요하지 않습니다.
        - 정렬 과정을 시각적으로 이해하기 쉽습니다.

    * 단점
        - 시간 복잡도가 O(n^2)으로 매우 비효율적입니다.
        - 데이터의 교환 작업(swap)이 많이 발생합니다.
        - 배열의 크기가 커질수록 성능이 급격하게 저하됩니다.

* 사용 사례
    - 교육용 목적
    - 매우 작은 데이터셋
    - 거의 정렬된 데이터의 경우 (최적화 버전)
    - 메모리 제약이 심한 환경

* 예제
    ```python
    # 단계별 과정을 보여주는 함수
    def bubble_sort_with_steps(arr):
        n = len(arr)
        print(f"Initial array: {arr}")
        
        for i in range(n):
            swapped = False
            
            for j in range(0, n - i - 1):
                if arr[j] > arr[j + 1]:
                    arr[j], arr[j + 1] = arr[j + 1], arr[j]
                    swapped = True
            
            print(f"Pass {i + 1}: {arr}")
            
            if not swapped:
                print("Array is already sorted!")
                break
        
        return arr

    # 예제 실행
    numbers = [64, 34, 25, 12, 22, 11, 90]
    bubble_sort_with_steps(numbers)
    ```

* 변형 및 응용
    1. 양방향 버블 정렬 (칵테일 정렬)
        ```python
        def cocktail_sort(arr):
            n = len(arr)
            swapped = True
            start = 0
            end = n - 1
            
            while swapped:
                # 왼쪽에서 오른쪽으로
                swapped = False
                for i in range(start, end):
                    if arr[i] > arr[i + 1]:
                        arr[i], arr[i + 1] = arr[i + 1], arr[i]
                        swapped = True
                
                if not swapped:
                    break
                
                end -= 1
                swapped = False
                
                # 오른쪽에서 왼쪽으로
                for i in range(end - 1, start - 1, -1):
                    if arr[i] > arr[i + 1]:
                        arr[i], arr[i + 1] = arr[i + 1], arr[i]
                        swapped = True
                
                start += 1
            
            return arr
        ```
        - 칵테일 정렬은 양방향으로 교환을 진행하므로, 데이터의 분포가 일정하지 않을 때 유용함.

    - 버블 정렬은 가장 단순한 정렬 알고리즘이지만 효율성이 매우 낮아 실제 프로덕션 환경에서는 거의 사용되지 않습니다.
    하지만 알고리즘의 기본 개념을 이해하고 최적화 방법을 학습하는 데 좋은 예시가 됩니다. 실제 상황에서는 퀵 정렬, 병합 정렬, 또는 각
    프로그래밍 언어에서 제공하는 내장 정렬 함수를 사용하는 것이 바람직합니다.

## 셸 정렬 (Shell Sort)

* 셸 정렬의 개념
    * 셸 정렬은 삽입 정렬을 보완한 알고리즘으로, Donald Shell이 1959년에 제안했습니다.
    * 삽입 정렬의 단점을 보완하기 위해 일정한 간격(gap)으로 떨어진 요소들끼리 부분 집합을 만들어 정렬합니다.
    * 간격을 점차 줄여가며 정렬하고, 최종적으로 간격이 1이 되면 일반 삽입 정렬을 수행합니다.

* 동작 과정
    1. 정렬할 배열의 요소들을 일정한 간격(gap)으로 나눕니다.
    2. 나눠진 각 부분 집합별로 삽입 정렬을 수행합니다.
    3. 간격을 줄여가며 위 과정을 반복합니다.
    4. 간격이 1이 되면 마지막으로 전체 삽입 정렬을 수행합니다.

    <img src="https://blog.kakaocdn.net/dn/cilqCs/btsGCWBThd2/Ps9wJGLbEDorcqWYHpCqFk/img.png">

* 구현
    ```python
    def shell_sort(arr):
        n = len(arr)
        gap = n // 2  # 초기 간격
        
        # 간격을 줄여가며 반복
        while gap > 0:
            # gap 간격만큼 떨어진 요소들에 대해 삽입 정렬 수행
            for i in range(gap, n):
                temp = arr[i]
                j = i
                
                # gap 간격의 요소들을 비교하여 정렬
                while j >= gap and arr[j - gap] > temp:
                    arr[j] = arr[j - gap]
                    j -= gap
                
                arr[j] = temp
            
            # 간격을 절반으로 줄임
            gap //= 2
        
        return arr
    ```

* 시간 복잡도
    * 최선의 경우: O(n*log n)
    * 평균의 경우: 간격 수열에 따라 다름
        - 일반적으로 O(n^1.3 ~ n^1.5)사이
    * 최악의 경우: O(n^2)

* 공간 복잡도
    - O(1): 추가적인 메모리 공간을 거의 필요로 하지 않습니다.

* 장단점
    * 장점
        - 삽입 정렬보다 더 빠릅니다.
        - 멀리 떨어진 요소들의 교환이 가능합니다.
        - 정렬의 범위가 전체 데이터로 확장되어 있습니다.
        - 추가 메모리가 필요하지 않습니다.

    * 단점
        - 알고리즘이 복잡합니다.
        - 간격 수열의 선택에 따라 성능 차이가 큽니다.
        - 안정 정렬이 아닙니다.

* 최적화된 구현
    ```python
    def optimized_shell_sort(arr):
        n = len(arr)
        # Marcin Ciura's gap sequence
        gaps = [701, 301, 132, 57, 23, 10, 4, 1]
        
        for gap in gaps:
            if gap > n:
                continue
                
            for i in range(gap, n):
                temp = arr[i]
                j = i
                
                while j >= gap and arr[j - gap] > temp:
                    arr[j] = arr[j - gap]
                    j -= gap
                
                arr[j] = temp
        
        return arr
    ```

* 예제:
    ```python
    def shell_sort_with_steps(arr):
        n = len(arr)
        gap = n // 2
        
        print(f"Initial array: {arr}")
        step = 1
        
        while gap > 0:
            print(f"\nStep {step} (gap={gap}):")
            for i in range(gap, n):
                temp = arr[i]
                j = i
                
                while j >= gap and arr[j - gap] > temp:
                    arr[j] = arr[j - gap]
                    j -= gap
                
                arr[j] = temp
                print(f"Current array: {arr}")
            
            gap //= 2
            step += 1
        
        return arr

    # 예제 실행
    numbers = [64, 34, 25, 12, 22, 11, 90]
    shell_sort_with_steps(numbers)
    ```

* 간격 수열의 종류
    ```python
    def get_gap_sequence(n):
    # Shell's original sequence
    def shell_sequence():
        gap = n // 2
        while gap > 0:
            yield gap
            gap //= 2
    
    # Knuth's sequence
    # Knuth`s의 수열은 데이터 크기가 클 때 더 나은 성능을 제공합니다.
    def knuth_sequence():
        gap = 1
        while gap < n/3:
            gap = gap * 3 + 1
        while gap > 0:
            yield gap
            gap //= 3
    
    # Hibbard's sequence
    # Hibbard의 수열은 비교적 단순하지만, 간격이 적어지는 속도가 빠릅니다.
    def hibbard_sequence():
        k = 1
        while (2**k - 1) < n:
            k += 1
        while k > 0:
            yield 2**k - 1
            k -= 1
            
    # Sedgewick's sequence
    def sedgewick_sequence():
        gaps = []
        k = 0
        gap = 0
        while gap < n:
            if k % 2 == 0:
                gap = 9 * (2**k - 2**k//2) + 1
            else:
                gap = 8 * 2**k - 6 * 2**(k+1)//2 + 1
            if gap < n:
                gaps.append(gap)
            k += 1
        for gap in sorted(gaps, reverse=True):
            yield gap
    ```

    - 셸 정렬은 중간 크기의 데이터셋에서 효율적으로 동작할 수 있는 정렬 알고리즘입니다.
    특히 거의 정렬된 데이터셋에서는 매우 효율적으로 동작하며, 삽입 정렬의 성능을 크게 개선한 알고리즘입니다.
    하지만 퀵 정렬이나 병합 정렬과 같은 더 효율적인 알고리즘들이 있어 실제 환경에서는 이들을 더 많이 사용합니다.

* 각 기초 정렬들의 장단점 비교표

| 알고리즘  | 시간 복잡도 (최선/평균/최악) | 공간 복잡도 | 안정성 | 주요 특징             |
|-----------|------------------------------|-------------|---------|-----------------------|
| 선택 정렬 | O(n^2) / O(n^2) / O(n^2)    | O(1)        | 비안정  | 교환 횟수 적음         |
| 삽입 정렬 | O(n) / O(n^2) / O(n^2)      | O(1)        | 안정    | 거의 정렬된 데이터 적합|
| 버블 정렬 | O(n) / O(n^2) / O(n^2)      | O(1)        | 안정    | 가장 단순한 정렬 알고리즘|
| 셸 정렬   | O(n log n) ~ O(n^2)         | O(1)        | 비안정  | 삽입 정렬의 개선판     |

* 기초 정렬 알고리즘의 사용 사례

| 알고리즘  | 사용 사례                                      |
|-----------|-----------------------------------------------|
| 선택 정렬 | 메모리 제약이 큰 시스템, 작은 데이터셋 정렬     |
| 삽입 정렬 | 거의 정렬된 데이터, 실시간 데이터 처리         |
| 버블 정렬 | 교육용 목적, 작은 데이터셋 정렬               |
| 셸 정렬   | 중간 크기의 데이터셋, 제한된 메모리 환경       |

## 병합 정렬 (Merge Sort)

* 병합 정렬의 개념
    * 분할 정복 방식을 사용하는 정렬 알고리즘입니다.
    * 리스트를 절반으로 나누고, 각각을 재귀적으로 정렬한 후 병합합니다.
    * 안정 정렬(Stable Sort)이며, 데이터의 분포에 관계없이 일정한 성능을 보장합니다.

* 동작 과정
    1. 리스트를 절반으로 분할합니다.
    2. 각 부분을 재귀적으로 정렬합니다.
    3. 정렬된 두 부분을 하나로 병합합니다.

* 기본 구현
    ```python
    def merge_sort(arr):
        if len(arr) <= 1:
            return arr
        
        # 분할
        mid = len(arr) // 2
        left = merge_sort(arr[:mid])
        right = merge_sort(arr[mid:])
        
        # 병합
        return merge(left, right)

    def merge(left, right):
        result = []
        i = j = 0
        
        while i < len(left) and j < len(right):
            if left[i] <= right[j]:
                result.append(left[i])
                i += 1
            else:
                result.append(right[j])
                j += 1
        
        result.extend(left[i:])
        result.extend(right[j:])
        return result
    ```

* 최적화된 구현
    ```python
    def optimized_merge_sort(arr):
    # 보조 배열을 미리 생성하여 메모리 할당 최소화
    temp = [0] * len(arr)
    
    def sort(start, end):
        if start >= end:
            return
            
        mid = (start + end) // 2
        sort(start, mid)
        sort(mid + 1, end)
        merge(start, mid, end)
    
    def merge(start, mid, end):
        # 임시 배열에 복사
        for i in range(start, end + 1):
            temp[i] = arr[i]
        
        part1 = start
        part2 = mid + 1
        index = start
        
        while part1 <= mid and part2 <= end:
            if temp[part1] <= temp[part2]:
                arr[index] = temp[part1]
                part1 += 1
            else:
                arr[index] = temp[part2]
                part2 += 1
            index += 1
        
        # 남은 요소 처리
        while part1 <= mid:
            arr[index] = temp[part1]
            part1 += 1
            index += 1
    
    sort(0, len(arr) - 1)
    return arr
    ```

* 시간 복잡도
    - 최선: O(n log n)
    - 평균: O(n log n)
    - 최악: O(n log n)

* 공간 복잡도
    - O(n): 병합 과정에서 임시 배열 필요

* 장단점
    * 장점
        - 안정 정렬
        - 일관된 성능 (O(n log n))
        - 연결 리스트 정렬에 적합
        - 대용량 데이터 처리에 효과적

    * 단점
        - 추가적인 메모리 공간 필요
        - 작은 데이터셋에서는 퀵 정렬보다 느림
        - 재귀 호출로 인한 오버헤드

* 응용 예제
    ```python
    def merge_sort_linked_list(head):
        if not head or not head.next:
            return head
        
        # 중간 지점 찾기
        slow = fast = head
        prev = None
        while fast and fast.next:
            fast = fast.next.next
            prev = slow
            slow = slow.next
        
        prev.next = None
        
        # 재귀적으로 정렬
        left = merge_sort_linked_list(head)
        right = merge_sort_linked_list(slow)
        
        # 병합
        return merge_lists(left, right)

    def merge_lists(l1, l2):
        dummy = ListNode(0)
        current = dummy
        
        while l1 and l2:
            if l1.val <= l2.val:
                current.next = l1
                l1 = l1.next
            else:
                current.next = l2
                l2 = l2.next
            current = current.next
        
        current.next = l1 or l2
        return dummy.next
    ```

- 병합 정렬은 안정적이고 예측 가능한 성능을 제공하는 중요한 정렬 알고리즘입니다. 특히 연결 리스트나 대용량 데이터 처리에 적합하며,
병렬 처리가 가능한 장점이 있습니다. 실제로 Java의 Arrays.sort()는 기본 타입(primitive type)의 경우 QuickSort를, 객체의 경우 안정성을 위해
MergeSort를 사용합니다.

## 퀵 정렬 (Quick Sort)

* 퀵 정렬의 개념
    * 분할 정복 방식을 사용하는 정렬 알고리즘입니다.
    * 피벗(pivot)을 선택하여 피벗보다 작은 값과 큰 값으로 분할하고 재귀적으로 정렬합니다.
    * 평균적으로 매우 빠른 성능을 보이는 알고리즘입니다.

* 동작 과정
    1. 피벗을 선택합니다.
    2. 피벗보다 작은 요소는 왼쪽으로, 큰 요소는 오른쪽으로 분할합니다.
    3. 분할된 두 부분에 대해 재귀적으로 정렬을 수행합니다.

* 기본 구현
    ```python
    def quick_sort(arr):
        if len(arr) <= 1:
            return arr
        
        pivot = arr[len(arr) // 2]
        left = [x for x in arr if x < pivot]
        middle = [x for x in arr if x == pivot]
        right = [x for x in arr if x > pivot]
        
        return quick_sort(left) + middle + quick_sort(right)
    ```

* 최적화된 구현 (In-place 퀵 정렬)
    ```python
    def optimized_quick_sort(arr, low, high):
        def partition(low, high):
            pivot = arr[high]
            i = low - 1
            
            for j in range(low, high):
                if arr[j] <= pivot:
                    i += 1
                    arr[i], arr[j] = arr[j], arr[i]
                    
            arr[i + 1], arr[high] = arr[high], arr[i + 1]
            return i + 1

        if low < high:
            pivot_index = partition(low, high)
            optimized_quick_sort(arr, low, pivot_index - 1)
            optimized_quick_sort(arr, pivot_index + 1, high)

        return arr

    # 호출
    def quick_sort_wrapper(arr):
        return optimized_quick_sort(arr, 0, len(arr) - 1)
    ```

* 향상된 피벗 선택
    ```python
    def median_of_three(arr, low, high):
        mid = (low + high) // 2
        
        # 세 값을 정렬하여 중간값을 피벗으로 선택
        if arr[low] > arr[mid]:
            arr[low], arr[mid] = arr[mid], arr[low]
        if arr[low] > arr[high]:
            arr[low], arr[high] = arr[high], arr[low]
        if arr[mid] > arr[high]:
            arr[mid], arr[high] = arr[high], arr[mid]
            
        return mid
    ```

* 시간 복잡도
    * 최선: O(n log n)
    * 평균: O(n log n)
    * 최악: O(n^2) - 이미 정렬된 배열, 피벗이 최소/최대값일 때

* 공간 복잡도
    * 기본 구현: O(n)
    * In-place 구현: O(log n) - 재귀 호출 스택

* 장단점
    * 장점
        - 평균적으로 매우 빠른 성능
        - 추가 메모리 사용이 적음 (In-place 구현)
        - 캐시 효율성이 좋음

    * 단점
        - 불안한 정렬
        - 최악의 경우 O(n^2)
        - 이미 정렬된 데이터에 취약

* 실제 구현 예제 (다양한 최적화 포함)
    ```python
    def enhanced_quick_sort(arr):
        def insertion_sort(arr, low, high):
            for i in range(low + 1, high + 1):
                key = arr[i]
                j = i - 1
                while j >= low and arr[j] > key:
                    arr[j + 1] = arr[j]
                    j -= 1
                arr[j + 1] = key

        def partition(low, high):
            # 3-중간값 피벗 선택
            mid = (low + high) // 2
            pivot_index = median_of_three(arr, low, mid, high)
            arr[pivot_index], arr[high] = arr[high], arr[pivot_index]
            
            pivot = arr[high]
            i = low - 1
            
            for j in range(low, high):
                if arr[j] <= pivot:
                    i += 1
                    arr[i], arr[j] = arr[j], arr[i]
            
            arr[i + 1], arr[high] = arr[high], arr[i + 1]
            return i + 1

        def quick_sort_internal(low, high):
            while low < high:
                # 작은 부분 배열은 삽입 정렬 사용
                if high - low + 1 < 10:
                    insertion_sort(arr, low, high)
                    break
                
                pivot_index = partition(low, high)
                
                # 작은 부분을 먼저 정렬 (tail recursion 최적화)
                if pivot_index - low < high - pivot_index:
                    quick_sort_internal(low, pivot_index - 1)
                    low = pivot_index + 1
                else:
                    quick_sort_internal(pivot_index + 1, high)
                    high = pivot_index - 1

        quick_sort_internal(0, len(arr) - 1)
        return arr
    ```

- 퀵 정렬은 평균적으로 가장 빠른 정렬 알고리즘 중 하나이며, 실제로 많은 프로그래밍 언어의 표준 라이브러리에서 사용됩니다.
하지만 최악의 경우 성능이 크게 저하될 수 있으며, 실제 구현에서는 다양한 최적화 기법을 함께 사용하는 것이 좋습니다.


# 탐색 알고리즘

## 선형 탐색 (Linear Search)

* 선형 탐색의 개념:
    * 선형 탐색은 배열이나 리스트에서 원하는 값을 찾기 위해서 처음부터 끝까지 순차적으로 확인하는 가장 기본적인 탐색 알고리즘입니다.
    * 정렬되지 않은 데이터에서도 사용할 수 있는 가장 단순한 탐색 방법입니다.
    * 순차 탐색(Sequential Search)이라고도 합니다.

* 동작 과정:
    1. 배열의 첫 번째 요소부터 시작합니다.
    2. 현재 요소가 찾고자 하는 값인지 확인합니다.
    3. 찾고자 하는 값이 아니라면 다음 요소로 이동합니다.
    4. 찾고자 하는 값을 발견하거나 배열의 끝에 도달할 때까지 2~3 과정을 반복합니다.
    <img src="https://blog.kakaocdn.net/dn/cxaIv3/btqwdBoe2qb/1MXasQjts7UxK3KKK9e3hK/img.gif">

* 구현:
    ```python
    def linear_search(arr, target):
        for i in range(len(arr)):
            if arr[i] == target:
                return i  # 찾은 요소의 인덱스 반환
        return -1  # 요소를 찾지 못한 경우

    # 여러 개의 결과를 찾는 버전
    def linear_search_multiple(arr, target):
        indices = []
        for i in range(len(arr)):
            if arr[i] == target:
                indices.append(i)
        return indices if indices else [-1]
    ```

* 최적화된 구현:
    ```python
    def optimized_linear_search(arr, target):
        n = len(arr)
        # 보초값(sentinel) 추가
        arr.append(target)
        
        i = 0
        while arr[i] != target:
            i += 1
        
        # 보초값 제거
        arr.pop()
        
        # target을 찾았는지 확인
        if i < n:
            return i
        return -1
    ```

* 시간 복잡도
    * 최선의 경우: O(1)
        - 찾고자 하는 요소가 배열의 첫 번째에 있는 경우
    
    * 평균의 경우: O(n/2)
        - 요소가 배열의 중간쯤에 있는 경우

    * 최악의 경우: O(n)
        - 요소가 배열의 마지막에 있거나 배열에 없는 경우

* 공간 복잡도
    - O(1): 추가적인 메모리 공간을 거의 필요로 하지 않습니다.

* 장단점
    * 장점
        - 구현이 매우 간단합니다.
        - 정렬되지 않은 데이터셋에서도 사용 가능합니다.
        - 작은 데이터셋에서 효율적입니다.
        - 다른 탐색 알고리즘에 비해 추가 메모리가 필요하지 않습니다.

    * 단점
        - 배열의 크기가 커질수록 비효율적입니다.
        - 정렬된 데이터에서도 이진 탐색보다 느립니다.
        - 모든 요소를 확인해야 할 수 있습니다.

* 사용 사례:
    - 작은 데이터셋에서의 검색
    - 정렬되지 않은 데이터에서의 검색
    - 한 번만 검색하는 경우
    - 데이터가 자주 변경되는 경우

* 예제 및 활용
    ```python
    def linear_search_with_steps(arr, target):
        print(f"탐색 배열: {arr}")
        print(f"찾는 값: {target}")
        print("\n단계별 탐색 과정:")
        
        for i in range(len(arr)):
            print(f"Step {i + 1}: 인덱스 {i}의 값 {arr[i]} 확인")
            if arr[i] == target:
                print(f"\n값 {target}을(를) 인덱스 {i}에서 찾았습니다!")
                return i
        
        print(f"\n값 {target}을(를) 찾지 못했습니다.")
        return -1

    # 실행 예제
    numbers = [64, 34, 25, 12, 22, 11, 90]
    target = 22
    result = linear_search_with_steps(numbers, target)
    ```

* 변형 및 응용
    1. 범위 지정 선형 탐색
        ```python
        def range_linear_search(arr, target, start, end):
            for i in range(start, end + 1):
                if arr[i] == target:
                    return i
            return -1
        ```

    2. 조건부 선형 탐색
        ```python
        def conditional_linear_search(arr, condition):
            """조건을 만족하는 첫 번째 요소 찾기"""
            for i in range(len(arr)):
                if condition(arr[i]):
                    return i
            return -1

        # 사용 예시
        numbers = [1, 3, 5, 7, 9, 11]
        # 5보다 큰 첫 번째 숫자 찾기
        index = conditional_linear_search(numbers, lambda x: x > 5)
        ```

- 선형 탐색은 가장 기본적인 탐색 알고리즘으로, 작은 데이터셋이나 정렬되지 않은 데이터에서 유용합니다.
하지만 대규모 데이터셋에서는 이진 탐색과 같은 더 효율적인 알고리즘을 사용하는 것이 좋습니다. 특히 데이터가 정렬되어 있는 경우에는
이진 탐색이 훨씬 더 효율적입니다.

- 실제 프로그래밍에서는 선형 탐색보다 내장된 검색 함수나 더 효율적인 자료구조(해시 테이블 등)를 사용하는 것이 일반적이지만, 알고리즘의
기본 개념을 이해하는 데 있어 선형 탐색은 매우 중요한 시작점이 됩니다.

## 이진 탐색 (Binary Search)

* 이진 탐색의 개념
    * 이진 탐색은 정렬된 배열에서 특정 값을 찾는 효율적인 알고리즘입니다.
    * 배열의 중간 값을 확인하고, 찾고자 하는 값이 중간 값보다 작으면 왼쪽 부분을, 크면 오른쪽 부분을 탐색하는 방식입니다.
    * 매 단계마다 탐색 범위가 절반으로 줄어들어 매우 효율적입니다.
    * **중요**: 반드시 정렬된 배열에서만 사용할 수 있습니다.

* 동작 과정
    1. 배열의 중간 요소를 선택합니다.
    2. 중간 요소와 찾고자 하는 값을 비교합니다.
    3. 찾고자 하는 값이 중간 요소보다 작으면 왼쪽 부분을, 크면 오른쪽 부분을 선택합니다.
    4. 선택된 부분에서 1~3과정을 반복합니다.
    5. 값을 찾거나 더 이상 탐색할 수 없을 때까지 반복합니다.
    <img src="https://blog.kakaocdn.net/dn/zwZKf/btsyLtuB9GT/lGYPusuwXqk1zWMt3KA411/img.gif">

* 구현
    ```python
    def binary_search(arr, target):
        left = 0
        right = len(arr) - 1
        
        while left <= right:
            mid = (left + right) // 2
            
            if arr[mid] == target:
                return mid  # 찾은 요소의 인덱스 반환
            elif arr[mid] < target:
                left = mid + 1  # 오른쪽 부분 탐색
            else:
                right = mid - 1  # 왼쪽 부분 탐색
        
        return -1  # 요소를 찾지 못한 경우
    ```

* 재귀적 구현
    ```python
    def recursive_binary_search(arr, target, left, right):
        if left > right:
            return -1
            
        mid = (left + right) // 2
        
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            return recursive_binary_search(arr, target, mid + 1, right)
        else:
            return recursive_binary_search(arr, target, left, mid - 1)
    ```

* 시간 복잡도
    * 최선의 경우: O(1)
        - 찾고자 하는 요소가 중간 값인 경우

    * 평균의 경우: O(log n)
    * 최악의 경우: O(log n)
        - 찾고자 하는 요소가 없거나 맨 끝에 있는 경우

* 공간 복잡도
    * 반복적 구현: O(1)
    * 재귀적 구현: O(log n) - 재귀 호출 스택 때문

* 장단점
    * 장점
        - 매우 효율적인 탐색 속도 (O(log n))
        - 구현이 비교적 간단합니다.
        - 큰 데이터셋에서도 빠른 성능을 보장합니다.
        - 메모리 사용이 적습니다. (반복 구현의 경우)

    * 단점
        - 정렬된 배열에서만 사용 가능합니다.
        - 데이터가 자주 변경되는 경우 정렬 상태를 유지해야 합니다.
        - 연결 리스트와 같은 순차적 접근 자료구조에는 적합하지 않습니다.

* 사용 사례
    - 대규모 정렬된 데이터에서의 검색
    - 데이터베이스 인덱싱
    - 사전이나 전화번호부 검색
    - 시스템의 루트 찾기
    - 최적화 문제 해결

* 예제 및 활용
    ```python
    def binary_search_with_steps(arr, target):
        left = 0
        right = len(arr) - 1
        step = 1
        
        print(f"탐색 배열: {arr}")
        print(f"찾는 값: {target}")
        print("\n단계별 탐색 과정:")
        
        while left <= right:
            mid = (left + right) // 2
            print(f"\nStep {step}:")
            print(f"왼쪽 범위: {left}, 오른쪽 범위: {right}")
            print(f"중간 인덱스: {mid}, 중간 값: {arr[mid]}")
            
            if arr[mid] == target:
                print(f"\n값 {target}을(를) 인덱스 {mid}에서 찾았습니다!")
                return mid
            elif arr[mid] < target:
                print(f"중간 값이 작습니다. 오른쪽 부분 탐색")
                left = mid + 1
            else:
                print(f"중간 값이 큽니다. 왼쪽 부분 탐색")
                right = mid - 1
                
            step += 1
        
        print(f"\n값 {target}을(를) 찾지 못했습니다.")
        return -1

    # 실행 예제
    numbers = sorted([64, 34, 25, 12, 22, 11, 90])  # 정렬된 배열
    target = 22
    result = binary_search_with_steps(numbers, target)
    ```

* 응용 및 변형
    ```python
    def binary_search_first_occurrence(arr, target):
        """중복된 값이 있을 때 첫 번째 발생 위치 찾기"""
        left = 0
        right = len(arr) - 1
        result = -1
        
        while left <= right:
            mid = (left + right) // 2
            
            if arr[mid] == target:
                result = mid
                right = mid - 1  # 왼쪽도 계속 탐색
            elif arr[mid] < target:
                left = mid + 1
            else:
                right = mid - 1
                
        return result

    def binary_search_range(arr, target):
        """특정 값의 시작과 끝 인덱스 찾기"""
        first = binary_search_first_occurrence(arr, target)
        if first == -1:
            return [-1, -1]
            
        # 마지막 발생 위치 찾기
        left = first
        right = len(arr) - 1
        last = first
        
        while left <= right:
            mid = (left + right) // 2
            
            if arr[mid] == target:
                last = mid
                left = mid + 1
            elif arr[mid] < target:
                left = mid + 1
            else:
                right = mid - 1
                
        return [first, last]
    ```

- 이진 탐색은 대규모 정렬 데이터에서 매우 효율적인 탐색 알고리즘입니다. 특히 데이터베이스 인덱싱이나 시스템 최적화와 같은 실제
응용 분야에서 널리 사용됩니다. 데이터가 정렬되어 있어야 한다는 제약이 있지만, 그 제약을 만족하는 경우에는 가장 효율적인 탐색방법 중 하나입니다.

## 이진 검색 (Binary Search)의 심화

* 이진 검색의 변형
    1. 하한 검색 (Lower Bound)
        ```python
        def lower_bound(arr, target):
            """target 값이 처음 나타나는 위치를 찾음"""
            left, right = 0, len(arr)
            
            while left < right:
                mid = (left + right) // 2
                if arr[mid] < target:
                    left = mid + 1
                else:
                    right = mid
                    
            return left
        ```

    2. 상한 검색 (Upper Bound)
        ```python
        def upper_bound(arr, target):
            """target 값보다 큰 첫 번째 위치를 찾음"""
            left, right = 0, len(arr)
            
            while left < right:
                mid = (left + right) // 2
                if arr[mid] <= target:
                    left = mid + 1
                else:
                    right = mid
                    
            return left
        ```

* 고급 응용
    1. 범위 검색
        ```python
        def find_range(arr, target):
            """target의 시작과 끝 인덱스를 찾음"""
            first = lower_bound(arr, target)
            last = upper_bound(arr, target) - 1
            
            if first <= last:
                return [first, last]
            return [-1, -1]
        ```

    2. 순환 배열에서의 검색
        ```python
        def search_rotated(arr, target):
            """회전된 정렬 배열에서 검색"""
            left, right = 0, len(arr) - 1
            
            while left <= right:
                mid = (left + right) // 2
                
                if arr[mid] == target:
                    return mid
                    
                # 왼쪽 부분이 정렬되어 있는 경우
                if arr[left] <= arr[mid]:
                    if arr[left] <= target < arr[mid]:
                        right = mid - 1
                    else:
                        left = mid + 1
                # 오른쪽 부분이 정렬되어 있는 경우
                else:
                    if arr[mid] < target <= arr[right]:
                        left = mid + 1
                    else:
                        right = mid - 1
                        
            return -1
        ```

* 실수 값에서의 이진 검색
    ```python
    def binary_search_real(func, target, epsilon=1e-9):
        """실수 범위에서 특정 값을 찾는 이진 검색"""
        left, right = 0.0, 1e9
            
        while right - left > epsilon:
            mid = (left + right) / 2
            result = func(mid)
                
            if abs(result - target) < epsilon:
                return mid
            elif result < target:
                left = mid
            else:
                right = mid
                    
        return left
        ```

* 최적화 문제 해결
    ```python
    def find_peak_element(arr):
        """배열에서 peak 요소 찾기"""
        left, right = 0, len(arr) - 1
        
        while left < right:
            mid = (left + right) // 2
            if arr[mid] > arr[mid + 1]:
                right = mid
            else:
                left = mid + 1
                
        return left

    def minimize_maximum(arr, k):
        """최대값을 최소화하는 문제"""
        def can_divide(max_sum):
            count = 1
            current_sum = 0
            for num in arr:
                if current_sum + num > max_sum:
                    count += 1
                    current_sum = num
                else:
                    current_sum += num
            return count <= k

        left = max(arr)
        right = sum(arr)
        result = right
        
        while left <= right:
            mid = (left + right) // 2
            if can_divide(mid):
                result = mid
                right = mid - 1
            else:
                left = mid + 1
                
        return result
    ```

* 병렬 처리를 위한 이진 검색
    ```python
    from concurrent.futures import ThreadPoolExecutor
    import threading

    class ParallelBinarySearch:
        def __init__(self, arr):
            self.arr = arr
            self.lock = threading.Lock()
            
        def search_range(self, start, end, target):
            """주어진 범위에서 target 검색"""
            while start <= end:
                mid = (start + end) // 2
                if self.arr[mid] == target:
                    return mid
                elif self.arr[mid] < target:
                    start = mid + 1
                else:
                    end = mid - 1
            return -1
            
        def parallel_search(self, target, num_threads=4):
            n = len(self.arr)
            chunk_size = n // num_threads
            futures = []
            
            with ThreadPoolExecutor(max_workers=num_threads) as executor:
                for i in range(num_threads):
                    start = i * chunk_size
                    end = start + chunk_size - 1 if i < num_threads - 1 else n - 1
                    futures.append(
                        executor.submit(self.search_range, start, end, target)
                    )
                    
            for future in futures:
                result = future.result()
                if result != -1:
                    return result
                    
            return -1
    ```

* 이진 검색 트리와의 연계
    ```python
    class BSTNode:
        def __init__(self, value):
            self.value = value
            self.left = None
            self.right = None
            self.count = 1  # 중복 값 처리
            
        def insert(self, value):
            if value == self.value:
                self.count += 1
            elif value < self.value:
                if self.left:
                    self.left.insert(value)
                else:
                    self.left = BSTNode(value)
            else:
                if self.right:
                    self.right.insert(value)
                else:
                    self.right = BSTNode(value)
                    
        def find_kth_element(self, k):
            """k번째 작은 원소 찾기"""
            left_count = 0 if not self.left else self.left.count
            
            if k <= left_count:
                return self.left.find_kth_element(k)
            elif k <= left_count + self.count:
                return self.value
            else:
                return self.right.find_kth_element(k - left_count - self.count)
    ```

- 이진 검색의 심화 내용은 실제 문제 해결에서 매우 유용하게 활용됩니다. 특히 최적화 문제나 실수 값을 다루는
문제에서 자주 사용되며, 병렬 처리를 통해 성능을 더욱 향상시킬 수 있습니다.

## 해시 탐색 (Hash Search)

* 해시 탐색의 개념:
    * 해시 탐색은 해시 테이블을 사용하여 데이터를 저장하고 검색하는 방법입니다.
    * 해시 함수를 사용하여 검색 키를 해시 테이블의 인덱스로 변환합니다.
    * 이상적인 경우 O(1)의 시간 복잡도로 검색이 가능합니다.
    * 키-값 쌍의 데이터를 다루는데 매우 효율적입니다.

* 동작 과정
    1. 키를 해시 함수에 입력하여 해시 값(인덱스)를 생성합니다.
    2. 해시 값을 테이블 크기로 모듈로 연산하여 실제 인덱스를 계산합니다.
    3. 해당 인덱스에서 데이터를 검색합니다.
    4. 충돌이 발생한 경우 충돌 해결 방법을 사용합니다.
    <img src="https://blog.kakaocdn.net/dn/qm7rv/btqSpGi1keL/DmcosF7WCgjRmGiM5cE4p1/img.gif">

* 기본 구현
    ```python
    class HashTable:
        def __init__(self, size=10):
            self.size = size
            self.table = [[] for _ in range(self.size)]
        
        def _hash(self, key):
            if isinstance(key, str):
                # 문자열 키의 경우
                return sum(ord(c) for c in key) % self.size
            # 숫자 키의 경우
            return key % self.size
        
        def insert(self, key, value):
            hash_key = self._hash(key)
            # 체이닝 방식으로 충돌 해결
            for item in self.table[hash_key]:
                if item[0] == key:
                    item[1] = value  # 키가 이미 존재하면 값 업데이트
                    return
            self.table[hash_key].append([key, value])
        
        def search(self, key):
            hash_key = self._hash(key)
            # 체인에서 키 검색
            for item in self.table[hash_key]:
                if item[0] == key:
                    return item[1]
            return None
    ```

* 충돌 해결 방법
    1. 체이닝 (Chaining)
        ```python
        class ChainHashTable:
            def __init__(self, size):
                self.size = size
                self.table = [[] for _ in range(size)]
            
            def insert(self, key, value):
                hash_key = self._hash(key)
                self.table[hash_key].append([key, value])
            
            def search(self, key):
                hash_key = self._hash(key)
                for k, v in self.table[hash_key]:
                    if k == key:
                        return v
                return None
        ```

    2. 개방 주소법(Open Addressing)
        ```python
        class OpenAddressHashTable:
            def __init__(self, size):
                self.size = size
                self.table = [None] * size
            
            def _probe(self, key, i):
                # 선형 조사
                return (self._hash(key) + i) % self.size
            
            def insert(self, key, value):
                i = 0
                while i < self.size:
                    hash_key = self._probe(key, i)
                    if self.table[hash_key] is None:
                        self.table[hash_key] = [key, value]
                        return True
                    i += 1
                return False  # 테이블이 가득 참
            
            def search(self, key):
                i = 0
                while i < self.size:
                    hash_key = self._probe(key, i)
                    if self.table[hash_key] is None:
                        return None
                    if self.table[hash_key][0] == key:
                        return self.table[hash_key][1]
                    i += 1
                return None
        ```

* 시간 복잡도
    * 최선의 경우: O(1)
        - 충돌이 없는 경우
    
    * 평균의 경우: O(1)
        - 좋은 해시 함수와 적절한 테이블 크기 사용 시

    * 최악의 경우: O(n)
        - 모든 키가 같은 값을 가지는 경우

* 공간 복잡도
    - O(n): n개의 키-값 쌍을 저장하기 위한 공간 필요

* 장단점
    * 장점
        - 평균적으로 매우 빠른 검색 속도 (O(1))
        - 삽입과 삭제도 빠름
        - 키-값 쌍의 데이터를 다루기에 적합
        - 정렬되지 않은 데이터에서도 효율적

    * 단점
        - 추가 메모리 공간 필요
        - 해시 충돌 가능성
        - 데이터의 순서가 유지되지 않음
        - 적절한 해시 함수 선택이 중요

* 해시 함수 예제
    ```python
    def string_hash(key, table_size):
        """문자열 키에 대한 해시 함수"""
        hash_value = 0
        for char in key:
            hash_value = (hash_value * 31 + ord(char)) % table_size
        return hash_value

    def integer_hash(key, table_size):
        """정수 키에 대한 해시 함수"""
        return key % table_size

    def djb2_hash(key, table_size):
        """DJB2 해시 함수"""
        hash_value = 5381
        for char in str(key):
            hash_value = ((hash_value << 5) + hash_value) + ord(char)
        return hash_value % table_size
    ```

* 실제 응용 사례
    - 데이터베이스 인덱싱
    - 캐시 구현
    - 중복 검사
    - 사용자 인증 시스템
    - 블룸 필터

* 고급 기능 구현
    ```python
    class AdvancedHashTable:
        def __init__(self, size=10):
            self.size = size
            self.table = [[] for _ in range(self.size)]
            self.item_count = 0
            self.load_factor_threshold = 0.7
        
        def _resize(self):
            """테이블 크기를 두 배로 증가"""
            old_table = self.table
            self.size *= 2
            self.table = [[] for _ in range(self.size)]
            self.item_count = 0
            
            # 기존 항목들을 새 테이블에 재삽입
            for bucket in old_table:
                for key, value in bucket:
                    self.insert(key, value)
        
        def insert(self, key, value):
            if self.item_count / self.size >= self.load_factor_threshold:
                self._resize()
            
            hash_key = self._hash(key)
            for item in self.table[hash_key]:
                if item[0] == key:
                    item[1] = value
                    return
            
            self.table[hash_key].append([key, value])
            self.item_count += 1
    ```

- 해시 탐색은 현대 컴퓨터 시스템에서 가장 널리 사용되는 탐색방법 중 하나입니다. 특히 데이터베이스, 캐시 시스템,
컴파일러 등에서 핵심적인 역할을 합니다. 적절한 해시 함수와 충돌 해결 방법을 선택하면 매우 효율적인 검색 성능을 얻을 수 있습니다.

* 각 기초 탐색들의 장단점 비교표

| 알고리즘  | 시간 복잡도 (최선/평균/최악) | 공간 복잡도 | 장점 | 단점             |
|-----------|------------------------------|-------------|---------|-----------------------|
| 선형 탐색 | O(1) / O(n/2) / O(n)  | O(1) | 구현이 간단, 정렬 불필요  | 비효율적         |
| 이진 탐색 | O(1) / O(log n) / O(log n)     | O(1) | 효율적, 정렬된 데이터에서 강력    | 정렬 필요|
| 해시 탐색 | O(1) / O(1) / O(n)      | O(n)  |  매우 빠른 검색 속도   | 데이터 순서 유지 X |

* 기초 탐색 알고리즘의 사용 사례

| 알고리즘  | 사용 사례                                      |
|-----------|-----------------------------------------------|
| 선형 탐색 | 작은 데이터셋에서는 선형 탐색도 충분히 효율적. & 정렬되지 않은 작은 데이터나 드문 검색에는 선형 탐색이 적합. |
| 이진 탐색 | 정렬된 큰 데이터셋에서는 이진 탐색이 최적. & 데이터 정렬 후 이진 탐색을 사용하는 것이 효율적일 수 있음. |
| 해시 탐색 | 키-값 쌍의 데이터는 해시 탐색이 가장 효율적. |

# 재귀 알고리즘

## 일반 재귀 (Recursion)

* 재귀의 개념
    * 재귀는 함수가 자기 자신을 호출하여 문제를 해결하는 프로그래밍 기법입니다.
    * 큰 문제를 같은 형태의 작은 문제로 나누어 해결하는 방식입니다.
    * 재귀 함수는 항상 종료 조건(base case)을 가져야 합니다.
    * 대부분의 재귀는 반복문으로 변환이 가능합니다.

* 재귀의 필수 요소
    1. 종료 조건(base case)
        - 재귀 호출이 종료되는 조건
        - 더 이상의 재귀 호출이 필요 없는 가장 단순한 경우

    2. 재귀 단계 (Recursive Step)
        - 문제를 더 작은 부분 문제로 나누는 과정
        - 자기 자신을 호출하여 문제를 해결

* 기본 구현 예제
    ```python
    # 팩토리얼 계산
    def factorial(n):
        # 종료 조건
        if n <= 1:
            return 1
        # 재귀 단계
        return n * factorial(n - 1)

    # 피보나치 수열
    def fibonacci(n):
        # 종료 조건
        if n <= 1:
            return n
        # 재귀 단계
        return fibonacci(n - 1) + fibonacci(n - 2)
    ```

* 시간 복잡도
    * 문제와 구현 방식에 따라 다름
    * 예시:
        - 팩토리얼: O(n)
        - 피보나치(단순 재귀): O(2^n)
        - 이진 검색: O(log n)

* 공간 복잡도
    * 재귀 깊이만큼의 스택 공간 필요
    * 각 재귀 호출마다 지역 변수와 매개변수를 위한 메모리 필요
    * 대부분의 경우 O(n) 또는 그 이상

* 장단점
    * 장점
        - 코드가 직관적이고 이해하기 쉬움
        - 복잡한 문제를 단순한 부분으로 나누어 해결 가능
        - 수학적 귀납법과 유사한 문제 해결 방식
        - 트리나 그래프 같은 재귀적 자료구조를 다루기 적합

    * 단점
        - 메모리 사용량이 많음 (스택 오버플로우 위험)
        - 반복문에 비해 성능이 떨어질 수 있음.
        - 잘못 구현하면 무한 재귀에 빠질 수 있음.
        - 디버깅이 어려울 수 있음.

* 주요 응용 예제:
    1. 하노이 탑:
        ```python
        def hanoi(n, source, auxiliary, target):
            if n == 1:
                print(f"원반 1을 {source}에서 {target}으로 이동")
                return
            
            hanoi(n - 1, source, target, auxiliary)
            print(f"원반 {n}을 {source}에서 {target}으로 이동")
            hanoi(n - 1, auxiliary, source, target)
        ```

    2. 디렉토리 탐색:
        ```python
        import os

        def explore_directory(path, depth=0):
            indent = "  " * depth
            print(f"{indent}{os.path.basename(path)}/")
            
            try:
                for item in os.listdir(path):
                    item_path = os.path.join(path, item)
                    if os.path.isdir(item_path):
                        explore_directory(item_path, depth + 1)
                    else:
                        print(f"{indent}  {item}")
            except PermissionError:
                print(f"{indent}  Permission denied")
        ```

    3. 트리 순회:
        ```python
        class TreeNode:
        def __init__(self, value):
            self.value = value
            self.left = None
            self.right = None

        def inorder_traversal(node):
            if node:
                inorder_traversal(node.left)
                print(node.value, end=' ')
                inorder_traversal(node.right)
        ```

* 재귀를 반복문으로 변환
    ```python
    # 재귀적 팩토리얼
    def recursive_factorial(n):
        if n <= 1:
            return 1
        return n * recursive_factorial(n - 1)

    # 반복문으로 변환한 팩토리얼
    def iterative_factorial(n):
        result = 1
        for i in range(1, n + 1):
            result *= i
        return result
    ```

* 메모이제이션을 활용한 최적화
    ```python
    def fibonacci_memo(n, memo=None):
        if memo is None:
            memo = {}
        
        if n in memo:
            return memo[n]
        
        if n <= 1:
            return n
            
        memo[n] = fibonacci_memo(n - 1, memo) + fibonacci_memo(n - 2, memo)
        return memo[n]
    ```

* 꼬리 재귀 최적화
    ```python
    def tail_factorial(n, accumulator=1):
        if n <= 1:
            return accumulator
        return tail_factorial(n - 1, n * accumulator)
    ```

- 재귀는 프로그래밍의 강력한 도구이지만, 신중하게 사용해야 합니다. 특히 깊이가 깊어질 수 있는 경우에는 스택 오버플로우를 피하기 위해
반복문이나 꼬리 재귀를 고려해야 합니다. 또한, 성능이 중요한 경우에는 메모이제이션과 같은 최적화 기법을 활용하는 것이 좋습니다.

- 실제 사용할 때는 문제의 특성과 제약 조건을 고려하여 재귀와 반복문 중 적절한 방식을 선택해야 합니다. 특히 트리나 그래프와 같은 계층적
구조를 다룰 때는 재귀가 매우 유용할 수 있습니다.

## 꼬리 재귀 (Tail Recursion)

* 꼬리 재귀의 개념:
    * 꼬리 재귀는 재귀 호출이 함수의 마지막 연산으로 수행되는 형태의 재귀입니다.
    * 재귀 호출 이후에 추가적인 계산이 필요 없는 재귀 방식입니다.
    * 컴파일러가 최적화를 통해 반복문처럼 처리할 수 있어 일반 재귀보다 효율적입니다.
    * 스택 오버플로우의 위험이 적습니다.

* 일반 재귀와 꼬리 재귀의 차이
    ```python
    # 일반 재귀 (팩토리얼)
    def factorial(n):
        if n <= 1:
            return 1
        return n * factorial(n - 1)  # 재귀 호출 후 곱셈 연산 필요

    # 꼬리 재귀 (팩토리얼)
    def tail_factorial(n, accumulator=1):
        if n <= 1:
            return accumulator
        return tail_factorial(n - 1, n * accumulator)  # 재귀 호출이 마지막 연산
    ```

* 주요 특징
    1. 메모리 사용
        - 일반 재귀: 각 호출마다 스택 프레임 유지 필요
        - 꼬리 재귀: 컴파일러 최적화로 단일 스택 프레임만 사용 가능

    2. 성능
        - 일반 재귀보다 효율적
        - 반복문과 비슷한 성능 가능
        - 컴파일러의 최적화 지원 필요

* 구현 예제
    1. 피보나치 수열
        ```python
        # 꼬리 재귀로 구현한 피보나치
        def tail_fibonacci(n, curr=0, next=1):
            if n == 0:
                return curr
            return tail_fibonacci(n - 1, next, curr + next)
        ```

    2. 리스트 합계 계산
        ```python
        # 일반 재귀
        def sum_list(arr):
            if not arr:
                return 0
            return arr[0] + sum_list(arr[1:])

        # 꼬리 재귀
        def tail_sum_list(arr, acc=0):
            if not arr:
                return acc
            return tail_sum_list(arr[1:], acc + arr[0])
        ```

    3. 리스트 뒤집기
        ```python
        def tail_reverse_list(lst, acc=None):
            if acc is None:
                acc = []
            if not lst:
                return acc
            return tail_reverse_list(lst[1:], [lst[0]] + acc)
        ```

* 장단점
    * 장점
        - 메모리 효율성 향상
        - 스택 오버플로우 위험 감소
        - 컴파일러 최적화 가능
        - 실행 속도 향상 가능

    * 단점
        - 코드가 덜 직관적일 수 있음.
        - 누적 값(accumulator)관리 필요.
        - 모든 언어/컴파일러가 최적화를 지원하지 않음.
        - 일부 문제는 꼬리 재귀로 변환이 어려움.

* 실제 활용 예제
    1. 트리 순회
        ```python
        class TreeNode:
            def __init__(self, value):
                self.value = value
                self.left = None
                self.right = None

        def tail_inorder_traversal(node, acc=None):
            if acc is None:
                acc = []
                
            if not node:
                return acc
                
            # 왼쪽 서브트리 순회
            acc = tail_inorder_traversal(node.left, acc)
            # 현재 노드 처리
            acc.append(node.value)
            # 오른쪽 서브트리 순회
            return tail_inorder_traversal(node.right, acc)
        ```

    2. GCD(최대공약수) 계산
        ```python
        def tail_gcd(a, b):
            if b == 0:
                return a
            return tail_gcd(b, a % b)
        ```

* 꼬리 재귀로의 변환 가이드
    ```python
    # 일반적인 변환 패턴

    # 1. 누적 인자 추가
    def regular_sum(n):
        if n <= 1:
            return n
        return n + regular_sum(n - 1)

    def tail_sum(n, acc=0):
        if n <= 1:
            return n + acc
        return tail_sum(n - 1, acc + n)

    # 2. 보조 함수 사용
    def quick_sort(arr):
        def quick_sort_tail(arr, start, end):
            if start >= end:
                return
                
            pivot = partition(arr, start, end)
            quick_sort_tail(arr, start, pivot - 1)
            return quick_sort_tail(arr, pivot + 1, end)
            
        return quick_sort_tail(arr, 0, len(arr) - 1)
    ```

* 최적화 예제
    ```python
    class TailRecursionOptimizer:
        """꼬리 재귀 최적화를 시뮬레이션하는 클래스"""
        
        def __init__(self, func):
            self.func = func
            
        def __call__(self, *args, **kwargs):
            result = self.func(*args, **kwargs)
            while callable(result):
                result = result()
            return result

    @TailRecursionOptimizer
    def optimized_factorial(n, acc=1):
        if n <= 1:
            return acc
        return lambda: optimized_factorial(n - 1, n * acc)
    ```

- 꼬리 재귀는 일반 재귀의 단점을 보완하는 중요한 최적화 기법입니다. 특히 함수형 프로그래밍에서 자주 사용되며,
적절한 컴파일러 지원이 있을 경우 반복문 수준의 효율성을 얻을 수 있습니다. 하지만 Python과 같은 일부 언어들은 꼬리 재귀 최적화를
기본적으로 지원하지 않으므로, 이러한 제약사항을 고려하여 사용해야 합니다.

## 직접 재귀 (Direct Recursion)

* 직접 재귀의 개념
    * 함수가 자기 자신을 직접적으로 호출하는 재귀 방식입니다.
    * 가장 기본적이고 단순한 형태의 재귀입니다.
    * 중간 매개 함수 없이 바로 자신을 호출합니다.

* 구조와 특징
    * 함수 내부에서 동일한 함수를 직접 호출
    * 종료 조건과 재귀 호출로 구성
    * 스택 프레임이 직접적으로 쌓임

* 기본 구현 예제
    ```python
    def factorial(n):
        # 종료 조건
        if n <= 1:
            return 1
        # 직접 재귀 호출
        return n * factorial(n - 1)

    def countdown(n):
        # 종료 조건
        if n <= 0:
            print("발사!")
            return
        print(n)
        # 직접 재귀 호출
        countdown(n - 1)
    ```

* 활용 예제
    1. 배열의 합 계산
        ```python
        def array_sum(arr):
            if not arr:  # 빈 배열 체크
                return 0
            return arr[0] + array_sum(arr[1:])
        ```

    2. 문자열 뒤집기
        ```python
        def reverse_string(s):
            if len(s) <= 1:
                return s
            return reverse_string(s[1:]) + s[0]
        ```

    3. 거듭제곱 계산
        ```python
        def power(base, exponent):
            if exponent == 0:
                return 1
            return base * power(base, exponent - 1)
        ```

* 시간 복잡도와 공간 복잡도
    * 시간 복잡도: 문제에 따라 다름
        - 팩토리얼: O(n)
        - 피보나치: O(2^n)

    * 공간 복잡도: 재귀 깊이에 비례
        - 대부분 O(n)이상의 스택 공간 필요

* 최적화 기법
    ```python
    # 메모이제이션을 활용한 최적화
    def fibonacci_memo(n, memo=None):
        if memo is None:
            memo = {}
        if n in memo:
            return memo[n]
        if n <= 1:
            return n
        
        memo[n] = fibonacci_memo(n-1, memo) + fibonacci_memo(n-2, memo)
        return memo[n]

    # 파라미터 최적화
    def optimized_array_sum(arr, start=0):
        if start >= len(arr):
            return 0
        return arr[start] + optimized_array_sum(arr, start + 1)
    ```

* 장단점
    * 장점
        - 구현이 간단하고 직관적
        - 코드 가독성이 좋음
        - 문제를 자연스럽게 분할 가능

    * 단점
        - 메모리 사용량이 많음
        - 스택 오버플로우 위험
        - 깊은 재귀에서 성능 저하

* 실제 사용 예시
    ```python
    # 디렉토리 탐색
    def list_files(path):
        if os.path.isfile(path):
            return [path]
        
        files = []
        for item in os.listdir(path):
            full_path = os.path.join(path, item)
            files.extend(list_files(full_path))
        return files

    # 트리 순회
    class TreeNode:
        def __init__(self, value):
            self.value = value
            self.left = None
            self.right = None

    def preorder(self):
        print(self.value, end=' ')
        if self.left:
            self.left.preorder()
        if self.right:
            self.right.preorder()
    ```

- 직접 재귀는 가장 기본적인 재귀 형태로, 적절한 종료 조건과 함계 사용하면 많은 문제를 효율적으로 해결할 수 있습니다.
하지만 깊은 재귀나 큰 입력값에 대해서는 스택 오버플로우와 성능 저하에 주의해야 합니다.

## 간접 재귀 (Indirect Recursion)

* 간접 재귀의 개념
    * 두 개 이상의 함수가 서로를 호출하며 재귀를 형성하는 방식입니다.
    * 순환적 의존 관계를 가진 함수들의 호출입니다.
    * A -> B -> C -> A 형태로 호출이 순환됩니다.

* 기본 구현 예제
    ```python
    def is_even(n):
        if n == 0:
            return True
        return is_odd(n - 1)

    def is_odd(n):
        if n == 0:
            return False
        return is_even(n - 1)
    ```

* 실용적인 예제
    ```python
    class TreeNode:
        def __init__(self, value):
            self.value = value
            self.children = []

    def process_tree(node):
        print(f"처리: {node.value}")
        process_children(node.children)

    def process_children(children):
        if not children:
            return
        process_tree(children[0])
        process_children(children[1:])
    ```

* 파일 탐색 시스템 예제
    ```python
    def explore_directory(path):
        if os.path.isfile(path):
            process_file(path)
        else:
            process_directory(path)

    def process_directory(path):
        for item in os.listdir(path):
            full_path = os.path.join(path, item)
            explore_directory(full_path)

    def process_file(path):
        print(f"파일 발견: {path}")
    ```

* 성능 최적화
    ```python
    # 메모이제이션을 활용한 최적화
    def evaluate_expression(expr, memo=None):
        if memo is None:
            memo = {}
        if expr in memo:
            return memo[expr]
            
        result = parse_and_evaluate(expr, memo)
        memo[expr] = result
        return result

    def parse_and_evaluate(expr, memo):
        # 수식 파싱 및 평가
        if is_simple_expression(expr):
            return calculate(expr)
        return evaluate_expression(simplify(expr), memo)
    ```

* 시간 및 공간 복잡도
    * 시간 복잡도: 서로 호출하는 함수들의 복잡도 합
    * 공간 복잡도: 재귀 깊이에 비례(보통 O(n))

* 장단점
    * 장점
        - 복잡한 문제를 논리적으로 분할 가능
        - 코드의 모듈성 향상
        - 자연스러운 문제 해결 방식

    * 단점
        - 디버깅이 어려움
        - 함수 간 의존성 관리 필요
        - 메모리 사용량이 많음

* 데이터 구조 처리 예제
    ```python
    class LinkedList:
        def __init__(self):
            self.head = None

        def process_odd_nodes(self, node):
            if not node:
                return
            print(f"홀수 노드: {node.value}")
            if node.next:
                self.process_even_nodes(node.next)

        def process_even_nodes(self, node):
            if not node:
                return
            print(f"짝수 노드: {node.value}")
            if node.next:
                self.process_odd_nodes(node.next)
    ```

* 게임 로직 예제
    ```python
    def player1_turn(score1, score2):
        if score1 >= 100:
            return "Player 1 wins!"
        if score2 >= 100:
            return "Player 2 wins!"
        
        move = get_player1_move()
        return player2_turn(score1 + move, score2)

    def player2_turn(score1, score2):
        if score1 >= 100:
            return "Player 1 wins!"
        if score2 >= 100:
            return "Player 2 wins!"
            
        move = get_player2_move()
        return player1_turn(score1, score2 + move)
    ```

- 간접 재귀는 복잡한 문제를 여러 단계로 나누어 해결할 때 유용합니다. 특히 상태 기계나 게임 로직 구현에
자주 사용됩니다. 하지만 직접 재귀보다 디버깅이 어렵고 함수 간 의존성을 잘 관리해야 하므로 신중하게 사용해야 합니다.

## 순수 재귀 (Pure Recursion)

* 순수 재귀의 개념
    * 의부 변수나 상태를 사용하지 않고 오직 매개변수와 반환값만으로 재귀를 구현하는 방식
    * 함수형 프로그래밍의 원칙을 따르는 재귀 방식
    * 부수 효과(side effect)가 없는 재귀 구현

* 기본 구현
    ```python
    # 순수 재귀 팩토리얼
    def pure_factorial(n):
        if n <= 1:
            return 1
        return n * pure_factorial(n - 1)

    # 순수 재귀 피보나치
    def pure_fibonacci(n):
        if n <= 1:
            return n
        return pure_fibonacci(n - 1) + pure_fibonacci(n - 2)
    ```

* 리스트 처리 예제
    ```python
    def pure_sum(arr):
        if not arr:
            return 0
        return arr[0] + pure_sum(arr[1:])

    def pure_reverse(lst):
        if not lst:
            return []
        return [lst[-1]] + pure_reverse(lst[:-1])

    def pure_map(func, lst):
        if not lst:
            return []
        return [func(lst[0])] + pure_map(func, lst[1:])
    ```

* 트리 구조 처리
    ```python
    class TreeNode:
        def __init__(self, value):
            self.value = value
            self.left = None
            self.right = None

    def pure_tree_sum(node):
        if not node:
            return 0
        return node.value + pure_tree_sum(node.left) + pure_tree_sum(node.right)
    ```

* 장단점
    * 장점
        - 코드가 명확하고 예측 가능
        - 디버깅이 용이
        - 병렬 처리에 적합
        - 테스트가 쉬움

    * 단점
        - 성능이 상대적으로 낮을 수 있음.
        - 메모리 사용량이 많을 수 있음
        - 일부 문제는 구현이 복잡할 수 있음.

* 실제 응용
    ```python
    # 깊은 복사
    def pure_deep_copy(obj):
        if isinstance(obj, (int, float, str, bool)):
            return obj
        if isinstance(obj, list):
            return [pure_deep_copy(item) for item in obj]
        if isinstance(obj, dict):
            return {k: pure_deep_copy(v) for k, v in obj.items()}
        return obj

    # 경로 탐색
    def pure_find_path(maze, start, end, path=()):
        if start == end:
            return path + (end,)
        if start not in maze:
            return None
        
        for next_pos in maze[start]:
            if next_pos not in path:
                new_path = pure_find_path(maze, next_pos, end, path + (start,))
                if new_path:
                    return new_path
        return None
    ```

* 최적화 기법
    ```python
    def pure_fibonacci_optimized(n, a=0, b=1):
        if n == 0:
            return a
        if n == 1:
            return b
        return pure_fibonacci_optimized(n - 1, b, a + b)
    ```

- 순수 재귀는 함수형 프로그래밍의 원칙을 따르며, 코드의 예측 가능성과 테스트 용이성을 높입니다. 하지만 성능과 메모리 사용에
주의해야 하며, 적절한 사용 사례를 선택하는 것이 중요합니다.

# 분할 정복 (Divide and Conquer)

* 병합, 퀵, 이진 검색의 심화 부분도 분할 정복에 속함.

## 최대/최소 문제 해결(Max/Min Divide and Conquer)

* 개념
    * 분할 정복을 사용하여 배열이나 리스트에서 최대값/최소값을 찾는 알고리즘입니다.
    * 전체 배열을 작은 부분으로 나누어 각 부분의 최대/최소를 찾고 이를 결합합니다.
    * 단순 순회보다 효율적인 방법을 제공할 수 있습니다.

* 기본 구현
    ```python
    def find_max_min(arr, left, right):
        # 기저 사례: 요소가 하나인 경우
        if left == right:
            return arr[left], arr[left]
            
        # 기저 사례: 요소가 두 개인 경우
        if right - left == 1:
            return max(arr[left], arr[right]), min(arr[left], arr[right])
            
        # 분할
        mid = (left + right) // 2
        left_max, left_min = find_max_min(arr, left, mid)
        right_max, right_min = find_max_min(arr, mid + 1, right)
        
        # 결합
        return max(left_max, right_max), min(left_min, right_min)
    ```

* 최적화된 구현
    ```python
    def optimized_max_min(arr):
        n = len(arr)
        
        # 초기화
        if n % 2 == 0:
            max_val = max(arr[0], arr[1])
            min_val = min(arr[0], arr[1])
            start = 2
        else:
            max_val = min_val = arr[0]
            start = 1
            
        # 쌍으로 비교
        for i in range(start, n-1, 2):
            curr_max = max(arr[i], arr[i+1])
            curr_min = min(arr[i], arr[i+1])
            max_val = max(max_val, curr_max)
            min_val = min(min_val, curr_min)
            
        return max_val, min_val
    ```

* 응용: k번째 최대/최소값 찾기
    ```python
    def find_kth_element(arr, k, find_max=True):
        if len(arr) == 1:
            return arr[0]
            
        # 배열을 두 부분으로 분할
        mid = len(arr) // 2
        left = arr[:mid]
        right = arr[mid:]
        
        # 각 부분에서 재귀적으로 k번째 값 찾기
        if find_max:
            left_max = find_kth_element(left, k, True)
            right_max = find_kth_element(right, k, True)
            return max(left_max, right_max)
        else:
            left_min = find_kth_element(left, k, False)
            right_min = find_kth_element(right, k, False)
            return min(left_min, right_min)
    ```

* 구간 최대/최소값 찾기
    ```python
    class RangeMaxMin:
        def __init__(self, arr):
            self.arr = arr
            self.n = len(arr)
            self.tree = [{'max': 0, 'min': float('inf')} for _ in range(4 * self.n)]
            self.build_tree(0, 0, self.n - 1)
        
        def build_tree(self, node, start, end):
            if start == end:
                self.tree[node] = {'max': self.arr[start], 'min': self.arr[start]}
                return
                
            mid = (start + end) // 2
            self.build_tree(2*node + 1, start, mid)
            self.build_tree(2*node + 2, mid + 1, end)
            
            self.tree[node] = {
                'max': max(self.tree[2*node + 1]['max'], self.tree[2*node + 2]['max']),
                'min': min(self.tree[2*node + 1]['min'], self.tree[2*node + 2]['min'])
            }
            
        def query(self, left, right):
            def query_range(node, start, end, l, r):
                if l > end or r < start:
                    return float('-inf'), float('inf')
                    
                if l <= start and end <= r:
                    return self.tree[node]['max'], self.tree[node]['min']
                    
                mid = (start + end) // 2
                left_max, left_min = query_range(2*node + 1, start, mid, l, r)
                right_max, right_min = query_range(2*node + 2, mid + 1, end, l, r)
                
                return max(left_max, right_max), min(left_min, right_min)
                
            return query_range(0, 0, self.n - 1, left, right)
    ```

* 병렬 처리를 이용한 최적화
    ```python
    from concurrent.futures import ThreadPoolExecutor

    def parallel_max_min(arr, num_threads=4):
        n = len(arr)
        chunk_size = n // num_threads
        results = []
        
        def process_chunk(start, end):
            return max(arr[start:end]), min(arr[start:end])
            
        with ThreadPoolExecutor(max_workers=num_threads) as executor:
            futures = []
            for i in range(num_threads):
                start = i * chunk_size
                end = start + chunk_size if i < num_threads - 1 else n
                futures.append(executor.submit(process_chunk, start, end))
                
            for future in futures:
                results.append(future.result())
                
        final_max = max(result[0] for result in results)
        final_min = min(result[1] for result in results)
        return final_max, final_min
    ```

- 최대/최소 값을 찾는 분할 정복 알고리즘은 단순한 순회보다 더 효율적일 수 있으며, 특히 구간 쿼리나 병렬 처리가 필요한 경우에 유용합니다.
실제로는 문제의 특성과 데이터의 크기에 따라 적절한 방법을 선택해야 합니다.


## 카라츠바 알고리즘 (Karatsuba Algorithm, 큰 정수 곱셈)

* 카라츠바 알고리즘의 개념
    * 큰 수의 곱셈을 효율적으로 수행하기 위한 분할 정복 알고리즘입니다.
    * 일반적인 곱셈의 O(n^2)의 복잡도를 O(n^1.585)로 개선합니다.
    * 두 큰 수를 더 작은 부분으로 분할하여 곱셈을 수행합니다.

* 알고리즘 원리
    * x와 y를 각각 두 부분으로 분할:
        - `x = x1 x 10^(n/2) + x0`
        - `y = y1 x 10^(n/2) + y0`

    * 다음 세 값을 계산:
        - `z2 = x1 x y1`
        - `zo = x0 x y0`
        - `z1 = (x1 + x0)(y1 + y0) - z2 - z0`

    * 최종 결과:
        - `X x Y = z2 x 10^n + z1 x 10^(n/2) + z0`

* 기본 구현
    ```python
    def karatsuba(x, y):
        # 기저 사례
        if x < 10 or y < 10:
            return x * y
        
        # 자릿수 계산
        n = max(len(str(x)), len(str(y)))
        m = n // 2
        
        # 숫자 분할
        power = 10**m
        x1, x0 = divmod(x, power)
        y1, y0 = divmod(y, power)
        
        # 세 번의 재귀 호출
        z2 = karatsuba(x1, y1)
        z0 = karatsuba(x0, y0)
        z1 = karatsuba(x1 + x0, y1 + y0) - z2 - z0
        
        return (z2 * 10**(2*m)) + (z1 * 10**m) + z0
    ```

* 최적화된 구현
    ```python
    class KaratsubaMultiplier:
        def __init__(self):
            self.threshold = 64  # 임계값 설정
            
        def multiply(self, x, y):
            if x < self.threshold or y < self.threshold:
                return x * y
                
            n = max(self._bit_length(x), self._bit_length(y))
            m = (n + 32) // 64 * 32
            
            x1, x0 = x >> m, x & ((1 << m) - 1)
            y1, y0 = y >> m, y & ((1 << m) - 1)
            
            z2 = self.multiply(x1, y1)
            z0 = self.multiply(x0, y0)
            z1 = self.multiply(x1 + x0, y1 + y0) - z2 - z0
            
            return (z2 << (2*m)) + (z1 << m) + z0
            
        def _bit_length(self, n):
            return len(bin(n)) - 2
    ```

* 문자열 기반 구현 (매우 큰 수 처리)
    ```python
    def string_karatsuba(x_str, y_str):
        # 문자열 길이를 동일하게 맞춤
        n = max(len(x_str), len(y_str))
        if n == 1:
            return str(int(x_str) * int(y_str))
            
        x_str = x_str.zfill(n)
        y_str = y_str.zfill(n)
        
        m = n // 2
        x1, x0 = x_str[:-m], x_str[-m:]
        y1, y0 = y_str[:-m], y_str[-m:]
        
        # 재귀 호출
        z2 = int(string_karatsuba(x1, y1))
        z0 = int(string_karatsuba(x0, y0))
        z1 = int(string_karatsuba(str(int(x1) + int(x0)), 
                                str(int(y1) + int(y0)))) - z2 - z0
        
        # 결과 조합
        return str(z2 * 10**(2*m) + z1 * 10**m + z0)
    ```

* 병렬 처리 버전
    ```python
    from concurrent.futures import ProcessPoolExecutor

    def parallel_karatsuba(x, y, num_processes=4):
        if x < 1000 or y < 1000:
            return x * y
            
        n = max(len(str(x)), len(str(y)))
        m = n // 2
        power = 10**m
        
        x1, x0 = divmod(x, power)
        y1, y0 = divmod(y, power)
        
        with ProcessPoolExecutor(max_workers=num_processes) as executor:
            # 병렬로 세 부분 계산
            futures = [
                executor.submit(karatsuba, x1, y1),
                executor.submit(karatsuba, x0, y0),
                executor.submit(karatsuba, x1 + x0, y1 + y0)
            ]
            
            z2 = futures[0].result()
            z0 = futures[1].result()
            z1 = futures[2].result() - z2 - z0
            
        return (z2 * 10**(2*m)) + (z1 * 10**m) + z0
    ```

- 카라츠바 알고리즘은 매우 큰 수의 곱셈을 효율적으로 처리할 수 있는 중요한 알고리즘입니다.
특히 암호화나 큰 수의 정밀 계산이 필요한 분야에서 유용하게 사용됩니다. 하지만 작은 수의 경우 일반적인 곱셈이 더 효율적일 수 있으므로,
입력 크기에 따라 적절한 알고리즘을 선택하는 것이 중요합니다.

## 스트라센 알고리즘 (Strassen Algorithm, 행렬 곱셈)

* 스트라센 알고리즘의 개념
    * 행렬 곱셈을 효율적으로 수행하기 위한 분할 정복 알고리즘입니다.
    * 일반적인 행렬 곱셈의 O(n^3) 복잡도를 O(n^2.807)로 개선합니다.
    * 7번의 곱셈과 18번의 덧셈/뺄셈으로 행렬 곱셈을 수행합니다.

* 기본 구현
    ```python
    import numpy as np

    def strassen(A, B):
        n = len(A)
        
        # 기저 사례: 1x1 행렬
        if n == 1:
            return np.array([[A[0][0] * B[0][0]]])
        
        # 행렬을 4등분
        mid = n // 2
        A11 = A[:mid, :mid]
        A12 = A[:mid, mid:]
        A21 = A[mid:, :mid]
        A22 = A[mid:, mid:]
        
        B11 = B[:mid, :mid]
        B12 = B[:mid, mid:]
        B21 = B[mid:, :mid]
        B22 = B[mid:, mid:]
        
        # 7개의 곱셈
        M1 = strassen(A11 + A22, B11 + B22)
        M2 = strassen(A21 + A22, B11)
        M3 = strassen(A11, B12 - B22)
        M4 = strassen(A22, B21 - B11)
        M5 = strassen(A11 + A12, B22)
        M6 = strassen(A21 - A11, B11 + B12)
        M7 = strassen(A12 - A22, B21 + B22)
        
        # 결과 행렬 계산
        C11 = M1 + M4 - M5 + M7
        C12 = M3 + M5
        C21 = M2 + M4
        C22 = M1 - M2 + M3 + M6
        
        # 결과 합치기
        C = np.vstack([np.hstack([C11, C12]),
                    np.hstack([C21, C22])])
        
        return C
    ```

* 최적화된 구현
    ```python
    class StrassenMultiplier:
        def __init__(self, threshold=64):
            self.threshold = threshold
            
        def multiply(self, A, B):
            n = len(A)
            # 임계값보다 작은 경우 일반 행렬 곱셈 사용
            if n <= self.threshold:
                return np.dot(A, B)
                
            # 2의 제곱수로 패딩
            next_power = 1 << (n-1).bit_length()
            if n != next_power:
                A_padded = np.pad(A, ((0, next_power - n), (0, next_power - n)))
                B_padded = np.pad(B, ((0, next_power - n), (0, next_power - n)))
                result = self._strassen(A_padded, B_padded)
                return result[:n, :n]
                
            return self._strassen(A, B)
            
        def _strassen(self, A, B):
            n = len(A)
            if n <= self.threshold:
                return np.dot(A, B)
                
            mid = n // 2
            A11, A12, A21, A22 = self._split_matrix(A)
            B11, B12, B21, B22 = self._split_matrix(B)
            
            # 7개의 곱셈 수행
            M1 = self._strassen(A11 + A22, B11 + B22)
            M2 = self._strassen(A21 + A22, B11)
            M3 = self._strassen(A11, B12 - B22)
            M4 = self._strassen(A22, B21 - B11)
            M5 = self._strassen(A11 + A12, B22)
            M6 = self._strassen(A21 - A11, B11 + B12)
            M7 = self._strassen(A12 - A22, B21 + B22)
            
            C11 = M1 + M4 - M5 + M7
            C12 = M3 + M5
            C21 = M2 + M4
            C22 = M1 - M2 + M3 + M6
            
            return self._combine_matrix(C11, C12, C21, C22)
            
        def _split_matrix(self, M):
            n = len(M)
            mid = n // 2
            return (M[:mid, :mid], M[:mid, mid:],
                M[mid:, :mid], M[mid:, mid:])
                
        def _combine_matrix(self, C11, C12, C21, C22):
            return np.vstack([np.hstack([C11, C12]),
                            np.hstack([C21, C22])])
    ```

* 병렬 처리 버전
    ```python
    from concurrent.futures import ProcessPoolExecutor

    class ParallelStrassen:
        def __init__(self, threshold=64, num_processes=4):
            self.threshold = threshold
            self.num_processes = num_processes
            
        def multiply(self, A, B):
            with ProcessPoolExecutor(max_workers=self.num_processes) as executor:
                return self._parallel_strassen(A, B, executor)
                
        def _parallel_strassen(self, A, B, executor):
            n = len(A)
            if n <= self.threshold:
                return np.dot(A, B)
                
            mid = n // 2
            A11, A12, A21, A22 = self._split_matrix(A)
            B11, B12, B21, B22 = self._split_matrix(B)
            
            # 병렬로 7개의 곱셈 수행
            futures = [
                executor.submit(self._parallel_strassen,
                            A11 + A22, B11 + B22, executor),
                executor.submit(self._parallel_strassen,
                            A21 + A22, B11, executor),
                executor.submit(self._parallel_strassen,
                            A11, B12 - B22, executor),
                executor.submit(self._parallel_strassen,
                            A22, B21 - B11, executor),
                executor.submit(self._parallel_strassen,
                            A11 + A12, B22, executor),
                executor.submit(self._parallel_strassen,
                            A21 - A11, B11 + B12, executor),
                executor.submit(self._parallel_strassen,
                            A12 - A22, B21 + B22, executor)
            ]
            
            M1, M2, M3, M4, M5, M6, M7 = [f.result() for f in futures]
            
            C11 = M1 + M4 - M5 + M7
            C12 = M3 + M5
            C21 = M2 + M4
            C22 = M1 - M2 + M3 + M6
            
            return self._combine_matrix(C11, C12, C21, C22)
    ```

- 스트라센 알고리즘은 이론적으로는 더 빠르지만, 실제로는 작은 크기의 행렬에서 일반적인 행렬 곱셈보다는 느릴 수 있습니다.
따라서 적절한 임계값을 설정하여 하이브리드 방식으로 구현하는 것이 좋습니다. 또한, 수치 안정성 문제가 있을 수 있으므로 과학 계산에서는 주의가
필요합니다.

- 실제 응용에서는 BLAS나 LAPACK과 같은 최적화된 라이브러리를 사용하는 것이 더 효율적일 수 있습니다. 스트라센 알고리즘은 주로 이론적인 중요성과
대규모 행렬 연산의 가능성을 보여주는 데 의의가 있습니다.