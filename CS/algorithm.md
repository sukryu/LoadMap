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
