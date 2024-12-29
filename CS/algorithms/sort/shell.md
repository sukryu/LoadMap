# 셸 정렬 (Shell Sort)

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
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>

    void shell_sort(std::vector<int>& arr) {
        int n = static_cast<int>(arr.size());
        int gap = n / 2;

        while (gap > 0) {
            for (int i = gap; i < n; i++) {
                int temp = arr[i];
                int j = i;

                while (j >= gap && arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }

                arr[j] = temp;
            }

            gap /= 2;
        }
    }
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