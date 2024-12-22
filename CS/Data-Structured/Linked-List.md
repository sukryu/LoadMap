# 연결 리스트 (Linked-List)

1. 연결 리스트 개요
    1. 연결 리스트란?
        - 연결 리스트는 데이터 요소들을 순차적으로 연결하는 선형 자료구조입니다. 각 요소(노드)는 데이터와 다음 노드를 가리키는 포인터로 구성됩니다.
        <img src="https://velog.velcdn.com/images%2Fwoojinn8%2Fpost%2Ff384a51f-73cb-4e99-82c0-5643470d7585%2F%EB%A7%81%ED%81%AC%EB%93%9C%EB%A6%AC%EC%8A%A4%ED%8A%B8%EA%B5%AC%EC%A1%B0.PNG">

    2. 배열과의 차이점
        - 배열: 연속된 메모리 공간, 고정 크기
        - 연결 리스트: 분산된 메모리 공간, 가변 크기

        | |특성|배열|연결 리스트| |
          |----|----|--------|
        |메모리 할당 | 연속 | 분산|
        |크기 변경 | 고정 | 동적|
        |접근 시간 | O(1) | O(n)|
        |삽입/삭제 | O(n) | O(1)|

2. 연결 리스트의 종류
    1. 단일 연결 리스트 (Singly Linked List)
        ```cpp
        struct Node {
            int data;
            Node* next;
        };
        ```
        <img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FdCeaPQ%2FbtrqLwmRyy4%2FDvlBBRO0vg2tnoenYLd4d0%2Fimg.png" width="507" height="303">

    2. 이중 연결 리스트 (Doubly Linked List)
        ```cpp
        struct Node {
            int data;
            Node* next;
            Node* prev;
        };
        ```
        <img src="https://velog.velcdn.com/images%2Fwoojinn8%2Fpost%2F4a0955a0-1fff-4c60-bf18-a98d37e73fd4%2FDoubly.PNG">

    3. 원형 연결 리스트 (Circular Linked List)
        ```cpp
        struct Node {
            int data;
            Node* next;
            // 마지막 노드의 next가 첫 노드를 가리킴
        };
        ```
        <img src="https://velog.velcdn.com/images%2Fwoojinn8%2Fpost%2Fa80262a6-5c75-423c-9914-4626ebf3eccf%2Fcircular.PNG">

3. 기본 연산과 구현
    1. 노드 생성
        ```javascript
        class Node {
            constructor(data) {
                this.data = data;
                this.next = null;
            }
        }
        ```

    2. 삽입 연산
        ```javascript
        function insert(head, data) {
            const newNode = new Node(data);
            if (!head) {
                return newNode;
            }
            let current = head;
            while (current.next) {
                current = current.next;
            }
            current.next = newNode;
            return head;
        }
        ```
        <img src="https://velog.velcdn.com/images%2Fwoojinn8%2Fpost%2F29ac0a3f-482c-4676-b220-7020cc5c87c7%2F%EB%85%B8%EB%93%9C%EC%B6%94%EA%B0%80%20%EC%A0%84%EC%B2%B4.PNG">

    3. 삭제 연산
        ```javascript
        function delete(head, data) {
            if (!head) return null;
            if (head.data === data) {
                return head.next;
            }
            let current = head;
            while (current.next) {
                if (current.next.data === data) {
                    current.next = current.next.next;
                    break;
                }
                current = current.next;
            }
            return head;
        }
        ```
        <img src="https://velog.velcdn.com/images%2Fwoojinn8%2Fpost%2F7b5928fb-97d8-4cd3-a317-c4811b2ccca1%2F%EB%85%B8%EB%93%9C%EC%82%AD%EC%A0%9C.PNG">

4. 고급 주제
    1. 메모리 관리
        ```cpp
        void deleteList(Node* node) {
            while (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
        ```

    2. 스레드 안전성
        ```java
        public class ThreadSafeLinkedList<T> {
            private Node<T> head;
            private final Object lock = new Object();
            
            public void add(T data) {
                synchronized(lock) {
                    // 삽입 로직
                }
            }
        }
        ```

5. 실제 사용 사례
    1. LRU 캐시 구현
        ```typescript
        class LRUCache {
            private capacity: number;
            private cache: Map<number, Node>;
            private list: LinkedList;
            
            constructor(capacity: number) {
                this.capacity = capacity;
                this.cache = new Map();
                this.list = new LinkedList();
            }
            
            get(key: number): number {
                // 구현
            }
            
            put(key: number, value: number): void {
                // 구현
            }
        }
        ```

6. 연습 문제 및 해결 방법
    1. 연결 리스트 뒤집기
        ```javascript
        function reverse(head) {
            let prev = null;
            let current = head;
            
            while (current) {
                const next = current.next;
                current.next = prev;
                prev = current;
                current = next;
            }
            
            return prev;
        }
        ```

    2. 순환 검출
        ```javascript
        function hasCycle(head) {
            let slow = head;
            let fast = head;
            
            while (fast && fast.next) {
                slow = slow.next;
                fast = fast.next.next;
                if (slow === fast) return true;
            }
            
            return false;
        }
        ```

7. 언어별 기본적인 연결 리스트 구현
    1. Python
        ```python
        class Node:
             def __init__(self, data):
                 self.data = data
                 self.next = None
         
         class LinkedList:
             def __init__(self):
                 self.head = None
         
             def add(self, data):
                 new_node = Node(data)
                 if not self.head:
                     self.head = new_node
                 else:
                     current = self.head
                     while current.next:
                         current = current.next
                     current.next = new_node
         
             def remove(self, data):
                 if not self.head:
                     return False
                 if self.head.data == data:
                     self.head = self.head.next
                     return True
                 current = self.head
                 while current.next:
                     if current.next.data == data:
                         current.next = current.next.next
                         return True
                     current = current.next
                 return False
         
             def display(self):
                 current = self.head
                 while current:
                     print(current.data, end=" -> ")
                     current = current.next
                 print("None")
         
         # 사용 예제
         ll = LinkedList()
         ll.add(1)
         ll.add(2)
         ll.add(3)
         ll.display()  # 출력: 1 -> 2 -> 3 -> None
         ll.remove(2)
         ll.display()  # 출력: 1 -> 3 -> None
        ```

    3. TypeScript
        ```typescript
        class LinkedListNode<T> {
            data: T;
            next: LinkedListNode<T> | null;
            
            constructor(data: T) {
                this.data = data;
                this.next = null;
            }
        }

        class LinkedList<T> {
            private head: LinkedListNode<T> | null;
            private size: number;
            
            constructor() {
                this.head = null;
                this.size = 0;
            }
            
            add(data: T): void {
                const newNode = new LinkedListNode(data);
                if (!this.head) {
                    this.head = newNode;
                } else {
                    let current = this.head;
                    while (current.next) {
                        current = current.next;
                    }
                    current.next = newNode;
                }
                this.size++;
            }
            
            insert(position: number, data: T): void {
                if (position < 0 || position > this.size) {
                    throw new Error("Index out of bounds");
                }
                
                const newNode = new LinkedListNode(data);
                if (position === 0) {
                    newNode.next = this.head;
                    this.head = newNode;
                } else {
                    let current = this.head;
                    for (let i = 0; i < position - 1; i++) {
                        current = current!.next;
                    }
                    newNode.next = current!.next;
                    current!.next = newNode;
                }
                this.size++;
            }
            
            remove(data: T): boolean {
                if (!this.head) return false;
                
                if (this.head.data === data) {
                    this.head = this.head.next;
                    this.size--;
                    return true;
                }
                
                let current = this.head;
                while (current.next) {
                    if (current.next.data === data) {
                        current.next = current.next.next;
                        this.size--;
                        return true;
                    }
                    current = current.next;
                }
                return false;
            }
            
            contains(data: T): boolean {
                let current = this.head;
                while (current) {
                    if (current.data === data) {
                        return true;
                    }
                    current = current.next;
                }
                return false;
            }
            
            size(): number {
                return this.size;
            }
        }
        ```

    4. Golang
        ```go
        package main

        type Node struct {
            data interface{}
            next *Node
        }

        type LinkedList struct {
            head *Node
            size int
        }

        func NewLinkedList() *LinkedList {
            return &LinkedList{
                head: nil,
                size: 0,
            }
        }

        func (l *LinkedList) Add(data interface{}) {
            newNode := &Node{data: data}
            if l.head == nil {
                l.head = newNode
            } else {
                current := l.head
                for current.next != nil {
                    current = current.next
                }
                current.next = newNode
            }
            l.size++
        }

        func (l *LinkedList) Insert(position int, data interface{}) error {
            if position < 0 || position > l.size {
                return fmt.Errorf("index out of bounds")
            }
            
            newNode := &Node{data: data}
            if position == 0 {
                newNode.next = l.head
                l.head = newNode
            } else {
                current := l.head
                for i := 0; i < position-1; i++ {
                    current = current.next
                }
                newNode.next = current.next
                current.next = newNode
            }
            l.size++
            return nil
        }

        func (l *LinkedList) Remove(data interface{}) bool {
            if l.head == nil {
                return false
            }
            
            if l.head.data == data {
                l.head = l.head.next
                l.size--
                return true
            }
            
            current := l.head
            for current.next != nil {
                if current.next.data == data {
                    current.next = current.next.next
                    l.size--
                    return true
                }
                current = current.next
            }
            return false
        }

        func (l *LinkedList) Contains(data interface{}) bool {
            current := l.head
            for current != nil {
                if current.data == data {
                    return true
                }
                current = current.next
            }
            return false
        }

        func (l *LinkedList) Size() int {
            return l.size
        }
        ```