# 이진 탐색 (Binary Search)

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
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>

    int binary_search(std::vector<int>& arr, int target) {
        int len = static_cast<int>(arr.size());
        int left = 0;
        int right = len - 1;

        while (left <= right) {
            int mid = (left + right) / 2;

            if (arr[mid] == target) return mid;
            else if (arr[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }
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
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>

    int recursive_binary_search(
        std::vector<int>& arr,
        int target,
        int left,
        int right
    ) {
        if (left > right) return -1;

        int mid = (left + right) / 2;

        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) {
            return recursive_binary_search(arr, target, mid + 1, right);
        }
        else {
            return recursive_binary_search(arr, target, left, mid - 1);
        }
    }
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