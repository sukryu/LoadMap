# 버블 정렬 (Bubble Sort)

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
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>

    void bubble_sort(std::vector<int>& arr) {
        int n = static_cast<int>(arr.size());

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
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
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>

    void optimized_bubble_sort(std::vector<int>& arr) {
        int n = static_cast<int>(arr.size());

        for (int i = 0; i < n; i++) {
            bool swapped = false;

            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }

            if (!swapped) break;
        }
    }
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