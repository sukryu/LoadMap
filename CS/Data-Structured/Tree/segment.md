# 세그먼트 트리 (Segment Tree)

* 개념
    * **세그먼트 트리**는 구간 쿼리(Range Query)를 효율적으로 처리하기 위한 트리 자료구조입니다.
    * 각 노드가 특정 구간의 정보(합, 최댓값, 최솟값 등)를 담고 있음
    * 전체 구간을 분할 정복(Divide and Conquer) 방식으로 나누어 관리
    * 특징:
        - 완전 이진 트리 구조
        - 리프 노드는 배열의 각 원소를 나타냄
        - 내부 노드는 자식 노드들의 결과를 결합한 값을 저장

* 주요 연산
    1. 트리 생성(Build)
        - 배열을 기반으로 세그먼트 트리 구축
        - 시간 복잡도: O(N)

    2. 구간 쿼리(Query)
        - 특정 구간의 결과값을 조회
        - 시간 복잡도: O(log N)

    3. 업데이트(Update)
        - 특정 위치의 값을 수정하고 트리를 갱신
        - 시간 복잡도: O(log N)

* 시간 복잡도
    |연산|복잡도|설명|
    |---|------|-----|
    |Build|O(N)|초기 트리 구축|
    |Query|O(log N)|구간 쿼리 처리|
    |Update|O(log N)|단일 값 업데이트|
    |Range Update*|O(log N)|구간 업데이트 (Lazy Propagation 사용 시)|

    * N은 원본 배열의 크기

* 기본 구현 (구간 합 세그먼트 트리)
    ```python
    class SegmentTree:
        def __init__(self, arr):
            self.n = len(arr)
            # 세그먼트 트리는 최대 4N 크기의 공간이 필요
            self.tree = [0] * (4 * self.n)
            self.build(arr, 0, 0, self.n - 1)
        
        def build(self, arr, node, start, end):
            if start == end:
                self.tree[node] = arr[start]
                return self.tree[node]
            
            mid = (start + end) // 2
            left_sum = self.build(arr, 2*node + 1, start, mid)
            right_sum = self.build(arr, 2*node + 2, mid + 1, end)
            self.tree[node] = left_sum + right_sum
            
            return self.tree[node]
        
        def query(self, node, start, end, left, right):
            # 구간이 전혀 겹치지 않는 경우
            if right < start or end < left:
                return 0
            
            # 구간이 완전히 포함되는 경우
            if left <= start and end <= right:
                return self.tree[node]
            
            # 구간이 일부만 겹치는 경우
            mid = (start + end) // 2
            left_sum = self.query(2*node + 1, start, mid, left, right)
            right_sum = self.query(2*node + 2, mid + 1, end, left, right)
            
            return left_sum + right_sum
        
        def update(self, node, start, end, index, new_value):
            # 범위를 벗어난 경우
            if index < start or end < index:
                return
            
            # 리프 노드에 도달한 경우
            if start == end:
                self.tree[node] = new_value
                return
            
            mid = (start + end) // 2
            self.update(2*node + 1, start, mid, index, new_value)
            self.update(2*node + 2, mid + 1, end, index, new_value)
            
            # 자식 노드들의 값을 결합
            self.tree[node] = self.tree[2*node + 1] + self.tree[2*node + 2]
```

* Lazy Propagation (지연 전파)
    ```python
    class LazySegmentTree:
        def __init__(self, arr):
            self.n = len(arr)
            self.tree = [0] * (4 * self.n)
            self.lazy = [0] * (4 * self.n)  # 지연 배열
            self.build(arr, 0, 0, self.n - 1)
        
        def propagate(self, node, start, end):
            if self.lazy[node] != 0:
                self.tree[node] += (end - start + 1) * self.lazy[node]
                if start != end:  # 리프 노드가 아니면 자식에게 전파
                    self.lazy[2*node + 1] += self.lazy[node]
                    self.lazy[2*node + 2] += self.lazy[node]
                self.lazy[node] = 0
        
        def range_update(self, node, start, end, left, right, value):
            self.propagate(node, start, end)
            
            if right < start or end < left:
                return
            
            if left <= start and end <= right:
                self.tree[node] += (end - start + 1) * value
                if start != end:
                    self.lazy[2*node + 1] += value
                    self.lazy[2*node + 2] += value
                return
            
            mid = (start + end) // 2
            self.range_update(2*node + 1, start, mid, left, right, value)
            self.range_update(2*node + 2, mid + 1, end, left, right, value)
            
            self.tree[node] = self.tree[2*node + 1] + self.tree[2*node + 2]
```

* 다양한 활용 케이스
    1. 구간 최솟값/최댓값
        ```python
        # 구간 최솟값을 구하는 세그먼트 트리
        def min_query(self, node, start, end, left, right):
            if right < start or end < left:
                return float('inf')
            
            if left <= start and end <= right:
                return self.tree[node]
            
            mid = (start + end) // 2
            left_min = self.min_query(2*node + 1, start, mid, left, right)
            right_min = self.min_query(2*node + 2, mid + 1, end, left, right)
            
            return min(left_min, right_min)
        ```

    2. 구간 XOR
        ```python
        # XOR 연산을 수행하는 세그먼트 트리
        def xor_query(self, node, start, end, left, right):
            if right < start or end < left:
                return 0
            
            if left <= start and end <= right:
                return self.tree[node]
            
            mid = (start + end) // 2
            return (self.xor_query(2*node + 1, start, mid, left, right) ^ 
                    self.xor_query(2*node + 2, mid + 1, end, left, right))
        ```

* 활용 사례
    1. 구간 합 쿼리
        - 특정 범위의 합을 O(log N)에 계산
        - 주식 거래량 집계, 매출 통계 등

    2. 히스토그램 최대 직사각형
        - 구간 최솟값을 이용한 분할 정복

    3. 구간 업데이트가 필요한 상황
        - Lazy Propagation으로 효율적 처리
        - 대량의 데이터 범위 수정

    4. 2D 세그먼트 트리
        - 2차원 배열의 구간 쿼리
        - 이미지 처리, 지도 데이터 등

* 장단점
    1. 장점
        - 구간 쿼리를 O(log N)에 처리
        - 동적 업데이트 지원
        - 다양한 연산에 적용 가능

    2. 단점
        - 구현이 복잡
        - 메모리 사용량이 큼 (4N)
        - 초기 구축 비용 (O(N))

* 실전 팁
    1. 구현 최적화
        - 재귀 대신 반복문 사용 가능
        - 비트 연산으로 인덱스 계산 최적화

    2. 메모리 관리
        - 필요한 경우 압축된 세그먼트 트리 사용
        - 동적 할당으로 메모리 효율화

    3. 문제 유형별 접근
        - 구간 업데이트가 많으면 Lazy Propagation
        - 특수한 연산은 결합법칙 확인

* 마무리
    - 세그먼트 트리는 구간 쿼리를 효율적으로 처리하는 강력한 자료구조
    - Lazy Propagation으로 구간 업데이트도 효율적 처리 가능
    - 구현이 복잡하지만, 많은 문제에서 최적의 해결책을 제공

```mermaid
graph TD
    subgraph "세그먼트 트리 구조"
        Root((Sum[0,7]))--> L1((Sum[0,3]))
        Root --> R1((Sum[4,7]))
        L1 --> L2((Sum[0,1]))
        L1 --> R2((Sum[2,3]))
        R1 --> L3((Sum[4,5]))
        R1 --> R3((Sum[6,7]))
    end
    
    subgraph "구간 쿼리 [2,5]"
        Q1[범위에 걸치는 노드들 방문]
        Q2[2,3 구간]
        Q3[4,5 구간]
        Q1 --> Q2
        Q1 --> Q3
    end
    
    style Root fill:#f9f,stroke:#333
    style L1 fill:#bbf,stroke:#333
    style R1 fill:#bbf,stroke:#333
    style L2 fill:#bfb,stroke:#333
    style R2 fill:#fbf,stroke:#333
    style L3 fill:#fbf,stroke:#333
    style R3 fill:#bfb,stroke:#333
```