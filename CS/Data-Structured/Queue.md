# 큐 (Queue)

* 개념
    * **큐(Queue)**는 **선입선출(FIFO, First In First Out)**을 특징으로 하는 선형 자료구조입니다.
        * 먼저 들어간 (Enqueue) 요소가 가장 먼저 나온 (Dequeue)다는 점에서 파이프나 줄 서기 (Line)을 연상할 수 있습니다.

    * 일상 생활에서의 예시:
        * 매표소 줄 서기: 먼저 줄을 선 사람이 먼저 표를 구입하고 줄을 빠져나옵니다.
        * 프린터 작업 대기열: 먼저 요청된 인쇄 작업이 먼저 처리된 후, 다음 요청이 처리됩니다.

    <img src="https://upload.wikimedia.org/wikipedia/commons/5/52/Data_Queue.svg" width="300"> <br>

* 큐의 주요 연산
    1. Enqueue(item)
        - 큐의 뒤(rear)에 새로운 요소를 삽입
        - 큐가 가득 차 있지 않으면 성공, 삽입 후 rear가 한 칸 이동

    2. Dequeue()
        - 큐의 앞(front)에서 요소를 제거하고 반환
        - 큐가 비어 있지 않으면 제거 가능, 제거 후 front가 한 칸 이동

    3. Peek()
        - 큐의 맨 앞(front) 요소를 반한하되, 제거하지 않음

    4. isEmpty()
        - 큐가 비어 있는지 확인(보통 front == rear 또는 size == 0으로 판단)

    5. isFull(배열 기반 고정 크기 큐의 경우)
        - 큐가 가득 찼는지 확인(size == capacity)

<br>

* 큐의 시작 복잡도
    | |연산|시간 복잡도| |
    |----|--------|
    |Enqueue | O(1)|
    |Dequeue | O(1)|
    |Peek | O(1)|
    |isEmpty | O(1)|
    |isFull | O(1)|

    * 단, 배열로 큐를 구현하되 배열의 맨 앞을 Dequeue 위치로 사용할 경우, 매 연산마다 원소를 한 칸씩 옮겨야 하므로 O(n)이 될 수도 있습니다.
        * 이를 해결하기 위해 원형 큐(Circular Queue) 또는 링크드 리스트 구현을 사용하면 각 연산을 O(1)에 처리할 수 있습니다.

<br>

* 큐의 구현 방법
    1. 배열 기반 구현 (고정 크기 큐)
        - 전제: 배열의 크기가 고정 (capacity)
        - 인덱스: front와 rear 인덱스를 별도로 관리
        - 주의사항: 단순히 front를 0부터 증가시키기만 하면, 배열의 앞 부분에 공간이 남아도 rear가 끝까지 가면 큐가 가득 찼다고 인식할 수 있음.
            - 해결: 원형 큐(Circular Queue) 구조로 인덱스를 `(index + 1) % capacity`로 계산

        - (1) 고정 크기 배열 + 원형 큐 예시
            ```python
            class CircularQueue:
                def __init__(self, capacity):
                    self.capacity = capacity
                    self.queue = [None] * capacity
                    self.front = 0
                    self.rear = 0
                    self.size = 0

                def isEmpty(self):
                    return self.size == 0
                
                def isFull(self):
                    return self.size == self.capacity
                
                def enqueue(self, item):
                    if self.isFull():
                        raise Exception("Queue is full")
                    self.queue[self.rear] = item
                    self.rear = (self.rear + 1) % self.capacity
                    self.size += 1
                
                def dequeue(self):
                    if self.isEmpty():
                        raise Exception("Queue is empty")
                    item = self.queue[self.front]
                    self.front = (self.front + 1) % self.capacity
                    self.size -= 1
                    return item
                
                def peek(self):
                    if self.isEmpty():
                        return None
                    return self.queue[self.front]
            ```

    2. 연결 리스트 기반 구현 (동적 크기 큐)
        - 크기 제한 없음: 노드를 동적으로 할당하므로, 메모리가 허용하는 한 확장 가능
        - 노드(Node)에 `data`와 `next`가 있으며, 큐는 보통 front와 rear노드 포인터를 유지
        - Enqueue시 `rear.next`에 새 노드 연결 후 `rear`를 새 노드로 갱신
        - Dequeue시 `front` 노드를 제거하고, `front = front.next`로 이동

        - (1) Python 구현
            ```python
            class Node:
                def __init__(self, data):
                    self.data = data
                    self.next = None

            class LinkedQueue:
                def __init__(self):
                    self.front = None
                    self.rear = None
                    self.size = 0
                
                def isEmpty(self):
                    return self.size == 0
                
                def enqueue(self, item):
                    new_node = Node(item)
                    if self.isEmpty():
                        self.front = new_node
                        self.rear = new_node
                    else:
                        self.rear.next = new_node
                        self.rear = new_node
                    self.size += 1
                
                def dequeue(self):
                    if self.isEmpty():
                        raise Exception("Queue is empty")
                    item = self.front.data
                    self.front = self.front.next
                    self.size -= 1
                    if self.isEmpty():
                        self.rear = None
                    return item
                
                def peek(self):
                    if self.isEmpty():
                        return None
                    return self.front.data
            ```

* 큐의 변형
    1. 원형 큐 (Circular Queue)
        - 인덱스를 원형으로 활용
            - Enqueue/Dequeue 시 `% capacity` 연산을 활용해 인덱스 재활용
            - 공간 낭비 없이 배열 앞뒤를 재활용 가능

    2. 덱 (Deque, Double-Ended Queue)
        - 양쪽(Front/Rear)에서 삽입/삭제가 가능한 자료구조
        - 스택과 큐의 혼합된 기능 제공
            - front, rear 어디서든 Enqueue, Dequeue 가능
        - 실사용 예시:
            - 슬라이딩 윈도우 문제
            - 양방향에서 처리가 필요한 버퍼 등

    3. 우선순위 큐(Priority Queue)
        - 일반 큐는 FIFO로 처리하지만, 우선순위 큐는 우선순위가 높은 요소가 먼저 나오도록 보장
            - 보통 힙(Heap) 자료구조를 사용

* 큐의 사용 사례
    1. BFS(너비 우선 탐색)
        - 그래프에서 인정 정점을 차례대로 큐에 넣어가며 탐색

    2. 프로세스 스케줄링
        - 운영체제에서 프로세스를 라운드 로빈(Round Robin) 방식으로 CPU에 할당

    3. 프린터 대기열
        - 먼저 들어온 인쇄 작업이 먼저 처리됨

    4. 캐시/버퍼
        - 네트워크 스위치나 메시지 큐 시스템에서 데이터를 큐 형태로 저장 후 순차 처리

* 실제 코드 예시
    1. Golang
        ```go
        package main

        import "fmt"

        type Node struct {
            data interface{}
            next *Node
        }

        type LinkedQueue struct {
            front *Node
            rear  *Node
            size  int
        }

        func NewLinkedQueue() *LinkedQueue {
            return &LinkedQueue{}
        }

        func (q *LinkedQueue) IsEmpty() bool {
            return q.size == 0
        }

        func (q *LinkedQueue) Enqueue(item interface{}) {
            newNode := &Node{data: item}
            if q.IsEmpty() {
                q.front = newNode
                q.rear = newNode
            } else {
                q.rear.next = newNode
                q.rear = newNode
            }
            q.size++
        }

        func (q *LinkedQueue) Dequeue() interface{} {
            if q.IsEmpty() {
                return nil
            }
            item := q.front.data
            q.front = q.front.next
            q.size--
            if q.IsEmpty() {
                q.rear = nil
            }
            return item
        }

        func (q *LinkedQueue) Peek() interface{} {
            if q.IsEmpty() {
                return nil
            }
            return q.front.data
        }

        func main() {
            queue := NewLinkedQueue()
            queue.Enqueue(10)
            queue.Enqueue(20)
            queue.Enqueue(30)
            
            fmt.Println(queue.Dequeue()) // 10
            fmt.Println(queue.Peek())    // 20
        }
        ```

* 큐의 장단점
    1. 장점
        - 선입선출(FIFO)로 순서 보장
        - 동시성 프로그래밍에서 생산자-소비자(Producer-Consumer) 모델에 활용
        - 삽입/삭제 연산이 O(1)(원형 큐, 링크드 리스트 기준)

    2. 단점
        - 임의 접근(중간 요소 직접 접근)이 어려움 -> O(n)
        - 배열 기반 고정 큐는 크기 제한 존재
        - 자료 구조상 가장 오래된 데이터부터만 제거 가능 -> 특정 요소만 빨리 빼내기가 힘듦

* 실전 팀
    1. 배열 vs 연결 리스트:
        - 간단한 구현: 배열 기반 (원형 큐)
        - 동적 크기 / 노드 삽입 빈번: 연결 리스트 기반

    2. 동시성:
        - 멀티스레드 환경에서는 스레드 안전한 큐(Locking, Lock-free) 사용

    3. 대규모 이벤트 처리:
        - 메시지 큐(RabbitMQ, Kafka 등)는 큐 개념과 유사하지만 내부는 Log-structured, 파티션, broker 클러스터링을 다룹니다.

    4. BFS 구현에 필수
        - 그래프, 트리에서 너비 우선 탐색 시 큐가 핵심적으로 활용됩니다.

* 마무리
    - 큐는 선입선출(FIFO) 특성을 지닌 대표적 자료구조로, 프로세스 스케줄링, 프린터 스풀러, 네트워크 패킷 처리 등 순차 처리에 매우 유용합니다.
    - 원형 큐, 연결 리스트 큐 등을 통해 삽입/삭제 시간 복잡도 O(1)을 달성할 수 있으며, 배열로 간단히 구현할 수도 있습니다.(단, 크기 제한 및 인덱스 처리 주의)
    - 덱(Deque), 우선순위 큐(Priority Queue)등 큐의 변형형도 자주 사용되므로, 다른 알고리즘/문제 해결에 필요한 경우 참고하면 좋습니다.