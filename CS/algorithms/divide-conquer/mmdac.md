# 최대/최소 문제 해결(Max/Min Divide and Conquer)

* 개념
    * 분할 정복을 사용하여 배열이나 리스트에서 최대값/최소값을 찾는 알고리즘입니다.
    * 전체 배열을 작은 부분으로 나누어 각 부분의 최대/최소를 찾고 이를 결합합니다.
    * 단순 순회보다 효율적인 방법을 제공할 수 있습니다.

* 기본 구현
    ```python
    def find_max_min(arr, left, right):
        # 기저 사례: 요소가 하나인 경우
        if left == right:
            return arr[left], arr[left]
            
        # 기저 사례: 요소가 두 개인 경우
        if right - left == 1:
            return max(arr[left], arr[right]), min(arr[left], arr[right])
            
        # 분할
        mid = (left + right) // 2
        left_max, left_min = find_max_min(arr, left, mid)
        right_max, right_min = find_max_min(arr, mid + 1, right)
        
        # 결합
        return max(left_max, right_max), min(left_min, right_min)
    ```

* 최적화된 구현
    ```python
    def optimized_max_min(arr):
        n = len(arr)
        
        # 초기화
        if n % 2 == 0:
            max_val = max(arr[0], arr[1])
            min_val = min(arr[0], arr[1])
            start = 2
        else:
            max_val = min_val = arr[0]
            start = 1
            
        # 쌍으로 비교
        for i in range(start, n-1, 2):
            curr_max = max(arr[i], arr[i+1])
            curr_min = min(arr[i], arr[i+1])
            max_val = max(max_val, curr_max)
            min_val = min(min_val, curr_min)
            
        return max_val, min_val
    ```

* 응용: k번째 최대/최소값 찾기
    ```python
    def find_kth_element(arr, k, find_max=True):
        if len(arr) == 1:
            return arr[0]
            
        # 배열을 두 부분으로 분할
        mid = len(arr) // 2
        left = arr[:mid]
        right = arr[mid:]
        
        # 각 부분에서 재귀적으로 k번째 값 찾기
        if find_max:
            left_max = find_kth_element(left, k, True)
            right_max = find_kth_element(right, k, True)
            return max(left_max, right_max)
        else:
            left_min = find_kth_element(left, k, False)
            right_min = find_kth_element(right, k, False)
            return min(left_min, right_min)
    ```

* 구간 최대/최소값 찾기
    ```python
    class RangeMaxMin:
        def __init__(self, arr):
            self.arr = arr
            self.n = len(arr)
            self.tree = [{'max': 0, 'min': float('inf')} for _ in range(4 * self.n)]
            self.build_tree(0, 0, self.n - 1)
        
        def build_tree(self, node, start, end):
            if start == end:
                self.tree[node] = {'max': self.arr[start], 'min': self.arr[start]}
                return
                
            mid = (start + end) // 2
            self.build_tree(2*node + 1, start, mid)
            self.build_tree(2*node + 2, mid + 1, end)
            
            self.tree[node] = {
                'max': max(self.tree[2*node + 1]['max'], self.tree[2*node + 2]['max']),
                'min': min(self.tree[2*node + 1]['min'], self.tree[2*node + 2]['min'])
            }
            
        def query(self, left, right):
            def query_range(node, start, end, l, r):
                if l > end or r < start:
                    return float('-inf'), float('inf')
                    
                if l <= start and end <= r:
                    return self.tree[node]['max'], self.tree[node]['min']
                    
                mid = (start + end) // 2
                left_max, left_min = query_range(2*node + 1, start, mid, l, r)
                right_max, right_min = query_range(2*node + 2, mid + 1, end, l, r)
                
                return max(left_max, right_max), min(left_min, right_min)
                
            return query_range(0, 0, self.n - 1, left, right)
    ```

* 병렬 처리를 이용한 최적화
    ```python
    from concurrent.futures import ThreadPoolExecutor

    def parallel_max_min(arr, num_threads=4):
        n = len(arr)
        chunk_size = n // num_threads
        results = []
        
        def process_chunk(start, end):
            return max(arr[start:end]), min(arr[start:end])
            
        with ThreadPoolExecutor(max_workers=num_threads) as executor:
            futures = []
            for i in range(num_threads):
                start = i * chunk_size
                end = start + chunk_size if i < num_threads - 1 else n
                futures.append(executor.submit(process_chunk, start, end))
                
            for future in futures:
                results.append(future.result())
                
        final_max = max(result[0] for result in results)
        final_min = min(result[1] for result in results)
        return final_max, final_min
    ```

- 최대/최소 값을 찾는 분할 정복 알고리즘은 단순한 순회보다 더 효율적일 수 있으며, 특히 구간 쿼리나 병렬 처리가 필요한 경우에 유용합니다.
실제로는 문제의 특성과 데이터의 크기에 따라 적절한 방법을 선택해야 합니다.