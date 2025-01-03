# 삽입 정렬 (Insertion Sort)

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
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>

    void insertion_sort(std::vector<int>& arr) {
        int n = static_cast<int>(arr.size());

        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
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