# 선형 탐색 (Linear Search)

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
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>

    int linear_search(std::vector<int>& arr, int target) {
        int len = static_cast<int>(arr.size());

        for (int i = 0; i < len; i++) {
            if (arr[i] == target) return i;
        }
        return -1;
    }

    std::vector<int> linear_search_multiple(std::vector<int>& arr, int target) {
        int len = static_cast<int>(arr.size());
        std::vector<int> indices;
        indices.reserve(len / 2);  // 단순히 메모리 예약, 꼭 필요한 건 아님

        for (int i = 0; i < len; i++) {
            if (arr[i] == target) {
                indices.push_back(i);
            }
        }

        if (!indices.empty()) {
            return indices;
        } else {
            return std::vector<int>(); 
        }
    }

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
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>

    int optimized_linear_search(std::vector<int>& arr, int target) {
        int n = static_cast<int>(arr.size());

        // 보초값(sentinel) 추가
        arr.push_back(target);

        int i = 0;
        while (arr[i] != target) {
            i++;
        }

        // 보초값 제거
        arr.pop_back();

        // target을 찾았는지 확인
        if (i < n)
            return i;
        return -1;
    }
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