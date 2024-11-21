# 자료구조의 기본 개념

자료구조는 데이터를 저장하고 관리하는 방식 또는 방법을 말합니다.
프로그래밍 및 컴퓨터 과학에서는 데이터의 효율적인 접근, 수정, 삽입, 삭제 등을 위해 다양한 자료구조를 사용합니다. 자료구조의 선택은 문제 해결의 효율성과 알고리즘의 성능에 큰 영향을 미칩니다.

# 배열 (Array)

* 배열은 여러 개의 같은 타입의 데이터를 순서대로 저장하는 구조입니다. 서랍장을 생각하면 이해하기 편합니다.

<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FcqPkgm%2FbtsJDgS66VB%2FeKSm2MhNKbPJgECDp2SkYK%2Fimg.png" width="832" height="101">

1. 기본 연산고 시간 복잡도
    * 접근 (Access) - O(1)
        - 인덱스를 통한 직접 접근
        - 한 번의 계산으로 원하는 위치 접근 가능
        - 예: 배열[3] = 시작주소 + 데이터크기(x3)

    <img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FxAtLX%2FbtsJD7U9Wt8%2FnAKNwOuLCtddlOkebYQeh1%2Fimg.png" width="824" heigth="157">

    * 수정 (Modification) - O(1)
        - 특정 인덱스의 값을 즉시 수정 가능
        - 다른 요소들에 영향을 주지 않음.

    <img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbphKNP%2FbtsJDyFRLnJ%2FKGITXVSklzrzyEY4gc0vO0%2Fimg.png" width="844" height="160">

    * 삽입 (Insertion) - O(n)
        - 중간 삽입 시 뒤의 모든 요소를 이동시켜야 함.
        - 예: 5번째 위치에 삽입 -> 6 ~ 10번 요소를 한 칸씩 뒤로 이동

    <img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fr64nM%2FbtsJEUgAaFr%2FkeogcMz3YKRKHjIQeK94M0%2Fimg.png" width="819" height="294">

    * 삭제 (Deletion) - O(n)
        - 중간 삭제 시 모든 요소를 앞으로 이동
        - 예: 5번째 위치 삭제 -> 6 ~ 10번 요소 모두 한 칸씩 앞으로 이동

    <img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbehhFB%2FbtsJD0aMDDV%2FPspBPc8uDuARgvPspNtwO1%2Fimg.png" width="846" height="303">

2. 배열의 시작 복잡도 요약표
    * 접근 (O(1))
    * 수정 (O(1))
    * 삽입 (O(n))
    * 삭제 (O(n))

3. 배열의 종류
    1. 정적 배열 (Static Array)
        * 크기가 고정된 배열
        * 메모리 사용이 효율적
        * 크기 변경 불가
        * 예: C언어의 기본 배열

    2. 동적 배열 (Dynamic Array)
        * 크기가 가변적인 배열
        * 필요에 따라 크기 조정 가능
        * 메모리 재할당 필요
        * 예: C++의 vector, Java의 ArrayList

4. 심화 학습 내용
    1. 다차원 배열
        ```java
        // 2차원 배열 예시
        int[][] matrix = new int[3][4];
        ```
        - 행렬 구현에 적합
        - 그래프 표현 가능
        - 이미지 처리에 활용

    2. 언어별 특성
        - JavaScript
        ```javascript
        let arr = [];
        arr.push(1);
        arr.pop();
        ```

        - TypeScript
        ```typescript
        let numbers: number[] = [1, 2, 3];
        let matrix: number[][] = [[1, 2], [3, 4]];
        ```

        - Go
        ```go
        var arr [5]int              // 정적 배열
        slice := make([]int, 5)     // 슬라이스(동적 배열)
        ```

    3. 메모리 관리
        * 스택 메모리 vs 힙 메모리
        * 메모리 누수 방지
        * 가비지 컬렉션

    4. 오픈소스 예시
        ```java
        // ArrayList 구현 예시
        public class ArrayList<E> {
            private Object[] elementData;
            private int size;
            
            public ArrayList() {
                elementData = new Object[10];
                size = 0;
            }
            
            public boolean add(E e) {
                ensureCapacity(size + 1);
                elementData[size++] = e;
                return true;
            }
            
            private void ensureCapacity(int minCapacity) {
                if (minCapacity > elementData.length) {
                    int newCapacity = Math.max(minCapacity, elementData.length * 2);
                    elementData = Arrays.copyOf(elementData, newCapacity);
                }
            }
        }
        ```

    5. 배열의 장단점 예시
        * 장점
            * 빠른 접근 시간 O(1)
            * 간단한 구현
            * 메모리 효율성
            * 캐시 지역성

        * 단점
            * 크기 변경의 어려움(정적 배열)
            * 삽입/삭제의 비효율성
            * 메모리 낭비 가능성
            * 연속된 메모리 공간 필요

    6. 실전 활용 팁
        1. 데이터 크기가 고정적일 때 정적 배열 사용
        2. 빈번한 접근이 필요할 경우 배열 선호
        3. 삽입/삭제가 빈번한 경우 다른 자료구조 고려
        4. 캐시 효율성을 고려한 배치

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
    1. Java
        ```java
        public class LinkedList<T> {
            private class Node {
                T data;
                Node next;
                
                Node(T data) {
                    this.data = data;
                    this.next = null;
                }
            }
            
            private Node head;
            private int size;
            
            public LinkedList() {
                head = null;
                size = 0;
            }
            
            // 노드 추가
            public void add(T data) {
                Node newNode = new Node(data);
                if (head == null) {
                    head = newNode;
                } else {
                    Node current = head;
                    while (current.next != null) {
                        current = current.next;
                    }
                    current.next = newNode;
                }
                size++;
            }
            
            // 특정 위치에 노드 삽입
            public void insert(int position, T data) {
                if (position < 0 || position > size) {
                    throw new IndexOutOfBoundsException();
                }
                
                Node newNode = new Node(data);
                if (position == 0) {
                    newNode.next = head;
                    head = newNode;
                } else {
                    Node current = head;
                    for (int i = 0; i < position - 1; i++) {
                        current = current.next;
                    }
                    newNode.next = current.next;
                    current.next = newNode;
                }
                size++;
            }
            
            // 노드 삭제
            public boolean remove(T data) {
                if (head == null) return false;
                
                if (head.data.equals(data)) {
                    head = head.next;
                    size--;
                    return true;
                }
                
                Node current = head;
                while (current.next != null) {
                    if (current.next.data.equals(data)) {
                        current.next = current.next.next;
                        size--;
                        return true;
                    }
                    current = current.next;
                }
                return false;
            }
            
            // 노드 검색
            public boolean contains(T data) {
                Node current = head;
                while (current != null) {
                    if (current.data.equals(data)) {
                        return true;
                    }
                    current = current.next;
                }
                return false;
            }
            
            // 리스트 크기 반환
            public int size() {
                return size;
            }
        }
        ```

    2. TypeScript
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

    3. Golang
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

# 해시 테이블 (Hash Table)

1. 해시 테이블의 개념
    1. 기본 개념

        * 해시 테이블은 (Key, Value) 쌍으로 데이터를 저장하는 자료구조로, 빠른 데이터 검색이 가능하다.
        
        * 해시 테이블이 빠른 검색속도를 제공하는 이유는 내부적으로 배열(버킷)을 사용하여 데이터를 저장하기 때문입니다. 해시 테이블은 각각의 Key값에 해시함수를 적용해
            배열의 고유한 index를 생성하고, 이 index를 활용해 값을 저장하거나 검색하게 된다. 여기서 실제 값이 저장되는 장소를 버킷 또는 슬롯이라고 한다.

        * 해시 테이블의 평균 시간복잡도는 O(1)이다.

        * 해시 테이블 구조
            <img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fb1zOw1%2FbtqL6HAW7jy%2FjpBA5pPkQFnfiZcPLakg00%2Fimg.png">
            * Key, Hash Function, Hash, Value, 저장소(Bucket, Slot)로 구성
            * Key
                * 고유한 값
                * 저장 공간의 효율성을 위해 Hash Function에 입력하여 Hash로 변경 후 저장
                * Key는 길이가 다양하기 때문에 그대로 저장하면 다양한 길이만큼 저장소 구성이 필요
            * Hash Function
                * Key를 Hash로 바꿔주는 역할
                * 해시 충돌(서로 다른 Key가 같은 Hash가 되는 경우)이 발생할 확률을 최대한 줄이는 함수를 만드는 것이 중요
            * Hash
                * Hash Function의 결과
                * 저장소에서 Value와 매칭되어 저장
            * Value
                * 저장소에 최종적으로 저장되는 값
                * 키와 매칭되어 저장, 삭제, 검색, 접근 가능

        * 해시 테이블 동작 과정
            1. Key -> Hash Function -> Hash Function 결과 = Hash
            2. Hash를 배열의 Index로 사용
            3. 해당 Index에 Value 저장
            * HashTable 크기가 10이라면 A라는 Key의 Value를 찾을 때 hashFunction("A") % 10 연산을 통해 인덱스 값 계산하여 Value 조회

        * Hash 충돌
            * 서로 다른 Key가 Hash Function에서 중복 Hash로 나오는 경우
            * 충돌이 많아질수록 탐색의 시간 복잡도가 O(1)에서 O(n)으로 증가

    2. 해시 함수
        * 해시 함수는 키를 고유한 인덱스로 변환하는 함수입니다.

        * 주요 해시 함수:
            * Division Method: `index = key % table_size`
                * 나눗셈을 이용하는 방법으로 입력값을 테이블의 크기로 나누어 계산한다. (주소 = 입력값 % 테이블의 크기) 테이블의 크기를 소수로 정하고 2의 제곱수와 먼 값을 사용해야 효과가 좋다고 알려져있다.
            * Digit Folding: ASCII 코드 변환 후 합산
                * 각 Key의 문자열을 ASCII 코드로 바꾸고 값을 합한 데이터를 테이블 내의 주소로 사용하는 방법이다.
            * Multiplication Method: `h(k) = (kA mod 1) x m`
                * 숫자로 된 Key값 K와 0과 1사이의 실수 A, 보통 2의 제곱수인 m을 사용하여 위와 같은 계산을 한다.
            * Universal Hashing: 다수의 해시함수 중 무작위 선택
                * 다수의 해시함수를 만들어 집합 H에 넣어두고, 무작위로 해시함수를 선택해 해시값을 만드는 기법이다.

    3. 해시 (Hash)값이 충돌하는 경우
        * 간혹 해시 테이블이 충돌하는 경우가 있는데 이 경우 `분리 연결법(Separate Chaining)과 개방 주소법(Open Addressing)` 크게 2가지로 해결하고 있다.

        1. 분리 연결법(Separate Chaining)
            <img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbTF67c%2FbtqL7xx3OGw%2FDM8KEKU5x7dx6Nks4JR7K1%2Fimg.png">

            - Separate Chaining이란 동일한 버킷의 데이터에 대해 자료구조를 활용해 추가 메모리를 사용하여 다음 데이터의 주소를 저장하는 것이다.
            위의 그림과 같이 동일한 버킷으로 접근을 한다면 데이터들을 연결해서 관리해주고 있다. 실제로 Java8의 Hash 테이블은 Self-Balancing Binary Search Tree 자료구조를 사용해
            Chaining 방식을 구현하였다. 이러한 Chaining방식은 해시 테이블의 확장이 필요 없고 구현이 간단하며, 손쉽게 삭제할 수 있다는 장점이 있지만 데이터의 수가 많아지면 버킷에 Chaining되는
            데이터가 많아지며 그에 따라 캐시 효율성이 감소한다.

        2. 개방 주소법(Open Addressing)
            * Open Addressing이란 추가적인 메모리를 사용하는 Chaining 방식과 다르게 비어있는 해시 테이블의 공간을 활용하는 방법이다.
            Open Addressing을 구현하기 우한 대표적인 방법으로는 3가지 방식이 존재한다.

            1. Linear Probing: 현재의 버킷 index로부터 고정폭 만큼씩 이동하여 차례대로 검색해 비어있는 버킷에 데이터를 저장한다.

            2. Quadratic Probing: 해시의 저장순서 폭을 제곱으로 저장하는 방식이다. 예를 들어 처음 충돌이 발생한 경우에는 1만큼 이동하고 그 다음 계속
            충돌이 발생하면 2^2, 3^2 칸씩 옮기는 방식이다.

            3. Double Hashing Probing: 해시된 값을 한 번 더 해싱하여 해시의 규칙성을 없애버리는 방식이다. 해시된 값을 한 번 더 해싱하여 새로운 주소를 할당하기 때문에
            다른 방법들보다 많은 연산을 하게 된다.

            <img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FWR1fv%2FbtqL5APCcSa%2FBZN6wvxUXzJBEiOfOMLfR0%2Fimg.png">

            * Open Addressing에서 데이터를 삭제하면 삭제된 공간은 Dummy Space로 활용되는데, 그렇기 때문에 `Hash Table을 재정리 해주는 작업`이 필요하다고 한다.

        3. Resizing
            * 저장 공간이 일정 수준 채워지면 Separate Chaining의 경우 성능 향상을 위해, Open Addressing의 경우 배열 크기 확장을 위해 Resizing
            * 보통 두 배로 확장함
            * 확장 임계점은 현재 데이터 개수가 Hash Bucket 개수의 75%가 될 때

    4. 해시 테이블의 장점
         * 적은 리소스로 많은 데이터를 효율적으로 관리 가능
            * ex. HDD. Cloud에 있는 많은 데이터를 Hash로 매핑하여 작은 크기의 시 메모리로 프로세스 관리 가능

        * 배열의 인덱스를 사용하기 때문에 빠른 검색, 삽입, 삭제 (O(1))
            * HashTable의 경우 인덱스는 데이터의 고유 위치이기 때문에 삽입 삭제 시 다른 데이터를 이동할 필요가 없어 삽입, 삭제도 빠른 속도 가능

        * Key와 Hash에 연관성이 없어 보안 유리
        
        * 데이터 캐싱에 많이 사용
            * get, put 기능에 캐시 로직 추가 시 자주 hit하는 데이터 바로 검색 가능\

        * 중복 제거 유용

    5. 해시 테이블의 단점
        * HashTable 단점
        * 충돌 발생 가능성
        * 공간 복잡도 증가
        * 순서 무시
        * 해시 함수에 의존

    6. HashTable vs HashMap
        * Key-Value 구조 및 Key에 대한 Hash로 Value 관리하는 것은 동일
        * HashTable
            * 동기
            * Key-Value 값으로 null 미허용 (Key가 hashcode(), equals()를 사용하기 때문)
            * 보조 Hash Function과 separating Chaining을 사용해서 비교적 충돌 덜 발생 (Key의 Hash 변형)
        * HashMap
            * 비동기 (멀티 스레드 환경에서 주의)
            * Key-Value 값으로 null 허용

    7. HashTable 성능

    | |평균|최악|
    |----|----|----|
    |탐색|O(1)|O(N)|
    |삽입|O(1)|O(N)|
    |삭제|O(1)|O(N)|

# 스택 (Stack)

1. 스택의 개념
    * 스택(Stack)은 데이터가 차곡차곡 쌓이는 형태의 자료구조로 LIFO(Last In First Out)원칙을 따릅니다. 즉, 마지막에 추가된 데이터가 가장 먼저 제거됩니다.

    * 일상 생활에서의 예시:
        * 접시 쌓기: 새로운 접시는 맨 위에 놓이고, 사용할 때도 맨 위의 접시부터 꺼냅니다.
        * 서류 더미: 새로운 서류를 맨 위에 놓이고, 처리할 때도 맨 위의 서류부터 처리합니다.

2. 스택의 연산
    * 스택은 기본적으로 다음과 같은 연산을 지원합니다.
        * `push(item)`: 스택의 맨 위에 `item`을 추가합니다.
        * `pop()`: 스택의 맨 위에 있는 아이템을 제거하고 반환합니다.
        * `peek()`: 스택의 맨 위에 있는 아이템을 반환하지만 제거하지는 않습니다.
        * `isEmpty()`: 스택이 비어 있는지 확인합니다.

3. 스택의 구현
    * 배열 기반의 스택 구현
        1. Java
            ```java
            public class ArrayStack<T> {
                private T[] array;
                private int top;
                private static final int DEFAULT_SIZE = 10;
                
                @SuppressWarnings("unchecked")
                public ArrayStack() {
                    array = (T[]) new Object[DEFAULT_SIZE];
                    top = -1;
                }
                
                public void push(T item) {
                    if (top == array.length - 1) {
                        resize();
                    }
                    array[++top] = item;
                }
                
                public T pop() {
                    if (isEmpty()) {
                        throw new IllegalStateException("Stack is empty");
                    }
                    T item = array[top];
                    array[top--] = null;
                    return item;
                }
                
                private void resize() {
                    T[] newArray = (T[]) new Object[array.length * 2];
                    System.arraycopy(array, 0, newArray, 0, array.length);
                    array = newArray;
                }
                
                public boolean isEmpty() {
                    return top == -1;
                }
            }
            ```

        2. TypeScript
            ```typescript
            class ArrayStack<T> {
                private items: T[];
                private top: number;
                private readonly initialCapacity: number = 10;
                
                constructor() {
                    this.items = new Array<T>(this.initialCapacity);
                    this.top = -1;
                }
                
                push(item: T): void {
                    if (this.top === this.items.length - 1) {
                        this.resize();
                    }
                    this.items[++this.top] = item;
                }
                
                pop(): T | undefined {
                    if (this.isEmpty()) {
                        return undefined;
                    }
                    const item = this.items[this.top];
                    this.items[this.top--] = undefined!;
                    return item;
                }
                
                private resize(): void {
                    const newItems = new Array<T>(this.items.length * 2);
                    for (let i = 0; i < this.items.length; i++) {
                        newItems[i] = this.items[i];
                    }
                    this.items = newItems;
                }
                
                isEmpty(): boolean {
                    return this.top === -1;
                }
            }
            ```

        3. Golang
            ```go
            package stack

            type ArrayStack struct {
                items []interface{}
                top   int
            }

            func NewArrayStack() *ArrayStack {
                return &ArrayStack{
                    items: make([]interface{}, 0),
                    top:   -1,
                }
            }

            func (s *ArrayStack) Push(item interface{}) {
                s.items = append(s.items, item)
                s.top++
            }

            func (s *ArrayStack) Pop() interface{} {
                if s.IsEmpty() {
                    return nil
                }
                item := s.items[s.top]
                s.items = s.items[:s.top]
                s.top--
                return item
            }

            func (s *ArrayStack) IsEmpty() bool {
                return s.top == -1
            }
            ```

    * 연결 리스트 기반의 스택 구현
        1. Java
            ```java
            public class LinkedStack<T> {
                private class Node {
                    T data;
                    Node next;
                    
                    Node(T data) {
                        this.data = data;
                    }
                }
                
                private Node top;
                private int size;
                
                public void push(T item) {
                    Node newNode = new Node(item);
                    newNode.next = top;
                    top = newNode;
                    size++;
                }
                
                public T pop() {
                    if (isEmpty()) {
                        throw new IllegalStateException("Stack is empty");
                    }
                    T item = top.data;
                    top = top.next;
                    size--;
                    return item;
                }
                
                public boolean isEmpty() {
                    return top == null;
                }
                
                public int size() {
                    return size;
                }
            }
            ```

        2. TypeScript
            ```typescript
            class LinkedStack<T> {
                private class Node {
                    data: T;
                    next: Node | null;
                    
                    constructor(data: T) {
                        this.data = data;
                        this.next = null;
                    }
                }
                
                private top: Node | null = null;
                private size: number = 0;
                
                push(item: T): void {
                    const newNode = new Node(item);
                    newNode.next = this.top;
                    this.top = newNode;
                    this.size++;
                }
                
                pop(): T | undefined {
                    if (this.isEmpty()) {
                        return undefined;
                    }
                    const item = this.top!.data;
                    this.top = this.top!.next;
                    this.size--;
                    return item;
                }
                
                isEmpty(): boolean {
                    return this.top === null;
                }
                
                getSize(): number {
                    return this.size;
                }
            }
            ```

        3. Golang
            ```go
            type Node struct {
                data interface{}
                next *Node
            }

            type LinkedStack struct {
                top  *Node
                size int
            }

            func NewLinkedStack() *LinkedStack {
                return &LinkedStack{}
            }

            func (s *LinkedStack) Push(item interface{}) {
                newNode := &Node{data: item}
                newNode.next = s.top
                s.top = newNode
                s.size++
            }

            func (s *LinkedStack) Pop() interface{} {
                if s.IsEmpty() {
                    return nil
                }
                item := s.top.data
                s.top = s.top.next
                s.size--
                return item
            }

            func (s *LinkedStack) IsEmpty() bool {
                return s.top == nil
            }

            func (s *LinkedStack) Size() int {
                return s.size
            }
            ```

4. 스택의 사용 사례
    * 재귀 알고리즘
        * 재귀 알고리즘 호출 시 함수 호출 스택이 사용됩니다. 각 함수 호출은 스택 프레임에 저장되며, 함수가 종료되면 스택에서 제거됩니다.

        * 예제: 재귀함수
            ```python
            def recursive(data):
                if data < 0:
                    print('ended')
                else:
                    print(data)
                    recursive(data - 1)
                    print('returned', data)

            recursive(3)
            ```
            * 출력 결과:
                ```bash
                3
                2
                1
                0
                ended
                returned 0
                returned 1
                returned 2
                returned 3
                ```

    * 웹 브라우저의 방문 기록
        * 뒤로 가기: 방문한 페이지들을 스택에 저장하여 이전 페이지로 돌아갈 수 있습니다.
        * 언어별 구현
            1. Java
                ```java
                public class BrowserHistory {
                    private Stack<String> backStack = new Stack<>();
                    private Stack<String> forwardStack = new Stack<>();
                    
                    public void visit(String url) {
                        backStack.push(url);
                        forwardStack.clear(); // 새로운 페이지 방문 시 forward 기록 삭제
                    }
                    
                    public String back() {
                        if (backStack.size() <= 1) return backStack.peek();
                        
                        forwardStack.push(backStack.pop());
                        return backStack.peek();
                    }
                    
                    public String forward() {
                        if (forwardStack.isEmpty()) return backStack.peek();
                        
                        String url = forwardStack.pop();
                        backStack.push(url);
                        return url;
                    }
                }
                ```

            2. TypeScript
                ```typescript
                class BrowserHistory {
                    private backStack: string[] = [];
                    private forwardStack: string[] = [];
                    
                    visit(url: string): void {
                        this.backStack.push(url);
                        this.forwardStack = [];
                    }
                    
                    back(): string | undefined {
                        if (this.backStack.length <= 1) return this.backStack[this.backStack.length - 1];
                        
                        const current = this.backStack.pop()!;
                        this.forwardStack.push(current);
                        return this.backStack[this.backStack.length - 1];
                    }
                    
                    forward(): string | undefined {
                        if (this.forwardStack.length === 0) return this.backStack[this.backStack.length - 1];
                        
                        const url = this.forwardStack.pop()!;
                        this.backStack.push(url);
                        return url;
                    }
                }
                ```

            3. Golang
                ```go
                type BrowserHistory struct {
                    backStack    []string
                    forwardStack []string
                }

                func NewBrowserHistory() *BrowserHistory {
                    return &BrowserHistory{
                        backStack:    make([]string, 0),
                        forwardStack: make([]string, 0),
                    }
                }

                func (bh *BrowserHistory) Visit(url string) {
                    bh.backStack = append(bh.backStack, url)
                    bh.forwardStack = make([]string, 0)
                }

                func (bh *BrowserHistory) Back() string {
                    if len(bh.backStack) <= 1 {
                        return bh.backStack[len(bh.backStack)-1]
                    }
                    
                    current := bh.backStack[len(bh.backStack)-1]
                    bh.backStack = bh.backStack[:len(bh.backStack)-1]
                    bh.forwardStack = append(bh.forwardStack, current)
                    return bh.backStack[len(bh.backStack)-1]
                }
                ```
    * 실행 취소 기능
        * Undo 기능: 사용자 동작을 스택에 저장하여 이전 상태로 복구할 수 있습니다.
        * 언어별 구현
            1. java
                ```java
                public class UndoManager<T> {
                    private Stack<T> undoStack = new Stack<>();
                    private Stack<T> redoStack = new Stack<>();
                    
                    public void doAction(T action) {
                        undoStack.push(action);
                        redoStack.clear();
                    }
                    
                    public T undo() {
                        if (undoStack.isEmpty()) {
                            throw new IllegalStateException("No actions to undo");
                        }
                        T action = undoStack.pop();
                        redoStack.push(action);
                        return action;
                    }
                    
                    public T redo() {
                        if (redoStack.isEmpty()) {
                            throw new IllegalStateException("No actions to redo");
                        }
                        T action = redoStack.pop();
                        undoStack.push(action);
                        return action;
                    }
                }
                ```

            2. TypeScript
                ```typescript
                class UndoManager<T> {
                    private undoStack: T[] = [];
                    private redoStack: T[] = [];
                    
                    doAction(action: T): void {
                        this.undoStack.push(action);
                        this.redoStack = [];
                    }
                    
                    undo(): T | undefined {
                        if (this.undoStack.length === 0) {
                            throw new Error("No actions to undo");
                        }
                        const action = this.undoStack.pop()!;
                        this.redoStack.push(action);
                        return action;
                    }
                    
                    redo(): T | undefined {
                        if (this.redoStack.length === 0) {
                            throw new Error("No actions to redo");
                        }
                        const action = this.redoStack.pop()!;
                        this.undoStack.push(action);
                        return action;
                    }
                }
                ```

            3. Golang
                ```go
                type UndoManager struct {
                    undoStack []interface{}
                    redoStack []interface{}
                }

                func NewUndoManager() *UndoManager {
                    return &UndoManager{
                        undoStack: make([]interface{}, 0),
                        redoStack: make([]interface{}, 0),
                    }
                }

                func (um *UndoManager) DoAction(action interface{}) {
                    um.undoStack = append(um.undoStack, action)
                    um.redoStack = make([]interface{}, 0)
                }

                func (um *UndoManager) Undo() interface{} {
                    if len(um.undoStack) == 0 {
                        return nil
                    }
                    
                    action := um.undoStack[len(um.undoStack)-1]
                    um.undoStack = um.undoStack[:len(um.undoStack)-1]
                    um.redoStack = append(um.redoStack, action)
                    return action
                }
                ```
    * 수식의 괄호 검사
        * 괄호 짝 맞추기: 여는 괄호를 스택에 저장하고, 닫는 괄호를 만나면 스택에서 꺼내어 짝이 맞는지 확인합니다.
        * 언어별 구현
            1. Java
                ```java
                public class BracketChecker {
                    public boolean isValid(String s) {
                        Stack<Character> stack = new Stack<>();
                        Map<Character, Character> brackets = Map.of(
                            ')', '(',
                            '}', '{',
                            ']', '['
                        );
                        
                        for (char c : s.toCharArray()) {
                            if (brackets.containsValue(c)) {
                                stack.push(c);
                            } else if (brackets.containsKey(c)) {
                                if (stack.isEmpty() || stack.pop() != brackets.get(c)) {
                                    return false;
                                }
                            }
                        }
                        
                        return stack.isEmpty();
                    }
                }
                ```

            2. TypeScript
                ```typescript
                class BracketChecker {
                    isValid(s: string): boolean {
                        const stack: string[] = [];
                        const brackets: Map<string, string> = new Map([
                            [')', '('],
                            ['}', '{'],
                            [']', '[']
                        ]);
                        
                        for (const char of s) {
                            if (['{', '[', '('].includes(char)) {
                                stack.push(char);
                            } else if (brackets.has(char)) {
                                if (stack.length === 0 || stack.pop() !== brackets.get(char)) {
                                    return false;
                                }
                            }
                        }
                        
                        return stack.length === 0;
                    }
                }
                ```

            3. Golang
                ```go
                func isValid(s string) bool {
                    stack := make([]rune, 0)
                    brackets := map[rune]rune{
                        ')': '(',
                        '}': '{',
                        ']': '[',
                    }
                    
                    for _, char := range s {
                        if char == '(' || char == '{' || char == '[' {
                            stack = append(stack, char)
                        } else if opening, exists := brackets[char]; exists {
                            if len(stack) == 0 || stack[len(stack)-1] != opening {
                                return false
                            }
                            stack = stack[:len(stack)-1]
                        }
                    }
                    
                    return len(stack) == 0
                }
                ```
    * 후위 표기법 계산
        * 표현식 평가: 연산자와 피연산자를 스택에 저장하여 후위 표기식을 계산합니다.

5. 스택의 장점과 단점
    * 장점
        * 간단한 구현: 구조가 단순하여 구현이 쉽습니다.
        * 데이터 역순 처리: 후입선출이 필요한 상황에서 유용합니다.
        * 메모리 효율성: 연속된 메모리 공간을 사용하여 캐시 적중률이 높습니다.

    * 단점
        * 임의 접근 불가: 중간에 있는 요소에 직접 접근할 수 없습니다.
        * 크기 제한: 고정 크기의 스택은 오버플로우 위험이 있습니다.
        * 오버플로우/언더플로우: 스택이 가득 찼거나 비었을 떄 오류가 발생할 수 있습니다.

6. 심화 내용
    * 스택 오버플로우와 언더플로우
        * 스택 오버플로우(Stack Overflow): 스택이 가득 찬 상태에서 `push`연산을 수행하면 발생합니다.
        * 스택 언더플로우(Stack Underflow): 스택이 비어 있는데 `pop`연산을 수행하면 발생합니다.

        - 예외처리 예제:

    * 스택을 이용한 알고리즘 문제
        * 예제: DFS(깊이 우선 탐색)
        * 언어별 구현
            1. Java
                ```java
                public class DFS {
                    public void dfs(Graph graph, int start) {
                        boolean[] visited = new boolean[graph.V];
                        Stack<Integer> stack = new Stack<>();
                        
                        stack.push(start);
                        
                        while (!stack.isEmpty()) {
                            int vertex = stack.pop();
                            
                            if (!visited[vertex]) {
                                visited[vertex] = true;
                                System.out.print(vertex + " ");
                                
                                for (int adj : graph.getAdjacent(vertex)) {
                                    if (!visited[adj]) {
                                        stack.push(adj);
                                    }
                                }
                            }
                        }
                    }
                }
                ```

            2. TypeScript
                ```typescript
                class DFS {
                    dfs(graph: Map<number, number[]>, start: number): void {
                        const visited = new Set<number>();
                        const stack: number[] = [];
                        
                        stack.push(start);
                        
                        while (stack.length > 0) {
                            const vertex = stack.pop()!;
                            
                            if (!visited.has(vertex)) {
                                visited.add(vertex);
                                console.log(vertex);
                                
                                const adjacent = graph.get(vertex) || [];
                                for (const adj of adjacent) {
                                    if (!visited.has(adj)) {
                                        stack.push(adj);
                                    }
                                }
                            }
                        }
                    }
                }
                ```

            3. Golang
                ```go
                type Graph struct {
                    vertices map[int][]int
                }

                func NewGraph() *Graph {
                    return &Graph{
                        vertices: make(map[int][]int),
                    }
                }

                func (g *Graph) DFS(start int) {
                    visited := make(map[int]bool)
                    stack := []int{start}
                    
                    for len(stack) > 0 {
                        vertex := stack[len(stack)-1]
                        stack = stack[:len(stack)-1]
                        
                        if !visited[vertex] {
                            visited[vertex] = true
                            fmt.Printf("%d ", vertex)
                            
                            for _, adj := range g.vertices[vertex] {
                                if !visited[adj] {
                                    stack = append(stack, adj)
                                }
                            }
                        }
                    }
                }
                ```
7. 정리
    * 스택은 단순하지만 강력한 자료구조로, 다양한 분야에서 활용됩니다. 스택의 기본 원리인 LIFO는 많은 알고리즘과 시스템에서
    핵심적인 역할을 합니다.

    * 핵심 개념: LIFO(Last In First Out)
    * 주요 사용 사례: 재귀 호출, 실행 취소 기능, 수식 계산, 괄호 검사 등
    * 장점: 간단한 구현, 역순 처리에 용이
    * 단점: 임의 접근 불가, 크기 제한