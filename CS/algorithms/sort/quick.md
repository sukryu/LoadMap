# 퀵 정렬 (Quick Sort)

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
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>

    std::vector<int> quick_sort(std::vector<int>& arr) {
        int len = static_cast<int>(arr.size());
        if (len <= 1) return arr;

        int pivot = arr[len / 2];

        std::vector<int> left_part;
        std::vector<int> middle_part;
        std::vector<int> right_part;

        for (int i = 0; i < len; i++) {
            if (arr[i] < pivot) {
                left_part.push_back(arr[i]);
            } else if (arr[i] == pivot) {
                middle_part.push_back(arr[i]);
            } else {
                right_part.push_back(arr[i]);
            }
        }

        left_part = quick_sort(left_part);
        right_part = quick_sort(right_part);

        std::vector<int> result;
        result.reserve(left_part.size() + middle_part.size() + right_part.size());
        result.insert(result.end(), left_part.begin(), left_part.end());
        result.insert(result.end(), middle_part.begin(), middle_part.end());
        result.insert(result.end(), right_part.begin(), right_part.end());

        return result;
    }
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
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>

    int partition(std::vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }

        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    void quick_sort(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int pivot_index = partition(arr, low, high);
            quick_sort(arr, low, pivot_index - 1);
            quick_sort(arr, pivot_index + 1, high);
        }
    }

    void quick_sort_wrapper(std::vector<int>& arr) {
        if (!arr.empty()) {
            quick_sort(arr, 0, static_cast<int>(arr.size()) - 1);
        }
    }
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