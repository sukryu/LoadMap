# 병합 정렬 (Merge Sort)

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
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>

    std::vector<int> merge(
        std::vector<int>& left,
        std::vector<int>& right
    ) {
        std::vector<int> result;
        result.reserve(left.size() + right.size());

        int i = 0, j = 0;
        int n_left = static_cast(left.size());
        int n_right = static_cast(right.size());

        while (i < n_left && j < n_right) {
            if (left[i] <= right[j]) {
                result.push_back(left[i]);
                i++;
            } else {
                result.push_back(right[i]);
                j++;
            }
        }

        result.insert(result.end(), left.begin() + i; left.end());
        result.insert(result.end(), right.begin() + j; right.end());

        return result;
    }

    std::vector<int> merge_sort(std::vector<int> arr) {
        int n = static_cast<int>(arr.size());

        if (n <= 1) return arr;

        int mid = n / 2;
        std::vector<int> left_part(arr.begin(), arr.begin() + mid);
        std::vector<int> right_part(arr.begin() + mid, arr.end());

        left_part = merge_sort(left_part);
        right_part = merge_sort(right_part);

        return merge(left_part, right_part);
    }
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