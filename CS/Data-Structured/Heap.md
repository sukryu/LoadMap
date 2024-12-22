# 힙 (Heap)

* 개념
    * 힙(Heap)은 완전 이진 트리(Complete Binary Tree) 형태로 구성되며, 부모 노드와 자식 노드 사이의 우선순위 관계를 보장하는 자료구조입니다.
        - 최대 힙(Max-Heap): 부모 노드가 자식 노드보다 항상 크거나 같음 -> 루트가 최댓값
        - 최소 힙(Min-Heap): 부모 노드가 자식 노드보다 항상 작거나 같음 -> 루트가 최솟값

    <img src="https://upload.wikimedia.org/wikipedia/commons/3/38/Max-Heap.svg" width="350" alt="Max-Heap 예시">

    * 완전 이진 트리(Complete Binary Tree)란?
        - 트리의 마지막 레벨을 제외한 모든 레벨이 노드로 꽉 차 있고, 마지막 레벨 역시 왼쪽부터 노드가 채워져 있는 이진 트리
        - 이를 통해 배열 인덱스로 쉽고 효율적으로 트리를 표현할 수 있음.

* 힙의 특징
    1. 부모-자식 간의 우선순위(힙 속성)
        - 최대 힙: 부모 >= 자식
        - 최소 힙: 부모 <= 자식
        - 트리 전체가 이를 만족하므로, 루트가 최댓값/최솟값이 됨

    2. 완전 이진 트리 구조
        - 배열에 순서대로 노드를 저장하는 방식으로 구현 가능
        - 부모 인덱스 = `i`, 자식 인덱스 = `2*i + 1 (왼쪽)`, `2*i + 2 (오른쪽)`(0-based)
        - 삽입과 삭제 시, 트리의 마지막 위치(또는 루트)와 교체하여 상향식 혹은 하향식 재정렬(Heapify)

    3. 시간 복잡도
        - 삽입(Insert): O(log n)
        - 삭제(Delete): O(log n) (루트 삭제)
        - 최댓값/최솟값 가져오기(Peek): O(1) (루트 노드 접근)
        - n은 힙에 저장된 원소의 개수

    4. 우선순위 큐(Priotiry Queue)의 핵심 구현
        - 힙은 우선순위 큐를 효율적으로 구현하기 위한 자료구조로 자주 활용됨

* 힙의 연산
    1. 삽입 (Insert)
        1. 힙(배열)의 가장 마지막 인덱스에 새 노드 추가
        2. 상향식 재정렬(Bubble Up)
            - 새로 삽입된 노드를 부모 노드와 비교
            - 최대 힙 -> 새 노드가 부모보다 크면 교환, 최소 힙 -> 새 노드가 부모보다 작으면 교환
            - 루트 또는 더 이상 조건을 만족하지 않을 때까지 반복

    2. 삭제 (Delete)
        1. 보통 힙의 루트 노드(최대 힙 -> 최댓값, 최소 힙 -> 최솟값) 삭제
        2. 힙(배열)의 마지막 노드를 루트 자리에 가져옴
        3. 하향식 재정렬(Bubble Down or Heapify Down)
            - 새 루트 노드들 자식들과 비교
            - 최대 힙 -> 더 큰 자식과 교환, 최소 힙 -> 더 작은 자식과 교환
            - 리프에 도달하거나 더 이상 조건을 만족하지 않을 때까지 반복

    3. 조회 (Peek)
        - 힙의 루트 노드(가장 큰/가장 작은 값) 확인
        - 시간 복잡도 O(1), 단순히 배열의 첫 요소 반환

* 힙 구현 예시
    1. Python (직접 구현, 최대 힙)
        ```python
        class MaxHeap:
            def __init__(self):
                self.heap = []  # 배열 기반

            def __len__(self):
                return len(self.heap)

            def is_empty(self):
                return len(self.heap) == 0

            def _swap(self, i, j):
                self.heap[i], self.heap[j] = self.heap[j], self.heap[i]

            def insert(self, value):
                # 1. 힙의 끝에 새로운 노드 삽입
                self.heap.append(value)
                # 2. 상향식 재정렬(bubble up)
                idx = len(self.heap) - 1
                parent = (idx - 1) // 2
                while idx > 0 and self.heap[idx] > self.heap[parent]:
                    self._swap(idx, parent)
                    idx = parent
                    parent = (idx - 1) // 2

            def pop(self):
                if self.is_empty():
                    return None
                # 루트(최댓값) 반환을 위해 저장
                root_value = self.heap[0]
                # 마지막 노드를 루트로 이동
                last = self.heap.pop()
                if not self.is_empty():
                    self.heap[0] = last
                    # 3. 하향식 재정렬(bubble down)
                    self._heapify_down(0)
                return root_value

            def _heapify_down(self, idx):
                length = len(self.heap)
                while True:
                    left = 2 * idx + 1
                    right = 2 * idx + 2
                    largest = idx

                    # 왼쪽 자식이 존재하고, 더 크면 교환 대상
                    if left < length and self.heap[left] > self.heap[largest]:
                        largest = left
                    # 오른쪽 자식이 존재하고, 더 크면 교환 대상
                    if right < length and self.heap[right] > self.heap[largest]:
                        largest = right
                    # 더 이상 교환할 필요가 없으면 종료
                    if largest == idx:
                        break
                    # 교환 후 계속 진행
                    self._swap(idx, largest)
                    idx = largest

            def peek(self):
                return None if self.is_empty() else self.heap[0]

        # 사용 예시
        if __name__ == "__main__":
            h = MaxHeap()
            h.insert(20)
            h.insert(10)
            h.insert(30)
            h.insert(25)

            print(h.pop())  # 30
            print(h.pop())  # 25
            print(h.pop())  # 20
            print(h.pop())  # 10
            print(h.pop())  # None (힙 비어 있음)
        ```

* 힙의 종류 및 응용
    1. 최대 힙(Max-Heap)
        - 부모 노드가 자식 노드보다 항상 크거나 같음
        - 루트 노드 = 힙 내 최댓값
        - 우선순위 큐에서 '값이 클수록 우선순위가 높다'는 기준일 때 사용

    2. 최소 힙 (Min-Heap)
        - 부모 노드가 자식 노드보다 항상 작거나 같음
        - 루트 노드 = 힙 내 최솟값
        - 우선순위 큐에서 '값이 작을수록 우선순위가 높다'는 기준일 때 사용
        - Dijkstra 최단 경로, Prim MST, 이벤트 처리 등에서 자주 쓰임

    3. 이진 힙(Binary Heap) 이외 확장
        - d-힙(d-ary heap): 자식이 최대 d개인 힙
        - 피보나치 힙(Fibonacci Heap): Decrease-Key가 빠른 고급 힙(Amortized O(1))

* 힙의 사용 사례
    1. 우선순위 큐
        - 최대 힙/최소 힙을 사용해 O(log n)의 빠른 삽입/삭제
    
    2. 힙 정렬(Heap Sort)
        - 최대 힙을 이용하여 오름차순 정렬(O(n log n))
        - 최소 힙을 이용하면 내림차순

    3. 그래프 알고리즘
        - Dijkstra(최단 경로), Prim(최소 신장 트리)등에서 최소 힙 사용

    4. 중간 값 찾기(Median)
        - 최대 힙과 최소 힙을 결합하여 스트림 중간값을 실시간 계산

    5. 스케줄링
        - 운영체제 또는 작업 스케줄링에서 우선순위가 높은 작을 먼저 수행

* 힙의 장단점
    1. 장점
        - 배열로 구현 가능, 메모리 접근 효율이 높음(인접한 인덱스에 노드 배치)
        - 최대/최소값을 **O(1)**에 확인 가능(루트 노드)
        - 삽입/삭제 모두 O(log n), 우선순위 큐로서 효율적

    2. 단점
        - 임의 노드 탐색은 효율적이지 않음 (일반적으로 O(n))
        - 루트 노드만 최댓값/최솟값 보장, 두 번째 최댓값/최솟값 등은 트리 구조 내에서 추가 탐색 필요
        - 배열처럼 인덱스 기반 랜덤 접근해도, 힙 속성 때문에 노드 간 우선순위 구조를 무시하면 안 됨

* 힙 정렬 (Heap Sort)
    1. 최대 힙 구축 (Build-Heap)
        - 전체 배열을 최대 힙 형태로 O(n) 시간에 만들 수 있음 (상향식으로 heapify)

    2. 정렬 과정
        - 루트(최댓값)과 배열의 마지막 요소 교환 -> 마지막 요소는 정렬 완료 구간으로 확정
        - 힙 크기를 1 감소 후, 루트에 대한 하향식 heapify
        - 반복하여 정렬된 결과를 얻음 (O(n log n))

* 실전 팁
    1. Python: `import heapq`
        - 기본적으로 최소 힙 기능 제공
        - 최대 힙 필요 시 음수로 변환해서 푸시/팝 또는 별도 클래스 구현

    2. Go: `container/heap` 패키지
        - 인터페이스를 직접 구현하여 MinHeap/MaxHeap 등 커스터마이징

    3. 정렬된 데이터 관리:
        - 삽입/삭제 빈도가 많을 때 매번 전체 정렬보다 힙 사용이 효율적 (O(log n) vs O(n log n))

    4. Decrease-Key 연산 **(우선순위 업데이트)**
        - 일반 이진 힙에서는 기존 노드를 찾아서 값 변경 후 재정렬이 필요 (검색에 O(n))
        - 대안으로 Fibonacci Heap 등 사용하면 Decrease-Key가 Amortized O(1), 그러나 구현 난이도 ↑

    5. 메모리 사용
        - 힙 정렬 시 내부 배열 하나로 정렬 수행, 추가 공간은 O(1)
        - 우선순위 큐로 활용 시 삽입마다 배열 리사이징(동적 배열)가능성 고려

* 마무리
    - **힙(Heap)**은 완전 이진 트리 형태에서 부모-자식 간 우선순위를 유지하는 자료구조입니다.
    - 삽입/삭제가 **O(log n)**으로 빠르며, 최댓값/최솟값을 즉시 얻을 수 있어 우선순위 큐, 힙 정렬, 그래프 알고리즘 등에 널리 쓰입니다.
    - 힙 구현 자체는 비교적 간단(배열과 인덱스 연산), 그러나 Decrease-Key, 임의 노드 삭제 등은 추가 고려가 필요합니다.