# 선택 정렬 (Selection Sort)

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
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>

    void selection_sort(std::vector<int>& arr) {
        int n = static_cast<int>(arr.size());

        for (int i = 0; i < n; i++) {
            int min_idx = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[min_idx]) {
                    min_idx = j;
                }
            }
            std::swap(arr[i], arr[min_idx]);
        }
    }
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