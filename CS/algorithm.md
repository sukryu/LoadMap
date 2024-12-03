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