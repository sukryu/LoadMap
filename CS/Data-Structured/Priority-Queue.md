# 우선순위 큐 (Priority Queue)

* 개념
    * **우선순위 큐(Priority Queue)**는 각 요소가 **우선순위(priority)**를 가지고 있으며, 우선순위가 높은 요소를 먼저 꺼낼 수 있는 자료구조입니다.
    * 일반 큐가 FIFO(First In First Out)를 따른다면, 우선순위 큐는 우선순위가 높은 순으로 Dequeue가 이루어짐.
    * 가장 흔히 사용하는 내부 구현은 힙(Heap) 구조를 사용합니다.
        - 최소 힙(Min-Heap): 가장 작은 값(우선순위가 가장 높은 값)이 루트
        - 최대 힙(Max-Heap): 가장 큰 값(우선순위가 가장 높은 값)이 루트.

* 우선순위 큐의 주요 연산
    1. Insert(Enqueue)
        - 새로운 요소를 힙에 삽입
        - 힙 트리에서 재정렬(상향/하향 이동) 과정을 거쳐 우선순위 속성 유지

    2. Pop(Dequeue)
        - 우선순위가 가장 높은(힙의 루트) 요소를 제거하고 반환
        - 보통 루트와 마지막 노드를 교환 후, 마지막 노드를 제거 -> 힙을 재정렬(Heapify)

    3. Peek()
        - 루트 노드를 반환하되 제거하지 않음 (최우선순위 값 확인)

    4. isEmpty()
        - 힙이 비어 있는지 확인

* 시간 복잡도
    | |연산|평균|최악| |
    |----|--------|----|
    |Insert | O(log n)| O(log n)|
    |Pop (remove) | O(log n)| O(log n)|
    |Peek | O(1)| O(1)|

    - n은 힙에 저장된 원소 개수
    - 내부적으로 완전 이진 트리 구조(힙)을 사용하기 때문에, 트리 높이가 O(log n)
    - 배열로 구현하더라도, 루트에서 리프까지의 Heapify 과정이 O(log n)

* 힙의 구조
    - 우선순위 큐를 구현할 때, 힙(Heap) 자료구조를 가장 많이 사용
    - 완전 이진 트리(Complete Binary Tree) 형태로, 배열 인덱스를 통해 빠르게 부모-자식 관계를 개선할 수 있음.

    1. 최대 힙 (Max-Heap)
        - 루트가 가장 큰 값(가장 높은 우선순위)을 가진 노드
        - 예: `[40, 25, 15, 10, 9, 4, 1]`
            - 루트(40)가 가장 큼
            - Insert 시: 새 노드는 배열 끝(트리의 마지막 레벨)에 삽입 -> 부모와 비교하며 위로 이동(상향식 재정렬)
            - Pop 시: 루트 노드 제거 -> 배열 끝 노드를 루트로 이동 -> 자식과 비교하며 아래로 이동 (하향식 재정렬)

    2. 최소 힙 (Min-Heap)
        - 루트가 가장 작은 값(가장 높은 우선순위)을 가진 노드
        - 예: Dijkstra 알고리즘에서 거리값이 작은 노드가 먼저 나와야 하므로 최소 힙 활용
        - Insert/Pop 시 상향식, 하향식 재정렬 과정은 동일하지만, 비교 기준이 반대(더 작은 값이 올라옴)

* 우선순위 큐 구현
    1. Python
        ```python
        import heapq

        # Python의 heapq는 기본적으로 '최소 힙(Min-Heap)' 기능 제공
        class MinPriorityQueue:
            def __init__(self):
                self.heap = []

            def insert(self, item):
                heapq.heappush(self.heap, item)  # O(log n)
            
            def pop(self):
                if not self.isEmpty():
                    return heapq.heappop(self.heap)  # O(log n)
                return None
            
            def peek(self):
                if not self.isEmpty():
                    return self.heap[0]
                return None

            def isEmpty(self):
                return len(self.heap) == 0

        # 사용 예시
        pq = MinPriorityQueue()
        pq.insert(10)
        pq.insert(3)
        pq.insert(5)
        print(pq.pop())  # 3 (가장 작은 값)
        print(pq.pop())  # 5
        print(pq.pop())  # 10
        ```

    2. Golang
        ```go
        package main

        import (
            "container/heap"
            "fmt"
        )

        // MinHeap 예시
        type MinHeap []int

        func (h MinHeap) Len() int           { return len(h) }
        func (h MinHeap) Less(i, j int) bool { return h[i] < h[j] }
        func (h MinHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

        // Push / Pop은 포인터 리시버로 구현
        func (h *MinHeap) Push(x interface{}) {
            *h = append(*h, x.(int))
        }

        func (h *MinHeap) Pop() interface{} {
            old := *h
            n := len(old)
            item := old[n-1]
            *h = old[0 : n-1]
            return item
        }

        func main() {
            mh := &MinHeap{}
            heap.Init(mh)

            heap.Push(mh, 10)
            heap.Push(mh, 3)
            heap.Push(mh, 7)
            fmt.Println(heap.Pop(mh)) // 3 (최소 값)
            fmt.Println(heap.Pop(mh)) // 7
            fmt.Println(heap.Pop(mh)) // 10
        }
        ```
        - Go 기본 패키지 `container/heap`은 최소 힙 구현을 위한 인터페이스 제공

* 우선순위 큐의 사용 사례
    1. Dijkstra 알고리즘
        - 그래프 최단 경로 계산에서, 현재까지의 최단 거리가 가장 작은 정점을 우선으로 탐색
        - Min-Heap 사용

    2. CPU 스케줄링 (오래된 OS 커널 개념)
        - 우선순위가 높은 프로세스가 먼저 CPU 점유
        - 시분할 시, 우선순위 재조정

    3. 이벤트 시뮬레이션
        - 타임스탬프가 작은 이벤트(시간이 빠른 이벤트)부터 처리

    4. 허프만 코딩(Huffman Coding)
        - 빈도가 가장 낮은 노드(우선순위가 높음)를 먼저 합침
        - 문자 빈도 기반 트리 생성

    5. 멀티 태스킹 환경의 작업 관리
        - 태스크 매니저(Task Manager)에서 긴급하거나 중요한 태스크 먼저 처리

    6. 데이터 스트림 분석
        - 상위 K개 요소만 관리할 때, 최소 힙으로 유지하면 전체를 정렬하지 않고도 관리 가능

* 우선순위 큐의 장단점
    1. 장점
        - 우선순위가 높은 요소부터 빠르게 꺼낼 수 있음.
        - 힙(Heap)사용으로 **O(log n)**의 효율적인 삽입/삭제 가능
        - 간단한 배열 혹은 연결 리스트 구현 대비 우선순위 처리에 최적화

    2. 단점
        - 임의 접근(중간 요소)를 원하는 경우 비효율적 (힙 트리에서 O(n) 탐색)
        - 우선순위 갱신(Decrease-Key 등)이 자주 필요한 경우, 힙 구조를 재정렬하는 구현이 조금 번거로움
        - 메모리 사용량 측면에서는 일반 큐와 크게 다르진 않으나, 내부 구조가 더 복잡

* 실전 팁
    1. Min-Heap vs Max-Heap
        - Python: `heapq`는 기본 Min-Heap
        - Max-Heap이 필요하면 `heapq`사용 시 음수로 변환, 혹은 직접 구현

    2. Decrease-Key 연산
        - 예: Dijkstra에서 노드 거리 갱신 -> 보통은 새로 삽입한 뒤 이전 요소를 사용하지 않는 식으로 처리(추가 메모리)

    3. 동시성 고려
        - 다중 스레드 환경이면 우선순위 큐 접근 시 락 (Lock)이나 락프리 알고리즘을 고려

    4. 배열 정렬과의 비교
        - 우선순위 큐가 필요한 경우: 매 삽입 시마다 정렬할 필요 없이 O(log n)에 처리 가능
        - 한 번에 전체 정렬이 필요한 경우: 정렬 알고리즘(O(n log n))을 쓰는게 낫기도 함.

    5. 실무 예시
        - Huffman 압축, Dijkstra 최단 경로, 타임스탬프 기반 이벤트 처리, Top-K 문제 등등

* 마무리
    - 우선순위 큐는 우선순위가 있는 작업을 관리할 때 매우 유용한 자료구조입니다.
    - 내부 구현은 **힙(Heap)**을 가장 자주 활용하며, 삽입/삭제 모두 O(log n) 시간에 가능.
    - 실무에서 그래프 최단 경로 알고리즘, 작업 스케줄링, 이벤트 시뮬레이션, Huffman 코딩 등 다양한 문제 해결에 필수적으로 사용됩니다.